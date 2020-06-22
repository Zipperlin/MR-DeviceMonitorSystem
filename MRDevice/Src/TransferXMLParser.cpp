/* Time: <@(#)TransferXMLParser.cpp   2009-3-5 - 10:52:15   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : TransferXMLParser.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : The operation class for Send .xml file
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:52:15		FanZF	Creation
 *
 *********************************************************************
 */

// TransferXMLParser.cpp: implementation of the CTransferXMLParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TransferXMLParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransferXMLParser::CTransferXMLParser()
{

}

CTransferXMLParser::~CTransferXMLParser()
{

}


BOOL CTransferXMLParser::Init()
{
	BOOL bRet = TRUE;
	TCHAR szBuffer[MAX_PATH] = {0};
	CString strTrace;

	DWORD dwRet = GetModuleFileName(NULL, szBuffer, MAX_PATH);
	if (0 != dwRet)
	{
		wchar_t* p = wcsrchr(szBuffer, _T('\\'));
		if (NULL != p)
		{
			*p = _T('\0');
			m_strXmlFile = szBuffer;
			m_strXmlFile += SYSTEM_CONFIG_DIR;
			m_strXmlFile += _T("\\");
			m_strXmlFile += TRANSFER_SVR_CONFIG_FILENAME;
		}
	}
	else
	{
		return FALSE;
	}

	///< 配置文件是否存在
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(m_strXmlFile, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		CString strTempbk = m_strXmlFile + _T(".bk");
		if (IsFileExist(strTempbk))
		{
			CopyFile(strTempbk,m_strXmlFile,FALSE);
			return TRUE;
		}
		else
		{
			strTrace.Format(_T("FindFirstFile(), szFile: %s"), m_strXmlFile);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
	}
	else
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
	}

	return TRUE;


// 	NXMLArchive xml;
// 	try
// 	{
// 		// Read config form the .xml
// 		if (xml.Open(szFile, FALSE))
// 		{
// 			if (xml.FindElem(_T("TRANSFERCONFIG")))
// 			{
// 				//AE LIST
// 				if (xml.FindChildElem(_T("AELIST")) && xml.IntoElem())
// 				{
// 					int num = xml.GetAttribInt(_T("number"));				
// 					for (int i=0; i<num; i++)
// 					{
// 						CString strItem;
// 						strItem.Format(_T("item%d"), i);
// 						if (xml.FindChildElem(strItem) && xml.IntoElem())
// 						{
// 							nns.strCalledAE = xml.GetAttrib(_T("server"));
// 							nns.strCallingAE = xml.GetAttrib(_T("host"));
// 							nns.strIP = xml.GetAttrib(_T("address"));
// 							nns.strPort = xml.GetAttrib(_T("port"));
// 
// 							if ((xml.GetAttribInt(_T("state")) == 1))
// 							{
// 								nns.bDefault = TRUE;	
// 							}
// 							else
// 							{
// 								nns.bDefault = FALSE;
// 							}
// 
// 							m_vtrNodes.push_back(nns);
// 
// 							xml.OutOfElem();
// 						}					
// 					}
// 					xml.OutOfElem();
// 				}
// 			}//end if
// 			xml.Close();
// 		}
// 		else
// 			return FALSE;
// 	}//end try
// 	catch (...)
// 	{
// 		PRINTTRACE_ERROR("CTransferXMLParser::Init()");
// 	}
// 
// 	return TRUE;
}

BOOL CTransferXMLParser::UnInit()
{
	return TRUE;
}


INT CTransferXMLParser::GetAutoServers(vector<NetworkNodeStruct>* pvtrServers)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	CString strTempbk = m_strXmlFile + _T(".bk");
	if (!IsFileExist(m_strXmlFile))
	{
		if (IsFileExist(strTempbk))
		{
			CopyFile(strTempbk,m_strXmlFile,FALSE);
		}
		else
		{
			return E_UNEXPECTED_ERROR;
		}
	}

	INT iErrCode = GetServers(TRUE, pvtrServers);

	sLock.Unlock();
	return iErrCode;
}

INT CTransferXMLParser::GetDefaultAutoServers(vector<NetworkNodeStruct>* pvtrServers)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		sLock.Unlock();
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;

	strTag = TRANSFER_SVR_CONFIG_XML_TAG_AUTO;

	///< 获得节点总数
	int iSvrCount = 0;
	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		sLock.Unlock();
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		iSvrCount = _ttoi(szData);
	}


	///< 寻找默认节点
	for (int i = 0; i < iSvrCount; i++)
	{
		
		CString strSubTag;
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);
		CString strAttriValue;

		///< Select state
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
			PRINTTRACE_ERROR(strTrace)
			sLock.Unlock();
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			strAttriValue = szData;
			if (!strAttriValue.Compare(_T("1")))
			{
				//<< 找到默认节点
				NetworkNodeStruct nns;
				nns.bDefault = TRUE;

				///< ServerAE
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					nns.strCalledAE = szData;
				}

				///< ServerIP
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					nns.strIP = szData;
				}

				///< ServerPort
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					nns.strPort = szData;
				}

				///< HostAE
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					nns.strCallingAE = szData;
				}

				///< Raw
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					strAttriValue = szData;
					if (!strAttriValue.Compare(_T("1")))
					{
						nns.bRaw = TRUE;
					}
					else
					{
						nns.bRaw = FALSE;
					}
				}

				///< Processed
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					strAttriValue = szData;
					if (!strAttriValue.Compare(_T("1")))
					{
						nns.bProcessed = TRUE;
					}
					else
					{
						nns.bProcessed = FALSE;
					}
				}
				
				// Add [Sun hongwen 10/16/2009]
				///< SendPS
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS);
					PRINTTRACE_ERROR(strTrace)
						return E_UNEXPECTED_ERROR;
				}
				else
				{
					strAttriValue = szData;
					if (!strAttriValue.Compare(_T("1")))
					{
						nns.bSendPS = TRUE;
					}
					else
					{
						nns.bSendPS = FALSE;
					}
				}
				
				pvtrServers->push_back(nns);
			}
			else
			{
				continue;
			}
		}

	}

	//<< 没有默认节点
	sLock.Unlock();
	return E_OK;
}

INT CTransferXMLParser::SetAutoServers(vector<NetworkNodeStruct>* pvtrServers)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	CString strTempbk = m_strXmlFile + _T(".bk");
	if (!IsFileExist(m_strXmlFile))
	{
		if (IsFileExist(strTempbk))
		{
			CopyFile(strTempbk,m_strXmlFile,FALSE);
		}
		else
		{
			return E_UNEXPECTED_ERROR;
		}
	}
	else
	{
		if (IsFileExist(strTempbk))
		{
			::DeleteFile(strTempbk);
		}
		CopyFile(m_strXmlFile,strTempbk,FALSE);
	}	

	INT iErrCode = SetServers(TRUE, pvtrServers);

	if (E_OK != iErrCode)
	{
		 _wrename(strTempbk,m_strXmlFile);
	}
	else
	{
		CopyFile(m_strXmlFile,strTempbk,FALSE);
	}

	sLock.Unlock();
	return iErrCode;
}

INT CTransferXMLParser::GetManualServers(vector<NetworkNodeStruct>* pvtrServers)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	CString strTempbk = m_strXmlFile + _T(".bk");
	if (!IsFileExist(m_strXmlFile))
	{
		if (IsFileExist(strTempbk))
		{
			CopyFile(strTempbk,m_strXmlFile,FALSE);
		}
		else
		{
			return E_UNEXPECTED_ERROR;
		}
	}

	INT iErrCode = GetServers(FALSE, pvtrServers);

	sLock.Unlock();
	return iErrCode;
}

INT CTransferXMLParser::GetManualServer(LPCTSTR szServerCalledAE, NetworkNodeStruct* pServer)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		sLock.Unlock();
		return iErrCode;
	}


	CString strServerSalledAE = szServerCalledAE;
	LPCWSTR szData;
	CString strTag;

	strTag = TRANSFER_SVR_CONFIG_XML_TAG_MANUAL;

	///< 获得节点总数
	int iSvrCount = 0;
	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		sLock.Unlock();
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		iSvrCount = _ttoi(szData);
	}


	///< 寻找指定节点
	for (int i = 0; i < iSvrCount; i++)
	{
		
		CString strSubTag;
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);
		CString strAttriValue;

		///< ServerAE
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
			PRINTTRACE_ERROR(strTrace)
			sLock.Unlock();
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			if (!strServerSalledAE.Compare(szData))
			{
				//<< 找到指定节点
				pServer->strCalledAE = szData;

				///< ServerIP
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					pServer->strIP = szData;
				}

				///< ServerPort
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					pServer->strPort = szData;
				}

				///< HostAE
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					pServer->strCallingAE = szData;
				}

				///< Raw
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					strAttriValue = szData;
					if (!strAttriValue.Compare(_T("1")))
					{
						pServer->bRaw = TRUE;
					}
					else
					{
						pServer->bRaw = FALSE;
					}
				}

				///< Processed
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					strAttriValue = szData;
					if (!strAttriValue.Compare(_T("1")))
					{
						pServer->bProcessed = TRUE;
					}
					else
					{
						pServer->bProcessed = FALSE;
					}
				}
				
				// Add [Sun hongwen 10/16/2009]
				///< SendPS
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS);
					PRINTTRACE_ERROR(strTrace)
						return E_UNEXPECTED_ERROR;
				}
				else
				{
					strAttriValue = szData;
					if (!strAttriValue.Compare(_T("1")))
					{
						pServer->bSendPS = TRUE;
					}
					else
					{
						pServer->bSendPS = FALSE;
					}
				}
				
				///< Select state
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					strAttriValue = szData;
					if (!strAttriValue.Compare(_T("1")))
					{
						pServer->bDefault = TRUE;
					}
					else
					{
						pServer->bDefault = FALSE;
					}
				}

				sLock.Unlock();
				return E_OK;
			}
			else
			{
				continue;
			}
		}

	}

	//<< 没有指定节点
	sLock.Unlock();
	return E_UNEXPECTED_ERROR;
}

INT CTransferXMLParser::SetManualServers(vector<NetworkNodeStruct>* pvtrServers)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	CString strTempbk = m_strXmlFile + _T(".bk");
	if (!IsFileExist(m_strXmlFile))
	{
		if (IsFileExist(strTempbk))
		{
			CopyFile(strTempbk,m_strXmlFile,FALSE);
		}
		else
		{
			return E_UNEXPECTED_ERROR;
		}
	}
	else
	{
		if (IsFileExist(strTempbk))
		{
			::DeleteFile(strTempbk);
		}
		CopyFile(m_strXmlFile,strTempbk,FALSE);
	}

	INT iErrCode = SetServers(FALSE, pvtrServers);

	if (E_OK != iErrCode)
	{
		 _wrename(strTempbk,m_strXmlFile);
	}
	else
	{
		CopyFile(m_strXmlFile,strTempbk,FALSE);
	}
	
	sLock.Unlock();
	return iErrCode;
}

INT CTransferXMLParser::SetManualServerState(NetworkNodeStruct* pServer)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;
	CString strServerCalledAE = pServer->strCalledAE;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		sLock.Unlock();
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;

	strTag = TRANSFER_SVR_CONFIG_XML_TAG_MANUAL;


	///< 获得节点总数
	int iSvrCount = 0;
	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		sLock.Unlock();
		return FALSE;
	}
	else
	{
		iSvrCount = _ttoi(szData);
	}

	BOOL bServerExist = FALSE;

	///< 找到指定节点并设置
	for (int i = 0; i < iSvrCount; i++)
	{
		
		CString strSubTag;
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);

		///< ServerAE
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
			PRINTTRACE_ERROR(strTrace)
			sLock.Unlock();
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			if (!strServerCalledAE.Compare(szData))
			{
				bServerExist = TRUE;

				//<< 修改
				CString strAttriValue;

				//<< state
				if (pServer->bDefault)
				{
					strAttriValue = _T("1");
				}
				else
				{
					strAttriValue = _T("0");
				}

				if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, strAttriValue))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.strAttriValue(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
					PRINTTRACE_ERROR(strTrace)
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}

				//<< raw
				if (pServer->bRaw)
				{
					strAttriValue = _T("1");
				}
				else
				{
					strAttriValue = _T("0");
				}

				if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW, strAttriValue))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.strAttriValue(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW);
					PRINTTRACE_ERROR(strTrace)
						sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				
				//<< processed
				if (pServer->bProcessed)
				{
					strAttriValue = _T("1");
				}
				else
				{
					strAttriValue = _T("0");
				}
				
				if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC, strAttriValue))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.strAttriValue(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC);
					PRINTTRACE_ERROR(strTrace)
						sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}
				
				
				// Add [Sun hongwen 10/16/2009]
				//<< SendPS
				if (pServer->bSendPS)
				{
					strAttriValue = _T("1");
				}
				else
				{
					strAttriValue = _T("0");
				}
				if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS, strAttriValue))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS);
					PRINTTRACE_ERROR(strTrace)
						return E_UNEXPECTED_ERROR;
				}
				
				//<< 设置完毕
				if (xml.GenXmlSave())
				{
					sLock.Unlock();
					return E_OK;
				}
				else
				{
					PRINTTRACE_ERROR("xml.GenXmlSave()")
					sLock.Unlock();
					return E_UNEXPECTED_ERROR;
				}

			}
		}
	}

	sLock.Unlock();
	return E_UNEXPECTED_ERROR;

// 	if (bServerExist)
// 	{
// 		if (pServer->bDefault)
// 		{
// 			//<< 将其他节点的state都设为0
// 			for (int i = 0; i < iSvrCount; i++)
// 			{
// 				CString strSubTag;
// 				strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);
// 
// 				///< ServerAE
// 				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
// 				{
// 					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
// 					PRINTTRACE_ERROR(strTrace)
// 					sLock.Unlock();
// 					return E_UNEXPECTED_ERROR;
// 				}
// 				else
// 				{
// 					if (strServerCalledAE.Compare(szData))
// 					{
// 						//<< 修改state
// 						CString strAttriValue = _T("0");
// 						if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, strAttriValue))
// 						{
// 							strTrace.Format(_T("enumXmlAxOK != xml.strAttriValue(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
// 							PRINTTRACE_ERROR(strTrace)
// 							sLock.Unlock();
// 							return E_UNEXPECTED_ERROR;
// 						}
// 
// 					}
// 				}
// 			}
// 
// 		}
// 
// 		if (xml.GenXmlSave())
// 		{
// 			sLock.Unlock();
// 			return E_OK;
// 		}
// 		else
// 		{
// 			PRINTTRACE_ERROR("xml.GenXmlSave()")
// 			sLock.Unlock();
// 			return E_UNEXPECTED_ERROR;
// 		}
// 	}
// 	else
// 	{
// 		sLock.Unlock();
// 		return E_UNEXPECTED_ERROR;
// 	}
}


INT CTransferXMLParser::GetServers(BOOL bAuto, vector<NetworkNodeStruct>* pvtrServers)
{
	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;
	if (bAuto)
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_AUTO;
	}
	else
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_MANUAL;
	}

	///< 获得节点总数
	int iSvrCount = 0;
	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		iSvrCount = _ttoi(szData);
	}

	pvtrServers->clear();

	///< 读取节点列表
	for (int i = 0; i < iSvrCount; i++)
	{
		NetworkNodeStruct nns;
		
		CString strSubTag;
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);
		CString strAttriValue;

		///< ServerAE
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strCalledAE = szData;
		}

		///< ServerIP
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strIP = szData;
		}

		///< ServerPort
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strPort = szData;
		}

		///< HostAE
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			nns.strCallingAE = szData;
		}

		///< Select state
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			strAttriValue = szData;
			if (!strAttriValue.Compare(_T("1")))
			{
				nns.bDefault = TRUE;
			}
			else
			{
				nns.bDefault = FALSE;
			}
		}

		///< Raw
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			strAttriValue = szData;
			if (!strAttriValue.Compare(_T("1")))
			{
				nns.bRaw = TRUE;
			}
			else
			{
				nns.bRaw = FALSE;
			}
		}

		///< Processed
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			strAttriValue = szData;
			if (!strAttriValue.Compare(_T("1")))
			{
				nns.bProcessed = TRUE;
			}
			else
			{
				nns.bProcessed = FALSE;
			}
		}
		
		// Add [Sun hongwen 10/16/2009]
		///< SendPS
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			strAttriValue = szData;
			if (!strAttriValue.Compare(_T("1")))
			{
				nns.bSendPS = TRUE;
			}
			else
			{
				nns.bSendPS = FALSE;
			}
		}

		pvtrServers->push_back(nns);
	}

	return E_OK;
}

INT	CTransferXMLParser::SetServers(BOOL bAuto, vector<NetworkNodeStruct>* pvtrServers)
{
	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;
	CString strAttriValue;
	CString strSubTag;

	if (bAuto)
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_AUTO;
	}
	else
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_MANUAL;
	}

	///< 获得节点总数
	int iSvrCount = 0;
	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		iSvrCount = _ttoi(szData);
	}

	//<< 删除所有节点
	for (int i = 0; i < iSvrCount; i++)
	{
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);
		if (enumXmlAxOK != xml.GenDelXmlTag(strSubTag))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenDelXmlTag(), %s"), strSubTag);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
	}

	//<< 添加新的节点
	for (i = 0; i < pvtrServers->size(); i++)
	{
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);

		///< ServerAE
		if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, (*pvtrServers)[i].strCalledAE))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}

		///< ServerIP
		if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS, (*pvtrServers)[i].strIP))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}

		///< ServerPort
		if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT, (*pvtrServers)[i].strPort))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}

		///< HostAE
		if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST, (*pvtrServers)[i].strCallingAE))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}

		///< state
		if ((*pvtrServers)[i].bDefault)
		{
			strAttriValue = _T("1");
		}
		else
		{
			strAttriValue = _T("0");
		}
		if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, strAttriValue))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}

		//<< Raw
		if ((*pvtrServers)[i].bRaw)
		{
			strAttriValue = _T("1");
		}
		else
		{
			strAttriValue = _T("0");
		}
		if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW, strAttriValue))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}

		//<< processed
		if ((*pvtrServers)[i].bProcessed)
		{
			strAttriValue = _T("1");
		}
		else
		{
			strAttriValue = _T("0");
		}
		if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC, strAttriValue))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}

		// Add [Sun hongwen 10/16/2009]
		//<< SendPS
		if ((*pvtrServers)[i].bSendPS)
		{
			strAttriValue = _T("1");
		}
		else
		{
			strAttriValue = _T("0");
		}
		if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS, strAttriValue))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
	}

	//<< 修改节点数
	strAttriValue.Format(_T("%d"), pvtrServers->size());
	if (enumXmlAxOK != xml.GenWriteXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, strAttriValue))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	if (xml.GenXmlSave())
	{
		return E_OK;
	}
	else
	{
		PRINTTRACE_ERROR("xml.GenXmlSave()")
		return E_UNEXPECTED_ERROR;
	}
}

INT	CTransferXMLParser::SetDefaultServer(BOOL bAuto, LPCTSTR szServerCalledAE, BOOL bDefault)
{
	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;
	CString strServerCalledAE = szServerCalledAE;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;
	if (bAuto)
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_AUTO;
	}
	else
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_MANUAL;
	}

	///< 获得节点总数
	int iSvrCount = 0;
	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
	else
	{
		iSvrCount = _ttoi(szData);
	}

	BOOL bServerExist = FALSE;

	///< 找到指定节点并设置其state
	for (int i = 0; i < iSvrCount; i++)
	{
		
		CString strSubTag;
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);

		///< ServerAE
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
		else
		{
			if (!strServerCalledAE.Compare(szData))
			{
				bServerExist = TRUE;

				//<< 修改state
				CString strAttriValue;
				if (bDefault)
				{
					strAttriValue = _T("1");
				}
				else
				{
					strAttriValue = _T("0");
				}

				if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, strAttriValue))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.strAttriValue(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
					PRINTTRACE_ERROR(strTrace)
					return E_UNEXPECTED_ERROR;
				}

				break;
			}
		}
	}

	if (bServerExist)
	{
		if (bDefault)
		{
			//<< 将其他节点的state都设为0
			for (int i = 0; i < iSvrCount; i++)
			{
				CString strSubTag;
				strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);

				///< ServerAE
				if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
					PRINTTRACE_ERROR(strTrace)
					return E_UNEXPECTED_ERROR;
				}
				else
				{
					if (strServerCalledAE.Compare(szData))
					{
						//<< 修改state
						CString strAttriValue = _T("0");
						if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, strAttriValue))
						{
							strTrace.Format(_T("enumXmlAxOK != xml.strAttriValue(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
							PRINTTRACE_ERROR(strTrace)
							return E_UNEXPECTED_ERROR;
						}

					}
				}
			}

		}

		if (xml.GenXmlSave())
		{
			return E_OK;
		}
		else
		{
			PRINTTRACE_ERROR("xml.GenXmlSave()")
			return E_UNEXPECTED_ERROR;
		}
	}
	else
	{
		return E_UNEXPECTED_ERROR;
	}
}

INT	CTransferXMLParser::AddServer(BOOL bAuto, NetworkNodeStruct* pServer)
{
	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;
	CString strAttriValue;
	CString strSubTag;

	if (bAuto)
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_AUTO;
	}
	else
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_MANUAL;
	}

	///< 获得节点总数
	int iSvrCount = 0;
	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		iSvrCount = _ttoi(szData);
	}

	//<< 判断新的节点CalledAE不存在，且state不冲突
	BOOL bCalledAEOK = TRUE;
	BOOL bStateOK = TRUE;
	for (int i = 0; i < iSvrCount; i++)
	{
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);

		///< ServerAE
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}

		if (!pServer->strCalledAE.Compare(szData))
		{
			bCalledAEOK = FALSE;
			break;
		}

		if (pServer->bDefault)
		{
			//<< state
			if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, szData))
			{
				strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
				PRINTTRACE_ERROR(strTrace)
				return E_UNEXPECTED_ERROR;
			}
			else
			{
				if (!CString(_T("1")).Compare(szData))
				{
					bStateOK = FALSE;
					break;
				}
			}
		}
	}

	if (!bCalledAEOK || !bStateOK)
	{
		return E_UNEXPECTED_ERROR;
	}

	//<< 新的节点数
	strAttriValue.Format(_T("%d"), iSvrCount+1);
	if (enumXmlAxOK != xml.GenWriteXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	///< 添加节点
		
	strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, iSvrCount);

	///< ServerAE
	if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, pServer->strCalledAE))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	///< ServerIP
	if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS, pServer->strIP))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	///< ServerPort
	if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT, pServer->strPort))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	///< HostAE
	if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST, pServer->strCallingAE))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	///< state
	if (pServer->bDefault)
	{
		strAttriValue = _T("1");
	}
	else
	{
		strAttriValue = _T("0");
	}
	if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, strAttriValue))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}


	if (xml.GenXmlSave())
	{
		return E_OK;
	}
	else
	{
		PRINTTRACE_ERROR("xml.GenXmlSave()")
		return E_UNEXPECTED_ERROR;
	}
}

INT	CTransferXMLParser::ModifyServer(BOOL bAuto, LPCTSTR szServerCalledAE, NetworkNodeStruct* pServer)
{
	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		return iErrCode;
	}


	CString strServerCalledAE = szServerCalledAE;
	LPCWSTR szData;
	CString strTag;
	CString strAttriValue;
	CString strSubTag;

	if (bAuto)
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_AUTO;
	}
	else
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_MANUAL;
	}

	///< 获得节点总数
	int iSvrCount = 0;
	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		iSvrCount = _ttoi(szData);
	}

	//<< 判断新的节点CalledAE不存在，且state不冲突
	BOOL bCalledAEOK = TRUE;
	BOOL bStateOK = TRUE;
	int iDstItem = -1;
	for (int i = 0; i < iSvrCount; i++)
	{
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);

		///< ServerAE
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}

		//<<当前的和要修改的是否同一item
		if (!strServerCalledAE.Compare(szData))
		{
			iDstItem = i;
			continue;
		}

		if (!pServer->strCalledAE.Compare(szData))
		{
			bCalledAEOK = FALSE;
			break;
		}

		if (pServer->bDefault)
		{
			//<< state
			if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, szData))
			{
				strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
				PRINTTRACE_ERROR(strTrace)
				return E_UNEXPECTED_ERROR;
			}
			else
			{
				if (!CString(_T("1")).Compare(szData))
				{
					bStateOK = FALSE;
					break;
				}
			}
		}
	}

	if (iDstItem = -1)
	{
		//<< 未找到目标item
		return E_UNEXPECTED_ERROR;
	}

	if (!bCalledAEOK || !bStateOK)
	{
		return E_UNEXPECTED_ERROR;
	}

	//<<< 修改此节点

	strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, iDstItem);

	///< ServerAE
	if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, pServer->strCalledAE))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	///< ServerIP
	if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS, pServer->strIP))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	///< ServerPort
	if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT, pServer->strPort))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	///< HostAE
	if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST, pServer->strCallingAE))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	///< state
	if (pServer->bDefault)
	{
		strAttriValue = _T("1");
	}
	else
	{
		strAttriValue = _T("0");
	}
	if (enumXmlAxOK != xml.GenWriteXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, strAttriValue))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}


	if (xml.GenXmlSave())
	{
		return E_OK;
	}
	else
	{
		PRINTTRACE_ERROR("xml.GenXmlSave()")
		return E_UNEXPECTED_ERROR;
	}
	
}

INT	CTransferXMLParser::RemoveServer(BOOL bAuto, LPCTSTR szServerCalledAE)
{
	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		return iErrCode;
	}


	CString strServerCalledAE = szServerCalledAE;
	LPCWSTR szData;
	CString strTag;
	CString strAttriValue;
	CString strSubTag;

	if (bAuto)
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_AUTO;
	}
	else
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_MANUAL;
	}

	///< 获得节点总数
	int iSvrCount = 0;
	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		iSvrCount = _ttoi(szData);
	}

	//<< 找到该节点并处理
	for (int i = 0; i < iSvrCount; i++)
	{
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);

		///< ServerAE
		if (enumXmlAxOK != xml.GenReadXml(strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}

		if (!strServerCalledAE.Compare(szData))
		{
			//<<已找到该节点
			//<<若是最后一个节点，删除之
			if (i == iSvrCount-1)
			{
				if (enumXmlAxOK != xml.GenDelXmlTag(strSubTag))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenDelXmlTag(), %s"), strSubTag);
					PRINTTRACE_ERROR(strTrace)
					return E_UNEXPECTED_ERROR;
				}
			}
			else
			{
				//<< 将后面每个节点的item id 减一
				for (int j = i+1; j < iSvrCount; j++)
				{
					NetworkNodeStruct nns;
					CString strSubTagOld, strSubTagNew;
					strSubTagOld.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, j);
					strSubTagNew.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, j-1);

					///< ServerAE
					if (enumXmlAxOK != xml.GenReadXml(strSubTagOld, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
					{
						strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTagOld, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
						PRINTTRACE_ERROR(strTrace)
						return E_UNEXPECTED_ERROR;
					}
					else
					{
						if (enumXmlAxOK != xml.GenWriteXml(strSubTagNew, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER, szData))
						{
							strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTagNew, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER);
							PRINTTRACE_ERROR(strTrace)
							return E_UNEXPECTED_ERROR;
						}
					}

					///< ServerIP
					if (enumXmlAxOK != xml.GenReadXml(strSubTagOld, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS, szData))
					{
						strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTagOld, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS);
						PRINTTRACE_ERROR(strTrace)
						return E_UNEXPECTED_ERROR;
					}
					else
					{
						if (enumXmlAxOK != xml.GenWriteXml(strSubTagNew, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS, szData))
						{
							strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTagNew, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS);
							PRINTTRACE_ERROR(strTrace)
							return E_UNEXPECTED_ERROR;
						}
					}

					///< ServerPort
					if (enumXmlAxOK != xml.GenReadXml(strSubTagOld, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT, szData))
					{
						strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTagOld, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT);
						PRINTTRACE_ERROR(strTrace)
						return E_UNEXPECTED_ERROR;
					}
					else
					{
						if (enumXmlAxOK != xml.GenWriteXml(strSubTagNew, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT, szData))
						{
							strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTagNew, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT);
							PRINTTRACE_ERROR(strTrace)
							return E_UNEXPECTED_ERROR;
						}
					}

					///< HostAE
					if (enumXmlAxOK != xml.GenReadXml(strSubTagOld, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST, szData))
					{
						strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTagOld, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST);
						PRINTTRACE_ERROR(strTrace)
						return E_UNEXPECTED_ERROR;
					}
					else
					{
						if (enumXmlAxOK != xml.GenWriteXml(strSubTagNew, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST, szData))
						{
							strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTagNew, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST);
							PRINTTRACE_ERROR(strTrace)
							return E_UNEXPECTED_ERROR;
						}
					}

					///< Select state
					if (enumXmlAxOK != xml.GenReadXml(strSubTagOld, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, szData))
					{
						strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strSubTagOld, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
						PRINTTRACE_ERROR(strTrace)
						return E_UNEXPECTED_ERROR;
					}
					else
					{
						if (enumXmlAxOK != xml.GenWriteXml(strSubTagNew, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE, szData))
						{
							strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strSubTagNew, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE);
							PRINTTRACE_ERROR(strTrace)
							return E_UNEXPECTED_ERROR;
						}
					}
				}

				//<< 删除item id为iSvrCount-1 的节点
				strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, iSvrCount-1);
				if (enumXmlAxOK != xml.GenDelXmlTag(strSubTag))
				{
					strTrace.Format(_T("enumXmlAxOK != xml.GenDelXmlTag(), %s"), strSubTag);
					PRINTTRACE_ERROR(strTrace)
					return E_UNEXPECTED_ERROR;
				}
			}


			//<< 修改节点数
			strAttriValue.Format(_T("%d"), iSvrCount-1);
			if (enumXmlAxOK != xml.GenWriteXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
			{
				strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
				PRINTTRACE_ERROR(strTrace)
				return E_UNEXPECTED_ERROR;
			}

			if (xml.GenXmlSave())
			{
				return E_OK;
			}
			else
			{
				PRINTTRACE_ERROR("xml.GenXmlSave()")
				return E_UNEXPECTED_ERROR;
			}
		}
	}

	return E_UNEXPECTED_ERROR;
}

INT	CTransferXMLParser::RemoveAllServers(BOOL bAuto)
{
	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;
	CString strAttriValue;
	CString strSubTag;

	if (bAuto)
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_AUTO;
	}
	else
	{
		strTag = TRANSFER_SVR_CONFIG_XML_TAG_MANUAL;
	}

	///< 获得节点总数
	int iSvrCount = 0;
	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		iSvrCount = _ttoi(szData);
	}

	//<< 删除所有节点
	for (int i = 0; i < iSvrCount; i++)
	{
		strSubTag.Format(_T("%s\\%s%d"), strTag, TRANSFER_SVR_CONFIG_XML_TAG_ITEM, i);
		if (enumXmlAxOK != xml.GenDelXmlTag(strSubTag))
		{
			strTrace.Format(_T("enumXmlAxOK != xml.GenDelXmlTag(), %s"), strSubTag);
			PRINTTRACE_ERROR(strTrace)
			return E_UNEXPECTED_ERROR;
		}
	}

	//<< 修改节点数
	strAttriValue.Format(_T("%d"), 0);
	if (enumXmlAxOK != xml.GenWriteXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM, strAttriValue))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}

	if (xml.GenXmlSave())
	{
		return E_OK;
	}
	else
	{
		PRINTTRACE_ERROR("xml.GenXmlSave()")
		return E_UNEXPECTED_ERROR;
	}

}

BOOL CTransferXMLParser::IsFileExist(LPCTSTR szFile)
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

INT	CTransferXMLParser::InitXmlFile(CGenXml* pXml)
{
	CString strTrace;

	if (!IsFileExist(m_strXmlFile))
	{
		return E_SEND_CONFIG_FILE_NOT_EXIST;
	}

	if (!pXml->GenXmlIni(m_strXmlFile))
	{
		strTrace.Format(_T("xml.GenXmlIni(szFile), szFile: %s"), m_strXmlFile);
		PRINTTRACE_ERROR(strTrace)
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		return E_OK;
	}

}

//设置自动发送状态  [ GaoXing 10/22/2009]
INT CTransferXMLParser::SetEnableAutoTransferStatus(BOOL bEnable)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;


	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		sLock.Unlock();
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;

	strTag = TRANSFER_SVR_CONFIG_XML_TAG_AUTOTRANSFERSTATUS;

	if (bEnable)
	{
		szData = _T("1");
	}
	else
	{
		szData = _T("0");
	}

	if (enumXmlAxOK != xml.GenWriteXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_VALUE, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_VALUE);
		PRINTTRACE_ERROR(strTrace)
		sLock.Unlock();
		return E_UNEXPECTED_ERROR;
	}

	if (xml.GenXmlSave())
	{
		sLock.Unlock();
		return E_OK;
	}
	else
	{
		PRINTTRACE_ERROR("xml.GenXmlSave()")
		sLock.Unlock();
		return E_UNEXPECTED_ERROR;
	}
}

//获取自动发送状态  [ GaoXing 10/22/2009]
INT CTransferXMLParser::GetEnableAutoTransferStatus(BOOL *bEnable)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		sLock.Unlock();
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;

	int nAttributeEnable = 0;
	strTag = TRANSFER_SVR_CONFIG_XML_TAG_AUTOTRANSFERSTATUS;

	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_VALUE, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_VALUE);
		PRINTTRACE_ERROR(strTrace)
		sLock.Unlock();
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		nAttributeEnable = _ttoi(szData);
		if (nAttributeEnable == 1)
		{
			*bEnable = TRUE;
		}
		else
		{
			*bEnable = FALSE;
		}
	}

	sLock.Unlock();
	return E_OK;
}


//设置是否询问用户进行自动发送 [ GaoXing 1/11/2010]
INT CTransferXMLParser::SetAskforAutoTransfer(BOOL bAskfor)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();
	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;


	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		sLock.Unlock();
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;

	strTag = TRANSFER_SVR_CONFIG_XML_TAG_ASKFORAUTOTRANSFER;
	if (bAskfor)
	{
		szData = _T("1");
	}
	else
	{
		szData = _T("0");
	}

	if (enumXmlAxOK != xml.GenWriteXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_VALUE, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenWriteXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_VALUE);
		PRINTTRACE_ERROR(strTrace)
		sLock.Unlock();
		return E_UNEXPECTED_ERROR;
	}

	if (xml.GenXmlSave())
	{
		sLock.Unlock();
		return E_OK;
	}
	else
	{
		PRINTTRACE_ERROR("xml.GenXmlSave()")
		sLock.Unlock();
		return E_UNEXPECTED_ERROR;
	}
}



//获取是否询问用户自动发送 [ GaoXing 1/11/2010]
INT CTransferXMLParser::GetAskforAutoTransfer(BOOL *bAskfor)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	CString strTrace;

	CGenXml xml;
	INT iErrCode = E_OK;

	iErrCode = InitXmlFile(&xml);
	if (E_OK != iErrCode)
	{
		sLock.Unlock();
		return iErrCode;
	}


	LPCWSTR szData;
	CString strTag;

	int nAttributeEnable = 0;
	strTag = TRANSFER_SVR_CONFIG_XML_TAG_ASKFORAUTOTRANSFER;

	if (enumXmlAxOK != xml.GenReadXml(strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_VALUE, szData))
	{
		strTrace.Format(_T("enumXmlAxOK != xml.GenReadXml(), %s, %s"), strTag, TRANSFER_SVR_CONFIG_XML_ATTRI_VALUE);
		PRINTTRACE_ERROR(strTrace)
		sLock.Unlock();
		return E_UNEXPECTED_ERROR;
	}
	else
	{
		nAttributeEnable = _ttoi(szData);
		if (nAttributeEnable == 1)
		{
			*bAskfor = TRUE;
		}
		else
		{
			*bAskfor = FALSE;
		}
	}

	sLock.Unlock();
	return E_OK;
}