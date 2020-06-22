#if !defined(AFX_CONFIGDLG_H__4A3B0848_BC63_4202_BDD9_0FD3F5FA6577__INCLUDED_)
#define AFX_CONFIGDLG_H__4A3B0848_BC63_4202_BDD9_0FD3F5FA6577__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_FORMVIEW_CONFIG };
	CListCtrl	m_listAutoServer;
	int		m_radioServerType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InitServerList(int iType);

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonConifgAutoAdd();
	afx_msg void OnButtonConifgAutoModify();
	afx_msg void OnButtonConifgAutoDelete();
	afx_msg void OnButtonConifgAutoClear();
	afx_msg void OnButtonConifgAutoSave();
	afx_msg void OnButtonConifgAutoRefresh();
	afx_msg void OnButtonConifgAutoTest();
	afx_msg void OnItemchangingListConfigSendAuto(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListConfigSendAuto(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioConfigAutoSend();
	afx_msg void OnRadioConfigManualSend();
	afx_msg void OnRadioConfigWl();
	afx_msg void OnRadioConfigMpps();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__4A3B0848_BC63_4202_BDD9_0FD3F5FA6577__INCLUDED_)
