/* Time: <@(#)FireMsgQueue.h   2009-3-5 - 10:43:52   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : FireMsgQueue.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Queue for fire messages
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:43:52		FanZF	Creation
 *
 *********************************************************************
 */

// FireMsgQueue.h: interface for the CFireMsgQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREMSGQUEUE_H__D57874FE_881C_4992_99F8_9E1614936039__INCLUDED_)
#define AFX_FIREMSGQUEUE_H__D57874FE_881C_4992_99F8_9E1614936039__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "PALib_i.h"
#define QUE_LEN_MAX		1024

typedef struct _FireMsg
{
	UINT uiMessage;
	LPARAM lParam;
	WPARAM wParam;
} FireMsg;

typedef struct _FireMsgNode
{
	FireMsg msg;
	_FireMsgNode* pNextNode;
}FireMsgNode;


class CFireMsgQueue  
{
public:
	CFireMsgQueue();
	virtual ~CFireMsgQueue();

public:
	//Push a PA message to BeamLimitation
	BOOL PushPAMsg(FireMsgNode& msg);

	//Pull a PA message from the queue
	BOOL PullPAMsg(FireMsgNode& msg);

	//Destroy the queue and clear all the command event
	BOOL ClearQueque();

	//Get the number of message in queue
	SHORT GetMsgNumber();
private:
	CCriticalSection	m_CSLock;
	FireMsgNode*		m_pHeadNode;
	FireMsgNode*		m_pCurrentNode;
	SHORT				m_CurNodeNum;
};


#endif // !defined(AFX_FIREMSGQUEUE_H__D57874FE_881C_4992_99F8_9E1614936039__INCLUDED_)
