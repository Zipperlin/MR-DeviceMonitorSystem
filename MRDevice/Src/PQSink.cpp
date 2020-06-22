/* Time: <@(#)PQSink.cpp   2009-3-5 - 10:50:26   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : PQSink.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Sink class to recieve print queue events in FilmComposer
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:50:26		FanZF	Creation
 *
 *********************************************************************
 */

// PQSink.cpp: implementation of the CPQSink class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PQSink.h"
#include "PrintQueueManager_i.c"
#include "FCPartner.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPQSink::CPQSink()
{
	//Initialize the member
	m_dwCookie = 0;
	m_ICallBack = (IUnknown*)this;
	m_pConnectionPoint = NULL;

	m_pFCPartner = NULL;

}

CPQSink::~CPQSink()
{
	
}

ULONG CPQSink::AddRef()
{
	return 1;
}

ULONG CPQSink::Release()
{
	return 0;
}

HRESULT CPQSink::QueryInterface(REFIID riid, void** ppv)
{
	//Return the interface for callback
	if(riid == IID_IUnknown)
	{
		*ppv = (_IPrintQueueChangeEvents*)this;
	}
	else if(riid == DIID__IPrintQueueChangeEvents)
	{
		*ppv = (_IPrintQueueChangeEvents*)this;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	return S_OK;
}

BOOL CPQSink::SetConnection(REFCLSID rclsid, REFIID callid)
{
	HRESULT hResult = S_OK;
	IConnectionPointContainer* pContainer = NULL; 
	
	//Create the link to server by callback interface in order to receive event
	hResult = ::CoCreateInstance(rclsid, NULL, CLSCTX_LOCAL_SERVER,
		                         IID_IConnectionPointContainer,
								 (LPVOID*)&pContainer);
	
	if(hResult != S_OK || !pContainer)
		return FALSE;
	
	if(SUCCEEDED(pContainer->FindConnectionPoint(callid, &m_pConnectionPoint)))
	{
		//Register the callback
		hResult = m_pConnectionPoint->Advise((IUnknown*)m_ICallBack, &m_dwCookie);
		if (FAILED(hResult))
		{
			return FALSE;
		}
		//Release the connection point container
		pContainer->Release();
		if(hResult == S_OK)
			return TRUE;
		else
			return FALSE;
		
	}
	
	pContainer->Release();	
	return FALSE;
}


BOOL CPQSink::ReleaseConnection()
{
	if(m_pConnectionPoint)
	{
		//Release the link
		m_pConnectionPoint->Unadvise(m_dwCookie);
		m_pConnectionPoint->Release();
		m_pConnectionPoint = NULL;

		return TRUE;
	}else
		return FALSE;
}

STDMETHODIMP CPQSink::GetTypeInfoCount(UINT *pctinfo)
{
	return S_OK;
}


STDMETHODIMP CPQSink::GetTypeInfo(UINT iTInfo,LCID lcid,ITypeInfo** ppTInfo)
{
	return S_OK;
}
STDMETHODIMP CPQSink::GetIDsOfNames(REFIID riid,LPOLESTR* rgszNames, UINT cNames,LCID lcid,DISPID __RPC_FAR *rgDispId)
{
	return S_OK;
}
STDMETHODIMP CPQSink::Invoke( 
						DISPID dispIdMember,
						REFIID riid,
						LCID lcid,
						WORD wFlags,
						DISPPARAMS *pDispParams,
						VARIANT *pVarResult,
						EXCEPINFO *pExcepInfo,
						UINT  *puArgErr)
{
	// ֻ��Ҫʵ��������㹻��
	switch(dispIdMember)	// ���ݲ�ͬ��dispID,��ɲ�ͬ�Ļص�����
	{
	case 1:
		// ������ܽ��յ� COM �������¼���
		{
			BSTR bsJobUID = pDispParams->rgvarg[1].bstrVal;
			PQ_EPrintJobStatusChange operation = (PQ_EPrintJobStatusChange)pDispParams->rgvarg[0].intVal;
			StateChangeNotify(bsJobUID, operation);
		}
		break;
	case 2:
		// �¼��Ĵ��� dispID ��ʵ���� IDL �ļ��е����ӵ㺯����id(n)�ĺ���
		{
			BSTR bsJobUID = pDispParams->rgvarg[1].bstrVal;
			BSTR errorMsg = pDispParams->rgvarg[0].bstrVal;
			ErrorOutput(bsJobUID, errorMsg);
		}
		break;
	default:
		break;
	}

	return S_OK;
}

STDMETHODIMP CPQSink::StateChangeNotify(BSTR jobUID, PQ_EPrintJobStatusChange operation)
{

	if (NULL != m_pFCPartner)
	{
		CString strJobUID = CBSTROpt::BSTRToCString(jobUID);
		m_pFCPartner->PQStateChangeNotify(strJobUID, operation);
	}

	return S_OK;
}

STDMETHODIMP CPQSink::ErrorOutput(BSTR jobUID, BSTR errorMsg)
{
	CString strJobUID = jobUID;
	CString strErrMsg = errorMsg;

	CString strTrace;
	strTrace.Format(_T("Error: %s, %s"), strJobUID, strErrMsg);
	PRINTTRACE_ERROR(strTrace)

	return S_OK;
}

void CPQSink::Attch(CFCPartner* pFCP)
{
	m_pFCPartner = pFCP;
}

void CPQSink::Detach()
{
	m_pFCPartner = NULL;
}
