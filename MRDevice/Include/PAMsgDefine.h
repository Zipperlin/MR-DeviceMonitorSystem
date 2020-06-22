/* Time: <@(#)PAMsgDefine.h   2009-3-5 - 10:27:32   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : PAMsgDefine.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Messages definition
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:27:32		FanZF	Creation
 *
 *********************************************************************
 */

#ifndef __PAMSGDEFINE_H__
#define __PAMSGDEFINE_H__



// For Notify
const UINT NOTIFY_CPA_STARTUPRESULT				= 1;
const UINT NOTIFY_CPA_WORKSTATE					= 2;


const UINT NOTIFY_PRINT							= 3;
const UINT NOTIFY_TRANSFER						= 4;
const UINT NOTIFY_BURN							= 5;

const UINT NOTIFY_FC_STARTUP					= 6;
const UINT NOTIFY_FC_STATE_CHANGED				= 7;
const UINT NOTIFY_FC_LOAD_IMAGE_LIMITED			= 8;
const UINT NOTIFY_FC_LOAD_IMAGE_PROGRESS		= 9;
const UINT NOTIFY_FC_INVALID_PRINTER			= 10;
const UINT NOTIFY_FC_ENABLE_FC					= 11;


const UINT NOTIFY_BURN_DEVICE_STATUS			= 12;
const UINT NOTIFY_BURN_ERROR					= 13;
const UINT NOTIFY_BURN_MEDIA_NOT_READY			= 14;
const UINT NOTIFY_BURN_DEVICE_MEDIA_INFO_SPEED	= 15;
const UINT NOTIFY_BURN_DEVICE_MEDIA_INFO_MEDIA	= 16;

const UINT NOTIFY_JOB_DETAIL_CHANGED			= 17;
const UINT NOTIFY_JOB_PROGRESS_CHANGED			= 18;
const UINT NOTIFY_JOB_PHASE_CHANGED				= 19;
const UINT NOTIFY_JOB_STATE_CHANGED				= 20;
const UINT NOTIFY_JOB_QUEUE_CHANGED				= 21;

const UINT NOTIFY_SUBMODULE_STATE_CHANGED		= 22;

const UINT NOTIFY_USERGUIDANCE					= 23;

const UINT NOTIFY_HARDDISK_FREE_SPACE_NOT_ENOUGH		= 24;

const UINT NOTIFY_BURN_PATIENTS_INFO					= 25;
const UINT NOTIFY_BURN_STUDYS_INFO						= 26;
const UINT NOTIFY_BURN_SERIES_INFO						= 27;
const UINT NOTIFY_BURN_IMAGE_INFO						= 28;

const UINT NOTIFY_IMPORT_SERIES_STATE_CHANGED			= 29;
const UINT NOTIFY_IMPORT_SERIES_PROGRESS_CHANGED		= 30;
const UINT NOTIFY_IMPORT_SERIES_DETIAL_CHANGED			= 31;
const UINT NOTIFY_IMPORT_ONE_IMAGE_IMPORTED				= 38;
const UINT NOTIFY_IMPORT_ONE_JOB_FINISHED				= 39;

const UINT NOTIFY_DISCIMPORT_GET_DISCINFO_STATE			= 32;
const UINT NOTIFY_DISCIMPORT_DISCINFO_READY				= 33;

const UINT NOTIFY_WLMPPS_REPORT_WORKLIST				= 34;
const UINT NOTIFY_WLMPPS_SET_MPPS_FINISHED				= 35;
const UINT NOTIFY_WLMPPS_MPPS_STATUS_CHANGED			= 36;

const UINT NOTIFY_UI_DB_CHANGED							= 37;


// For Connection points messages
const UINT CP_ACQ_EXPOSURE_FLUO_PREPARING				= 200;



#endif // __PAMSGDEFINE_H__