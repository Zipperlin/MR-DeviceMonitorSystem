/* Time: <@(#)JobHandler.h   2009-3-5 - 10:46:34   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : JobHandler.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The job handler class
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:46:34		FanZF	Creation
 *
 *********************************************************************
 */

// JobHandler.h: interface for the CJobHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_JOBHANDLER__H_)
#define _JOBHANDLER__H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DcmPartner.h"

class CJobHandler : public NObserver,
					public NSubject
{
public:
	CJobHandler();
	virtual ~CJobHandler();

	static CJobHandler* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	BOOL UnInit();

	BOOL HandleJobQueue();

	BOOL PushJob(PAJob* pJob);
	BOOL GetJobList(JobInfo** ppJobInfoList, long *pLen);
	
	BOOL GetSendJobInfo(LPCTSTR szJobID, JobInfo* pJobInfo, PSSIInfo** ppPSSIList, long* pPSSILen, NetworkNode** ppNodeList, long* pNodeLen, JobDetailStruct** ppDetailList, long* pDetailLen);
	BOOL GetBurnJobInfo(LPCTSTR szJobID, JobInfo* pJobInfo, PSSIInfo** ppPSSIList, long* pPSSILen, JobDetailStruct** ppDetailList, long* pDetailLen);
	BOOL GetDiscImportJobInfo(LPCTSTR szJobID, DiscImport_SeriesStruct** ppSeriesList, long* pLen);

	BOOL MoveJob(LPCTSTR szJobUID, BOOL bForward = TRUE);

	BOOL CancelJobs(vector<CString>* pvtrJobIDs);
	BOOL DeleteJobs(vector<CString>* pvtrJobIDs);

	BOOL IsPatientStudySeriesImageUIDInUse(PatientAdminUIDType enumUIDType, vector<CString>* pvtrUIDList);

	BOOL IsUnfinishedJobExist(JobType enumJobType, BOOL* pbExist);

	void NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive);

	BOOL GetJobPSSIInfo(PAJob* pJob, PSSIInfo** ppPSSIInfo, long* plLen);

protected:
	virtual LONG HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam);

private:

	BOOL GetJobNetworkNodeInfo(PAJob* pJob, NetworkNode** ppNodeInfo, long* plLen);
	BOOL GetJobDetailInfo(PAJob* pJob, JobDetailStruct** ppDetailInfo, long* plLen);

	SeriesInfoStruct* GetSeriesInfoStruct(LPCTSTR szUID, vector<SeriesInfoStruct>* pvtrSeries);
	StudyInfoStruct* GetStudyInfoStruct(LPCTSTR szUID, vector<StudyInfoStruct>* pvtrStudy);
	PatientInfoStruct* GetPatientInfoStruct(LPCTSTR szUID, vector<PatientInfoStruct>* pvtrPatient);

private:

	static CJobHandler*		m_pInstance;

	BOOL					m_bActive;
	CJobQueue				m_JobQueue;

	HANDLE					m_hEvent;
	HANDLE					m_hJobQueueHandleThread;
	PAJob*					m_pCurrentJob;

	CCriticalSection		m_CSLockJobState;
};

#endif // !defined(_JOBHANDLER__H_)
