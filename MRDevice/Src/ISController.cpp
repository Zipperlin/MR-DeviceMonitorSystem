/* Time: <@(#)ISController.cpp   2009-3-5 - 10:35:32   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : ISController.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Communication class with IS
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:35:32		FanZF	Creation
 *
 *********************************************************************
 */

// ISController.cpp: implementation of the CISController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ISController.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CISController* CISController::m_pInstance = NULL;

CISController::CISController()
{
	m_pInstance = NULL;
	m_pISExp = NULL;
	
}

CISController::~CISController()
{

}

CISController* CISController::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CISController;
	}

	return m_pInstance;
}

void CISController::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

BOOL CISController::Init()
{
	BOOL bRet = TRUE;


	if(NULL == m_pISExp)
	{		
		if(CoCreateInstance(CLSID_ISATL,
							NULL, 
							CLSCTX_LOCAL_SERVER,
							IID_ISExp,
							(LPVOID*)&m_pISExp) != S_OK)
		{
			PRINTTRACE_ERROR("ERROR: CoCreateInstance m_pISDiskOperation");
			bRet = FALSE ;
		}
	}	

	
	return bRet;

}

BOOL CISController::UnInit()
{
	if (m_pISExp)
	{
		m_pISExp->Release();
		m_pISExp = NULL;
	}

	return TRUE;
}

BOOL CISController::GetDiskFreeImageNum(long* plNum)
{
	HRESULT hr = m_pISExp->GetDiskCapacity(plNum);
	if (S_OK == hr)
	{
		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR("m_pISFSDisk->GetDiskCapacity(plNum)")
		return FALSE;
	}
}



