/* Time: <@(#)PAStructDefine.h   2009-3-5 - 10:27:56   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : PAStructDefine.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Structure definition
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:27:56		FanZF	Creation
 *
 *********************************************************************
 */

#ifndef __PAStructDefine_H__
#define __PAStructDefine_H__

class CMppsOpt;

typedef struct _TagNetworkNodeStruct
{
	BOOL bDefault;
	CString strCalledAE;
	CString strCallingAE;
	CString strIP;
	CString strPort;
	BOOL bRaw;
	BOOL bProcessed;

	// Add [Sun hongwen 10/16/2009]
	BOOL bSendPS;
	//

}NetworkNodeStruct;


typedef struct _TagJobDetail
{
	SYSTEMTIME			stDateTime;
	CString				strDetail;

}JobDetail;

typedef enum _TagBurnAbortSetting
{
	enumBurnAbortSetting_None				= 0,
	enumBurnAbortSetting_Abort				= 1,
	enumBurnAbortSetting_AbortAndReburn		= 2
}BurnAbortSetting;

typedef enum _TagPrintWorkingState
{
	enumPrintWorkingState_UnWorking				= 0,
	enumPrintWorkingState_JobWorking			= 1,
	enumPrintWorkingState_FCWorking				= 2,
	enumPrintWorkingState_JobUnWorking			= 3,
	enumPrintWorkingState_FCUnWorking			= 4
}PrintWorkingState;

typedef enum _DiscImport_ImageState
{
	enumSeriesState_Waiting			= 0,
	enumSeriesState_Importing		= 1,
	enumSeriesState_Completed		= 2,
	enumSeriesState_Skipped			= 3,
	enumSeriesState_Failed			= 4,
	enumSeriesState_Cancelled		= 5
}DiscImport_ImageState;


typedef enum _DiscImport_SeriesProgress
{	
	enumSeriesProgress_None			= 0,
	enumSeriesProgress_Percentage	= 1
}DiscImport_SeriesProgress;

typedef struct _tagDiscImport_Image
{
	// 导入前图像信息

	CString						strImageUID;
	CString						strSeriesUID;
	CString						strStudyUID;
	CString						strPatientUID;

	CString						strIndex;
	CString						strPatientID;
	CString						strPatientName;
	CString						strStudyID;
	CString						strSeriesID;
	CString						strImageID;

	CString						strReferencedFileID;

	// 状态
	DiscImport_ImageState		enumState;

	// 进度
	CString						strProgress;

	// 详细信息
	CString						strDetailInfo;

}DiscImport_Image;

typedef struct _tagStudyMppsStatusStruct
{
	CString						strStudyUID;
	WorkListStatus				enumStatus;
}StudyMppsStatusStruct;


typedef struct _tagMppsStatusStruct
{

	CString						strStudyUID;
	WorkListStatus				enumStatus;

	CString						strPatientUID;

	HANDLE						hThread;

	CMppsOpt*					pMppsOpt;

	// whether Report (by connection point) the SET is finished or not
	BOOL						bReport;

}MppsStatusStruct;


typedef struct _tagGetImportDiscInfoStruct
{
	CString						strDevice;
	
	HANDLE						hThread;

	HANDLE						hFindDcmDir;
	CDcmDirParser*				pDcmDirParser;

	BOOL						bValid;

}GetImportDiscInfoStruct;


typedef struct _tagPatientDirStruct
{
	CString						strPatientID;
	CString						strPatientDir;

}PatientDirStruct;

typedef struct _TagBurnJobSettingsStruct
{
	PatientAdminUIDType		enumUIDType;

	LONG				lBurnSpeed;

	BOOL				bBMP;
	BOOL				bJPEG;
}BurnJobSettingsStruct;

typedef struct _TagPrintJobSettingsStruct
{

}PrintJobSettingsStruct;

typedef struct _TagTransferJobSettingsStruct
{
	PatientAdminUIDType		enumUIDType;
	vector<NetworkNodeStruct>	vtrNodes;

}TransferJobSettingsStruct;

typedef struct _TagDiscImportJobSettingsStruct
{
	CString						strDevice;
	vector<DiscImport_Image>	vtrImagesToBeImported;

}DiscImportJobSettingsStruct;



#endif // __PAStructDefine_H__