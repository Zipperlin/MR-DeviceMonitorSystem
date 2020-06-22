#if !defined(AFX_PRINTDLG_H__B80EA452_CAAF_43DE_AF72_99E0EAD30711__INCLUDED_)
#define AFX_PRINTDLG_H__B80EA452_CAAF_43DE_AF72_99E0EAD30711__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrintDlg.h : header file
//
#include "..\\src\\PALib_i.h"
#include "TestClientSrcDlg.h"
//#include "Winsock2.h"

class CTestClientSrcDlg;
// #include "Hook.h"


/////////////////////////////////////////////////////////////////////////////
// CPrintDlg dialog


class CPrintDlg : public CDialog
{
// Construction
public:
	void Init();
	CPrintDlg(CWnd* pParent = NULL);   // standard constructor

	vector<CString> m_vtrNetwork;
	CString m_CurSvr;
	int m_iCurNode;
// 	CHook m_hook;


	void UpdateJobList();
	void SetJobState(LPCTSTR szJobID, JobState enumJobState);
	void SetJobPhase(LPCTSTR szJobID, LPCTSTR szJobPhase);
	void SetJobProgress(JobProgressStruct* pJobProgressStruct);
	void SetJobDetail(JobDetailStruct* pJobDetailStruct);
	void SetExecutingJobPhaseProgress(LPCTSTR szPhase, LPCTSTR szProgress);

	BOOL RecvFilmComposerSocketMsg();
// Dialog Data
	//{{AFX_DATA(CPrintDlg)
	enum { IDD = IDD_FORMVIEW_PRINT };
	CListCtrl	m_CListJobList;
	CComboBox	m_cbSvrList;
	int		m_ImageType;
	int		m_iFileSelection;
	int		m_iImageSelection;
	SOCKET m_socketFCServer;
	HANDLE m_hCheckFCStatusThread;
	SOCKET m_socketFCMonitorServer;
	SOCKET m_socketFCMonitorClient;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintDlg)
	afx_msg void OnButtonSetimagetype();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonCancelprint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboNetworknode();
	afx_msg void OnButtonView();
	afx_msg void OnButtonDeleteJob();
	afx_msg void OnDestroy();
	afx_msg void OnButtonShowFc();
	afx_msg void OnButtonHideFc();
	afx_msg void OnButtonFcloadimg();
	afx_msg void OnButtonFcpath();
	afx_msg void OnButtonStartfc();
	afx_msg void OnButtonStarthook();
	afx_msg void OnButtonPssOccupyState();
	afx_msg void OnButtonCancelFcPrint();
	afx_msg void OnButtonSocketCnct();
	afx_msg void OnButtonSocketSvr();
	afx_msg void OnButtonCloseSocketSvr();
	afx_msg void OnButtonSocketDiscnct2();
	afx_msg void OnButtonHideprogress();
	afx_msg void OnButtonShowprogress();
	afx_msg void OnButtonLoadInDir();
	afx_msg void OnButtonPrintUidAdd();
	afx_msg void OnButtonPrintUidDel();
	afx_msg void OnButtonPrintUidClear();
	afx_msg void OnButtonGetPrintSubmoduleState();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTDLG_H__B80EA452_CAAF_43DE_AF72_99E0EAD30711__INCLUDED_)
