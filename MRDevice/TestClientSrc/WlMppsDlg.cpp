// WlMppsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "WlMppsDlg.h"
#include "TestClientSrcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CTestClientSrcDlg* g_smDlg;

/////////////////////////////////////////////////////////////////////////////
// CWlMppsDlg dialog


CWlMppsDlg::CWlMppsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWlMppsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWlMppsDlg)
	m_radioMppsStatus = -1;
	//}}AFX_DATA_INIT
}


void CWlMppsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWlMppsDlg)
	DDX_Control(pDX, IDC_LIST_PATIENTSTUDY, m_listPatientStudy);
	DDX_Control(pDX, IDC_LIST_WORKLIST, m_listWorkList);
	DDX_Radio(pDX, IDC_RADIO_INPROGRESS, m_radioMppsStatus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWlMppsDlg, CDialog)
	//{{AFX_MSG_MAP(CWlMppsDlg)
	ON_BN_CLICKED(IDC_BUTTON_GET_WORKLIST, OnButtonGetWorklist)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_GET_PSSTRUCT, OnButtonGetPsstruct)
	ON_BN_CLICKED(IDC_BUTTON_ISIMPORTED, OnButtonIsimported)
	ON_BN_CLICKED(IDC_BUTTON_SET_MPPS, OnButtonSetMpps)
	ON_BN_CLICKED(IDC_BUTTON_SET_MPPS_TEST, OnButtonSetMppsTest)
	ON_BN_CLICKED(IDC_BUTTON_IS_SET_ENABLE, OnButtonIsSetEnable)
	ON_BN_CLICKED(IDC_BUTTON_ISWLWORKING, OnButtonIswlworking)
	ON_BN_CLICKED(IDC_BUTTON_ISMPPSWORKING, OnButtonIsmppsworking)
	ON_BN_CLICKED(IDC_BUTTON_IS_CLOSING_STUDY_MPPS, OnButtonIsClosingStudyMpps)
	ON_BN_CLICKED(IDC_BUTTON_ISMPPSVALID, OnButtonIsmppsvalid)
	ON_BN_CLICKED(IDC_BUTTON_IS_CLOSING_PATIENT_OR_STUDY_MPPS, OnButtonIsClosingPatientOrStudyMpps)
	ON_BN_CLICKED(IDC_BUTTON_IS_SETTING_P_OR_S_MPPS_UID_ADD, OnButtonIsSettingPOrSMppsUidAdd)
	ON_BN_CLICKED(IDC_BUTTON_IS_SETTING_P_OR_S_MPPS_UID_CLEAR, OnButtonIsSettingPOrSMppsUidClear)
	ON_BN_CLICKED(IDC_BUTTON_STUDY_IMPORTED, OnButtonStudyImported)
	ON_BN_CLICKED(IDC_BUTTON_IS_STUDYINSTUID_EXIST, OnButtonIsStudyinstuidExist)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL_STUDYINSTUID, OnButtonDeleteAllStudyinstuid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWlMppsDlg message handlers

BOOL CWlMppsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listWorkList.SetExtendedStyle(m_listWorkList.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listPatientStudy.SetExtendedStyle(m_listPatientStudy.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// WorkList header
	m_listWorkList.InsertColumn(0, _T("Status"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(1, _T("Scheduled Station AE Title"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(2, _T("SPS StartDateTime"), LVCFMT_LEFT, 200);
	m_listWorkList.InsertColumn(3, _T("SPS Description"), LVCFMT_LEFT, 200);
	m_listWorkList.InsertColumn(4, _T("SPS ID"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(5, _T("ScheduledPerformingPhysicianName"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(6, _T("PatientName"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(7, _T("PatientID"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(8, _T("AccessionNumber"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(9, _T("PatientBirthDate"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(10, _T("PatientSex"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(11, _T("ReferringPhysicianName"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(12, _T("RequestedProcedureID"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(13, _T("RequestedProcedureDescription"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(14, _T("StudyInstanceUID"), LVCFMT_LEFT, 100);

	m_listWorkList.InsertColumn(15, _T("OtherPatientIDs"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(16, _T("OtherPatientNames"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(17, _T("PatientAge"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(18, _T("Occupation"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(19, _T("PatientSize"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(20, _T("PatientWeight"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(21, _T("EthinicGroup"), LVCFMT_LEFT, 100);
	m_listWorkList.InsertColumn(22, _T("PatientComments"), LVCFMT_LEFT, 100);

	m_listWorkList.InsertColumn(23, _T("CharacterSet"), LVCFMT_LEFT, 100);

	// PatientStudy header

	// SPS Start Date default selection
	((CComboBox*)GetDlgItem(IDC_COMBO_SPSSTARTDATE))->SetCurSel(5);		// "All" selected
	
	// MPPS Init
	((CButton*)GetDlgItem(IDC_EDIT_STUDYUID))->SetWindowText(_T("0520070125124552937"));
	((CButton*)GetDlgItem(IDC_RADIO_INPROGRESS))->SetCheck(BST_CHECKED);

	((CButton*)(GetDlgItem(IDC_RADIO_IS_SETTING_P_OR_S_MPPS_PATIENT)))->SetCheck(BST_CHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWlMppsDlg::OnButtonGetWorklist() 
{
	// TODO: Add your control notification handler code here
	m_listWorkList.DeleteAllItems();

	HRESULT hResult = S_OK;
	hResult = g_smDlg->m_pIPAWlMpps->GetWorkList();
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("error: g_smDlg->m_pIPAWlMpps->GetWorkList()"));
	}

}

void CWlMppsDlg::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here
	m_listWorkList.DeleteAllItems();

	HRESULT hResult = S_OK;
	WorkListQueryCond QueyCond;

	QueyCond.enumWLQuerySPSStartDate = (WLQuerySPSStartDate)(((CComboBox*)GetDlgItem(IDC_COMBO_SPSSTARTDATE))->GetCurSel() + 1);
	hResult = g_smDlg->m_pIPAWlMpps->RefreshWorkList(&QueyCond);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("error: g_smDlg->m_pIPAWlMpps->RefreshWorkList()"));
	}
}

void CWlMppsDlg::OnButtonGetPsstruct() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listWorkList.GetFirstSelectedItemPosition();
	CString strStudyInstanceUID;
	if (pos == NULL)
	{
		return;
	}
	else
	{			
		int nItem = m_listWorkList.GetNextSelectedItem(pos);
		strStudyInstanceUID = m_listWorkList.GetItemText(nItem, 14);
		BSTR bsStudyInstanceUID = strStudyInstanceUID.AllocSysString();
		WLPatientStudyStruct Struct;
		HRESULT hResult = g_smDlg->m_pIPAWlMpps->GetImportPatientStudyInfo(bsStudyInstanceUID, &Struct);
		if (S_OK == hResult)
		{
			UpdatePatientStudyList(&Struct);
		}
		else
		{
			AfxMessageBox(_T("CTestClientSrcDlg::m_pIPAWlMpps->GetImportPatientStudyInfo"));
		}
	}
}

void CWlMppsDlg::OnButtonIsimported() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listWorkList.GetFirstSelectedItemPosition();
	CString strStudyInstanceUID;
	if (pos == NULL)
	{
		return;
	}
	else
	{			
		int nItem = m_listWorkList.GetNextSelectedItem(pos);
		strStudyInstanceUID = m_listWorkList.GetItemText(nItem, 14);
		BSTR bsStudyInstanceUID = strStudyInstanceUID.AllocSysString();
		WLPatientStudyStatusInDB StatusStruct;
		HRESULT hResult = g_smDlg->m_pIPAWlMpps->IsStudyImported(bsStudyInstanceUID, &StatusStruct);
		if (S_OK == hResult)
		{
			UpdatePatientStudyList(&StatusStruct);
		}
		else
		{
			AfxMessageBox(_T("CTestClientSrcDlg::m_pIPAWlMpps->IsStudyImported"));
		}
	}
}

void CWlMppsDlg::UpdateWorkList(long lItemNum, WorkListStruct* pWorkList)
{

	m_listWorkList.DeleteAllItems();
	
	if (0 == lItemNum)
		return;

	for (int i = 0; i < lItemNum; i++)
	{
		WorkListStruct* pCurrent = pWorkList + i;
		CString strInfo;

		switch (pCurrent->enumStatus)
		{
		case enumWorkListStatus_NotImported:
			strInfo = _T("NotImported");
			break;
		case enumWorkListStatus_Imported:
			strInfo = _T("Imported");
			break;
		case enumWorkListStatus_InProgress:
			strInfo = _T("InProgress");
			break;
		case enumWorkListStatus_Discontinued:
			strInfo = _T("Discontinued");
			break;
		case enumWorkListStatus_Completed:
			strInfo = _T("Completed");
			break;
		default:
			strInfo = _T("Unknow");
			break;
		}

 		m_listWorkList.InsertItem(i, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsSSAETitle);
		m_listWorkList.SetItemText(i, 1, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsSPSDateTime);
		m_listWorkList.SetItemText(i, 2, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsSPSDescription);
		m_listWorkList.SetItemText(i, 3, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsSPSID);
		m_listWorkList.SetItemText(i, 4, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsSPPhisicianName);
		m_listWorkList.SetItemText(i, 5, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsPatientName);
		m_listWorkList.SetItemText(i, 6, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsPatientID);
		m_listWorkList.SetItemText(i, 7, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsAccessionNumber);
		m_listWorkList.SetItemText(i, 8, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsPatientBirthDate);
		m_listWorkList.SetItemText(i, 9, strInfo);

		switch(pCurrent->iPatientSex)
		{
		case 0:
			strInfo = _T("Male");
			break;
		case 1:
			strInfo = _T("Female");
			break;
		case 2:
			strInfo = _T("Other");
		    break;
		default:
			strInfo = _T("Unknow");
		    break;
		}
		m_listWorkList.SetItemText(i, 10, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsRefPhisicianName);
		m_listWorkList.SetItemText(i, 11, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsRPID);
		m_listWorkList.SetItemText(i, 12, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsRPDescription);
		m_listWorkList.SetItemText(i, 13, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsStudyInstanceUID);
		m_listWorkList.SetItemText(i, 14, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsOtherPatientIDs);
		m_listWorkList.SetItemText(i, 15, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsOtherPatientNames);
		m_listWorkList.SetItemText(i, 16, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsPatientAge);
		m_listWorkList.SetItemText(i, 17, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsOccupation);
		m_listWorkList.SetItemText(i, 18, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsPatientSize);
		m_listWorkList.SetItemText(i, 19, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsPatientWeight);
		m_listWorkList.SetItemText(i, 20, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsEthnicGroup);
		m_listWorkList.SetItemText(i, 21, strInfo);

		strInfo = _com_util::ConvertBSTRToString(pCurrent->bsPatientComments);
		m_listWorkList.SetItemText(i, 22, strInfo);

	}
}


void CWlMppsDlg::UpdatePatientStudyList(WLPatientStudyStruct* pStruct)
{
	GetDlgItem(IDC_STATIC_PSStruct)->SetWindowText(_T("PatientStudyStruct"));

	//Çå¿ÕCListCtrl items and columns
	m_listPatientStudy.DeleteAllItems();
	int nColumnCount = m_listPatientStudy.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount; i++)
	{
	   m_listPatientStudy.DeleteColumn(0);
	}

	m_listPatientStudy.InsertColumn(0, _T("Section"), LVCFMT_LEFT, 100);
	m_listPatientStudy.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 200);
	m_listPatientStudy.InsertColumn(2, _T("value"), LVCFMT_LEFT, 300);

	int iIndex = -1;
	CString strInfo;

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("StudyInstanceUID"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsStudyInstanceUID);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);


	// Patient
	m_listPatientStudy.InsertItem(++iIndex, _T("PatientStruct"));

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientID"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientID);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientFirstName"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientFirstName);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientMidName"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientMidName);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientLastName"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientLastName);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientBirthDateAgeUsing"));
	strInfo.Format(_T("%d"), pStruct->enumBirthDateAgeUsing);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientAge"));
	strInfo.Format(_T("%d"), pStruct->iPatientAge);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientAgeUnit"));
	strInfo.Format(_T("%d"), pStruct->iPatientAgeUnit);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientBirthDate"));
	COleDateTime odtDateTime = pStruct->dtPatientBirthDate;
	strInfo = odtDateTime.Format(_T("%Y-%m-%d"));
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("RegDateTime"));
	odtDateTime = pStruct->dtRegDateTime;
	strInfo = odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientSex"));
	strInfo.Format(_T("%d"), pStruct->iPatientSex);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("OtherPatientName"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsOtherPatientName);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("OtherPatientIDs"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsOtherPatientIDs);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("EthnicGroup"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsEthnicGroup);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("Occupation"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsOccupation);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientComments"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientComment);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);


	// Study
	m_listPatientStudy.InsertItem(++iIndex, _T("Studytruct"));

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("StudyDateTime"));
	odtDateTime = pStruct->dtStudyDateTime;
	strInfo = odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

// 	m_listPatientStudy.InsertItem(++iIndex, _T(""));
// 	m_listPatientStudy.SetItemText(iIndex, 1, _T("ApplicationGroupUID"));
// 	strInfo.Format(_T("%d"), pStruct->lApplicationGroupUID);
// 	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);
// 
// 	m_listPatientStudy.InsertItem(++iIndex, _T(""));
// 	m_listPatientStudy.SetItemText(iIndex, 1, _T("ApplicationUID"));
// 	strInfo.Format(_T("%d"), pStruct->lApplicationUID);
// 	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("RefferingPhsicianName"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsRefferingPhsicianName);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("OperatorName"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsOperatorName);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PerformingPhysicianName"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPerformingPhysicianName);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientSize"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientSize);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientWeight"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientWeight);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("StudyDescription"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsStudyDescription);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("PatientHistory"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientHistory);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T(""));
	m_listPatientStudy.SetItemText(iIndex, 1, _T("AccessionNumber"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsAccessionNumber);
	m_listPatientStudy.SetItemText(iIndex, 2, strInfo);


}

void CWlMppsDlg::UpdatePatientStudyList(WLPatientStudyStatusInDB* pStruct)
{
	GetDlgItem(IDC_STATIC_PSStruct)->SetWindowText(_T("StudyStatusStruct"));

	//Çå¿ÕCListCtrl items and columns
	m_listPatientStudy.DeleteAllItems();
	int nColumnCount = m_listPatientStudy.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount; i++)
	{
	   m_listPatientStudy.DeleteColumn(0);
	}

	m_listPatientStudy.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 200);
	m_listPatientStudy.InsertColumn(1, _T("value"), LVCFMT_LEFT, 200);

	int iIndex = -1;
	CString strInfo;

	m_listPatientStudy.InsertItem(++iIndex, _T("StudyExists"));
	strInfo.Format(_T("%d"), pStruct->bStudyExists);
	m_listPatientStudy.SetItemText(iIndex, 1, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T("PatientExists"));
	strInfo.Format(_T("%d"), pStruct->bPatientExists);
	m_listPatientStudy.SetItemText(iIndex, 1, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T("PatientUID"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientUID);
	m_listPatientStudy.SetItemText(iIndex, 1, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T("PatientID"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientID);
	m_listPatientStudy.SetItemText(iIndex, 1, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T("PatientFullName"));
	strInfo = _com_util::ConvertBSTRToString(pStruct->bsPatientFullName);
	m_listPatientStudy.SetItemText(iIndex, 1, strInfo);

	m_listPatientStudy.InsertItem(++iIndex, _T("PatientSex"));
	strInfo.Format(_T("%d"), pStruct->iPatientSex);
	m_listPatientStudy.SetItemText(iIndex, 1, strInfo);

}

void CWlMppsDlg::OnButtonSetMpps() 
{
	// TODO: Add your control notification handler code here
	CString strStudyUID;
	BSTR bsStudyUID;
	GetDlgItem(IDC_EDIT_STUDYUID)->GetWindowText(strStudyUID);
	if (strStudyUID.IsEmpty())
	{
		AfxMessageBox(_T("Plz input StudyUID!"));
		return;
	}
	else
	{
		bsStudyUID = strStudyUID.AllocSysString();
	}

	UpdateData(TRUE);
	WorkListStatus enumStatus = enumWorkListStatus_NotImported;
	switch(m_radioMppsStatus)
	{
	case 0:
		enumStatus = enumWorkListStatus_InProgress;
		break;
	case 1:
		enumStatus = enumWorkListStatus_Completed;
		break;
	case 2:
		enumStatus = enumWorkListStatus_Discontinued;
		break;
	default:
		AfxMessageBox(_T("Invalid MPPS status selection!"));
		return;
	}

	HRESULT hResult = S_OK;
	hResult = g_smDlg->m_pIPAWlMpps->SetMPPSStatus(bsStudyUID, enumStatus);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("error: g_smDlg->m_pIPAWlMpps->SetMPPSStatus()"));
	}
	
}

void CWlMppsDlg::OnButtonSetMppsTest() 
{
	// TODO: Add your control notification handler code here
	CString strStudyUID;
	BSTR bsStudyUID;
	WorkListStatus enumStatus = enumWorkListStatus_NotImported;

	int iStudyUID = 3000;
	for (; iStudyUID < 3010; iStudyUID++)
	{
		strStudyUID.Format(_T("%d"), iStudyUID);
		bsStudyUID = strStudyUID.AllocSysString();

		UpdateData(TRUE);
		switch(m_radioMppsStatus)
		{
		case 0:
			enumStatus = enumWorkListStatus_InProgress;
			break;
		case 1:
			enumStatus = enumWorkListStatus_Completed;
			break;
		case 2:
			enumStatus = enumWorkListStatus_Discontinued;
			break;
		default:
			AfxMessageBox(_T("Invalid MPPS status selection!"));
			return;
		}

		HRESULT hResult = S_OK;
		hResult = g_smDlg->m_pIPAWlMpps->SetMPPSStatus(bsStudyUID, enumStatus);
		if (S_OK != hResult)
		{
			AfxMessageBox(_T("error: g_smDlg->m_pIPAWlMpps->SetMPPSStatus()"));
		}
	}
}

void CWlMppsDlg::OnButtonIsSetEnable() 
{
	// TODO: Add your control notification handler code here
	CString strStudyUID;
	BSTR bsStudyUID;
	GetDlgItem(IDC_EDIT_STUDYUID)->GetWindowText(strStudyUID);
	if (strStudyUID.IsEmpty())
	{
		AfxMessageBox(_T("Plz input StudyUID!"));
		return;
	}
	else
	{
		bsStudyUID = strStudyUID.AllocSysString();
	}

	BOOL bEnabled = FALSE;
	HRESULT hResult = S_OK;
	hResult = g_smDlg->m_pIPAWlMpps->IsSetMPPSStatusEnabled(bsStudyUID, &bEnabled);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("error: g_smDlg->m_pIPAWlMpps->SetMPPSStatus()"));
	}
	else
	{
		if (bEnabled)
		{
			AfxMessageBox(_T("Enable!"));
		}
		else
		{
			AfxMessageBox(_T("Disable!"));
		}
	}
}

void CWlMppsDlg::OnButtonIswlworking() 
{
	// TODO: Add your control notification handler code here
	BOOL bWorking = FALSE;
	HRESULT hResult = S_OK;
	hResult = g_smDlg->m_pIPAWlMpps->IsWorkListWorking(&bWorking);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("error: g_smDlg->m_pIPAWlMpps->IsWorkListWorking()"));
	}
	else
	{
		if (bWorking)
		{
			AfxMessageBox(_T("Working!"));
		}
		else
		{
			AfxMessageBox(_T("Not Working!"));
		}
	}
}

void CWlMppsDlg::OnButtonIsmppsworking() 
{
	// TODO: Add your control notification handler code here
	BOOL bWorking = FALSE;
	HRESULT hResult = S_OK;
	hResult = g_smDlg->m_pIPAWlMpps->IsMppsWorking(&bWorking);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("error: g_smDlg->m_pIPAWlMpps->IsMppsWorking()"));
	}
	else
	{
		if (bWorking)
		{
			AfxMessageBox(_T("Working!"));
		}
		else
		{
			AfxMessageBox(_T("Not Working!"));
		}
	}
}

void CWlMppsDlg::OnButtonIsClosingStudyMpps() 
{
	// TODO: Add your control notification handler code here
	CString strStudyUID;
	BSTR bsStudyUID;
	GetDlgItem(IDC_EDIT_STUDYUID)->GetWindowText(strStudyUID);
	if (strStudyUID.IsEmpty())
	{
		AfxMessageBox(_T("Plz input StudyUID!"));
		return;
	}
	else
	{
		bsStudyUID = strStudyUID.AllocSysString();
	}

	BOOL bClosing = FALSE;
	HRESULT hResult = S_OK;
	hResult = g_smDlg->m_pIPAWlMpps->IsClosingStudyMPPS(bsStudyUID, &bClosing);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("error: g_smDlg->m_pIPAWlMpps->IsClosingStudyMPPS()"));
	}
	else
	{
		if (bClosing)
		{
			AfxMessageBox(_T("Closing!"));
		}
		else
		{
			AfxMessageBox(_T("Not Closing!"));
		}
	}
}

void CWlMppsDlg::OnButtonIsmppsvalid() 
{
	// TODO: Add your control notification handler code here
	BOOL bValid = FALSE;
	HRESULT hResult = S_OK;
	hResult = g_smDlg->m_pIPAWlMpps->IsMPPSValid(&bValid);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("error: g_smDlg->m_pIPAWlMpps->IsMppsValid()"));
	}
	else
	{
		if (bValid)
		{
			AfxMessageBox(_T("Valid!"));
		}
		else
		{
			AfxMessageBox(_T("Not Valid!"));
		}
	}
}

void CWlMppsDlg::OnButtonIsClosingPatientOrStudyMpps() 
{
	// TODO: Add your control notification handler code here
	int iCount = ((CListBox*)GetDlgItem(IDC_LIST_IS_SETTING_P_OR_S_MPPS_PATIENT_UIDS))->GetCount();
	if (0 == iCount)
	{
		AfxMessageBox(_T("Plz add UID"));
		return;
	}

	BSTR* pbsUIDs = new BSTR[iCount];
	for (int i = 0; i < iCount; ++i)
	{
		CString strUID;
		((CListBox*)GetDlgItem(IDC_LIST_IS_SETTING_P_OR_S_MPPS_PATIENT_UIDS))->GetText(i, strUID);
		*(pbsUIDs +i) = strUID.AllocSysString();
	}

	PatientAdminUIDType enumUIDType = enumPatientAdminUIDType_Unknow;
	if (BST_CHECKED == ((CButton*)(GetDlgItem(IDC_RADIO_IS_SETTING_P_OR_S_MPPS_PATIENT)))->GetCheck())
	{
		enumUIDType = enumPatientAdminUIDType_Patient;
	}
	else
	{
		enumUIDType = enumPatientAdminUIDType_Study;
	}

	BOOL bSetting = FALSE;
	if (S_OK == g_smDlg->m_pIPAWlMpps->IsSettingPatientOrStudyMPPS(iCount, pbsUIDs, enumUIDType, &bSetting))
	{
		if (bSetting)
		{
			AfxMessageBox(_T("Setting"));
		}
		else
		{
			AfxMessageBox(_T("Not Setting"));
		}
	}
	else
	{
		AfxMessageBox(_T("Error: g_smDlg->m_pIPAWlMpps->IsSettingPaitentOrStudyMPPS()"));
	}
}

void CWlMppsDlg::OnButtonIsSettingPOrSMppsUidAdd() 
{
	// TODO: Add your control notification handler code here
	CString strUID;
	GetDlgItem(IDC_EDIT_IS_SETTING_P_OR_S_MPPS_INPUT_UID)->GetWindowText(strUID);
	if (strUID.IsEmpty())
	{
		AfxMessageBox(_T("Plz input UID"));
		return;
	}

	((CListBox*)GetDlgItem(IDC_LIST_IS_SETTING_P_OR_S_MPPS_PATIENT_UIDS))->AddString(strUID);
}

void CWlMppsDlg::OnButtonIsSettingPOrSMppsUidClear() 
{
	// TODO: Add your control notification handler code here
	((CListBox*)GetDlgItem(IDC_LIST_IS_SETTING_P_OR_S_MPPS_PATIENT_UIDS))->ResetContent();
}

void CWlMppsDlg::OnButtonStudyImported() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listWorkList.GetFirstSelectedItemPosition();
	CString strStudyInstanceUID;
	if (pos == NULL)
	{
		return;
	}
	else
	{			
		int nItem = m_listWorkList.GetNextSelectedItem(pos);
		strStudyInstanceUID = m_listWorkList.GetItemText(nItem, 14);
		BSTR bsStudyInstanceUID = strStudyInstanceUID.AllocSysString();
		HRESULT hResult = g_smDlg->m_pIPAWlMpps->StudyImported(bsStudyInstanceUID);
		if (S_OK == hResult)
		{
			AfxMessageBox(_T("OK"));
		}
		else
		{
			AfxMessageBox(_T("CTestClientSrcDlg::m_pIPAWlMpps->StudyImported"));
		}
	}
}

void CWlMppsDlg::OnButtonIsStudyinstuidExist() 
{
	// TODO: Add your control notification handler code here
// 	POSITION pos = m_listWorkList.GetFirstSelectedItemPosition();
// 	CString strStudyInstanceUID;
// 	if (pos == NULL)
// 	{
// 		return;
// 	}
// 	else
// 	{			
// 		int nItem = m_listWorkList.GetNextSelectedItem(pos);
// 		strStudyInstanceUID = m_listWorkList.GetItemText(nItem, 14);
// 		BSTR bsStudyInstanceUID = strStudyInstanceUID.AllocSysString();
// 
// 		BOOL bExist = FALSE;
// 		HRESULT hResult = g_smDlg->m_pIPAWlMpps->IsStudyInstanceUIDExist(bsStudyInstanceUID, &bExist);
// 		if (S_OK == hResult)
// 		{
// 			if (bExist)
// 			{
// 				AfxMessageBox(_T("Exist"));
// 			}
// 			else
// 			{
// 				AfxMessageBox(_T("Not Exist"));
// 			}
// 		}
// 		else
// 		{
// 			AfxMessageBox(_T("CTestClientSrcDlg::m_pIPAWlMpps->StudyImported"));
// 		}
// 	}
}

void CWlMppsDlg::OnButtonDeleteAllStudyinstuid() 
{
	// TODO: Add your control notification handler code here
	HRESULT hResult = g_smDlg->m_pIPAWlMpps->DeleteAllImportedStudyRecords();
	if (S_OK == hResult)
	{
		AfxMessageBox(_T("All deleted"));
	}
	else
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPAWlMpps->DeleteAllStudyInstanceUID"));
	}
}
