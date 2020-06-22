/* Time: <@(#)DBSink.h   2009-3-5 - 10:35:42   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DBSink.h
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
 *	1	2009-3-5 - 10:35:42		FanZF	Creation
 *
 *********************************************************************
 */

// DBSink.h: interface for the CDBSink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBSINK_H__A3FB67C8_A012_4072_9A36_B8F53C4D3C2D__INCLUDED_)
#define AFX_DBSINK_H__A3FB67C8_A012_4072_9A36_B8F53C4D3C2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDBSink : public IGeneralEvent
{
public:
	CDBSink();
	virtual ~CDBSink();

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

	STDMETHOD(ReportStartupResult)(STARTUPRESULT enumResult);
	STDMETHOD(ReportWorkState)(WORKSTATE enumState);
	STDMETHOD(ReportError)(INT iError);

};

#endif // !defined(AFX_DBSINK_H__A3FB67C8_A012_4072_9A36_B8F53C4D3C2D__INCLUDED_)
