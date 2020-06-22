// PatientAdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "PatientAdminDlg.h"
#include "PATestClientLibExt_i.c"
#include "TestClientSrcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatientAdminDlg dialog
extern CTestClientSrcDlg* g_smDlg; 


CPatientAdminDlg::CPatientAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPatientAdminDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPatientAdminDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_pIDBPIM = NULL;
	m_pIDBConfig = NULL;
	m_pIDBSession = NULL;
	m_pIDBGeneral = NULL;
	m_pIISGeneral = NULL;


	//}}AFX_DATA_INIT
}
CPatientAdminDlg::~CPatientAdminDlg()
{
	ReleaseInterface();
}


void CPatientAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPatientAdminDlg)
	DDX_Control(pDX, IDC_LIST_IMAGE, m_lstImages);
	DDX_Control(pDX, IDC_LIST_SERIES, m_lstSeries);
	DDX_Control(pDX, IDC_LIST_STUDY, m_lstStudies);
	DDX_Control(pDX, IDC_LIST_PATIENT, m_lstPatients);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPatientAdminDlg, CDialog)
	//{{AFX_MSG_MAP(CPatientAdminDlg)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_UNINIT, OnButtonUninit)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PATIENT, OnClickListPatient)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STUDY, OnClickListStudy)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SERIES, OnClickListSeries)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_PATIENTS, OnButtonUpdatePatients)
	ON_BN_CLICKED(IDC_BUTTON_SET_CRT_PATIENT, OnButtonSetCrtPatient)
	ON_BN_CLICKED(IDC_BUTTON_SET_CRT_STUDY, OnButtonSetCrtStudy)
	ON_BN_CLICKED(IDC_BUTTON_SET_CRT_SERIES, OnButtonSetCrtSeries)
	ON_BN_CLICKED(IDC_BUTTON_FLAG_IMAGE, OnButtonFlagImage)
	ON_BN_CLICKED(IDC_BUTTON_UNFLAG_IMAGE, OnButtonUnflagImage)
	ON_BN_CLICKED(IDC_BUTTON_FLAG_ALL_IMAGE, OnButtonFlagAllImage)
	ON_BN_CLICKED(IDC_BUTTON_UNFLAG_ALL_IMAGE, OnButtonUnflagAllImage)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_FLAG, OnButtonClearFlag)
	ON_BN_CLICKED(IDC_BUTTON_CURRENT_UID, OnButtonCurrentUid)
	ON_BN_CLICKED(IDC_BUTTON_FLAGGED_IMAGE_NUM, OnButtonFlaggedImageNum)
	ON_BN_CLICKED(IDC_BUTTON_COPY_UID, OnButtonCopyUid)
	ON_NOTIFY(NM_HOVER, IDC_LIST_PATIENT, OnHOVERListPatient)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_FROM_DB, OnButtonDeleteFromDb)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_IMAGE, OnButtonViewImage)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IMAGE, OnClickListImage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatientAdminDlg message handlers
BOOL CPatientAdminDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Patient
	DWORD dwStype = m_lstPatients.GetExtendedStyle();
//	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	dwStype |= LVS_EX_GRIDLINES;
	dwStype |= LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE;
	dwStype |= LVS_EX_INFOTIP;
	m_lstPatients.SetExtendedStyle(dwStype);
//	m_lstPatients.SetHoverTime(3000);

	m_lstPatients.InsertColumn(0, _T("PatientUID"), LVCFMT_LEFT, 130);
	m_lstPatients.InsertColumn(1, _T("PatientID"), LVCFMT_LEFT, 100);
	m_lstPatients.InsertColumn(2, _T("PatientName"), LVCFMT_LEFT, 100);
	m_lstPatients.InsertColumn(3, _T("Gender"), LVCFMT_LEFT, 100);
// 	m_lstPatients.InsertColumn(4, _T("BirthDate"), LVCFMT_LEFT, 100);
// 	m_lstPatients.InsertColumn(5, _T("StudyNum"), LVCFMT_LEFT, 100);
// 	m_lstPatients.InsertColumn(6, _T(""), LVCFMT_LEFT, 0);

	// Study
	dwStype = m_lstStudies.GetExtendedStyle();
//	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	dwStype |= LVS_EX_GRIDLINES;
	m_lstStudies.SetExtendedStyle(dwStype);

	m_lstStudies.InsertColumn(0, _T("StudyUID"), LVCFMT_LEFT, 130);
	m_lstStudies.InsertColumn(1, _T("StudyID"), LVCFMT_LEFT, 100);
	m_lstStudies.InsertColumn(2, _T("InstanceUID"), LVCFMT_LEFT, 100);
	m_lstStudies.InsertColumn(3, _T("MPPSState"), LVCFMT_LEFT, 100);
// 	m_lstStudies.InsertColumn(4, _T("SeriesNum"), LVCFMT_LEFT, 100);
// 	m_lstStudies.InsertColumn(5, _T("Description"), LVCFMT_LEFT, 100);
// 	m_lstStudies.InsertColumn(6, _T(""), LVCFMT_LEFT, 0);

	// Series
	dwStype = m_lstSeries.GetExtendedStyle();
//	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	dwStype |= LVS_EX_GRIDLINES;
	m_lstSeries.SetExtendedStyle(dwStype);

	m_lstSeries.InsertColumn(0, _T("SeriesUID"), LVCFMT_LEFT, 130);
	m_lstSeries.InsertColumn(1, _T("SeriesID"), LVCFMT_LEFT, 100);
// 	m_lstSeries.InsertColumn(2, _T("SeriesType"), LVCFMT_LEFT, 100);
// 	m_lstSeries.InsertColumn(3, _T("StartDateTime"), LVCFMT_LEFT, 150);
// 	m_lstSeries.InsertColumn(3, _T("FrameNum"), LVCFMT_LEFT, 100);
// 	m_lstSeries.InsertColumn(5, _T("ImageSize"), LVCFMT_LEFT, 100);
// 	m_lstSeries.InsertColumn(6, _T(""), LVCFMT_LEFT, 0);


	// Image
	dwStype = m_lstImages.GetExtendedStyle();
//	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	dwStype |= LVS_EX_GRIDLINES;
	m_lstImages.SetExtendedStyle(dwStype);

	m_lstImages.InsertColumn(0, _T("ImageUID"), LVCFMT_LEFT, 130);
	m_lstImages.InsertColumn(1, _T("ImageID"), LVCFMT_LEFT, 100);
// 	m_lstImages.InsertColumn(2, _T(""), LVCFMT_LEFT, 100);
// 	m_lstImages.InsertColumn(3, _T(""), LVCFMT_LEFT, 100);


	GetDlgItem(IDC_EDIT_FLAG_IMAGE_INDEX)->SetWindowText(_T("1"));

	// SeriesImages Dialog
	m_SeriesImagesDlg.Create(IDD_FORMVIEW_SERIES_IMAGE);
	m_SeriesImagesDlg.ShowWindow(SW_HIDE);
	CRect rectParent, rectChild;
	GetWindowRect(&rectParent);
	m_SeriesImagesDlg.GetWindowRect(&rectChild);
	rectChild.left = rectParent.right - 200;
	rectChild.right = rectChild.left + 150 + 512;
	rectChild.bottom = rectChild.top + 512;
	m_SeriesImagesDlg.MoveWindow(rectChild);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPatientAdminDlg::OnButtonInit() 
{
	// TODO: Add your control notification handler code here
	HRESULT hr = S_OK;
	if(NULL == m_pIDBPIM)
	{		
		hr = ::CoCreateInstance(CLSID_DBPIM,
								NULL, 
								CLSCTX_LOCAL_SERVER,
								IID_IDBPIM,
								(LPVOID*)&m_pIDBPIM);
		if(hr != S_OK)
		{
			AfxMessageBox(_T("ERROR: CoCreateInstance m_pIDBPIM"));
			return;
		}
	}
	if(NULL == m_pIDBConfig)
	{
		if(CoCreateInstance(CLSID_DBConfig,
							NULL, 
							CLSCTX_LOCAL_SERVER,
							IID_IDBConfig,
							(LPVOID*)&m_pIDBConfig) != S_OK)
		{
			AfxMessageBox(_T("ERROR: CoCreateInstance m_pIDBConfig"));
			return;
		}
	}
	if(NULL == m_pIDBSession)
	{
		if(CoCreateInstance(CLSID_DBSession,
							NULL,
							CLSCTX_LOCAL_SERVER,
							IID_IDBSession,
							(LPVOID*)&m_pIDBSession) != S_OK)
		{
			AfxMessageBox(_T("ERROR: CoCreateInstance m_pIDBSession"));
			return;
		}
	}
	
	if(NULL == m_pIDBGeneral)
	{
		if(S_OK != m_pIDBSession->QueryInterface(IID_IGeneralSys,(LPVOID*)&m_pIDBGeneral))
		{
			AfxMessageBox(_T("S_OK != m_pIDBSession->QueryInterface(IID_IGeneralSys,(LPVOID*)&m_pIDBGeneral)"));
			return;
		}
	}

	// DB StartUp

   if ( S_OK != m_pIDBGeneral->StartUp())
   {
		AfxMessageBox(_T("Error: m_pIDBGeneral->StartUp()"));
   }

	if(NULL == m_pIISGeneral)
	{
		if(CoCreateInstance(CLSID_ISATL,
							NULL,
							CLSCTX_LOCAL_SERVER,
							IID_IGeneralSys,
							(LPVOID*)&m_pIISGeneral) != S_OK)
		{
			AfxMessageBox(_T("S_OK != m_pIISGeneral->CoCreateInstance(IID_IGeneralSys,(LPVOID*)&m_pIDBGeneral)"));
			return;
		}
	}

	if ( S_OK != m_pIISGeneral->StartUp())
	{
		AfxMessageBox(_T("Error: m_pIISGeneral->StartUp()"));
		return;
	}

//    sleep(1);
// 
//    GetPatientsInfo();
}

void CPatientAdminDlg::OnButtonUninit() 
{
	// TODO: Add your control notification handler code here
	ReleaseInterface();
}

void CPatientAdminDlg::GetPatientsInfo()
{
	if (NULL == m_pIDBPIM)
	{
		AfxMessageBox(_T("NULL == m_pIDBPIM"));
		return;
	}

	m_lstPatients.DeleteAllItems();
	int iItemIndex = 0;

// 	//<< 获得默认患者
// 	BOOL bExist = FALSE;
// 	BSTR bsPatietUID;
// 
// 	if (S_OK != m_pIDBPIM->GetDefaultPatientUID(&bExist, &bsPatietUID))
// 	{
// 		AfxMessageBox(_T("S_OK != m_pIDBPIM->GetDefaultPatientUID(&bExist, &bsPatietUID)"));
// 		return;
// 	}
// 
// 	if (bExist)
// 	{
// 		PatientInfoStruct PatientInfo;
// 		if (S_OK != m_pIDBPIM->GetPatientInfo(bsPatietUID, &PatientInfo))
// 		{
// 			AfxMessageBox(_T("S_OK != m_pIDBPIM->GetPatientInfo(bsPatietUID, &PatientInfo)"));
// 			return;
// 		}
// 		else
// 		{
// 			m_lstPatients.InsertItem(iItemIndex, CString(_com_util::ConvertBSTRToString(PatientInfo.bsPatientUID)));
// 			m_lstPatients.SetItemText(iItemIndex, 1, CString(_com_util::ConvertBSTRToString(PatientInfo.bsPatientID)));
// 			m_lstPatients.SetItemText(iItemIndex, 2, CString(_com_util::ConvertBSTRToString(PatientInfo.bsPatientFullName)));
// 			
// 			CString strInfo;
// 			switch (PatientInfo.iGender)
// 			{
// 			case 0:
// 				strInfo = _T("M");
// 				break;
// 			case 1:
// 				strInfo = _T("F");
// 				break;
// 			case 2:
// 				strInfo = _T("O");
// 				break;
// 			default:
// 				strInfo.Format(_T("unknow, iGender: %d"), PatientInfo.iGender);
// 				break;
// 			}
// 			m_lstPatients.SetItemText(iItemIndex, 3, strInfo);
// 
// 			++iItemIndex;
// 		}
// 	}
// 

	//<< 获得其它患者
	UINT uInNum = 10000;
	UINT uOutNum = 0;
	PatientInfoStruct* pStruct = NULL;
	if (S_OK != m_pIDBPIM->GetPatientList(uInNum, &uOutNum, &pStruct))
	{
		AfxMessageBox(_T("S_OK != m_pIDBPIM->GetPatientList(uInNum, &uOutNum, &pStruct)"));
		return;
	}


	PatientInfoStruct* p = pStruct;
	for (int i = 0; i < uOutNum; i++)
	{
		BOOL bExist = FALSE;
		CString strPatientUID = _com_util::ConvertBSTRToString((p+i)->bsPatientUID);

		m_lstPatients.InsertItem(iItemIndex, strPatientUID);
		m_lstPatients.SetItemText(iItemIndex, 1, CString(_com_util::ConvertBSTRToString((p+i)->bsPatientID)));
		m_lstPatients.SetItemText(iItemIndex, 2, CString(_com_util::ConvertBSTRToString((p+i)->bsPatientName)));
		
		CString strInfo;
		switch ((p+i)->iGender)
		{
		case 0:
			strInfo = _T("M");
			break;
		case 1:
			strInfo = _T("F");
			break;
		case 2:
			strInfo = _T("O");
			break;
		default:
			strInfo.Format(_T("unknow, iGender: %d"), (p+i)->iGender);
			break;
		}
		m_lstPatients.SetItemText(iItemIndex, 3, strInfo);

		++iItemIndex;

	}

	if (NULL != pStruct)
	{
		CoTaskMemFree(pStruct);
	}

}

void CPatientAdminDlg::GetStudysInfo(LPCTSTR szPatientUID)
{
	if (NULL == szPatientUID)
	{
		AfxMessageBox(_T("NULL == szPatientUID"));
		return;
	}

	long lNum = 0;
	StudyInfoStruct* pStruct = NULL;
	BSTR bsPatientUID = CString(szPatientUID).AllocSysString();
	if (S_OK != m_pIDBPIM->GetStudyListByPatientUID(bsPatientUID, &lNum, &pStruct))
	{
		AfxMessageBox(_T("S_OK != m_pIDBPIM->GetStudyListByPatientUID(bsPatientUID, &lNum, &pStruct)"));
	}

	m_lstStudies.DeleteAllItems();

	int iItemIndex = 0;
	StudyInfoStruct* p = pStruct;
	for (int i = 0; i < lNum; i++)
	{
		m_lstStudies.InsertItem(iItemIndex, CString(_com_util::ConvertBSTRToString((p+i)->bsStudyUID)));
		CString strInfo;
		strInfo.Format(_T("%d"), (p+i)->iStudyID);
		m_lstStudies.SetItemText(iItemIndex, 1, strInfo);

		strInfo = _com_util::ConvertBSTRToString((p+i)->bsInstanceUID);
		m_lstStudies.SetItemText(iItemIndex, 2, strInfo);

		strInfo.Format(_T("%d"), (p+i)->enumMPPSState);
		m_lstStudies.SetItemText(iItemIndex, 3, strInfo);

		++iItemIndex;

	}

	if (NULL != pStruct)
	{
		CoTaskMemFree(pStruct);
	}
}

void CPatientAdminDlg::GetSeriesInfo(LPCTSTR szStudyUID)
{
	if (NULL == szStudyUID)
	{
		AfxMessageBox(_T("NULL == szStudyUID"));
		return;
	}

	long lNum = 0;
	SeriesInfoStruct* pStruct = NULL;
	BSTR bsStudyUID = CString(szStudyUID).AllocSysString();
	if (S_OK != m_pIDBPIM->GetSeriesListByStudyUID(bsStudyUID, &lNum, &pStruct))
	{
		AfxMessageBox(_T("S_OK != m_pIDBPIM->GetSeriesListByStudyUID(bsStudyUID, &lNum, &pStruct)"));
	}

	m_lstSeries.DeleteAllItems();

	int iItemIndex = 0;
	SeriesInfoStruct* p = pStruct;
	for (int i = 0; i < lNum; i++)
	{
		CString strInfo;

		m_lstSeries.InsertItem(iItemIndex, CString(_com_util::ConvertBSTRToString((p+i)->bsSeriesUID)));
		
		strInfo.Format(_T("%d"), (p+i)->iSeriesID);
		m_lstSeries.SetItemText(iItemIndex, 1, strInfo);

// 		switch (SeriesInfo.iSeriesType)
// 		{
// 		case 0:
// 			strInfo = _T("Exposure");
// 			break;
// 		case 1:
// 			strInfo = _T("Fluo");
// 		    break;
// 		default:
// 			strInfo.Format(_T("unknow, iSereisType: %d"), SeriesInfo.iSeriesType);
// 		    break;
// 		}
// 		m_lstSeries.SetItemText(iItemIndex, 2, strInfo);
// 
// 		strInfo.Format(_T("%d"), SeriesInfo.lNumberofImages);
// 		m_lstSeries.SetItemText(iItemIndex, 3, strInfo);

		++iItemIndex;
	}

	if (NULL != pStruct)
	{
		CoTaskMemFree(pStruct);
	}

}

void CPatientAdminDlg::GetImageInfo(LPCTSTR szSeriesUID)
{
	if (NULL == szSeriesUID)
	{
		AfxMessageBox(_T("NULL == szStudyUID"));
		return;
	}

	long lNum = 0;
	ImageInfoStruct* pStruct = NULL;
	BSTR bsSeriesUID = CString(szSeriesUID).AllocSysString();
	if (S_OK != m_pIDBPIM->GetImageListBySeriesUID(bsSeriesUID, &lNum, &pStruct))
	{
		AfxMessageBox(_T("S_OK != m_pIDBPIM->GetImageListByStudyUID(bsSeriesUID, &lNum, &pStruct)"));
	}

	m_lstImages.DeleteAllItems();

	int iItemIndex = 0;
	ImageInfoStruct* p = pStruct;
	for (int i = 0; i < lNum; i++)
	{
		CString strInfo;

		m_lstImages.InsertItem(iItemIndex, CString(_com_util::ConvertBSTRToString((p+i)->bsImageUID)));
		
		strInfo.Format(_T("%d"), (p+i)->iImageID);
		m_lstImages.SetItemText(iItemIndex, 1, strInfo);


		++iItemIndex;
	}

	if (NULL != pStruct)
	{
		CoTaskMemFree(pStruct);
	}
}

void CPatientAdminDlg::OnClickListPatient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem == -1)
		return;

	for (int i = 0; i < m_lstPatients.GetItemCount(); i++)
	{
		m_lstPatients.SetItemTextColor(i, COLORREF(RGB(0,0,0)));
		m_lstPatients.SetItemBkColor(i, COLORREF(RGB(255, 255, 255)));
	}

	m_lstPatients.SetItemTextColor(pNMListView->iItem, COLORREF(RGB(255, 255, 255)));
	m_lstPatients.SetItemBkColor(pNMListView->iItem, COLORREF(RGB(49, 106, 197)));
	m_lstPatients.RedrawItems(0, m_lstPatients.GetItemCount());

	CString strPatientUID = m_lstPatients.GetItemText(pNMListView->iItem, 0);
	GetDlgItem(IDC_EDIT_SELECTED_ITEM_UID)->SetWindowText(strPatientUID);
	GetDlgItem(IDC_BUTTON_DELETE_FROM_DB)->SetWindowText(_T("Delete Patient"));

	GetStudysInfo(strPatientUID);

	*pResult = 0;
}

void CPatientAdminDlg::OnClickListStudy(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem == -1)
		return;

	for (int i = 0; i < m_lstStudies.GetItemCount(); i++)
	{
		m_lstStudies.SetItemTextColor(i, COLORREF(RGB(0,0,0)));
		m_lstStudies.SetItemBkColor(i, COLORREF(RGB(255, 255, 255)));
	}

	m_lstStudies.SetItemTextColor(pNMListView->iItem, COLORREF(RGB(255, 255, 255)));
	m_lstStudies.SetItemBkColor(pNMListView->iItem, COLORREF(RGB(49, 106, 197)));
	m_lstStudies.RedrawItems(0, m_lstStudies.GetItemCount());

	CString strStudyUID = m_lstStudies.GetItemText(pNMListView->iItem, 0);
	GetDlgItem(IDC_EDIT_SELECTED_ITEM_UID)->SetWindowText(strStudyUID);
	GetDlgItem(IDC_BUTTON_DELETE_FROM_DB)->SetWindowText(_T("Delete Study"));

	GetSeriesInfo(strStudyUID);
	
	*pResult = 0;
}

void CPatientAdminDlg::OnClickListSeries(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem == -1)
		return;
	
	for (int i = 0; i < m_lstSeries.GetItemCount(); i++)
	{
		m_lstSeries.SetItemTextColor(i, COLORREF(RGB(0,0,0)));
		m_lstSeries.SetItemBkColor(i, COLORREF(RGB(255, 255, 255)));
	}

	m_lstSeries.SetItemTextColor(pNMListView->iItem, COLORREF(RGB(255, 255, 255)));
	m_lstSeries.SetItemBkColor(pNMListView->iItem, COLORREF(RGB(49, 106, 197)));
	m_lstSeries.RedrawItems(0, m_lstSeries.GetItemCount());

	CString strSeriesUID = m_lstSeries.GetItemText(pNMListView->iItem, 0);
	GetDlgItem(IDC_EDIT_SELECTED_ITEM_UID)->SetWindowText(strSeriesUID);
	GetDlgItem(IDC_BUTTON_DELETE_FROM_DB)->SetWindowText(_T("Delete Series"));

	
	GetImageInfo(strSeriesUID);

	*pResult = 0;
}

void CPatientAdminDlg::OnClickListImage(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem == -1)
		return;
	
	for (int i = 0; i < m_lstImages.GetItemCount(); i++)
	{
		m_lstImages.SetItemTextColor(i, COLORREF(RGB(0,0,0)));
		m_lstImages.SetItemBkColor(i, COLORREF(RGB(255, 255, 255)));
	}

	m_lstImages.SetItemTextColor(pNMListView->iItem, COLORREF(RGB(255, 255, 255)));
	m_lstImages.SetItemBkColor(pNMListView->iItem, COLORREF(RGB(49, 106, 197)));
	m_lstImages.RedrawItems(0, m_lstImages.GetItemCount());

	CString strImageUID = m_lstImages.GetItemText(pNMListView->iItem, 0);
	GetDlgItem(IDC_EDIT_SELECTED_ITEM_UID)->SetWindowText(strImageUID);
	GetDlgItem(IDC_BUTTON_DELETE_FROM_DB)->SetWindowText(_T("Delete Image"));


	*pResult = 0;
}

void CPatientAdminDlg::OnButtonUpdatePatients() 
{
	// TODO: Add your control notification handler code here
	m_lstPatients.DeleteAllItems();
	GetPatientsInfo();
}

void CPatientAdminDlg::OnButtonSetCrtPatient() 
{
	// TODO: Add your control notification handler code here
	
}

void CPatientAdminDlg::OnButtonSetCrtStudy() 
{
	// TODO: Add your control notification handler code here
	
}

void CPatientAdminDlg::OnButtonSetCrtSeries() 
{
	// TODO: Add your control notification handler code here
// 	CString strUID;
// 	BSTR bsUID;
// 
// 	POSITION pos;
// 	int nPatientItem = -1;
// 	int nStudyItem = -1;
// 	int nSeriesItem = -1;
// 
// 	pos = m_lstPatients.GetFirstSelectedItemPosition();
// 	if (pos == NULL)
// 	{
// 		AfxMessageBox(_T("Plz select a patient"));
// 		return;
// 	}
// 	else
// 	{			
// 		nPatientItem = m_lstPatients.GetNextSelectedItem(pos);
// 	}
// 
// 	pos = m_lstStudies.GetFirstSelectedItemPosition();
// 	if (pos == NULL)
// 	{
// 		AfxMessageBox(_T("Plz select a study"));
// 		return;
// 	}
// 	else
// 	{			
// 		nStudyItem = m_lstStudies.GetNextSelectedItem(pos);
// 	}
// 
// 	pos = m_lstSeries.GetFirstSelectedItemPosition();
// 	if (pos == NULL)
// 	{
// 		AfxMessageBox(_T("Plz select a series"));
// 		return;
// 	}
// 	else
// 	{			
// 		nSeriesItem = m_lstSeries.GetNextSelectedItem(pos);
// 	}
// 
// 	strUID = m_lstPatients.GetItemText(nPatientItem, 0);
// 	bsUID = strUID.AllocSysString();
// 	HRESULT hResult = m_pIDBSession->SetCurrentPatientUID(bsUID);
// 	if (S_OK != hResult)
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBSession->SetCurrentPatientUID(bsUID)"));
// 		return;
// 	}
// 
// 	strUID = m_lstStudies.GetItemText(nStudyItem, 0);
// 	bsUID = strUID.AllocSysString();
// 	hResult = m_pIDBSession->SetCurrentStudyUID(bsUID);
// 	if (S_OK != hResult)
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBSession->SetCurrentStudyUID(bsUID)"));
// 		return;
// 	}
// 
// 	strUID = m_lstSeries.GetItemText(nSeriesItem, 0);
// 	bsUID = strUID.AllocSysString();
// 	hResult = m_pIDBSession->SetCurrentRunUID(bsUID);
// 	if (S_OK != hResult)
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBSession->SetCurrentSeriesUID(bsUID)"));
// 		return;
// 	}
// 
// 	GetCurrentUID();

}

void CPatientAdminDlg::OnButtonFlagImage() 
{
	// TODO: Add your control notification handler code here
// 	CString strUID;
// 	INT iImageIndex;
// 
// 	POSITION pos;
// 	int nSeriesItem = -1;
// 
// 	pos = m_lstSeries.GetFirstSelectedItemPosition();
// 	if (pos == NULL)
// 	{
// 		AfxMessageBox(_T("Plz select a series"));
// 		return;
// 	}
// 	else
// 	{			
// 		nSeriesItem = m_lstSeries.GetNextSelectedItem(pos);
// 		strUID = m_lstSeries.GetItemText(nSeriesItem, 0);
// 
// 	}
// 
// 	CString strImageIndex;
// 	CString strSeriesImageNum;
// 	GetDlgItem(IDC_EDIT_FLAG_IMAGE_INDEX)->GetWindowText(strImageIndex);
// 	if (strImageIndex.IsEmpty())
// 	{
// 		AfxMessageBox(_T("Plz input image index!"));
// 		return;
// 	}
// 	else
// 	{
// 		iImageIndex = _ttoi(strImageIndex);
// 
// 		strSeriesImageNum = m_lstSeries.GetItemText(nSeriesItem, 3);;
// 		if (iImageIndex <= 0 || iImageIndex > _ttoi(strSeriesImageNum))
// 		{
// 			AfxMessageBox(_T("Invalid image index!"));
// 			return;
// 		}
// 	}
// 
// 	strUID = m_lstSeries.GetItemText(nSeriesItem, 0);
// 
// 	ArchiveImageStruct scImageList;
// 	scImageList.bOptType = 1;		// flag
// 	scImageList.bRunType = 1;
// 	scImageList.bsSeriesUID = strUID.AllocSysString();
// 	scImageList.bsImageName = CString(_T("")).AllocSysString();
// 	scImageList.iImageIndex = iImageIndex;
// 
// 	if (S_OK != m_pIDBSession->SetArchiveImageList(scImageList))
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBSession->SetArchiveImageList(scImageList)"));
// 		return;
// 	}
// 	else
// 	{
// 		GetFlaggedImageNum();
// 	
// 		if (iImageIndex < _ttoi(strSeriesImageNum))
// 		{
// 			strImageIndex.Format(_T("%d"), iImageIndex+1);
// 			GetDlgItem(IDC_EDIT_FLAG_IMAGE_INDEX)->SetWindowText(strImageIndex);
// 		}
// 	}

}

void CPatientAdminDlg::OnButtonUnflagImage() 
{
	// TODO: Add your control notification handler code here
// 	CString strUID;
// 	INT iImageIndex;
// 
// 	POSITION pos;
// 	int nSeriesItem = -1;
// 
// 	pos = m_lstSeries.GetFirstSelectedItemPosition();
// 	if (pos == NULL)
// 	{
// 		AfxMessageBox(_T("Plz select a series"));
// 		return;
// 	}
// 	else
// 	{			
// 		nSeriesItem = m_lstSeries.GetNextSelectedItem(pos);
// 		strUID = m_lstSeries.GetItemText(nSeriesItem, 0);
// 
// 	}
// 
// 	CString strImageIndex;
// 	GetDlgItem(IDC_EDIT_FLAG_IMAGE_INDEX)->GetWindowText(strImageIndex);
// 	if (strImageIndex.IsEmpty())
// 	{
// 		AfxMessageBox(_T("Plz input image index!"));
// 		return;
// 	}
// 	else
// 	{
// 		iImageIndex = _ttoi(strImageIndex);
// 
// 		CString strSeriesImageNum = m_lstSeries.GetItemText(nSeriesItem, 3);;
// 		if (iImageIndex <= 0 || iImageIndex > _ttoi(strSeriesImageNum))
// 		{
// 			AfxMessageBox(_T("Invalid image index!"));
// 			return;
// 		}
// 	}
// 
// 	strUID = m_lstSeries.GetItemText(nSeriesItem, 0);
// 
// 	ArchiveImageStruct scImageList;
// 	scImageList.bOptType = 0;		// unflag
// 	scImageList.bRunType = 1;
// 	scImageList.bsSeriesUID = strUID.AllocSysString();
// 	scImageList.bsImageName = CString(_T("")).AllocSysString();
// 	scImageList.iImageIndex = iImageIndex;
// 
// 	if (S_OK != m_pIDBSession->SetArchiveImageList(scImageList))
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBSession->SetArchiveImageList(scImageList)"));
// 		return;
// 	}
// 	else
// 	{
// 		GetFlaggedImageNum();
// 	}
}

void CPatientAdminDlg::OnButtonFlagAllImage() 
{
	// TODO: Add your control notification handler code here
// 	CString strUID;
// 	INT iImageIndex;
// 
// 	POSITION pos;
// 	int nSeriesItem = -1;
// 
// 	pos = m_lstSeries.GetFirstSelectedItemPosition();
// 	if (pos == NULL)
// 	{
// 		AfxMessageBox(_T("Plz select a series"));
// 		return;
// 	}
// 	else
// 	{			
// 		nSeriesItem = m_lstSeries.GetNextSelectedItem(pos);
// 		strUID = m_lstSeries.GetItemText(nSeriesItem, 0);
// 
// 	}
// 
// 	CString strImageIndex;
// 	CString strSeriesImageNum;
// 
// 	strSeriesImageNum = m_lstSeries.GetItemText(nSeriesItem, 3);;
// 	strUID = m_lstSeries.GetItemText(nSeriesItem, 0);
// 
// 
// 	ArchiveImageStruct scImageList;
// 	scImageList.bOptType = 1;		// flag
// 	scImageList.bRunType = 1;
// 
// 	for (iImageIndex = 1; iImageIndex <= _ttoi(strSeriesImageNum); iImageIndex++)
// 	{
// 		strImageIndex.Format(_T("%d"), iImageIndex);
// 		GetDlgItem(IDC_EDIT_FLAG_IMAGE_INDEX)->SetWindowText(strImageIndex);
// 
// 		scImageList.bsSeriesUID = strUID.AllocSysString();
// 		scImageList.bsImageName = CString(_T("")).AllocSysString();
// 		scImageList.iImageIndex = iImageIndex;
// 
// 		if (S_OK != m_pIDBSession->SetArchiveImageList(scImageList))
// 		{
// 			AfxMessageBox(_T("Error: m_pIDBSession->SetArchiveImageList(scImageList)"));
// 			GetFlaggedImageNum();
// 			return;
// 		}
// 	}
// 
// 	GetFlaggedImageNum();

}

void CPatientAdminDlg::OnButtonUnflagAllImage() 
{
	// TODO: Add your control notification handler code here
// 	CString strUID;
// 	INT iImageIndex;
// 
// 	POSITION pos;
// 	int nSeriesItem = -1;
// 
// 	pos = m_lstSeries.GetFirstSelectedItemPosition();
// 	if (pos == NULL)
// 	{
// 		AfxMessageBox(_T("Plz select a series"));
// 		return;
// 	}
// 	else
// 	{			
// 		nSeriesItem = m_lstSeries.GetNextSelectedItem(pos);
// 		strUID = m_lstSeries.GetItemText(nSeriesItem, 0);
// 
// 	}
// 
// 	CString strImageIndex;
// 	CString strSeriesImageNum;
// 
// 	strSeriesImageNum = m_lstSeries.GetItemText(nSeriesItem, 3);;
// 	strUID = m_lstSeries.GetItemText(nSeriesItem, 0);
// 
// 	vector<int> vtrFailedImage;
// 	BOOL bRet = TRUE;
// 
// 	ArchiveImageStruct scImageList;
// 	scImageList.bOptType = 0;		// unflag
// 	scImageList.bRunType = 1;
// 
// 	for (iImageIndex = _ttoi(strSeriesImageNum); iImageIndex > 0; iImageIndex--)
// 	{
// 		strImageIndex.Format(_T("%d"), iImageIndex);
// 		GetDlgItem(IDC_EDIT_FLAG_IMAGE_INDEX)->SetWindowText(strImageIndex);
// 
// 		scImageList.bsSeriesUID = strUID.AllocSysString();
// 		scImageList.bsImageName = CString(_T("")).AllocSysString();
// 		scImageList.iImageIndex = iImageIndex;
// 
// 		if (S_OK != m_pIDBSession->SetArchiveImageList(scImageList))
// 		{
// 			vtrFailedImage.push_back(iImageIndex);
// 			bRet = FALSE;
// //			AfxMessageBox(_T("Error: m_pIDBSession->SetArchiveImageList(scImageList)"));
// // 			GetFlaggedImageNum();
// // 			return;
// 		}
// 	}
// 
// 	if (!bRet)
// 	{
// 		CString strInfo = _T("Error: m_pIDBSession->SetArchiveImageList(), ImageIndex:");
// 		for (int i = 0; i < vtrFailedImage.size(); i++)
// 		{
// 			CString strIndex;
// 			strIndex.Format(_T("%d "), vtrFailedImage[i]);
// 			strInfo += strIndex;
// 		}
// 
// 		AfxMessageBox(strInfo);
// 	}
// 
// 	GetFlaggedImageNum();
// 
}

void CPatientAdminDlg::OnButtonClearFlag() 
{
	// TODO: Add your control notification handler code here
// 	if (S_OK != m_pIDBSession->ClearArchiveImageList())
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBSession->ClearArchiveImageList()"));
// 		return;
// 	}
// 	else
// 	{
// 		GetFlaggedImageNum();
// 	}
}

void CPatientAdminDlg::GetCurrentUID()
{
// 	BSTR bsStrUID;
// 	CString strUID;
// 	HRESULT hResult = S_OK;
// 
// 	hResult = m_pIDBSession->GetCurrentPatientUID(&bsStrUID);
// 	if (S_OK != hResult)
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBSession->GetCurrentPatientUID(&bsStrUID)"));
// 		return;
// 	}
// 	else
// 	{
// 		strUID = _com_util::ConvertBSTRToString(bsStrUID);
// 		GetDlgItem(IDC_EDIT_CRT_PATIENT_UID)->SetWindowText(strUID);
// 	}
// 
// 	hResult = m_pIDBSession->GetCurrentStudyUID(&bsStrUID);
// 	if (S_OK != hResult)
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBSession->GetCurrentStudyUID(&bsStrUID)"));
// 		return;
// 	}
// 	else
// 	{
// 		strUID = _com_util::ConvertBSTRToString(bsStrUID);
// 		GetDlgItem(IDC_EDIT_CRT_STUDY_UID)->SetWindowText(strUID);
// 	}
// 
// 	hResult = m_pIDBSession->GetCurrentRunUID(&bsStrUID);
// 	if (S_OK != hResult)
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBSession->GetCurrentRunUID(&bsStrUID)"));
// 		return;
// 	}
// 	else
// 	{
// 		strUID = _com_util::ConvertBSTRToString(bsStrUID);
// 		GetDlgItem(IDC_EDIT_CRT_SERIES_UID)->SetWindowText(strUID);
// 	}

}

void CPatientAdminDlg::GetFlaggedImageNum()
{
// 	INT iCount = 0;
// 	ArchiveImageStruct* pList = NULL;
// 
// 	HRESULT hResult = m_pIDBSession->GetArchiveImageList(&iCount, &pList);
// 	if (S_OK != hResult)
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBSession->GetArchiveImageList(&iCount, &pList)"));
// 		return;
// 	}
// 	else
// 	{
// 		CString strInfo;
// 		strInfo.Format(_T("%d"), iCount);
// 		GetDlgItem(IDC_EDIT_FLAGGED_IMAGES_NUM)->SetWindowText(strInfo);
// 
// 		if (NULL != pList)
// 		{
// 			CoTaskMemFree(pList);
// 		}
// 	}
}

void CPatientAdminDlg::ReleaseInterface()
{
	if (m_pIDBPIM)
	{
		m_pIDBPIM->Release();
		m_pIDBPIM = NULL;
	}
	
	if (m_pIDBSession)
	{
		m_pIDBSession->Release();
		m_pIDBSession = NULL;
	}

	if (m_pIDBConfig)
	{
		m_pIDBConfig->Release();
		m_pIDBConfig = NULL;
	}

	if (m_pIDBGeneral)
	{
		m_pIDBGeneral->Release();
		m_pIDBGeneral = NULL;
	}

	if (m_pIISGeneral)
	{
		m_pIISGeneral->Release();
		m_pIISGeneral = NULL;
	}
}

void CPatientAdminDlg::OnButtonCurrentUid() 
{
	// TODO: Add your control notification handler code here
// 	GetCurrentUID();
}

void CPatientAdminDlg::OnButtonFlaggedImageNum() 
{
	// TODO: Add your control notification handler code here
// 	GetFlaggedImageNum();
}

void CPatientAdminDlg::OnButtonCopyUid() 
{
	// TODO: Add your control notification handler code here
	CString strUID;
	GetDlgItem(IDC_EDIT_SELECTED_ITEM_UID)->GetWindowText(strUID);
	
	//put   your   text   in   source   
	if(OpenClipboard())   
	{   
		HGLOBAL   clipbuffer;   
		char   *   buffer;   
		EmptyClipboard();   
		clipbuffer   =   GlobalAlloc(GMEM_DDESHARE,   (strUID.GetLength()+1) * sizeof(TCHAR));   
		buffer   =   (char*)GlobalLock(clipbuffer);   
		memcpy(buffer,   (void*)(LPCTSTR)strUID, (strUID.GetLength()+1) * sizeof(TCHAR));   
		GlobalUnlock(clipbuffer);   
		SetClipboardData(CF_UNICODETEXT,clipbuffer);   
		CloseClipboard();   
	}

// 	char*   source = new char[strUID.GetLength() + 1];
// 	WideCharToMultiByte (CP_ACP, WC_COMPOSITECHECK, (LPCTSTR)strUID, -1, source, strUID.GetLength() + 1, NULL, NULL ); 
// 	
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
// 
// 	delete [] source;
	
// 	DWORD dwStype = m_lstSeries.GetExtendedStyle();
// 	if (dwStype & LVS_EX_GRIDLINES)
// 		dwStype &= ~LVS_EX_GRIDLINES;
// 	else
// 		dwStype |= LVS_EX_GRIDLINES;
// 
// 	m_lstSeries.SetExtendedStyle(dwStype);

}

void CPatientAdminDlg::OnHOVERListPatient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
// 	LPNMLISTVIEW   pNMLV   =   reinterpret_cast <LPNMLISTVIEW> (pNMHDR);
// 
// 	int iItem = m_lstPatients.GetHotItem();
// 	CString strInfo = m_lstPatients.GetItemText(iItem, 0);
// 	AfxMessageBox(strInfo);
	
	CRect       rect;       
	m_lstPatients.GetWindowRect(rect);       
	CPoint       point;       
	GetCursorPos(&point);       
	point.x=point.x-rect.left;       
	point.y=point.y-rect.top;       
	
	LVHITTESTINFO       LVHTestInfo;       
	LVHTestInfo.pt           =       point;       
	m_lstPatients.HitTest(&LVHTestInfo);       
	int nRow=LVHTestInfo.iItem;       //行数 
	m_lstPatients.SubItemHitTest(&LVHTestInfo);       
	int   nCol=LVHTestInfo.iSubItem;     //列数 
	
	if (-1 != nRow && -1 != nCol)
	{
		CString   stritem; 
		stritem   =   m_lstPatients.GetItemText(nRow,nCol); 
	//	AfxMessageBox(stritem);     //可以获得鼠标悬停item的text
	}

	*pResult = 1;
}

void CPatientAdminDlg::OnButtonDeleteFromDb() 
{
	// TODO: Add your control notification handler code here
	if (NULL == m_pIDBPIM)
	{
		AfxMessageBox(_T("NULL == m_pIDBPIM"));
		return;
	}

	CString strUID;
	GetDlgItem(IDC_EDIT_SELECTED_ITEM_UID)->GetWindowText(strUID);
	if (strUID.IsEmpty())
	{
		return;
	}

	if (IDNO == AfxMessageBox(_T("Delete, are you sure?"), MB_YESNO))
	{
		return;
	}

	CString strButtonText;
	GetDlgItem(IDC_BUTTON_DELETE_FROM_DB)->GetWindowText(strButtonText);
	if (!strButtonText.Compare(_T("Delete Patient")))
	{
		BSTR bsUID = strUID.AllocSysString();
		if (S_OK == m_pIDBPIM->DeletePatientInfo(bsUID))
		{
			AfxMessageBox(_T("Succeed: m_pIDBPIM->DeletePatientInfo(bsUID)"));
		}
		else
		{
			AfxMessageBox(_T("Error: m_pIDBPIM->DeletePatientInfo(bsUID)"));
		}

		::SysFreeString(bsUID);
	}
	else if (!strButtonText.Compare(_T("Delete Study")))
	{
		BSTR bsUID = strUID.AllocSysString();
		if (S_OK == m_pIDBPIM->DeleteStudyInfo(bsUID))
		{
			AfxMessageBox(_T("Succeed: m_pIDBPIM->DeleteStudyInfo(bsUID)"));
		}
		else
		{
			AfxMessageBox(_T("Error: m_pIDBPIM->DeleteStudyInfo(bsUID)"));
		}

		::SysFreeString(bsUID);
	}
	else if (!strButtonText.Compare(_T("Delete Series")))
	{
		BSTR bsUID = strUID.AllocSysString();
		if (S_OK == m_pIDBPIM->DeleteSeriesInfo(bsUID))
		{
			AfxMessageBox(_T("Succeed: m_pIDBPIM->DeleteSeriesInfo(bsUID)"));
		}
		else
		{
			AfxMessageBox(_T("Error: m_pIDBPIM->DeleteSeriesInfo(bsUID)"));
		}

		::SysFreeString(bsUID);
	}
	else if (!strButtonText.Compare(_T("Delete Image")))
	{
		BSTR bsUID = strUID.AllocSysString();
		if (S_OK == m_pIDBPIM->DeleteImageInfo(bsUID))
		{
			AfxMessageBox(_T("Succeed: m_pIDBPIM->DeleteImageInfo(bsUID)"));
		}
		else
		{
			AfxMessageBox(_T("Error: m_pIDBPIM->DeleteImageInfo(bsUID)"));
		}

		::SysFreeString(bsUID);
	}
	else
	{
		AfxMessageBox(_T("Error"));
		return;
	}
}

void CPatientAdminDlg::OnButtonViewImage() 
{
	// TODO: Add your control notification handler code here
// 	CString strUID;
// 	BSTR bsUID;
// 
// 	POSITION pos;
// 	int nSeriesItem = -1;
// 
// 	pos = m_lstSeries.GetFirstSelectedItemPosition();
// 	if (pos == NULL)
// 	{
// 		AfxMessageBox(_T("Plz select a series"));
// 		return;
// 	}
// 	else
// 	{			
// 		nSeriesItem = m_lstSeries.GetNextSelectedItem(pos);
// 	}
// 
// 	strUID = m_lstSeries.GetItemText(nSeriesItem, 0);
// 	bsUID = strUID.AllocSysString();
// 
// 	HRESULT hResult = m_pIDBPIM->GetSeriesInfo(bsUID, m_SeriesImagesDlg.GetSeriesInfoStruct());
// 	::SysFreeString(bsUID);
// 	if (S_OK != hResult)
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBPIM->GetSeriesInfo()"));
// 		return;
// 	}
// 
// 	// 设置后处理结构
// 	hResult = m_pIDBPIM->GetPostProcessingInfo(bsUID, m_SeriesImagesDlg.GetPostProcessInfo());
// 	::SysFreeString(bsUID);
// 	if (S_OK != hResult)
// 	{
// 		AfxMessageBox(_T("Error: m_pIDBPIM->GetPostProcessingInfo()"));
// 		return;
// 	}
// 
// 	// 设置图像路径及图像数
// 	
// 	CString strImagePath = _T("E:\\images");
// 	strImagePath += CString(m_SeriesImagesDlg.GetSeriesInfoStruct()->bsImageFilePath);
// 	m_SeriesImagesDlg.SetImagePath(strImagePath);
// 
// 	INT iImageNum = m_SeriesImagesDlg.GetSeriesInfoStruct()->lNumberofImages;
// 	INT iImageStartIndex = m_SeriesImagesDlg.GetSeriesInfoStruct()->iRunStartIndex;
// 	m_SeriesImagesDlg.SetImageNum(iImageNum, iImageStartIndex);
// 
// 	m_SeriesImagesDlg.ShowImage(1);

}

