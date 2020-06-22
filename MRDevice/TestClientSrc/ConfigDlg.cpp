// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "ConfigDlg.h"
#include "ServerDlg.h"
#include "TestClientSrcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_radioServerType = -1;
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_LIST_CONFIG_SEND_AUTO, m_listAutoServer);
	DDX_Radio(pDX, IDC_RADIO_CONFIG_AUTO_SEND, m_radioServerType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_BN_CLICKED(IDC_BUTTON_CONIFG_AUTO_ADD, OnButtonConifgAutoAdd)
	ON_BN_CLICKED(IDC_BUTTON_CONIFG_AUTO_MODIFY, OnButtonConifgAutoModify)
	ON_BN_CLICKED(IDC_BUTTON_CONIFG_AUTO_DELETE, OnButtonConifgAutoDelete)
	ON_BN_CLICKED(IDC_BUTTON_CONIFG_AUTO_CLEAR, OnButtonConifgAutoClear)
	ON_BN_CLICKED(IDC_BUTTON_CONIFG_AUTO_SAVE, OnButtonConifgAutoSave)
	ON_BN_CLICKED(IDC_BUTTON_CONIFG_AUTO_REFRESH, OnButtonConifgAutoRefresh)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_CONFIG_SEND_AUTO, OnItemchangingListConfigSendAuto)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONFIG_SEND_AUTO, OnDblclkListConfigSendAuto)
	ON_BN_CLICKED(IDC_RADIO_CONFIG_AUTO_SEND, OnRadioConfigAutoSend)
	ON_BN_CLICKED(IDC_RADIO_CONFIG_MANUAL_SEND, OnRadioConfigManualSend)
	ON_BN_CLICKED(IDC_RADIO_CONFIG_WL, OnRadioConfigWl)
	ON_BN_CLICKED(IDC_RADIO_CONFIG_MPPS, OnRadioConfigMpps)
	ON_BN_CLICKED(IDC_BUTTON_CONIFG_AUTO_TEST, OnButtonConifgAutoTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listAutoServer.SetExtendedStyle(m_listAutoServer.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	InitServerList(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::InitServerList(int iType)
{
	OnButtonConifgAutoClear();

	int nColumnCount = m_listAutoServer.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount; i++)
	{
	   m_listAutoServer.DeleteColumn(0);
	}

	switch (iType)
	{
	case 0:
	case 1:
		m_listAutoServer.InsertColumn(0, _T("state"), LVCFMT_CENTER, 50);
		m_listAutoServer.InsertColumn(1, _T("CalledAE"), LVCFMT_CENTER, 130);
		m_listAutoServer.InsertColumn(2, _T("IP"), LVCFMT_CENTER, 110);
		m_listAutoServer.InsertColumn(3, _T("Port"), LVCFMT_CENTER, 50);
		m_listAutoServer.InsertColumn(4, _T("CallingAE"), LVCFMT_CENTER, 130);
		m_listAutoServer.InsertColumn(5, _T("Raw"), LVCFMT_CENTER, 60);
		m_listAutoServer.InsertColumn(6, _T("Processed"), LVCFMT_CENTER, 70);
		break;
	case 2:
	case 3:
		m_listAutoServer.InsertColumn(0, _T("state"), LVCFMT_CENTER, 50);
		m_listAutoServer.InsertColumn(1, _T("CalledAE"), LVCFMT_CENTER, 130);
		m_listAutoServer.InsertColumn(2, _T("IP"), LVCFMT_CENTER, 110);
		m_listAutoServer.InsertColumn(3, _T("Port"), LVCFMT_CENTER, 50);
		m_listAutoServer.InsertColumn(4, _T("CallingAE"), LVCFMT_CENTER, 130);
		break;
	default:
		break;
	}
}

void CConfigDlg::OnButtonConifgAutoAdd() 
{
	// TODO: Add your control notification handler code here
	CServerDlg dlg;

	if (IDOK == dlg.DoModal())
	{
		int iIndex = m_listAutoServer.GetItemCount();

		iIndex = m_listAutoServer.InsertItem(iIndex, _T(""));
		m_listAutoServer.SetItemText(iIndex, 1, dlg.m_strServerAE);
		m_listAutoServer.SetItemText(iIndex, 2, dlg.m_strServerIP);
		m_listAutoServer.SetItemText(iIndex, 3, dlg.m_strServerPort);
		m_listAutoServer.SetItemText(iIndex, 4, dlg.m_strHostAE);
		m_listAutoServer.SetItemText(iIndex, 5, dlg.m_bRaw ? _T("Y") : _T(""));
		m_listAutoServer.SetItemText(iIndex, 6, dlg.m_bProcessed ? _T("Y") : _T(""));
	}
}

void CConfigDlg::OnButtonConifgAutoModify() 
{
	// TODO: Add your control notification handler code here
	CServerDlg dlg;

	int nItem = -1;
	POSITION pos = m_listAutoServer.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		///< 写错误信息
		AfxMessageBox(_T("Please select a server"));

		return;
	}

	UpdateData(TRUE);
	dlg.SetType(m_radioServerType);
			
	nItem = m_listAutoServer.GetNextSelectedItem(pos);
	dlg.m_strServerAE = m_listAutoServer.GetItemText(nItem, 1);
	dlg.m_strServerIP = m_listAutoServer.GetItemText(nItem, 2);
	dlg.m_strServerPort = m_listAutoServer.GetItemText(nItem, 3);
	dlg.m_strHostAE = m_listAutoServer.GetItemText(nItem, 4);
	dlg.m_bRaw = CString(m_listAutoServer.GetItemText(nItem, 5)).IsEmpty() ? FALSE : TRUE;
	dlg.m_bProcessed = CString(m_listAutoServer.GetItemText(nItem, 6)).IsEmpty() ? FALSE : TRUE;



	if (IDOK == dlg.DoModal())
	{
		m_listAutoServer.SetItemText(nItem, 1, dlg.m_strServerAE);
		m_listAutoServer.SetItemText(nItem, 2, dlg.m_strServerIP);
		m_listAutoServer.SetItemText(nItem, 3, dlg.m_strServerPort);
		m_listAutoServer.SetItemText(nItem, 4, dlg.m_strHostAE);
		m_listAutoServer.SetItemText(nItem, 5, dlg.m_bRaw ? _T("Y") : _T(""));
		m_listAutoServer.SetItemText(nItem, 6, dlg.m_bProcessed ? _T("Y") : _T(""));

	}
}

void CConfigDlg::OnButtonConifgAutoDelete() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listAutoServer.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		///< 写错误信息
		AfxMessageBox(_T("Please select a server"));

		return;
	}
	else
	{			
		int nItem = m_listAutoServer.GetNextSelectedItem(pos);
		m_listAutoServer.DeleteItem(nItem);
	}
}

void CConfigDlg::OnButtonConifgAutoClear() 
{
	// TODO: Add your control notification handler code here
	int iIndex = m_listAutoServer.GetItemCount();
	for (int i = iIndex; i >= 0; i--)
	{
		m_listAutoServer.DeleteItem(i);
	}
}

void CConfigDlg::OnButtonConifgAutoSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iNum = m_listAutoServer.GetItemCount();
	NetworkNode* pServers = new NetworkNode[iNum];
	CString strInfo;

	for (int i = 0; i < iNum; i++)
	{
		strInfo = m_listAutoServer.GetItemText(i, 1);
		pServers[i].bsCalledAE = strInfo.AllocSysString();

		strInfo = m_listAutoServer.GetItemText(i, 2);
		pServers[i].bsIP = strInfo.AllocSysString();

		strInfo = m_listAutoServer.GetItemText(i, 3);
		pServers[i].bsPort = strInfo.AllocSysString();

		strInfo = m_listAutoServer.GetItemText(i, 4);
		pServers[i].bsCallingAE = strInfo.AllocSysString();

		pServers[i].bDefault = m_listAutoServer.GetCheck(i);

			switch (m_radioServerType)
			{
			case 0:
			case 1:
				pServers[i].bRaw = CString(m_listAutoServer.GetItemText(i, 5)).IsEmpty() ? FALSE : TRUE;
				pServers[i].bProcessed = CString(m_listAutoServer.GetItemText(i, 6)).IsEmpty() ? FALSE : TRUE;
				break;
			case 2:
			case 3:
				break;
			}

	}

	HRESULT hResult = S_OK;

	switch (m_radioServerType)
	{
	case 0:
		hResult = CTestClientSrcDlg::m_pIPATransfer->SetAutoServers(pServers, iNum);
		break;
	case 1:
		hResult = CTestClientSrcDlg::m_pIPATransfer->SetManualServers(pServers, iNum);
		break;
	case 2:
		hResult = CTestClientSrcDlg::m_pIPAWlMpps->SetWlServers(pServers, iNum);
	    break;
	case 3:
		hResult = CTestClientSrcDlg::m_pIPAWlMpps->SetMppsServers(pServers, iNum);
	    break;
	default:
	    return;
	}

	if (S_OK != hResult)
	{
		AfxMessageBox(_T("Error: CTestClientSrcDlg::m_pIPATransfer->SetAutoServers(&pServers, &iNum)"));
	}

	delete []pServers;

}

void CConfigDlg::OnButtonConifgAutoRefresh() 
{
	// TODO: Add your control notification handler code here


	OnButtonConifgAutoClear();

	NetworkNode* pServers = NULL;
	long lNum = 0;
	HRESULT hResult = S_OK;
	
	UpdateData(TRUE);
	switch (m_radioServerType)
	{
	case 0:
		hResult = CTestClientSrcDlg::m_pIPATransfer->GetAutoServers(&pServers, &lNum);
		break;
	case 1:
		hResult = CTestClientSrcDlg::m_pIPATransfer->GetManualServers(&pServers, &lNum);
		break;
	case 2:
		hResult = CTestClientSrcDlg::m_pIPAWlMpps->GetWlServers(&pServers, &lNum);
	    break;
	case 3:
		hResult = CTestClientSrcDlg::m_pIPAWlMpps->GetMppsServers(&pServers, &lNum);
	    break;
	default:
	    return;
	}
	if (S_OK == hResult)
	{
		for (int i = 0; i < lNum; i++)
		{
			int iIndex = m_listAutoServer.GetItemCount();

			iIndex = m_listAutoServer.InsertItem(iIndex, _T(""));
			m_listAutoServer.SetItemText(iIndex, 1, CBSTROpt::BSTRToCString(pServers[i].bsCalledAE));
			m_listAutoServer.SetItemText(iIndex, 2, CBSTROpt::BSTRToCString(pServers[i].bsIP));
			m_listAutoServer.SetItemText(iIndex, 3, CBSTROpt::BSTRToCString(pServers[i].bsPort));
			m_listAutoServer.SetItemText(iIndex, 4, CBSTROpt::BSTRToCString(pServers[i].bsCallingAE));
			switch (m_radioServerType)
			{
			case 0:
			case 1:
				m_listAutoServer.SetItemText(iIndex, 5, pServers[i].bRaw ? _T("Y") : _T(""));
				m_listAutoServer.SetItemText(iIndex, 6, pServers[i].bProcessed ? _T("Y") : _T(""));
				break;
			case 2:
			case 3:
				break;
			}

			m_listAutoServer.SetCheck(iIndex, pServers[i].bDefault);
		}

		CoTaskMemFree(pServers);
	}
	else
	{
		AfxMessageBox(_T("Error: CTestClientSrcDlg::m_pIPATransfer->GetAutoServers(&pServers, &lNum)"));
	}
}

void CConfigDlg::OnButtonConifgAutoTest() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listAutoServer.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		///< 写错误信息
		AfxMessageBox(_T("Please select a server"));

		return;
	}
	else
	{			
		int nItem = m_listAutoServer.GetNextSelectedItem(pos);

		NetworkNode nns;
		BOOL bResult = FALSE;
		CString strInfo;

		strInfo = m_listAutoServer.GetItemText(nItem, 1);
		nns.bsCalledAE = strInfo.AllocSysString();

		strInfo = m_listAutoServer.GetItemText(nItem, 2);
		nns.bsIP = strInfo.AllocSysString();

		strInfo = m_listAutoServer.GetItemText(nItem, 3);
		nns.bsPort = strInfo.AllocSysString();

		strInfo = m_listAutoServer.GetItemText(nItem, 4);
		nns.bsCallingAE = strInfo.AllocSysString();

		HRESULT hResult = S_OK;
		UpdateData(TRUE);
		switch (m_radioServerType)
		{
		case 0:
			hResult = CTestClientSrcDlg::m_pIPATransfer->ConnectTest(&nns, &bResult);
			break;
		case 1:
			hResult = CTestClientSrcDlg::m_pIPATransfer->ConnectTest(&nns, &bResult);
			break;
		case 2:
			hResult = CTestClientSrcDlg::m_pIPAWlMpps->WlServerConnectTest(&nns, &bResult);
			break;
		case 3:
			hResult = CTestClientSrcDlg::m_pIPAWlMpps->MppsServerConnectTest(&nns, &bResult);
			break;
		default:
			return;
		}

		if (S_OK == hResult)
		{
			if (bResult)
			{
				AfxMessageBox(_T("Succeed in connecting server!"));
			}
			else
			{
				AfxMessageBox(_T("Failed to connect server!"), MB_OK|MB_ICONERROR);
			}
		}
		else
		{
			AfxMessageBox(_T("Error: CTestClientSrcDlg::m_pIPATransfer->ConnectTest(&nns, &bResult)"));
		}
	}
}
void CConfigDlg::OnItemchangingListConfigSendAuto(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (pNMListView->uOldState == 0 && pNMListView->uNewState == 0)   
		return; //   no   change   
	
	UpdateData(TRUE);

	//<< 自动发送或手动发送，CheckBox任选，故直接返回
	if (0 == m_radioServerType || 1 == m_radioServerType)
		return;
	
	//   old   check   box   state   
	BOOL bPrevState = (BOOL)(((pNMListView->uOldState & LVIS_STATEIMAGEMASK)>>12)-1);   
	
	if (bPrevState < 0)   //   on   startup   there's   no   previous   state,so   assign   as   false   (unchecked)     
		bPrevState = 0;   
	
	//   new   check   box   state   
	BOOL bChecked = (BOOL)(((pNMListView->uNewState & LVIS_STATEIMAGEMASK)>>12)-1);   
	
	if (bChecked < 0)   //   on   non-checkbox   notifications   assume   false     
		bChecked = 0;   
	
	if (bPrevState == bChecked)//   no   change   in   check   box   
		return;

	// check changed
	BOOL bSelectedState = FALSE;
	if (bChecked)
	{
		bSelectedState = TRUE;
	}
	else
	{
		bSelectedState = FALSE;
	}

	if (bSelectedState)
	{
		int nCount = m_listAutoServer.GetItemCount();
		for (int i = 0; i < nCount; i++)
		{
			if (i != pNMListView->iItem)
			{
				m_listAutoServer.SetCheck(i, FALSE);
			}
		}
	}
	
	*pResult = 0;
}

void CConfigDlg::OnDblclkListConfigSendAuto(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE lpNMIA = (LPNMITEMACTIVATE)pNMHDR;
    int nItem = lpNMIA->iItem;

	///< 判断行号是否合法
	if(nItem >= 0 && nItem < m_listAutoServer.GetItemCount())
	{
		OnButtonConifgAutoModify();
	}

	*pResult = 0;
}


void CConfigDlg::OnRadioConfigAutoSend() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_CONFIG_INFO)->SetWindowText(_T("Auto Send Server Config"));
	InitServerList(0);

	OnButtonConifgAutoRefresh();
}

void CConfigDlg::OnRadioConfigManualSend() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_CONFIG_INFO)->SetWindowText(_T("Manual Send Server Config"));
	InitServerList(1);
	OnButtonConifgAutoRefresh();
}

void CConfigDlg::OnRadioConfigWl() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_CONFIG_INFO)->SetWindowText(_T("Worklist Send Server Config"));
	InitServerList(2);
	OnButtonConifgAutoRefresh();
}

void CConfigDlg::OnRadioConfigMpps() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_CONFIG_INFO)->SetWindowText(_T("MPPS Send Server Config"));
	InitServerList(3);
	OnButtonConifgAutoRefresh();
}
