/* Time: <@(#)JobQueue.h   2009-3-5 - 10:47:19   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : JobQueue.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The job queue class
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:47:19		FanZF	Creation
 *
 *********************************************************************
 */

// PrintJobQueue.h: interface for the CPrintJobQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JOBQUEUE_H__33F9F10D_425D_4131_84D2_844ABCA7E451__INCLUDED_)
#define AFX_JOBQUEUE_H__33F9F10D_425D_4131_84D2_844ABCA7E451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "PALib_i.h"
#include "PAJob.h"

#define QUE_LEN_MAX 1024



typedef struct PAJobNode
{
	PAJob* pJob;
	struct PAJobNode *pNextNode;
}PAJobNode;

class CJobQueue
{
public:
	CJobQueue();
	virtual ~CJobQueue();
public:
	//Push a PA message to the queue
	BOOL PushJob(PAJob* pJob);


	//Pull a PA message from the queue
	BOOL PullJob(PAJob** ppJob);

	// cancel a job
	int CancelJob(LPCTSTR szJobID);

	// delete a job
	int DeleteJob(LPCTSTR szJobID);

	//Clear the queue
	BOOL ClearQueque();

	//Get the number of Jobs in queue
	SHORT GetJobNumber();

	// Get head job pointer
	PAJobNode* GetHeadJobNode();

	// Get a Job pointer by job ID
	PAJob* GetJob(LPCTSTR szJobID);

	// Whether the queue has Submitted Jobs or not
	BOOL HasSubmittedJob();

	// Get the first Submitted Job in queue
	PAJob* GetASubmittedJob();

	// GetJobList for GUI, not including the init job
	BOOL GetJobList(JobInfo** ppJobInfoList, long* pLen);

	// Get a Job's JobInfo
	BOOL GetJobInfo(LPCTSTR szJobID, JobInfo* pJobInfo);

	// Move Job
	BOOL MoveJobForward(LPCTSTR szJobID);
	BOOL MoveJobBackward(LPCTSTR szJobID);

	// Is a UID is In use(Submitted or Executing);
	BOOL IsPatientStudySeriesImageUIDInUse(PatientAdminUIDType enumUIDType, vector<CString>* pvtrUIDList);

	BOOL IsUnfinishedJobExist(JobType enumJobType, BOOL* pbExist);

private:
	BOOL GetJobDetailInfo(PAJob* pJob, JobInfo* pJobInfo);

	// Get Job index in queue, based on 1
	// return -1 if no Job found with the szJobID
	int GetJobIndex(PAJob* pJob);

private:

	CCriticalSection	m_CSLock;
	PAJobNode*			m_pHeadNode;
	SHORT				m_CurNodeNum;
};

#endif // !defined(AFX_JOBQUEUE_H__33F9F10D_425D_4131_84D2_844ABCA7E451__INCLUDED_)
