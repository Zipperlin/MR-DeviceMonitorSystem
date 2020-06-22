#if !defined(AFX_SERVERDLG_H__D33D90F9_0C2A_4DF1_B69D_554CA1FC52CE__INCLUDED_)
#define AFX_SERVERDLG_H__D33D90F9_0C2A_4DF1_B69D_554CA1FC52CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

class CServerDlg : public CDialog
{
// Construction
public:
	CServerDlg(CWnd* pParent = NULL);   // standard constructor
	void SetType(int iType);

	CString				m_strServerAE;
	CString				m_strServerIP;
	CString				m_strServerPort;
	CString				m_strHostAE;
	BOOL				m_bRaw;
	BOOL				m_bProcessed;

	int					m_iType;

// Dialog Data
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_FORMVIEW_SERVER };
	CButton	m_ckProcessed;
	CButton	m_ckRaw;
	CIPAddressCtrl	m_ServerIP;
	CEdit	m_ServerPort;
	CEdit	m_HostAE;
	CEdit	m_ServerAE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonServerOk();
	afx_msg void OnButtonServerCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDLG_H__D33D90F9_0C2A_4DF1_B69D_554CA1FC52CE__INCLUDED_)
