// PAGeneralDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "PAGeneralDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CTestClientSrcDlg* g_smDlg; 

/////////////////////////////////////////////////////////////////////////////
// CPAGeneralDlg dialog


CPAGeneralDlg::CPAGeneralDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPAGeneralDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPAGeneralDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPAGeneralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPAGeneralDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPAGeneralDlg, CDialog)
	//{{AFX_MSG_MAP(CPAGeneralDlg)
	ON_BN_CLICKED(IDC_BUTTON_SEND_UG, OnButtonSendUg)
	ON_BN_CLICKED(IDC_BUTTON_UID_OCCUPIED, OnButtonUidOccupied)
	ON_BN_CLICKED(IDC_BUTTON_PAGENERAL_PING, OnButtonPageneralPing)
	ON_BN_CLICKED(IDC_BUTTON_COMPACT_DB, OnButtonCompactDb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPAGeneralDlg message handlers
BOOL CPAGeneralDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CComboBox*)GetDlgItem(IDC_COMBO_UID_TYPE))->SetCurSel(0);
	
	((CEdit*)GetDlgItem(IDC_EDIT_UG_ID))->SetWindowText(_T("55001"));
	((CComboBox*)GetDlgItem(IDC_COMBO_UG_TYPE))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_UG_PRIOR))->SetCurSel(0);
	((CButton*)GetDlgItem(IDC_CHECK_UG_BACTIVE))->SetCheck(BST_CHECKED);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPAGeneralDlg::OnButtonSendUg() 
{
	// TODO: Add your control notification handler code here
	CString strUGID, strUGType, strUGPrio;
	
	GetDlgItem(IDC_EDIT_UG_ID)->GetWindowText(strUGID);
	if (strUGID.IsEmpty())
		return;

	LONG lUGID = _wtol((LPCTSTR)strUGID);

	
	int iType = ((CComboBox*)GetDlgItem(IDC_COMBO_UG_TYPE))->GetCurSel();
	USER_GUIDANCE_TYPE enumType;
	switch (iType)
	{
	case 0:
		enumType = enumUG_TYPE_E;
		break;
	case 1:
		enumType = enumUG_TYPE_T;
		break;
	case 2:
		enumType = enumUG_TYPE_ET;
		break;
	default:
		return;
	}

	int iPriority = ((CComboBox*)GetDlgItem(IDC_COMBO_UG_PRIOR))->GetCurSel();
	USER_GUIDANCE_PRIORITY enumPrior;
	switch (iPriority)
	{
	case 0:
		enumPrior = enumUG_PRIOR_L;
		break;
	case 1:
		enumPrior = enumUG_PRIOR_M;
		break;
	case 2:
		enumPrior = enumUG_PRIOR_H;
		break;
	default:
		return;
	}

	BOOL bActive = (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK_UG_BACTIVE))->GetCheck()) ? FALSE : TRUE;
	
	HRESULT hResult = CTestClientSrcDlg::m_pIPAGeneral->ReportUserGuidance(lUGID, enumType, enumPrior, bActive);
	if (S_OK == hResult)
	{
	}
	else
	{
		AfxMessageBox(_T("m_pIPAGeneral->ReportUserGuidance"));
	}
}

void CPAGeneralDlg::OnButtonUidOccupied() 
{
	// TODO: Add your control notification handler code here
	int iSelected = ((CComboBox*)GetDlgItem(IDC_COMBO_UID_TYPE))->GetCurSel();
	if (-1 == iSelected)
		return;

	PatientAdminUIDType enumPAUIDType;
	switch (iSelected)
	{
	case 0:
		enumPAUIDType = enumPatientAdminUIDType_Series;
		break;
	case 1:
		enumPAUIDType = enumPatientAdminUIDType_Study;
		break;
	case 2:
		enumPAUIDType = enumPatientAdminUIDType_Patient;
	    break;
	default:
	    return;
	}

	CString strUID;
	GetDlgItem(IDC_EDIT_UID)->GetWindowText(strUID);
	if (strUID.IsEmpty())
		return;

	BSTR bsUID = strUID.AllocSysString();
	BOOL bOccupied = FALSE;
	HRESULT hResult = CTestClientSrcDlg::m_pIPAGeneral->GetPatientStudySeriesImageOccupyState(enumPAUIDType, 1, &bsUID, &bOccupied);
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




void CPAGeneralDlg::OnButtonPageneralPing() 
{
	// TODO: Add your control notification handler code here
	HRESULT hResult = CTestClientSrcDlg::m_pIPing->Ping();
	if (S_OK == hResult)
	{
		AfxMessageBox(_T("Ping OK"));
	}
	else
	{
		AfxMessageBox(_T("Failed"));
	}
}

void CPAGeneralDlg::OnButtonCompactDb() 
{
	// TODO: Add your control notification handler code here
	CButton* pbtn = (CButton*)GetDlgItem(IDC_BUTTON_COMPACT_DATABASE);
	int iCheck = pbtn->GetCheck();
	BOOL bBackUp = (BST_CHECKED == iCheck) ? TRUE : FALSE;
	if (S_OK == CTestClientSrcDlg::m_pIPAGeneral->CompactDB(bBackUp))
	{
		AfxMessageBox(_T("OK!"));
	}
	else
	{
		AfxMessageBox(_T("Error!"));
	}
}
