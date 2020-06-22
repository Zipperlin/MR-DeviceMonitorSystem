/* Time: <@(#)DBStructInitor.cpp   2009-3-5 - 10:36:39   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DBStructInitor.cpp
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
 *	1	2009-3-5 - 10:36:39		FanZF	Creation
 *
 *********************************************************************
 */

// DBStructInitor.cpp: implementation of the CDBStructInitor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DBStructInitor.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBStructInitor::CDBStructInitor()
{

}

CDBStructInitor::~CDBStructInitor()
{

}

void CDBStructInitor::InitPatientInfoStruct(PatientInfoStruct* pStruct)
{
	pStruct->bsPatientUID = NULL; 
	pStruct->bsPatientID = NULL;
	pStruct->bsPatientName = NULL;
	pStruct->bsPatientFullName = NULL;
	pStruct->bsPatientComment = NULL; 
	pStruct->bsEthnicGroup = NULL;
	pStruct->bsOtherPatientIDs = NULL; 
	pStruct->bsOtherPatientName = NULL; 
	pStruct->bsOccupation = NULL;
	pStruct->bsPatientFilePath = NULL;
}

void CDBStructInitor::InitStudyInfoStruct(StudyInfoStruct* pStruct)
{
	pStruct->bsStudyUID = NULL;
	pStruct->bsPatientUID = NULL;
	pStruct->bsReferringPhysicianName = NULL;
	pStruct->bsStudyDescription = NULL;
	pStruct->bsPatientHistory = NULL;
	pStruct->bsStudyImagePath = NULL;
	pStruct->bsOperatorName = NULL;
	pStruct->bsInstanceUID = NULL;
	pStruct->bsAccessionNumber = NULL;
	pStruct->bsPerformingPhysicianName = NULL;
}

void CDBStructInitor::InitSeriesInfoStruct(SeriesInfoStruct* pStruct)
{
	pStruct->bsSeriesUID = NULL; 
	pStruct->bsStudyUID = NULL; 
	pStruct->bsSeriesDescription = NULL;
	pStruct->bsSeriesFilePath = NULL; 
 	pStruct->bsAprRegionName = NULL;
}

void CDBStructInitor::InitImageInfoStruct(ImageInfoStruct* pStruct)
{
	pStruct->bsImageUID = NULL; 
	pStruct->bsSeriesUID = NULL; 
	pStruct->bsImageFilePath = NULL; 
	pStruct->bsPatientOrientation = NULL;
	pStruct->bsAprOrganUID = NULL;
	pStruct->bsAprOrganName = NULL;
}

void CDBStructInitor::InitPostProcessInfoStruct(PostProcessingInfo* pStruct)
{
	pStruct->bsImageUID = NULL; 
	pStruct->bsSeriesUID = NULL;
	pStruct->bsProcessedImageFilePath = NULL;
}

