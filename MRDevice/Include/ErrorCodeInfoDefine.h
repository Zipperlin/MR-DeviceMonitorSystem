/* Time: <@(#)ErrorCodeInfoDefine.h   2009-3-5 - 10:26:43   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : ErrorCodeInfoDefine.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Error code information definition
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:26:43		FanZF	Creation
 *
 *********************************************************************
 */

#ifndef __ERRORCODEINFODEFINE_H__
#define __ERRORCODEINFODEFINE_H__


#define E_OK_INFO									_T("OK")
#define E_UNEXPECTED_ERROR_INFO								_T("Unexpected error")
#define E_INVALID_PARA_INFO						_T("Invalid parameter")

#define E_BURN_START_INFO							_T("")
#define E_BURN_NERO_API_UNINITED_INFO					_T("Nero API Uninited")
#define E_BURN_NERO_API_INIT_FAILED_INFO				_T("Nero API Init failed")
#define E_BURN_NO_DEVICE_FOUND_INFO						_T("No device found")
#define E_BURN_NO_SPECIFIED_DEVICE_INFO						_T("No specified device found")
#define E_BURN_NO_DISC_OR_DISC_CORRUPTED_INFO						_T("No disc or disc corrupted")
#define E_BURN_MEDIA_NOT_DVD_INFO						_T("Disc is not DVD")
#define E_BURN_MEDIA_NOT_CD_INFO						_T("Disc is not CD")
#define E_BURN_DISC_NOT_WRITEABLE_INFO						_T("Disc is not writable")
#define E_BURN_NOT_SUPPORT_BURNING_SPECIFIED_MEDIA_INFO						_T("Device can't write this type of disc")
#define E_BURN_CANT_OPEN_NERO_API_DLL_INFO						_T("Can't open Nero API dll")
#define E_BURN_NERO_API_INVALID_SERIAL_NUM_INFO						_T("Nero API invalid serial number")
#define E_BURN_NO_BURN_DIR_OR_FILE_INFO						_T("No burn dirs or files")
#define E_BURN_DEVICE_NOT_SPECIFIED_INFO					_T("Device not specified")
#define E_BURN_OPEN_DEVICE_FAILED_INFO							_T("Open device failed")
#define E_BURN_NERO_MEMORY_LEAK_INFO							_T("Nero memory leak!")
#define E_BURN_UNSET_DISC_NAME_INFO						_T("Disc name unset")
#define E_BURN_UNSET_DISC_TYPE_INFO						_T("Disc type unset")
#define E_BURN_UNSET_BURN_SPEED_INFO						_T("Burn speed unset")
#define E_BURN_NOT_APPLICABLE_DURING_BURNING_INFO						_T("not applicable during running")
#define E_BURN_A_BURN_THREAD_IS_ALREADY_RUNNING_INFO						_T("A burn thread is already running")
#define E_BURN_NOT_EMPTY_DISC_INFO							_T("Not a empty disc")
#define E_BURN_FILES_NAME_CONFLICT_INFO						_T("Name of dirs or files conflict")
#define E_BURN_INVALID_DIR_OR_FILE_INFO						_T("Invalid dir or file")
#define E_BURN_DISC_NAME_TOO_LONG_INFO						_T("Disc name should be less than 64 bytes")
#define E_BURN_USER_ABORT_INFO						_T("User abort burning")


#endif // __ERRORCODEINFODEFINE_H__