/* Time: <@(#)DBSink.cpp   2009-3-5 - 10:36:07   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DBSink.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Sink class to recieve DB events
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:36:07		FanZF	Creation
 *
 *********************************************************************
 */

// DBSink.cpp: implementation of the CDBSink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DBSink.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "DBController.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBSink::CDBSink()
{
	m_dwCookie = 0;
	m_ICallBack = (IUnknown*)this;
	m_pConnectionPoint = NULL;

}

CDBSink::~CDBSink()
{

}


ULONG CDBSink::AddRef()
{
	return 1;
}

ULONG CDBSink::Release()
{
	return 0;
}

HRESULT CDBSink::QueryInterface(REFIID riid, void** ppv)
{
	//Return the interface for callback
	if(riid == IID_IUnknown)
	{
		*ppv = (IGeneralEvent*)this;
	}
	else if(riid == IID_IGeneralEvent)
	{
		*ppv = (IGeneralEvent*)this;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	return S_OK;
}

BOOL CDBSink::SetConnection(REFCLSID rclsid, REFIID callid)
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

BOOL CDBSink::ReleaseConnection()
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

STDMETHODIMP CDBSink::ReportStartupResult(STARTUPRESULT enumResult)
{
	return S_OK;
}

STDMETHODIMP CDBSink::ReportWorkState(WORKSTATE enumState)
{
	CDBController::GetInstance()->SetDBWorkState(enumState);
	return S_OK;
}

STDMETHODIMP CDBSink::ReportError(INT iError)
{
	return S_OK;
}
