/* Time: <@(#)Transfer.h   2009-3-5 - 10:33:34   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : Transfer.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Capsulation class of image sending function
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:33:34		FanZF	Creation
 *
 *********************************************************************
 */

// Transfer.h: interface for the CTransfer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFER_H__A33C26FC_DCAF_4918_B606_370ED93205F6__INCLUDED_)
#define AFX_TRANSFER_H__A33C26FC_DCAF_4918_B606_370ED93205F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "ASBasis.h"
#include "PALib_i.h"
#include "DBController.h"
#include "JobQueue.h"
#include "TransferXMLParser.h"
#include "DcmPartner.h"
#include "UserGuidanceOpt.h"


class CTransfer : public NObserver,
				  public NSubject
{
public:
	virtual ~CTransfer();
	
	static CTransfer* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	BOOL UnInit();

	//<< 创建自动发送任务
	BOOL CreateJobAutoSend(LPCTSTR szUID, PatientAdminUIDType enumUIDType);
	//<< 创建手动发送任务
	BOOL CreateJobManualSend(vector<CString>* pvtrUIDs, PatientAdminUIDType enumUIDType, vector<NetworkNodeStruct>&	vtrNodes);

	//<< 设置子模块状态
	void SetSubModuleState(SubModuleState enumSubModuleState);
	//<< 获得子模块状态
	SubModuleState GetSubModuleState();
	
	//<< 链接DcmPartner
	void AttachDcmPartner(CDcmPartner* pDcmPartner);
	//<< 断开DcmPartner对象
	void DetachDcmPartner(CDcmPartner* pDcmPartner);

	//<< 处理任务
	BOOL HandleJob(PAJob* pJob);

	//<< 暂停发送
	void PauseTransfer();
	//<< 恢复发送
	void ResumeTransfer();


	//<< 获得自动发送服务器
	BOOL GetAutoServers(NetworkNode** ppServers, long* pLen);
	//<< 设置自动发送服务器
	BOOL SetAutoServers(NetworkNode* pServer, long lLen);
	//<< 是否自动发送有效
	BOOL IsAutoSendValid(BOOL* pbValid);
	//<< 获得手动发送服务器
	BOOL GetManualServers(NetworkNode** ppServers, long* pLen);
	//<< 设置手动发送服务器
	BOOL SetManualServers(NetworkNode* pServer, long lLen);
	//<< 连接发送服务器测试
	BOOL ConnectTest(NetworkNode* pServer, BOOL* pbResult);
	
	//设置自动发送状态  [ GaoXing 9/11/2009]
	BOOL SetEnableAutoTransferStatus(BOOL bEnable);
	//获取是否自动发送状态
	BOOL GetEnableAutoTransferStatus(BOOL *bEnalbe);

	//设置是否询问用户进行自动发送 [ GaoXing 1/11/2010]
	BOOL SetAskforAutoTransfer(BOOL bAskfor);
	//获取是否询问用户进行自动发送
	BOOL GetAskforAutoTransfer(BOOL *bAskfor);

	//<< 转发UserGuidance
	void NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive);

protected:
	//<< 处理NSubject返回的消息
	virtual LONG HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam);
private:
	CTransfer();
	//<< 设置当前任务进度
	void SetCurrentJobProgress(JobProgressUsing enumJobProgressUsing, UINT uiFirstParam = 0, UINT uiSecondParam = 0);
	//<< 设置当前任务详细信息
	void SetCurrentJobDetailByUGID(LONG iUGID = 0);

	//<< 获得自动发送服务器
	BOOL GetJobAutoSendServers(TransferJobSettingsStruct* ptjss);
	//<< 获得手动发送服务器
	BOOL GetJobManualSendServers(TransferJobSettingsStruct* ptjss, vector<NetworkNodeStruct>& vtrNodes);

	
private:
	BSTR m_bstrStudyUID; //发送时，传给UI的StudyUID,由UI解析
	BSTR m_bstrPatientUID; //发送时，传给UI的PatientUID,由UI解析
	//根据pJob, 通知UI修改数据库 发送状态
	BOOL NotifyUIModifyDB(PAJob* pJob);

	static CTransfer*	m_pInstance;

	CDcmPartner*		m_pDcmPartner;

	CStoreSCUOpt		m_StoreScuOpt;

	CTransferXMLParser	m_XMLParser;
	
	PAJob*				m_pCurrentJob;

	SubModuleState		m_SubModuleState;

	// Enable or Disable Transfer
	HANDLE				m_hTransferEvent;

	CCriticalSection	m_CSLockJobState;
	CCriticalSection	m_CSLockSubModuleState;

};

#endif // !defined(AFX_TRANSFER_H__A33C26FC_DCAF_4918_B606_370ED93205F6__INCLUDED_)
