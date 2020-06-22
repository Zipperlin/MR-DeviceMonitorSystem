// DiscImportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "DiscImportDlg.h"
#include "TestClientSrcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDiscImportDlg dialog


CDiscImportDlg::CDiscImportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiscImportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiscImportDlg)
	//}}AFX_DATA_INIT
	m_DiscImportState = enumSubModuleState_UnInited;
	m_bLVN_ITEMCHANGING_Enable = TRUE;
	m_bGetDiscInfoReady = FALSE;
}

CDiscImportDlg::~CDiscImportDlg()
{
}

void CDiscImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiscImportDlg)
	DDX_Control(pDX, IDC_LIST_IMAGE, m_listImage);
	DDX_Control(pDX, IDC_LIST_IMPORT_SERIES, m_listImportSeries);
	DDX_Control(pDX, IDC_LIST_STUDY, m_listStudy);
	DDX_Control(pDX, IDC_LIST_SERIES, m_listSeries);
	DDX_Control(pDX, IDC_LIST_PATIENT, m_listPatient);
	DDX_Control(pDX, IDC_COMBO_IMPORT_DEVICE, m_cbDevices);
	//}}AFX_DATA_MAP
}

BOOL CDiscImportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_imgState.Create(IDB_BITMAP_STATE,13, 1, RGB(255,255,255));
	m_listPatient.SetImageList(&m_imgState,LVSIL_STATE);
	m_listStudy.SetImageList(&m_imgState,LVSIL_STATE);
	m_listSeries.SetImageList(&m_imgState,LVSIL_STATE);


	// Patient
	DWORD dwStype = m_listPatient.GetExtendedStyle();
//	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	dwStype |= LVS_EX_GRIDLINES;
	m_listPatient.SetExtendedStyle(dwStype);
	m_listPatient.SetCheck(0, FALSE);

	m_listPatient.InsertColumn(0, _T("Status"), LVCFMT_LEFT, 100);
	m_listPatient.InsertColumn(1, _T("PatientID"), LVCFMT_LEFT, 100);
	m_listPatient.InsertColumn(2, _T("PatientName"), LVCFMT_LEFT, 100);
	m_listPatient.InsertColumn(3, _T("Gender"), LVCFMT_LEFT, 100);
	m_listPatient.InsertColumn(4, _T("BirthDate"), LVCFMT_LEFT, 100);
	m_listPatient.InsertColumn(5, _T("StudyNum"), LVCFMT_LEFT, 100);
	m_listPatient.InsertColumn(6, _T(""), LVCFMT_LEFT, 0);

	// Study
	dwStype = m_listStudy.GetExtendedStyle();
//	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	dwStype |= LVS_EX_GRIDLINES;
	m_listStudy.SetExtendedStyle(dwStype);
	m_listStudy.SetCheck(0, FALSE);

	m_listStudy.InsertColumn(0, _T("Status"), LVCFMT_LEFT, 0);
	m_listStudy.InsertColumn(1, _T("StudyID"), LVCFMT_LEFT, 100);
	m_listStudy.InsertColumn(2, _T("StartDateTime"), LVCFMT_LEFT, 150);
	m_listStudy.InsertColumn(3, _T("RefPhisician"), LVCFMT_LEFT, 100);
	m_listStudy.InsertColumn(4, _T("SeriesNum"), LVCFMT_LEFT, 100);
	m_listStudy.InsertColumn(5, _T("Description"), LVCFMT_LEFT, 100);
	m_listStudy.InsertColumn(6, _T(""), LVCFMT_LEFT, 0);

	// Series
	dwStype = m_listSeries.GetExtendedStyle();
//	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	dwStype |= LVS_EX_GRIDLINES;
	m_listSeries.SetExtendedStyle(dwStype);
	m_listSeries.SetCheck(0, FALSE);

	m_listSeries.InsertColumn(0, _T("Status"), LVCFMT_LEFT, 0);
	m_listSeries.InsertColumn(1, _T("SeriesID"), LVCFMT_LEFT, 100);
	m_listSeries.InsertColumn(2, _T("AprRegionName"), LVCFMT_LEFT, 100);
	m_listSeries.InsertColumn(3, _T("ImageNum"), LVCFMT_LEFT, 100);
	m_listSeries.InsertColumn(4, _T(""), LVCFMT_LEFT, 0);
	m_listSeries.InsertColumn(5, _T(""), LVCFMT_LEFT, 0);
	m_listSeries.InsertColumn(6, _T(""), LVCFMT_LEFT, 0);

	// Image
	dwStype = m_listImage.GetExtendedStyle();
//	dwStype |= LVS_EX_CHECKBOXES;
	dwStype |= LVS_EX_FULLROWSELECT;
	dwStype |= LVS_EX_GRIDLINES;
	m_listImage.SetExtendedStyle(dwStype);
	m_listImage.SetCheck(0, FALSE);

	m_listImage.InsertColumn(0, _T("Status"), LVCFMT_LEFT, 0);
	m_listImage.InsertColumn(1, _T("ImageID"), LVCFMT_LEFT, 100);
	m_listImage.InsertColumn(2, _T("AprOrganName"), LVCFMT_LEFT, 100);
	m_listImage.InsertColumn(3, _T("Row"), LVCFMT_LEFT, 100);
	m_listImage.InsertColumn(4, _T("Column"), LVCFMT_LEFT, 100);
	m_listImage.InsertColumn(5, _T(""), LVCFMT_LEFT, 0);
	m_listImage.InsertColumn(6, _T(""), LVCFMT_LEFT, 0);


	// Get Devices
	BSTR* pbsDevices = NULL;
	long lLen = 0;
	HRESULT hResult = CTestClientSrcDlg::m_pIPADiscImport->GetDiscImportDevices(&pbsDevices, &lLen);
	if (S_OK == hResult)
	{
		for (int i = 0; i < lLen; i++)
		{
			CString strDevice = _com_util::ConvertBSTRToString(*(pbsDevices+i));
			m_cbDevices.InsertString(i, strDevice);
		}
		m_cbDevices.SetCurSel(0);
	}
	else
	{
		AfxMessageBox(_T("hResult = CTestClientSrcDlg::m_pIPADiscImport->GetDiscImportDevices()"));
	}
	
	CoTaskMemFree(pbsDevices);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CDiscImportDlg, CDialog)
	//{{AFX_MSG_MAP(CDiscImportDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PATIENT, OnClickListPatient)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STUDY, OnClickListStudy)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SERIES, OnClickListSeries)
	ON_CBN_SELCHANGE(IDC_COMBO_IMPORT_DEVICE, OnSelchangeComboImportDevice)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, OnButtonImport)
	ON_NOTIFY(HDN_DIVIDERDBLCLICK, IDC_LIST_PATIENT, OnDividerdblclickListPatient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiscImportDlg message handlers

void CDiscImportDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	
	if (!m_bGetDiscInfoReady)
	{
		HRESULT hResult = CTestClientSrcDlg::m_pIPADiscImport->CancelGetImportDiscInfo();
		if (S_OK != hResult)
		{
			AfxMessageBox(_T("CTestClientSrcDlg::m_pIPADiscImport->CancelGetImportDiscInfo()"));
		}
	}

	OnOK();
}

void CDiscImportDlg::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here
	m_bGetDiscInfoReady = FALSE;

	GetDlgItem(IDC_COMBO_IMPORT_DEVICE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REFRESH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_IMPORT)->EnableWindow(FALSE);
	

	m_listPatient.DeleteAllItems();
	m_listStudy.DeleteAllItems();
	m_listSeries.DeleteAllItems();

	m_vtrPatient.clear();
	m_vtrStudy.clear();
	m_vtrSeries.clear();
	m_vtrImage.clear();

	
	CString strDevice;
	GetDlgItem(IDC_COMBO_IMPORT_DEVICE)->GetWindowText(strDevice);
	if (strDevice.IsEmpty())
	{
		AfxMessageBox(_T("No Selected Device"));
		GetDlgItem(IDC_COMBO_IMPORT_DEVICE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_REFRESH)->EnableWindow(TRUE);
		return;
	}

	BSTR bsDevice = strDevice.AllocSysString();
	HRESULT hResult = CTestClientSrcDlg::m_pIPADiscImport->GetImportDiscInfoNotify(bsDevice);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPADiscImport->GetImportDiscInfoNotify()"));
		GetDlgItem(IDC_COMBO_IMPORT_DEVICE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_REFRESH)->EnableWindow(TRUE);
		return;
	}

}

void CDiscImportDlg::UpDateImportDiscInfo(BOOL bReady)
{
	if (!bReady)
	{
		GetDlgItem(IDC_COMBO_IMPORT_DEVICE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_REFRESH)->EnableWindow(TRUE);
	}

	m_bGetDiscInfoReady = TRUE;

	DiscImportPatientInfo* pPatients = NULL;
	DiscImportStudyInfo* pStudies = NULL;
	DiscImportSeriesInfo* pSeries = NULL;
	DiscImportImageInfo* pImages = NULL;
	long lPatientNum = 0;
	long lStudyNum = 0;
	long lSeriesNum = 0;
	long lImageNum = 0;

	HRESULT hResult = CTestClientSrcDlg::m_pIPADiscImport->GetImportDiscInfo(&pPatients, &lPatientNum, &pStudies, &lStudyNum, &pSeries, &lSeriesNum, &pImages, &lImageNum);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPADiscImport->GetImportDiscInfo()"));
		GetDlgItem(IDC_COMBO_IMPORT_DEVICE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_REFRESH)->EnableWindow(TRUE);
		return;
	}

	// Patient
	for (int i = 0; i < lPatientNum; i++)
	{
		DiscImportPatientStruct dips;
		dips.strPatientUID = _com_util::ConvertBSTRToString(((DiscImportPatientInfo*)(pPatients + i))->bsPatientUID);

		dips.enumSelectState = enumUnSelected;

		dips.strPatientID = _com_util::ConvertBSTRToString(((DiscImportPatientInfo*)(pPatients + i))->bsPatientID);
		dips.strPatientName = _com_util::ConvertBSTRToString(((DiscImportPatientInfo*)(pPatients + i))->bsPatientName);
		switch (((DiscImportPatientInfo*)(pPatients + i))->iPatientGender)
		{
		case 0:
			dips.strPatientGender = _T("Male");
			break;
		case 1:
			dips.strPatientGender = _T("Female");
			break;
		default:
			dips.strPatientGender = _T("Other");
			break;
		}
		dips.dtBirthDate = ((DiscImportPatientInfo*)(pPatients + i))->dtBirthDate;
		dips.uStudyNum = ((DiscImportPatientInfo*)(pPatients + i))->uStudyNum;

		m_vtrPatient.push_back(dips);
	}

	// Study
	for (i = 0; i < lStudyNum; i++)
	{
		DiscImportStudyStruct dists;
		dists.strStudyUID = _com_util::ConvertBSTRToString(((DiscImportStudyInfo*)(pStudies + i))->bsStudyUID);
		dists.strPatientUID = _com_util::ConvertBSTRToString(((DiscImportStudyInfo*)(pStudies + i))->bsPatientUID);

		dists.enumSelectState = enumUnSelected;

		dists.strStudyID = _com_util::ConvertBSTRToString(((DiscImportStudyInfo*)(pStudies + i))->bsStudyID);
		dists.dtStudyDateTime = ((DiscImportStudyInfo*)(pStudies + i))->dtStudyDateTime;
		dists.strRefPhisicianName = _com_util::ConvertBSTRToString(((DiscImportStudyInfo*)(pStudies + i))->bsRefPhisicianName);
		dists.strStudyDescription = _com_util::ConvertBSTRToString(((DiscImportStudyInfo*)(pStudies + i))->bsStudyDescription);
		dists.uSeriesNum = ((DiscImportStudyInfo*)(pStudies + i))->uSeriesNum;

		m_vtrStudy.push_back(dists);
	}

	//Series
	for (i = 0; i < lSeriesNum; i++)
	{
		DiscImportSeriesStruct dises;
		dises.strSeriesUID = _com_util::ConvertBSTRToString(((DiscImportSeriesInfo*)(pSeries + i))->bsSeriesUID);
		dises.strStudyUID = _com_util::ConvertBSTRToString(((DiscImportSeriesInfo*)(pSeries + i))->bsStudyUID);

		dises.enumSelectState = enumUnSelected;

		dises.strSeriesID = _com_util::ConvertBSTRToString(((DiscImportSeriesInfo*)(pSeries + i))->bsSeriesID);
		dises.strAprRegionName = CBSTROpt::BSTRToCString(((DiscImportSeriesInfo*)(pSeries + i))->bsAprRegionName);
		dises.uImageNum = ((DiscImportSeriesInfo*)(pSeries + i))->uImageNum;

		m_vtrSeries.push_back(dises);
	}

	// Image
	for (i = 0; i < lImageNum; i++)
	{
		DiscImportImageStruct diis;
		diis.strImageUID = _com_util::ConvertBSTRToString(((DiscImportImageInfo*)(pImages + i))->bsImageUID);
		diis.strSeriesUID = _com_util::ConvertBSTRToString(((DiscImportImageInfo*)(pImages + i))->bsSeriesUID);
		diis.strImageID = _com_util::ConvertBSTRToString(((DiscImportImageInfo*)(pImages + i))->bsImageID);
		diis.strAprOrganName = _com_util::ConvertBSTRToString(((DiscImportImageInfo*)(pImages + i))->bsAprOrganName);
		diis.uRows = ((DiscImportImageInfo*)(pImages + i))->uRows;
		diis.uColumns = ((DiscImportImageInfo*)(pImages + i))->uColumns;

		diis.enumSelectState = enumUnSelected;

		m_vtrImage.push_back(diis);
	}

	if (NULL != pPatients)
	{
		CoTaskMemFree(pPatients);
	}
	if (NULL != pStudies)
	{
		CoTaskMemFree(pStudies);
	}
	if (NULL != pSeries)
	{
		CoTaskMemFree(pSeries);
	}
	if (NULL != pImages)
	{
		CoTaskMemFree(pImages);
	}

	UpdatePatientInfo();

	GetDlgItem(IDC_COMBO_IMPORT_DEVICE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_REFRESH)->EnableWindow(TRUE);

}

void CDiscImportDlg::UpDateImportDiscInfoState(LPCTSTR szState)
{
	GetDlgItem(IDC_EDIT_GET_DI_STATE)->SetWindowText(szState);
}

void CDiscImportDlg::UpdatePatientInfo()
{
	m_bLVN_ITEMCHANGING_Enable = FALSE;

	m_listPatient.DeleteAllItems();
	
	// InsertPatient
	CString strInfo;
	for (int i = 0; i < m_vtrPatient.size(); i++)
	{
		LVITEM tvinsert;
		tvinsert.mask=LVIF_IMAGE|LVIF_TEXT|LVIF_STATE;
		tvinsert.iItem=i;
		tvinsert.iSubItem=0;
		int nState = 0;
		switch (m_vtrPatient[i].enumSelectState)
		{
		case enumUnSelected:
			nState = 2;
			break;
		case enumPartlySelected:
			nState = 3;
			break;
		case enumSelected:
			nState = 4;
			break;
		default:
			nState = 0;
			break;
		}
		tvinsert.state=INDEXTOSTATEIMAGEMASK(nState);
		tvinsert.stateMask=LVIS_STATEIMAGEMASK;
		tvinsert.pszText=_T("");
		tvinsert.cchTextMax=6;
		tvinsert.lParam=0;
		tvinsert.iImage=1;
		
 		m_listPatient.InsertItem(&tvinsert);

// 		m_listPatient.InsertItem(i, _T(""));

		// checkbox state
//		m_listPatient.SetItemState(i, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK);

//		m_listPatient.SetCheck(i, m_vtrPatient[i].bSelected);

 		m_listPatient.SetItemText(i, 1, m_vtrPatient[i].strPatientID);

 		m_listPatient.SetItemText(i, 2, m_vtrPatient[i].strPatientName);
		
		m_listPatient.SetItemText(i, 3, m_vtrPatient[i].strPatientGender);

		COleDateTime odtDateTime = m_vtrPatient[i].dtBirthDate;
		strInfo = odtDateTime.Format(_T("%Y-%m-%d"));
		m_listPatient.SetItemText(i, 4, strInfo);

		strInfo.Format(_T("%d"), m_vtrPatient[i].uStudyNum);
		m_listPatient.SetItemText(i, 5, strInfo);

		m_listPatient.SetItemText(i, 6, m_vtrPatient[i].strPatientUID);


//		m_listPatient.SetItemState(i, INDEXTOSTATEIMAGEMASK(nState), LVIS_STATEIMAGEMASK);
	}

// 	LVITEM tvinsert;
// 	tvinsert.mask=LVIF_IMAGE|LVIF_TEXT|LVIF_STATE;
// 	tvinsert.iItem=i;
// 	tvinsert.iSubItem=0;
// 	tvinsert.state=INDEXTOSTATEIMAGEMASK(1);
// 	tvinsert.stateMask=LVIS_STATEIMAGEMASK;
// 	
// 	tvinsert.pszText=_T("");
// 	tvinsert.cchTextMax=6;
// 	
// 	tvinsert.lParam=0;
// 	
// 	tvinsert.iImage=0;
// 
// 	m_listPatient.InsertItem(&tvinsert);
	
	if (i > 0)
	{
		m_listPatient.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
		m_listPatient.SetItemTextColor(0, COLORREF(RGB(255, 255, 255)));
		m_listPatient.SetItemBkColor(0, COLORREF(RGB(49, 106, 197)));
		m_listPatient.RedrawItems(0, 0);

		CString strPatientUID = m_listPatient.GetItemText(0, 6);
		UpdateStudyInfo(strPatientUID);
	}

	m_bLVN_ITEMCHANGING_Enable = TRUE;
}

void CDiscImportDlg::UpdateStudyInfo(LPCTSTR szPatientUID)
{
	m_bLVN_ITEMCHANGING_Enable = FALSE;

	m_listStudy.DeleteAllItems();

	CString strInfo;
	int j = 0;
	for (int i = 0; i < m_vtrStudy.size(); i++)
	{
		if (!m_vtrStudy[i].strPatientUID.CompareNoCase(szPatientUID))
		{
			LVITEM tvinsert;
			tvinsert.mask=LVIF_IMAGE|LVIF_TEXT|LVIF_STATE;
			tvinsert.iItem=j;
			tvinsert.iSubItem=0;
			int nState = 0;
			switch (m_vtrStudy[i].enumSelectState)
			{
			case enumUnSelected:
				nState = 2;
				break;
			case enumPartlySelected:
				nState = 3;
				break;
			case enumSelected:
				nState = 4;
				break;
			default:
				nState = 0;
				break;
			}
			tvinsert.state=INDEXTOSTATEIMAGEMASK(nState);
			tvinsert.stateMask=LVIS_STATEIMAGEMASK;
			tvinsert.pszText=_T("");
			tvinsert.cchTextMax=6;
			tvinsert.lParam=0;
			tvinsert.iImage=1;
			
 			m_listStudy.InsertItem(&tvinsert);

// 			m_listStudy.InsertItem(j, _T(""));
//			m_listStudy.SetCheck(j, m_vtrStudy[i].bSelected);

 			m_listStudy.SetItemText(j, 1, m_vtrStudy[i].strStudyID);

 			COleDateTime odtDateTime = m_vtrStudy[i].dtStudyDateTime;
			strInfo = odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
			m_listStudy.SetItemText(j, 2, strInfo);

			m_listStudy.SetItemText(j, 3, m_vtrStudy[i].strRefPhisicianName);
			
			strInfo.Format(_T("%d"), m_vtrStudy[i].uSeriesNum);
			m_listStudy.SetItemText(j, 4, strInfo);
			
			m_listStudy.SetItemText(j, 5, m_vtrStudy[i].strStudyDescription);

			m_listStudy.SetItemText(j, 6, m_vtrStudy[i].strStudyUID);


//			m_listStudy.SetItemState(j, INDEXTOSTATEIMAGEMASK(nState), LVIS_STATEIMAGEMASK);

			++j;
		}
	}
	
	if (j > 0)
	{
		m_listStudy.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
		m_listStudy.SetItemTextColor(0, COLORREF(RGB(255, 255, 255)));
		m_listStudy.SetItemBkColor(0, COLORREF(RGB(49, 106, 197)));
		m_listStudy.RedrawItems(0, m_listStudy.GetItemCount());

		CString strStudyUID = m_listStudy.GetItemText(0, 6);

		UpdateSeriesInfo(strStudyUID);
	}

	m_bLVN_ITEMCHANGING_Enable = TRUE;

}

void CDiscImportDlg::UpdateSeriesInfo(LPCTSTR szStudyUID)
{
	m_bLVN_ITEMCHANGING_Enable = FALSE;

	m_listSeries.DeleteAllItems();

	CString strInfo;
	int j = 0;
	for (int i = 0; i < m_vtrSeries.size(); i++)
	{
		if (!m_vtrSeries[i].strStudyUID.CompareNoCase(szStudyUID))
		{
			LVITEM tvinsert;
			tvinsert.mask=LVIF_IMAGE|LVIF_TEXT|LVIF_STATE;
			tvinsert.iItem=j;
			tvinsert.iSubItem=0;
			int nState = 0;
			switch (m_vtrSeries[i].enumSelectState)
			{
			case enumUnSelected:
				nState = 2;
				break;
			case enumPartlySelected:
				nState = 3;
				break;
			case enumSelected:
				nState = 4;
				break;
			default:
				nState = 0;
				break;
			}
			tvinsert.state=INDEXTOSTATEIMAGEMASK(nState);
			tvinsert.stateMask=LVIS_STATEIMAGEMASK;
			tvinsert.pszText=_T("");
			tvinsert.cchTextMax=6;
			tvinsert.lParam=0;
			tvinsert.iImage=1;
			
 			m_listSeries.InsertItem(&tvinsert);
// 			m_listSeries.InsertItem(j, _T(""));
//			m_listSeries.SetCheck(j, m_vtrSeries[i].bSelected);
		
 			m_listSeries.SetItemText(j, 1, m_vtrSeries[i].strSeriesID);


 			m_listSeries.SetItemText(j, 2, m_vtrSeries[i].strAprRegionName);

			strInfo.Format(_T("%d"), m_vtrSeries[i].uImageNum);
			m_listSeries.SetItemText(j, 3, strInfo);
			

			m_listSeries.SetItemText(j, 6, m_vtrSeries[i].strSeriesUID);

//			m_listSeries.SetItemState(j, INDEXTOSTATEIMAGEMASK(nState), LVIS_STATEIMAGEMASK);

			++j;
		}
	}

	if (j > 0)
	{
		m_listSeries.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
		m_listSeries.SetItemTextColor(0, COLORREF(RGB(255, 255, 255)));
		m_listSeries.SetItemBkColor(0, COLORREF(RGB(49, 106, 197)));
		m_listSeries.RedrawItems(0, m_listSeries.GetItemCount());

		CString strSeriesUID = m_listSeries.GetItemText(0, 6);

		UpdateImageInfo(strSeriesUID);
	}


	m_bLVN_ITEMCHANGING_Enable = TRUE;

}

void CDiscImportDlg::UpdateImageInfo(LPCTSTR szSeriesUID)
{
	m_bLVN_ITEMCHANGING_Enable = FALSE;

	m_listImage.DeleteAllItems();

	CString strInfo;
	int j = 0;
	for (int i = 0; i < m_vtrImage.size(); i++)
	{
		if (!m_vtrImage[i].strSeriesUID.CompareNoCase(szSeriesUID))
		{
			LVITEM tvinsert;
			tvinsert.mask=LVIF_IMAGE|LVIF_TEXT|LVIF_STATE;
			tvinsert.iItem=j;
			tvinsert.iSubItem=0;
			int nState = 0;
			switch (m_vtrImage[i].enumSelectState)
			{
			case enumUnSelected:
				nState = 2;
				break;
			case enumPartlySelected:
				nState = 3;
				break;
			case enumSelected:
				nState = 4;
				break;
			default:
				nState = 0;
				break;
			}
			tvinsert.state=INDEXTOSTATEIMAGEMASK(nState);
			tvinsert.stateMask=LVIS_STATEIMAGEMASK;
			tvinsert.pszText=_T("");
			tvinsert.cchTextMax=6;
			tvinsert.lParam=0;
			tvinsert.iImage=1;
			
 			m_listImage.InsertItem(&tvinsert);
			CString str = m_vtrImage[i].strImageID;
 			m_listImage.SetItemText(j, 1, m_vtrImage[i].strImageID);

 			m_listImage.SetItemText(j, 2, m_vtrImage[i].strAprOrganName);

			strInfo.Format(_T("%d"), m_vtrImage[i].uRows);
			m_listImage.SetItemText(j, 3, strInfo);
			
			strInfo.Format(_T("%d"), m_vtrImage[i].uColumns);
			m_listImage.SetItemText(j, 4, strInfo);

			m_listImage.SetItemText(j, 6, m_vtrImage[i].strSeriesUID);


			++j;
		}
	}

	m_bLVN_ITEMCHANGING_Enable = TRUE;
}

void CDiscImportDlg::EnableImportButton()
{
// 	for (int i = 0; i < m_vtrSeries.size(); i++)
// 	{
// 		if (enumSelected == m_vtrSeries[i].enumSelectState)
// 		{
// 			GetDlgItem(IDC_BUTTON_IMPORT)->EnableWindow(TRUE);
// 			break;
// 		}
// 	}
// 
// 	if (i == m_vtrSeries.size())
// 	{
// 		GetDlgItem(IDC_BUTTON_IMPORT)->EnableWindow(FALSE);
// 	}

	for (int i = 0; i < m_vtrPatient.size(); i++)
	{
		if (enumSelected == m_vtrPatient[i].enumSelectState)
		{
			GetDlgItem(IDC_BUTTON_IMPORT)->EnableWindow(TRUE);
			break;
		}
	}

	if (i == m_vtrPatient.size())
	{
		GetDlgItem(IDC_BUTTON_IMPORT)->EnableWindow(FALSE);
	}

}

void CDiscImportDlg::UpdateSelectState()
{
	m_bLVN_ITEMCHANGING_Enable = FALSE;

	// Patient
	int iItemCount = m_listPatient.GetItemCount();
	for (int i = 0; i < iItemCount; i++)
	{
		CString strPatientUID = m_listPatient.GetItemText(i, 6);
		for (int j = 0; j < m_vtrPatient.size(); j++)
		{
			if (!strPatientUID.CompareNoCase(m_vtrPatient[j].strPatientUID))
			{
				switch (m_vtrPatient[j].enumSelectState)
				{
				case enumUnSelected:
					m_listPatient.SetItemState(i, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
					break;
				case enumPartlySelected:
					m_listPatient.SetItemState(i, INDEXTOSTATEIMAGEMASK(3), LVIS_STATEIMAGEMASK);
					break;
				case enumSelected:
					m_listPatient.SetItemState(i, INDEXTOSTATEIMAGEMASK(4), LVIS_STATEIMAGEMASK);
					break;
				default:
					break;
				}

				break;
			}
		}
	}

	// Study
	iItemCount = m_listStudy.GetItemCount();
	for (i = 0; i < iItemCount; i++)
	{
		CString strStudyUID = m_listStudy.GetItemText(i, 6);
		for (int j = 0; j < m_vtrStudy.size(); j++)
		{
			if (!strStudyUID.CompareNoCase(m_vtrStudy[j].strStudyUID))
			{
				switch (m_vtrStudy[j].enumSelectState)
				{
				case enumUnSelected:
					m_listStudy.SetItemState(i, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
					break;
				case enumPartlySelected:
					m_listStudy.SetItemState(i, INDEXTOSTATEIMAGEMASK(3), LVIS_STATEIMAGEMASK);
					break;
				case enumSelected:
					m_listStudy.SetItemState(i, INDEXTOSTATEIMAGEMASK(4), LVIS_STATEIMAGEMASK);
					break;
				default:
					break;
				}

				break;
			}
		}
	}


	// Series
	iItemCount = m_listSeries.GetItemCount();
	for (i = 0; i < iItemCount; i++)
	{
		CString strSeriesUID = m_listSeries.GetItemText(i, 6);
		for (int j = 0; j < m_vtrSeries.size(); j++)
		{
			if (!strSeriesUID.CompareNoCase(m_vtrSeries[j].strSeriesUID))
			{
				switch (m_vtrSeries[j].enumSelectState)
				{
				case enumUnSelected:
					m_listSeries.SetItemState(i, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
					break;
				case enumPartlySelected:
					m_listSeries.SetItemState(i, INDEXTOSTATEIMAGEMASK(3), LVIS_STATEIMAGEMASK);
					break;
				case enumSelected:
					m_listSeries.SetItemState(i, INDEXTOSTATEIMAGEMASK(4), LVIS_STATEIMAGEMASK);
					break;
				default:
					break;
				}

				break;
			}
		}
	}

	m_bLVN_ITEMCHANGING_Enable = TRUE;
}


void CDiscImportDlg::OnClickListPatient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;


    if(pNMListView->iItem == -1)
		return;

	for (int i = 0; i < m_listPatient.GetItemCount(); i++)
	{
		m_listPatient.SetItemTextColor(i, COLORREF(RGB(0,0,0)));
		m_listPatient.SetItemBkColor(i, COLORREF(RGB(255, 255, 255)));
	}
	
	CString strPatientUID = m_listPatient.GetItemText(pNMListView->iItem, 6);

	m_listPatient.SetItemState(pNMListView->iItem, LVIS_SELECTED, LVIS_SELECTED);
	m_listPatient.SetItemTextColor(pNMListView->iItem, COLORREF(RGB(255, 255, 255)));
	m_listPatient.SetItemBkColor(pNMListView->iItem, COLORREF(RGB(49, 106, 197)));
	
	m_listPatient.RedrawItems(0, m_listPatient.GetItemCount());

	// 是否checkbox区域

	if (pNMListView->ptAction.x <= 13)
	{
		// 点击在checkbox区域
		UINT nState = m_listPatient.GetItemState(pNMListView->iItem, TVIS_STATEIMAGEMASK ) >> 12;
		nState=(nState==4)?2:4;
		m_listPatient.SetItemState(pNMListView->iItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );

		// 更改该患者的选择属性
		for (int i = 0; i < m_vtrPatient.size(); i++)
		{
			if (!m_vtrPatient[i].strPatientUID.Compare(strPatientUID))
			{
				m_vtrPatient[i].enumSelectState = (nState==4)?enumSelected:enumUnSelected;
				break;
			}	
		}

// 		//更改该患者所有的Study及Series选择属性
// 		for (i = 0; i < m_vtrStudy.size(); i++)
// 		{
// 			if (!m_vtrStudy[i].strPatientUID.Compare(strPatientUID))
// 			{
// 				m_vtrStudy[i].enumSelectState = (nState==4)?enumSelected:enumUnSelected;
// 
// 				for (int j = 0; j < m_vtrSeries.size(); j++)
// 				{
// 					if (!m_vtrSeries[j].strStudyUID.Compare(m_vtrStudy[i].strStudyUID))
// 					{
// 						m_vtrSeries[j].enumSelectState = (nState==4)?enumSelected:enumUnSelected;
// 					}
// 				}
// 			}
// 		}
// 
// 
// 		UpdateSelectState();

	}
	
//	m_listPatient.SetItemState(pNMListView->iItem, LVIS_SELECTED, LVIS_SELECTED);

	// 更新显示
	UpdateStudyInfo(strPatientUID);

	EnableImportButton();
}

void CDiscImportDlg::OnClickListStudy(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

    if(pNMListView->iItem == -1)
		return;

	
	for (int i = 0; i < m_listStudy.GetItemCount(); i++)
	{
		m_listStudy.SetItemTextColor(i, COLORREF(RGB(0,0,0)));
		m_listStudy.SetItemBkColor(i, COLORREF(RGB(255, 255, 255)));
	}
	
	CString strStudyUID = m_listStudy.GetItemText(pNMListView->iItem, 6);
	CString strPatientUID;

	m_listStudy.SetItemState(pNMListView->iItem, LVIS_SELECTED, LVIS_SELECTED);
	m_listStudy.SetItemTextColor(pNMListView->iItem, COLORREF(RGB(255, 255, 255)));
	m_listStudy.SetItemBkColor(pNMListView->iItem, COLORREF(RGB(49, 106, 197)));
	
	m_listStudy.RedrawItems(0, m_listStudy.GetItemCount());

// 	if (pNMListView->ptAction.x <= 13)
// 	{
// 		//点击在checkbox区域
// 		UINT nState = m_listStudy.GetItemState(pNMListView->iItem, TVIS_STATEIMAGEMASK ) >> 12;
// 		nState=(nState==4)?2:4;
// 		m_listStudy.SetItemState(pNMListView->iItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
// 
// 		// 更改该Study的选择属性
// 		for (int i = 0; i < m_vtrStudy.size(); i++)
// 		{
// 			if (!m_vtrStudy[i].strStudyUID.Compare(strStudyUID))
// 			{
// 				m_vtrStudy[i].enumSelectState = (nState==4)?enumSelected:enumUnSelected;
// 				strPatientUID = m_vtrStudy[i].strPatientUID;
// 				break;
// 			}	
// 		}
// 
// 		//更改该检查所属Patient选择属性
// 
// 		//确定该PatientSelect属性
// 		SelectedState enumSelectState = enumUnSelected;
// 		BOOL bNoneSelected = TRUE;
// 		BOOL bAllSelected = TRUE;
// 		for (i = 0; i < m_vtrStudy.size(); i++)
// 		{
// 			if (!m_vtrStudy[i].strPatientUID.Compare(strPatientUID))
// 			{
// 				if (enumUnSelected == m_vtrStudy[i].enumSelectState)
// 				{
// 					bAllSelected = FALSE;
// 				}
// 				else if (enumSelected == m_vtrStudy[i].enumSelectState)
// 				{
// 					bNoneSelected = FALSE;
// 				}
// 				else
// 				{
// 					bNoneSelected = FALSE;
// 					bAllSelected = FALSE;
// 					break;
// 				}
// 			}
// 		}
// 
// 		if (bNoneSelected)
// 		{
// 			enumSelectState = enumUnSelected;
// 		}
// 		else if (bAllSelected)
// 		{
// 			enumSelectState = enumSelected;
// 		}
// 		else
// 		{
// 			enumSelectState = enumPartlySelected;
// 		}
// 
// 		//找到Patient并设置其Select属性
// 		for (i = 0; i < m_vtrPatient.size(); i++)
// 		{
// 			if (!m_vtrPatient[i].strPatientUID.Compare(strPatientUID))
// 			{
// 				m_vtrPatient[i].enumSelectState = enumSelectState;
// 				break;
// 			}
// 		}
// 
// 
// 		// 更改该Study所有Sereis的选择属性
// 		for (i = 0; i < m_vtrSeries.size(); i++)
// 		{
// 			if (!m_vtrSeries[i].strStudyUID.Compare(strStudyUID))
// 			{
// 				m_vtrSeries[i].enumSelectState = (nState==4)?enumSelected:enumUnSelected;
// 			}
// 		}
// 
// 
// 		UpdateSelectState();
// 
// 	}
// 
	UpdateSeriesInfo(strStudyUID);
// 
// 	EnableImportButton();

}

void CDiscImportDlg::OnClickListSeries(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if(pNMListView->iItem == -1)
		return;


	for (int i = 0; i < m_listSeries.GetItemCount(); i++)
	{
		m_listSeries.SetItemTextColor(i, COLORREF(RGB(0,0,0)));
		m_listSeries.SetItemBkColor(i, COLORREF(RGB(255, 255, 255)));
	}
	
	CString strSeriesUID = m_listSeries.GetItemText(pNMListView->iItem, 6);

	m_listSeries.SetItemState(pNMListView->iItem, LVIS_SELECTED, LVIS_SELECTED);
	m_listSeries.SetItemTextColor(pNMListView->iItem, COLORREF(RGB(255, 255, 255)));
	m_listSeries.SetItemBkColor(pNMListView->iItem, COLORREF(RGB(49, 106, 197)));
	
	m_listSeries.RedrawItems(0, m_listSeries.GetItemCount());

// 	if (pNMListView->ptAction.x <= 13)
// 	{
// 		//点击在checkbox区域
// 		UINT nState = m_listSeries.GetItemState(pNMListView->iItem, TVIS_STATEIMAGEMASK ) >> 12;
// 		nState=(nState==4)?2:4;
// 
// 		CString strSeriesUID = m_listSeries.GetItemText(pNMListView->iItem, 6);
// 		CString	strStudyUID;
// 		CString strPatientUID;
// 
// 		// 确定该序列的Select属性
// 		for (int i = 0; i < m_vtrSeries.size(); i++)
// 		{
// 			if (!m_vtrSeries[i].strSeriesUID.CompareNoCase(strSeriesUID))
// 			{
// 				m_vtrSeries[i].enumSelectState = (nState==4)?enumSelected:enumUnSelected;
// 				strStudyUID = m_vtrSeries[i].strStudyUID;
// 				break;
// 			}
// 		}
// 
// 		// 确定该Study的Selected属性
// 		SelectedState enumSelectState = enumUnSelected;
// 		BOOL bNoneSelected = TRUE;
// 		BOOL bAllSelected = TRUE;
// 		for (i = 0; i < m_vtrSeries.size(); i++)
// 		{
// 			if (!m_vtrSeries[i].strStudyUID.Compare(strStudyUID))
// 			{
// 				if (enumUnSelected == m_vtrSeries[i].enumSelectState)
// 				{
// 					bAllSelected = FALSE;
// 				}
// 				else if (enumSelected == m_vtrSeries[i].enumSelectState)
// 				{
// 					bNoneSelected = FALSE;
// 				}
// 				else
// 				{
// 					bNoneSelected = FALSE;
// 					bAllSelected = FALSE;
// 					break;
// 				}
// 			}
// 		}
// 
// 		if (bNoneSelected)
// 		{
// 			enumSelectState = enumUnSelected;
// 		}
// 		else if (bAllSelected)
// 		{
// 			enumSelectState = enumSelected;
// 		}
// 		else
// 		{
// 			enumSelectState = enumPartlySelected;
// 		}
// 
// 
// 		// 找到该study并设置bSelected
// 		for (i = 0; i < m_vtrStudy.size(); i++)
// 		{
// 			if (!m_vtrStudy[i].strStudyUID.CompareNoCase(strStudyUID))
// 			{
// 				m_vtrStudy[i].enumSelectState = enumSelectState;
// 				strPatientUID = m_vtrStudy[i].strPatientUID;
// 				break;
// 			}
// 		}
// 
// 		// 确定该Patient的Selected属性
// 		enumSelectState = enumUnSelected;
// 		bNoneSelected = TRUE;
// 		bAllSelected = TRUE;
// 
// 		for (i = 0; i < m_vtrStudy.size(); i++)
// 		{
// 			if (!m_vtrStudy[i].strPatientUID.Compare(strPatientUID))
// 			{
// 				if (enumUnSelected == m_vtrStudy[i].enumSelectState)
// 				{
// 					bAllSelected = FALSE;
// 				}
// 				else if (enumSelected == m_vtrStudy[i].enumSelectState)
// 				{
// 					bNoneSelected = FALSE;
// 				}
// 				else
// 				{
// 					bNoneSelected = FALSE;
// 					bAllSelected = FALSE;
// 					break;
// 				}
// 			}
// 		}
// 
// 		if (bNoneSelected)
// 		{
// 			enumSelectState = enumUnSelected;
// 		}
// 		else if (bAllSelected)
// 		{
// 			enumSelectState = enumSelected;
// 		}
// 		else
// 		{
// 			enumSelectState = enumPartlySelected;
// 		}
// 
// 		// 找到该patient并设置Select属性
// 		for (i = 0; i < m_vtrPatient.size(); i++)
// 		{
// 			if (!m_vtrPatient[i].strPatientUID.CompareNoCase(strPatientUID))
// 			{
// 				// 找到patient
// 				m_vtrPatient[i].enumSelectState = enumSelectState;
// 
// 				break;
// 			}
// 		}
// 
// 		UpdateSelectState();
// 	}
// 
// 	EnableImportButton();

	UpdateImageInfo(strSeriesUID);

}

void CDiscImportDlg::OnSelchangeComboImportDevice() 
{
	// TODO: Add your control notification handler code here
	OnButtonRefresh();
}

// void CDiscImportDlg::OnItemchangingListPatient(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
// 	// TODO: Add your control notification handler code here
// 	
// 	*pResult = 0;
// 
// 	if (!m_bLVN_ITEMCHANGING_Enable)
// 		return;
// 
// 	if (pNMListView->uOldState == 0 && pNMListView->uNewState == 0)   
// 		return; //   no   change   
// 	
// 	//   old   check   box   state   
// 	BOOL bPrevState = (BOOL)(((pNMListView->uOldState & LVIS_STATEIMAGEMASK)>>12)-1);   
// 	
// 	if (bPrevState < 0)   //   on   startup   there's   no   previous   state,so   assign   as   false   (unchecked)     
// 		bPrevState = 0;   
// 	
// 	//   new   check   box   state   
// 	BOOL bChecked = (BOOL)(((pNMListView->uNewState & LVIS_STATEIMAGEMASK)>>12)-1);   
// 	
// 	if (bChecked < 0)   //   on   non-checkbox   notifications   assume   false     
// 		bChecked = 0;   
// 	
// 	if (bPrevState == bChecked)//   no   change   in   check   box   
// 		return;
// 
// 	// check changed
// 	BOOL bSelectedState = FALSE;
// 	if (bChecked)
// 	{
// 		bSelectedState = TRUE;
// 	}
// 	else
// 	{
// 		bSelectedState = FALSE;
// 	}
// 
// 	// 改变选择状态
// 	CString strPatientUID = m_listPatient.GetItemText(pNMListView->iItem, 6);
// 
// 	// Patient
// 	for (int i = 0; i < m_vtrPatient.size(); i++)
// 	{
// 		if (!m_vtrPatient[i].strPatientUID.CompareNoCase(strPatientUID))
// 		{
// //			m_vtrPatient[i].bSelected = bSelectedState;
// 
// 			break;
// 		}
// 
// 	}
// 
// 	// Study and Series
// 	for (i = 0; i < m_vtrStudy.size(); i++)
// 	{
// 		if (!m_vtrStudy[i].strPatientUID.CompareNoCase(strPatientUID))
// 		{
// 			m_vtrStudy[i].bSelected = bSelectedState;
// 
// 			CString strStudyUID = m_vtrStudy[i].strStudyUID;
// 			for (int j = 0; j < m_vtrSeries.size(); j++)
// 			{
// 				if (!m_vtrSeries[j].strStudyUID.CompareNoCase(strStudyUID))
// 				{
// 					m_vtrSeries[j].bSelected = bSelectedState;
// 				}
// 			}
// 		}
// 	}
// 
// 	// 刷新显示
// 	UpdateSelectState();
// 
// 	// 更新Import按钮状态
// 	EnableImportButton();
// 
// }
// 
// void CDiscImportDlg::OnItemchangingListStudy(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
// 	// TODO: Add your control notification handler code here
// 	
// 	*pResult = 0;
// 
// 	if (!m_bLVN_ITEMCHANGING_Enable)
// 		return;
// 
// 	if (pNMListView->uOldState == 0 && pNMListView->uNewState == 0)   
// 		return; //   no   change   
// 	
// 	//   old   check   box   state   
// 	BOOL bPrevState = (BOOL)(((pNMListView->uOldState & LVIS_STATEIMAGEMASK)>>12)-1);   
// 	
// 	if (bPrevState < 0)   //   on   startup   there's   no   previous   state,so   assign   as   false   (unchecked)     
// 		bPrevState = 0;   
// 	
// 	//   new   check   box   state   
// 	BOOL bChecked = (BOOL)(((pNMListView->uNewState & LVIS_STATEIMAGEMASK)>>12)-1);   
// 	
// 	if (bChecked < 0)   //   on   non-checkbox   notifications   assume   false     
// 		bChecked = 0;   
// 	
// 	if (bPrevState == bChecked)//   no   change   in   check   box   
// 		return;
// 
// 	// check changed
// 	BOOL bSelectedState = FALSE;
// 	if (bChecked)
// 	{
// 		bSelectedState = TRUE;
// 	}
// 	else
// 	{
// 		bSelectedState = FALSE;
// 	}
// 
// 	// 改变选择状态
// 	CString strStudyUID = m_listStudy.GetItemText(pNMListView->iItem, 6);
// 	CString strPatientUID;
// 
// 	// Patient, Study and Series
// 	for (int i = 0; i < m_vtrStudy.size(); i++)
// 	{
// 		if (!m_vtrStudy[i].strStudyUID.CompareNoCase(strStudyUID))
// 		{
// 			m_vtrStudy[i].bSelected = bSelectedState;
// 
// 			strPatientUID = m_vtrStudy[i].strPatientUID;
// 
// 			// Series
// 			for (int k = 0; k < m_vtrSeries.size(); k++)
// 			{
// 				if (!m_vtrSeries[k].strStudyUID.CompareNoCase(strStudyUID))
// 				{
// 					m_vtrSeries[k].bSelected = bSelectedState;
// 				}
// 			}
// 
// 			break;
// 		}
// 	}
// 
// 	// Patient
// 	SelectedState enumSelectState = enumUnSelected;
// 	BOOL bNoneSelected = TRUE;
// 	BOOL bAllSelected = TRUE;
// 
// 	for (int k = 0; k < m_vtrStudy.size(); k++)
// 	{
// 		if (!m_vtrStudy[k].strPatientUID.CompareNoCase(strPatientUID))
// 		{
// 			if (!m_vtrStudy[k].bSelected)
// 			{
// 				bNoneSelected = FALSE;
// 			}
// 			else
// 			{
// 				bAllSelected = FALSE;
// 			}
// 		}
// 	}
// 
// 	if (bNoneSelected)
// 	{
// 		enumSelectState = enumUnSelected;
// 	}
// 	else if (bAllSelected)
// 	{
// 		enumSelectState = enumSelected;
// 	}
// 	else
// 	{
// 		enumSelectState = enumPartlySelected;
// 	}
// 
// 	for (int j = 0; j < m_vtrPatient.size(); j++)
// 	{
// 		if (!strPatientUID.CompareNoCase(m_vtrPatient[j].strPatientUID))
// 		{
// 			// 找到patient
// 			m_vtrPatient[j].enumSelectState = enumSelectState;
// 
// 			break;
// 		}
// 	}
// 
// 	UpdateSelectState();
// 
// 	// 更新Import按钮状态
// 	EnableImportButton();
// 
// }
// 
// void CDiscImportDlg::OnItemchangingListSeries(NMHDR* pNMHDR, LRESULT* pResult) 
// {
// 	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
// 	// TODO: Add your control notification handler code here
// 	
// 	*pResult = 0;
// 
// 	if (!m_bLVN_ITEMCHANGING_Enable)
// 		return;
// 
// 	if (pNMListView->uOldState == 0 && pNMListView->uNewState == 0)   
// 		return; //   no   change   
// 	
// 	//   old   check   box   state   
// 	BOOL bPrevState = (BOOL)(((pNMListView->uOldState & LVIS_STATEIMAGEMASK)>>12)-1);   
// 	
// 	if (bPrevState < 0)   //   on   startup   there's   no   previous   state,so   assign   as   false   (unchecked)     
// 		bPrevState = 0;   
// 	
// 	//   new   check   box   state   
// 	BOOL bChecked = (BOOL)(((pNMListView->uNewState & LVIS_STATEIMAGEMASK)>>12)-1);   
// 	
// 	if (bChecked < 0)   //   on   non-checkbox   notifications   assume   false     
// 		bChecked = 0;   
// 	
// 	if (bPrevState == bChecked)//   no   change   in   check   box   
// 		return;
// 
// 	// check changed
// 	BOOL bSelectedState = FALSE;
// 	if (bChecked)
// 	{
// 		bSelectedState = TRUE;
// 	}
// 	else
// 	{
// 		bSelectedState = FALSE;
// 	}
// 
// 	// 改变选择状态
// 
// 	CString strSeriesUID = m_listSeries.GetItemText(pNMListView->iItem, 6);
// 	CString strStudyUID;
// 	CString strPatientUID;
// 
// 	// 处理序列
// 	for (int i = 0; i < m_vtrSeries.size(); i++)
// 	{
// 		if (!m_vtrSeries[i].strSeriesUID.CompareNoCase(strSeriesUID))
// 		{
// 			m_vtrSeries[i].bSelected = bSelectedState;
// 			strStudyUID = m_vtrSeries[i].strStudyUID;
// 			break;
// 		}
// 	}
// 
// 	// 确定该Study的Selected属性
// 	BOOL bStudySelected = TRUE;
// 	for (i = 0; i < m_vtrSeries.size(); i++)
// 	{
// 		if (!m_vtrSeries[i].strStudyUID.CompareNoCase(strStudyUID))
// 		{
// 			if (!m_vtrSeries[i].bSelected)
// 			{
// 				bStudySelected = FALSE;
// 				break;
// 			}
// 		}
// 	}
// 
// 	// 找到该study并设置bSelected
// 	for (i = 0; i < m_vtrStudy.size(); i++)
// 	{
// 		if (!m_vtrStudy[i].strStudyUID.CompareNoCase(strStudyUID))
// 		{
// 			m_vtrStudy[i].bSelected = bStudySelected;
// 			strPatientUID = m_vtrStudy[i].strPatientUID;
// 			break;
// 		}
// 	}
// 
// 	// 确定该Patient的Selected属性
// 	SelectedState enumSelectState = enumUnSelected;
// 	BOOL bNoneSelected = TRUE;
// 	BOOL bAllSelected = TRUE;
// 
// 	for (int k = 0; k < m_vtrStudy.size(); k++)
// 	{
// 		if (!m_vtrStudy[k].strPatientUID.CompareNoCase(strPatientUID))
// 		{
// 			if (!m_vtrStudy[k].bSelected)
// 			{
// 				bNoneSelected = FALSE;
// 			}
// 			else
// 			{
// 				bAllSelected = FALSE;
// 			}
// 		}
// 	}
// 
// 	if (bNoneSelected)
// 	{
// 		enumSelectState = enumUnSelected;
// 	}
// 	else if (bAllSelected)
// 	{
// 		enumSelectState = enumSelected;
// 	}
// 	else
// 	{
// 		enumSelectState = enumPartlySelected;
// 	}
// 
// 	for (int j = 0; j < m_vtrPatient.size(); j++)
// 	{
// 		if (!strPatientUID.CompareNoCase(m_vtrPatient[j].strPatientUID))
// 		{
// 			// 找到patient
// 			m_vtrPatient[j].enumSelectState = enumSelectState;
// 
// 			break;
// 		}
// 	}
// 
// 
// 	UpdateSelectState();
// 	
// 
// 	// 更新Import按钮状态
// 	EnableImportButton();
// 
// }

void CDiscImportDlg::OnButtonImport() 
{
	// TODO: Add your control notification handler code here
	long lPatientNum = 0;
	for (int i = 0; i < m_vtrPatient.size(); i++)
	{
		if (enumSelected == m_vtrPatient[i].enumSelectState)
		{
			++lPatientNum;
		}
	}

	if (0 == lPatientNum)
	{
		AfxMessageBox(_T("No Patient Selected!"));
		return;
	}

	BSTR* pbsSeriesList = new BSTR[lPatientNum];
	int j = 0;
	for (i = 0; i < m_vtrPatient.size(); i++)
	{
		if (enumSelected == m_vtrPatient[i].enumSelectState)
		{
			*(pbsSeriesList + j) = m_vtrPatient[i].strPatientUID.AllocSysString();
			++j;
		}
	}

	HRESULT hResult = CTestClientSrcDlg::m_pIPADiscImport->DiscImport(lPatientNum, pbsSeriesList, enumPatientAdminUIDType_Patient);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPADiscImport->DiscImport()"));
	}

	delete [] pbsSeriesList;
	OnOK();

	// 
// 	DiscImport_SeriesStruct* pSeriesList = NULL;
// 	long lLen = 0;
// 
// 	hResult = CTestClientSrcDlg::m_pIPADiscImport->GetDiscImportSeries(&pSeriesList, &lLen);
// 	if (S_OK != hResult)
// 	{
// 		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPADiscImport->GetDiscImportSeries()"));
// 		return;
// 	}
// 
// 	//
// 	
// 	GetDlgItem(IDC_COMBO_IMPORT_DEVICE)->EnableWindow(FALSE);
// 	GetDlgItem(IDC_LIST_PATIENT)->ShowWindow(FALSE);
// 	GetDlgItem(IDC_LIST_STUDY)->ShowWindow(FALSE);
// 	GetDlgItem(IDC_LIST_SERIES)->ShowWindow(FALSE);
// 	GetDlgItem(IDC_BUTTON_REFRESH)->ShowWindow(FALSE);
// 	GetDlgItem(IDC_BUTTON_IMPORT)->ShowWindow(FALSE);
// 
// 	GetDlgItem(IDC_LIST_IMPORT_SERIES)->ShowWindow(TRUE);
// 
// 	DWORD dwStype = m_listImportSeries.GetExtendedStyle();
// 	dwStype |= LVS_EX_FULLROWSELECT;
// 	m_listImportSeries.SetExtendedStyle(dwStype);
// 	m_listImportSeries.SetCheck(0, FALSE);
// 
// 	m_listImportSeries.InsertColumn(0, _T("Index"), LVCFMT_LEFT, 50);
// 	m_listImportSeries.InsertColumn(1, _T("PatientID"), LVCFMT_LEFT, 100);
// 	m_listImportSeries.InsertColumn(2, _T("PatientName"), LVCFMT_LEFT, 100);
// 	m_listImportSeries.InsertColumn(3, _T("StudyID"), LVCFMT_LEFT, 70);
// 	m_listImportSeries.InsertColumn(4, _T("SeriesID"), LVCFMT_LEFT, 70);
// 	m_listImportSeries.InsertColumn(5, _T("State"), LVCFMT_LEFT, 70);
// 	m_listImportSeries.InsertColumn(6, _T("Progress"), LVCFMT_LEFT, 70);
// 	m_listImportSeries.InsertColumn(7, _T("Detail"), LVCFMT_LEFT, 600);
// 
// 	CString strInfo;
// 
// 	for (i = 0;	i < lLen; i++)
// 	{
// 		strInfo.Format(_T("%d"), (pSeriesList + i)->uIndex + 1);
//  		m_listImportSeries.InsertItem(i, strInfo);
// 
// 		strInfo = _com_util::ConvertBSTRToString((pSeriesList + i)->bsPatientID);
//  		m_listImportSeries.SetItemText(i, 1, strInfo);
// 
// 		strInfo = _com_util::ConvertBSTRToString((pSeriesList + i)->bsPatientName);
//  		m_listImportSeries.SetItemText(i, 2, strInfo);
// 
// 		strInfo = _com_util::ConvertBSTRToString((pSeriesList + i)->bsStudyID);
//  		m_listImportSeries.SetItemText(i, 3, strInfo);
// 
// 		strInfo = _com_util::ConvertBSTRToString((pSeriesList + i)->bsSeriesID);
//  		m_listImportSeries.SetItemText(i, 4, strInfo);
// 
// 		switch ((pSeriesList + i)->enumSeriesState)
// 		{
// 		case enumSeriesState_Waiting:
// 			m_listImportSeries.SetItemText(i, 5, _T("Waiting"));
// 			break;
// 		case enumSeriesState_Importing:
// 			m_listImportSeries.SetItemText(i, 5, _T("Importing"));
// 			break;
// 		case enumSeriesState_Completed:
// 			m_listImportSeries.SetItemText(i, 5, _T("Completed"));
// 			break;
// 		case enumSeriesState_Skipped:
// 			m_listImportSeries.SetItemText(i, 5, _T("Skipped"));
// 			break;
// 		case enumSeriesState_Failed:
// 			m_listImportSeries.SetItemText(i, 5, _T("Failed"));
// 			break;
// 		default:
// 			m_listImportSeries.SetItemText(i, 5, _T("Unknow!"));
// 		}
// 
// 
// 		strInfo.Format(_T("%d%%"), (pSeriesList + i)->dwProgressInPercent);
// 		switch ((pSeriesList + i)->enumSeriesProgress)
// 		{
// 		case enumSeriesProgress_None:
// 			m_listImportSeries.SetItemText(i, 6, _T(""));
// 			break;
// 		case enumSeriesProgress_Percentage:
// 			m_listImportSeries.SetItemText(i, 6, strInfo);
// 			break;
// 		default:
// 			m_listImportSeries.SetItemText(i, 6, _T("Unknow"));
// 			break;
// 		}
// 


// 		strInfo = _com_util::ConvertBSTRToString((pSeriesList + i)->bsPatientID)
//  		m_listImportSeries.SetItemText(i, 7, m_vtrPatient[i].strPatientID);

// 	}
	
}



// void CDiscImportDlg::ImportedSeriesStateChanged(DiscImport_SeriesStateStruct* pState)
// {
// 	CString strChangedSeriesIndex;
// 	strChangedSeriesIndex.Format(_T("%d"), pState->uIndex + 1);
// 
// 	for (int i = 0; i < m_listImportSeries.GetItemCount(); i++)
// 	{
// 		CString strSeriesIndex = m_listImportSeries.GetItemText(i, 0);
// 		if (!strSeriesIndex.Compare(strChangedSeriesIndex))
// 		{
// 			switch (pState->enumSeriesState)
// 			{
// 			case enumSeriesState_Waiting:
// 				m_listImportSeries.SetItemText(i, 5, _T("Waiting"));
// 				break;
// 			case enumSeriesState_Importing:
// 				m_listImportSeries.SetItemText(i, 5, _T("Importing"));
// 				break;
// 			case enumSeriesState_Completed:
// 				m_listImportSeries.SetItemText(i, 5, _T("Completed"));
// 				break;
// 			case enumSeriesState_Skipped:
// 				m_listImportSeries.SetItemText(i, 5, _T("Skipped"));
// 				break;
// 			case enumSeriesState_Failed:
// 				m_listImportSeries.SetItemText(i, 5, _T("Failed"));
// 				break;
// 			default:
// 				m_listImportSeries.SetItemText(i, 5, _T("unknow"));
// 				break;
// 
// 			}
// 
// 			break;
// 		}
// 	}
// }
// 
// void CDiscImportDlg::ImportedSeriesProgressChanged(DiscImport_SeriesProgressStruct* pProgress)
// {
// 	CString strChangedSeriesIndex;
// 	strChangedSeriesIndex.Format(_T("%d"), pProgress->uIndex + 1);
// 
// 	CString strProgress;
// 	switch (pProgress->enumSeriesProgress)
// 	{
// 	case enumSeriesProgress_None:
// 		strProgress = _T("");
// 		break;
// 	case enumSeriesProgress_Percentage:
// 		strProgress.Format(_T("%d%%"), pProgress->dwProgressInPercent);
// 		break;
// 	default:
// 		strProgress = _T("unknow");
// 		break;
// 
// 	}
// 
// 
// 	for (int i = 0; i < m_listImportSeries.GetItemCount(); i++)
// 	{
// 		CString strSeriesIndex = m_listImportSeries.GetItemText(i, 0);
// 		if (!strSeriesIndex.Compare(strChangedSeriesIndex))
// 		{
// 			m_listImportSeries.SetItemText(i, 6, strProgress);
// 			break;
// 		}
// 	}
// }
// 
// void CDiscImportDlg::ImportedSeriesDetailChanged(DiscImport_SeriesDetailStruct* pDetail)
// {
// 	CString strChangedSeriesIndex;
// 	strChangedSeriesIndex.Format(_T("%d"), pDetail->uIndex + 1);
// 
// 	CString strDetail;
// 	
// 	switch (pDetail->enumSeriesDetail)
// 	{
// 	case enumSeriesDetail_None:
// 		strDetail = _T("");
// 		break;
// 	case enumSeriesDetail_CompleteInfo:
// 		strDetail = CString(_com_util::ConvertBSTRToString(pDetail->bsCompleteInfoPrefix)) +
// 			_com_util::ConvertBSTRToString(pDetail->bsCompleteInfoPatientID) +
// 			_com_util::ConvertBSTRToString(pDetail->bsPatientIDInDB) +
// 			_com_util::ConvertBSTRToString(pDetail->bsCompleteInfoPatientName) +
// 			_com_util::ConvertBSTRToString(pDetail->bsPatientNameInDB) +
// 			_com_util::ConvertBSTRToString(pDetail->bsCompleteInfoStudyID) +
// 			_com_util::ConvertBSTRToString(pDetail->bsStudyIDInDB) +
// 			_com_util::ConvertBSTRToString(pDetail->bsCompleteInfoSeriesID) +
// 			_com_util::ConvertBSTRToString(pDetail->bsSeriesIDInDB);
// 		break;
// 	case enumSeriesDetail_DetailInfo:
// 		strDetail = _com_util::ConvertBSTRToString(pDetail->bsDetailInfo);
// 		break;
// 	case enumSeriesDetail_UG:
// 		strDetail = _T("UG");
// 		break;
// 	default:
// 		strDetail = _T("unknow");
// 		break;
// 	}
// 
// 	for (int i = 0; i < m_listImportSeries.GetItemCount(); i++)
// 	{
// 		CString strSeriesIndex = m_listImportSeries.GetItemText(i, 0);
// 		if (!strSeriesIndex.Compare(strChangedSeriesIndex))
// 		{
// 			m_listImportSeries.SetItemText(i, 7, strDetail);
// 	
// 			break;
// 		}
// 	}
// }
// 
void CDiscImportDlg::DiscImportStateChanged(SubModuleState* pState)
{

}

void CDiscImportDlg::OnDividerdblclickListPatient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
