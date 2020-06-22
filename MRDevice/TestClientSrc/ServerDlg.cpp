// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog


CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	m_strServerAE = _T("");
	m_strServerIP = _T("");
	m_strServerPort = _T("");
	m_strHostAE = _T("");
	m_bRaw = FALSE;
	m_bProcessed = FALSE;
	m_iType = 0;
	//{{AFX_DATA_INIT(CServerDlg)
	//}}AFX_DATA_INIT
}


void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	DDX_Control(pDX, IDC_CHECK_SERVER_PROCESSED, m_ckProcessed);
	DDX_Control(pDX, IDC_CHECK_SERVER_RAW, m_ckRaw);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER_IP, m_ServerIP);
	DDX_Control(pDX, IDC_EDIT_SERVER_PORT, m_ServerPort);
	DDX_Control(pDX, IDC_EDIT_SERVER_CALLINGAE, m_HostAE);
	DDX_Control(pDX, IDC_EDIT_SERVER_CALLEDAE, m_ServerAE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	ON_BN_CLICKED(IDC_BUTTON_SERVER_OK, OnButtonServerOk)
	ON_BN_CLICKED(IDC_BUTTON_SERVER_CANCEL, OnButtonServerCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ServerAE.SetWindowText(m_strServerAE);
	m_ServerIP.SetWindowText(m_strServerIP);
	m_ServerPort.SetWindowText(m_strServerPort);
	m_HostAE.SetWindowText(m_strHostAE);

	switch (m_iType)
	{
	case 0:
	case 1:
		m_ckRaw.SetCheck(m_bRaw ? BST_CHECKED : BST_UNCHECKED);
		m_ckProcessed.SetCheck(m_bProcessed ? BST_CHECKED : BST_UNCHECKED);
		break;
	case 2:
	case 3:
		m_ckRaw.ShowWindow(SW_HIDE);
		m_ckProcessed.ShowWindow(SW_HIDE);
		break;
	default:
		break;
	}

	m_ServerAE.SetSel(0, -1);
	m_ServerAE.SetFocus();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CServerDlg::SetType(int iType)
{
	m_iType = iType;
}

void CServerDlg::OnButtonServerOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_ServerAE.GetWindowText(m_strServerAE);
	m_ServerIP.GetWindowText(m_strServerIP);
	m_ServerPort.GetWindowText(m_strServerPort);
	m_HostAE.GetWindowText(m_strHostAE);
	m_bRaw = (BST_CHECKED==m_ckRaw.GetCheck()) ? TRUE : FALSE;
	m_bProcessed = (BST_CHECKED==m_ckProcessed.GetCheck()) ? TRUE : FALSE;

	///< 判断输入合法性
	if (m_strServerAE.IsEmpty())
	{
		///< 写错误信息
		AfxMessageBox(_T("Invalid ServerAE"));

		m_ServerAE.SetFocus();
		return;
	}

// 	CString strIPPart1, strIPPart2, strIPPart3, strIPPart4;
// 	
// 	if (strIPPart1.IsEmpty() ||
// 		strIPPart2.IsEmpty() ||
// 		strIPPart3.IsEmpty() ||
// 		strIPPart4.IsEmpty())
// 	{
// 		///< 写错误信息
// 		NFSSystemPluginPartObj::GetInstance()->WriteSystemInfoMessage(
// 			_T("Invalid ServerIP..."));
// 		return;
// 	}

	if (m_strServerPort.IsEmpty())
	{
		///< 写错误信息
		AfxMessageBox(_T("Invalid ServerPort"));

		m_ServerPort.SetFocus();
		return;
	}
	else
	{
		int nPort = _ttoi((LPCTSTR)m_strServerPort);
		m_strServerPort.Format(_T("%d"), nPort);
	}

	if (m_strHostAE.IsEmpty())
	{
		///< 写错误信息
		AfxMessageBox(_T("Invalid HostAE"));

		m_HostAE.SetFocus();
		return;
	}


	CDialog::OnOK();
}

void CServerDlg::OnButtonServerCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
