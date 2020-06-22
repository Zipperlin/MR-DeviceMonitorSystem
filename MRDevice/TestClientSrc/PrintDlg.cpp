// PrintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "PrintDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintDlg dialogf

// HHOOK   g_hhk = NULL;
extern CTestClientSrcDlg* g_smDlg; 
extern HINSTANCE g_hResourceInstance;

DWORD WINAPI CheckFCStatusThreadProc(LPVOID lpParam) 
{ 

	CPrintDlg* PrintDlg = (CPrintDlg*)lpParam;

	PrintDlg->RecvFilmComposerSocketMsg();

    return 0; 
}

// LRESULT CALLBACK kb_proc (int code, WPARAM w, LPARAM l)
// {
// 	if (w == WM_KEYDOWN)
// 	{ 
// //		AfxMessageBox("a");
// 
// // 		::PostMessage(g_smDlg->m_hWnd, WM_KEYDOWN, ((KBDLLHOOKSTRUCT*)l)->vkCode, NULL);
// //  		::SetForegroundWindow(g_smDlg->m_hWnd);   
// //  		::SetFocus(g_smDlg->m_hWnd);//可能不需要   
// //  		::ShowWindow(g_smDlg->m_hWnd, SW_NORMAL);
// 		g_smDlg->GetDlgItem(IDC_EDIT_OUTPUT)->SetFocus();
// 		::PostMessage(g_smDlg->m_hWnd, WM_KEYDOWN, ((KBDLLHOOKSTRUCT*)l)->vkCode, NULL);
// 		return 0;
// 	}
// 	
//     return CallNextHookEx (g_hhk, code, w, l);
// 
// }
// 

CPrintDlg::CPrintDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintDlg)
	m_ImageType = -1;
	m_iFileSelection = -1;
	m_iImageSelection = -1;

	m_hCheckFCStatusThread = NULL;

	m_socketFCMonitorServer = INVALID_SOCKET;
	m_socketFCMonitorClient = INVALID_SOCKET;

	//}}AFX_DATA_INIT
}


void CPrintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintDlg)
	DDX_Control(pDX, IDC_LIST_JOB_QUEUE, m_CListJobList);
	DDX_Control(pDX, IDC_COMBO_NETWORKNODE, m_cbSvrList);
	DDX_Radio(pDX, IDC_RADIO_XA, m_ImageType);
	DDX_CBIndex(pDX, IDC_COMBO_PRINT_FILES, m_iFileSelection);
	DDX_CBIndex(pDX, IDC_COMBO_IMAGESELECTION, m_iImageSelection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintDlg, CDialog)
	//{{AFX_MSG_MAP(CPrintDlg)
	ON_BN_CLICKED(IDC_BUTTON_SETIMAGETYPE, OnButtonSetimagetype)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_CANCELPRINT, OnButtonCancelprint)
	ON_CBN_SELCHANGE(IDC_COMBO_NETWORKNODE, OnSelchangeComboNetworknode)
	ON_BN_CLICKED(IDC_BUTTON_VIEW, OnButtonView)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_JOB, OnButtonDeleteJob)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SHOW_FC, OnButtonShowFc)
	ON_BN_CLICKED(IDC_BUTTON_HIDE_FC, OnButtonHideFc)
	ON_BN_CLICKED(IDC_BUTTON_FCLOADIMG, OnButtonFcloadimg)
	ON_BN_CLICKED(IDC_BUTTON_FCPATH, OnButtonFcpath)
	ON_BN_CLICKED(IDC_BUTTON_STARTFC, OnButtonStartfc)
	ON_BN_CLICKED(IDC_BUTTON_PSS_OCCUPY_STATE, OnButtonPssOccupyState)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_FC_PRINT, OnButtonCancelFcPrint)
	ON_BN_CLICKED(IDC_BUTTON_SOCKET_CNCT, OnButtonSocketCnct)
	ON_BN_CLICKED(IDC_BUTTON_SOCKET_SVR, OnButtonSocketSvr)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_SOCKET_SVR, OnButtonCloseSocketSvr)
	ON_BN_CLICKED(IDC_BUTTON_SOCKET_DISCNCT2, OnButtonSocketDiscnct2)
	ON_BN_CLICKED(IDC_BUTTON_HIDEPROGRESS, OnButtonHideprogress)
	ON_BN_CLICKED(IDC_BUTTON_SHOWPROGRESS, OnButtonShowprogress)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_IN_DIR, OnButtonLoadInDir)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_UID_ADD, OnButtonPrintUidAdd)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_UID_DEL, OnButtonPrintUidDel)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_UID_CLEAR, OnButtonPrintUidClear)
	ON_BN_CLICKED(IDC_BUTTON_GET_PRINT_SUBMODULE_STATE, OnButtonGetPrintSubmoduleState)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintDlg message handlers

void CPrintDlg::OnButtonSetimagetype() 
{
	// TODO: Add your control notification handler code here
//	UpdateData();
//	switch (m_ImageType)
//	{
//	case 0:
//		CTestClientSrcDlg::m_pIPAPrint->SetDICOMImageType(enumUnitPRINT, enumXA);	
//		break;
//	case 1:
//		CTestClientSrcDlg::m_pIPAPrint->SetDICOMImageType(enumUnitPRINT, enumSC);	
//		break;
//	default:
//		AfxMessageBox("Please select image type");
//		return;
//		break;
//	}	
}

void CPrintDlg::OnButtonPrint() 
{
	// TODO: Add your control notification handler code here

// 	UpdateData(TRUE);
// 	PrintJobSettings pjs;
// 	switch (m_iFileSelection)
// 	{
// 	case 0:
// 		pjs.enumFileSelection = enumFileSelection_CurrentStudy;
// 		break;
// 	case 1:
// 		pjs.enumFileSelection = enumFileSelection_CurrentRun;
// 		break;
// 	default:
// 		AfxMessageBox(_T("File Selection error!"));
// 		break;
// 	}
// 
// 	switch (m_iImageSelection)
// 	{
// 	case 0:
// 		pjs.enumImageSelection = enumImageSelection_All;
// 		break;
// 	case 1:
// 		pjs.enumImageSelection = enumImageSelection_Flagged;
// 		break;
// 	case 2:
// 		pjs.enumImageSelection = enumImageSelection_Unflagged;
// 		break;
// 	default:
// 		AfxMessageBox(_T("Image Selection error!"));
// 		break;
// 	}

	int iCount = ((CListBox*)GetDlgItem(IDC_LIST_PRINT_UID))->GetCount();
	if (iCount <= 0)
	{
		AfxMessageBox(_T("Plz input UID!"));
		return;
	}

	BSTR* pbsUIDs = new BSTR[iCount];
	for (int i = 0; i <iCount; i++)
	{
		CString strUID;
		((CListBox*)GetDlgItem(IDC_LIST_PRINT_UID))->GetText(i, strUID);
		pbsUIDs[i] = strUID.AllocSysString();
	}

	HRESULT hResult = CTestClientSrcDlg::m_pIPAPrint->Print(iCount, pbsUIDs);	
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPAPrint->Print(&iCount, pbsUIDs)"));
	}

	for (i = 0; i <iCount; i++)
	{
		CBSTROpt::FreeBSTR(pbsUIDs[i]);
	}
	delete []pbsUIDs;

}

void CPrintDlg::OnButtonCancelprint() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_CListJobList.GetFirstSelectedItemPosition();
	CString strJobID;
	if (pos == NULL)
	{
		AfxMessageBox(_T("No Job is selected!"));
		return;
	}
	else
	{			
		int nItem = m_CListJobList.GetNextSelectedItem(pos);
		strJobID = m_CListJobList.GetItemText(nItem, 0);
		BSTR bsJobID = strJobID.AllocSysString();
// 		CTestClientSrcDlg::m_pIPAPrint->CancelPrintJob(bsJobID);
	}

}

BOOL CPrintDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ImageType = 0;
	UpdateData(FALSE);

	GetDlgItem(IDC_EDIT_FCPATH)->SetWindowText(_T("D:\\commonPrj\\Printing & Archiving\\bin\\FilmComposer\\filmcomposer.exe"));

	((CComboBox*)GetDlgItem(IDC_COMBO_PRINT_FILES))->SetCurSel(1);
	((CComboBox*)GetDlgItem(IDC_COMBO_IMAGESELECTION))->SetCurSel(1);
	
	m_CListJobList.SetExtendedStyle(m_CListJobList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_CListJobList.InsertColumn(0, _T("JobID"), LVCFMT_CENTER, 120);
	m_CListJobList.InsertColumn(1, _T("State"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(2, _T("Phase"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(3, _T("Progress"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(4, _T("Detail"), LVCFMT_LEFT, 300);

	GetDlgItem(IDC_EDIT_CMD_TO_FC)->SetWindowText(_T("2STOP"));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrintDlg::Init()
{
//	m_cbSvrList.ResetContent();
//	
//	NetworkNode* pNetworkNodeList = NULL;
//	long NodeCount = 0;
//	CTestClientSrcDlg::m_pIPAPrint->GetPrintNetworkNodes(&pNetworkNodeList, &NodeCount);
//	NetworkNode* pNode = pNetworkNodeList;
//
//	CString strCalledAE;
//	for (int i = 0; i < NodeCount; i++)
//	{
//		strCalledAE = _com_util::ConvertBSTRToString(pNode->bsCalledAE);
//		m_vtrNetwork.push_back(strCalledAE);
//		if (pNode->bDefault)
//			m_iCurNode = i;
//
//		m_cbSvrList.InsertString(i, m_vtrNetwork[i]);
//
//		pNode++;
//	}
//
//	m_cbSvrList.SetCurSel(m_iCurNode);

}

void CPrintDlg::OnSelchangeComboNetworknode() 
{
	// TODO: Add your control notification handler code here
	CString strServerAE;
	int icbboxSelIndex = m_cbSvrList.GetCurSel();
	if (-1 == icbboxSelIndex)
	{
		AfxMessageBox(_T("please select a destination"));
		return;
	}
	else
		m_cbSvrList.GetLBText(icbboxSelIndex, strServerAE);

	for (int i = 0; i < m_vtrNetwork.size(); i++)
	{
		if (!m_vtrNetwork[i].Compare((LPCTSTR)strServerAE))
		{
			m_CurSvr = m_vtrNetwork[i];
//			m_SvrAE.SetWindowText(m_CurSvr.ServerAE);
//			m_HostAE.SetWindowText(m_CurSvr.HostAE);
//			m_SvrIP.SetWindowText(m_CurSvr.ServerIP);
//			m_SvrPort.SetWindowText(m_CurSvr.ServerPort);
			break;
		}
	}
	
}

void CPrintDlg::OnButtonView() 
{
	// TODO: Add your control notification handler code here
	DWORD dwImageCount = 0;
//	HRESULT hResult = CTestClientSrcDlg::m_pIPAPrint->GetPrintJobViewImageCount(enumFileSelection_CurrentRun, enumImageSelection_Flagged, &dwImageCount);
// 	if (SUCCEEDED(hResult))
// 	{
// 		if (S_OK == hResult)
// 		{
// 			CString strImageCount;
// 			strImageCount.Format(_T("%d"), dwImageCount);
// 			GetDlgItem(IDC_STATIC_IMAGE_NUM)->SetWindowText(strImageCount);
// 		}
// 		else
// 			GetDlgItem(IDC_STATIC_IMAGE_NUM)->SetWindowText(_T(""));
// 	}
// 	else
// 		AfxMessageBox("failed: CTestClientSrcDlg::m_pIPAPrint->GetPrintJobViewImageCount()");
}

void CPrintDlg::UpdateJobList()
{
// 	m_CListJobList.DeleteAllItems();
// 	JobInfo* pJobList = NULL;
// 	JobInfo* pJobInfo = NULL;
// 	long lJobCount = 0;
// 	HRESULT hResult =  CTestClientSrcDlg::m_pIPAPrint->GetPrintJobList(&pJobList, &lJobCount);
// 	if (SUCCEEDED(hResult))
// 	{
// 		if (0 == lJobCount)
// 		{
// 		}
// 		else
// 		{
// 			pJobInfo = pJobList;
// 			for (int i = 0; i < lJobCount; i++)
// 			{
// 				CString temp;
// 				LV_ITEM lvitemAdd;
// 				lvitemAdd.mask = LVIF_TEXT;
// 				lvitemAdd.iItem = 0;
// 				lvitemAdd.iSubItem = 0;
// 				lvitemAdd.pszText = NULL;
// 
// 				m_CListJobList.InsertItem(&lvitemAdd);
// 				
// 				// For JobID
// 				temp = _com_util::ConvertBSTRToString(pJobInfo->bsJobID);
// 				m_CListJobList.SetItemText(0, 0, (LPCTSTR)temp);
// 
// 				// For Job state
// 				switch (pJobInfo->enumJobState)
// 				{
// 				case enumJobState_Submitted:
// 					m_CListJobList.SetItemText(0, 1, _T("Submitted"));
// 					break;
// 				case enumJobState_Executing:
// 					m_CListJobList.SetItemText(0, 1, _T("Executing"));
// 					break;
// 				case enumJobState_Completed:
// 					m_CListJobList.SetItemText(0, 1, _T("Completed"));
// 					break;
// 				case enumJobState_Failed:
// 					m_CListJobList.SetItemText(0, 1, _T("Failed"));
// 					break;
// 				case enumJobState_Cancelled:
// 					m_CListJobList.SetItemText(0, 1, _T("Cancelled"));
// 					break;
// 				default:
// 					m_CListJobList.SetItemText(0, 1, _T("unknow"));
// 					break;
// 
// 				}
// 
// 				// For Phase
// 				CString strJobPhase = _com_util::ConvertBSTRToString(pJobInfo->bsPhase);
// 				m_CListJobList.SetItemText(0, 2, strJobPhase);
// 
// 				// For Progress
// 				CString strJobProgress;
// 				
// 				switch (pJobInfo->enumJobProgressUsing)
// 				{
// 				case enumJobProgressUsing_None:
// 					strJobProgress = _T("");
// 					break;
// 				case enumJobProgressUsing_CompletedTotal:
// 					strJobProgress.Format(_T("%d/%d"), pJobInfo->uiCompleted, pJobInfo->uiTotal);
// 					break;
// 				case enumJobProgressUsing_Percentage:
// 					strJobProgress.Format(_T("%d%%"), pJobInfo->dwPercentage);
// 					break;
// 				default:
// 					break;
// 				}
// 				m_CListJobList.SetItemText(0, 3, strJobProgress);
// 
// 				// Job Detail
// 				CString strJobDetail;
// 				TCHAR tcDisplayUserGuidanceInfo[255] = {0};
// 				
// 				switch (pJobInfo->enumJobDetailUsing)
// 				{
// 				case enumJobDetailUsing_None:
// 					strJobDetail = _T("");
// 					break;
// 				case enumJobDetailUsing_UGID:
// 
// 					if (NULL != g_hResourceInstance)
// 						LoadString(g_hResourceInstance, pJobInfo->iUGID, tcDisplayUserGuidanceInfo, sizeof(tcDisplayUserGuidanceInfo));
// 
// 					strJobDetail = tcDisplayUserGuidanceInfo;
// 					break;
// 				case enumJobDetailUsing_DetailInfo:
// 					strJobDetail = _com_util::ConvertBSTRToString(pJobInfo->bsDetailInfo);
// 					break;
// 				default:
// 					break;
// 				}
// 
// 				m_CListJobList.SetItemText(0, 4, strJobDetail);
// 
// 				// Next Job
// 				pJobInfo++;
// 			}
// 		}
// 		
// 		if (pJobList)
// 			CoTaskMemFree(pJobList);
// 	}
// 
}

void CPrintDlg::SetJobState(LPCTSTR szJobID, JobState enumJobState)
{
	for (int i = 0; i < m_CListJobList.GetItemCount(); i++)
	{
		CString strJobID = m_CListJobList.GetItemText(i, 0);
		if (!strJobID.Compare(szJobID))
		{
			switch (enumJobState)
			{
			case enumJobState_Submitted:
				m_CListJobList.SetItemText(i, 1, _T("Submitted"));
				break;
			case enumJobState_Executing:
				m_CListJobList.SetItemText(i, 1, _T("Executing"));
				break;
			case enumJobState_Completed:
				m_CListJobList.SetItemText(i, 1, _T("Completed"));
				break;
			case enumJobState_Failed:
				m_CListJobList.SetItemText(i, 1, _T("Failed"));
				break;
			case enumJobState_Cancelled:
				m_CListJobList.SetItemText(i, 1, _T("Cancelled"));
				break;
			default:
				m_CListJobList.SetItemText(i, 1, _T("unknow"));
				break;

			}
		}
	}
}


void CPrintDlg::SetJobPhase(LPCTSTR szJobID, LPCTSTR szJobPhase)
{
	for (int i = 0; i < m_CListJobList.GetItemCount(); i++)
	{
		CString strJobID = m_CListJobList.GetItemText(i, 0);
		if (!strJobID.Compare(szJobID))
		{
			m_CListJobList.SetItemText(i, 2, szJobPhase);
			return;
		}
	}
	
}

void CPrintDlg::SetJobProgress(JobProgressStruct* pJobProgressStruct)
{
	CString strDstJobID = _com_util::ConvertBSTRToString(pJobProgressStruct->bsJobUID);
	CString strJobProgress;
	
	switch (pJobProgressStruct->enumJobProgressUsing)
	{
	case enumJobProgressUsing_None:
		strJobProgress = _T("");
		break;
	case enumJobProgressUsing_CompletedTotal:
		strJobProgress.Format(_T("%d/%d"), pJobProgressStruct->uiCompleted, pJobProgressStruct->uiTotal);
		break;
	case enumJobProgressUsing_Percentage:
		strJobProgress.Format(_T("%d%%"), pJobProgressStruct->dwPercentage);
		break;
	default:
		break;
	}

	for (int i = 0; i < m_CListJobList.GetItemCount(); i++)
	{
		CString strJobID = m_CListJobList.GetItemText(i, 0);
		if (!strJobID.Compare(strDstJobID))
		{
			m_CListJobList.SetItemText(i, 3, strJobProgress);
			return;
		}
	}
}

void CPrintDlg::SetJobDetail(JobDetailStruct* pJobDetailStruct)
{
// 	CString strDstJobID = _com_util::ConvertBSTRToString(pJobDetailStruct->bsJobUID);
// 	CString strJobDetail;
// 	TCHAR tcDisplayUserGuidanceInfo[255] = {0};
// 	
// 	switch (pJobDetailStruct->enumJobDetailUsing)
// 	{
// 	case enumJobDetailUsing_None:
// 		strJobDetail = _T("");
// 		break;
// 	case enumJobDetailUsing_UGID:
// 
// 		if (NULL != g_hResourceInstance)
// 			LoadString(g_hResourceInstance, pJobDetailStruct->iUGID, tcDisplayUserGuidanceInfo, sizeof(tcDisplayUserGuidanceInfo));
// 
// 		strJobDetail = tcDisplayUserGuidanceInfo;
// 		break;
// 	case enumJobDetailUsing_DetailInfo:
// 		strJobDetail = _com_util::ConvertBSTRToString(pJobDetailStruct->bsDetailInfo);
// 		break;
// 	default:
// 		break;
// 	}
// 
// 	for (int i = 0; i < m_CListJobList.GetItemCount(); i++)
// 	{
// 		CString strJobID = m_CListJobList.GetItemText(i, 0);
// 		if (!strJobID.Compare(strDstJobID))
// 		{
// 			m_CListJobList.SetItemText(i, 4, strJobDetail);
// 			return;
// 		}
// 	}
}

void CPrintDlg::SetExecutingJobPhaseProgress(LPCTSTR szPhase, LPCTSTR szProgress)
{
	for (int i = 0; i < m_CListJobList.GetItemCount(); i++)
	{
		CString strJobID = m_CListJobList.GetItemText(i, 1);
		if (!strJobID.Compare(_T("Executing")))
		{
			if (szPhase)
				m_CListJobList.SetItemText(i, 2, szPhase);

			if (szProgress)
				m_CListJobList.SetItemText(i, 3, szProgress);
			
			break;
		}
	}
}


void CPrintDlg::OnButtonDeleteJob() 
{
	// TODO: Add your control notification handler code here
	// margen is good
	POSITION pos = m_CListJobList.GetFirstSelectedItemPosition();
	CString strJobID;
	if (pos == NULL)
	{
		AfxMessageBox(_T("No Job is selected!"));
		return;
	}
	else
	{			
		int nItem = m_CListJobList.GetNextSelectedItem(pos);
		strJobID = m_CListJobList.GetItemText(nItem, 0);
		BSTR bsJobID = strJobID.AllocSysString();

// 		CTestClientSrcDlg::m_pIPAPrint->DeletePrintJob(bsJobID);

//		UpdateJobList();
	}
	
}

void CPrintDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CPrintDlg::OnButtonShowFc() 
{
	// TODO: Add your control notification handler code here
	// Show FC window
	HWND hFCWnd = NULL;
	hFCWnd = ::FindWindow(_T("PNMS_FilmComposer"), NULL);

	if (hFCWnd != NULL)
	{
		if (::ShowWindow(hFCWnd, SW_SHOW))
		{
		}
	}
	else
	{
		AfxMessageBox(_T("Didn't find FC!"));
	}
	
	
}

void CPrintDlg::OnButtonHideFc() 
{
	// TODO: Add your control notification handler code here
	HWND hFCWnd = NULL;
	hFCWnd = ::FindWindow(_T("PNMS_FilmComposer"), NULL);

	if (hFCWnd != NULL)
	{
		if (::ShowWindow(hFCWnd, SW_HIDE))
		{
		}
	}
	else
	{
		AfxMessageBox(_T("Didn't find FC!"));
	}
	
}

void CPrintDlg::OnButtonFcloadimg() 
{
	// TODO: Add your control notification handler code here


	CString strFCPath;
	GetDlgItem(IDC_EDIT_FCPATH)->GetWindowText(strFCPath);
	if (strFCPath.IsEmpty())
		AfxMessageBox(_T("Plz specifies FC Path"));
	
	static TCHAR BASED_CODE szFilter[] = _T("All Files (*.*)|*.*|DICOM Files (*.dic)|*.dic||");


	CFileDialog dlgOpen(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, szFilter, this);

	// do nothing if IDCANCEL is returned

	CString strPathName;
	
	if (dlgOpen.DoModal() == IDOK)
	{
		// retrieve and display the selected file name
		strPathName = dlgOpen.GetPathName();

		strFCPath += _T(" -f ");
		strFCPath += strPathName;
		char strDstPathByte[MAX_PATH * 2] = {0};
		WideCharToMultiByte (CP_ACP, WC_COMPOSITECHECK, (LPCTSTR)strFCPath, -1, strDstPathByte, sizeof(strDstPathByte), NULL, NULL ); 
		::WinExec(strDstPathByte, SW_SHOW);
	}
	
}

void CPrintDlg::OnButtonFcpath() 
{
	// TODO: Add your control notification handler code here
	static TCHAR BASED_CODE szFilter[] = _T("(*.exe)|*.exe||");


	CFileDialog dlgOpen(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, szFilter, this);

	// do nothing if IDCANCEL is returned

	CString strPathName;
	
	if (dlgOpen.DoModal() == IDOK)
	{
		// retrieve and display the selected file name
		strPathName = dlgOpen.GetPathName();
		GetDlgItem(IDC_EDIT_FCPATH)->SetWindowText(strPathName);
	}
}


void CPrintDlg::OnButtonStartfc() 
{
	// TODO: Add your control notification handler code here


//	m_hook.SetHook();
	
	CString strFCFullPath;
	STARTUPINFO suInfo;
	memset (&suInfo, 0, sizeof(suInfo));
	suInfo.cb = sizeof(suInfo);
	suInfo.dwFlags = STARTF_USESHOWWINDOW ;
	suInfo.wShowWindow = SW_HIDE ;
	PROCESS_INFORMATION m_PrintProcessInfo;

	GetDlgItem(IDC_EDIT_FCPATH)->GetWindowText(strFCFullPath);

	BOOL bRet = ::CreateProcess(strFCFullPath,
		NULL,
		NULL,
		NULL,
		FALSE,
		HIGH_PRIORITY_CLASS,
		NULL,
		NULL,
		&suInfo,
		&m_PrintProcessInfo);

	if(!bRet)
	{
 
	}
	else
	{
	}

	//UnhookWindowsHookEx(g_hhk);  
}



// void CPrintDlg::OnButtonStarthook() 
// {
// 	// TODO: Add your control notification handler code here
// 	g_hhk = SetWindowsHookEx(WH_KEYBOARD_LL,     
//           kb_proc,   GetModuleHandle (NULL), 0); 
// 
// 	
// }

void CPrintDlg::OnButtonPssOccupyState() 
{
	// TODO: Add your control notification handler code here
	BOOL bOccupied = FALSE;
	CString strUID = _T("0720070125112419640");
	BSTR bsUID = strUID.AllocSysString();

	HRESULT hResult = CTestClientSrcDlg::m_pIPAGeneral->GetPatientStudySeriesImageOccupyState(enumPatientAdminUIDType_Patient, 1, &bsUID, &bOccupied);
	if (S_OK == hResult)
	{
		if (bOccupied)
			AfxMessageBox(_T("Occupied"));
		else
			AfxMessageBox(_T("Not Occupied"));
	}
	else
	{
		AfxMessageBox(_T("S_OK != m_pIPAGeneral->GetPatientStudySeriesOccupyState"));
	}
}

void CPrintDlg::OnButtonCancelFcPrint() 
{
	// TODO: Add your control notification handler code here
	WORD wVersionRequested;
	int err;
	WSADATA  wsaData;
	wVersionRequested = MAKEWORD(2,0);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		AfxMessageBox(_T("error WSAStartup"));
		return;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0)
	{
		WSACleanup();
		AfxMessageBox(_T("error LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0"));
		return;
	}
	 //int addrlen;
	int iRet;
	struct sockaddr_in servaddr;
	if ((m_socketFCServer = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		iRet = WSAGetLastError();
		AfxMessageBox(_T("error m_socketFCServer = socket(AF_INET, SOCK_STREAM, 0"));
		return;
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(8888);
 
	if(SOCKET_ERROR == connect(m_socketFCServer, (struct sockaddr *)&servaddr, sizeof(servaddr)))
	{
		closesocket(m_socketFCServer);
		iRet = WSAGetLastError();
		AfxMessageBox(_T("error connect(...)"));
		return;
	}

//	char buf[16] = {0};
//	GetDlgItem(IDC_EDIT_CMD_TO_FC)->GetWindowText(buf, 16);

	if (SOCKET_ERROR == send(m_socketFCServer, "2STOP", strlen("2STOP"), 0))
	{
		closesocket(m_socketFCServer);
		int Errcode = WSAGetLastError();
		CString strMsg;
		strMsg.Format(_T("error send(...), Error code: %d"), Errcode);
		AfxMessageBox(strMsg);
	}
	else
	{
		closesocket(m_socketFCServer);
		AfxMessageBox(_T("Succeed send(...)"));
	}
}

void CPrintDlg::OnButtonSocketCnct() 
{
	// TODO: Add your control notification handler code here
	WORD wVersionRequested;
	int err;
	WSADATA  wsaData;
	wVersionRequested = MAKEWORD(2,0);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		AfxMessageBox(_T("error WSAStartup"));
		return;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0)
	{
		WSACleanup();
		AfxMessageBox(_T("error LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0"));
		return;
	}
	 //int addrlen;
	int iRet;
	struct sockaddr_in servaddr;
	if ((m_socketFCServer = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		iRet = WSAGetLastError();
		AfxMessageBox(_T("error m_socketFCServer = socket(AF_INET, SOCK_STREAM, 0)"));
		return;
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(8888);
 
	if(SOCKET_ERROR == connect(m_socketFCServer, (struct sockaddr *)&servaddr, sizeof(servaddr)))
	{
		iRet = WSAGetLastError();
		AfxMessageBox(_T("error connect(...)"));
		return;
	}
	else
	{
		AfxMessageBox(_T("Succeed connected"));
	}
	
}

void CPrintDlg::OnButtonSocketDiscnct2() 
{
	// TODO: Add your control notification handler code here
	closesocket(m_socketFCServer);
	m_socketFCServer = INVALID_SOCKET;
}


void CPrintDlg::OnButtonSocketSvr() 
{
	// TODO: Add your control notification handler code here
	m_hCheckFCStatusThread = CreateThread(NULL, 0, CheckFCStatusThreadProc, this, 0, NULL);

}

BOOL CPrintDlg::RecvFilmComposerSocketMsg()
{
	WORD wVersionRequested;
	int err;
	WSADATA  wsaData;
	wVersionRequested = MAKEWORD(2,0);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		AfxMessageBox(_T("Error!"));
		return FALSE;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0)
	{
		WSACleanup();
		AfxMessageBox(_T("Error!"));
		return FALSE;
	}

	char buf[128];
	struct sockaddr_in servaddr, cliaddr;
	int addrlen;
	if ((m_socketFCMonitorServer = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		AfxMessageBox(_T("Error!"));
		 return FALSE;
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 
	
	int iRet = bind(m_socketFCMonitorServer, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (iRet)
	{
		iRet = WSAGetLastError();

		AfxMessageBox(_T("Error!"));
		return FALSE;
	}

	g_smDlg->AppendString(_T("Server Listening..."));

	listen(m_socketFCMonitorServer, 5);
	addrlen = sizeof(cliaddr);
	while(TRUE)
	{
			
		if((m_socketFCMonitorClient = accept(m_socketFCMonitorServer, (struct sockaddr *)&cliaddr, &addrlen)) <0 )
		{
			iRet = WSAGetLastError();
			AfxMessageBox(_T("Error!"));
			return FALSE;
		}

		memset(buf, 0, sizeof(buf));		
		recv(m_socketFCMonitorClient, buf, sizeof(buf), 0);
		
		CString strAccepted = buf;
		g_smDlg->AppendString(strAccepted);
		
		closesocket(m_socketFCMonitorClient);
		m_socketFCMonitorClient = INVALID_SOCKET;
		
	}


	return TRUE;
}

void CPrintDlg::OnButtonCloseSocketSvr() 
{
	// TODO: Add your control notification handler code here
	if (m_hCheckFCStatusThread)
	{
		TerminateThread(m_hCheckFCStatusThread, 0);
		m_hCheckFCStatusThread = NULL;
	}

	closesocket(m_socketFCMonitorServer);
	m_socketFCMonitorServer = INVALID_SOCKET;
	closesocket(m_socketFCMonitorClient);
	m_socketFCMonitorClient = INVALID_SOCKET;

	g_smDlg->AppendString(_T("Server Listen stop!"));

}


void CPrintDlg::OnButtonHideprogress() 
{
	// TODO: Add your control notification handler code here
//	CTestClientSrcDlg::m_pIPAPrint->ShowFCProgressBar(FALSE);

	WORD wVersionRequested;
	int err;
	WSADATA  wsaData;
	wVersionRequested = MAKEWORD(2,0);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		AfxMessageBox(_T("error WSAStartup"));
		WSACleanup();
		return;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0)
	{
		AfxMessageBox(_T("error LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0"));
		WSACleanup();
		return;
	}
	 //int addrlen;
	int iRet;
	struct sockaddr_in servaddr;
	if ((m_socketFCServer = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		iRet = WSAGetLastError();
		AfxMessageBox(_T("error m_socketFCServer = socket(AF_INET, SOCK_STREAM, 0)"));
		WSACleanup();
		return;
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(8888);
 
	if(SOCKET_ERROR == connect(m_socketFCServer, (struct sockaddr *)&servaddr, sizeof(servaddr)))
	{
		closesocket(m_socketFCServer);
		iRet = WSAGetLastError();
		AfxMessageBox(_T("error connect(...)"));
		WSACleanup();
		return;
	}

//	char buf[16] = {0};
//	GetDlgItem(IDC_EDIT_CMD_TO_FC)->GetWindowText(buf, 16);

	if (SOCKET_ERROR == send(m_socketFCServer, "2HIDEPROGRESS", strlen("2HIDEPROGRESS"), 0))
	{
		closesocket(m_socketFCServer);
		int Errcode = WSAGetLastError();
		CString strMsg;
		strMsg.Format(_T("error send(...), Error code: %d"), Errcode);
		AfxMessageBox(strMsg);
	}
	else
	{
		closesocket(m_socketFCServer);
//		AfxMessageBox("Succeed send(...)");
	}
	WSACleanup();

}

void CPrintDlg::OnButtonShowprogress() 
{
	// TODO: Add your control notification handler code here
// 	CTestClientSrcDlg::m_pIPAPrint->ShowFCProgressBar(TRUE);

	WORD wVersionRequested;
	int err;
	WSADATA  wsaData;
	wVersionRequested = MAKEWORD(2,0);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		AfxMessageBox(_T("error WSAStartup"));
		return;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0)
	{
		WSACleanup();
		AfxMessageBox(_T("error LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0"));
		return;
	}
	 //int addrlen;
	int iRet;
	struct sockaddr_in servaddr;
	if ((m_socketFCServer = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		iRet = WSAGetLastError();
		AfxMessageBox(_T("error m_socketFCServer = socket(AF_INET, SOCK_STREAM, 0)"));
		WSACleanup();
		return;
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(8888);
 
	if(SOCKET_ERROR == connect(m_socketFCServer, (struct sockaddr *)&servaddr, sizeof(servaddr)))
	{
		closesocket(m_socketFCServer);
		iRet = WSAGetLastError();
		AfxMessageBox(_T("error connect(...)"));
		WSACleanup();
		return;
	}

//	char buf[16] = {0};
//	GetDlgItem(IDC_EDIT_CMD_TO_FC)->GetWindowText(buf, 16);

	if (SOCKET_ERROR == send(m_socketFCServer, "2SHOWPROGRESS", strlen("2SHOWPROGRESS"), 0))
	{
		closesocket(m_socketFCServer);
		int Errcode = WSAGetLastError();
		CString strMsg;
		strMsg.Format(_T("error send(...), Error code: %d"), Errcode);
		AfxMessageBox(strMsg);
	}
	else
	{
		closesocket(m_socketFCServer);
//		AfxMessageBox("Succeed send(...)");
	}
	WSACleanup();

}

void CPrintDlg::OnButtonLoadInDir() 
{
	// TODO: Add your control notification handler code here

	
	CString strExtentName;
	GetDlgItem(IDC_EDIT_DCM_EXTENT)->GetWindowText(strExtentName);
	CString strFCFullPath;
	GetDlgItem(IDC_EDIT_FCPATH)->GetWindowText(strFCFullPath);

	TCHAR   buffer[MAX_PATH];   
	BROWSEINFO   m_pbi;   

	::ZeroMemory(&m_pbi,   sizeof(BROWSEINFO));   
	m_pbi.hwndOwner   =   GetSafeHwnd();   
	m_pbi.pszDisplayName   =   buffer;   
	m_pbi.lpszTitle   =   _T("");   
	m_pbi.ulFlags   =   BIF_RETURNONLYFSDIRS;   

	ITEMIDLIST   *idl   =   SHBrowseForFolder(&m_pbi);
	
	if   (idl)   
	{   
		SHGetPathFromIDList   (idl,   buffer);
		CString strDir = buffer;

		Sleep(3000);
		
		WIN32_FIND_DATA fd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		CString strTrace;

		BOOL bRet = TRUE;

		hFind = FindFirstFile(strDir + _T("\\*"), &fd);
		if (INVALID_HANDLE_VALUE == hFind)
		{
			return;
		}

		do
		{
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				continue;
			}
			else
			{
				wchar_t* p = wcsrchr(fd.cFileName, _T('.'));
				if (strExtentName.IsEmpty() && NULL == p)
				{
					char strDstPathByte[MAX_PATH * 2] = {0};
					CString strCMD = strFCFullPath+_T(" -f ")+strDir+_T("\\")+fd.cFileName;
					WideCharToMultiByte (CP_ACP, WC_COMPOSITECHECK, (LPCTSTR)strCMD, -1, strDstPathByte, sizeof(strDstPathByte), NULL, NULL ); 
					::WinExec(strDstPathByte, SW_SHOWNOACTIVATE);
				}
				else
				{
					;
				}
			}
		}while (FindNextFile(hFind, &fd));

		FindClose(hFind);

	}   	
	
}

void CPrintDlg::OnButtonPrintUidAdd() 
{
	// TODO: Add your control notification handler code here
	CString strUID;
	GetDlgItem(IDC_EDIT_PRINT_UID)->GetWindowText(strUID);

	if (strUID.IsEmpty())
		return;

	((CListBox*)GetDlgItem(IDC_LIST_PRINT_UID))->AddString(strUID);
}

void CPrintDlg::OnButtonPrintUidDel() 
{
	// TODO: Add your control notification handler code here
	INT iIndex = ((CListBox*)GetDlgItem(IDC_LIST_PRINT_UID))->GetCurSel();

	if (LB_ERR == iIndex)
		return;

	CString strUID;
		
	((CListBox*)GetDlgItem(IDC_LIST_PRINT_UID))->DeleteString(iIndex);
}

void CPrintDlg::OnButtonPrintUidClear() 
{
	// TODO: Add your control notification handler code here
	((CListBox*)GetDlgItem(IDC_LIST_PRINT_UID))->ResetContent();
}

void CPrintDlg::OnButtonGetPrintSubmoduleState() 
{
	// TODO: Add your control notification handler code here
	SubModuleState enumState;
	HRESULT hResult = CTestClientSrcDlg::m_pIPAPrint->GetPrintSubModuleState(&enumState);	
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPAPrint->GetPrintSubModuleState(&enumState)"));
	}
	else
	{
		CString strState;
		switch (enumState)
		{
		case enumSubModuleState_UnInited:
			strState = _T("UnInited");
			break;
		case enumSubModuleState_Ready:
			strState = _T("Ready");
			break;
		case enumSubModuleState_Work:
			strState = _T("Work");
		    break;
		case enumSubModuleState_UnInitializing:
			strState = _T("UnInitializing");
		    break;
		case enumSubModuleState_Error:
			strState = _T("Error");
		    break;
		default:
			strState = _T("Unknow");
		    break;
		}

		AfxMessageBox(strState);
	}
}
