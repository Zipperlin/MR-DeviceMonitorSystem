#if !defined(AFX_PATIENTADMINDLG_H__85DF580A_3881_4D63_BAB6_4CDA8D7869FD__INCLUDED_)
#define AFX_PATIENTADMINDLG_H__85DF580A_3881_4D63_BAB6_4CDA8D7869FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PatientAdminDlg.h : header file
//

#include "PATestClientLibExt_i.h"
#include "SeriesImagesDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CPatientAdminDlg dialog

class CPatientAdminDlg : public CDialog
{
// Construction
public:
	CPatientAdminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPatientAdminDlg();

	void GetPatientsInfo();
	void GetStudysInfo(LPCTSTR szPatientUID);
	void GetSeriesInfo(LPCTSTR szStudyUID);
	void GetImageInfo(LPCTSTR szSeriesUID);


// Dialog Data
	//{{AFX_DATA(CPatientAdminDlg)
	enum { IDD = IDD_FORMVIEW_PATIENTADMIN };
	CReportCtrl		m_lstImages;
	CReportCtrl		m_lstSeries;
	CReportCtrl		m_lstStudies;
	CReportCtrl		m_lstPatients;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatientAdminDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void ReleaseInterface();

	void GetCurrentUID();
	void GetFlaggedImageNum();


	IDBPIM*					m_pIDBPIM;
	IDBConfig*				m_pIDBConfig;
	IDBSession*				m_pIDBSession;
	IGeneralSys*			m_pIDBGeneral;
	IGeneralSys*			m_pIISGeneral;

	CSeriesImagesDlg		m_SeriesImagesDlg;
	
protected:

	// Generated message map functions
	//{{AFX_MSG(CPatientAdminDlg)
	afx_msg void OnButtonInit();
	afx_msg void OnButtonUninit();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListPatient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListStudy(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListSeries(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonUpdatePatients();
	afx_msg void OnButtonSetCrtPatient();
	afx_msg void OnButtonSetCrtStudy();
	afx_msg void OnButtonSetCrtSeries();
	afx_msg void OnButtonFlagImage();
	afx_msg void OnButtonUnflagImage();
	afx_msg void OnButtonFlagAllImage();
	afx_msg void OnButtonUnflagAllImage();
	afx_msg void OnButtonClearFlag();
	afx_msg void OnButtonCurrentUid();
	afx_msg void OnButtonFlaggedImageNum();
	afx_msg void OnButtonCopyUid();
	afx_msg void OnHOVERListPatient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDeleteFromDb();
	afx_msg void OnButtonViewImage();
	afx_msg void OnClickListImage(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATIENTADMINDLG_H__85DF580A_3881_4D63_BAB6_4CDA8D7869FD__INCLUDED_)
