/* Time: <@(#)ConstDefine.h   2009-3-5 - 10:26:22   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : ConstDefine.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Constant definition
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:26:22		FanZF	Creation
 *
 *********************************************************************
 */

#ifndef __CONSTDEFINE_H__
#define __CONSTDEFINE_H__


const DWORD SUBMODULE_COUNT											= 5;
const DWORD SHUTDOWN_JOB_HANDLER_JOB_QUEUE_EXIT_WAIT_TIME			= 10000;
const DWORD SHUTDOWN_SUBMODULE_DISCIMPORT_CANCEL_GETDISCINFO_WAIT_TIME		= 4000;
const DWORD SHUTDOWN_SUBMODULE_MPPS_CANCEL_NPROC_WAIT_TIME			= 9000;




// For handle background job during Acq
#define HANDLE_PRINT_DURING_ACQ
#define HANDLE_TRANSFER_DURING_ACQ
#define HANDLE_BURN_DURING_ACQ
#define HANDLE_DISCIMPORT_DURING_ACQ


//<< For Printing&Archiving data base
#define PA_DATABASE_FILE_NAME								_T("P&ADB.mdb")
#define PA_DATABASE_PASSWORD								_T("admin")



// For MPPS Status
#define MPPS_STATUS_INPROGRESS								_T("IN PROGRESS")
#define MPPS_STATUS_COMPLETED								_T("COMPLETED")
#define MPPS_STATUS_DISCONTINUED							_T("DISCONTINUED")



/********************************************************/
const DWORD FIREMSGQUEUEMNG_WAIT_THREAD_EXIT_TIME = 1000;



// For \\Setting\\UIScheme.ini
#define UISCHEME_INI_FILE						_T("\\Setting\\UIScheme.ini")

// For \\Language\\ECVChinese.lng
#define SYSTEM_LANG_FILE						_T("\\Language\\Printing&Archiving_chs.lng")

// For FilmComposer Full Path
#define FILMCOMPOSER_DIRECTORY					_T("\\dragon")
#define FILMCOMPOSER_PROCNAME					_T("FilmComposer.exe")

// For CVDicomViewer Full Path
#define AUTOVIEW_DIRECTORY						_T("\\AutoView")
#define CVDICOMVIEWER_DIRECTORY					_T("\\MaxViewer")
#define CVDICOMVIEWER_AUTORUN_FILE				_T("\\AutoRun.inf")


// For FilmComposer send and recv message
const UINT FILMCOMPOSER_SOCKET_BUFFER_LEN		= 16;

#define FILMCOMPOSER_STATUS_PRINTING			_T("PRINTING")
#define FILMCOMPOSER_STATUS_SUCCESS				_T("SUCCESS")
#define FILMCOMPOSER_STATUS_ERROR				_T("PRINTERROR")
#define FILMCOMPOSER_STATUS_STOPOVER			_T("STOPOVER")
#define FILMCOMPOSER_STATUS_BREAK				_T("BREAK")
#define FILMCOMPOSER_IMAGES_LIMITED				_T("LIMITED")
#define FILMCOMPOSER_STATUS_INVALID_PRINTER		_T("ERROR:Have no valid printer")
#define FILMCOMPOSER_RECEIVED_OK				_T("2OK")

#define FILMCOMPOSER_SEND_SUSPEND				_T("2STOP")
#define FILMCOMPOSER_SEND_SHOW_PROGRESSBAR		_T("2SHOWPROGRESS")
#define FILMCOMPOSER_SEND_HIDE_PROGRESSBAR		_T("2HIDEPROGRESS")

#define FILMCOMPOSER_CMDLINE_LOADIMAGE			_T("-f")
#define FILMCOMPOSER_CMDLINE_ROW				_T("-row")
#define FILMCOMPOSER_CMDLINE_COL				_T("-col")
#define FILMCOMPOSER_CMDLINE_CLOSE				_T("-close")

#define FILMCOMPOSER_HOST_ADRESS				("127.0.0.1")
const unsigned short FILMCOMPOSER_SERVER_PORT			= 8888;
const unsigned short FILMCOMPOSER_CLIENT_PORT			= 6666;

const UINT FILMCOMPOSER_CONNECT_SVR_RETRY_TIMES			= 5;
const DWORD FILMCOMPOSER_MONITOR_INSPECT_TIME			= 5000;
const DWORD FILMCOMPOSER_MONITOR_THREAD_EXIT_WAIT_TIME	= 1000;

const DWORD FILMCOMPOSER_LOADIMAGES_MAX_PER_TIME		= 1;

const DWORD PRINT_JOB_IMAGES_COUNT_LIMITATION			= 100;

const DWORD	FILMCOMPOSER_SEND_CMD_RETRY_TIMES			= 3;
const DWORD	FILMCOMPOSER_RECEIVE_OK_WAIT_TIME			= 100;


// Config Dir
#define SYSTEM_CONFIG_DIR						_T("\\Config")

// LUT Dir
#define SYSTEM_LUT_DIR							_T("\\LUT")


// For Raw and DICOM Image Path
#define	IS_PATH									_T("E:\\images")

#define	DICOM_IMAGE_STORE_PATH					_T("F:\\DcmCache")
#define	DICOM_IMAGE_PRINT_STORE_PATH			_T("F:\\DcmCache\\Print")
#define	DICOM_IMAGE_TRANSFER_STORE_PATH			_T("F:\\DcmCache\\Send")
#define	DICOM_IMAGE_BURN_STORE_PATH				_T("F:\\DcmCache\\Burn")
#define DICOM_IMAGE_WORK_DIR					_T("\\Work")

#define DICOM_CACHE_DIR							_T("\\Cache")
#define DICOM_DCM_DIR							_T("\\DICOM")
#define DICOM_BMP_DIR							_T("\\BMP")
#define DICOM_JPEG_DIR							_T("\\JPEG")

#define DICOM_DCM_PATIENT_DIR_PREFIX			_T("P")
#define DICOM_DCM_STUDY_DIR_PREFIX				_T("STUDY")
#define DICOM_DCM_SERIES_DIR_PREFIX				_T("SERIES")

#define DICOM_DCM_RAW_IMAGE_PREFIX				_T('R')
#define DICOM_DCM_PROC_IMAGE_PREFIX				_T('P')
#define DICOM_DCM_PS_FILE_EXTEND_NAME			_T(".pre")



#define DICOM_XA_BMP_NAME_PREFIX				_T("BX")
#define DICOM_SC_BMP_NAME_PREFIX				_T("BC")
#define DICOM_XA_JPEG_NAME_PREFIX				_T("JX")
#define DICOM_SC_JPEG_NAME_PREFIX				_T("JC")

#define DICOM_BMP_EXTEND_NAME					_T(".bmp")
#define DICOM_JPEG_EXTEND_NAME					_T(".jpeg")

#define RAW_IMAGE_EXTEND_NAME					_T(".raw")

// For Anno File path
#define ANNO_FILE_STORAGE_DRIVER				_T("F:\\Annotations")
#define ANNO_FILE_NAME_EXTEND					_T(".AnnoProperty")
#define	IP_DISPLAYLUT_FILE_NAME					_T("DisplayLUT.raw")

// For UserGuidance.dll
#define USERGUIDANCE_DLL_PATH					_T("\\UserGuidanceRes.dll")


// For DB
const DWORD WAITING_FOR_DB_STARTUP_TIME			= 1000;


/**************************Burn***********************************/

// Disc Name
#define BURN_DISC_NAME_BACKUP					_T("Backup Disc")
#define BURN_DISC_NAME_EXPORT					_T("Export Disc")
#define BURN_DISC_NAME_PREFIX					_T("MaxViewer")


// data CD/DVD block size
const UINT BURN_DATA_CD_BLOCK_SIZE				= 2048;
const UINT BURN_DATA_DVD_BLOCK_SIZE				= 2048;

const double HARDDISK_FREE_SPACE_SAFETY_COEFFICIENT = 0.8f;

//<< BMP and JPEG file size
const double BURN_BMP_SIZE						= 1024*1024*9;	//<< 9M
const double BURN_JPEG_SIZE						= 1024*1024;	//<< 1M


const DWORD THREADE_RET_CODE_OK					= 0;
const DWORD THREADE_RET_CODE_ERROR				= 1;


/**********************/
const DWORD IS_CONNECT_RAW_IMAGE_DISK_WAIT_TIME		= 1000;


/******************** Image compress rate *************************/
const double IMAGE_COMPRESS_RATE_1024_SF			= 1.0f;
const double IMAGE_COMPRESS_RATE_512_SF				= 60.0f;
const double IMAGE_COMPRESS_RATE_1024_MF			= 2.5f;
const double IMAGE_COMPRESS_RATE_512_MF				= 60.0f;
const double IMAGE_COMPRESS_RATE_BMP				= 2.0f;
const double IMAGE_COMPRESS_RATE_JPEG				= 25.0f;

/******************************************************************/



// For Print Working State
const DWORD PWS_UNWORKING					= 0x00;
const DWORD PWS_JOBWORKING					= 0x01;
const DWORD PWS_FCWORKING					= 0x02;
const DWORD PWS_JOBUNWORKING				= ~0x01;
const DWORD PWS_FCUNWORKING					= ~0x02;




/*******************************************************************/
#ifndef PA_CATCH_ERROR
#define PA_CATCH_ERROR \
	catch(_com_error &e) \
{ \
		CString strComError;  \
		strComError.Format(_T("Error code: %08x"),e.Error()); \
		GenWriteTrace(ECVTRACE_LEVEL_ERROR,ECVU_Printing_and_Archiving,strComError,__FILE__,__LINE__); \
		strComError.Format(_T("Error message: %s"),e.ErrorMessage()); \
		GenWriteTrace(ECVTRACE_LEVEL_ERROR,ECVU_Printing_and_Archiving,strComError,__FILE__,__LINE__); \
		strComError.Format(_T("Error source: %s"),(LPCTSTR)e.Source()); \
		GenWriteTrace(ECVTRACE_LEVEL_ERROR,ECVU_Printing_and_Archiving,strComError,__FILE__,__LINE__); \
		strComError.Format(_T("Error description: %s"),(LPCTSTR)e.Description()); \
		GenWriteTrace(ECVTRACE_LEVEL_ERROR,ECVU_Printing_and_Archiving,strComError,__FILE__,__LINE__); \
		return S_FALSE;\
} \
	catch (...)\
{ \
		GenWriteTrace(ECVTRACE_LEVEL_ERROR,ECVU_Printing_and_Archiving,_T("Catch exception error in interface"),__FILE__,__LINE__); \
		return S_FALSE; \
}
#endif // #define PA_CATCH_ERROR

#ifndef PA_CATCH_ERROR_RET
#define PA_CATCH_ERROR_RET(ret) \
	catch (...)\
{ \
		GenWriteTrace(ECVTRACE_LEVEL_ERROR,ECVU_Printing_and_Archiving,_T("Catch exception error"),__FILE__,__LINE__); \
		return (ret); \
}
#endif // #define PA_CATCH_ERROR_RET

#ifndef PA_CATCH_ERROR_NORET
#define PA_CATCH_ERROR_NORET \
	catch (...)\
{ \
		GenWriteTrace(ECVTRACE_LEVEL_ERROR,ECVU_Printing_and_Archiving,_T("Catch exception error"),__FILE__,__LINE__); \
		return; \
}
#endif // #define PA_CATCH_ERROR_RET

#endif // __CONSTDEFINE_H__