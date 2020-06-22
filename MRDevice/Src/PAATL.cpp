/* Time: <@(#)PAATL.cpp   2009-3-5 - 10:49:12   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : PAATL.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : COM class for Printing&Archiving
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:49:12		FanZF	Creation
 *
 *********************************************************************
 */

// PAATL.cpp : Implementation of CPA

#include "stdafx.h"
#include "PALib_i.h"
#include "PAATL.h"
#include "ConstDefine.h"
#include "SystemEventProxy.h"
/////////////////////////////////////////////////////////////////////////////


DWORD WINAPI StartUpThreadProc(LPVOID lpParam)
{
	try
	{
		//CoInitialize(NULL);

		CPA* pPA = (CPA*)lpParam;

		if (pPA->StartUpProc())
		{
			return THREADE_RET_CODE_OK;
		}
		else
		{
			return THREADE_RET_CODE_ERROR;
		}
	}
	PA_CATCH_ERROR_RET(THREADE_RET_CODE_ERROR)
}


CPA::CPA()
{
	PRINTTRACE_ENTER_FUNCTION

	m_WorkState = enumWORKSTATE_UNINITIALIZED;
	m_StartUpResult = enumSTARTUPRESULT_UNKNOWN;
	m_StartUpThreadHandle = NULL;

	m_pJobHandlerInstance = NULL; 
	m_pPrintInstance = NULL;
	m_pBurnInstance = NULL;
	m_pTransferInstance = NULL;
	m_pDiscImportInstance = NULL;
	m_pWlMppsInstance = NULL;
	
	m_pUGOptInstance = NULL;

	m_pISControllerInstance = NULL;
	m_pDBControllerInstance = NULL;

	m_pPADBOptInstance = NULL;

	m_pFireMsgInstance = NULL;

	m_pLanguageIniOptInstance = NULL;

	m_pFireMsgInstance = CFireMsgQueueMng::GetInstance();
	if(m_pFireMsgInstance)
	{
		ARCHVTRACE_INFO("Get m_pFireMsgInstance OK")
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pFireMsgInstance error")
	}

	// FireMsgMng Init
    if (!m_pFireMsgInstance->Init(this))
	{
		ARCHVTRACE_ERROR("pCPA->m_pFireMsgInstance->Init() failed")
	}
	else
	{
		ARCHVTRACE_INFO("pCPA->m_pFireMsgInstance->Init() succeed")
	}



	m_pISControllerInstance = CISController::GetInstance();
	if (m_pISControllerInstance)
	{
		ARCHVTRACE_INFO("Get m_pISControllerInstance OK");
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pISControllerInstance error");
	}

	m_pDBControllerInstance = CDBController::GetInstance();
	if (m_pDBControllerInstance)
	{
		ARCHVTRACE_INFO("Get m_pDBControllerInstance OK");
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pDBControllerInstance error");
	}

	m_pLanguageIniOptInstance = CLanguageIniOpt::GetInstance();
	if (m_pLanguageIniOptInstance)
	{
		ARCHVTRACE_INFO("Get m_pLanguageIniOptInstance OK");
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pLanguageIniOptInstance error");
	}
	
	m_pPADBOptInstance = CPADataBaseOpt::GetInstance();
	if (m_pPADBOptInstance)
	{
		ARCHVTRACE_INFO("Get m_pPADBOptInstance OK");
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pPADBOptInstance error");
	}

	m_pUGOptInstance = CUserGuidanceOpt::GetInstance();
	if (m_pUGOptInstance)
	{
		ARCHVTRACE_INFO("Get m_pUGOptInstance OK");
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pUGOptInstance error");
	}

	m_pJobHandlerInstance = CJobHandler::GetInstance();
	if (m_pJobHandlerInstance)
	{
		m_pJobHandlerInstance->Attach(this);
		ARCHVTRACE_INFO("Get m_pJobHandlerInstance OK");
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pJobHandlerInstance error");
	}

	m_pWlMppsInstance = CWlMpps::GetInstance();
	if (m_pWlMppsInstance)
	{
		m_pWlMppsInstance->Attach(this);
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pWlMppsInstance error");
	}

	m_pPrintInstance = CPrinting::GetInstance();
	if(m_pPrintInstance)
	{
		m_pPrintInstance->Attach(this);
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pPrintInstance error");
	}

	m_pBurnInstance = CBurner::GetInstance();
	if(m_pBurnInstance)
	{
		m_pBurnInstance->Attach(this);
		m_pBurnInstance->AttachDcmPartner(&m_DcmPartner);
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pBurnInstance error")
	}

	m_pTransferInstance = CTransfer::GetInstance();
	if(m_pTransferInstance)
	{
		m_pTransferInstance->Attach(this);
		m_pTransferInstance->AttachDcmPartner(&m_DcmPartner);
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pTransferInstance error")
	}

	m_pDiscImportInstance = CDiscImport::GetInstance();
	if(m_pDiscImportInstance)
	{
		m_pDiscImportInstance->Attach(this);
	}
	else
	{
		ARCHVTRACE_ERROR("Get m_pDiscImportInstance error")
	}

}

CPA::~CPA()
{

	PRINTTRACE_ENTER_FUNCTION

	// m_pFireMsgInstance UnInit
	if (m_pFireMsgInstance->UnInit())
	{
		ARCHVTRACE_INFO("m_pFireMsgInstance->UnInit() succeed")
	}
	else
	{
		ARCHVTRACE_ERROR("m_pFireMsgInstance->UnInit() failed")
	}

	if(m_pFireMsgInstance)
	{
		m_pFireMsgInstance->ReleaseInstance();
		m_pFireMsgInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pFireMsgInstance pointer is null!");
	}


	if(m_pISControllerInstance)
	{
		m_pISControllerInstance->ReleaseInstance();
		m_pISControllerInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pISControllerInstance pointer is null!");
	}

	if(m_pDBControllerInstance)
	{
		m_pDBControllerInstance->ReleaseInstance();
		m_pDBControllerInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pDBControllerInstance pointer is null!");
	}


	if(m_pLanguageIniOptInstance)
	{
		m_pLanguageIniOptInstance->ReleaseInstance();
		m_pLanguageIniOptInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pLanguageIniOptInstance pointer is null!");
	}


	if (m_pUGOptInstance)
	{
		m_pUGOptInstance->ReleaseInstance();
		m_pUGOptInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pUGOptInstance pointer is null!");
	}

	if (m_pWlMppsInstance)
	{
		m_pWlMppsInstance->Detach(this);
		m_pWlMppsInstance->ReleaseInstance();
		m_pWlMppsInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pWlMppsInstance pointer is null!");
	}

	if(m_pPrintInstance)
	{
		m_pPrintInstance->Detach(this);
		m_pPrintInstance->ReleaseInstance();
		m_pPrintInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pPrintInstance pointer is null!");
	}

	if(m_pBurnInstance)
	{
		m_pBurnInstance->Detach(this);
		m_pBurnInstance->DetachDcmPartner(&m_DcmPartner);
		m_pBurnInstance->ReleaseInstance();
		m_pBurnInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pBurnInstance pointer is null!");
	}

	if(m_pTransferInstance)
	{
		m_pTransferInstance->Detach(this);
		m_pTransferInstance->DetachDcmPartner(&m_DcmPartner);
		m_pTransferInstance->ReleaseInstance();
		m_pBurnInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pTransferInstance pointer is null!");
	}

	if(m_pDiscImportInstance)
	{
		m_pDiscImportInstance->Detach(this);
		m_pDiscImportInstance->ReleaseInstance();
		m_pBurnInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pDiscImportInstance pointer is null!");
	}

	if (m_pJobHandlerInstance)
	{
		m_pJobHandlerInstance->Detach(this);
		m_pJobHandlerInstance->ReleaseInstance();
		m_pJobHandlerInstance = NULL;
	}
	else
	{
		ARCHVTRACE_ERROR("m_pDcmPartnerInstance pointer is null!");
	}

}

LONG CPA::HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam)
{
	CString strTrace;

	FireMsgNode msgNode;
	msgNode.msg.uiMessage = uMessage;
	msgNode.msg.lParam = lParam;
	msgNode.msg.wParam = wParam;
	msgNode.pNextNode = NULL;

	//
	if(pSubject == m_pPrintInstance ||
		pSubject == m_pBurnInstance ||
		pSubject == m_pTransferInstance ||
		pSubject == m_pDiscImportInstance ||
		pSubject == m_pWlMppsInstance ||
		pSubject == m_pJobHandlerInstance)
	{
		// Push msg to FireMsgQueue

		m_pFireMsgInstance->PushMsg(msgNode);

	}

	// handle module state
	if (NOTIFY_SUBMODULE_STATE_CHANGED == uMessage)
	{
		SubModuleState PrintSubModuleState = m_pPrintInstance->GetSubModuleState();
		SubModuleState BurnSubModuleState = m_pBurnInstance->GetSubModuleState();
		SubModuleState TransferSubModuleState = m_pTransferInstance->GetSubModuleState();
		SubModuleState DiscImportSubModuleState = m_pDiscImportInstance->GetSubModuleState();
		SubModuleState WlMppsSubModuleState = m_pDiscImportInstance->GetSubModuleState();

		if (enumSubModuleState_UnInited == PrintSubModuleState ||
			enumSubModuleState_UnInited == BurnSubModuleState ||
			enumSubModuleState_UnInited == TransferSubModuleState ||
			enumSubModuleState_UnInited == DiscImportSubModuleState ||
			enumSubModuleState_UnInited == WlMppsSubModuleState)
		{
//			SetWorkState(enumWORKSTATE_UNINITIALIZED);
		}
		else if (enumSubModuleState_UnInited == PrintSubModuleState &&
				enumSubModuleState_UnInited == BurnSubModuleState &&
				enumSubModuleState_UnInited == TransferSubModuleState &&
				enumSubModuleState_UnInited == DiscImportSubModuleState &&
				enumSubModuleState_UnInited == WlMppsSubModuleState)
		{
//			SetWorkState(enumWORKSTATE_UNINITIALIZED);
		}
		else if (enumSubModuleState_Error == PrintSubModuleState &&
			enumSubModuleState_Error == BurnSubModuleState &&
			enumSubModuleState_Error == TransferSubModuleState &&
			enumSubModuleState_Error == DiscImportSubModuleState &&
			enumSubModuleState_Error == WlMppsSubModuleState)
		{
			SetWorkState(enumWORKSTATE_ERROR);
		}
		else if ((enumSubModuleState_Ready == PrintSubModuleState ||
			enumSubModuleState_Ready == BurnSubModuleState ||
			enumSubModuleState_Ready == TransferSubModuleState ||
			enumSubModuleState_Ready == DiscImportSubModuleState ||
			enumSubModuleState_Ready == WlMppsSubModuleState)
			&& (enumSubModuleState_UnInited != PrintSubModuleState &&
			enumSubModuleState_UnInited != BurnSubModuleState &&
			enumSubModuleState_UnInited != TransferSubModuleState && 
			enumSubModuleState_UnInited != DiscImportSubModuleState &&
			enumSubModuleState_UnInited != WlMppsSubModuleState)
			&& (enumSubModuleState_UnInitializing != PrintSubModuleState &&
			enumSubModuleState_UnInitializing != BurnSubModuleState &&
			enumSubModuleState_UnInitializing != TransferSubModuleState &&
			enumSubModuleState_UnInitializing != DiscImportSubModuleState &&
			enumSubModuleState_UnInitializing != WlMppsSubModuleState))
		{
			SetWorkState(enumWORKSTATE_READY);
		}
		else if (enumSubModuleState_Work == PrintSubModuleState ||
			enumSubModuleState_Work == BurnSubModuleState ||
			enumSubModuleState_Work == TransferSubModuleState ||
			enumSubModuleState_Work == DiscImportSubModuleState ||
			enumSubModuleState_Work == WlMppsSubModuleState)
		{
			SetWorkState(enumWORKSTATE_WORKING);
		}
		else if (enumSubModuleState_UnInitializing == PrintSubModuleState ||
			enumSubModuleState_UnInitializing == BurnSubModuleState ||
			enumSubModuleState_UnInitializing == TransferSubModuleState ||
			enumSubModuleState_UnInitializing == DiscImportSubModuleState ||
			enumSubModuleState_UnInitializing == WlMppsSubModuleState)
		{
			SetWorkState(enumWORKSTATE_UNINITIALIZING);
		}
		else
		{
			PRINTTRACE_ERROR("!!!Unhandled module state")
			CString strTrace;
			strTrace.Format(_T("P:%d,B:%d,T:%d,D:%d,W:%d"), PrintSubModuleState,BurnSubModuleState,TransferSubModuleState,DiscImportSubModuleState,WlMppsSubModuleState);
			PRINTTRACE_ERROR(strTrace)
		}
	}

	return 0;
}

// Ping
STDMETHODIMP CPA::Ping()
{
	// TODO: Add your implementation code here
	return S_OK;
}

// IGeneralSys
STDMETHODIMP CPA::StartUp()
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (NULL == m_StartUpThreadHandle)
		{
			m_StartUpThreadHandle = CreateThread(NULL, 0, StartUpThreadProc, this, 0, NULL);
			if (NULL == m_StartUpThreadHandle)
			{
				sLock.Unlock();
				PRINTTRACE_ERROR("Create Thread StartUpThreadProc failed: m_StartUpThreadHandle = NULL")
				return S_FALSE;
			}
			else
			{
				sLock.Unlock();
				PRINTTRACE_INFO("Create Tread StartUpThreadProc Succeed")
				return S_OK;
			}
		}
		else
		{
			sLock.Unlock();
			PRINTTRACE_INFO("StartUp() is called, however, it has been called before")
			return S_OK;
		}

	}
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::ShutDown()
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if ((enumWORKSTATE_UNINITIALIZED == m_WorkState) ||
			(enumWORKSTATE_INITIALIZING == m_WorkState) ||
			(enumWORKSTATE_UNINITIALIZING == m_WorkState))
		{
			sLock.Unlock();
			ARCHVTRACE_INFO("ShutDown() be called when m_WorkState is UNINITIALIZED, INITIALIZING or UNINITIALIZING")
			return S_FALSE;
		}
						
		if (ShutDownProc())
		{
			sLock.Unlock();
			ARCHVTRACE_INFO("ShutDownNotify() succeed")
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			ARCHVTRACE_ERROR("ShutDownNotify() failed")
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

BOOL CPA::StartUpProc()
{
	BOOL bRet = TRUE;

	SetWorkState(enumWORKSTATE_INITIALIZING);

	if(!sysProxy.Initialize())
	{
		ARCHVTRACE_ERROR(_T("System Event DB proxy initialize failed."));
	}

	// DBController Init
    if (!m_pDBControllerInstance->Init())
	{
		m_pPrintInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pBurnInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pTransferInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pDiscImportInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pWlMppsInstance->SetSubModuleState(enumSubModuleState_Error);

		SetWorkState(enumWORKSTATE_ERROR);
		ARCHVTRACE_ERROR("pCPA->m_pDBControllerInstance->Init() failed")
		return FALSE;
	}
	else
	{
		ARCHVTRACE_INFO("pCPA->m_pDBControllerInstance->Init() succeed")
	}

	
	// ISController Init
    if (!m_pISControllerInstance->Init())
	{
		m_pPrintInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pBurnInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pTransferInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pDiscImportInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pWlMppsInstance->SetSubModuleState(enumSubModuleState_Error);

		SetWorkState(enumWORKSTATE_ERROR);
		ARCHVTRACE_ERROR("pCPA->m_pISControllerInstance->Init() failed")
		return FALSE;
	}
	else
	{
		ARCHVTRACE_INFO("pCPA->m_pISControllerInstance->Init() succeed")
	}

	//设置语言
	if (!m_pLanguageIniOptInstance->Init())
	{
		m_pPrintInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pBurnInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pTransferInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pDiscImportInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pWlMppsInstance->SetSubModuleState(enumSubModuleState_Error);

		SetWorkState(enumWORKSTATE_ERROR);
		ARCHVTRACE_ERROR("pCPA->m_pLanguageIniOptInstance.Init() failed")
		//语言设置不成功，不返回false，继续进行(来自DR CE认证)  [5/3/2011 gaoxing]
		//return FALSE;
	}
	else
	{
		ARCHVTRACE_INFO("pCPA->m_pLanguageIniOptInstance.Init() succeed")
	}


	// PADBOpt init
	if (!m_pPADBOptInstance->Init())
	{
		//<< 失败无需P&A模块失败
		ARCHVTRACE_ERROR("m_pPADBOptInstance->Init()")
	}
	else
	{
		ARCHVTRACE_INFO("m_pPADBOptInstance->Init() succeed")
	}

	// UGOpt init
	if (!m_pUGOptInstance->Init())
	{
		m_pPrintInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pBurnInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pTransferInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pDiscImportInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pWlMppsInstance->SetSubModuleState(enumSubModuleState_Error);

		SetWorkState(enumWORKSTATE_ERROR);
		ARCHVTRACE_ERROR("m_pUGOptInstance->Init()")
		return FALSE;
	}
	else
	{
		ARCHVTRACE_INFO("m_pUGOptInstance->Init() succeed")
	}

	if (!m_DcmPartner.Init())
	{
		m_pPrintInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pBurnInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pTransferInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pDiscImportInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pWlMppsInstance->SetSubModuleState(enumSubModuleState_Error);

		SetWorkState(enumWORKSTATE_ERROR);
		ARCHVTRACE_ERROR("m_DcmPartner.Init()")
		return FALSE;
	}
	else
	{
		ARCHVTRACE_INFO("m_DcmPartner->Init() succeed")
	}

	// CJobHandler Init
    if (!m_pJobHandlerInstance->Init())
	{
		m_pPrintInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pBurnInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pTransferInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pDiscImportInstance->SetSubModuleState(enumSubModuleState_Error);
		m_pWlMppsInstance->SetSubModuleState(enumSubModuleState_Error);

		SetWorkState(enumWORKSTATE_ERROR);
		ARCHVTRACE_ERROR("m_pJobHandlerInstance->Init() failed")
		return FALSE;
	}
	else
	{
		ARCHVTRACE_INFO("m_pJobHandlerInstance->Init() succeed")
	}

	// CWlMpps Init
	if (!m_pWlMppsInstance->Init())
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("pCPA->m_pWlMppsInstance->Init() failed")
	}
	else
	{
		ARCHVTRACE_INFO("pCPA->m_pWlMppsInstance->Init() succeed")
	}

	// CPrinting sub-module Init
	if (!m_pPrintInstance->Init())
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("pCPA->m_pPrintInstance->Init() failed")
	}
	else
	{
		ARCHVTRACE_INFO("pCPA->m_pPrintInstance->Init() succeed")
	}

	// CBurner sub-module Init
	if (!m_pBurnInstance->Init())
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("pCPA->m_pBurnInstance->Init() failed")
	}
	else
	{
		ARCHVTRACE_INFO("pCPA->m_pBurnInstance->Init() succeed")
	}

	
	//CTransfer sub-module Init
	if (!m_pTransferInstance->Init())
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("pCPA->m_pTransferInstance->Init() failed")
	}
	else
	{
		ARCHVTRACE_INFO("pCPA->m_pTransferInstance->Init() succeed")
	}

	//CDiscImport sub-module Init
	if (!m_pDiscImportInstance->Init())
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("pCPA->m_pDiscImportInstance->Init() failed")
	}
	else
	{
		ARCHVTRACE_INFO("pCPA->m_pDiscImportInstance->Init() succeed")
	}

	if (bRet)
		return TRUE;
	else
		return FALSE;
}

BOOL CPA::ShutDownProc()
{
	SetWorkState(enumWORKSTATE_UNINITIALIZING);

	BOOL bRet = TRUE;

	if (m_StartUpThreadHandle)
	{
		CloseHandle(m_StartUpThreadHandle);
		m_StartUpThreadHandle = NULL;
	}

	if (m_pPrintInstance->UnInit())
	{
		PRINTTRACE_INFO("m_pPrintInstance->UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("m_pPrintInstance->UnInit() failed")
	}

	if (m_pWlMppsInstance->UnInit())
	{
		ARCHVTRACE_INFO("m_pWlMppsInstance->UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_pWlMppsInstance->UnInit() failed")
	}

	if (m_pJobHandlerInstance->UnInit())
	{
		PRINTTRACE_INFO("m_pJobHandlerInstance->UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("m_pJobHandlerInstance->UnInit() failed")
	}


	if (m_pBurnInstance->UnInit())
	{
		ARCHVTRACE_INFO("m_pBurnInstance->UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_pBurnInstance->UnInit() failed")
	}

	if (m_pTransferInstance->UnInit())
	{
		ARCHVTRACE_INFO("m_pTransferInstance->UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_pTransferInstance->UnInit() failed")
	}
	
	if (m_pDiscImportInstance->UnInit())
	{
		ARCHVTRACE_INFO("m_pDiscImportInstance->UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_pDiscImportInstance->UnInit() failed")
	}

	m_DcmPartner.UnInit();

	if (m_pUGOptInstance->UnInit())
	{
		ARCHVTRACE_INFO("m_pUGOptInstance.UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_pUGOptInstance.UnInit() failed")
	}


	if (m_pDBControllerInstance->UnInit())
	{
		ARCHVTRACE_INFO("m_DBController.UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_DBController.UnInit() failed")
	}

	if (m_pISControllerInstance->UnInit())
	{
		ARCHVTRACE_INFO("m_pISControllerInstance.UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_pISControllerInstance.UnInit() failed")
	}

	if (m_pLanguageIniOptInstance->UnInit())
	{
		ARCHVTRACE_INFO("m_pLanguageIniOptInstance.UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_pLanguageIniOptInstance.UnInit() failed")
	}


	if (m_pPADBOptInstance->UnInit())
	{
		ARCHVTRACE_INFO("m_pPADBOptInstance.UnInit() succeed")
	}
	else
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_pPADBOptInstance.UnInit() failed")
	}


	SetWorkState(enumWORKSTATE_UNINITIALIZED);
	
	return bRet;
}

BOOL CPA::PushMsgToFireMsgQueue(FireMsgNode& MsgNode)
{
	return m_pFireMsgInstance->PushMsg(MsgNode);
}

BOOL CPA::IsInterfaceValid()
{
	if (enumWORKSTATE_READY == m_WorkState ||
		enumWORKSTATE_WORKING == m_WorkState ||
		enumWORKSTATE_ERROR == m_WorkState )
	{
		return TRUE;
	}
	else
	{
		PRINTTRACE_INFO("Interface Unaccessable since CPA module state is not ready, working or error")
		return FALSE;
	}
}

BOOL CPA::IsPrintInterfaceValid()
{
	SubModuleState enumSubModuleState = m_pPrintInstance->GetSubModuleState();
	if (enumSubModuleState_Ready == enumSubModuleState ||
		enumSubModuleState_Work == enumSubModuleState)
	{
		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR("Print SubModule interface unvalid since it's state is not Ready or Work")
		return FALSE;
	}
}

BOOL CPA::IsBurnInterfaceValid()
{
	SubModuleState enumSubModuleState = m_pBurnInstance->GetSubModuleState();
	if (enumSubModuleState_Ready == enumSubModuleState ||
		enumSubModuleState_Work == enumSubModuleState)
	{
		return TRUE;
	}
	else
	{
		ARCHVTRACE_ERROR("Burn SubModule interface unvalid since it's state is not Ready or Work")
		return FALSE;
	}
}

BOOL CPA::IsTransferInterfaceValid()
{
	SubModuleState enumSubModuleState = m_pTransferInstance->GetSubModuleState();
	if (enumSubModuleState_Ready == enumSubModuleState ||
		enumSubModuleState_Work == enumSubModuleState)
	{
		return TRUE;
	}
	else
	{
		ARCHVTRACE_ERROR("Transfer SubModule interface unvalid since it's state is not Ready or Work")
		return FALSE;
	}
}

BOOL CPA::IsDiscImportInterfaceValid()
{
	SubModuleState enumSubModuleState = m_pDiscImportInstance->GetSubModuleState();
	if (enumSubModuleState_Ready == enumSubModuleState ||
		enumSubModuleState_Work == enumSubModuleState)
	{
		return TRUE;
	}
	else
	{
		ARCHVTRACE_ERROR("DiscImport SubModule interface unvalid since it's state is not Ready or Work")
		return FALSE;
	}
}

BOOL CPA::IsWlMppsInterfaceValid()
{
	SubModuleState enumSubModuleState = m_pWlMppsInstance->GetSubModuleState();
	if (enumSubModuleState_Ready == enumSubModuleState ||
		enumSubModuleState_Work == enumSubModuleState)
	{
		return TRUE;
	}
	else
	{
		ARCHVTRACE_ERROR("WlMpps SubModule interface unvalid since it's state is not Ready or Work")
		return FALSE;
	}
}


//
STDMETHODIMP CPA::GetStartupResult(/*[out]*/STARTUPRESULT* pResult)
{
	PRINTTRACE_ENTER_FUNCTION

	*pResult = m_StartUpResult;
	return S_OK;
}

STDMETHODIMP CPA::GetWorkState(/*[out]*/WORKSTATE* pState)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			return S_FALSE;
		}

		*pState = m_WorkState;
		return S_OK;
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetError(/*[out]*/INT* pError)
{
	PRINTTRACE_ENTER_FUNCTION

	return S_OK;
}

//IUserWorkingMode
STDMETHODIMP CPA::Logout()
{
	PRINTTRACE_ENTER_FUNCTION

	return S_OK;
}

STDMETHODIMP CPA::Login()
{
	PRINTTRACE_ENTER_FUNCTION

	return S_OK;
}

STDMETHODIMP CPA::GetPatientStudySeriesImageOccupyState(PatientAdminUIDType enumUIDType, long lUIDNum, BSTR* pbsUIDList, BOOL* pbOccupied)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		vector<CString> vtrUIDList;
		CString strUID;
		PRINTTRACE_INFO("GetPatientStudySeriesOccupyState, UIDs is: ")
		for (int i = 0; i < lUIDNum; i++)
		{
			BSTR* pbsUID = pbsUIDList + i;
			strUID = CBSTROpt::BSTRToCString(*pbsUID);
			PRINTTRACE_INFO(strUID);
			vtrUIDList.push_back(strUID);
		}
		
 		*pbOccupied = m_pJobHandlerInstance->IsPatientStudySeriesImageUIDInUse(enumUIDType, &vtrUIDList);
		sLock.Unlock();
		return S_OK;
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::ReportUserGuidance(LONG iMessageID, USER_GUIDANCE_TYPE enumType, USER_GUIDANCE_PRIORITY enumPrior, BOOL bActive)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		UGNotifyStruct* pUG = new UGNotifyStruct;
		pUG->iMessageID = iMessageID;
		pUG->enumUGType = enumType;
		pUG->enumGUIPriority = enumPrior;
		pUG->bActive = bActive;

		FireMsgNode msgNode;
		msgNode.msg.uiMessage = NOTIFY_USERGUIDANCE;
		msgNode.msg.lParam = (LPARAM)pUG;
		msgNode.msg.wParam = 0;
		msgNode.pNextNode = NULL;
		if (PushMsgToFireMsgQueue(msgNode))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			delete pUG;
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR

}

STDMETHODIMP CPA::GetJobList(JobInfo** ppJobList, long* pLen)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pJobHandlerInstance->GetJobList(ppJobList, pLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pJobHandler->GetJobList(ppJobList, pLen)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::MoveJob(BSTR bsJobID, BOOL bForward)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
		if (m_pJobHandlerInstance->MoveJob(strJobID, bForward))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("oveJob(strJobID, bForward)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::CancelJobs(BSTR* pbsJobIDs, long lNum)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		vector<CString> vtrJobIDs;
		for (int i = 0; i < lNum; i++)
		{
			CString strJobID = CBSTROpt::BSTRToCString(*(pbsJobIDs+i));
			vtrJobIDs.push_back(strJobID);
		}

		if (m_pJobHandlerInstance->CancelJobs(&vtrJobIDs))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pJobHandler->CancelJobs(&vtrJobIDs)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::DeleteJobs(BSTR* pbsJobIDs, long lNum)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		vector<CString> vtrJobIDs;
		for (int i = 0; i < lNum; i++)
		{
			CString strJobID = CBSTROpt::BSTRToCString(*(pbsJobIDs+i));
			vtrJobIDs.push_back(strJobID);
		}

		if (m_pJobHandlerInstance->DeleteJobs(&vtrJobIDs))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pJobHandler->DeleteJobs(&vtrJobIDs)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetHistoryJobCount(DWORD* pdwCount)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pPADBOptInstance->GetJobCount(pdwCount))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPADBOptInstance->GetJobCount()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}


STDMETHODIMP CPA::GetHistoryJobs(DWORD dwStartIndex, DWORD* pdwCount, JobInfo** ppJobList)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pPADBOptInstance->GetJobs(dwStartIndex, pdwCount, ppJobList))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPADBOptInstance->GetJobs()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetHistoryJobInfo(BSTR bsJobID, JobInfo* pJobInfo)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
		if (m_pPADBOptInstance->GetJobInfo(strJobID, pJobInfo))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPADBOptInstance->GetHistoryJobPSSIInfo()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetHistoryJobPSSIInfo(BSTR bsJobID, long* pLen, PSSIInfo** ppPSSIList)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
		if (m_pPADBOptInstance->GetJobPSSIInfo(strJobID, pLen, ppPSSIList))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPADBOptInstance->GetHistoryJobPSSIInfo()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetHistoryJobNetworkNodeInfo(BSTR bsJobID, long* pLen, NetworkNode** ppNodeList)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
		if (m_pPADBOptInstance->GetJobNetworkNodeInfo(strJobID, pLen, ppNodeList))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPADBOptInstance->GetHistoryJobNetworkNodeInfo()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetHistoryJobDetailInfo(BSTR bsJobID, long* pLen, JobDetailStruct** ppDetailList)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
		if (m_pPADBOptInstance->GetJobDetailInfo(strJobID, pLen, ppDetailList))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPADBOptInstance->GetHistoryJobDetailInfo()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetHistoryJobDiscImportImageInfo(BSTR bsJobID, long* pLen, DiscImport_SeriesStruct** ppDISSList)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
		if (m_pPADBOptInstance->GetJobDiscImportImageInfo(strJobID, pLen, ppDISSList))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPADBOptInstance->GetHistoryJobDiscImportImageInfo()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::DeleteHistoryJobs(long lNum, BSTR* pbsJobIDList)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		vector<CString> vtrJobIDs;
		for (int i = 0; i < lNum; i++)
		{
			CString strJobID = CBSTROpt::BSTRToCString(pbsJobIDList[i]);
			vtrJobIDs.push_back(strJobID);
		}

		if (m_pPADBOptInstance->DeleteJobs(vtrJobIDs))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPADBOptInstance->DeleteHistoryJobs()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::DeleteAllHistoryJobs()
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pPADBOptInstance->DeleteAllJobs())
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPADBOptInstance->DeleteAllHistoryJobs()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::CompactDB(BOOL bBackUp)
{
	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pPADBOptInstance->CompactDabaBase(bBackUp))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPADBOptInstance->CompactDabaBase()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

//Print
STDMETHODIMP CPA::Print(long lUIDNum, BSTR* pbsImageUIDList)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (!IsPrintInterfaceValid())
		{
			sLock.Unlock();
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsPrintInterfaceValid()")
			return S_FALSE;
		}

		vector<CString> vtrUID;
		for (int i = 0; i < lUIDNum; i++)
		{
			BSTR* pbsUID = pbsImageUIDList + i;
			CString strUID = CBSTROpt::BSTRToCString(*pbsUID);
			vtrUID.push_back(strUID);
		}
		
		if (m_pPrintInstance->LoadToFC(&vtrUID))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPrintInstance->CreateJob(pPrintJobSettings)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
	
}

STDMETHODIMP CPA::GetPrintJobList(JobInfo** ppJobInfoList, long *pLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		if (!IsPrintInterfaceValid())
		{
			sLock.Unlock();
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsPrintInterfaceValid()")
			return S_FALSE;
		}

// 		if (m_pPrintInstance->GetJobList(ppJobInfoList, pLen))
// 		{
// 			sLock.Unlock();
// 			return S_OK;
// 		}
// 		else
		{
			PRINTTRACE_ERROR("m_pPrintInstance->GetJobList(ppJobInfoList, pLen)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::ShowFCProgressBar(BOOL bShow)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		if (!IsPrintInterfaceValid())
		{
			sLock.Unlock();
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsPrintInterfaceValid()")
			return S_FALSE;
		}

		if (m_pPrintInstance->ShowFCProgressBar(bShow))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPrintInstance->ShowFCProgressBar(bShow)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}


STDMETHODIMP CPA::GetPrintNetworkNodes(NetworkNode** ppNodesList, long* pLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		if (!IsPrintInterfaceValid())
		{
			sLock.Unlock();
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsPrintInterfaceValid()")
			return S_FALSE;
		}
		
		if (m_pPrintInstance->GetNetworkNodes(ppNodesList, pLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pPrintInstance->GetNetworkNodes(ppNodesList, pLen)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetPrintErrorMsg(int iErrCode, BSTR* bsErrMsg)
{
	PRINTTRACE_ENTER_FUNCTION

	GetErrorMsg(iErrCode, bsErrMsg);
	return S_OK;
}

STDMETHODIMP CPA::GetPrintSubModuleState(SubModuleState* pSubModuleState)
{
	*pSubModuleState = m_pPrintInstance->GetSubModuleState();
	return S_OK;
}

void CPA::GetErrorMsg(int iErrCode, BSTR* bsErrMsg)
{
	CString strErrMsg;
	switch (iErrCode)
	{
	case E_OK:
		strErrMsg = E_OK_INFO;
		break;
	case E_UNEXPECTED_ERROR:
		strErrMsg = E_UNEXPECTED_ERROR_INFO;
		break;
	case E_INVALID_PARA:
		strErrMsg = E_INVALID_PARA_INFO;
		break;
	case E_BURN_NERO_API_UNINITED:
		strErrMsg = E_BURN_NERO_API_UNINITED_INFO;
		break;
	case E_BURN_NERO_API_INIT_FAILED:
		strErrMsg = E_BURN_NERO_API_INIT_FAILED_INFO;
		break;
	case E_BURN_NO_DEVICE_FOUND:
		strErrMsg = E_BURN_NO_DEVICE_FOUND_INFO;
		break;
	case E_BURN_NO_SPECIFIED_DEVICE:
		strErrMsg = E_BURN_NO_SPECIFIED_DEVICE_INFO;
		break;
	case E_BURN_NO_DISC_OR_DISC_CORRUPTED:
		strErrMsg = E_BURN_NO_DISC_OR_DISC_CORRUPTED_INFO;
		break;
	case E_BURN_MEDIA_NOT_DVD:
		strErrMsg = E_BURN_MEDIA_NOT_DVD_INFO;
		break;
	case E_BURN_MEDIA_NOT_CD:
		strErrMsg = E_BURN_MEDIA_NOT_CD_INFO;
		break;
	case E_BURN_DISC_NOT_WRITEABLE:
		strErrMsg = E_BURN_DISC_NOT_WRITEABLE_INFO;
		break;
	case E_BURN_NOT_SUPPORT_BURNING_SPECIFIED_MEDIA:
		strErrMsg = E_BURN_NOT_SUPPORT_BURNING_SPECIFIED_MEDIA_INFO;
		break;
	case E_BURN_CANT_OPEN_NERO_API_DLL:
		strErrMsg = E_BURN_CANT_OPEN_NERO_API_DLL_INFO;
		break;
	case E_BURN_NERO_API_INVALID_SERIAL_NUM:
		strErrMsg = E_BURN_NERO_API_INVALID_SERIAL_NUM_INFO;
		break;
	case E_BURN_NO_BURN_DIR_OR_FILE:
		strErrMsg = E_BURN_NO_BURN_DIR_OR_FILE_INFO;
		break;
	case E_BURN_DEVICE_NOT_SPECIFIED:
		strErrMsg = E_BURN_DEVICE_NOT_SPECIFIED_INFO;
		break;
	case E_BURN_OPEN_DEVICE_FAILED:
		strErrMsg = E_BURN_OPEN_DEVICE_FAILED_INFO;
		break;
	case E_BURN_NERO_MEMORY_LEAK:
		strErrMsg = E_BURN_NERO_MEMORY_LEAK_INFO;
		break;
	case E_BURN_UNSET_DISC_NAME:
		strErrMsg = E_BURN_UNSET_DISC_NAME_INFO;
		break;
	case E_BURN_UNSET_DISC_TYPE:
		strErrMsg = E_BURN_UNSET_DISC_TYPE_INFO;
		break;
	case E_BURN_UNSET_BURN_SPEED:
		strErrMsg = E_BURN_UNSET_BURN_SPEED_INFO;
		break;
	case E_BURN_NOT_APPLICABLE_DURING_BURNING:
		strErrMsg = E_BURN_NOT_APPLICABLE_DURING_BURNING_INFO;
		break;
	case E_BURN_A_BURN_THREAD_IS_ALREADY_RUNNING:
		strErrMsg = E_BURN_A_BURN_THREAD_IS_ALREADY_RUNNING_INFO;
		break;
	case E_BURN_NOT_EMPTY_DISC:
		strErrMsg = E_BURN_NOT_EMPTY_DISC_INFO;
		break;
	case E_BURN_FILES_NAME_CONFLICT:
		strErrMsg = E_BURN_FILES_NAME_CONFLICT_INFO;
		break;
	case E_BURN_INVALID_DIR_OR_FILE:
		strErrMsg = E_BURN_INVALID_DIR_OR_FILE_INFO;
		break;
	case E_BURN_DISC_NAME_TOO_LONG:
		strErrMsg = E_BURN_DISC_NAME_TOO_LONG_INFO;
		break;
	case E_BURN_USER_ABORT:
		strErrMsg = E_BURN_USER_ABORT_INFO;
		break;
	default:
		strErrMsg = _T("No Error Message for this Error Code");
		break;
	}

	*bsErrMsg = strErrMsg.AllocSysString();
}


BOOL CPA::SetWorkState(WORKSTATE State)
{
	if (m_WorkState == State)
		return TRUE;

	CSingleLock sLock(&m_CSLockModuleState);
	sLock.Lock();
	m_WorkState = State;
	sLock.Unlock();

	FireMsgNode msgNode;
	msgNode.msg.uiMessage = NOTIFY_CPA_WORKSTATE;
	msgNode.msg.lParam = m_WorkState;
	msgNode.msg.wParam = 0;
	msgNode.pNextNode = NULL;
	BOOL bRet = PushMsgToFireMsgQueue(msgNode);

	CString strTrace;
	strTrace = _T("CPA module state: ");
	switch (m_WorkState)
	{
	case enumWORKSTATE_UNINITIALIZED:
		if (enumSTARTUPRESULT_UNKNOWN != m_StartUpResult)
		{
			m_StartUpResult = enumSTARTUPRESULT_UNKNOWN;
		}
		strTrace += _T("Uninitialized");
		break;
	case enumWORKSTATE_INITIALIZING:
		strTrace += _T("Initializing");
		break;
	case enumWORKSTATE_READY:
		if (enumSTARTUPRESULT_UNKNOWN == m_StartUpResult)
		{
			m_StartUpResult = enumSTARTUPRESULT_SUCCESS;
			msgNode.msg.uiMessage = NOTIFY_CPA_STARTUPRESULT;
			msgNode.msg.lParam = m_StartUpResult;
			msgNode.msg.wParam = 0;
			msgNode.pNextNode = NULL;
			bRet = PushMsgToFireMsgQueue(msgNode);
			ARCHVTRACE_INFO("CPA startup result: enumSTARTUPRESULT_SUCCESS")
		}
		strTrace += _T("Ready");
		break;
	case enumWORKSTATE_WORKING:
		strTrace += _T("Working");
		break;
	case enumWORKSTATE_UNINITIALIZING:
		strTrace += _T("Uninitializing");
		break;
	case enumWORKSTATE_ERROR:
		if (enumSTARTUPRESULT_UNKNOWN == m_StartUpResult)
		{
			m_StartUpResult = enumSTARTUPRESULT_FAILED;
			msgNode.msg.uiMessage = NOTIFY_CPA_STARTUPRESULT;
			msgNode.msg.lParam = m_StartUpResult;
			msgNode.msg.wParam = 0;
			msgNode.pNextNode = NULL;
			bRet = PushMsgToFireMsgQueue(msgNode);
			ARCHVTRACE_INFO("CPA startup result: enumSTARTUPRESULT_FAILED")
		}
		strTrace += _T("Error");
		break;
	default:
		strTrace += _T("Unknow");
		break;
	}
	ARCHVTRACE_INFO(strTrace);

	return bRet;
}

BOOL CPA::HandleBackGroundJobAcq()
{
	CSingleLock sLock(&m_CSLockAcqEvent);
	sLock.Lock();

	BOOL bRet = TRUE;

#ifdef HANDLE_PRINT_DURING_ACQ
	if (m_pPrintInstance->HandlePrintBeforeAcq())
	{
		ARCHVTRACE_INFO("m_pPrintInstance->PausePrint()")
	}
	else
	{
		ARCHVTRACE_ERROR("m_pPrintInstance->PausePrint()")
		bRet = FALSE;
	}
#endif

#ifdef HANDLE_TRANSFER_DURING_ACQ
	m_pTransferInstance->PauseTransfer();
#endif

#ifdef HANDLE_BURN_DURING_ACQ
// 	if (m_pBurnInstance->AbortBurnWork())
// 	{
// 		ARCHVTRACE_INFO("m_pBurnInstance->AbortBurnWork(TRUE)")
// 	}
// 	else
// 	{
// 		ARCHVTRACE_ERROR("m_pBurnInstance->AbortBurnWork(TRUE)")
// 		bRet = FALSE;
// 	}
#endif

#ifdef HANDLE_DISCIMPORT_DURING_ACQ
	if (m_pDiscImportInstance->HandleWorkBeforeAcq())
	{
		ARCHVTRACE_INFO("m_pDiscImportInstance->HandleWorkBeforeAcq()")
	}
	else
	{
		ARCHVTRACE_ERROR("m_pDiscImportInstance->HandleWorkBeforeAcq()")
		bRet = FALSE;
	}
#endif

	// MPPS NCreate
	CString strStudyUID;
	CString strTrace;
	if (CDBController::GetInstance()->GetCurrentStudyUID(strStudyUID))
	{
		if (strStudyUID.IsEmpty())
		{
			bRet = FALSE;
			PRINTTRACE_ERROR("CDBController::GetInstance()->GetCurrentStudyUID(), strStudyUID == _T("")")
		}
		else
		{
			BSTR bsStudyUID = strStudyUID.AllocSysString();
			HRESULT hResult = SetMPPSStatus(bsStudyUID, enumWorkListStatus_InProgress);
			CBSTROpt::FreeBSTR(bsStudyUID);
			if (S_OK == hResult)
			{
				strTrace.Format(_T("S_OK == SetMPPSStatus(), StudyUID: %s"), strStudyUID);
				PRINTTRACE_INFO(strTrace)
			}
			else
			{
				bRet = FALSE;
				strTrace.Format(_T("S_OK != SetMPPSStatus(), StudyUID: %s"), strStudyUID);
				PRINTTRACE_ERROR(strTrace)
			}
		}

	}
	else
	{
		PRINTTRACE_ERROR("CDBController::GetInstance()->GetCurrentStudyUID()")
		bRet = FALSE;
	}

	sLock.Unlock();
	return bRet;
}

BOOL CPA::ResumeBackGroundJobAcq()
{
	CSingleLock sLock(&m_CSLockAcqEvent);
	sLock.Lock();

	BOOL bRet = TRUE;

#ifdef HANDLE_PRINT_DURING_ACQ
	m_pPrintInstance->HandlePrintAfterAcq();
#endif

#ifdef HANDLE_TRANSFER_DURING_ACQ
	m_pTransferInstance->ResumeTransfer();
#endif

#ifdef HANDLE_BURN_DURING_ACQ
	// do nothing
#endif

#ifdef HANDLE_DISCIMPORT_DURING_ACQ
	// nothing to do
#endif

	sLock.Unlock();
	return bRet;
}


// For Burn setting
STDMETHODIMP CPA::SetBurnDevice(BSTR bsDeviceName)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (!IsBurnInterfaceValid())
		{
			sLock.Unlock();
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			return S_FALSE;
		}

		CString strDeviceName;
		strDeviceName = CBSTROpt::BSTRToCString(bsDeviceName);
		
		if (m_pBurnInstance->SetDevice((LPCTSTR)strDeviceName))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pBurnInstance->SetDevice(strDeviceName)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	PA_CATCH_ERROR

}


STDMETHODIMP CPA::GetDevices(BSTR** ppbsDevices, long* pLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (!IsBurnInterfaceValid())
		{
			sLock.Unlock();
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			return S_FALSE;
		}

		if (m_pBurnInstance->GetDevices(ppbsDevices, pLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pBurnInstance->GetDevices(ppDeviceInfo, pLen)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetCurrentDeviceMediaInfo()
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (!IsBurnInterfaceValid())
		{
			sLock.Unlock();
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			return S_FALSE;
		}

		if (m_pBurnInstance->GetDeviceDiscInfo())
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pBurnInstance->GetCurrentDeviceMediaInfo()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetEstimatedSize(BOOL bBMP, BOOL bJPEG, unsigned long* plSizeInMega)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (!IsBurnInterfaceValid())
		{
			sLock.Unlock();
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			return S_FALSE;
		}

		if (m_pBurnInstance->GetEstimatedSize(bBMP, bJPEG, plSizeInMega))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pBurnInstance->GetEstimatedSize()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::BurnPrepare(long lUIDNum, BSTR* pbsUIDList, PatientAdminUIDType enumUIDType)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsBurnInterfaceValid())
		{
			sLock.Unlock();
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			return S_FALSE;
		}

		vector<CString> vtrUID;
		for (int i = 0; i < lUIDNum; i++)
		{
			BSTR* pbsUID = pbsUIDList + i;
			CString strUID = CBSTROpt::BSTRToCString(*pbsUID);
			vtrUID.push_back(strUID);
		}

		if (m_pBurnInstance->BurnPrepare(&vtrUID, enumUIDType))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pBurnInstance->CancelBurn((LPCTSTR)strJobID)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::CancelBurnPrepare()
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsBurnInterfaceValid())
		{
			sLock.Unlock();
			PRINTTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			return S_FALSE;
		}

		if (m_pBurnInstance->CancelBurnPrepare())
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pBurnInstance->CancelBurn((LPCTSTR)strJobID)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::BurnByPA(BurnJobSettingsByPA* pBurnJobSettingsByPA)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		if (!IsBurnInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pBurnInstance->CreateJob(pBurnJobSettingsByPA))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pBurnInstance->CreateJobByPA(&vtrUID, enumUIDType, pBurnJobSettingsByPA)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetBurnJobInfo(BSTR bsJobID, JobInfo* pJobInfo, PSSIInfo** ppPSSIList, long* pPSSILen, JobDetailStruct** ppDetailList, long* pDetailLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		if (!IsBurnInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
		if (m_pJobHandlerInstance->GetBurnJobInfo(strJobID, pJobInfo, ppPSSIList, pPSSILen, ppDetailList, pDetailLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pBurnInstance->CreateJobByPA(&vtrUID, enumUIDType, pBurnJobSettingsByPA)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::EnableCheckDevice(BOOL bCheck)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		if (!IsBurnInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		m_pBurnInstance->EnableCheckDevice(bCheck);

		sLock.Unlock();
		return S_OK;
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::SetBurnMediaCheckRetry(BOOL bRetry)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		if (!IsBurnInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

 		m_pBurnInstance->SetBurnMediaCheckRetry(bRetry);

		sLock.Unlock();
		return S_OK;
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::IsUnfinishedBurnJobExist(BOOL* pbExist)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		if (!IsBurnInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsBurnInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

 		if (m_pJobHandlerInstance->IsUnfinishedJobExist(enumJobType_BurnJob, pbExist))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pJobHandlerInstance->IsUnfinishedJobExist(enumJobType_BurnJob, pbExist)")
			sLock.Unlock();
			return S_FALSE;
		}

	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetBurnErrorMsg(int iErrCode, BSTR* bsErrMsg)
{
	PRINTTRACE_ENTER_FUNCTION

	GetErrorMsg(iErrCode, bsErrMsg);
	return S_OK;
}

STDMETHODIMP CPA::GetBurnSubModuleState(SubModuleState* pSubModuleState)
{
	PRINTTRACE_ENTER_FUNCTION

	*pSubModuleState = m_pBurnInstance->GetSubModuleState();
	return S_OK;
}


//Transfer
STDMETHODIMP CPA::AutoTransfer(BSTR bsUID, PatientAdminUIDType enumUIDType)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strUID = CBSTROpt::BSTRToCString(bsUID);
		if (m_pTransferInstance->CreateJobAutoSend(strUID, enumUIDType))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->CreateJobAutoSend(strStudyUID)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
	
}

STDMETHODIMP CPA::ManualTransfer(long lUIDNum, BSTR* pbsUIDList, PatientAdminUIDType enumUIDType, TransferJobSettingsByUID* pTransferJobSettings)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		vector<CString> vtrUIDs;
		for (int i = 0; i < lUIDNum; i++)
		{
			CString strUID = CBSTROpt::BSTRToCString(*(pbsUIDList + i));
			vtrUIDs.push_back(strUID);
		}

		vector<NetworkNodeStruct>	vtrNodes;
		NetworkNodeStruct nns;
		nns.bDefault = pTransferJobSettings->bSelected;
		nns.strCalledAE = CBSTROpt::BSTRToCString(pTransferJobSettings->bsCalledAE);
		nns.bRaw = pTransferJobSettings->bRaw;
		nns.bProcessed = pTransferJobSettings->bProcessed;

		// Add [Sun hongwen 10/16/2009]
		nns.bSendPS = pTransferJobSettings->bSendPS;
		//

		vtrNodes.push_back(nns);


		if (m_pTransferInstance->CreateJobManualSend(&vtrUIDs, enumUIDType, vtrNodes))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->ManualTransfer()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
	
}

STDMETHODIMP CPA::ManualTransferWithMultiServers(long lUIDNum, BSTR* pbsUIDList, PatientAdminUIDType enumUIDType, long lServerNum, TransferJobSettingsByUID* pTransferJobSettings)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		vector<CString> vtrUIDs;
		for (int i = 0; i < lUIDNum; i++)
		{
			CString strUID = CBSTROpt::BSTRToCString(*(pbsUIDList + i));
			vtrUIDs.push_back(strUID);
		}

		vector<NetworkNodeStruct>	vtrNodes;
		for (int j = 0; j < lServerNum; j++)
		{
			NetworkNodeStruct nns;
			nns.bDefault = (pTransferJobSettings + j)->bSelected;
			nns.strCalledAE = CBSTROpt::BSTRToCString((pTransferJobSettings + j)->bsCalledAE);
			nns.bRaw = (pTransferJobSettings + j)->bRaw;
			nns.bProcessed = (pTransferJobSettings + j)->bProcessed;

			// Add [Sun hongwen 10/16/2009]
			nns.bSendPS = (pTransferJobSettings + j)->bSendPS;
			//

			vtrNodes.push_back(nns);
		}

		if (m_pTransferInstance->CreateJobManualSend(&vtrUIDs, enumUIDType, vtrNodes))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->ManualTransferWithMultiServers()")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetSendJobInfo(BSTR bsJobID, JobInfo* pJobInfo, PSSIInfo** ppPSSIList, long* pPSSILen, NetworkNode** ppNodeList, long* pNodeLen, JobDetailStruct** ppDetailList, long* pDetailLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
		if (m_pJobHandlerInstance->GetSendJobInfo(strJobID, pJobInfo, ppPSSIList, pPSSILen, ppNodeList, pNodeLen, ppDetailList, pDetailLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->CreateJobByUID(enumJobType_TransferJob, pTransferJobSettings)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetTransferSubModuleState(SubModuleState* pSubModuleState)
{
	PRINTTRACE_ENTER_FUNCTION

	*pSubModuleState = m_pTransferInstance->GetSubModuleState();
	return S_OK;
}

STDMETHODIMP CPA::IsUnfinishedTrnasferJobExist(BOOL* pbExist)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

 		if (m_pJobHandlerInstance->IsUnfinishedJobExist(enumJobType_AutoSendJob, pbExist))
		{
			if (*pbExist)
			{
				sLock.Unlock();
				return S_OK;
			}
			else
			{
				if (m_pJobHandlerInstance->IsUnfinishedJobExist(enumJobType_ManualSendJob, pbExist))
				{
					sLock.Unlock();
					return S_OK;
				}
				else
				{
					PRINTTRACE_ERROR("m_pJobHandlerInstance->IsUnfinishedJobExist(enumJobType_ManualSendJob, pbExist)")
					sLock.Unlock();
					return S_FALSE;
				}
			}

		}
		else
		{
			PRINTTRACE_ERROR("m_pJobHandlerInstance->IsUnfinishedJobExist(enumJobType_AutoSendJob, pbExist)")
			sLock.Unlock();
			return S_FALSE;
		}

	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetAutoServers(NetworkNode** ppServers, long* pLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pTransferInstance->GetAutoServers(ppServers, pLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->GetAutoServers(ppServers, pLen)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::IsAutoSendValid(BOOL* pbValid)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pTransferInstance->IsAutoSendValid(pbValid))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->IsAutoSendValid(pbValid)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::SetAutoServers(NetworkNode* pServers, long lLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pTransferInstance->SetAutoServers(pServers, lLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->SetAutoServers(pServers, lLen)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetManualServers(NetworkNode** ppServers, long* pLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pTransferInstance->GetManualServers(ppServers, pLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->GetManualServers(ppServers, pLen)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::SetManualServers(NetworkNode* pServers, long lLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pTransferInstance->SetManualServers(pServers, lLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->SetManualServers(pServers, lLen)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::ConnectTest(NetworkNode* pServer, BOOL* pbResult)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pTransferInstance->ConnectTest(pServer, pbResult))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->ConnectTest(pServer, pbResult)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}


// DiscImport
STDMETHODIMP CPA::GetDiscImportDevices(BSTR** ppbsDevices, long* pLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsDiscImportInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsDiscImportInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pDiscImportInstance->GetImportDevices(ppbsDevices, pLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetImportDiscInfoNotify(BSTR bsDevice)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsDiscImportInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsDiscImportInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strDevice = CBSTROpt::BSTRToCString(bsDevice);

		if (m_pDiscImportInstance->GetImportDiscInfoNotify(strDevice))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetImportDiscInfo(DiscImportPatientInfo** ppPatients,
								long* pPatientNum,
								DiscImportStudyInfo** ppStudies,
								long* pStudyNum,
								DiscImportSeriesInfo** ppSeries,
								long* pSeriesNum,
								DiscImportImageInfo** ppImages,
								long* pImageNum)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsDiscImportInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsDiscImportInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pDiscImportInstance->GetImportDiscInfo(ppPatients,
													pPatientNum,
													ppStudies,
													pStudyNum,
													ppSeries,
													pSeriesNum,
													ppImages,
													pImageNum))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::CancelGetImportDiscInfo()
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsDiscImportInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsDiscImportInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pDiscImportInstance->CancelGetImportDiscInfo())
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::DiscImport(long lUIDNum, BSTR* pbsUIDList, PatientAdminUIDType enumUIDType)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsDiscImportInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsDiscImportInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (0 == lUIDNum || NULL == pbsUIDList)
		{
			sLock.Unlock();
			return S_FALSE;
		}

		vector<CString> vtrUIDs;
		for (int i = 0; i < lUIDNum; i++)
		{
			CString strUID = CBSTROpt::BSTRToCString(*(pbsUIDList + i));
			vtrUIDs.push_back(strUID);
		}

		if (m_pDiscImportInstance->CreateJob(&vtrUIDs, enumUIDType))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetDiscImportJobInfo(BSTR bsJobID, DiscImport_SeriesStruct** ppSeriesList, long* pLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsDiscImportInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsDiscImportInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strJobID = CBSTROpt::BSTRToCString(bsJobID);
		if (m_pDiscImportInstance->GetJobInfo(strJobID, ppSeriesList, pLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::IsUnfinishedDiscImportJobExist(BOOL* pbExist)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();

		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		if (!IsDiscImportInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsDiscImportInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

 		if (m_pJobHandlerInstance->IsUnfinishedJobExist(enumJobType_DiscImportJob, pbExist))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			PRINTTRACE_ERROR("m_pJobHandlerInstance->IsUnfinishedJobExist(enumJobType_DiscImportJob, pbExist)")
			sLock.Unlock();
			return S_FALSE;
		}

	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetDiscImportSubModuleState(SubModuleState* pSubModuleState)
{
	*pSubModuleState = m_pDiscImportInstance->GetSubModuleState();
	return S_OK;
}


// WorkList and MPPS
STDMETHODIMP CPA::GetWlMppsSubModuleState(SubModuleState* pSubModuleState)
{
	*pSubModuleState = m_pWlMppsInstance->GetSubModuleState();
	return S_OK;
}

STDMETHODIMP CPA::GetWorkList()
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->GetWorkList())
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::RefreshWorkList(WorkListQueryCond* pWorkListQueryCond)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->RefreshWorkList(pWorkListQueryCond))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetImportPatientStudyInfo(BSTR bsStudyInstanceUID, WLPatientStudyStruct* pStruct)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strStudyInstanceUID = CBSTROpt::BSTRToCString(bsStudyInstanceUID);
		if (m_pWlMppsInstance->GetPatientStudyStruct(strStudyInstanceUID, pStruct))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::IsStudyImported(BSTR bsStudyInstanceUID, WLPatientStudyStatusInDB* pStatus)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strStudyInstanceUID = CBSTROpt::BSTRToCString(bsStudyInstanceUID);
		if (m_pWlMppsInstance->IsStudyImported(strStudyInstanceUID, pStatus))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::StudyImported(BSTR bsStudyInstanceUID)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strStudyInstanceUID = CBSTROpt::BSTRToCString(bsStudyInstanceUID);
		if (m_pWlMppsInstance->StudyImported(strStudyInstanceUID))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::DeleteAllImportedStudyRecords()
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (m_pPADBOptInstance->DeleteAllImportedStudyRecords())
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::IsMPPSValid(BOOL* pbValid)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->IsMPPSValid(pbValid))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::IsSetMPPSStatusEnabled(BSTR bsStudyUID, BOOL* pbEnabled)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->IsSetMPPSStatusEnabled((LPCTSTR)CString(CBSTROpt::BSTRToCString(bsStudyUID)), pbEnabled))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}


STDMETHODIMP CPA::GetStudyMPPSStatus(BSTR bsStudyUID, WorkListStatus* penumStatus)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		CString strStudyUID = CBSTROpt::BSTRToCString(bsStudyUID);
		if (m_pWlMppsInstance->GetStudyMppsStatus((LPCTSTR)strStudyUID, penumStatus))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::SetMPPSStatus(BSTR bsStudyUID, WorkListStatus enumStatus)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->SetMppsStatus((LPCTSTR)CString(CBSTROpt::BSTRToCString(bsStudyUID)), enumStatus))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}


STDMETHODIMP CPA::IsWorkListWorking(BOOL* pbWorking)
{
	try
	{
		*pbWorking = m_pWlMppsInstance->IsWorkListWorking();

		return S_OK;
	}
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::IsMppsWorking(BOOL* pbWorking)
{
	try
	{
		*pbWorking = m_pWlMppsInstance->IsMppsWorking();

		return S_OK;
	}
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::IsClosingStudyMPPS(BSTR bsStudyUID, BOOL* pbClosing)
{
	try
	{
		CString strStudyUID = CBSTROpt::BSTRToCString(bsStudyUID);
		*pbClosing = m_pWlMppsInstance->IsClosingStudyMPPS(strStudyUID);

		return S_OK;
	}
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::IsSettingPatientOrStudyMPPS(long lUIDNum, BSTR* pbsUIDs, PatientAdminUIDType enumUIDType, BOOL* pbSetting)
{
	try
	{
		vector<CString> vtrUIDs;
		for (int i = 0; i < lUIDNum; i++)
		{
			BSTR* pbsUID = pbsUIDs + i;
			CString strUID = CBSTROpt::BSTRToCString(*pbsUIDs);
			vtrUIDs.push_back(strUID);
		}

		if (m_pWlMppsInstance->IsSettingPatientOrStudyMPPS(vtrUIDs, enumUIDType, pbSetting))
		{
			return S_OK;
		}
		else
		{
			return S_FALSE;
		}
	}
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetWlServers(NetworkNode** ppServers, long* pLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->GetWlServers(ppServers, pLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::SetWlServers(NetworkNode* pServers, long lLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->SetWlServers(pServers, lLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::WlServerConnectTest(NetworkNode* pServer, BOOL* pbResult)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->WlServerConnectTest(pServer, pbResult))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetMppsServers(NetworkNode** ppServers, long* pLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->GetMppsServers(ppServers, pLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::SetMppsServers(NetworkNode* pServers, long lLen)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->SetMppsServers(pServers, lLen))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::MppsServerConnectTest(NetworkNode* pServer, BOOL* pbResult)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsWlMppsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsWlMppsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pWlMppsInstance->MppsServerConnectTest(pServer, pbResult))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			sLock.Unlock();
			return S_FALSE;
		}
	}

	PA_CATCH_ERROR
}

STDMETHODIMP CPA::SetEnableAutoTransferStatus(BOOL bEnable)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pTransferInstance->SetEnableAutoTransferStatus(bEnable))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->SetEnableAutoTransferStatus(bEnable)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetEnableAutoTransferStatus(BOOL *bEnable)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pTransferInstance->GetEnableAutoTransferStatus(bEnable))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->GetEnableAutoTransferStatus(bEnable)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}


STDMETHODIMP CPA::SetAskforAutoTransfer(BOOL bAskfor)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pTransferInstance->SetAskforAutoTransfer(bAskfor))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->SetAskforAutoTransfer(bAskfor)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}

STDMETHODIMP CPA::GetAskforAutoTransfer(BOOL *bAskfor)
{
	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CSingleLock sLock(&m_CSLockInterface);
		sLock.Lock();
		if (!IsInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}
		
		if (!IsTransferInterfaceValid())
		{
			ARCHVTRACE_ERROR("Failed to access interface because: FALSE == IsTransferInterfaceValid()")
			sLock.Unlock();
			return S_FALSE;
		}

		if (m_pTransferInstance->GetAskforAutoTransfer(bAskfor))
		{
			sLock.Unlock();
			return S_OK;
		}
		else
		{
			ARCHVTRACE_ERROR("m_pTransferInstance->GetAskforAutoTransfer(bAskfor)")
			sLock.Unlock();
			return S_FALSE;
		}
	}
	
	PA_CATCH_ERROR
}