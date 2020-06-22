// TestClientSrcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestClientSrc.h"
#include "TestClientSrcDlg.h"
#include "PALib_i.c"
//#include "PALibExt_i.c"
#include "comutil.h"
//#include "shobjidl.h"
#include "shellapi.h"
//#include "shldisp.h"

#pragma comment(lib, "comsupp.lib")
#include "atlbase.h"

// #pragma   comment(linker,"/manifestdependency:\"type='win32'   name='Microsoft.Windows.Common-Controls'   version='6.0.0.0'   processorArchitecture='x86'   publicKeyToken='6595b64144ccf1df'   language='*'\"")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//DECLARE_INTERFACE_(ITaskbarList,IUnknown)
//{
//   STDMETHOD(QueryInterface)(THIS_ REFIID riid,LPVOID* ppvObj) PURE;
//   STDMETHOD_(ULONG,AddRef)(THIS) PURE;
//   STDMETHOD_(ULONG,Release)(THIS) PURE;
//   STDMETHOD(ActivateTab)(HWND) PURE;
//   STDMETHOD(AddTab)(HWND) PURE;
//   STDMETHOD(DeleteTab)(HWND) PURE;
//   STDMETHOD(HrInit)(void) PURE;
//};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
IGeneralSys*  CTestClientSrcDlg::m_pIGeneral = NULL;
IPAPrint*  CTestClientSrcDlg::m_pIPAPrint = NULL;
IPABurn*  CTestClientSrcDlg::m_pIPABurn = NULL;
IPATransfer* CTestClientSrcDlg::m_pIPATransfer = NULL;
IPAGeneral* CTestClientSrcDlg::m_pIPAGeneral = NULL;
IPADiscImport* CTestClientSrcDlg::m_pIPADiscImport = NULL;
IPAWLMPPS* CTestClientSrcDlg::m_pIPAWlMpps = NULL;

IGeneralInterface* CTestClientSrcDlg::m_pIGenaralInterface = NULL;
IPing* CTestClientSrcDlg::m_pIPing = NULL;

CTestClientSrcDlg* g_smDlg = NULL;
HINSTANCE g_hResourceInstance = NULL;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestClientSrcDlg dialog

CTestClientSrcDlg::CTestClientSrcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestClientSrcDlg::IDD, pParent)
{


	//{{AFX_DATA_INIT(CTestClientSrcDlg)
	m_RatioImageType = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_enumJobMode = enumJobMode_Current;
}

void CTestClientSrcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestClientSrcDlg)
	DDX_Control(pDX, IDC_LIST_JOB_QUEUE, m_listJobQueue);
	DDX_Control(pDX, IDC_EDIT_PASINK, m_Edit);
	DDX_Radio(pDX, IDC_RADIO_XA, m_RatioImageType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestClientSrcDlg, CDialog)
	//{{AFX_MSG_MAP(CTestClientSrcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PRINT, OnPrint)
	ON_BN_CLICKED(IDC_STARTUP, OnStartup)
	ON_BN_CLICKED(IDC_SHUTDOWN, OnShutdown)
	ON_BN_CLICKED(IDC_CANCELPRINT, OnCancelprint)
	ON_BN_CLICKED(IDC_BEEP, OnBeep)
	ON_BN_CLICKED(IDC_RADIO_XA, OnRadioXa)
	ON_BN_CLICKED(IDC_RADIO_SC, OnRadioSc)
	ON_BN_CLICKED(IDC_CNTPASINK, OnCntpasink)
	ON_BN_CLICKED(IDC_DISCNTPASINK, OnDiscntpasink)
	ON_BN_CLICKED(IDC_BUTTON_BURN, OnButtonBurn)
	ON_BN_CLICKED(IDC_RADIO_PRINT, OnRadioPrint)
	ON_BN_CLICKED(IDC_RADIO_TRANSFER, OnRadioTransfer)
	ON_BN_CLICKED(IDC_RADIO_BURNER, OnRadioBurner)
	ON_BN_CLICKED(IDC_BUTTON_HIDE_FC, OnButtonHideFc)
	ON_WM_ACTIVATE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_DCM_READ, OnRadioDcmRead)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, OnButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_TOPMOST, OnButtonTopmost)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_DESKTOP, OnButtonShowDesktop)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_AREA, OnArea)
	ON_BN_CLICKED(IDC_RADIO_PAGENERAL, OnRadioPageneral)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_MESSAGE(WM_MY_TRAY_NOTIFICATION,OnTrayNotification)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_WLMPPS, OnButtonWlmpps)
	ON_BN_CLICKED(IDC_RADIO_PATIENTADMIN, OnRadioPatientadmin)
	ON_BN_CLICKED(IDC_BUTTON_GEN_REG_FILE, OnButtonGenRegFile)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, OnButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_JOB_UP, OnButtonMoveJobUp)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_JOB_DOWN, OnButtonMoveJobDown)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_JOB, OnButtonCancelJob)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_JOB, OnButtonDeleteJob)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH_JOB, OnButtonRefreshJob)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_JOB_QUEUE, OnDblclkListJobQueue)
	ON_BN_CLICKED(IDC_BUTTON_HISTORYJOB_COUNT, OnButtonHistoryjobCount)
	ON_BN_CLICKED(IDC_BUTTON_HISTORYJOB_GET_JOB, OnButtonHistoryjobGetJob)
	ON_BN_CLICKED(IDC_BUTTON_HISTORYJOB_GET_JOB2, OnButtonHistoryjobGetJob2)
	ON_BN_CLICKED(IDC_BUTTON_HISTORYJOB_GET_JOB3, OnButtonHistoryjobGetJob3)
	ON_COMMAND(ID_TRAY_EXIT_SD_PA, OnOK)
	ON_COMMAND(ID_TRAY_EXIT_UNSD_PA, OnButtonExit)
	ON_COMMAND(ID_TRAY_SHOW_DESKTOP, OnButtonShowDesktop)
	ON_BN_CLICKED(IDC_PING, OnPing)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestClientSrcDlg message handlers

BOOL CTestClientSrcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


// 	CMenu menu;
// 	menu.LoadMenu(IDR_TRAYICON);//装载自定义的右键菜单
// 	SetMenu(&menu);
// 	
// 	CMenu menu1;
// 	menu1.LoadMenu(IDR_MENU_TEST);//装载自定义的右键菜单
// 	SetMenu(&menu1);

	// ToolBar
// 	if (!m_wndToolBar.CreateEx(this,TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS)||!m_wndToolBar.LoadToolBar(IDR_TOOLBAR))
// 	{
// 	}
// 	//定位工具条 
// 	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
// 
// 	
// 	m_wndToolBar.SetButtonStyle(0, TBBS_BUTTON);
// 	m_wndToolBar.SetButtonStyle(1, TBBS_BUTTON);
// 	m_wndToolBar.SetButtonStyle(2, TBBS_CHECKBOX);
// 	m_wndToolBar.SetButtonStyle(3, TBBS_DROPDOWN);
// 	m_wndToolBar.SetButtonStyle(4, TBBS_AUTOSIZE);
// 	m_wndToolBar.SetButtonStyle(5, TBBS_NOPREFIX);
// 	m_wndToolBar.SetButtonStyle(6, TBBS_GROUP);
// 	m_wndToolBar.SetButtonStyle(7, TBBS_GROUP);
// 	m_wndToolBar.SetButtonStyle(8, TBBS_GROUP);
// 	m_wndToolBar.SetButtonStyle(9, TBBS_CHECKGROUP);
// 	m_wndToolBar.SetButtonStyle(10, TBBS_CHECKBOX);
// 	m_wndToolBar.SetButtonStyle(11, TBBS_CHECKBOX);
// 	m_wndToolBar.SetButtonStyle(12, TBBS_CHECKGROUP);
// 	m_wndToolBar.SetButtonStyle(13, TBBS_CHECKGROUP);
// 	m_wndToolBar.SetButtonStyle(14, TBBS_CHECKGROUP);
// 	m_wndToolBar.SetButtonStyle(15, TBBS_CHECKGROUP);


	// 时间日期
	SetTimer(1, 1000, NULL);


	
	UINT msg;
	m_nid.uFlags = 0;
	
	// 设定系统托盘图标
	if (m_hIcon)
	{
		msg = NIM_ADD;
		m_nid.hWnd= m_hWnd;
		m_nid.hIcon = m_hIcon;
		m_nid.uFlags |= NIF_ICON;

		m_nid.uFlags |= NIF_MESSAGE;
		m_nid.uCallbackMessage = WM_MY_TRAY_NOTIFICATION;

		m_nid.uFlags |= NIF_TIP;
		memcpy(m_nid.szTip, _T("Printing&Archiving TestClient"), sizeof(_T("Printing&Archiving TestClient"))+1);

		Shell_NotifyIcon(msg, &m_nid);
	} 

 	((CButton*)GetDlgItem(IDC_BUTTON_TOPMOST))->ModifyStyle(0, WS_CHILD|WS_VISIBLE|BS_ICON);
	m_hIconTop = AfxGetApp()->LoadIcon(IDI_ICON_UNTOP);
 	((CButton*)GetDlgItem(IDC_BUTTON_TOPMOST))->SetIcon(m_hIconTop);

 	((CButton*)GetDlgItem(IDC_BUTTON_EXIT))->ModifyStyle(0, WS_CHILD|WS_VISIBLE|BS_ICON);
	m_hIconExitAndUnShutDownPA = AfxGetApp()->LoadIcon(IDI_ICON_XP_UNSDPA);
 	((CButton*)GetDlgItem(IDC_BUTTON_EXIT))->SetIcon(m_hIconExitAndUnShutDownPA);

 	((CButton*)GetDlgItem(IDOK))->ModifyStyle(0, WS_CHILD|WS_VISIBLE|BS_ICON);
	m_hIconExitAndShutDownPA = AfxGetApp()->LoadIcon(IDI_ICON_XP_SDPA);
 	((CButton*)GetDlgItem(IDOK))->SetIcon(m_hIconExitAndShutDownPA);

	((CButton*)GetDlgItem(IDC_BUTTON_SHOW_DESKTOP))->ModifyStyle(0, WS_CHILD|WS_VISIBLE|BS_ICON);
	m_hIconDesktop = AfxGetApp()->LoadIcon(IDI_ICON_XP_DESKTOP);
 	((CButton*)GetDlgItem(IDC_BUTTON_SHOW_DESKTOP))->SetIcon(m_hIconDesktop);

	((CButton*)GetDlgItem(IDC_BUTTON_GEN_REG_FILE))->ModifyStyle(0, WS_CHILD|WS_VISIBLE|BS_ICON);
	m_hIconPAReg = AfxGetApp()->LoadIcon(IDI_ICON_MAKE_PAREG);
 	((CButton*)GetDlgItem(IDC_BUTTON_GEN_REG_FILE))->SetIcon(m_hIconPAReg);


// 	CRect rect;
// 	GetWindowRect(&rect);
// 	////////////////////////////
// 	SetWindowPos(&CWnd::wndTopMost, rect.left, rect.top, 
// 			rect.right, rect.bottom, SWP_SHOWWINDOW);

	// TODO: Add extra initialization here
	g_smDlg = this;
	m_RatioImageType = 1;
	UpdateData(FALSE);

	// Create child window
	CRect rcDlgs;
	GetDlgItem(IDC_AREA)->GetWindowRect(rcDlgs);
	ScreenToClient(rcDlgs);

	
	m_pPADlg = new CPatientAdminDlg;
	m_pPADlg->Create(IDD_FORMVIEW_PATIENTADMIN, this);
	m_pPADlg->MoveWindow(rcDlgs);
	
	m_pPAGeneralDlg = new CPAGeneralDlg;
	m_pPAGeneralDlg->Create(IDD_FORMVIEW_PAGENERAL, this);
	m_pPAGeneralDlg->MoveWindow(rcDlgs);

	m_pPrintDlg = new CPrintDlg;
	m_pPrintDlg->Create(IDD_FORMVIEW_PRINT, this);
	m_pPrintDlg->MoveWindow(rcDlgs);

	m_pTransferDlg = new CTransferDlg;
	m_pTransferDlg->Create(IDD_FORMVIEW_TRANSFER, this);
	m_pTransferDlg->MoveWindow(rcDlgs);

	m_pBurnDlg = new CBurnDlg;
	m_pBurnDlg->Create(IDD_FORMVIEW_BURN, this);
	m_pBurnDlg->MoveWindow(rcDlgs);

	
	m_pImportDlg = new CImportDlg;
	m_pImportDlg->Create(IDD_FORMVIEW_IMPORT, this);
	m_pImportDlg->MoveWindow(rcDlgs);

	m_pWlMppsDlg = new CWlMppsDlg;
	m_pWlMppsDlg->Create(IDD_FORMVIEW_WLMPPS, this);
	m_pWlMppsDlg->MoveWindow(rcDlgs);

	m_pDcmReadDlg = new CDcmReadDlg;
	m_pDcmReadDlg->Create(IDD_FORMVIEW_DCM_READ, this);
	m_pDcmReadDlg->MoveWindow(rcDlgs);

	m_pConfigDlg = new CConfigDlg;
	m_pConfigDlg->Create(IDD_FORMVIEW_CONFIG, this);
	m_pConfigDlg->MoveWindow(rcDlgs);


//	m_pBurnDlg->ShowWindow(TRUE);


	HRESULT hResult;

	if(CoCreateInstance(CLSID_PA,
		NULL, CLSCTX_LOCAL_SERVER,
		IID_IGeneralSys,
		(LPVOID*)&m_pIGeneral) == S_OK)
	{
		hResult = m_pIGeneral->QueryInterface(IID_IPAPrint,(LPVOID*)&m_pIPAPrint);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("QueryInterface(IID_IPAPrint,(LPVOID*)&m_pIPAPrint) failed!"));
		}

		hResult = m_pIGeneral->QueryInterface(IID_IPABurn,(LPVOID*)&m_pIPABurn);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("QueryInterface(IID_IPABurn,(LPVOID*)&m_pIPABurn) failed!"));
		}

		hResult = m_pIGeneral->QueryInterface(IID_IPATransfer,(LPVOID*)&m_pIPATransfer);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("QueryInterface(IID_IPATransfer,(LPVOID*)&m_pIPATransfer) failed!"));
		}

		hResult = m_pIGeneral->QueryInterface(IID_IPADiscImport,(LPVOID*)&m_pIPADiscImport);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("QueryInterface(IID_IPADiscImport,(LPVOID*)&m_pIPADiscImport) failed!"));
		}

		
		hResult = m_pIGeneral->QueryInterface(IID_IPAWLMPPS,(LPVOID*)&m_pIPAWlMpps);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("QueryInterface(IID_IPADiscImport,(LPVOID*)&m_pIPAWlMpps) failed!"));
		}

		hResult = m_pIGeneral->QueryInterface(IID_IPAGeneral,(LPVOID*)&m_pIPAGeneral);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("QueryInterface(IID_IPAGeneral,(LPVOID*)&m_pIPAGeneral) failed!"));
		}

		hResult = m_pIGeneral->QueryInterface(IID_IGeneralInterface,(LPVOID*)&m_pIGenaralInterface);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("QueryInterface(IID_IGeneralInterface,(LPVOID*)&m_pIGenaralInterface) failed!"));
		}

		hResult = m_pIGeneral->QueryInterface(IID_IPing,(LPVOID*)&m_pIPing);
		if (FAILED(hResult))
		{
			AfxMessageBox(_T("QueryInterface(IID_IPing,(LPVOID*)&m_pIPing!"));
		}

		// connect point
		OnCntpasink();

	}

	// Patient
	CListCtrl* pList1 = (CListCtrl*)GetDlgItem(IDC_LIST_PATIENTS);
	CListCtrl* pList2 = (CListCtrl*)GetDlgItem(IDC_LIST_STUDY);
	CListCtrl* pList3 = (CListCtrl*)GetDlgItem(IDC_LIST_SERIES);

	DWORD dwStype = pList1->GetExtendedStyle();
	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	pList1->SetExtendedStyle(dwStype);
	pList1->SetCheck(0, FALSE);

	dwStype = pList2->GetExtendedStyle();
	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	pList2->SetExtendedStyle(dwStype);
	pList2->SetCheck(0, TRUE);

	dwStype = pList3->GetExtendedStyle();
	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	pList3->SetExtendedStyle(dwStype);
	pList3->SetCheck(0, TRUE);

	// Patient
// 	pList1->InsertColumn(0, "Status", LVCFMT_CENTER, 50);
// 	pList1->InsertColumn(1, "Patient Name", LVCFMT_CENTER, 60);
// 	pList1->InsertColumn(2, "Patient ID", LVCFMT_CENTER, 60);
// 	pList1->InsertColumn(3, "Gender", LVCFMT_CENTER, 60);
// 	pList1->InsertColumn(4, "Birth Date", LVCFMT_CENTER, 60);
// 	pList1->InsertColumn(5, "Study Num", LVCFMT_CENTER, 60);
// 
// 	pList1->InsertItem(0,"");
// 	pList1->SetItemText(0,1,"Tom H");
// 	pList1->SetItemText(0,2,"2536");
// 	pList1->SetItemText(0,3,"M");
// 	pList1->SetItemText(0,4,"1970-03-05");
// 	pList1->SetItemText(0,5,"2");
// 
// 	pList1->InsertItem(1,"");
// 	pList1->SetItemText(1,1,"Linda F");
// 	pList1->SetItemText(1,2,"1542");
// 	pList1->SetItemText(1,3,"F");
// 	pList1->SetItemText(1,4,"1956-11-02");
// 	pList1->SetItemText(1,5,"3");
// 
// 	// Study
// 	pList2->InsertColumn(0, "Status", LVCFMT_CENTER, 50);
// 	pList2->InsertColumn(1, "Patient Name", LVCFMT_CENTER, 60);
// 	pList2->InsertColumn(2, "Study ID", LVCFMT_CENTER, 60);
// 	pList2->InsertColumn(3, "Start Data/Time", LVCFMT_CENTER, 60);
// 	pList2->InsertColumn(4, "Series Num", LVCFMT_CENTER, 60);
// 
// 	pList2->InsertItem(0,"");
// 	pList2->SetItemText(0,1,"Tom H");
// 	pList2->SetItemText(0,2,"1");
// 	pList2->SetItemText(0,3,"2007-01-11 10:23:55");
// 	pList2->SetItemText(0,4,"2");
// 
// 	pList2->InsertItem(1,"");
// 	pList2->SetItemText(1,1,"Tom H");
// 	pList2->SetItemText(1,2,"2");
// 	pList2->SetItemText(1,3,"2007-01-12 09:44:12");
// 	pList2->SetItemText(1,4,"3");
// 
// 	// Series
// 	pList3->InsertColumn(0, "Status", LVCFMT_CENTER, 50);
// 	pList3->InsertColumn(1, "Patient Name", LVCFMT_CENTER, 60);
// 	pList3->InsertColumn(2, "Study ID", LVCFMT_CENTER, 60);
// 	pList3->InsertColumn(3, "Series ID", LVCFMT_CENTER, 60);
// 	pList3->InsertColumn(4, "Images Num", LVCFMT_CENTER, 60);
// 
// 	pList3->InsertItem(0,"");
// 	pList3->SetItemText(0,1,"Tom H");
// 	pList3->SetItemText(0,2,"1");
// 	pList3->SetItemText(0,3,"1");
// 	pList3->SetItemText(0,4,"56");
// 
// 	pList3->InsertItem(1,"");
// 	pList3->SetItemText(1,1,"Tom H");
// 	pList3->SetItemText(1,2,"1");
// 	pList3->SetItemText(1,3,"2");
// 	pList3->SetItemText(1,4,"34");

	m_listJobQueue.SetExtendedStyle(m_listJobQueue.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listJobQueue.InsertColumn(0, _T("Index"), LVCFMT_CENTER, 50);
	m_listJobQueue.InsertColumn(1, _T("JobType"), LVCFMT_CENTER, 100);
	m_listJobQueue.InsertColumn(2, _T("SubmitedTime"), LVCFMT_CENTER, 130);
	m_listJobQueue.InsertColumn(3, _T("State"), LVCFMT_CENTER, 70);
	m_listJobQueue.InsertColumn(4, _T("Phase"), LVCFMT_CENTER, 0);
	m_listJobQueue.InsertColumn(5, _T("Progress"), LVCFMT_CENTER, 70);
	m_listJobQueue.InsertColumn(6, _T("Detail"), LVCFMT_LEFT, 280);


	g_hResourceInstance = LoadLibrary(_T("UserGuidanceRes.dll"));
	if (NULL == g_hResourceInstance)
	{
		AfxMessageBox(_T("Failed to LoadLibrary UserGuidanceRes.dll"));
	}

	((CButton*)GetDlgItem(IDC_STORE))->SetFocus();
	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CTestClientSrcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}

	if (SC_MINIMIZE == nID)
	{
		//SetWindowLong(m_hWnd,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
		ShowWindow(SW_HIDE);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestClientSrcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestClientSrcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestClientSrcDlg::OnStartup() 
{

	if (m_pIGeneral)
		m_pIGeneral->StartUp();

//	GetDlgItem(IDC_RADIO_SC)->EnableWindow();
//	GetDlgItem(IDC_RADIO_XA)->EnableWindow();
//	GetDlgItem(IDC_PRINT)->EnableWindow();
//	GetDlgItem(IDC_CANCELPRINT)->EnableWindow();
//	GetDlgItem(IDC_STARTUP)->EnableWindow(FALSE);
//	GetDlgItem(IDC_SHUTDOWN)->EnableWindow();


	return ;
	
}

void CTestClientSrcDlg::OnPrint() 
{
}

void CTestClientSrcDlg::OnShutdown() 
{
	if (m_pIGeneral)
	{
		m_pIGeneral->ShutDown();

	}
//	GetDlgItem(IDC_RADIO_SC)->EnableWindow(FALSE);
//	GetDlgItem(IDC_RADIO_XA)->EnableWindow(FALSE);
//	GetDlgItem(IDC_PRINT)->EnableWindow(FALSE);
//	GetDlgItem(IDC_CANCELPRINT)->EnableWindow(FALSE);
//	GetDlgItem(IDC_STARTUP)->EnableWindow();
//	GetDlgItem(IDC_SHUTDOWN)->EnableWindow(FALSE);
}

void CTestClientSrcDlg::OnCancelprint() 
{
//    CComBSTR test = "0620061205155620015" ;
//	msg.bsPatientUID = test ;
//	CComBSTR test1 = "0520061206114158515" ;
//	msg.bsStudyUID   = test1 ;
//	CComBSTR test2 = "0520061206114" ;
//	msg.bsSeriesUID  = test2 ;
//	msg.iCmdType     = enumPRINTCANCEL ;
//
//    pIPAUICmd->PACmd(msg);
//	UpdateData();
//	switch (m_RatioImageType)
//	{
//	case 0:
//		m_ImageType = enumXA;
//		break;
//	case 1:
//		m_ImageType = enumSC;
//		break;
//	default:
//		AfxMessageBox("Please select image type");
//		return;
//		break;
//	}
//
//	msg.iCmdType     = enumPRINTCANCEL;
//
//    pIPAUICmd->PACmd(msg);

	
}

void CTestClientSrcDlg::OnBeep() 
{
// 	static DWORD dwFeq = 0x25;
// 
// 	Beep(dwFeq, 10);
// 	dwFeq += 100;
// 	if (dwFeq > 0x7FFF)
// 	{
// 		dwFeq = 0x25;
// 	}

//	FlashWindow(TRUE); // invert the title bar 
//	Sleep(2000);              // wait a bit 
//	FlashWindow(TRUE); // invert again 
 
	// Play the system exclamation sound. 
 
//	MessageBeep(MB_ICONEXCLAMATION);

// 	char*   source = ("hahaha");     
// 	//put   your   text   in   source   
// 	if(OpenClipboard())   
// 	{   
// 		HGLOBAL   clipbuffer;   
// 		char   *   buffer;   
// 		EmptyClipboard();   
// 		clipbuffer   =   GlobalAlloc(GMEM_DDESHARE,   strlen(source)+1);   
// 		buffer   =   (char*)GlobalLock(clipbuffer);   
// 		strcpy(buffer,   LPCSTR(source));   
// 		GlobalUnlock(clipbuffer);   
// 		SetClipboardData(CF_TEXT,clipbuffer);   
// 		CloseClipboard();   
// 	}

// 	CDcmGen dcm;
// 	CString strFile = _T("E:\\DcmCache\\Transfer\\Work\\00000001\\DICOM\\00000000\\X0010005");
// 	CString strsaveFile = _T("E:\\DcmCache\\Transfer\\Work\\00000001\\DICOM\\00000000\\X0010007");
// 	CString strInfo;
// 	DWORD dwStart = GetTickCount();
// 	if (!dcm.LoadDXFile(strFile))
// 	{
// 		AfxMessageBox(_T("dcm.LoadDXFile(strFile)"));
// 		return;
// 	}
// 	else
// 	{
// 		strInfo.Format(_T("Time span: %d ms"), GetTickCount() - dwStart);
// 		AppendString(strInfo);
// 	}
// 
// 	if (!dcm.ModifyPatientName(_T("aaaaaaaaaaabbbbbbbbb")))
// 	{
// 		AfxMessageBox(_T("dcm.ModifyPatientName()"));
// 		return;
// 	}
// 	else
// 	{
// 		strInfo.Format(_T("Time span: %d ms"), GetTickCount() - dwStart);
// 		AppendString(strInfo);
// 	}
// 
// 	if (!dcm.SaveDXFile(strsaveFile))
// 	{
// 		AfxMessageBox(_T("dcm.SaveDXFile()"));
// 		return;
// 	}
// 	else
// 	{
// 		strInfo.Format(_T("Time span: %d ms"), GetTickCount() - dwStart);
// 		AppendString(strInfo);
// 	}


// 	CString strTrace;
// 	long lLen = (18*1024*1024)/4;
// 	int* p = new int[lLen];
// 	p[0] = 1;
// 	p[1] = 2;
// 	p[(18*1024*1024)/4 - 1] = 3;
// 	
// 	DWORD dwStart = GetTickCount();
// 
// 	if (S_OK != m_pIPAPrint->TestFoo(lLen, p))
// 	{
// 		AfxMessageBox(_T("Error!"));
// 	}
// 	
// 	strTrace.Format(_T("用时: %d ms"), GetTickCount()-dwStart);
// 	AppendString(strTrace);
// 
// 	delete []p;

}

void CTestClientSrcDlg::OnOK() 
{
	// TODO: Add extra validation here
	OnDiscntpasink();

	if (m_pIGeneral)
	{
		m_pIGeneral->ShutDown();
		
		m_pIGeneral->Release();
		m_pIPAPrint->Release();
		m_pIPABurn->Release();
		m_pIPATransfer->Release();
		m_pIPADiscImport->Release();
		m_pIPAWlMpps->Release();
		m_pIGenaralInterface->Release();
		m_pIPing->Release();

		m_pIGeneral = NULL;
		m_pIPAPrint = NULL;
		m_pIPABurn = NULL;
		m_pIPATransfer = NULL;
		m_pIPADiscImport = NULL;
		m_pIPAWlMpps = NULL;
		m_pIGenaralInterface = NULL;
		m_pIPing = NULL;
	}

	if (m_pPrintDlg)
	{
		delete m_pPrintDlg;
		m_pPrintDlg = NULL;
	}
	if (m_pBurnDlg)
	{
		delete m_pBurnDlg;
		m_pBurnDlg = NULL;
	}
	if (m_pTransferDlg)
	{
		delete m_pTransferDlg;
		m_pTransferDlg = NULL;
	}

	if (g_hResourceInstance)
	{
		FreeLibrary(g_hResourceInstance);
		g_hResourceInstance = NULL;
	}

	UINT msg;
	m_nid.uFlags = 0;
	
	// 移除系统托盘图标
	if (m_hIcon)
	{
		msg = NIM_DELETE;
		m_nid.hWnd= m_hWnd;
		m_nid.hIcon = m_hIcon;
		m_nid.uFlags |= NIF_ICON;

		Shell_NotifyIcon(msg, &m_nid);
	} 

	CDialog::OnOK();

}

void CTestClientSrcDlg::OnRadioXa() 
{
	// TODO: Add your control notification handler code here
//	if (NULL != pIGeneral)
//		pIPAUICmd->SetDICOMImageType(enumUnitPRINT, enumXA);
}

void CTestClientSrcDlg::OnRadioSc() 
{
	// TODO: Add your control notification handler code here
//	if (NULL != pIGeneral)
//		pIPAUICmd->SetDICOMImageType(enumUnitPRINT, enumSC);
//	
}

void CTestClientSrcDlg::OnCntpasink() 
{
	// TODO: Add your control notification handler code here
	BOOL bRet;
	bRet = m_PAGeneralEventSink.SetConnection(CLSID_PA, IID_IPAGeneralEvent);
	bRet = m_PASinkPrint.SetConnection(CLSID_PA, IID_IPAPrintEvent);
	bRet = m_PASinkBurn.SetConnection(CLSID_PA, IID_IPABurnEvent);
	bRet = m_PASinkTransfer.SetConnection(CLSID_PA, IID_IPATransferEvent);
	bRet = m_PASinkDiscImport.SetConnection(CLSID_PA, IID_IPADiscImportEvent);
	bRet = m_PASinkWlMpps.SetConnection(CLSID_PA, IID_IPAWLMPPSEvent);

	bRet = m_IGeneralEventSink.SetConnection(CLSID_PA, IID_IGeneralEvent);
	
	bRet = m_IUserGuidanceEventSink.SetConnection(CLSID_PA, IID_IUserGuidanceEvent);

//	GetDlgItem(IDC_CNTPASINK)->EnableWindow(FALSE);
//	GetDlgItem(IDC_DISCNTPASINK)->EnableWindow();

}

void CTestClientSrcDlg::OnDiscntpasink() 
{
	// TODO: Add your control notification handler code here
	BOOL bRet;
	bRet = m_PAGeneralEventSink.ReleaseConnection();
	bRet = m_PASinkPrint.ReleaseConnection();
	bRet = m_PASinkBurn.ReleaseConnection();
	bRet = m_PASinkTransfer.ReleaseConnection();
	bRet = m_PASinkDiscImport.ReleaseConnection();
	bRet = m_PASinkWlMpps.ReleaseConnection();
	
	bRet = m_IGeneralEventSink.ReleaseConnection();
	bRet = m_IUserGuidanceEventSink.ReleaseConnection();

//	GetDlgItem(IDC_CNTPASINK)->EnableWindow();
//	GetDlgItem(IDC_DISCNTPASINK)->EnableWindow(FALSE);

}

void CTestClientSrcDlg::OnButtonBurn() 
{
	// TODO: Add your control notification handler code here
//	m_pBurnDlg = new CBurnDlg;
//	m_pBurnDlg->Create(IDD_FORMVIEW_BURN, this);
//	m_pBurnDlg->ShowWindow(SW_SHOW);.

//	msg.iCmdType     = enumWR2CD ;
//
//    pIPAUICmd->PACmd(msg);
//
//	char* p = NULL;
//	long cMax = 0;
//	m_pIPABurnSetting->GetDevices((BYTE**)&p, &cMax);
//	char* pTemp = p + 4;
//	CString strDeviceName = pTemp;
//	BSTR bsDeviceName = strDeviceName.AllocSysString();
//	CoTaskMemFree(p);
//
//	DeviceInfo localDeviceInfo;
//	
//	m_pIPABurnSetting->SetBurnDevice(bsDeviceName);
//	m_pIPABurnSetting->GetDeviceInfo(&localDeviceInfo);
//	m_pIPABurnSetting->SetBurnMedia(enumBurnMediaType_CD);
}

void CTestClientSrcDlg::OnRadioPatientadmin() 
{
	// TODO: Add your control notification handler code here
	m_pPADlg->ShowWindow(TRUE);
	m_pPAGeneralDlg->ShowWindow(FALSE);
	m_pPrintDlg->ShowWindow(FALSE);
	m_pTransferDlg->ShowWindow(FALSE);
	m_pBurnDlg->ShowWindow(FALSE);
	m_pImportDlg->ShowWindow(FALSE);
	m_pWlMppsDlg->ShowWindow(FALSE);
	m_pConfigDlg->ShowWindow(FALSE);
	m_pDcmReadDlg->ShowWindow(FALSE);
}


void CTestClientSrcDlg::OnRadioPageneral() 
{
	// TODO: Add your control notification handler code here
	m_pPADlg->ShowWindow(FALSE);
	m_pPAGeneralDlg->ShowWindow(TRUE);
	m_pPrintDlg->ShowWindow(FALSE);
	m_pTransferDlg->ShowWindow(FALSE);
	m_pBurnDlg->ShowWindow(FALSE);
	m_pImportDlg->ShowWindow(FALSE);
	m_pWlMppsDlg->ShowWindow(FALSE);
	m_pConfigDlg->ShowWindow(FALSE);
	m_pDcmReadDlg->ShowWindow(FALSE);
}

void CTestClientSrcDlg::OnRadioPrint() 
{
	// TODO: Add your control notification handler code here
	m_pPADlg->ShowWindow(FALSE);
	m_pPAGeneralDlg->ShowWindow(FALSE);
	m_pPrintDlg->ShowWindow(TRUE);
	m_pTransferDlg->ShowWindow(FALSE);
	m_pBurnDlg->ShowWindow(FALSE);
	m_pImportDlg->ShowWindow(FALSE);
	m_pWlMppsDlg->ShowWindow(FALSE);
	m_pConfigDlg->ShowWindow(FALSE);
	m_pDcmReadDlg->ShowWindow(FALSE);
}

void CTestClientSrcDlg::OnRadioTransfer() 
{
	// TODO: Add your control notification handler code here
	m_pPADlg->ShowWindow(FALSE);
	m_pPAGeneralDlg->ShowWindow(FALSE);
	m_pPrintDlg->ShowWindow(FALSE);
	m_pTransferDlg->ShowWindow(TRUE);
	m_pBurnDlg->ShowWindow(FALSE);
	m_pImportDlg->ShowWindow(FALSE);
	m_pWlMppsDlg->ShowWindow(FALSE);
	m_pConfigDlg->ShowWindow(FALSE);
	m_pDcmReadDlg->ShowWindow(FALSE);
	
}

void CTestClientSrcDlg::OnRadioBurner() 
{
	// TODO: Add your control notification handler code here
	m_pPADlg->ShowWindow(FALSE);
	m_pPAGeneralDlg->ShowWindow(FALSE);
	m_pPrintDlg->ShowWindow(FALSE);
	m_pTransferDlg->ShowWindow(FALSE);
	m_pBurnDlg->ShowWindow(TRUE);
	m_pImportDlg->ShowWindow(FALSE);
	m_pWlMppsDlg->ShowWindow(FALSE);
	m_pConfigDlg->ShowWindow(FALSE);
	m_pDcmReadDlg->ShowWindow(FALSE);
	
}

void CTestClientSrcDlg::OnButtonImport() 
{
	// TODO: Add your control notification handler code here
	m_pPADlg->ShowWindow(FALSE);
	m_pPAGeneralDlg->ShowWindow(FALSE);
	m_pPrintDlg->ShowWindow(FALSE);
	m_pTransferDlg->ShowWindow(FALSE);
	m_pBurnDlg->ShowWindow(FALSE);
	m_pImportDlg->ShowWindow(TRUE);
	m_pWlMppsDlg->ShowWindow(FALSE);
	m_pConfigDlg->ShowWindow(FALSE);
	m_pDcmReadDlg->ShowWindow(FALSE);
	
}

void CTestClientSrcDlg::OnButtonWlmpps() 
{
	// TODO: Add your control notification handler code here
	m_pPADlg->ShowWindow(FALSE);
	m_pPAGeneralDlg->ShowWindow(FALSE);
	m_pPrintDlg->ShowWindow(FALSE);
	m_pTransferDlg->ShowWindow(FALSE);
	m_pBurnDlg->ShowWindow(FALSE);
	m_pImportDlg->ShowWindow(FALSE);
	m_pWlMppsDlg->ShowWindow(TRUE);
	m_pConfigDlg->ShowWindow(FALSE);
	m_pDcmReadDlg->ShowWindow(FALSE);
	
}

void CTestClientSrcDlg::OnButtonConfig() 
{
	// TODO: Add your control notification handler code here
	m_pPADlg->ShowWindow(FALSE);
	m_pPAGeneralDlg->ShowWindow(FALSE);
	m_pPrintDlg->ShowWindow(FALSE);
	m_pTransferDlg->ShowWindow(FALSE);
	m_pBurnDlg->ShowWindow(FALSE);
	m_pImportDlg->ShowWindow(FALSE);
	m_pWlMppsDlg->ShowWindow(FALSE);
	m_pConfigDlg->ShowWindow(TRUE);
	m_pDcmReadDlg->ShowWindow(FALSE);
}

void CTestClientSrcDlg::OnRadioDcmRead() 
{
	// TODO: Add your control notification handler code here
	m_pPADlg->ShowWindow(FALSE);
	m_pPAGeneralDlg->ShowWindow(FALSE);
	m_pPrintDlg->ShowWindow(FALSE);
	m_pTransferDlg->ShowWindow(FALSE);
	m_pBurnDlg->ShowWindow(FALSE);
	m_pImportDlg->ShowWindow(FALSE);
	m_pWlMppsDlg->ShowWindow(FALSE);
	m_pConfigDlg->ShowWindow(FALSE);
	m_pDcmReadDlg->ShowWindow(TRUE);
	
}


void CTestClientSrcDlg::InitChildDlg()
{
	m_pPrintDlg->Init();
	m_pBurnDlg->Init();
	m_pTransferDlg->Init();
}

void CTestClientSrcDlg::AppendString(CString strMsg)
{
	CString temp;
	m_Edit.GetWindowText(temp);
	if (_T("") != temp)
		temp += _T("\r\n");

	temp += strMsg;
	m_Edit.SetWindowText(temp);

	int iLineCount = m_Edit.GetLineCount();
	m_Edit.LineScroll(iLineCount);
}

void CTestClientSrcDlg::OnButtonHideFc() 
{
	// TODO: Add your control notification handler code here
	HWND hArchiveHWnd = NULL;
	if (NULL != hArchiveHWnd) return;
//    ::WinExec(szPath, SW_SHOW);//::WinExec(szPath, SW_SHOW);
	hArchiveHWnd = ::FindWindow(_T("PNMS_FilmComposer"), NULL);
	while(TRUE)
	{
		if (NULL != hArchiveHWnd) break;
		hArchiveHWnd = ::FindWindow(_T("PNMS_FilmComposer"), NULL);
	}
	if (hArchiveHWnd !=NULL) 
	{
//		NOTIFYICONDATA tnid; 
//
//		tnid.cbSize = sizeof(NOTIFYICONDATA); 
//		tnid.hWnd = hArchiveHWnd; 
//		tnid.uID = uID; 
 
//		Shell_NotifyIcon(NIM_DELETE, &tnid); 

//		::ShowWindow(hArchiveHWnd, SW_HIDE);
// http://blog.csdn.net/mynamelj/archive/2006/08/25/1116797.aspx
//		HRESULT hr; 
//		ITaskbarList* pTaskbarList;
//		hr = CoCreateInstance( CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER,  
//				  IID_ITaskbarList, (void**)&pTaskbarList );
//
//		if(SUCCEEDED(hr))
//		{
//			 pTaskbarList->HrInit();
//			 pTaskbarList->DeleteTab(hArchiveHWnd);
//
//			 pTaskbarList->Release();
//		}
//
	}

}

BOOL CTestClientSrcDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
// 	static int i = 0;
// 	CString str;
// 	str.Format(_T("%d"), pMsg->message);
// 	AppendString(str);
//  	if (pMsg->message == WM_DEVICECHANGE)
// 	{
// 		AfxMessageBox(_T("changed"));
// 	}


// 	if (pMsg->message == WM_KEYDOWN)
// 	{
// 		//aasdfpMsg->lParam
// // 		GetDlgItem(IDC_EDIT_OUTPUT)->SetFocus();
// // 		GetDlgItem(IDC_EDIT_OUTPUT)->SetWindowText("aaaa");
// 	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CTestClientSrcDlg::OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized )
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	if (nState == WA_INACTIVE)
	{
		
//		SetForegroundWindow();
//		::BringWindowToTop(this->m_hWnd);
//		PostMessage(WM_LBUTTONDOWN);
//		SetFocus();
//		::PostMessage(this->m_hWnd, WM_ACTIVATE, NULL, NULL);


// 		::SetForegroundWindow(this->m_hWnd);   
// 		::SetFocus(this->m_hWnd);//可能不需要   
// 		::ShowWindow(this->m_hWnd, SW_NORMAL);

//		SetActiveWindow();         //设dlg为活动窗口 
//		ShowWindow(SW_RESTORE);    //让dlg显示在所有窗口的最顶层

// 	CRect rect;
// 	GetWindowRect(&rect);
// 	////////////////////////////
// 	SetWindowPos(&CWnd::wndTopMost, rect.left, rect.top, 
// 			rect.right, rect.bottom, SWP_SHOWWINDOW);

	}
	//加入你自己的代码
	//AfxMessageBox("fhaha");
}

void CTestClientSrcDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CTestClientSrcDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnLButtonDown(nFlags, point);
}

void CTestClientSrcDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_PASINK)->SetWindowText(_T(""));
}

void CTestClientSrcDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	OnOK();
//	CDialog::OnClose();
}

void CTestClientSrcDlg::OnButtonTopmost() 
{
	// TODO: Add your control notification handler code here
	static BOOL bTopMost = FALSE;

	CRect rc;
	GetWindowRect(&rc);

	if (!bTopMost)
	{
		bTopMost = TRUE;

		::SetWindowPos(this->GetSafeHwnd(), HWND_TOPMOST, rc.left, rc.top,
		           rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW);
		m_hIconTop = AfxGetApp()->LoadIcon(IDI_ICON_TOP);;
 		((CButton*)GetDlgItem(IDC_BUTTON_TOPMOST))->SetIcon(m_hIconTop);
	}
	else
	{
		bTopMost = FALSE;

		::SetWindowPos(this->GetSafeHwnd(), HWND_NOTOPMOST, rc.left, rc.top,
		           rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW);
		m_hIconTop = AfxGetApp()->LoadIcon(IDI_ICON_UNTOP);;
 		((CButton*)GetDlgItem(IDC_BUTTON_TOPMOST))->SetIcon(m_hIconTop);
	}
}

void CTestClientSrcDlg::OnButtonShowDesktop() 
{
	// TODO: Add your control notification handler code here
// 	CoInitialize(0); 
// 	IShellDispatch4* pdisp  =  NULL; 
// 	CoCreateInstance(CLSID_Shell,  NULL, CLSCTX_ALL, __uuidof(IShellDispatch4), (void**)&pdisp); 
// 	pdisp->ToggleDesktop();  //这句是用来切换桌面的 
// 	pdisp->Release(); 
// 	CoUninitialize(); 
//	::ShellExecute(this->GetSafeHwnd(),_T("Open"),_T("C:\\Documents and Settings\\Adminx\\Application Data\\Microsoft\\Internet Explorer\\Quick Launch\\显示桌面.scf"),NULL,NULL,SW_SHOW);
// 	IShellDispatch   *shell   =   NULL;   
// 	HRESULT   hr   =   CoCreateInstance(CLSID_Shell,   NULL,   CLSCTX_SERVER,   IID_IDispatch,   (void**)&shell);   
// 	if   (FAILED(hr)   ||   !shell)   
// 		return;       
// 	shell->MinimizeAll();   
// 	shell->Release();

//	::ShellExecute(this->GetSafeHwnd(),_T("ToggleDesktop"),_T("C:\\Documents and Settings\\Adminx\\Application Data\\Microsoft\\Internet Explorer\\Quick Launch\\显示桌面.scf"),NULL,NULL,SW_SHOW);

// 	keybd_event(VK_LWIN, 0, 0, 0);  
// 	keybd_event(77, 0, 0, 0);
// 	keybd_event(77, 0, 0x02, 0);
// 	keybd_event(VK_LWIN, 0, 0x02, 0);

	wchar_t wcsModuleName[MAX_PATH];
	GetModuleFileName(NULL, wcsModuleName, MAX_PATH);

	CString strFileName;
	wchar_t* p = wcsrchr(wcsModuleName, _T('\\'));
	if (NULL != p)
	{
		strFileName = CString(wcsModuleName, p - wcsModuleName + 1) + _T("ShowDesktop.scf");
		if (strFileName.GetLength() > MAX_PATH)
		{
			return;
		}
	}

	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = CreateFile(strFileName,           // open MYFILE.TXT 
					GENERIC_WRITE,              // open for reading 
					FILE_SHARE_READ,           // share for reading 
					NULL,                      // no security 
					CREATE_ALWAYS,             // existing file only 
					FILE_ATTRIBUTE_NORMAL,     // normal file 
					NULL);                     // no attr. template 

	if (hFile == INVALID_HANDLE_VALUE) 
	{
		AfxMessageBox(_T("error: CreateFile()"));
		return;
	}		

	char pFrameBuffer[] = "[Shell]\r\nCommand=2\r\nIconFile=explorer.exe,3\r\n[Taskbar]\r\nCommand=ToggleDesktop";
	DWORD dwBytesWritten = 0;
	if (!::WriteFile(hFile, pFrameBuffer, sizeof(pFrameBuffer), &dwBytesWritten, NULL))
	{
		AfxMessageBox(_T("error: WriteFile()"));
		CloseHandle(hFile);
		return;
	}

	CloseHandle(hFile);

	::ShellExecute(this->GetSafeHwnd(),_T("Open"),strFileName,NULL,NULL,SW_SHOW);

	::DeleteFile(strFileName);
}

void CTestClientSrcDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnMouseMove(nFlags, point);
}

void CTestClientSrcDlg::OnArea() 
{
	// TODO: Add your control notification handler code here
}


void CTestClientSrcDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	OnDiscntpasink();

	if (m_pIGeneral)
	{
//		m_pIGeneral->ShutDown();
		
		m_pIGeneral->Release();
		m_pIPAPrint->Release();
		m_pIPABurn->Release();
		m_pIPATransfer->Release();
		m_pIPADiscImport->Release();
		m_pIPAWlMpps->Release();
		m_pIGenaralInterface->Release();
		m_pIPing->Release();

		m_pIGeneral = NULL;
		m_pIPAPrint = NULL;
		m_pIPABurn = NULL;
		m_pIPATransfer = NULL;
		m_pIPADiscImport = NULL;
		m_pIPAWlMpps = NULL;
		m_pIGenaralInterface = NULL;
		m_pIPing = NULL;
	}

	if (m_pPrintDlg)
	{
		delete m_pPrintDlg;
		m_pPrintDlg = NULL;
	}
	if (m_pBurnDlg)
	{
		delete m_pBurnDlg;
		m_pBurnDlg = NULL;
	}
	if (m_pTransferDlg)
	{
		delete m_pTransferDlg;
		m_pTransferDlg = NULL;
	}

	if (g_hResourceInstance)
	{
		FreeLibrary(g_hResourceInstance);
		g_hResourceInstance = NULL;
	}

	UINT msg;
	m_nid.uFlags = 0;
	
	// 移除系统托盘图标
	if (m_hIcon)
	{
		msg = NIM_DELETE;
		m_nid.hWnd= m_hWnd;
		m_nid.hIcon = m_hIcon;
		m_nid.uFlags |= NIF_ICON;

		Shell_NotifyIcon(msg, &m_nid);
	} 

	CDialog::OnOK();
	
}

LRESULT CTestClientSrcDlg::OnTrayNotification(WPARAM wp, LPARAM lp)
{    
	if (wp!=m_nid.uID ||
		(lp!=WM_RBUTTONUP && lp!=WM_LBUTTONDBLCLK))
		return 0;
	
	if (WM_RBUTTONUP == lp)
	{
		// 右击消息
		CPoint oPoint;
		CMenu menu ;

		GetCursorPos(&oPoint);
		menu.LoadMenu(IDR_TRAYICON);//装载自定义的右键菜单

		CMenu* pSubMenu;//定义下面要用到的cmenu对象
		pSubMenu = menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单
		static CBitmap   bmpDesktop;
		static CBitmap   bmpExitUnSDPA;
		static CBitmap   bmpExitSDPA;

		bmpDesktop.LoadBitmap(IDB_BITMAP_DESKTOP);
		bmpExitUnSDPA.LoadBitmap(IDB_BITMAP_XP_UNSDPA);
		bmpExitSDPA.LoadBitmap(IDB_BITMAP_XP_SDPA);
		pSubMenu->SetMenuItemBitmaps(ID_TRAY_SHOW_DESKTOP,MF_BYCOMMAND,&bmpDesktop,&bmpDesktop); 
		pSubMenu->SetMenuItemBitmaps(ID_TRAY_EXIT_UNSD_PA,MF_BYCOMMAND,&bmpExitUnSDPA,&bmpExitUnSDPA); 
		pSubMenu->SetMenuItemBitmaps(ID_TRAY_EXIT_SD_PA,MF_BYCOMMAND,&bmpExitSDPA,&bmpExitSDPA); 
		
		pSubMenu->TrackPopupMenu (TPM_LEFTALIGN, oPoint.x, oPoint.y, this); //在指定位置显示弹出菜单

	}else
	{
		// 双击消息
		if (IsIconic())
		{
//			ShowWindow(SW_SHOW);
			ShowWindow(SW_RESTORE); 
		}

		::SetForegroundWindow(m_hWnd);   
		
		//   将主窗的对话框激活   
		::SetForegroundWindow(::GetLastActivePopup(m_hWnd));   
//		::SetForegroundWindow(m_hWnd);   
//		::SetForegroundWindow(::GetLastActivePopup(m_hWnd));   

//		SetActiveWindow();
//		BringWindowToTop();

// 
// //  主窗口已最小化，则恢复其大小   
//   if   (::IsIconic(hWndPrevious))   
//   {   
//   ::ShowWindow(hWndPrevious,SW_RESTORE);   
//   }   
//     
//   //   将主窗激活   
//   ::SetForegroundWindow(hWndPrevious);   
//     
//   //   将主窗的对话框激活   
//   ::SetForegroundWindow(::GetLastActivePopup(hWndPrevious));   

	}
	
	return 1;
}



void CTestClientSrcDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
}

void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnOK();
//	CDialog::OnLButtonDown(nFlags, point);
}


void CTestClientSrcDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	SYSTEMTIME st;
	::GetLocalTime(&st);
	CString strDateTime;
	CString strDayOfWeek;
	switch (st.wDayOfWeek)
	{
	case 0:
		strDayOfWeek = _T("Sunday");
		break;
	case 1:
		strDayOfWeek = _T("Monday");
		break;
	case 2:
		strDayOfWeek = _T("Tuesday");
		break;
	case 3:
		strDayOfWeek = _T("Wednesday");
		break;
	case 4:
		strDayOfWeek = _T("Thursday");
		break;
	case 5:
		strDayOfWeek = _T("Friday");
		break;
	case 6:
		strDayOfWeek = _T("Saturday");
		break;
	default:
		strDayOfWeek = _T("Unknow day of week");
		break;
	}

	strDateTime.Format(_T("%04d-%02d-%02d\r\n%02d:%02d:%02d\r\n%s"),
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, strDayOfWeek);

	GetDlgItem(IDC_STATIC_DATE_TIME)->SetWindowText(strDateTime);
	CDialog::OnTimer(nIDEvent);
}





void CTestClientSrcDlg::OnButtonGenRegFile() 
{
	// TODO: Add your control notification handler code here
	wchar_t wcsModuleName[MAX_PATH];
	GetModuleFileName(NULL, wcsModuleName, MAX_PATH);

	CString strFileName;
	wchar_t* p = wcsrchr(wcsModuleName, _T('\\'));
	if (NULL != p)
	{
		strFileName = CString(wcsModuleName, p - wcsModuleName + 1) + _T("regP&A.bat");
		if (strFileName.GetLength() > MAX_PATH)
		{
			return;
		}
	}

	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = CreateFile(strFileName,           // open MYFILE.TXT 
					GENERIC_WRITE,              // open for reading 
					FILE_SHARE_READ,           // share for reading 
					NULL,                      // no security 
					CREATE_ALWAYS,             // existing file only 
					FILE_ATTRIBUTE_NORMAL,     // normal file 
					NULL);                     // no attr. template 

	if (hFile == INVALID_HANDLE_VALUE) 
	{
		AfxMessageBox(_T("error: CreateFile()"));
		return;
	}		

	char pFrameBuffer[] = "regsvr32 PAps.dll\r\nPrintingArchiving_ur.exe /regserver";
	DWORD dwBytesWritten = 0;
	if (!::WriteFile(hFile, pFrameBuffer, sizeof(pFrameBuffer), &dwBytesWritten, NULL))
	{
		AfxMessageBox(_T("error: WriteFile()"));
		CloseHandle(hFile);
		return;
	}

	CloseHandle(hFile);
	
	CString strMsg;
	strMsg.Format(_T("Succeed in creating P&A reg file: \r\n%s"), strFileName);
	AfxMessageBox(strMsg);
}

void CTestClientSrcDlg::UpdateJobQueue()
{
	m_enumJobMode = enumJobMode_Current;

	ClearJobQueue();
	vector<CString> vtrOldSelectedJobs = m_vtrSelectedJobs;

	JobInfo* pJobList = NULL;
	JobInfo* pJobInfo = NULL;
	long lJobCount = 0;
	HRESULT hResult =  CTestClientSrcDlg::m_pIPAGeneral->GetJobList(&pJobList, &lJobCount);
	if (S_OK == hResult)
	{
		if (0 == lJobCount)
		{
		}
		else
		{
			pJobInfo = pJobList;
			for (int i = 0; i < lJobCount; i++)
			{
				CString temp;
				LV_ITEM lvitemAdd;
				lvitemAdd.mask = LVIF_TEXT;
				lvitemAdd.iItem = m_listJobQueue.GetItemCount();
				lvitemAdd.iSubItem = 0;
				lvitemAdd.pszText = NULL;

				int iIndex = m_listJobQueue.InsertItem(&lvitemAdd);

				// 记录JobID
				JobItemInfo* pJobItem = new JobItemInfo;
				pJobItem->strJobID = _com_util::ConvertBSTRToString(pJobInfo->bsJobID);
				pJobItem->enumJobType = pJobInfo->enumType;
				m_listJobQueue.SetItemData(iIndex, (DWORD)pJobItem);
				
				// For Index
				temp = _com_util::ConvertBSTRToString(pJobInfo->bsIndex);
				m_listJobQueue.SetItemText(iIndex, 0, (LPCTSTR)temp);

				// For Type
				temp = _com_util::ConvertBSTRToString(pJobInfo->bsType);
				m_listJobQueue.SetItemText(iIndex, 1, (LPCTSTR)temp);

				// For Job SubmitedTime
				temp = _com_util::ConvertBSTRToString(pJobInfo->bsSubmitTime);
				m_listJobQueue.SetItemText(iIndex, 2, temp);


				// State
				temp = _com_util::ConvertBSTRToString(pJobInfo->bsState);
				m_listJobQueue.SetItemText(iIndex, 3, temp);

				// For Phase
				CString strJobPhase = _com_util::ConvertBSTRToString(pJobInfo->bsPhase);
				m_listJobQueue.SetItemText(iIndex, 4, strJobPhase);

				// For Progress
				CString strJobProgress = _com_util::ConvertBSTRToString(pJobInfo->bsProgress);
				m_listJobQueue.SetItemText(iIndex, 5, strJobProgress);

				// Job Detail
				CString strJobDetail = _com_util::ConvertBSTRToString(pJobInfo->bsDetail);
				m_listJobQueue.SetItemText(iIndex, 6, strJobDetail);

				//<< 选择状态
// 				for (int j = 0; j < vtrOldSelectedJobs.size(); j++)
// 				{
// 					if (!pstrJobID->Compare(vtrOldSelectedJobs[j]))
// 					{
// 						m_vtrSelectedJobs.push_back(vtrOldSelectedJobs[j]);
// 						m_listJobQueue.SetItem(iIndex, 0, LVIF_STATE, NULL, 0, LVIS_SELECTED,LVIS_SELECTED, 0);
// 						break;
// 					}
// 				}
				
				// Next Job
				pJobInfo++;
			}
		}
		
		if (pJobList)
			CoTaskMemFree(pJobList);
	}
	else
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPAGeneral->GetJobList"));
	}

}

void CTestClientSrcDlg::UpdateJobState(BSTR bsJobID, BSTR bsState)
{
	CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
	CString strState = CBSTROpt::BSTRToCString(bsState);

	int iCount = m_listJobQueue.GetItemCount();
	for (int i = 0; i < iCount; i++)
	{
		CString* pstrJobID = (CString*)m_listJobQueue.GetItemData(i);
		if (!pstrJobID->Compare(strJobID))
		{
			m_listJobQueue.SetItemText(i, 3, strState);
			return;
		}
		else
		{
			continue;
		}
	}
}

void CTestClientSrcDlg::UpdateJobPhase(BSTR bsJobID, BSTR bsPhase)
{
	CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
	CString strPhase = CBSTROpt::BSTRToCString(bsPhase);

	int iCount = m_listJobQueue.GetItemCount();
	for (int i = 0; i < iCount; i++)
	{
		CString* pstrJobID = (CString*)m_listJobQueue.GetItemData(i);
		if (!pstrJobID->Compare(strJobID))
		{
			m_listJobQueue.SetItemText(i, 4, strPhase);
			return;
		}
		else
		{
			continue;
		}
	}
}

void CTestClientSrcDlg::UpdateJobProgress(BSTR bsJobID, BSTR bsProgress)
{
	CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
	CString strProgress = CBSTROpt::BSTRToCString(bsProgress);

	int iCount = m_listJobQueue.GetItemCount();
	for (int i = 0; i < iCount; i++)
	{
		CString* pstrJobID = (CString*)m_listJobQueue.GetItemData(i);
		if (!pstrJobID->Compare(strJobID))
		{
			m_listJobQueue.SetItemText(i, 5, strProgress);
			return;
		}
		else
		{
			continue;
		}
	}
}

void CTestClientSrcDlg::UpdateJobDetail(JobDetailStruct* pJobDetail)
{
	CString strJobID = CBSTROpt::BSTRToCString(pJobDetail->bsJobID);
	CString strDetail = CBSTROpt::BSTRToCString(pJobDetail->bsDetail);

	int iCount = m_listJobQueue.GetItemCount();
	for (int i = 0; i < iCount; i++)
	{
		CString* pstrJobID = (CString*)m_listJobQueue.GetItemData(i);
		if (!pstrJobID->Compare(strJobID))
		{
			m_listJobQueue.SetItemText(i, 6, strDetail);
			return;
		}
		else
		{
			continue;
		}
	}
}

void CTestClientSrcDlg::ClearJobQueue()
{
	//<< 记录选择的items
	POSITION pos = m_listJobQueue.GetFirstSelectedItemPosition();
	while (pos)
	{
		
		int nItem = m_listJobQueue.GetNextSelectedItem(pos);
		JobItemInfo* pJobItem = (JobItemInfo*)m_listJobQueue.GetItemData(nItem);
		m_vtrSelectedJobs.push_back(pJobItem->strJobID);
	}

	///<
	int iCount = m_listJobQueue.GetItemCount();
	for (int i = 0; i < iCount; i++)
	{
		JobItemInfo* pJobItem = (JobItemInfo*)m_listJobQueue.GetItemData(i);
		delete pJobItem;
	}

	m_listJobQueue.DeleteAllItems();
}

void CTestClientSrcDlg::OnButtonMoveJobUp() 
{
	// TODO: Add your control notification handler code here
	if (enumJobMode_Current != m_enumJobMode)
	{
		AfxMessageBox(_T("No current jobs display!"));
		return;
	}

	POSITION pos = m_listJobQueue.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("No Job selected!"));
		return;
	}
	else
	{
		
		int nItem = m_listJobQueue.GetNextSelectedItem(pos);
		JobItemInfo* pJobItem = (JobItemInfo*)m_listJobQueue.GetItemData(nItem);

		BSTR bsJobIDs = pJobItem->strJobID.AllocSysString();

		HRESULT hResult = m_pIPAGeneral->MoveJob(bsJobIDs, TRUE);
		if (S_OK != hResult)
		{
			AfxMessageBox(_T("Error: m_pIPAGeneral->MoveJob(...)"));
		}
	}

}

void CTestClientSrcDlg::OnButtonMoveJobDown() 
{
	// TODO: Add your control notification handler code here
	if (enumJobMode_Current != m_enumJobMode)
	{
		AfxMessageBox(_T("No current jobs display!"));
		return;
	}

	POSITION pos = m_listJobQueue.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("No Job selected!"));
		return;
	}
	else
	{
		
		int nItem = m_listJobQueue.GetNextSelectedItem(pos);
		JobItemInfo* pJobItem = (JobItemInfo*)m_listJobQueue.GetItemData(nItem);

		BSTR bsJobIDs = pJobItem->strJobID.AllocSysString();

		HRESULT hResult = m_pIPAGeneral->MoveJob(bsJobIDs, FALSE);
		if (S_OK != hResult)
		{
			AfxMessageBox(_T("Error: m_pIPAGeneral->MoveJob(...)"));
		}
	}
}

void CTestClientSrcDlg::OnButtonCancelJob() 
{
	// TODO: Add your control notification handler code here
	if (enumJobMode_Current != m_enumJobMode)
	{
		AfxMessageBox(_T("No current jobs display!"));
		return;
	}

	POSITION pos = m_listJobQueue.GetFirstSelectedItemPosition();
	vector<CString> vtrJobs;

	if (pos == NULL)
	{
		AfxMessageBox(_T("No Job selected!"));
		return;
	}

	while (pos)
	{
		
		int nItem = m_listJobQueue.GetNextSelectedItem(pos);
		JobItemInfo* pJobItem = (JobItemInfo*)m_listJobQueue.GetItemData(nItem);
		vtrJobs.push_back(pJobItem->strJobID);
	}

	BSTR* pbsJobIDs = new BSTR[vtrJobs.size()];
	for (int i=0; i < vtrJobs.size(); i++)
	{
		*(pbsJobIDs+i) = vtrJobs[i].AllocSysString();
	}

	HRESULT hResult = m_pIPAGeneral->CancelJobs(pbsJobIDs, vtrJobs.size());
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("Error: m_pIPAGeneral->CancelJobs(...)"));
	}

	for (i=0; i < vtrJobs.size(); i++)
	{
		CBSTROpt::FreeBSTR(*(pbsJobIDs+i));
	}
	delete []pbsJobIDs;

}

void CTestClientSrcDlg::OnButtonDeleteJob() 
{
	// TODO: Add your control notification handler code here
	if (enumJobMode_Current != m_enumJobMode)
	{
		AfxMessageBox(_T("No current jobs display!"));
		return;
	}

	POSITION pos = m_listJobQueue.GetFirstSelectedItemPosition();
	vector<CString> vtrJobs;

	if (pos == NULL)
	{
		AfxMessageBox(_T("No Job selected!"));
		return;
	}

	while (pos)
	{
		
		int nItem = m_listJobQueue.GetNextSelectedItem(pos);
		JobItemInfo* pJobItem = (JobItemInfo*)m_listJobQueue.GetItemData(nItem);
		vtrJobs.push_back(pJobItem->strJobID);
	}

	BSTR* pbsJobIDs = new BSTR[vtrJobs.size()];
	for (int i=0; i < vtrJobs.size(); i++)
	{
		*(pbsJobIDs+i) = vtrJobs[i].AllocSysString();
	}

	HRESULT hResult = m_pIPAGeneral->DeleteJobs(pbsJobIDs, vtrJobs.size());
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("Error: m_pIPAGeneral->DeleteJobs(...)"));
	}

	for (i=0; i < vtrJobs.size(); i++)
	{
		CBSTROpt::FreeBSTR(*(pbsJobIDs+i));
	}
	delete []pbsJobIDs;
}

void CTestClientSrcDlg::OnButtonRefreshJob() 
{
	// TODO: Add your control notification handler code here
	UpdateJobQueue();
}

void CTestClientSrcDlg::OnDblclkListJobQueue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;


	if(pNMListView->iItem == -1)
	{
		return;
	}

	JobItemInfo* pJobItem = (JobItemInfo*)m_listJobQueue.GetItemData(pNMListView->iItem);
 	switch (pJobItem->enumJobType)
	{
	case enumJobType_AutoSendJob:
	case enumJobType_ManualSendJob:
		m_SendJObDetailDlg.SetJobMode(m_enumJobMode);
		m_SendJObDetailDlg.SetJob(pJobItem->strJobID);
		m_SendJObDetailDlg.DoModal();
		break;
	case enumJobType_BurnJob:
		m_BurnJObDetailDlg.SetJobMode(m_enumJobMode);
		m_BurnJObDetailDlg.SetJob(pJobItem->strJobID);
		m_BurnJObDetailDlg.DoModal();
		break;
	case enumJobType_DiscImportJob:
		m_ImportJObDetailDlg.SetJobMode(m_enumJobMode);
		m_ImportJObDetailDlg.SetJob(pJobItem->strJobID);
		m_ImportJObDetailDlg.DoModal();
		break;
	default:
		break;
	}

}

void CTestClientSrcDlg::OnButtonHistoryjobCount() 
{
	// TODO: Add your control notification handler code here
	DWORD dwCount = 0;
	HRESULT hr = m_pIPAGeneral->GetHistoryJobCount(&dwCount);
	if (S_OK != hr)
	{
		AfxMessageBox(_T("m_pIPAGeneral->GetHistoryJobCount(&dwCount)"));
		return;
	}

	CString strInfo;
	strInfo.Format(_T("%d"), dwCount);
	GetDlgItem(IDC_EDIT_HIS_JOB_COUNT)->SetWindowText(strInfo);

	if (dwCount > 0)
	{
		strInfo.Format(_T("%d"), 1);
		GetDlgItem(IDC_EDIT_HIS_JOB_START)->SetWindowText(strInfo);
		
		strInfo.Format(_T("%d"), dwCount);
		GetDlgItem(IDC_EDIT_HIS_JOB_END)->SetWindowText(strInfo);
		
	}
}

void CTestClientSrcDlg::UpdatePages(DWORD dwJobCount, DWORD dwJobCountPerPage)
{
	
}

void CTestClientSrcDlg::OnButtonHistoryjobGetJob() 
{
	// TODO: Add your control notification handler code here
	m_enumJobMode = enumJobMode_History;
	ClearJobQueue();

	TCHAR* pStopString = NULL;

	CString strInfo;
	GetDlgItem(IDC_EDIT_HIS_JOB_START)->GetWindowText(strInfo);
	DWORD dwStart = _tcstoul(strInfo, &pStopString, 10);

	GetDlgItem(IDC_EDIT_HIS_JOB_END)->GetWindowText(strInfo);
	DWORD dwEnd = _tcstoul(strInfo, &pStopString, 10);

	if (dwStart <= 0 || dwEnd-dwStart+1 <=0)
	{
		AfxMessageBox(_T("Query index error!"));
		return;
	}

	DWORD dwCount = dwEnd-dwStart+1;
	JobInfo* pJobs = NULL;
	if (S_OK != m_pIPAGeneral->GetHistoryJobs(dwStart, &dwCount, &pJobs))
	{
		AfxMessageBox(_T("m_pIPAGeneral->GetHistoryJobs()"));
		return;
	}


	JobInfo* pJobInfo = NULL;

	if (0 == dwCount)
	{
	}
	else
	{
		pJobInfo = pJobs;
		for (int i = 0; i < dwCount; i++)
		{
			CString temp;
			LV_ITEM lvitemAdd;
			lvitemAdd.mask = LVIF_TEXT;
			lvitemAdd.iItem = m_listJobQueue.GetItemCount();
			lvitemAdd.iSubItem = 0;
			lvitemAdd.pszText = NULL;

			int iIndex = m_listJobQueue.InsertItem(&lvitemAdd);

			// 记录JobID
			JobItemInfo* pJobItem = new JobItemInfo;
			pJobItem->strJobID = _com_util::ConvertBSTRToString(pJobInfo->bsJobID);
			pJobItem->enumJobType = pJobInfo->enumType;
			m_listJobQueue.SetItemData(iIndex, (DWORD)pJobItem);
			
			// For Index
			temp = _com_util::ConvertBSTRToString(pJobInfo->bsIndex);
			m_listJobQueue.SetItemText(iIndex, 0, (LPCTSTR)temp);

			// For Type
			temp = _com_util::ConvertBSTRToString(pJobInfo->bsType);
			m_listJobQueue.SetItemText(iIndex, 1, (LPCTSTR)temp);

			// For Job SubmitedTime
			temp = _com_util::ConvertBSTRToString(pJobInfo->bsSubmitTime);
			m_listJobQueue.SetItemText(iIndex, 2, temp);


			// State
			temp = _com_util::ConvertBSTRToString(pJobInfo->bsState);
			m_listJobQueue.SetItemText(iIndex, 3, temp);


			// For Progress
			CString strJobProgress = _com_util::ConvertBSTRToString(pJobInfo->bsProgress);
			m_listJobQueue.SetItemText(iIndex, 5, strJobProgress);


			// Next Job
			pJobInfo++;
		}
	}
	
	if (pJobs)
		CoTaskMemFree(pJobs);


}

void CTestClientSrcDlg::OnButtonHistoryjobGetJob2() 
{
	// TODO: Add your control notification handler code here
	if (enumJobMode_History != m_enumJobMode)
	{
		AfxMessageBox(_T("No history jobs display!"));
		return;
	}

	POSITION pos = m_listJobQueue.GetFirstSelectedItemPosition();
	vector<CString> vtrJobs;

	if (pos == NULL)
	{
		AfxMessageBox(_T("No Job selected!"));
		return;
	}

	while (pos)
	{
		
		int nItem = m_listJobQueue.GetNextSelectedItem(pos);
		JobItemInfo* pJobItem = (JobItemInfo*)m_listJobQueue.GetItemData(nItem);
		vtrJobs.push_back(pJobItem->strJobID);
	}

	BSTR* pbsJobIDs = new BSTR[vtrJobs.size()];
	for (int i=0; i < vtrJobs.size(); i++)
	{
		*(pbsJobIDs+i) = vtrJobs[i].AllocSysString();
	}

	HRESULT hResult = m_pIPAGeneral->DeleteHistoryJobs(vtrJobs.size(), pbsJobIDs);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("Error: m_pIPAGeneral->DeleteHistoryJobs(...)"));
	}
	else
	{
		OnButtonHistoryjobCount();
		AfxMessageBox(_T("The selected history jobs are deleted!"));
	}

	for (i=0; i < vtrJobs.size(); i++)
	{
		CBSTROpt::FreeBSTR(*(pbsJobIDs+i));
	}
	delete []pbsJobIDs;
}

void CTestClientSrcDlg::OnButtonHistoryjobGetJob3() 
{
	// TODO: Add your control notification handler code here
	if (enumJobMode_History != m_enumJobMode)
	{
		AfxMessageBox(_T("No history jobs display!"));
		return;
	}

	HRESULT hResult = m_pIPAGeneral->DeleteAllHistoryJobs();
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("Error: m_pIPAGeneral->DeleteAllHistoryJobs(...)"));
	}
	else
	{
		OnButtonHistoryjobCount();
		AfxMessageBox(_T("All history jobs are deleted!"));
	}
	
}

void CTestClientSrcDlg::OnPing() 
{
	// TODO: Add your control notification handler code here
	HRESULT hResult = m_pIPing->Ping();
	if (S_OK == hResult)
	{
		AfxMessageBox(_T("Ping OK"));
	}
	else
	{
		AfxMessageBox(_T("Failed"));
	}
}
