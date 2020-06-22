#if !defined(AFX_BURNPATIENTINFO_H__6D940778_7AE7_4874_99EA_4DB5C21948BB__INCLUDED_)
#define AFX_BURNPATIENTINFO_H__6D940778_7AE7_4874_99EA_4DB5C21948BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BurnPatientInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBurnPatientInfo dialog

class CBurnPatientInfo : public CDialog
{
// Construction
public:
	CBurnPatientInfo(CWnd* pParent = NULL);   // standard constructor

	void Init();
	void SetPatientInfo(long lItemNum, BurnPatientInfoStruct* pBurnPatientList);
	void SetStudyInfo(long lItemNum, BurnStudyInfoStruct* pBurnStudyList);
	void SetSeriesInfo(long lItemNum, BurnSeriesInfoStruct* pBurnSeriesList);
	void SetImageInfo(long lItemNum, BurnImageInfoStruct* pBurnImageList);

// Dialog Data
	//{{AFX_DATA(CBurnPatientInfo)
	enum { IDD = IDD_DIALOG_BURN_INFO };
	CListCtrl	m_listBurnInfo;
	CButton	m_BurnUIDType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBurnPatientInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CString DATEToDateStr(DATE& dt);
	CString DATEToDateTimeStr(DATE& dt);

	// Generated message map functions
	//{{AFX_MSG(CBurnPatientInfo)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BURNPATIENTINFO_H__6D940778_7AE7_4874_99EA_4DB5C21948BB__INCLUDED_)
