/* Time: <@(#)PAJob.h   2009-3-5 - 10:49:23   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : PAJob.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The job class
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:49:23		FanZF	Creation
 *
 *********************************************************************
 */

// PAJob.h: interface for the CPAJob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAJOB_H__A1BED0F4_44F5_47F7_AC72_EE8ABAE54A2F__INCLUDED_)
#define AFX_PAJOB_H__A1BED0F4_44F5_47F7_AC72_EE8ABAE54A2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "PALib_i.h"

#include <vector>
using namespace std;

#define QUE_LEN_MAX 1024


class PAJob : public NSubject
{

public:
	PAJob();
	~PAJob();
	
	void SetState(JobState enumState);
	void SetPhase(LPCTSTR szPhase);
	void SetProgress(JobProgressUsing enumProgressUsing, UINT uiFirstParam = 0, UINT uiSecondParam = 0);

	//<< Detail信息被翻译；若szAddInfo不为NULL，则szDetailInfo为AAAAA%sAAAAA可扩展格式
	void SetDetail(LPCTSTR szDetailInfo, LPCTSTR szAddInfo = NULL);

	//<< 由UserGuidanceID获得Detail信息，并翻译
	void SetDetailByUGID(LONG iUGID = 0);

	//<< Detail信息无需翻译
	void SetDetailOriginal(LPCTSTR szDetailInfo);

	int GetImageCount();
	
private:
	void ReleaseData();


public:
	
	JobType			enumJobType;

	CString			strJobID;

	BOOL			bCancelFlag;

	JobState		enumJobState;

	CString			strPhase;

	JobProgressUsing	enumJobProgressUsing;
	UINT				uiCompleted;
	UINT				uiTotal;
	DWORD				dwPercentage;
	
	vector<JobDetail>	vtrDetail;

	vector<PatientInfoStruct>		vtrPatient;
	vector<StudyInfoStruct>			vtrStudy;
	vector<SeriesInfoStruct>		vtrSeries;
	vector<ImageInfoStruct>			vtrImages;
	vector<PostProcessingInfo>		vtrPostProcess;

	void* pData;

private:
	CCriticalSection		m_CSLockSetDetail;

};

#endif // !defined(AFX_PAJOB_H__A1BED0F4_44F5_47F7_AC72_EE8ABAE54A2F__INCLUDED_)
