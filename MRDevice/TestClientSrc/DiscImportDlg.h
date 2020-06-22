#if !defined(AFX_DISCIMPORTDLG_H__1BF06E85_EBDE_4940_B97A_A924A4C509C9__INCLUDED_)
#define AFX_DISCIMPORTDLG_H__1BF06E85_EBDE_4940_B97A_A924A4C509C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DiscImportDlg.h : header file
//


#include "DiscImportStructDef.h"
#include "vector"
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CDiscImportDlg dialog

class CDiscImportDlg : public CDialog
{
// Construction
public:
	CDiscImportDlg(CWnd* pParent = NULL);   // standard constructor
	~CDiscImportDlg();
	void UpDateImportDiscInfo(BOOL bReady);
	void UpDateImportDiscInfoState(LPCTSTR szState);

// 	void ImportedSeriesStateChanged(DiscImport_SeriesStateStruct* pState);
// 	void ImportedSeriesProgressChanged(DiscImport_SeriesProgressStruct* pProgress);
// 	void ImportedSeriesDetailChanged(DiscImport_SeriesDetailStruct* pDetail);

	void DiscImportStateChanged(SubModuleState* pState);

// Dialog Data
	//{{AFX_DATA(CDiscImportDlg)
	enum { IDD = IDD_FORMVIEW_DISC_IMPORT };
	CReportCtrl	m_listImage;
	CListCtrl	m_listImportSeries;
	CReportCtrl	m_listStudy;
	CReportCtrl	m_listSeries;
	CReportCtrl	m_listPatient;
	CComboBox	m_cbDevices;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiscImportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:

	void UpdatePatientInfo();
	void UpdateStudyInfo(LPCTSTR szPatientUID);
	void UpdateSeriesInfo(LPCTSTR szStudyUID);
	void UpdateImageInfo(LPCTSTR szSeriesUID);
	void EnableImportButton();

	// Ë¢ÐÂCheckbox×´Ì¬
	void UpdateSelectState();

	vector<DiscImportPatientStruct> m_vtrPatient;
	vector<DiscImportStudyStruct> m_vtrStudy;
	vector<DiscImportSeriesStruct> m_vtrSeries;
	vector<DiscImportImageStruct> m_vtrImage;

	SubModuleState m_DiscImportState;

	BOOL	m_bLVN_ITEMCHANGING_Enable;
	BOOL	m_bGetDiscInfoReady;

	CImageList	m_imgState;

protected:

	// Generated message map functions
	//{{AFX_MSG(CDiscImportDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonRefresh();
	afx_msg void OnClickListPatient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListStudy(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListSeries(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboImportDevice();
	afx_msg void OnButtonImport();
	afx_msg void OnDividerdblclickListPatient(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISCIMPORTDLG_H__1BF06E85_EBDE_4940_B97A_A924A4C509C9__INCLUDED_)
