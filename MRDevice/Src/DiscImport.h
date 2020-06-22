/* Time: <@(#)DiscImport.h   2009-3-5 - 10:32:47   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DiscImport.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Capsulation class of import function
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:32:47		FanZF	Creation
 *
 *********************************************************************
 */

// DiscImport.h: interface for the CDiscImport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__DISCIMPORT_H__)
#define __DISCIMPORT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "ASBasis.h"
#include "PALib_i.h"
#include "ISController.h"
#include "DBController.h"
#include "DcmDirParser.h"
#include "DcmParser.h"
#include "DirHandler.h"
// #include "RunFile.h"
#include "JobQueue.h"

typedef enum _TagConnectImageDiskResult
{
	enumCntImageDiscResult_OK = 0,
	enumCntImageDiscResult_Break = 1,
	enumCntImageDiscResult_Failed = 2

}ConnectImageDiskResult;

class CDiscImport : public NObserver,
				  public NSubject
{
public:
	virtual ~CDiscImport();
	
	static CDiscImport* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	BOOL UnInit();
	
	//<< 处理任务
	BOOL HandleJob(PAJob* pJob);

	//<< 获得导入设备列表
	BOOL GetImportDevices(BSTR** ppbsDevices, long* pLen);

	//<< 获得导入光盘信息通知
	BOOL GetImportDiscInfoNotify(LPCTSTR szDeviceName);
	//<< 获得导入光盘信息处理
	BOOL GetImportDiscInfoProc(GetImportDiscInfoStruct* pdis);
	//<< 获得导入光盘信息
	BOOL GetImportDiscInfo(DiscImportPatientInfo** ppPatients,
								long* pPatientNum,
								DiscImportStudyInfo** ppStudies,
								long* pStudyNum,
								DiscImportSeriesInfo** ppSeries,
								long* pSeriesNum,
								DiscImportImageInfo** ppImages,
								long* pImageNum);
	//<< 取消获得导入光盘信息
	BOOL CancelGetImportDiscInfo();

	//<< 创建任务
	BOOL CreateJob(vector<CString>* pvtrUIDs, PatientAdminUIDType enumUIDType);
	//<< 获得任务信息
	BOOL GetJobInfo(LPCTSTR szJobID, DiscImport_SeriesStruct** ppSeriesList, long* pLen);
	
	//<< 设置子模块状态
	void SetSubModuleState(SubModuleState enumSubModuleState);
	//<< 获得子模块状态
	SubModuleState GetSubModuleState();
	
	//<< 采集前处理工作
	BOOL HandleWorkBeforeAcq();

	//<< 取消一个状态为“已提交”导入任务的所有子任务；或者对于shutshow时强制终止的导入任务，取消未完成的子任务
	BOOL CancelDiscImportJob(PAJob* pJob);

	//<< 转发UserGuidance
	void NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive);

protected:
	//<< 处理NSubject返回的消息
	virtual LONG HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam);
private:
	CDiscImport();

	//<< 报告获取导入光盘信息状态与结果
	void ReportGetImportDiscInfoStateAndResult(LPCTSTR szState, BOOL bReady);

	//<< 有效化患者总体信息
	void ValidatePatientTotalInfo(DRDcmSysPatientTotalInfoStruct* pDcmPatientTotalInfo);

	//<< 获得DICOM文件中的患者信息
	BOOL GetPatientInfoInDcm();

	//<< 导入图像到磁盘
	BOOL ImportImageToDisk();
	//<< 光盘上的文件是否存在
	BOOL IsFileExistInMedia(LPCTSTR szFile);
	//<< 根据光盘上后处理DICOM图像名获取生数据DICOM图像名
	void GetRawDcmFileNameByProcessedDcmFileNameInMedia(CString& strRawFile, CString& strProcDcmFile);
	//<< 根据光盘上后处理DICOM图像名获取其PS文件名
	void GetPSFileNameByProcessedDcmFileNameInMedia(CString& strPSFile, CString& strProcDcmFile);

	//<< 设置导入图像状态
	void SetImportedSeriesState(UINT uImageIndex, DiscImport_ImageState enumState);
	//<< 设置导入图像进度
	void SetImportedSeriesProgress(UINT uImageIndex, DiscImport_SeriesProgress enumProgress, DWORD dwProgress = 0);
	//<< 设置导入图像详细信息
	void SetImportedSeriesDetailByDetailInfo(UINT uImageIndex, LPCTSTR szDetailInfo);
	//<< 设置导入图像详细信息
	void SetImportedSeriesDetailByCompletedInfo(UINT uImageIndex, LPCTSTR szDetailFormat, LPCTSTR szPatientID, LPCTSTR szPatientName, LPCTSTR szStudyID, LPCTSTR szSeriesID, LPCTSTR szImageID);
	
	//<< 清除当前导入图像信息
	void ClearCurrentImportedImageInfo();
	//<< 清除未正常导入图像所有信息
	BOOL RemoveInfoOfUnproperlyImportedImage();

// 	ConnectImageDiskResult ConnectToRawImageDisk();
// 	void EnableDisconnectToRawImageDisk();
// 	BOOL DisConnectToRawImageDisk();

private:

	static CDiscImport*			m_pInstance;

	SubModuleState				m_SubModuleState;

	PAJob*						m_pCurrentJob;

	CCriticalSection			m_CSLockSubModuleState;

	//<< Patient Info in DICOMDIR
	DICOMDIRPatientsTotalInfo	m_DcmDirPatientsTotalInfo;



	//<< 
	vector<GetImportDiscInfoStruct>		m_vtrGetDiscInfo;
	CCriticalSection					m_CSLockValidState;



	// After the Series Import thread is terminated, the image, dir and DB Info
	// of Current Series needs to be removed since the series is not imported properly.

	// Something related to current importing Series
	HANDLE						m_hFindFileDcm;
	CDcmParser*					m_pDcmParser;
	CString						m_strPostDcmFileInMedia;


	int							m_iCurrentImageIndex;

	PatientInfoStruct			m_PatientInfo;
	StudyInfoStruct				m_StudyInfo;
	SeriesInfoStruct			m_SeriesInfo;
	ImageInfoStruct				m_ImageInfo;
	PostProcessingInfo			m_PostProcessInfo;

	CString						m_strPatientUID;
	CString						m_strStudyUID;
	CString						m_strSeriesUID;
	CString						m_strImageUID;

	BOOL						m_bPatientExist;
	BOOL						m_bStudyExist;
	BOOL						m_bSeriesExist;
	BOOL						m_bImageExist;

	CString						m_strPatientFullPath;
	CString						m_strStudyFullPath;
	CString						m_strSeriesFullPath;
	CString						m_strImageFullPath;
	CString						m_strPostImageFullPath;
	CString						m_strPostImagePSFullPath;

};

#endif // !defined(__DISCIMPORT_H__)
