/* Time: <@(#)DBDatabaseOpt.cpp   2009-3-26 - 15:31:36   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DBDatabaseOpt.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-26
 *
 *  Description : Data base operation
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-26 - 15:31:36		FanZF	Creation
 *
 *********************************************************************
 */

// DBDatabaseOpt.cpp: implementation of the DBDatabaseOpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DBDatabaseOpt.h"
#include "afxdao.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//初始化单件指针
DBDatabaseOpt *DBDatabaseOpt::m_pInstance = NULL;

DBDatabaseOpt::DBDatabaseOpt()
{
	m_pDb = NULL;
	m_szCurrentDbPath = "";
}

DBDatabaseOpt::~DBDatabaseOpt()
{

}

DBDatabaseOpt * DBDatabaseOpt::GetInstance()
{
	if( NULL == m_pInstance )
	{
        try
		{
			m_pInstance = new DBDatabaseOpt();
		}
		catch(...)
		{
			return NULL;
		}
	}

	return m_pInstance;
}

CADODatabase * DBDatabaseOpt::GetDBObject()
{
    return m_pDb;
}

CString DBDatabaseOpt::GetDBPath()
{
    return m_szCurrentDbPath;
}

BOOL DBDatabaseOpt::OpenDB(const BSTR bstDBPath, const BSTR bstPassword)
{
	//TRACE_ENTER_FUNC(OpenDB);
	CString szDBPath("");
	CString szPassword("");
	szDBPath = _com_util::ConvertBSTRToString(bstDBPath);
	szPassword = _com_util::ConvertBSTRToString(bstPassword);
	m_szCurrentDbPath = szDBPath;
	if (m_szCurrentDbPath.IsEmpty())
	{
		return FALSE;
	}
	if( NULL == m_pDb )
	{
		try
		{
			m_pDb = new CADODatabase();
		}
		catch(...)
		{
			PRINTTRACE_ERROR(_T("Create CADODatabase object error"));
			m_szCurrentDbPath = "";
			return FALSE;
		}
	}
	
	//恢复数据库
/*	try
	{
		CDaoWorkspace m_DBEngine;
		m_DBEngine.CompactDatabase(_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source= C:\\CVESDB.mdb"),_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=c:\\CVESDB.mdb;Jet OLEDB:Engine Type=4"),dbLangGeneral, 0);
		int a = GetLastError();
		//CDaoWorkspace::RepairDatabase(_T("C:\\DB1.MDB"));   
	}
	catch(CDaoException* e)   
	{   
		int a = GetLastError();
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);   
		e->Delete();   
	}//*/ 

    if (m_DbBasisOpt.OpenDB(m_pDb, m_szCurrentDbPath, szPassword))
	{
        //TRACE_LEAVE_FUNC(OpenDB);
		return TRUE;
	}
	else
	{
		//修复
		//CDaoWorkspace::RepairDatabase(m_szCurrentDbPath);   
		 
		if (m_DbBasisOpt.OpenDB(m_pDb, m_szCurrentDbPath, szPassword))
		{
			//TRACE_LEAVE_FUNC(OpenDB);
			return TRUE;
		}
		
		m_szCurrentDbPath = "";
		return FALSE;
	}

}

BOOL DBDatabaseOpt::CloseDB()
{
	try
	{
		//TRACE_ENTER_FUNC(CloseDB);
		m_DbBasisOpt.CloseDB(m_pDb);
        //TRACE_LEAVE_FUNC(CloseDB);

		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	} 
}
