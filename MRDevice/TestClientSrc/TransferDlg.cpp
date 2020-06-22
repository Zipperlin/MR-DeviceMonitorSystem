// TransferDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "TransferDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE g_hResourceInstance;

/////////////////////////////////////////////////////////////////////////////
// CTransferDlg dialog


CTransferDlg::CTransferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransferDlg::IDD, pParent)
{
	m_CurSvrNum = -1;
	//{{AFX_DATA_INIT(CTransferDlg)
	m_iFileSelection = -1;
	m_iImageSelection = -1;
	m_iDownscale = -1;
	//}}AFX_DATA_INIT
}


void CTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransferDlg)
	DDX_Control(pDX, IDC_LIST_MANUAL_SEND_SERVER, m_listManualSendSvrs);
	DDX_Control(pDX, IDC_LIST_JOB_QUEUE, m_CListJobList);
	DDX_Control(pDX, IDC_EDIT_SERVERPORT, m_SvrPort);
	DDX_Control(pDX, IDC_EDIT_SERVERIP, m_SvrIP);
	DDX_Control(pDX, IDC_EDIT_SERVERAE, m_SvrAE);
	DDX_Control(pDX, IDC_EDIT_HOSTAE, m_HostAE);
	DDX_Control(pDX, IDC_COMBO_SVRLIST, m_cbServerList);
	DDX_CBIndex(pDX, IDC_COMBO_FILESELECTION, m_iFileSelection);
	DDX_CBIndex(pDX, IDC_COMBO_IMAGESELECTION, m_iImageSelection);
	DDX_CBIndex(pDX, IDC_COMBO_DOWNSCALE, m_iDownscale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransferDlg, CDialog)
	//{{AFX_MSG_MAP(CTransferDlg)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFER, OnButtonTransfer)
	ON_CBN_SELCHANGE(IDC_COMBO_SVRLIST, OnSelchangeComboSvrlist)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_JOB, OnButtonCancelJob)
	ON_BN_CLICKED(IDC_BUTTON_DELET_JOB, OnButtonDeletJob)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFERBYUID, OnButtonTransferbyuid)
	ON_CBN_SELCHANGE(IDC_COMBO_UID_SELECTION, OnSelchangeComboUidSelection)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFER_TRANSFER_VALID, OnButtonTransferTransferValid)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFER_AUTOSEND, OnButtonTransferAutosend)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFER_REFRESH_NETWORKNODES, OnButtonTransferRefreshNetworknodes)
	ON_BN_CLICKED(IDC_BUTTON_SEND_UID_ADD, OnButtonSendUidAdd)
	ON_BN_CLICKED(IDC_BUTTON_SEND_UID_DEL, OnButtonSendUidDel)
	ON_BN_CLICKED(IDC_BUTTON_SEND_UID_CLEAR, OnButtonSendUidClear)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MANUAL_SEND_SERVER, OnClickListManualSendServer)
	ON_BN_CLICKED(IDC_CHECK_SEND_SVR_RAW, OnCheckSendSvrRaw)
	ON_BN_CLICKED(IDC_CHECK_SEND_SVR_PRO, OnCheckSendSvrPro)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFERBYUID_MULTI_SVRS, OnButtonTransferbyuidMultiSvrs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransferDlg message handlers

void CTransferDlg::OnButtonTransfer() 
{
	// TODO: Add your control notification handler code here
// 	UpdateData(TRUE);
// 
// 	TransferJobSettings tjs;
// 	switch (m_iFileSelection)
// 	{
// 	case 0:
// 		tjs.enumFileSelection = enumFileSelection_CurrentStudy;
// 		break;
// 	case 1:
// 		tjs.enumFileSelection = enumFileSelection_CurrentRun;
// 		break;
// 	default:
// 		AfxMessageBox(_T("File Selection error!"));
// 		break;
// 	}
// 
// 	switch (m_iImageSelection)
// 	{
// 	case 0:
// 		tjs.enumImageSelection = enumImageSelection_All;
// 		break;
// 	case 1:
// 		tjs.enumImageSelection = enumImageSelection_Flagged;
// 		break;
// 	case 2:
// 		tjs.enumImageSelection = enumImageSelection_Unflagged;
// 		break;
// 	default:
// 		AfxMessageBox(_T("Image Selection error!"));
// 		break;
// 	}
// 
// 	switch (m_iDownscale)
// 	{
// 	case 0:
// 		tjs.enumDownscaleCriterion = enumDownscaleCriterion_1024_12_16;
// 		break;
// 	case 1:
// 		tjs.enumDownscaleCriterion = enumDownscaleCriterion_512_8_8;
// 		break;
// 	default:
// 		AfxMessageBox(_T("Downscale Selection error!"));
// 		break;
// 	}
// 
// 	tjs.bsCalledAE = m_CurSvr.AllocSysString();
// 
// 	HRESULT hResult = CTestClientSrcDlg::m_pIPATransfer->Transfer(&tjs);
// 	if (S_OK == hResult)
// 	{
// //		UpdateJobList();
// 	}
}

void CTransferDlg::OnSelchangeComboSvrlist() 
{
	// TODO: Add your control notification handler code here
// 	CString strServerAE;
// 	int icbboxSelIndex = m_cbServerList.GetCurSel();
// 	if (-1 == icbboxSelIndex)
// 	{
// 		AfxMessageBox(_T("please select a server"));
// 		return;
// 	}
// 	else
// 		m_cbServerList.GetLBText(icbboxSelIndex, strServerAE);
// 
// 	for (int i = 0; i < m_vtrServers.size(); i++)
// 	{
// 		if (!m_vtrServers[i].Compare((LPCTSTR)strServerAE))
// 		{
// 			m_CurSvr = m_vtrServers[i];
// 			break;
// 		}
// 	}
// 	


	int i = m_cbServerList.GetCurSel();
	if (-1 == i)
	{
		AfxMessageBox(_T("please select a server"));
		return;
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_SEND_AUT_RAW))->SetCheck(m_vtrServers[i].bRaw ? BST_CHECKED : BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_CHECK_SEND_AUT_PRO))->SetCheck(m_vtrServers[i].bProcessed ? BST_CHECKED : BST_UNCHECKED);
	}

}

void CTransferDlg::Init()
{
//	CString szFile = "D:\\commonPrj\\PA\\bin\\TransferSvrConfig.xml";
//
//	m_cbServerList.ResetContent();
//
//	NXMLArchive xml;		
//	try{
//		xml.Open(szFile, FALSE);
////		throw 0;
//		if (xml.FindElem("TRANSFERCONFIG"))
//		{
//			//AE LIST
//			m_vtrServers.clear();
//			if ((xml.FindChildElem("AELIST")) &&(xml.IntoElem()))
//			{
//				int num = xml.GetAttribInt("number");				
//				for (int i=0; i<num; i++)
//				{
//					if ((xml.FindChildElem("item")) && xml.IntoElem())
//					{
//						
//						CString strCalledAE = xml.GetAttrib("server");						
//						m_vtrServers.push_back(strCalledAE);
//						m_cbServerList.InsertString(i, m_vtrServers[i]);
//
//						if ((xml.GetAttribInt("state")) == 1)
//						{
//							m_CurSvr = strCalledAE;
//							m_CurSvrNum = xml.GetAttribInt("index");	
//						}
//						xml.OutOfElem();
//					}					
//				}
//				xml.OutOfElem();
//			}
//		}//end if
//	}//end try
//	catch (...) {
//		AfxMessageBox("Loading setting file failed.");
//	}
//	xml.Close();

//	NetWorkElement NWEtemp;
//	NWEtemp.HostAE = _T("Calling_ae");
//	NWEtemp.ServerAE = _T("Called_ae");
//	NWEtemp.ServerIP = _T("12.34.56.78");
//	NWEtemp.ServerPort = 21;
//
//	m_vtrServers.push_back(NWEtemp);
//
//	m_cbServerList.ResetContent();
//	m_cbServerList.InsertString(0, m_vtrServers[0].ServerAE);
//	

	m_vtrServers.clear();
	m_cbServerList.ResetContent();
	m_CurSvrNum = -1;

	NetworkNode* pNetworkNode = NULL;
	NetworkNode* pNode = NULL;
	long lNodeCount = 0;
	HRESULT hResult =  CTestClientSrcDlg::m_pIPATransfer->GetManualServers(&pNetworkNode, &lNodeCount);
	if (SUCCEEDED(hResult))
	{
		pNode = pNetworkNode;
		for (int i = 0; i < lNodeCount; i++)
		{
			LocalNetworkNode lnn;
			lnn.bDefault = pNode->bDefault;
			lnn.strCalledAE = _com_util::ConvertBSTRToString(pNode->bsCalledAE);
			lnn.strIP = _com_util::ConvertBSTRToString(pNode->bsIP);
			lnn.strPort = _com_util::ConvertBSTRToString(pNode->bsPort);
			lnn.strCallingAE = _com_util::ConvertBSTRToString(pNode->bsCallingAE);
			lnn.bRaw = pNode->bRaw;
			lnn.bProcessed = pNode->bProcessed;

			m_vtrServers.push_back(lnn);

			m_cbServerList.InsertString(i, lnn.strCalledAE);

			if (lnn.bDefault)
			{
				m_CurSvrNum = i;	
			}

			pNode++;
		}


		m_listManualSendSvrs.DeleteAllItems();
		//<< 加入server列表
		for (i = 0; i < m_vtrServers.size(); i++)
		{
			m_listManualSendSvrs.InsertItem(i, _T(""));

			// checkbox state
			m_listManualSendSvrs.SetItemState(i, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK);
			m_listManualSendSvrs.SetCheck(i, m_vtrServers[i].bDefault);
 			m_listManualSendSvrs.SetItemText(i, 1, m_vtrServers[i].strCalledAE);
			m_listManualSendSvrs.SetItemText(i, 2, m_vtrServers[i].bRaw ? _T("Y") : _T(""));
			m_listManualSendSvrs.SetItemText(i, 3, m_vtrServers[i].bProcessed ? _T("Y") : _T(""));
		}

		if (pNetworkNode)
		{
			CoTaskMemFree(pNetworkNode);
			pNetworkNode = NULL;
		}

		if (-1 != m_CurSvrNum)
		{
			m_cbServerList.SetCurSel(m_CurSvrNum);
// 			((CButton*)GetDlgItem(IDC_CHECK_SEND_AUT_RAW))->SetCheck(m_vtrServers[i].bRaw ? BST_CHECKED ? BST_UNCHECKED);
// 			((CButton*)GetDlgItem(IDC_CHECK_SEND_AUT_PRO))->SetCheck(m_vtrServers[i].bProcessed ? BST_CHECKED ? BST_UNCHECKED);
			OnSelchangeComboSvrlist();
		}
	}
	else
	{
		AfxMessageBox(_T("Get TRANSFER server node failed!"));
	}
}

BOOL CTransferDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
//	Init();
	((CComboBox*)GetDlgItem(IDC_COMBO_FILESELECTION))->SetCurSel(1);
	((CComboBox*)GetDlgItem(IDC_COMBO_IMAGESELECTION))->SetCurSel(1);
	((CComboBox*)GetDlgItem(IDC_COMBO_DOWNSCALE))->SetCurSel(0);

	m_CListJobList.SetExtendedStyle(m_CListJobList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_CListJobList.InsertColumn(0, _T("JobID"), LVCFMT_CENTER, 150);
	m_CListJobList.InsertColumn(1, _T("State"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(2, _T("Phase"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(3, _T("Progress"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(4, _T("Detail"), LVCFMT_LEFT, 100);


	m_listManualSendSvrs.SetExtendedStyle(m_CListJobList.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listManualSendSvrs.InsertColumn(0, _T("State"), LVCFMT_CENTER, 50);
	m_listManualSendSvrs.InsertColumn(1, _T("CalledAE"), LVCFMT_CENTER, 100);
	m_listManualSendSvrs.InsertColumn(2, _T("Raw"), LVCFMT_CENTER, 80);
	m_listManualSendSvrs.InsertColumn(3, _T("Processed"), LVCFMT_CENTER, 80);

	((CComboBox*)GetDlgItem(IDC_COMBO_UID_SELECTION))->SetCurSel(2);	
	GetDlgItem(IDC_EDIT_TRANSFER_UID)->SetWindowText(_T("0620070411171826751"));

	((CComboBox*)GetDlgItem(IDC_COMBO_UID_AUTOSEND_TYPE))->SetCurSel(3);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTransferDlg::UpdateJobList()
{
// 	m_CListJobList.DeleteAllItems();
// 	JobInfo* pJobList = NULL;
// 	JobInfo* pJobInfo = NULL;
// 	long lJobCount = 0;
// 	HRESULT hResult =  CTestClientSrcDlg::m_pIPATransfer->GetTransferJobList(&pJobList, &lJobCount);
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
// 				temp = _com_util::ConvertBSTRToString(pJobInfo->bsJobID);
// 				m_CListJobList.SetItemText(0, 0, (LPCTSTR)temp);
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
// 				pJobInfo++;
// 			}
// 		}
// 		
// 		if (pJobList)
// 			CoTaskMemFree(pJobList);
// 	}

}


void CTransferDlg::OnButtonCancelJob() 
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
// 		CTestClientSrcDlg::m_pIPATransfer->CancelTransferJob(bsJobID);
	}
	
}

void CTransferDlg::OnButtonDeletJob() 
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

// 		CTestClientSrcDlg::m_pIPATransfer->DeleteTransferJob(bsJobID);

//		UpdateJobList();
	}
	
}

void CTransferDlg::SetExecutingJobPhaseProgress(LPCTSTR szPhase, LPCTSTR szProgress)
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


void CTransferDlg::SetJobState(LPCTSTR szJobID, JobState enumJobState)
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


void CTransferDlg::SetJobPhase(LPCTSTR szJobID, LPCTSTR szJobPhase)
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

void CTransferDlg::SetJobProgress(JobProgressStruct* pJobProgressStruct)
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

void CTransferDlg::SetJobDetail(JobDetailStruct* pJobDetailStruct)
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

void CTransferDlg::OnButtonTransferbyuid() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);


	//UID list
	int iCount = ((CListBox*)GetDlgItem(IDC_LIST_SEND_MANUAL_UID_LIST))->GetCount();
	if (iCount <= 0)
	{
		AfxMessageBox(_T("Plz input UID!"));
		return;
	}

	BSTR* pbsUIDs = new BSTR[iCount];
	for (int i = 0; i <iCount; i++)
	{
		CString strUID;
		((CListBox*)GetDlgItem(IDC_LIST_SEND_MANUAL_UID_LIST))->GetText(i, strUID);
		pbsUIDs[i] = strUID.AllocSysString();
	}

	// UID type
	PatientAdminUIDType enumPAUIDType;
	int iIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_UID_SELECTION))->GetCurSel();
	switch (iIndex)
	{
	case 0:
		enumPAUIDType = enumPatientAdminUIDType_Patient;
		break;
	case 1:
		enumPAUIDType = enumPatientAdminUIDType_Study;
		break;
	case 2:
		enumPAUIDType = enumPatientAdminUIDType_Series;
		break;
	case 3:
		enumPAUIDType = enumPatientAdminUIDType_Image;
		break;
	default:
		AfxMessageBox(_T("Selection error!"));
		return;
	}

	// CalledAE
	TransferJobSettingsByUID tjs;
	iIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_SVRLIST))->GetCurSel();
	if (-1 == iIndex)
	{
		AfxMessageBox(_T("Plz select a Server!"));
		return;
	}
	
	CString strCalledAE;
	((CComboBox*)GetDlgItem(IDC_COMBO_SVRLIST))->GetLBText(iIndex, strCalledAE);
	tjs.bsCalledAE = strCalledAE.AllocSysString();

	tjs.bRaw = (BST_CHECKED==((CButton*)GetDlgItem(IDC_CHECK_SEND_AUT_RAW))->GetCheck()) ? TRUE : FALSE;
	tjs.bProcessed = (BST_CHECKED==((CButton*)GetDlgItem(IDC_CHECK_SEND_AUT_PRO))->GetCheck()) ? TRUE : FALSE;
		

// 	switch (m_iDownscale)
// 	{
// 	case 0:
// 		tjs.enumDownscaleCriterion = enumDownscaleCriterion_1024_12_16;
// 		break;
// 	case 1:
// 		tjs.enumDownscaleCriterion = enumDownscaleCriterion_512_8_8;
// 		break;
// 	default:
// 		AfxMessageBox(_T("Downscale Selection error!"));
// 		break;
// 	}
// 
// 	tjs.bsCalledAE = m_CurSvr.AllocSysString();

	HRESULT hResult = CTestClientSrcDlg::m_pIPATransfer->ManualTransfer(iCount, pbsUIDs, enumPAUIDType, &tjs);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPATransfer->ManualTransfer()"));
	}
	

	for (i = 0; i <iCount; i++)
	{
		CBSTROpt::FreeBSTR(pbsUIDs[i]);
	}
	delete []pbsUIDs;
}

void CTransferDlg::OnSelchangeComboUidSelection() 
{
	// TODO: Add your control notification handler code here
// 	int iIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_UID_SELECTION))->GetCurSel();
// 	switch (iIndex)
// 	{
// 	case 0:
// 		GetDlgItem(IDC_EDIT_TRANSFER_UID)->SetWindowText(_T("0720070125112419640"));
// 		break;
// 	case 1:
// 		GetDlgItem(IDC_EDIT_TRANSFER_UID)->SetWindowText(_T("0520070125124552937"));
// 		break;
// 	case 2:
// 		GetDlgItem(IDC_EDIT_TRANSFER_UID)->SetWindowText(_T("0620070411171826751"));
// 		break;
// 	default:
// 		AfxMessageBox(_T("Selection error!"));
// 		return;
// 	}
	
}

void CTransferDlg::OnButtonTransferTransferValid() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = FALSE;
	HRESULT hResult = CTestClientSrcDlg::m_pIPATransfer->IsAutoSendValid(&bValid);
	if (S_OK == hResult)
	{
		if (bValid)
		{
			AfxMessageBox(_T("Valid!"));
		}
		else
		{
			AfxMessageBox(_T("InValid!"), MB_OK | MB_ICONERROR);
		}
		
	}
	else
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPATransfer->IsAutoSendValid(&bValid)"), MB_OK | MB_ICONERROR);
	}
}

void CTransferDlg::OnButtonTransferAutosend() 
{
	// TODO: Add your control notification handler code here
	// UID type
	PatientAdminUIDType enumPAUIDType;
	int iIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_UID_AUTOSEND_TYPE))->GetCurSel();
	switch (iIndex)
	{
	case 0:
		enumPAUIDType = enumPatientAdminUIDType_Patient;
		break;
	case 1:
		enumPAUIDType = enumPatientAdminUIDType_Study;
		break;
	case 2:
		enumPAUIDType = enumPatientAdminUIDType_Series;
		break;
	case 3:
		enumPAUIDType = enumPatientAdminUIDType_Image;
		break;
	default:
		AfxMessageBox(_T("Selection error!"));
		return;
	}
	
	CString strStudyUID;
	GetDlgItem(IDC_EDIT_AUTOSEND_STUDYUID)->GetWindowText(strStudyUID);
	if (strStudyUID.IsEmpty())
	{
		AfxMessageBox(_T("Plz input Study UID!"));
		return;
	}

	BSTR bsUID = strStudyUID.AllocSysString();
	HRESULT hResult = CTestClientSrcDlg::m_pIPATransfer->AutoTransfer(bsUID, enumPAUIDType);
	if (S_OK == hResult)
	{
		;
	}
	else
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPATransfer->AutoTransfer(bsUID)"), MB_OK | MB_ICONERROR);
	}
}

void CTransferDlg::OnButtonTransferRefreshNetworknodes() 
{
	// TODO: Add your control notification handler code here
	Init();
}

void CTransferDlg::OnButtonSendUidAdd() 
{
	// TODO: Add your control notification handler code here
	CString strUID;
	GetDlgItem(IDC_EDIT_TRANSFER_UID)->GetWindowText(strUID);

	if (strUID.IsEmpty())
		return;

	((CListBox*)GetDlgItem(IDC_LIST_SEND_MANUAL_UID_LIST))->AddString(strUID);
}

void CTransferDlg::OnButtonSendUidDel() 
{
	// TODO: Add your control notification handler code here
	INT iIndex = ((CListBox*)GetDlgItem(IDC_LIST_SEND_MANUAL_UID_LIST))->GetCurSel();

	if (LB_ERR == iIndex)
		return;

	CString strUID;
		
	((CListBox*)GetDlgItem(IDC_LIST_SEND_MANUAL_UID_LIST))->DeleteString(iIndex);
}

void CTransferDlg::OnButtonSendUidClear() 
{
	// TODO: Add your control notification handler code here
	((CListBox*)GetDlgItem(IDC_LIST_SEND_MANUAL_UID_LIST))->ResetContent();

}

void CTransferDlg::OnClickListManualSendServer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;


    if(pNMListView->iItem == -1)
		return;

	BOOL bRaw = FALSE;
	BOOL bProcessed = FALSE;

	CString strInfo;
	strInfo = m_listManualSendSvrs.GetItemText(pNMListView->iItem, 2);
	if (strInfo.IsEmpty())
	{
		bRaw = FALSE;
	}
	else
	{
		bRaw = TRUE;
	}

	strInfo = m_listManualSendSvrs.GetItemText(pNMListView->iItem, 3);
	if (strInfo.IsEmpty())
	{
		bProcessed = FALSE;
	}
	else
	{
		bProcessed = TRUE;
	}


	((CButton*)GetDlgItem(IDC_CHECK_SEND_SVR_RAW))->SetCheck(bRaw ? BST_CHECKED : BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_SEND_SVR_PRO))->SetCheck(bProcessed ? BST_CHECKED : BST_UNCHECKED);

}

void CTransferDlg::OnCheckSendSvrRaw() 
{
	// TODO: Add your control notification handler code here
	int iState = ((CButton*)GetDlgItem(IDC_CHECK_SEND_SVR_RAW))->GetCheck();

	POSITION pos = m_listManualSendSvrs.GetFirstSelectedItemPosition();
	CString strJobID;
	if (pos == NULL)
	{
		return;
	}
	
	while (pos)
	{			
		int nItem = m_listManualSendSvrs.GetNextSelectedItem(pos);

		m_listManualSendSvrs.SetItemText(nItem, 2, (BST_CHECKED == iState ? _T("Y") : _T("")));
	}
}

void CTransferDlg::OnCheckSendSvrPro() 
{
	// TODO: Add your control notification handler code here
	int iState = ((CButton*)GetDlgItem(IDC_CHECK_SEND_SVR_PRO))->GetCheck();

	POSITION pos = m_listManualSendSvrs.GetFirstSelectedItemPosition();
	CString strJobID;
	if (pos == NULL)
	{
		return;
	}
	
	while (pos)
	{			
		int nItem = m_listManualSendSvrs.GetNextSelectedItem(pos);

		m_listManualSendSvrs.SetItemText(nItem, 3, (BST_CHECKED == iState ? _T("Y") : _T("")));
	}
}

void CTransferDlg::OnButtonTransferbyuidMultiSvrs() 
{
	// TODO: Add your control notification handler code here
	//UID list
	int iCount = ((CListBox*)GetDlgItem(IDC_LIST_SEND_MANUAL_UID_LIST))->GetCount();
	if (iCount <= 0)
	{
		AfxMessageBox(_T("Plz input UID!"));
		return;
	}

	BSTR* pbsUIDs = new BSTR[iCount];
	for (int i = 0; i <iCount; i++)
	{
		CString strUID;
		((CListBox*)GetDlgItem(IDC_LIST_SEND_MANUAL_UID_LIST))->GetText(i, strUID);
		pbsUIDs[i] = strUID.AllocSysString();
	}

	// UID type
	PatientAdminUIDType enumPAUIDType;
	int iIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_UID_SELECTION))->GetCurSel();
	switch (iIndex)
	{
	case 0:
		enumPAUIDType = enumPatientAdminUIDType_Patient;
		break;
	case 1:
		enumPAUIDType = enumPatientAdminUIDType_Study;
		break;
	case 2:
		enumPAUIDType = enumPatientAdminUIDType_Series;
		break;
	case 3:
		enumPAUIDType = enumPatientAdminUIDType_Image;
		break;
	default:
		AfxMessageBox(_T("Selection error!"));
		return;
	}

	// CalledAE
	int iSvrCount = m_listManualSendSvrs.GetItemCount();
	if (0 == iSvrCount)
	{
		return;
	}

	BOOL bServerAndImageFormatSelectionValid = FALSE;
	TransferJobSettingsByUID* ptjs = new TransferJobSettingsByUID[iSvrCount];
	for (i = 0; i < iSvrCount; i++)
	{
		int iCheckBoxState = m_listManualSendSvrs.GetItemState(i, TVIS_STATEIMAGEMASK ) >> 12;
		ptjs[i].bSelected = (1 == iCheckBoxState) ? FALSE : TRUE;
				
		CString strInfo = m_listManualSendSvrs.GetItemText(i, 1);
		ptjs[i].bsCalledAE = strInfo.AllocSysString();

		strInfo = m_listManualSendSvrs.GetItemText(i, 2);
		ptjs[i].bRaw = strInfo.IsEmpty() ? FALSE : TRUE;

		strInfo = m_listManualSendSvrs.GetItemText(i, 3);
		ptjs[i].bProcessed = strInfo.IsEmpty() ? FALSE : TRUE;

		//<< 获得校验服务器及图像格式选择有效性
		if (!bServerAndImageFormatSelectionValid)
		{
			if (ptjs[i].bSelected)
			{
				if (ptjs[i].bRaw || ptjs[i].bProcessed)
				{
					bServerAndImageFormatSelectionValid = TRUE;
				}
			}
		}
	}
		
	if (!bServerAndImageFormatSelectionValid)
	{
		AfxMessageBox(_T("Server or image selection invalid!"));
		return;
	}
	
	HRESULT hResult = CTestClientSrcDlg::m_pIPATransfer->ManualTransferWithMultiServers(iCount, pbsUIDs, enumPAUIDType, iSvrCount, ptjs);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPATransfer->ManualTransferWithMultiServers()"));
	}
	

	for (i = 0; i <iCount; i++)
	{
		CBSTROpt::FreeBSTR(pbsUIDs[i]);
	}
	delete []pbsUIDs;

	for (i = 0; i < iSvrCount; i++)
	{
		CBSTROpt::FreeBSTR(ptjs[i].bsCalledAE);
	}
	delete []ptjs;
}
