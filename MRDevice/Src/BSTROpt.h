/* Time: <@(#)BSTROpt.h   2009-3-5 - 10:28:45   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : BSTROpt.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : BSTR operation
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:28:45		FanZF	Creation
 *
 *********************************************************************
 */

// BSTROpt.h: interface for the CBSTROpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSTROPT_H__3CD8A020_04E7_4DDA_876C_38286B361F1D__INCLUDED_)
#define AFX_BSTROPT_H__3CD8A020_04E7_4DDA_876C_38286B361F1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PALib_i.h"
#include "PALibExt_i.h"
#include "JobQueue.h"

class CBSTROpt  
{
public:
	CBSTROpt();
	virtual ~CBSTROpt();

	static CString BSTRToCString(BSTR& bs);
	static void FreeBSTR(BSTR& bs);

	//<< P&A Struct
	static void FreeJobProgressStruct(JobProgressStruct* pStruct);
	static void FreeJobDetailStruct(JobDetailStruct* pStruct);

	static void FreeBurnPatientInfoStructList(BurnPatientInfoStruct* pStruct, int iCount);
	static void FreeBurnStudyInfoStructList(BurnStudyInfoStruct* pStruct, int iCount);
	static void FreeBurnSeriesInfoStructList(BurnSeriesInfoStruct* pStruct, int iCount);
	static void FreeBurnImageInfoStructList(BurnImageInfoStruct* pStruct, int iCount);
	static void FreeBurnSpeedInfoList(BurnSpeedInfo* pStruct, int iCount);
	static void FreeBurnPatientInfoStruct(BurnPatientInfoStruct* pStruct);
	static void FreeBurnStudyInfoStruct(BurnStudyInfoStruct* pStruct);
	static void FreeBurnSeriesInfoStruct(BurnSeriesInfoStruct* pStruct);
	static void FreeBurnImageInfoStruct(BurnImageInfoStruct* pStruct);
	static void FreeBurnSpeedInfo(BurnSpeedInfo* pStruct);
	static void FreeBurnMediaInfo(BurnMediaInfo* pStruct);

	static void FreeDiscImport_SeriesStateStruct(DiscImport_SeriesStateStruct* pStruct);
	static void FreeDiscImport_SeriesProgressStruct(DiscImport_SeriesProgressStruct* pStruct);
	static void FreeDiscImport_SeriesDetailStruct(DiscImport_SeriesDetailStruct* pStruct);

	static void FreeWorkListStruct(WorkListStruct* pStruct);
	static void FreeWorkListStructList(WorkListStruct* pStruct, int iCount);
	static void FreeMppsSetResultStruct(MppsSetResult* pStruct);

	static void FreePSSIStructList(PSSIInfo* pStruct, long lLen);
	static void FreePSSIStruct(PSSIInfo* pStruct);


	static void FreePAJob(PAJob* pJob);

	// DB struct
	static void FreeConfigInfoStruct(ConfigInfoStruct* pStruct);
	static void FreePatientInfoStruct(PatientInfoStruct* pStruct);
	static void FreeStudyInfoStruct(StudyInfoStruct* pStruct);
	static void FreeSeriesInfoStruct(SeriesInfoStruct* pStruct);
	static void FreeImageInfoStruct(ImageInfoStruct* pStruct);
	static void FreePostProcessingInfo(PostProcessingInfo* pStruct);

};

#endif // !defined(AFX_BSTROPT_H__3CD8A020_04E7_4DDA_876C_38286B361F1D__INCLUDED_)
