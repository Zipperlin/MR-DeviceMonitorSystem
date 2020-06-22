#if !defined(AFX_IMPORTDLG_H__4ED5DDD0_60FB_4CFA_B254_E1677B5B2932__INCLUDED_)
#define AFX_IMPORTDLG_H__4ED5DDD0_60FB_4CFA_B254_E1677B5B2932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportDlg.h : header file
//

#include "DiscImportDlg.h"
#include "TestClientSrcDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CImportDlg dialog

class CImportDlg : public CDialog
{
// Construction
public:
	CImportDlg(CWnd* pParent = NULL);   // standard constructor
	void UpDateImportDiscInfo(BOOL bReady);
	void UpDateImportDiscInfoState(LPCTSTR szState);

	void UpdateJobList();
	void UpdateJobInfo(LPCTSTR szJobID);
	
	void SetJobState(LPCTSTR szJobID, JobState enumJobState);
	void SetJobPhase(LPCTSTR szJobID, LPCTSTR szJobPhase);
	void SetJobProgress(JobProgressStruct* pJobProgressStruct);
	void SetJobDetail(JobDetailStruct* pJobDetailStruct);

	void ImportedSeriesStateChanged(DiscImport_SeriesStateStruct* pState);
	void ImportedSeriesProgressChanged(DiscImport_SeriesProgressStruct* pProgress);
	void ImportedSeriesDetailChanged(DiscImport_SeriesDetailStruct* pDetail);

	CDiscImportDlg* m_pDiscImportDlg;

// Dialog Data
	//{{AFX_DATA(CImportDlg)
	enum { IDD = IDD_FORMVIEW_IMPORT };
	CListCtrl	m_CListJobList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDiscImport();
	afx_msg void OnButtonDiViewjobinfo();
	afx_msg void OnButtonDiDeletejob();
	afx_msg void OnButtonDiCanceljob();
	afx_msg void OnDblclkListJobList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDiscImportUnfinishedjob();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:

	BOOL m_bViewJobQueue;
	CString m_strViewedJobID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTDLG_H__4ED5DDD0_60FB_4CFA_B254_E1677B5B2932__INCLUDED_)
