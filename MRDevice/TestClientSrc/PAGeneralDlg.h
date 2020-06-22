#if !defined(AFX_PAGENERALDLG_H__35185EFA_9A09_475E_96D4_5F5F28B346AA__INCLUDED_)
#define AFX_PAGENERALDLG_H__35185EFA_9A09_475E_96D4_5F5F28B346AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PAGeneralDlg.h : header file
//

#include "TestClientSrcDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CPAGeneralDlg dialog

class CPAGeneralDlg : public CDialog
{
// Construction
public:
	CPAGeneralDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPAGeneralDlg)
	enum { IDD = IDD_FORMVIEW_PAGENERAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPAGeneralDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPAGeneralDlg)
	afx_msg void OnButtonSendUg();
	afx_msg void OnButtonUidOccupied();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPageneralPing();
	afx_msg void OnButtonCompactDb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGENERALDLG_H__35185EFA_9A09_475E_96D4_5F5F28B346AA__INCLUDED_)
