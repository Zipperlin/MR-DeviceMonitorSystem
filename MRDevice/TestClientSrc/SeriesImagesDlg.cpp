// SeriesImagesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testclientsrc.h"
#include "SeriesImagesDlg.h"
#include "testclientsrcDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesImagesDlg dialog
extern CTestClientSrcDlg* g_smDlg;

const DWORD g_dwLeftMargin = 150;
const DWORD g_dwSurroundMargin = 10;

CSeriesImagesDlg::CSeriesImagesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeriesImagesDlg::IDD, pParent)
{
	m_strImagePath = _T("");
	m_iImageNum = 0;
	m_iImageStartIndex = 0;
	m_iCurrentImageIndex = 0;
	m_hFile = INVALID_HANDLE_VALUE;


	//{{AFX_DATA_INIT(CSeriesImagesDlg)
	m_uEditImageIndex = 0;
	m_radioImageFormat = -1;
	//}}AFX_DATA_INIT
}

CSeriesImagesDlg::~CSeriesImagesDlg()
{

}


void CSeriesImagesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeriesImagesDlg)
	DDX_Control(pDX, IDC_CHECK_PLAY, m_checkPlay);
	DDX_Control(pDX, IDC_SLIDER_PLAY_SPEED, m_sliderPlaySpeed);
	DDX_Control(pDX, IDC_SLIDER_IMAGE, m_sliderImage);
	DDX_Text(pDX, IDC_EDIT_CURRENT_NUM, m_uEditImageIndex);
	DDX_Radio(pDX, IDC_RADIO_RAW_IMAGE, m_radioImageFormat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSeriesImagesDlg, CDialog)
	//{{AFX_MSG_MAP(CSeriesImagesDlg)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_VIEW_IMAGE, OnButtonViewImage)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnButtonPrevious)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_WM_HSCROLL()
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_PLAY, OnCheckPlay)
	ON_BN_CLICKED(IDC_CHECK_FORWARD, OnCheckForward)
	ON_BN_CLICKED(IDC_CHECK_REVERSE, OnCheckReverse)
	ON_BN_CLICKED(IDC_BUTTON_SET_IMAGE_SIZE, OnButtonSetImageSize)
	ON_EN_CHANGE(IDC_EDIT_IMAGE_WIDTH, OnChangeEditImageWidth)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, OnButtonHide)
	ON_BN_CLICKED(IDC_RADIO_RAW_IMAGE, OnRadioRawImage)
	ON_BN_CLICKED(IDC_RADIO_POST_IMAGE, OnRadioPostImage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeriesImagesDlg message handlers


void CSeriesImagesDlg::SetImagePath(LPCTSTR szPath)
{
	m_strImagePath = szPath;
}

void CSeriesImagesDlg::SetImageNum(INT iImageNum, INT iImageStartIndex)
{
	m_iImageNum = iImageNum;
	m_iImageStartIndex = iImageStartIndex;
	m_sliderImage.SetRange(1, iImageNum);

	CString strInfo;
	strInfo.Format(_T("%d"), m_iImageNum);
	GetDlgItem(IDC_STATIC_IMAGE_NUM)->SetWindowText(strInfo);

}
SeriesInfoStruct* CSeriesImagesDlg::GetSeriesInfoStruct()
{
	return &m_SeriesInfo;
}

PostProcessingInfo*  CSeriesImagesDlg::GetPostProcessInfo()
{
	return &m_PostProcessInfo;
}

void CSeriesImagesDlg::ShowImage(INT iImageIndex)
{
	m_iCurrentImageIndex = iImageIndex;
	
	ViewImage(iImageIndex);

	// 显示窗口
	ShowWindow(SW_SHOW);
}

BOOL CSeriesImagesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// 图像格式设置
	m_radioImageFormat = 0;

	// 播放速度设置
	m_sliderPlaySpeed.SetRange(1, 30);
	m_sliderPlaySpeed.SetPos(1);

	// 播放方向
	((CButton*)GetDlgItem(IDC_CHECK_FORWARD))->SetCheck(BST_CHECKED);


	//
	m_ImageDlg.Create(IDD_FORMVIEW_IMAGE, this);
	
	CRect rect;
	GetImageWndPos(&rect);
 	m_ImageDlg.MoveWindow(&rect);

	// 显示初始图像大小
	CString strInfo;
	strInfo.Format(_T("%d"), rect.right - rect.left);
	GetDlgItem(IDC_EDIT_IMAGE_WIDTH)->SetWindowText(strInfo);

	m_ImageDlg.ShowWindow(SW_SHOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSeriesImagesDlg::InitProcessSettingBFS(LPCTSTR szSeriesFullName,
											INT iImageIndex,
											PVOID pRawImage)
{
// 	CString strTrace;
// 
// 	if (pRawImage)
// 	{
// 		memcpy(m_ProcessingSetting.pRawBuffer, pRawImage, DICOM_RAW_IMAGE_BYTE);
// 	}
// 	else
// 	{	
// 		if (INVALID_HANDLE_VALUE == m_hFile)
// 		{
// 			m_hFile = ::CreateFile(m_strImagePath,
// 								GENERIC_READ,              // open for reading 
// 								FILE_SHARE_READ,           // share for reading 
// 								NULL,                      // no security 
// 								OPEN_ALWAYS,             // existing file only 
// 								FILE_ATTRIBUTE_NORMAL,     // normal file 
// 								NULL);                     // no attr. template 
// 
// 			if (INVALID_HANDLE_VALUE == m_hFile)
// 			{
// 				AfxMessageBox(_T("Failed to ::CreateFile()"));
// 				return FALSE;
// 			}
// 		}
// 
// 
// 		// 获得图像物理位置
// 		INT iPhisicalPos = (m_iImageNum + iImageIndex + m_iImageStartIndex - 2) % m_iImageNum;
// 
// 		// 定位文件指针
// 		LONG lOffset = iPhisicalPos*m_ImageDlg.GetBufferSize() + 65536;
// 		if (INVALID_SET_FILE_POINTER == ::SetFilePointer(m_hFile, lOffset, NULL, FILE_BEGIN))
// 		{
// 			CloseHandle(m_hFile);
// 			m_hFile = INVALID_HANDLE_VALUE;
// 			AfxMessageBox(_T("Failed to ::SetFilePointer()!"));
// 			return FALSE;
// 		}
// 
// 		// 读取图像数据
// 		DWORD dwByteRead = 0;
//  		if (::ReadFile(m_hFile, m_ProcessingSetting.pRawBuffer, DICOM_RAW_IMAGE_BYTE, &dwByteRead, NULL))
// 		{
// 			if (dwByteRead != DICOM_RAW_IMAGE_BYTE)
// 			{
// 				CloseHandle(m_hFile);
// 				m_hFile = INVALID_HANDLE_VALUE;
// 				AfxMessageBox(_T("Failed to ::ReadFile(): dwByteRead != DICOM_RAW_IMAGE_BYTE!"));
// 				return FALSE;
// 			}
// 		}
// 		else
// 		{
// 			CloseHandle(m_hFile);
// 			m_hFile = INVALID_HANDLE_VALUE;
// 			AfxMessageBox(_T("Failed to ::ReadFile()!"));
// 			return FALSE;
// 		}
// 	}
// 
// 
// 	if (m_PostProcessInfo.bChangeFlag)
// 	{
// 		m_ProcessingSetting.bLogLUT = m_PostProcessInfo.bLogLUT;
// 
// 		// 判断是否做剪影
// 		if (m_PostProcessInfo.bSubtract && m_PostProcessInfo.iMaskIndex < m_SeriesInfo.lNumberofImages)
// 		{
// 			m_ProcessingSetting.bSubtract = TRUE;
// 		}
// 		else
// 		{
// 			m_ProcessingSetting.bSubtract = FALSE;
// 		}
// 		
// 		if (m_ProcessingSetting.bSubtract)
// 		{
// 			m_ProcessingSetting.bLandMarking = m_PostProcessInfo.bLandMarking;
// 
// 			m_ProcessingSetting.bPixelShift = m_PostProcessInfo.bPixelShift;
// // 				if (m_ProcessingSetting.bPixelShift)
// // 				{
// // 					PRINTTRACE_INFO("pixelshift on!")
// 				m_ProcessingSetting.iPixelShift_X = m_PostProcessInfo.iPixelShift_X;
// 				m_ProcessingSetting.iPixelShift_Y = m_PostProcessInfo.iPixelShift_Y;
// // 				}
// 
// 			m_ProcessingSetting.iMaskIndex = m_PostProcessInfo.iMaskIndex;
// 
// 			
// 			// 定位文件指针
// 			LONG lOffset = m_ProcessingSetting.iMaskIndex * DICOM_RAW_IMAGE_BYTE + 65536;
// 			if (INVALID_SET_FILE_POINTER == ::SetFilePointer(m_hFile, lOffset, NULL, FILE_BEGIN))
// 			{
// 				CloseHandle(m_hFile);
// 				m_hFile = INVALID_HANDLE_VALUE;
// 				AfxMessageBox(_T("Failed to ::SetFilePointer()!"));
// 				return FALSE;
// 			}
// 
// 			DWORD dwByteRead = 0;
//  			if (::ReadFile(m_hFile, m_ProcessingSetting.pMask, DICOM_RAW_IMAGE_BYTE, &dwByteRead, NULL))
// 			{
// 				if (dwByteRead != DICOM_RAW_IMAGE_BYTE)
// 				{
// 					CloseHandle(m_hFile);
// 					m_hFile = INVALID_HANDLE_VALUE;
// 					AfxMessageBox(_T("Failed to ::ReadFile(): dwByteRead != DICOM_RAW_IMAGE_BYTE!"));
// 					return FALSE;
// 				}
// 			}
// 			else
// 			{
// 				CloseHandle(m_hFile);
// 				m_hFile = INVALID_HANDLE_VALUE;
// 				AfxMessageBox(_T("Failed to ::ReadFile()!"));
// 				return FALSE;
// 			}
// 	
// 			m_ProcessingSetting.fSubGain = m_PostProcessInfo.fSubGain;
// 			m_ProcessingSetting.iSubOffset = m_PostProcessInfo.iSubOffset;
// 			m_ProcessingSetting.fLandmarkingGain = m_PostProcessInfo.fLandmarkingGain;
// 		}
// 
// 		m_ProcessingSetting.iEdgeenhancmentLevel = m_PostProcessInfo.iEdgeenhancmentLevel;
// 
// 		m_ProcessingSetting.iWW = m_PostProcessInfo.iWW;
// 		m_ProcessingSetting.iWL = m_PostProcessInfo.iWL;
// 		m_ProcessingSetting.iRotation = m_PostProcessInfo.iRotation;
// 		m_ProcessingSetting.bInverse = m_PostProcessInfo.bInverse;
// 		m_ProcessingSetting.fZoomFactor = m_PostProcessInfo.fZoomFactor;
// 		m_ProcessingSetting.bShutter = m_PostProcessInfo.bShutter;
// 
// 		m_ProcessingSetting.iImageHeight = 1024;
// 		m_ProcessingSetting.iImageWidth = 1024;
// 		m_ProcessingSetting.iPixelDepth = 12;
// 		m_ProcessingSetting.iMaxPixelValue = 4095;
// 
// 		m_ProcessingSetting.iOffsetX = m_PostProcessInfo.iOffsetX;
// 		m_ProcessingSetting.iOffsetY = m_PostProcessInfo.iOffsetY;
// 
// 		m_ProcessingSetting.bOverlay = m_PostProcessInfo.bOverlay;
// 
// 		m_ProcessingSetting.iElectroShutter_Left = m_PostProcessInfo.iElectroShutter_Left;
// 		m_ProcessingSetting.iElectroShutter_Right = m_PostProcessInfo.iElectroShutter_Right;
// 		m_ProcessingSetting.iElectroShutter_Top = m_PostProcessInfo.iElectroShutter_Top;
// 		m_ProcessingSetting.iElectroShutter_Bottom = m_PostProcessInfo.iElectroShutter_Bottom;
// 	}
// 	else
// 	{
// 		// 未经过Reviewing模块后处理
// 		m_ProcessingSetting.bLogLUT = FALSE;
// 
// 		if (m_SeriesInfo.iMaskImageIndex > 0 &&
// 			m_SeriesInfo.iMaskImageIndex <= m_SeriesInfo.lNumberofImages)
// 		{
// 			m_ProcessingSetting.bSubtract = TRUE;
// 		}
// 		else
// 		{
// 			m_ProcessingSetting.bSubtract = FALSE;
// 		}
// 
// 		m_ProcessingSetting.fLandmarkingGain = 0.1f;
// 		m_ProcessingSetting.bLandMarking =TRUE;
// 		m_ProcessingSetting.bPixelShift = TRUE;
// 		m_ProcessingSetting.iPixelShift_X =0;
// 		m_ProcessingSetting.iPixelShift_Y =0;
// 
// 		m_ProcessingSetting.iMaskIndex = m_SeriesInfo.iMaskImageIndex;
// 		if (m_ProcessingSetting.bSubtract)
// 		{
// 			m_ProcessingSetting.fSubGain = m_SeriesInfo.fConstrast;
// 			m_ProcessingSetting.iSubOffset = 4095*m_SeriesInfo.fBrightness/2.0;
// 			m_ProcessingSetting.iWW = 4096;
// 			m_ProcessingSetting.iWL = 2048;
// 
// 			// Read Mask pixel data
// 			
// 
// 			unsigned int iMaskImagePhisicalPos = (m_SeriesInfo.lNumberofImages + m_PostProcessInfo.iMaskIndex + m_SeriesInfo.iRunStartIndex - 2) % m_SeriesInfo.lNumberofImages;
// 			// 定位文件指针
// 			LONG lOffset = iMaskImagePhisicalPos * DICOM_RAW_IMAGE_BYTE + 65536;
// 			if (INVALID_SET_FILE_POINTER == ::SetFilePointer(m_hFile, lOffset, NULL, FILE_BEGIN))
// 			{
// 				CloseHandle(m_hFile);
// 				m_hFile = INVALID_HANDLE_VALUE;
// 				AfxMessageBox(_T("Failed to ::SetFilePointer()!"));
// 				return FALSE;
// 			}
// 
// 			DWORD dwByteRead = 0;
//  			if (::ReadFile(m_hFile, m_ProcessingSetting.pMask, DICOM_RAW_IMAGE_BYTE, &dwByteRead, NULL))
// 			{
// 				if (dwByteRead != DICOM_RAW_IMAGE_BYTE)
// 				{
// 					CloseHandle(m_hFile);
// 					m_hFile = INVALID_HANDLE_VALUE;
// 					AfxMessageBox(_T("Failed to ::ReadFile(): dwByteRead != DICOM_RAW_IMAGE_BYTE!"));
// 					return FALSE;
// 				}
// 			}
// 			else
// 			{
// 				CloseHandle(m_hFile);
// 				m_hFile = INVALID_HANDLE_VALUE;
// 				AfxMessageBox(_T("Failed to ::ReadFile()!"));
// 				return FALSE;
// 			}
// 		}
// 		else
// 		{
// 			m_ProcessingSetting.fSubGain = 1.0;
// 			m_ProcessingSetting.iSubOffset = 2048;
// 			CBrightContrastConvert BCConvert;
// 			//m_ProcessingSetting.iWW = BCConvert.ContrastToWindowWidth((int)m_pSeriesInfo->fConstrast);
// 			//m_ProcessingSetting.iWL = BCConvert.BrightNessToWindowCenter((int)m_pSeriesInfo->fBrightness);
// 			BCConvert.ContrastBrightness2WWWL((int)m_SeriesInfo.fConstrast,
// 											(int)m_SeriesInfo.fBrightness,
// 											m_ProcessingSetting.iWW,
// 											m_ProcessingSetting.iWL);
// 		}
// 
// 		m_ProcessingSetting.iRotation = m_iImageRotationArray[m_SeriesInfo.iNoseOrientation][m_SeriesInfo.iLegsOrientation][m_SeriesInfo.iLArmOrientation];
// 
// 		m_ProcessingSetting.bInverse = m_SeriesInfo.bVideoInvert;
// 		m_ProcessingSetting.fZoomFactor = 1.0;
// 		m_ProcessingSetting.bShutter = TRUE;
// 
// 		m_ProcessingSetting.iImageHeight = 1024;
// 		m_ProcessingSetting.iImageWidth = 1024;
// 		m_ProcessingSetting.iPixelDepth = 12;
// 		m_ProcessingSetting.iMaxPixelValue = 4095;
// 		m_ProcessingSetting.iEdgeenhancmentLevel = m_SeriesInfo.iEnhencement;
// 
// 		m_ProcessingSetting.iOffsetX = 0;
// 		m_ProcessingSetting.iOffsetY = 0;
// 
// 		m_ProcessingSetting.bOverlay = TRUE;
// 
// 		m_ProcessingSetting.iElectroShutter_Left = 0;
// 		m_ProcessingSetting.iElectroShutter_Right = 1024;
// 		m_ProcessingSetting.iElectroShutter_Top = 0;
// 		m_ProcessingSetting.iElectroShutter_Bottom = 1024;
// 	}
// 
// 	
// 		CString strAnnoFilePath;
// 		GetAnnoFileNameBFS(m_strImagePath, iImageIndex, strAnnoFilePath);
// 
// 		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, strAnnoFilePath, -1, (char*)m_ProcessingSetting.szAnnoFilePath, MAX_PATH, NULL, NULL ); 

	return TRUE;
}

void CSeriesImagesDlg::GetAnnoFileNameBFS(LPCTSTR szSeriesFullName, INT iImageIndex, CString& strAnnoFileFullPath)
{
	strAnnoFileFullPath = _T("F:\\Annotations");
	LPCTSTR szRelativePathStart = wcschr(szSeriesFullName, _T('\\'));
	LPCTSTR p = szRelativePathStart + 1;
	szRelativePathStart = wcschr(p, _T('\\'));

	CString strAnnoFileName;
	strAnnoFileName.Format(_T("%d%s"), iImageIndex,  _T(".AnnoProperty"));

	strAnnoFileFullPath += szRelativePathStart;
	strAnnoFileFullPath += _T("\\");;
	strAnnoFileFullPath += strAnnoFileName;
}

void CSeriesImagesDlg::ViewImage(INT iImageIndex)
{
	// 设置当前图像
	m_uEditImageIndex = m_iCurrentImageIndex;
	m_sliderImage.SetPos(m_iCurrentImageIndex);
	UpdateData(FALSE);

	// 显示图像
	if (iImageIndex < 1 || iImageIndex > m_iImageNum)
	{
		AfxMessageBox(_T("Image index error!"));
		return;
	}

	if (INVALID_HANDLE_VALUE == m_hFile)
	{
		m_hFile = ::CreateFile(m_strImagePath,
							GENERIC_READ,              // open for reading 
							FILE_SHARE_READ,           // share for reading 
							NULL,                      // no security 
							OPEN_ALWAYS,             // existing file only 
							FILE_ATTRIBUTE_NORMAL,     // normal file 
							NULL);                     // no attr. template 

		if (INVALID_HANDLE_VALUE == m_hFile)
		{
			AfxMessageBox(_T("Failed to ::CreateFile()"));
			return;
		}
	}


	// 获得图像物理位置
	INT iPhisicalPos = (m_iImageNum + iImageIndex + m_iImageStartIndex - 2) % m_iImageNum;

	// 定位文件指针
	LONG lOffset = iPhisicalPos*m_ImageDlg.GetBufferSize() + 65536;
	if (INVALID_SET_FILE_POINTER == ::SetFilePointer(m_hFile, lOffset, NULL, FILE_BEGIN))
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
		AfxMessageBox(_T("Failed to ::SetFilePointer()!"));
		return;
	}

	// 读取图像数据
	DWORD dwByteRead = 0;
 	if (::ReadFile(m_hFile, m_ImageDlg.GetPixelBuffer(), m_ImageDlg.GetBufferSize(), &dwByteRead, NULL))
	{
		if (dwByteRead != m_ImageDlg.GetBufferSize())
		{
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
			AfxMessageBox(_T("Failed to ::ReadFile(): dwByteRead != m_ImageDlg.GetBufferSize()!"));
			return;
		}
	}
	else
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
		AfxMessageBox(_T("Failed to ::ReadFile()!"));
		return;
	}

	// 是否需要对图像进行后处理
	if (0 == m_radioImageFormat)
	{
		// Raw
	}
	else if (1 == m_radioImageFormat)
	{
		// PostProcessed
		//设置前处理参数
		if (!InitProcessSettingBFS(m_strImagePath,
								iImageIndex,
								m_ImageDlg.GetPixelBuffer()))
		{

			AfxMessageBox(_T("InitProcessSetting(...)")); 
			return;
		}

// 		m_ArchiveProcessing.SetProcessingStruct(&m_ProcessingSetting);
// 		if (!m_ArchiveProcessing.GetPreprocessedBuffer((short*)m_ImageDlg.GetPixelBuffer()))
// 		{
// 			AfxMessageBox(_T("m_ArchiveProcessing.GetPreprocessedBuffer"));
// 			return;
// 		}
// 
// 		// 后处理
// 		if (!m_ArchiveProcessing.ArchivingProc())
// 		{
// 			AfxMessageBox(_T("m_ArchiveProcessing.ArchivingProc()"));
// 			return;
// 		}
// 
	}

	//设置显示图像

	// 16 -> 8
	m_ImageDlg.ConvertData();

	// 需要刷新窗口么？
	m_ImageDlg.Invalidate(FALSE);

}

void CSeriesImagesDlg::GetImageWndPos(CRect* pRect)
{
	CRect rect;
	GetWindowRect(&rect);

	pRect->top = g_dwSurroundMargin;
	pRect->left = g_dwLeftMargin + g_dwSurroundMargin;

	int iWidth = rect.right - rect.left - g_dwLeftMargin - 2*g_dwSurroundMargin;
	int iHeight = rect.bottom - rect.top - 2*g_dwSurroundMargin;
	int iMin = min(iWidth, iHeight);

// 	int iMin = min(rect.right - rect.left - g_dwLeftMargin - 2*g_dwSurroundMargin, rect.bottom - rect.top - 2*g_dwSurroundMargin);

	if (iMin < 50)
	{
		iMin = 50;
	}

	pRect->bottom = iMin;
	pRect->right = pRect->left + iMin;

}

void CSeriesImagesDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect;
	GetImageWndPos(&rect);



	CWnd* pWnd = (CWnd*)GetDlgItem(IDC_EDIT_IMAGE_WIDTH);
	if (pWnd)
	{
		CString strInfo;
		strInfo.Format(_T("%d"), rect.right - rect.left);
		pWnd->SetWindowText(strInfo);
	}
// 	GetDlgItem(IDC_EDIT_IMAGE_HEIGHT)->SetWindowText(strInfo);

 	m_ImageDlg.MoveWindow(&rect);
	m_ImageDlg.Invalidate(FALSE);
}

void CSeriesImagesDlg::OnButtonViewImage() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	ViewImage(m_uEditImageIndex);
}

void CSeriesImagesDlg::OnButtonPrevious() 
{
	// TODO: Add your control notification handler code here

	if (m_iCurrentImageIndex == 1)
	{
		m_uEditImageIndex = 1;
		UpdateData(FALSE);
		return;
	}

	m_iCurrentImageIndex--;
	UpdateData(FALSE);

	ViewImage(m_iCurrentImageIndex);

}

void CSeriesImagesDlg::OnButtonNext() 
{
	// TODO: Add your control notification handler code here
	if (m_iCurrentImageIndex == m_iImageNum)
	{
		m_uEditImageIndex = m_iImageNum;
		UpdateData(FALSE);
		return;
	}

	m_iCurrentImageIndex++;

	ViewImage(m_iCurrentImageIndex);
}

void CSeriesImagesDlg::OnButtonFirst() 
{
	// TODO: Add your control notification handler code here
	m_iCurrentImageIndex = 1;

	ViewImage(m_iCurrentImageIndex);
}

void CSeriesImagesDlg::OnButtonLast() 
{
	// TODO: Add your control notification handler code here
	m_iCurrentImageIndex = m_iImageNum;

	ViewImage(m_iCurrentImageIndex);
}

void CSeriesImagesDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	switch(pScrollBar->GetDlgCtrlID()) 
	{
	case IDC_SLIDER_IMAGE:
		{
			m_iCurrentImageIndex = m_sliderImage.GetPos();

			ViewImage(m_iCurrentImageIndex);
		}
		break;
	case IDC_SLIDER_PLAY_SPEED:
		{
			if (BST_CHECKED == m_checkPlay.GetCheck())
			{
				KillTimer(1);
				SetTimer(1, 1000/m_sliderPlaySpeed.GetPos(), NULL);
			}

			CString strInfo;
			strInfo.Format(_T("%d fr/s"), m_sliderPlaySpeed.GetPos());
			GetDlgItem(IDC_STATIC_PLAY_SPEED)->SetWindowText(strInfo);
		}
		break;
	default:
		return;
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

UINT CSeriesImagesDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	UINT nHitTest =CDialog::OnNcHitTest(point);
	return (nHitTest == HTCLIENT) ? HTCAPTION : nHitTest;
// 	return CDialog::OnNcHitTest(point);
}

void CSeriesImagesDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (1 == nIDEvent)
	{
		// 获得图像索引
		int iImageIndex = m_iCurrentImageIndex;

		if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_FORWARD))->GetCheck())
		{
			// 前向播放
			if (m_iCurrentImageIndex == m_iImageNum)
			{
				if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_CYCLE))->GetCheck())
				{
					// 循环播放
					iImageIndex = 1;
				}
			}
			else
			{
				++iImageIndex;
			}
		}
		else
		{
			// 反向播放
			if (m_iCurrentImageIndex == 1)
			{
				if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_CYCLE))->GetCheck())
				{
					// 循环播放
					iImageIndex = m_iImageNum;
				}
			}
			else
			{
				--iImageIndex;
			}
		}

		if (iImageIndex == m_iCurrentImageIndex)
		{
			// 播放应停止
			Stop();
		}
		else
		{
			m_iCurrentImageIndex = iImageIndex;

			ViewImage(m_iCurrentImageIndex);
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CSeriesImagesDlg::Play()
{
	// 设置播放定时器
	m_checkPlay.SetWindowText(_T("||"));
	m_checkPlay.SetCheck(BST_CHECKED);

	SetTimer(1, 1000/m_sliderPlaySpeed.GetPos(), NULL);

}

void CSeriesImagesDlg::Stop()
{
	m_checkPlay.SetWindowText(_T("|>"));
	m_checkPlay.SetCheck(BST_UNCHECKED);
	KillTimer(1);
}

void CSeriesImagesDlg::OnCheckPlay() 
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_checkPlay.GetCheck())
	{
		Play();
	}
	else
	{
		Stop();
	}
}

void CSeriesImagesDlg::OnCheckForward() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_CHECK_REVERSE))->SetCheck(BST_CHECKED != ((CButton*)GetDlgItem(IDC_CHECK_FORWARD))->GetCheck() ? BST_CHECKED : BST_UNCHECKED);
}

void CSeriesImagesDlg::OnCheckReverse() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_CHECK_FORWARD))->SetCheck(BST_CHECKED != ((CButton*)GetDlgItem(IDC_CHECK_REVERSE))->GetCheck() ? BST_CHECKED : BST_UNCHECKED);
}

void CSeriesImagesDlg::OnButtonSetImageSize() 
{
	// TODO: Add your control notification handler code here
	CString strInfo;
	GetDlgItem(IDC_EDIT_IMAGE_WIDTH)->GetWindowText(strInfo);
	if (strInfo.IsEmpty())
	{
		return;
	}
		
	int iSize = _tcstol(strInfo, NULL, 10);
	if (iSize < 50 || iSize > 2048)
	{
		return;
	}

	CRect rect;
	GetWindowRect(&rect);
	rect.right = rect.left + g_dwLeftMargin + 2*g_dwSurroundMargin + iSize;
	rect.bottom = rect.top + 2*g_dwSurroundMargin + iSize;
	MoveWindow(rect);
}

void CSeriesImagesDlg::OnChangeEditImageWidth() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString strInfo;
	GetDlgItem(IDC_EDIT_IMAGE_WIDTH)->GetWindowText(strInfo);
	GetDlgItem(IDC_EDIT_IMAGE_HEIGHT)->SetWindowText(strInfo);

	// TODO: Add your control notification handler code here
	
}

void CSeriesImagesDlg::OnButtonHide() 
{
	// TODO: Add your control notification handler code here
	if (BST_CHECKED == m_checkPlay.GetCheck())
	{
		Stop();
	}

	if (INVALID_HANDLE_VALUE != m_hFile)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}

	ShowWindow(SW_HIDE);
}

BOOL CSeriesImagesDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			OnButtonHide();
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CSeriesImagesDlg::OnRadioRawImage() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSeriesImagesDlg::OnRadioPostImage() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
