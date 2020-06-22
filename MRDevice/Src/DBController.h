/* Time: <@(#)DBController.h   2009-3-5 - 10:34:41   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DBController.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Communication class with DB
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:34:41		FanZF	Creation
 *
 *********************************************************************
 */

// DBController.h: interface for the CDBController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBCONTROLLER_H__CA441425_98AD_4A1C_A64C_97CA6E6B6867__INCLUDED_)
#define AFX_DBCONTROLLER_H__CA441425_98AD_4A1C_A64C_97CA6E6B6867__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PALib_i.h"
#include "JobQueue.h"
#include "DBSink.h"
#include "IDPathGen.h"

class CDBController
{
public:
	virtual ~CDBController();

	static CDBController* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	BOOL UnInit();


	//<< 获得与UIDs相关的患者、检查，序列，图像（包括后处理）信息
	//<< 注：所有UID需具有同一个〈父〉
	BOOL GetJobImageInfoByUIDs(vector<CString>* pvtrUID,
								PatientAdminUIDType enumUIDType,
								PAJob* pJob);
	
	// Get ConfigInfoStruct pointer
	ConfigInfoStruct* GetConfigInfo();

	void DisableGetJobInfo();

	BOOL IsPatientUIDExistsInDB(LPCTSTR szPatientUID, BOOL* pbExist);
	BOOL IsPatientIDExistsInDB(LPCTSTR szPatientID, BOOL* pbExist);
	BOOL IsStudyUIDExistsInDB(LPCTSTR szStudyUID, BOOL* pbExist);
	BOOL IsSeriesUIDExistsInDB(LPCTSTR szSeriesUID, BOOL* pbExist);
	BOOL IsImageUIDExistsInDB(LPCTSTR szImageUID, BOOL* pbExist);

	BOOL GetPatientInfo(LPCTSTR szPatientUID, PatientInfoStruct* pPatient);
	BOOL GetPatientInfoByID(LPCTSTR szPatientID, PatientInfoStruct* pPatient);
	BOOL GetStudyInfo(LPCTSTR szStudyUID, StudyInfoStruct* pStudy);
	BOOL GetSeriesInfo(LPCTSTR szSeriesUID, SeriesInfoStruct* pSeries);
	BOOL GetPostProcessInfo(LPCTSTR szImageUID, PostProcessingInfo* pPostInfo);

	BOOL IsStudyInstanceUIDExists(LPCTSTR szStudyInstanceUID, BOOL* pbExist);
	BOOL GetStudyUIDByInstanceUID(LPCTSTR szStudyInstanceUID, CString& strStudyUID);
	BOOL GetMPPSStatusByStudyInstanceUID(LPCTSTR szStudyInstanceUID, WorkListStatus* penumStatus);

	BOOL AddPatientRecordToDB(PatientInfoStruct* pPatient);
	BOOL AddStudyRecordToDB(StudyInfoStruct* pStudy);
	BOOL AddSeriesRecordToDB(SeriesInfoStruct* pSeries);
	BOOL AddImageRecordToDB(ImageInfoStruct* pImage);
	BOOL SetPostProcessingInfo(PostProcessingInfo* pPostProcess);

	BOOL DeletePatientRecordFromDB(LPCTSTR szPatientUID);
	BOOL DeleteStudyRecordFromDB(LPCTSTR szStudyUID);
	BOOL DeleteSeriesRecordFromDB(LPCTSTR szSeriesUID);
	BOOL DeleteImageRecordFromDB(LPCTSTR szImageUID);

	BOOL ModifyStudyInfo(StudyInfoStruct* pStudyInfo);
	/************************************************************************/
	//	修改患者的信息
	//	[9/2/2009 gaoxing]
	/************************************************************************/
	BOOL ModifyPatientInfo(PatientInfoStruct* pPatientInfo);

	BOOL GetCurrentStudyUID(CString& strStudyUID);

// 	BOOL GetNextStudyIDInPatient(LPCTSTR szPatientUID, INT* piStudyID);
	BOOL GetNextSeriesIDInStudy(LPCTSTR szStudyUID, INT* piSeriesID);

	// if strPatientID is not empty:
	//		check whether the PatientID exists in DB or not, 
	//		if exists,
	//			create a new one, 
	//		else
	//			just return the old one
	// else
	//		create a new one
	BOOL UpdatePatientID(CString& strPatientID);

	// Set and Get Study MPPS status
	BOOL SetStudyMPPSStatus(LPCTSTR szStudyUID, MPPS_STATE enumStatus);

	void SetDBWorkState(WORKSTATE enumWorkState);

private:
	//<< 下列接口仅添加《子》，不添加自身
	BOOL AddJobImageInfoByPatientUID(LPCTSTR szPatientUID);
	BOOL AddJobImageInfoByStudyUID(LPCTSTR szStudyUID);
	BOOL AddJobImageInfoBySeriesUID(LPCTSTR szSereisUID);
	BOOL AddJobImageInfoByImageUID(LPCTSTR szImageUID);

	SeriesInfoStruct* GetSereisInfoStruct(LPCTSTR szSeriesUID, vector<SeriesInfoStruct>* pvtrSereis);

	BOOL IsImageUIDExisted(vector<ImageInfoStruct>* pvtrImage, LPCTSTR szDstImageUID);
	BOOL IsSeriesUIDExisted(vector<SeriesInfoStruct>* pvtrSeries, LPCTSTR szDstSeriesUID);
	BOOL IsStudyUIDExisted(vector<StudyInfoStruct>* pvtrStudy, LPCTSTR szDstStudyUID);
	BOOL IsPatientUIDExisted(vector<PatientInfoStruct>* pvtrPatient, LPCTSTR szDstPatientUID);

	BOOL IsGetJobInfoEnabled();

	CDBController();

private:
	static CDBController*	m_pInstance;

	IDBPIM*					m_pIDBPIM;
	IDBConfig*				m_pIDBConfig;
	IDBSession*				m_pIDBSession;
	IGeneralInterface*		m_pIGeneral;

	ConfigInfoStruct*		m_pConfigInfo;

	PAJob*					m_pJob;

	BOOL					m_bEnableGetJobInfo;

	CCriticalSection		m_CSLock;

	CDBSink					m_DBSink;

	WORKSTATE				m_DBWorkState;

};

#endif // !defined(AFX_DBCONTROLLER_H__CA441425_98AD_4A1C_A64C_97CA6E6B6867__INCLUDED_)
