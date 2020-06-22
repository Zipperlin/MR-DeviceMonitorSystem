/* Time: <@(#)DcmPartner.cpp   2009-3-5 - 10:37:46   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DcmPartner.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : DICOM partner
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:37:46		FanZF	Creation
 *
 *********************************************************************
 */

// DcmPartner.cpp: implementation of the CDcmPartner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DcmPartner.h"
// #include "RunFile.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CDcmPartner::CDcmPartner()
{
	m_pDcmPixelData = NULL;

	m_pJob = NULL;
	m_szStorePath = NULL;

	m_bRawDcm = FALSE;
	m_bProcessedDcm = FALSE;
	m_bMakePSFile = FALSE;
	m_bMakeDICOMDIR = FALSE;

	m_pvtrRawDcmImages = NULL;
	m_pvtrProcDcmImages = NULL;

	m_pConfigInfo = NULL;

	m_pPatientInfo = NULL;
	m_pStudyInfo = NULL;
	m_pSeriesInfo = NULL;
	m_pPostProcessInfo = NULL;

	m_bChineseLang = FALSE;

}

CDcmPartner::~CDcmPartner()
{

}

BOOL CDcmPartner::Init()
{
	PRINTTRACE_ENTER_FUNCTION
		
// 	if (m_ArchiveProcessing.InitImageWndDlg(TRUE))
// 	{
// 		PRINTTRACE_INFO("m_ArchiveProcessing.InitImageWndDlg()")
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("m_ArchiveProcessing.InitImageWndDlg()")
// 		return FALSE;
// 	}

	GetLanguageSetting();
	
// 	if (!m_RawDataBuffer.SetSize(DICOM_RAW_IMAGE_BYTE))
// 	{
// 		PRINTTRACE_ERROR("m_RawDataBuffer.SetSize(DICOM_RAW_IMAGE_BYTE)")
// 		return FALSE;
// 	}


// 	if (GetProcessingSettingLogLUT())
// 	{
// 		PRINTTRACE_INFO("GetProcessingSettingLogLUT()")
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("GetProcessingSettingLogLUT()")
// 		return FALSE;
// 	}



	return TRUE;
}

void CDcmPartner::UnInit()
{
	PRINTTRACE_ENTER_FUNCTION

// 	m_RawDataBuffer.ReleaseBuffer();
	if (NULL != m_pDcmPixelData)
	{
		delete [] m_pDcmPixelData;
		m_pDcmPixelData = NULL;
	}

	m_pJob = NULL;
	m_szStorePath = NULL;

	m_bRawDcm = FALSE;
	m_bProcessedDcm = FALSE;
	m_bMakePSFile = FALSE;
	m_bMakeDICOMDIR = FALSE;

	m_pvtrRawDcmImages = NULL;
	m_pvtrProcDcmImages = NULL;

	m_pConfigInfo = NULL;

	m_pPatientInfo = NULL;
	m_pStudyInfo = NULL;
	m_pSeriesInfo = NULL;
	m_pPostProcessInfo = NULL;

	m_bChineseLang = FALSE;
	
	m_vtrPatientDir.clear();

}


BOOL CDcmPartner::GetPatientInfoStruct(vector<PatientInfoStruct>* pvtrPatientStruct, LPCTSTR szPatientUID, PatientInfoStruct** ppPatientStruct)
{
	CString strPatientUID;
	for (INT i = 0; i < pvtrPatientStruct->size(); i++)
	{
		strPatientUID = CBSTROpt::BSTRToCString((*pvtrPatientStruct)[i].bsPatientUID);
		if (!strPatientUID.Compare(szPatientUID))
		{
			*ppPatientStruct = &(*pvtrPatientStruct)[i];
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CDcmPartner::GetStudyInfoStruct(vector<StudyInfoStruct>* pvtrStudyStruct, LPCTSTR szStudyUID, StudyInfoStruct** ppStudyStruct)
{
	CString strStudyUID;
	for (INT i = 0; i < pvtrStudyStruct->size(); i++)
	{
		strStudyUID = CBSTROpt::BSTRToCString((*pvtrStudyStruct)[i].bsStudyUID);
		if (!strStudyUID.Compare(szStudyUID))
		{
			*ppStudyStruct = &(*pvtrStudyStruct)[i];
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CDcmPartner::GetSeriesInfoStruct(vector<SeriesInfoStruct>* pvtrSeriesStruct, LPCTSTR szSeriesUID, SeriesInfoStruct** ppSeriesStruct)
{
	CString strSeriesUID;
	for (INT i = 0; i < pvtrSeriesStruct->size(); i++)
	{
		strSeriesUID = CBSTROpt::BSTRToCString((*pvtrSeriesStruct)[i].bsSeriesUID);
		if (!strSeriesUID.Compare(szSeriesUID))
		{
			*ppSeriesStruct = &(*pvtrSeriesStruct)[i];
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CDcmPartner::GetPostProcessInfoStruct(vector<PostProcessingInfo>* pvtrPostProcessStruct, LPCTSTR szImageUID, PostProcessingInfo** ppPostProcessStruct)
{
	if (0 == pvtrPostProcessStruct->size())
	{
		PRINTTRACE_INFO("0 == pvtrSeriesPostProcessStruct->size()")
		*ppPostProcessStruct = NULL;
		return FALSE;
	}

	CString strImageUID;
	for (INT i = 0; i < pvtrPostProcessStruct->size(); i++)
	{
		strImageUID = CBSTROpt::BSTRToCString((*pvtrPostProcessStruct)[i].bsImageUID);
		if (!strImageUID.Compare(szImageUID))
		{
			*ppPostProcessStruct = &(*pvtrPostProcessStruct)[i];
			return TRUE;
		}
	}

	*ppPostProcessStruct = NULL;
	return FALSE;
}

// For Big File Series
void CDcmPartner::SetImageType(BOOL bRawDcm, BOOL bProcessedDcm)
{
	m_bRawDcm = bRawDcm;
	m_bProcessedDcm = bProcessedDcm;
}

void CDcmPartner::SetPSFile(BOOL bPS)
{
	m_bMakePSFile = bPS;
}

void CDcmPartner::SetDcmDir(BOOL bDcmDir)
{
	m_bMakeDICOMDIR = bDcmDir;
}


BOOL CDcmPartner::ConvertBFS(PAJob* pJob,
					LPCTSTR szStorePath,
					vector<CString>* pvtrRawDcmImages,
					vector<CString>* pvtrProcDcmImages)
{
	PRINTTRACE_ENTER_FUNCTION

	m_pJob = pJob;
	m_szStorePath = szStorePath;

	m_pvtrRawDcmImages = pvtrRawDcmImages;
	m_pvtrProcDcmImages = pvtrProcDcmImages;

	m_vtrPatientDir.clear();

	BOOL bRet = TRUE;
	BOOL bJobCancelled = FALSE;

	CString strSeriesFullName;
	CString strDstImageFullName;

	DWORD dwConvertedImagesCount = 0;

	switch (pJob->enumJobType)
	{
	case enumJobType_PrintJob:

		m_NotifyObject = NOTIFY_PRINT;
		break;

	case enumJobType_BurnJob:

		m_NotifyObject = NOTIFY_BURN;
		break;

	case enumJobType_AutoSendJob:
	case enumJobType_ManualSendJob:

		m_NotifyObject = NOTIFY_TRANSFER;
		break;

	default:
		return FALSE;
	}


	// Clear Task Dir
	if (!CheckTaskDir(m_szStorePath, TRUE))
	{
		PRINTTRACE_ERROR("CheckTaskDir(m_szStorePath, TRUE)")
		return FALSE;
	}

	// Check Disk Space
	if (!CheckDiskSpace())
	{
		PRINTTRACE_ERROR("CheckDiskSpace()")
		return FALSE;
	}


	m_dwPhaseNum = 0;
	
	if (!m_bRawDcm && !m_bProcessedDcm)
	{
		return FALSE;
	}

	if (m_bRawDcm)
	{
		++m_dwPhaseNum;
	}
	
	if (m_bProcessedDcm)
	{
		++m_dwPhaseNum;
	}

	if (0 == m_dwPhaseNum)
	{
		return FALSE;
	}

	m_dwHandledImagesCount = 0;
	NotifyProgress();

// 	if (!ConnectToRawImageDisk())
// 	{
// 		return FALSE;
// 	}
// 	else
// 	{
// 		EnableDisconnectToRawImageDisk();
// 	}


	// Convert Start!


	// Create raw or DX (raw and processed) dcm
	if (ConvertImages())
	{
		PRINTTRACE_INFO("ConvertSFImagesBFS(enumDownscaleCriterion_1024_12_16)")
	}
	else
	{
		PRINTTRACE_ERROR("ConvertSFImagesBFS(enumDownscaleCriterion_1024_12_16)")

		bRet = FALSE;
	}


	//<< 通过接口释放NFileFormat对象内存
	ReleaseNFFObj();

	// Convert End
// 	if (!DisConnectToRawImageDisk())
// 	{
// 		PRINTTRACE_ERROR("DisConnectToRawImageDisk()")
// 		bRet = FALSE;
// 	}


	return bRet;

}

BOOL CDcmPartner::ConvertImages()
{
	PRINTTRACE_ENTER_FUNCTION

	BOOL bRet = TRUE;
	BOOL bJobCancelled = FALSE;

	m_pConfigInfo = CDBController::GetInstance()->GetConfigInfo();
	if (NULL == m_pConfigInfo)
	{
		PRINTTRACE_ERROR("m_pConfigInfo = CDBController::GetInstance()->GetConfigInfo(), NULL == m_pConfigInfo")
		return FALSE;
	}


//<< 1. Processed First

	for (INT i = 0; i < m_pJob->vtrImages.size(); i++)
	{
		// the Job be cancelled?
		if (m_pJob->bCancelFlag)
		{
			PRINTTRACE_INFO("Image conversion cancelled because of pJob->bCancelFlag")
			
			return TRUE;
		}

		m_pImageInfo = &(m_pJob->vtrImages)[i];

		CString strImageUID = CBSTROpt::BSTRToCString(m_pImageInfo->bsImageUID);
		if (!GetPostProcessInfoStruct(&m_pJob->vtrPostProcess, strImageUID, &m_pPostProcessInfo))
		{
			PRINTTRACE_ERROR(_T("ERROR: GetPostProcessInfoStruct()"))
			bRet = FALSE;
			break;
		}

		CString strSeriesUID = CBSTROpt::BSTRToCString(m_pImageInfo->bsSeriesUID);
		if (!GetSeriesInfoStruct(&m_pJob->vtrSeries, strSeriesUID, &m_pSeriesInfo))
		{
			PRINTTRACE_ERROR(_T("ERROR: GetSeriesInfoStruct()"))
			bRet = FALSE;
			break;
		}

		CString strStudyUID = CBSTROpt::BSTRToCString(m_pSeriesInfo->bsStudyUID);
		if (!GetStudyInfoStruct(&m_pJob->vtrStudy, strStudyUID, &m_pStudyInfo))
		{
			PRINTTRACE_ERROR(_T("ERROR: GetPatientInfoStruct()"))
			bRet = FALSE;
			break;
		}

		CString strPatientUID = CBSTROpt::BSTRToCString(m_pStudyInfo->bsPatientUID);
		if (!GetPatientInfoStruct(&m_pJob->vtrPatient, strPatientUID, &m_pPatientInfo))
		{
			PRINTTRACE_ERROR(_T("ERROR: GetPatientInfoStruct()"))
			bRet = FALSE;
			break;
		}

		//<< 转换当前图像
		if (ConvertOneImageToDXImage(FALSE))
		{
			PRINTTRACE_INFO("ConvertOneImageToDXImage")
		}
		else
		{
			PRINTTRACE_ERROR("ConvertOneImageToDXImage")
			
			bRet = FALSE;
			break;
		}
	}

	if (!bRet)
	{
		return bRet;
	}

//<< 2. DICOMDIR
	if (m_pJob->bCancelFlag)
	{
		PRINTTRACE_INFO("Image conversion cancelled because of pJob->bCancelFlag")
		return TRUE;
	}
	
	if (m_bMakeDICOMDIR)
	{
		CString strDICOMDIRpath = m_szStorePath;
		strDICOMDIRpath += DICOM_IMAGE_WORK_DIR;
		CheckTaskDir(strDICOMDIRpath);
		
		CDcmDirGen DcmDirGen;
		if (DcmDirGen.CreateDicomDirFile(strDICOMDIRpath))
		{
			PRINTTRACE_INFO("CreateDicomDirFile(strDICOMDIRpath)")
		}
		else
		{
			bRet = FALSE;
			PRINTTRACE_ERROR("CreateDicomDirFile(strDICOMDIRpath)")
		}
	}

	if (!bRet)
	{
		return bRet;
	}

//<< 3. Raw Dcm
	for (i = 0; i < m_pJob->vtrImages.size(); i++)
	{
		// the Job be cancelled?
		if (m_pJob->bCancelFlag)
		{
			PRINTTRACE_INFO("Image conversion cancelled because of pJob->bCancelFlag")
			
			return TRUE;
		}

		m_pImageInfo = &(m_pJob->vtrImages)[i];

		CString strImageUID = CBSTROpt::BSTRToCString(m_pImageInfo->bsImageUID);
		if (!GetPostProcessInfoStruct(&m_pJob->vtrPostProcess, strImageUID, &m_pPostProcessInfo))
		{
			PRINTTRACE_ERROR(_T("ERROR: GetPostProcessInfoStruct()"))
			bRet = FALSE;
			break;
		}

		CString strSeriesUID = CBSTROpt::BSTRToCString(m_pImageInfo->bsSeriesUID);
		if (!GetSeriesInfoStruct(&m_pJob->vtrSeries, strSeriesUID, &m_pSeriesInfo))
		{
			PRINTTRACE_ERROR(_T("ERROR: GetSeriesInfoStruct()"))
			bRet = FALSE;
			break;
		}

		CString strStudyUID = CBSTROpt::BSTRToCString(m_pSeriesInfo->bsStudyUID);
		if (!GetStudyInfoStruct(&m_pJob->vtrStudy, strStudyUID, &m_pStudyInfo))
		{
			PRINTTRACE_ERROR(_T("ERROR: GetPatientInfoStruct()"))
			bRet = FALSE;
			break;
		}

		CString strPatientUID = CBSTROpt::BSTRToCString(m_pStudyInfo->bsPatientUID);
		if (!GetPatientInfoStruct(&m_pJob->vtrPatient, strPatientUID, &m_pPatientInfo))
		{
			PRINTTRACE_ERROR(_T("ERROR: GetPatientInfoStruct()"))
			bRet = FALSE;
			break;
		}

		//<< 转换当前图像
		if (ConvertOneImageToDXImage(TRUE))
		{
			PRINTTRACE_INFO("ConvertOneImageToDXImage")
		}
		else
		{
			PRINTTRACE_ERROR("ConvertOneImageToDXImage")
			
			bRet = FALSE;
			break;
		}
	}


	return bRet;
}

// BOOL CDcmPartner::ConvertMFImagesBFS()
// {
// 	PRINTTRACE_ENTER_FUNCTION
// 
// 	BOOL bRet = TRUE;
// 
// 	for (INT i = 0; i < m_pJob->vtrImages.size(); i++)
// 	{
// 		// the Job be cancelled?
// 		if (m_pJob->bCancelFlag)
// 		{
// 			PRINTTRACE_INFO("Image conversion cancelled because of pJob->bCancelFlag")
// 			break;
// 		}
// 
// 		// All Series?
// 		if (!(m_pJob->vtrImages)[i].bTotalSeries)
// 		{
// 			PRINTTRACE_ERROR("FALSE == (pJob->vtrImages)[i].bTotalSeries while Convert Multi-Frame Images")
// 			bRet = FALSE;
// 			break;
// 		}
// 
// 		if (!GetPatientInfoStruct(&m_pJob->vtrPatient, (m_pJob->vtrImages)[i].strPatientUID, &m_pPatientInfo))
// 		{
// 			PRINTTRACE_ERROR(_T("ERROR: GetPatientInfoStruct()"))
// 			bRet = FALSE;
// 			break;
// 		}
// 
// 		if (!GetStudyInfoStruct(&m_pJob->vtrStudy, (m_pJob->vtrImages)[i].strStudyUID, &m_pStudyInfo))
// 		{
// 			PRINTTRACE_ERROR(_T("ERROR: GetPatientInfoStruct()"))
// 			bRet = FALSE;
// 			break;
// 		}
// 
// 		if (!GetSeriesInfoStruct(&m_pJob->vtrSeries, (m_pJob->vtrImages)[i].strSeriesUID, &m_pSeriesInfo))
// 		{
// 			PRINTTRACE_ERROR(_T("ERROR: GetSeriesInfoStruct()"))
// 			bRet = FALSE;
// 			break;
// 		}
// 		
// 		m_pConfigInfo = CDBController::GetInstance()->GetConfigInfo();
// 		if (NULL == m_pConfigInfo)
// 		{
// 			PRINTTRACE_ERROR("m_pConfigInfo = CDBController::GetInstance()->GetConfigInfo(), NULL == m_pConfigInfo")
// 			bRet = FALSE;
// 			break;
// 		}
// 
// 		GetSeriesPostProcessInfoStruct(&m_pJob->vtrSeriesPostProcess, (m_pJob->vtrImages)[i].strSeriesUID, &m_pPostProcessInfo);
// 
// 		if (ConvertOneXAMFImageBFS())
// 		{
// 			PRINTTRACE_INFO("ConvertOneXAMFImageBFS()")
// 		}
// 		else
// 		{
// 			PRINTTRACE_ERROR("ConvertOneXAMFImageBFS()")
// 			bRet = FALSE;
// 			break;
// 		}
// 	}
// 
// 	DisConnectToRawImageDisk();
// 
// 	return bRet;
// }


BOOL CDcmPartner::ConvertOneImageToDXImage(BOOL bRaw)
{
	CString strTrace;
	

	DWORD dwStart =GetTickCount();

	//<< 源文件
	CString strImageFullName;
	GetImageFileName(bRaw, strImageFullName);

	CString strDcmImageDir;
	GetDcmImageDir(strDcmImageDir);
	if (!CheckTaskDir(strDcmImageDir))
	{
		strTrace.Format(_T("CheckTaskDir(strDcmImageDir), strDcmImageDir is : %s"), strDcmImageDir);
		PRINTTRACE_INFO(strTrace)
		return FALSE;
	}

	// 目标文件
	CString strDstImageFullName;
	GetDcmImageFullName(strDcmImageDir, bRaw, strDstImageFullName);

	//<< 拷贝文件
	if (!::CopyFile(strImageFullName, strDstImageFullName, TRUE))
	{
		strTrace.Format(_T("CopyFile(strSrcPSPath, strDstPSPath), %s, %s"), strImageFullName, strDstImageFullName);
		PRINTTRACE_INFO(strTrace)
		return FALSE;
	}
	

	// 拷贝PS文件，仅Processed时需要
	if (!bRaw)
	{
		CString strSrcPSPath;
		GetOriginalPSFileName(strSrcPSPath);

		CString strDstPSPath;
		GetDcmPSFullName(strDstImageFullName, strDstPSPath);


		if (!::CopyFile(strSrcPSPath, strDstPSPath, TRUE))
		{
			strTrace.Format(_T("CopyFile(strSrcPSPath, strDstPSPath), %s, %s"), strSrcPSPath, strDstPSPath);
			PRINTTRACE_INFO(strTrace)
			return FALSE;
		}
	}

	++m_dwHandledImagesCount;
	NotifyProgress();
	
	strTrace.Format(_T("Dcm Time: %d"), GetTickCount() - dwStart);
	PRINTTRACE_WARNING(strTrace)

	// BMP or(and) JPEG
	

	return TRUE;
}

// BOOL CDcmPartner::ConvertOneXAImage512BFS()
// {
// 	CString strSeriesFullName;
// 
// 	CVDcmSysConfigInfoStruct DcmConfigInfo;
// 	CVDcmSysPatientTotalInfoStruct DcmPatientTotalInfo;
// 	CVDcmSysAdditionalInfoStruct DcmAdditionalInfo;
// 
// 	CString strTrace;
// 
// 
// 	// Fill Dcm Structs
// 	CDBDcmStructConverter ddsc;
// 	ddsc.ConfigConvertDBToDcm(m_pConfigInfo, &DcmConfigInfo);
// 	ddsc.PatientTotalConvertDBToDcm(m_pPatientInfo,
// 									m_pStudyInfo,
// 									m_pSeriesInfo,
// 									m_pPostProcessInfo,
// 									&DcmPatientTotalInfo);
// 
// 	DcmAdditionalInfo.g_usHeartRate = 0;
// 	if (m_bIP)
// 	{
// 		DcmAdditionalInfo.g_bPostProcessed = TRUE;
// 	}
// 	else
// 	{
// 		DcmAdditionalInfo.g_bPostProcessed = FALSE;
// 	}
// 
// 	if (!GetWWAndWL(enumDownscaleCriterion_512_8_8, &DcmAdditionalInfo.g_usWW, &DcmAdditionalInfo.g_usWL))
// 	{
// 		PRINTTRACE_ERROR("GetWWAndWL()")
// 		return FALSE;
// 	}
// 
// 	DcmAdditionalInfo.g_usImageIndex = m_iImageIndex;
// 
// 	GetSeriesFullName(m_pSeriesInfo, strSeriesFullName);
// 
// 
// 	SetTotalInfo(DcmConfigInfo,
// 				DcmPatientTotalInfo,
// 				DcmAdditionalInfo);
// 
// 
// 
// 	if (InitDicomDXStructIntoNFileFormatObj())
// 	{
// 		PRINTTRACE_INFO("InitDicomDXStructIntoNFileFormatObj()")
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("InitDicomDXStructIntoNFileFormatObj()")
// 		return FALSE;
// 	}
// 
// 
// 	// Connect to Raw image disk
// 	if (!ConnectToRawImageDisk())
// 	{
// 		PRINTTRACE_ERROR("ERROR: ConnectToRawImageDisk()")
// 		return FALSE;
// 	}
// 
// 	// Get Raw image pixel data
// 	RunFile BFSReader;
// 	if (BFSReader.Open(strSeriesFullName, DICOM_RAW_IMAGE_BYTE)) 
// 	{
// 		EnableDisconnectToRawImageDisk();
// 		PRINTTRACE_INFO(_T("Open BFS file, file name:")); 
// 		PRINTTRACE_INFO(strSeriesFullName)
// 
// 		unsigned int iPhisicalPos = (m_pSeriesInfo->lNumberofImages + m_iImageIndex + m_pSeriesInfo->iRunStartIndex - 2) % m_pSeriesInfo->lNumberofImages;
// 		// Connect to Raw image disk
// 		if (!ConnectToRawImageDisk())
// 		{
// 			PRINTTRACE_ERROR("ERROR: ConnectToRawImageDisk()")
// 			BFSReader.Close();
// 			return FALSE;
// 		}
// 
// 		// Job is Cancelled?
// 		if (m_pJob->bCancelFlag)
// 		{
// 			PRINTTRACE_INFO("m_pJob->bCancelFlag")
// 			BFSReader.Close();
// 			return TRUE;
// 		}
// 
// 		if (BFSReader.ReadImage(m_RawDataBuffer.GetBufferPointer(), iPhisicalPos))
// 		{
// 			strTrace.Format(_T("Read BFS file, read Pos: %d"), iPhisicalPos);
// 			PRINTTRACE_INFO(strTrace)
// 
// 			BFSReader.Close();
// 
// 			EnableDisconnectToRawImageDisk();
// 
// 			if (m_bIP)
// 			{
// 				if (NULL == m_pPostProcessInfo)
// 				{
// 					BFSReader.Close();
// 					return FALSE;
// 				}
// 
// 				//设置前处理参数
// 				if (InitProcessSettingBFS(strSeriesFullName,
// 										m_iImageIndex,
// 										(void*)m_RawDataBuffer.GetBufferPointer()))
// 				{
// 					PRINTTRACE_INFO(_T("InitProcessSettingBFS(...)")); 
// 				}
// 				else
// 				{
// 					PRINTTRACE_ERROR(_T("InitProcessSettingBFS(...)")); 
// 					BFSReader.Close();
// 					return FALSE;
// 				}
// 
// 				m_ArchiveProcessing.SetProcessingStruct(&m_ProcessingSetting);
// 
// 				//前处理
// 				PRINTTRACE_INFO("before m_ArchiveProcessing.GetPreprocessedBuffer")
// 				if (m_ArchiveProcessing.GetPreprocessedBuffer((short*)m_RawDataBuffer.GetBufferPointer()))
// 				{
// 					PRINTTRACE_INFO("m_ArchiveProcessing.GetPreprocessedBuffer")
// 				}
// 				else
// 				{
// 					PRINTTRACE_ERROR("m_ArchiveProcessing.GetPreprocessedBuffer")
// 					BFSReader.Close();
// 					return FALSE;
// 				}
// 			}
// 
// 			// 有损失压缩
// 			if (!m_bIP)
// 				m_ArchiveProcessing.GetGrayScalePixel((short*)m_RawDataBuffer.GetBufferPointer(), m_ProcessingSetting.pLogLUT, 1024, 1024);
// 			
// 			BYTE* pDownScaleData = m_ArchiveProcessing.GetDownScaleImage((short*)m_RawDataBuffer.GetBufferPointer(), 1024, 1024, 16, 512, 512, 8);
// 
// 			if(!SetUncompressedDXPixelData(pDownScaleData))
// 			{
// 				PRINTTRACE_ERROR("SetCVXADicomPixelData(pDownScaleData)")
// 				BFSReader.Close();
// 				return FALSE;
// 			}
// 
// 		}	
// 		else
// 		{
// 			strTrace.Format(_T("Read BFS file, read Pos: %d"), iPhisicalPos);
// 			PRINTTRACE_ERROR(strTrace)
// 
// 			BFSReader.Close();
// 			EnableDisconnectToRawImageDisk();
// 			return FALSE;
// 		}
// 
// 	}
// 	else
// 	{
// 		
// 		PRINTTRACE_ERROR(_T("Open BFS file, file name:")); 
// 		PRINTTRACE_ERROR(strSeriesFullName)
// 
// 		EnableDisconnectToRawImageDisk();
// 		return FALSE; 
// 	}
// 	
// 
// 	// Check dir
// 	CString strDcmStudyDir;
// 	GetDcmImageDir(strDcmStudyDir);
// 	if (!CheckTaskDir(strDcmStudyDir))
// 	{
// 		PRINTTRACE_ERROR("CheckTaskDir(strDcmStudyDir), strDcmCacheStudyDir is :")
// 		PRINTTRACE_INFO(strDcmStudyDir)
// 		return FALSE;
// 	}
// 
// 	// Get Dcm File Name
// 	CString strDstImageFullName;
// 	GetDcmSFImageFullName(strDcmStudyDir, strDstImageFullName);
// 
// 	if (SaveUncompressedDXDicomFile(strDstImageFullName))
// 	{
// 		PRINTTRACE_INFO("SaveUncompressedDXDicomFile(strDstImageFullName), Name is: ")
// 		PRINTTRACE_INFO(strDstImageFullName)
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("SaveUncompressedDXDicomFile(strDstImageFullName), Name is: ")
// 		PRINTTRACE_ERROR(strDstImageFullName)
// 		return FALSE;
// 	}
// 
// 	// 生成PS文件
// 	if (m_bMakePSFile)
// 	{
// 		CString strPSFileFullPath;
// 		GetPSFileName(strDstImageFullName, strPSFileFullPath);
// 
// 		if (m_ArchiveProcessing.ArchivingProc())
// 		{
// 			PRINTTRACE_INFO("m_ArchiveProcessing.ArchivingProc()")
// 		}
// 		else
// 		{
// 			PRINTTRACE_ERROR("m_ArchiveProcessing.ArchivingProc()")
// 			return FALSE;
// 		}
// 
// 		if (m_ArchiveProcessing.SavePSFile(strDstImageFullName, strPSFileFullPath))
// 		{
// 			PRINTTRACE_INFO("m_ArchiveProcessing.SavePSFile(strDstImageFullName, strPSFileFullPath)")
// 		}
// // 		else
// // 		{
// // 			PRINTTRACE_ERROR("m_ArchiveProcessing.SavePSFile(strDstImageFullName, strPSFileFullPath)")
// // 			return FALSE;
// // 		}
// 
// 	}
// 
// 	if (m_pvtrDcmImages)
// 	{
// 		m_pvtrDcmImages->push_back(strDstImageFullName);
// 	}
// 
// 	return TRUE;
// }

// BOOL CDcmPartner::ConvertOneXAMFImageBFS()
// {
// 
// 	CString strSeriesFullName;
// 
// 	CVDcmSysConfigInfoStruct DcmConfigInfo;
// 	CVDcmSysPatientTotalInfoStruct DcmPatientTotalInfo;
// 	CVDcmSysAdditionalInfoStruct DcmAdditionalInfo;
// 	
// 
// 	CString strTrace;
// 
// 
// 	// Fill Dcm Structs
// 	CDBDcmStructConverter ddsc;
// 	ddsc.ConfigConvertDBToDcm(m_pConfigInfo, &DcmConfigInfo);
// 	ddsc.PatientTotalConvertDBToDcm(m_pPatientInfo,
// 									m_pStudyInfo,
// 									m_pSeriesInfo,
// 									m_pPostProcessInfo,
// 									&DcmPatientTotalInfo);
// 
// 	DcmAdditionalInfo.g_usHeartRate = 0;
// 	if (m_bIP)
// 	{
// 		DcmAdditionalInfo.g_bPostProcessed = TRUE;
// 	}
// 	else
// 	{
// 		DcmAdditionalInfo.g_bPostProcessed = FALSE;
// 	}
// 
// 	if (!GetWWAndWL(m_enumDownscaleCriterion, &DcmAdditionalInfo.g_usWW, &DcmAdditionalInfo.g_usWL))
// 	{
// 		PRINTTRACE_ERROR("GetWWAndWL()")
// 		return FALSE;
// 	}
// 
// 	DcmAdditionalInfo.g_usImageIndex = 0;	// 0 for MF since it's useless
// 
// 	GetSeriesFullName(m_pSeriesInfo, strSeriesFullName);
// 
// 
// 	DICOMImageSize enumImageSize;
// 	if (enumDownscaleCriterion_1024_12_16 == m_enumDownscaleCriterion)
// 	{
// 		enumImageSize = enumDICOMImageSize_1024_12_16;
// 	}
// 	else
// 	{
// 		enumImageSize = enumDICOMImageSize_512_8_8;
// 	}
// 
// 	SetTotalInfo(DcmConfigInfo,
// 				DcmPatientTotalInfo,
// 				DcmAdditionalInfo);
// 	
// 	PRINTTRACE_INFO("Before InitCVDicomXAStructIntoNFileFormatObj();")
// 	if (InitDicomDXStructIntoNFileFormatObj())
// 	{
// 		PRINTTRACE_INFO("InitCVDicomXAStructIntoNFileFormatObj()")
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("InitCVDicomXAStructIntoNFileFormatObj()")
// 		return FALSE;
// 	}
// 
// 
// // 	// Too many images are not allowed to make Multi Frame Images
// // 	if (m_pSeriesInfo->lNumberofImages >= 100)
// // 	{
// // 		PRINTTRACE_ERROR("pSeriesInfo->lNumberofImages >= 50, can't make Multi Frame images")
// // 		return FALSE;
// // 	}
// 
// //	CBuffer m_RawDataBuffer(DICOM_RAW_IMAGE_BYTE * m_pSeriesInfo->lNumberofImages);
// 
// 	// Connect to Raw image disk
// 	if (!ConnectToRawImageDisk())
// 	{
// 		PRINTTRACE_ERROR("ERROR: ConnectToRawImageDisk()")
// 		return FALSE;
// 	}
// 
// 	// Get Raw image pixel data
// 	RunFile BFSReader;
// 	if (BFSReader.Open(strSeriesFullName, DICOM_RAW_IMAGE_BYTE)) 
// 	{
// 		EnableDisconnectToRawImageDisk();
// 		PRINTTRACE_INFO(_T("Open BFS file, file name:")); 
// 		PRINTTRACE_INFO(strSeriesFullName)
// 
// 		for (m_iImageIndex = 1; m_iImageIndex <= m_pSeriesInfo->lNumberofImages; m_iImageIndex++)
// 		{
// 			unsigned int iPhisicalPos = (m_pSeriesInfo->lNumberofImages + m_iImageIndex + m_pSeriesInfo->iRunStartIndex - 2) % m_pSeriesInfo->lNumberofImages;
// 			// Connect to Raw image disk
// 			if (!ConnectToRawImageDisk())
// 			{
// 				PRINTTRACE_ERROR("ERROR: ConnectToRawImageDisk()")
// 				BFSReader.Close();
// 				return FALSE;
// 			}
// 
// 			// Job is Cancelled?
// 			if (m_pJob->bCancelFlag)
// 			{
// 				PRINTTRACE_INFO("m_pJob->bCancelFlag")
// 				BFSReader.Close();
// 				return TRUE;
// 			}
// 
// 			if (BFSReader.ReadImage(m_RawDataBuffer.GetBufferPointer(), iPhisicalPos))
// 			{
// 				strTrace.Format(_T("Read BFS file, read Pos: %d"), iPhisicalPos);
// 				PRINTTRACE_INFO(strTrace)
// 
// 				EnableDisconnectToRawImageDisk();
// 
// 				if (m_bIP)
// 				{
// 					if (NULL == m_pPostProcessInfo)
// 					{
// 						BFSReader.Close();
// 						return FALSE;
// 					}
// 
// 					//设置前处理参数
// 					if (InitProcessSettingBFS(strSeriesFullName,
// 											m_iImageIndex,
// 											(void*)m_RawDataBuffer.GetBufferPointer()))
// 					{
// 						PRINTTRACE_INFO(_T("InitProcessSettingBFS(...)")); 
// 					}
// 					else
// 					{
// 						PRINTTRACE_ERROR(_T("InitProcessSettingBFS(...)")); 
// 						BFSReader.Close();
// 						return FALSE;
// 					}
// 
// 					m_ArchiveProcessing.SetProcessingStruct(&m_ProcessingSetting);
// 
// 					//前处理
// 					PRINTTRACE_INFO("before m_ArchiveProcessing.GetPreprocessedBuffer")
// 					if (m_ArchiveProcessing.GetPreprocessedBuffer((short*)m_RawDataBuffer.GetBufferPointer()))
// 					{
// 						PRINTTRACE_INFO("m_ArchiveProcessing.GetPreprocessedBuffer")
// 					}
// 					else
// 					{
// 						PRINTTRACE_ERROR("m_ArchiveProcessing.GetPreprocessedBuffer")
// 						BFSReader.Close();
// 						return FALSE;
// 					}
// 				}
// 
// 				if (enumDownscaleCriterion_1024_12_16 == m_enumDownscaleCriterion)
// 				{
// 					// 设置无损压缩数据
// 					if (SetUncompressedDXPixelData(m_RawDataBuffer.GetBufferPointer()))
// 					{
// 						PRINTTRACE_INFO("SetCVXADicomPixelData()")
// 					}
// 					else
// 					{
// 						PRINTTRACE_ERROR("SetCVXADicomPixelData()")
// 						return FALSE;
// 					}
// 				}
// 				else
// 				{
// 					// 有损失压缩
// 					if (!m_bIP)
// 					{
// 						m_ArchiveProcessing.GetGrayScalePixel((short*)m_RawDataBuffer.GetBufferPointer(), m_ProcessingSetting.pLogLUT, 1024, 1024);
// 					}
// 
// 					BYTE* pDownScaleData = m_ArchiveProcessing.GetDownScaleImage((short*)m_RawDataBuffer.GetBufferPointer(), 1024, 1024, 16, 512, 512, 8);
// 
// 					if (!SetUncompressedDXPixelData(pDownScaleData))
// 					{
// 						PRINTTRACE_ERROR("SetCVXADicomPixelData()")
// 						return FALSE;
// 					}
// 				}
// 
// 			}	
// 			else
// 			{
// 				strTrace.Format(_T("Read BFS file, read Pos: %d"), iPhisicalPos);
// 				PRINTTRACE_ERROR(strTrace)
// 
// 				BFSReader.Close();
// 				EnableDisconnectToRawImageDisk();
// 				return FALSE;
// 			}
// 
// 			// Handle Progress
// 			m_dwHandledImagesCount++;
// 			if (m_iImageIndex < m_pSeriesInfo->lNumberofImages)
// 			{
// 				NotifyProgress();
// 			}
// 		}
// 
// 		BFSReader.Close();
// 	}
// 	else
// 	{
// 		
// 		PRINTTRACE_ERROR(_T("Open BFS file, file name:")); 
// 		PRINTTRACE_ERROR(strSeriesFullName)
// 
// 		EnableDisconnectToRawImageDisk();
// 		return FALSE; 
// 	}
// 	
// 	
// 	// Check dir
// 	CString strDcmStudyDir;
// 	GetDcmImageDir(strDcmStudyDir);
// 	if (!CheckTaskDir(strDcmStudyDir))
// 	{
// 		PRINTTRACE_ERROR("CheckTaskDir(strDcmStudyDir), strDcmCacheStudyDir is :")
// 		PRINTTRACE_INFO(strDcmStudyDir)
// 		return FALSE;
// 	}
// 
// 	// Get Dcm File Name
// 	CString strDstImageFullName;
// 	GetDcmMFImageFullName(strDcmStudyDir, strDstImageFullName);
// 
// 	if (SaveUncompressedDXDicomFile(strDstImageFullName))
// 	{
// 		PRINTTRACE_INFO("SaveCVXADicomFile(strDstImageFullName), Name is: ")
// 		PRINTTRACE_INFO(strDstImageFullName)
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("SaveCVXADicomFile(strDstImageFullName), Name is: ")
// 		PRINTTRACE_ERROR(strDstImageFullName)
// 		return FALSE;
// 	}
// 
// 	//<< 为此多帧DICOM生成一个PS文件
// 	//<< 需要PS的条件：不是backup且TRUE == m_bMakePSFile
// 	if (!m_bBackUp && m_bMakePSFile)
// 	{
// 		CString strPSFileFullPath;
// 		GetPSFileName(strDstImageFullName, strPSFileFullPath);
// 
// 		if (CreateOnePSForSeriesBFS(strPSFileFullPath))
// 		{
// 			strTrace.Format(_T("CreateOnePSForSeriesBFS(strPSFileFullPath), strPSFileFullPath: "), strPSFileFullPath);
// 			PRINTTRACE_INFO(strTrace)
// 		}
// 		else
// 		{
// 			strTrace.Format(_T("CreateOnePSForSeriesBFS(strPSFileFullPath), strPSFileFullPath: "), strPSFileFullPath);
// 			PRINTTRACE_ERROR(strTrace)
// 			return FALSE;
// 		}
// 
// 	}
// 
// 
// 	NotifyProgress();
// 
// 	if (m_pvtrDcmImages)
// 	{
// 		m_pvtrDcmImages->push_back(strDstImageFullName);
// 	}
// 
// 	return TRUE;
// }

// BOOL CDcmPartner::CreateOnePSForSeriesBFS(LPCTSTR szPSFile)
// {
// 	CString strSeriesFullName;
// 
// 	CVDcmSysConfigInfoStruct DcmConfigInfo;
// 	CVDcmSysPatientTotalInfoStruct DcmPatientTotalInfo;
// 	CVDcmSysAdditionalInfoStruct DcmAdditionalInfo;
// 	
// 
// 	CString strTrace;
// 
// 
// 	// Fill Dcm Structs
// 	CDBDcmStructConverter ddsc;
// 	ddsc.ConfigConvertDBToDcm(m_pConfigInfo, &DcmConfigInfo);
// 	ddsc.PatientTotalConvertDBToDcm(m_pPatientInfo,
// 									m_pStudyInfo,
// 									m_pSeriesInfo,
// 									m_pPostProcessInfo,
// 									&DcmPatientTotalInfo);
// 
// 	DcmAdditionalInfo.g_usHeartRate = 0;
// 	if (m_bProcessed)
// 	{
// 		DcmAdditionalInfo.g_bPostProcessed = TRUE;
// 	}
// 	else
// 	{
// 		DcmAdditionalInfo.g_bPostProcessed = FALSE;
// 	}
// 
// 	if (!GetWWAndWL(m_enumDownscaleCriterion, &DcmAdditionalInfo.g_usWW, &DcmAdditionalInfo.g_usWL))
// 	{
// 		PRINTTRACE_ERROR("GetWWAndWL()")
// 		return FALSE;
// 	}
// 
// 	DcmAdditionalInfo.g_usImageIndex = 0;	// 0 for MF since it's useless
// 
// 	GetSeriesFullName(m_pSeriesInfo, strSeriesFullName);
// 
// 
// 	DICOMImageSize enumImageSize;
// 	if (enumDownscaleCriterion_1024_12_16 == m_enumDownscaleCriterion)
// 	{
// 		enumImageSize = enumDICOMImageSize_1024_12_16;
// 	}
// 	else
// 	{
// 		enumImageSize = enumDICOMImageSize_512_8_8;
// 	}
// 
// 	SetTotalInfo(DcmConfigInfo,
// 				DcmPatientTotalInfo,
// 				DcmAdditionalInfo);
// 
// 
// 	PRINTTRACE_INFO("Before InitCVDicomXAStructIntoNFileFormatObj();")
// 	if (InitDicomDXStructIntoNFileFormatObj())
// 	{
// 		PRINTTRACE_INFO("InitCVDicomXAStructIntoNFileFormatObj()")
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("InitCVDicomXAStructIntoNFileFormatObj()")
// 		return FALSE;
// 	}
// 
// 	//<< 读取第一帧图像数据并将其设入DICOM操作类对象
// 	
// 	// Connect to Raw image disk
// 	if (!ConnectToRawImageDisk())
// 	{
// 		PRINTTRACE_ERROR("ERROR: ConnectToRawImageDisk()")
// 		return FALSE;
// 	}
// 
// 	// Get Raw image pixel data
// 	RunFile BFSReader;
// 	if (BFSReader.Open(strSeriesFullName, DICOM_RAW_IMAGE_BYTE)) 
// 	{
// 		EnableDisconnectToRawImageDisk();
// 		PRINTTRACE_INFO(_T("Open BFS file, file name:")); 
// 		PRINTTRACE_INFO(strSeriesFullName)
// 
// 		m_iImageIndex = 1;
// 		unsigned int iPhisicalPos = (m_pSeriesInfo->lNumberofImages + m_iImageIndex + m_pSeriesInfo->iRunStartIndex - 2) % m_pSeriesInfo->lNumberofImages;
// 		// Connect to Raw image disk
// 		if (!ConnectToRawImageDisk())
// 		{
// 			PRINTTRACE_ERROR("ERROR: ConnectToRawImageDisk()")
// 			BFSReader.Close();
// 			return FALSE;
// 		}
// 
// 		// Job is Cancelled?
// 		if (m_pJob->bCancelFlag)
// 		{
// 			PRINTTRACE_INFO("m_pJob->bCancelFlag")
// 			BFSReader.Close();
// 			return TRUE;
// 		}
// 
// 		if (BFSReader.ReadImage(m_RawDataBuffer.GetBufferPointer(), iPhisicalPos))
// 		{
// 			strTrace.Format(_T("Read BFS file, read Pos: %d"), iPhisicalPos);
// 			PRINTTRACE_INFO(strTrace)
// 
// 			EnableDisconnectToRawImageDisk();
// 
// 			if (m_bIP)
// 			{
// 				if (NULL == m_pPostProcessInfo)
// 				{
// 					BFSReader.Close();
// 					return FALSE;
// 				}
// 
// 				//设置前处理参数
// 				if (InitProcessSettingBFS(strSeriesFullName,
// 										m_iImageIndex,
// 										(void*)m_RawDataBuffer.GetBufferPointer()))
// 				{
// 					PRINTTRACE_INFO(_T("InitProcessSettingBFS(...)")); 
// 				}
// 				else
// 				{
// 					PRINTTRACE_ERROR(_T("InitProcessSettingBFS(...)")); 
// 					BFSReader.Close();
// 					return FALSE;
// 				}
// 
// 				m_ArchiveProcessing.SetProcessingStruct(&m_ProcessingSetting);
// 
// 				//前处理
// 				PRINTTRACE_INFO("before m_ArchiveProcessing.GetPreprocessedBuffer")
// 				if (m_ArchiveProcessing.GetPreprocessedBuffer((short*)m_RawDataBuffer.GetBufferPointer()))
// 				{
// 					PRINTTRACE_INFO("m_ArchiveProcessing.GetPreprocessedBuffer")
// 				}
// 				else
// 				{
// 					PRINTTRACE_ERROR("m_ArchiveProcessing.GetPreprocessedBuffer")
// 					BFSReader.Close();
// 					return FALSE;
// 				}
// 			}
// 
// 			if (enumDownscaleCriterion_1024_12_16 == m_enumDownscaleCriterion)
// 			{
// 				// 设置无损压缩数据
// 				if (SetUncompressedDXPixelData(m_RawDataBuffer.GetBufferPointer()))
// 				{
// 					PRINTTRACE_INFO("SetCVXADicomPixelData()")
// 				}
// 				else
// 				{
// 					PRINTTRACE_ERROR("SetCVXADicomPixelData()")
// 					return FALSE;
// 				}
// 			}
// 			else
// 			{
// 				// 有损失压缩
// 				if (!m_bIP)
// 				{
// 					m_ArchiveProcessing.GetGrayScalePixel((short*)m_RawDataBuffer.GetBufferPointer(), m_ProcessingSetting.pLogLUT, 1024, 1024);
// 				}
// 
// 				BYTE* pDownScaleData = m_ArchiveProcessing.GetDownScaleImage((short*)m_RawDataBuffer.GetBufferPointer(), 1024, 1024, 16, 512, 512, 8);
// 
// 				if (!SetUncompressedDXPixelData(pDownScaleData))
// 				{
// 					PRINTTRACE_ERROR("SetCVXADicomPixelData()")
// 					return FALSE;
// 				}
// 			}
// 
// 		}	
// 		else
// 		{
// 			strTrace.Format(_T("Read BFS file, read Pos: %d"), iPhisicalPos);
// 			PRINTTRACE_ERROR(strTrace)
// 
// 			BFSReader.Close();
// 			EnableDisconnectToRawImageDisk();
// 			return FALSE;
// 		}
// 
// 		BFSReader.Close();
// 	}
// 	else
// 	{
// 		
// 		PRINTTRACE_ERROR(_T("Open BFS file, file name:")); 
// 		PRINTTRACE_ERROR(strSeriesFullName)
// 
// 		EnableDisconnectToRawImageDisk();
// 		return FALSE; 
// 	}
// 	
// 	
// 	// Check dir
// 	// the Dcm is not needed, so create cache dcm
// 	
// 	CString strDcmCacheStudyDir;
// 	GetDcmCacheStudyDir(strDcmCacheStudyDir);
// 	if (!CheckTaskDir(strDcmCacheStudyDir))
// 	{
// 		PRINTTRACE_ERROR("CheckTaskDir(strDcmCacheStudyDir), strDcmCacheStudyDir is :")
// 		PRINTTRACE_INFO(strDcmCacheStudyDir)
// 		return FALSE;
// 	}
// 
// 	// Get Cache Dcm File Name
// 	CString strCacheDcmName;
// 	GetDcmMFImageFullName(strDcmCacheStudyDir, strCacheDcmName);
// 
// 	if (SaveUncompressedDXDicomFile(strCacheDcmName))
// 	{
// 		PRINTTRACE_INFO("SaveCVXADicomFile(strCacheDcmName), Name is: ")
// 		PRINTTRACE_INFO(strCacheDcmName)
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("SaveCVXADicomFile(strCacheDcmName), Name is: ")
// 		PRINTTRACE_ERROR(strCacheDcmName)
// 		return FALSE;
// 	}
// 	
// 	// 生成PS文件
// 	if (m_ArchiveProcessing.ArchivingProc())
// 	{
// 		PRINTTRACE_INFO("m_ArchiveProcessing.ArchivingProc()")
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("m_ArchiveProcessing.ArchivingProc()")
// 		return FALSE;
// 	}
// 
// 	// 生成PS文件，以包含旋转，反色等信息，但不引入ANNO（不要标注）
// 	if (enumDownscaleCriterion_512_8_8 == m_enumDownscaleCriterion)
// 	{
// 		if (m_ArchiveProcessing.SavePSFile(strCacheDcmName, szPSFile, enumMultiframe_512Mode))
// 		{
// 			PRINTTRACE_INFO("m_ArchiveProcessing.SavePSFile(strCacheDcmName, szPSFile)")
// 		}
// // 		else
// // 		{
// // 			PRINTTRACE_ERROR("m_ArchiveProcessing.SavePSFile(strCacheDcmName, szPSFile)")
// // 			return FALSE;
// // 		}
// 	}
// 	else
// 	{
// 		if (m_ArchiveProcessing.SavePSFile(strCacheDcmName, szPSFile, enumMultiframe_1024Mode))
// 		{
// 			PRINTTRACE_INFO("m_ArchiveProcessing.SavePSFile(strCacheDcmName, szPSFile)")
// 		}
// // 		else
// // 		{
// // 			PRINTTRACE_ERROR("m_ArchiveProcessing.SavePSFile(strCacheDcmName, szPSFile)")
// // 			return FALSE;
// // 		}
// 	}
// 
// 	return TRUE;
// }

// BOOL CDcmPartner::FillDcmPatientStruct(PatientInfoStruct* pPatientStruct, DcmPatientInfoStruct* pDcmPatientStruct)
// {
// 	pDcmPatientStruct->strPatientID = CBSTROpt::BSTRToCString(pPatientStruct->bsPatientID);
// 
// 	CString strPatientNameInDB = CBSTROpt::BSTRToCString(pPatientStruct->bsPatientName);
// 
// 	int iIndex = 0;
// 	iIndex = strPatientNameInDB.Find(_T("##"));
// 	if (-1 == iIndex)
// 	{
// 		PRINTTRACE_ERROR("-1 == strPatientNameInDB.Find(_T(##))")
// 		return FALSE;
// 	}
// 	CString strFirstName(strPatientNameInDB, iIndex);
// 	CString strNameBeginByMid = strPatientNameInDB.Mid(iIndex + 2);
// 
// 	iIndex = strNameBeginByMid.Find(_T("##"));
// 	if (-1 == iIndex)
// 	{
// 		PRINTTRACE_ERROR("-1 == strNameBeginByMid.Find(_T(##)")
// 		return FALSE;
// 	}
// 	CString strMidName = strNameBeginByMid.Left(iIndex);
// 	CString strLastName = strNameBeginByMid.Mid(iIndex + 2);
// 	
// 
// 	pDcmPatientStruct->strPatientName = strLastName + _T("^") + strMidName + _T("^") + strFirstName;
// 
// 
// 	pDcmPatientStruct->iGender = pPatientStruct->iGender; 
// 	pDcmPatientStruct->dtBirthDate = pPatientStruct->dtBirthDate; 
// 	pDcmPatientStruct->strPatientComment = CBSTROpt::BSTRToCString(pPatientStruct->bsPatientComment); 
// 	pDcmPatientStruct->strEthnicGroup = CBSTROpt::BSTRToCString(pPatientStruct->bsEthnicGroup);
// 	pDcmPatientStruct->strOtherPatientIDs = CBSTROpt::BSTRToCString(pPatientStruct->bsOtherPatientIDs); 
// 	return TRUE;
// }
// 
// BOOL CDcmPartner::FillDcmStudyStruct(StudyInfoStruct* pStudyStruct, DcmStudyInfoStruct* pDcmStudyStruct)
// {
// 	pDcmStudyStruct->strStudyUID = CBSTROpt::BSTRToCString(pStudyStruct->bsStudyUID);;
// 	pDcmStudyStruct->iStudyID = pStudyStruct->iStudyID;
// 	pDcmStudyStruct->dtStartStudyDateTime = pStudyStruct->dtStartStudyDateTime;
// 	pDcmStudyStruct->dtEndStudyDateTime = pStudyStruct->dtEndStudyDateTime;
// 	pDcmStudyStruct->strReferringPhysicianName = CBSTROpt::BSTRToCString(pStudyStruct->bsReferringPhysicianName);
// 	pDcmStudyStruct->dbPatientSize = pStudyStruct->dbPatientSize;
// 	pDcmStudyStruct->dbPatientWeight = pStudyStruct->dbPatientWeight;
// 	pDcmStudyStruct->strStudyDescription = pStudyStruct->bsStudyDescription;
// 	return TRUE;
// }
// 
// BOOL CDcmPartner::FillDcmSeriesStruct(SeriesInfoStruct* pSeriesStruct, DcmSeriesInfoStruct* pDcmSeriesStruct, DownscaleCriterion enumDownScaleCriterion)
// {
// 	pDcmSeriesStruct->strSeriesUID = CBSTROpt::BSTRToCString(pSeriesStruct->bsSeriesUID);
// 	pDcmSeriesStruct->iSeriesID = pSeriesStruct->iSeriesID; 
// 	pDcmSeriesStruct->iSeriesType = pSeriesStruct->iSeriesType;
// 	pDcmSeriesStruct->iLaterality = pSeriesStruct->iLaterality;
// 	pDcmSeriesStruct->strPerformingPhysicianName = CBSTROpt::BSTRToCString(pSeriesStruct->bsPerformingPhysicianName);
// 	pDcmSeriesStruct->strOperatorName = CBSTROpt::BSTRToCString(pSeriesStruct->bsOperatorName); 
// 	pDcmSeriesStruct->lNumberofImages = pSeriesStruct->lNumberofImages;
// 	pDcmSeriesStruct->shutter.iShutterShape = pSeriesStruct->shutter.iShutterShape;
// 	pDcmSeriesStruct->shutter.lCenterofCircularShutter = pSeriesStruct->shutter.lCenterofCircularShutter;
// 	pDcmSeriesStruct->shutter.lRadiusofCircularShutter = pSeriesStruct->shutter.lRadiusofCircularShutter;
// 	pDcmSeriesStruct->shutter.lShutterLefVerticalEdge = pSeriesStruct->shutter.lShutterLefVerticalEdge;
// 	pDcmSeriesStruct->shutter.lShutterLowerHorizontalEdge = pSeriesStruct->shutter.lShutterLowerHorizontalEdge;
// 	pDcmSeriesStruct->shutter.lShutterRightVerticalEdge = pSeriesStruct->shutter.lShutterRightVerticalEdge;
// 	pDcmSeriesStruct->shutter.lShutterUpperHorizontalEdge = pSeriesStruct->shutter.lShutterUpperHorizontalEdge;
// 	pDcmSeriesStruct->dtReconStartDateTime = pSeriesStruct->dtReconStartDateTime;
// 	pDcmSeriesStruct->dbKV = pSeriesStruct->dbKV; 
// 	pDcmSeriesStruct->dbMA = pSeriesStruct->dbMA; 
// 	pDcmSeriesStruct->dbMS = pSeriesStruct->dbMS; 
// 	pDcmSeriesStruct->dbMAS = pSeriesStruct->dbMAS;
// 	pDcmSeriesStruct->dbRotationAngle = pSeriesStruct->dbRotationAngle;
// 	pDcmSeriesStruct->dbAngulationAngle = pSeriesStruct->dbAngulationAngle;
// 	pDcmSeriesStruct->strContrastAgent = CBSTROpt::BSTRToCString(pSeriesStruct->bsContrastAgent);
// 	pDcmSeriesStruct->dbSourceImageDistance = pSeriesStruct->dbSourceImageDistance;
// 	pDcmSeriesStruct->exposureSeriesInfo.iFrameSpeed = pSeriesStruct->exposureSeriesInfo.iFrameSpeed;
// 	pDcmSeriesStruct->FluoSeriesInfo.iPulseFluoSpeed = pSeriesStruct->fluoSeriesInfo.iPulseFluoSpeed;
// 
// 	// WW and WL
// 	if (m_bProcessed)
// 	{
// 		if (NULL == m_pPostProcessInfo)
// 			return FALSE;
// 
// 		if (m_pPostProcessInfo->bChangeFlag)
// 		{
// 			pDcmSeriesStruct->iWW = m_pPostProcessInfo->iWW;
// 			pDcmSeriesStruct->iWL = m_pPostProcessInfo->iWL;
// 		}
// 		else
// 		{
// 			if (pSeriesStruct->iMaskImageIndex > 0)
// 			{
// 				// Subtract
// 				pDcmSeriesStruct->iWW = 4096;
// 				pDcmSeriesStruct->iWL = 2048;
// 			}
// 			else
// 			{
// 				CBrightContrastConvert BCConvert;
// 				BCConvert.ContrastBrightness2WWWL((int)m_pSeriesInfo->fConstrast,
// 												(int)m_pSeriesInfo->fBrightness,
// 												pDcmSeriesStruct->iWW,
// 												pDcmSeriesStruct->iWL);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		CBrightContrastConvert BCConvert;
// 		BCConvert.ContrastBrightness2WWWL((int)m_pSeriesInfo->fConstrast,
// 										(int)m_pSeriesInfo->fBrightness,
// 										pDcmSeriesStruct->iWW,
// 										pDcmSeriesStruct->iWL);
// 	}
// 
// 	if (enumDownscaleCriterion_512_8_8 == enumDownScaleCriterion)
// 	{
// 		pDcmSeriesStruct->iWW = floor((double)pDcmSeriesStruct->iWW/16 + 0.5);
// 		pDcmSeriesStruct->iWL = floor((double)pDcmSeriesStruct->iWL/16 + 0.5);
// 	}
// 
// 	return TRUE;
// }
// 
// BOOL CDcmPartner::FillDcmConfigStruct(ConfigInfoStruct* pConfigStruct, DcmConfigInfoStruct* pDcmConfigInfoStruct)
// {
// 	pDcmConfigInfoStruct->strManufacture = CBSTROpt::BSTRToCString(pConfigStruct->bsManufacture);
// 	pDcmConfigInfoStruct->strSoftwareVersion = CBSTROpt::BSTRToCString(pConfigStruct->bsSoftwareVersion);
// 	pDcmConfigInfoStruct->strInstitutionName = CBSTROpt::BSTRToCString(pConfigStruct->bsInstitutionName);
// 	pDcmConfigInfoStruct->strStationName = CBSTROpt::BSTRToCString(pConfigStruct->bsStationName);
// 	pDcmConfigInfoStruct->strManufacturerModelName = CBSTROpt::BSTRToCString(pConfigStruct->bsManufacturerModelName);
// 	pDcmConfigInfoStruct->strDeviceSerialNumber = CBSTROpt::BSTRToCString(pConfigStruct->bsDeviceSerialNumber);
// 	pDcmConfigInfoStruct->lColumns = pConfigStruct->lColumns;
// 	pDcmConfigInfoStruct->lRow = pConfigStruct->lRow;
// 	pDcmConfigInfoStruct->iSamplesPerPixel = pConfigStruct->iSamplesPerPixel;
// 	pDcmConfigInfoStruct->iPhotometricInterpretation = pConfigStruct->iPhotometricInterpretation;
// 	pDcmConfigInfoStruct->iBitStored = pConfigStruct->iBitStored;
// 	pDcmConfigInfoStruct->iHighBit = pConfigStruct->iHighBit;
// 	return TRUE;
// }
// 
// BOOL CDcmPartner::GetImageIndex(LPCTSTR szImageFullName, int* piImageIndex)
// {
// 	wchar_t* pStart = wcsrchr(szImageFullName, _T('\\'));
// 	if (NULL == pStart)
// 		return FALSE;
// 
// 	wchar_t* pEnd = wcsrchr(szImageFullName, _T('.'));
// 	if (NULL == pEnd)
// 		return FALSE;
// 	
// 	CString strImageIndex(pStart + 1, pEnd - pStart - 1);
// 	*piImageIndex = wcstol((LPCTSTR)strImageIndex, NULL, 10);
// 	return TRUE;
// }

// BOOL CDcmPartner::GetWWAndWL(DownscaleCriterion enumDownScaleCriterion, unsigned short* pusWW, unsigned short* pusWL)
// {
// 	if (m_bProcessed)
// 	{
// 		if (NULL == m_pPostProcessInfo)
// 			return FALSE;
// 
// 		if (m_pPostProcessInfo->bChangeFlag)
// 		{
// 			*pusWW = m_pPostProcessInfo->iWW;
// 			*pusWL = m_pPostProcessInfo->iWL;
// 		}
// 		else
// 		{
// 			if (m_pSeriesInfo->iMaskImageIndex > 0)
// 			{
// 				// Subtract
// 				*pusWW = 4096;
// 				*pusWL = 2048;
// 			}
// 			else
// 			{
// 				CBrightContrastConvert BCConvert;
// 				int iWW = 0;
// 				int iWL = 0;
// 				BCConvert.ContrastBrightness2WWWL((int)m_pSeriesInfo->fConstrast,
// 												(int)m_pSeriesInfo->fBrightness,
// 												iWW,
// 												iWL);
// 				*pusWW = iWW;
// 				*pusWL = iWL;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		CBrightContrastConvert BCConvert;
// 		int iWW = 0;
// 		int iWL = 0;
// 		BCConvert.ContrastBrightness2WWWL((int)m_pSeriesInfo->fConstrast,
// 										(int)m_pSeriesInfo->fBrightness,
// 										iWW,
// 										iWL);
// 		*pusWW = iWW;
// 		*pusWL = iWL;
// 	}
// 
// 	if (enumDownscaleCriterion_512_8_8 == enumDownScaleCriterion)
// 	{
// 		*pusWW = floor((double)(*pusWW)/16 + 0.5);
// 		*pusWL = floor((double)(*pusWL)/16 + 0.5);
// 	}
// 
// 	return TRUE;
// }


// BOOL CDcmPartner::GetMaskImageName(LPCTSTR szRawImageName, int iImageIndex, CString& strMaskImageName)
// {
// 	wchar_t* p = wcsrchr(szRawImageName, _T('\\'));
// 	if (NULL == p)
// 		return FALSE;
// 
// 	CString strMaskImageFormer(szRawImageName, p - szRawImageName + 1);
// 	CString strMaskImageLater;
// 	strMaskImageLater.Format(_T("%d%s"), iImageIndex, RAW_IMAGE_EXTEND_NAME);
// 
// 	strMaskImageName = strMaskImageFormer + strMaskImageLater;
// 	return TRUE;
// }

// BOOL CDcmPartner::InitProcessSettingBFS(LPCTSTR szSeriesFullName,
// 										INT iImageIndex,
// 										PVOID pRawImage)
// {
// 	CString strTrace;
// 
// 	if (pRawImage)
// 	{
// 		memcpy(m_ProcessingSetting.pRawBuffer, pRawImage, DICOM_RAW_IMAGE_BYTE);
// 	}
// 	else
// 	{
// 		// Read Raw pixel data
// // 		if (!ConnectToRawImageDisk())
// // 		{
// // 			PRINTTRACE_ERROR("ERROR: ConnectToRawImageDisk()")
// // 			return FALSE;
// // 		}
// 
// 		
// 		RunFile	BFSReader;
// 		if (BFSReader.Open(szSeriesFullName, DICOM_RAW_IMAGE_BYTE)) 
// 		{
// 			PRINTTRACE_INFO("Open BFS Sereis Image File to Read Raw pixel data, as follow:")
// 			PRINTTRACE_INFO(szSeriesFullName)
// 
// 			unsigned int iRawImagePhisicalPos = (m_pSeriesInfo->lNumberofImages + iImageIndex + m_pSeriesInfo->iRunStartIndex - 2) % m_pSeriesInfo->lNumberofImages;
// 			if (BFSReader.ReadImage(m_ProcessingSetting.pRawBuffer, iRawImagePhisicalPos))
// 			{
// 				strTrace.Format(_T("Read BFS file, read Pos: %d"), iRawImagePhisicalPos);
// 				PRINTTRACE_INFO(strTrace)
// 
// 				BFSReader.Close();
// // 				CISController::GetInstance()->Enable();
// 			}	
// 			else
// 			{
// 				strTrace.Format(_T("Read BFS file, read Pos: %d"), iRawImagePhisicalPos);
// 				PRINTTRACE_ERROR(strTrace)
// 
// 				BFSReader.Close();
// // 				CISController::GetInstance()->Enable();
// 				return FALSE;
// 			}
// 		}
// 		else
// 		{
// 			PRINTTRACE_INFO("Failed to Open BFS Sereis Image File to Read Raw pixel data, as follow:")
// 			PRINTTRACE_INFO(szSeriesFullName)
// 
// // 			CISController::GetInstance()->Enable();
// 			return FALSE;
// 		}
// 	}
// 
// 	if (m_bMakePSFile)
// 	{
// 
// 		if (m_pPostProcessInfo->bChangeFlag)
// 		{
// 			m_ProcessingSetting.bLogLUT = m_pPostProcessInfo->bLogLUT;
// 
// 			// 判断是否做剪影
// 			if (m_pPostProcessInfo->bSubtract && m_pPostProcessInfo->iMaskIndex < m_pSeriesInfo->lNumberofImages)
// 			{
// 				m_ProcessingSetting.bSubtract = TRUE;
// 				PRINTTRACE_INFO("Subtract on!")
// 			}
// 			else
// 			{
// 				m_ProcessingSetting.bSubtract = FALSE;
// 			}
// 			
// 			if (m_ProcessingSetting.bSubtract)
// 			{
// 				PRINTTRACE_INFO("Subtract on!")
// 				m_ProcessingSetting.bLandMarking = m_pPostProcessInfo->bLandMarking;
// 
// 				m_ProcessingSetting.bPixelShift = m_pPostProcessInfo->bPixelShift;
// // 				if (m_ProcessingSetting.bPixelShift)
// // 				{
// // 					PRINTTRACE_INFO("pixelshift on!")
// 					m_ProcessingSetting.iPixelShift_X = m_pPostProcessInfo->iPixelShift_X;
// 					m_ProcessingSetting.iPixelShift_Y = m_pPostProcessInfo->iPixelShift_Y;
// // 				}
// 
// 				m_ProcessingSetting.iMaskIndex = m_pPostProcessInfo->iMaskIndex;
// 	
// 				// Read Mask pixel data
// // 				if (!ConnectToRawImageDisk())
// // 				{
// // 					PRINTTRACE_ERROR("ERROR: ConnectToRawImageDisk()")
// // 					return FALSE;
// // 				}
// 				
// 				RunFile	BFSReader;
// 				if (BFSReader.Open(szSeriesFullName, DICOM_RAW_IMAGE_BYTE)) 
// 				{
// 					PRINTTRACE_INFO("Open BFS Sereis Image File to Read Mask pixel data, as follow:")
// 					PRINTTRACE_INFO(szSeriesFullName)
// 
// // 					unsigned int iMaskImagePhisicalPos = (m_pSeriesInfo->lNumberofImages + m_pPostProcessInfo->iMaskIndex + m_pSeriesInfo->iRunStartIndex - 2) % m_pSeriesInfo->lNumberofImages;
// 					if (BFSReader.ReadImage(m_ProcessingSetting.pMask, m_ProcessingSetting.iMaskIndex))
// 					{
// 						strTrace.Format(_T("Read BFS file, read Pos: %d"), m_ProcessingSetting.iMaskIndex);
// 						PRINTTRACE_INFO(strTrace)
// 
// 						BFSReader.Close();
// // 						CISController::GetInstance()->Enable();
// 					}	
// 					else
// 					{
// 						strTrace.Format(_T("Read BFS file, read Pos: %d"), m_ProcessingSetting.iMaskIndex);
// 						PRINTTRACE_ERROR(strTrace)
// 
// 						BFSReader.Close();
// // 						CISController::GetInstance()->Enable();
// 						return FALSE;
// 					}
// 				}
// 				else
// 				{
// 					PRINTTRACE_INFO("Failed to Open BFS Sereis Image File to Read Mask pixel data, as follow:")
// 					PRINTTRACE_INFO(szSeriesFullName)
// 
// // 					CISController::GetInstance()->Enable();
// 					return FALSE;
// 				}
// 
// 				m_ProcessingSetting.fSubGain = m_pPostProcessInfo->fSubGain;
// 				m_ProcessingSetting.iSubOffset = m_pPostProcessInfo->iSubOffset;
// 				m_ProcessingSetting.fLandmarkingGain = m_pPostProcessInfo->fLandmarkingGain;
// 			}
// 
// 			m_ProcessingSetting.iEdgeenhancmentLevel = m_pPostProcessInfo->iEdgeenhancmentLevel;
// 
// 			m_ProcessingSetting.iWW = m_pPostProcessInfo->iWW;
// 			m_ProcessingSetting.iWL = m_pPostProcessInfo->iWL;
// 			m_ProcessingSetting.iRotation = m_pPostProcessInfo->iRotation;
// 			m_ProcessingSetting.bInverse = m_pPostProcessInfo->bInverse;
// 			m_ProcessingSetting.fZoomFactor = m_pPostProcessInfo->fZoomFactor;
// 			m_ProcessingSetting.bShutter = m_pPostProcessInfo->bShutter;
// 
// 			m_ProcessingSetting.iImageHeight = m_pConfigInfo->lColumns;
// 			m_ProcessingSetting.iImageWidth = m_pConfigInfo->lRow;
// 			m_ProcessingSetting.iPixelDepth = 12;
// 			m_ProcessingSetting.iMaxPixelValue = 4095;
// 
// 			m_ProcessingSetting.iOffsetX = m_pPostProcessInfo->iOffsetX;
// 			m_ProcessingSetting.iOffsetY = m_pPostProcessInfo->iOffsetY;
// 
// 			m_ProcessingSetting.bOverlay = m_pPostProcessInfo->bOverlay;
// 
// 			m_ProcessingSetting.iElectroShutter_Left = m_pPostProcessInfo->iElectroShutter_Left;
// 			m_ProcessingSetting.iElectroShutter_Right = m_pPostProcessInfo->iElectroShutter_Right;
// 			m_ProcessingSetting.iElectroShutter_Top = m_pPostProcessInfo->iElectroShutter_Top;
// 			m_ProcessingSetting.iElectroShutter_Bottom = m_pPostProcessInfo->iElectroShutter_Bottom;
// 		}
// 		else
// 		{
// 			// 未经过Reviewing模块后处理
// 			m_ProcessingSetting.bLogLUT = FALSE;
// 
// 			if (m_pSeriesInfo->iMaskImageIndex > 0 &&
// 				m_pSeriesInfo->iMaskImageIndex <= m_pSeriesInfo->lNumberofImages)
// 			{
// 				PRINTTRACE_INFO("Subtract on!")
// 				m_ProcessingSetting.bSubtract = TRUE;
// 			}
// 			else
// 			{
// 				m_ProcessingSetting.bSubtract = FALSE;
// 			}
// 
// 			m_ProcessingSetting.fLandmarkingGain = 0.1f;
// 			m_ProcessingSetting.bLandMarking =TRUE;
// 			m_ProcessingSetting.bPixelShift = TRUE;
// 			m_ProcessingSetting.iPixelShift_X =0;
// 			m_ProcessingSetting.iPixelShift_Y =0;
// 
// 			m_ProcessingSetting.iMaskIndex = m_pSeriesInfo->iMaskImageIndex;
// 			if (m_ProcessingSetting.bSubtract)
// 			{
// 				m_ProcessingSetting.fSubGain = m_pSeriesInfo->fConstrast;
// 				m_ProcessingSetting.iSubOffset = 4095*m_pSeriesInfo->fBrightness/2.0;
// 				m_ProcessingSetting.iWW = 4096;
// 				m_ProcessingSetting.iWL = 2048;
// 
// 				// Read Mask pixel data
// // 				if (!ConnectToRawImageDisk())
// // 				{
// // 					PRINTTRACE_ERROR("ERROR: ConnectToRawImageDisk()")
// // 					return FALSE;
// // 				}
// 
// 				
// 				RunFile	BFSReader;
// 				if (BFSReader.Open(szSeriesFullName, DICOM_RAW_IMAGE_BYTE)) 
// 				{
// 					PRINTTRACE_INFO("Open BFS Sereis Image File to Read Mask pixel data, as follow:")
// 					PRINTTRACE_INFO(szSeriesFullName)
// 
// 					unsigned int iMaskImagePhisicalPos = (m_pSeriesInfo->lNumberofImages + m_pPostProcessInfo->iMaskIndex + m_pSeriesInfo->iRunStartIndex - 2) % m_pSeriesInfo->lNumberofImages;
// 					if (BFSReader.ReadImage(m_ProcessingSetting.pMask, iMaskImagePhisicalPos))
// 					{
// 						strTrace.Format(_T("Read BFS file, read Pos: %d"), iMaskImagePhisicalPos);
// 						PRINTTRACE_INFO(strTrace)
// 
// 						BFSReader.Close();
// // 						CISController::GetInstance()->Enable();
// 					}	
// 					else
// 					{
// 						strTrace.Format(_T("Read BFS file, read Pos: %d"), iMaskImagePhisicalPos);
// 						PRINTTRACE_ERROR(strTrace)
// 
// 						BFSReader.Close();
// // 						CISController::GetInstance()->Enable();
// 						return FALSE;
// 					}
// 				}
// 				else
// 				{
// 					PRINTTRACE_INFO("Failed to Open BFS Sereis Image File to Read Mask pixel data, as follow:")
// 					PRINTTRACE_INFO(szSeriesFullName)
// 
// // 					CISController::GetInstance()->Enable();
// 					return FALSE;
// 				}
// 			}
// 			else
// 			{
// 				m_ProcessingSetting.fSubGain = 1.0;
// 				m_ProcessingSetting.iSubOffset = 2048;
// 				CBrightContrastConvert BCConvert;
// 				//m_ProcessingSetting.iWW = BCConvert.ContrastToWindowWidth((int)m_pSeriesInfo->fConstrast);
// 				//m_ProcessingSetting.iWL = BCConvert.BrightNessToWindowCenter((int)m_pSeriesInfo->fBrightness);
// 				BCConvert.ContrastBrightness2WWWL((int)m_pSeriesInfo->fConstrast,
// 												(int)m_pSeriesInfo->fBrightness,
// 												m_ProcessingSetting.iWW,
// 												m_ProcessingSetting.iWL);
// 			}
// 
// 			m_ProcessingSetting.iRotation = m_iImageRotationArray[m_pSeriesInfo->iNoseOrientation][m_pSeriesInfo->iLegsOrientation][m_pSeriesInfo->iLArmOrientation];
// 
// 			m_ProcessingSetting.bInverse = m_pSeriesInfo->bVideoInvert;
// 			m_ProcessingSetting.fZoomFactor = 1.0;
// 			m_ProcessingSetting.bShutter = TRUE;
// 
// 			m_ProcessingSetting.iImageHeight = m_pConfigInfo->lColumns;
// 			m_ProcessingSetting.iImageWidth = m_pConfigInfo->lRow;
// 			m_ProcessingSetting.iPixelDepth = 12;
// 			m_ProcessingSetting.iMaxPixelValue = 4095;
// 			m_ProcessingSetting.iEdgeenhancmentLevel = m_pSeriesInfo->iEnhencement;
// 
// 			m_ProcessingSetting.iOffsetX = 0;
// 			m_ProcessingSetting.iOffsetY = 0;
// 
// 			m_ProcessingSetting.bOverlay = TRUE;
// 
// 			m_ProcessingSetting.iElectroShutter_Left = 0;
// 			m_ProcessingSetting.iElectroShutter_Right = 1024;
// 			m_ProcessingSetting.iElectroShutter_Top = 0;
// 			m_ProcessingSetting.iElectroShutter_Bottom = 1024;
// 		}
// 	}
// 
// 	// Write the para into trace
// 	CString strTraceSeriesUID = CBSTROpt::BSTRToCString(m_pPostProcessInfo->bsSeriesUID);
// 	strTrace.Format(_T("The PostProcessInfo got from DB:\r\n \
// 					bsSeriesUID: %s,\r\n \
// 					bChangeFlag: %d,\r\n \
// 					bLogLUT: %d,\r\n \
// 					bSubtract: %d,\r\n \
// 					bLandMarking: %d,\r\n \
// 					bPixelShift: %d,\r\n \
// 					iPixelShift_X: %d,\r\n \
// 					iPixelShift_Y: %d,\r\n \
// 					iMaskIndex: %d,\r\n \
// 					fSubGain: %f,\r\n \
// 					iSubOffset: %d,\r\n \
// 					fLandmarkingGain: %f,\r\n \
// 					iEdgeenhancmentLevel: %d,\r\n \
// 					iWW: %d,\r\n \
// 					iWL: %d,\r\n \
// 					iRotation: %d,\r\n \
// 					bInverse: %d,\r\n \
// 					fZoomFactor: %f,\r\n \
// 					bShutter: %d,\r\n \
// 					iOffsetX: %d,\r\n \
// 					iOffsetY: %d, \r\n \
// 					bOverlay: %d"),
// 					strTraceSeriesUID,
// 					m_pPostProcessInfo->bChangeFlag,
// 					m_pPostProcessInfo->bLogLUT, 
// 					m_pPostProcessInfo->bSubtract, 
// 					m_pPostProcessInfo->bLandMarking, 
// 					m_pPostProcessInfo->bPixelShift, 
// 					m_pPostProcessInfo->iPixelShift_X, 
// 					m_pPostProcessInfo->iPixelShift_Y, 
// 					m_pPostProcessInfo->iMaskIndex, 
// 					m_pPostProcessInfo->fSubGain, 
// 					m_pPostProcessInfo->iSubOffset, 
// 					m_pPostProcessInfo->fLandmarkingGain, 
// 					m_pPostProcessInfo->iEdgeenhancmentLevel, 
// 					m_pPostProcessInfo->iWW, 
// 					m_pPostProcessInfo->iWL, 
// 					m_pPostProcessInfo->iRotation, 
// 					m_pPostProcessInfo->bInverse, 
// 					m_pPostProcessInfo->fZoomFactor, 
// 					m_pPostProcessInfo->bShutter,
// 					m_pPostProcessInfo->iOffsetX,
// 					m_pPostProcessInfo->iOffsetY,
// 					m_pPostProcessInfo->bOverlay);
// 	PRINTTRACE_INFO(strTrace)
// 
// 	strTrace.Format(_T("The para that will be input to imagetool:\r\n \
// 					bLogLUT: %d,\r\n \
// 					bSubtract: %d,\r\n \
// 					bLandMarking: %d,\r\n \
// 					bPixelShift: %d,\r\n \
// 					iPixelShift_X: %d,\r\n \
// 					iPixelShift_Y: %d,\r\n \
// 					iMaskIndex: %d,\r\n \
// 					fSubGain: %f,\r\n \
// 					iSubOffset: %d,\r\n \
// 					fLandmarkingGain: %f,\r\n \
// 					iEdgeenhancmentLevel: %d,\r\n \
// 					iWW: %d,\r\n \
// 					iWL: %d,\r\n \
// 					iRotation: %d,\r\n \
// 					bInverse: %d,\r\n \
// 					fZoomFactor: %f,\r\n \
// 					bShutter: %d,\r\n \
// 					iImageHeight: %d,\r\n \
// 					iImageWidth: %d,\r\n \
// 					iPixelDepth: %d,\r\n \
// 					iMaxPixelValue: %d,\r\n \
// 					iOffsetX: %d,\r\n \
// 					iOffsetY: %d, \r\n \
// 					bOverlay: %d"),
// 					m_ProcessingSetting.bLogLUT, 
// 					m_ProcessingSetting.bSubtract, 
// 					m_ProcessingSetting.bLandMarking, 
// 					m_ProcessingSetting.bPixelShift, 
// 					m_ProcessingSetting.iPixelShift_X, 
// 					m_ProcessingSetting.iPixelShift_Y, 
// 					m_ProcessingSetting.iMaskIndex, 
// 					m_ProcessingSetting.fSubGain, 
// 					m_ProcessingSetting.iSubOffset, 
// 					m_ProcessingSetting.fLandmarkingGain, 
// 					m_ProcessingSetting.iEdgeenhancmentLevel, 
// 					m_ProcessingSetting.iWW, 
// 					m_ProcessingSetting.iWL, 
// 					m_ProcessingSetting.iRotation, 
// 					m_ProcessingSetting.bInverse, 
// 					m_ProcessingSetting.fZoomFactor, 
// 					m_ProcessingSetting.bShutter, 
// 					m_ProcessingSetting.iImageHeight, 
// 					m_ProcessingSetting.iImageWidth, 
// 					m_ProcessingSetting.iPixelDepth, 
// 					m_ProcessingSetting.iMaxPixelValue,
// 					m_ProcessingSetting.iOffsetX,
// 					m_ProcessingSetting.iOffsetY,
// 					m_ProcessingSetting.bOverlay);
// 	PRINTTRACE_INFO(strTrace)
// 
// 	
// 	if (m_bMakePSFile)
// 	{
// 		CString strAnnoFilePath;
// 		GetAnnoFileNameBFS(szSeriesFullName, iImageIndex, strAnnoFilePath);
// 
// 		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, strAnnoFilePath, -1, (char*)m_ProcessingSetting.szAnnoFilePath, MAX_PATH, NULL, NULL ); 
// 	}
// 	return TRUE;
// }
// 
void CDcmPartner::GetOriginalPSFileName(CString& strPSFile)
{
	CString strPostImage;
	GetImageFileName(FALSE, strPostImage);
	int iPos = strPostImage.ReverseFind(_T('.'));
	strPSFile = strPostImage.Left(iPos);
	strPSFile += DICOM_DCM_PS_FILE_EXTEND_NAME;
}

BOOL CDcmPartner::CheckTaskDir(LPCTSTR szTaskDir, BOOL bClearDir)
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString strTrace;

	LPCTSTR szAim = wcschr(szTaskDir, _T('\\'));
	CString strRoot(szTaskDir, szAim - szTaskDir + 1);

	// Is root dir exist?
	if (DRIVE_FIXED == GetDriveType(strRoot))
	{
		while (TRUE)
		{
			if (_T('\0') == *(szAim + 1))
				return TRUE;

			szAim = wcschr(szAim + 1, _T('\\'));
			if (szAim)
			{
				CString strDir(szTaskDir, szAim - szTaskDir);
				hFind = FindFirstFile(strDir, &fd);
				if (((INVALID_HANDLE_VALUE != hFind)     
					&& (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)))
				{
					// dir exist, so continue
					FindClose(hFind);
					hFind = INVALID_HANDLE_VALUE;
					continue;
				}
				else
				{
					// dir is not exist
					FindClose(hFind);
					hFind = INVALID_HANDLE_VALUE;
					if (CreateDirectory(strDir, NULL))
					{
						// Create dir succeed, so continue
						continue;
					}
					else
					{
						return FALSE;
					}
				}
			}
			else
			{
				hFind = FindFirstFile(szTaskDir, &fd);
				if (((INVALID_HANDLE_VALUE != hFind)     
					&& (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)))
				{
					FindClose(hFind);
					hFind = INVALID_HANDLE_VALUE;

					if (bClearDir)
					{
						// dir exist, so clear it
						if (ClearTaskDir(szTaskDir))
						{
							strTrace = _T("Succeed to Clear Task Dir : ");
							strTrace += szTaskDir;
							PRINTTRACE_INFO(strTrace)
							return TRUE;
						}
						else
						{
							strTrace = _T("Failed to Clear Task Dir : ");
							strTrace += szTaskDir;
							PRINTTRACE_ERROR(strTrace)
							return FALSE;
						}
					}
					else
					{
						return TRUE;
					}
				}
				else
				{
					FindClose(hFind);
					hFind = INVALID_HANDLE_VALUE;

					// dir is not exist
					if (CreateDirectory(szTaskDir, NULL))
					{
						// Create dir succeed
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
			}
		}
	}
	else
		return FALSE;

}

BOOL CDcmPartner::ClearTaskDir(LPCTSTR szTaskDir, BOOL bDeleteDir)
{
	if (NULL == szTaskDir)
		return FALSE;

	WIN32_FIND_DATA fd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString strTrace;

	BOOL bRet = TRUE;

	CString strTaskDir = szTaskDir;
	hFind = FindFirstFile(strTaskDir + _T("\\*"), &fd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return FALSE;
	}

	do{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!wcscmp(fd.cFileName, _T(".")) || !wcscmp(fd.cFileName, _T("..")))
				continue;
			else
			{
				if (ClearTaskDir(strTaskDir + _T("\\") + fd.cFileName, TRUE))
				{
					strTrace = _T("ClearTaskDir : ");
					strTrace += strTaskDir + _T("\\") + fd.cFileName;
					PRINTTRACE_INFO(strTrace)
				}
				else
				{
					bRet = FALSE;
					strTrace = _T("Failed to ClearTaskDir : ");
					strTrace += strTaskDir + _T("\\") + fd.cFileName;
					PRINTTRACE_ERROR(strTrace)
					break;
				}
			}
		}
		else
		{
			// It's File
			if (DeleteFile(strTaskDir + _T("\\") + fd.cFileName))
			{
				strTrace = _T("Delete file : ");
				strTrace += strTaskDir + _T("\\") + fd.cFileName;
				PRINTTRACE_INFO(strTrace)
			}
			else
			{
				bRet = FALSE;
				strTrace = _T("Failed to Delete file : ");
				strTrace += strTaskDir + _T("\\") + fd.cFileName;
				PRINTTRACE_ERROR(strTrace)
				break;
			}
		}
	}while (FindNextFile(hFind, &fd));

	FindClose(hFind);

	if (bRet && ERROR_NO_MORE_FILES == GetLastError())
	{
		if (bDeleteDir)
		{
			if (RemoveDirectory(strTaskDir))
			{
				strTrace = _T("Delete Dir : ");
				strTrace += strTaskDir;
				PRINTTRACE_INFO(strTrace)
				return TRUE;
			}
			else
			{
				strTrace = _T("Failed to Delete Dir : ");
				strTrace += strTaskDir;
				PRINTTRACE_ERROR(strTrace)
				return FALSE;
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}


DWORD CDcmPartner::GetEstimatedContentSize(DWORD dwImageCount, BOOL bDICOM, DownscaleCriterion enumDownscaleCriterion, BOOL bMultiFrame, BOOL bBMP, BOOL bJPEG, __int64 i64AdditionalSize)
{
	DWORD dwEstimatedSizeMb = 0;
	__int64 i64SizeByte = 0;
	
	__int64 i64ImageCount = dwImageCount;
	__int64 i64ImagesSizeBytes = i64ImageCount * DICOM_RAW_IMAGE_BYTE;

	if (bDICOM)
	{
		if (enumDownscaleCriterion_1024_12_16 == enumDownscaleCriterion)
		{
			if (bMultiFrame)
			{
				i64SizeByte += i64ImagesSizeBytes / IMAGE_COMPRESS_RATE_1024_MF;
			}
			else
			{
				i64SizeByte += i64ImagesSizeBytes / IMAGE_COMPRESS_RATE_1024_SF;
			}
		}
		else
		{
			if (bMultiFrame)
			{
				i64SizeByte += i64ImagesSizeBytes / IMAGE_COMPRESS_RATE_512_MF;
			}
			else
			{
				i64SizeByte += i64ImagesSizeBytes / IMAGE_COMPRESS_RATE_512_SF;
			}
		}
	}

	if (bBMP)
	{
		i64SizeByte += i64ImagesSizeBytes / IMAGE_COMPRESS_RATE_BMP;
	}

	if (bJPEG)
	{
		i64SizeByte += i64ImagesSizeBytes / IMAGE_COMPRESS_RATE_JPEG;
	}

	i64SizeByte += i64AdditionalSize;

	dwEstimatedSizeMb = (DWORD)ceil(i64SizeByte / (double)(1024*1024));

	return dwEstimatedSizeMb;
}

BOOL CDcmPartner::CheckDiskSpace()
{
	return TRUE;
}

DWORD CDcmPartner::GetEstimatedDiskSpaceNeeded(DWORD dwImageCount, BOOL bDICOM, DownscaleCriterion enumDownscaleCriterion, BOOL bMultiFrame, BOOL bBMP, BOOL bJPEG, __int64 i64AdditionalSize)
{
	DWORD dwSpaceNeeded = 0;
	__int64 i64TempFileSize = 0;
	__int64 i64ImageCount = dwImageCount;
	
	dwSpaceNeeded = GetEstimatedContentSize(dwImageCount, bDICOM, enumDownscaleCriterion, bMultiFrame, bBMP, bJPEG, 0);

	// Get Temp File Size
// 	if (bDICOM)
// 	{
// 		if ((bBMP || bJPEG) && (bMultiFrame || (enumDownscaleCriterion_512_8_8 == enumDownscaleCriterion)))
// 		{
// 			i64TempFileSize = i64ImageCount * DICOM_RAW_IMAGE_BYTE;
// 		}
// 	}
// 	else
// 	{
// 		if (bBMP || bJPEG)
// 		{
// 			i64TempFileSize = i64ImageCount * DICOM_RAW_IMAGE_BYTE;
// 		}
// 	}
	
	return dwSpaceNeeded + (DWORD)ceil(i64TempFileSize / (double)(1024*1024));
}

void CDcmPartner::GetDcmImageDir(CString& strGetDcmImageDir)
{
	CString strStudyDir;
	CString strSeriesDir;
	strStudyDir.Format(_T("\\%s%03d"), DICOM_DCM_STUDY_DIR_PREFIX, m_pStudyInfo->iStudyID);
	strSeriesDir.Format(_T("\\%s%02d"), DICOM_DCM_SERIES_DIR_PREFIX, m_pSeriesInfo->iSeriesID);

	strGetDcmImageDir = m_szStorePath;
	strGetDcmImageDir += DICOM_IMAGE_WORK_DIR;
	strGetDcmImageDir += GetPatientDir();
	strGetDcmImageDir += DICOM_DCM_DIR;
	strGetDcmImageDir += strStudyDir;
	strGetDcmImageDir += strSeriesDir;
}

CString CDcmPartner::GetPatientDir()
{
	CString strPatientID = CBSTROpt::BSTRToCString(m_pPatientInfo->bsPatientID);
	
	for (int i = 0; i < m_vtrPatientDir.size(); i++)
	{
		if (!strPatientID.Compare(m_vtrPatientDir[i].strPatientID))
		{
			return m_vtrPatientDir[i].strPatientDir;
		}
	}

	//<< 新的患者ID，故创建其患者Dir
	PatientDirStruct pds;
	pds.strPatientID = strPatientID;
	pds.strPatientDir.Format(_T("\\%s%07d"), DICOM_DCM_PATIENT_DIR_PREFIX, m_vtrPatientDir.size()+1);


	m_vtrPatientDir.push_back(pds);

	return pds.strPatientDir;
}

void CDcmPartner::GetBMPDir(CString& strBMPDir)
{	
	strBMPDir = m_szStorePath;
	strBMPDir += DICOM_IMAGE_WORK_DIR;
	strBMPDir += GetPatientDir();
	strBMPDir += DICOM_BMP_DIR;
}

void CDcmPartner::GetJPEGDir(CString& strJPEGDir)
{	
	strJPEGDir = m_szStorePath;
	strJPEGDir += DICOM_IMAGE_WORK_DIR;
	strJPEGDir += GetPatientDir();
	strJPEGDir += DICOM_JPEG_DIR;
}

void CDcmPartner::GetBMPFullName(LPCTSTR szDir, CString& strBMPFullName)
{
	CString strStudyID;
	strStudyID.Format(_T("%03d_"), m_pStudyInfo->iStudyID);

	CString strSeriesID;
	strSeriesID.Format(_T("%03d_"), m_pSeriesInfo->iSeriesID);

	CString strImageIndex;
	strImageIndex.Format(_T("%04d"), m_pImageInfo->iImageID);

	strBMPFullName = szDir;
	strBMPFullName += _T("\\");

// 	if (enumXA == m_enumType)
// 		strBMPFullName += DICOM_XA_BMP_NAME_PREFIX;
// 	else
// 		strBMPFullName += DICOM_SC_BMP_NAME_PREFIX;

	strBMPFullName += strStudyID + strSeriesID + strImageIndex + DICOM_BMP_EXTEND_NAME;

}

void CDcmPartner::GetJPEGFullName(LPCTSTR szDir, CString& strJPEGFullName)
{
	CString strStudyID;
	strStudyID.Format(_T("%03d_"), m_pStudyInfo->iStudyID);

	CString strSeriesID;
	strSeriesID.Format(_T("%03d_"), m_pSeriesInfo->iSeriesID);

	CString strImageIndex;
	strImageIndex.Format(_T("%04d"), m_pImageInfo->iImageID);

	strJPEGFullName = szDir;
	strJPEGFullName += _T("\\");

// 	if (enumXA == m_enumType)
// 		strJPEGFullName += DICOM_XA_JPEG_NAME_PREFIX;
// 	else
// 		strJPEGFullName += DICOM_SC_JPEG_NAME_PREFIX;

	strJPEGFullName += strStudyID + strSeriesID + strImageIndex + DICOM_JPEG_EXTEND_NAME;
}

void CDcmPartner::GetDcmImageFullName(LPCTSTR szDir, BOOL bRaw, CString& strDcmImageFullName)
{
	CString strDir = szDir;
	CString strImageName;

	if (bRaw)
	{
		strImageName.Format(_T("%c%07d"), DICOM_DCM_RAW_IMAGE_PREFIX, m_pImageInfo->iImageID);
	}
	else
	{
		strImageName.Format(_T("%c%07d"), DICOM_DCM_PROC_IMAGE_PREFIX, m_pImageInfo->iImageID);
	}

	strDcmImageFullName = strDir + _T("\\") + strImageName;
}

void CDcmPartner::GetDcmPSFullName(LPCTSTR szDcm, CString& strDcmPSFullName)
{
	strDcmPSFullName = szDcm;
	strDcmPSFullName += DICOM_DCM_PS_FILE_EXTEND_NAME;
}

BOOL CDcmPartner::ReadImageData(BOOL bRaw)
{
	CString strTrace;

	CString strFileName;
	if (!GetImageFileName(bRaw, strFileName))
	{
		PRINTTRACE_ERROR("GetImageFileName(bRaw, strFileName)")
		return FALSE;
	}

	if (!IsFileExist(strFileName))
	{
		strTrace.Format(_T("IsFileExist(strFileName), %s"), strFileName);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	CDcmParser aDcmParser;
	if (!aDcmParser.LoadDXDcmFile(strFileName))
	{
		strTrace.Format(_T("aDcmParser.LoadDXDcmFile(strFileName), %s"), strFileName);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	if (NULL != m_pDcmPixelData)
	{
		delete [] m_pDcmPixelData;
		m_pDcmPixelData = NULL;
	}

	if (!aDcmParser.GetPixelData(m_pDcmPixelData))
	{
		strTrace.Format(_T("aDcmParser.LoadDXDcmFile(strFileName), %s"), strFileName);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	return TRUE;
// 	HANDLE hFile = ::CreateFile(strFileName,           // 
// 								GENERIC_READ,              // open for reading 
// 								FILE_SHARE_READ,           // share for reading 
// 								NULL,                      // no security 
// 								OPEN_EXISTING,             // existing file only 
// 								FILE_ATTRIBUTE_NORMAL,     // normal file 
// 								NULL);                     // no attr. template 
//  
// 	if (hFile == INVALID_HANDLE_VALUE) 
// 	{
// 		strTrace.Format(_T("::CreateFile(strFileName, ...), strFileName: %s"), strFileName);
// 		PRINTTRACE_ERROR(strTrace);
// 		return FALSE;
// 	}		
// 
// 	DWORD dwBytesRead = 0;
// 	if (::ReadFile(hFile, m_RawDataBuffer.GetBuffer(), DICOM_RAW_IMAGE_BYTE, &dwBytesRead, NULL))
// 	{
// 		if (DICOM_RAW_IMAGE_BYTE != dwBytesRead)
// 		{
// 			CloseHandle(hFile);
// 			strTrace.Format(_T("DICOM_RAW_IMAGE_BYTE != dwBytesRead, dwBytesRead=%d"), dwBytesRead);
// 			PRINTTRACE_ERROR(strTrace)
// 			return FALSE;
// 		}
// 		else
// 		{
// 			CloseHandle(hFile);
// 			return TRUE;
// 		}
// 	}
// 	else
// 	{
// 		
// 		CloseHandle(hFile);
// 		strTrace.Format(_T("::ReadFile(strFileName, ...), strFileName: %s"), strFileName);
// 		PRINTTRACE_ERROR(strTrace);
// 		return FALSE;
// 	}
}

BOOL CDcmPartner::GetImageFileName(BOOL bRaw, CString& strFile)
{
	strFile = IS_PATH;
	if (bRaw)
	{
		strFile += CBSTROpt::BSTRToCString(m_pImageInfo->bsImageFilePath);
	}
	else
	{
		strFile += CBSTROpt::BSTRToCString(m_pPostProcessInfo->bsProcessedImageFilePath);
	}

	return TRUE;
}

// BOOL CDcmPartner::ConnectToRawImageDisk()
// {
// 	while (TRUE)
// 	{
// 		BOOL bConnected = FALSE;
// 		if ((CISController::GetInstance())->ConnectDisk(&bConnected))
// 		{
// 			// Is Connected?
// 			if (bConnected)
// 			{
// 				PRINTTRACE_INFO("TRUE == (CISController::GetInstance())->ConnectDisk(&bConnected) and TRUE == bConnected")
// 				PRINTTRACE_INFO("TRUE == bConnected")
// 				return TRUE;
// 			}
// 			else
// 			{
// 				PRINTTRACE_INFO("TRUE == (CISController::GetInstance())->ConnectDisk(&bConnected) But TRUE != bConnected")
// 				PRINTTRACE_INFO("TRUE != bConnected")
// 				Sleep(IS_CONNECT_RAW_IMAGE_DISK_WAIT_TIME);
// 				continue;
// 			}
// 		}
// 		else
// 		{
// 			// error occured
// 			PRINTTRACE_ERROR("TRUE != (CISController::GetInstance())->ConnectDisk(&bConnected)")
// 			return FALSE;
// 		}
// 	}
// }
// 
// void CDcmPartner::EnableDisconnectToRawImageDisk()
// {
// 	CISController::GetInstance()->Enable();
// }
// 
// BOOL CDcmPartner::DisConnectToRawImageDisk()
// {
// 	CISController::GetInstance()->Enable();	
// 	if (CISController::GetInstance()->DisConnectDisk())
// 	{
// 		PRINTTRACE_INFO("CISController::GetInstance()->DisConnectDisk()")
// 		return TRUE;
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("CISController::GetInstance()->DisConnectDisk()")
// 		return FALSE;
// 	}
// }



void CDcmPartner::NotifyProgress()
{
	if (NULL != m_pJob)
	{
		//<< 仅供刻录预处理，压缩进度为前30%
		m_pJob->SetProgress(enumJobProgressUsing_CompletedTotal, m_dwHandledImagesCount * 3, m_pJob->vtrImages.size() * m_dwPhaseNum * 10);
	}
}

void CDcmPartner::GetLanguageSetting()
{
	TCHAR cCurrentSystemDirectory[MAX_PATH]; 
	GetModuleFileName(NULL, cCurrentSystemDirectory, MAX_PATH);	//获得应用程序的路径(并且带应用程序文件名)
	CString strApplicationName = cCurrentSystemDirectory;

	CString strApplicationPath = strApplicationName.Left(strApplicationName.ReverseFind('\\'));	//获得不带应用程序文件名的应用程序路径(去掉应用程序文件名)	

	CString strINIFileName = strApplicationPath + UISCHEME_INI_FILE;

	int iValue = GetPrivateProfileIntW(_T("LANGUAGE_TRANSLATE"),
								     _T("IsTranslateLanguage"),
								     0,
								     strINIFileName);

	if (0 == iValue)
		m_bChineseLang = FALSE;
	else
		m_bChineseLang = TRUE;
}

BOOL CDcmPartner::IsFileExist(LPCTSTR szFile)
{
	CString strTrace;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(szFile, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		strTrace.Format(_T("FindFirstFile(), szFile: %s"), szFile);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
	else
	{
		FindClose(hFind);
		return TRUE;
	}
}
