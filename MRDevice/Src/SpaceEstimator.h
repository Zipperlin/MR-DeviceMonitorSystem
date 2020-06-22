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

	//<< 估计转换所需要的磁盘空间
	static __int64 GetConvertNeededSpaceInBytes(DWORD dwImageCount, BOOL bRaw, BOOL bProc);

	//<< 估计刻录光盘占用空间
	static __int64 GetBurnContentSizeInBytes(DWORD dwImageCount, BOOL bBMP, BOOL bJPEG, __int64& i64Additional);

	//<< 估计刻录任务需要的磁盘空间（包括图像转换和刻录映像文件系统的创建）
	static __int64 GetBurnNeededSpaceInBytes(DWORD dwImageCount, BOOL bBMP, BOOL bJPEG, __int64& i64Additional);

	//<< 刻录任务是否可进行，磁盘空间是否足够
	static BOOL IsBurnJobApplicable(DWORD dwImageCount, BOOL bBMP, BOOL bJPEG, __int64& i64Additional);

	//<< 发送任务是否可进行，磁盘空间是否足够
	static BOOL IsSendJobApplicable(DWORD dwImageCount, BOOL bRaw, BOOL bProc);

	//<< _获得磁盘剩余空间
	static __int64 GetHardDiskFreeSpace(LPCTSTR szRoot);
};

#endif // !defined(AFX_SPACEESTIMATOR_H__11B8DB0E_02EA_48C7_A60D_448DDBA1E4D4__INCLUDED_)
