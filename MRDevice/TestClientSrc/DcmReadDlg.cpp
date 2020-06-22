// DcmReadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "testclientsrcDlg.h"
#include "DcmReadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CTestClientSrcDlg* g_smDlg;

void ShowMsg(LPCTSTR szTagNum, LPCTSTR szTagName, LPCTSTR szTagValue)
{
	g_smDlg->m_pDcmReadDlg->AddMsg(szTagNum, szTagName, szTagValue);
}



/////////////////////////////////////////////////////////////////////////////
// CDcmReadDlg dialog


CDcmReadDlg::CDcmReadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDcmReadDlg::IDD, pParent)
{
	m_pNDcmDir = NULL;
	m_pNFileFormat = NULL;
	hThreadLoadDcm = NULL;
	//{{AFX_DATA_INIT(CDcmReadDlg)
	//}}AFX_DATA_INIT
}


void CDcmReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDcmReadDlg)
	DDX_Control(pDX, IDC_LIST_VIEW_DCM_INFO, m_listDcmInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDcmReadDlg, CDialog)
	//{{AFX_MSG_MAP(CDcmReadDlg)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_DCM_IMAGE, OnButtonLoadDcmImage)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_RAW_IMAGE, OnButtonSaveRawImage)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_TAG, OnButtonViewTag)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_PATIENT_INFO, OnButtonViewPatientInfo)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_DCMDIR, OnButtonLoadDcmdir)
	ON_EN_CHANGE(IDC_EDIT_SEARCH, OnChangeEditSearch)
	ON_BN_CLICKED(IDC_BUTTON_L_DCM, OnButtonLDcm)
	ON_BN_CLICKED(IDC_BUTTON_L_DCMDIR, OnButtonLDcmdir)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_L, OnButtonCancelL)
	ON_BN_CLICKED(IDC_BUTTON_DCM_MODIFY, OnButtonDcmModify)
	ON_BN_CLICKED(IDC_BUTTON_GEN_DCMDIR, OnButtonGenDcmdir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDcmReadDlg message handlers





void CDcmReadDlg::OnButtonLoadDcmImage() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	static TCHAR BASED_CODE szFilter[] = _T("(*.*)|*.*||");


	CFileDialog dlgOpen(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, szFilter, this);

	// do nothing if IDCANCEL is returned

	CString strFileName;
	
	if (dlgOpen.DoModal() == IDOK)
	{
		// retrieve and display the selected file name
		strFileName = dlgOpen.GetPathName();

		// Load Dcm Image
		LoadDcmFile(strFileName);
		
	}

}

void CDcmReadDlg::OnButtonSaveRawImage() 
{
	// TODO: Add your control notification handler code here
// 	CFileDialog dlgSave(FALSE);
// 	CString strFileName;
// 
// 	if (dlgSave.DoModal() == IDOK)
// 	{
// 		// retrieve and display the selected file name
// 		strFileName = dlgSave.GetPathName();
// 		DWORD dwFramNum = 0;
// 		if (!m_DcmParser.GetFramesNumber(&dwFramNum))
// 		{
// 			AfxMessageBox(_T("error: m_DcmParser.GetFramesNumber(&dwFramNum)"));
// 			return;
// 		}
// 
// 		// Save Raw
// 		HANDLE hFile; 
// 		void* pFrameBuffer = NULL;
// 		long lFrameSize = 0;
// 		DWORD dwBytesWritten = 0;
//  
// 		hFile = CreateFile(strFileName,           // open MYFILE.TXT 
// 						GENERIC_WRITE,              // open for reading 
// 						FILE_SHARE_READ,           // share for reading 
// 						NULL,                      // no security 
// 						CREATE_ALWAYS,             // existing file only 
// 						FILE_ATTRIBUTE_NORMAL,     // normal file 
// 						NULL);                     // no attr. template 
//  
// 		if (hFile == INVALID_HANDLE_VALUE) 
// 		{
// 			AfxMessageBox(_T("error: CreateFile()"));
// 			return;
// 		}		
// 
// 		if (0xffffffff==::SetFilePointer(hFile,65536,NULL,FILE_BEGIN))
// 		{
// 			AfxMessageBox(_T("error: SeekFile()"));
// 			CloseHandle(hFile);
// 			return;
// 		}
// 
// 		for (int i = 0; i < dwFramNum; i++)
// 		{
// 			if (!m_DcmParser.GetFramePixelData(pFrameBuffer, i, lFrameSize))
// 			{
// 				AfxMessageBox(_T("error: m_DcmParser.GetFramePixelData()"));
// 				CloseHandle(hFile);
// 				return;
// 			}
// 
// 			if (!::WriteFile(hFile, pFrameBuffer, lFrameSize, &dwBytesWritten, NULL))
// 			{
// 				AfxMessageBox(_T("error: WriteFile()"));
// 				CloseHandle(hFile);
// 				return;
// 			}
// 			else if (lFrameSize != dwBytesWritten)
// 			{
// 				AfxMessageBox(_T("error: WriteFile(), lFrameSize != dwBytesWritten"));
// 				CloseHandle(hFile);
// 				return;
// 			}
// 		}
// 
// 		CloseHandle(hFile);
// 	}
		
}

void CDcmReadDlg::LoadDcmFile(LPCTSTR szDcmFile)
{
	if (!m_DcmParser.LoadDXDcmFile(szDcmFile))
	{
		AfxMessageBox(_T("Error: m_DcmParser.LoadXADcmFile(szDcmFile)!"));
	}

}

void CDcmReadDlg::OnButtonViewTag() 
{
	// TODO: Add your control notification handler code here

	// Set the CListCtrl
	m_listDcmInfo.DeleteAllItems();
	int nColumnCount = m_listDcmInfo.GetHeaderCtrl()->GetItemCount();

	// Delete all of the columns.
	for (int i=0;i < nColumnCount; i++)
	{
	   m_listDcmInfo.DeleteColumn(0);
	}

	// 排序
	m_listDcmInfo.ModifyStyle(0, LVS_SORTASCENDING);
	m_listDcmInfo.InsertColumn(0, _T("Tag"), LVCFMT_LEFT, 80);
	m_listDcmInfo.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 200);
	m_listDcmInfo.InsertColumn(2, _T("Value"), LVCFMT_LEFT, 400);

	if (!m_DcmParser.GetTagInfo(ShowMsg))
	{
		AfxMessageBox(_T("m_DcmParser.GetTagInfo(ShowMsg)"));
	}

// 	static TCHAR BASED_CODE szFilter[] = _T("(*.*)|*.*||");
// 
// 
// 	CFileDialog dlgOpen(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, szFilter, this);
// 
// 	// do nothing if IDCANCEL is returned
// 
// 	CString strFileName;
// 	
// 	if (dlgOpen.DoModal() == IDOK)
// 	{
// 		// retrieve and display the selected file name
// 		strFileName = dlgOpen.GetPathName();
// 
// 		// Set the CListCtrl
// 		m_listDcmInfo.DeleteAllItems();
// 		int nColumnCount = m_listDcmInfo.GetHeaderCtrl()->GetItemCount();
// 
// 		// Delete all of the columns.
// 		for (int i=0;i < nColumnCount; i++)
// 		{
// 		   m_listDcmInfo.DeleteColumn(0);
// 		}
// 
// 		// 排序
// 	 	m_listDcmInfo.ModifyStyle(0, LVS_SORTASCENDING);
// 		m_listDcmInfo.InsertColumn(0, _T("DICOM Tag Info"), LVCFMT_CENTER, 500);
// 
// 		// Load Dcm Image
// //		CDcmInfoViewer DcmInfoViewer;
// //		DcmInfoViewer.ViewDcm(strFileName, ShowMsg);
// 
// 		m_R2D.GetTagInfo(ShowMsg);
// 		
// 	}
}

void CDcmReadDlg::OnButtonViewPatientInfo() 
{
	// TODO: Add your control notification handler code here

// 	if (!m_DcmParser.InitCVDicomXAStructFromNFileFormatObj())
// 	{
// 		AfxMessageBox(_T("Error: m_DcmParser.InitCVDicomXAStructFromNFileFormatObj()"));
// 		return;
// 	}
// 
// 	CVDcmSysPatientTotalInfoStruct PatientTotalInfo;
// 	if (!m_DcmParser.GetPatientTotalInfo(&PatientTotalInfo))
// 	{
// 		AfxMessageBox(_T("Error: m_DcmParser.GetPatientTotalInfo(&PatientTotalInfo)"));
// 		return;
// 	}
// 
// 	// Set the CListCtrl
// 	m_listDcmInfo.DeleteAllItems();
// 	int nColumnCount = m_listDcmInfo.GetHeaderCtrl()->GetItemCount();
// 
// 	// Delete all of the columns.
// 	for (int i=0;i < nColumnCount; i++)
// 	{
// 	   m_listDcmInfo.DeleteColumn(0);
// 	}
// 
// 	// 取消排序
// 	m_listDcmInfo.ModifyStyle(LVS_SORTASCENDING, 0);
// //	m_listDcmInfo.SetExtendedStyle(m_listDcmInfo.GetExtendedStyle() | ~(LVS_SORTASCENDING | LVS_SORTDESCENDING));
// 
// 	m_listDcmInfo.InsertColumn(0, _T("Session"), LVCFMT_LEFT, 100);
// 	m_listDcmInfo.InsertColumn(1, _T("Attribute"), LVCFMT_LEFT, 150);
// 	m_listDcmInfo.InsertColumn(2, _T("Value"), LVCFMT_LEFT, 400);
// 
// 	int iItenNum = 0;
// 	CString strInfo = _T("");
// 	COleDateTime odtDateTime;
// 
// 	
// 	// Patient Info
//  	m_listDcmInfo.InsertItem(iItenNum, _T("Patient"));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T(""));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,_T(""));
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientUID"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.PatientInfo.g_strPatientUID);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientID"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.PatientInfo.g_strPatientID);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientName"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.PatientInfo.g_strPatientName);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientFullName"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.PatientInfo.g_strPatientFullName);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("Gender"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.PatientInfo.g_iGender);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("BirthDate"));
// 	odtDateTime = PatientTotalInfo.PatientInfo.g_dtBirthDate;
// 	strInfo = odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("RegDateTime"));
// 	odtDateTime = PatientTotalInfo.PatientInfo.g_dtRegDateTime;
// 	strInfo = odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientAge"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.PatientInfo.g_iPatientAge);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientAgeUnit"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.PatientInfo.g_iPatientAgeUnit);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("LockFlag"));
// 	PatientTotalInfo.PatientInfo.g_bLockFlag ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientComment"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.PatientInfo.g_strPatientComment);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("EmergencyFlag"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.PatientInfo.g_usEmergencyFlag);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("EthnicGroup"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.PatientInfo.g_strEthnicGroup);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("OtherPatientID"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.PatientInfo.g_strOtherPatientIDs);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("OtherPatientName"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.PatientInfo.g_strOtherPatientName);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("Occupation"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.PatientInfo.g_strOccupation);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientImageFilePath"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.PatientInfo.g_strPatientImagePath);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ConfidentialFlag"));
// 	PatientTotalInfo.PatientInfo.g_bConfidentialityFlag ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("TotalFluoTime"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.PatientInfo.g_uiTotalFluoTime);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ImportedPatientOrNot"));
// 	PatientTotalInfo.PatientInfo.g_bImportedOrNot ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
// 
// 
// 	// Study
//  	m_listDcmInfo.InsertItem(iItenNum, _T("Study"));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T(""));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,_T(""));
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyUID"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.StudyInfo.g_strStudyUID);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientUID"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.StudyInfo.g_strPatientUID);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyID"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.StudyInfo.g_iStudyID);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ApplicationGroupUID"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.StudyInfo.g_lApplicationGroupUID);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ApplicationUID"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.StudyInfo.g_lApplicationUID);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("StartStudyDateTime"));
// 	odtDateTime = PatientTotalInfo.StudyInfo.g_dtStartStudyDateTime;
// 	strInfo = odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("EndStudyDateTime"));
// 	odtDateTime = PatientTotalInfo.StudyInfo.g_dtEndStudyDateTime;
// 	strInfo = odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ReferringPhysicianName"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.StudyInfo.g_strReferringPhysicianName);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("FieldServiceFlag"));
// 	PatientTotalInfo.StudyInfo.g_bFieldServiceFlag ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientSize"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.StudyInfo.g_dbPatientSize);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientWeight"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.StudyInfo.g_dbPatientWeight);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyDescription"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.StudyInfo.g_strStudyDescription);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PrintStatus"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.StudyInfo.g_iPrintStatus);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ArchiveFlag"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.StudyInfo.g_iArchiveFlag);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ProtectFlag"));
// 	PatientTotalInfo.StudyInfo.g_bProtectFlag ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ExportFlag"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.StudyInfo.g_iExportFlag);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ExamStatus"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.StudyInfo.g_iExamStatus);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientHistory"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.StudyInfo.g_strPatientHistory);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyImageFilePath"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.StudyInfo.g_strStudyImagePath);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("OperatorName"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.StudyInfo.g_strOperatorName);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("EmergencyFlag"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.StudyInfo.g_usEmergencyFlag);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ImportedStudyOrNot"));
// 	PatientTotalInfo.StudyInfo.g_bImportedOrNot ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
// 
// 	// Series
//  	m_listDcmInfo.InsertItem(iItenNum, _T("Series"));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T(""));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,_T(""));
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("SeriesUID"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_strSeriesUID);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyUID"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_strStudyUID);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("SeriesID"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iSeriesID);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("SeriesType"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iSeriesType);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("Laterality"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iLaterality);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("SeriesDescription"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_strSeriesDescription);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PerformingPhysicianName"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_strPerformingPhysicianName);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("OperatorName"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_strOperatorName);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("NumberofImages"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_lNumberofImages);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ImageFilePath"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_strImageFilePath);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ShutterShape"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iShutterShape);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ShutterLefVerticalEdge"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_lShutterLefVerticalEdge);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ShutterRightVerticalEdge"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_lShutterRightVerticalEdge);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ShutterUpperHorizontalEdge"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_lShutterUpperHorizontalEdge);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ShutterLowerHorizontalEdge"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_lShutterLowerHorizontalEdge);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("CenterofCircularShutter"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_lCenterofCircularShutter);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("RadiusofCircularShutter"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_lRadiusofCircularShutter);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("LegsOrientation"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iLegsOrientation);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("NoseOrientation"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iNoseOrientation);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("LArmOrientation"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iLArmOrientation);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("Contrast"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_fConstrast);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("Brightness"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_fBrightness);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("VideoInvert"));
// 	PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_bVideoInvert ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("Enhancement"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iEnhencement);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ReconStartDateTime"));
// 	odtDateTime = PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dtReconStartDateTime;
// 	strInfo = odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("IntervalTime"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iIntervalTime);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("KV"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbKV);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("MA"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbMA);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("MS"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbMS);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("MAS"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbMAS);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("RotationAngle"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbRotationAngle);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("AngulationAngle"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbAngulationAngle);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ContrastAgent"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_strContrastAgent);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("SourceImageDistance"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbSourceImageDistance);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("XRaySorToPatSupportRange"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbXRaySrceToPatSupportRange);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("TableHeight"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbTableHeight);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("TableLateral"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbTableLateral);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("TableLongitudinal"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbTableLongitudinal);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PixelSpacingX"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbPixelSpacingX);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PixelSpacingY"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbPixelSpacingY);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("CumulativeAreaDose"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbCumulativeAreaDose);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("CumulativeSkinDose"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_dbCumulativeSkinDose);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ReferenceImageFlag"));
// 	PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_bReferenceImageFlag ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("NoiseReduce"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iNoiseReduce);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("RunStartIndex"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iRunStartIndex);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("MaskImageIndex"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iMaskImageIndex);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ApplicationGroupUID"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_lApplicationGroupUID);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ApplicationUID"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_lApplicationUID);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ImportedOrNot"));
// 	PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_bImportedOrNot ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ImageColumns"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iImageColumns);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ImageRows"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iImageRows);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ImageBitStored"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.SeriesInfo.g_iImageBitStored);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
// 	// FluoSeries
//  	m_listDcmInfo.InsertItem(iItenNum, _T("FluoSeries"));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T(""));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,_T(""));
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("FluoFlavorLevel"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.FluoSeriesInfo.g_iFluoFlavorLevel);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PlusedFluoSpeed"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.FluoSeriesInfo.g_iPulseFluoSpeed);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("FluoViewMode"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.FluoSeriesInfo.g_usFluoviewMode);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
// 	// ExposureSeries
//  	m_listDcmInfo.InsertItem(iItenNum, _T("ExposureSeries"));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T(""));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,_T(""));
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ProcedureUID"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.ExposureSeriesInfo.g_lProcedureUID);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("DetectorDose"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.ExposureSeriesInfo.g_dbDetectorDose);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ReceptorFieldSize"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.ExposureSeriesInfo.g_iReceptorFiledSize);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ReceptorDiameter"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.ExposureSeriesInfo.g_iReceptorDiameter);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("FrameSpeed"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.ExposureSeriesInfo.g_iFrameSpeed);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
// 	// PostProcessing
//  	m_listDcmInfo.InsertItem(iItenNum, _T("PostProcessing"));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T(""));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,_T(""));
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("SeriesUID"));
//  	m_listDcmInfo.SetItemText(iItenNum++,2,PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_strSeriesUID);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ChangeFlag"));
// 	PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_bChangeFlag ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("LogLUT"));
// 	PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_bLogLUT ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("Subtract"));
// 	PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_bSubtract ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("LandMarking"));
// 	PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_bLandMarking ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PixelShift"));
// 	PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_bPixelShift ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PixelShift_X"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_iPixelShift_X);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("PixelShift_Y"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_iPixelShift_Y);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("MaskIndex"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_iMaskIndex);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("SubGain"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_fSubGain);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("SubOffset"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_iSubOffset);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("LandmarkingGain"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_fLandmarkingGain);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("EdgeenhancmentLevel"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_iEdgeenhancmentLevel);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("WW"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_iWW);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("WL"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_iWL);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("Rotation"));
// 	strInfo.Format(_T("%d"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_iRotation);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("Inverse"));
// 	PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_bInverse ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("ZoomFactor"));
// 	strInfo.Format(_T("%.6f"), PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_fZoomFactor);
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 
//  	m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  	m_listDcmInfo.SetItemText(iItenNum,1,_T("Shutter"));
// 	PatientTotalInfo.SeriesTotalInfo.PostProcessingInfo.g_bShutter ? strInfo = _T("TRUE") : strInfo = _T("FALSE");
//  	m_listDcmInfo.SetItemText(iItenNum++,2,strInfo);
// 


// 	m_listDcmInfo.SetItemText(0,3,"M");
// 	m_listDcmInfo.SetItemText(0,4,"1970-03-05");
// 	m_listDcmInfo.SetItemText(0,5,"2");
}


void CDcmReadDlg::AddMsg(LPCTSTR szTagNum, LPCTSTR szTagName, LPCTSTR szTagValue)
{

	int nColumnCount = m_listDcmInfo.GetHeaderCtrl()->GetItemCount();
	int iIndex = m_listDcmInfo.InsertItem(nColumnCount, szTagNum);
	m_listDcmInfo.SetItemText(iIndex, 1, szTagName);
	m_listDcmInfo.SetItemText(iIndex, 2, szTagValue);
}

BOOL CDcmReadDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_listDcmInfo.SetExtendedStyle(m_listDcmInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDcmReadDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CDcmReadDlg::OnButtonSearch() 
{
	// TODO: Add your control notification handler code here

	CString strText;
	BOOL bFind = FALSE;

	GetDlgItem(IDC_EDIT_SEARCH)->GetWindowText(strText);

	if (strText.IsEmpty())
		return;

	strText.MakeLower();

	int nItemCount = m_listDcmInfo.GetItemCount();
	int nColumnCount = m_listDcmInfo.GetHeaderCtrl()->GetItemCount();
// 	for (int i = 0; i < nItemCount; i++)
// 	{
// 		m_listDcmInfo.SetItemTextColor(i,  COLORREF(RGB(0, 0, 0)));
// 	}
// 	m_listDcmInfo.RedrawItems(0, m_listDcmInfo.GetItemCount());

	CString strItemText;
	for (int i = 0; i < nItemCount; i++)
	{
		for (int j = 0; j < nColumnCount; j++)
		{
			strItemText = m_listDcmInfo.GetItemText(i, j);
			strItemText.MakeLower();
			if (-1 != strItemText.Find(strText))
			{				
				// got one
				bFind = TRUE;
				m_listDcmInfo.SetSubItemTextColor(i, j, COLORREF(RGB(255, 0, 0)));
			}
			else
			{
				m_listDcmInfo.SetSubItemTextColor(i, j, COLORREF(RGB(0, 0, 0)));
			}
		}
	}
	m_listDcmInfo.RedrawItems(0, m_listDcmInfo.GetItemCount());

	if (!bFind)
	{
		AfxMessageBox(_T("Not Found!"));
	}
}

void CDcmReadDlg::OnButtonLoadDcmdir() 
{
	// TODO: Add your control notification handler code here
	static TCHAR BASED_CODE szFilter[] = _T("(*.*)|*.*||");


	CFileDialog dlgOpen(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, szFilter, this);

	// do nothing if IDCANCEL is returned

	CString strFileName;
	
// 	if (dlgOpen.DoModal() == IDOK)
// 	{
// 		// retrieve and display the selected file name
// 		strFileName = dlgOpen.GetPathName();
// 
// 		LPCTSTR p = wcsrchr(strFileName, _T('\\'));
// 		if (CString(p+1).CompareNoCase(_T("DICOMDIR")))
// 		{
// 			return;
// 		}
// 
// 		// Load Dcm Image
// 		CDcmDirParser DcmDirParser;
// 		if (!DcmDirParser.LoadDcmDir(strFileName))
// 		{
// 			AfxMessageBox(_T("DcmDirParser.LoadDcmDir(strFileName)"));
// 			return;
// 		}
// 
// 		CString strImpClassUID;
// 		LPCTSTR szImpClassUID = NULL;
// 		if (!DcmDirParser.GetImplementationClassUID(&szImpClassUID))
// 		{
// 			AfxMessageBox(_T("DcmDirParser.GetImplementationClassUID()"));
// 			return;
// 		}
// 		else
// 		{
// 			strImpClassUID = szImpClassUID;
// 		}
// 
// 		DICOMDIRPatientsTotalInfo* pDcmDirPTI;
// 		if (!DcmDirParser.GetDirPatientsInfo(&pDcmDirPTI))
// 		{
// 			AfxMessageBox(_T("DcmDirParser.GetDirPatientsInfo(&pDcmDirPTI)"));
// 			return;
// 		}
// 		// Set the CListCtrl
// 		m_listDcmInfo.DeleteAllItems();
// 		int nColumnCount = m_listDcmInfo.GetHeaderCtrl()->GetItemCount();
// 
// 		// Delete all of the columns.
// 		for (int i=0;i < nColumnCount; i++)
// 		{
// 		   m_listDcmInfo.DeleteColumn(0);
// 		}
// 
// 		// 取消排序
// 		m_listDcmInfo.ModifyStyle(LVS_SORTASCENDING, 0);
// 	//	m_listDcmInfo.SetExtendedStyle(m_listDcmInfo.GetExtendedStyle() | ~(LVS_SORTASCENDING | LVS_SORTDESCENDING));
// 
// 		m_listDcmInfo.InsertColumn(0, _T("Session"), LVCFMT_LEFT, 100);
// 		m_listDcmInfo.InsertColumn(1, _T("Attribute"), LVCFMT_LEFT, 200);
// 		m_listDcmInfo.InsertColumn(2, _T("Value"), LVCFMT_LEFT, 400);
// 		
// 
// 
// 		int iItenNum = 0;
// 		CString strInfo = _T("");
// 		COleDateTime odtDateTime;
// 
//  		m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  		m_listDcmInfo.SetItemText(iItenNum,1,_T("ImplementationClassUID"));
//  		m_listDcmInfo.SetItemText(iItenNum++,2,strImpClassUID);
// 		
// 		// Patient
// 		for (i = 0; i < pDcmDirPTI->vtrPatients.size(); i++)
// 		{
// 			strInfo.Format(_T("PATIENT : %d"), i+1);
//  			m_listDcmInfo.InsertItem(iItenNum, strInfo);
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T(""));
//  			m_listDcmInfo.SetItemText(iItenNum++,2,_T(""));
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientUID"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrPatients[i].strPatientUID);
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientName"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrPatients[i].strPatientName);
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientID"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrPatients[i].strPatientID);
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyNum"));
// 			strInfo.Format(_T("%d"), pDcmDirPTI->vtrPatients[i].uStudyNum);
//  			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 
// 			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientSex"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrPatients[i].strPatientGender);
// 
// 			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientBirthDate"));
//  			odtDateTime = pDcmDirPTI->vtrPatients[i].dtBirthDate;
// 			strInfo = odtDateTime.Format(_T("%Y-%m-%d"));
// 			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 		}
// 
// 
// 		// Study
// 		for (i = 0; i < pDcmDirPTI->vtrStudies.size(); i++)
// 		{
//  			strInfo.Format(_T("STUDY : %d"), i+1);
// 			m_listDcmInfo.InsertItem(iItenNum, strInfo);
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T(""));
//  			m_listDcmInfo.SetItemText(iItenNum++,2,_T(""));
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyUID"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrStudies[i].strStudyUID);
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("PatientUID"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrStudies[i].strPatientUID);
// 
//   			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyID"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrStudies[i].strStudyID);
// 
// 			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyDateTime"));
//  			odtDateTime = pDcmDirPTI->vtrStudies[i].dtStudyDateTime;
// 			strInfo = odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
// 			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 
//   			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("RefPhisicianName"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrStudies[i].strRefPhisicianName);
// 
// 			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("SeriesNum"));
// 			strInfo.Format(_T("%d"), pDcmDirPTI->vtrStudies[i].uSeriesNum);
//  			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 
//   			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyDescription"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrStudies[i].strStudyDescription);
// 		}
// 
// 
// 		// Series
// 		for (i = 0; i < pDcmDirPTI->vtrSeries.size(); i++)
// 		{
//  			strInfo.Format(_T("SERIES : %d"), i+1);
//  			m_listDcmInfo.InsertItem(iItenNum, strInfo);
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T(""));
//  			m_listDcmInfo.SetItemText(iItenNum++,2,_T(""));
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("SeriesUID"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrSeries[i].strSeriesUID);
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("StudyUID"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrSeries[i].strStudyUID);
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("ImageNum"));
// 			strInfo.Format(_T("%d"), pDcmDirPTI->vtrSeries[i].uImageNum);
//  			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 
// 			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("SeriesDateTime"));
//  			odtDateTime = pDcmDirPTI->vtrSeries[i].dtSeriesDateTime;
// 			strInfo = odtDateTime.Format(_T("%Y-%m-%d %H:%M:%S"));
// 			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("SeriesType"));
// 			strInfo.Format(_T("%d"), pDcmDirPTI->vtrSeries[i].uSeriesType);
//  			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 
// 		}
// 
// 		// Images
// 		for (i = 0; i < pDcmDirPTI->vtrImages.size(); i++)
// 		{
//  			strInfo.Format(_T("IMAGE : %d"), i+1);
//  			m_listDcmInfo.InsertItem(iItenNum, strInfo);
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T(""));
//  			m_listDcmInfo.SetItemText(iItenNum++,2,_T(""));
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("SeriesUID"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrImages[i].strSeriesUID);
// 
// 			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("ReferencedFileID"));
//  			m_listDcmInfo.SetItemText(iItenNum++,2, pDcmDirPTI->vtrImages[i].strReferencedFileID);
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("Rows"));
// 			strInfo.Format(_T("%d"), pDcmDirPTI->vtrImages[i].uRows);
//  			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 		
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("Columns"));
// 			strInfo.Format(_T("%d"), pDcmDirPTI->vtrImages[i].uColumns);
//  			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 
// 			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("FrameNum"));
// 			strInfo.Format(_T("%d"), pDcmDirPTI->vtrImages[i].uFrameNum);
//  			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 
//  			m_listDcmInfo.InsertItem(iItenNum, _T(""));
//  			m_listDcmInfo.SetItemText(iItenNum,1,_T("bPostProcessed"));
// 			strInfo.Format(_T("%d"), pDcmDirPTI->vtrImages[i].bPostProcessed);
//  			m_listDcmInfo.SetItemText(iItenNum++,2, strInfo);
// 		}
// 
// 	}
	
}

void CDcmReadDlg::OnChangeEditSearch() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

BOOL CDcmReadDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}




DWORD WINAPI DcmLoadThreadProc(LPVOID lpParam) 
{ 

	g_smDlg->m_pDcmReadDlg->LoadDcmProc((BOOL)lpParam);
	return 0;

}

void CDcmReadDlg::LoadDcmProc(BOOL bDcm)
{
// 	if (NULL != m_pNFileFormat)
// 	{
// 		delete m_pNFileFormat;
// 		m_pNFileFormat = NULL;
// 	}
// 
// 	if (NULL != m_pNDcmDir)
// 	{
// 		delete m_pNDcmDir;
// 		m_pNDcmDir = NULL;
// 	}
 	g_smDlg->AppendString(_T("Enter thread!"));

// 	if (bDcm)
// 	{
// 
// 		TCHAR strFilePath[MAX_PATH] = {_T("G:\\000007_20080314\\B004_005")};
// 	
// 		CDcmParser* pNFileFormat = new CDcmParser;
// 		BOOL bRet = pNFileFormat->LoadMFDcmFile(strFilePath);
// 		if (!bRet)
// 		{
// 			g_smDlg->AppendString(_T("Load dcm failed!"));
// 		}
// 		else
// 		{
// 			g_smDlg->AppendString(_T("Load dcm OK!"));
// 		}
// 	}
// 	else
// 	{
// 		TCHAR szMBDirFile[MAX_PATH] = {_T("G:\\DICOMDIR")};
// // 		TCHAR szMBDirFile[MAX_PATH] = {_T("E:\\DcmCache\\Burn\\Work\\DICOMDIR")};
// 
// 		m_pNDcmDir = new CDcmDirParser;
// 		BOOL bRet = m_pNDcmDir->LoadDcmDir(szMBDirFile);
// 		if (!bRet)
// 		{
// 			AfxMessageBox(_T("Load dcmdir failed!"));
// 		}
// 		else
// 		{
// 			AfxMessageBox(_T("Load dcmdir OK!"));
// 		}
// 	}


//  	TCHAR strFilePath[MAX_PATH] = {_T("G:\\000007_20080314\\B004_005")};
// 	HANDLE h = ::CreateFile(strFilePath,           // open MYFILE.TXT 
// 					GENERIC_READ,              // open for reading 
// 					FILE_SHARE_READ,           // share for reading 
// 					NULL,                      // no security 
// 					OPEN_ALWAYS,             // existing file only 
// 					FILE_ATTRIBUTE_NORMAL,     // normal file 
// 					NULL);                     // no attr. template 
// 
// 	if (INVALID_HANDLE_VALUE != h)
// 	{
//  		g_smDlg->AppendString(_T("Open OK!"));
// 		CloseHandle(h);
// 		h = INVALID_HANDLE_VALUE;
// 	}
// 	else
// 	{
//  		g_smDlg->AppendString(_T("Open Failed!"));
// 	}

	char strFilePath[MAX_PATH] = {("G:\\DICOMDIR")};
	FILE* pfile = fopen(strFilePath, "rb");

	if (NULL != pfile)
	{
 		g_smDlg->AppendString(_T("Open OK!"));
		fclose(pfile); ;
	}
	else
	{
 		g_smDlg->AppendString(_T("Open Failed!"));
	}


 	g_smDlg->AppendString(_T("Leave thread!"));

}

void CDcmReadDlg::OnButtonLDcm() 
{
	// TODO: Add your control notification handler code here
	if (NULL != hThreadLoadDcm)
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(hThreadLoadDcm, 0))
		{
			if (!TerminateThread(hThreadLoadDcm, 0))
			{
			}
		}

		CloseHandle(hThreadLoadDcm);
		hThreadLoadDcm = NULL;
	}
	hThreadLoadDcm = CreateThread(NULL, 0, DcmLoadThreadProc, (void*)TRUE, 0, NULL);
// 	if (NULL != hThreadLoadDcm)
// 	{
// 		CloseHandle(hThreadLoadDcm);
// 	}


// 	HANDLE hThread = CreateThread(NULL, 0, DcmLoadThreadProc, (void*)TRUE, 0, NULL);
// 	if (NULL != hThread)
// 	{
// 		CloseHandle(hThread);
// 	}
}

void CDcmReadDlg::OnButtonLDcmdir() 
{
	// TODO: Add your control notification handler code here
// 	if (NULL != hThreadLoadDcm)
// 	{
// 		if (WAIT_TIMEOUT == WaitForSingleObject(hThreadLoadDcm, 0))
// 		{
// 			if (!TerminateThread(hThreadLoadDcm, 0))
// 			{
// 			}
// 		}
// 
// 		CloseHandle(hThreadLoadDcm);
// 		hThreadLoadDcm = NULL;
// 	}

	HANDLE hThread = CreateThread(NULL, 0, DcmLoadThreadProc, (void*)FALSE, 0, NULL);
	if (NULL != hThread)
	{
		CloseHandle(hThread);
	}
}

void CDcmReadDlg::OnButtonCancelL() 
{
	// TODO: Add your control notification handler code here
	if (NULL != hThreadLoadDcm)
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(hThreadLoadDcm, 0))
		{
			if (!TerminateThread(hThreadLoadDcm, 0))
			{
			}
		}

		CloseHandle(hThreadLoadDcm);
		hThreadLoadDcm = NULL;
	}
}

void CDcmReadDlg::OnButtonDcmModify() 
{
	// TODO: Add your control notification handler code here
	DWORD dwStart = GetTickCount();
	CDcmModify aDcmModify;
	PatientInfoStruct pis;
	aDcmModify.ModifyDcm(_T("E:\\DcmCache\\Burn\\Work\\P0000001\\DICOM\\STUDY30000\\SERIES01\\P0000002"), &pis);

	CString str;
	str.Format(_T("%d"), GetTickCount()-dwStart);
	AfxMessageBox(str);
}

void CDcmReadDlg::OnButtonGenDcmdir() 
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

		//已获得文件夹路径，生成DICOMDIR

		
		CDcmDirGen DcmDirGen;
		if (DcmDirGen.CreateDicomDirFile(strDir))
		{
			AfxMessageBox(_T("OK"));
		}
		else
		{
			AfxMessageBox(_T("Failed"));
		}
	}

}
