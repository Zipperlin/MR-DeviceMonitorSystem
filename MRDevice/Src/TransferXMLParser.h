/* Time: <@(#)TransferXMLParser.h   2009-3-5 - 10:51:45   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : TransferXMLParser.h
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
 *	1	2009-3-5 - 10:51:45		FanZF	Creation
 *
 *********************************************************************
 */

// TransferXMLParser.h: interface for the CTransferXMLParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFERXMLPARSER_H__487F96B4_2DD0_4BC6_B869_BF02713B3054__INCLUDED_)
#define AFX_TRANSFERXMLPARSER_H__487F96B4_2DD0_4BC6_B869_BF02713B3054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "vector"
using namespace std;


// TransferSvrConfig
#define	TRANSFER_SVR_CONFIG_FILENAME					_T("TransferSvrConfig.xml")

#define TRANSFER_SVR_CONFIG_XML_TAG_MANUAL				_T("MANUAL")
#define TRANSFER_SVR_CONFIG_XML_TAG_AUTO				_T("AUTO")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_NUM			_T("number")

#define TRANSFER_SVR_CONFIG_XML_TAG_ITEM				_T("item")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_INDEX		_T("index")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SERVER		_T("server")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_ADDRESS		_T("address")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PORT			_T("port")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_HOST			_T("host")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_STATE		_T("state")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_RAW			_T("raw")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_PROC			_T("processed")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_NAME_SENDPS		_T("sendPS")
//自动发送状态  [ GaoXing 10/22/2009]
#define TRANSFER_SVR_CONFIG_XML_TAG_AUTOTRANSFERSTATUS	_T("AUTOTRANSFERSTATUS")
#define TRANSFER_SVR_CONFIG_XML_ATTRI_VALUE				_T("value")
//是否询问是否自动发送  [ GaoXing 1/11/2010]
#define TRANSFER_SVR_CONFIG_XML_TAG_ASKFORAUTOTRANSFER	_T("ASKFORAUTOTRANSFER")


class CTransferXMLParser  
{
public:
	CTransferXMLParser();
	virtual ~CTransferXMLParser();

	BOOL Init();
	BOOL UnInit();


	//<< 自动发送
	INT		GetAutoServers(vector<NetworkNodeStruct>* pvtrServers);
	INT		SetAutoServers(vector<NetworkNodeStruct>* pvtrServers);
	INT		GetDefaultAutoServers(vector<NetworkNodeStruct>* pvtrServers);


	//<< 手动发送
	INT		GetManualServers(vector<NetworkNodeStruct>* pvtrServers);
	INT		SetManualServers(vector<NetworkNodeStruct>* pvtrServers);
	INT		GetManualServer(LPCTSTR szServerCalledAE, NetworkNodeStruct* pServer);
	INT		SetManualServerState(NetworkNodeStruct* pServer);


	//设置、获取自动发送状态  [ GaoXing 10/22/2009]
	INT SetEnableAutoTransferStatus(BOOL bEnable);
	INT GetEnableAutoTransferStatus(BOOL *bEnable);

	//设置、获取是否询问用户自动发送  [ GaoXing 1/11/2010]
	INT SetAskforAutoTransfer(BOOL bAskfor);
	INT GetAskforAutoTransfer(BOOL *bAskfor);


private:
	INT		GetServers(BOOL bAuto, vector<NetworkNodeStruct>* pvtrServers);
	INT		SetServers(BOOL bAuto, vector<NetworkNodeStruct>* pvtrServers);
	INT		SetDefaultServer(BOOL bAuto, LPCTSTR szServerCalledAE, BOOL bDefault);
	INT		AddServer(BOOL bAuto, NetworkNodeStruct* pServer);
	INT		ModifyServer(BOOL bAuto, LPCTSTR szServerCalledAE, NetworkNodeStruct* pServer);
	INT		RemoveServer(BOOL bAuto, LPCTSTR szServerCalledAE);
	INT		RemoveAllServers(BOOL bAuto);

	BOOL	IsFileExist(LPCTSTR szFile);
	INT		InitXmlFile(CGenXml* pXml);

private:
//	NXMLArchive* m_xml;
	CString						m_strXmlFile;

	CCriticalSection			m_CSLock;
};

#endif // !defined(AFX_TRANSFERXMLPARSER_H__487F96B4_2DD0_4BC6_B869_BF02713B3054__INCLUDED_)
