#if !defined(AFX_IMPORTJOBDETAILDLG_H__DE45FEBF_2404_4A9E_985B_0CE3413D22E6__INCLUDED_)
#define AFX_IMPORTJOBDETAILDLG_H__DE45FEBF_2404_4A9E_985B_0CE3413D22E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportJobDetailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportJobDetailDlg dialog

class CImportJobDetailDlg : public CDialog
{
// Construction
public:
	CImportJobDetailDlg(CWnd* pParent = NULL);   // standard constructor

	void SetJobMode(JobMode enumJobMode);
	void SetJob(LPCTSTR szJobID);
	LPCTSTR GetJob();

	void RefreshList();
	void UpdateJobInfo(	DiscImport_SeriesStruct* pImagesList,
						long lLen);

	void UpdateImageState(DiscImport_SeriesStateStruct* pState);
	void UpdateImageProgress(DiscImport_SeriesProgressStruct* pProgress);
	void UpdateImageDetail(DiscImport_SeriesDetailStruct* pDetail);

	BOOL IsThisJob(BSTR bsJobID);
	BOOL IsShow();

// Dialog Data
	//{{AFX_DATA(CImportJobDetailDlg)
	enum { IDD = IDD_FORMVIEW_IMPORT_JOB_DETAIL };
	CListCtrl	m_listImages;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportJobDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:

	CString			m_strJobID;
	JobMode			m_enumJobMode;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportJobDetailDlg)
	afx_msg void OnButtonImportJobDetailClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTJOBDETAILDLG_H__DE45FEBF_2404_4A9E_985B_0CE3413D22E6__INCLUDED_)
