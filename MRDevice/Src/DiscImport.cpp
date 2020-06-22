/* Time: <@(#)DiscImport.cpp   2009-3-5 - 10:33:01   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : DiscImport.cpp
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : Capsulation class of import function
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:33:01		FanZF	Creation
 *
 *********************************************************************
 */

// DiscImport.cpp: implementation of the CDiscImport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiscImport.h"
#include "IDPathGen.h"
#include "UserGuidanceOpt.h"
#include "JobHandler.h"
#include "DBStructInitor.h"



/**
 ********************************************************************
 * \brief ��õ��������Ϣ�����߳�
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
DWORD WINAPI GetImportDiscInfoThreadProc(LPVOID lpParam) 
{ 
//	PRINTTRACE_ENTER_FUNCTION

	try
	{
		if (CDiscImport::GetInstance()->GetImportDiscInfoProc((GetImportDiscInfoStruct*)lpParam))
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

CDiscImport* CDiscImport::m_pInstance = NULL;



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
CDiscImport::CDiscImport()
{
	m_SubModuleState = enumSubModuleState_UnInited;

	m_pCurrentJob = NULL;
	
	// for get imported disc info
	m_vtrGetDiscInfo.clear();

	// for Import a series
	m_hFindFileDcm = INVALID_HANDLE_VALUE;
	m_pDcmParser = NULL;;
	
	CDBStructInitor::InitPatientInfoStruct(&m_PatientInfo);
	CDBStructInitor::InitStudyInfoStruct(&m_StudyInfo);
	CDBStructInitor::InitSeriesInfoStruct(&m_SeriesInfo);
	CDBStructInitor::InitImageInfoStruct(&m_ImageInfo);
	CDBStructInitor::InitPostProcessInfoStruct(&m_PostProcessInfo);

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
CDiscImport::~CDiscImport()
{

}


/**
 ********************************************************************
 * \brief ���CDiscImportʵ��
 *  
 *  
 * 
 * \return CDiscImport*  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-6	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
CDiscImport* CDiscImport::GetInstance()
{
	if(!m_pInstance)
		m_pInstance = new CDiscImport;
	return m_pInstance;
}


/**
 ********************************************************************
 * \brief �ͷ�CDiscImportʵ��
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
void CDiscImport::ReleaseInstance()
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
BOOL CDiscImport::Init()
{
	ARCHVTRACE_ENTER_FUNCTION

	DWORD dwRet = GetLogicalDriveStrings(0, NULL);
	if (0 == dwRet)
	{
		SetSubModuleState(enumSubModuleState_Error);
		return FALSE;
	}

	wchar_t* pDriversBuffer = new wchar_t[dwRet];
	dwRet = GetLogicalDriveStrings(dwRet, pDriversBuffer);
	if (0 == dwRet)
	{
		delete []pDriversBuffer;
		SetSubModuleState(enumSubModuleState_Error);
		return FALSE;
	}

	wchar_t* pDriver = pDriversBuffer;

	m_vtrGetDiscInfo.clear();

	while (_T('\0') != *pDriver)
	{
		if (DRIVE_CDROM == GetDriveType(pDriver))
		{
			//<< ���һ���ṹ
			GetImportDiscInfoStruct dis;
			dis.strDevice = pDriver;
			dis.hThread = NULL;
			dis.hFindDcmDir = INVALID_HANDLE_VALUE;
			dis.pDcmDirParser = NULL;
			dis.bValid = FALSE;

			m_vtrGetDiscInfo.push_back(dis);
		}

		pDriver = wcschr(pDriver, _T('\0'));
		pDriver++;
	}
	
	delete []pDriversBuffer;


	SetSubModuleState(enumSubModuleState_Ready);

	return TRUE;
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
BOOL CDiscImport::UnInit()
{
	SetSubModuleState(enumSubModuleState_UnInitializing);

	BOOL bRet = TRUE;

	if (!CancelGetImportDiscInfo())
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("CancelGetImportDiscInfo")
	}

	// �ȴ����е��豸�߳�
	HANDLE* phThread = new HANDLE[m_vtrGetDiscInfo.size()];
	int i = 0;
	for (; i < m_vtrGetDiscInfo.size(); i++)
	{
		phThread[i] = m_vtrGetDiscInfo[i].hThread;
	}

	WaitForMultipleObjects(m_vtrGetDiscInfo.size(), phThread, TRUE, SHUTDOWN_SUBMODULE_DISCIMPORT_CANCEL_GETDISCINFO_WAIT_TIME);
	delete []phThread;
	phThread = NULL;
	
	for (i = 0; i < m_vtrGetDiscInfo.size(); i++)
	{
		if (NULL != m_vtrGetDiscInfo[i].hThread)
		{
			if (WAIT_TIMEOUT == WaitForSingleObject(m_vtrGetDiscInfo[i].hThread, 0))
			{
				if (!TerminateThread(m_vtrGetDiscInfo[i].hThread, 0))
				{
					bRet = FALSE;
					PRINTTRACE_ERROR("TerminateThread(m_vtrGetDiscInfo[i].hThread)")
				}
			}

			CloseHandle(m_vtrGetDiscInfo[i].hThread);
			m_vtrGetDiscInfo[i].hThread = NULL;
		}

		if (INVALID_HANDLE_VALUE != m_vtrGetDiscInfo[i].hFindDcmDir)
		{
			FindClose(m_vtrGetDiscInfo[i].hFindDcmDir);
			m_vtrGetDiscInfo[i].hFindDcmDir = INVALID_HANDLE_VALUE;
		}

		if (NULL != m_vtrGetDiscInfo[i].pDcmDirParser)
		{
			delete m_vtrGetDiscInfo[i].pDcmDirParser;
			m_vtrGetDiscInfo[i].pDcmDirParser = NULL;
		}
	}

	m_vtrGetDiscInfo.clear();

	m_DcmDirPatientsTotalInfo.vtrPatients.clear();
	m_DcmDirPatientsTotalInfo.vtrStudies.clear();
	m_DcmDirPatientsTotalInfo.vtrSeries.clear();
	m_DcmDirPatientsTotalInfo.vtrImages.clear();	

	SetSubModuleState(enumSubModuleState_UnInited);
	return bRet ;
}


/**
 ********************************************************************
 * \brief ��������
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
BOOL CDiscImport::HandleJob(PAJob* pJob)
{
	CString strTrace;

	m_pCurrentJob = pJob;

	pJob->SetDetail(JOB_DETAIL_START);
	pJob->SetPhase(JOB_PHASE_IMPORT);
	pJob->SetDetail(JOB_DETAIL_IMPORT_IMPORTING);


	vector<DiscImport_Image>& vtrImagesToBeImported = ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported;

	for (m_iCurrentImageIndex = 0; m_iCurrentImageIndex < vtrImagesToBeImported.size(); m_iCurrentImageIndex++)
	{
		pJob->SetProgress(enumJobProgressUsing_Percentage, m_iCurrentImageIndex*100/vtrImagesToBeImported.size());

		//<< ��ʼ�����ͷ���Դ
		ClearCurrentImportedImageInfo();

		// Job be Cancelled?
		if (m_pCurrentJob->bCancelFlag)
		{
			ClearCurrentImportedImageInfo();

			for (int i = m_iCurrentImageIndex; i < vtrImagesToBeImported.size(); ++i)
			{
				SetImportedSeriesState(i, enumSeriesState_Cancelled);
				SetImportedSeriesProgress(i, enumSeriesProgress_None);
				SetImportedSeriesDetailByDetailInfo(i, _T(""));
			}

			pJob->SetDetail(JOB_DETAIL_CANCELLED);
			pJob->SetState(enumJobState_Cancelled);
			pJob->SetPhase(_T(""));
			pJob->SetProgress(enumJobProgressUsing_None);
			m_pCurrentJob = NULL;
			return TRUE;
		}


		SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Importing);
		SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_Percentage, 0);
		SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_TO_SYSTERM);

		m_strPatientUID = vtrImagesToBeImported[m_iCurrentImageIndex].strPatientUID;
		m_strStudyUID = vtrImagesToBeImported[m_iCurrentImageIndex].strStudyUID;
		m_strSeriesUID = vtrImagesToBeImported[m_iCurrentImageIndex].strSeriesUID;
		m_strImageUID = vtrImagesToBeImported[m_iCurrentImageIndex].strImageUID;

		int i = 0;

// 1. �ж�ͼ���Ƿ��Ѵ�����DB��

		// Does the Series Exist in DB?
		if (!CDBController::GetInstance()->IsImageUIDExistsInDB(m_strImageUID, &m_bImageExist))
		{
			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

			strTrace.Format(_T("CDBController::GetInstance()->IsImageUIDExistsInDB(...), UID: %s"), m_strImageUID);
			PRINTTRACE_ERROR(strTrace)
			continue;
		}

		if (m_bImageExist)
		{
			// The Image UID already Existed in DB, so notify user and continue
			//<< ע��������Ϣ�ɱ��޸ģ���ˣ�����ϵͳ�еĻ�����Ϣ��
			//<<     ����ID�����޸ģ���������¡�
			PatientInfoStruct DBPatientInfo;
			if (CDBController::GetInstance()->GetPatientInfo(m_strPatientUID, &DBPatientInfo))
			{
				SetImportedSeriesDetailByCompletedInfo(m_iCurrentImageIndex,
														DISCIMPORT_SERIES_SKIPPED_INFO_FORMAT,
														CString(CBSTROpt::BSTRToCString(DBPatientInfo.bsPatientID)),
														CString(CBSTROpt::BSTRToCString(DBPatientInfo.bsPatientName)),
														vtrImagesToBeImported[m_iCurrentImageIndex].strStudyID,
														vtrImagesToBeImported[m_iCurrentImageIndex].strSeriesID,
														vtrImagesToBeImported[m_iCurrentImageIndex].strImageID);
				SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
				SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Skipped);
				
				CBSTROpt::FreePatientInfoStruct(&DBPatientInfo);

				pJob->SetProgress(enumJobProgressUsing_CompletedTotal, m_iCurrentImageIndex, vtrImagesToBeImported.size());

				continue;
			}
			else
			{
				SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
				SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
				SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

				strTrace.Format(_T("CDBController::GetInstance()->GetPatientInfo(...), UID: %s"), vtrImagesToBeImported[m_iCurrentImageIndex].strPatientUID);
				PRINTTRACE_ERROR(strTrace)

				pJob->SetProgress(enumJobProgressUsing_CompletedTotal, m_iCurrentImageIndex, vtrImagesToBeImported.size());
				continue;
			}
		}


// 2. �ж�ͼ����̿ռ��Ƿ��㹻


		// Use IS interface to get Image disk free space. 
		long lFreeImageNum = 0;
		if (!CISController::GetInstance()->GetDiskFreeImageNum(&lFreeImageNum))
		{
			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

			strTrace.Format(_T("CISController::GetInstance()->GetDiskFreeImageNum()"));
			PRINTTRACE_ERROR(strTrace)
			continue;
		}

		if (lFreeImageNum <= 0)
		{
			// No enough free disk space
			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_NOT_ENOUGH_FREE_DISK_SPACE);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

			strTrace.Format(_T("CISController::GetInstance()->GetDiskFreeImageNum(), num: %d"), lFreeImageNum);
			PRINTTRACE_ERROR(strTrace)
			continue;
		}

// 		__int64 i64DiskFreeSpace = 0;
// 		//<< �õ�ͼ����ʣ��ռ䣬���ȥ��ȫ����ռ䣨��ϵͳ��ʾһ�£�
// 		if (!GetDiskFreeSpaceEx(IS_PATH, NULL, NULL, (PULARGE_INTEGER)&i64DiskFreeSpace))
// 		{
// 			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
// 			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
// 			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);
// 
// 			strTrace.Format(_T("GetDiskFreeSpaceEx(...), disk: %s"), IS_PATH);
// 			PRINTTRACE_ERROR(strTrace)
// 			continue;
// 		}
// 
// 		//<< ��ȥ����
// 		i64DiskFreeSpace -= 0;
// 		
// 		//<< ����Ҫ�Ĵ��̿ռ䣨Raw + Processed��
// 		__int64 i64ImagesSize = DICOM_RAW_IMAGE_BYTE * 2;
// 
// 		if (i64ImagesSize > i64DiskFreeSpace)
// 		{
// 			// No enough free disk space
// 			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_NOT_ENOUGH_FREE_DISK_SPACE);
// 			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
// 			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);
// 
// 			continue;
// 		}


		// Job be Cancelled?
		if (m_pCurrentJob->bCancelFlag)
		{
			ClearCurrentImportedImageInfo();

			for (i = m_iCurrentImageIndex; i < ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported.size(); ++i)
			{
				SetImportedSeriesState(i, enumSeriesState_Cancelled);
				SetImportedSeriesProgress(i, enumSeriesProgress_None);
				SetImportedSeriesDetailByDetailInfo(i, _T(""));
			}

			pJob->SetState(enumJobState_Cancelled);
			pJob->SetPhase(_T(""));
			pJob->SetProgress(enumJobProgressUsing_None);
			pJob->SetDetail(JOB_DETAIL_CANCELLED);
			m_pCurrentJob = NULL;

			return TRUE;
		}


		//<< ͼ����ϵͳ�в����ڣ��Ҵ��̿ռ��㹻, �ʵ���֮!

// 3. ��ȡ��ͼ��DICOM�ļ��Ļ��ߣ����Ƚṹ��Ϣ��������֮

		// Get PatientTotalInfo

		m_strPostDcmFileInMedia = ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->strDevice + vtrImagesToBeImported[m_iCurrentImageIndex].strReferencedFileID;
		if (!GetPatientInfoInDcm())
		{
			//<< ͼ���״̬�����Ⱥ���ϸ��Ϣ����GetPatientInfoInDcm()�����ã��ʴ˴�����Ҫ
			PRINTTRACE_ERROR("GetPatientInfoInDcm")
			continue;
		}

		// Job be Cancelled?
		if (m_pCurrentJob->bCancelFlag)
		{
			ClearCurrentImportedImageInfo();

			for (i = m_iCurrentImageIndex; i < ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported.size(); ++i)
			{
				SetImportedSeriesState(i, enumSeriesState_Cancelled);
				SetImportedSeriesProgress(i, enumSeriesProgress_None);
				SetImportedSeriesDetailByDetailInfo(i, _T(""));
			}

			pJob->SetState(enumJobState_Cancelled);
			pJob->SetPhase(_T(""));
			pJob->SetProgress(enumJobProgressUsing_None);
			pJob->SetDetail(JOB_DETAIL_CANCELLED);
			m_pCurrentJob = NULL;

			return TRUE;
		}


		// Is Patient, Study and Series exist in DB
		if (!CDBController::GetInstance()->IsPatientUIDExistsInDB(m_strPatientUID, &m_bPatientExist))
		{
			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

			strTrace.Format(_T("CDBController::GetInstance()->IsPatientUIDExistsInDB(...), UID: %s"), m_strPatientUID);
			PRINTTRACE_ERROR(strTrace)
			continue;
		}

		if (!CDBController::GetInstance()->IsStudyUIDExistsInDB(m_strStudyUID, &m_bStudyExist))
		{
			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

			strTrace.Format(_T("CDBController::GetInstance()->IsStudyUIDExistsInDB(...), UID: %s"), m_strStudyUID);
			PRINTTRACE_ERROR(strTrace)
			continue;
		}

		if (!CDBController::GetInstance()->IsSeriesUIDExistsInDB(m_strSeriesUID, &m_bSeriesExist))
		{
			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

			strTrace.Format(_T("CDBController::GetInstance()->IsSeriesUIDExistsInDB(...), UID: %s"), m_strSeriesUID);
			PRINTTRACE_ERROR(strTrace)
			continue;
		}

		// Path in DB
		CString strPatientPath;
		CString strStudyPath;
		CString strSeriesPath;
		CString strImagePath;
		CString strPostProcessedImagePath;

		// PatientInfoStruct
		if (m_bPatientExist)
		{
			//<< ���ߴ��ڣ����DB���»�û�����Ϣ����Ϊ����DB�Ļ�����Ϣ�ѱ��û��޸�
			CBSTROpt::FreePatientInfoStruct(&m_PatientInfo);
			BOOL bRet = CDBController::GetInstance()->GetPatientInfo(m_strPatientUID, &m_PatientInfo);
			if (bRet)
			{
				strPatientPath = CBSTROpt::BSTRToCString(m_PatientInfo.bsPatientFilePath);
			}
			else
			{
				// error, continue
				SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
				SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
				SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

				strTrace.Format(_T("CDBController::GetInstance()->GetPatientInfo(...), UID: %s"), m_strPatientUID);
				PRINTTRACE_ERROR(strTrace)
				continue;
			}
		}
		else
		{
			strPatientPath = CBSTROpt::BSTRToCString(m_PatientInfo.bsPatientFilePath);
			m_PatientInfo.bImportedOrNot = TRUE;
		}


		// StudyInfoStruct
		if (m_bStudyExist)
		{
			//<< �����ڣ����´�DB��ü����Ϣ����Ϊ����DB�ļ����Ϣ�ѱ��û��޸�
			CBSTROpt::FreeStudyInfoStruct(&m_StudyInfo);
			BOOL bRet = CDBController::GetInstance()->GetStudyInfo(m_strStudyUID, &m_StudyInfo);
			if (bRet)
			{
				strStudyPath = CBSTROpt::BSTRToCString(m_StudyInfo.bsStudyImagePath);
			}
			else
			{
				// error, continue
				SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
				SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
				SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

				strTrace.Format(_T("CDBController::GetInstance()->GetStudyInfo(...), UID: %s"), m_strStudyUID);
				PRINTTRACE_ERROR(strTrace)
				continue;
			}
		}
		else
		{
			strStudyPath = CBSTROpt::BSTRToCString(m_StudyInfo.bsStudyImagePath);
			m_StudyInfo.bImportedOrNot = TRUE;
		}

		// SereisInfoStruct
		if (m_bSeriesExist)
		{
			//<< ���д��ڣ����»��DB��������Ϣ����Ҫ�Ǹ���Image�ļ���·��
			CBSTROpt::FreeSeriesInfoStruct(&m_SeriesInfo);
			BOOL bRet = CDBController::GetInstance()->GetSeriesInfo(m_strSeriesUID, &m_SeriesInfo);
			if (bRet)
			{
				strSeriesPath = CBSTROpt::BSTRToCString(m_SeriesInfo.bsSeriesFilePath);
			}
			else
			{
				// error, continue
				SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
				SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
				SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

				strTrace.Format(_T("CDBController::GetInstance()->GetSeriesInfo(...), UID: %s"), m_strSeriesUID);
				PRINTTRACE_ERROR(strTrace)
				continue;
			}
		}
		else
		{
			strSeriesPath = CBSTROpt::BSTRToCString(m_SeriesInfo.bsSeriesFilePath);
			m_SeriesInfo.bImportedOrNot = TRUE;
		}

		// ImageInfoStruct
		strImagePath = CBSTROpt::BSTRToCString(m_ImageInfo.bsImageFilePath);

		// PostProcessingInfo
		strPostProcessedImagePath = CBSTROpt::BSTRToCString(m_PostProcessInfo.bsProcessedImageFilePath);

		m_strPatientFullPath = IS_PATH + strPatientPath;
		m_strStudyFullPath = IS_PATH + strStudyPath;
		m_strSeriesFullPath = IS_PATH + strSeriesPath;
		m_strImageFullPath = IS_PATH + strImagePath;
		m_strPostImageFullPath = IS_PATH + strPostProcessedImagePath;
		m_strPostImagePSFullPath = CIDPathGen::GetInstance()->GenPostProcessedImagePSPath(m_strPostImageFullPath);


//<< 4. �Ƚ����ߣ��������нṹд��DB����DB�в�����
		BOOL bImportDBInfoSuccess = TRUE;

		if (!m_bPatientExist)
		{
			//<< note: 2008-10-23 by Fanzf
			//<< ����ID�����޸ģ�����ʱ��Ψһ����Ŀǰ��Ϊ�䲻���ظ�����Ϊ����һ���Զ����ظ��Խ����ж�
			//<< end note

			// Whether the PatientID needs to be Created or not since PatientID is editable (by User through UI) and 
			// should be unique in system.
			// 
			//		if (PatientID������DB)	�����µ�PatientID
			//		else					Do nothing����ʹ�ø�PatientID

			CString strPatientID = CBSTROpt::BSTRToCString(m_PatientInfo.bsPatientID);
			if (bImportDBInfoSuccess = CDBController::GetInstance()->UpdatePatientID(strPatientID))
			{
				CBSTROpt::FreeBSTR(m_PatientInfo.bsPatientID);
				m_PatientInfo.bsPatientID = strPatientID.AllocSysString();

				// Create Patient Info in DB
				if (!(bImportDBInfoSuccess = CDBController::GetInstance()->AddPatientRecordToDB(&m_PatientInfo)))
				{
					// error, continue
					strTrace.Format(_T("CDBController::GetInstance()->AddPatientRecordToDB(), UID: %s"), m_strPatientUID);
					PRINTTRACE_ERROR(strTrace)
				}
			}
			else
			{
				// error, continue
				strTrace.Format(_T("CDBController::GetInstance()->UpdatePatientID(...), PatientID: %s"), strPatientID);
				PRINTTRACE_ERROR(strTrace)
			}
			
		}

		if (bImportDBInfoSuccess && !m_bStudyExist)
		{
			//<< �����ṹ�����DB��StudyID��DB�������ɣ��������»��DB�ṹ�����ID
			//<< ԭ������ɱ�ɾ��������ID������Ŀǰϵͳ�иû�������һ���ID�ظ��������Ҫ�����µ�ID��Ŀǰ��DB
			//<< ʵ�֣������Ӽ��������»����ID����ͼ����ϸ��Ϣ��ʾ��

			if (!(bImportDBInfoSuccess = CDBController::GetInstance()->AddStudyRecordToDB(&m_StudyInfo)))
			{
				// error, continue
				strTrace.Format(_T("CDBController::GetInstance()->AddStudyRecordToDB(), UID: %s"), m_strStudyUID);
				PRINTTRACE_ERROR(strTrace)
			}
			else
			{
				//<< ���¼��ṹ
				CBSTROpt::FreeStudyInfoStruct(&m_StudyInfo);
				if (!(bImportDBInfoSuccess = CDBController::GetInstance()->GetStudyInfo(m_strStudyUID, &m_StudyInfo)))
				{
					// error, continue
					strTrace.Format(_T("CDBController::GetInstance()->GetStudyInfo(), UID: %s"), m_strStudyUID);
					PRINTTRACE_ERROR(strTrace)
				}
			}

		}

		if (bImportDBInfoSuccess && !m_bSeriesExist)
		{
			if (!(bImportDBInfoSuccess = CDBController::GetInstance()->AddSeriesRecordToDB(&m_SeriesInfo)))
			{
				strTrace.Format(_T("CDBController::GetInstance()->AddSeriesRecordToDB(), UID: %s"), m_strSeriesUID);
				PRINTTRACE_ERROR(strTrace)
			}

		}
		
		if (!bImportDBInfoSuccess)
		{
			//<< ��DB��Ӽ�¼ʧ�ܣ�����������Ӵ˴���ʼ�������RemoveInfoOfUnproperlyImportedImage()
			//<< ���������ʧ�ܺ���Ҫ��DB��¼�ʹ���ͼ���ļ�
			if (!RemoveInfoOfUnproperlyImportedImage())
			{
				PRINTTRACE_ERROR("RemoveInfoOfUnproperlyImportedImage")
			}

			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);
		}

		if (m_pCurrentJob->bCancelFlag)
		{
			RemoveInfoOfUnproperlyImportedImage();

			for (i = m_iCurrentImageIndex; i < ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported.size(); ++i)
			{
				SetImportedSeriesState(i, enumSeriesState_Cancelled);
				SetImportedSeriesProgress(i, enumSeriesProgress_None);
				SetImportedSeriesDetailByDetailInfo(i, _T(""));
			}

			pJob->SetState(enumJobState_Cancelled);
			pJob->SetPhase(_T(""));
			pJob->SetProgress(enumJobProgressUsing_None);
			pJob->SetDetail(JOB_DETAIL_CANCELLED);
			m_pCurrentJob = NULL;

			return TRUE;
		}


// 5. ��ͼ��д��ͼ�����
		
		// Start to Write Info to DB and Image data to disk
		if (!ImportImageToDisk())
		{
			//<< ����ͼ��ʧ��
			//<< ����Detail����Ϣ�����ã��˴�������Ҫ
			
			RemoveInfoOfUnproperlyImportedImage();

			continue;
		}
		
		if (m_pCurrentJob->bCancelFlag)
		{
			RemoveInfoOfUnproperlyImportedImage();

			for (i = m_iCurrentImageIndex; i < ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported.size(); ++i)
			{
				SetImportedSeriesState(i, enumSeriesState_Cancelled);
				SetImportedSeriesProgress(i, enumSeriesProgress_None);
				SetImportedSeriesDetailByDetailInfo(i, _T(""));
			}

			pJob->SetState(enumJobState_Cancelled);
			pJob->SetPhase(_T(""));
			pJob->SetProgress(enumJobProgressUsing_None);
			pJob->SetDetail(JOB_DETAIL_CANCELLED);
			m_pCurrentJob = NULL;

			return TRUE;
		}

		
// 6. ��ͼ����Ϣд�����ݿ�


		//<< Create Image Info and PostProcess Info in DB

		if (bImportDBInfoSuccess = CDBController::GetInstance()->AddImageRecordToDB(&m_ImageInfo))
		{
			if (!(bImportDBInfoSuccess = CDBController::GetInstance()->SetPostProcessingInfo(&m_PostProcessInfo)))
			{
				strTrace.Format(_T("CDBController::GetInstance()->SetPostProcessingInfo(), UID: %s"), m_strImageUID);
				PRINTTRACE_ERROR(strTrace)
			}
		}
		else
		{
			strTrace.Format(_T("CDBController::GetInstance()->AddImageRecordToDB(), UID: %s"), m_strImageUID);
			PRINTTRACE_ERROR(strTrace)
		}


		if (bImportDBInfoSuccess)
		{
			CString strPatientID = CBSTROpt::BSTRToCString(m_PatientInfo.bsPatientID);
			CString strPatientName = CBSTROpt::BSTRToCString(m_PatientInfo.bsPatientName);
			CString strStudyID;
			strStudyID.Format(_T("%d"), m_StudyInfo.iStudyID);
			CString strSeriesID;
			strSeriesID.Format(_T("%d"), m_SeriesInfo.iSeriesID);
			CString strImageID;
			strImageID.Format(_T("%d"), m_ImageInfo.iImageID);

			SetImportedSeriesDetailByCompletedInfo(m_iCurrentImageIndex, DISCIMPORT_SERIES_COMPLETED_INFO_FORMAT, strPatientID, strPatientName, strStudyID, strSeriesID, strImageID);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_Percentage, 100);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Completed);
		}
		else
		{
			//<< ��DB��Ӽ�¼ʧ��
			if (!RemoveInfoOfUnproperlyImportedImage())
			{
				PRINTTRACE_ERROR("RemoveInfoOfUnproperlyImportedImage")
			}

			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);
		}

		ClearCurrentImportedImageInfo();

		// A Image is Imported, so notify GUI to refresh image disk space,
		// then continue
		Notify(NOTIFY_IMPORT_ONE_IMAGE_IMPORTED);

		pJob->SetProgress(enumJobProgressUsing_CompletedTotal, m_iCurrentImageIndex, vtrImagesToBeImported.size());
	}


	//<< ����ȫ������
	JobState enumJobState = enumJobState_Completed;
	for (int i = 0; i < ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported.size(); i++)
	{
		if (enumSeriesState_Failed == ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[i].enumState)
		{
			enumJobState = enumJobState_Failed;
			break;
		}
	}

	if (enumJobState_Completed == enumJobState)
	{
		pJob->SetDetail(JOB_DETAIL_COMPLETED);

		const unsigned int uiCompletedProgress(100);
		pJob->SetProgress(enumJobProgressUsing_CompletedTotal, uiCompletedProgress, uiCompletedProgress);
	}
	else
	{
		pJob->SetDetail(JOB_DETAIL_FAILED);
	}
	pJob->SetPhase(_T(""));
	pJob->SetState(enumJobState);

	// UserGuidance to notify User
	if (enumJobState_Completed == enumJobState)
	{
		NotifyUG(IDS_PRINTINGARCHIVING_IMPORT_JOB_COMPLETED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
	}
	else
	{
		NotifyUG(IDS_PRINTINGARCHIVING_IMPORT_JOB_FAILED, enumUG_TYPE_T, enumUG_PRIOR_L, TRUE);
	}

	m_pCurrentJob = NULL;

	return TRUE;
}


/**
 ********************************************************************
 * \brief ��õ����豸�б�
 *  
 *  
 * \param BSTR** ppbsDevices : [in] 
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
BOOL CDiscImport::GetImportDevices(BSTR** ppbsDevices, long* pLen)
{
	if (0 == m_vtrGetDiscInfo.size())
	{
		*ppbsDevices = NULL;
		*pLen = 0;
		return TRUE;
	}

	*pLen = m_vtrGetDiscInfo.size();
	ULONG cb = sizeof(BSTR) * (*pLen);
	*ppbsDevices = (BSTR*)CoTaskMemAlloc(cb);
	if (NULL == *ppbsDevices)
	{
		return FALSE;
	}

	for (int i = 0; i < m_vtrGetDiscInfo.size(); i++)
	{
		(*ppbsDevices)[i] = m_vtrGetDiscInfo[i].strDevice.AllocSysString();
	}

	return TRUE;

}


/**
 ********************************************************************
 * \brief ��õ��������Ϣ֪ͨ
 *  
 *  
 * \param LPCTSTR szDeviceName : [in] 
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
BOOL CDiscImport::GetImportDiscInfoNotify(LPCTSTR szDeviceName)
{	
	BSTR bsInfo = CString(_TT(DISCIMPORT_GET_DI_STATE_START)).AllocSysString(); 
	Notify(NOTIFY_DISCIMPORT_GET_DISCINFO_STATE, (LPARAM)bsInfo);

	CSingleLock sLock(&m_CSLockValidState);
	sLock.Lock();

	//<< �����Ϣ
	m_DcmDirPatientsTotalInfo.vtrPatients.clear();
	m_DcmDirPatientsTotalInfo.vtrStudies.clear();
	m_DcmDirPatientsTotalInfo.vtrSeries.clear();
	m_DcmDirPatientsTotalInfo.vtrImages.clear();

	GetImportDiscInfoStruct* pdis = NULL;
	int iIndex = 0;
	for (; iIndex < m_vtrGetDiscInfo.size(); iIndex++)
	{
		if (!m_vtrGetDiscInfo[iIndex].strDevice.Compare(szDeviceName))
		{
			pdis = &m_vtrGetDiscInfo[iIndex];
			m_vtrGetDiscInfo[iIndex].bValid = TRUE;
		}
		else
		{
			m_vtrGetDiscInfo[iIndex].bValid = FALSE;
		}
	}

	if (NULL == pdis)
	{
		ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_ERROR, FALSE);
		sLock.Unlock();
		return TRUE;
	}

	if (NULL != pdis->hThread)
	{
		if (WAIT_TIMEOUT == WaitForSingleObject(pdis->hThread, 0))
		{
			//<< ���߳���������
			sLock.Unlock();
			return TRUE;
		}
		else
		{
			CloseHandle(pdis->hThread);
			pdis->hThread = NULL;
		}
	}

	if (INVALID_HANDLE_VALUE != pdis->hFindDcmDir)
	{
		FindClose(pdis->hFindDcmDir);
		pdis->hFindDcmDir = INVALID_HANDLE_VALUE;
	}
	
	if (NULL != pdis->pDcmDirParser)
	{
		delete pdis->pDcmDirParser;
		pdis->pDcmDirParser = NULL;
	}


	if (NULL == szDeviceName)
	{
		ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_ERROR, FALSE);
		sLock.Unlock();
		return TRUE;
	}

	pdis->hThread = CreateThread(NULL, 0, GetImportDiscInfoThreadProc, pdis, 0, NULL);
	if (NULL == pdis->hThread)
	{
		ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_ERROR, FALSE);
		sLock.Unlock();
		return TRUE;
	}

	sLock.Unlock();
	return TRUE;
}


/**
 ********************************************************************
 * \brief ��õ��������Ϣ����
 *  
 *  
 * \param GetImportDiscInfoStruct* pdis : [in] 
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
BOOL CDiscImport::GetImportDiscInfoProc(GetImportDiscInfoStruct* pdis)
{
	CString strTrace;
	CSingleLock sLock(&m_CSLockValidState);

	if (NULL == pdis)
	{
		sLock.Lock();
		if (pdis->bValid)
		{
			ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_ERROR, FALSE);
		}
		sLock.Unlock();
		return FALSE;
	}

	//
	CString strDcmDirFileName = pdis->strDevice + _T("DICOMDIR");
	WIN32_FIND_DATA FindFileData;

	if (INVALID_HANDLE_VALUE != pdis->hFindDcmDir)
	{
		FindClose(pdis->hFindDcmDir);
		pdis->hFindDcmDir = INVALID_HANDLE_VALUE;
	}
	
	pdis->hFindDcmDir = FindFirstFile(strDcmDirFileName, &FindFileData);
	if (INVALID_HANDLE_VALUE == pdis->hFindDcmDir) 
	{
		DWORD dwRet = GetLastError();
		if (87 == dwRet				// Tray open
			|| 21 == dwRet)			// Tray closed but no disc
		{
			// No disc anyway
			sLock.Lock();
			if (pdis->bValid)
			{
				ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_NO_DISC, FALSE);
			}
			sLock.Unlock();
			return FALSE;
		}
		else if (2 == dwRet			// have a disc but no DICOMDIR
				|| 1005 == dwRet)	// unknow filesystem, maybe a blank disc?
		{
			// The disc is not a back up disc
			sLock.Lock();
			if (pdis->bValid)
			{
				ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_INVALID_IMPORTING_DISC, FALSE);
			}
			sLock.Unlock();
			return FALSE;
		}
		else
		{
			strTrace.Format(_T("%d == GetLastError() while FindFirstFile(...), file name: %s"), dwRet, strDcmDirFileName);
			PRINTTRACE_ERROR(strTrace)

			sLock.Lock();
			if (pdis->bValid)
			{
				ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_FAILED, FALSE);
			}
			sLock.Unlock();
			return FALSE;
		}
	} 
	else 
	{
		FindClose(pdis->hFindDcmDir);
		pdis->hFindDcmDir = INVALID_HANDLE_VALUE;
	}

	//<< �Ƿ���߳�����Ч
	sLock.Lock();
	if (!pdis->bValid)
	{
		sLock.Unlock();
		return TRUE;
	}
	sLock.Unlock();


	if (NULL != pdis->pDcmDirParser)
	{
		delete pdis->pDcmDirParser;
		pdis->pDcmDirParser = NULL;
	}

	pdis->pDcmDirParser = new CDcmDirParser;

	if (!pdis->pDcmDirParser->LoadDcmDir(strDcmDirFileName))
	{
		sLock.Lock();

		delete pdis->pDcmDirParser;
		pdis->pDcmDirParser = NULL;

		if (pdis->bValid)
		{
			ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_FAILED, FALSE);
		}
		sLock.Unlock();
		return FALSE;

		strTrace.Format(_T("m_pDcmDirParser->LoadDcmDir(strDcmDirFileName), strDcmDirFileName : %s"), strDcmDirFileName);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	//<< �Ƿ���߳�����Ч
	sLock.Lock();
	if (!pdis->bValid)
	{
		delete pdis->pDcmDirParser;
		pdis->pDcmDirParser = NULL;

		sLock.Unlock();
		return TRUE;
	}
	sLock.Unlock();

	// Does the disc can be imported by system?
	// Is Exported by our system? (By ImplementationClassUID)
	LPCTSTR szImpClassUID = NULL;
	pdis->pDcmDirParser->GetImplementationClassUID(&szImpClassUID);
	CString strImpClassUID = szImpClassUID;

	CDcmUIDGen DcmUIDGen;
	if (strImpClassUID.Compare(DcmUIDGen.GetImplementationClassUID()))
	{
		sLock.Lock();

		delete pdis->pDcmDirParser;
		pdis->pDcmDirParser = NULL;

		if (pdis->bValid)
		{
			ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_INVALID_IMPORTING_DISC, FALSE);
		}
		sLock.Unlock();
		return FALSE;
	}

	// The disc is Exported by our system!
	//<< ��pDcmDirPTI��ʹ�����ڲ�Ҫɾ������pDcmDirParser����ΪpDcmDirPTI
	//<< ָ�����pDcmDirParser�ĳ�Ա��
	DICOMDIRPatientsTotalInfo* pDcmDirPTI = NULL;
	if (!pdis->pDcmDirParser->GetDirPatientsInfo(&pDcmDirPTI))
	{
		sLock.Lock();

		delete pdis->pDcmDirParser;
		pdis->pDcmDirParser = NULL;

		if (pdis->bValid)
		{
			ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_FAILED, FALSE);
		}
		sLock.Unlock();

		strTrace.Format(_T("m_pDcmDirParser->GetDirPatientsInfo(&pDcmDirPTI), strDcmDirFileName : %s"), strDcmDirFileName);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	//<< �Ƿ���߳�����Ч
	sLock.Lock();
	if (!pdis->bValid)
	{
		delete pdis->pDcmDirParser;
		pdis->pDcmDirParser = NULL;

		sLock.Unlock();
		return TRUE;
	}
	sLock.Unlock();


	// Add Patient Info
	sLock.Lock();

	for (int i = 0; i < pDcmDirPTI->vtrPatients.size(); i++)
	{
		DICOMDIRPatientInfo DcmDirPatient;
		DcmDirPatient.strPatientUID = (LPCTSTR)pDcmDirPTI->vtrPatients[i].strPatientUID;
		DcmDirPatient.strPatientID = (LPCTSTR)pDcmDirPTI->vtrPatients[i].strPatientID;
		DcmDirPatient.strPatientName = (LPCTSTR)pDcmDirPTI->vtrPatients[i].strPatientName;
		DcmDirPatient.strPatientGender = (LPCTSTR)pDcmDirPTI->vtrPatients[i].strPatientGender;
		DcmDirPatient.dtBirthDate = pDcmDirPTI->vtrPatients[i].dtBirthDate;
		DcmDirPatient.uStudyNum = pDcmDirPTI->vtrPatients[i].uStudyNum;

		m_DcmDirPatientsTotalInfo.vtrPatients.push_back(DcmDirPatient);
	}

	// Add Study Info
	for (i = 0; i < pDcmDirPTI->vtrStudies.size(); i++)
	{
		DICOMDIRStudyInfo DcmDirStudy;
		DcmDirStudy.strStudyUID = (LPCTSTR)pDcmDirPTI->vtrStudies[i].strStudyUID;
		DcmDirStudy.strPatientUID = (LPCTSTR)pDcmDirPTI->vtrStudies[i].strPatientUID;
		DcmDirStudy.strStudyID = (LPCTSTR)pDcmDirPTI->vtrStudies[i].strStudyID;
		DcmDirStudy.dtStudyDateTime = pDcmDirPTI->vtrStudies[i].dtStudyDateTime;
		DcmDirStudy.strRefPhisicianName = (LPCTSTR)pDcmDirPTI->vtrStudies[i].strRefPhisicianName;
		DcmDirStudy.strStudyDescription = (LPCTSTR)pDcmDirPTI->vtrStudies[i].strStudyDescription;
		DcmDirStudy.uSeriesNum = pDcmDirPTI->vtrStudies[i].uSeriesNum;
		
		m_DcmDirPatientsTotalInfo.vtrStudies.push_back(DcmDirStudy);
	}

	// Add Series Info
	for (i = 0; i < pDcmDirPTI->vtrSeries.size(); i++)
	{
		DICOMDIRSeriesInfo DcmDirSeries;
		DcmDirSeries.strSeriesUID = (LPCTSTR)pDcmDirPTI->vtrSeries[i].strSeriesUID;
		DcmDirSeries.strStudyUID = (LPCTSTR)pDcmDirPTI->vtrSeries[i].strStudyUID;
		DcmDirSeries.strSeriesID = (LPCTSTR)pDcmDirPTI->vtrSeries[i].strSeriesID;
		DcmDirSeries.strAprRegionName = (LPCTSTR)pDcmDirPTI->vtrSeries[i].strAprRegionName;
		DcmDirSeries.uImageNum = pDcmDirPTI->vtrSeries[i].uImageNum;
		
		m_DcmDirPatientsTotalInfo.vtrSeries.push_back(DcmDirSeries);
	}

	// Add Image Info
	for (i = 0; i < pDcmDirPTI->vtrImages.size(); i++)
	{
		DICOMDIRImageInfo DcmDirImage;
		DcmDirImage.strSeriesUID = (LPCTSTR)pDcmDirPTI->vtrImages[i].strSeriesUID;
		DcmDirImage.strImageUID = (LPCTSTR)pDcmDirPTI->vtrImages[i].strImageUID;
		DcmDirImage.strReferencedFileID = (LPCTSTR)pDcmDirPTI->vtrImages[i].strReferencedFileID;
		DcmDirImage.strImageID = (LPCTSTR)pDcmDirPTI->vtrImages[i].strImageID;
		DcmDirImage.strAprOrganName = (LPCTSTR)pDcmDirPTI->vtrImages[i].strAprOrganName;
		DcmDirImage.uRows = pDcmDirPTI->vtrImages[i].uRows;
		DcmDirImage.uColumns = pDcmDirPTI->vtrImages[i].uColumns;
		
		m_DcmDirPatientsTotalInfo.vtrImages.push_back(DcmDirImage);
	}
	sLock.Unlock();

	//<< ������Ҫ�˶���
	delete pdis->pDcmDirParser;
	pdis->pDcmDirParser = NULL;

	// Notify Client to get the DiscInfo
	sLock.Lock();
	if (pdis->bValid)
	{
		ReportGetImportDiscInfoStateAndResult(DISCIMPORT_GET_DI_STATE_SUCCEED, TRUE);
	}
	sLock.Unlock();

	return TRUE;
}

/**
 ********************************************************************
 * \brief ��õ��������Ϣ
 *  
 *  
 * \param DiscImportPatientInfo** ppPatients : [out] 
 * \param long* pPatientNum : [out] 
 * \param DiscImportStudyInfo** ppStudies : [out] 
 * \param long* pStudyNum : [out] 
 * \param DiscImportSeriesInfo** ppSeries : [out] 
 * \param long* pSeriesNum : [out] 
 * \param DiscImportImageInfo** ppImages : [out] 
 * \param long* pImageNum : [out] 
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
BOOL CDiscImport::GetImportDiscInfo(DiscImportPatientInfo** ppPatients,
							long* pPatientNum,
							DiscImportStudyInfo** ppStudies,
							long* pStudyNum,
							DiscImportSeriesInfo** ppSeries,
							long* pSeriesNum,
							DiscImportImageInfo** ppImages,
							long* pImageNum)
{
	// PatientInfo
	*pPatientNum = m_DcmDirPatientsTotalInfo.vtrPatients.size();
	if (0 == *pPatientNum)
	{
		*ppPatients = NULL;
	}
	else
	{
		*ppPatients = (DiscImportPatientInfo*)CoTaskMemAlloc(sizeof(DiscImportPatientInfo) * (*pPatientNum));
		for (int i = 0; i < *pPatientNum; i++)
		{
			(*ppPatients + i)->bsPatientUID = m_DcmDirPatientsTotalInfo.vtrPatients[i].strPatientUID.AllocSysString();

			(*ppPatients + i)->bsPatientID = m_DcmDirPatientsTotalInfo.vtrPatients[i].strPatientID.AllocSysString();
			(*ppPatients + i)->bsPatientName = m_DcmDirPatientsTotalInfo.vtrPatients[i].strPatientName.AllocSysString();
			if (!m_DcmDirPatientsTotalInfo.vtrPatients[i].strPatientGender.Compare(_T("0")))
			{
				(*ppPatients + i)->iPatientGender = 0;
			}
			else if (!m_DcmDirPatientsTotalInfo.vtrPatients[i].strPatientGender.Compare(_T("1")))
			{
				(*ppPatients + i)->iPatientGender = 1;
			}
			else
			{
				(*ppPatients + i)->iPatientGender = 2;
			}
			(*ppPatients + i)->dtBirthDate = m_DcmDirPatientsTotalInfo.vtrPatients[i].dtBirthDate;
			(*ppPatients + i)->uStudyNum = m_DcmDirPatientsTotalInfo.vtrPatients[i].uStudyNum;
		}
	}

	// StudyInfo
	*pStudyNum = m_DcmDirPatientsTotalInfo.vtrStudies.size();
	if (0 == *pStudyNum)
	{
		*ppStudies = NULL;
	}
	else
	{
		*ppStudies = (DiscImportStudyInfo*)CoTaskMemAlloc(sizeof(DiscImportStudyInfo) * (*pStudyNum));
		for (int i = 0; i < *pStudyNum; i++)
		{
			(*ppStudies + i)->bsStudyUID = m_DcmDirPatientsTotalInfo.vtrStudies[i].strStudyUID.AllocSysString();
			(*ppStudies + i)->bsPatientUID = m_DcmDirPatientsTotalInfo.vtrStudies[i].strPatientUID.AllocSysString();

			(*ppStudies + i)->bsStudyID = m_DcmDirPatientsTotalInfo.vtrStudies[i].strStudyID.AllocSysString();
			(*ppStudies + i)->dtStudyDateTime = m_DcmDirPatientsTotalInfo.vtrStudies[i].dtStudyDateTime;
			(*ppStudies + i)->bsRefPhisicianName = m_DcmDirPatientsTotalInfo.vtrStudies[i].strRefPhisicianName.AllocSysString();
			(*ppStudies + i)->bsStudyDescription = m_DcmDirPatientsTotalInfo.vtrStudies[i].strStudyDescription.AllocSysString();
			(*ppStudies + i)->uSeriesNum = m_DcmDirPatientsTotalInfo.vtrStudies[i].uSeriesNum;
		}
	}

	// SeriesInfo
	*pSeriesNum = m_DcmDirPatientsTotalInfo.vtrSeries.size();
	if (0 == *pSeriesNum)
	{
		*ppSeries = NULL;
	}
	else
	{
		*ppSeries = (DiscImportSeriesInfo*)CoTaskMemAlloc(sizeof(DiscImportSeriesInfo) * *pSeriesNum);
		for (int i = 0; i < *pSeriesNum; i++)
		{
			(*ppSeries + i)->bsSeriesUID = m_DcmDirPatientsTotalInfo.vtrSeries[i].strSeriesUID.AllocSysString();
			(*ppSeries + i)->bsStudyUID = m_DcmDirPatientsTotalInfo.vtrSeries[i].strStudyUID.AllocSysString();

			(*ppSeries + i)->bsSeriesID = m_DcmDirPatientsTotalInfo.vtrSeries[i].strSeriesID.AllocSysString();
			(*ppSeries + i)->bsAprRegionName = m_DcmDirPatientsTotalInfo.vtrSeries[i].strAprRegionName.AllocSysString();
			(*ppSeries + i)->uImageNum = m_DcmDirPatientsTotalInfo.vtrSeries[i].uImageNum;
		}
	}

	// Image info
	*pImageNum = m_DcmDirPatientsTotalInfo.vtrImages.size();
	if (0 == *pImageNum)
	{
		*ppImages = NULL;
	}
	else
	{
		*ppImages = (DiscImportImageInfo*)CoTaskMemAlloc(sizeof(DiscImportImageInfo) * *pImageNum);
		for (int i = 0; i < *pImageNum; i++)
		{
			(*ppImages + i)->bsImageUID = m_DcmDirPatientsTotalInfo.vtrImages[i].strImageUID.AllocSysString();
			(*ppImages + i)->bsSeriesUID = m_DcmDirPatientsTotalInfo.vtrImages[i].strSeriesUID.AllocSysString();

			(*ppImages + i)->bsImageID = m_DcmDirPatientsTotalInfo.vtrImages[i].strImageID.AllocSysString();
			(*ppImages + i)->bsAprOrganName = m_DcmDirPatientsTotalInfo.vtrImages[i].strAprOrganName.AllocSysString();
			(*ppImages + i)->uRows = m_DcmDirPatientsTotalInfo.vtrImages[i].uRows;
			(*ppImages + i)->uColumns = m_DcmDirPatientsTotalInfo.vtrImages[i].uColumns;
		}
	}
	
	return TRUE;
}


/**
 ********************************************************************
 * \brief ȡ����õ��������Ϣ
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
BOOL CDiscImport::CancelGetImportDiscInfo()
{
	BOOL bRet = TRUE;

	CSingleLock sLock(&m_CSLockValidState);
	sLock.Lock();

	int iIndex = 0;
	for (; iIndex < m_vtrGetDiscInfo.size(); iIndex++)
	{
		m_vtrGetDiscInfo[iIndex].bValid = FALSE;
	}
	
	sLock.Unlock();
	return bRet;
}


/**
 ********************************************************************
 * \brief ��������
 *  
 *  
 * \param vector<CString>* pvtrUIDs : [in] 
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
BOOL CDiscImport::CreateJob(vector<CString>* pvtrUIDs, PatientAdminUIDType enumUIDType)
{
	if (0 == pvtrUIDs->size())
	{
		return FALSE;
	}

	PAJob* pJob = new PAJob;
	
	// make job ID
	SYSTEMTIME st;
	::GetLocalTime(&st);
	pJob->strJobID.Format(_T("%04d%02d%02d%02d%02d%02d%03d"), st.wYear, st.wMonth,
		st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	pJob->enumJobType = enumJobType_DiscImportJob;
	pJob->bCancelFlag = FALSE;
	pJob->enumJobState = enumJobState_Submitted;
	pJob->strPhase = _T("");
	pJob->enumJobProgressUsing = enumJobProgressUsing_None;
	pJob->uiCompleted = 0;
	pJob->uiTotal = 0;
	pJob->dwPercentage = 0;

	// First detail info
	pJob->vtrDetail.clear();
	JobDetail aJobDetail;
	aJobDetail.stDateTime = st;
	aJobDetail.strDetail = _TT(JOB_DETAIL_SUBMITED); 
	pJob->vtrDetail.push_back(aJobDetail);


	DiscImportJobSettingsStruct* pdijss = new DiscImportJobSettingsStruct;
	pJob->pData = pdijss;

	//<< ����豸
	int iIndex = 0;
	for (; iIndex < m_vtrGetDiscInfo.size(); iIndex++)
	{
		if (m_vtrGetDiscInfo[iIndex].bValid)
		{
			pdijss->strDevice = m_vtrGetDiscInfo[iIndex].strDevice;
			break;
		}
	}

	if (iIndex == m_vtrGetDiscInfo.size())
	{
		// error
		delete pJob;
		return FALSE;
	}

	//<< ���ѡ���ͼ��ṹ
	switch(enumUIDType)
	{
	case enumPatientAdminUIDType_Patient:
		{
			for (int i = 0; i < pvtrUIDs->size(); i++)
			{
				//<< һ������
				CString strPatientUID = (*pvtrUIDs)[i];
				
				//<< �ҵ��û���
				for (int h = 0; h < m_DcmDirPatientsTotalInfo.vtrPatients.size(); h++)
				{
					if (!strPatientUID.Compare(m_DcmDirPatientsTotalInfo.vtrPatients[h].strPatientUID))
					{
						//<< ���ҵ�
						break;
					}
				}

				for (int j = 0; j < m_DcmDirPatientsTotalInfo.vtrStudies.size(); j++)
				{
					if (!strPatientUID.Compare(m_DcmDirPatientsTotalInfo.vtrStudies[j].strPatientUID))
					{
						//<< �ҵ��û����µ�һ�����
						CString strStudyUID = m_DcmDirPatientsTotalInfo.vtrStudies[j].strStudyUID;
						for (int k = 0; k < m_DcmDirPatientsTotalInfo.vtrSeries.size(); k++)
						{
							if (!strStudyUID.Compare(m_DcmDirPatientsTotalInfo.vtrSeries[k].strStudyUID))
							{
								//<< �ҵ��ü���µ�һ������
								CString strSeriesUID = m_DcmDirPatientsTotalInfo.vtrSeries[k].strSeriesUID;
								for (int l =0; l < m_DcmDirPatientsTotalInfo.vtrImages.size(); l++)
								{
									if (!strSeriesUID.Compare(m_DcmDirPatientsTotalInfo.vtrImages[l].strSeriesUID))
									{
										//<< �ҵ��������µ�һ��ͼ�񣬽�����룡
										DiscImport_Image dii;
										dii.strImageUID = m_DcmDirPatientsTotalInfo.vtrImages[l].strImageUID;
										dii.strSeriesUID = strSeriesUID;
										dii.strStudyUID = strStudyUID;
										dii.strPatientUID = strPatientUID;

										dii.strIndex.Format(_T("%d"), pdijss->vtrImagesToBeImported.size() + 1);
										dii.strPatientID = m_DcmDirPatientsTotalInfo.vtrPatients[h].strPatientID;
										dii.strPatientName = m_DcmDirPatientsTotalInfo.vtrPatients[h].strPatientName;
										dii.strStudyID = m_DcmDirPatientsTotalInfo.vtrStudies[j].strStudyID;
										dii.strSeriesID = m_DcmDirPatientsTotalInfo.vtrSeries[k].strSeriesID;
										dii.strImageID = m_DcmDirPatientsTotalInfo.vtrImages[l].strImageID;

										dii.strReferencedFileID = m_DcmDirPatientsTotalInfo.vtrImages[l].strReferencedFileID;

										// ״̬
										dii.enumState = enumSeriesState_Waiting;

										// ����
										dii.strProgress = _T("");

										// ��ϸ��Ϣ
										dii.strDetailInfo = _T("");

										//<< ����
										pdijss->vtrImagesToBeImported.push_back(dii);
									}
								}	// for (series)
							}
						}	// for (study)
						
					}
				}
			}	// for (patient)
		}
		break;
	case enumPatientAdminUIDType_Study:
		delete pJob;
		return FALSE;
	case enumPatientAdminUIDType_Series:
		delete pJob;
		return FALSE;
	case enumPatientAdminUIDType_Image:
		delete pJob;
		return FALSE;
	default:
		delete pJob;
		return FALSE;
	}

	if (CJobHandler::GetInstance()->PushJob(pJob))
	{
		return TRUE;
	}
	else
	{
		delete pJob;
		return FALSE;
	}

// 	m_hGetFramePixelDataThread = CreateThread(NULL, 0, DiscImportThreadProc, this, 0, NULL);
// 	if (NULL == m_hGetFramePixelDataThread)
// 	{
// 		return FALSE;
// 	}

	return TRUE;
}


/**
 ********************************************************************
 * \brief ȡ����õ��������Ϣ
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
BOOL CDiscImport::GetPatientInfoInDcm()
{
	CString strTrace;

	if (m_pDcmParser)
	{
		delete m_pDcmParser;
		m_pDcmParser = NULL;
	}
	
	// Is the Dcm File exist?
	if (!IsFileExistInMedia(m_strPostDcmFileInMedia))
	{
		// ��ϸ��Ϣ�����ã��˴�����Ҫ

		delete m_pDcmParser;
		m_pDcmParser = NULL;

		return FALSE;
	}


	// Load Dcm file

	m_pDcmParser = new CDcmParser;
	if (!m_pDcmParser->LoadDXDcmFile(m_strPostDcmFileInMedia))
	{
		SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
		SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
		SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

		delete m_pDcmParser;
		m_pDcmParser = NULL;

		strTrace.Format(_T("DcmParser.LoadXADcmFile(strDcmFile), strDcmFile: %s"), m_strPostDcmFileInMedia);
		PRINTTRACE_ERROR(strTrace)

		return FALSE;
	}

	if (   m_pDcmParser->GetPatientInfo(&m_PatientInfo)
		&& m_pDcmParser->GetStudyInfo(&m_StudyInfo)
		&& m_pDcmParser->GetSeriesInfo(&m_SeriesInfo)
		&& m_pDcmParser->GetImageInfo(&m_ImageInfo)
		&& m_pDcmParser->GetPostProcessInfo(&m_PostProcessInfo))
	{
		;
	}
	else
	{
		SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
		SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
		SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

		delete m_pDcmParser;
		m_pDcmParser = NULL;

		strTrace.Format(_T("DcmParser.GetPatientTotalInfo(...), strDcmFile: %s"), m_strPostDcmFileInMedia);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}

	//<< ���ͼ�����Ч�ԣ����������ʱִ�У���ʱ�����еĵ����̿����Ѳ����ύ
	//<< ��������ʱ�ĵ����̣�������֤ͼ��UID
	CString strImageUIDInMedia = CBSTROpt::BSTRToCString(m_ImageInfo.bsImageUID);
	if (m_strImageUID.Compare(strImageUIDInMedia))
	{
		SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
		SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
		SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

		delete m_pDcmParser;
		m_pDcmParser = NULL;

		strTrace.Format(_T("ImageUIDs are not matching, UID of Job: %s, UID of media: %s"), m_strImageUID, strImageUIDInMedia);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}


// 		ValidatePatientTotalInfo(&DcmPatientTotalInfo);

	return TRUE;
}


/**
 ********************************************************************
 * \brief ����ͼ�񵽴���
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
BOOL CDiscImport::ImportImageToDisk()
{
	//<< Raw Dcm file and Processed Dcm File

	CString strTrace;

	// ����ͼ�����ڵ�Ŀ¼
	if (!CDirHandler::CreateDir(m_strSeriesFullPath))
	{
		// error
		SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
		SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
		SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

		strTrace.Format(_T("CDirHandler::CreateDir(), m_strStudyFullPath: %s"), m_strStudyFullPath);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;;
	}


//<< 1. Raw File
	
	CString strRawDcmFileInMedia;
	GetRawDcmFileNameByProcessedDcmFileNameInMedia(strRawDcmFileInMedia, m_strPostDcmFileInMedia);
	if (!IsFileExistInMedia(strRawDcmFileInMedia))
	{
		// ��ϸ��Ϣ�����ã��˴�����Ҫ

		return FALSE;
	}

	CDcmModify aDcmModify;
	if (!aDcmModify.ModifyDcm(strRawDcmFileInMedia, m_strImageFullPath, &m_PatientInfo, &m_StudyInfo))
	{
		// error
		SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
		SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
		SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

		strTrace.Format(_T("aDcmModify.ModifyDcm(strRawDcmFileInMedia, m_strImageFullPath, TRUE), m_strPostDcmFileInMedia:%s, m_strImageFullPath:%s"), strRawDcmFileInMedia, m_strImageFullPath);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;;
	}

	//<< ���ͽ���, 50%
	SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_Percentage, 50);
	
	//<< �Ƿ�ȡ��
	if (m_pCurrentJob->bCancelFlag)
	{
		return TRUE;
	}

//<< 2. Processed Dcm

	if (!IsFileExistInMedia(m_strPostDcmFileInMedia))
	{
		// ��ϸ��Ϣ�����ã��˴�����Ҫ

		return FALSE;
	}
	
	if (!aDcmModify.ModifyDcm(m_strPostDcmFileInMedia, m_strPostImageFullPath, &m_PatientInfo, &m_StudyInfo))
	{
		// error
		SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
		SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
		SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

		strTrace.Format(_T("aDcmModify.ModifyDcm(m_strPostDcmFileInMedia, m_strPostImageFullPath, TRUE), m_strPostDcmFileInMedia:%s, m_strPostImageFullPath:%s"), m_strPostDcmFileInMedia, m_strPostImageFullPath);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;;
	}

	//<< �Ƿ�ȡ��
	if (m_pCurrentJob->bCancelFlag)
	{
		return TRUE;
	}

//<< 3. Procssed Dcm PS
	CString strPSFileInMedia;
	GetPSFileNameByProcessedDcmFileNameInMedia(strPSFileInMedia, m_strPostDcmFileInMedia);
	if (!IsFileExistInMedia(strPSFileInMedia))
	{
		// ��ϸ��Ϣ�����ã��˴�����Ҫ

		return FALSE;
	}

	if (!::CopyFile(strPSFileInMedia, m_strPostImagePSFullPath, FALSE))
	{
		// error
		SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
		SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
		SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

		strTrace.Format(_T("CopyFile(strPSFileInMedia, m_strPostImagePSFullPath, TRUE), strPSFileInMedia:%s, m_strPostImagePSFullPath:%s"), strPSFileInMedia, m_strPostImagePSFullPath);
		PRINTTRACE_ERROR(strTrace)
		return FALSE;
	}
	else
	{
		//<< ȥ�����ļ���ֻ������
		if (!::SetFileAttributes(m_strPostImagePSFullPath, FILE_ATTRIBUTE_NORMAL))
		{
			//<< ����ʧ��
			// error
			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);

			strTrace.Format(_T("SetFileAttributes(szFile�� FILE_ATTRIBUTE_NORMAL): %s"), m_strPostImagePSFullPath);
			PRINTTRACE_ERROR(strTrace)
			return FALSE;
		}
	}


	//<< ����100��Ϣ�ڳɹ�д��DB����

	return TRUE;
}


/**
 ********************************************************************
 * \brief �����ϵ��ļ��Ƿ����
 *  
 *  
 * \param LPCTSTR szFile : [in] 
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
BOOL CDiscImport::IsFileExistInMedia(LPCTSTR szFile)
{
	CString strFile = szFile;
	WIN32_FIND_DATA FindFileData;
	CString strTrace;

	m_hFindFileDcm = FindFirstFile(strFile, &FindFileData);
	if (INVALID_HANDLE_VALUE == m_hFindFileDcm) 
	{
		DWORD dwRet = GetLastError();
		if (87 == dwRet				// Tray open
			|| 21 == dwRet)			// Tray closed but no disc
		{
			// No disc anyway
			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);
			return FALSE;
		}
		else if (2 == dwRet			// have a disc but no DICOMDIR
				|| 1005 == dwRet)	// unknow filesystem, maybe a blank disc?
		{
			// The disc is not a back up disc
			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);
			return FALSE;
		}
		else
		{
			// 
			strTrace.Format(_T("%d == GetLastError() while FindFirstFile(...), file name: %s"), dwRet, strFile);
			PRINTTRACE_ERROR(strTrace)
			SetImportedSeriesDetailByDetailInfo(m_iCurrentImageIndex, DISCIMPORT_SDI_IMPORTING_FAILED);
			SetImportedSeriesProgress(m_iCurrentImageIndex, enumSeriesProgress_None);
			SetImportedSeriesState(m_iCurrentImageIndex, enumSeriesState_Failed);
			return FALSE;
		}
	} 
	else 
	{
		FindClose(m_hFindFileDcm);
		m_hFindFileDcm = INVALID_HANDLE_VALUE;
		return TRUE;
	}

}


/**
 ********************************************************************
 * \brief ���ݹ����Ϻ���DICOMͼ������ȡ������DICOMͼ����
 *  
 *  
 * \param CString& strRawFile : [in] 
 * \param CString& strProcDcmFile : [in] 
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
void CDiscImport::GetRawDcmFileNameByProcessedDcmFileNameInMedia(CString& strRawFile, CString& strProcDcmFile)
{
	//<< Z:\P0000001\...\P0000001 to Z:\P0000001\...\R0000001
	strRawFile = strProcDcmFile;
	int iIndex = strRawFile.ReverseFind(DICOM_DCM_PROC_IMAGE_PREFIX);
	if (-1 != iIndex)
	{
		strRawFile.SetAt(iIndex, DICOM_DCM_RAW_IMAGE_PREFIX);
	}
	else
	{
		strRawFile = _T("");
	}
}


/**
 ********************************************************************
 * \brief ���ݹ����Ϻ���DICOMͼ������ȡ��PS�ļ���
 *  
 *  
 * \param CString& strPSFile : [in] 
 * \param CString& strProcDcmFile : [in] 
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
void CDiscImport::GetPSFileNameByProcessedDcmFileNameInMedia(CString& strPSFile, CString& strProcDcmFile)
{
	//<< Z:\P0000001\...\P0000001 to Z:\P0000001\...\R0000001.pre
	strPSFile = strProcDcmFile + DICOM_DCM_PS_FILE_EXTEND_NAME;
}


/**
 ********************************************************************
 * \brief ���������Ϣ
 *  
 *  
 * \param LPCTSTR szJobID : [in] 
 * \param DiscImport_SeriesStruct** ppSeriesList : [in] 
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
BOOL CDiscImport::GetJobInfo(LPCTSTR szJobID, DiscImport_SeriesStruct** ppSeriesList, long* pLen)
{
	if (NULL == szJobID || NULL == pLen)
	{
		return FALSE;
	}

	if (CJobHandler::GetInstance()->GetDiscImportJobInfo(szJobID, ppSeriesList, pLen))
	{
		PRINTTRACE_INFO("CJobHandler::GetInstance()->GetJob(szJobID)")
		return TRUE;
	}
	else
	{
		PRINTTRACE_ERROR("CJobHandler::GetInstance()->GetJob(szJobID)")
		return FALSE;
	}
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
SubModuleState CDiscImport::GetSubModuleState()
{
	return m_SubModuleState;
}



/**
 ********************************************************************
 * \brief �ɼ�ǰ������
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
BOOL CDiscImport::HandleWorkBeforeAcq()
{
	BOOL bRet = TRUE;

	//<< ���� ��õ��������Ϣ ������ʹ����Ч
	if (!CancelGetImportDiscInfo())
	{
		bRet = FALSE;
		PRINTTRACE_ERROR("CancelGetImportDiscInfo")
	}

	return bRet;
}

/**
 ********************************************************************
 * \brief ȡ��һ��״̬Ϊ�����ύ��������������������񣻻��߶���shutshowʱǿ����ֹ�ĵ�������ȡ��δ��ɵ�������
 *  
 *  
 * \param PAJob* pJob : [in] 
 * 
 * \return BOOL  : 
 * 
 ********************************************************************
 * \skipline Modification record : 
 * \skipline Date		Modifier		Modification Content
 * \skipline 2009-3-23	Fan Zengfei 		Create function
 * \skipline           
 * \skipline           
 * \skipline           
*********************************************************************/
BOOL CDiscImport::CancelDiscImportJob(PAJob* pJob)
{
	if (NULL == pJob)
	{
		return FALSE;
	}

	if (enumJobType_DiscImportJob != pJob->enumJobType)
	{
		return FALSE;
	}

	DiscImportJobSettingsStruct* pSettingStruct = (DiscImportJobSettingsStruct*)pJob->pData;
	for (int i = 0; i < pSettingStruct->vtrImagesToBeImported.size(); ++i)
	{
		if (enumSeriesState_Waiting == pSettingStruct->vtrImagesToBeImported[i].enumState 
			|| enumSeriesState_Importing == pSettingStruct->vtrImagesToBeImported[i].enumState)
		{
			//<< state
			pSettingStruct->vtrImagesToBeImported[i].enumState = enumSeriesState_Cancelled;

			DiscImport_SeriesStateStruct* pStateStruct = new DiscImport_SeriesStateStruct;
			pStateStruct->bsJobID = pJob->strJobID.AllocSysString();
			pStateStruct->bsIndex = pSettingStruct->vtrImagesToBeImported[i].strIndex.AllocSysString();

			CString strState = DISCIMPORT_SERIES_STATE_CANCELLED;
			pStateStruct->bsState = _TT(strState).AllocSysString(); 

			Notify(NOTIFY_IMPORT_SERIES_STATE_CHANGED, (LPARAM)pStateStruct);

			//<< progress
			CString strProgress = _T("");
			pSettingStruct->vtrImagesToBeImported[i].strProgress = _TT(strProgress).AllocSysString(); 

			DiscImport_SeriesProgressStruct* pProgressStruct = new DiscImport_SeriesProgressStruct;
			pProgressStruct->bsJobID = pJob->strJobID.AllocSysString();
			pProgressStruct->bsIndex = pSettingStruct->vtrImagesToBeImported[i].strIndex.AllocSysString();
			pProgressStruct->bsProgress = pSettingStruct->vtrImagesToBeImported[i].strProgress.AllocSysString();
			
			Notify(NOTIFY_IMPORT_SERIES_PROGRESS_CHANGED, (LPARAM)pProgressStruct);

			//<< detail
			CString strDetailInfo = _T("");
			pSettingStruct->vtrImagesToBeImported[i].strDetailInfo = _TT(strDetailInfo); 

			DiscImport_SeriesDetailStruct* pDetailStruct = new DiscImport_SeriesDetailStruct;
			pDetailStruct->bsJobID = pJob->strJobID.AllocSysString();
			pDetailStruct->bsIndex = pSettingStruct->vtrImagesToBeImported[i].strIndex.AllocSysString();;
			pDetailStruct->bsDetailInfo = pSettingStruct->vtrImagesToBeImported[i].strDetailInfo.AllocSysString();

			Notify(NOTIFY_IMPORT_SERIES_DETIAL_CHANGED, (LPARAM)pDetailStruct);
		}
	}

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
void CDiscImport::NotifyUG(LONG iMessageID, UserGuidanceType enumUGType, UserGuidancePriority enumGUIPriority, BOOL bActive)
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
 * \brief ����NSubject���ص���Ϣ
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
LONG CDiscImport::HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam)
{	
	return E_OK;
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
void CDiscImport::SetSubModuleState(SubModuleState enumSubModuleState)
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
	Notify(NOTIFY_SUBMODULE_STATE_CHANGED, enumSubModule_DISCIMPORT, m_SubModuleState);

	CString strTrace;
	strTrace = _T("DiscImport SubModule state: ");
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
 * \brief �����ȡ���������Ϣ״̬����
 *  
 *  
 * \param LPCTSTR szState : [in] 
 * \param BOOL bReady : [in] 
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
void CDiscImport::ReportGetImportDiscInfoStateAndResult(LPCTSTR szState, BOOL bReady)
{
	BSTR bsInfo = CString(_TT(szState)).AllocSysString(); 
	Notify(NOTIFY_DISCIMPORT_GET_DISCINFO_STATE, (LPARAM)bsInfo);
	Notify(NOTIFY_DISCIMPORT_DISCINFO_READY, bReady);
}


/**
 ********************************************************************
 * \brief ��Ч������������Ϣ
 *  
 *  
 * \param DRDcmSysPatientTotalInfoStruct* pDcmPatientTotalInfo : [in] 
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
void CDiscImport::ValidatePatientTotalInfo(DRDcmSysPatientTotalInfoStruct* pDcmPatientTotalInfo)
{
// 
// 	//<< Study����ReferringPhisicianName�Ƿ�Ϊ��
// 	if (pDcmPatientTotalInfo->StudyInfo.g_strReferringPhysicianName.IsEmpty())
// 	{
// 		pDcmPatientTotalInfo->StudyInfo.g_strReferringPhysicianName = _T(" ");
// 		pDcmPatientTotalInfo->SeriesTotalInfo.SeriesInfo.g_strPerformingPhysicianName = _T(" ");
// 	}
// 
// 	//<< Study����OperatorName�Ƿ�Ϊ��
// 	if (pDcmPatientTotalInfo->StudyInfo.g_strOperatorName.IsEmpty())
// 	{
// 		pDcmPatientTotalInfo->StudyInfo.g_strOperatorName = _T(" ");
// 		pDcmPatientTotalInfo->SeriesTotalInfo.SeriesInfo.g_strOperatorName = _T(" ");
// 	}
}


/**
 ********************************************************************
 * \brief ���õ���ͼ��״̬
 *  
 *  
 * \param UINT uImageIndex : [in] 
 * \param DiscImport_ImageState enumState : [in] 
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
void CDiscImport::SetImportedSeriesState(UINT uImageIndex, DiscImport_ImageState enumState)
{
	((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].enumState = enumState;

	DiscImport_SeriesStateStruct* pStruct = new DiscImport_SeriesStateStruct;
	pStruct->bsJobID = m_pCurrentJob->strJobID.AllocSysString();
	pStruct->bsIndex = ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].strIndex.AllocSysString();

	CString strState;
	switch (enumState)
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
	pStruct->bsState = _TT(strState).AllocSysString(); 

	Notify(NOTIFY_IMPORT_SERIES_STATE_CHANGED, (LPARAM)pStruct);

}


/**
 ********************************************************************
 * \brief ���õ���ͼ�����
 *  
 *  
 * \param UINT uImageIndex : [in] 
 * \param DiscImport_SeriesProgress enumProgress : [in] 
 * \param DWORD dwProgress : [in] 
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
void CDiscImport::SetImportedSeriesProgress(UINT uImageIndex, DiscImport_SeriesProgress enumProgress, DWORD dwProgress)
{
	CString strProgress;
	switch (enumProgress)
	{
	case enumSeriesProgress_None:
		strProgress = _T("");
		break;
	case enumSeriesProgress_Percentage:
		strProgress.Format(_T("%d%%"), dwProgress);
		break;
	default:
		strProgress = _T("");
		break;
	}
	((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].strProgress = _TT(strProgress); 

	DiscImport_SeriesProgressStruct* pStruct = new DiscImport_SeriesProgressStruct;
	pStruct->bsJobID = m_pCurrentJob->strJobID.AllocSysString();
	pStruct->bsIndex = ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].strIndex.AllocSysString();
	pStruct->bsProgress = ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].strProgress.AllocSysString();
	
	Notify(NOTIFY_IMPORT_SERIES_PROGRESS_CHANGED, (LPARAM)pStruct);
}


/**
 ********************************************************************
 * \brief ���õ���ͼ����ϸ��Ϣ
 *  
 *  
 * \param UINT uImageIndex : [in] 
 * \param LPCTSTR szDetailInfo : [in] 
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
void CDiscImport::SetImportedSeriesDetailByDetailInfo(UINT uImageIndex, LPCTSTR szDetailInfo)
{
	CString strDetailInfo;
	strDetailInfo = szDetailInfo;

	((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].strDetailInfo = _TT(strDetailInfo); 


	DiscImport_SeriesDetailStruct* pStruct = new DiscImport_SeriesDetailStruct;
	pStruct->bsJobID = m_pCurrentJob->strJobID.AllocSysString();
	pStruct->bsIndex = ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].strIndex.AllocSysString();;
	pStruct->bsDetailInfo = ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].strDetailInfo.AllocSysString();

	Notify(NOTIFY_IMPORT_SERIES_DETIAL_CHANGED, (LPARAM)pStruct);
}


/**
 ********************************************************************
 * \brief ���õ���ͼ����ϸ��Ϣ
 *  
 *  
 * \param UINT uImageIndex : [in] 
 * \param LPCTSTR szDetailFormat : [in] 
 * \param LPCTSTR szPatientID : [in] 
 * \param LPCTSTR szPatientName : [in] 
 * \param LPCTSTR szStudyID : [in] 
 * \param LPCTSTR szSeriesID : [in] 
 * \param LPCTSTR szImageID : [in] 
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
void CDiscImport::SetImportedSeriesDetailByCompletedInfo(UINT uImageIndex, LPCTSTR szDetailFormat, LPCTSTR szPatientID, LPCTSTR szPatientName, LPCTSTR szStudyID, LPCTSTR szSeriesID, LPCTSTR szImageID)
{
	CString strDetailFormat = _TT(szDetailFormat); 
	((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].strDetailInfo.Format((LPCTSTR)strDetailFormat, szPatientID, szPatientName, szStudyID, szSeriesID, szImageID);


	DiscImport_SeriesDetailStruct* pStruct = new DiscImport_SeriesDetailStruct;
	pStruct->bsJobID = m_pCurrentJob->strJobID.AllocSysString();
	pStruct->bsIndex = ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].strIndex.AllocSysString();;
	pStruct->bsDetailInfo = ((DiscImportJobSettingsStruct*)m_pCurrentJob->pData)->vtrImagesToBeImported[uImageIndex].strDetailInfo.AllocSysString();

	Notify(NOTIFY_IMPORT_SERIES_DETIAL_CHANGED, (LPARAM)pStruct);
}


/**
 ********************************************************************
 * \brief �����ǰ����ͼ����Ϣ
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
void CDiscImport::ClearCurrentImportedImageInfo()
{

	if (INVALID_HANDLE_VALUE != m_hFindFileDcm)
	{
		FindClose(m_hFindFileDcm);
		m_hFindFileDcm = INVALID_HANDLE_VALUE;
	}

	if (NULL != m_pDcmParser)
	{
		delete m_pDcmParser;
		m_pDcmParser = NULL;
	}

	m_strPostDcmFileInMedia = _T("");

	CBSTROpt::FreePatientInfoStruct(&m_PatientInfo);
	CBSTROpt::FreeStudyInfoStruct(&m_StudyInfo);
	CBSTROpt::FreeSeriesInfoStruct(&m_SeriesInfo);
	CBSTROpt::FreeImageInfoStruct(&m_ImageInfo);
	CBSTROpt::FreePostProcessingInfo(&m_PostProcessInfo);

	m_strPatientUID = _T("");
	m_strStudyUID = _T("");
	m_strSeriesUID = _T("");
	m_strImageUID = _T("");

	m_bPatientExist = TRUE;
	m_bStudyExist = TRUE;
	m_bSeriesExist = TRUE;
	m_bImageExist = TRUE;

	m_strPatientFullPath = _T("");
	m_strStudyFullPath = _T("");
	m_strSeriesFullPath = _T("");
	m_strImageFullPath = _T("");
	m_strPostImageFullPath = _T("");
}


/**
 ********************************************************************
 * \brief ���δ��������ͼ��������Ϣ
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
BOOL CDiscImport::RemoveInfoOfUnproperlyImportedImage()
{

	BOOL bRet = TRUE;
	CString strTrace;

	if (!m_bPatientExist && !m_strPatientUID.IsEmpty())
	{
		// Remove from DB
		BOOL bPatientExistNow = FALSE;
		if (CDBController::GetInstance()->IsPatientUIDExistsInDB(m_strPatientUID, &bPatientExistNow))
		{
			if (bPatientExistNow)
			{
				if (!CDBController::GetInstance()->DeletePatientRecordFromDB(m_strPatientUID))
				{
					bRet = FALSE;
					strTrace.Format(_T("CDBController::DeletePatientRecordFromDB(), m_strPatientUID = %s"), m_strPatientUID);
					PRINTTRACE_ERROR(strTrace)
				}
			}
		}
		else
		{
			bRet = FALSE;
			strTrace.Format(_T("CDBController::IsPatientUIDExistsInDB(), m_strPatientUID = %s"), m_strPatientUID);
			PRINTTRACE_ERROR(strTrace)
		}

		// Remove from disk
		if (!m_strPatientFullPath.IsEmpty())
		{
			if (!CDirHandler::DeleteDir(m_strPatientFullPath))
			{
				bRet = FALSE;
				strTrace.Format(_T("CDirHandler::DeleteDir, m_strPatientFullPath = %s"), m_strPatientFullPath);
				PRINTTRACE_ERROR(strTrace)
			}
		}
	}
	else
	{
		// Patient is originally existed in DB, how about study?

		if (!m_bStudyExist && !m_strStudyUID.IsEmpty())
		{
			BOOL bStudyExistNow = FALSE;
			if (CDBController::GetInstance()->IsStudyUIDExistsInDB(m_strStudyUID, &bStudyExistNow))
			{
				if (bStudyExistNow)
				{
					if (!CDBController::GetInstance()->DeleteStudyRecordFromDB(m_strStudyUID))
					{
						bRet = FALSE;
						strTrace.Format(_T("CDBController::DeleteStudyRecordFromDB(), m_strStudyUID = %s"), m_strStudyUID);
						PRINTTRACE_ERROR(strTrace)
					}
				}
			}
			else
			{
				bRet = FALSE;
				strTrace.Format(_T("CDBController::IsStudyUIDExistsInDB(), m_strStudyUID = %s"), m_strStudyUID);
				PRINTTRACE_ERROR(strTrace)
			}

			// Remove from disk
			if (!m_strStudyFullPath.IsEmpty())
			{
				if (!CDirHandler::DeleteDir(m_strStudyFullPath))
				{
					bRet = FALSE;
					strTrace.Format(_T("CDirHandler::DeleteDir, m_strStudyFullPath = %s"), m_strStudyFullPath);
					PRINTTRACE_ERROR(strTrace)
				}
			}

		}
		else
		{
			// Study is Originally existed in DB, how about Series

			if (!m_bSeriesExist && !m_strSeriesUID.IsEmpty())
			{
				// Remove DB Info
				BOOL bSeriesExistNow = FALSE;
				if (CDBController::GetInstance()->IsSeriesUIDExistsInDB(m_strSeriesUID, &bSeriesExistNow))
				{
					if (bSeriesExistNow)
					{
						if (!CDBController::GetInstance()->DeleteSeriesRecordFromDB(m_strSeriesUID))
						{
							bRet = FALSE;
							strTrace.Format(_T("CDBController::DeleteSeriesRecordFromDB(), SeriesUID = %s"), m_strSeriesUID);
							PRINTTRACE_ERROR(strTrace)
						}
					}
				}
				else
				{
					bRet = FALSE;
					strTrace.Format(_T("CDBController::IsSeriesUIDExistsInDB(), m_strSeriesUID = %s"), m_strSeriesUID);
					PRINTTRACE_ERROR(strTrace)
				}

				// remove from disk
				if (!m_strSeriesFullPath.IsEmpty())
				{
					if (!CDirHandler::DeleteDir(m_strSeriesFullPath))
					{
						bRet = FALSE;
						strTrace.Format(_T("CDirHandler::DeleteDir, m_strSeriesFullPath = %s"), m_strSeriesFullPath);
						PRINTTRACE_ERROR(strTrace)
					}
				}

			}
			else
			{
				// Series is Originally existed in DB, how about Image
				if (!m_bImageExist && !m_strImageUID.IsEmpty())
				{
					// Remove DB Info
					BOOL bImageExistNow = FALSE;
					if (CDBController::GetInstance()->IsImageUIDExistsInDB(m_strImageUID, &bImageExistNow))
					{
						if (bImageExistNow)
						{
							// Delete Image info
							if (!CDBController::GetInstance()->DeleteImageRecordFromDB(m_strImageUID))
							{
								bRet = FALSE;
								strTrace.Format(_T("CDBController::DeleteImageRecordFromDB(), m_strImageUID = %s"), m_strImageUID);
								PRINTTRACE_ERROR(strTrace)
							}
						}
					}
					else
					{
						bRet = FALSE;
						strTrace.Format(_T("CDBController::IsImageUIDExistsInDB(), m_strImageUID = %s"), m_strImageUID);
						PRINTTRACE_ERROR(strTrace)
					}

					// remove from disk (Image, PostProcessed Image and PS file)
					if (!m_strImageFullPath.IsEmpty())
					{
						if (!CDirHandler::DeleteFile(m_strImageFullPath))
						{
							bRet = FALSE;
							strTrace.Format(_T("CDirHandler::DeleteDir, m_strImageFullPath = %s"), m_strImageFullPath);
							PRINTTRACE_ERROR(strTrace)
						}
					}
					
					//<< PostProcessed Dcm
					if (!m_strPostImageFullPath.IsEmpty())
					{
						if (!CDirHandler::DeleteFile(m_strPostImageFullPath))
						{
							bRet = FALSE;
							strTrace.Format(_T("CDirHandler::DeleteDir, m_strPostImageFullPath = %s"), m_strPostImageFullPath);
							PRINTTRACE_ERROR(strTrace)
						}
					}

					//<< PS file
					if (!m_strPostImagePSFullPath.IsEmpty())
					{
						if (!CDirHandler::DeleteFile(m_strPostImagePSFullPath))
						{
							bRet = FALSE;
							strTrace.Format(_T("CDirHandler::DeleteDir, m_strPostImagePSFullPath = %s"), m_strPostImagePSFullPath);
							PRINTTRACE_ERROR(strTrace)
						}
					}

				}
			}
		}
	}

	if (NULL != m_pDcmParser)
	{
		delete m_pDcmParser;
		m_pDcmParser = NULL;
	}
	

	ClearCurrentImportedImageInfo();

	return bRet;
}



// ConnectImageDiskResult CDiscImport::ConnectToRawImageDisk()
// {
// 	while (TRUE)
// 	{
// 		// ��ǰ�����Ƿ�ȡ��
// 		if (NULL != m_pCurrentJob && m_pCurrentJob->bCancelFlag)
// 		{
// 			return enumCntImageDiscResult_Break;
// 		}
// 
// 		BOOL bConnected = FALSE;
// 		if ((CISController::GetInstance())->ConnectDisk(&bConnected))
// 		{
// 			// Is Connected?
// 			if (bConnected)
// 			{
// //				PRINTTRACE_INFO("TRUE == (CISController::GetInstance())->ConnectDisk(&bConnected) and TRUE == bConnected")
// 				return enumCntImageDiscResult_OK;
// 			}
// 			else
// 			{
// 				PRINTTRACE_INFO("TRUE == (CISController::GetInstance())->ConnectDisk(&bConnected) But TRUE != bConnected")
// 				Sleep(IS_CONNECT_RAW_IMAGE_DISK_WAIT_TIME);
// 				continue;
// 			}
// 		}
// 		else
// 		{
// 			// error occured
// 			PRINTTRACE_ERROR("TRUE != (CISController::GetInstance())->ConnectDisk(&bConnected)")
// 			return enumCntImageDiscResult_Failed;
// 		}
// 	}
// }
// 
// void CDiscImport::EnableDisconnectToRawImageDisk()
// {
// 	CISController::GetInstance()->Enable();
// }
// 
// BOOL CDiscImport::DisConnectToRawImageDisk()
// {
// 	if (CISController::GetInstance()->DisConnectDisk())
// 	{
// 		PRINTTRACE_INFO("CISController::GetInstance()->DisConnectDisk()")
// 		return TRUE;
// 	}
// 	else
// 	{
// 		PRINTTRACE_ERROR("CISController::GetInstance()->DisConnectDisk()")
// 		return FALSE;
// 	}
// }

