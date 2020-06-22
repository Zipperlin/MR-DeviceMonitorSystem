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
	
	//<< 设置子模块状态
	void SetSubModuleState(SubModuleState enumSubModuleState);
	//<< 获得子模块状态
	SubModuleState GetSubModuleState();

	//<< WorkList
	//<< 获得Worklist通知
	BOOL GetWorkList();
	//<< 刷新Worklist
	BOOL RefreshWorkList(WorkListQueryCond* pWorkListQueryCond);
	//<< 获得患者检查结构
	BOOL GetPatientStudyStruct(LPCTSTR szStudyInstanceUID, WLPatientStudyStruct* pStruct);
	//<< 判断检查是否已被导入
	BOOL IsStudyImported(LPCTSTR szStudyInstanceUID, WLPatientStudyStatusInDB* pStatus);
	//<< 一个检查被导入
	BOOL StudyImported(LPCTSTR szStudyInstanceUID);

	//<< WorkList是否正在工作
	BOOL IsWorkListWorking();

	//<< Worklist查询处理
	BOOL QueryProc();
	//<< 取消worklist查询
	BOOL CancelQuery();

	//<< 更新worklist工作状态
	void UpdateWorklistWorkState(BOOL bWorking);


	//<< MPPS
	//<< MPPS是否有效
	BOOL IsMPPSValid(BOOL* pbValid);
	//<< 判断检查MPPS状态是否使能
	BOOL IsSetMPPSStatusEnabled(LPCTSTR szStudyUID, BOOL* pbEnabled);
	//<< 获得检查MPPS状态
	BOOL GetStudyMppsStatus(LPCTSTR szStudyUID, WorkListStatus* penumStatus);
	//<< 设置MPPS状态
	BOOL SetMppsStatus(LPCTSTR szStudyUID, WorkListStatus enumStatus);
	//<< 设置MPPS状态处理
	BOOL SetMppsStatusProc(MppsStatusStruct* pStruct);

	//<< 通知UI一个MPPS状态设置已完成
	void NotifySetMppsFinished(LPCTSTR szStudyUID, WorkListStatus enumStatus, BOOL bResult);

	//<< 从MPPS任务列表中清除一个指定任务
	BOOL RemoveMppsStatusStruct(LPCTSTR szStudyUID, WorkListStatus enumStatus);

	//<< MPPS是否正在工作
	BOOL IsMppsWorking();

	//<< 是否指定的检查正在关闭MPPS
	BOOL IsClosingStudyMPPS(LPCTSTR szStudyUID);
	//<< 是否指定患者的某个检查或指定检查正在设置MPPS
	BOOL IsSettingPatientOrStudyMPPS(vector<CString>& vtrUIDs, PatientAdminUIDType enumUIDType, BOOL* pbSetting);

	//<< 更新MPPS工作状态
	void UpdateMppsWorkState(BOOL bWorking);

	//<< 判断是否患者等UID被使用
	BOOL IsPatientStudySeriesUIDInUse(PatientAdminUIDType enumUIDType, vector<CString>* pvtrUIDList);

	//<< 转发UserGuidance
	void NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive);

	//<< 服务器设置
	//<< 获得worklist服务器列表
	BOOL GetWlServers(NetworkNode** ppServers, long* pLen);
	//<< 设置worklist服务器列表
	BOOL SetWlServers(NetworkNode* pServers, long lLen);
	//<< worklist服务器连接测试
	BOOL WlServerConnectTest(NetworkNode* pServer, BOOL* pbResult);

	//<< 获得MPPS服务器列表
	BOOL GetMppsServers(NetworkNode** ppServers, long* pLen);
	//<< 设置MPPS服务器列表
	BOOL SetMppsServers(NetworkNode* pServers, long lLen);
	//<< MPPS服务器连接测试
	BOOL MppsServerConnectTest(NetworkNode* pServer, BOOL* pbResult);

private:
	CWlMpps();

	//<< 设置查询条件
	void SetQueryCondition(WorkListQueryCond* pWorkListQueryCond);
	//<< 初始化查询条件
	void InitQueryCondition();

	//<< 报告worklist
	BOOL ReportWorkList();
	//<< 修改查询条件
	BOOL ModifyQueryCondition(vector<WLQueryItem>& vtrWLQueryCond);

	// Create the query items' value by certain value set by GUI
	// 1. SPS Start Date
	void GetSPSStartDate(WLQuerySPSStartDate enumWLQuerySPSStartDate, CString& strSPSStartDate);
	// 2. ...

	//<< 由DICOM日期获得显示用日期
	CString GetDisplayDateFromDcmDate(LPCTSTR szDcmDate);
	//<< 由DICOM时间获得显示用时间
	CString GetDisplayTimeFromDcmTime(LPCTSTR szDcmTime);

	// Patient Name parse from Dcm PatientsName
	void ParsePatientNameFromDcmPN(LPCTSTR szDcmPN, CString& strFirstName, CString& strMidName, CString& strLastName);

	// Date Convert from Dcm to DATE
	DATE GetDATEFromDcmDate(LPCTSTR szDcmDate);

	// Get DATE by current Date Time
	DATE GetDATEByCurrentDateTime();

	//<< 获得患者出生日期/年龄
	void GetPatientBirthDateAge(LPCTSTR szDcmBirthDate, LPCTSTR szDcmAge, int& iAge, int& iAgeUnit, DATE& dtBirthDate, PatientBirthDateAgeUsing& enumBirthDateAgeUsing);

	// 取消MPPS工作
	BOOL CancelMppsNProc();

	//<< Update the NCreate Dcm items by DB and something else
	BOOL UpdateNCreateItems(vector<WLQueryItem>& vtrItems, LPCTSTR szStudyUID);
	//<< Update the NSet Dcm items by DB and something else
	BOOL UpdateNSetItems(vector<WLQueryItem>& vtrItems, WorkListStatus enumStatus, LPCTSTR szStudyUID);

	//<< 由DB患者姓名获得其DICOM姓名
	BOOL GetDcmPatientNameFromDBPatientName(CString& strDcmPN, LPCTSTR szDBPN);
	//<< 由当前时间获得DICOM时间 
	void GetDcmDateTimeByCurrentDateTime(CString& strDcmDate, CString& strDcmTime);

	//<< 由DATE获得DICOM 日期
	void GetDcmDateByDATE(CString& strDcmDate, DATE date);

	//<< 更新worklist/MPPS工作状态
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
