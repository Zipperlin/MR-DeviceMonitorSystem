#if !defined(AFX_SENDJOBDETAILDLG_H__715B4B1C_807B_4376_A2DE_4BDBD565B7D4__INCLUDED_)
#define AFX_SENDJOBDETAILDLG_H__715B4B1C_807B_4376_A2DE_4BDBD565B7D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendJobDetailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendJobDetailDlg dialog

class CSendJobDetailDlg : public CDialog
{
// Construction
public:
	CSendJobDetailDlg(CWnd* pParent = NULL);   // standard constructor
	
	void SetJobMode(JobMode enumJobMode);
	void SetJob(LPCTSTR szJobID);
	LPCTSTR GetJob();

	void GetJobInfo();
	void UpdateJobInfo(	JobInfo& aJobInfo,
						PSSIInfo* pPSSIInfo,
						long lPSSILen,
						NetworkNode* pNode,
						long lNodeLen,
						JobDetailStruct* pDetail,
						long lDetailLen);

	void UpdateState(BSTR bsJobID, BSTR bsState);
	void UpdateProgress(BSTR bsJobID, BSTR bsProgress);
	void UpdatePhase(BSTR bsJobID, BSTR bsPhase);
	void UpdateDetail(JobDetailStruct* pDetail);

	BOOL IsThisJob(BSTR bsJobID);
	BOOL IsShow();
// Dialog Data
	//{{AFX_DATA(CSendJobDetailDlg)
	enum { IDD = IDD_FORMVIEW_SEND_JOB_DETAIL };
	CListCtrl	m_listDetail;
	CListCtrl	m_listNodes;
	CListCtrl	m_listPSSI;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendJobDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:

	CString			m_strJobID;
	JobMode			m_enumJobMode;
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendJobDetailDlg)
	afx_msg void OnButtonSendJobDetailClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDJOBDETAILDLG_H__715B4B1C_807B_4376_A2DE_4BDBD565B7D4__INCLUDED_)
