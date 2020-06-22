// BSTROpt.cpp: implementation of the CBSTROpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BSTROpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBSTROpt::CBSTROpt()
{

}

CBSTROpt::~CBSTROpt()
{

}


CString CBSTROpt::BSTRToCString(BSTR& bs)
{
	char* p = _com_util::ConvertBSTRToString(bs);
	CString str = p;

	delete[] p;

	return str;
}

void CBSTROpt::FreeBSTR(BSTR& bs)
{
	::SysFreeString(bs);
}
