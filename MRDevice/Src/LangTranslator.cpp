/* Time: <@(#)LangTranslator.cpp   2009-3-5 - 10:48:11   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : LangTranslator.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Translation for multi-language version
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:48:11		FanZF	Creation
 *
 *********************************************************************
 */

// LangTranslator.cpp: implementation of the CLangTranslator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LangTranslator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CLangTranslator* CLangTranslator::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLangTranslator::CLangTranslator()
{
	m_pLocal = NULL;
	m_bChineseLang = FALSE;
}

CLangTranslator::~CLangTranslator()
{

}

CLangTranslator* CLangTranslator::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CLangTranslator;
	}

	return m_pInstance;
}

void CLangTranslator::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

BOOL CLangTranslator::Init()
{
	CString strTrace;

	m_pLocal = CLocale::GetInstance();
	if (NULL == m_pLocal)
	{
		PRINTTRACE_ERROR("m_pLocal = CLocale::GetInstance()")
		return FALSE;
	}

	// Get the P&A path
	TCHAR cCurrentSystemDirectory[MAX_PATH]; 
	GetModuleFileName(NULL, cCurrentSystemDirectory, MAX_PATH);
	CString strApplicationName = cCurrentSystemDirectory;

	CString strApplicationPath = strApplicationName.Left(strApplicationName.ReverseFind('\\'));	//获得不带应用程序文件名的应用程序路径(去掉应用程序文件名)	

	// UIScheme.ini file path
	CString strINIFileName = strApplicationPath + UISCHEME_INI_FILE;

// 	int iValue = GetPrivateProfileIntW(_T("LANGUAGE_TRANSLATE"),
// 								     _T("IsTranslateLanguage"),
// 								     0,
// 								     strINIFileName);

	int iValue = 1;
	if (0 == iValue)
		m_bChineseLang = FALSE;
	else
		m_bChineseLang = TRUE;

	if (m_bChineseLang)
	{
		//<< 中文的话，需要翻译
		// LangFile path
		CString strLangFile = strApplicationPath + SYSTEM_LANG_FILE;

		if (m_pLocal->LoadLanguage(strLangFile))
		{
			strTrace.Format(_T("m_Local->LoadLanguage(strLangFile), strLangFile:%s"), strLangFile);
			PRINTTRACE_INFO(strTrace)
		}
		else
		{
			strTrace.Format(_T("m_Local->LoadLanguage(strLangFile), strLangFile:%s"), strLangFile);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CLangTranslator::UnInit()
{
// 	if (NULL != m_pLocal)
// 	{
// 		m_pLocal->
// 	}

	return TRUE;
}

LPCTSTR CLangTranslator::TranslateText(LPCTSTR szText)
{
	CString strSrc = szText;

	if (NULL == szText)
	{
		m_strText = _T("");
		return (LPCTSTR)m_strText;
	}

	m_strText.Empty();
	if (NULL == m_pLocal)
	{
		m_strText = strSrc;
	}
	else
	{
		m_strText = m_pLocal->TranslateText(strSrc);
	}

	return (LPCTSTR)m_strText;
}

BOOL CLangTranslator::IsChineseLang()
{
	return m_bChineseLang;
}
