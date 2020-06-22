/* Time: <@(#)DirHandler.cpp   2009-3-5 - 10:42:17   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DirHandler.cpp
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
 *	1	2009-3-5 - 10:42:17		FanZF	Creation
 *
 *********************************************************************
 */

// DirHandler.cpp: implementation of the CDirHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DirHandler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirHandler::CDirHandler()
{

}

CDirHandler::~CDirHandler()
{

}

BOOL CDirHandler::CreateDir(LPCTSTR szDir)
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString strTrace;

	LPCTSTR szAim = wcschr(szDir, _T('\\'));
	CString strRoot(szDir, szAim - szDir + 1);

	// Is root dir exist?
	if (DRIVE_FIXED == GetDriveType(strRoot))
	{
		while (TRUE)
		{
			if (_T('\0') == *(szAim + 1))
				return TRUE;

			szAim = wcschr(szAim + 1, _T('\\'));
			if (szAim)
			{
				CString strDir(szDir, szAim - szDir);
				hFind = FindFirstFile(strDir, &fd);
				if (((INVALID_HANDLE_VALUE != hFind)     
					&& (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)))
				{
					// dir exist, so continue
					FindClose(hFind);
					hFind = INVALID_HANDLE_VALUE;
					continue;
				}
				else
				{
					// dir is not exist
					FindClose(hFind);
					hFind = INVALID_HANDLE_VALUE;
					if (CreateDirectory(strDir, NULL))
					{
						strTrace.Format(_T("CreateDirectory(): %s"), strDir);
						PRINTTRACE_INFO(strTrace)
						// Create dir succeed, so continue
						continue;
					}
					else
					{
						return FALSE;
					}
				}
			}
			else
			{
				hFind = FindFirstFile(szDir, &fd);
				if ((INVALID_HANDLE_VALUE != hFind)     
					&& (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					FindClose(hFind);
					return TRUE;
				}
				else if ((INVALID_HANDLE_VALUE != hFind)     
					&& !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					// the fish exists but it's a normal file, but dir...
					FindClose(hFind);
					return FALSE;
				}
				else
				{
					FindClose(hFind);

					// dir is not exist
					if (CreateDirectory(szDir, NULL))
					{
						strTrace.Format(_T("CreateDirectory(): %s"), szDir);
						PRINTTRACE_INFO(strTrace)
						// Create dir succeed
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}
			}
		}
	}
	else
	{
		return FALSE;
	}
}


BOOL CDirHandler::ClearDir(LPCTSTR szDir)
{
	if (NULL == szDir)
		return FALSE;

	WIN32_FIND_DATA fd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString strTrace;

	BOOL bRet = TRUE;

	// Dir exist?
	hFind = FindFirstFile(szDir, &fd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		DWORD dwRet = GetLastError();
		if (ERROR_FILE_NOT_FOUND == dwRet ||
			ERROR_PATH_NOT_FOUND == dwRet)
		{
			strTrace.Format(_T("Dir no found, szDir: %s"), szDir);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
		else
		{
			strTrace.Format(_T("hFind = FindFirstFile(szDir, &fd), szDir: %s"), szDir);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
	}
	else
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;

		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			// the specified szDir is not a dir
			strTrace.Format(_T("%s is not a dir"), szDir);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
		else
		{
			// Clear the dir
			CString strTaskDir = szDir;
			hFind = FindFirstFile(strTaskDir + _T("\\*"), &fd);
			if (INVALID_HANDLE_VALUE == hFind)
			{
				return FALSE;
			}

			do{
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (!wcscmp(fd.cFileName, _T(".")) || !wcscmp(fd.cFileName, _T("..")))
					{
						continue;
					}
					else
					{
						if (!DeleteDir(strTaskDir + _T("\\") + fd.cFileName))
						{
							bRet = FALSE;
							strTrace = _T("Failed to DeleteDir : ");
							strTrace += strTaskDir + _T("\\") + fd.cFileName;
							PRINTTRACE_ERROR(strTrace)
							break;
						}
					}
				}
				else
				{
					// It's File
					if (!DeleteExistedFile(strTaskDir + _T("\\") + fd.cFileName))
					{
						bRet = FALSE;
						strTrace = _T("Failed to Delete file : ");
						strTrace += strTaskDir + _T("\\") + fd.cFileName;
						PRINTTRACE_ERROR(strTrace)
						break;
					}
				}
			}while (FindNextFile(hFind, &fd));

			FindClose(hFind);

			if (bRet && ERROR_NO_MORE_FILES == GetLastError())
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}

	}
}

BOOL CDirHandler::CheckDir(LPCTSTR szDir, BOOL bClearDir)
{
	CString strTrace;

	if (CreateDir(szDir))
	{
		if (bClearDir)
		{
			if (ClearDir(szDir))
			{
				return TRUE;
			}
			else
			{
				strTrace.Format(_T("ClearDir(), szDir = %s"), szDir);
				PRINTTRACE_ERROR(strTrace)
				return FALSE;
			}
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		strTrace.Format(_T("CreateDir(), szDir = %s"), szDir);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

}

BOOL CDirHandler::DeleteDir(LPCTSTR szDir)
{
	if (NULL == szDir)
		return FALSE;

	WIN32_FIND_DATA fd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString strTrace;

	BOOL bRet = TRUE;

	// Dir exist?
	hFind = FindFirstFile(szDir, &fd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		DWORD dwRet = GetLastError();
		if (ERROR_FILE_NOT_FOUND == dwRet ||
			ERROR_PATH_NOT_FOUND == dwRet)
		{
			return TRUE;
		}
		else
		{
			strTrace.Format(_T("hFind = FindFirstFile(szDir, &fd), szDir: %s"), szDir);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
	}
	else
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;

		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			// the specified szDir is not a dir
			strTrace.Format(_T("%s is not a dir"), szDir);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}

	}
	

	CString strTaskDir = szDir;
	hFind = FindFirstFile(strTaskDir + _T("\\*"), &fd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return FALSE;
	}

	do{
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!wcscmp(fd.cFileName, _T(".")) || !wcscmp(fd.cFileName, _T("..")))
			{
				continue;
			}
			else
			{
				if (DeleteDir(strTaskDir + _T("\\") + fd.cFileName))
				{
					strTrace = _T("DeleteDir : ");
					strTrace += strTaskDir + _T("\\") + fd.cFileName;
					PRINTTRACE_INFO(strTrace)
				}
				else
				{
					bRet = FALSE;
					strTrace = _T("Failed to DeleteDir : ");
					strTrace += strTaskDir + _T("\\") + fd.cFileName;
					PRINTTRACE_ERROR(strTrace)
					break;
				}
			}
		}
		else
		{
			// It's File
			if (DeleteExistedFile(strTaskDir + _T("\\") + fd.cFileName))
			{
				strTrace = _T("Delete file : ");
				strTrace += strTaskDir + _T("\\") + fd.cFileName;
				PRINTTRACE_INFO(strTrace)
			}
			else
			{
				bRet = FALSE;
				strTrace = _T("Failed to Delete file : ");
				strTrace += strTaskDir + _T("\\") + fd.cFileName;
				PRINTTRACE_ERROR(strTrace)
				break;
			}
		}
	}while (FindNextFile(hFind, &fd));

	FindClose(hFind);

	if (bRet && ERROR_NO_MORE_FILES == GetLastError())
	{
		if (::RemoveDirectory(strTaskDir))
		{
			strTrace = _T("Delete Dir : ");
			strTrace += strTaskDir;
			PRINTTRACE_INFO(strTrace)
			return TRUE;
		}
		else
		{
			strTrace = _T("Failed to Delete Dir : ");
			strTrace += strTaskDir;
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CDirHandler::DeleteFile(LPCTSTR szFile)
{
	if (NULL == szFile)
	{
		return FALSE;
	}

	WIN32_FIND_DATA fd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	CString strTrace;

	// File exist?
	hFind = FindFirstFile(szFile, &fd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		DWORD dwRet = GetLastError();
		if (ERROR_FILE_NOT_FOUND == dwRet ||
			ERROR_PATH_NOT_FOUND == dwRet)
		{
			return TRUE;
		}
		else
		{
			strTrace.Format(_T("hFind = FindFirstFile(szFile, &fd), szFile: %s"), szFile);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
	}
	else
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;

		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// the specified szFile is a dir
			strTrace.Format(_T("%s is a dir"), szFile);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
		else
		{
			if (DeleteExistedFile(szFile))
			{
				return TRUE;
			}
			else
			{
				strTrace.Format(_T("Delete file: %s"), szFile);
				PRINTTRACE_ERROR(strTrace)
				return FALSE;
			}
		}
	}
}

BOOL CDirHandler::IsFileExist(LPCTSTR szFile)
{
	CString strTrace;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(szFile, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		strTrace.Format(_T("FindFirstFile(), szFile: %s"), szFile);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
	else
	{
		FindClose(hFind);
		return TRUE;
	}
}

BOOL CDirHandler::DeleteExistedFile(LPCTSTR szFile)
{
	CString strTrace;

	//<< ÒÆ³ýÖ»¶ÁÊôÐÔ
	if (!::SetFileAttributes(szFile, FILE_ATTRIBUTE_NORMAL))
	{
		strTrace.Format(_T("SetFileAttributes(szFile£¬ FILE_ATTRIBUTE_NORMAL): %s"), szFile);
		PRINTTRACE_INFO(strTrace)
	}

	if (::DeleteFile(szFile))
	{
		return TRUE;
	}
	else
	{
		strTrace.Format(_T("Delete file: %s"), szFile);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
}
