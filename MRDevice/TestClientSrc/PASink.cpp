// PASink.cpp: implementation of the CPASink class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PASink.h"
#include "TestClientSrc.h"
#include "TestClientSrcDlg.h"

extern CTestClientSrcDlg* g_smDlg;
extern HINSTANCE g_hResourceInstance;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPASink::CPASink()
{
	//Initialize the member
	m_dwCookie = 0;
	m_ICallBack = (IPAPrintEvent*)this;
	m_pConnectionPoint = NULL;

}

CPASink::~CPASink()
{
}

ULONG CPASink::AddRef()
{
	return 1;
}

ULONG CPASink::Release()
{
	return 0;
}

HRESULT CPASink::QueryInterface(REFIID riid, void** ppv)
{
	//Return the interface for callback
	if(riid == IID_IUnknown)
	{
		*ppv = (IPAPrintEvent*)this;
	}
	else if(riid == IID_IPAGeneralEvent)
	{
		*ppv = (IPAGeneralEvent*)this;
	}
	else if(riid == IID_IPAPrintEvent)
	{
		*ppv = (IPAPrintEvent*)this;
	}
	else if(riid == IID_IPABurnEvent)
	{
		*ppv = (IPABurnEvent*)this;
	}
	else if (riid == IID_IPATransferEvent)
	{
		*ppv = (IPATransferEvent*)this;
	}
	else if (riid == IID_IPADiscImportEvent)
	{
		*ppv = (IPADiscImportEvent*)this;
	}
	else if (riid == IID_IPAWLMPPSEvent)
	{
		*ppv = (IPAWLMPPSEvent*)this;
	}
	else if(riid == IID_IGeneralEvent)
	{
		*ppv = (IGeneralEvent*)this;
	}
	else if(riid == IID_IUserGuidanceEvent)
	{
		*ppv = (IUserGuidanceEvent*)this;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	return S_OK;
}

BOOL CPASink::SetConnection(REFCLSID rclsid, REFIID callid)
{
	HRESULT hResult = S_OK;
	IConnectionPointContainer* pContainer = NULL; 
	
	//Create the link to server by callback interface in order to receive event
	hResult = ::CoCreateInstance(rclsid, NULL, CLSCTX_LOCAL_SERVER,
		                         IID_IConnectionPointContainer,
								 (LPVOID*)&pContainer);
	
	if(hResult != S_OK || !pContainer)
		return FALSE;
	
	if(SUCCEEDED(pContainer->FindConnectionPoint(callid, &m_pConnectionPoint)))
	{
		//Register the callback
		hResult = m_pConnectionPoint->Advise((IUnknown*)m_ICallBack, &m_dwCookie);
		if (FAILED(hResult))
		{
			return FALSE;
		}
		//Release the connection point container
		pContainer->Release();
		if(hResult == S_OK)
			return TRUE;
		else
			return FALSE;
		
	}
	
	pContainer->Release();	
	return FALSE;
}

BOOL CPASink::ReleaseConnection()
{
	if(m_pConnectionPoint)
	{
		//Release the link
		m_pConnectionPoint->Unadvise(m_dwCookie);
		m_pConnectionPoint->Release();
		m_pConnectionPoint = NULL;

		return TRUE;
	}else
		return FALSE;
}

	// IPAGeneralEvent

STDMETHODIMP CPASink::ReportJobQueueChanged()
{
	g_smDlg->UpdateJobQueue();
	return S_OK;
}

STDMETHODIMP CPASink::ReportJobState(BSTR bsJobID, BSTR bsJobState)
{
	g_smDlg->UpdateJobState(bsJobID, bsJobState);

	CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
	if (!strJobID.Compare(g_smDlg->m_SendJObDetailDlg.GetJob()))
	{
		g_smDlg->m_SendJObDetailDlg.UpdateState(bsJobID, bsJobState);
	}
	else if (!strJobID.Compare(g_smDlg->m_BurnJObDetailDlg.GetJob()))
	{
		g_smDlg->m_BurnJObDetailDlg.UpdateState(bsJobID, bsJobState);
	}

	return S_OK;
}

STDMETHODIMP CPASink::ReportJobPhase(BSTR bsJobID, BSTR bsJobPhase)
{
	g_smDlg->UpdateJobPhase(bsJobID, bsJobPhase);

	CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
	if (!strJobID.Compare(g_smDlg->m_SendJObDetailDlg.GetJob()))
	{
		g_smDlg->m_SendJObDetailDlg.UpdatePhase(bsJobID, bsJobPhase);
	}
	else if (!strJobID.Compare(g_smDlg->m_BurnJObDetailDlg.GetJob()))
	{
		g_smDlg->m_BurnJObDetailDlg.UpdatePhase(bsJobID, bsJobPhase);
	}

	return S_OK;
}

STDMETHODIMP CPASink::ReportJobProgress(BSTR bsJobID, BSTR bsJobProgress)
{
	g_smDlg->UpdateJobProgress(bsJobID, bsJobProgress);

	CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
	if (!strJobID.Compare(g_smDlg->m_SendJObDetailDlg.GetJob()))
	{
		g_smDlg->m_SendJObDetailDlg.UpdateProgress(bsJobID, bsJobProgress);
	}
	else if (!strJobID.Compare(g_smDlg->m_BurnJObDetailDlg.GetJob()))
	{
		g_smDlg->m_BurnJObDetailDlg.UpdateProgress(bsJobID, bsJobProgress);
	}

	return S_OK;
}

STDMETHODIMP CPASink::ReportJobDetail(JobDetailStruct* pJobDetail)
{
	g_smDlg->UpdateJobDetail(pJobDetail);

	CString strJobID = CBSTROpt::BSTRToCString(pJobDetail->bsJobID);
	if (!strJobID.Compare(g_smDlg->m_SendJObDetailDlg.GetJob()))
	{
		g_smDlg->m_SendJObDetailDlg.UpdateDetail(pJobDetail);
	}
	else if (!strJobID.Compare(g_smDlg->m_BurnJObDetailDlg.GetJob()))
	{
		g_smDlg->m_BurnJObDetailDlg.UpdateDetail(pJobDetail);
	}


	return S_OK;
}


// IPAPrintEvent
STDMETHODIMP CPASink::ReportPrintWorkStatus(SubModule enumSubUnit, SubModuleState enumSubUnitStatus)
{  
//	AfxMessageBox("OK");
//	CString strTemp ;
//	CString str;
//	str = "Íê³É " ;
//	strTemp.Format("%d",PageCompleted);
//	str += strTemp ;
//	strTemp = "Ò³   ¹²    ";
//	str += strTemp ;
//	strTemp.Format("%d",tatal);
//	str += strTemp ;
//	strTemp = "Ò³ .";
//	str += strTemp ;
//	g_smDlg->m_workStatus.SetWindowText(str);

	CString temp;
	g_smDlg->m_Edit.GetWindowText(temp);
	CString strNew;
	switch (enumSubUnit)
	{
	case enumSubModule_PRINT:
		strNew = _T("Printing state:");
		switch (enumSubUnitStatus)
		{
		case enumSubModuleState_UnInited:
			strNew += _T(" UnInited");
			break;
		case enumSubModuleState_Ready:
			strNew += _T(" Ready");
			break;
		case enumSubModuleState_Work:
			strNew += _T(" Work");
			break;
		case enumSubModuleState_UnInitializing:
			strNew += _T(" UnInitializing");
			break;
		case enumSubModuleState_Error:
			strNew += _T(" Error");
			break;
		default:
			strNew += _T(" unknow state");
			break;
		}
		break;
	default:
		break;
	}

	if (_T("") != temp)
		temp += _T("\r\n");
	temp += strNew;
	g_smDlg->AppendString(strNew);
	
	return S_OK;
}


STDMETHODIMP CPASink::ReportPrintFilmComposerStatus(FilmComposerStatus enumFilmComposerStatus)
{
	CString strNew;
	strNew = _T("FilmComposer");
	switch (enumFilmComposerStatus)
	{
	case enumFilmComposerPRINTING:
		strNew += _T(" Printing");
		break;
	case enumFilmComposerIdle:
		strNew += _T(" Idle");
		break;
	default:
		strNew += _T(" Unkonw");
		break;
	}

	g_smDlg->AppendString(strNew);
	return S_OK;

}

STDMETHODIMP CPASink::ReportPrintFilmComposerStartUp()
{
	g_smDlg->AppendString(_T("FilmComposer startup!"));
	return S_OK;
}

STDMETHODIMP CPASink::ReportEnableFilmComposer(BOOL bEnable)
{
	
	CWnd* pWnd = CWnd::FindWindow(_T("PNMS_FilmComposer"), NULL);
	
	if(pWnd)
		
	{
		pWnd->EnableWindow(bEnable);
	}
	
	return S_OK;
}


// IPABurnEvent
STDMETHODIMP CPASink::ReportBurnWorkStatus(SubModule enumSubUnit, SubModuleState enumSubUnitStatus)
{  
	CString temp;
	g_smDlg->m_Edit.GetWindowText(temp);
	CString strNew;
	switch (enumSubUnit)
	{
	case enumSubModule_BURN:
		strNew = _T("Burn state:");
		switch (enumSubUnitStatus)
		{
		case enumSubModuleState_UnInited:
			strNew += _T(" UnInited");
			break;
		case enumSubModuleState_Ready:
			strNew += _T(" Ready");
			break;
		case enumSubModuleState_Work:
			strNew += _T(" Work");
			break;
		case enumSubModuleState_UnInitializing:
			strNew += _T(" UnInitializing");
			break;
		case enumSubModuleState_Error:
			strNew += _T(" Error");
			break;
		default:
			strNew += _T(" unknow state");
			break;
		}
		break;
	default:
		break;
	}

	if (_T("") != temp)
		temp += _T("\r\n");
	temp += strNew;
	g_smDlg->AppendString(strNew);
	
	return S_OK;
}


STDMETHODIMP CPASink::ReportBurnDeviceStatusChanged()
{
	g_smDlg->m_pBurnDlg->UpdateDlgInfo();
	return S_OK;

}

STDMETHODIMP CPASink::ReportBurnErrorCode(int iErrCode)
{
	BSTR	bsStrMsg/* = ::SysAllocString( L"" )*/;

	CString strErrMsg;
	g_smDlg->m_pIPABurn->GetBurnErrorMsg(iErrCode, &bsStrMsg);

	strErrMsg = _com_util::ConvertBSTRToString(bsStrMsg);
	SysFreeString(bsStrMsg);
	g_smDlg->AppendString(strErrMsg);
	return S_OK;
}

STDMETHODIMP CPASink::ReportBurnPhase(BSTR bsBurnPhase)
{
	CString strBurnPhase = _T("Burn Phase: ");
	strBurnPhase += _com_util::ConvertBSTRToString(bsBurnPhase);
	g_smDlg->AppendString(strBurnPhase);

	return S_OK;
}


//STDMETHODIMP CPASink::ReportBurnProgress(DWORD dwProgressPercent)
//{
//	g_smDlg->m_pBurnDlg->m_progressBurn.SetPos(dwProgressPercent);
//	return S_OK;
//}

STDMETHODIMP CPASink::ReportBurnLogLine(BSTR bsBurnLogLine)
{
	CString strLogLine = _com_util::ConvertBSTRToString(bsBurnLogLine);
	g_smDlg->AppendString(strLogLine);
	return S_OK;
}


STDMETHODIMP CPASink::ReportBurnPatientList(long lItemNum, BurnPatientInfoStruct* pBurnPatientList)
{
	g_smDlg->m_pBurnDlg->ShowPatientInfo(lItemNum, pBurnPatientList);
	return S_OK;
}

STDMETHODIMP CPASink::ReportBurnStudyList(long lItemNum, BurnStudyInfoStruct* pBurnStudyList)
{
	g_smDlg->m_pBurnDlg->ShowStudyInfo(lItemNum, pBurnStudyList);
	return S_OK;
}

STDMETHODIMP CPASink::ReportBurnSeriesList(long lItemNum, BurnSeriesInfoStruct* pBurnSeriesList)
{
	g_smDlg->m_pBurnDlg->ShowSeriesInfo(lItemNum, pBurnSeriesList);
	return S_OK;
}

STDMETHODIMP CPASink::ReportBurnImageList(long lItemNum, BurnImageInfoStruct* pBurnImageList)
{
	g_smDlg->m_pBurnDlg->ShowImageInfo(lItemNum, pBurnImageList);
	return S_OK;
}

STDMETHODIMP CPASink::ReportDeviceSpeedInfo(long lItemNum, BurnSpeedInfo* pSpeedInfo)
{
	g_smDlg->m_pBurnDlg->UpdateSpeedInfo(lItemNum, pSpeedInfo);
	return S_OK;
}

STDMETHODIMP CPASink::ReportMediaInfo(BurnMediaInfo* pMediaInfo)
{
	g_smDlg->m_pBurnDlg->UpdateMediaInfo(pMediaInfo);
	return S_OK;
}

STDMETHODIMP CPASink::ReportBurnMediaNotReady(BSTR bsInfo)
{
	g_smDlg->m_pBurnDlg->BurnMediaNotReady(bsInfo);
	return S_OK;
}

STDMETHODIMP CPASink::ReportBurnFileConflict(BSTR bsFirstFileName, BSTR bsSecondFileName)
{
	CString strFirstFile = _com_util::ConvertBSTRToString(bsFirstFileName);
	CString strSecondFile = _com_util::ConvertBSTRToString(bsSecondFileName);

	CString strMsg = _T("File Conflict:\r\n");
	strMsg += strFirstFile;
	strMsg += _T("\r\n");
	strMsg += strSecondFile;
	AfxMessageBox(strMsg);

//	g_smDlg->m_pIPABurn->SetFileConflictHandle(enumUpdateOldOneAlways);
	
	return S_OK;
}

// Transfer
STDMETHODIMP CPASink::ReportTransferWorkStatus(SubModule enumSubUnit, SubModuleState enumSubUnitStatus)
{
	CString temp;
	g_smDlg->m_Edit.GetWindowText(temp);
	CString strNew;
	switch (enumSubUnit)
	{
	case enumSubModule_TRANSFER:
		strNew = _T("Transfer state:");
		switch (enumSubUnitStatus)
		{
		case enumSubModuleState_UnInited:
			strNew += _T(" UnInited");
			break;
		case enumSubModuleState_Ready:
			strNew += _T(" Ready");
			break;
		case enumSubModuleState_Work:
			strNew += _T(" Work");
			break;
		case enumSubModuleState_UnInitializing:
			strNew += _T(" UnInitializing");
			break;
		case enumSubModuleState_Error:
			strNew += _T(" Error");
			break;
		default:
			strNew += _T(" unknow state");
			break;
		}
		break;
	default:
		break;
	}

	if (_T("") != temp)
		temp += _T("\r\n");
	temp += strNew;
	g_smDlg->AppendString(strNew);
	
	return S_OK;
}

//Transfer modify Patient or Study sendflag in DB  [9/3/2009 gaoxing]
STDMETHODIMP CPASink::ReportUITransferChangeDB(BSTR bstPatientUID,  BSTR bstStudyUID)
{
	return S_OK;
}



// DiscImport
STDMETHODIMP CPASink::ReportDiscImportWorkStatus(SubModule enumSubModule, SubModuleState enumSubModuleStatus)
{
	if (g_smDlg->m_pImportDlg->m_pDiscImportDlg)
	{
		g_smDlg->m_pImportDlg->m_pDiscImportDlg->DiscImportStateChanged(&enumSubModuleStatus);
	}
	
	CString temp;
	g_smDlg->m_Edit.GetWindowText(temp);
	CString strNew;
	switch (enumSubModule)
	{
	case enumSubModule_DISCIMPORT:
		strNew = _T("DiscImport state:");
		switch (enumSubModuleStatus)
		{
		case enumSubModuleState_UnInited:
			strNew += _T(" UnInited");
			break;
		case enumSubModuleState_Ready:
			strNew += _T(" Ready");
			break;
		case enumSubModuleState_Work:
			strNew += _T(" Work");
			break;
		case enumSubModuleState_UnInitializing:
			strNew += _T(" UnInitializing");
			break;
		case enumSubModuleState_Error:
			strNew += _T(" Error");
			break;
		default:
			strNew += _T(" unknow state");
			break;
		}
		break;
	default:
		break;
	}

	if (_T("") != temp)
		temp += _T("\r\n");
	temp += strNew;
	g_smDlg->AppendString(strNew);
	
	return S_OK;
}

STDMETHODIMP CPASink::ReportDiscImportDiscInfo(BOOL bReady)
{
	g_smDlg->m_pImportDlg->UpDateImportDiscInfo(bReady);
	return S_OK;
}

STDMETHODIMP CPASink::ReportDiscImportDiscInfoState(BSTR bsState)
{
	CString strState = _com_util::ConvertBSTRToString(bsState);
	g_smDlg->m_pImportDlg->UpDateImportDiscInfoState(strState);
	return S_OK;
}


STDMETHODIMP CPASink::ReportDiscImportSeriesStateChanged(DiscImport_SeriesStateStruct* pState)
{
	g_smDlg->m_ImportJObDetailDlg.UpdateImageState(pState);
	return S_OK;
}

STDMETHODIMP CPASink::ReportDiscImportSeriesProgressChanged(DiscImport_SeriesProgressStruct* pProgress)
{
	g_smDlg->m_ImportJObDetailDlg.UpdateImageProgress(pProgress);
	return S_OK;
}

STDMETHODIMP CPASink::ReportDiscImportSeriesDetailChanged(DiscImport_SeriesDetailStruct* pDetail)
{
	g_smDlg->m_ImportJObDetailDlg.UpdateImageDetail(pDetail);
	return S_OK;
}

STDMETHODIMP CPASink::ReportDiscImportOneImageImported()
{
	g_smDlg->AppendString(_T("One image imported"));
	return S_OK;
}

STDMETHODIMP CPASink::ReportDiscImportOneJobFinished()
{
	g_smDlg->AppendString(_T("One DiscImport Job finished"));
	return S_OK;
}

// Worklist and MPPS
STDMETHODIMP CPASink::ReportWlMppsWorkStatus(SubModule enumSubModule, SubModuleState enumSubModuleStatus)
{
	
	CString temp;
	g_smDlg->m_Edit.GetWindowText(temp);
	CString strNew;
	switch (enumSubModule)
	{
	case enumSubModule_WLMPPS:
		strNew = _T("WlMpps state:");
		switch (enumSubModuleStatus)
		{
		case enumSubModuleState_UnInited:
			strNew += _T(" UnInited");
			break;
		case enumSubModuleState_Ready:
			strNew += _T(" Ready");
			break;
		case enumSubModuleState_Work:
			strNew += _T(" Work");
			break;
		case enumSubModuleState_UnInitializing:
			strNew += _T(" UnInitializing");
			break;
		case enumSubModuleState_Error:
			strNew += _T(" Error");
			break;
		default:
			strNew += _T(" unknow state");
			break;
		}
		break;
	default:
		break;
	}

	if (_T("") != temp)
		temp += _T("\r\n");
	temp += strNew;
	g_smDlg->AppendString(strNew);
	
	return S_OK;
}

STDMETHODIMP CPASink::ReportWorkList(long lItemNum, WorkListStruct* pWorkList)
{
	g_smDlg->m_pWlMppsDlg->UpdateWorkList(lItemNum, pWorkList);
	return S_OK;
}

STDMETHODIMP CPASink::ReportSetMPPSStatusFinished(MppsSetResult* pResult)
{
	CString strText;
	strText.Format(_T("Set MPPS Status Finished: StudyUID:%s, status:%d, result:%d"),
		CBSTROpt::BSTRToCString(pResult->bsStudyUID),
		pResult->enumStatus,
		pResult->bResult);
	g_smDlg->AppendString(strText);
	return S_OK;
}

STDMETHODIMP CPASink::ReportMPPSStatusChanged(BSTR bsStudyUID, WorkListStatus enumStatus)
{
	CString strText;
	switch(enumStatus)
	{
	case enumWorkListStatus_InProgress:
		strText.Format(_T("Study MPPS Status Changed, StudyUID:%s, Status:InProgress"), CString(_com_util::ConvertBSTRToString(bsStudyUID)));
		break;
	case enumWorkListStatus_Discontinued:
		strText.Format(_T("Study MPPS Status Changed, StudyUID:%s, Status:Discontinued"), CString(_com_util::ConvertBSTRToString(bsStudyUID)));
		break;
	case enumWorkListStatus_Completed:
		strText.Format(_T("Study MPPS Status Changed, StudyUID:%s, Status:Completed"), CString(_com_util::ConvertBSTRToString(bsStudyUID)));
	    break;
	default:
		strText.Format(_T("Study MPPS Status Changed, StudyUID:%s, Status:%d"), CString(_com_util::ConvertBSTRToString(bsStudyUID)), enumStatus);
	    break;
	}

	g_smDlg->AppendString(strText);
	
	return S_OK;
}

STDMETHODIMP CPASink::ReportStartupResult(STARTUPRESULT enumResult)
{
	CString strNew;

	strNew = _T("PA StartUp");
	switch (enumResult)
	{
	case enumSTARTUPRESULT_SUCCESS:
		strNew += _T(" Success");
		break;
	case enumSTARTUPRESULT_FAILED:
		strNew += _T(" Failed");
		break;
	case enumSTARTUPRESULT_UNKNOWN:
		strNew += _T(" Unknow");
		break;
	default:
		strNew += _T(" Else");
		break;
	}

	g_smDlg->AppendString(strNew);

	if (enumSTARTUPRESULT_SUCCESS == enumResult ||
		enumSTARTUPRESULT_FAILED == enumResult)
	{
		g_smDlg->InitChildDlg();
	}
	return S_OK;
}

STDMETHODIMP CPASink::ReportWorkState(WORKSTATE enumState)
{
	CString strNew;

	strNew = _T("PA WorkState");
	switch (enumState)
	{
	case enumWORKSTATE_INITIALIZING:
		strNew += _T(" Initializing");
		break;
	case enumWORKSTATE_READY:
		strNew += _T(" Ready");
		break;
	case enumWORKSTATE_WORKING:
		strNew += _T(" Working");
		break;
	case enumWORKSTATE_UNINITIALIZING:
		strNew += _T(" Uninitializing");
		break;
	case enumWORKSTATE_UNINITIALIZED:
		strNew += _T(" Uinitialized");
		break;
	case enumWORKSTATE_ERROR:
		strNew += _T(" Error");
		break;

	default:
		strNew += _T(" Else");
		break;
	}

	g_smDlg->AppendString(strNew);
	
	return S_OK;
}

STDMETHODIMP CPASink::ReportError(INT iError)
{
	return S_OK;
}

//
STDMETHODIMP CPASink::UserGuidanceReporting(LONG iMessageID, USER_GUIDANCE_TYPE enumType, USER_GUIDANCE_PRIORITY enumPrior, BOOL bActive)
{
	CString szUserGuidance;
	CString szTemp;
	TCHAR tcDisplayUserGuidanceInfo[255] = {0};

	if (NULL != g_hResourceInstance)
		LoadString(g_hResourceInstance, iMessageID, tcDisplayUserGuidanceInfo, sizeof(tcDisplayUserGuidanceInfo));
	szUserGuidance = tcDisplayUserGuidanceInfo;

	szTemp.Format(_T(", USER_GUIDANCE_TYPE: %d, USER_GUIDANCE_PRIORITY: %d, bActive: %d"),
		enumType, enumPrior, bActive);
	
	szUserGuidance += szTemp;

	g_smDlg->AppendString(szUserGuidance);

	return S_OK;
}
