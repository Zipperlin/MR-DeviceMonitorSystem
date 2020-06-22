/* Time: <@(#)SpaceEstimator.cpp   2009-3-5 - 10:51:33   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : SpaceEstimator.cpp
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
 *	1	2009-3-5 - 10:51:33		FanZF	Creation
 *
 *********************************************************************
 */

// SpaceEstimator.cpp: implementation of the CSpaceEstimator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpaceEstimator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpaceEstimator::CSpaceEstimator()
{

}

CSpaceEstimator::~CSpaceEstimator()
{

}

//<< 估计转换所需要的磁盘空间
__int64 CSpaceEstimator::GetConvertNeededSpaceInBytes(DWORD dwImageCount, BOOL bRaw, BOOL bProc)
{
	int nTime = 0;
	if (bRaw) ++nTime;
	if (bProc) ++nTime;


	__int64 i64Size = dwImageCount * nTime * 20; //20 表示单幅图像的大小(M), 含PS文件大小 DICOM_RAW_IMAGE_BYTE;

	return i64Size;
}

//<< 估计刻录光盘占用空间
__int64 CSpaceEstimator::GetBurnContentSizeInBytes(DWORD dwImageCount, BOOL bBMP, BOOL bJPEG, __int64& i64Additional)
{
	__int64 i64Size = 0;

	//<< RAW Dcm and Processed Dcm
	i64Size = GetConvertNeededSpaceInBytes(dwImageCount, TRUE, TRUE);

	//<< BMP
	if (bBMP)
		i64Size += dwImageCount * BURN_BMP_SIZE;

	//<< JPEG
	if (bJPEG)
		i64Size += dwImageCount * BURN_JPEG_SIZE;

	//<< Additional 
	i64Size += i64Additional; //单位:M

	return i64Size;
}

//<< 估计刻录任务需要的磁盘空间（包括图像转换和刻录映像文件系统的创建）
__int64 CSpaceEstimator::GetBurnNeededSpaceInBytes(DWORD dwImageCount, BOOL bBMP, BOOL bJPEG, __int64& i64Additional)
{
	//<< 图像转换无需考虑Additional，刻录映像文件系统的创建需考虑Additioanl部分
	__int64 i64Zero = 0;
	__int64 i64Size = GetBurnContentSizeInBytes(dwImageCount, bBMP, bJPEG, i64Zero) +
					GetBurnContentSizeInBytes(dwImageCount, bBMP, bJPEG, i64Additional);

	return i64Size;
}


//<< 刻录任务是否可进行，磁盘空间是否足够
BOOL CSpaceEstimator::IsBurnJobApplicable(DWORD dwImageCount, BOOL bBMP, BOOL bJPEG, __int64& i64Additional)
{
	__int64 i64HardDiscSafeSpace = __int64(GetHardDiskFreeSpace(DICOM_IMAGE_STORE_PATH) * HARDDISK_FREE_SPACE_SAFETY_COEFFICIENT);

	if (GetBurnNeededSpaceInBytes(dwImageCount, bBMP, bJPEG, i64Additional) > i64HardDiscSafeSpace)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


//<< 发送任务是否可进行，磁盘空间是否足够
BOOL CSpaceEstimator::IsSendJobApplicable(DWORD dwImageCount, BOOL bRaw, BOOL bProc)
{
	__int64 i64HardDiscSafeSpace = __int64(GetHardDiskFreeSpace(DICOM_IMAGE_STORE_PATH) * HARDDISK_FREE_SPACE_SAFETY_COEFFICIENT);

	if (GetConvertNeededSpaceInBytes(dwImageCount, bRaw, bProc) > i64HardDiscSafeSpace)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


//<< _获得磁盘剩余空间
__int64 CSpaceEstimator::GetHardDiskFreeSpace(LPCTSTR szRoot)
{
	__int64 i64DiskFreeSpace = 0;
	if (!GetDiskFreeSpaceEx(szRoot, NULL, NULL, (PULARGE_INTEGER)&i64DiskFreeSpace))
	{
		return 0;
	}
	else
	{
		return i64DiskFreeSpace;
	}
}
