/* Time: <@(#)PAJob.cpp   2009-3-5 - 10:49:33   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : PAJob.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The job class
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:49:33		FanZF	Creation
 *
 *********************************************************************
 */

// PAJob.cpp: implementation of the CPAJob class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PAJob.h"
#include "UserGuidanceOpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PAJob::PAJob() : enumJobType(enumJobType_InitJob)
			   , bCancelFlag(FALSE)
			   , enumJobState(enumJobState_Submitted)
			   , enumJobProgressUsing(enumJobProgressUsing_None)
			   , uiCompleted(0)
			   , uiTotal(100)
			   , dwPercentage(0)
{
	vtrDetail.clear();

	vtrPatient.clear();
	vtrStudy.clear();
	vtrSeries.clear();
	vtrSeries.clear();
	vtrImages.clear();

	pData = NULL;
}

PAJob::~PAJob()
{
	CBSTROpt::FreePAJob(this);
	ReleaseData();
}

void PAJob::SetState(JobState enumState)
{
	enumJobState = enumState;

	CString strState;
	switch(enumJobState)
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
		PRINTTRACE_ERROR(_T("unknow Job State!"));
		break;
	}

	BSTR bsJobID = strJobID.AllocSysString();
	BSTR bsState = _TT(strState).AllocSysString(); 
	Notify(NOTIFY_JOB_STATE_CHANGED, (LPARAM)bsJobID, (WPARAM)bsState);
}

void PAJob::SetPhase(LPCTSTR szJobPhase)
{
	strPhase = _TT(szJobPhase); 

	BSTR bsJobID = strJobID.AllocSysString();
	BSTR bsPhase = strPhase.AllocSysString();
	Notify(NOTIFY_JOB_PHASE_CHANGED, (LPARAM)bsJobID, (WPARAM)bsPhase);
}

void PAJob::SetProgress(JobProgressUsing enumProgressUsing, UINT uiFirstParam, UINT uiSecondParam)
{
	enumJobProgressUsing = enumProgressUsing;
	CString strProgress;

	switch (enumJobProgressUsing)
	{
	case enumJobProgressUsing_None:
		{
			if (0 == uiTotal)
			{
				strProgress = _T("");
			}
			else
			{
				strProgress.Format(_T("%d%%"), (uiCompleted*100)/uiTotal);
			}
		}
		break;
	case enumJobProgressUsing_CompletedTotal:
		{
			uiCompleted = uiFirstParam;
			uiTotal = uiSecondParam;
			if (0 == uiTotal)
			{
				strProgress = _T("");
			}
			else
			{
				strProgress.Format(_T("%d%%"), (uiFirstParam*100)/uiSecondParam);
			}
		}
		break;
	case enumJobProgressUsing_Percentage:
		{
			dwPercentage = uiFirstParam;
			strProgress.Format(_T("%d%%"), uiFirstParam);
		}
		break;
	default:
		{
			strProgress = _T("");
		}
		break;
	}

	BSTR bsJobID = strJobID.AllocSysString();
	BSTR bsProgress = strProgress.AllocSysString();;

	Notify(NOTIFY_JOB_PROGRESS_CHANGED, (LPARAM)bsJobID, (WPARAM)bsProgress);
}

void PAJob::SetDetail(LPCTSTR szDetailInfo, LPCTSTR szAddInfo)
{
	CSingleLock sLock(&m_CSLockSetDetail);
	sLock.Lock();
	
	CString strDetailInfo;
	CString strFormat = _TT(szDetailInfo); 
	if (NULL != szDetailInfo)
	{
		strDetailInfo.Format(strFormat, szAddInfo);
	}
	else
	{
		strDetailInfo = strFormat;
	}

	JobDetail aJobDetail;
	::GetLocalTime(&aJobDetail.stDateTime);
	aJobDetail.strDetail = strDetailInfo;
	vtrDetail.push_back(aJobDetail);

	JobDetailStruct* pJobDetail = new JobDetailStruct;
	pJobDetail->bsJobID = strJobID.AllocSysString();
	CString strTime;
	strTime.Format(_T("%02d:%02d:%02d"), aJobDetail.stDateTime.wHour, aJobDetail.stDateTime.wMinute, aJobDetail.stDateTime.wSecond);
	pJobDetail->bsTime = strTime.AllocSysString();
	pJobDetail->bsDetail = vtrDetail[vtrDetail.size()-1].strDetail.AllocSysString();

	Notify(NOTIFY_JOB_DETAIL_CHANGED, (LPARAM)pJobDetail);

	sLock.Unlock();
}

void PAJob::SetDetailByUGID(LONG iUGID)
{
	CSingleLock sLock(&m_CSLockSetDetail);
	sLock.Lock();

	CString strDetailInfo;
	strDetailInfo = CUserGuidanceOpt::GetInstance()->GetString(iUGID);

	JobDetail aJobDetail;
	::GetLocalTime(&aJobDetail.stDateTime);
	aJobDetail.strDetail = _TT(strDetailInfo); 
	vtrDetail.push_back(aJobDetail);

	JobDetailStruct* pJobDetail = new JobDetailStruct;
	pJobDetail->bsJobID = strJobID.AllocSysString();
	CString strTime;
	strTime.Format(_T("%2d:%2d:%2d"), aJobDetail.stDateTime.wHour, aJobDetail.stDateTime.wMinute, aJobDetail.stDateTime.wSecond);
	pJobDetail->bsTime = strTime.AllocSysString();
	pJobDetail->bsDetail = vtrDetail[vtrDetail.size()-1].strDetail.AllocSysString();

	Notify(NOTIFY_JOB_DETAIL_CHANGED, (LPARAM)pJobDetail);

	sLock.Unlock();
}

void PAJob::SetDetailOriginal(LPCTSTR szDetailInfo)
{
	CSingleLock sLock(&m_CSLockSetDetail);
	sLock.Lock();

	JobDetail aJobDetail;
	::GetLocalTime(&aJobDetail.stDateTime);
	aJobDetail.strDetail = szDetailInfo;
	vtrDetail.push_back(aJobDetail);

	JobDetailStruct* pJobDetail = new JobDetailStruct;
	pJobDetail->bsJobID = strJobID.AllocSysString();
	CString strTime;
	strTime.Format(_T("%2d:%2d:%2d"), aJobDetail.stDateTime.wHour, aJobDetail.stDateTime.wMinute, aJobDetail.stDateTime.wSecond);
	pJobDetail->bsTime = strTime.AllocSysString();
	pJobDetail->bsDetail = vtrDetail[vtrDetail.size()-1].strDetail.AllocSysString();

	Notify(NOTIFY_JOB_DETAIL_CHANGED, (LPARAM)pJobDetail);

	sLock.Unlock();
}

int PAJob::GetImageCount()
{
	return vtrImages.size();
}


void PAJob::ReleaseData()
{
	if (NULL == pData)
		return;

	switch (enumJobType)
	{
	case enumJobType_PrintJob:
		delete (PrintJobSettingsStruct*)pData;
		pData = NULL;
		break;
	case enumJobType_BurnJob:
		delete (BurnJobSettingsStruct*)pData;
		pData = NULL;
		break;
	case enumJobType_AutoSendJob:
	case enumJobType_ManualSendJob:
		delete (TransferJobSettingsStruct*)pData;
		pData = NULL;
		break;
	case enumJobType_DiscImportJob:
		delete (DiscImportJobSettingsStruct*)pData;
		pData = NULL;
		break;
	default:
		break;
	}
}
