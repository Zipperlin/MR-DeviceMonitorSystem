/* Time: <@(#)Transfer.cpp   2009-3-5 - 10:33:54   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : Transfer.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Capsulation class of image sending function
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:33:54		FanZF	Creation
 *
 *********************************************************************
 */

// Transfer.cpp: implementation of the CTransfer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Transfer.h"
#include "JobHandler.h"
#include "DirHandler.h"
#include "PAEvent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransfer* CTransfer::m_pInstance = NULL;


/**
 ********************************************************************
 * \brief 构造函数
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
CTransfer::CTransfer()
{
	m_hTransferEvent = NULL;

	m_pDcmPartner = NULL;
	m_pCurrentJob = NULL;
	m_SubModuleState = enumSubModuleState_UnInited;

	m_bstrPatientUID = NULL;
	m_bstrStudyUID = NULL;
}


/**
 ********************************************************************
 * \brief 析构函数
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
CTransfer::~CTransfer()
{
	//释放BSTR
	if(NULL != m_bstrPatientUID)
	{
		SysFreeString(m_bstrPatientUID);
	}
	if(NULL != m_bstrStudyUID)
	{
		SysFreeString(m_bstrStudyUID);
	}
}

CTransfer* CTransfer::GetInstance()
{
	if(!m_pInstance)
		m_pInstance = new CTransfer;
	return m_pInstance;
}

void CTransfer::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


/**
 ********************************************************************
 * \brief 初始化函数
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
BOOL CTransfer::Init()
{
	ARCHVTRACE_ENTER_FUNCTION

	BOOL bRet = TRUE;

	m_hTransferEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

	CDcmUIDGen DcmUIDGen;
	m_StoreScuOpt.SetDcmTrasferImpClassUID(DcmUIDGen.GetImplementationClassUID());
	m_StoreScuOpt.SetDcmTrasferImpVersionName(DcmUIDGen.GetImplementationVersionName());
	m_StoreScuOpt.SetDcmTrasferTimeout(DcmUIDGen.GetTransferTimeOut());

	bRet = m_XMLParser.Init();
	if (bRet)
	{
		ARCHVTRACE_INFO("m_XMLParser.Init() succeed")
		SetSubModuleState(enumSubModuleState_Ready);
	}
	else
	{
		ARCHVTRACE_ERROR("m_XMLParser.Init() failed")
		SetSubModuleState(enumSubModuleState_Error);
	}

	return bRet;
}


/**
 ********************************************************************
 * \brief 创建自动发送任务
 *  
 *  
 * \param LPCTSTR szUID : [in] 
 * \param PatientAdminUIDType enumUIDType : [in] 
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
BOOL CTransfer::CreateJobAutoSend(LPCTSTR szUID, PatientAdminUIDType enumUIDType)
{
	PAJob* pJob = new PAJob;
	

	vector<CString> vtrUID;
	vtrUID.push_back(CString(szUID));
	if (!(CDBController::GetInstance())->GetJobImageInfoByUIDs(&vtrUID,
																enumUIDType,
																pJob))
	{
		PRINTTRACE_ERROR("m_pDBController->GetJobImageInfoByUID()")
		delete pJob;
		return FALSE;
	}

	if (0 == pJob->vtrImages.size())
	{
		//<< 自动发送无需此UG提示
// 		NotifyUG(IDS_PRINTINGARCHIVING_NO_IMAGE_INCLUDED_TO_SUBMIT_JOB, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		PRINTTRACE_INFO("0 == pJob->dwTotalImageCount")
		delete pJob;
		return TRUE;
	}
	
	pJob->enumJobType = enumJobType_AutoSendJob;
	pJob->bCancelFlag = FALSE;
	pJob->enumJobState = enumJobState_Submitted;
	pJob->strPhase = _T("");
	pJob->enumJobProgressUsing = enumJobProgressUsing_None;
	pJob->uiCompleted = 0;
	pJob->uiTotal = 0;
	pJob->dwPercentage = 0;
	


	// make job ID
	SYSTEMTIME st;
	::GetLocalTime(&st);
	pJob->strJobID.Format(_T("%04d%02d%02d%02d%02d%02d%03d"), st.wYear, st.wMonth,
		st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	// First detail info
	pJob->vtrDetail.clear();
	JobDetail aJobDetail;
	aJobDetail.stDateTime = st;
	aJobDetail.strDetail = _TT(JOB_DETAIL_SUBMITED); 
	pJob->vtrDetail.push_back(aJobDetail);

	pJob->pData = new TransferJobSettingsStruct;
	if (!GetJobAutoSendServers((TransferJobSettingsStruct*)pJob->pData))
	{
		delete pJob;
		ARCHVTRACE_ERROR("CreateJobAutoSend - > GetJobAutoSendServers is Error")
		return FALSE;
	}

	((TransferJobSettingsStruct*)pJob->pData)->enumUIDType = enumUIDType;


	//<< 加入队列
	if (CJobHandler::GetInstance()->PushJob(pJob))
	{
		return TRUE;
	}
	else
	{
		delete pJob;
		ARCHVTRACE_ERROR("CJobHandler::GetInstance()()->PushJob(pJob)")
		return FALSE;
	}
}


/**
 ********************************************************************
 * \brief 创建手动发送任务
 *  
 *  
 * \param vector<CString>* pvtrUIDs : [in] 
 * \param PatientAdminUIDType enumUIDType : [in] 
 * \param TransferJobSettingsByUID* pTransferJobSetings : [in] 
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
BOOL CTransfer::CreateJobManualSend(vector<CString>* pvtrUIDs, PatientAdminUIDType enumUIDType, vector<NetworkNodeStruct>&	vtrNodes)
{
	if (NULL == pvtrUIDs)
	{
		return FALSE;
	}

	if (0 == pvtrUIDs->size())
	{
		return FALSE;
	}


	if (0 == vtrNodes.size())
	{
		return FALSE;
	}
	else
	{
		int i = 0;
		for (; i < vtrNodes.size(); i++)
		{
			if (vtrNodes[i].bDefault &&
				(vtrNodes[i].bRaw || vtrNodes[i].bProcessed))
			{
				break;
			}
		}

		if (i == vtrNodes.size())
		{
			return FALSE;
		}
	}


	PAJob* pJob = new PAJob;


	if (!(CDBController::GetInstance())->GetJobImageInfoByUIDs(pvtrUIDs,
																enumUIDType,
																pJob))
	{
		PRINTTRACE_ERROR("m_pDBController->GetJobImageInfoByUID()")
		delete pJob;
		return FALSE;
	}

	CString szTemp;
	szTemp.Format(_T("UID Type is %d"), enumUIDType);
	PRINTTRACE_INFO(szTemp)

	if (0 == pJob->vtrImages.size())
	{
		NotifyUG(IDS_PRINTINGARCHIVING_NO_IMAGE_INCLUDED_TO_SUBMIT_JOB, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		PRINTTRACE_INFO("0 == pJob->dwTotalImageCount")
		delete pJob;
		return TRUE;
	}
	
	pJob->enumJobType = enumJobType_ManualSendJob;
	pJob->bCancelFlag = FALSE;
	pJob->enumJobState = enumJobState_Submitted;
	pJob->strPhase = _T("");
	pJob->enumJobProgressUsing = enumJobProgressUsing_None;
	pJob->uiCompleted = 0;
	pJob->uiTotal = 0;
	pJob->dwPercentage = 0;
	
	// make job ID
	SYSTEMTIME st;
	::GetLocalTime(&st);
	pJob->strJobID.Format(_T("%04d%02d%02d%02d%02d%02d%03d"), st.wYear, st.wMonth,
		st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	// First detail info
	pJob->vtrDetail.clear();
	JobDetail aJobDetail;
	aJobDetail.stDateTime = st;
	aJobDetail.strDetail = _TT(JOB_DETAIL_SUBMITED); 
	pJob->vtrDetail.push_back(aJobDetail);


	pJob->pData = new TransferJobSettingsStruct;
	if (!GetJobManualSendServers((TransferJobSettingsStruct*)pJob->pData, vtrNodes))
	{
		delete pJob;
		return FALSE;
	}

	((TransferJobSettingsStruct*)pJob->pData)->enumUIDType = enumUIDType;

	
	//<< 加入队列
	if (CJobHandler::GetInstance()->PushJob(pJob))
	{
		return TRUE;
	}
	else
	{
		delete pJob;
		ARCHVTRACE_ERROR("CJobHandler::GetInstance()()->PushJob(pJob)")
		return FALSE;
	}
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
BOOL CTransfer::UnInit()
{
	BOOL bRet = TRUE;

	// exit the job queue handle thread
	SetSubModuleState(enumSubModuleState_UnInitializing);

	if (m_hTransferEvent)
	{
		CloseHandle(m_hTransferEvent);
		m_hTransferEvent = NULL;
	}

	if (!m_XMLParser.UnInit())
	{
		bRet = FALSE;
		ARCHVTRACE_ERROR("m_XMLPartner.UnInit() failed")
	}
	else
	{
		ARCHVTRACE_INFO("m_XMLPartner.UnInit() succeed")
	}


	SetSubModuleState(enumSubModuleState_UnInited);


	return bRet;
}



/**
 ********************************************************************
 * \brief 获得子模块状态
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
SubModuleState CTransfer::GetSubModuleState()
{
	return m_SubModuleState;
}


/**
 ********************************************************************
 * \brief 链接DcmPartner
 *  
 *  
 * \param CDcmPartner* pDcmPartner : [in] 
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
void CTransfer::AttachDcmPartner(CDcmPartner* pDcmPartner)
{
	m_pDcmPartner = pDcmPartner;
	pDcmPartner->Attach(this);
}


/**
 ********************************************************************
 * \brief 断开DcmPartner对象
 *  
 *  
 * \param CDcmPartner* pDcmPartner : [in] 
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
void CTransfer::DetachDcmPartner(CDcmPartner* pDcmPartner)
{
	pDcmPartner->Detach(this);
}


/**
 ********************************************************************
 * \brief 处理任务
 *  
 *  
 * \param PAJob* pJob : [in] 
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
BOOL CTransfer::HandleJob(PAJob* pJob)
{
	PRINTTRACE_ENTER_FUNCTION

	if (NULL == pJob)
	{
		return FALSE;
	}

	m_pCurrentJob = pJob;

	pJob->SetDetail(JOB_DETAIL_START);

	
	CString strTrace;
	BOOL bAllServerSendComplete = TRUE; // 是否所有服务器都发送完成 [4/6/2010 gaoxing]

	vector<NetworkNodeStruct>& vtrServers = ((TransferJobSettingsStruct*)m_pCurrentJob->pData)->vtrNodes;

	//<< 确定发送进度（总数）
	UINT uCurrentProgress = 0;
	UINT uTotalProgress = 0;
	for (int iServerIndex = 0; iServerIndex < vtrServers.size(); iServerIndex++)
	{
		if (vtrServers[iServerIndex].bRaw)
		{
			uTotalProgress += m_pCurrentJob->vtrImages.size();
		}

		if (vtrServers[iServerIndex].bProcessed)
		{
			uTotalProgress += m_pCurrentJob->vtrImages.size();
		}
	}


	for (iServerIndex = 0; iServerIndex < vtrServers.size(); iServerIndex++)
	{
//<< 1. 连接服务器

		CVDcmNetworkInfoStruct CVDcmnis;
		CVDcmnis.strCalledAE = vtrServers[iServerIndex].strCalledAE;
		CVDcmnis.strCallingAE = vtrServers[iServerIndex].strCallingAE;
		CVDcmnis.strIP = vtrServers[iServerIndex].strIP;
		CVDcmnis.strPort = vtrServers[iServerIndex].strPort;

		pJob->SetDetail(JOB_DETAIL_SEND_CONNECTING_SERVER, CVDcmnis.strCalledAE);

		m_StoreScuOpt.SetDcmNetworkInfoStruct(&CVDcmnis);

		
		// Add [Sun hongwen 10/19/2009]
		BOOL bSendPS = vtrServers[iServerIndex].bSendPS;
		
		if (m_StoreScuOpt.Connect(bSendPS))
		{
			ARCHVTRACE_INFO("m_pDcmPartner.Connect()")

			if (m_pCurrentJob->bCancelFlag)
			{
				// Job be cancelled!
				m_StoreScuOpt.Disconnect();
				pJob->SetDetail(JOB_DETAIL_CANCELLED);
				pJob->SetProgress(enumJobProgressUsing_None);
				pJob->SetPhase(JOB_PHASE_NONE);
				pJob->SetState(enumJobState_Cancelled);
				m_pCurrentJob = NULL;
				PRINTTRACE_INFO("m_pCurrentJob->bCancelFlag")
				return TRUE;
			}
		}
		else
		{
			if (m_pCurrentJob->bCancelFlag)
			{
				// Job be cancelled! 
				pJob->SetDetail(JOB_DETAIL_CANCELLED);
				pJob->SetProgress(enumJobProgressUsing_None);
				pJob->SetPhase(JOB_PHASE_NONE);
				pJob->SetState(enumJobState_Cancelled);
				m_pCurrentJob = NULL;
				PRINTTRACE_INFO("m_pCurrentJob->bCancelFlag")
				return TRUE;
			}
			else
			{
				if ( vtrServers[iServerIndex].bRaw )
				{
					SendImageRawFailed++;
				}
				else if ( vtrServers[iServerIndex].bProcessed )
				{
					SendImageProFailed++;
				}
				else if ( vtrServers[iServerIndex].bSendPS )
				{
					SendImageOLFailed++;
				}
				
				SendPatientFailed++;

				// failed to connect server
				pJob->SetDetail(JOB_DETAIL_SEND_CONNECTING_FAILED, CVDcmnis.strCalledAE);
				pJob->SetDetail(JOB_DETAIL_FAILED);
				pJob->SetProgress(enumJobProgressUsing_None);
				pJob->SetPhase(JOB_PHASE_NONE);
				pJob->SetState(enumJobState_Failed);

				NotifyUG(IDS_PRINTINGARCHIVING_SEND_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
				
				//当有一组服务器连接不成功，就赋值 FALSE[4/6/2010 wangy]
				bAllServerSendComplete = FALSE;
				//m_pCurrentJob = NULL;
				ARCHVTRACE_ERROR("m_pDcmPartner.Connect()")
				//return FALSE;
				continue;
			}
		}

//<< 2. 开始发送

		pJob->SetPhase(JOB_PHASE_TRANSFER);
		pJob->SetDetail(JOB_DETAIL_SEND_SENDING_IMAGES, CVDcmnis.strCalledAE);
		

		pJob->SetProgress(enumJobProgressUsing_CompletedTotal, uCurrentProgress, uTotalProgress);


		for (int i = 0; i < pJob->vtrImages.size(); i++)
		{
			if (m_pCurrentJob->bCancelFlag)
			{
				// Job be cancelled!
				m_StoreScuOpt.Disconnect();
				pJob->SetDetail(JOB_DETAIL_SEND_DISCONN_SERVER, CVDcmnis.strCalledAE);
				pJob->SetDetail(JOB_DETAIL_CANCELLED);
				pJob->SetProgress(enumJobProgressUsing_None);
				pJob->SetPhase(JOB_PHASE_NONE);
				pJob->SetState(enumJobState_Cancelled);
				m_pCurrentJob = NULL;
				PRINTTRACE_INFO("m_pCurrentJob->bCancelFlag")
				return TRUE;
			}

			//<< Raw first
			if (vtrServers[iServerIndex].bRaw)
			{
				CString strISPath = IS_PATH;
				CString strFile = strISPath + pJob->vtrImages[i].bsImageFilePath;

				//<< 图像文件是否存在
				if (!CDirHandler::IsFileExist(strFile))
				{
					strTrace.Format(_T("File does not exist: %s"), strFile);
					ARCHVTRACE_ERROR(strTrace)

					pJob->SetDetail(JOB_DETAIL_ERROR_OCCURRED);
					m_StoreScuOpt.Disconnect();
					pJob->SetDetail(JOB_DETAIL_SEND_DISCONN_SERVER, CVDcmnis.strCalledAE);
					pJob->SetDetail(JOB_DETAIL_FAILED);

					pJob->SetProgress(enumJobProgressUsing_None);
					pJob->SetPhase(JOB_PHASE_NONE);
					pJob->SetState(enumJobState_Failed);

					NotifyUG(IDS_PRINTINGARCHIVING_SEND_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
					m_pCurrentJob = NULL;

					SendImageRawFailed++;

					SendPatientFailed++;

					return FALSE;
				}
				
				//<< 发送该图像
				if (m_StoreScuOpt.StoreFile(strFile))
				{
					++uCurrentProgress;
					pJob->SetProgress(enumJobProgressUsing_CompletedTotal, uCurrentProgress, uTotalProgress);
				}
				else
				{
					SendImageRawFailed++;
					
					SendPatientFailed++;

					pJob->SetDetail(JOB_DETAIL_SEND_SENDING_FAILED, CVDcmnis.strCalledAE);
					m_StoreScuOpt.Disconnect();
					pJob->SetDetail(JOB_DETAIL_SEND_DISCONN_SERVER, CVDcmnis.strCalledAE);
					pJob->SetDetail(JOB_DETAIL_FAILED);

					pJob->SetProgress(enumJobProgressUsing_None);
					pJob->SetPhase(JOB_PHASE_NONE);
					pJob->SetState(enumJobState_Failed);

					NotifyUG(IDS_PRINTINGARCHIVING_SEND_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
					m_pCurrentJob = NULL;
					ARCHVTRACE_ERROR("m_pDcmPartner.StoreFile((*pvtrDICOMImages)[i])")
					return FALSE;
				}
			}

			if (m_pCurrentJob->bCancelFlag)
			{
				// Job be cancelled!
				m_StoreScuOpt.Disconnect();
				pJob->SetDetail(JOB_DETAIL_SEND_DISCONN_SERVER, CVDcmnis.strCalledAE);
				pJob->SetDetail(JOB_DETAIL_CANCELLED);
				pJob->SetProgress(enumJobProgressUsing_None);
				pJob->SetPhase(JOB_PHASE_NONE);
				pJob->SetState(enumJobState_Cancelled);
				m_pCurrentJob = NULL;
				PRINTTRACE_INFO("m_pCurrentJob->bCancelFlag")
				return TRUE;
			}

			//<< Processed Second
			if (vtrServers[iServerIndex].bProcessed)
			{
				CString strISPath = IS_PATH;
				CString strFile = strISPath + pJob->vtrPostProcess[i].bsProcessedImageFilePath;

				//<< 图像文件是否存在
				if (!CDirHandler::IsFileExist(strFile))
				{
					strTrace.Format(_T("File does not exist: %s"), strFile);
					ARCHVTRACE_ERROR(strTrace)

					pJob->SetDetail(JOB_DETAIL_ERROR_OCCURRED);
					m_StoreScuOpt.Disconnect();
					pJob->SetDetail(JOB_DETAIL_SEND_DISCONN_SERVER, CVDcmnis.strCalledAE);
					pJob->SetDetail(JOB_DETAIL_FAILED);

					pJob->SetProgress(enumJobProgressUsing_None);
					pJob->SetPhase(JOB_PHASE_NONE);
					pJob->SetState(enumJobState_Failed);

					NotifyUG(IDS_PRINTINGARCHIVING_SEND_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
					m_pCurrentJob = NULL;

					SendImageProFailed++;

					SendPatientFailed++;

					return FALSE;
				}

				//<< 发送该图像
				if (m_StoreScuOpt.StoreFile(strFile))
				{
					++uCurrentProgress;
					pJob->SetProgress(enumJobProgressUsing_CompletedTotal, uCurrentProgress, uTotalProgress);
					
					// Send PS file [Sun hongwen 10/16/2009]
					if(vtrServers[iServerIndex].bSendPS)
					{
						int nLen = strFile.GetLength();
						CString szVal = strFile.Left(nLen - 3);
						CString szPSPath = szVal + "pre";
						if (CDirHandler::IsFileExist(szPSPath))
						{
							//CString sz = _T("c:\\temp.pre");
							//m_pDcmPartner->RemovePresentationLUTSequence(szPSPath,sz,pJob->vtrPostProcess[i].bInverse);
							m_StoreScuOpt.StoreFile(szPSPath);

						}
					}
					//
				}
				else
				{
					SendImageProFailed++;

					SendPatientFailed++;

					pJob->SetDetail(JOB_DETAIL_SEND_SENDING_FAILED, CVDcmnis.strCalledAE);
					m_StoreScuOpt.Disconnect();
					pJob->SetDetail(JOB_DETAIL_SEND_DISCONN_SERVER, CVDcmnis.strCalledAE);
					pJob->SetDetail(JOB_DETAIL_FAILED);

					pJob->SetProgress(enumJobProgressUsing_None);
					pJob->SetPhase(JOB_PHASE_NONE);
					pJob->SetState(enumJobState_Failed);

					NotifyUG(IDS_PRINTINGARCHIVING_SEND_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
					m_pCurrentJob = NULL;
					ARCHVTRACE_ERROR("m_pDcmPartner.StoreFile(vtrProcDICOMImages[i])")
					return FALSE;
				}
			}
		}


//<< 4. 往该服务器发送完毕，断开连接
		pJob->SetDetail(JOB_DETAIL_SEND_SENDING_COMPLETED, CVDcmnis.strCalledAE);
		m_StoreScuOpt.Disconnect();
		pJob->SetDetail(JOB_DETAIL_SEND_DISCONN_SERVER, CVDcmnis.strCalledAE);

		if ( vtrServers[iServerIndex].bRaw )
		{
			SendImageRawOK++;
		}
		else if ( vtrServers[iServerIndex].bProcessed )
		{
			SendImageProOK++;
		}
		else if ( vtrServers[iServerIndex].bSendPS )
		{
			SendImageOLOK++;
		}

		SendPatientOK++;
	}
	
	if (bAllServerSendComplete)
	{
		//必须通知UI修改数据库  [12/8/2009]
		NotifyUIModifyDB(pJob);
		pJob->SetDetail(JOB_DETAIL_COMPLETED);
		pJob->SetProgress(enumJobProgressUsing_None);
		pJob->SetPhase(JOB_PHASE_NONE);
		pJob->SetState(enumJobState_Completed);	
	}
	else
	{
		pJob->SetProgress(enumJobProgressUsing_None);
		pJob->SetPhase(JOB_PHASE_NONE);
		pJob->SetState(enumJobState_Failed);	
	}

	m_pCurrentJob = NULL;

	return TRUE;

}


/**
 ********************************************************************
 * \brief 暂停发送
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
void CTransfer::PauseTransfer()
{
	ResetEvent(m_hTransferEvent);
}


/**
 ********************************************************************
 * \brief 恢复发送
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
void CTransfer::ResumeTransfer()
{
	SetEvent(m_hTransferEvent);
}



/**
 ********************************************************************
 * \brief 获得自动发送服务器
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
BOOL CTransfer::GetAutoServers(NetworkNode** ppServers, long* pLen)
{
	vector<NetworkNodeStruct> vtrServers;
	if (E_OK != m_XMLParser.GetAutoServers(&vtrServers))
	{
		*pLen = 0;
		PRINTTRACE_ERROR("CTransfer::m_XMLParser.GetAutoServers error")
		return FALSE;
	}

	*ppServers = NULL;
	*pLen = vtrServers.size();

	if (0 == *pLen)
	{
		return TRUE;
	}

	ULONG cb = sizeof(**ppServers) * (*pLen);
	*ppServers = (NetworkNode*)CoTaskMemAlloc(cb);
	NetworkNode* pNode = *ppServers;

	for (int i = 0; i < vtrServers.size(); i++)
	{
		pNode->bsCalledAE = vtrServers[i].strCalledAE.AllocSysString();
		pNode->bsIP = vtrServers[i].strIP.AllocSysString();
		pNode->bsPort = vtrServers[i].strPort.AllocSysString();
		pNode->bsCallingAE = vtrServers[i].strCallingAE.AllocSysString();
		pNode->bDefault = vtrServers[i].bDefault;
		pNode->bRaw = vtrServers[i].bRaw;
		pNode->bProcessed = vtrServers[i].bProcessed;

		// Add [Sun hongwen 10/16/2009]
		pNode->bSendPS = vtrServers[i].bSendPS;
		//

		pNode++;
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief 是否自动发送有效
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
BOOL CTransfer::IsAutoSendValid(BOOL* pbValid)
{
	*pbValid = FALSE;
	vector<NetworkNodeStruct> vtrServers;
	if (E_OK != m_XMLParser.GetAutoServers(&vtrServers))
	{
		return FALSE;
	}

	for (int i = 0; i < vtrServers.size(); i++)
	{
		if (vtrServers[i].bDefault && (vtrServers[i].bRaw || vtrServers[i].bProcessed))
		{
			*pbValid = TRUE;
			break;
		}
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief 设置自动发送服务器
 *  
 *  
 * \param NetworkNode* pServer : [in] 
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
BOOL CTransfer::SetAutoServers(NetworkNode* pServer, long lLen)
{
	vector<NetworkNodeStruct> vtrServers;

	for (int i = 0; i < lLen; i++)
	{
		NetworkNode* pNode = pServer + i;
		NetworkNodeStruct nns;
		nns.strCalledAE = CBSTROpt::BSTRToCString(pNode->bsCalledAE);
		nns.strIP = CBSTROpt::BSTRToCString(pNode->bsIP);
		nns.strPort = CBSTROpt::BSTRToCString(pNode->bsPort);
		nns.strCallingAE = CBSTROpt::BSTRToCString(pNode->bsCallingAE);
		nns.bDefault = pNode->bDefault;
		nns.bRaw = pNode->bRaw;
		nns.bProcessed = pNode->bProcessed;

		// Add [Sun hongwen 10/16/2009]
		nns.bSendPS = pNode->bSendPS;
		//

		vtrServers.push_back(nns);
	}

	if (E_OK != m_XMLParser.SetAutoServers(&vtrServers))
	{
		return FALSE;
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief 获得手动发送服务器
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
BOOL CTransfer::GetManualServers(NetworkNode** ppServers, long* pLen)
{
	vector<NetworkNodeStruct> vtrServers;
	if (E_OK != m_XMLParser.GetManualServers(&vtrServers))
	{
		*pLen = 0;
		return FALSE;
	}

	*ppServers = NULL;
	*pLen = vtrServers.size();

	if (0 == *pLen)
	{
		return TRUE;
	}

	ULONG cb = sizeof(**ppServers) * (*pLen);
	*ppServers = (NetworkNode*)CoTaskMemAlloc(cb);
	NetworkNode* pNode = *ppServers;

	for (int i = 0; i < vtrServers.size(); i++)
	{
		pNode->bsCalledAE = vtrServers[i].strCalledAE.AllocSysString();
		pNode->bsIP = vtrServers[i].strIP.AllocSysString();
		pNode->bsPort = vtrServers[i].strPort.AllocSysString();
		pNode->bsCallingAE = vtrServers[i].strCallingAE.AllocSysString();
		pNode->bDefault = vtrServers[i].bDefault;
		pNode->bRaw = vtrServers[i].bRaw;
		pNode->bProcessed = vtrServers[i].bProcessed;

		// Add [Sun hongwen 10/16/2009]
		pNode->bSendPS = vtrServers[i].bSendPS;
		//

		pNode++;
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief 设置手动发送服务器
 *  
 *  
 * \param NetworkNode* pServer : [in] 
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
BOOL CTransfer::SetManualServers(NetworkNode* pServer, long lLen)
{
	vector<NetworkNodeStruct> vtrServers;

	for (int i = 0; i < lLen; i++)
	{
		NetworkNode* pNode = pServer + i;
		NetworkNodeStruct nns;
		nns.strCalledAE = CBSTROpt::BSTRToCString(pNode->bsCalledAE);
		nns.strIP = CBSTROpt::BSTRToCString(pNode->bsIP);
		nns.strPort = CBSTROpt::BSTRToCString(pNode->bsPort);
		nns.strCallingAE = CBSTROpt::BSTRToCString(pNode->bsCallingAE);
		nns.bDefault = pNode->bDefault;
		nns.bRaw = pNode->bRaw;
		nns.bProcessed = pNode->bProcessed;

		// Add [Sun hongwen 10/16/2009]
		nns.bSendPS = pNode->bSendPS;
		//

		vtrServers.push_back(nns);
	}

	if (E_OK != m_XMLParser.SetManualServers(&vtrServers))
	{
		return FALSE;
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief 连接发送服务器测试
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
BOOL CTransfer::ConnectTest(NetworkNode* pServer, BOOL* pbResult)
{
	CVDcmNetworkInfoStruct CVDcmnis;
	CVDcmnis.strCalledAE = CBSTROpt::BSTRToCString(pServer->bsCalledAE);
	CVDcmnis.strCallingAE = CBSTROpt::BSTRToCString(pServer->bsCallingAE);
	CVDcmnis.strIP = CBSTROpt::BSTRToCString(pServer->bsIP);
	CVDcmnis.strPort = CBSTROpt::BSTRToCString(pServer->bsPort);

	m_StoreScuOpt.SetDcmNetworkInfoStruct(&CVDcmnis);

	if (m_StoreScuOpt.Connect())
	{
		m_StoreScuOpt.Disconnect();
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
 * \brief 转发UserGuidance
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
void CTransfer::NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive)
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
 * \brief 处理NSubject返回的消息
 *  
 *  
 * \param NSubject* pSubject : [in] 
 * \param UINT uMessage : [in] 
 * \param LPARAM lParam : [in] 
 * \param WPARAM wParam : [in] 
 * 
 * \return LONG  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
LONG CTransfer::HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam)
{
	if (NOTIFY_TRANSFER == uMessage)
	{
		if (NOTIFY_HARDDISK_FREE_SPACE_NOT_ENOUGH == lParam)
		{
// 			SetCurrentJobDetailByUGID(IDS_PRINTINGARCHIVING_HARDDISK_FREESPACE_NOTENOUGH);
// 			NotifyUG(IDS_PRINTINGARCHIVING_HARDDISK_FREESPACE_NOTENOUGH, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		}
	}
	else if ((NOTIFY_PRINT == uMessage) ||
			(NOTIFY_BURN == uMessage))
	{
		// Do nothing
	}
	else
	{
		Notify(uMessage, lParam, wParam);
	}
	
	return E_OK;
}


/**
 ********************************************************************
 * \brief 设置子模块状态
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
void CTransfer::SetSubModuleState(SubModuleState enumSubModuleState)
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
	Notify(NOTIFY_SUBMODULE_STATE_CHANGED, enumSubModule_TRANSFER, m_SubModuleState);

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
 * \brief 设置当前任务进度
 *  
 *  
 * \param JobProgressUsing enumJobProgressUsing : [in] 
 * \param UINT uiFirstParam : [in] 
 * \param UINT uiSecondParam : [in] 
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
void CTransfer::SetCurrentJobProgress(JobProgressUsing enumJobProgressUsing, UINT uiFirstParam, UINT uiSecondParam)
{
	if (NULL != m_pCurrentJob)
	{
		m_pCurrentJob->SetProgress(enumJobProgressUsing, uiFirstParam, uiSecondParam);
	}
}


/**
 ********************************************************************
 * \brief 设置当前任务详细信息
 *  
 *  
 * \param LONG iUGID : [in] 
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
void CTransfer::SetCurrentJobDetailByUGID(LONG iUGID)
{
	if (NULL != m_pCurrentJob)
	{
		m_pCurrentJob->SetDetailByUGID(iUGID);
	}
}


/**
 ********************************************************************
 * \brief 获得自动发送服务器
 *  
 *  
 * \param TransferJobSettingsStruct* ptjss : [in] 
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
BOOL CTransfer::GetJobAutoSendServers(TransferJobSettingsStruct* ptjss)
{
	INT iErrCode = S_OK;
	vector<NetworkNodeStruct> vtrServers;
	iErrCode = m_XMLParser.GetDefaultAutoServers(&vtrServers);
	if (S_OK != iErrCode)
	{
		return FALSE;
	}

	if (vtrServers.size() == 0)
	{
		return FALSE;
	}

	for (int i = 0; i < vtrServers.size(); i++)
	{
		if (vtrServers[i].bRaw || vtrServers[i].bProcessed)
		{
			ptjss->vtrNodes.push_back(vtrServers[i]);
		}
	}

	if (ptjss->vtrNodes.size() == 0)
	{
		return FALSE;
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief 获得手动发送服务器
 *  
 *  
 * \param TransferJobSettingsStruct* ptjss : [in] 
 * \param LPCTSTR szCalledAE : [in] 
 * \param BOOL bRaw : [in] 
 * \param BOOL bProcessed : [in] 
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
BOOL CTransfer::GetJobManualSendServers(TransferJobSettingsStruct* ptjss, vector<NetworkNodeStruct>& vtrNodes)
{
	INT iErrCode = S_OK;

	//<< 获得Server信息
	for (int i = 0; i < vtrNodes.size(); i++)
	{
		NetworkNodeStruct nns;
		iErrCode = m_XMLParser.GetManualServer(vtrNodes[i].strCalledAE, &nns);
		if (E_OK != iErrCode)
		{
			return FALSE;
		}

		nns.bDefault = vtrNodes[i].bDefault;
		nns.bRaw = vtrNodes[i].bRaw;
		nns.bProcessed = vtrNodes[i].bProcessed;

		// Add [Sun hongwen 10/16/2009]
		nns.bSendPS = vtrNodes[i].bSendPS;
		//

		//<< 若该server选择有效，则加入任务
		if (vtrNodes[i].bDefault &&
			(vtrNodes[i].bRaw || vtrNodes[i].bProcessed))
		{
			ptjss->vtrNodes.push_back(nns);
		}

		//<< 设置该server在配置文件中的状态等
		iErrCode = m_XMLParser.SetManualServerState(&nns);
		if (E_OK != iErrCode)
		{
			PRINTTRACE_ERROR("m_XMLParser.SetDefaultManualServer(&nns)")
			//<< 只是写配置文件失败，无需返回失败
		}

	}
	return TRUE;
}


//设置自动发送状态使能 
BOOL CTransfer::SetEnableAutoTransferStatus(BOOL bEnable)
{
	if (E_OK != m_XMLParser.SetEnableAutoTransferStatus(bEnable))
	{
		return FALSE;
	}

	return TRUE;
}

//获取是否自动发送状态使能
BOOL CTransfer::GetEnableAutoTransferStatus(BOOL *bEnalbe)
{
	if (E_OK != m_XMLParser.GetEnableAutoTransferStatus(bEnalbe))
	{
		return FALSE;
	}

	return TRUE;
}


//设置是否询问用户自动发送状态 
BOOL CTransfer::SetAskforAutoTransfer(BOOL bAskfor)
{
	if (E_OK != m_XMLParser.SetAskforAutoTransfer(bAskfor))
	{
		return FALSE;
	}

	return TRUE;
}

//获取是否询问用户自动发送状态
BOOL CTransfer::GetAskforAutoTransfer(BOOL *bAskfor)
{
	if (E_OK != m_XMLParser.GetAskforAutoTransfer(bAskfor))
	{
		return FALSE;
	}

	return TRUE;
}


//根据pJob,通知UI修改数据库
BOOL CTransfer::NotifyUIModifyDB(PAJob *pJob)
{
	if (pJob == NULL)
	{
		PRINTTRACE_ERROR("In NotifyUIModifyDB pJob is null")
		return FALSE;
	}
	
	CString szStudyUID = _T("") ;
	CString szPatientUID = _T("");
	PRINTTRACE_INFO("Before Patient For")	
	int nSize = pJob->vtrPatient.size();
	CString szTemp;
	szTemp.Format(_T("Patient Size:%d"), nSize);
	PRINTTRACE_INFO(szTemp);
	for(int i = 0; i < pJob->vtrPatient.size(); i++)
	{
		szPatientUID += CBSTROpt::BSTRToCString(pJob->vtrPatient[i].bsPatientUID);
		szPatientUID += _T("|"); 
	}

	for(int j = 0; j < pJob->vtrStudy.size(); j++)
	{
		szStudyUID += CBSTROpt::BSTRToCString(pJob->vtrStudy[j].bsStudyUID);
		szStudyUID += _T("|");
	}


	if(NULL != m_bstrPatientUID)
	{
		SysFreeString(m_bstrPatientUID);
	}
	if(NULL != m_bstrStudyUID)
	{
		SysFreeString(m_bstrStudyUID);
	}

	m_bstrPatientUID = szPatientUID.AllocSysString();
	m_bstrStudyUID = szStudyUID.AllocSysString();
	
	PRINTTRACE_INFO(m_bstrPatientUID)
	PRINTTRACE_INFO(m_bstrStudyUID)
	Notify(NOTIFY_UI_DB_CHANGED, (LPARAM)m_bstrPatientUID, (WPARAM)m_bstrStudyUID);

	return TRUE;
}
