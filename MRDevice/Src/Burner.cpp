/* Time: <@(#)Burner.cpp   2009-3-5 - 10:32:36   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : Burner.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Capsulation class of export function
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:32:36		FanZF	Creation
 *
 *********************************************************************
 */

// Burner.cpp: implementation of the CBurner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Burner.h"
#include "math.h"
#include "UserGuidanceOpt.h"
#include "DirHandler.h"
#include "PAEvent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBurner* CBurner::m_pInstance = NULL;


/**
 ********************************************************************
 * \brief 处理由DVDBurner返回的消息
 *  
 *  
 * \param UINT uMessage : [in] 
 * \param LPARAM lParam : [in] 
 * \param WPARAM wParam : [in] 
 * 
 * \return CALLBACK  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CALLBACK MessageHandler(UINT uMessage, LPARAM lParam, WPARAM wParam)
{
	try
	{
		CBurner* pBurner = CBurner::GetInstance();
		if (NULL != pBurner)
		{
			pBurner->HandleMessageFromDVDBurner(uMessage, lParam, wParam);
		}
	}
	PA_CATCH_ERROR_NORET
}



/**
 ********************************************************************
 * \brief 获取刻录准备任务线程
 *  
 *  
 * \param LPVOID lpParam : [in] 
 * 
 * \return WINAPI  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
DWORD WINAPI GetPreBurnJobThreadProc(LPVOID lpParam) 
{ 
	try
	{
		CBurner* pBurner = (CBurner*)lpParam;

		if (pBurner->GetPreBurnJob())
		{
			ARCHVTRACE_INFO("pBurner->GetPreBurnJob() succeed")
			return THREADE_RET_CODE_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("pBurner->GetPreBurnJob() failed")
			return THREADE_RET_CODE_ERROR;
		}
	}
	PA_CATCH_ERROR_RET(THREADE_RET_CODE_ERROR)
}



/**
 ********************************************************************
 * \brief 构造函数
 *  
 *  
 * 
 * \return  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CBurner::CBurner()
{
	m_pDcmPartner = NULL;
	m_pCurrentJob = NULL;
	m_pPreBurnJob = NULL;

	m_hGetJobInfoThread = NULL;
	m_i64SizeOfDiscWith = 0;

	m_SubModuleState = enumSubModuleState_UnInited;

	m_bReportNeeded = FALSE;
	m_bGettingDeviceDiscInfo = FALSE;
}


/**
 ********************************************************************
 * \brief 析构函数
 *  
 *  
 * 
 * \return  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CBurner::~CBurner()
{
	if (m_pDcmPartner)
	{
		m_pDcmPartner->Detach(this);
// 		m_pDcmPartner->ReleaseInstance();
	}
}


/**
 ********************************************************************
 * \brief 获取CBurner实例
 *  
 *  
 * 
 * \return CBurner*  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CBurner* CBurner::GetInstance()
{
	if(!m_pInstance)
		m_pInstance = new CBurner;
	return m_pInstance;
}


/**
 ********************************************************************
 * \brief 释放CBurner实例
 *  
 *  
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


/**
 ********************************************************************
 * \brief 初始化
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::Init()
{
	BOOL bRet = TRUE;

	// Get the size of DiscWith
	TCHAR cCurrentSystemDirectory[MAX_PATH]; 
	GetModuleFileName(NULL, cCurrentSystemDirectory, MAX_PATH);
	CString strApplicationName = cCurrentSystemDirectory;

	CString strApplicationPath = strApplicationName.Left(strApplicationName.ReverseFind('\\'));	//获得不带应用程序文件名的应用程序路径(去掉应用程序文件名)	

	// AutoView
	CString strAutoView = strApplicationPath + AUTOVIEW_DIRECTORY;

	WIN32_FIND_DATA fd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	hFind = FindFirstFile(strAutoView, &fd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
		
		CFilePicker fp(strAutoView);
		fp.GetTotalSize(&m_i64SizeOfDiscWith, TRUE);
		// 转换为M[12/17/2009]
		m_i64SizeOfDiscWith = (m_i64SizeOfDiscWith / (1024 * 1024));
	}
	else
	{
		m_i64SizeOfDiscWith = 0;
	}


	bRet = m_BurnPartner.Init(MessageHandler);
	if (bRet)
	{
		ARCHVTRACE_INFO("m_BurnerControl.Init() succeed")
	}
	else
	{
		ARCHVTRACE_ERROR("m_BurnerControl.Init() failed")
	}

	if (bRet)
	{
		SetSubModuleState(enumSubModuleState_Ready);
		return TRUE;
	}
	else
	{
		SetSubModuleState(enumSubModuleState_Error);
		return FALSE;
	}

}


/**
 ********************************************************************
 * \brief 设置子模块状态
 *  
 *  
 * \param SubModuleState enumSubModuleState : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::SetSubModuleState(SubModuleState enumSubModuleState)
{
	CSingleLock sLock(&m_CSLockSubModuState);
	sLock.Lock();

	if (m_SubModuleState == enumSubModuleState)
	{
		sLock.Unlock();
		return;
	}
	
	if ((enumSubModuleState_Error == m_SubModuleState) &&
		(enumSubModuleState_Ready == enumSubModuleState ||
		enumSubModuleState_Work == enumSubModuleState))
	{
		// SubModule Init Result is Error, so can't changed to ready or work
		sLock.Unlock();
		return;
	}
	else if ((enumSubModuleState_UnInitializing == m_SubModuleState) &&
		((enumSubModuleState_UnInited != enumSubModuleState) &&
		(enumSubModuleState_Error != enumSubModuleState)))
	{
		// just return;
		sLock.Unlock();
		return;
	}
	else
	{
		m_SubModuleState = enumSubModuleState;
	}
	
	//notify CPA
	Notify(NOTIFY_SUBMODULE_STATE_CHANGED, enumSubModule_BURN, m_SubModuleState);

	CString strTrace;
	strTrace = _T("Burn SubModule state: ");
	switch (m_SubModuleState)
	{
	case enumSubModuleState_UnInited:
		strTrace += _T("UnInited");
		break;
	case enumSubModuleState_Ready:
		strTrace += _T("Ready");
		break;
	case enumSubModuleState_Work:
		strTrace += _T("Work");
		break;
	case enumSubModuleState_UnInitializing:
		strTrace += _T("UnInitializing");
		break;
	case enumSubModuleState_Error:
		strTrace += _T("Error");
		break;
	default:
		strTrace += _T("Unknow");
		break;
	}
	ARCHVTRACE_INFO(strTrace);
	
	sLock.Unlock();
}


/**
 ********************************************************************
 * \brief 获取子模块状态
 *  
 *  
 * 
 * \return SubModuleState  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
SubModuleState CBurner::GetSubModuleState()
{
	return m_SubModuleState;
}


/**
 ********************************************************************
 * \brief 创建任务
 *  
 *  
 * \param BurnJobSettingsByPA* pBurnJobSettingsByPA : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::CreateJob(BurnJobSettingsByPA* pBurnJobSettingsByPA)
{
	//<< GetPreJob 线程是否正在运行
	if (NULL != m_hGetJobInfoThread)
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hGetJobInfoThread, 0))
		{
			//<< 线程正在运行
			return FALSE;
		}
	}

	if (NULL == m_pPreBurnJob)
		return FALSE;


	if (0 == m_pPreBurnJob->vtrImages.size())
	{
		//无图像，通知GUI
		UGNotifyStruct* pUGNStruct = new UGNotifyStruct;
		pUGNStruct->iMessageID = IDS_PRINTINGARCHIVING_NO_IMAGE_INCLUDED_TO_SUBMIT_JOB;
		pUGNStruct->enumUGType = enumUG_TYPE_T;
		pUGNStruct->enumGUIPriority = enumUG_PRIOR_L;
		pUGNStruct->bActive = TRUE;
		Notify(NOTIFY_USERGUIDANCE, (LPARAM)pUGNStruct);

		delete m_pPreBurnJob;
		m_pPreBurnJob = NULL;

		PRINTTRACE_ERROR("0 == m_pPreBurnJob->vtrImages.size()")
		return TRUE;
	}


	PAJob* pJob = m_pPreBurnJob;
	m_pPreBurnJob = NULL;


// 	if (enumPatientAdminUIDType_Patient == enumUIDType)
// 	{
// 		for (int i = 0; i < pvtrUID->size(); i++)
// 		{
// 			// Get Patient struct
// 
// 			// Get the Studys of the patient
// 			CString strPatientUID = (*pvtrUID)[i];
// 			for (int j = 0; j < m_pPreBurnJob->vtrStudy.size(); j++)
// 			{
// 				CString strSearchedPatientUID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrStudy[j].bsPatientUID);
// 				if (!strPatientUID.Compare(strSearchedPatientUID))
// 				{
// 					// Get the Series of the Study
// 					CString strStudyUID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrStudy[j].bsStudyUID);
// 					for (int k = 0; k < m_pPreBurnJob->vtrSeries.size(); k++)
// 					{
// 						CString strSearchedStudyUID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrSeries[k].bsStudyUID);
// 						if (!strStudyUID.Compare(strSearchedStudyUID))
// 						{
// 							// Got the Images of the series
// 							CString	strSeriesUID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrSeries[k].bsSeriesUID);
// 							for (int l = 0; l < m_pPreBurnJob->vtrImages.size(); l++)
// 							{
// 								CString strSerchedSeriesUID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrImages[l].bsSeriesUID);
// 								if (!strSeriesUID.Compare(strSerchedSeriesUID))
// 								{
// 									// Got a Image
// 									++dwImagesCount;
// 								}
// 							}
// 							
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	else if (enumPatientAdminUIDType_Study == enumUIDType)
// 	{
// 		// Images
// 		for (int i = 0; i < pvtrUID->size(); i++)
// 		{
// 			for (int j = 0; j < m_pPreBurnJob->vtrImages.size(); j++)
// 			{
// 				if (!(*pvtrUID)[i].Compare(m_pPreBurnJob->vtrImages[j].strStudyUID))
// 				{
// 					pJob->vtrImages.push_back(m_pPreBurnJob->vtrImages[j]);
// 
// 					// Images Count
// 					for (int k = 0; k < pJob->vtrSeries.size(); k++)
// 					{
// 						CString strSeriesUID = CBSTROpt::BSTRToCString(pJob->vtrSeries[k].bsSeriesUID);
// 						if (!m_pPreBurnJob->vtrImages[j].strSeriesUID.Compare(strSeriesUID))
// 						{
// 							pJob->dwTotalImageCount += pJob->vtrSeries[k].lNumberofImages;
// 							break;
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	else if (enumPatientAdminUIDType_Series == enumUIDType)
// 	{
// 		// Images
// 		for (int i = 0; i < pvtrUID->size(); i++)
// 		{
// 			for (int j = 0; j < m_pPreBurnJob->vtrImages.size(); j++)
// 			{
// 				if (!(*pvtrUID)[i].Compare(m_pPreBurnJob->vtrImages[j].strSeriesUID))
// 				{
// 					pJob->vtrImages.push_back(m_pPreBurnJob->vtrImages[j]);
// 
// 					// Images Count
// 					for (int k = 0; k < pJob->vtrSeries.size(); k++)
// 					{
// 						CString strSeriesUID = CBSTROpt::BSTRToCString(pJob->vtrSeries[k].bsSeriesUID);
// 						if (!m_pPreBurnJob->vtrImages[j].strSeriesUID.Compare(strSeriesUID))
// 						{
// 							pJob->dwTotalImageCount += pJob->vtrSeries[k].lNumberofImages;
// 							break;
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	if (enumPatientAdminUIDType_Image == enumUIDType)
// 	{
// 		pJob->vtrPatient = m_pPreBurnJob->vtrPatient;
// 		pJob->vtrStudy = m_pPreBurnJob->vtrStudy;
// 		pJob->vtrSeries = m_pPreBurnJob->vtrSeries;
// 		pJob->vtrPostProcess = m_pPreBurnJob->vtrPostProcess;
// 
// 		//<< 获得需要的Image结构
// 
// 		pJob->vtrImages = m_pPreBurnJob->vtrImages;
// 	}
// 	else
// 	{
// 		delete pJob;
// 		return FALSE;
// 	}
	
	
	pJob->enumJobType = enumJobType_BurnJob;
	pJob->bCancelFlag = FALSE;
	pJob->enumJobState = enumJobState_Submitted;
	pJob->strPhase = _T("");
	pJob->enumJobProgressUsing = enumJobProgressUsing_None;
	pJob->uiCompleted = 0;
	pJob->uiTotal = 0;
	pJob->dwPercentage = 0;

	// make job ID
	SYSTEMTIME st;
	::GetLocalTime(&st);
	pJob->strJobID.Format(_T("%04d%02d%02d%02d%02d%02d%03d"), st.wYear, st.wMonth,
		st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	// First detail info
	pJob->vtrDetail.clear();
	JobDetail aJobDetail;
	aJobDetail.stDateTime = st;
	aJobDetail.strDetail = _TT(JOB_DETAIL_SUBMITED);  
	pJob->vtrDetail.push_back(aJobDetail);

	
	pJob->pData = new BurnJobSettingsStruct;

	((BurnJobSettingsStruct*)pJob->pData)->enumUIDType = m_enumPAUIDType;
	((BurnJobSettingsStruct*)pJob->pData)->lBurnSpeed = pBurnJobSettingsByPA->lBurnSpeed;
	((BurnJobSettingsStruct*)pJob->pData)->bBMP = pBurnJobSettingsByPA->bBMP;
	((BurnJobSettingsStruct*)pJob->pData)->bJPEG = pBurnJobSettingsByPA->bJPEG;

	
	if (CJobHandler::GetInstance()->PushJob(pJob))
	{
		return TRUE;
	}
	else
	{
		delete pJob;
		ARCHVTRACE_ERROR("CJobHandler::GetInstance()->PushJob(pJob)")
		return FALSE;
	}
}


/**
 ********************************************************************
 * \brief 处理NSubject返回的消息
 *  
 *  
 * \param NSubject* pSubject : [in] 
 * \param UINT uMessage : [in] 
 * \param LPARAM lParam : [in] 
 * \param WPARAM wParam : [in] 
 * 
 * \return LONG  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
LONG CBurner::HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam)
{
	if (NOTIFY_BURN == uMessage)
	{
		if (NOTIFY_HARDDISK_FREE_SPACE_NOT_ENOUGH == lParam)
		{
// 			SetCurrentJobDetail(enumJobDetailUsing_UGID, IDS_PRINTINGARCHIVING_HARDDISK_FREESPACE_NOTENOUGH, NULL);
// 			NotifyUG(IDS_PRINTINGARCHIVING_HARDDISK_FREESPACE_NOTENOUGH, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		}
	}
	else if ((NOTIFY_PRINT == uMessage) ||
			(NOTIFY_TRANSFER == uMessage))
	{
		// Do nothing
	}
	else if (NOTIFY_USERGUIDANCE == uMessage)
	{
		SetCurrentJobDetail(enumJobDetailUsing_UGID, ((UGNotifyStruct*)lParam)->iMessageID, NULL);
		Notify(uMessage, lParam, wParam);
	}
	else
	{
		Notify(uMessage, lParam, wParam);
	}
	
	return E_OK;
}


/**
 ********************************************************************
 * \brief 处理由DVDBurner返回的消息
 *  
 *  
 * \param UINT uMessage : [in] 
 * \param LPARAM lParam : [in] 
 * \param WPARAM wParam : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::HandleMessageFromDVDBurner(UINT uMessage, LPARAM lParam, WPARAM wParam)
{
	CString strTrace;

	CString strInfo = _T("");
	BSTR bsTemp = NULL;

	switch(uMessage)
	{
	case MSG_OUT_INFO:
		{
			bsTemp = (BSTR)lParam;
			strInfo.Format(_T("INFO: %s"), CBSTROpt::BSTRToCString(bsTemp));
			PRINTTRACE_INFO(strInfo)
		}
		break;
	case MSG_OUT_WARNNING:
		{
			bsTemp = (BSTR)lParam;
			strInfo.Format(_T("WARNNING: %s"), CBSTROpt::BSTRToCString(bsTemp));
			PRINTTRACE_WARNING(strInfo)
		}
		break;
	case MSG_OUT_ERROR:
		{
			bsTemp = (BSTR)lParam;
			strInfo.Format(_T("ERROR: %s"), CBSTROpt::BSTRToCString(bsTemp));
			PRINTTRACE_ERROR(strInfo)
		}
	    break;
	case MSG_OUT_BURN_STATUS_INFO:
		{
			bsTemp = (BSTR)lParam;
			strInfo = CBSTROpt::BSTRToCString(bsTemp);
			strTrace.Format(_T("MSG_OUT_BURN_STATUS_INFO: %s"), strInfo);
			PRINTTRACE_INFO(strInfo);
			SetCurrentJobDetail(enumJobDetailUsing_DetailInfo, 0, strInfo);
		}
	    break;
	case MSG_OUT_BURN_CREATE_FS_PROGRESS:
		{
			//<< 该阶段进度压缩为30%-60%
			LONG lPrg = 30 + (LONG)lParam * 30 / (LONG)wParam;
			SetCurrentJobProgress(enumJobProgressUsing_Percentage, (UINT)lPrg);
		}
		break;
	case MSG_OUT_BURN_ESTIMATED_TOTAL_TIME:
	    break;
	case MSG_OUT_BURN_ELAPSED_TIME:
		break;
	case MSG_OUT_BURN_REMAINING_TIME:
		break;
	case MSG_OUT_BURN_SYSTEM_BUFFER:
		break;
	case MSG_OUT_BURN_PROGRESS:
		{
			//<< 该阶段进度压缩为60%-100%
			LONG lPrg = 60 + (LONG)lParam *40 / (LONG)wParam;
			SetCurrentJobProgress(enumJobProgressUsing_Percentage, (UINT)lPrg);
		}
		break;
	case MSG_OUT_BURN_FINISHED:
		{
			switch((BurnResult)lParam)
			{
			case BurnResult_Success:
				if (NULL != m_pCurrentJob)
				{
					m_pCurrentJob->SetDetail(JOB_DETAIL_COMPLETED);
					m_pCurrentJob->SetProgress(enumJobProgressUsing_None);
					m_pCurrentJob->SetPhase(JOB_PHASE_NONE);
					m_pCurrentJob->SetState(enumJobState_Completed);
					m_pCurrentJob = NULL;
				}

				NotifyUG(IDS_PRINTINGARCHIVING_EXPORT_JOB_COMPLETED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
				break;
			case BurnResult_Cancelled:
				if (NULL != m_pCurrentJob)
				{
					m_pCurrentJob->SetDetail(JOB_DETAIL_CANCELLED);
					m_pCurrentJob->SetProgress(enumJobProgressUsing_None);
					m_pCurrentJob->SetPhase(JOB_PHASE_NONE);
					m_pCurrentJob->SetState(enumJobState_Cancelled);
					m_pCurrentJob = NULL;
				}

				break;
			case BurnResult_Failed:
				if (NULL != m_pCurrentJob)
				{
					m_pCurrentJob->SetDetail(JOB_DETAIL_FAILED);
					m_pCurrentJob->SetProgress(enumJobProgressUsing_None);
					m_pCurrentJob->SetPhase(JOB_PHASE_NONE);
					m_pCurrentJob->SetState(enumJobState_Failed);
					NotifyUG(IDS_PRINTINGARCHIVING_EXPORT_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
					m_pCurrentJob = NULL;
				}

				break;
			default:
				strTrace.Format(_T("MSG_OUT_BURN_FINISHED,unknow LPARAM: %d"), (BurnResult)lParam);
				PRINTTRACE_ERROR(strInfo);
			    break;
			}
		}
	    break;
	case MSG_OUT_BURN_MEDIA_NOT_READY:
		{
// 			bsTemp = (BSTR)lParam;
// 			strInfo = CBSTROpt::BSTRToCString(bsTemp);
// 			BSTR bsInfo = strInfo.AllocSysString();
// 			Notify(NOTIFY_BURN_MEDIA_NOT_READY, (LPARAM)bsInfo);
			m_BurnPartner.SetBurnMediaCheckRetry(BurnMediaCheckRetry_Fail);
		}
		break;
	case MSG_OUT_ERASE_STATUS_INFO:
		break;
	case MSG_OUT_ERASE_PROGRESS:
		break;
	case MSG_OUT_ERASE_FINISHED:
	    break;
	case MSG_OUT_GET_DEVICES:
		break;
	case MSG_OUT_GET_CURRENT_DEVICE_INFO:
		break;
	case MSG_OUT_GET_MEDIA_INFO_IN_CURRENT_DEVICE:
		break;
	case MSG_OUT_GET_CURRENT_DEVICE_MEDIA_INFO:
		m_bGettingDeviceDiscInfo = FALSE;
		if ((BOOL)lParam)
		{
			DeviceDiscInfo* pInfo = (DeviceDiscInfo*)wParam;

			//<< Speed Info
			DeviceInfo* pDevice = &pInfo->Device;
			BurnSpeedInfo* pSpeedInfo = new BurnSpeedInfo[pDevice->dwWriteSupportedSpeedsNum];
			for (int i = 0; i < pDevice->dwWriteSupportedSpeedsNum; i++)
			{
				if (BURNER_SPEED_MAX == pDevice->lNumOfSectorsWrittenPerSec[i])
				{
					pSpeedInfo[i].lSpeed = BURNER_SPEED_MAX;
					pSpeedInfo[i].bsSpeedInfo = CString(_TT(BURN_DMI_MAXSPEED)).AllocSysString(); 
				}
				else if (BURNER_SPEED_MIN == pDevice->lNumOfSectorsWrittenPerSec[i])
				{
					pSpeedInfo[i].lSpeed = BURNER_SPEED_MIN;
					pSpeedInfo[i].bsSpeedInfo = CString(_TT(BURN_DMI_MINSPEED)).AllocSysString(); 
				}
				else
				{
					pSpeedInfo[i].lSpeed = pDevice->lNumOfSectorsWrittenPerSec[i];

					float fSpeedInX = (float)(pDevice->lNumOfSectorsWrittenPerSec[i]) / pDevice->dwSectorsPerX;
					fSpeedInX = floor(fSpeedInX*10 + 0.5) /10;
					CString strSpeedInX;
					strSpeedInX.Format(_T("%.1f"), fSpeedInX);
					if (strSpeedInX.GetAt(strSpeedInX.GetLength() - 1) == _T('0'))
					{
						strSpeedInX = strSpeedInX.Left(strSpeedInX.GetLength() - 2);
					}
					DWORD dwSpeedInKB = fSpeedInX * pDevice->dwKBPerX;

					CString strSpeed;
					strSpeed.Format(_T("%sx [%d KB/s]"), strSpeedInX, dwSpeedInKB);
					pSpeedInfo[i].bsSpeedInfo = strSpeed.AllocSysString();
				}
			}

			if (m_bReportNeeded)
			{
				Notify(NOTIFY_BURN_DEVICE_MEDIA_INFO_SPEED, (LPARAM)pDevice->dwWriteSupportedSpeedsNum, (WPARAM)pSpeedInfo);
			}
			else
			{
				CBSTROpt::FreeBurnSpeedInfoList(pSpeedInfo, pDevice->dwWriteSupportedSpeedsNum);
				delete []pSpeedInfo;
			}

			//<< Media Info
			DiscInfo* pDisc = &pInfo->Disc;
			BurnMediaInfo* pMediaInfo = new BurnMediaInfo;

			if (pDisc->bDiscValid)
			{
				if (pDisc->bDiscEmpty)
				{
					CString strMediaType = _TT(CBSTROpt::BSTRToCString(pDisc->aMediaTypeStruct.bsMediaTypeName));
					strMediaType += _TT(BURN_DMI_BLANK_MEDIA); 
					pMediaInfo->bsMediaType = strMediaType.AllocSysString();

					CString strDiscSize;
					strDiscSize.Format(_T("%d M"), (__int64(pDisc->dwDiscSectorSizeInByte))*pDisc->dwDiscFreeSectorNum/1024/1024);
					pMediaInfo->bsMediaSize = strDiscSize.AllocSysString();

					pMediaInfo->bEmptyMedia = TRUE;
				}
				else
				{
					CString strMediaType = _TT(CBSTROpt::BSTRToCString(pDisc->aMediaTypeStruct.bsMediaTypeName));
					strMediaType += _TT(BURN_DMI_UNBLANK_MEDIA); 
					pMediaInfo->bsMediaType = strMediaType.AllocSysString();

					pMediaInfo->bsMediaSize = CString(_T("0 M")).AllocSysString();
					pMediaInfo->bEmptyMedia = FALSE;
				}
			}
			else
			{
				CString strMediaType = _TT(BURN_DMI_NO_MEDIA);
				pMediaInfo->bsMediaType = _TT(strMediaType).AllocSysString(); 
				pMediaInfo->bsMediaSize = CString(_T("0 M")).AllocSysString();
				pMediaInfo->bEmptyMedia = FALSE;
			}

			if (m_bReportNeeded)
			{
				Notify(NOTIFY_BURN_DEVICE_MEDIA_INFO_MEDIA, (LPARAM)pMediaInfo);
			}
			else
			{
				CBSTROpt::FreeBurnMediaInfo(pMediaInfo);
				delete pMediaInfo;
			}
		}
		break;
	case MSG_OUT_GET_FILES_SIZE:
		break;
	default:
		strInfo.Format(_T("Unknow Message: uMessage:%d, lParam:%d, wParam:%d"), uMessage, lParam, wParam);
		PRINTTRACE_ERROR(strInfo);
	}
}


/**
 ********************************************************************
 * \brief 刻录准备
 *  
 *  
 * \param vector<CString>* pvtrUID : [in] 
 * \param PatientAdminUIDType enumPatientAdminUIDType : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::BurnPrepare(vector<CString>* pvtrUID, PatientAdminUIDType enumPatientAdminUIDType)
{
	//<< 使能Report状态
	m_bReportNeeded = TRUE;

	if (NULL != m_hGetJobInfoThread)
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hGetJobInfoThread, 0))
		{
			return FALSE;
		}
		else
		{
			CloseHandle(m_hGetJobInfoThread);
			m_hGetJobInfoThread = NULL;
		}
	}
	
	if (pvtrUID->size() == 0)
	{
		return FALSE;
	}

	m_vtrPAUID = *pvtrUID;
	m_enumPAUIDType = enumPatientAdminUIDType;
	m_hGetJobInfoThread = CreateThread(NULL, 0, GetPreBurnJobThreadProc, this, 0, NULL);
	if (NULL == m_hGetJobInfoThread)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


/**
 ********************************************************************
 * \brief 取消刻录准备
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::CancelBurnPrepare()
{
	//<< 使能Report状态
	m_bReportNeeded = FALSE;

	CDBController::GetInstance()->DisableGetJobInfo();
	return TRUE;
}


/**
 ********************************************************************
 * \brief 获得刻录准备任务
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::GetPreBurnJob()
{
	if (NULL != m_pPreBurnJob)
	{
		delete m_pPreBurnJob;
		m_pPreBurnJob = NULL;
	}

	m_pPreBurnJob = new PAJob;

	DWORD dwStart = GetTickCount();

	if (!(CDBController::GetInstance())->GetJobImageInfoByUIDs(&m_vtrPAUID,
														m_enumPAUIDType,
														m_pPreBurnJob))
	{
		ARCHVTRACE_WARNING("m_pDBController->GetImagesInfo() error or CancelPrepare() is Called")
		delete m_pPreBurnJob;
		m_pPreBurnJob = NULL;
		return FALSE;
	}

	CString strTimeElapsed;
	strTimeElapsed.Format(_T("Burn GetJobImageInfoByMultiUIDBFS: %d ms"), GetTickCount() - dwStart);
	PRINTTRACE_INFO(strTimeElapsed)
	
	// Notify UI

	dwStart = GetTickCount();

	if (enumPatientAdminUIDType_Patient == m_enumPAUIDType)
	{
		BurnPatientInfoStruct* pPatientInfoList = new BurnPatientInfoStruct[m_pPreBurnJob->vtrPatient.size()];

		for (int i = 0; i < m_pPreBurnJob->vtrPatient.size(); i++)
		{


			pPatientInfoList[i].bsPatientName = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrPatient)[i].bsPatientName).AllocSysString();
			pPatientInfoList[i].bsPatientID = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrPatient)[i].bsPatientID).AllocSysString();
			pPatientInfoList[i].iGender = (m_pPreBurnJob->vtrPatient)[i].iGender; 
			pPatientInfoList[i].dtBirthDate = (m_pPreBurnJob->vtrPatient)[i].dtBirthDate;

		}

		if (m_bReportNeeded)
			Notify(NOTIFY_BURN_PATIENTS_INFO, (LPARAM)m_pPreBurnJob->vtrPatient.size(), (WPARAM)pPatientInfoList);
	
		CString strTimeElapsed;
		strTimeElapsed.Format(_T("Burn make notify UI struct: %d ms"), GetTickCount() - dwStart);
		PRINTTRACE_INFO(strTimeElapsed)
		
	}
	else if (enumPatientAdminUIDType_Study == m_enumPAUIDType)
	{
		BurnStudyInfoStruct* pStudyInfoList = new BurnStudyInfoStruct[m_vtrPAUID.size()];

		for (int i = 0; i < m_pPreBurnJob->vtrStudy.size(); i++)
		{
			CString strPatientUID = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrStudy)[i].bsPatientUID);
			for (int k = 0; k < m_pPreBurnJob->vtrPatient.size(); k++)
			{
				CString strUID = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrPatient)[k].bsPatientUID);
				if (!strPatientUID.Compare(strUID))
				{
					// Get Patient Info Struct
					pStudyInfoList[i].bsPatientName = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrPatient)[k].bsPatientName).AllocSysString();
					pStudyInfoList[i].bsPatientID = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrPatient)[k].bsPatientID).AllocSysString();
					break;
				}
			}

			if (k == m_pPreBurnJob->vtrPatient.size())
			{
				// not found, error
				delete []pStudyInfoList;
				return FALSE;
			}
			
			pStudyInfoList[i].iStudyID = (m_pPreBurnJob->vtrStudy)[i].iStudyID;
			pStudyInfoList[i].dtStartStudyDateTime = (m_pPreBurnJob->vtrStudy)[i].dtStartStudyDateTime;

		}

		if (m_bReportNeeded)
			Notify(NOTIFY_BURN_STUDYS_INFO, (LPARAM)m_pPreBurnJob->vtrStudy.size(), (WPARAM)pStudyInfoList);


		CString strTimeElapsed;
		strTimeElapsed.Format(_T("Burn make notify UI struct: %d ms"), GetTickCount() - dwStart);
		PRINTTRACE_INFO(strTimeElapsed)

	}
	else if (enumPatientAdminUIDType_Series == m_enumPAUIDType)
	{
		BurnSeriesInfoStruct* pSeriesInfoList = new BurnSeriesInfoStruct[m_vtrPAUID.size()];

		for (int i = 0; i < m_pPreBurnJob->vtrSeries.size(); i++)
		{
			// Get Series info
			pSeriesInfoList[i].iSeriesID = m_pPreBurnJob->vtrSeries[i].iSeriesID;

			// Get Study info struct
			CString strStudyUID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrSeries[i].bsStudyUID);
			for (int j = 0; j < m_pPreBurnJob->vtrStudy.size(); j++)
			{
				CString strUID = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrStudy)[j].bsStudyUID);
				if (!strStudyUID.Compare(strUID))
				{
					pSeriesInfoList[i].iStudyID = m_pPreBurnJob->vtrStudy[j].iStudyID;
					break;
				}
			}

			if (j == m_pPreBurnJob->vtrStudy.size())
			{
				// not found, error
				delete []pSeriesInfoList;
				return FALSE;
			}

			// Get Patient info Struct
			CString strPatientUID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrStudy[j].bsPatientUID);
			for (j = 0; j < m_pPreBurnJob->vtrPatient.size(); j++)
			{
				CString strUID = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrPatient)[j].bsPatientUID);
				if (!strPatientUID.Compare(strUID))
				{
					pSeriesInfoList[i].bsPatientName = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrPatient[j].bsPatientName).AllocSysString();
					pSeriesInfoList[i].bsPatientID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrPatient[j].bsPatientID).AllocSysString();
					break;
				}
			}

			if (j == m_pPreBurnJob->vtrPatient.size())
			{
				// not found, error
				delete []pSeriesInfoList;
				return FALSE;
			}
		}
		
		if (m_bReportNeeded)
			Notify(NOTIFY_BURN_SERIES_INFO, (LPARAM)m_pPreBurnJob->vtrSeries.size(), (WPARAM)pSeriesInfoList);

		CString strTimeElapsed;
		strTimeElapsed.Format(_T("Burn make notify UI struct: %d ms"), GetTickCount() - dwStart);
		PRINTTRACE_INFO(strTimeElapsed)

	}
	else if (enumPatientAdminUIDType_Image == m_enumPAUIDType)
	{
		BurnImageInfoStruct* pImageInfoList = new BurnImageInfoStruct[m_vtrPAUID.size()];

		for (int i = 0; i < m_pPreBurnJob->vtrImages.size(); i++)
		{
			// Get Image Info
			pImageInfoList[i].iImageID = m_pPreBurnJob->vtrImages[i].iImageID;

			// Get Series info
			CString strSeriesUID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrImages[i].bsSeriesUID);
			for (int j = 0; j < m_pPreBurnJob->vtrStudy.size(); j++)
			{
				CString strUID = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrSeries)[j].bsSeriesUID);
				if (!strSeriesUID.Compare(strUID))
				{
					pImageInfoList[i].iSeriesID = m_pPreBurnJob->vtrSeries[j].iSeriesID;
					break;
				}
			}

			if (j == m_pPreBurnJob->vtrSeries.size())
			{
				// not found, error
				delete []pImageInfoList;
				return FALSE;
			}

			// Get Study info struct
			CString strStudyUID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrSeries[j].bsStudyUID);
			for (j = 0; j < m_pPreBurnJob->vtrStudy.size(); j++)
			{
				CString strUID = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrStudy)[j].bsStudyUID);
				if (!strStudyUID.Compare(strUID))
				{
					pImageInfoList[i].iStudyID = m_pPreBurnJob->vtrStudy[j].iStudyID;
					break;
				}
			}

			if (j == m_pPreBurnJob->vtrStudy.size())
			{
				// not found, error
				delete []pImageInfoList;
				return FALSE;
			}

			// Get Patient info Struct
			CString strPatientUID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrStudy[j].bsPatientUID);
			for (j = 0; j < m_pPreBurnJob->vtrPatient.size(); j++)
			{
				CString strUID = CBSTROpt::BSTRToCString((m_pPreBurnJob->vtrPatient)[j].bsPatientUID);
				if (!strPatientUID.Compare(strUID))
				{
					pImageInfoList[i].bsPatientName = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrPatient[j].bsPatientName).AllocSysString();
					pImageInfoList[i].bsPatientID = CBSTROpt::BSTRToCString(m_pPreBurnJob->vtrPatient[j].bsPatientID).AllocSysString();
					break;
				}
			}

			if (j == m_pPreBurnJob->vtrPatient.size())
			{
				// not found, error
				delete []pImageInfoList;
				return FALSE;
			}
		}
		
		if (m_bReportNeeded)
			Notify(NOTIFY_BURN_IMAGE_INFO, (LPARAM)m_pPreBurnJob->vtrImages.size(), (WPARAM)pImageInfoList);

		CString strTimeElapsed;
		strTimeElapsed.Format(_T("Burn make notify UI struct: %d ms"), GetTickCount() - dwStart);
		PRINTTRACE_INFO(strTimeElapsed)
	}
	else
	{
		return FALSE;
	}


	return TRUE;
}


/**
 ********************************************************************
 * \brief 链接DcmPartner对象
 *  
 *  
 * \param CDcmPartner* pDcmPartner : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::AttachDcmPartner(CDcmPartner* pDcmPartner)
{
	m_pDcmPartner = pDcmPartner;
	pDcmPartner->Attach(this);
}


/**
 ********************************************************************
 * \brief 断开DcmPartner对象
 *  
 *  
 * \param CDcmPartner* pDcmPartner : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::DetachDcmPartner(CDcmPartner* pDcmPartner)
{
	pDcmPartner->Detach(this);
}



/**
 ********************************************************************
 * \brief 处理任务
 *  
 *  
 * \param PAJob* pJob : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::HandleJob(PAJob* pJob)
{
	ARCHVTRACE_ENTER_FUNCTION

	if (NULL == pJob)
	{
		return FALSE;
	}

	m_pCurrentJob = pJob;

	pJob->SetDetail(JOB_DETAIL_START);

	pJob->SetPhase(JOB_PHASE_IMAGE_CONVERSION);
	pJob->SetDetail(JOB_DETAIL_PHASE_PREPROCESSING);

	BOOL bRet = TRUE;

	//<< 清空刻录临时文件夹
	if (!CDirHandler::CheckDir(DICOM_IMAGE_BURN_STORE_PATH, TRUE))
	{
		pJob->SetDetail(JOB_DETAIL_ERROR_OCCURRED);
		pJob->SetDetail(JOB_DETAIL_FAILED);
		pJob->SetProgress(enumJobProgressUsing_None);
		pJob->SetPhase(JOB_PHASE_NONE);
		pJob->SetState(enumJobState_Failed);
		NotifyUG(IDS_PRINTINGARCHIVING_EXPORT_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		m_pCurrentJob = NULL;
		ARCHVTRACE_ERROR("CDirHandler::CheckDir()")
		return FALSE;
	}

	//<< 硬盘空间是否足够
	DWORD dwImageCount = pJob->vtrImages.size();
	if (!CSpaceEstimator::IsBurnJobApplicable(dwImageCount, FALSE, FALSE, m_i64SizeOfDiscWith))
	{
		pJob->SetDetail(JOB_DETAIL_CACHESPACE_NOTENOUGH);
		pJob->SetDetail(JOB_DETAIL_FAILED);
		pJob->SetProgress(enumJobProgressUsing_None);
		pJob->SetPhase(JOB_PHASE_NONE);
		pJob->SetState(enumJobState_Failed);
		NotifyUG(IDS_PRINTINGARCHIVING_EXPORT_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		m_pCurrentJob = NULL;
		ARCHVTRACE_ERROR("CSpaceEstimator::IsBurnJobApplicable()")
		return FALSE;
	}


	m_pDcmPartner->SetImageType(TRUE, TRUE);
	m_pDcmPartner->SetPSFile(TRUE);
	m_pDcmPartner->SetDcmDir(TRUE);

	if (m_pDcmPartner->ConvertBFS(m_pCurrentJob,
 									DICOM_IMAGE_BURN_STORE_PATH,
									NULL,
									NULL))
	{
		//<< 完成或取消
		PRINTTRACE_INFO("m_pDcmPartner.ConvertBFS()")
	}
	else
	{
		pJob->SetDetail(JOB_DETAIL_PHASE_PREPROC_FAILED);
		pJob->SetDetail(JOB_DETAIL_FAILED);
		pJob->SetProgress(enumJobProgressUsing_None);
		pJob->SetPhase(JOB_PHASE_NONE);
		pJob->SetState(enumJobState_Failed);
		NotifyUG(IDS_PRINTINGARCHIVING_EXPORT_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		m_pCurrentJob = NULL;
		ARCHVTRACE_ERROR("m_pDcmPartner.ConvertBFS()")
		return FALSE;
	}

	if (m_pCurrentJob->bCancelFlag)
	{
		pJob->SetDetail(JOB_DETAIL_CANCELLED);
		pJob->SetProgress(enumJobProgressUsing_None);
		pJob->SetPhase(JOB_PHASE_NONE);
		pJob->SetState(enumJobState_Cancelled);
		m_pCurrentJob = NULL;
		ARCHVTRACE_INFO("m_pCurrentJob->bCancelFlag")
		return TRUE;
	}
	else
	{
		//<< 预处理完成
		pJob->SetDetail(JOB_DETAIL_PHASE_PREPROC_COMPLETED);
	}


	// Phase Burn

	pJob->SetPhase(JOB_PHASE_BURN);

	
	// Burn settings
	m_BurnPartner.SetVolumeLabel(GetVolumeLabel(m_pCurrentJob->strJobID));
	m_BurnPartner.SetFileSystem((MediaFileSystem)(MediaFileSystem_ISO9660|MediaFileSystem_Joliet));
	m_BurnPartner.SetEjectAfterBurn(FALSE);
	m_BurnPartner.SetCloseMedia(TRUE);
	m_BurnPartner.SetBurnSpeed(((BurnJobSettingsStruct*)m_pCurrentJob->pData)->lBurnSpeed);

	if (m_pCurrentJob->bCancelFlag)
	{
		pJob->SetDetail(JOB_DETAIL_CANCELLED);
		pJob->SetProgress(enumJobProgressUsing_None);
		pJob->SetPhase(JOB_PHASE_NONE);
		pJob->SetState(enumJobState_Cancelled);
		m_pCurrentJob = NULL;
		ARCHVTRACE_INFO("m_pCurrentJob->bCancelFlag")
		return TRUE;
	}

	//必须清空BurnPartner的文件列表，否则再次刻录出错  [ GaoXing 4/27/2010]
	m_BurnPartner.ClearFiles();

	// Set Burn Content
	bRet = SetBurnContent();
	if (!bRet)
	{
		pJob->SetDetail(JOB_DETAIL_ERROR_OCCURRED);
		pJob->SetDetail(JOB_DETAIL_FAILED);
		pJob->SetProgress(enumJobProgressUsing_None);
		pJob->SetPhase(JOB_PHASE_NONE);
		pJob->SetState(enumJobState_Failed);
		NotifyUG(IDS_PRINTINGARCHIVING_EXPORT_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		m_pCurrentJob = NULL;
		ARCHVTRACE_ERROR("m_BurnerControl.SetBurnSettings((BurnJobSettingsStruct*)m_pCurrentJob->pData)")
		return bRet;
	}
	
	if (m_pCurrentJob->bCancelFlag)
	{
		pJob->SetDetail(JOB_DETAIL_CANCELLED);
		pJob->SetProgress(enumJobProgressUsing_None);
		pJob->SetPhase(JOB_PHASE_NONE);
		pJob->SetState(enumJobState_Cancelled);
		m_pCurrentJob = NULL;
		ARCHVTRACE_INFO("m_pCurrentJob->bCancelFlag")
		return TRUE;
	}

	
	// Burn disc
	UINT iRetCode = m_BurnPartner.Burn();
	ARCHVTRACE_INFO("m_BurnerControl.Burn()")
	//<< 在收到m_BurnPartner回调函数的MSG_OUT_BURN_FINISHED消息时处理JobDetail等信息
	if (S_BURNER_OK == iRetCode)
	{
		// 添加下面代码，dvdburner不再发送MSG_OUT_BURN_FINISHED->BurnResult_Success消息，改为通过返回值判断并设置刻录成功状态 [3/2/2010 wangy]
		pJob->SetDetail(JOB_DETAIL_COMPLETED);

		const unsigned int uiCompletedProgress(100);
		pJob->SetProgress(enumJobProgressUsing_CompletedTotal, uiCompletedProgress, uiCompletedProgress);

		pJob->SetPhase(JOB_PHASE_NONE);
		pJob->SetState(enumJobState_Completed);
		m_pCurrentJob = NULL;
		NotifyUG(IDS_PRINTINGARCHIVING_EXPORT_JOB_COMPLETED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		ARCHVTRACE_INFO("m_BurnerControl.Burn() completed!");
		
		ExpPatientOK++;
		////////////////////////////
	}
	else if (S_BURNER_BURNING_CANCELLED == iRetCode)
	{
		ARCHVTRACE_INFO("m_pCurrentJob->bCancelFlag")
	}
	else
	{
		bRet = FALSE;

		ARCHVTRACE_ERROR("m_BurnerControl.Burn()")
	}

	//<< 在收到m_BurnPartner回调函数的MSG_OUT_BURN_FINISHED消息时将m_pCurrentJob置NULL
// 	m_pCurrentJob = NULL;
	ARCHVTRACE_LEAVE_FUNCTION
	return bRet;

}



/**
 ********************************************************************
 * \brief 取消刻录
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::AbortBurnWork()
{
	if (m_BurnPartner.IsBurning())
	{
		m_BurnPartner.CancelBurn();
		
// 		NotifyUG(IDS_PRINTINGARCHIVING_BURN_CANCELLED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		
		if (NULL != m_pCurrentJob)
		{
			m_pCurrentJob->bCancelFlag = TRUE;
		}

		return TRUE;
		
	}
	else
	{
		PRINTTRACE_INFO("FALSE == m_BurnerControl.IsBurning()")
		return TRUE;
	}
}


/**
 ********************************************************************
 * \brief 获得估计大小
 *  
 *  
 * \param BOOL bBMP : [in] 
 * \param BOOL bJPEG : [in] 
 * \param unsigned long* plSizeInMega : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::GetEstimatedSize(BOOL bBMP, BOOL bJPEG, unsigned long* plSizeInMega)
{
	if (NULL == m_pPreBurnJob)
	{
		*plSizeInMega = 0;
		return FALSE;
	}

	//<< 估计大小
	__int64 i64Size = 0;

	i64Size = CSpaceEstimator::GetBurnContentSizeInBytes(m_pPreBurnJob->vtrImages.size(), bBMP, bJPEG, m_i64SizeOfDiscWith);


	//<< 转换成M
	*plSizeInMega = i64Size; //单位为M	[12/17/2009]

	// 添加Trace跟踪刻录内容的大小(单位：M) [7/20/2009 gaoxing]
	CString strTrace;
	strTrace.Format(_T("CBurner::GetEstimatedSize() is %ld"), *plSizeInMega);
	PRINTTRACE_INFO(strTrace);

	return TRUE;
}


/**
 ********************************************************************
 * \brief 使能检测设备
 *  
 *  
 * \param BOOL bCheck : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::EnableCheckDevice(BOOL bCheck)
{
// 	m_BurnerControl.EnableCheckDevice(bCheck);
}


/**
 ********************************************************************
 * \brief 设置光盘检测重试标志
 *  
 *  
 * \param BOOL bRetry : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::SetBurnMediaCheckRetry(BOOL bRetry)
{
// 	m_BurnPartner.SetBurnMediaCheckRetry(bRetry);
}


/**
 ********************************************************************
 * \brief 获得设备列表
 *  
 *  
 * \param BSTR** ppbsDevices : [in] 
 * \param long* pLen : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::GetDevices(BSTR** ppbsDevices, long* pLen)
{
	vector<BSTR> vtrDevices;
	if (m_BurnPartner.GetDevices(&vtrDevices))
	{
		*pLen = vtrDevices.size();
		ULONG cb = sizeof(**ppbsDevices) * (*pLen);
		*ppbsDevices = (BSTR*)CoTaskMemAlloc(cb);
		for (int i = 0; i < *pLen; i++)
		{
			CString strDevice = CBSTROpt::BSTRToCString(vtrDevices[i]);
			*ppbsDevices[i] = strDevice.AllocSysString();
			CBSTROpt::FreeBSTR(vtrDevices[i]);
		}
		return TRUE;
	}
	else
	{
		ARCHVTRACE_ERROR("m_BurnerControl.GetDevices(pDeviceInfo, pLen)")
		return FALSE;
	}
}


/**
 ********************************************************************
 * \brief 获得设备列表
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::GetDeviceDiscInfo()
{
	if (!m_bGettingDeviceDiscInfo)
	{
		m_bGettingDeviceDiscInfo = TRUE;
		if (m_BurnPartner.PostMessage(MSG_IN_GET_CURRENT_DEVICE_MEDIA_INFO))
		{
			return TRUE;
		}
		else
		{
			ARCHVTRACE_ERROR("m_BurnerControl.PostMessage(MSG_IN_GET_CURRENT_DEVICE_MEDIA_INFO)")
			return FALSE;
		}
	}
	else
	{
		return TRUE;
	}
}


/**
 ********************************************************************
 * \brief 设置设备
 *  
 *  
 * \param LPCTSTR strDeviceName : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::SetDevice(LPCTSTR strDeviceName)
{
	if (m_BurnPartner.SetCurrentDevice((LPCTSTR)strDeviceName))
	{
		return TRUE;
	}
	else
	{
		ARCHVTRACE_ERROR("m_BurnerControl.SetDevice((LPCTSTR)strDeviceName)")
		return FALSE;
	}
}


/**
 ********************************************************************
 * \brief 
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::UnInit()
{
	BOOL bRet = TRUE;

	SetSubModuleState(enumSubModuleState_UnInitializing);

	if (!m_BurnPartner.UnInit())
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_BurnerControl.UnInit() failed")
	}
	else
	{
		ARCHVTRACE_INFO("m_BurnerControl.UnInit() succeed")
	}
		

	SetSubModuleState(enumSubModuleState_UnInited);

	return bRet;
	
}


/**
 ********************************************************************
 * \brief 转发UserGuidance
 *  
 *  
 * \param LONG iMessageID : [in] 
 * \param UserGuidanceType enumUGType : [in] 
 * \param UserGuidancePriority enumGUIPriority : [in] 
 * \param BOOL bActive : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive)
{ 
	UGNotifyStruct* pUGNStruct = new UGNotifyStruct; 
	pUGNStruct->iMessageID = (iMessageID);
	pUGNStruct->enumUGType = (enumUGType);
	pUGNStruct->enumGUIPriority = (enumGUIPriority);
	pUGNStruct->bActive = (bActive); 
	Notify(NOTIFY_USERGUIDANCE, (LPARAM)pUGNStruct);
}


/**
 ********************************************************************
 * \brief 设置当前任务进度
 *  
 *  
 * \param JobProgressUsing enumJobProgressUsing : [in] 
 * \param UINT uiFirstParam : [in] 
 * \param UINT uiSecondParam : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::SetCurrentJobProgress(JobProgressUsing enumJobProgressUsing, UINT uiFirstParam, UINT uiSecondParam)
{
	if (NULL != m_pCurrentJob)
	{
		m_pCurrentJob->SetProgress(enumJobProgressUsing, uiFirstParam, uiSecondParam);
	}
}


/**
 ********************************************************************
 * \brief 设置当前任务详细信息
 *  
 *  
 * \param JobDetailUsing enumJobDetailUsing : [in] 
 * \param LONG iUGID : [in] 
 * \param LPCTSTR szDetailInfo : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::SetCurrentJobDetail(JobDetailUsing enumJobDetailUsing, LONG iUGID, LPCTSTR szDetailInfo)
{
	// different with other SetCurrentJobXXX, here may be no CurrentJob in 
	// the queue when CBurnPartner notify this event (BurnPhase)
	if (NULL == m_pCurrentJob)
		return;


	CString strDetailInfo;

	switch (enumJobDetailUsing)
	{
	case enumJobDetailUsing_None:
		m_pCurrentJob->SetDetail(_T(""));
		break;
	case enumJobDetailUsing_UGID:
		m_pCurrentJob->SetDetailByUGID(iUGID);
		break;
	case enumJobDetailUsing_DetailInfo:
		m_pCurrentJob->SetDetail(szDetailInfo);
		break;
	default:
		break;
	}
}


/**
 ********************************************************************
 * \brief 设置当前任务详细信息
 *  
 *  
 * \param LPCTSTR szDetail : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CBurner::SetCurrentJobDetailOriginal(LPCTSTR szDetail)
{
	if (NULL != m_pCurrentJob)
	{
		m_pCurrentJob->SetDetailOriginal(szDetail);
	}
}


/**
 ********************************************************************
 * \brief 设置刻录内容
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CBurner::SetBurnContent()
{
	if (NULL == m_pCurrentJob)
	{
		return FALSE;
	}

	WIN32_FIND_DATA fd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString strTrace;

	//<<　1. \Work\*
	CString strBurnDir = DICOM_IMAGE_BURN_STORE_PATH;
	strBurnDir += DICOM_IMAGE_WORK_DIR;

	hFind = FindFirstFile(strBurnDir + _T("\\*"), &fd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return FALSE;
	}

	do{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!wcscmp(fd.cFileName, _T(".")) || !wcscmp(fd.cFileName, _T("..")))
				continue;
			else
			{
				m_BurnPartner.AddFile(strBurnDir + _T("\\") + fd.cFileName);
			}
		}
		else
		{
			m_BurnPartner.AddFile(strBurnDir + _T("\\") + fd.cFileName);
		}
	}while (FindNextFile(hFind, &fd));

	FindClose(hFind);
	hFind = INVALID_HANDLE_VALUE;

	if (ERROR_NO_MORE_FILES != GetLastError())
	{
		return FALSE;
	}


	//<< 2. DicomViewer 及 autorun.inf
	TCHAR cCurrentSystemDirectory[MAX_PATH]; 
	GetModuleFileName(NULL, cCurrentSystemDirectory, MAX_PATH);
	CString strApplicationName = cCurrentSystemDirectory;

	CString strApplicationPath = strApplicationName.Left(strApplicationName.ReverseFind('\\'));	//获得不带应用程序文件名的应用程序路径(去掉应用程序文件名)	

	// Dicom Viewer
	CString strCVDicomViewer = strApplicationPath + AUTOVIEW_DIRECTORY + CVDICOMVIEWER_DIRECTORY;
	hFind = FindFirstFile(strCVDicomViewer, &fd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
		
		m_BurnPartner.AddFile(strCVDicomViewer);
		
	}

	// autorun.inf
	CString strAutorun = strApplicationPath + AUTOVIEW_DIRECTORY + CVDICOMVIEWER_AUTORUN_FILE;
	hFind = FindFirstFile(strAutorun, &fd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
		
		m_BurnPartner.AddFile(strAutorun);			
	}
	
	return TRUE;
}


/**
 ********************************************************************
 * \brief 获取卷标
 *  
 *  
 * \param LPCTSTR szJobID : [in] 
 * 
 * \return CString  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CString CBurner::GetVolumeLabel(LPCTSTR szJobID)
{
	CString strVolumeLabel = BURN_DISC_NAME_PREFIX;
// 	strVolumeLabel += _T(" ");
// 	strVolumeLabel += CString(szJobID).Left(8);

	return strVolumeLabel;
}
