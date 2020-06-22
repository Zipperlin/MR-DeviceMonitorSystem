/* Time: <@(#)ISController.h   2009-3-5 - 10:35:24   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : ISController.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Communication class with IS
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:35:24		FanZF	Creation
 *
 *********************************************************************
 */

// ISController.h: interface for the CISController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISCONTROLLER_H__A7106371_615D_4510_8EC3_C830212EA01B__INCLUDED_)
#define AFX_ISCONTROLLER_H__A7106371_615D_4510_8EC3_C830212EA01B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PALibExt_i.h"
// #include "ISSink.h"

class CISController
{
public:
	virtual ~CISController();

	static CISController* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	BOOL UnInit();

	BOOL GetDiskFreeImageNum(long* plNum);



private:
	CISController();
	static CISController*	m_pInstance;
	
	ISExp*					m_pISExp;


};

#endif // !defined(AFX_ISCONTROLLER_H__A7106371_615D_4510_8EC3_C830212EA01B__INCLUDED_)
