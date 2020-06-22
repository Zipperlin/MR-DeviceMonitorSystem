/* Time: <@(#)DcmPartner.h   2009-3-5 - 10:37:11   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DcmPartner.h
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
 *	1	2009-3-5 - 10:37:11		FanZF	Creation
 *
 *********************************************************************
 */

// DcmPartner.h: interface for the CDcmPartner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCMPARTNER_H__6F5EA875_7F0A_43BD_A7EC_281027D9FE42__INCLUDED_)
#define AFX_DCMPARTNER_H__6F5EA875_7F0A_43BD_A7EC_281027D9FE42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "JobQueue.h"
#include "DBController.h"

class CDcmPartner : public NSubject,
					public CDcmGen
{
public:
	
	
	CDcmPartner();
	virtual ~CDcmPartner();


	BOOL Init();
	void UnInit();


	// For Naming of Images
	void SetImageType(BOOL bRawDcm, BOOL bProcessedDcm);
	void SetPSFile(BOOL bPS);	//<< Only for Processed Dcm
	void SetDcmDir(BOOL bDcmDir);

	BOOL ConvertBFS(PAJob* pJob,
					LPCTSTR szStorePath,
					vector<CString>* pvtrRawDcmImages = NULL,
					vector<CString>* pvtrProcDcmImages = NULL);


	BOOL CheckTaskDir(LPCTSTR szTaskDir, BOOL bClearDir = FALSE);
	BOOL ClearTaskDir(LPCTSTR szTaskDir, BOOL bDeleteDir = FALSE);

	// Estimate Content size
	DWORD GetEstimatedContentSize(DWORD dwImageCount, BOOL bDICOM, DownscaleCriterion enumDownscaleCriterion, BOOL bMultiFrame, BOOL bBMP, BOOL bJPEG, __int64 i64AdditionalSize = 0);


private:
	BOOL ConvertImages();
// 	BOOL ConvertMFImagesBFS();

	BOOL ConvertOneImageToDXImage(BOOL bRaw);
// 	BOOL ConvertOneXAImage512BFS();

// 	BOOL ConvertOneXAMFImageBFS();

// 	BOOL CreateOnePSForSeriesBFS(LPCTSTR szPSFile);

// 	BOOL InitProcessSettingBFS(LPCTSTR szSeriesFullName,
// 							INT iImageIndex,
// 							PVOID pRawImage);

// 	BOOL FillDcmPatientStruct(PatientInfoStruct* pPatientStruct, DcmPatientInfoStruct* pDcmPatientStruct);
// 	BOOL FillDcmStudyStruct(StudyInfoStruct* pStudyStruct, DcmStudyInfoStruct* pDcmStudyStruct);
// 	BOOL FillDcmSeriesStruct(SeriesInfoStruct* pSeriesStruct, DcmSeriesInfoStruct* pDcmSeriesStruct, DownscaleCriterion enumDownScaleCriterion);
// 	BOOL FillDcmConfigStruct(ConfigInfoStruct* pConfigStruct, DcmConfigInfoStruct* pDcmConfigInfoStruct);
// 	BOOL GetImageIndex(LPCTSTR szImageFullName, int* piImageIndex);

// 	BOOL GetWWAndWL(DownscaleCriterion enumDownScaleCriterion, unsigned short* pusWW, unsigned short* pusWL);

	

	BOOL GetPatientInfoStruct(vector<PatientInfoStruct>* pvtrPatientStruct, LPCTSTR szPatientUID, PatientInfoStruct** ppPatientStruct);
	BOOL GetStudyInfoStruct(vector<StudyInfoStruct>* pvtrStudyStruct, LPCTSTR szStudyUID, StudyInfoStruct** ppStudyStruct);
	BOOL GetSeriesInfoStruct(vector<SeriesInfoStruct>* pvtrSeriesStruct, LPCTSTR szSeriesUID, SeriesInfoStruct** ppSeriesStruct);
	BOOL GetPostProcessInfoStruct(vector<PostProcessingInfo>* pvtrPostProcessStruct, LPCTSTR szImageUID, PostProcessingInfo** ppPostProcessStruct);


	void GetBMPDir(CString& strBMPDir);
	void GetJPEGDir(CString& strJPEGDir);

	void GetBMPFullName(LPCTSTR szDir, CString& strBMPFullName);
	void GetJPEGFullName(LPCTSTR szDir, CString& strJPEGFullName);

	//<< 获得图像在P&A分区的存储路径目录
	void GetDcmImageDir(CString& strDcmImageDir);
	//<< 获得图像在P&A分区的存储路径
	void GetDcmImageFullName(LPCTSTR szDir, BOOL bRaw, CString& strDcmImageFullName);
	//<< 获得图像PS文件在P&A分区的存储路径
	void GetDcmPSFullName(LPCTSTR szDcm, CString& strDcmPSFullName);
	//<< 获得图像在P&A分区的患者目录
	CString GetPatientDir();


	BOOL ReadImageData(BOOL bRaw);

	//<< 获得图像在图像盘的路径
	BOOL GetImageFileName(BOOL bRaw, CString& strFile);
	//<< 获得图像PS文件在图像盘的路径
	void GetOriginalPSFileName(CString& strPSFile);

// 	BOOL ConnectToRawImageDisk();
// 	void EnableDisconnectToRawImageDisk();
// 	BOOL DisConnectToRawImageDisk();

	void NotifyProgress();

	void GetLanguageSetting();

	// Check whether disk space is enough or not
	BOOL CheckDiskSpace();

	// Estimate the harddisk space needed
	DWORD GetEstimatedDiskSpaceNeeded(DWORD dwImageCount, BOOL bDICOM, DownscaleCriterion enumDownscaleCriterion, BOOL bMultiFrame, BOOL bBMP, BOOL bJPEG, __int64 i64AdditionalSize = 0);

	BOOL IsFileExist(LPCTSTR szFile);

private:
	
// 	CBuffer					m_RawDataBuffer;
	void*					m_pDcmPixelData;


	//

	PAJob*					m_pJob;
	LPCTSTR					m_szStorePath;
	DownscaleCriterion		m_enumDownscaleCriterion;

	BOOL					m_bRawDcm;
	BOOL					m_bProcessedDcm;
	BOOL					m_bMakePSFile;
	BOOL					m_bMakeDICOMDIR;

	vector<CString>*		m_pvtrRawDcmImages;
	vector<CString>*		m_pvtrProcDcmImages;


	ConfigInfoStruct*		m_pConfigInfo;
	PatientInfoStruct*		m_pPatientInfo;
	StudyInfoStruct*		m_pStudyInfo;
	SeriesInfoStruct*		m_pSeriesInfo;
	ImageInfoStruct*		m_pImageInfo;
	PostProcessingInfo*		m_pPostProcessInfo;

	DWORD					m_dwHandledImagesCount;

	vector<PatientDirStruct>	m_vtrPatientDir;

	DWORD					m_dwPhaseNum;
	UINT					m_NotifyObject;

	BOOL					m_bChineseLang;

};

#endif // !defined(AFX_DCMPARTNER_H__6F5EA875_7F0A_43BD_A7EC_281027D9FE42__INCLUDED_)
