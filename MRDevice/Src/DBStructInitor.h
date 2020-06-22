/* Time: <@(#)DBStructInitor.h   2009-3-5 - 10:36:18   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DBStructInitor.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The initialization of DB structures
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:36:18		FanZF	Creation
 *
 *********************************************************************
 */

// DBStructInitor.h: interface for the CDBStructInitor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__DBSTRUCTINITOR_H__)
#define __DBSTRUCTINITOR_H__


class CDBStructInitor  
{
public:
	CDBStructInitor();
	virtual ~CDBStructInitor();

	static void InitPatientInfoStruct(PatientInfoStruct* pStruct);
	static void InitStudyInfoStruct(StudyInfoStruct* pStruct);
	static void InitSeriesInfoStruct(SeriesInfoStruct* pStruct);
	static void InitImageInfoStruct(ImageInfoStruct* pStruct);
	static void InitPostProcessInfoStruct(PostProcessingInfo* pStruct);
};

#endif // !defined(__DBSTRUCTINITOR_H__)
