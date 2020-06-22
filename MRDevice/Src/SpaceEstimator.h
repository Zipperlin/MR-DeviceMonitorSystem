/* Time: <@(#)SpaceEstimator.h   2009-3-5 - 10:50:58   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : SpaceEstimator.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Space estimation for jobs
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:50:58		FanZF	Creation
 *
 *********************************************************************
 */

// SpaceEstimator.h: interface for the CSpaceEstimator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPACEESTIMATOR_H__11B8DB0E_02EA_48C7_A60D_448DDBA1E4D4__INCLUDED_)
#define AFX_SPACEESTIMATOR_H__11B8DB0E_02EA_48C7_A60D_448DDBA1E4D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSpaceEstimator  
{
public:
	CSpaceEstimator();
	virtual ~CSpaceEstimator();

	//<< ����ת������Ҫ�Ĵ��̿ռ�
	static __int64 GetConvertNeededSpaceInBytes(DWORD dwImageCount, BOOL bRaw, BOOL bProc);

	//<< ���ƿ�¼����ռ�ÿռ�
	static __int64 GetBurnContentSizeInBytes(DWORD dwImageCount, BOOL bBMP, BOOL bJPEG, __int64& i64Additional);

	//<< ���ƿ�¼������Ҫ�Ĵ��̿ռ䣨����ͼ��ת���Ϳ�¼ӳ���ļ�ϵͳ�Ĵ�����
	static __int64 GetBurnNeededSpaceInBytes(DWORD dwImageCount, BOOL bBMP, BOOL bJPEG, __int64& i64Additional);

	//<< ��¼�����Ƿ�ɽ��У����̿ռ��Ƿ��㹻
	static BOOL IsBurnJobApplicable(DWORD dwImageCount, BOOL bBMP, BOOL bJPEG, __int64& i64Additional);

	//<< ���������Ƿ�ɽ��У����̿ռ��Ƿ��㹻
	static BOOL IsSendJobApplicable(DWORD dwImageCount, BOOL bRaw, BOOL bProc);

	//<< _��ô���ʣ��ռ�
	static __int64 GetHardDiskFreeSpace(LPCTSTR szRoot);
};

#endif // !defined(AFX_SPACEESTIMATOR_H__11B8DB0E_02EA_48C7_A60D_448DDBA1E4D4__INCLUDED_)
