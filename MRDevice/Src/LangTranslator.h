/* Time: <@(#)LangTranslator.h   2009-3-5 - 10:47:51   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : LangTranslator.h
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
 *	1	2009-3-5 - 10:47:51		FanZF	Creation
 *
 *********************************************************************
 */

// LangTranslator.h: interface for the CLangTranslator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGTRANSLATOR_H__9194518E_42B5_46D7_8AA2_847FD32028C2__INCLUDED_)
#define AFX_LANGTRANSLATOR_H__9194518E_42B5_46D7_8AA2_847FD32028C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLangTranslator  
{
public:
	virtual ~CLangTranslator();

	static CLangTranslator* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	BOOL UnInit();

	LPCTSTR TranslateText(LPCTSTR szText);
	BOOL	IsChineseLang();

private:
	CLangTranslator();


	static CLangTranslator*		m_pInstance;
	
	CLocale*					m_pLocal;
	CString						m_strText;

	BOOL						m_bChineseLang;

};

#endif // !defined(AFX_LANGTRANSLATOR_H__9194518E_42B5_46D7_8AA2_847FD32028C2__INCLUDED_)
