/* Time: <@(#)PQSink.h   2009-3-5 - 10:49:45   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : PQSink.h
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
 *	1	2009-3-5 - 10:49:45		FanZF	Creation
 *
 *********************************************************************
 */

// PQSink.h: interface for the CPQSink class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__PQSINK_H__)
#define __PQSINK_H__

#include "PrintQueueManager_i.h"
class CFCPartner;


class CPQSink : public _IPrintQueueChangeEvents
{
public:
	CPQSink();
	virtual ~CPQSink();
	DWORD				m_dwCookie;			//Record the cookie of link
	IUnknown*			m_ICallBack;		//Define the interface for callback
	IConnectionPoint*	m_pConnectionPoint;	//Record the connection point for link

	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall QueryInterface(REFIID iid, void** ppv);

	//Create a link to the server
	BOOL SetConnection(REFCLSID rclsid, REFIID callid);	
	//Release the link to the server
	BOOL ReleaseConnection();

	STDMETHOD(GetTypeInfoCount)(UINT *pctinfo);
	STDMETHOD(GetTypeInfo)(UINT iTInfo,LCID lcid,ITypeInfo** ppTInfo);
	STDMETHOD(GetIDsOfNames)(REFIID riid,LPOLESTR* rgszNames, UINT cNames,LCID lcid,DISPID __RPC_FAR *rgDispId);
	STDMETHOD(Invoke)( 
						DISPID dispIdMember,
						REFIID riid,
						LCID lcid,
						WORD wFlags,
						DISPPARAMS *pDispParams,
						VARIANT *pVarResult,
						EXCEPINFO *pExcepInfo,
						UINT  *puArgErr);


	// IPAGeneralEvent
	STDMETHOD(StateChangeNotify)(BSTR jobUID, PQ_EPrintJobStatusChange operation);
	STDMETHOD(ErrorOutput)(BSTR jobUID, BSTR errorMsg);


	void Attch(CFCPartner* pFCP);
	void Detach();

private:
	CFCPartner*		m_pFCPartner;
};

#endif // !defined(__PQSINK_H__)
