// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__57DBBDA8_3A45_4179_8F7D_736AF0CAA8F4__INCLUDED_)
#define AFX_STDAFX_H__57DBBDA8_3A45_4179_8F7D_736AF0CAA8F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_FREE_THREADED
#include "afxtempl.h"
#include <afxmt.h>
#include <atlbase.h>

#include <afxwin.h>
#include <afxext.h>
#include <afxdisp.h>
#include "atlconv.h"
#include <afxdtctl.h>	 // MFC support for Internet Explorer 4


//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CExeModule : public CComModule
{
public:
	LONG Unlock();
	DWORD dwThreadID;
	HANDLE hEventShutdown;
	void MonitorShutdown();
	bool StartMonitor();
	bool bActivity;
};
extern CExeModule _Module;
#include <atlcom.h>


//<< for access database
#include "ado.h"
#include <afxdb.h>			// MFC ODBC database classes
#include "DBDatabaseBasisOpt.h" //Database operation basis class
#include "DBDatabaseOpt.h" //Database operation class


#include "PALibExt_i.h"

#include "DcmProc.h"

#include "comutil.h"

#include "ASBasis.h"
#include "GenXml.h"

#include "PALib_i.h"

#include "ConstDefine.h"
#include "OutputStrDefine.h"
#include "PAStructDefine.h"
#include "PAMsgDefine.h"


#include "BSTROpt.h"
#include "Buffer.h"
#include "ErrorCodeDefine.h"
#include "ErrorCodeInfoDefine.h"
#include "comdef.h"
#include "DcmPartner.h"
#include "FilePicker.h"
#include "UserGuidanceRes.h"
#include "SpaceEstimator.h"
#include "PAJob.h"

#include "WorklistStructDef.h"


/*************************UserGuidance structure for Notify*******/

typedef struct _TagUGNotifyStruct
{
	LONG iMessageID;
	USER_GUIDANCE_TYPE enumUGType;
	USER_GUIDANCE_PRIORITY enumGUIPriority;
	BOOL bActive;
}UGNotifyStruct;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__57DBBDA8_3A45_4179_8F7D_736AF0CAA8F4__INCLUDED)
