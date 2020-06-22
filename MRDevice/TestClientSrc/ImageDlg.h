#if !defined(AFX_IMAGEDLG_H__CF4B5882_E0DB_4A72_82CD_D7D66BFFC4C3__INCLUDED_)
#define AFX_IMAGEDLG_H__CF4B5882_E0DB_4A72_82CD_D7D66BFFC4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageDlg dialog

class CImageDlg : public CDialog
{
// Construction
public:
	CImageDlg(CWnd* pParent = NULL);   // standard constructor
	~CImageDlg();
	
	BYTE* GetPixelBuffer();
	DWORD GetBufferSize();

	void ConvertData();

// Dialog Data
	//{{AFX_DATA(CImageDlg)
	enum { IDD = IDD_FORMVIEW_IMAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:

	WORD*		m_pPixelBuffer;
	DWORD		m_dwPixelBufferSize;

	BYTE*		m_pDispBuffer;

	PBITMAPINFO	m_pDibInfo;



// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEDLG_H__CF4B5882_E0DB_4A72_82CD_D7D66BFFC4C3__INCLUDED_)
