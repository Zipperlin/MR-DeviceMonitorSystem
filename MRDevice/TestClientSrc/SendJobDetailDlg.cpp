// SendJobDetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "SendJobDetailDlg.h"
#include "TestClientSrcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CTestClientSrcDlg* g_smDlg; 

/////////////////////////////////////////////////////////////////////////////
// CSendJobDetailDlg dialog


CSendJobDetailDlg::CSendJobDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendJobDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendJobDetailDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSendJobDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendJobDetailDlg)
	DDX_Control(pDX, IDC_LIST_SEND_JOB_DETAIL_DETAIL, m_listDetail);
	DDX_Control(pDX, IDC_LIST_SEND_JOB_DETAIL_NODES, m_listNodes);
	DDX_Control(pDX, IDC_LIST_SEND_JOB_DETAIL_PSSI, m_listPSSI);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendJobDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CSendJobDetailDlg)
	ON_BN_CLICKED(IDC_BUTTON_SEND_JOB_DETAIL_CLOSE, OnButtonSendJobDetailClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendJobDetailDlg message handlers

void CSendJobDetailDlg::SetJobMode(JobMode enumJobMode)
{
	m_enumJobMode = enumJobMode;
}

void CSendJobDetailDlg::SetJob(LPCTSTR szJobID)
{
	m_strJobID = szJobID;
}

LPCTSTR CSendJobDetailDlg::GetJob()
{
	return m_strJobID;
}

void CSendJobDetailDlg::OnButtonSendJobDetailClose() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

BOOL CSendJobDetailDlg::OnInitDialog() 
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

	m_listNodes.SetExtendedStyle(m_listNodes.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listNodes.InsertColumn(0, _T("Server"), LVCFMT_LEFT, 100);
	m_listNodes.InsertColumn(1, _T("IP"), LVCFMT_LEFT, 100);
	m_listNodes.InsertColumn(2, _T("Port"), LVCFMT_LEFT, 40);
	m_listNodes.InsertColumn(3, _T("Raw"), LVCFMT_LEFT, 40);
	m_listNodes.InsertColumn(4, _T("Processed"), LVCFMT_LEFT, 40);

	m_listDetail.SetExtendedStyle(m_listDetail.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listDetail.InsertColumn(0, _T("Time"), LVCFMT_LEFT, 100);
	m_listDetail.InsertColumn(1, _T("Detail"), LVCFMT_LEFT, 300);

	
	GetJobInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSendJobDetailDlg::GetJobInfo()
{
	if (m_strJobID.IsEmpty())
		return;

	BSTR bsJobID = m_strJobID.AllocSysString();

	JobInfo aJobInfo;
	PSSIInfo* pPSSIInfo = NULL;
	long lPSSILen = 0;
	NetworkNode* pNode = NULL;
	long lNodeLen = 0;
	JobDetailStruct* pDetail = NULL;
	long lDetailLen = 0;

	HRESULT hr = S_OK;
	if (enumJobMode_Current == m_enumJobMode)
	{
		hr = g_smDlg->m_pIPATransfer->GetSendJobInfo(bsJobID, &aJobInfo,
															&pPSSIInfo, &lPSSILen,
															&pNode, &lNodeLen,
															&pDetail, &lDetailLen);
		if (S_OK != hr)
		{
			AfxMessageBox(_T("g_smDlg->m_pIPATransfer->GetSendJobInfo(...)"));
			return;
		}
	}
	else
	{
		if (S_OK == hr)
		{
			hr = g_smDlg->m_pIPAGeneral->GetHistoryJobInfo(bsJobID, &aJobInfo);
		}

		if (S_OK == hr)
		{
			hr = g_smDlg->m_pIPAGeneral->GetHistoryJobPSSIInfo(bsJobID, &lPSSILen, &pPSSIInfo);
		}

		if (S_OK == hr)
		{
			hr = g_smDlg->m_pIPAGeneral->GetHistoryJobNetworkNodeInfo(bsJobID, &lNodeLen, &pNode);
		}

		if (S_OK == hr)
		{
			hr = g_smDlg->m_pIPAGeneral->GetHistoryJobDetailInfo(bsJobID, &lDetailLen, &pDetail);
		}

		if (S_OK != hr)
		{
			AfxMessageBox(_T("g_smDlg->m_pIPAGeneral->GetHistoryJob...Info(...)"));
			return;
		}
	}

	UpdateJobInfo(aJobInfo,
				pPSSIInfo, lPSSILen,
				pNode, lNodeLen,
				pDetail, lDetailLen);

	// Free
}

void CSendJobDetailDlg::UpdateJobInfo(	JobInfo& aJobInfo,
						PSSIInfo* pPSSIInfo,
						long lPSSILen,
						NetworkNode* pNode,
						long lNodeLen,
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

	// Nodes
	for (i = 0; i < lNodeLen; i++)
	{
		strInfo = CBSTROpt::BSTRToCString(pNode[i].bsCalledAE);
		int iIndex = m_listNodes.InsertItem(i, strInfo);

		strInfo = CBSTROpt::BSTRToCString(pNode[i].bsIP);
		m_listNodes.SetItemText(i, 1, strInfo);

		strInfo = CBSTROpt::BSTRToCString(pNode[i].bsPort);
		m_listNodes.SetItemText(i, 2, strInfo);

		strInfo = pNode[i].bRaw ? _T("Y") : _T("");
		m_listNodes.SetItemText(i, 3, strInfo);

		strInfo = pNode[i].bProcessed ? _T("Y") : _T("");
		m_listNodes.SetItemText(i, 4, strInfo);
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

void CSendJobDetailDlg::UpdateState(BSTR bsJobID, BSTR bsState)
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

void CSendJobDetailDlg::UpdateProgress(BSTR bsJobID, BSTR bsProgress)
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

void CSendJobDetailDlg::UpdatePhase(BSTR bsJobID, BSTR bsPhase)
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

void CSendJobDetailDlg::UpdateDetail(JobDetailStruct* pDetail)
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

BOOL CSendJobDetailDlg::IsThisJob(BSTR bsJobID)
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

BOOL CSendJobDetailDlg::IsShow()
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