/* Time: <@(#)JobQueue.cpp   2009-3-5 - 10:47:45   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : JobQueue.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The job queue class
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:47:45		FanZF	Creation
 *
 *********************************************************************
 */

// PrintJobQueue.cpp: implementation of the CPrintJobQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JobQueue.h"
#include "UserGuidanceOpt.h"
#include "PADataBaseOpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CJobQueue::CJobQueue()
{
	//Initialize the member
	m_pHeadNode		= NULL;
	m_CurNodeNum	= 0;	

}

CJobQueue::~CJobQueue()
{
	ClearQueque();
}

BOOL CJobQueue::PushJob(PAJob* pJob)
{

	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	if(m_CurNodeNum < QUE_LEN_MAX)
	{

		//create a job node
		PAJobNode* pNewJobNode = new PAJobNode;
		pNewJobNode->pJob = pJob;
		pNewJobNode->pNextNode = NULL;

		if(m_pHeadNode)
		{
			//Set it to the end of queue
			PAJobNode* pTailNode = m_pHeadNode;
			while (pTailNode->pNextNode)
				pTailNode = pTailNode->pNextNode;
			
			pTailNode->pNextNode = pNewJobNode;
		}
		else
		{ 
			//If no member and set the head of queue
			m_pHeadNode = pNewJobNode;
		}

		//<< Add JobInfo to P&A database
		if (!CPADataBaseOpt::GetInstance()->AddJob(pJob))
		{
			PRINTTRACE_ERROR("CPADataBaseOpt::GetInstance()->AddJob(pJob)")
		}
		
		m_CurNodeNum++;
		sLock.Unlock();
		return TRUE;

	}else
	{
		sLock.Unlock();
		return FALSE;
	}	
}



BOOL CJobQueue::PullJob(PAJob** ppJob)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	if(m_pHeadNode)
	{
		//Get a job from the head of queue
		PAJobNode* pTempNode = m_pHeadNode;
		*ppJob = pTempNode->pJob;
		m_pHeadNode = m_pHeadNode->pNextNode;
		
		//Delete it and reduce the number of member
		delete pTempNode;
		m_CurNodeNum--;	
		sLock.Unlock();
		return TRUE;

	}else
	{
		sLock.Unlock();
		return FALSE;		
	}
}

int CJobQueue::DeleteJob(LPCTSTR szJobID)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	int iErrCode = E_OK;

	PAJobNode* pFormerNode = m_pHeadNode;
	PAJobNode* pobjNode = m_pHeadNode;

	if (pFormerNode)
	{
		if (!wcscmp(szJobID, (LPCTSTR)pFormerNode->pJob->strJobID))
		{
			pobjNode = pFormerNode;
		}
		else
		{
			pobjNode = pFormerNode->pNextNode;
			while(pobjNode)
			{
				if (!wcscmp(szJobID, (LPCTSTR)pobjNode->pJob->strJobID))
				{
					break;
				}
				else
				{
					pFormerNode = pFormerNode->pNextNode;
					pobjNode = pFormerNode->pNextNode;
				}
			}
		}

		if (pobjNode)
		{
			if (enumJobState_Executing == pobjNode->pJob->enumJobState)
			{
				ARCHVTRACE_ERROR("Can't delete Job since it's state is Executing")
				sLock.Unlock();
				return E_JOBQUEUE_CANT_DELETE_EXECUTTING_JOB;
			}
			else if (enumJobState_Submitted == pobjNode->pJob->enumJobState)
			{
				ARCHVTRACE_ERROR("Can't delete Job since it's state is Submitted")
				sLock.Unlock();
				return E_JOBQUEUE_CANT_DELETE_SUBMITTED_JOB;
			}
			else
			{
				if (m_pHeadNode == pobjNode)
				{
					m_pHeadNode = pobjNode->pNextNode;
				}
				else
				{
					pFormerNode->pNextNode = pobjNode->pNextNode;
				}

				//<< 删除添加至P&A database
				if (!CPADataBaseOpt::GetInstance()->SetJob(pobjNode->pJob))
				{
					PRINTTRACE_ERROR(_T("CPADataBaseOpt::GetInstance()->SetJob(pobjNode->pJob)"))
				}

				delete pobjNode->pJob;
				delete pobjNode;
				
				m_CurNodeNum--;
				ARCHVTRACE_INFO("A Job deleted")
				sLock.Unlock();
				return E_OK;
			}
		}
		else
		{
			ARCHVTRACE_ERROR("No Job with specified JobID")
			sLock.Unlock();
			return E_UNEXPECTED_ERROR;
		}
	}
	else
	{
		ARCHVTRACE_ERROR("No Job in job queue, NULL == m_pHeadNode")
		sLock.Unlock();
		return E_UNEXPECTED_ERROR;
	}
}

BOOL CJobQueue::ClearQueque()
{
	PAJobNode *pTemp, *pCurrent = m_pHeadNode;

	//Delete the list and release the memory
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	while(pCurrent != NULL)
	{
		pTemp = pCurrent->pNextNode;

		//<< 删除前写入P&A database
		if (!CPADataBaseOpt::GetInstance()->SetJob(pCurrent->pJob))
		{
			PRINTTRACE_ERROR(_T("CPADataBaseOpt::GetInstance()->SetJob(pobjNode->pJob)"))
		}

		delete pCurrent->pJob;
        delete pCurrent;
		pCurrent = pTemp;
	}
	m_pHeadNode = NULL ;
	m_CurNodeNum = 0 ;
	sLock.Unlock();
	return TRUE;
}


SHORT CJobQueue::GetJobNumber()
{

	return m_CurNodeNum;

}

PAJobNode* CJobQueue::GetHeadJobNode()
{
	return m_pHeadNode;
}

PAJob* CJobQueue::GetJob(LPCTSTR szJobID)
{

	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	PAJobNode* pCurrent = m_pHeadNode;
	while(pCurrent != NULL)
	{
		if (!wcscmp(szJobID, (LPCTSTR)pCurrent->pJob->strJobID))
		{
			sLock.Unlock();
			return pCurrent->pJob;
		}
		else
		{
			pCurrent = pCurrent->pNextNode;
		}
	}

	sLock.Unlock();
	return NULL;
}

BOOL CJobQueue::HasSubmittedJob()
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	
	PAJobNode* pCurrent = m_pHeadNode;
	while (pCurrent)
	{
		if (enumJobState_Submitted == pCurrent->pJob->enumJobState)
		{
			sLock.Unlock();
			return TRUE;
		}
		else
			pCurrent = pCurrent->pNextNode;
	}

	sLock.Unlock();
	return FALSE;
}

	//
PAJob* CJobQueue::GetASubmittedJob()
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	
	PAJobNode* pCurrent = m_pHeadNode;
	while (pCurrent)
	{
		if (enumJobState_Submitted == pCurrent->pJob->enumJobState)
		{
			sLock.Unlock();
			return pCurrent->pJob;
		}
		else
			pCurrent = pCurrent->pNextNode;
	}

	sLock.Unlock();
	return NULL;
}

BOOL CJobQueue::GetJobList(JobInfo** ppJobInfoList, long* pLen)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	*pLen = m_CurNodeNum;

	if (0 == *pLen)
	{
		*ppJobInfoList = NULL;

		sLock.Unlock();
		return TRUE;
	}

	ULONG cb = sizeof(**ppJobInfoList) * (*pLen);
	*ppJobInfoList = (JobInfo*)CoTaskMemAlloc(cb);
	if (NULL == *ppJobInfoList)
	{
		sLock.Unlock();
		return FALSE;
	}

	int iIndex = 0;
	CString strIndex;
	JobInfo* pJobInfo = *ppJobInfoList;

	PAJobNode* pTemp = m_pHeadNode;
	for (int i = 0; i < m_CurNodeNum; i++)
	{
		if (!GetJobDetailInfo(pTemp->pJob, &pJobInfo[iIndex]))
		{
			CoTaskMemFree(*ppJobInfoList);
			*ppJobInfoList = NULL;
			pLen = 0;

			sLock.Unlock();
			return FALSE;
		}
		else
		{
 			pTemp = pTemp->pNextNode;
			iIndex++;
		}
	}

	sLock.Unlock();
	return TRUE;

}

BOOL CJobQueue::MoveJobForward(LPCTSTR szJobID)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	
	PAJobNode* pCurrent = m_pHeadNode;
	while (pCurrent)
	{
		if (!pCurrent->pJob->strJobID.Compare(szJobID))
		{
			// Dst--->XXX
			// the Dst Job is HeadNode, so just return
			sLock.Unlock();
			return TRUE;
		}
		if ((NULL != pCurrent->pNextNode) && (!pCurrent->pNextNode->pJob->strJobID.Compare(szJobID)))
		{
			// head--->Dst--->XXX
			// the Dst Job is the Second Job
			m_pHeadNode = pCurrent->pNextNode;
			pCurrent->pNextNode = m_pHeadNode->pNextNode;
			m_pHeadNode->pNextNode = pCurrent;
			sLock.Unlock();
			return TRUE;
		}
		else if ((NULL != pCurrent->pNextNode->pNextNode) && (!pCurrent->pNextNode->pNextNode->pJob->strJobID.Compare(szJobID)))
		{
			// AAA--->BBB--->Dst--->XXX
			PAJobNode* pDst = pCurrent->pNextNode->pNextNode;
			pCurrent->pNextNode->pNextNode = pDst->pNextNode;
			pDst->pNextNode = pCurrent->pNextNode;
			pCurrent->pNextNode = pDst;
			sLock.Unlock();
			return TRUE;
		}
		else
		{
			pCurrent = pCurrent->pNextNode;
		}
	}

	sLock.Unlock();
	return FALSE;
}

BOOL CJobQueue::MoveJobBackward(LPCTSTR szJobID)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	
	PAJobNode* pCurrent = m_pHeadNode;
	while (pCurrent)
	{
		if (!pCurrent->pJob->strJobID.Compare(szJobID))
		{
			// Dst--->XXX
			// the Dst Job is HeadNode
			if (NULL == pCurrent->pNextNode)
			{
				// Dst--->NULL
				// the Dst is tail node too, so just return
				sLock.Unlock();
				return TRUE;
			}
			else
			{
				// Dst--->XXX
				m_pHeadNode = pCurrent->pNextNode;
				pCurrent->pNextNode = m_pHeadNode->pNextNode;
				m_pHeadNode->pNextNode = pCurrent;
				sLock.Unlock();
				return TRUE;
			}
		}
		else if ((NULL != pCurrent->pNextNode) && (!pCurrent->pNextNode->pJob->strJobID.Compare(szJobID)))
		{
			// AAA--->Dst--->XXX
			if (NULL == pCurrent->pNextNode->pNextNode)
			{
				// AAA--->Dst--->NULL
				// Dst is the tail node, so just return;
				sLock.Unlock();
				return TRUE;
			}
			else
			{
				// AAA--->Dst--->BBB
				PAJobNode* pDst = pCurrent->pNextNode;
				pCurrent->pNextNode = pDst->pNextNode;
				pDst->pNextNode = pCurrent->pNextNode->pNextNode;
				pCurrent->pNextNode->pNextNode = pDst;
				sLock.Unlock();
				return TRUE;
			}

		}
		else
		{
			pCurrent = pCurrent->pNextNode;
		}
	}

	sLock.Unlock();
	return FALSE;
}

BOOL CJobQueue::IsPatientStudySeriesImageUIDInUse(PatientAdminUIDType enumUIDType, vector<CString>* pvtrUIDList)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	
	BOOL bOccupied = FALSE;

	PAJobNode* pCurrent = m_pHeadNode;

	int nJobType; //临时变量，存Job类型	
	while (pCurrent)
	{
		if (enumJobState_Submitted == pCurrent->pJob->enumJobState ||
			enumJobState_Executing == pCurrent->pJob->enumJobState)
		{
			//获取Job的工作类型  [ GaoXing 8/25/2009]
			nJobType = pCurrent->pJob->enumJobType;	
			switch (enumUIDType)
			{
			case enumPatientAdminUIDType_Patient:
				{
					if (nJobType == enumJobType_DiscImportJob) //导入
					{
						DiscImportJobSettingsStruct* pDiscImportSettingStruct = (DiscImportJobSettingsStruct*)pCurrent->pJob->pData;
						for (int i = 0; i < pDiscImportSettingStruct->vtrImagesToBeImported.size(); i++)
						{
							CString strPatientUID = pDiscImportSettingStruct->vtrImagesToBeImported[i].strPatientUID;
							
							for (int j = 0; j < pvtrUIDList->size(); j++)
							{
								if (!strPatientUID.CompareNoCase((*pvtrUIDList)[j]))
								{
									sLock.Unlock();
									return TRUE;
								}
							}
						}
					}
					else 
					{
						for (int i = 0; i < pCurrent->pJob->vtrPatient.size(); i++)
						{
							CString strUID = CBSTROpt::BSTRToCString(pCurrent->pJob->vtrPatient[i].bsPatientUID);
							PRINTTRACE_INFO(strUID);
							for (int j = 0; j < pvtrUIDList->size(); j++)
							{
								if (!strUID.CompareNoCase((*pvtrUIDList)[j]))
								{
									sLock.Unlock();
									return TRUE;
								}
							}
						}
					}
					
					break;
				}
			case enumPatientAdminUIDType_Study:
				{
					if (nJobType == enumJobType_DiscImportJob) //导入
					{
						DiscImportJobSettingsStruct* pDiscImportSettingStruct = (DiscImportJobSettingsStruct*)pCurrent->pJob->pData;
						for (int i = 0; i < pDiscImportSettingStruct->vtrImagesToBeImported.size(); i++)
						{
							CString strStudyUID = pDiscImportSettingStruct->vtrImagesToBeImported[i].strStudyUID;
							
							for (int j = 0; j < pvtrUIDList->size(); j++)
							{
								if (!strStudyUID.CompareNoCase((*pvtrUIDList)[j]))
								{
									sLock.Unlock();
									return TRUE;
								}
							}
						}
					}
					else
					{
						for (int i = 0; i < pCurrent->pJob->vtrStudy.size(); i++)
						{
							CString strUID = CBSTROpt::BSTRToCString(pCurrent->pJob->vtrStudy[i].bsStudyUID);
							for (int j = 0; j < pvtrUIDList->size(); j++)	
							{
								if (!strUID.CompareNoCase((*pvtrUIDList)[j]))
								{
									sLock.Unlock();
									return TRUE;
								}
							}
						}
					}
					break;
				}
			case enumPatientAdminUIDType_Series:
				{
					if (nJobType == enumJobType_DiscImportJob) //导入
					{
						DiscImportJobSettingsStruct* pDiscImportSettingStruct = (DiscImportJobSettingsStruct*)pCurrent->pJob->pData;
						for (int i = 0; i < pDiscImportSettingStruct->vtrImagesToBeImported.size(); i++)
						{
							CString strSeriesUID = pDiscImportSettingStruct->vtrImagesToBeImported[i].strSeriesUID;
							
							for (int j = 0; j < pvtrUIDList->size(); j++)
							{
								if (!strSeriesUID.CompareNoCase((*pvtrUIDList)[j]))
								{
									sLock.Unlock();
									return TRUE;
								}
							}
						}
					}
					else
					{
						for (int i = 0; i < pCurrent->pJob->vtrSeries.size(); i++)
						{
							CString strUID = CBSTROpt::BSTRToCString(pCurrent->pJob->vtrSeries[i].bsSeriesUID);
							for (int j = 0; j < pvtrUIDList->size(); j++)
							{
								if (!strUID.CompareNoCase((*pvtrUIDList)[j]))
								{
									sLock.Unlock();
									return TRUE;
								}
							}
						}
					}
					break;
				}
			case enumPatientAdminUIDType_Image:
				{
					if (nJobType == enumJobType_DiscImportJob) //导入
					{
						DiscImportJobSettingsStruct* pDiscImportSettingStruct = (DiscImportJobSettingsStruct*)pCurrent->pJob->pData;
						for (int i = 0; i < pDiscImportSettingStruct->vtrImagesToBeImported.size(); i++)
						{
							CString strImageUID = pDiscImportSettingStruct->vtrImagesToBeImported[i].strImageUID;
							
							for (int j = 0; j < pvtrUIDList->size(); j++)
							{
								if (!strImageUID.CompareNoCase((*pvtrUIDList)[j]))
								{
									sLock.Unlock();
									return TRUE;
								}
							}
						}
					}
					else
					{
						for (int i = 0; i < pCurrent->pJob->vtrImages.size(); i++)
						{
							CString strUID = CBSTROpt::BSTRToCString(pCurrent->pJob->vtrImages[i].bsImageUID);
							for (int j = 0; j < pvtrUIDList->size(); j++)
							{
								if (!strUID.CompareNoCase((*pvtrUIDList)[j]))
								{
									sLock.Unlock();
									return TRUE;
								}
							}
						}
					}
					break;
				}
			default:
				sLock.Unlock();
				return FALSE;
				}
			}
			
			pCurrent = pCurrent->pNextNode;
		}
		
	sLock.Unlock();
	return FALSE;
}

BOOL CJobQueue::IsUnfinishedJobExist(JobType enumJobType, BOOL* pbExist)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	
	*pbExist = FALSE;

	PAJobNode* pCurrent = m_pHeadNode;
	while (pCurrent)
	{
		if (pCurrent->pJob->enumJobType == enumJobType)
		{
			if (enumJobState_Submitted == pCurrent->pJob->enumJobState 
				|| enumJobState_Executing == pCurrent->pJob->enumJobState)
			{
				*pbExist = TRUE;
				break;
			}
		}
		pCurrent = pCurrent->pNextNode;
	}

	sLock.Unlock();
	return TRUE;
}

BOOL CJobQueue::GetJobInfo(LPCTSTR szJobID, JobInfo* pJobInfo)
{
	if (NULL == szJobID)
	{
		return FALSE;
	}

	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	PAJobNode* pCurrent = m_pHeadNode;
	while(pCurrent != NULL)
	{
		if (!wcscmp(szJobID, (LPCTSTR)pCurrent->pJob->strJobID))
		{
			//<< 找到该Job
			if (GetJobDetailInfo(pCurrent->pJob, pJobInfo))
			{
				sLock.Unlock();
				return TRUE;
			}
			else
			{
				sLock.Unlock();
				return FALSE;
			}
		}
		else
		{
			pCurrent = pCurrent->pNextNode;
		}
	}

	sLock.Unlock();
	return FALSE;


}

BOOL CJobQueue::GetJobDetailInfo(PAJob* pJob, JobInfo* pJobInfo)
{
	if (NULL == pJob || NULL == pJobInfo)
	{
		return FALSE;
	}

	//<< JobID
	pJobInfo->bsJobID = pJob->strJobID.AllocSysString();

	//<< Index
	int iIndex = GetJobIndex(pJob);
	if (-1 == iIndex)
	{
		return FALSE;
	}
	CString strIndex;
	strIndex.Format(_T("%d"), iIndex);
	pJobInfo->bsIndex = strIndex.AllocSysString();

	//<< Type
	CString strType;
	switch (pJob->enumJobType)
	{
	case enumJobType_BurnJob:
		strType = JOB_TYPE_BURN;
		break;
	case enumJobType_AutoSendJob:
		strType = JOB_TYPE_SEND_AUTO;
		break;
	case enumJobType_ManualSendJob:
		strType = JOB_TYPE_SEND_MANUAL;
		break;
	case enumJobType_DiscImportJob:
		strType = JOB_TYPE_IMPORT;
		break;
	default:
		strType = _T("");
		break;
	}
	pJobInfo->bsType = _TT(strType).AllocSysString(); 
	pJobInfo->enumType = pJob->enumJobType;

	//<< Submit Time
	CString strSubmitTime;
	strSubmitTime.Format(_T("%s-%s-%s %s:%s:%s"), pJob->strJobID.Left(4),
												pJob->strJobID.Mid(4, 2),
												pJob->strJobID.Mid(6, 2),
												pJob->strJobID.Mid(8, 2),
												pJob->strJobID.Mid(10, 2),
												pJob->strJobID.Mid(12, 2));
	pJobInfo->bsSubmitTime = strSubmitTime.AllocSysString();


	//<< State
	CString strState;
	switch (pJob->enumJobState)
	{
	case enumJobState_Submitted:
		strState = JOB_STATE_SUBMITTED;
		break;
	case enumJobState_Executing:
		strState = JOB_STATE_EXECUTING;
		break;
	case enumJobState_Completed:
		strState = JOB_STATE_COMPLETED;
		break;
	case enumJobState_Cancelled:
		strState = JOB_STATE_CANCELLED;
		break;
	case enumJobState_Failed:
		strState = JOB_STATE_FAILED;
		break;
	default:
		strState = _T("");
		break;
	}
	pJobInfo->bsState = _TT(strState).AllocSysString(); 

	//<< Phase
	pJobInfo->bsPhase = pJob->strPhase.AllocSysString();

	//<< Progress
	CString strProgress;
	switch (pJob->enumJobProgressUsing)
	{
	case enumJobProgressUsing_None:
		{
			if (0 == pJob->uiTotal)
			{
				strProgress = _T("");
			}
			else
			{
				strProgress.Format(_T("%d%%"), (pJob->uiCompleted*100)/pJob->uiTotal);
			}
		}
		break;
	case enumJobProgressUsing_CompletedTotal:
		{
			if (0 == pJob->uiTotal)
			{
				strProgress = _T("");
			}
			else
			{
				strProgress.Format(_T("%d%%"), (pJob->uiCompleted*100)/pJob->uiTotal);
			}
		}
		break;
	case enumJobProgressUsing_Percentage:
		{
			strProgress.Format(_T("%d%%"), pJob->dwPercentage);
		}
		break;
	default:
		{
			strProgress = _T("");
		}
		break;
	}
	pJobInfo->bsProgress = strProgress.AllocSysString();

	//<< Detail
	if (pJob->vtrDetail.size() > 0)
	{
		pJobInfo->bsDetail = pJob->vtrDetail[pJob->vtrDetail.size()-1].strDetail.AllocSysString();
	}
	else
	{
		pJobInfo->bsDetail = CString(_T("")).AllocSysString();
	}

	return TRUE;
}

int CJobQueue::GetJobIndex(PAJob* pJob)
{
	if (NULL == pJob)
	{
		return -1;
	}
	
	int iIndex = 0;
	PAJobNode* pCurrent = m_pHeadNode;
	while(pCurrent != NULL)
	{
		++iIndex;
		if (pJob == pCurrent->pJob)
		{
			//<< 找到该Job
			return iIndex;
		}
		else
		{
			pCurrent = pCurrent->pNextNode;
		}
	}

	return -1;
}
