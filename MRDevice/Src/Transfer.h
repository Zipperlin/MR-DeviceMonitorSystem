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

	//<< �����Զ���������
	BOOL CreateJobAutoSend(LPCTSTR szUID, PatientAdminUIDType enumUIDType);
	//<< �����ֶ���������
	BOOL CreateJobManualSend(vector<CString>* pvtrUIDs, PatientAdminUIDType enumUIDType, vector<NetworkNodeStruct>&	vtrNodes);

	//<< ������ģ��״̬
	void SetSubModuleState(SubModuleState enumSubModuleState);
	//<< �����ģ��״̬
	SubModuleState GetSubModuleState();
	
	//<< ����DcmPartner
	void AttachDcmPartner(CDcmPartner* pDcmPartner);
	//<< �Ͽ�DcmPartner����
	void DetachDcmPartner(CDcmPartner* pDcmPartner);

	//<< ��������
	BOOL HandleJob(PAJob* pJob);

	//<< ��ͣ����
	void PauseTransfer();
	//<< �ָ�����
	void ResumeTransfer();


	//<< ����Զ����ͷ�����
	BOOL GetAutoServers(NetworkNode** ppServers, long* pLen);
	//<< �����Զ����ͷ�����
	BOOL SetAutoServers(NetworkNode* pServer, long lLen);
	//<< �Ƿ��Զ�������Ч
	BOOL IsAutoSendValid(BOOL* pbValid);
	//<< ����ֶ����ͷ�����
	BOOL GetManualServers(NetworkNode** ppServers, long* pLen);
	//<< �����ֶ����ͷ�����
	BOOL SetManualServers(NetworkNode* pServer, long lLen);
	//<< ���ӷ��ͷ���������
	BOOL ConnectTest(NetworkNode* pServer, BOOL* pbResult);
	
	//�����Զ�����״̬  [ GaoXing 9/11/2009]
	BOOL SetEnableAutoTransferStatus(BOOL bEnable);
	//��ȡ�Ƿ��Զ�����״̬
	BOOL GetEnableAutoTransferStatus(BOOL *bEnalbe);

	//�����Ƿ�ѯ���û������Զ����� [ GaoXing 1/11/2010]
	BOOL SetAskforAutoTransfer(BOOL bAskfor);
	//��ȡ�Ƿ�ѯ���û������Զ�����
	BOOL GetAskforAutoTransfer(BOOL *bAskfor);

	//<< ת��UserGuidance
	void NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive);

protected:
	//<< ����NSubject���ص���Ϣ
	virtual LONG HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam);
private:
	CTransfer();
	//<< ���õ�ǰ�������
	void SetCurrentJobProgress(JobProgressUsing enumJobProgressUsing, UINT uiFirstParam = 0, UINT uiSecondParam = 0);
	//<< ���õ�ǰ������ϸ��Ϣ
	void SetCurrentJobDetailByUGID(LONG iUGID = 0);

	//<< ����Զ����ͷ�����
	BOOL GetJobAutoSendServers(TransferJobSettingsStruct* ptjss);
	//<< ����ֶ����ͷ�����
	BOOL GetJobManualSendServers(TransferJobSettingsStruct* ptjss, vector<NetworkNodeStruct>& vtrNodes);

	
private:
	BSTR m_bstrStudyUID; //����ʱ������UI��StudyUID,��UI����
	BSTR m_bstrPatientUID; //����ʱ������UI��PatientUID,��UI����
	//����pJob, ֪ͨUI�޸����ݿ� ����״̬
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
