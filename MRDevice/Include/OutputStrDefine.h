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
#define JOB_TYPE_BURN							_T("Export")			//<< ����
#define JOB_TYPE_SEND_AUTO						_T("Send(auto)")		//<< ���ͣ��Զ���
#define JOB_TYPE_SEND_MANUAL					_T("Send(manual)")		//<< ���ͣ��ֶ���
#define JOB_TYPE_IMPORT							_T("Import")			//<< ����

// For Job State
#define JOB_STATE_SUBMITTED						_T("Submitted")			//<< ���ύ
#define JOB_STATE_EXECUTING						_T("Executing")			//<< ����ִ��
#define JOB_STATE_COMPLETED						_T("Completed")			//<< �����
#define JOB_STATE_CANCELLED						_T("Cancelled")			//<< ��ȡ��
#define JOB_STATE_FAILED						_T("Failed")			//<< ʧ��


// For Job Phase
#define JOB_PHASE_NONE							_T("")
#define JOB_PHASE_IMAGE_CONVERSION				_T("Preprocessing")		//<< Ԥ����
#define JOB_PHASE_TRANSFER						_T("Send")				//<< ����
#define	JOB_PHASE_BURN							_T("Export")			//<< ������ע��ǰ�����У�
#define JOB_PHASE_IMPORT						_T("Import")			//<< ���루ע��ǰ�����У�



// For Job Detail
#define JOB_DETAIL_SUBMITED						_T("Job submited")				//<< �������ύ
#define JOB_DETAIL_START						_T("Job start")					//<< �����ѿ�ʼ

#define JOB_DETAIL_CACHESPACE_NOTENOUGH			_T("Too many images contained in the Job, not enough cache spaces")			//<< �������̫��ͼ�񣬴��̻���ռ䲻��

#define JOB_DETAIL_PHASE_PREPROCESSING			_T("Preprocessing...")						//<< ����Ԥ����...
#define JOB_DETAIL_PHASE_PREPROC_COMPLETED		_T("Preprocessing completed")				//<< Ԥ�������
#define JOB_DETAIL_PHASE_PREPROC_FAILED			_T("Preprocessing failed")					//<< Ԥ����ʧ��

#define JOB_DETAIL_SEND_CONNECTING_SERVER		_T("Connecting to server (%s)...")			//<< �������ӷ�������%s��...
#define JOB_DETAIL_SEND_CONNECTING_FAILED		_T("Failed to connect server (%s)")			//<< ���ӷ�������%s��ʧ��
#define JOB_DETAIL_SEND_SENDING_IMAGES			_T("Sending images to server (%s)...")		//<< �������������%s������ͼ��...
#define JOB_DETAIL_SEND_SENDING_FAILED			_T("Failed to send images to server (%s)")		//<< ���������%s������ͼ��ʧ��
#define JOB_DETAIL_SEND_SENDING_COMPLETED		_T("Completed to send images to server (%s)")	//<< ���������%s������ͼ�����
#define JOB_DETAIL_SEND_DISCONN_SERVER			_T("Disconnect server (%s)")				//<< �Ͽ���������%s��

#define JOB_DETAIL_IMPORT_IMPORTING				_T("Importing to system...")				//<< ���ڵ��뵽ϵͳ...

#define JOB_DETAIL_ERROR_OCCURRED				_T("Error occurred")						//<< ��������

#define JOB_DETAIL_FAILED						_T("Job failed")							//<< ����ʧ��
#define JOB_DETAIL_CANCELLED					_T("Job cancelled")							//<< ������ȡ��
#define JOB_DETAIL_COMPLETED					_T("Job completed")							//<< ���������



// For Burn Device Media Info
#define BURN_DMI_BLANK_MEDIA					_T("(Blank media)")			// �հ׹���
#define BURN_DMI_UNBLANK_MEDIA					_T("(Not blank media)")		// �ǿհ��޹���
#define BURN_DMI_NO_MEDIA						_T("No media")				// �޹���
#define BURN_DMI_MAXSPEED						_T("Max Speed")				// ����ٶ�
#define BURN_DMI_MINSPEED						_T("Min Speed")				// ��С�ٶ�


// For Get Disc Info State of Disc Import
#define DISCIMPORT_GET_DI_STATE_START			_T("Reading importing disc...")				// ���ڶ�ȡ�������...
#define DISCIMPORT_GET_DI_STATE_ERROR			_T("Error occurred, failed to read disc")	// �������󣬶�ȡ����ʧ��
#define DISCIMPORT_GET_DI_STATE_NO_DISC			_T("No importing disc")						// �޵������ (ע:������û�й���)
#define DISCIMPORT_GET_DI_STATE_FAILED			_T("Error occurred, failed to read disc")	// �������󣬶�ȡ����ʧ�ܣ�ע��ǰ�����У�
#define DISCIMPORT_GET_DI_STATE_INVALID_IMPORTING_DISC	_T("Invalid importing disc")			// ��Ч�ĵ������ (ע:����������,�����ǵ������)
#define DISCIMPORT_GET_DI_STATE_SUCCEED			_T("Succeeded in reading importing disc")		// ��ȡ������̳ɹ�

// For Disc Import Series State
#define DISCIMPORT_SERIES_STATE_WAITING			_T("Waiting")					// �ȴ���
#define DISCIMPORT_SERIES_STATE_IMPORTING		_T("Importing")					// ���ڵ���
#define DISCIMPORT_SERIES_STATE_COMPLETED		_T("Completed")					// ����ɣ�ע��ǰ�����У�
#define DISCIMPORT_SERIES_STATE_SKIPPED			_T("Skipped")					// ����
#define DISCIMPORT_SERIES_STATE_FAILED			_T("Failed")					// ʧ�ܣ�ע��ǰ�����У�
#define DISCIMPORT_SERIES_STATE_CANCELLED		_T("Cancelled")					// ��ȡ����ע��ǰ�����У�



// For Disc Import Series Detail Info
// Imported Series Detail Info (SDI)
#define DISCIMPORT_SDI_IMPORTING_TO_SYSTERM					_T("Importing to system...")			// ���ڵ��뵽ϵͳ...��ע��ǰ�����У�
#define DISCIMPORT_SDI_IMPORTING_FAILED						_T("Importing Failed")				// ����ʧ��
#define DISCIMPORT_SDI_NOT_ENOUGH_FREE_DISK_SPACE			_T("Not enough free disk space")	// ���̿ռ䲻��
#define DISCIMPORT_SERIES_COMPLETED_INFO_FORMAT			_T("Imported, Patient ID: %s, Patient Name: %s, Study ID: %s, Series ID: %s, Image ID: %s")		//<< �ѵ��룬������ţ�%s������������%s�������ţ�%s��������ţ�%s��ͼ����ţ�%s
#define DISCIMPORT_SERIES_SKIPPED_INFO_FORMAT			_T("Image exists in system, Patient ID: %s, Patient Name: %s, Study ID: %s, Series ID: %s, Image ID: %s")	//<< ͼ���Ѵ��ڣ�������ţ�%s������������%s�������ţ�%s��������ţ�%s��ͼ����ţ�%s



#endif // __OUTPUTSTRDEFINE_H__