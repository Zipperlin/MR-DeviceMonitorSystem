/* Time: <@(#)UserGuidanceOpt.cpp   2009-3-5 - 10:52:44   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : UserGuidanceOpt.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The operation for UserGuidance
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:52:44		FanZF	Creation
 *
 *********************************************************************
 */

// UserGuidanceOpt.cpp: implementation of the CUserGuidanceOpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UserGuidanceOpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CUserGuidanceOpt* CUserGuidanceOpt::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserGuidanceOpt::CUserGuidanceOpt()
{
	m_hResourceInstance = NULL;
}

CUserGuidanceOpt::~CUserGuidanceOpt()
{

}

CUserGuidanceOpt* CUserGuidanceOpt::GetInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new CUserGuidanceOpt;
	}

	return m_pInstance;
}

void CUserGuidanceOpt::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

BOOL CUserGuidanceOpt::Init()
{

	PRINTTRACE_ENTER_FUNCTION

	BOOL bRet = TRUE;
	TCHAR szBuffer[MAX_PATH] = {0};
	CString strPath;
	CString strTrace;

	DWORD dwRet = GetModuleFileName(NULL, szBuffer, MAX_PATH);
	if (0 != dwRet)
	{
		wchar_t* p = wcsrchr(szBuffer, _T('\\'));
		if (NULL != p)
		{
			*p = _T('\0');
			strPath = szBuffer;
			strPath += USERGUIDANCE_DLL_PATH;
		}
		else
		{
			strTrace.Format(_T("NULL == wcsrchr(szBuffer, _T('\\')), szBuffer=%s"), szBuffer);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
	}
	else
	{
		strTrace.Format(_T("dwRet = GetModuleFileName(), dwRet=%d"), dwRet);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
	
	m_hResourceInstance = LoadLibrary(strPath);
	strTrace.Format(_T("%d == LoadLibrary(): %s"), m_hResourceInstance, strPath);
	if (NULL != m_hResourceInstance)
	{
		PRINTTRACE_INFO(strTrace)
		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
}


BOOL CUserGuidanceOpt::UnInit()
{
	if (m_hResourceInstance)
	{
		FreeLibrary(m_hResourceInstance);
		m_hResourceInstance = NULL;
	}

	return TRUE;
}

LPCTSTR CUserGuidanceOpt::GetString(UINT iUGID)
{
	TCHAR tcDisplayUserGuidanceInfo[255] = {0};

	if (NULL != m_hResourceInstance)
	{
		int iRet = ::LoadString(m_hResourceInstance, iUGID, tcDisplayUserGuidanceInfo, sizeof(tcDisplayUserGuidanceInfo));
		if (0 != iRet)
		{
			m_strUG	 = tcDisplayUserGuidanceInfo;
		}
		else
		{
			m_strUG = _T("");
		}
	}
	else
	{
		m_strUG = _T("");
	}

	return (LPCTSTR)m_strUG;
}
