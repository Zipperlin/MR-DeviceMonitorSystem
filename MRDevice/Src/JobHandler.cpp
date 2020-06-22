/* Time: <@(#)JobHandler.cpp   2009-3-5 - 10:47:11   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : JobHandler.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The job handler class
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:47:11		FanZF	Creation
 *
 *********************************************************************
 */

// JobHandler.cpp: implementation of the CJobHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JobHandler.h"
#include "Transfer.h"
#include "Burner.h"
#include "DiscImport.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CJobHandler* CJobHandler::m_pInstance = NULL;


DWORD WINAPI JobQueueHandleThreadProc(LPVOID lpParam) 
{ 
//	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CJobHandler* pHandler = (CJobHandler*)lpParam;

		if (pHandler->HandleJobQueue())
		{
			return THREADE_RET_CODE_OK;
		}
		else
		{
			return THREADE_RET_CODE_ERROR;
		}
	}

	PA_CATCH_ERROR_RET(THREADE_RET_CODE_ERROR)

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJobHandler::CJobHandler()
{
	m_bActive = FALSE;

	m_hEvent = NULL;
	m_hJobQueueHandleThread = NULL;
	m_pCurrentJob = NULL;
}

CJobHandler::~CJobHandler()
{

}

CJobHandler* CJobHandler::GetInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new CJobHandler;
	}

	return m_pInstance;
}

void CJobHandler::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

BOOL CJobHandler::Init()
{

	PRINTTRACE_ENTER_FUNCTION
		
	m_bActive = TRUE;
	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	m_hJobQueueHandleThread = CreateThread(NULL, 0, JobQueueHandleThreadProc, this, 0, NULL);
	if (NULL == m_hJobQueueHandleThread)
	{
		ARCHVTRACE_ERROR("create PrintJobQueueThreadProc failed")
		return FALSE;
	}
	else
	{
		ARCHVTRACE_INFO("create PrintJobQueueThreadProc")
		return TRUE;
	}
}


BOOL CJobHandler::UnInit()
{
	m_bActive = FALSE;
	if (m_hEvent)
		SetEvent(m_hEvent);

	//<< 指示当前任务被取消
	if ((NULL != m_pCurrentJob) && (enumJobState_Executing == m_pCurrentJob->enumJobState))
	{
		m_pCurrentJob->bCancelFlag = TRUE;
	}

	//<< 任务线程的结束
	if (m_hJobQueueHandleThread)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(m_hJobQueueHandleThread, SHUTDOWN_JOB_HANDLER_JOB_QUEUE_EXIT_WAIT_TIME))
		{
			PRINTTRACE_INFO("m_hJobQueueHandleThread thread already exit")
		}
		else
		{
			if (TerminateThread(m_hJobQueueHandleThread, 0))
			{
				//<< 任务被提前终止，需设置其状态为“已取消”
				if (enumJobState_Executing == m_pCurrentJob->enumJobState)
				{
					m_pCurrentJob->SetDetail(JOB_DETAIL_CANCELLED);
					m_pCurrentJob->SetProgress(enumJobProgressUsing_None);
					m_pCurrentJob->SetState(enumJobState_Cancelled);

					//<< 若是DiscImport任务，则需取消未完成的子任务
					if (enumJobType_DiscImportJob == m_pCurrentJob->enumJobType)
					{
						if (!CDiscImport::GetInstance()->CancelDiscImportJob(m_pCurrentJob))
						{
							PRINTTRACE_ERROR("CDiscImport::GetInstance()->CancelSubmittedDiscImportJob(m_pCurrentJob)")
						}
					}
				}
				PRINTTRACE_INFO("Terminate m_hJobQueueHandleThread thread")
			}
			else
			{
				PRINTTRACE_ERROR("Terminate m_hJobQueueHandleThread thread")
			}
		}

		CloseHandle(m_hJobQueueHandleThread);
		m_hJobQueueHandleThread = NULL;
	}

	if (m_hEvent)
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}

	//<< 将队列中状态为Submitted的任务置为Cancelled
	while (TRUE)
	{
		PAJob* pJob = m_JobQueue.GetASubmittedJob();
		if (NULL != pJob)
		{
			if (enumJobState_Submitted == pJob->enumJobState)
			{
				pJob->bCancelFlag = TRUE;
				pJob->SetDetail(JOB_DETAIL_CANCELLED);
				pJob->SetProgress(enumJobProgressUsing_None);
				pJob->SetState(enumJobState_Cancelled);

				//<< 若是DiscImport任务，则需取消未完成的子任务
				if (enumJobType_DiscImportJob == pJob->enumJobType)
				{
					if (!CDiscImport::GetInstance()->CancelDiscImportJob(m_pCurrentJob))
					{
						PRINTTRACE_ERROR("CDiscImport::GetInstance()->CancelSubmittedDiscImportJob(m_pCurrentJob)")
					}
				}
			}
		}
		else
		{
			break;
		}
	}

	//<<清空队列
	if (!m_JobQueue.ClearQueque())
	{
		ARCHVTRACE_ERROR("m_JobQueue.ClearQueque() failed")
	}
	else
	{
		ARCHVTRACE_INFO("m_JobQueue.ClearQueque() succeed")
	}
	
	return TRUE;
}

BOOL CJobHandler::HandleJobQueue()
{
	CString strTrace;

	while(TRUE)
	{
		if (m_JobQueue.HasSubmittedJob())
		{
			SetEvent(m_hEvent);
		}

		if (WAIT_OBJECT_0 == WaitForSingleObject(m_hEvent, INFINITE))
		{
			// 是否需要退出
			if (!m_bActive)
			{
				PRINTTRACE_INFO("HandlePrintJobQueue will exit for: enumSubModuleState_UnInitializing == m_SubModuleState")
				return TRUE;
			}

			// 开始任务状态保护，以防止取消、删除任务时可能出现的状态设置紊乱
			CSingleLock sLock(&m_CSLockJobState);
			sLock.Lock();

			m_pCurrentJob = m_JobQueue.GetASubmittedJob();
			if (NULL == m_pCurrentJob)
			{
				//no Job in job queue

				//<< 结束状态保护
				sLock.Unlock();

				PRINTTRACE_INFO("m_pCurrentJob = m_JobQueue.GetASubmittedJob(), but NULL == m_pCurrentJob")
				continue;
			}
			else
			{
				CString strTrace = _T("Got a submitted job which JobID is<none for InitJob>: ");
				strTrace += m_pCurrentJob->strJobID;
				PRINTTRACE_INFO(strTrace)
			}

			// got a job, so handle it
			switch (m_pCurrentJob->enumJobType)
			{
			case enumJobType_BurnJob:
				{
					CBurner::GetInstance()->SetSubModuleState(enumSubModuleState_Work);

					//<< 设置状态
					m_pCurrentJob->SetState(enumJobState_Executing);
					//<< 结束状态保护
					sLock.Unlock();

					if (CBurner::GetInstance()->HandleJob(m_pCurrentJob))
					{
						PRINTTRACE_INFO("CBurner::GetInstance()->HandleJob(m_pCurrentJob, &m_DcmPartner)")
					}
					else
					{
						PRINTTRACE_ERROR("CBurner::GetInstance()->HandleJob(m_pCurrentJob, &m_DcmPartner)")
					}
					CBurner::GetInstance()->SetSubModuleState(enumSubModuleState_Ready);
				}
				break;
			case enumJobType_AutoSendJob:
				//<< Just as ManualSendJob
			case enumJobType_ManualSendJob:
				{
					CTransfer::GetInstance()->SetSubModuleState(enumSubModuleState_Work);

					//<< 设置状态
					m_pCurrentJob->SetState(enumJobState_Executing);
					//<< 结束状态保护
					sLock.Unlock();

					if (CTransfer::GetInstance()->HandleJob(m_pCurrentJob))
					{
						PRINTTRACE_INFO("CTransfer::GetInstance()->HandleJob(m_pCurrentJob, &m_DcmPartner)")
					}
					else
					{
						PRINTTRACE_ERROR("CTransfer::GetInstance()->HandleJob(m_pCurrentJob, &m_DcmPartner)")
					}
					CTransfer::GetInstance()->SetSubModuleState(enumSubModuleState_Ready);
				}
				break;
			case enumJobType_DiscImportJob:
				{
					CDiscImport::GetInstance()->SetSubModuleState(enumSubModuleState_Work);

					//<< 设置状态
					m_pCurrentJob->SetState(enumJobState_Executing);
					//<< 结束状态保护
					sLock.Unlock();

					if (CDiscImport::GetInstance()->HandleJob(m_pCurrentJob))
					{
						PRINTTRACE_INFO("CDiscImport::GetInstance()->HandleJob(m_pCurrentJob, &m_DcmPartner)")
					}
					else
					{
						PRINTTRACE_ERROR("CDiscImport::GetInstance()->HandleJob(m_pCurrentJob, &m_DcmPartner)")
					}

					//<< 任务结束
					Notify(NOTIFY_IMPORT_ONE_JOB_FINISHED);
					CDiscImport::GetInstance()->SetSubModuleState(enumSubModuleState_Ready);
				}
				break;
			default:
				//<< 结束状态保护
				sLock.Unlock();

				strTrace.Format(_T("Unexpected Job type, enumJobType=%D"), m_pCurrentJob->enumJobType);
				PRINTTRACE_ERROR(strTrace)
				break;
			}

			m_pCurrentJob = NULL;
		}
	}
}

BOOL CJobHandler::PushJob(PAJob* pJob)
{
	if (NULL == pJob)
	{
		return FALSE;
	}

	if (m_JobQueue.PushJob(pJob))
	{
		pJob->Attach(this);
		SetEvent(m_hEvent);
		Notify(NOTIFY_JOB_QUEUE_CHANGED);
		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR("m_JobQueue.PushJob(pJob)")
		return FALSE;
	}

}

BOOL CJobHandler::GetJobList(JobInfo** ppJobInfoList, long *pLen)
{
	if (m_JobQueue.GetJobList(ppJobInfoList, pLen))
	{
		return TRUE;
	}
	else
	{
		ARCHVTRACE_ERROR("m_JobQueue.GetJobList(ppJobInfoList, pLen)")
		return FALSE;
	}
}

BOOL CJobHandler::GetSendJobInfo(LPCTSTR szJobID, JobInfo* pJobInfo, PSSIInfo** ppPSSIList, long* pPSSILen, NetworkNode** ppNodeList, long* pNodeLen, JobDetailStruct** ppDetailList, long* pDetailLen)
{
	if (NULL == szJobID)
	{
		return FALSE;
	}

	PAJob* pJob = m_JobQueue.GetJob(szJobID);
	if (NULL == pJob)
	{
		return FALSE;
	}

	if ((enumJobType_AutoSendJob != pJob->enumJobType) && 
		(enumJobType_ManualSendJob != pJob->enumJobType))
	{
		return FALSE;
	}

	if (!m_JobQueue.GetJobInfo(szJobID, pJobInfo))
	{
		return FALSE;
	}

	if (!GetJobPSSIInfo(pJob, ppPSSIList, pPSSILen))
	{
		return FALSE;
	}

	if (!GetJobNetworkNodeInfo(pJob, ppNodeList, pNodeLen))
	{
		return FALSE;
	}

	if (!GetJobDetailInfo(pJob, ppDetailList, pDetailLen))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CJobHandler::GetBurnJobInfo(LPCTSTR szJobID, JobInfo* pJobInfo, PSSIInfo** ppPSSIList, long* pPSSILen, JobDetailStruct** ppDetailList, long* pDetailLen)
{
	if (NULL == szJobID)
	{
		return FALSE;
	}

	PAJob* pJob = m_JobQueue.GetJob(szJobID);
	if (NULL == pJob)
	{
		return FALSE;
	}

	if (enumJobType_BurnJob != pJob->enumJobType)
	{
		return FALSE;
	}

	if (!m_JobQueue.GetJobInfo(szJobID, pJobInfo))
	{
		return FALSE;
	}

	if (!GetJobPSSIInfo(pJob, ppPSSIList, pPSSILen))
	{
		return FALSE;
	}

	if (!GetJobDetailInfo(pJob, ppDetailList, pDetailLen))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CJobHandler::GetDiscImportJobInfo(LPCTSTR szJobID, DiscImport_SeriesStruct** ppSeriesList, long* pLen)
{
	PAJob* pJob = m_JobQueue.GetJob(szJobID);
	if (NULL == pJob)
	{
		return FALSE;
	}
	
	if (enumJobType_DiscImportJob != pJob->enumJobType)
	{
		return FALSE;
	}
	
	*pLen = ((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported.size();
	if (0 == *pLen)
	{
		*ppSeriesList = NULL;
		return TRUE;
	}

	*ppSeriesList = (DiscImport_SeriesStruct*)CoTaskMemAlloc(sizeof(DiscImport_SeriesStruct) * (*pLen));
	for (int i = 0; i < *pLen; i++)
	{

		// 导入前序列信息
		(*ppSeriesList + i)->bsJobID = pJob->strJobID.AllocSysString();

		(*ppSeriesList + i)->bsIndex = ((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported[i].strIndex.AllocSysString();
		(*ppSeriesList + i)->bsPatientID = ((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported[i].strPatientID.AllocSysString();
		(*ppSeriesList + i)->bsPatientName = ((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported[i].strPatientName.AllocSysString();
		(*ppSeriesList + i)->bsStudyID = ((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported[i].strStudyID.AllocSysString();
		(*ppSeriesList + i)->bsSeriesID = ((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported[i].strSeriesID.AllocSysString();
		(*ppSeriesList + i)->bsImageID = ((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported[i].strImageID.AllocSysString();

		// 状态
		CString strState;
		switch (((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported[i].enumState)
		{
		case enumSeriesState_Waiting:
			strState = DISCIMPORT_SERIES_STATE_WAITING;
			break;
		case enumSeriesState_Importing:
			strState = DISCIMPORT_SERIES_STATE_IMPORTING;
			break;
		case enumSeriesState_Completed:
			strState = DISCIMPORT_SERIES_STATE_COMPLETED;
			break;
		case enumSeriesState_Skipped:
			strState = DISCIMPORT_SERIES_STATE_SKIPPED;
			break;
		case enumSeriesState_Failed:
			strState = DISCIMPORT_SERIES_STATE_FAILED;
			break;
		case enumSeriesState_Cancelled:
			strState = DISCIMPORT_SERIES_STATE_CANCELLED;
			break;
		default:
			strState = _T("");
			break;		
		}

		(*ppSeriesList + i)->bsState = _TT(strState).AllocSysString(); 

		// 进度
		(*ppSeriesList + i)->bsProgress = ((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported[i].strProgress.AllocSysString();

		// 详细信息
		(*ppSeriesList + i)->bsDetailInfo = ((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported[i].strDetailInfo.AllocSysString();
	}

	return TRUE;
}

BOOL CJobHandler::MoveJob(LPCTSTR szJobUID, BOOL bForward)
{
	BOOL bRet = TRUE;
	if (bForward)
	{
		bRet = m_JobQueue.MoveJobForward(szJobUID);
	}
	else
	{
		bRet = m_JobQueue.MoveJobBackward(szJobUID);
	}

	if (bRet)
	{
		Notify(NOTIFY_JOB_QUEUE_CHANGED);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CJobHandler::CancelJobs(vector<CString>* pvtrJobIDs)
{
	CSingleLock sLock(&m_CSLockJobState);
	sLock.Lock();

	for (int i = 0; i < pvtrJobIDs->size(); i++)
	{
		CString strJobID = (*pvtrJobIDs)[i];

		PAJob* pJob = m_JobQueue.GetJob(strJobID);
		if (NULL == pJob)
		{
			ARCHVTRACE_ERROR("No Job found with specified szJobID")
			sLock.Unlock();
			return FALSE;
		}
		else
		{
			if (enumJobState_Submitted == pJob->enumJobState)
			{
				pJob->bCancelFlag = TRUE;
				pJob->SetDetail(JOB_DETAIL_CANCELLED);
				pJob->SetProgress(enumJobProgressUsing_None);
				pJob->SetState(enumJobState_Cancelled);

				//<< 若是DiscImport任务，则需取消子任务
				if (enumJobType_DiscImportJob == pJob->enumJobType)
				{
					if (!CDiscImport::GetInstance()->CancelDiscImportJob(pJob))
					{
						PRINTTRACE_ERROR("CDiscImport::GetInstance()->CancelSubmittedDiscImportJob(pJob)")
					}
				}
				
				ARCHVTRACE_INFO("Set the UnCurrent Job State to be enumJobState_Cancelled")
				continue;
			}
			else if (enumJobState_Executing == pJob->enumJobState)
			{
				// 如果是刻录任务,则不作处理 [7/21/2009 gaoxing]
				if (enumJobType_BurnJob == pJob->enumJobType)
				{
					//UG提示  [7/22/2009 gaoxing]
					NotifyUG(IDS_NDMDR_GUI_FW_MainInfoPanel_ArchivingTask_CancelArchivingTaskJobs_Error_UG
						, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
					continue;
				}
				pJob->bCancelFlag = TRUE;
				//修改刻录功能，执行过程，不再进行取消操作 [7/22/2009 gaoxing]
// 				if (enumJobType_BurnJob == pJob->enumJobType)
// 				{
// 					CBurner::GetInstance()->AbortBurnWork();
// 				}
				continue;
			}
			else
			{
				ARCHVTRACE_WARNING("Can't Cancel the Burn Job since it's jobstate is Completed, Cancelled, or Failed")
				continue;
			}
		}
	}

	sLock.Unlock();
	return TRUE;
}

BOOL CJobHandler::DeleteJobs(vector<CString>* pvtrJobIDs)
{
	CSingleLock sLock(&m_CSLockJobState);
	sLock.Lock();

	BOOL bCertainJobIsDeleted = FALSE;
	BOOL bCertainJobCantBeDeleted = FALSE;

	for (int i = 0; i < pvtrJobIDs->size(); i++)
	{
		CString strJobID = (*pvtrJobIDs)[i];

		PAJob* pJob = m_JobQueue.GetJob(strJobID);
		if (NULL == pJob)
		{
			ARCHVTRACE_ERROR("No Job found with specified szJobID")
			sLock.Unlock();
			return FALSE;
		}
		else
		{
			if (enumJobState_Submitted == pJob->enumJobState ||
				enumJobState_Executing == pJob->enumJobState)
			{
				bCertainJobCantBeDeleted = TRUE;
				continue;
			}
			else
			{
				//<< delete the Job
				pJob->Detach(this);
				int iErrCode = m_JobQueue.DeleteJob(strJobID);
				if (E_OK == iErrCode)
				{
					bCertainJobIsDeleted = TRUE;
				}
				else if (E_JOBQUEUE_CANT_DELETE_SUBMITTED_JOB == iErrCode ||
					E_JOBQUEUE_CANT_DELETE_EXECUTTING_JOB == iErrCode)
				{
					bCertainJobCantBeDeleted = TRUE;
				}
				else
				{
					;
				}
				continue;
			}
		}
	}

	if (bCertainJobCantBeDeleted)
	{
		NotifyUG(IDS_PRINTINGARCHIVING_SUBMITTED_OR_EXECUTING_JOB_CANT_BE_DELETED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
	}

	if (bCertainJobIsDeleted)
	{
		Notify(NOTIFY_JOB_QUEUE_CHANGED);
	}
	
	sLock.Unlock();
	return TRUE;
}

BOOL CJobHandler::IsPatientStudySeriesImageUIDInUse(PatientAdminUIDType enumUIDType, vector<CString>* pvtrUIDList)
{
	return m_JobQueue.IsPatientStudySeriesImageUIDInUse(enumUIDType, pvtrUIDList);
}

BOOL CJobHandler::IsUnfinishedJobExist(JobType enumJobType, BOOL* pbExist)
{
	return m_JobQueue.IsUnfinishedJobExist(enumJobType, pbExist);
}

void CJobHandler::NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive)
{ 
	UGNotifyStruct* pUGNStruct = new UGNotifyStruct; 
	pUGNStruct->iMessageID = (iMessageID);
	pUGNStruct->enumUGType = (enumUGType);
	pUGNStruct->enumGUIPriority = (enumGUIPriority);
	pUGNStruct->bActive = (bActive); 
	Notify(NOTIFY_USERGUIDANCE, (LPARAM)pUGNStruct);
}

LONG CJobHandler::HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam)
{

	Notify(uMessage, lParam, wParam);
	
	return E_OK;
}


BOOL CJobHandler::GetJobPSSIInfo(PAJob* pJob, PSSIInfo** ppPSSIInfo, long* plLen)
{
	if (NULL == pJob)
	{
		return FALSE;
	}

	PatientAdminUIDType enumUIDType = enumPatientAdminUIDType_Unknow;
	switch (pJob->enumJobType)
	{
	case enumJobType_BurnJob:
		enumUIDType = ((BurnJobSettingsStruct*)pJob->pData)->enumUIDType;
		break;
	case enumJobType_AutoSendJob:
	case enumJobType_ManualSendJob:
		enumUIDType = ((TransferJobSettingsStruct*)pJob->pData)->enumUIDType;
		break;
	default:
		*plLen = 0;
		*ppPSSIInfo = NULL;
		return TRUE;
	}


	switch (enumUIDType)
	{
	case enumPatientAdminUIDType_Patient:
		*plLen = pJob->vtrPatient.size();
		break;
	case enumPatientAdminUIDType_Study:
		*plLen = pJob->vtrStudy.size();
		break;
	case enumPatientAdminUIDType_Series:
		*plLen = pJob->vtrSeries.size();
		break;
	case enumPatientAdminUIDType_Image:
		*plLen = pJob->vtrImages.size();
		break;
	default:
		*plLen = 0;
		*ppPSSIInfo = NULL;
		return FALSE;
	}
	
	if (0 == *plLen)
	{
		*ppPSSIInfo = NULL;
		return TRUE;
	}

	*ppPSSIInfo = (PSSIInfo*)CoTaskMemAlloc(sizeof(PSSIInfo) * (*plLen));

	for (int i = 0; i < *plLen; i++)
	{
		ImageInfoStruct* pImage = NULL;
		SeriesInfoStruct* pSeries = NULL;
		StudyInfoStruct* pStudy = NULL;
		PatientInfoStruct* pPatient = NULL;
		CString strUID = _T("");

		switch (enumUIDType)
		{
		case enumPatientAdminUIDType_Image:
			pImage = &pJob->vtrImages[i];

			strUID = CBSTROpt::BSTRToCString(pImage->bsSeriesUID);
			pSeries = GetSeriesInfoStruct(strUID, &pJob->vtrSeries);

			if (NULL != pSeries)
			{
				strUID = CBSTROpt::BSTRToCString(pSeries->bsStudyUID);
				pStudy = GetStudyInfoStruct(strUID, &pJob->vtrStudy);
			}

			if (NULL != pStudy)
			{
				strUID = CBSTROpt::BSTRToCString(pStudy->bsPatientUID);
				pPatient = GetPatientInfoStruct(strUID, &pJob->vtrPatient);
			}

			break;

		case enumPatientAdminUIDType_Series:
			pSeries = &pJob->vtrSeries[i];

			strUID = CBSTROpt::BSTRToCString(pSeries->bsStudyUID);
			pStudy = GetStudyInfoStruct(strUID, &pJob->vtrStudy);

			if (NULL != pStudy)
			{
				strUID = CBSTROpt::BSTRToCString(pStudy->bsPatientUID);
				pPatient = GetPatientInfoStruct(strUID, &pJob->vtrPatient);
			}

			break;

		case enumPatientAdminUIDType_Study:
			pStudy = &pJob->vtrStudy[i];

			strUID = CBSTROpt::BSTRToCString(pStudy->bsPatientUID);
			pPatient = GetPatientInfoStruct(strUID, &pJob->vtrPatient);

			break;

		case enumPatientAdminUIDType_Patient:
			pPatient = &pJob->vtrPatient[i];

			break;
		default:
			*plLen = 0;
			CoTaskMemFree(*ppPSSIInfo);
			*ppPSSIInfo = NULL;
			return FALSE;
		}

		if (NULL != pPatient)
		{
			(*ppPSSIInfo + i)->bsPatientID = CString(CBSTROpt::BSTRToCString(pPatient->bsPatientID)).AllocSysString();
			(*ppPSSIInfo + i)->bsPatientName = CString(CBSTROpt::BSTRToCString(pPatient->bsPatientName)).AllocSysString();
		}
		else
		{
			(*ppPSSIInfo + i)->bsPatientID = CString(_T("")).AllocSysString();
			(*ppPSSIInfo + i)->bsPatientName = CString(_T("")).AllocSysString();
		}

		if (NULL != pStudy)
		{
			CString strID;
			strID.Format(_T("%d"), pStudy->iStudyID);
			(*ppPSSIInfo + i)->bsStudyID = strID.AllocSysString();
		}
		else
		{
			(*ppPSSIInfo + i)->bsStudyID = CString(_T("")).AllocSysString();
		}

		if (NULL != pSeries)
		{
			CString strID;
			strID.Format(_T("%d"), pSeries->iSeriesID);
			(*ppPSSIInfo + i)->bsSeriesID = strID.AllocSysString();
		}
		else
		{
			(*ppPSSIInfo + i)->bsSeriesID = CString(_T("")).AllocSysString();
		}

		if (NULL != pImage)
		{
			CString strID;
			strID.Format(_T("%d"), pImage->iImageID);
			(*ppPSSIInfo + i)->bsImageID = strID.AllocSysString();
		}
		else
		{
			(*ppPSSIInfo + i)->bsImageID = CString(_T("")).AllocSysString();
		}
	}	

	return TRUE;
}

BOOL CJobHandler::GetJobNetworkNodeInfo(PAJob* pJob, NetworkNode** ppNodeInfo, long* plLen)
{
	if (NULL == pJob)
	{
		return FALSE;
	}

	*plLen = ((TransferJobSettingsStruct*)pJob->pData)->vtrNodes.size();
	if (0 == *plLen)
	{
		*ppNodeInfo = NULL;
		return TRUE;
	}

	*ppNodeInfo = (NetworkNode*)CoTaskMemAlloc(sizeof(NetworkNode) * (*plLen));
	vector<NetworkNodeStruct>& vtrNodes = ((TransferJobSettingsStruct*)pJob->pData)->vtrNodes;
	for (int i = 0; i < *plLen; i++)
	{
		(*ppNodeInfo + i)->bDefault = vtrNodes[i].bDefault;
		(*ppNodeInfo + i)->bsCalledAE = vtrNodes[i].strCalledAE.AllocSysString();
		(*ppNodeInfo + i)->bsIP = vtrNodes[i].strIP.AllocSysString();
		(*ppNodeInfo + i)->bsPort = vtrNodes[i].strPort.AllocSysString();
		(*ppNodeInfo + i)->bsCallingAE = vtrNodes[i].strCallingAE.AllocSysString();
		(*ppNodeInfo + i)->bRaw = vtrNodes[i].bRaw;
		(*ppNodeInfo + i)->bProcessed = vtrNodes[i].bProcessed;

		// Add [Sun hongwen 10/16/2009]
		(*ppNodeInfo + i)->bSendPS = vtrNodes[i].bSendPS;
		//
	}

	return TRUE;
}

BOOL CJobHandler::GetJobDetailInfo(PAJob* pJob, JobDetailStruct** ppDetailInfo, long* plLen)
{
	if (NULL == pJob)
	{
		return FALSE;
	}
	
	*plLen = pJob->vtrDetail.size();
	if (0 == *plLen)
	{
		*ppDetailInfo = NULL;
		return TRUE;
	}

	*ppDetailInfo = (JobDetailStruct*)CoTaskMemAlloc(sizeof(JobDetailStruct) * (*plLen));

	JobDetailStruct* pJobDetail = *ppDetailInfo;
	vector<JobDetail>& vtrDetail = pJob->vtrDetail;
	for (int i = 0; i < *plLen; i++)
	{
		(*ppDetailInfo + i)->bsJobID = pJob->strJobID.AllocSysString();
		CString strTime;
		strTime.Format(_T("%02d:%02d:%02d"), vtrDetail[i].stDateTime.wHour, vtrDetail[i].stDateTime.wMinute, vtrDetail[i].stDateTime.wSecond);
		(*ppDetailInfo + i)->bsTime = strTime.AllocSysString();
		(*ppDetailInfo + i)->bsDetail = vtrDetail[i].strDetail.AllocSysString();
	}

	return TRUE;
}

SeriesInfoStruct* CJobHandler::GetSeriesInfoStruct(LPCTSTR szUID, vector<SeriesInfoStruct>* pvtrSeries)
{
	for (int i = 0; i < pvtrSeries->size(); i++)
	{
		CString strUID = CBSTROpt::BSTRToCString((*pvtrSeries)[i].bsSeriesUID);
		if (!strUID.Compare(szUID))
		{
			return &(*pvtrSeries)[i];
		}
	}

	return NULL;
}

StudyInfoStruct* CJobHandler::GetStudyInfoStruct(LPCTSTR szUID, vector<StudyInfoStruct>* pvtrStudy)
{
	for (int i = 0; i < pvtrStudy->size(); i++)
	{
		CString strUID = CBSTROpt::BSTRToCString((*pvtrStudy)[i].bsStudyUID);
		if (!strUID.Compare(szUID))
		{
			return &(*pvtrStudy)[i];
		}
	}

	return NULL;
}

PatientInfoStruct* CJobHandler::GetPatientInfoStruct(LPCTSTR szUID, vector<PatientInfoStruct>* pvtrPatient)
{
	for (int i = 0; i < pvtrPatient->size(); i++)
	{
		CString strUID = CBSTROpt::BSTRToCString((*pvtrPatient)[i].bsPatientUID);
		if (!strUID.Compare(szUID))
		{
			return &(*pvtrPatient)[i];
		}
	}

	return NULL;
}

