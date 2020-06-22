/* Time: <@(#)PADataBaseOpt.cpp   2009-3-26 - 15:33:35   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : PADataBaseOpt.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-26
 *
 *  Description : Printing&Archiving data base operation
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-26 - 15:33:35		FanZF	Creation
 *
 *********************************************************************
 */

// PADabaBaseOpt.cpp: implementation of the CPADabaBaseOpt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PADataBaseOpt.h"
#include "PADataBaseDefine.h"
#include "JobHandler.h"
#include "DirHandler.h"

#import "C:\PROGRAM FILES\COMMON FILES\System\ado\MSJRO.DLL" no_namespace

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CPADataBaseOpt* CPADataBaseOpt::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPADataBaseOpt::CPADataBaseOpt()
{
	m_pDBOpt = NULL;
	m_bDBOpen = FALSE;
}

CPADataBaseOpt::~CPADataBaseOpt()
{

}

CPADataBaseOpt* CPADataBaseOpt::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CPADataBaseOpt;
	}

	return m_pInstance;
}

void CPADataBaseOpt::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

BOOL CPADataBaseOpt::Init()
{
	CString strTrace;


	m_pDBOpt = DBDatabaseOpt::GetInstance();
	if (NULL == m_pDBOpt)
	{
		return FALSE;
	}

	//<< Open P&A database
	CString szDBPath(_T(""));
	CString szPassword(_T(""));

	TCHAR cCurrentSystemDirectory[MAX_PATH]; 
	GetModuleFileName(NULL,cCurrentSystemDirectory,MAX_PATH);//获得应用程序的路径(并且带应用程序文件名)
	CString szApplicationPath = cCurrentSystemDirectory;
	int nIndex = szApplicationPath.ReverseFind('\\');
	szApplicationPath = szApplicationPath.Left(nIndex+1);//获得不带应用程序文件名的应用程序路径(去掉应用程序文件名)
	szDBPath = szApplicationPath + PA_DATABASE_FILE_NAME;
	szPassword = PA_DATABASE_PASSWORD;


	BOOL bOpenDBResult(FALSE);
	bOpenDBResult = m_pDBOpt->OpenDB(szDBPath.AllocSysString(), szPassword.AllocSysString());
	if (bOpenDBResult)
	{
		m_bDBOpen = TRUE;;
		strTrace.Format(_T("m_pDBOpt->OpenDB(), path:%s, pw:%s"), szDBPath, szPassword);
		PRINTTRACE_INFO(strTrace)
	}
	else
	{
		strTrace.Format(_T("m_pDBOpt->OpenDB(), path:%s, pw:%s"), szDBPath, szPassword);
		PRINTTRACE_ERROR(strTrace)

		return FALSE;
	}

	
	return TRUE;

}

BOOL CPADataBaseOpt::UnInit()
{
	if (m_bDBOpen)
	{
		BOOL bResult(FALSE);
		bResult = m_pDBOpt->CloseDB();
		if (bResult)
		{
			m_bDBOpen = FALSE;
		}
		else
		{
			PRINTTRACE_ERROR(_T("m_pDBOpt->CloseDB()"))

			return FALSE;
		}
	}
	
	return TRUE;
}

BOOL CPADataBaseOpt::AddJob(PAJob* pJob)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	

	CString szSQL(_T(""));
	szSQL = _T("From JobInfo");

	FIELDPARAM fpFieldList;
	for(int i=1; i<JOBINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobInfo_Field[i]);
	}
	
	DBTRACE_INFO(_T("set value"));
	RECORDSET rsRecordSet;
	//把结构体转化为记录链表
	//_variant_t vtValue;

	VARIANT vtValueJobID;
	VariantInit(&vtValueJobID);

	VARIANT vtValueType;
	VariantInit(&vtValueType);

	VARIANT vtValueState;
	VariantInit(&vtValueState);

	VARIANT vtValueProcess;
	VariantInit(&vtValueProcess);

	 //Field1 --- Index
// 	vtValue.vt = VT_I4;
// 	vtValue.lVal = 8;
// 	rsRecordSet.push_back(vtValue);

	//Field1 --- JobID
    vtValueJobID.vt = VT_BSTR;
	vtValueJobID.bstrVal = pJob->strJobID.AllocSysString();
	rsRecordSet.push_back(vtValueJobID);

	//Field2 --- Type
	vtValueType.vt = VT_I2;
	vtValueType.iVal = (SHORT)pJob->enumJobType;
	rsRecordSet.push_back(vtValueType);

	//Field3 --- State
	vtValueState.vt = VT_I2;
	vtValueState.iVal = (SHORT)pJob->enumJobState;
	rsRecordSet.push_back(vtValueState);

	//Field3 --- Progress
	vtValueProcess.vt = VT_BSTR;
	vtValueProcess.bstrVal = CString(_T("")).AllocSysString();
	rsRecordSet.push_back(vtValueProcess);

	DBTRACE_INFO(_T("set value finished"));

    BOOL bResult(FALSE);
	try
	{
		bResult = m_DbBasisOpt.AddRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, rsRecordSet);		
	}
	catch(CDBException& err)
	{

		//err.ReportError();
		err.m_strError += _T(" -- catch error in AddJob interface !");
		PRINTTRACE_ERROR(err.m_strError);

		VariantClear(&vtValueJobID);
		VariantClear(&vtValueType);
		VariantClear(&vtValueState);
		VariantClear(&vtValueProcess);

		return FALSE;
	}
	
	
	if (bResult)
	{
		VariantClear(&vtValueJobID);
		VariantClear(&vtValueType);
		VariantClear(&vtValueState);
		VariantClear(&vtValueProcess);

		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR(_T("m_DbBasisOpt.AddRecord() error"));

		VariantClear(&vtValueJobID);
		VariantClear(&vtValueType);
		VariantClear(&vtValueState);
		VariantClear(&vtValueProcess);

		return FALSE;
	}
}

BOOL CPADataBaseOpt::SetJob(PAJob* pJob)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	CString szSQL(_T(""));
	szSQL.Format(_T("From JobInfo Where JobID = '%s'"), pJob->strJobID);

	FIELDPARAM fpFieldList;
	for(int i=2; i<JOBINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobInfo_Field[i]);
	}
	
	DBTRACE_INFO(_T("set value"));
	RECORDSET rsRecordSet;
	//把结构体转化为记录链表
	//_variant_t vtValue;

	VARIANT vtValueType;
	VariantInit(&vtValueType);

	VARIANT vtValueState;
	VariantInit(&vtValueState);

	VARIANT vtValueProcess;
	VariantInit(&vtValueProcess);

 	//Field1 --- Index
// 	vtValue.vt = VT_I4;
// 	vtValue.lVal = 8;
// 	rsRecordSet.push_back(vtValue);

	//Field1 --- JobID
//	vtValue.vt = VT_BSTR;
// 	vtValue.bstrVal = pJob->strJobID.AllocSysString();
// 	rsRecordSet.push_back(vtValue);
//	VariantClear(&vtValue);

	//Field2 --- Type
	vtValueType.vt = VT_I2;
	vtValueType.iVal = (SHORT)pJob->enumJobType;
	rsRecordSet.push_back(vtValueType);

	//Field3 --- State
	vtValueState.vt = VT_I2;
	vtValueState.iVal = (SHORT)pJob->enumJobState;
	rsRecordSet.push_back(vtValueState);

	//Field3 --- Progress
	vtValueProcess.vt = VT_BSTR;
	vtValueProcess.bstrVal = CString(_T("")).AllocSysString();
	rsRecordSet.push_back(vtValueProcess);

	DBTRACE_INFO(_T("set value finished"));

    BOOL bResult(FALSE);
	try
	{
		bResult = m_DbBasisOpt.ModifyRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, rsRecordSet);
		
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in AddJob interface !");
		PRINTTRACE_ERROR(err.m_strError);

		VariantClear(&vtValueType);
		VariantClear(&vtValueState);
		VariantClear(&vtValueProcess);

		return FALSE;
	}
	  
	
	if (bResult)
	{
		bResult = AddJobPssiInfo(pJob);
		if (!bResult)
		{
			PRINTTRACE_ERROR("AddJobPatientInfo(pJob)")
		}
	}

	if (bResult)
	{
		bResult = AddJobUIDInfo(pJob);
		if (!bResult)
		{
			PRINTTRACE_ERROR("AddJobPatientInfo(pJob)")
		}
	}

	if (bResult)
	{
		bResult = AddJobDetailInfo(pJob);
		if (!bResult)
		{
			PRINTTRACE_ERROR("AddJobPatientInfo(pJob)")
		}
	}

	if (bResult)
	{
		bResult = AddJobNetworkNodeInfo(pJob);
		if (!bResult)
		{
			PRINTTRACE_ERROR("AddJobPatientInfo(pJob)")
		}
	}

	if (bResult)
	{
		bResult = AddJobDiscImportImageInfo(pJob);
		if (!bResult)
		{
			PRINTTRACE_ERROR("AddJobPatientInfo(pJob)")
		}
	}

	if (bResult)
	{
		PRINTTRACE_INFO("CPADataBaseOpt::SetJob -> return TRUE")

		VariantClear(&vtValueType);
		VariantClear(&vtValueState);
		VariantClear(&vtValueProcess);

		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR(_T("m_DbBasisOpt.AddRecord() error"));
		
		VariantClear(&vtValueType);
		VariantClear(&vtValueState);
		VariantClear(&vtValueProcess);

		return FALSE;
	}
}

BOOL CPADataBaseOpt::GetJobCount(DWORD* pdwCount)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}

	INT iCount = 0;
	CString szSQL;
	szSQL.Format(_T("Select * From JobInfo where State = %d or State = %d or State = %d"), enumJobState_Completed, enumJobState_Cancelled, enumJobState_Failed);
// 	szSQL = _T("Select * From JobInfo");
	
	try
	{
		iCount = m_DbBasisOpt.GetRecordCount(m_pDBOpt->GetDBObject(), szSQL);		
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in AddJob interface !");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}

	if (iCount >= 0)
	{
		*pdwCount = iCount;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPADataBaseOpt::GetJobs(DWORD dwStartIndex, DWORD* pdwCount, JobInfo** ppJobList)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	//<< dwStartIndex从1开始
	if (dwStartIndex < 1 || *pdwCount < 1)
	{
		return FALSE;
	}

	CString szSQL(_T(""));
	CString strJobStateCond;
	strJobStateCond.Format(_T("State = %d or State = %d or State = %d"), enumJobState_Completed, enumJobState_Cancelled, enumJobState_Failed);
	if (1 == dwStartIndex)
	{
		szSQL.Format(_T("Select top %d * From JobInfo where (%s) order by Index"), *pdwCount, strJobStateCond);
	}
	else
	{
		CString strSubSQL;
		strSubSQL.Format(_T("select top %d Index From JobInfo where %s order by Index"), dwStartIndex-1, strJobStateCond);
		szSQL.Format(_T("Select top %d * From JobInfo Where Index not in (%s) and (%s) order by Index"), *pdwCount, strSubSQL, strJobStateCond);
	}


	RESULT ResultList;
	RECORDSET *pRecordList;
	DBDatabaseBasisOpt m_DbBasisOpt;
	try
	{
		m_DbBasisOpt.QueryLoadRecordBySQL(m_pDBOpt->GetDBObject(), JOBINFO_TABLE_FIELD_NUM, szSQL, ResultList);
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in AddJob interface !");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}

	*pdwCount = ResultList.size();

	long nSize(0);
	nSize = *pdwCount * sizeof(**ppJobList);
	*ppJobList = (JobInfo*)CoTaskMemAlloc(nSize);
	if (NULL == *ppJobList)
	{
		pdwCount = 0;
		return FALSE;
	}

	for(int i = 0; i < *pdwCount; i++ )
	{
		pRecordList = ResultList[i];
		
		//把查询的结果赋于输出参数
		CString strInfo;

		//Field1 --- Index
		RECORDSET::iterator iterRecord = pRecordList->begin();
		strInfo.Format(_T("%d"), dwStartIndex + i);
		(*ppJobList)[i].bsIndex = strInfo.AllocSysString();

		//Field2 ---JobID
		iterRecord++;
		(*ppJobList)[i].bsJobID = SysAllocString(iterRecord->bstrVal);

	    //Field3 --- Type
		iterRecord++;
		(*ppJobList)[i].enumType = (JobType)iterRecord->iVal;
		switch ((*ppJobList)[i].enumType)
		{
		case enumJobType_BurnJob:
			strInfo = JOB_TYPE_BURN;
			break;
		case enumJobType_AutoSendJob:
			strInfo = JOB_TYPE_SEND_AUTO;
			break;
		case enumJobType_ManualSendJob:
			strInfo = JOB_TYPE_SEND_MANUAL;
		    break;
		case enumJobType_DiscImportJob:
			strInfo = JOB_TYPE_IMPORT;
		    break;
		default:
			strInfo = _T("");
		    break;
		}
		(*ppJobList)[i].bsType = _TT(strInfo).AllocSysString(); 


	    //Field3 --- State
		iterRecord++;
		switch((JobState)iterRecord->iVal)
		{
		case enumJobState_Submitted:
			strInfo = JOB_STATE_SUBMITTED;
			break;
		case enumJobState_Executing:
			strInfo = JOB_STATE_EXECUTING;
			break;
		case enumJobState_Completed:
			strInfo = JOB_STATE_COMPLETED;
			break;
		case enumJobState_Cancelled:
			strInfo = JOB_STATE_CANCELLED;
			break;
		case enumJobState_Failed:
			strInfo = JOB_STATE_FAILED;
			break;
		default:
			strInfo = _T("");
		    break;
		}
		(*ppJobList)[i].bsState = _TT(strInfo).AllocSysString(); 

        //Field4 --- Progress
		iterRecord++;
		BSTR bs = iterRecord->bstrVal;
		(*ppJobList)[i].bsProgress = SysAllocString(iterRecord->bstrVal);

		// others
		CString strJobID = CBSTROpt::BSTRToCString((*ppJobList)[i].bsJobID);
		strInfo.Format(_T("%s-%s-%s %s:%s:%s"), strJobID.Left(4),
												strJobID.Mid(4, 2),
												strJobID.Mid(6, 2),
												strJobID.Mid(8, 2),
												strJobID.Mid(10, 2),
												strJobID.Mid(12, 2));
		(*ppJobList)[i].bsSubmitTime = strInfo.AllocSysString();
		(*ppJobList)[i].bsPhase = CString(_T("")).AllocSysString();
		(*ppJobList)[i].bsDetail = CString(_T("")).AllocSysString();
		
	}
    
	//Release result list
	if (ResultList.size() > 0)
	{
		m_DbBasisOpt.ReleaseResult(ResultList);
	}


	return TRUE;
}

BOOL CPADataBaseOpt::GetJobInfo(LPCTSTR szJobID, JobInfo* pJobInfo)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	if (NULL == szJobID || NULL == pJobInfo)
	{
		return FALSE;
	}

	CString strJobID = szJobID;
	if (strJobID.IsEmpty())
	{
		return FALSE;
	}

	CString szSQL(_T(""));
	szSQL = _T("From JobInfo where JobID = '") + strJobID + _T("'");

	FIELDPARAM fpFieldList;
	for(int i=1; i<JOBINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobInfo_Field[i]);
	}

	RESULT ResultList;
	
	try
	{
		m_DbBasisOpt.QueryLoadRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, ResultList);	
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in GetJobPSSIInfo interface!");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}

	if (ResultList.size() <= 0)
	{
		PRINTTRACE_ERROR("ResultList.size() <= 0")
		return FALSE;
	}
	else if (ResultList.size() > 1)
	{
		PRINTTRACE_ERROR("ResultList.size() > 1")
		return FALSE;
	}

	
	//把查询的结果赋于输出参数
	CString strInfo;

	//Field1 --- Index
	strInfo.Format(_T("%d"), 1);
	(*pJobInfo).bsIndex = strInfo.AllocSysString();

	//Field2 ---JobID
	RECORDSET::iterator iterRecord = ResultList[0]->begin();
	(*pJobInfo).bsJobID = SysAllocString(iterRecord->bstrVal);

	//Field3 --- Type
	iterRecord++;
	(*pJobInfo).enumType = (JobType)iterRecord->iVal;
	switch ((*pJobInfo).enumType)
	{
	case enumJobType_BurnJob:
		strInfo = JOB_TYPE_BURN;
		break;
	case enumJobType_AutoSendJob:
		strInfo = JOB_TYPE_SEND_AUTO;
		break;
	case enumJobType_ManualSendJob:
		strInfo = JOB_TYPE_SEND_MANUAL;
		break;
	case enumJobType_DiscImportJob:
		strInfo = JOB_TYPE_IMPORT;
		break;
	default:
		strInfo = _T("");
		break;
	}
	(*pJobInfo).bsType = _TT(strInfo).AllocSysString(); 


	//Field3 --- State
	iterRecord++;
	switch((JobState)iterRecord->iVal)
	{
	case enumJobState_Submitted:
		strInfo = JOB_STATE_SUBMITTED;
		break;
	case enumJobState_Executing:
		strInfo = JOB_STATE_EXECUTING;
		break;
	case enumJobState_Completed:
		strInfo = JOB_STATE_COMPLETED;
		break;
	case enumJobState_Cancelled:
		strInfo = JOB_STATE_CANCELLED;
		break;
	case enumJobState_Failed:
		strInfo = JOB_STATE_FAILED;
		break;
	default:
		strInfo = _T("");
		break;
	}
	(*pJobInfo).bsState = _TT(strInfo).AllocSysString(); 

    //Field4 --- Progress
	iterRecord++;
	BSTR bs = iterRecord->bstrVal;
	(*pJobInfo).bsProgress = SysAllocString(iterRecord->bstrVal);

	// others
	strInfo.Format(_T("%s-%s-%s %s:%s:%s"), strJobID.Left(4),
											strJobID.Mid(4, 2),
											strJobID.Mid(6, 2),
											strJobID.Mid(8, 2),
											strJobID.Mid(10, 2),
											strJobID.Mid(12, 2));
	(*pJobInfo).bsSubmitTime = strInfo.AllocSysString();
	(*pJobInfo).bsPhase = CString(_T("")).AllocSysString();
	(*pJobInfo).bsDetail = CString(_T("")).AllocSysString();

    
	//Release result list
	if (ResultList.size() > 0)
	{
		m_DbBasisOpt.ReleaseResult(ResultList);
	}

	return TRUE;
}

BOOL CPADataBaseOpt::GetJobPSSIInfo(LPCTSTR szJobID, long* pLen, PSSIInfo** ppPSSIList)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	if (NULL == szJobID)
	{
		return FALSE;
	}

	CString strJobID = szJobID;
	if (strJobID.IsEmpty())
	{
		return FALSE;
	}

	CString szSQL(_T(""));
	szSQL = _T("From JobPSSIInfo where JobID = '") + strJobID + _T("' order by Index asc");

	FIELDPARAM fpFieldList;
	for(int i=2; i<JOBPSSIINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobPSSIInfo_Field[i]);
	}

	RESULT ResultList;
	
	try
	{
		m_DbBasisOpt.QueryLoadRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, ResultList);	
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in GetJobPSSIInfo interface!");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}
	
	long lRecordCount(0);
	lRecordCount = ResultList.size();
	*pLen = lRecordCount;
	if (lRecordCount < 0)
	{
		*ppPSSIList = NULL;
		*pLen = 0;
		PRINTTRACE_ERROR(_T("RecordCount < 0"));
		return FALSE;
	}

	if (lRecordCount == 0)
	{
		*ppPSSIList = NULL;
		*pLen = 0;
		return TRUE;
	}

    //assign memory for ppInfo
	long nSize(0);
	nSize = *pLen * sizeof(**ppPSSIList);
	*ppPSSIList = (PSSIInfo*)CoTaskMemAlloc(nSize);
	if (NULL == *ppPSSIList) 
	{
		*pLen = 0;
		PRINTTRACE_ERROR(_T("CoTaskMemAlloc error)"));
		return FALSE;
	}
 	
	for(i = 0; i < lRecordCount; i++)
	{
		RECORDSET *pRecordList = ResultList[i];
		//把查询的结果赋于输出参数
		//Field1 --- PatientID
		RECORDSET::iterator iterRecord = pRecordList->begin();
		(*ppPSSIList)[i].bsPatientID =  SysAllocString(iterRecord->bstrVal);

	    //Field2 --- PatientName
		iterRecord++;
        (*ppPSSIList)[i].bsPatientName = SysAllocString(iterRecord->bstrVal);

        //Field3 --- StudyID
		iterRecord++;
		(*ppPSSIList)[i].bsStudyID = SysAllocString(iterRecord->bstrVal);

        //Field4 --- StudyID
		iterRecord++;
		(*ppPSSIList)[i].bsSeriesID = SysAllocString(iterRecord->bstrVal);

        //Field5 --- StudyID
		iterRecord++;
		(*ppPSSIList)[i].bsImageID = SysAllocString(iterRecord->bstrVal);
    }

	//Release result list
	if (ResultList.size() > 0)
	{
		m_DbBasisOpt.ReleaseResult(ResultList);
	}
	
	return TRUE;
}

BOOL CPADataBaseOpt::GetJobNetworkNodeInfo(LPCTSTR szJobID, long* pLen, NetworkNode** ppNodeList)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	if (NULL == szJobID)
	{
		return FALSE;
	}

	CString strJobID = szJobID;
	if (strJobID.IsEmpty())
	{
		return FALSE;
	}

	CString szSQL(_T(""));
	szSQL = _T("From JobNetworkNodeInfo where JobID = '") + strJobID + _T("' order by Index asc");

	FIELDPARAM fpFieldList;
	for(int i=2; i<JOBNETWORKNODEINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobNetworkNodeInfo_Field[i]);
	}

	RESULT ResultList;
	
	try
	{
		m_DbBasisOpt.QueryLoadRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, ResultList);	
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in GetJobNetworkNodeInfo interface!");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}
	
	long lRecordCount(0);
	lRecordCount = ResultList.size();
	*pLen = lRecordCount;
	if (lRecordCount < 0)
	{
		*ppNodeList = NULL;
		*pLen = 0;
		PRINTTRACE_ERROR(_T("RecordCount < 0"));
		return FALSE;
	}

	if (lRecordCount == 0)
	{
		*ppNodeList = NULL;
		*pLen = 0;
		return TRUE;
	}

    //assign memory for ppInfo
	long nSize(0);
	nSize = *pLen * sizeof(**ppNodeList);
	*ppNodeList = (NetworkNode*)CoTaskMemAlloc(nSize);
	if (NULL == *ppNodeList) 
	{
		*pLen = 0;
		PRINTTRACE_ERROR(_T("CoTaskMemAlloc error)"));
		return FALSE;
	}
 	
	for(i = 0; i < lRecordCount; i++)
	{
		RECORDSET *pRecordList = ResultList[i];
		//把查询的结果赋于输出参数
		//Field3 --- Default
		RECORDSET::iterator iterRecord = pRecordList->begin();
		(*ppNodeList)[i].bDefault =  iterRecord->boolVal;

	    //Field4 --- CalledAE
		iterRecord++;
        (*ppNodeList)[i].bsCalledAE = SysAllocString(iterRecord->bstrVal);

        //Field5 --- CallingAE
		iterRecord++;
		(*ppNodeList)[i].bsCallingAE = SysAllocString(iterRecord->bstrVal);

        //Field6 --- IP
		iterRecord++;
		(*ppNodeList)[i].bsIP = SysAllocString(iterRecord->bstrVal);

        //Field7 --- Port
		iterRecord++;
		(*ppNodeList)[i].bsPort = SysAllocString(iterRecord->bstrVal);

        //Field8 --- Raw
		iterRecord++;
		(*ppNodeList)[i].bRaw = iterRecord->boolVal;

        //Field9 --- Processed
		iterRecord++;
		(*ppNodeList)[i].bProcessed = iterRecord->boolVal;

		// Add [Sun hongwen 10/16/2009]
		iterRecord++;
		(*ppNodeList)[i].bSendPS = iterRecord->boolVal;
		//
    }

	//Release result list
	if (ResultList.size() > 0)
	{
		m_DbBasisOpt.ReleaseResult(ResultList);
	}
	
	return TRUE;
}

BOOL CPADataBaseOpt::GetJobDetailInfo(LPCTSTR szJobID, long* pLen, JobDetailStruct** ppDetailList)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	if (NULL == szJobID)
	{
		return FALSE;
	}

	CString strJobID = szJobID;
	if (strJobID.IsEmpty())
	{
		return FALSE;
	}

	CString szSQL(_T(""));
	szSQL = _T("From JobDetailInfo where JobID = '") + strJobID + _T("' order by Index asc");

	FIELDPARAM fpFieldList;
	for(int i=2; i<JOBDETAILINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobDetailInfo_Field[i]);
	}

	RESULT ResultList;
	
	try
	{
		m_DbBasisOpt.QueryLoadRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, ResultList);	
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in GetJobDetailInfo interface!");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}
	
	long lRecordCount(0);
	lRecordCount = ResultList.size();
	*pLen = lRecordCount;
	if (lRecordCount < 0)
	{
		*ppDetailList = NULL;
		*pLen = 0;
		PRINTTRACE_ERROR(_T("RecordCount < 0"));
		return FALSE;
	}

	if (lRecordCount == 0)
	{
		*ppDetailList = NULL;
		*pLen = 0;
		return TRUE;
	}

    //assign memory for ppInfo
	long nSize(0);
	nSize = *pLen * sizeof(**ppDetailList);
	*ppDetailList = (JobDetailStruct*)CoTaskMemAlloc(nSize);
	if (NULL == *ppDetailList) 
	{
		*pLen = 0;
		PRINTTRACE_ERROR(_T("CoTaskMemAlloc error)"));
		return FALSE;
	}
 	
	for(i = 0; i < lRecordCount; i++)
	{
		RECORDSET *pRecordList = ResultList[i];
		//把查询的结果赋于输出参数

		//Field2 --- JobID
		(*ppDetailList)[i].bsJobID =  strJobID.AllocSysString();

		//Field3 --- DateTime
		RECORDSET::iterator iterRecord = pRecordList->begin();
		COleDateTime odtDateTime = iterRecord->date;
		CString strTime = odtDateTime.Format(_T("%H:%M:%S"));
		(*ppDetailList)[i].bsTime =  strTime.AllocSysString();

	    //Field4 --- Detail
		iterRecord++;
        (*ppDetailList)[i].bsDetail = SysAllocString(iterRecord->bstrVal);
    }

	//Release result list
	if (ResultList.size() > 0)
	{
		m_DbBasisOpt.ReleaseResult(ResultList);
	}
	
	return TRUE;
}

BOOL CPADataBaseOpt::GetJobDiscImportImageInfo(LPCTSTR szJobID, long* pLen, DiscImport_SeriesStruct** ppDISSList)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	if (NULL == szJobID)
	{
		return FALSE;
	}

	CString strJobID = szJobID;
	if (strJobID.IsEmpty())
	{
		return FALSE;
	}

	CString szSQL(_T(""));
	szSQL = _T("From JobDiscImportImageInfo where JobID = '") + strJobID + _T("' order by Index asc");

	FIELDPARAM fpFieldList;
	for(int i=6; i<JOBDISCIMPORTIMAGEINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobDiscImportImageInfo_Field[i]);
	}

	RESULT ResultList;
	
	try
	{
		m_DbBasisOpt.QueryLoadRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, ResultList);	
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in GetJobDiscImportImageInfo interface!");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}
	
	long lRecordCount(0);
	lRecordCount = ResultList.size();
	*pLen = lRecordCount;
	if (lRecordCount < 0)
	{
		*ppDISSList = NULL;
		*pLen = 0;
		PRINTTRACE_ERROR(_T("RecordCount < 0"));
		return FALSE;
	}

	if (lRecordCount == 0)
	{
		*ppDISSList = NULL;
		*pLen = 0;
		return TRUE;
	}

    //assign memory for ppInfo
	long nSize(0);
	nSize = *pLen * sizeof(**ppDISSList);
	*ppDISSList = (DiscImport_SeriesStruct*)CoTaskMemAlloc(nSize);
	if (NULL == *ppDISSList) 
	{
		*pLen = 0;
		PRINTTRACE_ERROR(_T("CoTaskMemAlloc error)"));
		return FALSE;
	}
 	
	for(i = 0; i < lRecordCount; i++)
	{
		RECORDSET *pRecordList = ResultList[i];
		//把查询的结果赋于输出参数

		//Field2 --- JobID
		(*ppDISSList)[i].bsJobID =  strJobID.AllocSysString();

		//Field7 --- ImageIndex
		RECORDSET::iterator iterRecord = pRecordList->begin();
		(*ppDISSList)[i].bsIndex =  SysAllocString(iterRecord->bstrVal);

	    //Field8 --- PatientID
		iterRecord++;
        (*ppDISSList)[i].bsPatientID = SysAllocString(iterRecord->bstrVal);

	    //Field9 --- PatientName
		iterRecord++;
        (*ppDISSList)[i].bsPatientName = SysAllocString(iterRecord->bstrVal);

	    //Field10 --- StudyID
		iterRecord++;
        (*ppDISSList)[i].bsStudyID = SysAllocString(iterRecord->bstrVal);

	    //Field11 --- SeriesID
		iterRecord++;
        (*ppDISSList)[i].bsSeriesID = SysAllocString(iterRecord->bstrVal);

	    //Field12 --- ImageID
		iterRecord++;
        (*ppDISSList)[i].bsImageID = SysAllocString(iterRecord->bstrVal);

	    //Field13 --- ReferencedFileID
		iterRecord++;

	    //Field14 --- State
		iterRecord++;
		CString strState;
		switch ((DiscImport_ImageState)iterRecord->iVal)
		{
		case enumSeriesState_Waiting:
			strState = DISCIMPORT_SERIES_STATE_WAITING;
			break;
		case enumSeriesState_Importing:
			strState = DISCIMPORT_SERIES_STATE_IMPORTING;
			break;
		case enumSeriesState_Completed:
			strState = DISCIMPORT_SERIES_STATE_COMPLETED;
			break;
		case enumSeriesState_Skipped:
			strState = DISCIMPORT_SERIES_STATE_SKIPPED;
			break;
		case enumSeriesState_Failed:
			strState = DISCIMPORT_SERIES_STATE_FAILED;
			break;
		case enumSeriesState_Cancelled:
			strState = DISCIMPORT_SERIES_STATE_CANCELLED;
			break;
		default:
			strState = _T("");
			break;		
		}
        (*ppDISSList)[i].bsState = _TT(strState).AllocSysString(); 

	    //Field15 --- Progress
		iterRecord++;
        (*ppDISSList)[i].bsProgress = SysAllocString(iterRecord->bstrVal);

	    //Field16 --- DetailInfo
		iterRecord++;
        (*ppDISSList)[i].bsDetailInfo = SysAllocString(iterRecord->bstrVal);

    }

	//Release result list
	if (ResultList.size() > 0)
	{
		m_DbBasisOpt.ReleaseResult(ResultList);
	}
	
	return TRUE;
}

BOOL CPADataBaseOpt::DeleteJobs(vector<CString>& vtrJobIDs)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}

	BOOL bResult(FALSE);
	for (int i = 0; i < vtrJobIDs.size(); i++)
	{
		CString szSQL(_T(""));
		szSQL = _T("From JobInfo where JobID = '") + vtrJobIDs[i] + _T("'");

		try
		{
			bResult = m_DbBasisOpt.DeleteRecord(m_pDBOpt->GetDBObject(), szSQL);		
		}
		catch(CDBException& err)
		{
			//err.ReportError();
			err.m_strError += _T(" -- catch error in DeleteJobs interface !");
			PRINTTRACE_ERROR(err.m_strError);
			return FALSE;
		}
  	
		if (!bResult)
		{
			PRINTTRACE_ERROR(_T("m_DbBasisOpt.DeleteRecord() error"));
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CPADataBaseOpt::DeleteAllJobs()
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}

	BOOL bResult(FALSE);

	CString szSQL(_T(""));
	szSQL = _T("From JobInfo");

	try
	{
		bResult = m_DbBasisOpt.DeleteRecord(m_pDBOpt->GetDBObject(), szSQL);		
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in DeleteAllJobs interface !");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}

	if (!bResult)
	{
		PRINTTRACE_ERROR(_T("m_DbBasisOpt.DeleteRecord() error"));
		return FALSE;
	}


	return TRUE;
}

BOOL CPADataBaseOpt::AddWorklistImportedStudy(LPCTSTR szStudyInstanceUID)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	if (NULL == szStudyInstanceUID)
	{
		return FALSE;
	}

	CString strStudyInstanceUID = szStudyInstanceUID;
	if (strStudyInstanceUID.IsEmpty())
	{
		return FALSE;
	}

	CString szSQL(_T(""));
	szSQL = _T("From WorklistImportedStudyInfo");

	FIELDPARAM fpFieldList;
	for(int i=0; i<WORKLISTIMPORTEDSTUDYINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(WorklistImportedStudyInfo_Field[i]);
	}
	
	DBTRACE_INFO(_T("set value"));
	RECORDSET rsRecordSet;
	//把结构体转化为记录链表
	//_variant_t vtValue;
	VARIANT vtValue;
	VariantInit(&vtValue);

	//Field1 --- StudyInstanceUID
    vtValue.vt = VT_BSTR;
	vtValue.bstrVal = strStudyInstanceUID.AllocSysString();
	rsRecordSet.push_back(vtValue);
	VariantClear(&vtValue);


	DBTRACE_INFO(_T("set value finished"));

    BOOL bResult(FALSE);
	try
	{
		bResult = m_DbBasisOpt.AddRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, rsRecordSet);		
	}
	catch(CDBException& err)
	{
		//Release recordset list
		if (rsRecordSet.size() > 0)
		{
			rsRecordSet.clear();
		}

		//err.ReportError();
		err.m_strError += _T(" -- catch error in AddWorklistImportedStudy interface !");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}
  
	
	if (bResult)
	{
		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR(_T("m_DbBasisOpt.AddRecord() error"));
		return FALSE;
	}
}

BOOL CPADataBaseOpt::IsStudyInstanceUIDExist(LPCTSTR szStudyInstanceUID, BOOL* pbExist)
{
	*pbExist = FALSE;
	
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	if (NULL == szStudyInstanceUID)
	{
		return FALSE;
	}

	CString strStudyInstanceUID = szStudyInstanceUID;
	if (strStudyInstanceUID.IsEmpty())
	{
		return FALSE;
	}

	CString szSQL(_T(""));
	szSQL = _T("From WorklistImportedStudyInfo where StudyInstanceUID = '") + strStudyInstanceUID + _T("'");

	FIELDPARAM fpFieldList;
	fpFieldList.push_back(JobInfo_Field[0]);


	RESULT ResultList;
	
	try
	{
		m_DbBasisOpt.QueryLoadRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, ResultList);	
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in IsStudyInstanceUIDExist interface!");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}

	if (ResultList.size() <= 0)
	{
		*pbExist = FALSE;
		return TRUE;
	}
	else if (ResultList.size() > 1)
	{
		PRINTTRACE_ERROR("ResultList.size() > 1")
		*pbExist = TRUE;
		return FALSE;
	}
	else
	{
		*pbExist = TRUE;
		return TRUE;
	}

	
    
	//Release result list
	if (ResultList.size() > 0)
	{
		m_DbBasisOpt.ReleaseResult(ResultList);
	}

	return TRUE;
}

BOOL CPADataBaseOpt::DeleteAllImportedStudyRecords()
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}

	BOOL bResult(FALSE);

	CString szSQL(_T(""));
	szSQL = _T("From WorklistImportedStudyInfo");

	try
	{
		bResult = m_DbBasisOpt.DeleteRecord(m_pDBOpt->GetDBObject(), szSQL);		
	}
	catch(CDBException& err)
	{
		//err.ReportError();
		err.m_strError += _T(" -- catch error in DeleteAllImportedStudyRecords interface !");
		PRINTTRACE_ERROR(err.m_strError);
		return FALSE;
	}

	if (!bResult)
	{
		PRINTTRACE_ERROR(_T("m_DbBasisOpt.DeleteRecord() error"));
		return FALSE;
	}


	return TRUE;
}

BOOL CPADataBaseOpt::CompactDabaBase(BOOL bBackUp)
{
	//<< 关闭数据库
	if (!UnInit())
	{
		PRINTTRACE_ERROR("UnInit()")
		return FALSE;
	}

	//<< 
	CString szDBPath(_T(""));
	CString szPassword(_T(""));

	TCHAR cCurrentSystemDirectory[MAX_PATH]; 
	GetModuleFileName(NULL,cCurrentSystemDirectory,MAX_PATH);//获得应用程序的路径(并且带应用程序文件名)
	CString szApplicationPath = cCurrentSystemDirectory;
	int nIndex = szApplicationPath.ReverseFind('\\');
	szApplicationPath = szApplicationPath.Left(nIndex+1);//获得不带应用程序文件名的应用程序路径(去掉应用程序文件名)
	szDBPath = szApplicationPath + PA_DATABASE_FILE_NAME;
	szPassword = PA_DATABASE_PASSWORD;

	if (!CompactDB(szDBPath, szPassword, bBackUp))
	{
		PRINTTRACE_ERROR("CompactDB(szDBPath, szPassword, bBackUp)")

		if (!Init())
		{
			PRINTTRACE_ERROR("Init()")
		}

		return FALSE;
	}

	//<< 重新启动数据库
	if (!Init())
	{
		PRINTTRACE_ERROR("Init()")
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CPADataBaseOpt::AddJobUIDInfo(PAJob* pJob)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	PatientAdminUIDType enumUIDType = enumPatientAdminUIDType_Unknow;
	if (enumJobType_BurnJob == pJob->enumJobType)
	{
		enumUIDType = ((BurnJobSettingsStruct*)pJob->pData)->enumUIDType;
	}
	else if (enumJobType_AutoSendJob == pJob->enumJobType
			|| enumJobType_ManualSendJob == pJob->enumJobType)
	{
		enumUIDType = ((TransferJobSettingsStruct*)pJob->pData)->enumUIDType;
	}
	else
	{
		return TRUE;
	}

	vector<CString> vtrUIDs;
	switch (enumUIDType)
	{
	case enumPatientAdminUIDType_Patient:
		{
			for (int i = 0; i < pJob->vtrPatient.size(); i++)
			{
				CString strUID = CBSTROpt::BSTRToCString(pJob->vtrPatient[i].bsPatientUID);
				vtrUIDs.push_back(strUID);
			}
		}
		break;
	case enumPatientAdminUIDType_Study:
		{
			for (int i = 0; i < pJob->vtrStudy.size(); i++)
			{
				CString strUID = CBSTROpt::BSTRToCString(pJob->vtrStudy[i].bsStudyUID);
				vtrUIDs.push_back(strUID);
			}
		}
		break;
	case enumPatientAdminUIDType_Series:
		{
			for (int i = 0; i < pJob->vtrSeries.size(); i++)
			{
				CString strUID = CBSTROpt::BSTRToCString(pJob->vtrSeries[i].bsSeriesUID);
				vtrUIDs.push_back(strUID);
			}
		}
	    break;
	case enumPatientAdminUIDType_Image:
		{
			for (int i = 0; i < pJob->vtrImages.size(); i++)
			{
				CString strUID = CBSTROpt::BSTRToCString(pJob->vtrImages[i].bsImageUID);
				vtrUIDs.push_back(strUID);
			}
		}
	    break;
	default:
		PRINTTRACE_ERROR("Error PatientAdminUIDType")
	    return FALSE;
	}

	CString szSQL(_T(""));
	szSQL = _T("From JobUIDInfo");

	FIELDPARAM fpFieldList;
	for(int i=1; i<JOBUIDINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobUIDInfo_Field[i]);
	}
	
	BOOL bRet = TRUE;
	for (i = 0; i < vtrUIDs.size(); i++)
	{
		DBTRACE_INFO(_T("set value"));
		RECORDSET rsRecordSet;
		//把结构体转化为记录链表
		//_variant_t vtValue;
		VARIANT vtValue;
		VariantInit(&vtValue);

 		//Field1 --- Index
	// 	vtValue.vt = VT_I4;
	// 	vtValue.lVal = 8;
	// 	rsRecordSet.push_back(vtValue);

		//Field2 --- JobID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = (pJob->strJobID).AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field3 --- UID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrUIDs[i].AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field4 --- UIDType
		vtValue.vt = VT_I2;
		vtValue.iVal = (SHORT)enumUIDType;
		rsRecordSet.push_back(vtValue);


		DBTRACE_INFO(_T("set value finished"));

		BOOL bResult(TRUE);
		try
		{
			bResult = m_DbBasisOpt.AddRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, rsRecordSet);		
		}
		catch(CDBException& err)
		{
			//err.ReportError();
			err.m_strError += _T(" -- catch error in AddJobUIDInfo interface !");
			PRINTTRACE_ERROR(err.m_strError);
		}

		if (!bResult)
		{
			bRet = FALSE;
			PRINTTRACE_ERROR(_T("m_DbBasisOpt.AddRecord() error"));
		}
	}
  
	
	if (bRet)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CPADataBaseOpt::AddJobPssiInfo(PAJob* pJob)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	//<< 获得PSSI结构列表
	PSSIInfo* pPSSIInfo = NULL;
	long lLen = 0;
	if (!CJobHandler::GetInstance()->GetJobPSSIInfo(pJob, &pPSSIInfo, &lLen))
	{
		PRINTTRACE_ERROR("CJobHandler::GetInstance()->GetJobPSSIInfo(pJob, &pPSSIInfo, &lLen)")
		return FALSE;
	}
	
	CString szSQL(_T(""));
	szSQL = _T("From JobPssiInfo");

	FIELDPARAM fpFieldList;
	for(int i=1; i<JOBPSSIINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobPSSIInfo_Field[i]);
	}
	
	BOOL bRet = TRUE;
	for (i = 0; i < lLen; i++)
	{
		DBTRACE_INFO(_T("set value"));
		RECORDSET rsRecordSet;
		//把结构体转化为记录链表
		//_variant_t vtValue;
		VARIANT vtValue;
		VariantInit(&vtValue);

 		//Field1 --- Index
	// 	vtValue.vt = VT_I4;
	// 	vtValue.lVal = 8;
	// 	rsRecordSet.push_back(vtValue);

		//Field2 --- JobID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = pJob->strJobID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field3 --- PatientID
		vtValue.vt = VT_BSTR;
		CString strPatientID = CBSTROpt::BSTRToCString(pPSSIInfo[i].bsPatientID);
		vtValue.bstrVal = strPatientID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field4 --- PatientName
		vtValue.vt = VT_BSTR;
		CString strPatientName = CBSTROpt::BSTRToCString(pPSSIInfo[i].bsPatientName);
		vtValue.bstrVal = strPatientName.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field5 --- StudyID
		vtValue.vt = VT_BSTR;
		CString strStudyID = CBSTROpt::BSTRToCString(pPSSIInfo[i].bsStudyID);
		vtValue.bstrVal = strStudyID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field6 --- SeriesID
		vtValue.vt = VT_BSTR;
		CString strSeriesID = CBSTROpt::BSTRToCString(pPSSIInfo[i].bsSeriesID);
		vtValue.bstrVal = strSeriesID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field7 --- ImageID
		vtValue.vt = VT_BSTR;
		CString strImageID = CBSTROpt::BSTRToCString(pPSSIInfo[i].bsImageID);
		vtValue.bstrVal = strImageID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		
		DBTRACE_INFO(_T("set value finished"));

		BOOL bResult(TRUE);
		try
		{
			bResult = m_DbBasisOpt.AddRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, rsRecordSet);		
		}
		catch(CDBException& err)
		{
			//err.ReportError();
			err.m_strError += _T(" -- catch error in AddPssiInfo interface !");
			PRINTTRACE_ERROR(err.m_strError);
		}
		

		if (!bResult)
		{
			bRet = FALSE;
			PRINTTRACE_ERROR(_T("m_DbBasisOpt.AddRecord() error"));
		}
	}
  
	//<< 释放PSSI结构
	CBSTROpt::FreePSSIStructList(pPSSIInfo, lLen);
	

	if (bRet)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CPADataBaseOpt::AddJobNetworkNodeInfo(PAJob* pJob)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	if (!(enumJobType_AutoSendJob == pJob->enumJobType
		|| enumJobType_ManualSendJob == pJob->enumJobType))
	{
		//<< 非发送任务
		return TRUE;
	}

	CString szSQL(_T(""));
	szSQL = _T("From JobNetworkNodeInfo");

	FIELDPARAM fpFieldList;
	for(int i=1; i<JOBNETWORKNODEINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobNetworkNodeInfo_Field[i]);
	}
	
	BOOL bRet = TRUE;
	vector<NetworkNodeStruct>& vtrNodes = ((TransferJobSettingsStruct*)pJob->pData)->vtrNodes;
	for (i = 0; i < vtrNodes.size(); i++)
	{
		DBTRACE_INFO(_T("set value"));
		RECORDSET rsRecordSet;
		//把结构体转化为记录链表
		//_variant_t vtValue;
		VARIANT vtValue;
		VariantInit(&vtValue);

 		//Field1 --- Index
	// 	vtValue.vt = VT_I4;
	// 	vtValue.lVal = 8;
	// 	rsRecordSet.push_back(vtValue);

		//Field2 --- JobID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = pJob->strJobID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field3 --- Default
		vtValue.vt = VT_BOOL;
		vtValue.boolVal = (VARIANT_BOOL)vtrNodes[i].bDefault;
		rsRecordSet.push_back(vtValue);

		//Field4 --- CalledAE
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrNodes[i].strCalledAE.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field5 --- CallingAE
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrNodes[i].strCallingAE.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field6 --- IP
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrNodes[i].strIP.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field7 --- Port
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrNodes[i].strPort.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field8 --- Raw
		vtValue.vt = VT_BOOL;
		vtValue.boolVal = (VARIANT_BOOL)vtrNodes[i].bRaw;
		rsRecordSet.push_back(vtValue);

		//Field9 --- Processed
		vtValue.vt = VT_BOOL;
		vtValue.boolVal = (VARIANT_BOOL)vtrNodes[i].bProcessed;
		rsRecordSet.push_back(vtValue);

		// Add [Sun hongwen 10/16/2009]
		vtValue.vt = VT_BOOL;
		vtValue.boolVal = (VARIANT_BOOL)vtrNodes[i].bSendPS;
		rsRecordSet.push_back(vtValue);
		//


		DBTRACE_INFO(_T("set value finished"));

		BOOL bResult(TRUE);
		try
		{
			bResult = m_DbBasisOpt.AddRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, rsRecordSet);		
		}
		catch(CDBException& err)
		{
			//err.ReportError();
			err.m_strError += _T(" -- catch error in AddJobNetworkNodeInfo interface !");
			PRINTTRACE_ERROR(err.m_strError);
		}


		if (!bResult)
		{
			bRet = FALSE;
			PRINTTRACE_ERROR(_T("m_DbBasisOpt.AddRecord() error"));
		}
	}
  
	
	if (bRet)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CPADataBaseOpt::AddJobDetailInfo(PAJob* pJob)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	

	CString szSQL(_T(""));
	szSQL = _T("From JobDetailInfo");

	FIELDPARAM fpFieldList;
	for(int i=1; i<JOBDETAILINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobDetailInfo_Field[i]);
	}
	
	BOOL bRet = TRUE;
	for (i = 0; i < pJob->vtrDetail.size(); i++)
	{
		DBTRACE_INFO(_T("set value"));
		RECORDSET rsRecordSet;
		//把结构体转化为记录链表
		//_variant_t vtValue;
		VARIANT vtValue;
		VariantInit(&vtValue);

 		//Field1 --- Index
	// 	vtValue.vt = VT_I4;
	// 	vtValue.lVal = 8;
	// 	rsRecordSet.push_back(vtValue);

		//Field2 --- JobID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = pJob->strJobID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field3 --- DateTime
		vtValue.vt = VT_DATE;
		COleDateTime odtDateTime;
		odtDateTime.SetDateTime(pJob->vtrDetail[i].stDateTime.wYear,pJob->vtrDetail[i].stDateTime.wMonth,pJob->vtrDetail[i].stDateTime.wDay, pJob->vtrDetail[i].stDateTime.wHour,pJob->vtrDetail[i].stDateTime.wMinute,pJob->vtrDetail[i].stDateTime.wSecond);
		vtValue.date = odtDateTime;
		rsRecordSet.push_back(vtValue);

		//Field4 --- Detail
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = pJob->vtrDetail[i].strDetail.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);


		DBTRACE_INFO(_T("set value finished"));

		BOOL bResult(TRUE);
		try
		{
			bResult = m_DbBasisOpt.AddRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, rsRecordSet);		
		}
		catch(CDBException& err)
		{
			//err.ReportError();
			err.m_strError += _T(" -- catch error in AddJob interface !");
			PRINTTRACE_ERROR(err.m_strError);
		}


		if (!bResult)
		{
			bRet = FALSE;
			PRINTTRACE_ERROR(_T("m_DbBasisOpt.AddRecord() error"));
		}
	}
  
	
	if (bRet)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CPADataBaseOpt::AddJobDiscImportImageInfo(PAJob* pJob)
{
	if (!m_bDBOpen)
	{
		return FALSE;
	}
	
	if (enumJobType_DiscImportJob != pJob->enumJobType)
	{
		//<< 非导入任务
		return TRUE;
	}


	CString szSQL(_T(""));
	szSQL = _T("From JobDiscImportImageInfo");

	FIELDPARAM fpFieldList;
	for(int i=1; i<JOBDISCIMPORTIMAGEINFO_TABLE_FIELD_NUM; i++)
	{
		fpFieldList.push_back(JobDiscImportImageInfo_Field[i]);
	}
	
	BOOL bRet = TRUE;
	vector<DiscImport_Image>& vtrImagesToBeImported = ((DiscImportJobSettingsStruct*)pJob->pData)->vtrImagesToBeImported;
	for (i = 0; i < vtrImagesToBeImported.size(); i++)
	{
		DBTRACE_INFO(_T("set value"));
		RECORDSET rsRecordSet;
		//把结构体转化为记录链表
		//_variant_t vtValue;
		VARIANT vtValue;
		VariantInit(&vtValue);

 		//Field1 --- Index
	// 	vtValue.vt = VT_I4;
	// 	vtValue.lVal = 8;
	// 	rsRecordSet.push_back(vtValue);

		//Field2 --- JobID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = pJob->strJobID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field3 --- ImageUID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strImageUID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field4 --- SeriesUID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strSeriesUID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field5 --- StudyUID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strStudyUID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field6 --- PatientUID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strPatientUID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field7 --- ImageIndex
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strIndex.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field8 --- PatientID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strPatientID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field9 --- PatientName
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strPatientName.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field10 --- StudyID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strStudyID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field11 --- SeriesID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strSeriesID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field12 --- ImageID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strImageID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field13 --- ReferencedFileID
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strReferencedFileID.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field14 --- State
		vtValue.vt = VT_I2;
		vtValue.iVal = (SHORT)vtrImagesToBeImported[i].enumState;
		rsRecordSet.push_back(vtValue);

		//Field15 --- Progress
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strProgress.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);

		//Field15 --- DetailInfo
		vtValue.vt = VT_BSTR;
		vtValue.bstrVal = vtrImagesToBeImported[i].strDetailInfo.AllocSysString();
		rsRecordSet.push_back(vtValue);
		VariantClear(&vtValue);


		DBTRACE_INFO(_T("set value finished"));

		BOOL bResult(TRUE);
		try
		{
			bResult = m_DbBasisOpt.AddRecord(m_pDBOpt->GetDBObject(), fpFieldList, szSQL, rsRecordSet);		
		}
		catch(CDBException& err)
		{
			//err.ReportError();
			err.m_strError += _T(" -- catch error in AddJobDiscImportImageInfo interface !");
			PRINTTRACE_ERROR(err.m_strError);
		}
		

		if (!bResult)
		{
			bRet = FALSE;
			PRINTTRACE_ERROR(_T("m_DbBasisOpt.AddRecord() error"));
		}
	}
  
	
	if (bRet)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CPADataBaseOpt::CompactDB(LPCTSTR szDBPath, LPCTSTR szPw, BOOL bBackUp)
{
	CString strTrace;

	// 数据库压缩修复功能
	CString strSrcDB = szDBPath; 
	CString strTmpDB = szDBPath + CString(_T(".tmp"));
	if (!CDirHandler::DeleteFile(strTmpDB))
	{
		strTrace.Format(_T("CDirHandler::DeleteFile(strTmpDB), &s"), strTmpDB);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	CString szDatabasePwd;
	szDatabasePwd.Format(_T(";Jet OLEDB:Database Password=%s;"), szPw);

	CString strSrc;
	CString strDst;
	strSrc = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") + strSrcDB + szDatabasePwd;
	strDst = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") + strTmpDB + szDatabasePwd;

	BSTR bsSrc = strSrc.AllocSysString();
	BSTR bsDst = strDst.AllocSysString();
	HRESULT hr = S_OK;
	try
	{	
		IJetEnginePtr jet(__uuidof(JetEngine));	
		hr = jet->CompactDatabase(bsSrc, bsDst);
	}
	catch(_com_error &e) 
	{       
		//MessageBox(NULL, (LPCTSTR)e.Description( ), _T(""), MB_OK);  
		PRINTTRACE_ERROR((LPCTSTR)e.Description( ))
		
		CBSTROpt::FreeBSTR(bsSrc);
		CBSTROpt::FreeBSTR(bsDst);
		return FALSE;
	}

	CBSTROpt::FreeBSTR(bsSrc);
	CBSTROpt::FreeBSTR(bsDst);

	if (S_OK == hr)
	{
		//<< 备份或删除原DB文件，并将临时DB文件名修改为原DB文件名
		if (bBackUp)
		{
			//<< 需要备份原数据库
			SYSTEMTIME st;
			::GetLocalTime(&st);
			CString strBackUpTime;
			strBackUpTime.Format(_T("%04d%02d%02d%02d%02d%02d%03d"), st.wYear, st.wMonth,
				st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		
			CString strBackUpDBPath = strSrcDB + _T(".") + strBackUpTime;
			CFile::Rename(strSrcDB, strBackUpDBPath);

			//<< 将临时DB文件名修改为原DB文件名
			CFile::Rename(strTmpDB, strSrcDB);
			return TRUE;
		}
		else
		{
			//<< 删除原数据库
			if (CDirHandler::DeleteFile(strSrcDB))
			{
				CFile::Rename(strTmpDB, strSrcDB);
				return TRUE;
			}
			else
			{
				strTrace.Format(_T("CDirHandler::DeleteFile(strSrcDB), &s"), strSrcDB);
				PRINTTRACE_ERROR(strTrace)

				if (!CDirHandler::DeleteFile(strTmpDB))
				{
					strTrace.Format(_T("CDirHandler::DeleteFile(strTmpDB), &s"), strTmpDB);
					PRINTTRACE_ERROR(strTrace)
				}

				return FALSE;
			}
		}
	}
	else
	{
		strTrace.Format(_T("hr = jet->CompactDatabase(bsSrc, bsDst), hr=%0x8d"), hr);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

}
