/* Time: <@(#)DBDatabaseOpt.h   2009-3-26 - 15:31:11   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DBDatabaseOpt.h
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
 *	1	2009-3-26 - 15:31:11		FanZF	Creation
 *
 *********************************************************************
 */

// DBDatabaseOpt.h: interface for the DBDatabaseOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBDATABASEOPT_H__1EABC1AF_D4B7_4174_A523_9D634D649342__INCLUDED_)
#define AFX_DBDATABASEOPT_H__1EABC1AF_D4B7_4174_A523_9D634D649342__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DBDatabaseOpt  
{
public:
	BOOL CloseDB();
	BOOL OpenDB(const BSTR bstDBPath, const BSTR bstPassword);
	CString GetDBPath();
	CADODatabase * GetDBObject();
	static DBDatabaseOpt * GetInstance();
	virtual ~DBDatabaseOpt();

//DBDatabaseOpt类定义为一个单件类
protected:
	DBDatabaseOpt();

private:
	static DBDatabaseOpt * m_pInstance;
	//当前数据库完整路径(包含数据库文件名)
	CString m_szCurrentDbPath;
	CADODatabase * m_pDb;
	//数据库基本操作类实例
	DBDatabaseBasisOpt m_DbBasisOpt;

};

#endif // !defined(AFX_DBDATABASEOPT_H__1EABC1AF_D4B7_4174_A523_9D634D649342__INCLUDED_)
