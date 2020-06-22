/* Time: <@(#)Printing.cpp   2009-3-5 - 10:33:27   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : Printing.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Capsulation class of printing function
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:33:27		FanZF	Creation
 *
 *********************************************************************
 */

// Printing.cpp: implementation of the CPrinting class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Printing.h"
#include "DirHandler.h"
#include "PALibExt_i.c"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CPrinting* CPrinting::m_pInstance = NULL;



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
CPrinting::CPrinting()
{
	m_DcmPartner.Attach(this);


	m_FCPartner.Attach(this);

	m_SubModuleState = enumSubModuleState_UnInited;
	m_PrintWorkingState = PWS_UNWORKING;
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
CPrinting::~CPrinting()
{

	m_DcmPartner.Detach(this);

	m_FCPartner.Detach(this);

}


/**
 ********************************************************************
 * \brief 获得CPrinting实例
 *  
 *  
 * 
 * \return CPrinting*  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CPrinting* CPrinting::GetInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new CPrinting;
	}

	return m_pInstance;
}


/**
 ********************************************************************
 * \brief 释放CPrinting实例
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
void CPrinting::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


/**
 ********************************************************************
 * \brief 初始化
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
BOOL CPrinting::Init()
{
	if (m_DcmPartner.Init())
	{
		PRINTTRACE_INFO("m_DcmPartner.Init() succeed")
	}
	else
	{
		PRINTTRACE_ERROR("m_DcmPartner.Init() failed")
		SetSubModuleState(enumSubModuleState_Error);
		return FALSE;
	}

	if (m_FCPartner.Init())
	{
		PRINTTRACE_INFO("m_FCPartner.Init() succeed")
	}
	else
	{
		PRINTTRACE_ERROR("m_FCPartner.Init() failed")
		SetSubModuleState(enumSubModuleState_Error);
		return FALSE;
	}

	SetSubModuleState(enumSubModuleState_Ready);
	return TRUE;
}


/**
 ********************************************************************
 * \brief 创建任务
 *  
 *  
 * \param PrintJobSettings* pPrintJobSettings : [in] 
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
BOOL CPrinting::CreateJob(PrintJobSettings* pPrintJobSettings)
{
	PAJob Job;
	Job.enumJobType = enumJobType_PrintJob;
	Job.bCancelFlag = FALSE;

// 	if (!(CDBController::GetInstance())->GetJobImageInfoInCurrentStudyBFS(pPrintJobSettings->enumFileSelection,
// 														pPrintJobSettings->enumImageSelection,
// 														&Job,
// 														TRUE))
// 	{
// 		PRINTTRACE_ERROR("(CDBController::GetInstance())->GetJobImageInfoInCurrentStudyBFS")
// 		CBSTROpt::FreePAJob(&Job);
// 		return FALSE;
// 	}

	if (0 == Job.vtrImages.size())
	{
		NotifyUG(IDS_PRINTINGARCHIVING_NO_IMAGE_INCLUDED_TO_SUBMIT_JOB, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		PRINTTRACE_INFO("0 == pJob->dwTotalImageCount")
		CBSTROpt::FreePAJob(&Job);
		return TRUE;
	}
	
// 	if (PRINT_JOB_IMAGES_COUNT_LIMITATION < Job.vtrImages.size())
// 	{
// 		NotifyUG(IDS_PRINTINGARCHIVING_P_TOO_MANY_IMAGES, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
// 		PRINTTRACE_INFO("PRINT_JOB_IMAGES_COUNT_LIMITATION < pJob->dwTotalImageCount")
// 		CBSTROpt::FreePAJob(&Job);
// 		return TRUE;
// 	}

	// Phase Image conversion


	//<< 清空打印临时文件夹
	if (!CDirHandler::CheckDir(DICOM_IMAGE_PRINT_STORE_PATH, TRUE))
	{
		PRINTTRACE_ERROR("CDirHandler::CheckDir()")
		CBSTROpt::FreePAJob(&Job);
		return FALSE;
	}

	m_DcmPartner.SetImageType(FALSE, FALSE);
	m_DcmPartner.SetPSFile(TRUE);
	m_DcmPartner.SetDcmDir(FALSE);

	vector<CString> vtrProcDICOMImages;
	if (m_DcmPartner.ConvertBFS(&Job,
 								DICOM_IMAGE_PRINT_STORE_PATH,
								NULL,
								&vtrProcDICOMImages))
	{
		PRINTTRACE_INFO("m_DcmPartner.ConvertBFS()")
	}
	else
	{
		PRINTTRACE_ERROR("m_DcmPartner.ConvertBFS()")
		CBSTROpt::FreePAJob(&Job);
		return FALSE;
	}
	
	CBSTROpt::FreePAJob(&Job);


	// FC Load Image
	BOOL bCancelFlag = FALSE;
	if (!m_FCPartner.LoadImages(&vtrProcDICOMImages, &bCancelFlag))
	{
		PRINTTRACE_ERROR("m_FCPartner.LoadImages(vtrProcDICOMImages)")
		return FALSE;
	}


	return TRUE;
}


/**
 ********************************************************************
 * \brief CPrinting实例
 *  
 *  
 * \param vector<CString>* pvtrUID : [in] 
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
BOOL CPrinting::LoadToFC(vector<CString>* pvtrUID)
{
	if (NULL == pvtrUID)
	{
		return FALSE;
	}

	if (0 == pvtrUID->size())
	{
		return FALSE;
	}

	CString strTrace;

	for (int i = 0; i < pvtrUID->size(); i++)
	{
		PostProcessingInfo aPostInfo;
		if (CDBController::GetInstance()->GetPostProcessInfo((*pvtrUID)[i], &aPostInfo))
		{
			CString strPostImage = IS_PATH;
			strPostImage += CBSTROpt::BSTRToCString(aPostInfo.bsProcessedImageFilePath);
			CBSTROpt::FreePostProcessingInfo(&aPostInfo);


			//GaoXing 每次发送给FC前，复制一个带时间挫的副本dic [10/13/2009]
			SYSTEMTIME sysTime;
			GetSystemTime(&sysTime);
			CString strSystemTime = _T("");
			strSystemTime.Format(_T("%d%d%d%d%d%d%d"),sysTime.wYear,sysTime.wMonth,sysTime.wDay,sysTime.wHour,sysTime.wMinute,sysTime.wSecond,sysTime.wMilliseconds);
			
			int nDotPos = strPostImage.ReverseFind(TCHAR('.'));
			CString szExtName = strPostImage.Right(strPostImage.GetLength()-nDotPos);
			
			CString strPostImage_new = strPostImage.Left(nDotPos);

			//获取原始的PS文件
			CString strPostImagePS = strPostImage_new + _T(".pre");
			//新PS文件的名称
			CString strPostImagePS_new = strPostImage_new + strSystemTime + _T(".pre");
			
			//新dcm文件，不保存后缀名，此时FC可以同时删除dcm和pre文件
			strPostImage_new = strPostImage_new + strSystemTime;
			

			//拷贝一个dcm文件 2009-10-29
			if (!CopyFile(strPostImage,strPostImage_new,FALSE))
			{
				strTrace.Format(_T("m_FCPartner.CopyFile %s Failed"), strPostImage);
				PRINTTRACE_ERROR(strTrace)
				return FALSE;
			}

			//新需求，判断pre文件是否存在，如果不存在，则不需要进行拷贝工作  [ GaoXing 5/5/2010]
			
			CFileFind fFind;
			BOOL bFind = fFind.FindFile(strPostImagePS);

			if (bFind) //找到Pre文件，则进行下面的操作  [ GaoXing 5/5/2010]
			{
				// 拷贝一个pre文件 2009-10-29
				if (!CopyFile(strPostImagePS,strPostImagePS_new,FALSE))
				{
					strTrace.Format(_T("m_FCPartner.CopyFile %s Failed"), strPostImagePS);
					PRINTTRACE_ERROR(strTrace)
					fFind.Close(); //关闭查找文件
					return FALSE;
				}
			}
			else // 没找到pre文件，写Trace [ GaoXing 5/5/2010]
			{
				strTrace.Format(_T("Not Find PS file %s "), strPostImagePS);
				PRINTTRACE_INFO(strTrace)
				fFind.Close(); //关闭查找文件
			}

			//<< Load to FC
			if (!m_FCPartner.LoadImage(strPostImage_new))
			{
				strTrace.Format(_T("m_FCPartner.LoadImage(strPostImage_new), %s"), strPostImage_new);
				PRINTTRACE_ERROR(strTrace)

				return FALSE;
			}
		}
		else
		{
			strTrace.Format(_T("CDBController::GetInstance()->GetPostProcessInfo(), ImageUID:%s"), (*pvtrUID)[i]);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief 将图像加载到FC
 *  
 *  
 * \param BOOL bShow : [in] 
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
BOOL CPrinting::ShowFCProgressBar(BOOL bShow)
{
// 	if (m_FCPartner.ShowProgressBar(bShow))
// 	{
// 		return TRUE;
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("m_FCPartner.ShowProgressBar(bShow)")
// 		return FALSE;
// 	}

	return TRUE;
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
LONG CPrinting::HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam)
{
	if (NOTIFY_FC_LOAD_IMAGE_PROGRESS == uMessage)
	{
	}
	else if (NOTIFY_PRINT == uMessage)
	{
		if (NOTIFY_HARDDISK_FREE_SPACE_NOT_ENOUGH == lParam)
		{
// 			NotifyUG(IDS_PRINTINGARCHIVING_HARDDISK_FREESPACE_NOTENOUGH, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
		}
	}
	else if ((NOTIFY_TRANSFER == uMessage) ||
			(NOTIFY_BURN == uMessage))
	{
		// Do nothing
	}
	else if (NOTIFY_FC_STATE_CHANGED == uMessage)
	{
		if (enumFilmComposerPRINTING == (FilmComposerStatus)lParam)
		{
			SetPrintWorkingState(enumPrintWorkingState_FCWorking);
		}
		else if (enumFilmComposerIdle == (FilmComposerStatus)lParam)
		{
			SetPrintWorkingState(enumPrintWorkingState_FCUnWorking);
		}

		Notify(uMessage, lParam, wParam);
	}
	else if (NOTIFY_FC_LOAD_IMAGE_LIMITED == uMessage)
	{
		// UserGuidance since Images in FC reach the Limitation
// 		NotifyUG(IDS_PRINTINGARCHIVING_FC_IMAGES_LIMITED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
	}
	else if (NOTIFY_FC_INVALID_PRINTER == uMessage)
	{
		// UserGuidance since No valid printer
// 		NotifyUG(IDS_PRINTINGARCHIVING_INVALID_PRINTER, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
	}
	else
	{
		Notify(uMessage, lParam, wParam);
	}
	
	return E_OK;
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
BOOL CPrinting::UnInit()
{
	PRINTTRACE_ENTER_FUNCTION
	
	BOOL bRet = TRUE;
	
	SetSubModuleState(enumSubModuleState_UnInitializing);


	// Cancel FC printing
	if (!CancelFCPrinting())
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("CancelFCPrinting()")
	}

	m_PrintWorkingState = PWS_UNWORKING;
		
	if (!m_FCPartner.UnInit())
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("m_FCPartner.UnInit() failed")
	}
	else
	{
		PRINTTRACE_INFO("m_FCPartner.UnInit() succeed")
	}		

	m_DcmPartner.UnInit();

	SetSubModuleState(enumSubModuleState_UnInited);

	
	return bRet;

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
void CPrinting::SetSubModuleState(SubModuleState enumSubModuleState)
{
	CSingleLock sLock(&m_CSLockSubModuState);
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
	Notify(NOTIFY_SUBMODULE_STATE_CHANGED, enumSubModule_PRINT, m_SubModuleState);

	CString strTrace;
	strTrace = _T("Print SubModule state: ");
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
	PRINTTRACE_INFO(strTrace);

	sLock.Unlock();
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
SubModuleState CPrinting::GetSubModuleState()
{
	return m_SubModuleState;
}


/**
 ********************************************************************
 * \brief 取消FC打印
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
BOOL CPrinting::CancelFCPrinting()
{
	if (m_FCPartner.IsFCPrinting())
	{
		if (m_FCPartner.CancelPrinting())
		{
			PRINTTRACE_INFO("m_FCPartner.CancelPrinting()")
			return TRUE;
		}
		else
		{
			PRINTTRACE_ERROR("m_FCPartner.CancelPrinting()")
			return FALSE;
		}
	}
	else
	{
		return TRUE;
	}
}


/**
 ********************************************************************
 * \brief 获得打印服务器列表
 *  
 *  
 * \param NetworkNode** ppNodesList : [in] 
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
BOOL CPrinting::GetNetworkNodes(NetworkNode** ppNodesList, long* pLen)
{
	return TRUE;
}

/**
 ********************************************************************
 * \brief 采集前处理打印
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
BOOL CPrinting::HandlePrintBeforeAcq()
{
	m_FCPartner.DisableLoadImage();

	if (CancelFCPrinting())
	{
		PRINTTRACE_INFO("CancelFCPrinting()")
		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR("CancelFCPrinting()")
		return FALSE;
	}
}


/**
 ********************************************************************
 * \brief 采集后处理打印
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
void CPrinting::HandlePrintAfterAcq()
{
	m_FCPartner.EnableLoadImage();
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
void CPrinting::NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive)
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
 * \brief 设置打印工作状态
 *  
 *  
 * \param PrintWorkingState enumWorkingState : [in] 
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
void CPrinting::SetPrintWorkingState(PrintWorkingState enumWorkingState)
{
	CSingleLock sLock(&m_CSLockPrintWorkingState);
	sLock.Lock();

	switch (enumWorkingState)
	{
	case enumPrintWorkingState_UnWorking:
		m_PrintWorkingState = PWS_UNWORKING;
		break;
	case enumPrintWorkingState_JobWorking:
		m_PrintWorkingState |= PWS_JOBWORKING;
		break;
	case enumPrintWorkingState_FCWorking:
		m_PrintWorkingState |= PWS_FCWORKING;
		break;
	case enumPrintWorkingState_JobUnWorking:
		m_PrintWorkingState &= PWS_JOBUNWORKING;
		break;
	case enumPrintWorkingState_FCUnWorking:
		m_PrintWorkingState &= PWS_FCUNWORKING;
		break;
	default :
		PRINTTRACE_ERROR("Unknow PrintWorkingState")
		break;
	}

	if ((m_PrintWorkingState & 0x01) ||
		(m_PrintWorkingState & 0x02))
	{
		SetSubModuleState(enumSubModuleState_Work);
	}
	else
	{
		SetSubModuleState(enumSubModuleState_Ready);
	}

	sLock.Unlock();
	return;
	
}
