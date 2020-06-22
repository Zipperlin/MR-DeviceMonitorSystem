#if !defined(AFX_DCMREADDLG_H__96AE213F_0640_4D77_AD8C_B8A8DD37A1E3__INCLUDED_)
#define AFX_DCMREADDLG_H__96AE213F_0640_4D77_AD8C_B8A8DD37A1E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DcmReadDlg.h : header file

#include "DcmGen.h"
#include "DcmDirParser.h"
#include "DcmParser.h"
//#include "ReportCtrl.h"
//

/////////////////////////////////////////////////////////////////////////////
// CDcmReadDlg dialog

class CDcmReadDlg : public CDialog
{
// Construction
public:
	CDcmReadDlg(CWnd* pParent = NULL);   // standard constructor


	void AddMsg(LPCTSTR szTagNum, LPCTSTR szTagName, LPCTSTR szTagValue);

	
	CReportCtrl m_listDcmInfo;



	//////////// dcm(dir) load test
	void LoadDcmProc(BOOL bDcm);
	CDcmDirParser* m_pNDcmDir;
	CDcmParser* m_pNFileFormat;
	HANDLE hThreadLoadDcm;

// Dialog Data
	//{{AFX_DATA(CDcmReadDlg)
	enum { IDD = IDD_FORMVIEW_DCM_READ };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDcmReadDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	void LoadDcmFile(LPCTSTR szDcmFile);

	CDcmGen m_R2D;
	CDcmParser m_DcmParser;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDcmReadDlg)
	afx_msg void OnButtonLoadDcmImage();
	afx_msg void OnButtonSaveRawImage();
	afx_msg void OnButtonViewTag();
	afx_msg void OnButtonViewPatientInfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnButtonSearch();
	afx_msg void OnButtonLoadDcmdir();
	afx_msg void OnChangeEditSearch();
	afx_msg void OnButtonLDcm();
	afx_msg void OnButtonLDcmdir();
	afx_msg void OnButtonCancelL();
	afx_msg void OnButtonDcmModify();
	afx_msg void OnButtonGenDcmdir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DCMREADDLG_H__96AE213F_0640_4D77_AD8C_B8A8DD37A1E3__INCLUDED_)
