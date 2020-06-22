/* Time: <@(#)DBController.cpp   2009-3-5 - 10:35:15   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DBController.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Communication class with DB
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:35:15		FanZF	Creation
 *
 *********************************************************************
 */

// DBController.cpp: implementation of the CDBController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ASBasis.h"
#include "DBController.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDBController* CDBController::m_pInstance = NULL;

CDBController::CDBController()
{
	m_pIDBPIM = NULL;
	m_pIDBConfig = NULL;
	m_pIDBSession = NULL;
	m_pIGeneral = NULL;

	m_pConfigInfo = NULL;

	m_pJob = FALSE;

	m_bEnableGetJobInfo = TRUE;

	m_DBWorkState= enumWORKSTATE_UNKNOWN;

}

CDBController::~CDBController()
{
}

CDBController* CDBController::GetInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDBController;
	}

	return m_pInstance;
}

void CDBController::ReleaseInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

BOOL CDBController::Init()
{
	PRINTTRACE_ENTER_FUNCTION
		
	if(NULL == m_pIDBPIM)
	{		
		if(CoCreateInstance(CLSID_DBPIM,
							NULL, 
							CLSCTX_LOCAL_SERVER,
							IID_IDBPIM,
							(LPVOID*)&m_pIDBPIM) != S_OK)
		{
			PRINTTRACE_ERROR("ERROR: CoCreateInstance m_pIDBPIM");
			return FALSE ;
		}
	}
	if(NULL == m_pIDBConfig)
	{
		if(CoCreateInstance(CLSID_DBConfig,
							NULL, 
							CLSCTX_LOCAL_SERVER,
							IID_IDBConfig,
							(LPVOID*)&m_pIDBConfig) != S_OK)
		{
			PRINTTRACE_ERROR("ERROR: CoCreateInstance m_pIDBConfig");
			return FALSE ;
		}
	}
	if(NULL == m_pIDBSession)
	{
		if(CoCreateInstance(CLSID_DBSession,
							NULL,
							CLSCTX_LOCAL_SERVER,
							IID_IDBSession,
							(LPVOID*)&m_pIDBSession) != S_OK)
		{
			PRINTTRACE_ERROR("ERROR: CoCreateInstance m_pIDBSession");
			return FALSE ;
		}
	}
	
	if(NULL == m_pIGeneral)
	{
		if(CoCreateInstance(CLSID_DBSession,
							NULL,
							CLSCTX_LOCAL_SERVER,
							IID_IGeneralInterface,
							(LPVOID*)&m_pIGeneral) != S_OK)
		{
			PRINTTRACE_ERROR("ERROR: CoCreateInstance m_pIGeneral");
			return FALSE ;
		}
	}

	if (!m_DBSink.SetConnection(CLSID_DBSession, IID_IGeneralEvent))
	{
		PRINTTRACE_ERROR("ERROR: m_DBSink.SetConnection()");
		return FALSE ;
	}

	HRESULT hResult = m_pIGeneral->GetWorkState(&m_DBWorkState);
	if (S_OK != hResult)
	{
		PRINTTRACE_ERROR("ERROR: m_pIGeneral->GetWorkState(&m_DBWorkState)");
		return FALSE;
	}

	PRINTTRACE_LEAVE_FUNCTION
	return TRUE;

}

BOOL CDBController::UnInit()
{
	BOOL bRet = TRUE;

	if (m_pIDBPIM)
	{
		m_pIDBPIM->Release();
		m_pIDBPIM = NULL;
	}
	if (m_pIDBConfig)
	{
		m_pIDBConfig->Release();
		m_pIDBConfig = NULL;
	}
	if (m_pIDBSession)
	{
		m_pIDBSession->Release();
		m_pIDBSession = NULL;
	}
	if (m_pIGeneral)
	{
		m_pIGeneral->Release();
		m_pIGeneral = NULL;
	}

	if (m_pConfigInfo)
	{
		CBSTROpt::FreeConfigInfoStruct(m_pConfigInfo);
		delete m_pConfigInfo;
		m_pConfigInfo = NULL;
	}

	if (!m_DBSink.ReleaseConnection())
	{
		bRet = FALSE;
	}

	m_pJob = NULL;

	m_DBWorkState = enumWORKSTATE_UNKNOWN;

	return bRet;
}

void CDBController::DisableGetJobInfo()
{
	m_bEnableGetJobInfo = FALSE;
}

ConfigInfoStruct* CDBController::GetConfigInfo()
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	if (NULL == m_pConfigInfo)
	{
		if (enumWORKSTATE_WORKING != m_DBWorkState)
		{
			PRINTTRACE_ERROR("enumSTARTUPRESULT_SUCCESS != m_DBStartUpResult")
			sLock.Unlock();
			return NULL;
		}

		m_pConfigInfo = new ConfigInfoStruct;
		HRESULT hResult = m_pIDBConfig->GetConfigInfo(m_pConfigInfo);
		if (S_OK != hResult)
		{
			delete m_pConfigInfo;
			m_pConfigInfo = NULL;

			PRINTTRACE_ERROR(_T("ERROR: m_pIDBConfig->GetConfigInfo(m_pConfigInfo)"));
			sLock.Unlock();
			return NULL;
		}
	}

	sLock.Unlock();
	return m_pConfigInfo;
}

BOOL CDBController::IsPatientUIDExistsInDB(LPCTSTR szPatientUID, BOOL* pbExist)
{
	if (NULL == szPatientUID || NULL == pbExist)
	{
		return FALSE;
	}

	BSTR bsPatientUID = CString(szPatientUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->IsPatientExist(bsPatientUID, pbExist);
	CBSTROpt::FreeBSTR(bsPatientUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

BOOL CDBController::IsPatientIDExistsInDB(LPCTSTR szPatientID, BOOL* pbExist)
{
	if (NULL == szPatientID || NULL == pbExist)
	{
		return FALSE;
	}

	BSTR bsPatientID = CString(szPatientID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->IsPatientIDExist(bsPatientID, pbExist);
	CBSTROpt::FreeBSTR(bsPatientID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::IsStudyUIDExistsInDB(LPCTSTR szStudyUID, BOOL* pbExist)
{
	if (NULL == szStudyUID || NULL == pbExist)
	{
		return FALSE;
	}

	BSTR bsStudyUID = CString(szStudyUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->IsStudyExist(bsStudyUID, pbExist);
	CBSTROpt::FreeBSTR(bsStudyUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

BOOL CDBController::IsSeriesUIDExistsInDB(LPCTSTR szSeriesUID, BOOL* pbExist)
{
	if (NULL == szSeriesUID || NULL == pbExist)
	{
		return FALSE;
	}

	BSTR bsSeriesUID = CString(szSeriesUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->IsSeriesExist(bsSeriesUID, pbExist);
	CBSTROpt::FreeBSTR(bsSeriesUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

BOOL CDBController::IsImageUIDExistsInDB(LPCTSTR szImageUID, BOOL* pbExist)
{
	if (NULL == szImageUID || NULL == pbExist)
	{
		return FALSE;
	}

	BSTR bsImageUID = CString(szImageUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->IsImageExist(bsImageUID, pbExist);
	CBSTROpt::FreeBSTR(bsImageUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CDBController::SetDBWorkState(WORKSTATE enumWorkState)
{
	m_DBWorkState = enumWorkState;
}

BOOL CDBController::GetJobImageInfoByUIDs(vector<CString>* pvtrUID,
										PatientAdminUIDType enumUIDType,
										PAJob* pJob)
{
	CSingleLock sLock(&m_CSLock);
	sLock.Lock();

	if (NULL == pvtrUID ||
		NULL == pJob)
	{
		PRINTTRACE_ERROR("NULL == pvtrUID || NULL == pJob")
		sLock.Unlock();
		return FALSE;
	}

	if (0 == pvtrUID->size())
	{
		PRINTTRACE_ERROR("0 == pvtrUID->size()")
		sLock.Unlock();
		return FALSE;
	}

	m_bEnableGetJobInfo = TRUE;

	m_pJob = pJob;

	BOOL bRet = TRUE;
	HRESULT hResult = S_OK;

	if (enumWORKSTATE_WORKING != m_DBWorkState)
	{
		PRINTTRACE_ERROR("enumWORKSTATE_WORKING != m_DBWorkState")
		sLock.Unlock();
		return FALSE;
	}

	// Get Config Info
	if (NULL == m_pConfigInfo)
	{
		m_pConfigInfo = new ConfigInfoStruct;
		hResult = m_pIDBConfig->GetConfigInfo(m_pConfigInfo);
		if (S_OK != hResult)
		{
			delete m_pConfigInfo;
			m_pConfigInfo = NULL;

			PRINTTRACE_ERROR(_T("ERROR: m_pIDBConfig->GetConfigInfo(m_pConfigInfo)"));
			sLock.Unlock();
			return FALSE;
		}
	}

	//<< 获得UID父辈信息，不包含自身


	HRESULT hr = S_OK;

	switch (enumUIDType)
	{
	case enumPatientAdminUIDType_Image:
		{
			CString strImageUID = _T("");
			//后处理的手动发送，是跨Series的，所以需要进行循环处理GaoXing [7/8/2011]
			for(int i = 0; i< pvtrUID->size(); i++)
			{
				strImageUID = (*pvtrUID)[i];
				
				CString szTemp;
				szTemp.Format(_T("CDBController::GetJobImageInfoByUIDs Image UID[%d]"), i);
				szTemp += strImageUID;
				PRINTTRACE_INFO(szTemp);
				
				BSTR bsImageUID = strImageUID.AllocSysString();
				//<< 图像信息结构
				ImageInfoStruct aImageInfo;
				hr = m_pIDBPIM->GetImageInfo(bsImageUID, &aImageInfo);
				CBSTROpt::FreeBSTR(bsImageUID);
				
				szTemp = CBSTROpt::BSTRToCString(aImageInfo.bsSeriesUID);
				szTemp = "SeriseUID : " + szTemp;
				PRINTTRACE_INFO(szTemp);
				
				if (S_OK == hr)
				{
					//<< 序列信息结构
					SeriesInfoStruct aSeriesInfo;
					hr = m_pIDBPIM->GetSeriesInfo(aImageInfo.bsSeriesUID, &aSeriesInfo);
					
					szTemp = CBSTROpt::BSTRToCString(aSeriesInfo.bsStudyUID);
					szTemp = "StudyUID : " + szTemp;
					PRINTTRACE_INFO(szTemp);
					
					if (S_OK == hr)
					{
						m_pJob->vtrSeries.push_back(aSeriesInfo);
						//<< 检查信息结构
						StudyInfoStruct aStudyInfo;
						hr = m_pIDBPIM->GetStudyInfo(aSeriesInfo.bsStudyUID, &aStudyInfo);
						
						szTemp = CBSTROpt::BSTRToCString(aStudyInfo.bsPatientUID);
						szTemp = "PatientUID : " + szTemp;
						PRINTTRACE_INFO(szTemp);
						
						if (S_OK == hr)
						{
							m_pJob->vtrStudy.push_back(aStudyInfo);
							//<< 患者信息结构
							PatientInfoStruct aPatientInfo;
							hr = m_pIDBPIM->GetPatientInfo(aStudyInfo.bsPatientUID, &aPatientInfo);
							
							CString szTemp;
							szTemp.Format(_T("GetPatientInfo result: 0X%X"), hr);
							PRINTTRACE_INFO(szTemp);
							
							
							if (S_OK == hr)
							{
								m_pJob->vtrPatient.push_back(aPatientInfo);
							}
							else
							{
								bRet = FALSE;
								
								szTemp = CBSTROpt::BSTRToCString(aPatientInfo.bsPatientID);
								szTemp = "PatientID is : " + szTemp;
								PRINTTRACE_ERROR(szTemp);
								szTemp = CBSTROpt::BSTRToCString(aPatientInfo.bsPatientName);
								szTemp = "PatientName is : " + szTemp;
								PRINTTRACE_ERROR(szTemp)
									PRINTTRACE_ERROR("m_pIDBPIM->GetPatientInfo")
							}
						}
						else
						{
							bRet = FALSE;
							PRINTTRACE_ERROR("m_pIDBPIM->GetStudyInfo()")
						}
					}
					else
					{
						bRet = FALSE;
						PRINTTRACE_ERROR("m_pIDBPIM->GetSeriesInfo()")
					}
					
					//<< 此结构此时并不push入Job，故需释放
					CBSTROpt::FreeImageInfoStruct(&aImageInfo);
				}
				else
				{
					bRet = FALSE;
					PRINTTRACE_ERROR("m_pIDBPIM->GetImageInfo()")
				}	
			}
		}
		break;

	case enumPatientAdminUIDType_Series:
		{
			CString strSeriesUID = (*pvtrUID)[0];
			BSTR bsSeriesUID = strSeriesUID.AllocSysString();
			//<< 序列信息结构
			SeriesInfoStruct aSeriesInfo;
			hr = m_pIDBPIM->GetSeriesInfo(bsSeriesUID, &aSeriesInfo);
			CBSTROpt::FreeBSTR(bsSeriesUID);
			if (S_OK == hr)
			{
				//<< 检查信息结构
				StudyInfoStruct aStudyInfo;
				hr = m_pIDBPIM->GetStudyInfo(aSeriesInfo.bsStudyUID, &aStudyInfo);
				if (S_OK == hr)
				{
					m_pJob->vtrStudy.push_back(aStudyInfo);
					//<< 患者信息结构
					PatientInfoStruct aPatientInfo;
					hr = m_pIDBPIM->GetPatientInfo(aStudyInfo.bsPatientUID, &aPatientInfo);
					if (S_OK == hr)
					{
						m_pJob->vtrPatient.push_back(aPatientInfo);
					}
					else
					{
						bRet = FALSE;
						PRINTTRACE_ERROR("m_pIDBPIM->GetPatientInfo")
					}
				}
				else
				{
					bRet = FALSE;
					PRINTTRACE_ERROR("m_pIDBPIM->GetStudyInfo()")
				}

				//<< 此结构此时并不push入Job，故需释放
				CBSTROpt::FreeSeriesInfoStruct(&aSeriesInfo);
			}
			else
			{
				bRet = FALSE;
				PRINTTRACE_ERROR("m_pIDBPIM->GetSeriesInfo()")
			}
		}
		break;

	case enumPatientAdminUIDType_Study:
		{
			CString strStudyUID = (*pvtrUID)[0];
			BSTR bsStudyUID = strStudyUID.AllocSysString();

			//<< 检查信息结构
			StudyInfoStruct aStudyInfo;
			hr = m_pIDBPIM->GetStudyInfo(bsStudyUID, &aStudyInfo);
			CBSTROpt::FreeBSTR(bsStudyUID);
			if (S_OK == hr)
			{
				//<< 患者信息结构
				PatientInfoStruct aPatientInfo;
				hr = m_pIDBPIM->GetPatientInfo(aStudyInfo.bsPatientUID, &aPatientInfo);
				if (S_OK == hr)
				{
					m_pJob->vtrPatient.push_back(aPatientInfo);
				}
				else
				{
					bRet = FALSE;
					PRINTTRACE_ERROR("m_pIDBPIM->GetPatientInfo")
				}

				//<< 此结构此时并不push入Job，故需释放
				CBSTROpt::FreeStudyInfoStruct(&aStudyInfo);
			}
			else
			{
				bRet = FALSE;
				PRINTTRACE_ERROR("m_pIDBPIM->GetSeriesInfo()")
			}
		}
		
	case enumPatientAdminUIDType_Patient:
		//<< Here, do nothing
		break;

	default:
		bRet = FALSE;
		break;
	}

	if (!IsGetJobInfoEnabled())
	{
		bRet = FALSE;
	}

	//<< Error
	if (!bRet)
	{
		sLock.Unlock();
		return bRet;
	}

	//<< 获得UID自身结构及所有〈子〉信息结构

	for (int i = 0; i < pvtrUID->size(); i++)
	{
		if (!IsGetJobInfoEnabled())
		{
			bRet = FALSE;
			break;
		}

		switch (enumUIDType)
		{
		case enumPatientAdminUIDType_Patient:
			{
				BSTR bsPatientUID = (*pvtrUID)[i].AllocSysString();
				PatientInfoStruct aPatientInfo;
				hr = m_pIDBPIM->GetPatientInfo(bsPatientUID, &aPatientInfo);
				CBSTROpt::FreeBSTR(bsPatientUID);
				if (S_OK == hr)
				{
					m_pJob->vtrPatient.push_back(aPatientInfo);
					//<< 添加〈子〉
					bRet = AddJobImageInfoByPatientUID((*pvtrUID)[i]);
					if (bRet)
					{
						PRINTTRACE_INFO("AddJobImageInfoByPatientUIDBFS")
					}
					else
					{
						bRet = FALSE;
						PRINTTRACE_ERROR("AddJobImageInfoByPatientUIDBFS")
					}

				}
				else
				{
					bRet = FALSE;
					PRINTTRACE_ERROR("m_pIDBPIM->GetPatientInfo")
				}

			}
			break;

		case enumPatientAdminUIDType_Study:
			{
				BSTR bsStudyUID = (*pvtrUID)[i].AllocSysString();
				StudyInfoStruct aStudyInfo;
				hr = m_pIDBPIM->GetStudyInfo(bsStudyUID, &aStudyInfo);
				CBSTROpt::FreeBSTR(bsStudyUID);
				if (S_OK == hr)
				{
					m_pJob->vtrStudy.push_back(aStudyInfo);
					bRet = AddJobImageInfoByStudyUID((*pvtrUID)[i]);
					if (bRet)
					{
						PRINTTRACE_INFO("AddJobImageInfoByStudyUIDBFS")
					}
					else
					{
						bRet = FALSE;
						PRINTTRACE_ERROR("AddJobImageInfoByStudyUIDBFS")
					}
				}
				else
				{
					bRet = FALSE;
					PRINTTRACE_ERROR("m_pIDBPIM->GetStudyInfo")
				}
			}
			break;

		case enumPatientAdminUIDType_Series:
			{
				BSTR bsSeriesUID = (*pvtrUID)[i].AllocSysString();
				SeriesInfoStruct aSeriesInfo;
				hr = m_pIDBPIM->GetSeriesInfo(bsSeriesUID, &aSeriesInfo);
				CBSTROpt::FreeBSTR(bsSeriesUID);
				if (S_OK == hr)
				{
					m_pJob->vtrSeries.push_back(aSeriesInfo);
					bRet = AddJobImageInfoBySeriesUID((*pvtrUID)[i]);
					if (bRet)
					{
						PRINTTRACE_INFO("AddJobImageInfoBySeriesUIDBFS")
					}
					else
					{
						bRet = FALSE;
						PRINTTRACE_ERROR("AddJobImageInfoBySeriesUIDBFS")
					}
				}
				else
				{
					bRet = FALSE;
					PRINTTRACE_ERROR("m_pIDBPIM->GetSeriesInfo")
				}
			}
			break;
			
		case enumPatientAdminUIDType_Image:
			{
				BSTR bsImageUID = (*pvtrUID)[i].AllocSysString();
				ImageInfoStruct aImageInfo;
				hr = m_pIDBPIM->GetImageInfo(bsImageUID, &aImageInfo);
				CBSTROpt::FreeBSTR(bsImageUID);
				if (S_OK == hr)
				{
					m_pJob->vtrImages.push_back(aImageInfo);
					bRet = AddJobImageInfoByImageUID((*pvtrUID)[i]);
					if (bRet)
					{
						PRINTTRACE_INFO("AddJobImageInfoByImageUID")
					}
					else
					{
						bRet = FALSE;
						PRINTTRACE_ERROR("AddJobImageInfoByImageUID")
					}
				}
				else
				{
					bRet = FALSE;
					PRINTTRACE_ERROR("m_pIDBPIM->GetImagenfo")
				}
			}
			break;

		default:
			bRet = FALSE;
			break;
		}

		if (!bRet)
		{
			break;
		}
	}

	sLock.Unlock();
	return bRet;
}

BOOL CDBController::AddJobImageInfoByPatientUID(LPCTSTR szPatientUID)
{
	if (NULL == szPatientUID)
	{
		PRINTTRACE_ERROR("NULL == szPatientUID")
		return FALSE;
	}

	HRESULT hResult = S_OK;
	BOOL bRet = TRUE;

	CString strPatientUID = szPatientUID;

	CString strTrace;
	long lCount = 0;
	StudyInfoStruct* pStudyList = NULL;

	BSTR bsPatientUID = strPatientUID.AllocSysString();
	hResult = m_pIDBPIM->GetStudyListByPatientUID(bsPatientUID, &lCount, &pStudyList);
	CBSTROpt::FreeBSTR(bsPatientUID);
	strTrace.Format(_T("m_pIDBPIM->GetSeriesListByStudyUID, PatientUID = %s"), strPatientUID);
	if (S_OK != hResult)
	{
		PRINTTRACE_ERROR(strTrace);
		bRet = FALSE;
	}
	else
	{
		PRINTTRACE_INFO(strTrace)
		
		for (int i = 0; i < lCount; i++)
		{
			m_pJob->vtrStudy.push_back(*(pStudyList + i));
		}

		for (i = 0; i < lCount; i++)
		{
			CString strStudyUID = CBSTROpt::BSTRToCString((pStudyList+i)->bsStudyUID);
			bRet = AddJobImageInfoByStudyUID(strStudyUID);
			if (bRet)
			{
				PRINTTRACE_INFO("AddJobImageInfoByStudyUID")
			}
			else
			{
				PRINTTRACE_ERROR("AddJobImageInfoByStudyUID")
				break;
			}

			if (!IsGetJobInfoEnabled())
			{
				bRet = FALSE;
				break;
			}
		}
	}
		
	if (NULL != pStudyList)
	{
		CoTaskMemFree(pStudyList);
	}

	return bRet;
}

BOOL CDBController::AddJobImageInfoByStudyUID(LPCTSTR szStudyUID)
{
	if (NULL == szStudyUID)
	{
		PRINTTRACE_ERROR("NULL == szPatientUID")
		return FALSE;
	}

	HRESULT hResult = S_OK;
	BOOL bRet = TRUE;

	CString strStudyUID = szStudyUID;
	CString strTrace;

	BSTR bsStudyUID = strStudyUID.AllocSysString();
	SeriesInfoStruct* pSeriesList = NULL;
	long lCount = 0;
	hResult = m_pIDBPIM->GetSeriesListByStudyUID(bsStudyUID, &lCount, &pSeriesList);
	CBSTROpt::FreeBSTR(bsStudyUID);
	strTrace.Format(_T("m_pIDBPIM->GetAllSeriesInfoByStudyUID, StudyUID = %s"), strStudyUID);
	if (S_OK != hResult)
	{
		PRINTTRACE_ERROR(strTrace);
		bRet = FALSE;
	}
	else
	{
		PRINTTRACE_INFO(strTrace)
		
		for (int i = 0; i < lCount; i++)
		{
			m_pJob->vtrSeries.push_back(*(pSeriesList + i));
		}

		for (i = 0; i < lCount; i++)
		{
			CString strSeriesUID = CBSTROpt::BSTRToCString((pSeriesList+i)->bsSeriesUID);
			bRet = AddJobImageInfoBySeriesUID(strSeriesUID);
			if (bRet)
			{
				PRINTTRACE_INFO("AddJobImageInfoBySeriesUID")
			}
			else
			{
				PRINTTRACE_ERROR("AddJobImageInfoBySeriesUID")
				break;
			}

			if (!IsGetJobInfoEnabled())
			{
				bRet = FALSE;
				break;
			}
		}
	}
		
	if (NULL != pSeriesList)
	{
		CoTaskMemFree(pSeriesList);
	}

	return bRet;
}

BOOL CDBController::AddJobImageInfoBySeriesUID(LPCTSTR szSereisUID)
{
	if (NULL == szSereisUID)
	{
		PRINTTRACE_ERROR("NULL == szSereisUID")
		return FALSE;
	}

	HRESULT hResult = S_OK;
	BOOL bRet = TRUE;

	CString strSeriesUID = szSereisUID;
	CString strTrace;

	BSTR bsSeriesUID = strSeriesUID.AllocSysString();
	ImageInfoStruct* pImagesList = NULL;
	long lCount = 0;
	hResult = m_pIDBPIM->GetImageListBySeriesUID(bsSeriesUID, &lCount, &pImagesList);
	CBSTROpt::FreeBSTR(bsSeriesUID);
	strTrace.Format(_T("m_pIDBPIM->GetImageListBySeriesUID, SeriesUID = %s"), strSeriesUID);
	if (S_OK != hResult)
	{
		PRINTTRACE_ERROR(strTrace);
		bRet = FALSE;
	}
	else
	{
		PRINTTRACE_INFO(strTrace)
		
		for (int i = 0; i < lCount; i++)
		{
			m_pJob->vtrImages.push_back(*(pImagesList + i));
		}

		for (i = 0; i < lCount; i++)
		{
			CString strImageUID = CBSTROpt::BSTRToCString((pImagesList+i)->bsImageUID);
			bRet = AddJobImageInfoByImageUID(strImageUID);
			if (bRet)
			{
				//PRINTTRACE_INFO("AddJobImageInfoByImageUID")
			}
			else
			{
				PRINTTRACE_ERROR("AddJobImageInfoByImageUID")
				break;
			}

			if (!IsGetJobInfoEnabled())
			{
				bRet = FALSE;
				break;
			}
		}
	}

	if (NULL != pImagesList)
	{
		CoTaskMemFree(pImagesList);
	}
		
	return bRet;
}

BOOL CDBController::AddJobImageInfoByImageUID(LPCTSTR szImageUID)
{
	if (NULL == szImageUID)
	{
		return FALSE;
	}

	HRESULT hr = S_OK;
	CString strImageUID = szImageUID;
	BSTR bsImageUID = strImageUID.AllocSysString();

	PostProcessingInfo aPostInfo;
	hr = m_pIDBPIM->GetPostProcessingInfo(bsImageUID, &aPostInfo);
	CBSTROpt::FreeBSTR(bsImageUID);
	if (S_OK == hr)
	{
		m_pJob->vtrPostProcess.push_back(aPostInfo);

		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR("m_pIDBPIM->GetPostProcessingInfo")

		return FALSE;
	}
}

SeriesInfoStruct* CDBController::GetSereisInfoStruct(LPCTSTR szSeriesUID, vector<SeriesInfoStruct>* pvtrSereis)
{
	for (int i = 0; i < pvtrSereis->size(); i++)
	{
		CString strSeriesUID = CBSTROpt::BSTRToCString((*pvtrSereis)[i].bsSeriesUID);
		if (!strSeriesUID.CompareNoCase(szSeriesUID))
			return &(*pvtrSereis)[i];
	}

	return NULL;
}

BOOL CDBController::IsImageUIDExisted(vector<ImageInfoStruct>* pvtrImage, LPCTSTR szDstImageUID)
{
	return FALSE;
}

BOOL CDBController::IsSeriesUIDExisted(vector<SeriesInfoStruct>* pvtrSeries, LPCTSTR szDstSeriesUID)
{
	for (int i = 0; i < pvtrSeries->size(); i++)
	{
		CString strSeriesUID = CBSTROpt::BSTRToCString((*pvtrSeries)[i].bsSeriesUID);
		CString strTrace = _T("IsSeriesUIDExisted, compare: ");
		strTrace += strSeriesUID;
		strTrace += _T(" and ");
		strTrace += szDstSeriesUID;
		PRINTTRACE_INFO(strTrace);
		if (!strSeriesUID.CompareNoCase(szDstSeriesUID))
			return TRUE;
	}

	return FALSE;
}

BOOL CDBController::IsStudyUIDExisted(vector<StudyInfoStruct>* pvtrStudy, LPCTSTR szDstStudyUID)
{
	for (int i = 0; i < pvtrStudy->size(); i++)
	{
		CString strStudyUID = CBSTROpt::BSTRToCString((*pvtrStudy)[i].bsStudyUID);
		CString strTrace = _T("IsStudysUIDExisted, compare: ");
		strTrace += strStudyUID;
		strTrace += _T(" and ");
		strTrace += szDstStudyUID;
		PRINTTRACE_INFO(strTrace);
		if (!strStudyUID.CompareNoCase(szDstStudyUID))
			return TRUE;
	}

	return FALSE;
}

BOOL CDBController::IsPatientUIDExisted(vector<PatientInfoStruct>* pvtrPatient, LPCTSTR szDstPatientUID)
{
	for (int i = 0; i < pvtrPatient->size(); i++)
	{
		CString strPatientUID = CBSTROpt::BSTRToCString((*pvtrPatient)[i].bsPatientUID);
		CString strTrace = _T("IsStudysUIDExisted, compare: ");
		strTrace += strPatientUID;
		strTrace += _T(" and ");
		strTrace += szDstPatientUID;
		PRINTTRACE_INFO(strTrace);
		if (!strPatientUID.CompareNoCase(szDstPatientUID))
			return TRUE;
	}

	return FALSE;
}


BOOL CDBController::IsGetJobInfoEnabled()
{
	if (!m_bEnableGetJobInfo)
	{
		PRINTTRACE_WARNING("FALSE == m_bEnableGetJobInfo")
	}

	return m_bEnableGetJobInfo;
}

BOOL CDBController::GetPatientInfo(LPCTSTR szPatientUID, PatientInfoStruct* pPatient)
{
	if (NULL == szPatientUID || NULL == pPatient)
	{	
		return FALSE;
	}

	BSTR bsPatientUID = CString(szPatientUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->GetPatientInfo(bsPatientUID, pPatient);
	CBSTROpt::FreeBSTR(bsPatientUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::GetPatientInfoByID(LPCTSTR szPatientID, PatientInfoStruct* pPatient)
{
	if (NULL == szPatientID || NULL == pPatient)
	{
		return FALSE;
	}

	BSTR bsPatientUID = CString(szPatientID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->GetPatientInfoByID(bsPatientUID, pPatient);
	CBSTROpt::FreeBSTR(bsPatientUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::GetStudyInfo(LPCTSTR szStudyUID, StudyInfoStruct* pStudy)
{
	if (NULL == szStudyUID || NULL == pStudy)
	{
		return FALSE;
	}

	BSTR bsStudyUID = CString(szStudyUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->GetStudyInfo(bsStudyUID, pStudy);
	CBSTROpt::FreeBSTR(bsStudyUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::GetSeriesInfo(LPCTSTR szSeriesUID, SeriesInfoStruct* pSeries)
{
	if (NULL == szSeriesUID || NULL == pSeries)
	{
		return FALSE;
	}

	BSTR bsStudyUID = CString(szSeriesUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->GetSeriesInfo(bsStudyUID, pSeries);
	CBSTROpt::FreeBSTR(bsStudyUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::GetPostProcessInfo(LPCTSTR szImageUID, PostProcessingInfo* pPostInfo)
{
	if (NULL == szImageUID || NULL == pPostInfo)
	{
		return FALSE;
	}

	BSTR bsImageUID = CString(szImageUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->GetPostProcessingInfo(bsImageUID, pPostInfo);
	CBSTROpt::FreeBSTR(bsImageUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::IsStudyInstanceUIDExists(LPCTSTR szStudyInstanceUID, BOOL* pbExist)
{
	if (NULL == szStudyInstanceUID || NULL == pbExist)
	{
		return FALSE;
	}

	BSTR bsStudyInstanceUID = CString(szStudyInstanceUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->IsInstanceUIDExist(bsStudyInstanceUID, pbExist);
	CBSTROpt::FreeBSTR(bsStudyInstanceUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::GetStudyUIDByInstanceUID(LPCTSTR szStudyInstanceUID, CString& strStudyUID)
{
	if (NULL == szStudyInstanceUID)
	{
		return FALSE;
	}

	BSTR bsStudyInstanceUID = CString(szStudyInstanceUID).AllocSysString();
	BSTR bsStudyUID;
	HRESULT hResult = m_pIDBPIM->GetStudyUIDByInstanceUID(bsStudyInstanceUID, &bsStudyUID);
	CBSTROpt::FreeBSTR(bsStudyInstanceUID);
	if (S_OK == hResult)
	{
		strStudyUID = CBSTROpt::BSTRToCString(bsStudyUID);
		CBSTROpt::FreeBSTR(bsStudyUID);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

BOOL CDBController::GetMPPSStatusByStudyInstanceUID(LPCTSTR szStudyInstanceUID, WorkListStatus* penumStatus)
{
	if (NULL == szStudyInstanceUID || NULL == penumStatus)
	{
		return FALSE;
	}

	BOOL bExist = FALSE;
	BSTR bsStudyInstanceUID = CString(szStudyInstanceUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->IsInstanceUIDExist(bsStudyInstanceUID, &bExist);
	CBSTROpt::FreeBSTR(bsStudyInstanceUID);
	if (S_OK == hResult)
	{
		if (!bExist)
		{
			*penumStatus = enumWorkListStatus_NotImported;
			return TRUE;
		}
		else
		{
			// should query from DB if MPPS is added in P&A
			*penumStatus = enumWorkListStatus_Imported;

			bsStudyInstanceUID = CString(szStudyInstanceUID).AllocSysString();
			BSTR bsStudyUID;
			hResult = m_pIDBPIM->GetStudyUIDByInstanceUID(bsStudyInstanceUID, &bsStudyUID);
			CBSTROpt::FreeBSTR(bsStudyInstanceUID);
			if (S_OK == hResult)
			{
				StudyInfoStruct StudyStruct;
				hResult = m_pIDBPIM->GetStudyInfo(bsStudyUID, &StudyStruct);
				CBSTROpt::FreeBSTR(bsStudyUID);
				if (S_OK == hResult)
				{
					switch(StudyStruct.enumMPPSState)
					{
					case enumMPPSStatus_NotImported:
						*penumStatus = enumWorkListStatus_NotImported;
						break;
					case enumMPPSStatus_Imported:
						*penumStatus = enumWorkListStatus_Imported;
						break;
					case enumMPPSStatus_InProgress:
						*penumStatus = enumWorkListStatus_InProgress;
					    break;
					case enumMPPSStatus_Discontinued:
						*penumStatus = enumWorkListStatus_Discontinued;
					    break;
					case enumMPPSStatus_Completed:
						*penumStatus = enumWorkListStatus_Completed;
					    break;
					default:
						return FALSE;
					}
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
		}
	}
	else
	{
		return FALSE;
	}

}

BOOL CDBController::AddPatientRecordToDB(PatientInfoStruct* pPatient)
{
	if (NULL == pPatient)
	{
		return FALSE;
	}

	HRESULT hResult = m_pIDBPIM->ImportPatientInfo(*pPatient);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::AddStudyRecordToDB(StudyInfoStruct* pStudy)
{
	if (NULL == pStudy)
	{
		return FALSE;
	}

	HRESULT hResult = m_pIDBPIM->ImportStudyInfo(*pStudy);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::AddSeriesRecordToDB(SeriesInfoStruct* pSeries)
{
	if (NULL == pSeries)
	{
		return FALSE;
	}

	HRESULT hResult = m_pIDBPIM->ImportSeriesInfo(*pSeries);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::AddImageRecordToDB(ImageInfoStruct* pImage)
{
	if (NULL == pImage)
	{
		return FALSE;
	}

	HRESULT hResult = m_pIDBPIM->ImportImageInfo(*pImage);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::SetPostProcessingInfo(PostProcessingInfo* pPostProcess)
{
	if (NULL == pPostProcess)
	{
		return FALSE;
	}

	HRESULT hResult = m_pIDBPIM->SetPostProcessingInfo(*pPostProcess);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL CDBController::DeletePatientRecordFromDB(LPCTSTR szPatientUID)
{
	if (NULL == szPatientUID)
	{
		return FALSE;
	}

	BSTR bsPatientUID = CString(szPatientUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->DeletePatientInfo(bsPatientUID);
	CBSTROpt::FreeBSTR(bsPatientUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::DeleteStudyRecordFromDB(LPCTSTR szStudyUID)
{
	if (NULL == szStudyUID)
	{
		return FALSE;
	}

	BSTR bsStudyUID = CString(szStudyUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->DeleteStudyInfo(bsStudyUID);
	CBSTROpt::FreeBSTR(bsStudyUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::DeleteSeriesRecordFromDB(LPCTSTR szSeriesUID)
{
	if (NULL == szSeriesUID)
	{
		return FALSE;
	}

	BSTR bsSeriesUID = CString(szSeriesUID).AllocSysString();
	HRESULT hResult = m_pIDBPIM->DeleteSeriesInfo(bsSeriesUID);
	CBSTROpt::FreeBSTR(bsSeriesUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::DeleteImageRecordFromDB(LPCTSTR szImageUID)
{
	if (NULL == szImageUID)
	{
		return FALSE;
	}

	BSTR bsImageUID = CString(szImageUID).AllocSysString();
	// DB应同时删除对应的PostProcessInfo
	HRESULT hResult = m_pIDBPIM->DeleteImageInfo(bsImageUID);
	CBSTROpt::FreeBSTR(bsImageUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDBController::ModifyStudyInfo(StudyInfoStruct* pStudyInfo)
{
	if (NULL == pStudyInfo)
	{
		return FALSE;
	}

	CString strTrace;
	HRESULT hResult = S_OK;

	hResult = m_pIDBPIM->ModifyStudyInfo(*pStudyInfo);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		strTrace.Format(_T("m_pIDBPIM->ModifyStudyInfo(), StudyUID: %s"), CString(CBSTROpt::BSTRToCString(pStudyInfo->bsStudyUID)));
		PRINTTRACE_ERROR(strTrace)

		return FALSE;
	}
}


BOOL CDBController::ModifyPatientInfo(PatientInfoStruct* pPatientInfo)
{
	if (NULL == pPatientInfo)
	{
		return FALSE;
	}

	CString strTrace;
	HRESULT hResult = S_OK;

	hResult = m_pIDBPIM->ModifyPatientInfo(*pPatientInfo);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		strTrace.Format(_T("m_pIDBPIM->ModifyPatientInfo(), PatientUID: %s"), CString(CBSTROpt::BSTRToCString(pPatientInfo->bsPatientUID)));
		PRINTTRACE_ERROR(strTrace)

		return FALSE;
	}
}

BOOL CDBController::GetCurrentStudyUID(CString& strStudyUID)
{
	CString strTrace;
	HRESULT hResult = S_OK;

	BSTR bsStudyUID;
	hResult = m_pIDBSession->GetCurrentStudyUID(&bsStudyUID);
	if (S_OK == hResult)
	{
		strStudyUID = CBSTROpt::BSTRToCString(bsStudyUID);
		CBSTROpt::FreeBSTR(bsStudyUID);
		return TRUE;
	}
	else
	{
		strTrace.Format(_T("m_pIDBSession->GetCurrentStudyUID()"));
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
}

// BOOL CDBController::GetNextStudyIDInPatient(LPCTSTR szPatientUID, INT* piStudyID)
// {
// 	BSTR bsPatientUID = CString(szPatientUID).AllocSysString();
// 	HRESULT hResult = S_OK;
// 	hResult = m_pIDBPIM->GetNextStudyID(bsPatientUID, piStudyID);
// 	CBSTROpt::FreeBSTR(bsPatientUID);
// 	if (S_OK != hResult)
// 	{
// 		return FALSE;
// 	}
// 	else
// 	{
// 		return TRUE;
// 	}
// }

BOOL CDBController::GetNextSeriesIDInStudy(LPCTSTR szStudyUID, INT* piSeriesID)
{
	BSTR bsStudyUID = CString(szStudyUID).AllocSysString();
	HRESULT hResult = S_OK;
	hResult = m_pIDBPIM->GetNextSeriesID(bsStudyUID, piSeriesID);
	CBSTROpt::FreeBSTR(bsStudyUID);
	if (S_OK != hResult)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CDBController::UpdatePatientID(CString& strPatientID)
{
	HRESULT hResult = S_OK;
	BOOL bExist = FALSE;

	if (!strPatientID.IsEmpty())
	{
		BOOL bExist = FALSE;
		BSTR bsPatientID = strPatientID.AllocSysString();
		hResult = m_pIDBPIM->IsPatientIDExist(bsPatientID, &bExist);
		CBSTROpt::FreeBSTR(bsPatientID);
		if (S_OK == hResult)
		{
			if (!bExist)
			{
				return TRUE;
			}
		}
	}

	// Create New PatientID is needed
	int iCreateTime = 0;
	BSTR bsNewID;

	while (++iCreateTime <= 3)
	{
		strPatientID = CIDPathGen::GetInstance()->GenPatientID();
		bsNewID = strPatientID.AllocSysString();
		hResult = m_pIDBPIM->IsPatientIDExist(bsNewID, &bExist);
		CBSTROpt::FreeBSTR(bsNewID);
		if (S_OK == hResult)
		{
			if (bExist)
			{
				continue;
			}
			else
			{
				return TRUE;
			}
		}
		else
		{
			return FALSE;
		}
	}

	return FALSE;
}

BOOL CDBController::SetStudyMPPSStatus(LPCTSTR szStudyUID, MPPS_STATE enumStatus)
{
	if (NULL == szStudyUID)
	{
		return FALSE;
	}

	HRESULT hResult = S_OK;

	BSTR bsStudyUID = CString(szStudyUID).AllocSysString();
	hResult = m_pIDBPIM->SetMPPSState(bsStudyUID, enumStatus);
	CBSTROpt::FreeBSTR(bsStudyUID);
	if (S_OK == hResult)
	{
		return TRUE;
	}
	else
	{
		CString strTrace;
		strTrace.Format(_T("m_pIDBPIM->SetMPPSState(), StudyUID: %s, enumStatus: %d"), szStudyUID, enumStatus);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
}

