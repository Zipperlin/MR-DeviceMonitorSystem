/* Time: <@(#)WorklistIniOpt.cpp   2009-3-5 - 10:53:11   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : WorklistIniOpt.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The operation for worklist .ini file
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:53:11		FanZF	Creation
 *
 *********************************************************************
 */

// WorklistIniOpt.cpp: implementation of the CWorklistIniOpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WorklistIniOpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CWorklistIniOpt* CWorklistIniOpt::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorklistIniOpt::CWorklistIniOpt()
{

}

CWorklistIniOpt::~CWorklistIniOpt()
{

}

CWorklistIniOpt* CWorklistIniOpt::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CWorklistIniOpt;
	}

	return m_pInstance;
}

void CWorklistIniOpt::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

BOOL CWorklistIniOpt::Init()
{
	TCHAR cCurrentSystemDirectory[MAX_PATH]; 
	GetModuleFileName(NULL, cCurrentSystemDirectory, MAX_PATH);
	CString strApplicationName = cCurrentSystemDirectory;

	CString strApplicationPath = strApplicationName.Left(strApplicationName.ReverseFind('\\'));	//获得不带应用程序文件名的应用程序路径(去掉应用程序文件名)	

	// Worklist.ini
	CString strIniFile = strApplicationPath + SYSTEM_CONFIG_DIR + _T("\\") + WORKLIST_INI_FILE_NAME;
	SetIniFile(strIniFile);

	return TRUE;
}

void CWorklistIniOpt::UnInit()
{
	SetIniFile(_T(""));
}


int CWorklistIniOpt::GetDefaultWorklistServer(NetworkNodeStruct* pNodeStruct)
{
	if (!IsIniFileExist())
	{
		return E_UNEXPECTED_ERROR;
	}

	int iServerCount = GetIntFromINI(WORKLIST_INI_SECTION_WL_SERVER_INFO, WORKLIST_INI_KEY_SERVER_COUNT);
	if (0 == iServerCount)
	{
		return E_WLMPPS_INI_NO_SERVER;
	}

	// iCurSel从1开始
	int iCurSel = GetIntFromINI(WORKLIST_INI_SECTION_WL_SERVER_INFO, WORKLIST_INI_KEY_SERVER_CUR_SEL);
	if (iCurSel < 1 || iCurSel > iServerCount)
	{
		return E_WLMPPS_INI_NO_SERVER_SELECTED;
	}

	CString strSelServer;
	strSelServer.Format(_T("%s%d"), WORKLIST_INI_SECTION_WL_SERVER, iCurSel);
	pNodeStruct->strCalledAE = GetStrFromINI(strSelServer, WORKLIST_INI_KEY_SERVER_CALLEDAE);
	pNodeStruct->strIP = GetStrFromINI(strSelServer, WORKLIST_INI_KEY_SERVER_IP);
	pNodeStruct->strPort = GetStrFromINI(strSelServer, WORKLIST_INI_KEY_SERVER_PORT);
	pNodeStruct->strCallingAE = GetStrFromINI(strSelServer, WORKLIST_INI_KEY_SERVER_CALLINGAE);

	pNodeStruct->bDefault = TRUE;

	if (pNodeStruct->strCalledAE.IsEmpty() ||
		pNodeStruct->strIP.IsEmpty() ||
		pNodeStruct->strPort.IsEmpty() ||
		pNodeStruct->strCallingAE.IsEmpty())
	{
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		return E_OK;
	}
}

BOOL CWorklistIniOpt::GetQueryItemList(vector<WLQueryItem>* pWLQueryItemList)
{
	int iSPSSSItemCount = GetIntFromINI(WORKLIST_INI_SECTION_INFORMATION, WORKLIST_INI_KEY_INFO_SPSSS_ITEMCOUNT);
	int iItemCount = GetIntFromINI(WORKLIST_INI_SECTION_INFORMATION, WORKLIST_INI_KEY_INFO_ITEMCOUNT);

	CString strSectionName;
	CString strTemp;

	// 从1开始读取SPS Sequence Subitem
	for (int i = 1; i <= iSPSSSItemCount; i++)
	{
		strSectionName.Format(_T("%s%d"), WORKLIST_INI_SECTION_SPSSS, i);
		if (GetIntFromINI(strSectionName, WORKLIST_INI_KEY_ISCHECK))
		{
			WLQueryItem aWLQueryItem;
			strTemp = GetStrFromINI(strSectionName, WORKLIST_INI_KEY_GROUP);
			if (strTemp.IsEmpty())
			{
				continue;
			}
			else
			{
				aWLQueryItem.usGroup = _tcstoul((LPCTSTR)strTemp, NULL, 16);
			}
			
			strTemp = GetStrFromINI(strSectionName, WORKLIST_INI_KEY_ELEMENT);
			if (strTemp.IsEmpty())
			{
				continue;
			}
			else
			{
				aWLQueryItem.usElement = _tcstoul((LPCTSTR)strTemp, NULL, 16);
			}

			aWLQueryItem.strValue = GetStrFromINI(strSectionName, WORKLIST_INI_KEY_VALUE);

			if (0 == aWLQueryItem.usGroup || 0 == aWLQueryItem.usElement)
			{
				continue;
			}
			else
			{
				pWLQueryItemList->push_back(aWLQueryItem);
			}
		}
	}

	// 从1开始读取Item
	for (i = 1; i <= iItemCount; i++)
	{
		strSectionName.Format(_T("%s%d"), WORKLIST_INI_SECTION_ITEM, i);
		if (GetIntFromINI(strSectionName, WORKLIST_INI_KEY_ISCHECK))
		{
			WLQueryItem aWLQueryItem;
			strTemp = GetStrFromINI(strSectionName, WORKLIST_INI_KEY_GROUP);
			if (strTemp.IsEmpty())
			{
				continue;
			}
			else
			{
				aWLQueryItem.usGroup = _tcstoul((LPCTSTR)strTemp, NULL, 16);
			}
			
			strTemp = GetStrFromINI(strSectionName, WORKLIST_INI_KEY_ELEMENT);
			if (strTemp.IsEmpty())
			{
				continue;
			}
			else
			{
				aWLQueryItem.usElement = _tcstoul((LPCTSTR)strTemp, NULL, 16);
			}

			aWLQueryItem.strValue = GetStrFromINI(strSectionName, WORKLIST_INI_KEY_VALUE);

			if (0 == aWLQueryItem.usGroup || 0 == aWLQueryItem.usElement)
			{
				continue;
			}
			else
			{
				pWLQueryItemList->push_back(aWLQueryItem);
			}
		}
	}

	return TRUE;
}

INT CWorklistIniOpt::GetServers(vector<NetworkNodeStruct>* pvtrServers)
{
	if (!IsIniFileExist())
	{
		return E_UNEXPECTED_ERROR;
	}

	//<< server总数及当前选择item id
	int iServerCount = GetIntFromINI(WORKLIST_INI_SECTION_WL_SERVER_INFO, WORKLIST_INI_KEY_SERVER_COUNT);
	int iCurSel = GetIntFromINI(WORKLIST_INI_SECTION_WL_SERVER_INFO, WORKLIST_INI_KEY_SERVER_CUR_SEL);

	CString strSection;
	for (int i = 1; i <= iServerCount; i++)
	{
		NetworkNodeStruct nns;
		strSection.Format(_T("%s%d"), WORKLIST_INI_SECTION_WL_SERVER, i);

		CString strValue;
		strValue = GetStrFromINI(strSection, WORKLIST_INI_KEY_SERVER_CALLEDAE);
		if (strValue.IsEmpty())
		{
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strCalledAE = strValue;
		}

		strValue = GetStrFromINI(strSection, WORKLIST_INI_KEY_SERVER_IP);
		if (strValue.IsEmpty())
		{
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strIP = strValue;
		}

		strValue = GetStrFromINI(strSection, WORKLIST_INI_KEY_SERVER_PORT);
		if (strValue.IsEmpty())
		{
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strPort = strValue;
		}

		strValue = GetStrFromINI(strSection, WORKLIST_INI_KEY_SERVER_CALLINGAE);
		if (strValue.IsEmpty())
		{
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strCallingAE = strValue;
		}

		if (i == iCurSel)
		{
			nns.bDefault = TRUE;
		}
		else
		{
			nns.bDefault = FALSE;
		}

		pvtrServers->push_back(nns);
	}

	return E_OK;
}

INT CWorklistIniOpt::SetServers(vector<NetworkNodeStruct>* pvtrServers)
{
	if (!IsIniFileExist())
	{
		return E_UNEXPECTED_ERROR;
	}

	//<< server总数及当前选择item id
	int iServerCount = GetIntFromINI(WORKLIST_INI_SECTION_WL_SERVER_INFO, WORKLIST_INI_KEY_SERVER_COUNT);

	//<< 删除原有servers
	CString strSection;
	for (int i = 1; i <= iServerCount; i++)
	{
		strSection.Format(_T("%s%d"), WORKLIST_INI_SECTION_WL_SERVER, i);
		if (!DeleteSectionFromINI(strSection))
		{
			return E_UNEXPECTED_ERROR;
		}
	}

	//<< 写入新的servers
	int iCurSel = 0;
	
	for (i = 1; i <= pvtrServers->size(); i++)
	{
		NetworkNodeStruct nns;
		strSection.Format(_T("%s%d"), WORKLIST_INI_SECTION_WL_SERVER, i);

		if (!WriteKeyToINI(strSection, WORKLIST_INI_KEY_SERVER_CALLEDAE, (*pvtrServers)[i-1].strCalledAE))
		{
			return E_UNEXPECTED_ERROR;
		}

		if (!WriteKeyToINI(strSection, WORKLIST_INI_KEY_SERVER_IP, (*pvtrServers)[i-1].strIP))
		{
			return E_UNEXPECTED_ERROR;
		}

		if (!WriteKeyToINI(strSection, WORKLIST_INI_KEY_SERVER_PORT, (*pvtrServers)[i-1].strPort))
		{
			return E_UNEXPECTED_ERROR;
		}

		if (!WriteKeyToINI(strSection, WORKLIST_INI_KEY_SERVER_CALLINGAE, (*pvtrServers)[i-1].strCallingAE))
		{
			return E_UNEXPECTED_ERROR;
		}
		
		if (!WriteKeyToINI(strSection, WORKLIST_INI_KEY_SERVER_TIMEOUT, _T("20")))
		{
			return E_UNEXPECTED_ERROR;
		}

		if ((*pvtrServers)[i-1].bDefault)
		{
			iCurSel = i;
		}
	}

	//<< 写入server数和选择的server id
	CString strValue;
	strValue.Format(_T("%d"), pvtrServers->size());
	if (!WriteKeyToINI(WORKLIST_INI_SECTION_WL_SERVER_INFO, WORKLIST_INI_KEY_SERVER_COUNT, strValue))
	{
		return E_UNEXPECTED_ERROR;
	}

	strValue.Format(_T("%d"), iCurSel);
	if (!WriteKeyToINI(WORKLIST_INI_SECTION_WL_SERVER_INFO, WORKLIST_INI_KEY_SERVER_CUR_SEL, strValue))
	{
		return E_UNEXPECTED_ERROR;
	}

	return E_OK;

}