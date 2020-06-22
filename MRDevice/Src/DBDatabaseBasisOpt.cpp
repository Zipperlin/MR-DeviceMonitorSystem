// DBDatabaseBasisOpt.cpp: implementation of the DBDatabaseBasisOpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DBDatabaseBasisOpt.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DBDatabaseBasisOpt::DBDatabaseBasisOpt()
{
	///< 初始化数据库连接字符
	m_strConnection = _T("");
}

DBDatabaseBasisOpt::~DBDatabaseBasisOpt()
{

}

BOOL DBDatabaseBasisOpt::OpenDB(CADODatabase *pDB, const CString strDBPath, const CString strPasswd, const BOOL bWriteDB)
{
    ///< 检测数据库路径是否存在
	CFileFind finder;
	if(!finder.FindFile(strDBPath))
	{
		finder.Close();
		return FALSE;
	}
	finder.Close();

	///< 检测更改数据库文件只读属性
	if(bWriteDB)
	{
		if( GetFileAttributes(strDBPath) & FILE_ATTRIBUTE_READONLY)
			if(!SetFileAttributes(strDBPath,FILE_ATTRIBUTE_NORMAL))return FALSE;
	}

	///< 连接数据库字符
	m_strConnection= _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source= ");
	m_strConnection += strDBPath;
    m_strConnection += _T(";Persist Security Info=FALSE;Jet OLEDB:Database Password= ");
	m_strConnection += strPasswd;

	///< 连接打开数据库
	if(pDB->Open(m_strConnection))return TRUE;
	else
	{	
		m_strConnection = _T("");
		PRINTTRACE_ERROR(pDB->GetLastErrorString());
		DWORD dwError = pDB->GetLastError();
		return FALSE;
	}
}

void DBDatabaseBasisOpt::CloseDB(CADODatabase *pDB)
{
	if(pDB&&pDB->IsOpen())
	{
		pDB->Close();
	}
}

INT DBDatabaseBasisOpt::QueryLoadRecord(CADODatabase *pDB, const FIELDPARAM &fp, const CString strTblAndCondition, RESULT &result)
{
	CSingleLock sLock(&m_SessionLock);
	sLock.Lock();

    // 查询字段数目
	int nFieldSize = fp.size();	
	INT iResult;
	CString strSQL;
	if(nFieldSize == 0)
	{
		return 0;
	}
	else
	{
		CString strFields(_T(""));
		for(int i=0; i<nFieldSize-1; i++)
			strFields = strFields + fp[i] + _T(",");
		
		strFields = _T("select ") + strFields + fp[nFieldSize-1] + _T(" ");

		// 生成查询语句
		strSQL = strFields + strTblAndCondition;
	}

	PRINTTRACE_INFO(strSQL);

	CADORecordset* pRS = new CADORecordset(pDB);
	
	try
	{
		if(pRS->Open((LPCTSTR)strSQL,CADORecordset::openQuery))
		{
			if(pRS->GetRecordCount()>0)
				pRS->MoveFirst();

			while(!pRS->IsEOF())
			{
				//存储字段
				RECORDSET* pRecord = new RECORDSET;  
				for(int i=0; i<nFieldSize; i++)
				{
					_variant_t v;			
					if(pRS->IsFieldNull(i))
					{
						v=(_bstr_t)_T("");
					}
					else
						pRS->GetFieldValue(fp[i], v);
							
					pRecord->push_back(v);
				}
				result.push_back(pRecord);
				pRS->MoveNext();
			}

			pRS->Close();
			iResult = result.size();
		}
		else
		{
			iResult = 0;
			PRINTTRACE_ERROR(_T("QueryLoadRecord open fail"));
		}

		delete pRS;
		pRS = NULL;
	}
	catch(CDBException& err)
	{
		if(NULL != pRS)
		{
			if(pRS->IsOpen())
				pRS->Close();
			
			delete pRS;
			pRS = NULL;
		}

		iResult = 0;
		HandleError(err);

		sLock.Unlock();

		return 0;
	}
	
	sLock.Unlock();
	
	return iResult;
}

INT DBDatabaseBasisOpt::QueryTableRecord(CADODatabase *pDB, const TABLEPARAM &fp,const FIELDPARAM& ftp, const CString strTblAndCondition, RESULT &result)
{
	CSingleLock sLock(&m_SessionLock);
	sLock.Lock();

    // 查询字段数目
	int nFieldSize = ftp.size();	//
	INT iResult;
	if(fp.size() < 1)
	{
		PRINTTRACE_ERROR(_T("QueryLoadRecord input field size <= 0"));
		return 0;
	}

	CString strFields(_T(""));
	for(int i=0; i<fp.size()-1; i++)
		strFields = strFields + fp[i] + _T(",");
	
	strFields = _T("select ") + strFields + fp[fp.size()-1] + _T(" ");

	// 生成查询语句
	CString strSQL = strFields + strTblAndCondition;

	PRINTTRACE_INFO(strSQL);

	CADORecordset* pRS = new CADORecordset(pDB);
	
	try
	{
		if(pRS->Open((LPCTSTR)strSQL,CADORecordset::openQuery))
		{
			if(pRS->GetRecordCount()>0)
				pRS->MoveFirst();

			while(!pRS->IsEOF())
			{
				//存储字段
				RECORDSET* pRecord = new RECORDSET;  
				
				for(int i=0; i<nFieldSize; i++)
				{
					_variant_t v;			
					if(pRS->IsFieldNull(i))
					{
						v=(_bstr_t)_T("");
					}
					else
					{
						pRS->GetFieldValue(ftp[i], v);
					}
							
					pRecord->push_back(v);
				}
				result.push_back(pRecord);
				pRS->MoveNext();
			}

			pRS->Close();
			iResult = result.size();
		}
		else
		{
			iResult = 0;
			PRINTTRACE_ERROR(_T("QueryLoadRecord open fail"));
		}

		delete pRS;
		pRS = NULL;
	}
	catch(CDBException& err)
	{
		if(NULL != pRS)
		{
			if(pRS->IsOpen())
				pRS->Close();
			
			delete pRS;
			pRS = NULL;
		}

		iResult = 0;
		HandleError(err);

		sLock.Unlock();

		return 0;
	}
	
	sLock.Unlock();
	
	return iResult;
}

void DBDatabaseBasisOpt::HandleError(CDBException &err)
{
	CString szErr = err.m_strError;

	err.m_strError += _T(" -- catch error in DBDatabaseBasisOpt!");
	PRINTTRACE_ERROR(err.m_strError);
	err.ReportError();
}

BOOL DBDatabaseBasisOpt::AddRecord(CADODatabase *pDB, const FIELDPARAM &fp, const CString strTblAndCondition, RECORDSET &result)
{
	CSingleLock sLock(&m_SessionLock);
	sLock.Lock();

	BOOL bUpdateResult(FALSE);
	int nFieldSize = fp.size();	// 查询字段数目

	CString strFields(_T(""));
	
	// 生成查询语句
	strFields = _T("select * ");

	CString strSQL = strFields + strTblAndCondition;

	PRINTTRACE_INFO(strSQL);

	CADORecordset* pRS = new CADORecordset(pDB);
	
	try
	{
		if (pRS->Open((LPCTSTR)strSQL,CADORecordset::openQuery))
		{
			pRS->AddNew();
			for(int i=0; i<nFieldSize; i++)
			{
				CString strFldName=fp[i];
				_variant_t vtFld=result[i];
				///< 判断值类型
				switch(vtFld.vt)
				{
					///< 整型
				case VT_I2:
					{
						pRS->SetFieldValue(strFldName, vtFld.iVal);
					}
					break;
					///< 长整型
				case VT_I4:
					{
						pRS->SetFieldValue(strFldName, vtFld.lVal);
					}
					break;
					///< 浮点型
				case VT_R4:
					{
						pRS->SetFieldValue(strFldName, vtFld.fltVal);
					}
					break;
				     ///< Double类型
				case VT_R8:
					{
						pRS->SetFieldValue(strFldName, vtFld.dblVal);
					}
					break;
					//< 布尔型
				case VT_BOOL:
					{
						pRS->SetFieldValue(strFldName, vtFld.boolVal);
					}
					break;
					///< 日期型
				case VT_DATE:
					{
						pRS->SetFieldValue(strFldName, vtFld.date);
					}
					break;
					///< 默认字符型
				default:
					{
						pRS->SetFieldValue(strFldName, vtFld);
					}
					break;
				}
			}
			//pRS->Update();//Originality code
			//2006-09-01 modify (deal with update error)
			bUpdateResult = pRS->Update();

			pRS->Close();
		}
		delete pRS;
		pRS = NULL;
		//2006-09-01 modify (deal with update error)
		if (FALSE == bUpdateResult)
		{
			sLock.Unlock();
			return FALSE;
		}
	}
	catch(CDBException& err)
	{
		if(NULL != pRS)
		{
			if(pRS->IsOpen())
				pRS->Close();
			
			delete pRS;
			pRS = NULL;
		}

		sLock.Unlock();

		HandleError(err);
		return FALSE;
	}

	sLock.Unlock();
	
	return TRUE;
}

BOOL DBDatabaseBasisOpt::ModifyRecord(CADODatabase *pDB, const FIELDPARAM &fp, const CString strTblAndCondition, RECORDSET &result)
{
	CSingleLock sLock(&m_SessionLock);
	sLock.Lock();

    BOOL bUpdateResult(FALSE);
    // 查询字段数目
	int nFieldSize = fp.size();	
	///< 形成SQL语句
	CString strSQL = _T("select *") + strTblAndCondition;
	CADORecordset* pRS = new CADORecordset(pDB);
	try
	{
		if (pRS->Open((LPCTSTR)strSQL, CADORecordset::openQuery)) 
		{
			if(pRS->GetRecordCount()<=0)
			{
				sLock.Unlock();
				return FALSE;
			}

			while(!pRS->IsEOF())
			{
				pRS->Edit();
				for(int i=0; i<nFieldSize; i++)
				{
					CString strFldName=fp[i];
					_variant_t vtFld=result[i];
					///< 判断字段类型
					switch(vtFld.vt)
					{
						///< 整型
					case VT_I2:
						{
							pRS->SetFieldValue(strFldName, vtFld.iVal);
						}
						break;
						///< 整型
					case VT_I4:
						{
							pRS->SetFieldValue(strFldName, vtFld.lVal);
						}
						break;
						///< 浮点型
					case VT_R4:
						{
							pRS->SetFieldValue(strFldName, vtFld.fltVal);
						}
						break;
					    ///< Double类型
				    case VT_R8:
						{
						    pRS->SetFieldValue(strFldName, vtFld.dblVal);
						}
					    break;
						///< 布尔型
					case VT_BOOL:
						{
							pRS->SetFieldValue(strFldName, vtFld.boolVal);
						}
						break;
						///< 日期型
					case VT_DATE:
						{
							pRS->SetFieldValue(strFldName, vtFld.date);
						}
						break;
						///< 默认字符类型
					default:
						{	
							pRS->SetFieldValue(strFldName, vtFld);	
						}
						break;
					}
				}
				//pRS->Update();//Originality code
				//2006-09-01 modify (deal with update error)
				bUpdateResult = pRS->Update();
				if (FALSE == bUpdateResult)
				{
					break;// exit while Cyc
				}
				
				pRS->MoveNext();
			}
		}

		if(pRS->IsOpen())
			pRS->Close();
		
		delete pRS;
		pRS = NULL;

        //2006-09-01 modify (deal with update error)
		if (FALSE == bUpdateResult)
		{
			sLock.Unlock();
			return FALSE;
		}
	}
	catch(CDBException& err)
	{
		if(NULL != pRS)
		{
			if(pRS->IsOpen())
				pRS->Close();
			
			delete pRS;
			pRS = NULL;
		}
	
		HandleError(err);

		sLock.Unlock();

		return FALSE;
	}

	sLock.Unlock();
	
	return TRUE;
}

BOOL DBDatabaseBasisOpt::DeleteRecord(CADODatabase *pDB, const CString strTblAndCondition)
{
	CString strSQL = _T("delete * ") + strTblAndCondition;
	PRINTTRACE_INFO(strSQL);
	return pDB->Execute(strSQL);
}

_variant_t DBDatabaseBasisOpt::AddAutoIDRecord(CADODatabase *pDB, const FIELDPARAM &fp, const CString strTblAndCondition, const CString ID, RECORDSET &result)
{
	_variant_t IDValue;

	int nFieldSize = fp.size();	// 查询字段数目

	// 生成查询语句
	CString strFields(_T(""));
	
	strFields = _T("select * ");
	CString strSQL = strFields + strTblAndCondition;	
	
	CADORecordset* pRS = new CADORecordset(pDB);

	try
	{
		if (pRS->Open((LPCTSTR)strSQL,CADORecordset::openQuery))
		{
			pRS->AddNew();
			for(int i=0; i<nFieldSize; i++)
			{
				CString strFldName=fp[i];
				_variant_t vtFld=result[i];
				///< 判断字段类型
				switch(vtFld.vt)
				{
					///< 整型
				case VT_I2:
					{
						pRS->SetFieldValue(strFldName, vtFld.iVal);
					}
					break;
					///< 整型
				case VT_I4:
					{
						pRS->SetFieldValue(strFldName, vtFld.lVal);
					}
					break;
					///< 浮点型
				case VT_R4:
					{
						pRS->SetFieldValue(strFldName, vtFld.fltVal);
					}
					break;
					///< Double类型
				case VT_R8:
					{
						pRS->SetFieldValue(strFldName, vtFld.dblVal);
					}
					break;
					///< 布尔型
				case VT_BOOL:
					{
						pRS->SetFieldValue(strFldName, vtFld.boolVal);
					}
					break;
					///< 日期型
				case VT_DATE:
					{
						pRS->SetFieldValue(strFldName, vtFld.date);
					}
					break;
					///< 默认字符型
				default:
					{
						pRS->SetFieldValue(strFldName, vtFld);
					}
					break;
				}
			}
			pRS->Update();

			///< 判断ID值
			if(ID.IsEmpty())
			{
				pRS->Close();
				delete pRS;
				pRS = NULL;
				return _T("NULL");
			}
			
			///< 得到ID值
			pRS->GetFieldValue(ID,IDValue);
			pRS->Close();
			delete pRS;
			pRS = NULL;
		}
	}
	catch(CDBException& err)
	{
		///< 判断ID值
		if(ID.IsEmpty())
		{
			pRS->Close();
			delete pRS;
			pRS = NULL;
			return _T("NULL");
		}
		///< 得到ID值
		if(NULL != pRS)
		{
			pRS->GetFieldValue(ID,IDValue);
			pRS->Close();
			delete pRS;
			pRS = NULL;
		}
		
		HandleError(err);
		return _T("");
	}
	return IDValue;
}

INT DBDatabaseBasisOpt::GetRecordCount(CADODatabase *pDB, const CString strSQL)
{
    int iCount=0;
	CADORecordset* pRS = new CADORecordset(pDB);

	try
	{
		if (pRS->Open(strSQL,CADORecordset::openQuery))
		{
			iCount=pRS->GetRecordCount();
			pRS->Close();
		}
		delete pRS;
		pRS = NULL;
	}
	catch(CDBException& err)
	{
		if(NULL != pRS)
		{
			if(pRS->IsOpen())
				pRS->Close();
			
			delete pRS;
			pRS = NULL;
		}
		HandleError(err);
	}
	return iCount;
}

_variant_t DBDatabaseBasisOpt::GetFieldValue(CADODatabase *pDB, const CString strFieldName, const CString strSqlList)
{
	_variant_t v;
	CString strSQL = _T("SELECT ") + strFieldName + strSqlList;
	
	CADORecordset* pRS = new CADORecordset(pDB);

	try
	{
		if(pRS->Open(strSQL,CADORecordset::openQuery)) 
		{
			if(pRS->GetRecordCount()>0)
				pRS->MoveFirst();

			while(!pRS->IsEOF())
			{
				pRS->GetFieldValue(strFieldName, v);
				pRS->MoveNext();
			}
			pRS->Close();
		}
		delete pRS;
		pRS = NULL;
	}
	catch(CDBException& err)
	{
		if(NULL != pRS)
		{
			if(pRS->IsOpen())
				pRS->Close();
			
			delete pRS;
			pRS = NULL;
		}
		
		HandleError(err);
	}
	return v;
}

void DBDatabaseBasisOpt::ReleaseResult(RESULT &result)
{
	if(result.size() > 0)
	{
		for(int i=0;i<result.size();i++)
		{
			RECORDSET* recordSet=result[i];
			if (recordSet!=NULL)
			{
				delete recordSet;
				recordSet = NULL;
			}
		}
		result.clear();
	}
}

INT DBDatabaseBasisOpt::QueryLoadRecordByFieldIndex(CADODatabase *pDB, const FIELDPARAM &fp, const CString strTblAndCondition, RESULT &result)
{
    // 查询字段数目
	int nFieldSize = fp.size();	

	CString strFields(_T(""));
	for(int i=0; i<nFieldSize-1; i++)
		strFields = strFields + fp[i] + _T(",");
	
	strFields = _T("select ") + strFields + fp[nFieldSize-1] + _T(" ");

	// 生成查询语句
	//string strSQL = strFields + strTblAndCondition;
	CString strSQL = strFields + strTblAndCondition;

	CADORecordset* pRS = new CADORecordset(pDB);

	try
	{
		//if(pRS->Open(strSQL.c_str(),CADORecordset::openQuery))
		if(pRS->Open((LPCTSTR)strSQL,CADORecordset::openQuery))
		{
			if(pRS->GetRecordCount()>0)
				pRS->MoveFirst();

			while(!pRS->IsEOF())
			{
				//存储字段
				RECORDSET* pRecord = new RECORDSET;  
				for(int i=0; i<nFieldSize; i++)
				{
					_variant_t v;			
					if(pRS->IsFieldNull(i))
					{
						v=(_bstr_t)_T("");
					}
					else
						pRS->GetFieldValue(i, v);
							
					pRecord->push_back(v);
				}
				result.push_back(pRecord);
				pRS->MoveNext();
			}
			pRS->Close();
		}
		delete pRS;
		pRS = NULL;
	}
	catch(CDBException& err)
	{
		if(NULL != pRS)
		{
			if(pRS->IsOpen())
				pRS->Close();
			
			delete pRS;
			pRS = NULL;
		}
		
		HandleError(err);
	}
	return result.size();
}

INT DBDatabaseBasisOpt::QueryLoadRecordBySQL(CADODatabase* pDB, const UINT uFieldSize, const CString& strSQL, RESULT& result)
{

	CADORecordset* pRS = new CADORecordset(pDB);

	try
	{
		if(pRS->Open((LPCTSTR)strSQL,CADORecordset::openQuery))
		{
			if(pRS->GetRecordCount()>0)
				pRS->MoveFirst();

			while(!pRS->IsEOF())
			{
				//存储字段
				RECORDSET* pRecord = new RECORDSET;  
				for(int i=0; i<uFieldSize; i++)
				{
					_variant_t v;			
					if(pRS->IsFieldNull(i))
					{
						v=(_bstr_t)_T("");
					}
					else
						pRS->GetFieldValue(i, v);
							
					pRecord->push_back(v);
				}
				result.push_back(pRecord);
				pRS->MoveNext();
			}
			pRS->Close();
		}
		delete pRS;
		pRS = NULL;
	}
	catch(CDBException& err)
	{
		if(NULL != pRS)
		{
			if(pRS->IsOpen())
				pRS->Close();
			
			delete pRS;
			pRS = NULL;
		}
		
		HandleError(err);
	}
	return result.size();
}
