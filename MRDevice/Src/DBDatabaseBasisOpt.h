/* Time: <@(#)DBDatabaseBasisOpt.h   2009-3-26 - 15:32:28   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DBDatabaseBasisOpt.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-26
 *
 *  Description : Data base basic operation
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-26 - 15:32:28		FanZF	Creation
 *
 *********************************************************************
 */



// DBDatabaseBasisOpt.h: interface for the DBDatabaseBasisOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBDATABASEBASISOPT_H__5D71CF3F_9622_445E_AEF7_D2227F51728C__INCLUDED_)
#define AFX_DBDATABASEBASISOPT_H__5D71CF3F_9622_445E_AEF7_D2227F51728C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef UNICODE 

    typedef LPWSTR LPTSTR; // 在Unicode下LPTSTR与LPWSTR是相同的 

    typedef LPCWSTR LPCTSTR; // 在Unicode下LPCTSTR与LPCWSTR是相同的 

    #else typedef LPSTR LPTSTR; //在ANSI下LPTSTR与LPSTR是相同的 

    typedef LPCSTR LPCTSTR; //在ANSI下LPTCSTR与LPCSTR是相同的 

#endif 


///< Begin【头文件包含】

///< 包含STL模板头文件
#pragma warning(disable:4786)
#include <vector>
#include <list>
using namespace std;
///< 包含ADO基础类头文件
#include "ado.h"

///< End【头文件包含】

///< 【类型定义】

///< 定义数据库记录字段链表
typedef vector< CString     >	TABLEPARAM;
///< 定义数据库记录字段链表
typedef vector< CString     >	FIELDPARAM;
///< 定义数据库记录值链表
typedef vector< _variant_t  >	RECORDSET;
///< 定义记录链表类型的链表
typedef vector< RECORDSET*  >	RESULT;

class  DBDatabaseBasisOpt : public CObject  
{
public:
	DBDatabaseBasisOpt();
	virtual ~DBDatabaseBasisOpt();

///< 【外部接口函数】
public:
	
	//< 释放链表
	void ReleaseResult(RESULT& result);
	///< 得到字段值
	_variant_t GetFieldValue(CADODatabase* pDB,const CString strFieldName,const CString strSqlList);
	///< 得到记录数目
	INT GetRecordCount(CADODatabase* pDB,const CString strSQL);
	///< 添加自动ID记录
	_variant_t AddAutoIDRecord(CADODatabase* pDB,const FIELDPARAM& fp,const CString strTblAndCondition,const CString ID,RECORDSET& result);
	///< 删除数据库中记录
	BOOL DeleteRecord(CADODatabase* pDB,const CString strTblAndCondition);
	///< 修改数据库中记录
	BOOL ModifyRecord(CADODatabase* pDB,const FIELDPARAM& fp,const CString strTblAndCondition,RECORDSET& result);
	///< 添加记录到数据库中
	BOOL AddRecord(CADODatabase* pDB,const FIELDPARAM& fp,const CString strTblAndCondition,RECORDSET& result);
	///< 错误处理
	void HandleError(CDBException& err);
	///< 查询装载数据库表记录
	INT QueryTableRecord(CADODatabase *pDB, const TABLEPARAM& fp, const FIELDPARAM& ftp, const CString strTblAndCondition, RESULT &result);
	///< 查询装载数据库字段记录
	INT QueryLoadRecord(CADODatabase* pDB,const FIELDPARAM& fp,const CString strTblAndCondition,RESULT& result);
    ///< 查询装载数据库记录
	INT QueryLoadRecordByFieldIndex(CADODatabase* pDB,const FIELDPARAM& fp,const CString strTblAndCondition,RESULT& result);
    ///< 查询装载数据库记录，查询语句已齐备
	INT QueryLoadRecordBySQL(CADODatabase* pDB, const UINT uFieldSize, const CString& strSQL, RESULT& result);
	///< 关闭数据库
	void CloseDB(CADODatabase* pDB);
	///< 打开数据库
	BOOL OpenDB(CADODatabase* pDB,const CString strDBPath,const CString strPasswd = _T(""),const BOOL bWriteDB = TRUE);
	///< 得到数据库连接字符
	CString GetDBConnectionStr(){return m_strConnection;};

	///< 【内部成员】
protected:
	CString				m_strConnection;
	CCriticalSection	m_SessionLock;
};

#endif // !defined(AFX_DBDATABASEBASISOPT_H__5D71CF3F_9622_445E_AEF7_D2227F51728C__INCLUDED_)
