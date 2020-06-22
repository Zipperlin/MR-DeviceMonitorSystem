// ImportJobDetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "ImportJobDetailDlg.h"
#include "TestClientSrcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CTestClientSrcDlg* g_smDlg; 

/////////////////////////////////////////////////////////////////////////////
// CImportJobDetailDlg dialog


CImportJobDetailDlg::CImportJobDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportJobDetailDlg::IDD, pParent)
{
	m_strJobID = _T("");

	//{{AFX_DATA_INIT(CImportJobDetailDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CImportJobDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportJobDetailDlg)
	DDX_Control(pDX, IDC_LIST_IMPORT_JOB_DETAIL, m_listImages);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportJobDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CImportJobDetailDlg)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_JOB_DETAIL_CLOSE, OnButtonImportJobDetailClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportJobDetailDlg message handlers
BOOL CImportJobDetailDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listImages.SetExtendedStyle(m_listImages.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listImages.InsertColumn(0, _T("Index"), LVCFMT_LEFT, 50);
	m_listImages.InsertColumn(1, _T("PatientID"), LVCFMT_LEFT, 100);
	m_listImages.InsertColumn(2, _T("PatientName"), LVCFMT_LEFT, 100);
	m_listImages.InsertColumn(3, _T("StudyID"), LVCFMT_LEFT, 70);
	m_listImages.InsertColumn(4, _T("SeriesID"), LVCFMT_LEFT, 70);
	m_listImages.InsertColumn(5, _T("ImageID"), LVCFMT_LEFT, 70);
	m_listImages.InsertColumn(6, _T("State"), LVCFMT_LEFT, 70);
	m_listImages.InsertColumn(7, _T("Progress"), LVCFMT_LEFT, 70);
	m_listImages.InsertColumn(8, _T("Detail"), LVCFMT_LEFT, 600);

	RefreshList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportJobDetailDlg::OnButtonImportJobDetailClose() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CImportJobDetailDlg::SetJobMode(JobMode enumJobMode)
{
	m_enumJobMode = enumJobMode;
}

void CImportJobDetailDlg::SetJob(LPCTSTR szJobID)
{
	m_strJobID = szJobID;
}

LPCTSTR CImportJobDetailDlg::GetJob()
{
	return m_strJobID;
}

void CImportJobDetailDlg::RefreshList()
{
	if (m_strJobID.IsEmpty())
		return;

	BSTR bsJobID = m_strJobID.AllocSysString();
	DiscImport_SeriesStruct* pImagesList = NULL;
	long lLen = 0;

	HRESULT hr = S_OK;

	if (enumJobMode_Current == m_enumJobMode)
	{
		hr = g_smDlg->m_pIPADiscImport->GetDiscImportJobInfo(bsJobID, &pImagesList, &lLen);
		if (S_OK != hr)
		{
			AfxMessageBox(_T("g_smDlg->m_pIPADiscImport->GetDiscImportJobList(...)"));
			return;
		}
	}
	else
	{
		hr = g_smDlg->m_pIPAGeneral->GetHistoryJobDiscImportImageInfo(bsJobID, &lLen, &pImagesList);
		if (S_OK != hr)
		{
			AfxMessageBox(_T("g_smDlg->m_pIPADiscImport->GetDiscImportJobList(...)"));
			return;
		}
	}

	UpdateJobInfo(pImagesList, lLen);

	// Free
}

void CImportJobDetailDlg::UpdateJobInfo(DiscImport_SeriesStruct* pImagesList,
										long lLen)
{
	CString strInfo;

	for (int i = 0;	i < lLen; i++)
	{
		strInfo = CBSTROpt::BSTRToCString((pImagesList + i)->bsIndex);
 		m_listImages.InsertItem(i, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pImagesList + i)->bsPatientID);
 		m_listImages.SetItemText(i, 1, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pImagesList + i)->bsPatientName);
 		m_listImages.SetItemText(i, 2, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pImagesList + i)->bsStudyID);
 		m_listImages.SetItemText(i, 3, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pImagesList + i)->bsSeriesID);
 		m_listImages.SetItemText(i, 4, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pImagesList + i)->bsImageID);
 		m_listImages.SetItemText(i, 5, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pImagesList + i)->bsState);
		m_listImages.SetItemText(i, 6, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pImagesList + i)->bsProgress);
		m_listImages.SetItemText(i, 7, strInfo);


		// Job detail info
		strInfo = CBSTROpt::BSTRToCString((pImagesList + i)->bsDetailInfo);
 		m_listImages.SetItemText(i, 8, strInfo);
	}
}

void CImportJobDetailDlg::UpdateImageState(DiscImport_SeriesStateStruct* pState)
{
	if (!IsThisJob(pState->bsJobID))
	{
		return;
	}

	if (!IsShow())
	{
		return;
	}

	CString strImageIndex = CBSTROpt::BSTRToCString(pState->bsIndex);
	for (int i = 0; i < m_listImages.GetItemCount(); i++)
	{
		CString strListImageIndex = m_listImages.GetItemText(i, 0);
		if (!strListImageIndex.Compare(strImageIndex))
		{
			CString strInfo = CBSTROpt::BSTRToCString(pState->bsState);
			m_listImages.SetItemText(i, 6, strInfo);
	
			break;
		}
	}
}

void CImportJobDetailDlg::UpdateImageProgress(DiscImport_SeriesProgressStruct* pProgress)
{
	if (!IsThisJob(pProgress->bsJobID))
	{
		return;
	}

	if (!IsShow())
	{
		return;
	}

	CString strImageIndex = CBSTROpt::BSTRToCString(pProgress->bsIndex);
	for (int i = 0; i < m_listImages.GetItemCount(); i++)
	{
		CString strListImageIndex = m_listImages.GetItemText(i, 0);
		if (!strListImageIndex.Compare(strImageIndex))
		{
			CString strInfo = CBSTROpt::BSTRToCString(pProgress->bsProgress);
			m_listImages.SetItemText(i, 7, strInfo);
	
			break;
		}
	}
}

void CImportJobDetailDlg::UpdateImageDetail(DiscImport_SeriesDetailStruct* pDetail)
{
	if (!IsThisJob(pDetail->bsJobID))
	{
		return;
	}

	if (!IsShow())
	{
		return;
	}

	CString strImageIndex = CBSTROpt::BSTRToCString(pDetail->bsIndex);
	for (int i = 0; i < m_listImages.GetItemCount(); i++)
	{
		CString strListImageIndex = m_listImages.GetItemText(i, 0);
		if (!strListImageIndex.Compare(strImageIndex))
		{
			CString strInfo = CBSTROpt::BSTRToCString(pDetail->bsDetailInfo);
			m_listImages.SetItemText(i, 8, strInfo);
	
			break;
		}
	}
}

BOOL CImportJobDetailDlg::IsThisJob(BSTR bsJobID)
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

BOOL CImportJobDetailDlg::IsShow()
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