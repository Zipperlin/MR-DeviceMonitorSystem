/* Time: <@(#)WorklistIniOpt.h   2009-3-5 - 10:52:51   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : WorklistIniOpt.h
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
 *	1	2009-3-5 - 10:52:51		FanZF	Creation
 *
 *********************************************************************
 */

// WorklistIniOpt.h: interface for the CWorklistIniOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKLISTINIOPT_H__CD6F1F63_8F5C_40FC_B1C2_82813453AF7E__INCLUDED_)
#define AFX_WORKLISTINIOPT_H__CD6F1F63_8F5C_40FC_B1C2_82813453AF7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IniOpt.h"

// Config file name
#define WORKLIST_INI_FILE_NAME					_T("Worklist.ini")

#define WORKLIST_INI_SECTION_WL_SERVER_INFO		_T("WorkList_Server_Info")
#define WORKLIST_INI_KEY_SERVER_COUNT			_T("ServerCount")
#define WORKLIST_INI_KEY_SERVER_CUR_SEL			_T("CurSel")

#define WORKLIST_INI_SECTION_WL_SERVER			_T("WorkList_Server")
#define WORKLIST_INI_KEY_SERVER_CALLEDAE		_T("CalledAE")
#define WORKLIST_INI_KEY_SERVER_IP				_T("IP")
#define WORKLIST_INI_KEY_SERVER_PORT			_T("Port")
#define WORKLIST_INI_KEY_SERVER_CALLINGAE		_T("CallingAE")
#define WORKLIST_INI_KEY_SERVER_TIMEOUT			_T("TimeOut")


#define WORKLIST_INI_SECTION_INFORMATION		_T("Information")
#define WORKLIST_INI_KEY_INFO_SPSSS_ITEMCOUNT	_T("Scheduled_Procedure_Step_Sequence_ItemCount")
#define WORKLIST_INI_KEY_INFO_ITEMCOUNT			_T("ItemCount")


#define WORKLIST_INI_SECTION_SPSSS				_T("Scheduled_Procedure_Step_Sequence_SubItem")
#define WORKLIST_INI_SECTION_ITEM				_T("Item")
#define WORKLIST_INI_KEY_GROUP					_T("group")
#define WORKLIST_INI_KEY_ELEMENT				_T("element")
#define WORKLIST_INI_KEY_NAME					_T("name")
#define WORKLIST_INI_KEY_VALUE					_T("value")
#define WORKLIST_INI_KEY_ISCHECK				_T("IsCheck")






class CWorklistIniOpt : public CIniOpt  
{
public:
	virtual ~CWorklistIniOpt();

	static CWorklistIniOpt* GetInstance();
	void ReleaseInstance();

	BOOL Init();
	void UnInit();

	int GetDefaultWorklistServer(NetworkNodeStruct* pNodeStruct);
	BOOL GetQueryItemList(vector<WLQueryItem>* pWLQueryItemList);

	INT GetServers(vector<NetworkNodeStruct>* pvtrServers);
	INT SetServers(vector<NetworkNodeStruct>* pvtrServers);

private:
	CWorklistIniOpt();
	
	static CWorklistIniOpt*	m_pInstance;

};

#endif // !defined(AFX_WORKLISTINIOPT_H__CD6F1F63_8F5C_40FC_B1C2_82813453AF7E__INCLUDED_)
