/* Time: <@(#)IniOpt.h   2009-3-5 - 10:46:00   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : IniOpt.h
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
 *	1	2009-3-5 - 10:46:00		FanZF	Creation
 *
 *********************************************************************
 */

// IniOpt.h: interface for the CIniOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIOPT_H__934FA1F8_91C2_4829_A345_7448F84F5B60__INCLUDED_)
#define AFX_INIOPT_H__934FA1F8_91C2_4829_A345_7448F84F5B60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniOpt  
{
public:
	CIniOpt();
	virtual ~CIniOpt();

	void SetIniFile(LPCTSTR szIniFile);
	BOOL IsIniFileExist();

	INT GetIntFromINI(LPCTSTR szApp, LPCTSTR szKey, INT iDefault = 0);

	CString GetStrFromINI(LPCTSTR szApp, LPCTSTR szKey, LPCTSTR szDefault = _T(""));

	BOOL DeleteSectionFromINI(LPCTSTR szApp);
	BOOL WriteKeyToINI(LPCTSTR szApp, LPCTSTR szKey, LPCTSTR szValue);

private:

	CString m_strIniFile;

};

#endif // !defined(AFX_INIOPT_H__934FA1F8_91C2_4829_A345_7448F84F5B60__INCLUDED_)
