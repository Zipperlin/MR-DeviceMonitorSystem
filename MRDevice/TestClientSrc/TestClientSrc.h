// TestClientSrc.h : main header file for the TESTCLIENTSRC application
//

#if !defined(AFX_TESTCLIENTSRC_H__556D8CFC_DEEE_4B0D_8165_DE42A81B83DA__INCLUDED_)
#define AFX_TESTCLIENTSRC_H__556D8CFC_DEEE_4B0D_8165_DE42A81B83DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestClientSrcApp:
// See TestClientSrc.cpp for the implementation of this class
//

class CTestClientSrcApp : public CWinApp
{
public:
	CTestClientSrcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestClientSrcApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestClientSrcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCLIENTSRC_H__556D8CFC_DEEE_4B0D_8165_DE42A81B83DA__INCLUDED_)
