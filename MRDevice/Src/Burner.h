/* Time: <@(#)Burner.h   2009-3-5 - 10:29:33   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : Burner.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Capsulation class of export function
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:29:33		FanZF	Creation
 *
 *********************************************************************
 */

// Burner.h: interface for the CBurner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BURNER_H__005E889C_7C7E_4E30_A373_D6A59DA5242B__INCLUDED_)
#define AFX_BURNER_H__005E889C_7C7E_4E30_A373_D6A59DA5242B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DBController.h"
#include "JobQueue.h"
#include "BurnPartner.h"
#include "DcmPartner.h"
#include "JobHandler.h"


class CBurner  : public NObserver,
				 public NSubject
{
public:
	virtual ~CBurner();

	static CBurner* GetInstance();
	void ReleaseInstance();

	BOOL Init();
 	BOOL UnInit();

	//<< 设置子模块状态
	void SetSubModuleState(SubModuleState enumSubModuleState);
	//<< 获取子模块状态
	SubModuleState GetSubModuleState();

	//<< 创建任务
	BOOL CreateJob(BurnJobSettingsByPA* pBurnJobSettingsByPA);

	//<< 链接DcmPartner对象
	void AttachDcmPartner(CDcmPartner* pDcmPartner);
	//<< 断开DcmPartner对象
	void DetachDcmPartner(CDcmPartner* pDcmPartner);

	//<< 处理任务
	BOOL HandleJob(PAJob* pJob);

	//<< 刻录准备
	BOOL BurnPrepare(vector<CString>* pvtrUID, PatientAdminUIDType enumPatientAdminUIDType);
	//<< 取消刻录准备
	BOOL CancelBurnPrepare();
	//<< 获得刻录准备任务
	BOOL GetPreBurnJob();

	//<< 取消刻录
	BOOL AbortBurnWork();

	//<< 获得估计大小
	BOOL GetEstimatedSize(BOOL bBMP, BOOL bJPEG, unsigned long* plSizeInMega);

	//<< 使能检测设备
	void EnableCheckDevice(BOOL bCheck);

	//<< 设置光盘检测重试标志
	void SetBurnMediaCheckRetry(BOOL bRetry);

	//<< 设置设备
	BOOL SetDevice(LPCTSTR strDeviceName);
	//<< 获得设备列表
	BOOL GetDevices(BSTR** ppbsDevices, long* pLen);
	//<< 获得设备光盘信息
	BOOL GetDeviceDiscInfo();

	//<< 转发UserGuidance
	void NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive);
	//<< 处理由DVDBurner返回的消息
	void HandleMessageFromDVDBurner(UINT uMessage, LPARAM lParam, WPARAM wParam);

protected:
	//<< 处理NSubject返回的消息
	virtual LONG HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam);

private:
	CBurner();

	//<< 设置当前任务进度
	void SetCurrentJobProgress(JobProgressUsing enumJobProgressUsing, UINT uiFirstParam = 0, UINT uiSecondParam = 0);
	//<< 设置当前任务详细信息
	void SetCurrentJobDetail(JobDetailUsing enumJobDetailUsing, LONG iUGID = 0, LPCTSTR szDetailInfo = NULL);
	//<< 设置当前任务详细信息
	void SetCurrentJobDetailOriginal(LPCTSTR szDetail);
	
	//<< 设置刻录内容
	BOOL SetBurnContent();
	//<< 获取卷标
	CString GetVolumeLabel(LPCTSTR szJobID);

public:

	PAJob*				m_pCurrentJob;

private:
	
	static CBurner*		m_pInstance;

	CDcmPartner*		m_pDcmPartner;


	HANDLE				m_hGetJobInfoThread;
	PAJob*				m_pPreBurnJob;
	vector<CString>		m_vtrPAUID;
	PatientAdminUIDType	m_enumPAUIDType;

	CBurnPartner		m_BurnPartner;

	CCriticalSection	m_CSLockJobState;
	CCriticalSection	m_CSLockSubModuState;
	SubModuleState		m_SubModuleState;

	__int64				m_i64SizeOfDiscWith;

	BOOL				m_bReportNeeded;
	BOOL				m_bGettingDeviceDiscInfo;
};

#endif // !defined(AFX_BURNER_H__005E889C_7C7E_4E30_A373_D6A59DA5242B__INCLUDED_)
