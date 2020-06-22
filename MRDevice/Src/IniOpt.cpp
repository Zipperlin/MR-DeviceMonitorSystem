/* Time: <@(#)IniOpt.cpp   2009-3-5 - 10:46:19   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : IniOpt.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Operation class for .ini file
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:46:19		FanZF	Creation
 *
 *********************************************************************
 */

// IniOpt.cpp: implementation of the CIniOpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniOpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniOpt::CIniOpt()
{
	m_strIniFile = _T("");
}

CIniOpt::~CIniOpt()
{

}

void CIniOpt::SetIniFile(LPCTSTR szIniFile)
{
	m_strIniFile = szIniFile;
}

INT CIniOpt::GetIntFromINI(LPCTSTR szApp, LPCTSTR szKey, INT iDefault)
{
	int iDigital = 0;
	iDigital = GetPrivateProfileInt(szApp,
									szKey,
									iDefault,
									m_strIniFile);
	return iDigital;
}

CString CIniOpt::GetStrFromINI(LPCTSTR szApp, LPCTSTR szKey, LPCTSTR szDefault)
{
	TCHAR szStrBuffer[MAX_PATH] = {0};

	GetPrivateProfileString(szApp,
							szKey,
							szDefault,
							szStrBuffer,
							sizeof(szStrBuffer),
							m_strIniFile);

	return (CString)szStrBuffer;
}

BOOL CIniOpt::IsIniFileExist()
{
	if (m_strIniFile.IsEmpty())
	{
		return FALSE;
	}
	
	WIN32_FIND_DATA fd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	hFind = FindFirstFile(m_strIniFile, &fd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return FALSE;
	}
	else
	{
		FindClose(hFind);
		return TRUE;
	}
}

BOOL CIniOpt::DeleteSectionFromINI(LPCTSTR szApp)
{
	if (NULL == szApp)
	{
		return FALSE;
	}

	if (WritePrivateProfileString(szApp,
								NULL,
								NULL,
								m_strIniFile))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CIniOpt::WriteKeyToINI(LPCTSTR szApp, LPCTSTR szKey, LPCTSTR szValue)
{
	if (NULL == szApp || NULL == szKey || NULL == szValue)
	{
		return FALSE;
	}

	if (WritePrivateProfileString(szApp,
								szKey,
								szValue,
								m_strIniFile))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}