// LanguageIniOpt.h: interface for the CLanguageIniOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGEINIOPT_H__E4BC314B_178E_4257_9B8C_C5541DB4D20F__INCLUDED_)
#define AFX_LANGUAGEINIOPT_H__E4BC314B_178E_4257_9B8C_C5541DB4D20F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IniOpt.h"

class CLanguageIniOpt : public CIniOpt  
{
private:
	static CLanguageIniOpt* m_pInstance;
	CLanguageIniOpt();
public:
	BOOL UnInit();
	BOOL Init();
	void ReleaseInstance();
	static CLanguageIniOpt* GetInstance();
	virtual ~CLanguageIniOpt();

};

#endif // !defined(AFX_LANGUAGEINIOPT_H__E4BC314B_178E_4257_9B8C_C5541DB4D20F__INCLUDED_)
