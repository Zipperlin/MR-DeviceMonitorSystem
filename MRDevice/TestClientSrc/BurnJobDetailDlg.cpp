// BurnJobDetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "BurnJobDetailDlg.h"
#include "TestClientSrcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CTestClientSrcDlg* g_smDlg; 

/////////////////////////////////////////////////////////////////////////////
// CBurnJobDetailDlg dialog


CBurnJobDetailDlg::CBurnJobDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBurnJobDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBurnJobDetailDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBurnJobDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBurnJobDetailDlg)
	DDX_Control(pDX, IDC_LIST_BURN_JOB_DETAIL_DETAIL, m_listDetail);
	DDX_Control(pDX, IDC_LIST_BURN_JOB_DETAIL_PSSI, m_listPSSI);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBurnJobDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CBurnJobDetailDlg)
	ON_BN_CLICKED(IDC_BUTTON_BURN_JOB_DETAIL_CLOSE, OnButtonBurnJobDetailClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBurnJobDetailDlg message handlers

void CBurnJobDetailDlg::SetJobMode(JobMode enumJobMode)
{
	m_enumJobMode = enumJobMode;
}

void CBurnJobDetailDlg::SetJob(LPCTSTR szJobID)
{
	m_strJobID = szJobID;
}

LPCTSTR CBurnJobDetailDlg::GetJob()
{
	return m_strJobID;
}

void CBurnJobDetailDlg::OnButtonBurnJobDetailClose() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

BOOL CBurnJobDetailDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listPSSI.SetExtendedStyle(m_listPSSI.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listPSSI.InsertColumn(0, _T("Index"), LVCFMT_LEFT, 50);
	m_listPSSI.InsertColumn(1, _T("PatientID"), LVCFMT_LEFT, 100);
	m_listPSSI.InsertColumn(2, _T("PatientName"), LVCFMT_LEFT, 100);
	m_listPSSI.InsertColumn(3, _T("StudyID"), LVCFMT_LEFT, 100);
	m_listPSSI.InsertColumn(4, _T("SeriesID"), LVCFMT_LEFT, 100);
	m_listPSSI.InsertColumn(5, _T("ImageID"), LVCFMT_LEFT, 100);

	m_listDetail.SetExtendedStyle(m_listDetail.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listDetail.InsertColumn(0, _T("Time"), LVCFMT_LEFT, 100);
	m_listDetail.InsertColumn(1, _T("Detail"), LVCFMT_LEFT, 300);

	
	GetJobInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBurnJobDetailDlg::GetJobInfo()
{
	if (m_strJobID.IsEmpty())
		return;

	BSTR bsJobID = m_strJobID.AllocSysString();

	JobInfo aJobInfo;
	PSSIInfo* pPSSIInfo = NULL;
	long lPSSILen = 0;
	JobDetailStruct* pDetail = NULL;
	long lDetailLen = 0;

	HRESULT hr = S_OK;
	if (enumJobMode_Current == m_enumJobMode)
	{
		hr = g_smDlg->m_pIPABurn->GetBurnJobInfo(bsJobID, &aJobInfo,
															&pPSSIInfo, &lPSSILen,
															&pDetail, &lDetailLen);
		if (S_OK != hr)
		{
			AfxMessageBox(_T("g_smDlg->m_pIPABurn->GetBurnJobInfo(...)"));
			return;
		}
	}
	else
	{
		hr = g_smDlg->m_pIPAGeneral->GetHistoryJobInfo(bsJobID, &aJobInfo);
		if (S_OK != hr)
		{
			AfxMessageBox(_T("g_smDlg->m_pIPAGeneral->GetHistoryJobInfo(...)"));
			return;
		}

		hr = g_smDlg->m_pIPAGeneral->GetHistoryJobPSSIInfo(bsJobID,
															&lPSSILen, &pPSSIInfo);
		if (S_OK != hr)
		{
			AfxMessageBox(_T("g_smDlg->m_pIPAGeneral->GetHistoryJobPSSIInfo(...)"));
			return;
		}

		hr = g_smDlg->m_pIPAGeneral->GetHistoryJobDetailInfo(bsJobID,
															&lDetailLen, &pDetail);
		if (S_OK != hr)
		{
			AfxMessageBox(_T("g_smDlg->m_pIPAGeneral->GetHistoryJobDetailInfo(...)"));
			return;
		}
	}

	UpdateJobInfo(aJobInfo,
				pPSSIInfo,
				lPSSILen,
				pDetail,
				lDetailLen);

	// Free
}

void CBurnJobDetailDlg::UpdateJobInfo(JobInfo& aJobInfo,
									PSSIInfo* pPSSIInfo,
									long lPSSILen,
									JobDetailStruct* pDetail,
									long lDetailLen)
{
	int i = 0;
	CString strInfo;

	// PSSI
	for (i = 0; i < lPSSILen; i++)
	{
		strInfo.Format(_T("%d"), i+1);
		int iIndex = m_listPSSI.InsertItem(i, strInfo);

		strInfo = CBSTROpt::BSTRToCString(pPSSIInfo[i].bsPatientID);
		m_listPSSI.SetItemText(i, 1, strInfo);

		strInfo = CBSTROpt::BSTRToCString(pPSSIInfo[i].bsPatientName);
		m_listPSSI.SetItemText(i, 2, strInfo);

		strInfo = CBSTROpt::BSTRToCString(pPSSIInfo[i].bsStudyID);
		m_listPSSI.SetItemText(i, 3, strInfo);

		strInfo = CBSTROpt::BSTRToCString(pPSSIInfo[i].bsSeriesID);
		m_listPSSI.SetItemText(i, 4, strInfo);

		strInfo = CBSTROpt::BSTRToCString(pPSSIInfo[i].bsImageID);
		m_listPSSI.SetItemText(i, 5, strInfo);

	}

	// State, Phase and Progress
	strInfo = CBSTROpt::BSTRToCString(aJobInfo.bsState);
	GetDlgItem(IDC_EDIT_SEND_JOB_DETAIL_STATE)->SetWindowText(strInfo);

	strInfo = CBSTROpt::BSTRToCString(aJobInfo.bsPhase);
	GetDlgItem(IDC_EDIT_SEND_JOB_DETAIL_PHASE)->SetWindowText(strInfo);

	strInfo = CBSTROpt::BSTRToCString(aJobInfo.bsProgress);
	GetDlgItem(IDC_EDIT_SEND_JOB_DETAIL_PROGRESS)->SetWindowText(strInfo);

	// Detail
	for (i = 0; i < lDetailLen; i++)
	{
		strInfo = CBSTROpt::BSTRToCString(pDetail[i].bsTime);
		int iIndex = m_listDetail.InsertItem(i, strInfo);

		strInfo = CBSTROpt::BSTRToCString(pDetail[i].bsDetail);
		m_listDetail.SetItemText(i, 1, strInfo);
	}
}

void CBurnJobDetailDlg::UpdateState(BSTR bsJobID, BSTR bsState)
{
	if (!IsThisJob(bsJobID))
	{
		return;
	}

	if (!IsShow())
	{
		return;
	}

	CString strInfo = CBSTROpt::BSTRToCString(bsState);
	GetDlgItem(IDC_EDIT_SEND_JOB_DETAIL_STATE)->SetWindowText(strInfo);
}

void CBurnJobDetailDlg::UpdateProgress(BSTR bsJobID, BSTR bsProgress)
{
	if (!IsThisJob(bsJobID))
	{
		return;
	}

	if (!IsShow())
	{
		return;
	}

	CString strInfo = CBSTROpt::BSTRToCString(bsProgress);
	GetDlgItem(IDC_EDIT_SEND_JOB_DETAIL_PROGRESS)->SetWindowText(strInfo);
}

void CBurnJobDetailDlg::UpdatePhase(BSTR bsJobID, BSTR bsPhase)
{
	if (!IsThisJob(bsJobID))
	{
		return;
	}

	if (!IsShow())
	{
		return;
	}

	CString strInfo = CBSTROpt::BSTRToCString(bsPhase);
	GetDlgItem(IDC_EDIT_SEND_JOB_DETAIL_PHASE)->SetWindowText(strInfo);
}

void CBurnJobDetailDlg::UpdateDetail(JobDetailStruct* pDetail)
{
	if (!IsThisJob(pDetail->bsJobID))
	{
		return;
	}

	if (!IsShow())
	{
		return;
	}

	CString strTime = CBSTROpt::BSTRToCString(pDetail->bsTime);
	CString strInfo = CBSTROpt::BSTRToCString(pDetail->bsDetail);
	int iIndex = m_listDetail.GetItemCount();
	m_listDetail.InsertItem(iIndex, strTime);
	m_listDetail.SetItemText(iIndex, 1, strInfo);

}

BOOL CBurnJobDetailDlg::IsThisJob(BSTR bsJobID)
{
	CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
	if (!strJobID.Compare(m_strJobID))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CBurnJobDetailDlg::IsShow()
{
// 	return TRUE;
	if (NULL == this->GetSafeHwnd())
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
