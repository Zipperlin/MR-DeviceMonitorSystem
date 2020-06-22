#if !defined(AFX_BURNJOBDETAILDLG_H__D46981B0_729D_4709_8CF8_344ABE70C506__INCLUDED_)
#define AFX_BURNJOBDETAILDLG_H__D46981B0_729D_4709_8CF8_344ABE70C506__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BurnJobDetailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBurnJobDetailDlg dialog

class CBurnJobDetailDlg : public CDialog
{
// Construction
public:
	CBurnJobDetailDlg(CWnd* pParent = NULL);   // standard constructor

	void SetJobMode(JobMode enumJobMode);
	void SetJob(LPCTSTR szJobID);
	LPCTSTR GetJob();
	
	void GetJobInfo();
	void UpdateJobInfo(	JobInfo& aJobInfo,
						PSSIInfo* pPSSIInfo,
						long lPSSILen,
						JobDetailStruct* pDetail,
						long lDetailLen);

	void UpdateState(BSTR bsJobID, BSTR bsState);
	void UpdateProgress(BSTR bsJobID, BSTR bsProgress);
	void UpdatePhase(BSTR bsJobID, BSTR bsPhase);
	void UpdateDetail(JobDetailStruct* pDetail);

	BOOL IsThisJob(BSTR bsJobID);
	BOOL IsShow();

// Dialog Data
	//{{AFX_DATA(CBurnJobDetailDlg)
	enum { IDD = IDD_FORMVIEW_BURN_JOB_DETAIL };
	CListCtrl	m_listDetail;
	CListCtrl	m_listPSSI;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBurnJobDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:

	CString			m_strJobID;
	JobMode			m_enumJobMode;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBurnJobDetailDlg)
	afx_msg void OnButtonBurnJobDetailClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BURNJOBDETAILDLG_H__D46981B0_729D_4709_8CF8_344ABE70C506__INCLUDED_)
