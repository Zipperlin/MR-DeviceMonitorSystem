/* Time: <@(#)FireMsgQueue.cpp   2009-3-5 - 10:44:10   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : FireMsgQueue.cpp
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
 *	1	2009-3-5 - 10:44:10		FanZF	Creation
 *
 *********************************************************************
 */

// FireMsgQueue.cpp: implementation of the CFireMsgQueue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FireMsgQueue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFireMsgQueue::CFireMsgQueue()
{
	//Initialize the member
	m_pHeadNode		= NULL;
	m_pCurrentNode	= NULL;
	m_CurNodeNum	= 0;	
	
}

CFireMsgQueue::~CFireMsgQueue()
{
	FireMsgNode *Temp, *Current = m_pHeadNode;

	//Delete the list and release the memory
	while(Current)
	{
		Temp = Current;
		Current = Current->pNextNode;

		delete Temp;
	}
}

BOOL CFireMsgQueue::PushPAMsg(FireMsgNode& msg)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	if(m_CurNodeNum < QUE_LEN_MAX)
	{
		FireMsgNode *NewMsgNode = new FireMsgNode;
//		NewMsgNode->msg.uiMessage = msg.uiMessage;
//		NewMsgNode->msg.lParam = msg.lParam;
//		NewMsgNode->msg.wParam = msg.wParam;
		memcpy(NewMsgNode, &msg, sizeof(FireMsgNode));
		NewMsgNode->pNextNode = NULL;
		
		if(m_pCurrentNode)
		{
			//Set it to the end of queue
			m_pCurrentNode->pNextNode = NewMsgNode;
			m_pCurrentNode = NewMsgNode;
		}else{ 
			//If no member and set the head of queue
			m_pHeadNode = NewMsgNode;
			m_pCurrentNode = NewMsgNode;
		}
		m_CurNodeNum++;
		sLock.Unlock();
		return TRUE;

	}else
	{
		sLock.Unlock();
		return FALSE;
	}	
}

BOOL CFireMsgQueue::PullPAMsg(FireMsgNode& msg)
{
	FireMsgNode* Temp;
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	if(m_pHeadNode)
	{
		//Get a collimator from the head of queue
//		msg = m_pHeadNode->msg;
		memcpy(&msg, &(m_pHeadNode->msg), sizeof(FireMsgNode));
		Temp = m_pHeadNode;
		m_pHeadNode = m_pHeadNode->pNextNode;
		if(m_pHeadNode == NULL)
			m_pCurrentNode = NULL;
		
		//Delete it and reduce the number of member
		delete Temp;
		m_CurNodeNum--;	
		sLock.Unlock();
		return TRUE;

	}else
	{
		sLock.Unlock();
		return FALSE;		
	}
}


BOOL CFireMsgQueue::ClearQueque()
{
	FireMsgNode *Temp, *Current = m_pHeadNode;

	//Delete the list and release the memory
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	while(Current != NULL)
	{
		Temp = Current->pNextNode;
        delete Current;
		Current = Temp;
	}
	m_pHeadNode = NULL ;
	m_pCurrentNode = NULL ;
	m_CurNodeNum = 0 ;
	sLock.Unlock();
	return TRUE;
}

SHORT CFireMsgQueue::GetMsgNumber()
{

	return m_CurNodeNum;

}