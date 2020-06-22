/* Time: <@(#)BSTROpt.cpp   2009-3-5 - 10:28:57   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : BSTROpt.cpp
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
 *	1	2009-3-5 - 10:28:57		FanZF	Creation
 *
 *********************************************************************
 */

// BSTROpt.cpp: implementation of the CBSTROpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BSTROpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBSTROpt::CBSTROpt()
{

}

CBSTROpt::~CBSTROpt()
{

}


CString CBSTROpt::BSTRToCString(BSTR& bs)
{
	char* p = _com_util::ConvertBSTRToString(bs);
	CString str = p;

	delete[] p;

	return str;
}

void CBSTROpt::FreeBSTR(BSTR& bs)
{
	::SysFreeString(bs);
	bs = NULL;
}

void CBSTROpt::FreeJobProgressStruct(JobProgressStruct* pStruct)
{
	FreeBSTR(pStruct->bsJobUID);
}

void CBSTROpt::FreeJobDetailStruct(JobDetailStruct* pStruct)
{
    FreeBSTR(pStruct->bsJobID);
    FreeBSTR(pStruct->bsTime);
    FreeBSTR(pStruct->bsDetail);

}


void CBSTROpt::FreeBurnPatientInfoStructList(BurnPatientInfoStruct* pStruct, int iCount)
{
	for (int i = 0; i < iCount; i++)
	{
		FreeBurnPatientInfoStruct(pStruct + i);
	}
}

void CBSTROpt::FreeBurnStudyInfoStructList(BurnStudyInfoStruct* pStruct, int iCount)
{
	for (int i = 0; i < iCount; i++)
	{
		FreeBurnStudyInfoStruct(pStruct + i);
	}
}

void CBSTROpt::FreeBurnSeriesInfoStructList(BurnSeriesInfoStruct* pStruct, int iCount)
{
	for (int i = 0; i < iCount; i++)
	{
		FreeBurnSeriesInfoStruct(pStruct + i);
	}
}

void CBSTROpt::FreeBurnImageInfoStructList(BurnImageInfoStruct* pStruct, int iCount)
{
	for (int i = 0; i < iCount; i++)
	{
		FreeBurnImageInfoStruct(pStruct + i);
	}
}

void CBSTROpt::FreeBurnSpeedInfoList(BurnSpeedInfo* pStruct, int iCount)
{
	for (int i = 0; i < iCount; i++)
	{
		FreeBurnSpeedInfo(pStruct + i);
	}
}

void CBSTROpt::FreeBurnPatientInfoStruct(BurnPatientInfoStruct* pStruct)
{
	FreeBSTR(pStruct->bsPatientName);
	FreeBSTR(pStruct->bsPatientID);
}

void CBSTROpt::FreeBurnStudyInfoStruct(BurnStudyInfoStruct* pStruct)
{
	FreeBSTR(pStruct->bsPatientName);
	FreeBSTR(pStruct->bsPatientID);
}

void CBSTROpt::FreeBurnSeriesInfoStruct(BurnSeriesInfoStruct* pStruct)
{
	FreeBSTR(pStruct->bsPatientName);
	FreeBSTR(pStruct->bsPatientID);
}

void CBSTROpt::FreeBurnImageInfoStruct(BurnImageInfoStruct* pStruct)
{
	FreeBSTR(pStruct->bsPatientName);
	FreeBSTR(pStruct->bsPatientID);
}

void CBSTROpt::FreeBurnSpeedInfo(BurnSpeedInfo* pStruct)
{
	FreeBSTR(pStruct->bsSpeedInfo);
}

void CBSTROpt::FreeBurnMediaInfo(BurnMediaInfo* pStruct)
{
	FreeBSTR(pStruct->bsMediaType);
	FreeBSTR(pStruct->bsMediaSize);
}

void CBSTROpt::FreeDiscImport_SeriesStateStruct(DiscImport_SeriesStateStruct* pStruct)
{
	FreeBSTR(pStruct->bsJobID);
	FreeBSTR(pStruct->bsIndex);
	FreeBSTR(pStruct->bsState);
}

void CBSTROpt::FreeDiscImport_SeriesProgressStruct(DiscImport_SeriesProgressStruct* pStruct)
{
	FreeBSTR(pStruct->bsJobID);
	FreeBSTR(pStruct->bsIndex);
	FreeBSTR(pStruct->bsProgress);
}

void CBSTROpt::FreeDiscImport_SeriesDetailStruct(DiscImport_SeriesDetailStruct* pStruct)
{
	FreeBSTR(pStruct->bsJobID);
	FreeBSTR(pStruct->bsIndex);
	FreeBSTR(pStruct->bsDetailInfo);
}

void CBSTROpt::FreeWorkListStruct(WorkListStruct* pStruct)
{
	FreeBSTR(pStruct->bsSSAETitle);
	FreeBSTR(pStruct->bsSPSDateTime);
	FreeBSTR(pStruct->bsSPSDescription);
	FreeBSTR(pStruct->bsSPSID);
	FreeBSTR(pStruct->bsSPPhisicianName);
	FreeBSTR(pStruct->bsPatientName);
	FreeBSTR(pStruct->bsPatientID);
	FreeBSTR(pStruct->bsAccessionNumber);
	FreeBSTR(pStruct->bsPatientBirthDate);
	FreeBSTR(pStruct->bsRefPhisicianName);
	FreeBSTR(pStruct->bsRPID);
	FreeBSTR(pStruct->bsRPDescription);
	FreeBSTR(pStruct->bsStudyInstanceUID);
    FreeBSTR(pStruct->bsOtherPatientIDs);
    FreeBSTR(pStruct->bsOtherPatientNames);
    FreeBSTR(pStruct->bsPatientAge);
    FreeBSTR(pStruct->bsOccupation);
    FreeBSTR(pStruct->bsPatientSize);
    FreeBSTR(pStruct->bsPatientWeight);
    FreeBSTR(pStruct->bsEthnicGroup);
    FreeBSTR(pStruct->bsPatientComments);
}

void CBSTROpt::FreeWorkListStructList(WorkListStruct* pStruct, int iCount)
{
	for (int i = 0; i < iCount; i++)
	{
		FreeWorkListStruct(pStruct + i);
	}
}

void CBSTROpt::FreeMppsSetResultStruct(MppsSetResult* pStruct)
{
	FreeBSTR(pStruct->bsStudyUID);
}


// DB struct
void CBSTROpt::FreeConfigInfoStruct(ConfigInfoStruct* pStruct)
{
	FreeBSTR(pStruct->bsManufacture);
	FreeBSTR(pStruct->bsSoftwareVersion);
	FreeBSTR(pStruct->bsInstitutionName);
	FreeBSTR(pStruct->bsInstitutionAddress);
	FreeBSTR(pStruct->bsStationName);
	FreeBSTR(pStruct->bsInstitutionalDepartmentName);
	FreeBSTR(pStruct->bsManufacturerModelName);
	FreeBSTR(pStruct->bsDeviceSerialNumber);
	FreeBSTR(pStruct->bsLastRecPatientUID);
	FreeBSTR(pStruct->bsDetectorType);
	FreeBSTR(pStruct->bsPositionerType);
	FreeBSTR(pStruct->bsRescaleType);
}

void CBSTROpt::FreePatientInfoStruct(PatientInfoStruct* pStruct)
{
	FreeBSTR(pStruct->bsPatientUID);
	FreeBSTR(pStruct->bsPatientID);
	FreeBSTR(pStruct->bsPatientName);
	FreeBSTR(pStruct->bsPatientFullName);
	FreeBSTR(pStruct->bsPatientComment);
	FreeBSTR(pStruct->bsEthnicGroup);
	FreeBSTR(pStruct->bsOtherPatientIDs);
	FreeBSTR(pStruct->bsOtherPatientName);
	FreeBSTR(pStruct->bsOccupation);
	FreeBSTR(pStruct->bsPatientFilePath);
}

void CBSTROpt::FreeStudyInfoStruct(StudyInfoStruct* pStruct)
{
	FreeBSTR(pStruct->bsStudyUID);
	FreeBSTR(pStruct->bsPatientUID);
	FreeBSTR(pStruct->bsReferringPhysicianName);
	FreeBSTR(pStruct->bsStudyDescription);
	FreeBSTR(pStruct->bsPatientHistory);
	FreeBSTR(pStruct->bsStudyImagePath);
	FreeBSTR(pStruct->bsOperatorName);
	FreeBSTR(pStruct->bsInstanceUID);
	FreeBSTR(pStruct->bsAccessionNumber);
	FreeBSTR(pStruct->bsPerformingPhysicianName);
}

void CBSTROpt::FreeSeriesInfoStruct(SeriesInfoStruct* pStruct)
{
	FreeBSTR(pStruct->bsSeriesUID);
	FreeBSTR(pStruct->bsStudyUID);
	FreeBSTR(pStruct->bsSeriesDescription);
	FreeBSTR(pStruct->bsSeriesFilePath); 
	FreeBSTR(pStruct->bsAprRegionName);
}

void CBSTROpt::FreeImageInfoStruct(ImageInfoStruct* pStruct)
{
	FreeBSTR(pStruct->bsImageUID); 
	FreeBSTR(pStruct->bsSeriesUID); 
	FreeBSTR(pStruct->bsImageFilePath); 
	FreeBSTR(pStruct->bsPatientOrientation);
	FreeBSTR(pStruct->bsAprOrganUID);
	FreeBSTR(pStruct->bsAprOrganName);
}

void CBSTROpt::FreePostProcessingInfo(PostProcessingInfo* pStruct)
{
	FreeBSTR(pStruct->bsImageUID); 
	FreeBSTR(pStruct->bsSeriesUID); 
	FreeBSTR(pStruct->bsProcessedImageFilePath);
}

void CBSTROpt::FreePSSIStructList(PSSIInfo* pStruct, long lLen)
{
	for (int i = 0; i < lLen; i++)
	{
		FreePSSIStruct(pStruct + i);
	}
}

void CBSTROpt::FreePSSIStruct(PSSIInfo* pStruct)
{
	FreeBSTR(pStruct->bsPatientID); 
	FreeBSTR(pStruct->bsPatientName); 
	FreeBSTR(pStruct->bsStudyID); 
	FreeBSTR(pStruct->bsSeriesID); 
	FreeBSTR(pStruct->bsImageID); 
}

void CBSTROpt::FreePAJob(PAJob* pJob)
{
	int i = 0;

	for (i = 0; i < pJob->vtrPatient.size(); i++)
	{
		FreePatientInfoStruct(&(pJob->vtrPatient[i]));
	}

	for (i = 0; i < pJob->vtrStudy.size(); i++)
	{
		FreeStudyInfoStruct(&(pJob->vtrStudy[i]));
	}

	for (i = 0; i < pJob->vtrSeries.size(); i++)
	{
		FreeSeriesInfoStruct(&(pJob->vtrSeries[i]));
	}

	for (i = 0; i < pJob->vtrImages.size(); i++)
	{
		FreeImageInfoStruct(&(pJob->vtrImages[i]));
	}

	for (i = 0; i < pJob->vtrPostProcess.size(); i++)
	{
		FreePostProcessingInfo(&(pJob->vtrPostProcess[i]));
	}

}
