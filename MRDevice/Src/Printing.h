/* Time: <@(#)Printing.h   2009-3-5 - 10:33:13   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : Printing.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Capsulation class of printing function
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:33:13		FanZF	Creation
 *
 *********************************************************************
 */

// Printing.h: interface for the CPrinting class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTING_H__60ABD6DF_7524_47D6_A3A5_F74CD5669AB1__INCLUDED_)
#define AFX_PRINTING_H__60ABD6DF_7524_47D6_A3A5_F74CD5669AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "ASBasis.h"
#include "PALib_i.h"
#include "DBController.h"
#include "JobQueue.h"
#include "DcmPartner.h"
#include "UserGuidanceOpt.h"
#include "FCPartner.h"


class CPrinting: public NObserver,
				 public NSubject  
{
public:
	virtual ~CPrinting();

	static CPrinting* GetInstance();
	void ReleaseInstance();
	
	BOOL Init();
	BOOL UnInit();

	//<< ������ģ��״̬
	void SetSubModuleState(SubModuleState enumSubModuleState);
	//<< �����ģ��״̬
	SubModuleState GetSubModuleState();
	
	//<< ��������
	BOOL CreateJob(PrintJobSettings* pPrintJobSettings);

	//<< ��ͼ����ص�FC
	BOOL LoadToFC(vector<CString>* pvtrUID);

	//<< ��ʾFC������
	BOOL ShowFCProgressBar(BOOL bShow);

	//<< ȡ��FC��ӡ
	BOOL CancelFCPrinting();

	//<< ��ô�ӡ�������б�
	BOOL GetNetworkNodes(NetworkNode** ppNodesList, long* pLen);

	//<< �ɼ�ǰ�����ӡ
	BOOL HandlePrintBeforeAcq();
	//<< �ɼ������ӡ
	void HandlePrintAfterAcq();

protected:
	//<< ����NSubject���ص���Ϣ
	virtual LONG HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam);

private:
	CPrinting();

	//<< ���ô�ӡ����״̬
	void SetPrintWorkingState(PrintWorkingState enumWorkingState);

	//<< ת��UserGuidance
	void NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive);

private:

	static CPrinting*	m_pInstance;
	
	CFCPartner			m_FCPartner;

	CDcmPartner			m_DcmPartner;

	CCriticalSection	m_CSLockSubModuState;
	CCriticalSection	m_CSLockPrintWorkingState;


	SubModuleState		m_SubModuleState;
	DWORD				m_PrintWorkingState;
};

#endif // !defined(AFX_PRINTING_H__60ABD6DF_7524_47D6_A3A5_F74CD5669AB1__INCLUDED_)
