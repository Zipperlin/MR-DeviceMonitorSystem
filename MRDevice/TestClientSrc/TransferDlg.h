#if !defined(AFX_TRANSFERDLG_H__49E292B1_1968_4AA1_9F40_AAE550AB1232__INCLUDED_)
#define AFX_TRANSFERDLG_H__49E292B1_1968_4AA1_9F40_AAE550AB1232__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransferDlg.h : header file
//
#include "TestClientSrcDlg.h"
#include <vector>
using namespace std;

typedef struct _tagLocalNetworkNode
{
	BOOL bDefault;
	CString strCalledAE;
	CString strIP;
	CString strPort;
	CString strCallingAE;
	BOOL bRaw;
	BOOL bProcessed;
}LocalNetworkNode;

/////////////////////////////////////////////////////////////////////////////
// CTransferDlg dialog

class CTransferDlg : public CDialog
{
// Construction
public:
	void Init();
	CTransferDlg(CWnd* pParent = NULL);   // standard constructor

	vector<LocalNetworkNode> m_vtrServers;
	void UpdateJobList();
	void SetJobState(LPCTSTR szJobID, JobState enumJobState);
	void SetJobPhase(LPCTSTR szJobID, LPCTSTR szJobPhase);
	void SetJobProgress(JobProgressStruct* pJobProgressStruct);
	void SetJobDetail(JobDetailStruct* pJobDetailStruct);
	void SetExecutingJobPhaseProgress(LPCTSTR szPhase, LPCTSTR szProgress);
// Dialog Data
	//{{AFX_DATA(CTransferDlg)
	enum { IDD = IDD_FORMVIEW_TRANSFER };
	CListCtrl	m_listManualSendSvrs;
	CListCtrl	m_CListJobList;
	CEdit	m_SvrPort;
	CEdit	m_SvrIP;
	CEdit	m_SvrAE;
	CEdit	m_HostAE;
	CComboBox	m_cbServerList;
	CString m_CurSvr;
	int m_CurSvrNum;
	int		m_iFileSelection;
	int		m_iImageSelection;
	int		m_iDownscale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransferDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransferDlg)
	afx_msg void OnButtonTransfer();
	afx_msg void OnSelchangeComboSvrlist();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCancelJob();
	afx_msg void OnButtonDeletJob();
	afx_msg void OnButtonTransferbyuid();
	afx_msg void OnSelchangeComboUidSelection();
	afx_msg void OnButtonTransferTransferValid();
	afx_msg void OnButtonTransferAutosend();
	afx_msg void OnButtonTransferRefreshNetworknodes();
	afx_msg void OnButtonSendUidAdd();
	afx_msg void OnButtonSendUidDel();
	afx_msg void OnButtonSendUidClear();
	afx_msg void OnClickListManualSendServer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckSendSvrRaw();
	afx_msg void OnCheckSendSvrPro();
	afx_msg void OnButtonTransferbyuidMultiSvrs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFERDLG_H__49E292B1_1968_4AA1_9F40_AAE550AB1232__INCLUDED_)
