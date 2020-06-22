/* Time: <@(#)PADataBaseOpt.h   2009-3-26 - 15:33:12   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : PADataBaseOpt.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-26
 *
 *  Description : Printing&Archiving data base operation
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-26 - 15:33:12		FanZF	Creation
 *
 *********************************************************************
 */

// PADabaBaseOpt.h: interface for the CPADabaBaseOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PADABABASEOPT_H__FC92E85C_4812_462C_AA6B_0F0E33AD5274__INCLUDED_)
#define AFX_PADABABASEOPT_H__FC92E85C_4812_462C_AA6B_0F0E33AD5274__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "PAJob.h"


class CPADataBaseOpt  
{
public:
	virtual ~CPADataBaseOpt();
	
	static CPADataBaseOpt* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	BOOL UnInit();

	BOOL AddJob(PAJob* pJob);
	BOOL SetJob(PAJob* pJob);

	BOOL GetJobCount(DWORD* pdwCount);
	BOOL GetJobs(DWORD dwStartIndex, DWORD* pdwCount, JobInfo** ppJobList);

	BOOL GetJobInfo(LPCTSTR szJobID, JobInfo* pJobInfo);
	BOOL GetJobPSSIInfo(LPCTSTR szJobID, long* pLen, PSSIInfo** ppPSSIList);
	BOOL GetJobNetworkNodeInfo(LPCTSTR szJobID, long* pLen, NetworkNode** ppNodeList);
	BOOL GetJobDetailInfo(LPCTSTR szJobID, long* pLen, JobDetailStruct** ppDetailList);
	BOOL GetJobDiscImportImageInfo(LPCTSTR szJobID, long* pLen, DiscImport_SeriesStruct** ppDISSList);
	BOOL DeleteJobs(vector<CString>& vtrJobIDs);
	BOOL DeleteAllJobs();

	BOOL AddWorklistImportedStudy(LPCTSTR szStudyInstanceUID);
	BOOL IsStudyInstanceUIDExist(LPCTSTR szStudyInstanceUID, BOOL* pbExist);
	BOOL DeleteAllImportedStudyRecords();

	BOOL CompactDabaBase(BOOL bBackUp);

private:
	CPADataBaseOpt();

	BOOL AddJobUIDInfo(PAJob* pJob);
	BOOL AddJobPssiInfo(PAJob* pJob);
	BOOL AddJobNetworkNodeInfo(PAJob* pJob);
	BOOL AddJobDetailInfo(PAJob* pJob);
	BOOL AddJobDiscImportImageInfo(PAJob* pJob);

	BOOL CompactDB(LPCTSTR szDBPath, LPCTSTR szPw, BOOL bBackUp);

	static CPADataBaseOpt*	m_pInstance;
	DBDatabaseOpt*			m_pDBOpt;
	DBDatabaseBasisOpt		m_DbBasisOpt;
	BOOL					m_bDBOpen;
};

#endif // !defined(AFX_PADABABASEOPT_H__FC92E85C_4812_462C_AA6B_0F0E33AD5274__INCLUDED_)
