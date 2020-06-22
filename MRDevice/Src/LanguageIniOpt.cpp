// LanguageIniOpt.cpp: implementation of the CLanguageIniOpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LanguageIniOpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CLanguageIniOpt* CLanguageIniOpt::m_pInstance = NULL;
CLanguageIniOpt::CLanguageIniOpt()
{

}

CLanguageIniOpt::~CLanguageIniOpt()
{

}

CLanguageIniOpt* CLanguageIniOpt::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CLanguageIniOpt;
	}

	return m_pInstance;
}

void CLanguageIniOpt::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

BOOL CLanguageIniOpt::Init()
{
	TCHAR cCurrentSystemDirectory[MAX_PATH]; 
	GetModuleFileName(NULL, cCurrentSystemDirectory, MAX_PATH);
	CString strApplicationName = cCurrentSystemDirectory;

	CString strApplicationPath = strApplicationName.Left(strApplicationName.ReverseFind('\\'));	//获得不带应用程序文件名的应用程序路径(去掉应用程序文件名)	

	//UIScheme.ini
	CString strIniFile = strApplicationPath + UISCHEME_INI_FILE;
	SetIniFile(strIniFile);

	//设置语言
	CString szLanguageFileName = GetStrFromINI(_T("LANGUAGE_SETTING"), _T("CurrentLanguageFileName"));
	CString szLanguageFile = strApplicationPath + _T("\\") + szLanguageFileName;
	CAppUI *pInstance = CAppUI::GetInstance();
	BOOL bResult = pInstance->SetLanguage(szLanguageFile, FALSE);

	return bResult;
}

BOOL CLanguageIniOpt::UnInit()
{
	SetIniFile(_T(""));
	return TRUE;
}
