/* Time: <@(#)WlMpps.h   2009-3-5 - 10:34:07   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : WlMpps.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Capsulation class of worklist and MPPS function
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:34:07		FanZF	Creation
 *
 *********************************************************************
 */

// WlMpps.h: interface for the CWlMpps class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __WLMPPS_H__
#define __WLMPPS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "ASBasis.h"
#include "PALib_i.h"
#include "DBController.h"
#include "WorklistIniOpt.h"
#include "MPPSIniOpt.h"
#include <vector>
#include <list>
using namespace std;


class CWlMpps : public NSubject
{
public:
	virtual ~CWlMpps();
	
	static CWlMpps* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	BOOL UnInit();
	
	//<< ������ģ��״̬
	void SetSubModuleState(SubModuleState enumSubModuleState);
	//<< �����ģ��״̬
	SubModuleState GetSubModuleState();

	//<< WorkList
	//<< ���Worklist֪ͨ
	BOOL GetWorkList();
	//<< ˢ��Worklist
	BOOL RefreshWorkList(WorkListQueryCond* pWorkListQueryCond);
	//<< ��û��߼��ṹ
	BOOL GetPatientStudyStruct(LPCTSTR szStudyInstanceUID, WLPatientStudyStruct* pStruct);
	//<< �жϼ���Ƿ��ѱ�����
	BOOL IsStudyImported(LPCTSTR szStudyInstanceUID, WLPatientStudyStatusInDB* pStatus);
	//<< һ����鱻����
	BOOL StudyImported(LPCTSTR szStudyInstanceUID);

	//<< WorkList�Ƿ����ڹ���
	BOOL IsWorkListWorking();

	//<< Worklist��ѯ����
	BOOL QueryProc();
	//<< ȡ��worklist��ѯ
	BOOL CancelQuery();

	//<< ����worklist����״̬
	void UpdateWorklistWorkState(BOOL bWorking);


	//<< MPPS
	//<< MPPS�Ƿ���Ч
	BOOL IsMPPSValid(BOOL* pbValid);
	//<< �жϼ��MPPS״̬�Ƿ�ʹ��
	BOOL IsSetMPPSStatusEnabled(LPCTSTR szStudyUID, BOOL* pbEnabled);
	//<< ��ü��MPPS״̬
	BOOL GetStudyMppsStatus(LPCTSTR szStudyUID, WorkListStatus* penumStatus);
	//<< ����MPPS״̬
	BOOL SetMppsStatus(LPCTSTR szStudyUID, WorkListStatus enumStatus);
	//<< ����MPPS״̬����
	BOOL SetMppsStatusProc(MppsStatusStruct* pStruct);

	//<< ֪ͨUIһ��MPPS״̬���������
	void NotifySetMppsFinished(LPCTSTR szStudyUID, WorkListStatus enumStatus, BOOL bResult);

	//<< ��MPPS�����б������һ��ָ������
	BOOL RemoveMppsStatusStruct(LPCTSTR szStudyUID, WorkListStatus enumStatus);

	//<< MPPS�Ƿ����ڹ���
	BOOL IsMppsWorking();

	//<< �Ƿ�ָ���ļ�����ڹر�MPPS
	BOOL IsClosingStudyMPPS(LPCTSTR szStudyUID);
	//<< �Ƿ�ָ�����ߵ�ĳ������ָ�������������MPPS
	BOOL IsSettingPatientOrStudyMPPS(vector<CString>& vtrUIDs, PatientAdminUIDType enumUIDType, BOOL* pbSetting);

	//<< ����MPPS����״̬
	void UpdateMppsWorkState(BOOL bWorking);

	//<< �ж��Ƿ��ߵ�UID��ʹ��
	BOOL IsPatientStudySeriesUIDInUse(PatientAdminUIDType enumUIDType, vector<CString>* pvtrUIDList);

	//<< ת��UserGuidance
	void NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive);

	//<< ����������
	//<< ���worklist�������б�
	BOOL GetWlServers(NetworkNode** ppServers, long* pLen);
	//<< ����worklist�������б�
	BOOL SetWlServers(NetworkNode* pServers, long lLen);
	//<< worklist���������Ӳ���
	BOOL WlServerConnectTest(NetworkNode* pServer, BOOL* pbResult);

	//<< ���MPPS�������б�
	BOOL GetMppsServers(NetworkNode** ppServers, long* pLen);
	//<< ����MPPS�������б�
	BOOL SetMppsServers(NetworkNode* pServers, long lLen);
	//<< MPPS���������Ӳ���
	BOOL MppsServerConnectTest(NetworkNode* pServer, BOOL* pbResult);

private:
	CWlMpps();

	//<< ���ò�ѯ����
	void SetQueryCondition(WorkListQueryCond* pWorkListQueryCond);
	//<< ��ʼ����ѯ����
	void InitQueryCondition();

	//<< ����worklist
	BOOL ReportWorkList();
	//<< �޸Ĳ�ѯ����
	BOOL ModifyQueryCondition(vector<WLQueryItem>& vtrWLQueryCond);

	// Create the query items' value by certain value set by GUI
	// 1. SPS Start Date
	void GetSPSStartDate(WLQuerySPSStartDate enumWLQuerySPSStartDate, CString& strSPSStartDate);
	// 2. ...

	//<< ��DICOM���ڻ����ʾ������
	CString GetDisplayDateFromDcmDate(LPCTSTR szDcmDate);
	//<< ��DICOMʱ������ʾ��ʱ��
	CString GetDisplayTimeFromDcmTime(LPCTSTR szDcmTime);

	// Patient Name parse from Dcm PatientsName
	void ParsePatientNameFromDcmPN(LPCTSTR szDcmPN, CString& strFirstName, CString& strMidName, CString& strLastName);

	// Date Convert from Dcm to DATE
	DATE GetDATEFromDcmDate(LPCTSTR szDcmDate);

	// Get DATE by current Date Time
	DATE GetDATEByCurrentDateTime();

	//<< ��û��߳�������/����
	void GetPatientBirthDateAge(LPCTSTR szDcmBirthDate, LPCTSTR szDcmAge, int& iAge, int& iAgeUnit, DATE& dtBirthDate, PatientBirthDateAgeUsing& enumBirthDateAgeUsing);

	// ȡ��MPPS����
	BOOL CancelMppsNProc();

	//<< Update the NCreate Dcm items by DB and something else
	BOOL UpdateNCreateItems(vector<WLQueryItem>& vtrItems, LPCTSTR szStudyUID);
	//<< Update the NSet Dcm items by DB and something else
	BOOL UpdateNSetItems(vector<WLQueryItem>& vtrItems, WorkListStatus enumStatus, LPCTSTR szStudyUID);

	//<< ��DB�������������DICOM����
	BOOL GetDcmPatientNameFromDBPatientName(CString& strDcmPN, LPCTSTR szDBPN);
	//<< �ɵ�ǰʱ����DICOMʱ�� 
	void GetDcmDateTimeByCurrentDateTime(CString& strDcmDate, CString& strDcmTime);

	//<< ��DATE���DICOM ����
	void GetDcmDateByDATE(CString& strDcmDate, DATE date);

	//<< ����worklist/MPPS����״̬
	void UpdateWlMppsWorkState();

private:

	static CWlMpps*			m_pInstance;

	SubModuleState			m_SubModuleState;
	CCriticalSection		m_CSLockSubModuleState;
	
	CWorklistIniOpt*		m_pWLIniOpt;
	CWorklistOpt			m_WLOpt;

	CMPPSIniOpt*			m_pMppsIniOpt;
	
	WorkListQueryCond		m_WkLQueryCond;
	HANDLE					m_hWLQueryThread;
	vector<WLQueryStruct>	m_vtrWLStruct;

	CCriticalSection		m_CSLockMppsList;	
	list<MppsStatusStruct>	m_lstMppsStatus;

	//<< the work state of WorkList and MPPS
	BOOL					m_bWorkListWorking;
	BOOL					m_bMppsWorking;
	CCriticalSection		m_CSLockMppsWorkState;	

};

#endif // __WLMPPS_H__
