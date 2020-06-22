/* Time: <@(#)FireMsgQueueMng.h   2009-3-5 - 10:44:21   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : FireMsgQueueMng.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Management for fire message queue
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:44:21		FanZF	Creation
 *
 *********************************************************************
 */

// FireMsgQueueMng.h: interface for the CFireMsgQueueMng class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREMSGQUEUEMNG_H__067DC93F_CA08_41F9_BD53_8A63380ECC4A__INCLUDED_)
#define AFX_FIREMSGQUEUEMNG_H__067DC93F_CA08_41F9_BD53_8A63380ECC4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FireMsgQueue.h"
#include "PAATL.h"

class CPA;

class CFireMsgQueueMng  
{
public:
	virtual ~CFireMsgQueueMng();
	
	static CFireMsgQueueMng* GetInstance();
	void ReleaseInstance();

	BOOL Init(CPA* pPA);
	BOOL UnInit();

	BOOL PushMsg(FireMsgNode& msg);
	BOOL HandleMsg();

private:
	CFireMsgQueueMng();

	static CFireMsgQueueMng*	m_pInstance;

	CFireMsgQueue				m_MsgQueue;
	CPA*						m_pCPA;
	
	BOOL						m_bExist;
	HANDLE						m_hThread;

	HANDLE						m_hEvent;
	CCriticalSection			m_CSLock;

};

#endif // !defined(AFX_FIREMSGQUEUEMNG_H__067DC93F_CA08_41F9_BD53_8A63380ECC4A__INCLUDED_)
