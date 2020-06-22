/* Time: <@(#)OutputStrDefine.h   2009-3-5 - 10:27:05   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : OutputStrDefine.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : output string definition
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:27:05		FanZF	Creation
 *
 *********************************************************************
 */

#ifndef __OUTPUTSTRDEFINE_H__
#define __OUTPUTSTRDEFINE_H__


// For Job Type
#define JOB_TYPE_BURN							_T("Export")			//<< 导出
#define JOB_TYPE_SEND_AUTO						_T("Send(auto)")		//<< 发送（自动）
#define JOB_TYPE_SEND_MANUAL					_T("Send(manual)")		//<< 发送（手动）
#define JOB_TYPE_IMPORT							_T("Import")			//<< 导入

// For Job State
#define JOB_STATE_SUBMITTED						_T("Submitted")			//<< 已提交
#define JOB_STATE_EXECUTING						_T("Executing")			//<< 正在执行
#define JOB_STATE_COMPLETED						_T("Completed")			//<< 已完成
#define JOB_STATE_CANCELLED						_T("Cancelled")			//<< 已取消
#define JOB_STATE_FAILED						_T("Failed")			//<< 失败


// For Job Phase
#define JOB_PHASE_NONE							_T("")
#define JOB_PHASE_IMAGE_CONVERSION				_T("Preprocessing")		//<< 预处理
#define JOB_PHASE_TRANSFER						_T("Send")				//<< 发送
#define	JOB_PHASE_BURN							_T("Export")			//<< 导出（注：前面已有）
#define JOB_PHASE_IMPORT						_T("Import")			//<< 导入（注：前面已有）



// For Job Detail
#define JOB_DETAIL_SUBMITED						_T("Job submited")				//<< 任务已提交
#define JOB_DETAIL_START						_T("Job start")					//<< 任务已开始

#define JOB_DETAIL_CACHESPACE_NOTENOUGH			_T("Too many images contained in the Job, not enough cache spaces")			//<< 任务包含太多图像，磁盘缓存空间不足

#define JOB_DETAIL_PHASE_PREPROCESSING			_T("Preprocessing...")						//<< 正在预处理...
#define JOB_DETAIL_PHASE_PREPROC_COMPLETED		_T("Preprocessing completed")				//<< 预处理完成
#define JOB_DETAIL_PHASE_PREPROC_FAILED			_T("Preprocessing failed")					//<< 预处理失败

#define JOB_DETAIL_SEND_CONNECTING_SERVER		_T("Connecting to server (%s)...")			//<< 正在连接服务器（%s）...
#define JOB_DETAIL_SEND_CONNECTING_FAILED		_T("Failed to connect server (%s)")			//<< 连接服务器（%s）失败
#define JOB_DETAIL_SEND_SENDING_IMAGES			_T("Sending images to server (%s)...")		//<< 正在向服务器（%s）发送图像...
#define JOB_DETAIL_SEND_SENDING_FAILED			_T("Failed to send images to server (%s)")		//<< 向服务器（%s）发送图像失败
#define JOB_DETAIL_SEND_SENDING_COMPLETED		_T("Completed to send images to server (%s)")	//<< 向服务器（%s）发送图像完成
#define JOB_DETAIL_SEND_DISCONN_SERVER			_T("Disconnect server (%s)")				//<< 断开服务器（%s）

#define JOB_DETAIL_IMPORT_IMPORTING				_T("Importing to system...")				//<< 正在导入到系统...

#define JOB_DETAIL_ERROR_OCCURRED				_T("Error occurred")						//<< 发生错误

#define JOB_DETAIL_FAILED						_T("Job failed")							//<< 任务失败
#define JOB_DETAIL_CANCELLED					_T("Job cancelled")							//<< 任务已取消
#define JOB_DETAIL_COMPLETED					_T("Job completed")							//<< 任务已完成



// For Burn Device Media Info
#define BURN_DMI_BLANK_MEDIA					_T("(Blank media)")			// 空白光盘
#define BURN_DMI_UNBLANK_MEDIA					_T("(Not blank media)")		// 非空白无光盘
#define BURN_DMI_NO_MEDIA						_T("No media")				// 无光盘
#define BURN_DMI_MAXSPEED						_T("Max Speed")				// 最大速度
#define BURN_DMI_MINSPEED						_T("Min Speed")				// 最小速度


// For Get Disc Info State of Disc Import
#define DISCIMPORT_GET_DI_STATE_START			_T("Reading importing disc...")				// 正在读取导入光盘...
#define DISCIMPORT_GET_DI_STATE_ERROR			_T("Error occurred, failed to read disc")	// 发生错误，读取光盘失败
#define DISCIMPORT_GET_DI_STATE_NO_DISC			_T("No importing disc")						// 无导入光盘 (注:光驱中没有光盘)
#define DISCIMPORT_GET_DI_STATE_FAILED			_T("Error occurred, failed to read disc")	// 发生错误，读取光盘失败（注：前面已有）
#define DISCIMPORT_GET_DI_STATE_INVALID_IMPORTING_DISC	_T("Invalid importing disc")			// 无效的导入光盘 (注:光驱中有盘,但不是导入光盘)
#define DISCIMPORT_GET_DI_STATE_SUCCEED			_T("Succeeded in reading importing disc")		// 读取导入光盘成功

// For Disc Import Series State
#define DISCIMPORT_SERIES_STATE_WAITING			_T("Waiting")					// 等待中
#define DISCIMPORT_SERIES_STATE_IMPORTING		_T("Importing")					// 正在导入
#define DISCIMPORT_SERIES_STATE_COMPLETED		_T("Completed")					// 已完成（注：前面已有）
#define DISCIMPORT_SERIES_STATE_SKIPPED			_T("Skipped")					// 跳过
#define DISCIMPORT_SERIES_STATE_FAILED			_T("Failed")					// 失败（注：前面已有）
#define DISCIMPORT_SERIES_STATE_CANCELLED		_T("Cancelled")					// 已取消（注：前面已有）



// For Disc Import Series Detail Info
// Imported Series Detail Info (SDI)
#define DISCIMPORT_SDI_IMPORTING_TO_SYSTERM					_T("Importing to system...")			// 正在导入到系统...（注：前面已有）
#define DISCIMPORT_SDI_IMPORTING_FAILED						_T("Importing Failed")				// 导入失败
#define DISCIMPORT_SDI_NOT_ENOUGH_FREE_DISK_SPACE			_T("Not enough free disk space")	// 磁盘空间不足
#define DISCIMPORT_SERIES_COMPLETED_INFO_FORMAT			_T("Imported, Patient ID: %s, Patient Name: %s, Study ID: %s, Series ID: %s, Image ID: %s")		//<< 已导入，患者序号：%s，患者姓名：%s，检查序号：%s，序列序号：%s，图像序号：%s
#define DISCIMPORT_SERIES_SKIPPED_INFO_FORMAT			_T("Image exists in system, Patient ID: %s, Patient Name: %s, Study ID: %s, Series ID: %s, Image ID: %s")	//<< 图像已存在，患者序号：%s，患者姓名：%s，检查序号：%s，序列序号：%s，图像序号：%s



#endif // __OUTPUTSTRDEFINE_H__