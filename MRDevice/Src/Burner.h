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

	//<< ������ģ��״̬
	void SetSubModuleState(SubModuleState enumSubModuleState);
	//<< ��ȡ��ģ��״̬
	SubModuleState GetSubModuleState();

	//<< ��������
	BOOL CreateJob(BurnJobSettingsByPA* pBurnJobSettingsByPA);

	//<< ����DcmPartner����
	void AttachDcmPartner(CDcmPartner* pDcmPartner);
	//<< �Ͽ�DcmPartner����
	void DetachDcmPartner(CDcmPartner* pDcmPartner);

	//<< ��������
	BOOL HandleJob(PAJob* pJob);

	//<< ��¼׼��
	BOOL BurnPrepare(vector<CString>* pvtrUID, PatientAdminUIDType enumPatientAdminUIDType);
	//<< ȡ����¼׼��
	BOOL CancelBurnPrepare();
	//<< ��ÿ�¼׼������
	BOOL GetPreBurnJob();

	//<< ȡ����¼
	BOOL AbortBurnWork();

	//<< ��ù��ƴ�С
	BOOL GetEstimatedSize(BOOL bBMP, BOOL bJPEG, unsigned long* plSizeInMega);

	//<< ʹ�ܼ���豸
	void EnableCheckDevice(BOOL bCheck);

	//<< ���ù��̼�����Ա�־
	void SetBurnMediaCheckRetry(BOOL bRetry);

	//<< �����豸
	BOOL SetDevice(LPCTSTR strDeviceName);
	//<< ����豸�б�
	BOOL GetDevices(BSTR** ppbsDevices, long* pLen);
	//<< ����豸������Ϣ
	BOOL GetDeviceDiscInfo();

	//<< ת��UserGuidance
	void NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive);
	//<< ������DVDBurner���ص���Ϣ
	void HandleMessageFromDVDBurner(UINT uMessage, LPARAM lParam, WPARAM wParam);

protected:
	//<< ����NSubject���ص���Ϣ
	virtual LONG HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam);

private:
	CBurner();

	//<< ���õ�ǰ�������
	void SetCurrentJobProgress(JobProgressUsing enumJobProgressUsing, UINT uiFirstParam = 0, UINT uiSecondParam = 0);
	//<< ���õ�ǰ������ϸ��Ϣ
	void SetCurrentJobDetail(JobDetailUsing enumJobDetailUsing, LONG iUGID = 0, LPCTSTR szDetailInfo = NULL);
	//<< ���õ�ǰ������ϸ��Ϣ
	void SetCurrentJobDetailOriginal(LPCTSTR szDetail);
	
	//<< ���ÿ�¼����
	BOOL SetBurnContent();
	//<< ��ȡ���
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
