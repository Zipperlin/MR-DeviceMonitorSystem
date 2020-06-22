/* Time: <@(#)DirHandler.h   2009-3-5 - 10:42:02   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DirHandler.h
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
 *	1	2009-3-5 - 10:42:02		FanZF	Creation
 *
 *********************************************************************
 */

// DirHandler.h: interface for the CDirHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRHANDLER_H__160D799A_A335_425B_AFF5_78599CD4380C__INCLUDED_)
#define AFX_DIRHANDLER_H__160D799A_A335_425B_AFF5_78599CD4380C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDirHandler  
{
public:
	CDirHandler();
	virtual ~CDirHandler();

	// Create dir if it does not exist, do nothing if it does exist
	// Return TRUE if the dir already existed
	static BOOL CreateDir(LPCTSTR szDir);

	// Delete all the sub-dir and files, but reserve szDir
	// Return FALSE if the dir does not exist
	static BOOL ClearDir(LPCTSTR szDir);

	// Create dir if it does not exists
	// Clear dir if the dir exists and bClearDir == TRUE
	// Do nothing if the dir exists and bClearDir == FALSE
	static BOOL CheckDir(LPCTSTR szDir, BOOL bClearDir);

	// Delete a dir
	// Return TRUE if the dir does not exist
	// Return FALSE if szDir is a file
	static BOOL DeleteDir(LPCTSTR szDir);

	// Delete a file
	// Return TRUE if the file does not exist
	// Return FALSE if szFile is a dir
	static BOOL DeleteFile(LPCTSTR szFile);

	// Determine whether the file exist or not
	// Return TRUE if the file exist
	// Return FALSE if the file does not exist
	static BOOL IsFileExist(LPCTSTR szFile);

private:

	static BOOL DeleteExistedFile(LPCTSTR szFile);
};

#endif // !defined(AFX_DIRHANDLER_H__160D799A_A335_425B_AFF5_78599CD4380C__INCLUDED_)
