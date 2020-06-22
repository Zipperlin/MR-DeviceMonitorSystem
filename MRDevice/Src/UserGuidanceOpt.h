/* Time: <@(#)UserGuidanceOpt.h   2009-3-5 - 10:52:26   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : UserGuidanceOpt.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The operation for UserGuidance
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:52:26		FanZF	Creation
 *
 *********************************************************************
 */

// UserGuidanceOpt.h: interface for the CUserGuidanceOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERGUIDANCEOPT_H__BDF3F31A_69BB_43AD_99DC_3D2A1D3B8FE8__INCLUDED_)
#define AFX_USERGUIDANCEOPT_H__BDF3F31A_69BB_43AD_99DC_3D2A1D3B8FE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUserGuidanceOpt  
{
public:
	CUserGuidanceOpt();
	virtual ~CUserGuidanceOpt();

	static CUserGuidanceOpt* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	BOOL UnInit();

	LPCTSTR GetString(UINT iUGID);


private:

	static CUserGuidanceOpt*		m_pInstance;

	HINSTANCE						m_hResourceInstance;

	CString							m_strUG;

};

#endif // !defined(AFX_USERGUIDANCEOPT_H__BDF3F31A_69BB_43AD_99DC_3D2A1D3B8FE8__INCLUDED_)
