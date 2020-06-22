
#ifndef __PADataBaseDefine_H__
#define __PADataBaseDefine_H__


const DWORD JOBINFO_TABLE_FIELD_NUM								= 5;

const DWORD JOBDETAILINFO_TABLE_FIELD_NUM						= 4;
const DWORD JOBPSSIINFO_TABLE_FIELD_NUM							= 7;
const DWORD JOBNETWORKNODEINFO_TABLE_FIELD_NUM					= 9;
const DWORD JOBDISCIMPORTIMAGEINFO_TABLE_FIELD_NUM				= 16;
const DWORD JOBUIDINFO_TABLE_FIELD_NUM							= 4;

const DWORD WORKLISTIMPORTEDSTUDYINFO_TABLE_FIELD_NUM			= 1;


CString JobInfo_Field[JOBINFO_TABLE_FIELD_NUM] = 
{
	_T("Index"),
	_T("JobID"),
	_T("Type"),
	_T("State"),
	_T("Progress"),
};

CString JobDetailInfo_Field[JOBDETAILINFO_TABLE_FIELD_NUM] = 
{
	_T("Index"),
	_T("JobID"),
	_T("DateTime"),
	_T("Detail"),
};

CString JobUIDInfo_Field[JOBUIDINFO_TABLE_FIELD_NUM] = 
{
	_T("Index"),
	_T("JobID"),
	_T("UID"),
	_T("UIDType"),
};

CString JobPSSIInfo_Field[JOBPSSIINFO_TABLE_FIELD_NUM] = 
{
	_T("Index"),
	_T("JobID"),
	_T("PatientID"),
	_T("PatientName"),
	_T("StudyID"),
	_T("SeriesID"),
	_T("ImageID"),
};

CString JobNetworkNodeInfo_Field[JOBNETWORKNODEINFO_TABLE_FIELD_NUM] = 
{
	_T("Index"),
	_T("JobID"),
	_T("Default"),
	_T("CalledAE"),
	_T("CallingAE"),
	_T("IP"),
	_T("Port"),
	_T("Raw"),
	_T("Processed"),
};

CString JobDiscImportImageInfo_Field[JOBDISCIMPORTIMAGEINFO_TABLE_FIELD_NUM] = 
{
	_T("Index"),
	_T("JobID"),
	_T("ImageUID"),
	_T("SeriesUID"),
	_T("StudyUID"),
	_T("PatientUID"),
	_T("ImageIndex"),
	_T("PatientID"),
	_T("PatientName"),
	_T("StudyID"),
	_T("SeriesID"),
	_T("ImageID"),
	_T("ReferencedFileID"),
	_T("State"),
	_T("Progress"),
	_T("DetailInfo"),
};

CString WorklistImportedStudyInfo_Field[WORKLISTIMPORTEDSTUDYINFO_TABLE_FIELD_NUM] = 
{
	_T("StudyInstanceUID"),
};

#endif // __PADataBaseDefine_H__