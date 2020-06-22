// ImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "ImageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageDlg dialog


CImageDlg::CImageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CImageDlg::~CImageDlg()
{
	if (m_pPixelBuffer)
	{
		delete m_pPixelBuffer;
		m_pPixelBuffer = NULL;
	}
	if (m_pDispBuffer)
	{
		delete m_pDispBuffer;
		m_pDispBuffer = NULL;
	}


}


void CImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP

	m_dwPixelBufferSize = 2*1024*1024;
	m_pPixelBuffer = new WORD[m_dwPixelBufferSize/2];
	m_pDispBuffer = new BYTE[1024*1024];

}


BEGIN_MESSAGE_MAP(CImageDlg, CDialog)
	//{{AFX_MSG_MAP(CImageDlg)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageDlg message handlers

BOOL CImageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pDibInfo=(PBITMAPINFO)malloc( 
									sizeof(BITMAPINFOHEADER)+
									256*sizeof(RGBQUAD)
								  );
	
	m_pDibInfo->bmiHeader.biSize=(long)sizeof(BITMAPINFOHEADER);
	m_pDibInfo->bmiHeader.biPlanes=1;
	m_pDibInfo->bmiHeader.biCompression=BI_RGB;//0
	m_pDibInfo->bmiHeader.biBitCount=8;
	m_pDibInfo->bmiHeader.biSizeImage=0L;
	m_pDibInfo->bmiHeader.biXPelsPerMeter=0L;
	m_pDibInfo->bmiHeader.biYPelsPerMeter=0L;
	m_pDibInfo->bmiHeader.biClrUsed=0L;
	m_pDibInfo->bmiHeader.biClrImportant=0L;

	for(int i=0;i<256;i++)
	{	//默认为256级灰度
		m_pDibInfo->bmiColors[i].rgbRed=i;
		m_pDibInfo->bmiColors[i].rgbGreen=i;
		m_pDibInfo->bmiColors[i].rgbBlue=i;
		m_pDibInfo->bmiColors[i].rgbReserved=0;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BYTE* CImageDlg::GetPixelBuffer()
{
	return (BYTE*)m_pPixelBuffer;
}

DWORD CImageDlg::GetBufferSize()
{
	return m_dwPixelBufferSize;
}

void CImageDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	HBITMAP			hBitmap,hOldBitmap;
	HDC				hdc;
	CDC*			pdc=GetDC();
	HDC				hMemoryDC;

	m_pDibInfo->bmiHeader.biWidth= 1024;
	m_pDibInfo->bmiHeader.biHeight= 1024;

	hdc=pdc->GetSafeHdc();

	hBitmap=::CreateDIBitmap(pdc->m_hDC,
						(LPBITMAPINFOHEADER)&(m_pDibInfo->bmiHeader),
						CBM_INIT,
						(LPSTR)m_pDispBuffer,
						(LPBITMAPINFO)m_pDibInfo,
						DIB_RGB_COLORS);
	
	hMemoryDC=::CreateCompatibleDC(hdc);
	hOldBitmap=(HBITMAP)::SelectObject(hMemoryDC,hBitmap);

// 	::BitBlt(hdc, 0, 0, 1024,1024,	
// 				hMemoryDC,0,0,SRCCOPY);	

	SetStretchBltMode(hdc,COLORONCOLOR);
	// 获得窗口大小
	CRect rect;
	GetWindowRect(&rect);

	::StretchDIBits(hdc,0,0,rect.right-rect.left,rect.bottom-rect.top,
					0, 0,1024, 1024, 
					m_pDispBuffer,(LPBITMAPINFO)m_pDibInfo, 
					DIB_RGB_COLORS, 
					SRCCOPY);

	::SelectObject(hMemoryDC,hOldBitmap);

	::DeleteDC(hMemoryDC);
	::DeleteObject(hBitmap);
	
	ReleaseDC(pdc);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CImageDlg::ConvertData()
{
	DWORD dwCount = 1024*1024;
	for (int i = 0; i < dwCount; i++)
	{
		m_pDispBuffer[i] = m_pPixelBuffer[i] >> 4;
// 		m_pDispBuffer[i] = m_pPixelBuffer[i] / 16;
	}
}

UINT CImageDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
// 	UINT nHitTest =CDialog::OnNcHitTest(point);
// 	return (nHitTest == HTCLIENT) ? HTCAPTION : nHitTest;
	
	return CDialog::OnNcHitTest(point);
}

void CImageDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
// 	CRect rect1;
// 	GetWindowRect(&rect1);
// 
// 	CRect rect;
// 	GetParent()->GetWindowRect(&rect);
// 	int iHeight = rect.bottom - rect.top;
// 	int iWidth = rect.right - rect.left;
// 	rect.top = rect1.top;
// 	rect.left = rect1.left - 150;
// 	rect.right = rect.left + iWidth;
// 	rect.bottom = rect.top + iHeight;
// 	GetParent()->MoveWindow(rect);
}
