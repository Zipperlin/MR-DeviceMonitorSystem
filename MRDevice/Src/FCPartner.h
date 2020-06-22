/* Time: <@(#)FCPartner.h   2009-3-5 - 10:42:29   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : FCPartner.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Communication class with FilmComposer
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:42:29		FanZF	Creation
 *
 *********************************************************************
 */

// FCPartner.h: interface for the CFCPartner class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FCPARTNER_H__6C1D8076_AC24_45F0_B71E_D2FE1D3178BA__INCLUDED_)
#define AFX_FCPARTNER_H__6C1D8076_AC24_45F0_B71E_D2FE1D3178BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ConstDefine.h"
// #include "Winsock2.h"
#include "PQSink.h"


class CFCPartner : public NSubject
{
public:
	CFCPartner();
	virtual ~CFCPartner();

	BOOL Init();
	BOOL UnInit();

	BOOL StartUpFilmComposer();
	BOOL ShutDownFilmComposer();

	BOOL GetFCHandle();

// 	BOOL CheckFilmComposerStatus();
	BOOL FCMonitorProc();

	BOOL SendCMDLine(CString& strCMDLine);

	BOOL LoadImage(CString& strImageFullName);
	BOOL LoadImages(vector<CString>* pvtrDICOMImages, BOOL* pJobCancelFlag);

	BOOL SetRowAndCol(UINT uiRow, UINT uiCol);
// 	BOOL SendCMD(char* buf, UINT len);

// 	BOOL ShowProgressBar(BOOL bShow);

	BOOL SaveSession();
	BOOL CancelPrinting();

	BOOL IsFCPrinting();

	void EnableLoadImage();
	void DisableLoadImage();

	void PQStateChangeNotify(LPCTSTR szJobUID, PQ_EPrintJobStatusChange operation);
	
private:
	BOOL SetConnection();
	BOOL Disconnection();

	CString GetFCFullPath();

private:

	CPQSink			m_PQSink;
	IPrintQueue*	m_IPrintQueue;
	
// 	SOCKET	m_socketFCServer;
// 	SOCKET	m_socketFCMonitorServer;
// 	SOCKET	m_socketFCMonitorClient;

	HANDLE	m_FCProcessHandle;
	HANDLE	m_FCMonitorHandle;

	HANDLE	m_hFCMonitorEvent;
	HANDLE	m_hFCLoadImageEvent;
// 	HANDLE	m_hFCSocketOKEvent;

	PROCESS_INFORMATION m_PrintProcessInfo;
	
// 	HANDLE	m_hCheckFCStatusThread;

	BOOL	m_bImagesReachLimitation;

	CString	m_strFCFullPath;

	INT		m_iActivePrintJobCount;
	FilmComposerStatus	m_enumFCStatus;
};

#endif // !defined(AFX_FCPARTNER_H__6C1D8076_AC24_45F0_B71E_D2FE1D3178BA__INCLUDED_)
