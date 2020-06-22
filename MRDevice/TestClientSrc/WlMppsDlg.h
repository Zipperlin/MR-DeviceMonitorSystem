#if !defined(AFX_WLMPPSDLG_H__205A7D47_0104_4613_8834_04670129AB24__INCLUDED_)
#define AFX_WLMPPSDLG_H__205A7D47_0104_4613_8834_04670129AB24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WlMppsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWlMppsDlg dialog

class CWlMppsDlg : public CDialog
{
// Construction
public:
	CWlMppsDlg(CWnd* pParent = NULL);   // standard constructor
	void UpdateWorkList(long lItemNum, WorkListStruct* pWorkList);

	void UpdatePatientStudyList(WLPatientStudyStruct* pStruct);
	void UpdatePatientStudyList(WLPatientStudyStatusInDB* pStruct);

// Dialog Data
	//{{AFX_DATA(CWlMppsDlg)
	enum { IDD = IDD_FORMVIEW_WLMPPS };
	CListCtrl	m_listPatientStudy;
	CListCtrl	m_listWorkList;
	int			m_radioMppsStatus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWlMppsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWlMppsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGetWorklist();
	afx_msg void OnButtonRefresh();
	afx_msg void OnButtonGetPsstruct();
	afx_msg void OnButtonIsimported();
	afx_msg void OnButtonSetMpps();
	afx_msg void OnButtonSetMppsTest();
	afx_msg void OnButtonIsSetEnable();
	afx_msg void OnButtonIswlworking();
	afx_msg void OnButtonIsmppsworking();
	afx_msg void OnButtonIsClosingStudyMpps();
	afx_msg void OnButtonIsmppsvalid();
	afx_msg void OnButtonIsClosingPatientOrStudyMpps();
	afx_msg void OnButtonIsSettingPOrSMppsUidAdd();
	afx_msg void OnButtonIsSettingPOrSMppsUidClear();
	afx_msg void OnButtonStudyImported();
	afx_msg void OnButtonIsStudyinstuidExist();
	afx_msg void OnButtonDeleteAllStudyinstuid();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WLMPPSDLG_H__205A7D47_0104_4613_8834_04670129AB24__INCLUDED_)
