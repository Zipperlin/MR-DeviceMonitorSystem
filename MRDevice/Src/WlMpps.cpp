/* Time: <@(#)WlMpps.cpp   2009-3-5 - 10:34:22   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : WlMpps.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Capsulation class of worklist and MPPS function
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:34:22		FanZF	Creation
 *
 *********************************************************************
 */

// WlMpps.cpp: implementation of the CWlMpps class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WlMpps.h"
#include "PADataBaseOpt.h"


/**
 ********************************************************************
 * \brief Worklist��ѯ�߳�
 *  
 *  
 * \param LPVOID lpParam : [in] 
 * 
 * \return WINAPI  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
DWORD WINAPI WorkListQueryThreadProc(LPVOID lpParam) 
{ 
//	PRINTTRACE_ENTER_FUNCTION

	try
	{
		CWlMpps* pWlMpps = (CWlMpps*)lpParam;

		pWlMpps->UpdateWorklistWorkState(TRUE);

		BOOL bRet = pWlMpps->QueryProc();

		pWlMpps->UpdateWorklistWorkState(FALSE);

		if (bRet)
		{
			return THREADE_RET_CODE_OK;
		}
		else
		{
			return THREADE_RET_CODE_ERROR;
		}
	}
	PA_CATCH_ERROR_RET(THREADE_RET_CODE_ERROR)
}


/**
 ********************************************************************
 * \brief MPPS�����߳�
 *  
 *  
 * \param LPVOID lpParam : [in] 
 * 
 * \return WINAPI  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
DWORD WINAPI SetMppsStatusThreadProc(LPVOID lpParam)
{ 
//	PRINTTRACE_ENTER_FUNCTION
	try
	{
		CWlMpps::GetInstance()->UpdateMppsWorkState(TRUE);

		BOOL bRet = TRUE;
		bRet = CWlMpps::GetInstance()->SetMppsStatusProc((MppsStatusStruct*)lpParam);

		CString strStudyUID = ((MppsStatusStruct*)lpParam)->strStudyUID;
		WorkListStatus enumStatus = ((MppsStatusStruct*)lpParam)->enumStatus;
		delete (MppsStatusStruct*)lpParam;

		// Notify GUI to close the Wait dialog
		CWlMpps::GetInstance()->NotifySetMppsFinished(strStudyUID, enumStatus, bRet);

		//<< ��MPPS�б�������ṹ
		bRet = CWlMpps::GetInstance()->RemoveMppsStatusStruct(strStudyUID, enumStatus);

		CWlMpps::GetInstance()->UpdateMppsWorkState(FALSE);

		if (bRet)
		{
			return THREADE_RET_CODE_OK;
		}
		else
		{
			return THREADE_RET_CODE_ERROR;
		}
	}
	PA_CATCH_ERROR_RET(THREADE_RET_CODE_ERROR)

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWlMpps* CWlMpps::m_pInstance = NULL;



/**
 ********************************************************************
 * \brief ���캯��
 *  
 *  
 * 
 * \return  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CWlMpps::CWlMpps()
{
	m_pWLIniOpt = NULL;
	m_pWLIniOpt = CWorklistIniOpt::GetInstance();
	m_pMppsIniOpt = NULL;
	m_pMppsIniOpt = CMPPSIniOpt::GetInstance();

	m_hWLQueryThread = NULL;

	m_SubModuleState = enumSubModuleState_UnInited;

	m_bWorkListWorking = FALSE;
	m_bMppsWorking = FALSE;
}


/**
 ********************************************************************
 * \brief ��������
 *  
 *  
 * 
 * \return  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CWlMpps::~CWlMpps()
{
	m_pWLIniOpt->ReleaseInstance();
	m_pMppsIniOpt->ReleaseInstance();
}


/**
 ********************************************************************
 * \brief ���CWlMppsʵ��
 *  
 *  
 * 
 * \return CWlMpps*  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CWlMpps* CWlMpps::GetInstance()
{
	if(!m_pInstance)
		m_pInstance = new CWlMpps;
	return m_pInstance;
}


/**
 ********************************************************************
 * \brief �ͷ�CWlMppsʵ��
 *  
 *  
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


/**
 ********************************************************************
 * \brief ��ʼ������
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::Init()
{
	BOOL bRet = TRUE;

	m_vtrWLStruct.clear();
	
	if (!m_pWLIniOpt->Init())
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("m_pWLIniOpt->Init()")
	}

	if (!m_pMppsIniOpt->Init())
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("m_pMppsIniOpt->Init()")
	}

	m_bWorkListWorking = FALSE;
	m_bMppsWorking = FALSE;
	
	if (bRet)
	{
		SetSubModuleState(enumSubModuleState_Ready);
	}
	else
	{
		SetSubModuleState(enumSubModuleState_Ready);
	}
	return bRet;
}


/**
 ********************************************************************
 * \brief 
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::UnInit()
{
	SetSubModuleState(enumSubModuleState_UnInitializing);
	
	BOOL bRet = TRUE;

	m_vtrWLStruct.clear();


	if (!CancelQuery())
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("CancelQuery()")
	}
	
	if (!CancelMppsNProc())
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("CancelMppsNProc()")
	}
	
	m_pWLIniOpt->UnInit();
	m_pMppsIniOpt->UnInit();

	SetSubModuleState(enumSubModuleState_UnInited);
	return bRet;
}



/**
 ********************************************************************
 * \brief ���Worklist֪ͨ
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::GetWorkList()
{
	if (0 == m_vtrWLStruct.size())
	{
		return TRUE;
	}
	else
	{
		if (ReportWorkList())
		{
			return TRUE;
		}
		else
		{
			PRINTTRACE_ERROR("ReportWorkList()")
			return FALSE;
		}
	}
}


/**
 ********************************************************************
 * \brief ˢ��Worklist
 *  
 *  
 * \param WorkListQueryCond* pWorkListQueryCond : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::RefreshWorkList(WorkListQueryCond* pWorkListQueryCond)
{
	if (m_hWLQueryThread)
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hWLQueryThread, 0))
		{
			// A thread is running, so UserGuidance to notify User
			NotifyUG(IDS_PRINTINGARCHIVING_WORKLIST_REFRESHING_PLZ_WAIT, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
			return TRUE;
		}
		else
		{
			CloseHandle(m_hWLQueryThread);
			m_hWLQueryThread = NULL;
		}
	}

	// save query condition
	SetQueryCondition(pWorkListQueryCond);


	m_hWLQueryThread = CreateThread(NULL, 0, WorkListQueryThreadProc, this, 0, NULL);
	if (m_hWLQueryThread)
	{
		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR("m_hWLQueryThread = CreateThread(NULL, 0, WorkListQueryThreadProc, this, 0, NULL)")
		return FALSE;
	}
}


/**
 ********************************************************************
 * \brief ��û��߼��ṹ
 *  
 *  
 * \param LPCTSTR szStudyInstanceUID : [in] 
 * \param WLPatientStudyStruct* pStruct : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::GetPatientStudyStruct(LPCTSTR szStudyInstanceUID, WLPatientStudyStruct* pStruct)
{
	CString strTrace;

	for (int i = 0; i < m_vtrWLStruct.size(); i++)
	{
		if (!m_vtrWLStruct[i].strStudyInstanceUID.Compare(szStudyInstanceUID))
		{
			pStruct->bsStudyInstanceUID = m_vtrWLStruct[i].strStudyInstanceUID.AllocSysString();

			// Patient info
			CString strPatientID = m_vtrWLStruct[i].strPatientID;
			if (CDBController::GetInstance()->UpdatePatientID(strPatientID))
			{
				pStruct->bsPatientID = strPatientID.AllocSysString();
			}
			else
			{
				return FALSE;
			}

			// Patient FirstName, MidName, LastName
			CString strFirstName, strMidName, strLastName;
			ParsePatientNameFromDcmPN(m_vtrWLStruct[i].strPatientName, strFirstName, strMidName, strLastName);
			pStruct->bsPatientFirstName = strFirstName.AllocSysString();
			pStruct->bsPatientMidName = strMidName.AllocSysString();
			pStruct->bsPatientLastName = strLastName.AllocSysString();
			
			// Patient BirthDate, Age and Age Unit
			GetPatientBirthDateAge(m_vtrWLStruct[i].strPatientBirthDate,
									m_vtrWLStruct[i].strPatientAge,
									pStruct->iPatientAge,
									pStruct->iPatientAgeUnit,
									pStruct->dtPatientBirthDate,
									pStruct->enumBirthDateAgeUsing);


			// RegDateTime
			pStruct->dtRegDateTime = GetDATEByCurrentDateTime();

			// Patient Sex
			if (!m_vtrWLStruct[i].strPatientSex.Compare(_T("M")))
			{
				pStruct->iPatientSex = 0;
			}
			else if (!m_vtrWLStruct[i].strPatientSex.Compare(_T("F")))
			{
				pStruct->iPatientSex = 1;
			}
			else if (!m_vtrWLStruct[i].strPatientSex.Compare(_T("O")))
			{
				pStruct->iPatientSex = 2;
			}
			else
			{
				pStruct->iPatientSex = 2;
			}

			pStruct->bsOtherPatientName = m_vtrWLStruct[i].strOtherPatientNames.AllocSysString();
			pStruct->bsOtherPatientIDs = m_vtrWLStruct[i].strOtherPatientIDs.AllocSysString();
			pStruct->bsEthnicGroup = m_vtrWLStruct[i].strEthnicGroup.AllocSysString();
			pStruct->bsOccupation = m_vtrWLStruct[i].strOccupation.AllocSysString();
			pStruct->bsPatientComment = m_vtrWLStruct[i].strPatientComments.AllocSysString();

			// Study Info
			pStruct->dtStudyDateTime = GetDATEByCurrentDateTime();
			pStruct->bsRefferingPhsicianName = m_vtrWLStruct[i].strRefPysicianName.AllocSysString();
			pStruct->bsOperatorName = CString(_T("")).AllocSysString();
			pStruct->bsPerformingPhysicianName = m_vtrWLStruct[i].strSPPhysicianName.AllocSysString();
			pStruct->bsPatientSize = m_vtrWLStruct[i].strPatientSize.AllocSysString();
			pStruct->bsPatientWeight = m_vtrWLStruct[i].strPatientWeight.AllocSysString();
			pStruct->bsStudyDescription = m_vtrWLStruct[i].strRequestedProcedureDescription.AllocSysString();
			pStruct->bsPatientHistory = CString(_T("")).AllocSysString();
			pStruct->bsAccessionNumber = m_vtrWLStruct[i].strAccessionNumber.AllocSysString();
			return TRUE;
		}
	}

	strTrace.Format(_T("not found input para szStudyInstanceUID inm_vtrWLStruct, szStudyInstanceUID: %s"), szStudyInstanceUID);
	PRINTTRACE_ERROR(strTrace)
	return FALSE;
}


/**
 ********************************************************************
 * \brief �жϼ���Ƿ��ѱ�����
 *  
 *  
 * \param LPCTSTR szStudyInstanceUID : [in] 
 * \param WLPatientStudyStatusInDB* pStatus : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::IsStudyImported(LPCTSTR szStudyInstanceUID, WLPatientStudyStatusInDB* pStatus)
{
	CString strTrace;

	for (int i = 0; i < m_vtrWLStruct.size(); i++)
	{
		if (!m_vtrWLStruct[i].strStudyInstanceUID.Compare(szStudyInstanceUID))
		{
			WorkListStatus enumStatus = enumWorkListStatus_NotImported;
			if (CDBController::GetInstance()->GetMPPSStatusByStudyInstanceUID(szStudyInstanceUID, &enumStatus))
			{
				if (enumWorkListStatus_NotImported == enumStatus)
				{
					// Study not imported
					pStatus->bStudyExists = FALSE;
					
					// Patient Exist or not? (by PatientID)
					if (CDBController::GetInstance()->IsPatientIDExistsInDB(m_vtrWLStruct[i].strPatientID, &pStatus->bPatientExists))
					{
						if (!pStatus->bPatientExists)
						{
							pStatus->bsPatientUID = CString(_T("")).AllocSysString();
							pStatus->bsPatientID = CString(_T("")).AllocSysString();
							pStatus->bsPatientFullName = CString(_T("")).AllocSysString();
							pStatus->iPatientSex = 0;
							
							return TRUE;
						}
						else
						{
							PatientInfoStruct PatientInfo;
							if (CDBController::GetInstance()->GetPatientInfoByID(m_vtrWLStruct[i].strPatientID, &PatientInfo))
							{
								pStatus->bsPatientUID = CBSTROpt::BSTRToCString(PatientInfo.bsPatientUID).AllocSysString();
								pStatus->bsPatientID = CBSTROpt::BSTRToCString(PatientInfo.bsPatientID).AllocSysString();
								pStatus->bsPatientFullName = CBSTROpt::BSTRToCString(PatientInfo.bsPatientName).AllocSysString();
								pStatus->iPatientSex = PatientInfo.iGender;

								CBSTROpt::FreePatientInfoStruct(&PatientInfo);

								return TRUE;
							}
							else
							{
								strTrace.Format(_T("CDBController::GetInstance()->GetPatientInfoByID, patientid: %s"), m_vtrWLStruct[i].strPatientID);
								PRINTTRACE_ERROR(strTrace)
								return FALSE;
							}
						}
					}
					else
					{
						strTrace.Format(_T("CDBController::GetInstance()->IsPatientIDExistsInDB, patientid: %s"), m_vtrWLStruct[i].strPatientID);
						PRINTTRACE_ERROR(strTrace)
						return FALSE;
					}
				}
				else
				{
					// Study imported already
					pStatus->bStudyExists = TRUE;
					pStatus->bPatientExists = TRUE;		// GUI need this
					// GUI don't need the following items, since Study has been imported
					pStatus->bsPatientUID = CString(_T("")).AllocSysString();
					pStatus->bsPatientID = CString(_T("")).AllocSysString();
					pStatus->bsPatientFullName = CString(_T("")).AllocSysString();
					pStatus->iPatientSex = 0;

					return TRUE;
				}
			}
			else
			{
				strTrace.Format(_T("CDBController::GetInstance()->GetMPPSStatusByStudyInstanceUID, StudyInstanceUID: %s"), szStudyInstanceUID);
				PRINTTRACE_ERROR(strTrace)
				return FALSE;
			}
		}
	}

	strTrace.Format(_T("not found input para szStudyInstanceUID inm_vtrWLStruct, szStudyInstanceUID: %s"), szStudyInstanceUID);
	PRINTTRACE_ERROR(strTrace)
	return FALSE;
}


/**
 ********************************************************************
 * \brief һ����鱻����
 *  
 *  
 * \param LPCTSTR szStudyInstanceUID : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-25	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::StudyImported(LPCTSTR szStudyInstanceUID)
{
	CString strTrace;
	if (!CPADataBaseOpt::GetInstance()->AddWorklistImportedStudy(szStudyInstanceUID))
	{
		strTrace.Format(_T("CPADataBaseOpt::GetInstance()->AddWorklistImportedStudy(szStudyInstanceUID), szStudyInstanceUID:%s"), szStudyInstanceUID);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

/**
 ********************************************************************
 * \brief Worklist��ѯ����
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::QueryProc()
{
	NetworkNodeStruct ServerStruct;
	vector<WLQueryItem> vtrWLQueryCond;


	// Read query condition from Ini
	if (!m_pWLIniOpt->GetQueryItemList(&vtrWLQueryCond))
	{
		PRINTTRACE_ERROR("m_pWLIniOpt->GetQueryItemList(&vtrWLQueryCond)")
		return FALSE;
	}

	// Modify query condition according GUI required 
	if (!ModifyQueryCondition(vtrWLQueryCond))
	{
		PRINTTRACE_ERROR("ModifyQueryCondition(vtrWLQueryCond)")
		return FALSE;
	}

	// Read default WorkList Server from ini
	int iErrCode = m_pWLIniOpt->GetDefaultWorklistServer(&ServerStruct);
	if (E_OK == iErrCode)
	{
		// succeed
	}
	else if (E_WLMPPS_INI_NO_SERVER == iErrCode ||
		E_WLMPPS_INI_NO_SERVER_SELECTED == iErrCode)
	{
		// UserGuidance to notify User
		NotifyUG(IDS_PRINTINGARCHIVING_WORKLIST_INVALID_SERVER_CFG, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		PRINTTRACE_WARNING("E_WLMPPS_NO_SERVER or E_WLMPPS_NO_SERVER_SELECTED == m_pWLIniOpt->GetDefaultWorklistServer(&ServerStruct)")
		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR("m_pWLIniOpt->GetDefaultWorklistServer(&ServerStruct)")
		return FALSE;
	}

	// Set Server
	m_WLOpt.SetServer(ServerStruct.strCalledAE, ServerStruct.strIP, ServerStruct.strPort, ServerStruct.strCallingAE);

	// Clear the former worklist record
	m_vtrWLStruct.clear();

	// Query!!! May take a long time...
	iErrCode = m_WLOpt.Query(&vtrWLQueryCond, &m_vtrWLStruct);
	if (E_OK == iErrCode)
	{
		// Query Successfully, so Send the query result to GUI
		if (ReportWorkList())
		{
			// UserGuidance to notify User
			NotifyUG(IDS_PRINTINGARCHIVING_WORKLIST_REFRESH_COMPLETED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
			return TRUE;
		}
		else
		{
			PRINTTRACE_ERROR("ReportWorkList()")
			return FALSE;
		}
	}
	else if (E_WLMPPS_CNT_SERVER_FAILED == iErrCode)
	{
		// UserGuidance to notify User
		NotifyUG(IDS_PRINTINGARCHIVING_WORKLIST_CNT_SVR_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		PRINTTRACE_ERROR("m_WLOpt.Query(&vtrWLQueryCond, &m_vtrWLStruct), E_WLMPPS_CNT_SERVER_FAILED == iErrCode")
		return FALSE;
	}
	else
	{
		PRINTTRACE_ERROR("m_WLOpt.Query(&vtrWLQueryCond, &m_vtrWLStruct)")
		return FALSE;
	}
}


/**
 ********************************************************************
 * \brief ȡ��worklist��ѯ
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::CancelQuery()
{
	BOOL bRet = TRUE;

	if (m_hWLQueryThread)
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hWLQueryThread, 0))
		{
			// A thread is running, so Terminate the Thread
			if (!::TerminateThread(m_hWLQueryThread, 0))
			{
				bRet = FALSE;
				PRINTTRACE_ERROR("::TerminateThread(m_hWLQueryThread, 0)")
			}
		}

		CloseHandle(m_hWLQueryThread);
		m_hWLQueryThread = NULL;

		UpdateWorklistWorkState(FALSE);
	}

	return bRet;
}


/**
 ********************************************************************
 * \brief ����worklist
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::ReportWorkList()
{
	CString strTrace;

	int iStructNum = m_vtrWLStruct.size();
	
	if (0 == iStructNum)
	{
		// Report is not needed
		return TRUE;
	}

	WorkListStruct* pStruct = new WorkListStruct[m_vtrWLStruct.size()];
	if (NULL == pStruct)
	{
		return FALSE;
	}

	for (int i = 0; i < m_vtrWLStruct.size(); i++)
	{
		if (m_vtrWLStruct[i].strStudyInstanceUID.IsEmpty())
		{
			strTrace.Format(_T("m_vtrWLStruct[i].strStudyInstanceUID.IsEmpty(), i=%d, PatientID:%s"), i, m_vtrWLStruct[i].strPatientID);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}

		// Confirm the Study's Worklist status
//		pStruct[i].enumStatus = enumWorkListStatus_NotImported;
		if (!CDBController::GetInstance()->GetMPPSStatusByStudyInstanceUID(m_vtrWLStruct[i].strStudyInstanceUID, &pStruct[i].enumStatus))
		{
			PRINTTRACE_ERROR("CDBController::GetInstance()->GetMPPSStatusByStudyInstanceUID(m_vtrWLStruct[i].strStudyInstanceUID, &m_vtrWLStruct[i].enumStatus)")
			return FALSE;
		}

		pStruct[i].bsSSAETitle = m_vtrWLStruct[i].strSSAETitle.AllocSysString();

		// Combinate Date and Time to DateTime
		pStruct[i].bsSPSDateTime = (GetDisplayDateFromDcmDate(m_vtrWLStruct[i].strSPSStartDate)
									+ _T(" ")
									+ GetDisplayTimeFromDcmTime(m_vtrWLStruct[i].strSPSStartTime)).AllocSysString();

		pStruct[i].bsSPSDescription = m_vtrWLStruct[i].strSPSDescription.AllocSysString();
		pStruct[i].bsSPSID = m_vtrWLStruct[i].strSPSID.AllocSysString();

		pStruct[i].bsSPPhisicianName = m_vtrWLStruct[i].strSPPhysicianName.AllocSysString();

		// parse PatientName
		pStruct[i].bsPatientName = m_vtrWLStruct[i].strPatientName.AllocSysString();

		pStruct[i].bsPatientID = m_vtrWLStruct[i].strPatientID.AllocSysString();
		pStruct[i].bsAccessionNumber = m_vtrWLStruct[i].strAccessionNumber.AllocSysString();

		// Convert Dcm Date to Display Date
		pStruct[i].bsPatientBirthDate = GetDisplayDateFromDcmDate(m_vtrWLStruct[i].strPatientBirthDate).AllocSysString();

		pStruct[i].bsStudyInstanceUID = m_vtrWLStruct[i].strStudyInstanceUID.AllocSysString();

		// string Sex to int Sex
		if (!m_vtrWLStruct[i].strPatientSex.Compare(_T("M")))
		{
			pStruct[i].iPatientSex = 0;
		}
		else if (!m_vtrWLStruct[i].strPatientSex.Compare(_T("F")))
		{
			pStruct[i].iPatientSex = 1;
		}
		else if (!m_vtrWLStruct[i].strPatientSex.Compare(_T("O")))
		{
			pStruct[i].iPatientSex = 2;
		}
		else
		{
			// empty or something else
			pStruct[i].iPatientSex = 2;
		}
    
		pStruct[i].bsRefPhisicianName = m_vtrWLStruct[i].strRefPysicianName.AllocSysString();
		pStruct[i].bsRPID = m_vtrWLStruct[i].strRequestedProcedureID.AllocSysString();
		pStruct[i].bsRPDescription = m_vtrWLStruct[i].strRequestedProcedureDescription.AllocSysString();


		pStruct[i].bsOtherPatientIDs = m_vtrWLStruct[i].strOtherPatientIDs.AllocSysString();
		pStruct[i].bsOtherPatientNames = m_vtrWLStruct[i].strOtherPatientNames.AllocSysString();
		pStruct[i].bsPatientAge = m_vtrWLStruct[i].strPatientAge.AllocSysString();
		pStruct[i].bsOccupation = m_vtrWLStruct[i].strOccupation.AllocSysString();
		pStruct[i].bsPatientSize = m_vtrWLStruct[i].strPatientSize.AllocSysString();
		pStruct[i].bsPatientWeight = m_vtrWLStruct[i].strPatientWeight.AllocSysString();
		pStruct[i].bsEthnicGroup = m_vtrWLStruct[i].strEthnicGroup.AllocSysString();		
		pStruct[i].bsPatientComments = m_vtrWLStruct[i].strPatientComments.AllocSysString();
	}

	// Report the Patient/Study list, the list memory should be freed after ConnectionPoint Calling.
	Notify(NOTIFY_WLMPPS_REPORT_WORKLIST, (LPARAM)iStructNum, (WPARAM)pStruct);
		
	return TRUE;
}


/**
 ********************************************************************
 * \brief �޸Ĳ�ѯ����
 *  
 *  
 * \param vector<WLQueryItem>& vtrWLQueryCond : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::ModifyQueryCondition(vector<WLQueryItem>& vtrWLQueryCond)
{
	// Get condition items' index in the vector
	int iSPSStartDateIndex = -1;

	for (int i = 0; i < vtrWLQueryCond.size(); i++)
	{
		// 1. SPS Start Date
		if (0x0040 == vtrWLQueryCond[i].usGroup &&  0x0002 == vtrWLQueryCond[i].usElement)
		{
			iSPSStartDateIndex = i;
		}

		// 2. ...
	}

	// 1. SPS Start Date
	if (-1 != iSPSStartDateIndex)
	{
		GetSPSStartDate(m_WkLQueryCond.enumWLQuerySPSStartDate, vtrWLQueryCond[iSPSStartDateIndex].strValue);
	}

	// 2. ...

	return TRUE;
}


/**
 ********************************************************************
 * \brief ����worklist����״̬
 *  
 *  
 * \param BOOL bWorking : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::UpdateWorklistWorkState(BOOL bWorking)
{
	m_bWorkListWorking = bWorking;

	UpdateWlMppsWorkState();
}



/**
 ********************************************************************
 * \brief SPS Start Date
 *  
 *  
 * \param WLQuerySPSStartDate enumWLQuerySPSStartDate : [in] 
 * \param CString& strSPSStartDate : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::GetSPSStartDate(WLQuerySPSStartDate enumWLQuerySPSStartDate, CString& strSPSStartDate)
{
	CTime tEnd, tBegin;
	tEnd = CTime::GetCurrentTime();
	int iDays = 0;

	switch (enumWLQuerySPSStartDate)
	{
	case enumWLQuery_SPS_SD_UnUse:
		// GUI unuse SPS Start Date, so use the ini setting
		return;

	case enumWLQuery_SPS_SD_Today:
		iDays = 1;
		break;

	case enumWLQuery_SPS_SD_LastTwoDays:
		iDays = 2;
		break;

	case enumWLQuery_SPS_SD_LastOneWeek:
		iDays = 7;
		break;

	case enumWLQuery_SPS_SD_LastOneMonth:
		iDays = 30;
		break;

	case enumWLQuery_SPS_SD_LastOneYear:
		iDays = 365;
		break;

	case enumWLQuery_SPS_SD_All:
		strSPSStartDate = _T("");			// it's means ALL
		return;
		
	default:
		return;
	}

	CTimeSpan tSpan(iDays - 1, 0, 0, 0);
	tBegin = tEnd - tSpan;

	strSPSStartDate.Format(_T("%04d%02d%02d-%04d%02d%02d"), tBegin.GetYear(),
															tBegin.GetMonth(),
															tBegin.GetDay(),
															tEnd.GetYear(),
															tEnd.GetMonth(),
															tEnd.GetDay());
}


/**
 ********************************************************************
 * \brief ���ò�ѯ����
 *  
 *  
 * \param WorkListQueryCond* pWorkListQueryCond : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::SetQueryCondition(WorkListQueryCond* pWorkListQueryCond)
{
	InitQueryCondition();

	m_WkLQueryCond.enumWLQuerySPSStartDate = pWorkListQueryCond->enumWLQuerySPSStartDate;
}


/**
 ********************************************************************
 * \brief ��ʼ����ѯ����
 *  
 *  
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::InitQueryCondition()
{
	m_WkLQueryCond.enumWLQuerySPSStartDate = enumWLQuery_SPS_SD_UnUse;
}



/**
 ********************************************************************
 * \brief ��DICOM���ڻ����ʾ������
 *  
 *  
 * \param LPCTSTR szDcmDate : [in] 
 * 
 * \return CString  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CString CWlMpps::GetDisplayDateFromDcmDate(LPCTSTR szDcmDate)
{
	// YYYYmmdd to YYYY-mm-dd
	if (NULL == szDcmDate)
	{
		return CString(_T(""));
	}

	CString strDcmDate = szDcmDate;
	CString	strDisplayDate = _T("");

	if (8 == strDcmDate.GetLength())
	{
		strDisplayDate.Format(_T("%s-%s-%s"), strDcmDate.Left(4), strDcmDate.Mid(4, 2), strDcmDate.Right(2));
	}

	return strDisplayDate;
}


/**
 ********************************************************************
 * \brief ��DICOMʱ������ʾ��ʱ��
 *  
 *  
 * \param LPCTSTR szDcmTime : [in] 
 * 
 * \return CString  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CString CWlMpps::GetDisplayTimeFromDcmTime(LPCTSTR szDcmTime)
{
	// HHMMSS.mmmmm(000000-999999) to HH:MM:SS
	if (NULL == szDcmTime)
	{
		return CString(_T(""));
	}

	CString strDcmTime = szDcmTime;
	CString	strDisplayTime = _T("");

	if (2 == strDcmTime.GetLength())
	{
		// HH
		strDisplayTime.Format(_T("%s:00:00"), strDcmTime.Left(2));
	}
	else if (4 == strDcmTime.GetLength())
	{
		// HHMM
		strDisplayTime.Format(_T("%s:%s:00"), strDcmTime.Left(2), strDcmTime.Mid(2, 2));
	}
	else if (6 == strDcmTime.GetLength())
	{
		// HHMMSS
		strDisplayTime.Format(_T("%s:%s:%s"), strDcmTime.Left(2), strDcmTime.Mid(2, 2), strDcmTime.Mid(4, 2));
	}
	else if (strDcmTime.GetLength() > 6 && strDcmTime.GetAt(6) == _T('.'))
	{
		// HHMMSS.mmmmm(000000-999999)
		strDisplayTime.Format(_T("%s:%s:%s"), strDcmTime.Left(2), strDcmTime.Mid(2, 2), strDcmTime.Mid(4, 2));
	}

	return strDisplayTime;
}


/**
 ********************************************************************
 * \brief Patient Name parse from Dcm PatientsName
 *  
 *  
 * \param LPCTSTR szDcmPN : [in] 
 * \param CString& strFirstName : [in] 
 * \param CString& strMidName : [in] 
 * \param CString& strLastName : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::ParsePatientNameFromDcmPN(LPCTSTR szDcmPN, CString& strFirstName, CString& strMidName, CString& strLastName)
{
	// Dcm PatientsName format:
	// family name complex(LastName)^given name complex(FirstName)^middle name(MidName)^name prefix^name suffix

	strFirstName = _T("");
	strMidName = _T("");
	strLastName = _T("");

	if (NULL == szDcmPN)
	{
		return;
	}

	CString strDcmPN = szDcmPN;
	if (strDcmPN.IsEmpty())
	{
		return;
	}

	// LastName
	int iFirstDelimiter = strDcmPN.Find(_T('^'));
	if (-1 == iFirstDelimiter)
	{
		// no '^' found
		strLastName = strDcmPN;
		return;
	}
	else
	{
		strLastName = strDcmPN.Left(iFirstDelimiter);
	}

	// FirstName
	int iSecondDelimiter = strDcmPN.Find(_T('^'), iFirstDelimiter + 1);
	if (-1 == iSecondDelimiter)
	{
		// no '^' found
		strFirstName = strDcmPN.Right(strDcmPN.GetLength() - iFirstDelimiter - 1);
		return;
	}
	else
	{
		strFirstName = strDcmPN.Mid(iFirstDelimiter + 1, iSecondDelimiter - iFirstDelimiter - 1);
	}

	// MidName
	int iThirdDelimiter = strDcmPN.Find(_T('^'), iSecondDelimiter + 1);
	if (-1 == iThirdDelimiter)
	{
		// no '^' found
		strMidName = strDcmPN.Right(strDcmPN.GetLength() - iSecondDelimiter - 1);
		return;
	}
	else
	{
		strMidName = strDcmPN.Mid(iSecondDelimiter + 1, iThirdDelimiter - iSecondDelimiter - 1);
	}


}


/**
 ********************************************************************
 * \brief Date Convert from Dcm to DATE
 *  
 *  
 * \param LPCTSTR szDcmDate : [in] 
 * 
 * \return DATE  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
DATE CWlMpps::GetDATEFromDcmDate(LPCTSTR szDcmDate)
{
	CString strDcmDate;

	if (NULL != szDcmDate && 8 == _tcslen(szDcmDate))
	{
		strDcmDate = szDcmDate;
	}
	else
	{
		SYSTEMTIME st;
		::GetLocalTime(&st);
		strDcmDate.Format(_T("%04d%02d%02d"), st.wYear, st.wMonth, st.wDay);
	}

	COleDateTime odtDateTime;

	int iYear, iMonth, iDay;
	iYear = iMonth = iDay = 0;
	
	CString strTemp = _T("");

	strTemp = strDcmDate.Mid(0, 4);
	iYear = _wtoi(strTemp);

	strTemp = strDcmDate.Mid(4, 2);
	iMonth = _wtoi(strTemp);

	strTemp = strDcmDate.Mid(6, 2);
	iDay = _wtoi(strTemp);

	odtDateTime.SetDateTime(iYear, iMonth, iDay, 0, 0, 0);

	return DATE(odtDateTime);
}


/**
 ********************************************************************
 * \brief Get DATE by current Date Time
 *  
 *  
 * 
 * \return DATE  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
DATE CWlMpps::GetDATEByCurrentDateTime()
{
	COleDateTime odtDateTime;
	SYSTEMTIME st;
	::GetLocalTime(&st);

	odtDateTime.SetDateTime(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return DATE(odtDateTime);
}


/**
 ********************************************************************
 * \brief ��û��߳�������/����
 *  
 *  
 * \param LPCTSTR szDcmBirthDate : [in] 
 * \param LPCTSTR szDcmAge : [in] 
 * \param int& iAge : [in] 
 * \param int& iAgeUnit : [in] 
 * \param DATE& dtBirthDate : [in] 
 * \param PatientBirthDateAgeUsing& enumBirthDateAgeUsing : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::GetPatientBirthDateAge(LPCTSTR szDcmBirthDate, LPCTSTR szDcmAge, int& iAge, int& iAgeUnit, DATE& dtBirthDate, PatientBirthDateAgeUsing& enumBirthDateAgeUsing)
{
	CString strDcmBirthDate = szDcmBirthDate;
	CString strDcmAge = szDcmAge;

	if (strDcmBirthDate.IsEmpty() && strDcmAge.IsEmpty())
	{
		enumBirthDateAgeUsing = enumBirthDateAgeUsing_None;
		iAge = 0;
		iAgeUnit = 0;
		dtBirthDate = GetDATEByCurrentDateTime();
	}
	else if (!strDcmBirthDate.IsEmpty() && strDcmAge.IsEmpty())
	{
		enumBirthDateAgeUsing = enumBirthDateAgeUsing_BirthDate;
		iAge = 0;
		iAgeUnit = 0;
		dtBirthDate = GetDATEFromDcmDate(strDcmBirthDate);
	}
	else if (strDcmBirthDate.IsEmpty() && !strDcmAge.IsEmpty())
	{
		dtBirthDate = GetDATEByCurrentDateTime();
		if (4 == strDcmAge.GetLength())
		{
			enumBirthDateAgeUsing = enumBirthDateAgeUsing_Age;
			iAge = _ttoi(strDcmAge.Left(3));
			switch (strDcmAge.GetAt(3))
			{
			case _T('D'):
				iAgeUnit = 2;
				break;
			case _T('W'):
				enumBirthDateAgeUsing = enumBirthDateAgeUsing_None;
				iAge = 0;
				iAgeUnit = 0;
				break;
			case _T('M'):
				iAgeUnit = 1;
			    break;
			case _T('Y'):
				iAgeUnit = 0;
			    break;
			default:
				enumBirthDateAgeUsing = enumBirthDateAgeUsing_None;
				iAge = 0;
				iAgeUnit = 0;
			    break;
			}
		}
		else
		{
			enumBirthDateAgeUsing = enumBirthDateAgeUsing_None;
			iAge = 0;
			iAgeUnit = 0;
		}
	}
	else
	{
		//<< ����Ϊ�գ������ݳ������ڣ���������
		enumBirthDateAgeUsing = enumBirthDateAgeUsing_BirthDate;
		iAge = 0;
		iAgeUnit = 0;
		dtBirthDate = GetDATEFromDcmDate(strDcmBirthDate);
	}
}


/**
 ********************************************************************
 * \brief MPPS�Ƿ���Ч
 *  
 *  
 * \param BOOL* pbValid : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::IsMPPSValid(BOOL* pbValid)
{
	*pbValid = FALSE;
	vector<NetworkNodeStruct> vtrServers;
	if (E_OK != m_pMppsIniOpt->GetServers(&vtrServers))
	{
		return FALSE;
	}

	for (int i = 0; i < vtrServers.size(); i++)
	{
		if (vtrServers[i].bDefault)
		{
			*pbValid = TRUE;
			break;
		}
	}


	return TRUE;
}


/**
 ********************************************************************
 * \brief �жϼ��MPPS״̬�Ƿ�ʹ��
 *  
 *  
 * \param LPCTSTR szStudyUID : [in] 
 * \param BOOL* pbEnabled : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::IsSetMPPSStatusEnabled(LPCTSTR szStudyUID, BOOL* pbEnabled)
{
	if (NULL == szStudyUID || NULL == pbEnabled)
	{
		return FALSE;
	}

	StudyInfoStruct StudyInfo;
	CString strTrace;
	
	if (!CDBController::GetInstance()->GetStudyInfo(szStudyUID, &StudyInfo))
	{
		*pbEnabled = FALSE;
		strTrace.Format(_T("CDBController::GetInstance()->GetStudyInfo(), StudyUID: %s"), szStudyUID);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	MPPS_STATE enumMPPSState = StudyInfo.enumMPPSState;
	CBSTROpt::FreeStudyInfoStruct(&StudyInfo);

	// 1. whether the MPPS status of the Study is enumMPPSStatus_InProgress or not?
	//    (SET enabled only if the MPPS status of the study is enumMPPSStatus_InProgress 
	//    since this SET is requested by Clinical User!)
	switch (enumMPPSState)
	{
	case enumMPPSStatus_NotImported:
		*pbEnabled = FALSE;
		// UserGuidance to notify User
// 		NotifyUG(IDS_PRINTINGARCHIVING_MPPS_APPLICABLE_TO_INPROGRESS, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		return TRUE;

	case enumMPPSStatus_Imported:
		*pbEnabled = FALSE;
		// UserGuidance to notify User
// 		NotifyUG(IDS_PRINTINGARCHIVING_MPPS_APPLICABLE_TO_INPROGRESS, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		return TRUE;

	case enumMPPSStatus_InProgress:
		// just break
	    break;

	case enumMPPSStatus_Discontinued:
		*pbEnabled = FALSE;
		// UserGuidance to notify User
// 		NotifyUG(IDS_PRINTINGARCHIVING_MPPS_APPLICABLE_TO_INPROGRESS, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
	    return TRUE;

	case enumMPPSStatus_Completed:
		*pbEnabled = FALSE;
		// UserGuidance to notify User
// 		NotifyUG(IDS_PRINTINGARCHIVING_MPPS_APPLICABLE_TO_INPROGRESS, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		return TRUE;

	default:
		*pbEnabled = FALSE;
	    return FALSE;
	}

	// 2. Whether a SET is under-working in the SET list or not?
	CSingleLock	sLock(&m_CSLockMppsList);
	sLock.Lock();

	list<MppsStatusStruct>::iterator it;
	for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); it++)
	{
		if (!it->strStudyUID.Compare(szStudyUID))
		{
			// ����������һ���ṹ�Ը�Study����MPPS SET
			*pbEnabled = FALSE;

			// UserGuidance to notify User
// 			NotifyUG(IDS_PRINTINGARCHIVING_MPPS_SETTING_PLZ_WAIT, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
			sLock.Unlock();
			return TRUE;			
		}
	}

	// ������û�жԸ�Study��SET����SET is Enabled
	*pbEnabled = TRUE;

	sLock.Unlock();
	return TRUE;

}


/**
 ********************************************************************
 * \brief ��ü��MPPS״̬
 *  
 *  
 * \param LPCTSTR szStudyUID : [in] 
 * \param WorkListStatus* penumStatus : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::GetStudyMppsStatus(LPCTSTR szStudyUID, WorkListStatus* penumStatus)
{
	if (NULL == szStudyUID || NULL == penumStatus)
	{
		return FALSE;
	}

	CString strTrace;
	StudyInfoStruct aStudyInfo;
	if (CDBController::GetInstance()->GetStudyInfo(szStudyUID, &aStudyInfo))
	{
		MPPS_STATE enumMPPSState = aStudyInfo.enumMPPSState;
		CBSTROpt::FreeStudyInfoStruct(&aStudyInfo);

		switch(enumMPPSState)
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
		strTrace.Format(_T("CDBController::GetInstance()->GetStudyInfo(), StudyUID:%s"), szStudyUID);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
}



/**
 ********************************************************************
 * \brief ����MPPS״̬
 *  
 *  
 * \param LPCTSTR szStudyUID : [in] 
 * \param WorkListStatus enumStatus : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::SetMppsStatus(LPCTSTR szStudyUID, WorkListStatus enumStatus)
{
	BOOL bRet = TRUE;
	CString strTrace;

	if (NULL == szStudyUID)
	{
		return FALSE;
	}

	if (enumWorkListStatus_InProgress != enumStatus &&
		enumWorkListStatus_Discontinued != enumStatus &&
		enumWorkListStatus_Completed != enumStatus)
	{
		return FALSE;
	}

	CSingleLock	sLock(&m_CSLockMppsList);
	sLock.Lock();

	list<MppsStatusStruct>::iterator it;

	// ���ǽ�բ���£��ı�MPPS�б��и��ṹ��report״̬
	for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); ++it)
	{
		//<< ��բ���£��ı�report״̬
		if (enumWorkListStatus_InProgress == enumStatus)
		{
			it->bReport = FALSE;
		}
	}

	// ����SET�Ƿ��б�Ҫ
	for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); it++)
	{
		if (!it->strStudyUID.Compare(szStudyUID))
		{
			// ������������һ���ṹ�Ը�Study����MPPS SETʱ��������ͬʱ�ٶ���������ã�
			sLock.Unlock();
			return TRUE;			
		}
	}

	// ����DB�е��ֶ�StudyInfoStruct.enumMPPSState�жϱ���SET�Ƿ����
	StudyInfoStruct StudyInfo;
	if (!CDBController::GetInstance()->GetStudyInfo(szStudyUID, &StudyInfo))
	{
		strTrace.Format(_T("CDBController::GetInstance()->GetStudyInfo(), StudyUID: %s"), szStudyUID);
		PRINTTRACE_ERROR(strTrace)
		sLock.Unlock();
		return FALSE;
	}

	if (((enumMPPSStatus_NotImported == StudyInfo.enumMPPSState || enumMPPSStatus_Imported == StudyInfo.enumMPPSState) && enumWorkListStatus_InProgress == enumStatus) ||
		(enumMPPSStatus_InProgress == StudyInfo.enumMPPSState && (enumWorkListStatus_Completed == enumStatus || enumWorkListStatus_Discontinued == enumStatus)))
	{
		// SET����
	}
	else
	{
		CBSTROpt::FreeStudyInfoStruct(&StudyInfo);
		strTrace.Format(_T("SET is invalid since pStudyInfo->enumMPPSState: %d and enumStatus(to be set): %d, StudyUID: %s"), StudyInfo.enumMPPSState, enumStatus, szStudyUID);
		PRINTTRACE_WARNING(strTrace)
		sLock.Unlock();
		return FALSE;
	}

	// 
	MppsStatusStruct mss;
	mss.strStudyUID = szStudyUID;
	mss.enumStatus = enumStatus;
	mss.strPatientUID = CBSTROpt::BSTRToCString(StudyInfo.bsPatientUID);
	mss.hThread = NULL;
	mss.pMppsOpt = NULL;
	CBSTROpt::FreeStudyInfoStruct(&StudyInfo);

	if (enumWorkListStatus_InProgress == enumStatus)
	{
		mss.bReport = TRUE;
	}
	else
	{
		mss.bReport = TRUE;
	}

	m_lstMppsStatus.push_back(mss);
	it = m_lstMppsStatus.end();
	--it;

	// this MppsStatusStruct is new(ed) to pass the StudyUID and Status to the Thread
	MppsStatusStruct* pStruct = new MppsStatusStruct;
	pStruct->strStudyUID = szStudyUID;
	pStruct->enumStatus = enumStatus;
	pStruct->strPatientUID = _T("");
	pStruct->hThread = NULL;
	pStruct->pMppsOpt = NULL;
	pStruct->bReport = FALSE;
	
 	it->hThread = CreateThread(NULL, 0, SetMppsStatusThreadProc, (LPVOID)pStruct, 0, NULL);
	if (NULL != it->hThread)
	{
		sLock.Unlock();
		return TRUE;
	}
	else
	{
		delete pStruct;
		m_lstMppsStatus.erase(it);
		PRINTTRACE_ERROR("CreateThread(NULL, 0, SetMppsStatusThreadProc, this, 0, NULL)")
		sLock.Unlock();
		return FALSE;
	}
}


/**
 ********************************************************************
 * \brief ����MPPS״̬����
 *  
 *  
 * \param MppsStatusStruct* pStruct : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::SetMppsStatusProc(MppsStatusStruct* pStruct)
{
	list<MppsStatusStruct>::iterator it;
	for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); it++)
	{
		if (!pStruct->strStudyUID.Compare(it->strStudyUID) &&
			pStruct->enumStatus == it->enumStatus)
		{
			break;
		}
	}

	if (it == m_lstMppsStatus.end())
	{
		return FALSE;
	}

	int iErrCode = E_OK;
	CString strTrace;
	NetworkNodeStruct ServerNode;
	vector<WLQueryItem> vtrItems;
	
	iErrCode = m_pMppsIniOpt->GetDefaultServer(&ServerNode);
	if (E_OK == iErrCode)
	{
		// succeed
	}
	else if (E_WLMPPS_INI_NO_SERVER == iErrCode ||
		E_WLMPPS_INI_NO_SERVER_SELECTED == iErrCode)
	{
		// Whether User Guidance is needed or not
		// FanZF: unneeded, by 2007-12-26
		PRINTTRACE_WARNING("E_WLMPPS_NO_SERVER or E_WLMPPS_NO_SERVER_SELECTED == m_pMppsIniOpt->GetDefaultServer(&ServerStruct)")
		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR("m_pMppsIniOpt->GetDefaultServer(&ServerNode)")
		return FALSE;
	}

	if (enumWorkListStatus_InProgress == it->enumStatus)
	{
		if (!m_pMppsIniOpt->GetNCreateItems(&vtrItems))
		{
			PRINTTRACE_ERROR("GetNCreateItems(&vtrItems)")
			return FALSE;
		}

		if (!UpdateNCreateItems(vtrItems, it->strStudyUID))
		{
			PRINTTRACE_ERROR("UpdateNCreateItems(vtrItems, it->strStudyUID)")
			return FALSE;
		}
	}
	else
	{
		if (!m_pMppsIniOpt->GetNSetItems(&vtrItems))
		{
			PRINTTRACE_ERROR("GetNCreateItems(&vtrItems)")
			return FALSE;
		}

		if (!UpdateNSetItems(vtrItems, it->enumStatus, it->strStudyUID))
		{
			PRINTTRACE_ERROR("UpdateNSetItems(vtrItems, it->enumStatus)")
			return FALSE;
		}
	}


	CString strMppsSOPInstanceUID;
	CDcmUIDGen UIDGen;
	strMppsSOPInstanceUID = UIDGen.GenMppsSOPInstanceUID(it->strStudyUID);

	it->pMppsOpt = new CMppsOpt;
	it->pMppsOpt->SetServer(ServerNode.strCalledAE, ServerNode.strIP, ServerNode.strPort, ServerNode.strCallingAE);
	DWORD dwStart = GetTickCount();

	if (enumWorkListStatus_InProgress == it->enumStatus)
	{
		iErrCode = it->pMppsOpt->NCreate(&vtrItems, strMppsSOPInstanceUID);
	}
	else
	{
		iErrCode = it->pMppsOpt->NSet(&vtrItems, strMppsSOPInstanceUID);
	}

	if (E_OK == iErrCode)
	{
		strTrace.Format(_T("it->pMppsOpt->NCreate or NSet time used: %d, StudyUID: %s"), GetTickCount() - dwStart, it->strStudyUID);
		PRINTTRACE_INFO(strTrace)

		// Set MPPS status to the study and close the study(if needed) in DB
		StudyInfoStruct StudyInfo;
		if (CDBController::GetInstance()->GetStudyInfo(it->strStudyUID, &StudyInfo))
		{
			switch(it->enumStatus)
			{
			case enumWorkListStatus_InProgress:
				StudyInfo.enumMPPSState = enumMPPSStatus_InProgress;
				break;
			case enumWorkListStatus_Completed:
				StudyInfo.enumMPPSState = enumMPPSStatus_Completed;
				break;
			case enumWorkListStatus_Discontinued:
				StudyInfo.enumMPPSState = enumMPPSStatus_Discontinued;
				break;
			default:
				CBSTROpt::FreeStudyInfoStruct(&StudyInfo);
				return FALSE;;
			}

			if (CDBController::GetInstance()->ModifyStudyInfo(&StudyInfo))
			{
				// Notify GUI that Study MPPS status has changed
				CBSTROpt::FreeStudyInfoStruct(&StudyInfo);
				BSTR bsStudyUID = it->strStudyUID.AllocSysString();
				Notify(NOTIFY_WLMPPS_MPPS_STATUS_CHANGED, (LPARAM)bsStudyUID, (WPARAM)it->enumStatus);
				return TRUE;
			}
			else
			{
				CBSTROpt::FreeStudyInfoStruct(&StudyInfo);
				strTrace.Format(_T("CDBController::GetInstance()->ModifyStudyInfo(), StudyUID: %s"), it->strStudyUID);
				PRINTTRACE_ERROR(strTrace)
				return FALSE;
			}
		}
		else
		{
			strTrace.Format(_T("CDBController::GetInstance()->GetStudyInfo(), StudyUID: %s"), it->strStudyUID);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
	}
	else if (E_WLMPPS_CNT_SERVER_FAILED == iErrCode)
	{
		// UserGuidance to notify User
		NotifyUG(IDS_PRINTINGARCHIVING_MPPS_CNT_SVR_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		PRINTTRACE_ERROR("it->pMppsOpt->NCreate() or NSet(), E_WLMPPS_CNT_SERVER_FAILED == iErrCode")
		return FALSE;
	}
	else if (E_WLMPPS_NCREATE_FAILED == iErrCode ||
			 E_WLMPPS_NCREATE_OK_RESULT_FAILED == iErrCode ||
			 E_WLMPPS_NSET_FAILED == iErrCode ||
			 E_WLMPPS_NSET_OK_RESULT_FAILED == iErrCode)
	{
		// UserGuidance to notify User
// 		NotifyUG(IDS_PRINTINGARCHIVING_MPPS_NCREATE_OR_NSET_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		PRINTTRACE_ERROR("it->pMppsOpt->NCreate() or NSet(),  E_WLMPPS_NCREATE_FAILED etc. == iErrCode")
		return FALSE;
	}
	else
	{
		PRINTTRACE_ERROR("it->pMppsOpt->NCreate() or NSet()")
		return FALSE;
	}
}


/**
 ********************************************************************
 * \brief ȡ��MPPS����
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::CancelMppsNProc()
{
	CSingleLock	sLock(&m_CSLockMppsList);
	sLock.Lock();

	BOOL bRet = TRUE;

	HANDLE* phThread = new HANDLE[m_lstMppsStatus.size()];
	list<MppsStatusStruct>::iterator it = m_lstMppsStatus.begin();
	int i = 0;
	for (; it != m_lstMppsStatus.end(); it++, i++)
	{
		phThread[i] = it->hThread;
	}

	sLock.Unlock();

	//<< ע�⣺��ʱm_SubModuleStateΪenumSubModuleState_UnInitializing��
	//<< ���߳�SetMppsStatusThreadProc��󲻻��MPPS�б���нṹɾ������
	//<< Դ�ͷţ�������Щ��������CancelMppsNProc()������
	//<< ����Ϊ�˷�ֹWaitForMultipleObjects()�ȴ����߳̾����ָ����̺߳�
	//<< �Ķ����ѱ�����ϵͳ�ͷţ�����WaitForMultipleObjects()���Ϸ���WAIT_FAILED
	WaitForMultipleObjects(m_lstMppsStatus.size(), phThread, TRUE, SHUTDOWN_SUBMODULE_MPPS_CANCEL_NPROC_WAIT_TIME);
	delete []phThread;
	phThread = NULL;

	sLock.Lock();
	
	for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); it++)
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(it->hThread, 0))
		{
			if (TerminateThread(it->hThread, 0))
			{
				PRINTTRACE_INFO("TerminateThread(it->hThread)")
			}
			else
			{
				bRet = FALSE;
				PRINTTRACE_ERROR("TerminateThread(it->hThread)")
			}
		}

		CloseHandle(it->hThread);
		it->hThread = NULL;

		if (NULL != it->pMppsOpt)
		{
			delete it->pMppsOpt;
			it->pMppsOpt = NULL;
		}

		UpdateMppsWorkState(FALSE);
	}

	m_lstMppsStatus.clear();
	
	sLock.Unlock();
	return bRet;
}



/**
 ********************************************************************
 * \brief Update the NCreate Dcm items by DB and something else
 *  
 *  
 * \param vector<WLQueryItem>& vtrItems : [in] 
 * \param LPCTSTR szStudyUID : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::UpdateNCreateItems(vector<WLQueryItem>& vtrItems, LPCTSTR szStudyUID)
{
	if (NULL == szStudyUID)
	{
		return FALSE;
	}

	CString				strTrace;
	StudyInfoStruct		StudyInfo;
	PatientInfoStruct	PatientInfo;

	if (!CDBController::GetInstance()->GetStudyInfo(szStudyUID, &StudyInfo))
	{
		strTrace.Format(_T("CDBController::GetInstance()->GetStudyInfo(), StudyUID: %s"), szStudyUID);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	CString strPatientUID = CBSTROpt::BSTRToCString(StudyInfo.bsPatientUID);
	if (!CDBController::GetInstance()->GetPatientInfo(strPatientUID, &PatientInfo))
	{
		CBSTROpt::FreeStudyInfoStruct(&StudyInfo);
		strTrace.Format(_T("CDBController::GetInstance()->GetPatientInfo(), PatientUID: %s"), strPatientUID);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	CString strValue;
	int iPPSStartDateIndex, iPPSStartTimeIndex;
	iPPSStartDateIndex = iPPSStartTimeIndex = -1;
	for (int i = 0; i < vtrItems.size(); i++)
	{
		// 1. StudyInstanceUID
		if (0x0020 == vtrItems[i].usGroup && 0x000d == vtrItems[i].usElement)
		{
			strValue = CBSTROpt::BSTRToCString(StudyInfo.bsInstanceUID);
			if (strValue.IsEmpty())
			{
				//<< ����StudyInstanceUID
				CString strStudyUID = CBSTROpt::BSTRToCString(StudyInfo.bsStudyUID);
				CDcmUIDGen aDcmUIDGen;
				vtrItems[i].strValue = aDcmUIDGen.GenStudyInstanceUID(strStudyUID);
				continue;
			}
			else
			{
				vtrItems[i].strValue = strValue;
				continue;
			}
		}

		// 1.1 Accession Number
		if (0x0008 == vtrItems[i].usGroup && 0x0050 == vtrItems[i].usElement)
		{
			strValue = CBSTROpt::BSTRToCString(StudyInfo.bsAccessionNumber);
			vtrItems[i].strValue = strValue;

		}

		// 2. Patient's Name
		if (0x0010 == vtrItems[i].usGroup && 0x0010 == vtrItems[i].usElement)
		{
			strValue = CBSTROpt::BSTRToCString(PatientInfo.bsPatientName);
			vtrItems[i].strValue = strValue;

		}

		// 3. Patient's ID
		if (0x0010 == vtrItems[i].usGroup && 0x0020 == vtrItems[i].usElement)
		{
			strValue = CBSTROpt::BSTRToCString(PatientInfo.bsPatientID);
			vtrItems[i].strValue = strValue;
			continue;
		}

		// 4. Patient Birth Date
		if (0x0010 == vtrItems[i].usGroup && 0x0030 == vtrItems[i].usElement)
		{
			GetDcmDateByDATE(vtrItems[i].strValue, PatientInfo.dtBirthDate);
			continue;
		}

		// 5. Patient's Sex
		if (0x0010 == vtrItems[i].usGroup && 0x0040 == vtrItems[i].usElement)
		{
			switch (PatientInfo.iGender)
			{
			case 0:
				strValue = _T("M");
				break;
			case 1:
				strValue = _T("F");
			    break;
			default:
				strValue = _T("O");
			    break;
			}
			vtrItems[i].strValue = strValue;
			continue;
		}

		// 6. Study ID
		if (0x0020 == vtrItems[i].usGroup && 0x0010 == vtrItems[i].usElement)
		{
			strValue.Format(_T("%d"), StudyInfo.iStudyID);
			vtrItems[i].strValue = strValue;
			continue;
		}

		// 7. PPSStartDateIndex
		if (0x0040 == vtrItems[i].usGroup && 0x0244 == vtrItems[i].usElement)
		{
			iPPSStartDateIndex = i;
			continue;
		}

		// 8. PPSStartTimeIndex
		if (0x0040 == vtrItems[i].usGroup && 0x0245 == vtrItems[i].usElement)
		{
			iPPSStartTimeIndex = i;
			continue;
		}

		// 9. PPSStatus
		if (0x0040 == vtrItems[i].usGroup && 0x0252 == vtrItems[i].usElement)
		{
			vtrItems[i].strValue = MPPS_STATUS_INPROGRESS;
			continue;
		}

		// 10. ...
	}

	CBSTROpt::FreeStudyInfoStruct(&StudyInfo);
	CBSTROpt::FreePatientInfoStruct(&PatientInfo);

	if (-1 == iPPSStartDateIndex ||
		-1 == iPPSStartTimeIndex)
	{
		return FALSE;
	}
	else
	{
		GetDcmDateTimeByCurrentDateTime(vtrItems[iPPSStartDateIndex].strValue, vtrItems[iPPSStartTimeIndex].strValue);
	}
	
	return TRUE;
}


/**
 ********************************************************************
 * \brief Update the NSet Dcm items by DB and something else
 *  
 *  
 * \param vector<WLQueryItem>& vtrItems : [in] 
 * \param WorkListStatus enumStatus : [in] 
 * \param LPCTSTR szStudyUID : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::UpdateNSetItems(vector<WLQueryItem>& vtrItems, WorkListStatus enumStatus, LPCTSTR szStudyUID)
{
	if (NULL == szStudyUID)
	{
		return FALSE;
	}

	CString				strTrace;
	StudyInfoStruct		StudyInfo;

	if (!CDBController::GetInstance()->GetStudyInfo(szStudyUID, &StudyInfo))
	{
		strTrace.Format(_T("CDBController::GetInstance()->GetStudyInfo(), StudyUID: %s"), szStudyUID);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	CString strValue;
	int iPPSEndDateIndex, iPPSEndTimeIndex;
	iPPSEndDateIndex = iPPSEndTimeIndex = -1;
	
	for (int i = 0; i < vtrItems.size(); i++)
	{
		// 1. PerformingPhysiciansName
		if (0x0008 == vtrItems[i].usGroup && 0x1050 == vtrItems[i].usElement)
		{
			strValue = CBSTROpt::BSTRToCString(StudyInfo.bsPerformingPhysicianName);
			vtrItems[i].strValue = strValue;
			continue;
		}

		// 2. Operator'sName
		if (0x0008 == vtrItems[i].usGroup && 0x1070 == vtrItems[i].usElement)
		{
			strValue = CBSTROpt::BSTRToCString(StudyInfo.bsOperatorName);
			vtrItems[i].strValue = strValue;
			continue;
		}

		// 3. NSetSeriesInstanceUID
		if (0x0020 == vtrItems[i].usGroup && 0x000e == vtrItems[i].usElement)
		{
			CDcmUIDGen DcmUIDGen;
			vtrItems[i].strValue = DcmUIDGen.GenMPPSNSetSeriesInstanceUID(szStudyUID);
			continue;
		}

		// 4. PPSEndDateIndex
		if (0x0040 == vtrItems[i].usGroup && 0x0250 == vtrItems[i].usElement)
		{
			iPPSEndDateIndex = i;
			continue;
		}

		// 5. PPSEndTimeIndex
		if (0x0040 == vtrItems[i].usGroup && 0x0251 == vtrItems[i].usElement)
		{
			iPPSEndTimeIndex = i;
			continue;
		}

		// 6. PPSStatus
		if (0x0040 == vtrItems[i].usGroup && 0x0252 == vtrItems[i].usElement)
		{
			if (enumWorkListStatus_Discontinued == enumStatus)
			{
				vtrItems[i].strValue = MPPS_STATUS_DISCONTINUED;
				continue;
			} 
			else if (enumWorkListStatus_Completed == enumStatus)
			{
				vtrItems[i].strValue = MPPS_STATUS_COMPLETED;
				continue;
			}
			else
			{
				return FALSE;
			}
		}
	}

	CBSTROpt::FreeStudyInfoStruct(&StudyInfo);

	if (-1 == iPPSEndDateIndex || -1 == iPPSEndTimeIndex)
	{
		return FALSE;
	}
	else
	{
		GetDcmDateTimeByCurrentDateTime(vtrItems[iPPSEndDateIndex].strValue, vtrItems[iPPSEndTimeIndex].strValue);
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief ����MPPS����״̬
 *  
 *  
 * \param BOOL bWorking : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::UpdateMppsWorkState(BOOL bWorking)
{
	BOOL bIsWorking = FALSE;
	if (bWorking)
	{
		bIsWorking = TRUE;
	}
	else
	{
		list<MppsStatusStruct>::iterator it;
		for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); it++)
		{
			if (NULL != it->hThread)
			{
				bIsWorking = TRUE;
				break;
			}
		}
	}

	if (bIsWorking != m_bMppsWorking)
	{
		CSingleLock sLock(&m_CSLockMppsWorkState);
		sLock.Lock();
		m_bMppsWorking = bIsWorking;
		sLock.Unlock();

		UpdateWlMppsWorkState();
	}
}


/**
 ********************************************************************
 * \brief ��DB�������������DICOM����
 *  
 *  
 * \param CString& strDcmPN : [in] 
 * \param LPCTSTR szDBPN : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::GetDcmPatientNameFromDBPatientName(CString& strDcmPN, LPCTSTR szDBPN)
{
	// DB PatientName: ??##??##??
	// Dcm Patient's Name: family name complex(LastName)^given name complex(FirstName)^middle name(MidName)

	CString strPatientNameInDB = szDBPN;

	int iIndex = 0;
	iIndex = strPatientNameInDB.Find(_T("##"));
	if (-1 == iIndex)
	{
		PRINTTRACE_ERROR("-1 == strPatientNameInDB.Find(_T(##))")
		return FALSE;
	}
	CString strFirstName(strPatientNameInDB, iIndex);
	CString strNameBeginByMid = strPatientNameInDB.Mid(iIndex + 2);

	iIndex = strNameBeginByMid.Find(_T("##"));
	if (-1 == iIndex)
	{
		PRINTTRACE_ERROR("-1 == strNameBeginByMid.Find(_T(##)")
		return FALSE;
	}
	CString strMidName = strNameBeginByMid.Left(iIndex);
	CString strLastName = strNameBeginByMid.Mid(iIndex + 2);

	strDcmPN = strLastName + _T("^") + strFirstName + _T("^") + strMidName;
	return TRUE;
}


/**
 ********************************************************************
 * \brief �ɵ�ǰʱ����DICOMʱ�� 
 *  
 *  
 * \param CString& strDcmDate : [in] 
 * \param CString& strDcmTime : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::GetDcmDateTimeByCurrentDateTime(CString& strDcmDate, CString& strDcmTime)
{
	SYSTEMTIME st;
	::GetLocalTime(&st);

	strDcmDate.Format(_T("%04d%02d%02d"), st.wYear, st.wMonth, st.wDay);
	strDcmTime.Format(_T("%02d%02d%02d.%03d"), st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
}


/**
 ********************************************************************
 * \brief ��DATE���DICOM ����
 *  
 *  
 * \param CString& strDcmDate : [in] 
 * \param DATE date : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::GetDcmDateByDATE(CString& strDcmDate, DATE date)
{
	COleDateTime odtDateTime = date;
	strDcmDate = odtDateTime.Format(_T("%Y%m%d"));
}


/**
 ********************************************************************
 * \brief ֪ͨUIһ��MPPS״̬���������
 *  
 *  
 * \param LPCTSTR szStudyUID : [in] 
 * \param WorkListStatus enumStatus : [in] 
 * \param BOOL bResult : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::NotifySetMppsFinished(LPCTSTR szStudyUID, WorkListStatus enumStatus, BOOL bResult)
{
	list<MppsStatusStruct>::iterator it;
	for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); it++)
	{
		if (!it->strStudyUID.Compare(szStudyUID) &&
			enumStatus == it->enumStatus)
		{
			if (it->bReport)
			{
				// Report to GUI
				MppsSetResult* pResult = new MppsSetResult;
				pResult->bsStudyUID = CString(szStudyUID).AllocSysString();
				pResult->enumStatus = enumStatus;
				pResult->bResult = bResult;
				Notify(NOTIFY_WLMPPS_SET_MPPS_FINISHED, (LPARAM)pResult);
			}
			return;
		}
	}

}


/**
 ********************************************************************
 * \brief ��MPPS�����б������һ��ָ������
 *  
 *  
 * \param LPCTSTR szStudyUID : [in] 
 * \param WorkListStatus enumStatus : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::RemoveMppsStatusStruct(LPCTSTR szStudyUID, WorkListStatus enumStatus)
{
	//<< ������ģ�鴦��enumSubModuleState_UnInitializing״̬������б����Ƴ��ṹ
	//<< ���ͷ���Դ�Ĺ�������CancelMppsNProc()����
	if (enumSubModuleState_UnInitializing == m_SubModuleState)
	{
		return TRUE;
	}
	else
	{
		CSingleLock	sLock(&m_CSLockMppsList);
		sLock.Lock();

		list<MppsStatusStruct>::iterator it;
		for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); it++)
		{
			if (!it->strStudyUID.Compare(szStudyUID) &&
				enumStatus == it->enumStatus)
			{
				//<< �ҵ��ýṹ���ͷ���Դ�����б����Ƴ��ýṹ
				CloseHandle(it->hThread);
				it->hThread = NULL;

				if (NULL != it->pMppsOpt)
				{
					delete it->pMppsOpt;
					it->pMppsOpt = NULL;
				}

				m_lstMppsStatus.erase(it);

				sLock.Unlock();
				return TRUE;
			}
		}

		sLock.Unlock();
		return FALSE;
	}
}


/**
 ********************************************************************
 * \brief �ж��Ƿ��ߵ�UID��ʹ��
 *  
 *  
 * \param PatientAdminUIDType enumUIDType : [in] 
 * \param vector<CString>* pvtrUIDList : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::IsPatientStudySeriesUIDInUse(PatientAdminUIDType enumUIDType, vector<CString>* pvtrUIDList)
{
	CSingleLock	sLock(&m_CSLockMppsList);
	sLock.Lock();

	switch (enumUIDType)
	{
	case enumPatientAdminUIDType_Patient:
		{
			list<MppsStatusStruct>::iterator it;
			for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); ++it)
			{
				for (int i = 0; i < pvtrUIDList->size(); i++)
				{
					if (!it->strPatientUID.Compare((*pvtrUIDList)[i]))
					{
						sLock.Unlock();
						return TRUE;
					}
				}
			}
			break;
		}
	case enumPatientAdminUIDType_Study:
		{
			list<MppsStatusStruct>::iterator it;
			for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); ++it)
			{
				for (int i = 0; i < pvtrUIDList->size(); i++)
				{
					if (!it->strStudyUID.Compare((*pvtrUIDList)[i]))
					{
						sLock.Unlock();
						return TRUE;
					}
				}
			}
			break;
		}
	case enumPatientAdminUIDType_Series:
		break;
	default:
		break;
	}

	sLock.Unlock();
	return FALSE;
}



/**
 ********************************************************************
 * \brief WorkList�Ƿ����ڹ���
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::IsWorkListWorking()
{
	return m_bWorkListWorking;
}


/**
 ********************************************************************
 * \brief MPPS�Ƿ����ڹ���
 *  
 *  
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::IsMppsWorking()
{
	return m_bMppsWorking;
}


/**
 ********************************************************************
 * \brief �Ƿ�ָ���ļ�����ڹر�MPPS
 *  
 *  
 * \param LPCTSTR szStudyUID : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::IsClosingStudyMPPS(LPCTSTR szStudyUID)
{
	CSingleLock	sLock(&m_CSLockMppsList);
	sLock.Lock();

	list<MppsStatusStruct>::iterator it;
	for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); ++it)
	{
		if (!it->strStudyUID.Compare(szStudyUID))
		{
			if (enumWorkListStatus_Completed == it->enumStatus ||
				enumWorkListStatus_Discontinued == it->enumStatus)
			{
				sLock.Unlock();
				return TRUE;
			}
		}
	}

	sLock.Unlock();
	return FALSE;
}


/**
 ********************************************************************
 * \brief �Ƿ�ָ�����ߵ�ĳ������ָ�������������MPPS
 *  
 *  
 * \param vector<CString>& vtrUIDs : [in] 
 * \param PatientAdminUIDType enumUIDType : [in] 
 * \param BOOL* pbSetting : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::IsSettingPatientOrStudyMPPS(vector<CString>& vtrUIDs, PatientAdminUIDType enumUIDType, BOOL* pbSetting)
{
	CSingleLock	sLock(&m_CSLockMppsList);
	sLock.Lock();

	switch (enumUIDType)
	{
	case enumPatientAdminUIDType_Patient:
		{
			list<MppsStatusStruct>::iterator it;
			for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); ++it)
			{
				for (int i = 0; i < vtrUIDs.size(); ++i)
				{
					if (!it->strPatientUID.Compare(vtrUIDs[i]))
					{
						*pbSetting = TRUE;
						sLock.Unlock();
						return TRUE;
					}
				}
			}
		}
		break;
	case enumPatientAdminUIDType_Study:
		{
			list<MppsStatusStruct>::iterator it;
			for (it = m_lstMppsStatus.begin(); it != m_lstMppsStatus.end(); ++it)
			{
				for (int i = 0; i < vtrUIDs.size(); ++i)
				{
					if (!it->strStudyUID.Compare(vtrUIDs[i]))
					{
						*pbSetting = TRUE;
						sLock.Unlock();
						return TRUE;
					}
				}
			}
		}
		break;
	default:
		*pbSetting = FALSE;
		sLock.Unlock();
		return FALSE;
	}

	*pbSetting = FALSE;
	sLock.Unlock();
	return TRUE;

}


/**
 ********************************************************************
 * \brief ת��UserGuidance
 *  
 *  
 * \param LONG iMessageID : [in] 
 * \param UserGuidanceType enumUGType : [in] 
 * \param UserGuidancePriority enumGUIPriority : [in] 
 * \param BOOL bActive : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive)
{ 
	UGNotifyStruct* pUGNStruct = new UGNotifyStruct; 
	pUGNStruct->iMessageID = (iMessageID);
	pUGNStruct->enumUGType = (enumUGType);
	pUGNStruct->enumGUIPriority = (enumGUIPriority);
	pUGNStruct->bActive = (bActive); 
	Notify(NOTIFY_USERGUIDANCE, (LPARAM)pUGNStruct);
}


/**
 ********************************************************************
 * \brief ���worklist�������б�
 *  
 *  
 * \param NetworkNode** ppServers : [in] 
 * \param long* pLen : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::GetWlServers(NetworkNode** ppServers, long* pLen)
{
	vector<NetworkNodeStruct> vtrServers;
	if (E_OK != m_pWLIniOpt->GetServers(&vtrServers))
	{
		*pLen = 0;
		return FALSE;
	}

	*pLen = vtrServers.size();
	*ppServers = (NetworkNode*)CoTaskMemAlloc(sizeof(NetworkNode) * (*pLen));
	if (NULL == *ppServers)
	{
		*pLen = 0;
		return FALSE;
	}
	
	for (int i = 0; i < *pLen; i++)
	{
		NetworkNode* p = *ppServers + i;
		p->bsCalledAE = vtrServers[i].strCalledAE.AllocSysString();
		p->bsIP = vtrServers[i].strIP.AllocSysString();
		p->bsPort = vtrServers[i].strPort.AllocSysString();
		p->bsCallingAE = vtrServers[i].strCallingAE.AllocSysString();
		p->bDefault = vtrServers[i].bDefault;
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief ����worklist�������б�
 *  
 *  
 * \param NetworkNode* pServers : [in] 
 * \param long lLen : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::SetWlServers(NetworkNode* pServers, long lLen)
{
	vector<NetworkNodeStruct> vtrServers;
	for (int i = 0; i < lLen; i++)
	{
		NetworkNodeStruct nns;
		nns.strCalledAE = CBSTROpt::BSTRToCString(pServers[i].bsCalledAE);
		nns.strIP = CBSTROpt::BSTRToCString(pServers[i].bsIP);
		nns.strPort = CBSTROpt::BSTRToCString(pServers[i].bsPort);
		nns.strCallingAE = CBSTROpt::BSTRToCString(pServers[i].bsCallingAE);
		nns.bDefault = pServers[i].bDefault;

		vtrServers.push_back(nns);
	}

	if (E_OK != m_pWLIniOpt->SetServers(&vtrServers))
	{
		return FALSE;
	}
	
	return TRUE;
}


/**
 ********************************************************************
 * \brief worklist���������Ӳ���
 *  
 *  
 * \param NetworkNode* pServer : [in] 
 * \param BOOL* pbResult : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::WlServerConnectTest(NetworkNode* pServer, BOOL* pbResult)
{
	CVDcmNetworkInfoStruct CVDcmnis;
	CVDcmnis.strCalledAE = CBSTROpt::BSTRToCString(pServer->bsCalledAE);
	CVDcmnis.strCallingAE = CBSTROpt::BSTRToCString(pServer->bsCallingAE);
	CVDcmnis.strIP = CBSTROpt::BSTRToCString(pServer->bsIP);
	CVDcmnis.strPort = CBSTROpt::BSTRToCString(pServer->bsPort);

	m_WLOpt.SetServer(CVDcmnis.strCalledAE, CVDcmnis.strIP, CVDcmnis.strPort, CVDcmnis.strCallingAE);

	if (E_OK == m_WLOpt.ConnectTest())
	{
		*pbResult = TRUE;
	}
	else
	{
		*pbResult = FALSE;
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief ���MPPS�������б�
 *  
 *  
 * \param NetworkNode** ppServers : [in] 
 * \param long* pLen : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::GetMppsServers(NetworkNode** ppServers, long* pLen)
{
	vector<NetworkNodeStruct> vtrServers;
	if (E_OK != m_pMppsIniOpt->GetServers(&vtrServers))
	{
		*pLen = 0;
		return FALSE;
	}

	*pLen = vtrServers.size();
	*ppServers = (NetworkNode*)CoTaskMemAlloc(sizeof(NetworkNode) * (*pLen));
	if (NULL == *ppServers)
	{
		*pLen = 0;
		return FALSE;
	}
	
	for (int i = 0; i < *pLen; i++)
	{
		NetworkNode* p = *ppServers + i;
		p->bsCalledAE = vtrServers[i].strCalledAE.AllocSysString();
		p->bsIP = vtrServers[i].strIP.AllocSysString();
		p->bsPort = vtrServers[i].strPort.AllocSysString();
		p->bsCallingAE = vtrServers[i].strCallingAE.AllocSysString();
		p->bDefault = vtrServers[i].bDefault;

	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief ����MPPS�������б�
 *  
 *  
 * \param NetworkNode* pServers : [in] 
 * \param long lLen : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::SetMppsServers(NetworkNode* pServers, long lLen)
{
	vector<NetworkNodeStruct> vtrServers;
	for (int i = 0; i < lLen; i++)
	{
		NetworkNodeStruct nns;
		nns.strCalledAE = CBSTROpt::BSTRToCString(pServers[i].bsCalledAE);
		nns.strIP = CBSTROpt::BSTRToCString(pServers[i].bsIP);
		nns.strPort = CBSTROpt::BSTRToCString(pServers[i].bsPort);
		nns.strCallingAE = CBSTROpt::BSTRToCString(pServers[i].bsCallingAE);
		nns.bDefault = pServers[i].bDefault;

		vtrServers.push_back(nns);
	}

	if (E_OK != m_pMppsIniOpt->SetServers(&vtrServers))
	{
		return FALSE;
	}
	
	return TRUE;
}


/**
 ********************************************************************
 * \brief MPPS���������Ӳ���
 *  
 *  
 * \param NetworkNode* pServer : [in] 
 * \param BOOL* pbResult : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CWlMpps::MppsServerConnectTest(NetworkNode* pServer, BOOL* pbResult)
{
	CVDcmNetworkInfoStruct CVDcmnis;
	CVDcmnis.strCalledAE = CBSTROpt::BSTRToCString(pServer->bsCalledAE);
	CVDcmnis.strCallingAE = CBSTROpt::BSTRToCString(pServer->bsCallingAE);
	CVDcmnis.strIP = CBSTROpt::BSTRToCString(pServer->bsIP);
	CVDcmnis.strPort = CBSTROpt::BSTRToCString(pServer->bsPort);

	CMppsOpt MppsOpt;
	MppsOpt.SetServer(CVDcmnis.strCalledAE, CVDcmnis.strIP, CVDcmnis.strPort, CVDcmnis.strCallingAE);

	if (E_OK == MppsOpt.ConnectTest())
	{
		*pbResult = TRUE;
	}
	else
	{
		*pbResult = FALSE;
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief ����worklist/MPPS����״̬
 *  
 *  
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::UpdateWlMppsWorkState()
{
	if (!m_bWorkListWorking && !m_bMppsWorking)
	{
		SetSubModuleState(enumSubModuleState_Ready);
	}
	else
	{
		SetSubModuleState(enumSubModuleState_Work);
	}
}


/**
 ********************************************************************
 * \brief ������ģ��״̬
 *  
 *  
 * \param SubModuleState enumSubModuleState : [in] 
 * 
 * \return void  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
void CWlMpps::SetSubModuleState(SubModuleState enumSubModuleState)
{
	CSingleLock sLock(&m_CSLockSubModuleState);
	sLock.Lock();

	if (m_SubModuleState == enumSubModuleState)
	{
		sLock.Unlock();
		return;
	}

	if ((enumSubModuleState_Error == m_SubModuleState) &&
		(enumSubModuleState_Ready == enumSubModuleState ||
		enumSubModuleState_Work == enumSubModuleState))
	{
		// SubModule Init Result is Error, so can't changed to ready or work
		sLock.Unlock();
		return;
	}
	else if ((enumSubModuleState_UnInitializing == m_SubModuleState) &&
		((enumSubModuleState_UnInited != enumSubModuleState) &&
		(enumSubModuleState_Error != enumSubModuleState)))
	{
		// just return;
		sLock.Unlock();
		return;
	}
	else
	{
		m_SubModuleState = enumSubModuleState;
	}
	
	//notify CPA
	Notify(NOTIFY_SUBMODULE_STATE_CHANGED, enumSubModule_WLMPPS, m_SubModuleState);

	CString strTrace;
	strTrace = _T("Transfer SubModule state: ");
	switch (m_SubModuleState)
	{
	case enumSubModuleState_UnInited:
		strTrace += _T("UnInited");
		break;
	case enumSubModuleState_Ready:
		strTrace += _T("Ready");
		break;
	case enumSubModuleState_Work:
		strTrace += _T("Work");
		break;
	case enumSubModuleState_UnInitializing:
		strTrace += _T("UnInitializing");
		break;
	case enumSubModuleState_Error:
		strTrace += _T("Error");
		break;
	default:
		strTrace += _T("Unknow");
		break;
	}
	ARCHVTRACE_INFO(strTrace);

	sLock.Unlock();
}


/**
 ********************************************************************
 * \brief �����ģ��״̬
 *  
 *  
 * 
 * \return SubModuleState  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
SubModuleState CWlMpps::GetSubModuleState()
{
	return m_SubModuleState;
}

