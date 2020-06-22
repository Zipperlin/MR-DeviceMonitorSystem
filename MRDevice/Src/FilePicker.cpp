/* Time: <@(#)FilePicker.cpp   2009-3-5 - 10:43:42   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : FilePicker.cpp
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
 *	1	2009-3-5 - 10:43:42		FanZF	Creation
 *
 *********************************************************************
 */

// FilePicker.cpp: implementation of the CFilePicker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FilePicker.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFilePicker::CFilePicker()
{
	m_strOriginalDir = _T("");
	m_strDir = _T("");
	m_hFind = NULL;
	m_bGotDirInfo = FALSE;

	
}

CFilePicker::CFilePicker(CString& strDir)
{
	m_strOriginalDir = strDir;
	m_strDir = strDir;
	m_hFind = NULL;
	m_bGotDirInfo = FALSE;
	m_bIsDir = IsDir(strDir);
}

CFilePicker::~CFilePicker()
{
	Clear();
}

CString CFilePicker::GetFile()
{
	BOOL bRet;

	while (TRUE)
	{
		// Is a file
		if (!m_bIsDir)
		{
			static BOOL bFirstTime = TRUE;
			if (bFirstTime)
			{
				bFirstTime = FALSE;
				return m_strDir;
			}
			else
			{
				return _T("");
			}
		}

		// Is a dir exactly
		if (NULL == m_hFind)
		{
//			m_strDir += _T("\\*");
			m_hFind = FindFirstFile(m_strDir + _T("\\*"), &m_fd);
			if (INVALID_HANDLE_VALUE == m_hFind)
				return CString(_T(""));
			else
			{
				// if the fish is a file
				if (!(m_fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					return CString(m_strDir + _T("\\") + m_fd.cFileName);
				
				// if the fish is a dir
				else
					// if the fish is a "." or ".."
					if (!(_tcscmp(m_fd.cFileName, _T("."))) || !(_tcscmp(m_fd.cFileName, _T(".."))))
					{
						continue;
					}
					// if the fish is a normal dir
					else
					{
						m_DirStack.push(m_strDir);
						m_HandleStack.push(m_hFind);
						m_strDir += _T("\\");
						m_strDir += m_fd.cFileName;
						m_hFind = NULL;
						continue;
					}
			}
		}
		else
		{
			bRet = FindNextFile(m_hFind, &m_fd);
			if (bRet)
			{
				// if the fish is a file
				if (!(m_fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					return CString(m_strDir + _T("\\") + m_fd.cFileName);
				
				// if the fish is a dir
				else
				{
					// if the fish is a "." or ".."
					if (!(_tcscmp(m_fd.cFileName, _T("."))) || !(_tcscmp(m_fd.cFileName, _T(".."))))
					{
						continue;
					}
					// if the fish is a normal dir
					else
					{
						m_DirStack.push(m_strDir);
						m_HandleStack.push(m_hFind);
						m_strDir += _T("\\");
						m_strDir += m_fd.cFileName;
						m_hFind = NULL;
						continue;
					}
				}

			}
			else
			{
				if (ERROR_NO_MORE_FILES == GetLastError())
				{
					// no more files can be found in current dir
					FindClose(m_hFind);
					m_hFind = NULL;
					if (m_DirStack.empty())
					{
						// Searching is over
						return CString(_T(""));
					}
					else
					{
						// 
						m_strDir = m_DirStack.top();
						m_hFind = m_HandleStack.top();
						m_DirStack.pop();
						m_HandleStack.pop();
						continue;
					}
				}
			}
		}
	}

}

BOOL CFilePicker::GetFile(CString& strFileName)
{
	BOOL bRet;

	while (TRUE)
	{
		// Is a file
		if (!m_bIsDir)
		{
			static BOOL bFirstTime = TRUE;
			if (bFirstTime)
			{
				strFileName = m_strOriginalDir;
				bFirstTime = FALSE;
				return TRUE;
			}
			else
			{
				strFileName = _T("");
				return TRUE;
			}
		}

		// Is a dir exactly
		if (NULL == m_hFind)
		{
			// first into a dir
			m_hFind = FindFirstFile(m_strDir + _T("\\*"), &m_fd);
			if (INVALID_HANDLE_VALUE == m_hFind)
			{
				strFileName =  _T("");
				return FALSE;
			}
			else
			{
				// if the fish is a file
				if (!(m_fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					strFileName = m_strDir + _T("\\") + m_fd.cFileName;
					return TRUE;
				}
				
				// if the fish is a dir
				else
					// if the fish is a "." or ".."
					if (!(_tcscmp(m_fd.cFileName, _T("."))) || !(_tcscmp(m_fd.cFileName, _T(".."))))
					{
						continue;
					}
					// if the fish is a normal dir
					else
					{
						m_DirStack.push(m_strDir);
						m_HandleStack.push(m_hFind);
						m_strDir += _T("\\");
						m_strDir += m_fd.cFileName;
						m_hFind = NULL;
						continue;
					}
			}
		}
		else
		{
			bRet = FindNextFile(m_hFind, &m_fd);
			if (bRet)
			{
				// if the fish is a file
				if (!(m_fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					strFileName = m_strDir + _T("\\") + m_fd.cFileName;
					return TRUE;
				}
				
				// if the fish is a dir
				else
				{
					// if the fish is a "." or ".."
					if (!(_tcscmp(m_fd.cFileName, _T("."))) || !(_tcscmp(m_fd.cFileName, _T(".."))))
					{
						continue;
					}
					// if the fish is a normal dir
					else
					{
						m_DirStack.push(m_strDir);
						m_HandleStack.push(m_hFind);
						m_strDir += _T("\\");
						m_strDir += m_fd.cFileName;
						m_hFind = NULL;
						continue;
					}
				}

			}
			else
			{
				if (ERROR_NO_MORE_FILES == GetLastError())
				{
					// no more files can be found in current dir
					FindClose(m_hFind);
					m_hFind = NULL;
					if (m_DirStack.empty())
					{
						// Searching is over
						strFileName = _T("");
						return TRUE;
					}
					else
					{
						// 
						m_strDir = m_DirStack.top();
						m_hFind = m_HandleStack.top();
						m_DirStack.pop();
						m_HandleStack.pop();
						continue;
					}
				}

				else
				{
					strFileName = _T("");
					return FALSE;
				}
			}
		}
	}

}

BOOL CFilePicker::GetDirOrFile(CString& strDirOrFileName, BOOL& bIsDir)
{
	BOOL bRet;
	
	while (TRUE)
	{
		// Is a file
		if (!m_bIsDir)
		{
			static BOOL bFirstTime = TRUE;
			if (bFirstTime)
			{
				strDirOrFileName = m_strDir;
				bIsDir = FALSE;
				bFirstTime = FALSE;
				return TRUE;
			}
			else
			{
				strDirOrFileName = _T("");
				return TRUE;
			}
		}

		// Is a dir exactly
		if (NULL == m_hFind)
		{
			// first into a dir
			m_hFind = FindFirstFile(m_strDir + _T("\\*"), &m_fd);
			if (INVALID_HANDLE_VALUE == m_hFind)
			{
				strDirOrFileName =  _T("");
				return FALSE;
			}
			else
			{
				// if the fish is a file
				if (!(m_fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					strDirOrFileName = m_strDir + _T("\\") + m_fd.cFileName;
					bIsDir = FALSE;
					return TRUE;
				}
				
				// if the fish is a dir
				else
					// if the fish is a "." or ".."
					if (!(_tcscmp(m_fd.cFileName, _T("."))) || !(_tcscmp(m_fd.cFileName, _T(".."))))
					{
						continue;
					}
					// if the fish is a normal dir
					else
					{
						m_DirStack.push(m_strDir);
						m_HandleStack.push(m_hFind);
						m_strDir += _T("\\");
						m_strDir += m_fd.cFileName;
						m_hFind = NULL;
						
						strDirOrFileName = m_strDir;
						bIsDir = TRUE;
						return TRUE;
					}
			}
		}
		else
		{
			bRet = FindNextFile(m_hFind, &m_fd);
			if (bRet)
			{
				// if the fish is a file
				if (!(m_fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					strDirOrFileName = m_strDir + _T("\\") + m_fd.cFileName;
					bIsDir = FALSE;
					return TRUE;
				}
				
				// if the fish is a dir
				else
				{
					// if the fish is a "." or ".."
					if (!(_tcscmp(m_fd.cFileName, _T("."))) || !(_tcscmp(m_fd.cFileName, _T(".."))))
					{
						continue;
					}
					// if the fish is a normal dir
					else
					{
						m_DirStack.push(m_strDir);
						m_HandleStack.push(m_hFind);
						m_strDir += _T("\\");
						m_strDir += m_fd.cFileName;
						m_hFind = NULL;

						strDirOrFileName = m_strDir;
						bIsDir = TRUE;
						return TRUE;
					}
				}

			}
			else
			{
				if (ERROR_NO_MORE_FILES == GetLastError())
				{
					// no more files can be found in current dir
					FindClose(m_hFind);
					m_hFind = NULL;
					if (m_DirStack.empty())
					{
						// Searching is over
						strDirOrFileName = _T("");
						return TRUE;
					}
					else
					{
						// Searching is not over
						m_strDir = m_DirStack.top();
						m_hFind = m_HandleStack.top();
						m_DirStack.pop();
						m_HandleStack.pop();
						continue;
					}
				}

				else
				{
					// Error
					strDirOrFileName = _T("");
					return FALSE;
				}
			}
		}
	}

}

BOOL CFilePicker::GetDirOrFileEx(CString& strDirOrFileName, BOOL& bIsDir)
{
	return TRUE;
}

void CFilePicker::SetDir(CString strDir)
{
	Clear();
	
	m_strDir = strDir;
	m_strOriginalDir = strDir;
	m_hFind = NULL;
	m_bGotDirInfo = FALSE;
	m_bIsDir = IsDir(strDir);
}

void CFilePicker::Clear()
{
	m_strOriginalDir = _T("");
	m_strDir = _T("");

	if (NULL != m_hFind)
	{
		FindClose(m_hFind);
		m_hFind = NULL;
	}
	
	while(!m_HandleStack.empty())
	{
		m_hFind = m_HandleStack.top();
		FindClose(m_hFind);
		m_hFind = NULL;

		m_DirStack.pop();
		m_HandleStack.pop();
	}
}


BOOL CFilePicker::GetFileCount(UINT* puiFileCount, BOOL bForce)
{
	BOOL bRet;
	if (bForce || !m_bGotDirInfo)
	{
		bRet = GetDirInfo();
	}

	*puiFileCount = m_uiFileCount;
	return bRet;
}

BOOL CFilePicker::GetDirCount(UINT* puiDirCount, BOOL bForce)
{
	BOOL bRet;
	if (bForce || !m_bGotDirInfo)
	{
		bRet = GetDirInfo();
	}

	*puiDirCount = m_uiDirCount;
	return bRet;

}

BOOL CFilePicker::GetTotalSize(__int64* pi64TotalSize, BOOL bForce)
{
	BOOL bRet;
	if (bForce || !m_bGotDirInfo)
	{
		bRet = GetDirInfo();
	}

	*pi64TotalSize = m_i64TotalSize;
	return bRet;

}

BOOL CFilePicker::GetDirInfo()
{
	BOOL bRet;
	CString strDir = m_strOriginalDir;
	HANDLE hFind = NULL;
	WIN32_FIND_DATA fd;
	stack<CString> stackDir;
	stack<HANDLE> stackHandle;

	m_uiFileCount = 0;
	m_uiDirCount = 0;
	m_i64TotalSize = 0;
	
	while (TRUE)
	{
		if (!m_bIsDir)
		{
			// Is a file, not dir
			hFind = FindFirstFile(strDir, &fd);
			if (INVALID_HANDLE_VALUE == hFind)
			{
				return FALSE;
			}
			else
			{
				m_uiFileCount = 1;

				if (0 == fd.nFileSizeHigh)
					m_i64TotalSize += fd.nFileSizeLow;
				else
				{
					__int64 i64 = (DWORD)MAXDWORD;
					m_i64TotalSize += fd.nFileSizeHigh*(i64 + 1) + fd.nFileSizeLow;
				}

				FindClose(hFind);
				return TRUE;
			}
		}

		// Is a dir
		if (NULL == hFind)
		{
			// first into a dir
			hFind = FindFirstFile(strDir + _T("\\*"), &fd);
			if (INVALID_HANDLE_VALUE == hFind)
			{
				return FALSE;
			}
			else
			{
				// if the fish is a file
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					++m_uiFileCount;
					if (0 == fd.nFileSizeHigh)
						m_i64TotalSize += fd.nFileSizeLow;
					else
					{
						__int64 i64 = (DWORD)MAXDWORD;
						m_i64TotalSize += fd.nFileSizeHigh*(i64 + 1) + fd.nFileSizeLow;
					}
					continue;
				}
				
				// if the fish is a dir
				else
					// if the fish is a "." or ".."
					if (!(_tcscmp(fd.cFileName, _T("."))) || !(_tcscmp(fd.cFileName, _T(".."))))
					{
						continue;
					}
					// if the fish is a normal dir
					else
					{
						stackDir.push(strDir);
						stackHandle.push(hFind);
						strDir += _T("\\");
						strDir += fd.cFileName;
						hFind = NULL;
						
						++m_uiDirCount;
						continue;
					}
			}
		}
		else
		{
			bRet = FindNextFile(hFind, &fd);
			if (bRet)
			{
				// if the fish is a file
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					++m_uiFileCount;
					if (0 == fd.nFileSizeHigh)
						m_i64TotalSize += fd.nFileSizeLow;
					else
					{
						__int64 i64 = (DWORD)MAXDWORD;
						m_i64TotalSize += fd.nFileSizeHigh*(i64 + 1) + fd.nFileSizeLow;
					}
					continue;
				}
				
				// if the fish is a dir
				else
				{
					// if the fish is a "." or ".."
					if (!(_tcscmp(fd.cFileName, _T("."))) || !(_tcscmp(fd.cFileName, _T(".."))))
					{
						continue;
					}
					// if the fish is a normal dir
					else
					{
						stackDir.push(strDir);
						stackHandle.push(hFind);
						strDir += _T("\\");
						strDir += fd.cFileName;
						hFind = NULL;

						++m_uiDirCount;
						continue;
					}
				}

			}
			else
			{
				if (ERROR_NO_MORE_FILES == GetLastError())
				{
					// no more files can be found in current dir
					FindClose(hFind);
					hFind = NULL;
					if (stackDir.empty())
					{
						// Searching is over
						return TRUE;
					}
					else
					{
						// Searching is not over, pop a dir
						strDir = stackDir.top();
						hFind = stackHandle.top();
						stackDir.pop();
						stackHandle.pop();
						continue;
					}
				}

				else
				{
					// Error, should clear stack and close handle
					
					return FALSE;
				}
			}
		}
	}

}


BOOL CFilePicker::IsDir(CString &strFileName)
{
	DWORD dwRet = GetFileAttributes(strFileName);
	if (FALSE/*INVALID_FILE_ATTRIBUTES == dwRet*/)
	{
		// error
	}
	else
	{
		if (dwRet & FILE_ATTRIBUTE_DIRECTORY)
			return TRUE;
		else
			return FALSE;
	}
}
