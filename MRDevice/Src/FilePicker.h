/* Time: <@(#)FilePicker.h   2009-3-5 - 10:42:59   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : FilePicker.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Directory and file operation
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:42:59		FanZF	Creation
 *
 *********************************************************************
 */

// FilePicker.h: interface for the CFilePicker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEPICKER_H__627980AA_58A9_4341_A87D_8F6B12F9CBAE__INCLUDED_)
#define AFX_FILEPICKER_H__627980AA_58A9_4341_A87D_8F6B12F9CBAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stack>
using namespace std;


class CFilePicker  
{
public:
	CFilePicker();
	CFilePicker(CString& strDir);
	virtual ~CFilePicker();

	void SetDir(CString strDir);
	void Clear();

	CString GetFile();
	BOOL GetFile(CString& strFileName);
	BOOL GetDirOrFile(CString& strDirOrFileName, BOOL& bIsDir);
	BOOL GetDirOrFileEx(CString& strDirOrFileName, BOOL& bIsDir);

	BOOL GetFileCount(UINT* puiFileCount, BOOL bForce = FALSE);
	BOOL GetDirCount(UINT* puiDirCount, BOOL bForce = FALSE);
	BOOL GetTotalSize(__int64* pi64TotalSize, BOOL bForce = FALSE);
private:
	BOOL IsDir(CString& strFileName);

	BOOL GetDirInfo();

	CString			m_strOriginalDir;
	BOOL			m_bIsDir;
	CString			m_strDir;
	HANDLE			m_hFind;
	WIN32_FIND_DATA	m_fd;
	stack<CString>	m_DirStack;
	stack<HANDLE>	m_HandleStack;

	UINT			m_uiFileCount;
	UINT			m_uiDirCount;
	__int64			m_i64TotalSize;

	
	BOOL			m_bGotDirInfo;

};

#endif // !defined(AFX_FILEPICKER_H__627980AA_58A9_4341_A87D_8F6B12F9CBAE__INCLUDED_)
