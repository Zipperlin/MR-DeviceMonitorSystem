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

    typedef LPWSTR LPTSTR; // ��Unicode��LPTSTR��LPWSTR����ͬ�� 

    typedef LPCWSTR LPCTSTR; // ��Unicode��LPCTSTR��LPCWSTR����ͬ�� 

    #else typedef LPSTR LPTSTR; //��ANSI��LPTSTR��LPSTR����ͬ�� 

    typedef LPCSTR LPCTSTR; //��ANSI��LPTCSTR��LPCSTR����ͬ�� 

#endif 


///< Begin��ͷ�ļ�������

///< ����STLģ��ͷ�ļ�
#pragma warning(disable:4786)
#include <vector>
#include <list>
using namespace std;
///< ����ADO������ͷ�ļ�
#include "ado.h"

///< End��ͷ�ļ�������

///< �����Ͷ��塿

///< �������ݿ��¼�ֶ�����
typedef vector< CString     >	TABLEPARAM;
///< �������ݿ��¼�ֶ�����
typedef vector< CString     >	FIELDPARAM;
///< �������ݿ��¼ֵ����
typedef vector< _variant_t  >	RECORDSET;
///< �����¼�������͵�����
typedef vector< RECORDSET*  >	RESULT;

class  DBDatabaseBasisOpt : public CObject  
{
public:
	DBDatabaseBasisOpt();
	virtual ~DBDatabaseBasisOpt();

///< ���ⲿ�ӿں�����
public:
	
	//< �ͷ�����
	void ReleaseResult(RESULT& result);
	///< �õ��ֶ�ֵ
	_variant_t GetFieldValue(CADODatabase* pDB,const CString strFieldName,const CString strSqlList);
	///< �õ���¼��Ŀ
	INT GetRecordCount(CADODatabase* pDB,const CString strSQL);
	///< ����Զ�ID��¼
	_variant_t AddAutoIDRecord(CADODatabase* pDB,const FIELDPARAM& fp,const CString strTblAndCondition,const CString ID,RECORDSET& result);
	///< ɾ�����ݿ��м�¼
	BOOL DeleteRecord(CADODatabase* pDB,const CString strTblAndCondition);
	///< �޸����ݿ��м�¼
	BOOL ModifyRecord(CADODatabase* pDB,const FIELDPARAM& fp,const CString strTblAndCondition,RECORDSET& result);
	///< ��Ӽ�¼�����ݿ���
	BOOL AddRecord(CADODatabase* pDB,const FIELDPARAM& fp,const CString strTblAndCondition,RECORDSET& result);
	///< ������
	void HandleError(CDBException& err);
	///< ��ѯװ�����ݿ���¼
	INT QueryTableRecord(CADODatabase *pDB, const TABLEPARAM& fp, const FIELDPARAM& ftp, const CString strTblAndCondition, RESULT &result);
	///< ��ѯװ�����ݿ��ֶμ�¼
	INT QueryLoadRecord(CADODatabase* pDB,const FIELDPARAM& fp,const CString strTblAndCondition,RESULT& result);
    ///< ��ѯװ�����ݿ��¼
	INT QueryLoadRecordByFieldIndex(CADODatabase* pDB,const FIELDPARAM& fp,const CString strTblAndCondition,RESULT& result);
    ///< ��ѯװ�����ݿ��¼����ѯ������뱸
	INT QueryLoadRecordBySQL(CADODatabase* pDB, const UINT uFieldSize, const CString& strSQL, RESULT& result);
	///< �ر����ݿ�
	void CloseDB(CADODatabase* pDB);
	///< �����ݿ�
	BOOL OpenDB(CADODatabase* pDB,const CString strDBPath,const CString strPasswd = _T(""),const BOOL bWriteDB = TRUE);
	///< �õ����ݿ������ַ�
	CString GetDBConnectionStr(){return m_strConnection;};

	///< ���ڲ���Ա��
protected:
	CString				m_strConnection;
	CCriticalSection	m_SessionLock;
};

#endif // !defined(AFX_DBDATABASEBASISOPT_H__5D71CF3F_9622_445E_AEF7_D2227F51728C__INCLUDED_)
