// TestClientSrcDlg.h : header file
//

#if !defined(AFX_TESTCLIENTSRCDLG_H__BB63D905_EA3C_447A_B25D_3B948CF7746F__INCLUDED_)
#define AFX_TESTCLIENTSRCDLG_H__BB63D905_EA3C_447A_B25D_3B948CF7746F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "PASink.h"
#include "..\\src\\PALib_i.h"
#include "BurnDlg.h"
#include "TransferDlg.h"
#include "PrintDlg.h"
#include "PAGeneralDlg.h"
#include "DcmReadDlg.h"
#include "ImportDlg.h"
#include "WlMppsDlg.h"
#include "PatientAdminDlg.h"
#include "ConfigDlg.h"
#include "ImportJobDetailDlg.h"
#include "SendJobDetailDlg.h"
#include "BurnJobDetailDlg.h"


class CBurnDlg;
class CPrintDlg;
class CTransferDlg;
class CImportDlg;
class CPAGeneralDlg;
class CConfigDlg;


#define WM_MY_TRAY_NOTIFICATION WM_USER+1

typedef struct _JobItemInfo
{
	CString strJobID;
	JobType enumJobType;
}JobItemInfo;



/////////////////////////////////////////////////////////////////////////////
// CTestClientSrcDlg dialog

class CTestClientSrcDlg : public CDialog
{
// Construction
public:
	CTestClientSrcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestClientSrcDlg)
	enum { IDD = IDD_TESTCLIENTSRC_DIALOG };
	CListCtrl	m_listJobQueue;
	CEdit	m_Edit;
	CStatic	m_workStatus;
	int		m_RatioImageType;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestClientSrcDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HICON m_hIconTop;
	HICON m_hIconExitAndShutDownPA;
	HICON m_hIconExitAndUnShutDownPA;
	HICON m_hIconDesktop;
	HICON m_hIconPAReg;

	CToolBar m_wndToolBar;

public:
	void AppendString(CString strMsg);
	void InitChildDlg();

	void UpdateJobQueue();
	void UpdateJobState(BSTR bsJobID, BSTR bsState);
	void UpdateJobPhase(BSTR bsJobID, BSTR bsPhase);
	void UpdateJobProgress(BSTR bsJobID, BSTR bsProgress);
	void UpdateJobDetail(JobDetailStruct* pJobDetail);

	void ClearJobQueue();

	void UpdatePages(DWORD dwJobCount, DWORD dwJobCountPerPage);

    static IGeneralSys* m_pIGeneral; 
    static IPing* m_pIPing; 
    static IPAPrint* m_pIPAPrint;
	static IPABurn* m_pIPABurn;
	static IPATransfer* m_pIPATransfer;
	static IPADiscImport* m_pIPADiscImport;
	static IPAWLMPPS* m_pIPAWlMpps;
	static IPAGeneral* m_pIPAGeneral;
	static IGeneralInterface* m_pIGenaralInterface;

	CPASink m_PAGeneralEventSink;
	CPASink m_PASinkPrint;
	CPASink m_PASinkBurn;
	CPASink m_PASinkTransfer;
	CPASink m_PASinkDiscImport;
	CPASink m_PASinkWlMpps;
	CPASink m_IGeneralEventSink;
	CPASink m_IUserGuidanceEventSink;

// 	DICOMImageType m_ImageType;
	STARTUPRESULT m_PAStartUpResult;
	STARTUPRESULT* m_pPAStartUpResult;

	CPatientAdminDlg*	m_pPADlg;

	CPAGeneralDlg*	m_pPAGeneralDlg;
	CBurnDlg*		m_pBurnDlg;
	CPrintDlg*		m_pPrintDlg;
	CTransferDlg*	m_pTransferDlg;
	CImportDlg*		m_pImportDlg;
	CWlMppsDlg*		m_pWlMppsDlg;
	CDcmReadDlg*	m_pDcmReadDlg;
	CConfigDlg*		m_pConfigDlg;
	
 	CImportJobDetailDlg		m_ImportJObDetailDlg;
	CSendJobDetailDlg		m_SendJObDetailDlg;
	CBurnJobDetailDlg		m_BurnJObDetailDlg;

	NOTIFYICONDATA	m_nid;

	JobMode			m_enumJobMode;

private:
	vector<CString>		m_vtrSelectedJobs;

	// Generated message map functions
	//{{AFX_MSG(CTestClientSrcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPrint();
	afx_msg void OnStartup();
	afx_msg void OnShutdown();
	afx_msg void OnCancelprint();
	afx_msg void OnBeep();
	virtual void OnOK();
	afx_msg void OnRadioXa();
	afx_msg void OnRadioSc();
	afx_msg void OnCntpasink();
	afx_msg void OnDiscntpasink();
	afx_msg void OnButtonBurn();
	afx_msg void OnRadioPrint();
	afx_msg void OnRadioTransfer();
	afx_msg void OnRadioBurner();
	afx_msg void OnButtonHideFc();
	afx_msg void OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized );
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonClear();
	afx_msg void OnClose();
	afx_msg void OnRadioDcmRead();
	afx_msg void OnButtonImport();
	afx_msg void OnButtonTopmost();
	afx_msg void OnButtonShowDesktop();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnArea();
	afx_msg void OnRadioPageneral();
	afx_msg void OnButtonExit();
	afx_msg LRESULT OnTrayNotification(WPARAM wp, LPARAM lp);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonWlmpps();
	afx_msg void OnRadioPatientadmin();
	afx_msg void OnButtonGenRegFile();
	afx_msg void OnButtonConfig();
	afx_msg void OnButtonMoveJobUp();
	afx_msg void OnButtonMoveJobDown();
	afx_msg void OnButtonCancelJob();
	afx_msg void OnButtonDeleteJob();
	afx_msg void OnButtonRefreshJob();
	afx_msg void OnDblclkListJobQueue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonHistoryjobCount();
	afx_msg void OnButtonHistoryjobGetJob();
	afx_msg void OnButtonHistoryjobGetJob2();
	afx_msg void OnButtonHistoryjobGetJob3();
	afx_msg void OnPing();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCLIENTSRCDLG_H__BB63D905_EA3C_447A_B25D_3B948CF7746F__INCLUDED_)
