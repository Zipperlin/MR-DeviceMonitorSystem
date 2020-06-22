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
	
	//<< ��������
	BOOL HandleJob(PAJob* pJob);

	//<< ��õ����豸�б�
	BOOL GetImportDevices(BSTR** ppbsDevices, long* pLen);

	//<< ��õ��������Ϣ֪ͨ
	BOOL GetImportDiscInfoNotify(LPCTSTR szDeviceName);
	//<< ��õ��������Ϣ����
	BOOL GetImportDiscInfoProc(GetImportDiscInfoStruct* pdis);
	//<< ��õ��������Ϣ
	BOOL GetImportDiscInfo(DiscImportPatientInfo** ppPatients,
								long* pPatientNum,
								DiscImportStudyInfo** ppStudies,
								long* pStudyNum,
								DiscImportSeriesInfo** ppSeries,
								long* pSeriesNum,
								DiscImportImageInfo** ppImages,
								long* pImageNum);
	//<< ȡ����õ��������Ϣ
	BOOL CancelGetImportDiscInfo();

	//<< ��������
	BOOL CreateJob(vector<CString>* pvtrUIDs, PatientAdminUIDType enumUIDType);
	//<< ���������Ϣ
	BOOL GetJobInfo(LPCTSTR szJobID, DiscImport_SeriesStruct** ppSeriesList, long* pLen);
	
	//<< ������ģ��״̬
	void SetSubModuleState(SubModuleState enumSubModuleState);
	//<< �����ģ��״̬
	SubModuleState GetSubModuleState();
	
	//<< �ɼ�ǰ������
	BOOL HandleWorkBeforeAcq();

	//<< ȡ��һ��״̬Ϊ�����ύ��������������������񣻻��߶���shutshowʱǿ����ֹ�ĵ�������ȡ��δ��ɵ�������
	BOOL CancelDiscImportJob(PAJob* pJob);

	//<< ת��UserGuidance
	void NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive);

protected:
	//<< ����NSubject���ص���Ϣ
	virtual LONG HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam);
private:
	CDiscImport();

	//<< �����ȡ���������Ϣ״̬����
	void ReportGetImportDiscInfoStateAndResult(LPCTSTR szState, BOOL bReady);

	//<< ��Ч������������Ϣ
	void ValidatePatientTotalInfo(DRDcmSysPatientTotalInfoStruct* pDcmPatientTotalInfo);

	//<< ���DICOM�ļ��еĻ�����Ϣ
	BOOL GetPatientInfoInDcm();

	//<< ����ͼ�񵽴���
	BOOL ImportImageToDisk();
	//<< �����ϵ��ļ��Ƿ����
	BOOL IsFileExistInMedia(LPCTSTR szFile);
	//<< ���ݹ����Ϻ���DICOMͼ������ȡ������DICOMͼ����
	void GetRawDcmFileNameByProcessedDcmFileNameInMedia(CString& strRawFile, CString& strProcDcmFile);
	//<< ���ݹ����Ϻ���DICOMͼ������ȡ��PS�ļ���
	void GetPSFileNameByProcessedDcmFileNameInMedia(CString& strPSFile, CString& strProcDcmFile);

	//<< ���õ���ͼ��״̬
	void SetImportedSeriesState(UINT uImageIndex, DiscImport_ImageState enumState);
	//<< ���õ���ͼ�����
	void SetImportedSeriesProgress(UINT uImageIndex, DiscImport_SeriesProgress enumProgress, DWORD dwProgress = 0);
	//<< ���õ���ͼ����ϸ��Ϣ
	void SetImportedSeriesDetailByDetailInfo(UINT uImageIndex, LPCTSTR szDetailInfo);
	//<< ���õ���ͼ����ϸ��Ϣ
	void SetImportedSeriesDetailByCompletedInfo(UINT uImageIndex, LPCTSTR szDetailFormat, LPCTSTR szPatientID, LPCTSTR szPatientName, LPCTSTR szStudyID, LPCTSTR szSeriesID, LPCTSTR szImageID);
	
	//<< �����ǰ����ͼ����Ϣ
	void ClearCurrentImportedImageInfo();
	//<< ���δ��������ͼ��������Ϣ
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
