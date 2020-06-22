// BSTROpt.h: interface for the CBSTROpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSTROPT_H__3CD8A020_04E7_4DDA_876C_38286B361F1D__INCLUDED_)
#define AFX_BSTROPT_H__3CD8A020_04E7_4DDA_876C_38286B361F1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "comutil.h"

class CBSTROpt  
{
public:
	CBSTROpt();
	virtual ~CBSTROpt();

	static CString BSTRToCString(BSTR& bs);
	static void FreeBSTR(BSTR& bs);

};

#endif // !defined(AFX_BSTROPT_H__3CD8A020_04E7_4DDA_876C_38286B361F1D__INCLUDED_)
