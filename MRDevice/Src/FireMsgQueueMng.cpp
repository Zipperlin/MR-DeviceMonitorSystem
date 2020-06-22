/* Time: <@(#)FireMsgQueueMng.cpp   2009-3-5 - 10:44:42   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : FireMsgQueueMng.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Management for fire message queue
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:44:42		FanZF	Creation
 *
 *********************************************************************
 */

// FireMsgQueueMng.cpp: implementation of the CFireMsgQueueMng class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FireMsgQueueMng.h"


DWORD WINAPI HandleMsgThreadProc(LPVOID lpParam)
{
	try
	{
		CFireMsgQueueMng* pMng = (CFireMsgQueueMng*)lpParam;

		if (pMng->HandleMsg())
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

CFireMsgQueueMng* CFireMsgQueueMng::m_pInstance = NULL;

CFireMsgQueueMng::CFireMsgQueueMng()
{
	m_bExist = FALSE;
	m_pCPA = NULL;
	m_hThread = NULL;
	m_hEvent = NULL;
}

CFireMsgQueueMng::~CFireMsgQueueMng()
{

}

CFireMsgQueueMng* CFireMsgQueueMng::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CFireMsgQueueMng;
	}

	return m_pInstance;
}

void CFireMsgQueueMng::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

BOOL CFireMsgQueueMng::Init(CPA* pPA)
{
	m_pCPA = pPA;
	m_bExist = TRUE;

	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThread = CreateThread(NULL, 0, HandleMsgThreadProc, this, 0, NULL);
	if (NULL == m_hThread)
	{
		PRINTTRACE_ERROR("ERROR: CFireMsgQueueMng CreateThread HandleMsgThreadProc")
		return FALSE;
	}

	return TRUE;
}

BOOL CFireMsgQueueMng::UnInit()
{
	BOOL bRet = TRUE;

	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	m_bExist = FALSE;
	sLock.Unlock();

	if (m_hEvent)
		SetEvent(m_hEvent);

	if (m_hThread)
	{
		DWORD dwRet = WaitForSingleObject(m_hThread, FIREMSGQUEUEMNG_WAIT_THREAD_EXIT_TIME);
		if (WAIT_OBJECT_0 == dwRet)
		{
		}
		else if (WAIT_TIMEOUT == dwRet)
		{
			if (TerminateThread(m_hThread, 0))
			{
				ARCHVTRACE_INFO("TerminateThread: HandleMsgThreadProc() of FireMsgQueueMng succeed")
			}
			else
			{
				ARCHVTRACE_ERROR("failed to TerminateThread: HandleMsgThreadProc() of FireMsgQueueMng")
				bRet = FALSE;
			}
		}

		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	if (m_hEvent)
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}

	m_MsgQueue.ClearQueque();
	m_pCPA = NULL;
	m_bExist = FALSE;

	return bRet;
}

BOOL CFireMsgQueueMng::PushMsg(FireMsgNode& msg)
{
	BOOL bRet;
	bRet = m_MsgQueue.PushPAMsg(msg);

	if (bRet)
	{
		SetEvent(m_hEvent);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CFireMsgQueueMng::HandleMsg()
{
	FireMsgNode msgNode;
	UINT uiMessage;
	LPARAM lParam;
	WPARAM wParam;
	CString strTemp;
	BSTR bsTemp;
	CString strFirstParam;
	CString strSecondParam;
	BSTR bsFirstParam;
	BSTR bsSecondParam;
	UGNotifyStruct* pUGNStruct = NULL;

	while (m_bExist)
	{
		if (m_MsgQueue.GetMsgNumber() > 0)
		{
			SetEvent(m_hEvent);
		}
		if (WaitForSingleObject(m_hEvent, INFINITE) == WAIT_OBJECT_0)
			if (m_MsgQueue.GetMsgNumber() > 0)
			{
				m_MsgQueue.PullPAMsg(msgNode);
				uiMessage = msgNode.msg.uiMessage;
				lParam = msgNode.msg.lParam;
				wParam = msgNode.msg.wParam;
				
				switch(uiMessage)
				{
				case NOTIFY_SUBMODULE_STATE_CHANGED:
					switch ((SubModule)lParam)
					{
					case enumSubModule_PRINT:
						m_pCPA->Fire_ReportPrintWorkStatus(enumSubModule_PRINT, (SubModuleState)wParam);
						break;
					case enumSubModule_BURN:
						m_pCPA->Fire_ReportBurnWorkStatus(enumSubModule_BURN, (SubModuleState)wParam);
						break;
					case enumSubModule_TRANSFER:
						m_pCPA->Fire_ReportTransferWorkStatus(enumSubModule_TRANSFER, (SubModuleState)wParam);
						break;
					case enumSubModule_DISCIMPORT:
						m_pCPA->Fire_ReportDiscImportWorkStatus(enumSubModule_DISCIMPORT, (SubModuleState)wParam);
						break;
					case enumSubModule_WLMPPS:
						m_pCPA->Fire_ReportWlMppsWorkStatus(enumSubModule_WLMPPS, (SubModuleState)wParam);
						break ;
					default:
						PRINTTRACE_ERROR("SubModule para error")
						break;
					}
					break;

				//<< PAGeneralEvent
				case NOTIFY_JOB_QUEUE_CHANGED:
					m_pCPA->Fire_ReportJobQueueChanged();
					break;
				case NOTIFY_JOB_STATE_CHANGED:
					bsFirstParam = (BSTR)lParam;
					bsSecondParam = (BSTR)wParam;
					m_pCPA->Fire_ReportJobState(bsFirstParam, bsSecondParam);
					CBSTROpt::FreeBSTR(bsFirstParam);
					CBSTROpt::FreeBSTR(bsSecondParam);
					break;
				case NOTIFY_JOB_PHASE_CHANGED:
					bsFirstParam = (BSTR)lParam;
					bsSecondParam = (BSTR)wParam;
					m_pCPA->Fire_ReportJobPhase(bsFirstParam, bsSecondParam);
					CBSTROpt::FreeBSTR(bsFirstParam);
					CBSTROpt::FreeBSTR(bsSecondParam);
					break;
				case NOTIFY_JOB_PROGRESS_CHANGED:
					bsFirstParam = (BSTR)lParam;
					bsSecondParam = (BSTR)wParam;
					m_pCPA->Fire_ReportJobProgress(bsFirstParam, bsSecondParam);
					CBSTROpt::FreeBSTR(bsFirstParam);
					CBSTROpt::FreeBSTR(bsSecondParam);
					break;
				case NOTIFY_JOB_DETAIL_CHANGED:
					m_pCPA->Fire_ReportJobDetail((JobDetailStruct*)lParam);
					CBSTROpt::FreeJobDetailStruct((JobDetailStruct*)lParam);
					delete (JobDetailStruct*)lParam;
					break;


				//<<
				case NOTIFY_FC_STATE_CHANGED:
					m_pCPA->Fire_ReportPrintFilmComposerStatus((FilmComposerStatus)lParam);
					break;
				case NOTIFY_FC_STARTUP:
					m_pCPA->Fire_ReportPrintFilmComposerStartUp();
					break;
				case NOTIFY_FC_ENABLE_FC:
					m_pCPA->Fire_ReportEnableFilmComposer((BOOL)lParam);
					break;
				case NOTIFY_CPA_STARTUPRESULT:
					m_pCPA->Fire_ReportStartupResult((STARTUPRESULT)lParam);
					break;
				case NOTIFY_CPA_WORKSTATE:
					m_pCPA->Fire_ReportWorkState((WORKSTATE)lParam);
					break;
				case NOTIFY_BURN_DEVICE_STATUS:
					m_pCPA->Fire_ReportBurnDeviceStatusChanged();
					break;
				case NOTIFY_BURN_ERROR:
					m_pCPA->Fire_ReportBurnErrorCode((int)lParam);
					break;
				case NOTIFY_BURN_PATIENTS_INFO:
					m_pCPA->Fire_ReportBurnPatientList((long)lParam, (BurnPatientInfoStruct*)wParam);
					CBSTROpt::FreeBurnPatientInfoStructList((BurnPatientInfoStruct*)wParam, (long)lParam);
					delete [](BurnPatientInfoStruct*)wParam;
					break;
				case NOTIFY_BURN_STUDYS_INFO:
					m_pCPA->Fire_ReportBurnStudyList((long)lParam, (BurnStudyInfoStruct*)wParam);
					CBSTROpt::FreeBurnStudyInfoStructList((BurnStudyInfoStruct*)wParam, (long)lParam);
					delete [](BurnStudyInfoStruct*)wParam;
					break;
				case NOTIFY_BURN_SERIES_INFO:
					m_pCPA->Fire_ReportBurnSeriesList((long)lParam, (BurnSeriesInfoStruct*)wParam);
					CBSTROpt::FreeBurnSeriesInfoStructList((BurnSeriesInfoStruct*)wParam, (long)lParam);
					delete [](BurnSeriesInfoStruct*)wParam;
					break;
				case NOTIFY_BURN_IMAGE_INFO:
					m_pCPA->Fire_ReportBurnImageList((long)lParam, (BurnImageInfoStruct*)wParam);
					CBSTROpt::FreeBurnImageInfoStructList((BurnImageInfoStruct*)wParam, (long)lParam);
					delete [](BurnImageInfoStruct*)wParam;
					break;
				case NOTIFY_BURN_MEDIA_NOT_READY:
					m_pCPA->Fire_ReportBurnMediaNotReady((BSTR)lParam);
					CBSTROpt::FreeBSTR((BSTR&)lParam);
					break;
				case NOTIFY_BURN_DEVICE_MEDIA_INFO_SPEED:
					m_pCPA->Fire_ReportDeviceSpeedInfo((long)lParam, (BurnSpeedInfo*)wParam);
					CBSTROpt::FreeBurnSpeedInfoList((BurnSpeedInfo*)wParam, (long)lParam);
					delete [](BurnSpeedInfo*)wParam;
					break;
				case NOTIFY_BURN_DEVICE_MEDIA_INFO_MEDIA:
					m_pCPA->Fire_ReportMediaInfo((BurnMediaInfo*)lParam);
					CBSTROpt::FreeBurnMediaInfo((BurnMediaInfo*)lParam);
					break;

				// DiscImport
				case NOTIFY_DISCIMPORT_DISCINFO_READY:
					m_pCPA->Fire_ReportDiscImportDiscInfo((BOOL)lParam);
					break;
				case NOTIFY_DISCIMPORT_GET_DISCINFO_STATE:
					bsTemp = (BSTR)lParam;
					m_pCPA->Fire_ReportDiscImportDiscInfoState(bsTemp);
					CBSTROpt::FreeBSTR(bsTemp);
					break;


				// Import Series State, Progress or Detail Changed
				case NOTIFY_IMPORT_SERIES_STATE_CHANGED:
					m_pCPA->Fire_ReportDiscImportSeriesStateChanged((DiscImport_SeriesStateStruct*)lParam);
					CBSTROpt::FreeDiscImport_SeriesStateStruct((DiscImport_SeriesStateStruct*)lParam);
					delete (DiscImport_SeriesStateStruct*)lParam;
					break;
				case NOTIFY_IMPORT_SERIES_PROGRESS_CHANGED:
					m_pCPA->Fire_ReportDiscImportSeriesProgressChanged((DiscImport_SeriesProgressStruct*)lParam);
					CBSTROpt::FreeDiscImport_SeriesProgressStruct((DiscImport_SeriesProgressStruct*)lParam);
					delete (DiscImport_SeriesProgressStruct*)lParam;
					break;
				case NOTIFY_IMPORT_SERIES_DETIAL_CHANGED:
					m_pCPA->Fire_ReportDiscImportSeriesDetailChanged((DiscImport_SeriesDetailStruct*)lParam);
					CBSTROpt::FreeDiscImport_SeriesDetailStruct((DiscImport_SeriesDetailStruct*)lParam);
					delete (DiscImport_SeriesDetailStruct*)lParam;
					break;
				case NOTIFY_IMPORT_ONE_IMAGE_IMPORTED:
					m_pCPA->Fire_ReportDiscImportOneImageImported();
					break;
				case NOTIFY_IMPORT_ONE_JOB_FINISHED:
					m_pCPA->Fire_ReportDiscImportOneJobFinished();
					break;
			
				// WLMPPS
				case NOTIFY_WLMPPS_REPORT_WORKLIST:
					m_pCPA->Fire_ReportWorkList((long)lParam, (WorkListStruct*)wParam);
					CBSTROpt::FreeWorkListStructList((WorkListStruct*)wParam, (long)lParam);
					delete [](WorkListStruct*)wParam;
					break;
				case NOTIFY_WLMPPS_SET_MPPS_FINISHED:
					m_pCPA->Fire_ReportSetMPPSStatusFinished((MppsSetResult*)lParam);
					CBSTROpt::FreeMppsSetResultStruct((MppsSetResult*)lParam);
					delete (MppsSetResult*)lParam;
					break;
				case NOTIFY_WLMPPS_MPPS_STATUS_CHANGED:
					bsTemp = (BSTR)lParam;
					m_pCPA->Fire_ReportMPPSStatusChanged(bsTemp, (WorkListStatus)wParam);
					CBSTROpt::FreeBSTR(bsTemp);
					break;
				
				// UserGuidance
				case NOTIFY_USERGUIDANCE:
					pUGNStruct = (UGNotifyStruct*)lParam;
					m_pCPA->Fire_UserGuidanceReporting(pUGNStruct->iMessageID, pUGNStruct->enumUGType, pUGNStruct->enumGUIPriority, pUGNStruct->bActive);
					delete pUGNStruct;
					break;


				// For Connection points
				case CP_ACQ_EXPOSURE_FLUO_PREPARING:
					if (m_pCPA->HandleBackGroundJobAcq())
					{
						PRINTTRACE_INFO("m_pPA->HandleBackGroundJobAcq()")
					}
					else
					{
						PRINTTRACE_ERROR("m_pPA->HandleBackGroundJobAcq()")
					}
					break;

				//Transfer has changed DB sendflag
				case NOTIFY_UI_DB_CHANGED:
					PRINTTRACE_INFO("m_pPA Fire_ReportUITransferChangeDB")
					m_pCPA->Fire_ReportUITransferChangeDB((BSTR)lParam, (BSTR)wParam);
					break;
 
				default:
					strTemp.Format(_T("UnHandled msg, uiMessage = %d"), uiMessage);
					PRINTTRACE_ERROR(strTemp)
					break;
				}
			}


	}
	return TRUE;
}