/* Time: <@(#)MPPSIniOpt.cpp   2009-3-5 - 10:48:45   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : MPPSIniOpt.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Operation class for MPPS .ini file
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:48:45		FanZF	Creation
 *
 *********************************************************************
 */

// MPPSIniOpt.cpp: implementation of the CMPPSIniOpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MPPSIniOpt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CMPPSIniOpt* CMPPSIniOpt::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMPPSIniOpt::CMPPSIniOpt()
{

}

CMPPSIniOpt::~CMPPSIniOpt()
{

}

CMPPSIniOpt* CMPPSIniOpt::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CMPPSIniOpt;
	}

	return m_pInstance;
}

void CMPPSIniOpt::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

BOOL CMPPSIniOpt::Init()
{
	TCHAR cCurrentSystemDirectory[MAX_PATH]; 
	GetModuleFileName(NULL, cCurrentSystemDirectory, MAX_PATH);
	CString strApplicationName = cCurrentSystemDirectory;

	CString strApplicationPath = strApplicationName.Left(strApplicationName.ReverseFind('\\'));	//获得不带应用程序文件名的应用程序路径(去掉应用程序文件名)	

	// MPPS.ini
	CString strIniFile = strApplicationPath + SYSTEM_CONFIG_DIR + _T("\\") + MPPS_INI_FILE_NAME;
	SetIniFile(strIniFile);

	return TRUE;
}

void CMPPSIniOpt::UnInit()
{
	SetIniFile(_T(""));
}

int CMPPSIniOpt::GetDefaultServer(NetworkNodeStruct* pNodeStruct)
{
	if (!IsIniFileExist())
	{
		return E_UNEXPECTED_ERROR;
	}

	int iServerCount = GetIntFromINI(MPPS_INI_SECTION_MPPS_SERVER_INFO, MPPS_INI_KEY_SERVER_COUNT);
	if (0 == iServerCount)
	{
		return E_WLMPPS_INI_NO_SERVER;
	}

	// iCurSel从1开始
	int iCurSel = GetIntFromINI(MPPS_INI_SECTION_MPPS_SERVER_INFO, MPPS_INI_KEY_SERVER_CUR_SEL);
	if (iCurSel < 1 || iCurSel > iServerCount)
	{
		return E_WLMPPS_INI_NO_SERVER_SELECTED;
	}

	CString strSelServer;
	strSelServer.Format(_T("%s%d"), MPPS_INI_SECTION_MPPS_SERVER, iCurSel);
	pNodeStruct->strCalledAE = GetStrFromINI(strSelServer, MPPS_INI_KEY_SERVER_CALLEDAE);
	pNodeStruct->strIP = GetStrFromINI(strSelServer, MPPS_INI_KEY_SERVER_IP);
	pNodeStruct->strPort = GetStrFromINI(strSelServer, MPPS_INI_KEY_SERVER_PORT);
	pNodeStruct->strCallingAE = GetStrFromINI(strSelServer, MPPS_INI_KEY_SERVER_CALLINGAE);

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

BOOL CMPPSIniOpt::GetNCreateItems(vector<WLQueryItem>* pItems)
{
	return GetItems(pItems, TRUE);
}

BOOL CMPPSIniOpt::GetNSetItems(vector<WLQueryItem>* pItems)
{
	return GetItems(pItems, FALSE);
}

BOOL CMPPSIniOpt::GetItems(vector<WLQueryItem>* pItems, BOOL bNCreate)
{
	int iSeqItemCount = 0;
	int iItemCount = 0;
	CString strSecSeqSubItem;
	CString strSecItem;

	if (bNCreate)
	{
		iSeqItemCount = GetIntFromINI(MPPS_INI_SECTION_CREATE_INFORMATION, MPPS_INI_KEY_CREATE_INFO_SEQ_ITEMCOUNT);
		iItemCount = GetIntFromINI(MPPS_INI_SECTION_CREATE_INFORMATION, MPPS_INI_KEY_CREATE_INFO_ITEMCOUNT);

		strSecSeqSubItem = MPPS_INI_SECTION_CREATE_SEQ_SUBITEM;
		strSecItem = MPPS_INI_SECTION_CREATE_ITEM;
	}
	else
	{
		iSeqItemCount = GetIntFromINI(MPPS_INI_SECTION_SET_INFORMATION, MPPS_INI_KEY_SET_INFO_SEQ_ITEMCOUNT);
		iItemCount = GetIntFromINI(MPPS_INI_SECTION_SET_INFORMATION, MPPS_INI_KEY_SET_INFO_ITEMCOUNT);

		strSecSeqSubItem = MPPS_INI_SECTION_SET_SEQ_SUBITEM;
		strSecItem = MPPS_INI_SECTION_SET_ITEM;

	}

	CString strSectionName;
	CString strTemp;

	// 从1开始读取 Sequence SubItem
	for (int i = 1; i <= iSeqItemCount; i++)
	{
		strSectionName.Format(_T("%s%d"), strSecSeqSubItem, i);
		if (GetIntFromINI(strSectionName, MPPS_INI_KEY_ISCHECK))
		{
			WLQueryItem aItem;
			strTemp = GetStrFromINI(strSectionName, MPPS_INI_KEY_GROUP);
			if (strTemp.IsEmpty())
			{
				continue;
			}
			else
			{
				aItem.usGroup = _tcstoul((LPCTSTR)strTemp, NULL, 16);
			}
			
			strTemp = GetStrFromINI(strSectionName, MPPS_INI_KEY_ELEMENT);
			if (strTemp.IsEmpty())
			{
				continue;
			}
			else
			{
				aItem.usElement = _tcstoul((LPCTSTR)strTemp, NULL, 16);
			}

			strTemp = GetStrFromINI(strSectionName, MPPS_INI_KEY_TYPE);
			if (strTemp.IsEmpty())
			{
				continue;
			}
			else
			{
				aItem.usType = _tcstoul((LPCTSTR)strTemp, NULL, 10);
			}

			aItem.strValue = GetStrFromINI(strSectionName, MPPS_INI_KEY_VALUE);

			if (0 == aItem.usGroup || 0 == aItem.usElement)
			{
				continue;
			}
			else
			{
				pItems->push_back(aItem);
			}
		}
	}

	// 从1开始读取Item
	for (i = 1; i <= iItemCount; i++)
	{
		strSectionName.Format(_T("%s%d"), strSecItem, i);
		if (GetIntFromINI(strSectionName, MPPS_INI_KEY_ISCHECK))
		{
			WLQueryItem aItem;
			strTemp = GetStrFromINI(strSectionName, MPPS_INI_KEY_GROUP);
			if (strTemp.IsEmpty())
			{
				continue;
			}
			else
			{
				aItem.usGroup = _tcstoul((LPCTSTR)strTemp, NULL, 16);
			}
			
			strTemp = GetStrFromINI(strSectionName, MPPS_INI_KEY_ELEMENT);
			if (strTemp.IsEmpty())
			{
				continue;
			}
			else
			{
				aItem.usElement = _tcstoul((LPCTSTR)strTemp, NULL, 16);
			}

			strTemp = GetStrFromINI(strSectionName, MPPS_INI_KEY_TYPE);
			if (strTemp.IsEmpty())
			{
				continue;
			}
			else
			{
				aItem.usType = _tcstoul((LPCTSTR)strTemp, NULL, 10);
			}

			aItem.strValue = GetStrFromINI(strSectionName, MPPS_INI_KEY_VALUE);

			if (0 == aItem.usGroup || 0 == aItem.usElement)
			{
				continue;
			}
			else
			{
				pItems->push_back(aItem);
			}
		}
	}

	return TRUE;
}

INT CMPPSIniOpt::GetServers(vector<NetworkNodeStruct>* pvtrServers)
{
	if (!IsIniFileExist())
	{
		return E_UNEXPECTED_ERROR;
	}

	//<< server总数及当前选择item id
	int iServerCount = GetIntFromINI(MPPS_INI_SECTION_MPPS_SERVER_INFO, MPPS_INI_KEY_SERVER_COUNT);
	int iCurSel = GetIntFromINI(MPPS_INI_SECTION_MPPS_SERVER_INFO, MPPS_INI_KEY_SERVER_CUR_SEL);

	CString strSection;
	for (int i = 1; i <= iServerCount; i++)
	{
		NetworkNodeStruct nns;
		strSection.Format(_T("%s%d"), MPPS_INI_SECTION_MPPS_SERVER, i);

		CString strValue;
		strValue = GetStrFromINI(strSection, MPPS_INI_KEY_SERVER_CALLEDAE);
		if (strValue.IsEmpty())
		{
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strCalledAE = strValue;
		}

		strValue = GetStrFromINI(strSection, MPPS_INI_KEY_SERVER_IP);
		if (strValue.IsEmpty())
		{
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strIP = strValue;
		}

		strValue = GetStrFromINI(strSection, MPPS_INI_KEY_SERVER_PORT);
		if (strValue.IsEmpty())
		{
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strPort = strValue;
		}

		strValue = GetStrFromINI(strSection, MPPS_INI_KEY_SERVER_CALLINGAE);
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

INT CMPPSIniOpt::SetServers(vector<NetworkNodeStruct>* pvtrServers)
{
	if (!IsIniFileExist())
	{
		return E_UNEXPECTED_ERROR;
	}

	//<< server总数及当前选择item id
	int iServerCount = GetIntFromINI(MPPS_INI_SECTION_MPPS_SERVER_INFO, MPPS_INI_KEY_SERVER_COUNT);

	//<< 删除原有servers
	CString strSection;
	for (int i = 1; i <= iServerCount; i++)
	{
		strSection.Format(_T("%s%d"), MPPS_INI_SECTION_MPPS_SERVER, i);
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
		strSection.Format(_T("%s%d"), MPPS_INI_SECTION_MPPS_SERVER, i);

		if (!WriteKeyToINI(strSection, MPPS_INI_KEY_SERVER_CALLEDAE, (*pvtrServers)[i-1].strCalledAE))
		{
			return E_UNEXPECTED_ERROR;
		}

		if (!WriteKeyToINI(strSection, MPPS_INI_KEY_SERVER_IP, (*pvtrServers)[i-1].strIP))
		{
			return E_UNEXPECTED_ERROR;
		}

		if (!WriteKeyToINI(strSection, MPPS_INI_KEY_SERVER_PORT, (*pvtrServers)[i-1].strPort))
		{
			return E_UNEXPECTED_ERROR;
		}

		if (!WriteKeyToINI(strSection, MPPS_INI_KEY_SERVER_CALLINGAE, (*pvtrServers)[i-1].strCallingAE))
		{
			return E_UNEXPECTED_ERROR;
		}
		
		if (!WriteKeyToINI(strSection, MPPS_INI_KEY_SERVER_TIMEOUT, _T("20")))
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
	if (!WriteKeyToINI(MPPS_INI_SECTION_MPPS_SERVER_INFO, MPPS_INI_KEY_SERVER_COUNT, strValue))
	{
		return E_UNEXPECTED_ERROR;
	}

	strValue.Format(_T("%d"), iCurSel);
	if (!WriteKeyToINI(MPPS_INI_SECTION_MPPS_SERVER_INFO, MPPS_INI_KEY_SERVER_CUR_SEL, strValue))
	{
		return E_UNEXPECTED_ERROR;
	}

	return E_OK;

}