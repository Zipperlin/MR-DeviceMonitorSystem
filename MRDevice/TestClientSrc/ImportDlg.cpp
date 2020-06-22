// ImportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern HINSTANCE g_hResourceInstance;

/////////////////////////////////////////////////////////////////////////////
// CImportDlg dialog


CImportDlg::CImportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bViewJobQueue = TRUE;
	m_pDiscImportDlg = NULL;
}


void CImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportDlg)
	DDX_Control(pDX, IDC_LIST_JOB_LIST, m_CListJobList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportDlg, CDialog)
	//{{AFX_MSG_MAP(CImportDlg)
	ON_BN_CLICKED(IDC_BUTTON_DISC_IMPORT, OnButtonDiscImport)
	ON_BN_CLICKED(IDC_BUTTON_DI_VIEWJOBINFO, OnButtonDiViewjobinfo)
	ON_BN_CLICKED(IDC_BUTTON_DI_DELETEJOB, OnButtonDiDeletejob)
	ON_BN_CLICKED(IDC_BUTTON_DI_CANCELJOB, OnButtonDiCanceljob)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_JOB_LIST, OnDblclkListJobList)
	ON_BN_CLICKED(IDC_BUTTON_DISC_IMPORT_UNFINISHEDJOB, OnButtonDiscImportUnfinishedjob)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportDlg message handlers
BOOL CImportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_CListJobList.SetExtendedStyle(m_CListJobList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_CListJobList.InsertColumn(0, _T("JobID"), LVCFMT_CENTER, 150);
	m_CListJobList.InsertColumn(1, _T("State"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(2, _T("Phase"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(3, _T("Progress"), LVCFMT_CENTER, 100);
	m_CListJobList.InsertColumn(4, _T("Detail"), LVCFMT_LEFT, 300);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportDlg::OnButtonDiscImport() 
{
	// TODO: Add your control notification handler code here
	m_pDiscImportDlg = new CDiscImportDlg;
	m_pDiscImportDlg->DoModal();
	
	delete m_pDiscImportDlg;
	m_pDiscImportDlg = NULL;
}

void CImportDlg::UpDateImportDiscInfo(BOOL bReady)
{
	if (NULL == m_pDiscImportDlg)
	{
		AfxMessageBox(_T("NULL == m_pDiscImportDlg"));
		return;
	}
	else
	{
		m_pDiscImportDlg->UpDateImportDiscInfo(bReady);
	}
}
void CImportDlg::UpDateImportDiscInfoState(LPCTSTR szState)
{
	if (NULL == m_pDiscImportDlg)
	{
		AfxMessageBox(_T("NULL == m_pDiscImportDlg"));
		return;
	}
	else
	{
		m_pDiscImportDlg->UpDateImportDiscInfoState(szState);
	}
}


void CImportDlg::UpdateJobList()
{

// 	if (!m_bViewJobQueue)
// 		return;
// 
// 	m_CListJobList.DeleteAllItems();
// 	JobInfo* pJobList = NULL;
// 	JobInfo* pJobInfo = NULL;
// 	long lJobCount = 0;
// 	HRESULT hResult =  CTestClientSrcDlg::m_pIPADiscImport->GetDiscImportJobList(&pJobList, &lJobCount);
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
// 		
// 		if (pJobList)
// 			CoTaskMemFree(pJobList);
// 	}
// 
}

void CImportDlg::UpdateJobInfo(LPCTSTR szJobID)
{
	DiscImport_SeriesStruct* pSeriesList = NULL;
	long lLen = 0;

	BSTR bsJobID = CString(szJobID).AllocSysString();
	HRESULT hResult = CTestClientSrcDlg::m_pIPADiscImport->GetDiscImportJobInfo(bsJobID, &pSeriesList, &lLen);
	if (S_OK != hResult)
	{
		AfxMessageBox(_T("CTestClientSrcDlg::m_pIPADiscImport->GetDiscImportSeries()"));
		return;
	}

	//
	
	CString strInfo;

	for (int i = 0;	i < lLen; i++)
	{
		strInfo = CBSTROpt::BSTRToCString((pSeriesList + i)->bsIndex);
 		m_CListJobList.InsertItem(i, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pSeriesList + i)->bsPatientID);
 		m_CListJobList.SetItemText(i, 1, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pSeriesList + i)->bsPatientName);
 		m_CListJobList.SetItemText(i, 2, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pSeriesList + i)->bsStudyID);
 		m_CListJobList.SetItemText(i, 3, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pSeriesList + i)->bsSeriesID);
 		m_CListJobList.SetItemText(i, 4, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pSeriesList + i)->bsState);
		m_CListJobList.SetItemText(i, 5, strInfo);

		strInfo = CBSTROpt::BSTRToCString((pSeriesList + i)->bsProgress);
		m_CListJobList.SetItemText(i, 6, strInfo);


		// Job detail info
		strInfo = CBSTROpt::BSTRToCString((pSeriesList + i)->bsDetailInfo);
 		m_CListJobList.SetItemText(i, 7, strInfo);


	}

}


void CImportDlg::SetJobState(LPCTSTR szJobID, JobState enumJobState)
{
	if (!m_bViewJobQueue)
		return;

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


void CImportDlg::SetJobPhase(LPCTSTR szJobID, LPCTSTR szJobPhase)
{
	if (!m_bViewJobQueue)
		return;

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

void CImportDlg::SetJobProgress(JobProgressStruct* pJobProgressStruct)
{
	if (!m_bViewJobQueue)
		return;

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

void CImportDlg::SetJobDetail(JobDetailStruct* pJobDetailStruct)
{
// 	if (!m_bViewJobQueue)
// 		return;
// 
// 	CString strDstJobID = _com_util::ConvertBSTRToString(pJobDetailStruct->bsJobUID);
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


void CImportDlg::ImportedSeriesStateChanged(DiscImport_SeriesStateStruct* pState)
{
	if (m_bViewJobQueue)
		return;

	if (m_strViewedJobID.CompareNoCase(CString(_com_util::ConvertBSTRToString(pState->bsJobID))))
		return;

	CString strChangedSeriesIndex;
	strChangedSeriesIndex = CBSTROpt::BSTRToCString(pState->bsIndex);

	for (int i = 0; i < m_CListJobList.GetItemCount(); i++)
	{
		CString strSeriesIndex = m_CListJobList.GetItemText(i, 0);
		if (!strSeriesIndex.Compare(strChangedSeriesIndex))
		{
			m_CListJobList.SetItemText(i, 5, CBSTROpt::BSTRToCString(pState->bsState));
		}
	}
}

void CImportDlg::ImportedSeriesProgressChanged(DiscImport_SeriesProgressStruct* pProgress)
{
	if (m_bViewJobQueue)
		return;

	if (m_strViewedJobID.CompareNoCase(CString(_com_util::ConvertBSTRToString(pProgress->bsJobID))))
		return;

	CString strChangedSeriesIndex = CBSTROpt::BSTRToCString(pProgress->bsIndex);

	CString strProgress = CBSTROpt::BSTRToCString(pProgress->bsProgress);

	for (int i = 0; i < m_CListJobList.GetItemCount(); i++)
	{
		CString strSeriesIndex = m_CListJobList.GetItemText(i, 0);
		if (!strSeriesIndex.Compare(strChangedSeriesIndex))
		{
			m_CListJobList.SetItemText(i, 6, strProgress);
			break;
		}
	}
}

void CImportDlg::ImportedSeriesDetailChanged(DiscImport_SeriesDetailStruct* pDetail)
{
	if (m_bViewJobQueue)
		return;

	if (m_strViewedJobID.CompareNoCase(CString(_com_util::ConvertBSTRToString(pDetail->bsJobID))))
		return;

	CString strChangedSeriesIndex = CBSTROpt::BSTRToCString(pDetail->bsIndex);

	CString strDetail = CBSTROpt::BSTRToCString(pDetail->bsDetailInfo);

	for (int i = 0; i < m_CListJobList.GetItemCount(); i++)
	{
		CString strSeriesIndex = m_CListJobList.GetItemText(i, 0);
		if (!strSeriesIndex.Compare(strChangedSeriesIndex))
		{
			m_CListJobList.SetItemText(i, 7, strDetail);
	
			break;
		}
	}
}

void CImportDlg::OnButtonDiViewjobinfo() 
{
	// TODO: Add your control notification handler code here


	if (m_bViewJobQueue)
	{
		// select a Job?
		POSITION pos = m_CListJobList.GetFirstSelectedItemPosition();
		if (pos == NULL)
		{
			AfxMessageBox(_T("Plz select a Job!"));
			return;
		}
		else
		{
			while (pos)
			{
				
				int nItem = m_CListJobList.GetNextSelectedItem(pos);
				m_strViewedJobID = m_CListJobList.GetItemText(nItem, 0);
				break;
			}
		}

		// Selected a Job
		m_bViewJobQueue = FALSE;
	
		GetDlgItem(IDC_STATIC_JOB_QUEUE)->SetWindowText(_T("Job Info"));

		GetDlgItem(IDC_BUTTON_DI_CANCELJOB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_DI_DELETEJOB)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_DI_VIEWJOBINFO)->SetWindowText(_T("ViewJobs"));

		//清空CListCtrl items and columns
		m_CListJobList.DeleteAllItems();
		int nColumnCount = m_CListJobList.GetHeaderCtrl()->GetItemCount();

		// Delete all of the columns.
		for (int i=0;i < nColumnCount; i++)
		{
		   m_CListJobList.DeleteColumn(0);
		}

		m_CListJobList.InsertColumn(0, _T("Index"), LVCFMT_LEFT, 50);
		m_CListJobList.InsertColumn(1, _T("PatientID"), LVCFMT_LEFT, 100);
		m_CListJobList.InsertColumn(2, _T("PatientName"), LVCFMT_LEFT, 100);
		m_CListJobList.InsertColumn(3, _T("StudyID"), LVCFMT_LEFT, 70);
		m_CListJobList.InsertColumn(4, _T("SeriesID"), LVCFMT_LEFT, 70);
		m_CListJobList.InsertColumn(5, _T("State"), LVCFMT_LEFT, 70);
		m_CListJobList.InsertColumn(6, _T("Progress"), LVCFMT_LEFT, 70);
		m_CListJobList.InsertColumn(7, _T("Detail"), LVCFMT_LEFT, 600);

		// 获取JobInfo
		UpdateJobInfo(m_strViewedJobID);
	}
	else
	{
		m_bViewJobQueue = TRUE;
		m_strViewedJobID = _T("");

		GetDlgItem(IDC_STATIC_JOB_QUEUE)->SetWindowText(_T("Job Queue"));

		GetDlgItem(IDC_BUTTON_DI_CANCELJOB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_DI_DELETEJOB)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_DI_VIEWJOBINFO)->SetWindowText(_T("ViewJobInfo"));

			//清空CListCtrl items and columns
		m_CListJobList.DeleteAllItems();
		int nColumnCount = m_CListJobList.GetHeaderCtrl()->GetItemCount();

		// Delete all of the columns.
		for (int i=0;i < nColumnCount; i++)
		{
		   m_CListJobList.DeleteColumn(0);
		}

		m_CListJobList.InsertColumn(0, _T("JobID"), LVCFMT_CENTER, 150);
		m_CListJobList.InsertColumn(1, _T("State"), LVCFMT_CENTER, 100);
		m_CListJobList.InsertColumn(2, _T("Phase"), LVCFMT_CENTER, 100);
		m_CListJobList.InsertColumn(3, _T("Progress"), LVCFMT_CENTER, 100);
		m_CListJobList.InsertColumn(4, _T("Detail"), LVCFMT_LEFT, 300);

		// 获取JobList
		UpdateJobList();

	}
}

void CImportDlg::OnButtonDiDeletejob() 
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

// 		CTestClientSrcDlg::m_pIPADiscImport->DeleteDiscImportJob(bsJobID);
	}
}

void CImportDlg::OnButtonDiCanceljob() 
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
// 		CTestClientSrcDlg::m_pIPADiscImport->CancelDiscImportJob(bsJobID);
	}
}

void CImportDlg::OnDblclkListJobList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	if (!m_bViewJobQueue)
	{
		OnButtonDiViewjobinfo();
		return;
	}
	else
	{
		if(pNMListView->iItem == -1)
		{
			return;
		}

		CString strJobID = m_CListJobList.GetItemText(pNMListView->iItem, 0);
		if (strJobID.IsEmpty())
			return;

		OnButtonDiViewjobinfo();
	}



}

void CImportDlg::OnButtonDiscImportUnfinishedjob() 
{
	// TODO: Add your control notification handler code here
	BOOL bExist = FALSE;
	if (S_OK !=CTestClientSrcDlg::m_pIPADiscImport->IsUnfinishedDiscImportJobExist(&bExist))
	{
		AfxMessageBox(_T("m_pIPADiscImport->IsUnfinishedDiscImportJobExist()"));
	}
	else
	{
		if (bExist)
		{
			AfxMessageBox(_T("There IS unfinished DiscImport Job"));
		}
		else
		{
			AfxMessageBox(_T("There is NOT unfinished DiscImport Job"));
		}
	}
}
