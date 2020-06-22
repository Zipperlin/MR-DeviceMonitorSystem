/* Time: <@(#)MPPSIniOpt.h   2009-3-5 - 10:48:22   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : MPPSIniOpt.h
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
 *	1	2009-3-5 - 10:48:22		FanZF	Creation
 *
 *********************************************************************
 */

// MPPSIniOpt.h: interface for the CMPPSIniOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPPSINIOPT_H__E606214E_6880_4D25_97BA_2381DC6D5F19__INCLUDED_)
#define AFX_MPPSINIOPT_H__E606214E_6880_4D25_97BA_2381DC6D5F19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IniOpt.h"

// Config file name
#define MPPS_INI_FILE_NAME							_T("MPPS.ini")

#define MPPS_INI_SECTION_MPPS_SERVER_INFO			_T("MPPS_Server_Info")
#define MPPS_INI_KEY_SERVER_COUNT					_T("ServerCount")
#define MPPS_INI_KEY_SERVER_CUR_SEL					_T("CurSel")

#define MPPS_INI_SECTION_MPPS_SERVER				_T("MPPS_Server")
#define MPPS_INI_KEY_SERVER_CALLEDAE				_T("CalledAE")
#define MPPS_INI_KEY_SERVER_IP						_T("IP")
#define MPPS_INI_KEY_SERVER_PORT					_T("Port")
#define MPPS_INI_KEY_SERVER_CALLINGAE				_T("CallingAE")
#define MPPS_INI_KEY_SERVER_TIMEOUT					_T("TimeOut")

#define MPPS_INI_SECTION_CREATE_INFORMATION			_T("MPPS_Create_Information")
// Scheduled Step Attribute Sequence
#define MPPS_INI_KEY_CREATE_INFO_SEQ_ITEMCOUNT		_T("Sequence_ItemCount")
#define MPPS_INI_KEY_CREATE_INFO_ITEMCOUNT			_T("ItemCount")

#define MPPS_INI_SECTION_SET_INFORMATION			_T("MPPS_Set_Information")
// Performed Series Sequence
#define MPPS_INI_KEY_SET_INFO_SEQ_ITEMCOUNT			_T("Sequence_ItemCount")
#define MPPS_INI_KEY_SET_INFO_ITEMCOUNT				_T("ItemCount")

#define MPPS_INI_SECTION_CREATE_SEQ_SUBITEM			_T("Create_Sequence_SubItem")
#define MPPS_INI_SECTION_CREATE_ITEM				_T("Create_Item")

#define MPPS_INI_SECTION_SET_SEQ_SUBITEM			_T("Set_Sequence_SubItem")
#define MPPS_INI_SECTION_SET_ITEM					_T("Set_Item")


#define MPPS_INI_KEY_GROUP							_T("group")
#define MPPS_INI_KEY_ELEMENT						_T("element")
#define MPPS_INI_KEY_NAME							_T("name")
#define MPPS_INI_KEY_VALUE							_T("value")
#define MPPS_INI_KEY_ISCHECK						_T("IsCheck")
#define MPPS_INI_KEY_TYPE							_T("type")


class CMPPSIniOpt : public CIniOpt  
{
public:
	virtual ~CMPPSIniOpt();

	static CMPPSIniOpt* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	void UnInit();

	int GetDefaultServer(NetworkNodeStruct* pNodeStruct);
	BOOL GetNCreateItems(vector<WLQueryItem>* pItems);
	BOOL GetNSetItems(vector<WLQueryItem>* pItems);

	INT GetServers(vector<NetworkNodeStruct>* pvtrServers);
	INT SetServers(vector<NetworkNodeStruct>* pvtrServers);

private:
	CMPPSIniOpt();

	BOOL GetItems(vector<WLQueryItem>* pItems, BOOL bNCreate);

	static CMPPSIniOpt*	m_pInstance;

};

#endif // !defined(AFX_MPPSINIOPT_H__E606214E_6880_4D25_97BA_2381DC6D5F19__INCLUDED_)
