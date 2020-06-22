// BurnPatientInfo.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "BurnPatientInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBurnPatientInfo dialog


CBurnPatientInfo::CBurnPatientInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CBurnPatientInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBurnPatientInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBurnPatientInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBurnPatientInfo)
	DDX_Control(pDX, IDC_LIST_BURN_PATIENT, m_listBurnInfo);
	DDX_Control(pDX, IDC_STATIC_BURN_INFO_TYPE, m_BurnUIDType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBurnPatientInfo, CDialog)
	//{{AFX_MSG_MAP(CBurnPatientInfo)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBurnPatientInfo message handlers

void CBurnPatientInfo::Init()
{
	m_listBurnInfo.DeleteAllItems();
	int nColumnCount = m_listBurnInfo.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount;i++)
	{
	   m_listBurnInfo.DeleteColumn(0);
	}

	m_BurnUIDType.SetWindowText(_T(""));

}


void CBurnPatientInfo::SetPatientInfo(long lItemNum, BurnPatientInfoStruct* pBurnPatientList)
{
	m_listBurnInfo.DeleteAllItems();
	int nColumnCount = m_listBurnInfo.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount;i++)
	{
	   m_listBurnInfo.DeleteColumn(0);
	}
	
	m_BurnUIDType.SetWindowText(_T("Patient Info"));

	m_listBurnInfo.InsertColumn(0, _T("Status"), LVCFMT_CENTER, 50);
	m_listBurnInfo.InsertColumn(1, _T("Patient Name"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(2, _T("Patient ID"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(3, _T("Gender"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(4, _T("Birth Date"), LVCFMT_CENTER, 120);
// 	m_listBurnInfo.InsertColumn(5, _T("Study Num"), LVCFMT_CENTER, 100);

	BurnPatientInfoStruct* pPatientInfo = pBurnPatientList;
	CString strTemp;

	for (i = 0; i < lItemNum; i++)
	{
		m_listBurnInfo.InsertItem(0,_T(""));

		strTemp = _com_util::ConvertBSTRToString(pPatientInfo->bsPatientName);
		m_listBurnInfo.SetItemText(0,1,strTemp);

		strTemp = _com_util::ConvertBSTRToString(pPatientInfo->bsPatientID);
		m_listBurnInfo.SetItemText(0,2,strTemp);

		switch (pPatientInfo->iGender)
		{
		case 0:
			strTemp = _T("M");
			break;
		case 1:
			strTemp = _T("F");
			break;
		case 2:
			strTemp = _T("O");
			break;
		default:
			strTemp = _T("error");
			break;
		}
		m_listBurnInfo.SetItemText(0,3,strTemp);

		strTemp = DATEToDateStr(pPatientInfo->dtBirthDate);
		m_listBurnInfo.SetItemText(0,4,strTemp);

// 		strTemp.Format(_T("%d"), pPatientInfo->iStudyNumber);
// 		m_listBurnInfo.SetItemText(0,5,strTemp);

		pPatientInfo++;
	}

}

void CBurnPatientInfo::SetStudyInfo(long lItemNum, BurnStudyInfoStruct* pBurnStudyList)
{
	m_listBurnInfo.DeleteAllItems();
	int nColumnCount = m_listBurnInfo.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount;i++)
	{
	   m_listBurnInfo.DeleteColumn(0);
	}

	m_BurnUIDType.SetWindowText(_T("Study Info"));

	m_listBurnInfo.InsertColumn(0, _T("Status"), LVCFMT_CENTER, 50);
	m_listBurnInfo.InsertColumn(1, _T("Patient Name"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(2, _T("Patient ID"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(3, _T("Study ID"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(4, _T("StartStudyDateTime"), LVCFMT_CENTER, 100);
// 	m_listBurnInfo.InsertColumn(4, _T("iSeriesNumber"), LVCFMT_CENTER, 120);

	BurnStudyInfoStruct* pStudyInfo = pBurnStudyList;
	CString strTemp;

	for (i = 0; i < lItemNum; i++)
	{
		m_listBurnInfo.InsertItem(0,_T(""));
		strTemp = _com_util::ConvertBSTRToString(pStudyInfo->bsPatientName);
		m_listBurnInfo.SetItemText(0,1,strTemp);

		strTemp = _com_util::ConvertBSTRToString(pStudyInfo->bsPatientID);
		m_listBurnInfo.SetItemText(0,2,strTemp);

		strTemp.Format(_T("%d"), pStudyInfo->iStudyID);
		m_listBurnInfo.SetItemText(0,3,strTemp);

		strTemp = DATEToDateTimeStr(pStudyInfo->dtStartStudyDateTime);
		m_listBurnInfo.SetItemText(0,4,strTemp);

// 		strTemp.Format(_T("%d"), pStudyInfo->iSeriesNumber);
// 		m_listBurnInfo.SetItemText(0,4,strTemp);

		pStudyInfo++;
	}
}

void CBurnPatientInfo::SetSeriesInfo(long lItemNum, BurnSeriesInfoStruct* pBurnSeriesList)
{
	m_listBurnInfo.DeleteAllItems();
	int nColumnCount = m_listBurnInfo.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount;i++)
	{
	   m_listBurnInfo.DeleteColumn(0);
	}

	m_BurnUIDType.SetWindowText(_T("Series Info"));

	m_listBurnInfo.InsertColumn(0, _T("Status"), LVCFMT_CENTER, 50);
	m_listBurnInfo.InsertColumn(1, _T("Patient Name"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(2, _T("Patient ID"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(3, _T("Study ID"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(4, _T("Series ID"), LVCFMT_CENTER, 100);
// 	m_listBurnInfo.InsertColumn(4, _T("Number of images"), LVCFMT_CENTER, 120);

	BurnSeriesInfoStruct* pSeriesInfo = pBurnSeriesList;
	CString strTemp;

	for (i = 0; i < lItemNum; i++)
	{
		m_listBurnInfo.InsertItem(0,_T(""));

		strTemp = _com_util::ConvertBSTRToString(pSeriesInfo->bsPatientName);
		m_listBurnInfo.SetItemText(0,1,strTemp);

		strTemp = _com_util::ConvertBSTRToString(pSeriesInfo->bsPatientID);
		m_listBurnInfo.SetItemText(0,2,strTemp);

		strTemp.Format(_T("%d"), pSeriesInfo->iStudyID);
		m_listBurnInfo.SetItemText(0,3,strTemp);

		strTemp.Format(_T("%d"), pSeriesInfo->iSeriesID);
		m_listBurnInfo.SetItemText(0,4,strTemp);

// 		strTemp.Format(_T("%d"), pSeriesInfo->lNumberofImages);
// 		m_listBurnInfo.SetItemText(0,4,strTemp);

		pSeriesInfo++;
	}
}

void CBurnPatientInfo::SetImageInfo(long lItemNum, BurnImageInfoStruct* pBurnImageList)
{
	m_listBurnInfo.DeleteAllItems();
	int nColumnCount = m_listBurnInfo.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount;i++)
	{
	   m_listBurnInfo.DeleteColumn(0);
	}

	m_BurnUIDType.SetWindowText(_T("Image Info"));

	m_listBurnInfo.InsertColumn(0, _T("Status"), LVCFMT_CENTER, 50);
	m_listBurnInfo.InsertColumn(1, _T("Patient Name"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(2, _T("Patient ID"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(3, _T("Study ID"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(4, _T("Sereis ID"), LVCFMT_CENTER, 100);
	m_listBurnInfo.InsertColumn(5, _T("Image ID"), LVCFMT_CENTER, 120);

	BurnImageInfoStruct* pSeriesInfo = pBurnImageList;
	CString strTemp;

	for (i = 0; i < lItemNum; i++)
	{
		m_listBurnInfo.InsertItem(0,_T(""));

		strTemp = _com_util::ConvertBSTRToString(pSeriesInfo->bsPatientName);
		m_listBurnInfo.SetItemText(0,1,strTemp);

		strTemp = _com_util::ConvertBSTRToString(pSeriesInfo->bsPatientID);
		m_listBurnInfo.SetItemText(0,2,strTemp);

		strTemp.Format(_T("%d"), pSeriesInfo->iStudyID);
		m_listBurnInfo.SetItemText(0,3,strTemp);

		strTemp.Format(_T("%d"), pSeriesInfo->iSeriesID);
		m_listBurnInfo.SetItemText(0,4,strTemp);

		strTemp.Format(_T("%d"), pSeriesInfo->iImageID);
		m_listBurnInfo.SetItemText(0,5,strTemp);

		pSeriesInfo++;
	}
}

void CBurnPatientInfo::OnOK() 
{
	// TODO: Add extra validation here
	ShowWindow(SW_HIDE);
	
//	CDialog::OnOK();
}

BOOL CBurnPatientInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CenterWindow(NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBurnPatientInfo::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

CString CBurnPatientInfo::DATEToDateStr(DATE& dt)
{
	COleDateTime odtDateTime = dt;
	return odtDateTime.Format(_T("%Y-%m-%d"));

}

CString CBurnPatientInfo::DATEToDateTimeStr(DATE& dt)
{
	COleDateTime odtDateTime = dt;
	return odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
}
