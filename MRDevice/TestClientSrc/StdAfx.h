// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__08447156_AC78_48F8_A116_5B14676AD6E5__INCLUDED_)
#define AFX_STDAFX_H__08447156_AC78_48F8_A116_5B14676AD6E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define _WIN32_WINNT 0x0400
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include "PALib_i.h"
// #include "PALibExt_i.h"
#include "PATestClientLibExt_i.h"
#include "comutil.h"

#include "BSTROpt.h"
#include "ReportCtrl.h"
#include "DcmProc.h"


typedef enum _JobMode
{
	enumJobMode_Current			= 0,
	enumJobMode_History			= 1,
}JobMode;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__08447156_AC78_48F8_A116_5B14676AD6E5__INCLUDED_)
