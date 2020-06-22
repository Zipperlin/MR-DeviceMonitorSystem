#if !defined(AFX_SERIESIMAGESDLG_H__B5B7DA90_E51E_493D_959E_AFACCB131272__INCLUDED_)
#define AFX_SERIESIMAGESDLG_H__B5B7DA90_E51E_493D_959E_AFACCB131272__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SeriesImagesDlg.h : header file
//

#include "imagedlg.h"

#if !defined(INVALID_SET_FILE_POINTER)
	#define INVALID_SET_FILE_POINTER 0xffffffff
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesImagesDlg dialog

class CSeriesImagesDlg : public CDialog
{
// Construction
public:
	CSeriesImagesDlg(CWnd* pParent = NULL);   // standard constructor
	~CSeriesImagesDlg();

	void SetImagePath(LPCTSTR szPath);
	void SetImageNum(INT iImageNum, INT iImageStartIndex);
	SeriesInfoStruct* GetSeriesInfoStruct();
	PostProcessingInfo* GetPostProcessInfo();

	// iImageIndex为逻辑索引，从1开始
	void ShowImage(INT iImageIndex);

// Dialog Data
	//{{AFX_DATA(CSeriesImagesDlg)
	enum { IDD = IDD_FORMVIEW_SERIES_IMAGE };
	CButton	m_checkPlay;
	CSliderCtrl	m_sliderPlaySpeed;
	CSliderCtrl	m_sliderImage;
	UINT	m_uEditImageIndex;
	int		m_radioImageFormat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeriesImagesDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	BOOL InitProcessSettingBFS(LPCTSTR szSeriesFullName,
							INT iImageIndex,
							PVOID pRawImage);
	void GetAnnoFileNameBFS(LPCTSTR szSeriesFullName, INT iImageIndex, CString& strAnnoFileFullPath);

 	void ViewImage(INT iImageIndex);
	void GetImageWndPos(CRect* pRect);

	void Play();
	void Stop();

	CImageDlg		m_ImageDlg;

	CString			m_strImagePath;
	INT				m_iImageNum;
	INT				m_iImageStartIndex;

	INT				m_iCurrentImageIndex;

	SeriesInfoStruct		m_SeriesInfo;
	PostProcessingInfo		m_PostProcessInfo;


	HANDLE			m_hFile;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSeriesImagesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonViewImage();
	afx_msg void OnButtonPrevious();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonFirst();
	afx_msg void OnButtonLast();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckPlay();
	afx_msg void OnCheckForward();
	afx_msg void OnCheckReverse();
	afx_msg void OnButtonSetImageSize();
	afx_msg void OnChangeEditImageWidth();
	afx_msg void OnButtonHide();
	afx_msg void OnRadioRawImage();
	afx_msg void OnRadioPostImage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIESIMAGESDLG_H__B5B7DA90_E51E_493D_959E_AFACCB131272__INCLUDED_)
