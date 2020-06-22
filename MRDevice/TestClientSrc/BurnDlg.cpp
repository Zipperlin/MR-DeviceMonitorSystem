// BurnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestClientSrc.h"
#include "BurnDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE g_hResourceInstance;

DWORD WINAPI CheckDeviceAndDiscStatusThreadProc(LPVOID lpParameter)
{
	CBurnDlg* pBurnDlg = (CBurnDlg*)lpParameter;

	pBurnDlg->CheckDeviceAndDiscStatus();

	return 0;
	
}

/////////////////////////////////////////////////////////////////////////////
// CBurnDlg dialog


CBurnDlg::CBurnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBurnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBurnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBurnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBurnDlg)
	DDX_Control(pDX, IDC_STATIC_BURN_PHASE, m_staticBurnPhase);
	DDX_Control(pDX, IDC_PROGRESS, m_progressBurn);
	DDX_Control(pDX, IDC_EDIT_MSG, m_editMessage);
	DDX_Control(pDX, IDC_LIST_DIR_FILE, m_listboxDirsAndFiles);
	DDX_Control(pDX, IDC_RADIO_DVD, m_ratioDiscTypeDVD);
	DDX_Control(pDX, IDC_COMBO_BURNSPEED, m_cbboxBurnSpeed);
	DDX_Control(pDX, IDC_RADIO_CD, m_ratioDiscTypeCD);
	DDX_Control(pDX, IDC_COMBO_DEVICE, m_cbboxDevices);
	DDX_Control(pDX, IDC_LIST_JOBLIST, m_CListJobList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBurnDlg, CDialog)
	//{{AFX_MSG_MAP(CBurnDlg)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonNeroapiinit)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE, OnSelchangeComboDevice)
	ON_BN_CLICKED(IDC_BUTTON_BURN, OnButtonBurn)
	ON_BN_CLICKED(IDC_BUTTON_ADD_FILES, OnButtonAddFiles)
	ON_BN_CLICKED(IDC_BUTTON_ADD_DIRS, OnButtonAddDirs)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnButtonErase)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_ABORT, OnButtonAbort)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_BURNBYPA, OnButtonBurnbypa)
	ON_BN_CLICKED(IDC_CHECK_DICOM, OnCheckDicom)
	ON_BN_CLICKED(IDC_CHECK_BMP, OnCheckBmp)
	ON_BN_CLICKED(IDC_CHECK_JPEG, OnCheckJpeg)
	ON_CBN_SELCHANGE(IDC_COMBO_DOWNSCALE, OnSelchangeComboDownscale)
	ON_BN_CLICKED(IDC_BUTTON_ADD_UID, OnButtonAddUid)
	ON_BN_CLICKED(IDC_BUTTON_DEL_UID, OnButtonDelUid)
	ON_CBN_SELCHANGE(IDC_COMBO_UID_TYPE, OnSelchangeComboUidType)
	ON_BN_CLICKED(IDC_BUTTON_CHECKDEVICE, OnButtonCheckdevice)
	ON_BN_CLICKED(IDC_BUTTON_UNCHECKDEVICE, OnButtonUncheckdevice)
	ON_BN_CLICKED(IDC_BUTTON_BURNPREPARE, OnButtonBurnprepare)
	ON_BN_CLICKED(IDC_BUTTON_CANCELBURNPREPARE, OnButtonCancelburnprepare)
	ON_CBN_SELCHANGE(IDC_COMBO_BURN_TYPE, OnSelchangeComboBurnType)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH_DEVICE_MEDIA_INFO, OnButtonRefreshDeviceMediaInfo)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_UID, OnButtonClearUid)
	ON_BN_CLICKED(IDC_BUTTON_DELJOB, OnButtonDelJob)	
	ON_BN_CLICKED(IDC_BUTTON_BURN_UNFINISHEDJOB, OnButtonBurnUnfinishedjob)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBurnDlg message handlers

void CBurnDlg::OnButtonNeroapiinit() 
{
//	// TODO: Add your control notification handler code here
//	// Make, set the dir and file buffer
//	DWORD dwBufferLen = sizeof(DWORD) + m_listboxDirsAndFiles.GetCount() * MAX_PATH;
//	char* pbuffer = new char[dwBufferLen];
//	char* p = pbuffer;
//
//	*(DWORD*)p = m_listboxDirsAndFiles.GetCount();
//	p += sizeof(DWORD);
//	
//	for (int i = 0; i < m_listboxDirsAndFiles.GetCount(); i++)
//	{
//		int iLen = m_listboxDirsAndFiles.GetText(i, p);
//		p += iLen + 1;
//	}
//
//	CTestClientSrcDlg::m_pIPABurn->SetBurnFiles((BYTE*)pbuffer, dwBufferLen);
//
//	// Set Burn media type
////	BurnMediaType enumBurnMediaType;
//	int iRatioCheckCD = m_ratioDiscTypeCD.GetCheck();
//	int iRatioCheckDVD = m_ratioDiscTypeDVD.GetCheck();
//	if ((BST_UNCHECKED == iRatioCheckCD) && (BST_CHECKED == iRatioCheckDVD))
//	{
//		// DVD
//		CTestClientSrcDlg::m_pIPABurn->SetBurnMedia(enumBurnMediaType_DVD);
//	}
//	else if ((BST_CHECKED == iRatioCheckCD) && (BST_UNCHECKED == iRatioCheckDVD))
//	{
//		// CD
//		CTestClientSrcDlg::m_pIPABurn->SetBurnMedia(enumBurnMediaType_CD);
//	}
//	else if ((BST_UNCHECKED == iRatioCheckCD) && (BST_UNCHECKED == iRatioCheckDVD))
//	{
//		// Unselected media type
////		AfxMessageBox(_T("Please select the disc type"));
////		return;
//	}
//	else
//	{
////		AfxMessageBox(_T("disc type select error!"));
////		return;
//	}
//
//	// set burn speed
//	int iIndex = m_cbboxBurnSpeed.GetCurSel();
//	if (-1 != iIndex)
//	{
//		DWORD* pdwBurnSpeedKBs = (DWORD*)m_cbboxBurnSpeed.GetItemDataPtr(iIndex);
//		CTestClientSrcDlg::m_pIPABurn->SetBurnSpeed(*pdwBurnSpeedKBs);
//	}
//
//	CString strDiscName;
//	GetDlgItem(IDC_EDIT_DISCNAME)->GetWindowText(strDiscName);
//	BSTR bsDiscName = strDiscName.AllocSysString();
//	CTestClientSrcDlg::m_pIPABurn->SetDiscName(bsDiscName);
//
//	UpdateDlgInfo();
}

BOOL CBurnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT_DISCNAME)->SetWindowText(_T("My Disc"));
	m_progressBurn.SetRange(0, 100);

//	WORKSTATE ws;
//	while (TRUE)
//	{
//		if (NULL != CTestClientSrcDlg::m_pIGenaralInterface &&
//			S_OK == CTestClientSrcDlg::m_pIGenaralInterface->GetWorkState(&ws))
//		{
//			if (enumWORKSTATE_READY == ws ||
//				enumWORKSTATE_WORKING == ws ||
//				enumWORKSTATE_ERROR == ws)
//			{
//				break;
//			}
//			else
//				Sleep(100);
//		}
//		else
//			Sleep(100);
//	}
//	UpdateDlgInfo();
//	m_progressBurn.SetPos(60);

	// Init DLG
	m_vtrPatientUIDs.push_back(_T("0720070125112419640"));
// 	m_vtrStudyUIDs.push_back(_T("0520070125124552937"));
	m_vtrStudyUIDs.push_back(_T("0520070125124552937"));
	m_vtrSeriesUIDs.push_back(_T("0620070411171826751"));

	((CComboBox*)GetDlgItem(IDC_COMBO_UID_TYPE))->SetCurSel(2);
	((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->AddString(m_vtrSeriesUIDs[0]);
//	((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->SetExtendedStyle(((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->GetExtendedStyle() | LVS_EX_SIMPLESELECT);

	// Set BackUp
	((CComboBox*)GetDlgItem(IDC_COMBO_BURN_TYPE))->SetCurSel(1);

	((CButton*)GetDlgItem(IDC_CHECK_DICOM))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_DICOM))->EnableWindow(FALSE);
	((CComboBox*)GetDlgItem(IDC_COMBO_DOWNSCALE))->SetCurSel(1);
	((CComboBox*)GetDlgItem(IDC_COMBO_DOWNSCALE))->EnableWindow(TRUE);

	((CButton*)GetDlgItem(IDC_CHECK_BMP))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_BMP))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_JPEG))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_JPEG))->EnableWindow(TRUE);
	

	m_CListJobList.SetExtendedStyle(m_CListJobList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_CListJobList.InsertColumn(0, _T("JobID"), LVCFMT_CENTER, 150);
	m_CListJobList.InsertColumn(1, _T("State"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(2, _T("Phase"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(3, _T("Progress"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(4, _T("Detail"), LVCFMT_LEFT, 300);

	m_BurnPatientInfoDlg.Create(CBurnPatientInfo::IDD, this);

	m_cbboxBurnSpeed.ResetContent();
	int iIndex = m_cbboxBurnSpeed.AddString(_T("Max Speed"));
	m_cbboxBurnSpeed.SetItemData(iIndex, (DWORD)0xffffffff);
	iIndex = m_cbboxBurnSpeed.AddString(_T("Min Speed"));
	m_cbboxBurnSpeed.SetItemData(iIndex, (DWORD)0);
	m_cbboxBurnSpeed.SetCurSel(0);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBurnDlg::Init()
{

	char* pDevicebuffer = NULL;
	long lLen;

	m_cbboxDevices.ResetContent();

	BSTR* pDevices = NULL;
	HRESULT hResult = CTestClientSrcDlg::m_pIPABurn->GetDevices(&pDevices, &lLen);
	if (S_OK != hResult)
		return;
	

	for (DWORD i = 0; i < lLen; i++)
	{
		CString strDeviceName = CBSTROpt::BSTRToCString(pDevices[i]);
		m_cbboxDevices.AddString(strDeviceName);
	}
	CoTaskMemFree(pDevices);
	m_cbboxDevices.SetCurSel(0);

	OnSelchangeComboDevice();

//	UpdataEstimatedSize();
//	m_hCheckDeviceAndDiscStatusEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
//	m_hCheckDeviceAndDiscStatusThread = CreateThread(NULL, 0, CheckDeviceAndDiscStatusThreadProc, this, 0, NULL);
	
}

void CBurnDlg::OnSelchangeComboDevice() 
{
	// TODO: Add your control notification handler code here
	CString strDeviceName;

	int iIndex = m_cbboxDevices.GetCurSel();
	if (-1 == iIndex)
		return;
	
	m_cbboxDevices.GetLBText(iIndex, strDeviceName);

//	if (strDeviceName.IsEmpty())
//		return;

	BSTR bsDeviceName = strDeviceName.AllocSysString();
	CTestClientSrcDlg::m_pIPABurn->SetBurnDevice(bsDeviceName);

// 	UpdateDlgInfo();
}

void CBurnDlg::OnButtonBurn() 
{
	// TODO: Add your control notification handler code here

	if (NULL == CTestClientSrcDlg::m_pIPABurn)
		return;

	BurnJobSettings bjs;

	// device
	CString strDeviceName;
	int icbboxSelIndex = m_cbboxDevices.GetCurSel();
	if (-1 == icbboxSelIndex)
	{
		AfxMessageBox(_T("please select a device"));
		return;
	}
	else
		m_cbboxDevices.GetLBText(icbboxSelIndex, strDeviceName);

	bjs.bsDeviceName = strDeviceName.AllocSysString();


	// Set Burn media type
//  	bjs.enumBurnMediaType = enumBurnMediaType_UnSet;

// 	int iRatioCheckCD = m_ratioDiscTypeCD.GetCheck();
// 	int iRatioCheckDVD = m_ratioDiscTypeDVD.GetCheck();
// 	if ((BST_UNCHECKED == iRatioCheckCD) && (BST_CHECKED == iRatioCheckDVD))
// 	{
// 		// DVD
// 		bjs.enumBurnMediaType = enumBurnMediaType_DVD;
// 	}
// 	else if ((BST_CHECKED == iRatioCheckCD) && (BST_UNCHECKED == iRatioCheckDVD))
// 	{
// 		// CD
// 		bjs.enumBurnMediaType = enumBurnMediaType_CD;
// 	}
// 	else if ((BST_UNCHECKED == iRatioCheckCD) && (BST_UNCHECKED == iRatioCheckDVD))
// 	{
// 		// Unselected media type
// 		AfxMessageBox(_T("Please select the disc type"));
// 		return;
// 	}
// 	else
// 	{
// 		AfxMessageBox(_T("disc type select error!"));
// 		return;
// 	}

	// set burn speed
	int iIndex = m_cbboxBurnSpeed.GetCurSel();
	if (-1 != iIndex)
	{
		DWORD* pdwBurnSpeedKBs = (DWORD*)m_cbboxBurnSpeed.GetItemDataPtr(iIndex);
		bjs.lBurnSpeed = *pdwBurnSpeedKBs;
	}

	// disc name
	CString strDiscName;
	GetDlgItem(IDC_EDIT_DISCNAME)->GetWindowText(strDiscName);
// 	bjs.bsDiscName = strDiscName.AllocSysString();

	bjs.enumFileSelection = enumFileSelection_CurrentRun;
	bjs.enumImageSelection = enumImageSelection_All;
	bjs.enumDownscaleCriterion = enumDownscaleCriterion_1024_12_16;

//	if (S_OK ==CTestClientSrcDlg::m_pIPABurn->Burn(&bjs))
	{
//		UpdateJobList();
	}

}

void CBurnDlg::OnButtonAddFiles() 
{
	// TODO: Add your control notification handler code here
	// browse for the DICOM file that is supposed to be burned on CD

	// provide information about the file type that we want to open

	static TCHAR BASED_CODE szFilter[] = _T("All Files (*.*)|*.*|DICOM Files (*.dic)|*.dic||");

	// create a CFileDialog object. 
	// usage : CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL,
	//  					DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL,
	//  					CWnd* pParentWnd = NULL );
	//
	// bOpenFileDialog = TRUE, create a File Open dialog 
	// lpszDefExt = NULL, do not automatically append a file extension
	// dwFlags = OFN_FILEMUSTEXIST, only accepts file names for files that are present
	// szFilter = "MP3 Files (*.mp3)|*.mp3|All Files (*.*)|*.*||"
	// pParentWnd = this, our current Dialog window is the parent

	CFileDialog dlgOpen(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, szFilter, this);

	// do nothing if IDCANCEL is returned

	CString strPathName;
	CString strFileName;
	
	if (dlgOpen.DoModal() == IDOK)
	{
		// retrieve and display the selected file name
		strPathName = dlgOpen.GetPathName();
		strFileName = dlgOpen.GetFileName();	


		m_listboxDirsAndFiles.AddString(strPathName);//·µ»ØItemListµÄindexÖµ



	}
	
}

void CBurnDlg::OnButtonAddDirs() 
{
	// TODO: Add your control notification handler code here
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
		m_listboxDirsAndFiles.AddString(strDir);
	}   	
}

void CBurnDlg::CheckDeviceAndDiscStatus()
{
// 	DeviceInfo deviceinfoCurrent;
// 	DiscInfo discinfoCurrent;
// 	while (TRUE)
// 	{
// 		DWORD dwRet =  WaitForSingleObject(m_hCheckDeviceAndDiscStatusEvent, 1000);
// 		if (WAIT_OBJECT_0 == dwRet)
// 		{
// 			return;
// 		}
// 		else if (WAIT_TIMEOUT == dwRet)
// 		{
// 			// time to check
// //			CTestClientSrcDlg::m_pIPABurn->GetDeviceInfo(&deviceinfoCurrent);
// //			CTestClientSrcDlg::m_pIPABurn->GetDiscInfo(&discinfoCurrent);
// 			
// 			if (!CompareDeviceInfo(&m_DeviceInfo, &deviceinfoCurrent) ||
// 				0 != memcmp(&m_DiscInfo, &discinfoCurrent, sizeof(DiscInfo)))
// 			{
// 				memcpy(&m_DeviceInfo, &deviceinfoCurrent, sizeof(DeviceInfo));
// 				memcpy(&m_DiscInfo, &deviceinfoCurrent, sizeof(DeviceInfo));
// 				UpdateDlgInfo();
// 			}
// 		}
// 	}
	

}

void CBurnDlg::UpdateDlgInfo()
{

	CString strMessageToShow;
//	CTestClientSrcDlg::m_pIPABurnSetting->GetDeviceInfo(&m_DeviceInfo);
//	CTestClientSrcDlg::m_pIPABurnSetting->GetDiscInfo(&m_DiscInfo);
// 	if (S_FALSE == CTestClientSrcDlg::m_pIPABurn->GetDeviceDiscInfo(&m_DeviceDiscInfo))
// 		return;

//	CTestClientSrcDlg::m_pIPABurn->GetBurnSettings(&m_BurnSettins);

	// disc type ratio and burn speed set
//	m_ratioDiscTypeCD.SetCheck(BST_UNCHECKED);
//	m_ratioDiscTypeDVD.SetCheck(BST_UNCHECKED);
//	m_ratioDiscTypeCD.EnableWindow(FALSE);
//	m_ratioDiscTypeDVD.EnableWindow(FALSE);

	m_cbboxBurnSpeed.ResetContent();
	m_vtrBurnSpeed.clear();

	strMessageToShow = _T("Device Info:\r\n");
// 	if (m_DeviceDiscInfo.bDeviceValid)
// 	{
// 		strMessageToShow += _T("recordable disc:");
// 
// 		CString strDeviceSupportedMediaType = _com_util::ConvertBSTRToString(m_DeviceDiscInfo.bsDeviceSupportedMediaType);
// 		strMessageToShow += strDeviceSupportedMediaType;
// //		if (m_DeviceInfo.bCanWriteCD)
// //		{
// ////			m_ratioDiscTypeCD.EnableWindow(TRUE);
// //			strMessageToShow += _T(" CD");
// //		}
// //		else
// //		{
// //// 			m_ratioDiscTypeCD.EnableWindow(FALSE);
// //		}
// //
// //		if (m_DeviceInfo.bCanWriteDVD)
// //		{
// //// 			m_ratioDiscTypeDVD.EnableWindow(TRUE);
// //			strMessageToShow += _T(", DVD");
// //		}
// //		else
// //		{
// //// 			m_ratioDiscTypeDVD.EnableWindow(FALSE);
// //		}
// 		DWORD i = 0;
// 		for (; i < m_DeviceDiscInfo.dwDeviceWriteSupportedSpeedsNum; i++)
// 		{
// 			CString strBurnSpeed;
// 			if (m_DeviceDiscInfo.dwDeviceWriteBaseSpeedKBs != 0)
// 			{
// 				if (0 == m_DeviceDiscInfo.dwDeviceWriteSupportedSpeedsKBs[i] % m_DeviceDiscInfo.dwDeviceWriteBaseSpeedKBs)
// 				{
// 					strBurnSpeed.Format(_T("%dx (%dKB/s)"), m_DeviceDiscInfo.dwDeviceWriteSupportedSpeedsKBs[i]/m_DeviceDiscInfo.dwDeviceWriteBaseSpeedKBs, m_DeviceDiscInfo.dwDeviceWriteSupportedSpeedsKBs[i]);
// 				}
// 				else
// 				{
// 					strBurnSpeed.Format(_T("%.1fx (%dKB/s)"), (double)m_DeviceDiscInfo.dwDeviceWriteSupportedSpeedsKBs[i]/m_DeviceDiscInfo.dwDeviceWriteBaseSpeedKBs, m_DeviceDiscInfo.dwDeviceWriteSupportedSpeedsKBs[i]);
// 				}
// 				m_vtrBurnSpeed.push_back(m_DeviceDiscInfo.dwDeviceWriteSupportedSpeedsKBs[i]);
// 			}
// 			else
// 			{
// 				strBurnSpeed.Format(_T("%dKB/s"), m_DeviceDiscInfo.dwDeviceWriteSupportedSpeeds[i]);
// 				m_vtrBurnSpeed.push_back(m_DeviceDiscInfo.dwDeviceWriteSupportedSpeeds[i]);
// 			}
// 
// 
// 			m_cbboxBurnSpeed.AddString(strBurnSpeed);
// 			m_cbboxBurnSpeed.SetItemDataPtr(i, &m_vtrBurnSpeed[i]);
// 		}
// 		if (0 == i)
// 		{
// 			m_vtrBurnSpeed.push_back(0);
// 			m_cbboxBurnSpeed.AddString(_T("MinSpeed"));
// 
// 			m_vtrBurnSpeed.push_back(MAXDWORD);
// 			m_cbboxBurnSpeed.AddString(_T("MaxSpeed"));
// 
// 			m_cbboxBurnSpeed.SetItemDataPtr(0, &m_vtrBurnSpeed[0]);
// 		}
// 		m_cbboxBurnSpeed.SetCurSel(0);
// 	}
// 	else
// 	{
// 		strMessageToShow += _T("invalid device");
// 	}

	// disc info
// 	strMessageToShow += _T("\r\n\r\nDisc info:");
// 
// 	strMessageToShow += _T("\r\ndisc type:");
// 	if (m_DiscInfo.bValidDisc)
// 	{
// //		switch (m_DiscInfo.enumBurnMediaType)
// //		{
// //		case enumBurnMediaType_CD:
// //			strMessageToShow += " CD";
// //				break;
// //		case enumBurnMediaType_DVD:
// //			strMessageToShow += " DVD";
// //				break;
// //		default:
// //			strMessageToShow += " Unknow";
// //			break;
// //		}
// 		CString strDiscMediaType = _com_util::ConvertBSTRToString(m_DeviceDiscInfo.bsDiscMediaType);
// 		strMessageToShow += strDiscMediaType;
// 
// 		strMessageToShow += _T("\r\nempty disc:");
// 		if (m_DeviceDiscInfo.bDiscEmpty)
// 		{
// 			strMessageToShow += _T(" yes");
// 
// 			strMessageToShow += _T("\r\ncapacity:");
// 			
// 			CString strCapacity;
// 			_int64 i64 = m_DeviceDiscInfo.dwDiscBlockSizeInByte;
// 			i64 = i64*m_DeviceDiscInfo.dwDiscFreeBlockNum/1024/1024;
// 
// 			strCapacity.Format(_T(" %dM"), i64);
// 			strMessageToShow += strCapacity;
// 		}
// 		else
// 			strMessageToShow += _T(" no");
// 
// 		strMessageToShow += _T("\r\nwritable:");
// 		if (m_DeviceDiscInfo.bDiscWritable)
// 		{
// 			strMessageToShow += _T(" yes");
// 			
// 		}
// 		else
// 			strMessageToShow += _T(" no");
// 	}
// 	else
// 	{
// 		// no disc in device
// 		m_vtrBurnSpeed.push_back(0);
// 
// 		m_cbboxBurnSpeed.AddString(_T("MaxSpeed"));
// 		m_cbboxBurnSpeed.SetItemDataPtr(0, &m_vtrBurnSpeed[0]);
// 
// 		strMessageToShow += _T("\r\nno disc or disc corrupted");
// 	}


	// disc capacity
//  	if (!m_DeviceDiscInfo.bDiscValid || !m_DeviceDiscInfo.bDiscEmpty)
// 	{
// 		GetDlgItem(IDC_EDIT_DISC_CAPACITY)->SetWindowText(_T("No Empty Disc"));
// 	}
// 	else
// 	{
// 		CString strCapacity;
// 		__int64 i64Capacity = m_DeviceDiscInfo.dwDiscBlockSizeInByte;
// 		i64Capacity = (0.92 * i64Capacity) * m_DeviceDiscInfo.dwDiscFreeBlockNum / 1024/ 1024;
// 
// 		strCapacity.Format(_T("%d M"), i64Capacity);
// 
// 		GetDlgItem(IDC_EDIT_DISC_CAPACITY)->SetWindowText(strCapacity);
// 	}


	// burn settings
// 	strMessageToShow += _T("\r\n\r\nBurn Settings:");
// 
// 	strMessageToShow += _T("\r\nDevice:");
// 	CString strDeviceName = _com_util::ConvertBSTRToString(m_BurnSettins.bsDeviceName);
// 	if (strDeviceName.IsEmpty())
// 	{
// 		strMessageToShow += _T("unset");
// 	}
// 	else
// 	{
// 		strMessageToShow += strDeviceName;
// 	}
// 
// 	strMessageToShow += _T("\r\ndisc name:");
// 	CString strDiscName = _com_util::ConvertBSTRToString(m_BurnSettins.bsDiscName);
// 	if (strDiscName.IsEmpty())
// 	{
// 		strMessageToShow += _T("unset");
// 	}
// 	else
// 	{
// 		strMessageToShow += strDiscName;
// 	}
// 
// 	strMessageToShow += _T("\r\nBurn speed:");
// 	if (MAXDWORD == m_BurnSettins.dwBurnSpeed)
// 	{
// 		strMessageToShow += _T("unset");
// 	}
// 	else
// 	{
// 		CString strBurnSpeed;
// 		strBurnSpeed.Format(_T("%d KB/s"), m_BurnSettins.dwBurnSpeed);
// 		strMessageToShow += strBurnSpeed;
// 	}
// 
// 	strMessageToShow += _T("\r\ndisc type:");
// 	if (enumBurnMediaType_UnSet == m_BurnSettins.enumBurnMediaType)
// 	{
// 		strMessageToShow += _T("unset");
// 	}
// 	else if (enumBurnMediaType_CD == m_BurnSettins.enumBurnMediaType)
// 	{
// 		strMessageToShow += _T("CD");
// 	}
// 	else if (enumBurnMediaType_DVD == m_BurnSettins.enumBurnMediaType)
// 	{
// 		strMessageToShow += _T("DVD");
// 	}
// 
// 	strMessageToShow += _T("\r\nFile info:");
// 	if (!m_BurnSettins.bFilesSet)
// 	{
// 		strMessageToShow += _T("unset");
// 	}
// 	else
// 	{
// 		strMessageToShow += _T("\r\nfile count:");
// 		CString strFileCount;
// 		strFileCount.Format(_T("%d"), m_BurnSettins.dwFileCount);
// 		strMessageToShow += strFileCount;
// 
// 		strMessageToShow += _T("\r\nfile size:");
// 		__int64 i64FileSize = (m_BurnSettins.dwTotalFileSizeHighPart*((__int64)MAXDWORD+1) + m_BurnSettins.dwTotalFileSizeLowPart)/1024/1024;
// 		CString strFileSize;
// 		strFileSize.Format(_T("%dM"), i64FileSize);
// 		strMessageToShow += strFileSize;
// 
// 
// 	}
// 
// 	m_editMessage.SetWindowText(strMessageToShow);

}

void CBurnDlg::UpdateJobList()
{
// 	m_CListJobList.DeleteAllItems();
// 	JobInfo* pJobList = NULL;
// 	JobInfo* pJobInfo = NULL;
// 	long lJobCount = 0;
// 	HRESULT hResult =  CTestClientSrcDlg::m_pIPABurn->GetBurnJobList(&pJobList, &lJobCount);
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
// 		if (pJobList)
// 			CoTaskMemFree(pJobList);
// 	}
// 
}



// BOOL CBurnDlg::CompareDeviceInfo(DeviceInfo* pDeviceInfoFormer, DeviceInfo* pDeviceInfoLatter)
// {
// 
// 	if (pDeviceInfoFormer->bValidDevice != pDeviceInfoLatter->bValidDevice)
// 		return FALSE;
// 
// 	CString strFormerDeviceName = _com_util::ConvertBSTRToString(pDeviceInfoFormer->bsDeviceName);
// 	CString strLatterDeviceName = _com_util::ConvertBSTRToString(pDeviceInfoLatter->bsDeviceName);
// 	int iRet = strFormerDeviceName.Compare(strLatterDeviceName);
// 	if (0 != iRet)
// 		return FALSE;
// 
// 	if (pDeviceInfoFormer->bCanWriteCD != pDeviceInfoLatter->bCanWriteCD)
// 		return FALSE;
// 
// 	if (pDeviceInfoFormer->bCanWriteDVD != pDeviceInfoLatter->bCanWriteDVD)
// 		return FALSE;
// 
// 	if (pDeviceInfoFormer->dwWriteSupportedSpeedsNum != pDeviceInfoLatter->dwWriteSupportedSpeedsNum)
// 		return FALSE;
// 	
// 	if (pDeviceInfoFormer->dwWriteBaseSpeedKBs != pDeviceInfoLatter->dwWriteBaseSpeedKBs)
// 		return FALSE;
// 
// 	iRet = memcmp(pDeviceInfoFormer->dwWriteSupportedSpeedsKBs, pDeviceInfoLatter->dwWriteSupportedSpeedsKBs, sizeof(DWORD)*64);
// 	if (0 != iRet)
// 		return FALSE;
// 	
// 	iRet = memcmp(pDeviceInfoFormer->dwWriteSupportedSpeeds, pDeviceInfoLatter->dwWriteSupportedSpeeds, sizeof(DWORD)*64);
// 	if (0 != iRet)
// 		return FALSE;
// 
// 	return TRUE;
// 
// }

void CBurnDlg::OnButtonErase() 
{
	// TODO: Add your control notification handler code here
	
}

void CBurnDlg::OnButtonPause() 
{
	// TODO: Add your control notification handler code here
	
}

void CBurnDlg::OnButtonAbort() 
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
// 		CTestClientSrcDlg::m_pIPABurn->CancelBurnJob(bsJobID);
	}
	
}

void CBurnDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	int sel=m_listboxDirsAndFiles.GetCurSel();
	m_listboxDirsAndFiles.DeleteString(sel);
	
}

void CBurnDlg::OnButtonDelJob()
{
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

// 		CTestClientSrcDlg::m_pIPABurn->DeleteBurnJob(bsJobID);

//		UpdateJobList();
	}
}


void CBurnDlg::SetJobState(LPCTSTR szJobID, JobState enumJobState)
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


void CBurnDlg::SetJobPhase(LPCTSTR szJobID, LPCTSTR szJobPhase)
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

void CBurnDlg::SetJobProgress(JobProgressStruct* pJobProgressStruct)
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

void CBurnDlg::SetJobDetail(JobDetailStruct* pJobDetailStruct)
{
// 	CString strDstJobID = _com_util::ConvertBSTRToString(pJobDetailStruct->bsJobID);
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

void CBurnDlg::ShowPatientInfo(long lItemNum, BurnPatientInfoStruct* pBurnPatientList)
{
	m_BurnPatientInfoDlg.SetPatientInfo(lItemNum, pBurnPatientList);
	m_BurnPatientInfoDlg.ShowWindow(SW_SHOW);
	
	UpdataEstimatedSize();
}

void CBurnDlg::ShowStudyInfo(long lItemNum, BurnStudyInfoStruct* pBurnStudyList)
{
	m_BurnPatientInfoDlg.ShowWindow(SW_SHOW);
	m_BurnPatientInfoDlg.SetStudyInfo(lItemNum, pBurnStudyList);
	UpdataEstimatedSize();

}

void CBurnDlg::ShowSeriesInfo(long lItemNum, BurnSeriesInfoStruct* pBurnSeriesList)
{
	m_BurnPatientInfoDlg.ShowWindow(SW_SHOW);
	m_BurnPatientInfoDlg.SetSeriesInfo(lItemNum, pBurnSeriesList);
	UpdataEstimatedSize();

}

void CBurnDlg::ShowImageInfo(long lItemNum, BurnImageInfoStruct* pBurnImageList)
{
	m_BurnPatientInfoDlg.ShowWindow(SW_SHOW);
	m_BurnPatientInfoDlg.SetImageInfo(lItemNum, pBurnImageList);
	UpdataEstimatedSize();
}

void CBurnDlg::ShowContentSize(unsigned long ulSizeInMega)
{
		CString strEstimatedSize;
		strEstimatedSize.Format(_T("%d M"), ulSizeInMega);
		((CEdit*)GetDlgItem(IDC_EDIT_ESTIMATEDSIZE))->SetWindowText(strEstimatedSize);
}

void CBurnDlg::OnButtonBurnbypa() 
{
	// TODO: Add your control notification handler code here

// 	OnButtonUncheckdevice();
	
	BurnJobSettingsByPA bjs;
	if (!GetBurnJobSettings(&bjs))
		return;

// 	long lUIDNum = 0;
// 	BSTR* pbsUIDList = NULL;
// 	PatientAdminUIDType enumPAUIDType = enumPatientAdminUIDType_Unknow;
// 	if (!GetBurnUIDTypeAndList(&lUIDNum, &pbsUIDList, &enumPAUIDType))
// 		return;

	if (S_OK !=CTestClientSrcDlg::m_pIPABurn->BurnByPA(&bjs))
	{
		AfxMessageBox(_T("m_pIPABurn->BurnByPA"));
	}

// 	if (pbsUIDList)
// 		delete [] pbsUIDList;
// 
	
}

BOOL CBurnDlg::GetBurnJobSettings(BurnJobSettingsByPA* pbjs)
{
// 	switch (((CComboBox*)GetDlgItem(IDC_COMBO_BURN_TYPE))->GetCurSel())
// 	{
// 		case 0:
// 			pbjs->enumBurnJobType = enumBurnJobType_BackUp;
// 			break;
// 		case 1:
// 			pbjs->enumBurnJobType = enumBurnJobType_Export;
// 			break;
// 		default:
// 			return FALSE;
// 	}
// 
// 	pbjs->bRaw = (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_BURN_DICOM_RAW))->GetCheck()) ? TRUE : FALSE;
// 	pbjs->bProcessed = (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_BURN_DICOM_PROC))->GetCheck()) ? TRUE : FALSE;
// 

// 	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_DICOM))->GetCheck())
// 	{
// 		pbjs->bDICOM = TRUE;
// 		
// 		switch (((CComboBox*)GetDlgItem(IDC_COMBO_DOWNSCALE))->GetCurSel())
// 		{
// 		case 0:
// 			pbjs->enumDownscaleCriterion = enumDownscaleCriterion_512_8_8;
// 			break;
// 		case 1:
// 			pbjs->enumDownscaleCriterion = enumDownscaleCriterion_1024_12_16;
// 			break;
// 		default:
// 			return FALSE;
// 		}
// 	}
// 	else
// 	{
// 		pbjs->bDICOM = FALSE;
// 		pbjs->enumDownscaleCriterion = enumDownscaleCriterion_Unknow;
// 	}
// 
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_BMP))->GetCheck())
	{
		pbjs->bBMP = TRUE;
	}
	else
	{
		pbjs->bBMP = FALSE;
	}

	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_JPEG))->GetCheck())
	{
		pbjs->bJPEG = TRUE;
	}
	else
	{
		pbjs->bJPEG = FALSE;
	}
// 
// 	// device
// 	CString strDeviceName;
// 	int icbboxSelIndex = m_cbboxDevices.GetCurSel();
// 	if (-1 == icbboxSelIndex)
// 	{
// 		strDeviceName = _T("Test");
// //		return FALSE;
// 	}
// 	else
// 		m_cbboxDevices.GetLBText(icbboxSelIndex, strDeviceName);
// 
// 	pbjs->bsDeviceName = strDeviceName.AllocSysString();

	// set burn speed
	int iIndex = m_cbboxBurnSpeed.GetCurSel();
	if (-1 != iIndex)
	{
		pbjs->lBurnSpeed = (LONG)m_cbboxBurnSpeed.GetItemData(iIndex);
	}
	else
		return FALSE;


	return TRUE;
}

BOOL CBurnDlg::GetBurnUIDTypeAndList(long* plUIDNum, BSTR** ppbsUIDList, PatientAdminUIDType* penumUIDType)
{
	*plUIDNum = ((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->GetCount();

// 	if (0 == *plUIDNum)
// 	{
// 		*ppszUIDList = new LPCTSTR[1];
// 		(*ppszUIDList)[0] = new TCHAR[16];
// 		memcpy((void*)(*ppszUIDList)[0], _T("1"), sizeof(TCHAR));
// 
// 	}
// 	else
// 	{
// 		*ppszUIDList = new LPCTSTR[*plUIDNum];
// 
// 		for (int i = 0; i < *plUIDNum; i++)
// 		{
// 			(*ppszUIDList)[i] = new TCHAR[16];
// 			CString strUID;
// 			((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->GetText(i, strUID);
// 			memcpy((void*)(*ppszUIDList)[0], (LPCTSTR)strUID, strUID.GetLength()*sizeof(TCHAR));
// 		}
// 	}

	if (0 == *plUIDNum)
	{
		AfxMessageBox(_T("Plz input UID!"));
		return FALSE;

	}
	else
	{
		*ppbsUIDList = new BSTR[*plUIDNum];

		for (int i = 0; i < *plUIDNum; i++)
		{
			CString strUID;
			((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->GetText(i, strUID);
			(*ppbsUIDList)[i] = strUID.AllocSysString();
		}
	}

	switch (((CComboBox*)GetDlgItem(IDC_COMBO_UID_TYPE))->GetCurSel())
	{
	case 0:
		*penumUIDType = enumPatientAdminUIDType_Patient;
		break;
	case 1:
		*penumUIDType = enumPatientAdminUIDType_Study;
		break;
	case 2:
		*penumUIDType = enumPatientAdminUIDType_Series;
		break;
	case 3:
		*penumUIDType = enumPatientAdminUIDType_Image;
		break;
	default:
		delete []*ppbsUIDList;
		return FALSE;
	}

	return TRUE;
}

void CBurnDlg::OnCheckDicom() 
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_DICOM))->GetCheck())
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_DOWNSCALE))->EnableWindow(TRUE);
	}
	else
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_DOWNSCALE))->EnableWindow(FALSE);
	}

	/*UpdataEstimatedSize();*/
}

void CBurnDlg::UpdataEstimatedSize()
{

	BOOL bBMP = BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_BMP))->GetCheck() ? TRUE : FALSE;
	BOOL bJPEG = BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_JPEG))->GetCheck() ? TRUE : FALSE;

	unsigned long dwEstimatedSize = 0;
	if (S_OK !=CTestClientSrcDlg::m_pIPABurn->GetEstimatedSize(bBMP, bJPEG, &dwEstimatedSize))
	{
		AfxMessageBox(_T("m_pIPABurn->GetEstimateSize"));
	}
	else
	{
		CString strEstimatedSize;
		strEstimatedSize.Format(_T("%d M"), dwEstimatedSize);
		((CEdit*)GetDlgItem(IDC_EDIT_ESTIMATEDSIZE))->SetWindowText(strEstimatedSize);
	}

}

void CBurnDlg::OnCheckBmp() 
{
	// TODO: Add your control notification handler code here
	UpdataEstimatedSize();
}

void CBurnDlg::OnCheckJpeg() 
{
	// TODO: Add your control notification handler code here
	UpdataEstimatedSize();
}

void CBurnDlg::OnSelchangeComboDownscale() 
{
	// TODO: Add your control notification handler code here
	/*UpdataEstimatedSize();*/
	
}



void CBurnDlg::OnButtonAddUid() 
{
	// TODO: Add your control notification handler code here
	CString strUID;
	GetDlgItem(IDC_EDIT_UID)->GetWindowText(strUID);

	if (strUID.IsEmpty())
		return;

	((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->AddString(strUID);
	
// 	switch (((CComboBox*)GetDlgItem(IDC_COMBO_UID_TYPE))->GetCurSel())
// 	{
// 	case 0:
// 		m_vtrPatientUIDs.push_back(strUID);
// 		break;
// 	case 1:
// 		m_vtrStudyUIDs.push_back(strUID);
// 		break;
// 	case 2:
// 		m_vtrSeriesUIDs.push_back(strUID);
// 		break;
// 	default:
// 		return;
// 	}
// 
	/*UpdataEstimatedSize();*/
}

void CBurnDlg::OnButtonDelUid() 
{
	// TODO: Add your control notification handler code here
	INT iIndex = ((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->GetCurSel();

	if (LB_ERR == iIndex)
		return;

// 	CString strUID;
// 	((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->GetText(iIndex, strUID);
		
	((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->DeleteString(iIndex);

// 	vector<CString>* pvtrUIDs = NULL;
// 
// 	switch (((CComboBox*)GetDlgItem(IDC_COMBO_UID_TYPE))->GetCurSel())
// 	{
// 	case 0:
// 		pvtrUIDs = &m_vtrPatientUIDs;
// 		break;
// 	case 1:
// 		pvtrUIDs = &m_vtrStudyUIDs;
// 		break;
// 	case 2:
// 		pvtrUIDs = &m_vtrSeriesUIDs;
// 		break;
// 	default:
// 		return;
// 	}
// 
// 	vector<CString>::iterator Iter;
// 
// 	for (Iter = pvtrUIDs->begin(); Iter != pvtrUIDs->end(); Iter++)
// 	{
// 		if (!strUID.Compare(*Iter))
// 		{
// 			pvtrUIDs->erase(Iter);
// 			break;
// 		}
// 	}
// 
	/*UpdataEstimatedSize();*/
	
}

void CBurnDlg::OnButtonClearUid() 
{
	// TODO: Add your control notification handler code here
	((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->ResetContent();
}

void CBurnDlg::OnSelchangeComboUidType() 
{
	// TODO: Add your control notification handler code here

// 	((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->ResetContent();
// 
// 	vector<CString>* pvtrUIDs = NULL;
// 
// 	switch (((CComboBox*)GetDlgItem(IDC_COMBO_UID_TYPE))->GetCurSel())
// 	{
// 	case 0:
// 		pvtrUIDs = &m_vtrPatientUIDs;
// 		break;
// 	case 1:
// 		pvtrUIDs = &m_vtrStudyUIDs;
// 		break;
// 	case 2:
// 		pvtrUIDs = &m_vtrSeriesUIDs;
// 		break;
// 	default:
// 		return;
// 	}
// 	
// 	for (int i = 0; i < pvtrUIDs->size(); i++)
// 	{
// 		((CListBox*)GetDlgItem(IDC_LIST_UIDLIST))->AddString((*pvtrUIDs)[i]);
// 	}
// 
	/*UpdataEstimatedSize();*/
}

void CBurnDlg::OnButtonCheckdevice() 
{
	// TODO: Add your control notification handler code here
// 	CTestClientSrcDlg::m_pIPABurn->EnableCheckDevice(TRUE);
}

void CBurnDlg::OnButtonUncheckdevice() 
{
	// TODO: Add your control notification handler code here
// 	CTestClientSrcDlg::m_pIPABurn->EnableCheckDevice(FALSE);
	
}

void CBurnDlg::OnButtonBurnprepare() 
{
	// TODO: Add your control notification handler code here

// 	DWORD dwStart = GetTickCount();

	GetDlgItem(IDC_EDIT_DISC_TYPE)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_DISC_CAPACITY)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_EMPTY_MEDIA)->SetWindowText(_T(""));
	m_cbboxBurnSpeed.ResetContent();

	Init();
	OnButtonCheckdevice();

	CTestClientSrcDlg::m_pIPABurn->GetCurrentDeviceMediaInfo();
	

	long lUIDNum = 0;
	BSTR* pbsUIDList = NULL;
	PatientAdminUIDType enumPAUIDType = enumPatientAdminUIDType_Unknow;
	if (!GetBurnUIDTypeAndList(&lUIDNum, &pbsUIDList, &enumPAUIDType))
		return;

	if (S_OK !=CTestClientSrcDlg::m_pIPABurn->BurnPrepare(lUIDNum, pbsUIDList, enumPAUIDType))
	{
		AfxMessageBox(_T("m_pIPABurn->BurnPrepare"));
	}

	if (pbsUIDList)
		delete [] pbsUIDList;

// 	m_BurnPatientInfoDlg.Init();
// 	m_BurnPatientInfoDlg.ShowWindow(SW_SHOW);

// 	DWORD dwTime = GetTickCount() - dwStart;
// 	CString str;
// 	str.Format(_T("%d"), dwTime);
// 	AfxMessageBox(str);
	
}

void CBurnDlg::OnButtonCancelburnprepare() 
{
	// TODO: Add your control notification handler code here
	if (S_OK !=CTestClientSrcDlg::m_pIPABurn->CancelBurnPrepare())
	{
		AfxMessageBox(_T("m_pIPABurn->CancelBurnPrepare()"));
	}
}

void CBurnDlg::OnSelchangeComboBurnType() 
{
	// TODO: Add your control notification handler code here
// 	switch (((CComboBox*)GetDlgItem(IDC_COMBO_BURN_TYPE))->GetCurSel())
// 	{
// 		case 0:
// 			// BackUp
// 			((CButton*)GetDlgItem(IDC_CHECK_DICOM))->SetCheck(BST_CHECKED);
// 			((CButton*)GetDlgItem(IDC_CHECK_DICOM))->EnableWindow(FALSE);
// 			((CComboBox*)GetDlgItem(IDC_COMBO_DOWNSCALE))->SetCurSel(1);
// 			((CComboBox*)GetDlgItem(IDC_COMBO_DOWNSCALE))->EnableWindow(TRUE);
// 
// 			((CButton*)GetDlgItem(IDC_CHECK_BMP))->SetCheck(BST_UNCHECKED);
// 			((CButton*)GetDlgItem(IDC_CHECK_BMP))->EnableWindow(FALSE);
// 			((CButton*)GetDlgItem(IDC_CHECK_JPEG))->SetCheck(BST_UNCHECKED);
// 			((CButton*)GetDlgItem(IDC_CHECK_JPEG))->EnableWindow(FALSE);
// 
// 			/*UpdataEstimatedSize();*/
// 			break;
// 		case 1:
// 			// Export
// 			((CButton*)GetDlgItem(IDC_CHECK_DICOM))->SetCheck(BST_CHECKED);
// 			((CButton*)GetDlgItem(IDC_CHECK_DICOM))->EnableWindow(TRUE);
// 			((CComboBox*)GetDlgItem(IDC_COMBO_DOWNSCALE))->SetCurSel(0);
// 			((CComboBox*)GetDlgItem(IDC_COMBO_DOWNSCALE))->EnableWindow(TRUE);
// 
// 			((CButton*)GetDlgItem(IDC_CHECK_BMP))->SetCheck(BST_UNCHECKED);
// 			((CButton*)GetDlgItem(IDC_CHECK_BMP))->EnableWindow(TRUE);
// 			((CButton*)GetDlgItem(IDC_CHECK_JPEG))->SetCheck(BST_UNCHECKED);
// 			((CButton*)GetDlgItem(IDC_CHECK_JPEG))->EnableWindow(TRUE);
// 
// 			/*UpdataEstimatedSize();*/
// 			
// 			break;
// 		default:
// 			return;
// 	}
}

void CBurnDlg::OnButtonRefreshDeviceMediaInfo() 
{
	// TODO: Add your control notification handler code here
	EnableWindowDuringGetDeviceMediaInfo(FALSE);
	CTestClientSrcDlg::m_pIPABurn->GetCurrentDeviceMediaInfo();
}


void CBurnDlg::UpdateSpeedInfo(long lItemNum, BurnSpeedInfo* pSpeedInfo)
{
	m_cbboxBurnSpeed.ResetContent();
	for (int i = 0; i < lItemNum; i++)
	{
		CString strSpeed = CBSTROpt::BSTRToCString(pSpeedInfo[i].bsSpeedInfo);
		int iIndex = m_cbboxBurnSpeed.AddString(strSpeed);
		m_cbboxBurnSpeed.SetItemData(iIndex, (DWORD)pSpeedInfo[i].lSpeed);
	}

	m_cbboxBurnSpeed.SetCurSel(m_cbboxBurnSpeed.GetCount()-1);
}

void CBurnDlg::UpdateMediaInfo(BurnMediaInfo* pMediaInfo)
{
	CString strInfo = CBSTROpt::BSTRToCString(pMediaInfo->bsMediaType);
	GetDlgItem(IDC_EDIT_DISC_TYPE)->SetWindowText(strInfo);

	strInfo = CBSTROpt::BSTRToCString(pMediaInfo->bsMediaSize);
	GetDlgItem(IDC_EDIT_DISC_CAPACITY)->SetWindowText(strInfo);

	if (pMediaInfo->bEmptyMedia)
	{
		strInfo = _T("TRUE");
	}
	else
	{
		strInfo = _T("FALSE");
	}
	GetDlgItem(IDC_EDIT_EMPTY_MEDIA)->SetWindowText(strInfo);


	EnableWindowDuringGetDeviceMediaInfo(TRUE);

}

void CBurnDlg::BurnMediaNotReady(BSTR bsInfo)
{
	CString strInfo = CBSTROpt::BSTRToCString(bsInfo);
	int iRet = AfxMessageBox(strInfo, MB_OKCANCEL);
	CTestClientSrcDlg::m_pIPABurn->SetBurnMediaCheckRetry(iRet==IDOK ? TRUE : FALSE);
	
}

void CBurnDlg::EnableWindowDuringGetDeviceMediaInfo(BOOL bEnable)
{
	GetDlgItem(IDC_COMBO_DEVICE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_BURNSPEED)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_REFRESH_DEVICE_MEDIA_INFO)->EnableWindow(bEnable);
}


void CBurnDlg::OnButtonBurnUnfinishedjob() 
{
	// TODO: Add your control notification handler code here
	BOOL bExist = FALSE;
	if (S_OK !=CTestClientSrcDlg::m_pIPABurn->IsUnfinishedBurnJobExist(&bExist))
	{
		AfxMessageBox(_T("m_pIPABurn->IsUnfinishedBurnJobExist()"));
	}
	else
	{
		if (bExist)
		{
			AfxMessageBox(_T("There IS unfinished burn Job"));
		}
		else
		{
			AfxMessageBox(_T("There is NOT unfinished burn Job"));
		}
	}
}
