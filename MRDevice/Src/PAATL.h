/* Time: <@(#)PAATL.h   2009-3-5 - 10:48:51   Fan Zengfei >
 *********************************************************************
 *  Philips-Neusoft Medical Systems Co. Corporation 
 *
 *  Project : 
 *
 *  File Name : PAATL.h
 *         
 *  Author : Fan Zengfei                          Date: 2009-3-5
 *
 *  Description : COM class for Printing&Archiving
 *
 *********************************************************************
 * Develop or modification record:
 *
 * $Log: $ 
 *
 *	1	2009-3-5 - 10:48:51		FanZF	Creation
 *
 *********************************************************************
 */

// PAATL.h : Declaration of the CPA

#ifndef __PA_H_
#define __PA_H_

#include "resource.h"       // main symbols
//#include "ASBasis.h"
#include "JobHandler.h"
#include "Printing.h"
#include "Burner.h"
#include "Transfer.h"
#include "DiscImport.h"
#include "WlMpps.h"
#include "FireMsgQueueMng.h"
#include "DBController.h"
#include "ISController.h"
#include "UserGuidanceOpt.h"
#include "PADataBaseOpt.h"
#include "DcmPartner.h"
#include "PALibConnectionPoint.h"
#include "LanguageIniOpt.h"

class CFireMsgQueueMng;

/////////////////////////////////////////////////////////////////////////////
// CPA
class ATL_NO_VTABLE CPA : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CPA, &CLSID_PA>,
	public IGeneralInterface,
	public IGeneralSys,
	public IPing,
	public IUserWorkingMode,
	public IPAGeneral,
	public IPAPrint,
	public IPABurn,
	public IPATransfer,
	public IPADiscImport,
	public IPAWLMPPS,
	public CProxyIPABurnEvent<CPA>,
	public CProxyIGeneralEvent<CPA>,
	public CProxyIPAGeneralEvent<CPA>,
	public CProxyIPAPrintEvent<CPA>,
	public CProxyIPATransferEvent<CPA>,
	public CProxyIPADiscImportEvent<CPA>,
	public CProxyIPAWLMPPSEvent<CPA>,
	public CProxyIUserGuidanceEvent<CPA>,
	public IConnectionPointContainerImpl<CPA>,
	public NObserver
	
{
public:
	CPA();
	virtual ~CPA();

DECLARE_REGISTRY_RESOURCEID(IDR_PA1)
DECLARE_NOT_AGGREGATABLE(CPA)
DECLARE_CLASSFACTORY_SINGLETON(CPA)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPA)
	COM_INTERFACE_ENTRY(IPAGeneral)
	COM_INTERFACE_ENTRY(IPAPrint)
	COM_INTERFACE_ENTRY(IPABurn)
	COM_INTERFACE_ENTRY(IPATransfer)
	COM_INTERFACE_ENTRY(IPADiscImport)
	COM_INTERFACE_ENTRY(IPAWLMPPS)
	COM_INTERFACE_ENTRY(IGeneralSys)
	COM_INTERFACE_ENTRY(IGeneralInterface)
	COM_INTERFACE_ENTRY(IPing)
	COM_INTERFACE_ENTRY(IUserWorkingMode)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()


BEGIN_CONNECTION_POINT_MAP(CPA)
	CONNECTION_POINT_ENTRY(IID_IPAGeneralEvent)
	CONNECTION_POINT_ENTRY(IID_IPAPrintEvent)
	CONNECTION_POINT_ENTRY(IID_IPABurnEvent)
	CONNECTION_POINT_ENTRY(IID_IPATransferEvent)
	CONNECTION_POINT_ENTRY(IID_IPADiscImportEvent)
	CONNECTION_POINT_ENTRY(IID_IPAWLMPPSEvent)
	CONNECTION_POINT_ENTRY(IID_IUserGuidanceEvent)
	CONNECTION_POINT_ENTRY(IID_IGeneralEvent)
END_CONNECTION_POINT_MAP()

// IPA
public :
	//IGeneralSys
	STDMETHOD(ShutDown)();
	STDMETHOD(StartUp)();

	//IPing
	STDMETHOD(Ping)();

	//General
	STDMETHOD(GetStartupResult)(STARTUPRESULT* pResult);
	STDMETHOD(GetWorkState)(WORKSTATE* pState);
	STDMETHOD(GetError)(INT* pError);

	//IUserWorkingMode
    STDMETHOD(Logout)();
    STDMETHOD(Login)();

	//IPAGeneral
	STDMETHOD(GetPatientStudySeriesImageOccupyState)(PatientAdminUIDType enumUIDType, long lUIDNum, BSTR* pbsUIDList, BOOL* pbOccupied);
	STDMETHOD(ReportUserGuidance)(LONG iMessageID, USER_GUIDANCE_TYPE enumType, USER_GUIDANCE_PRIORITY enumPrior, BOOL bActive);

	STDMETHOD(GetJobList)(JobInfo** ppJobList, long* pLen);
	STDMETHOD(MoveJob)(BSTR bsJobID, BOOL bForward);
	STDMETHOD(CancelJobs)(BSTR* pbsJobIDs, long lNum);
	STDMETHOD(DeleteJobs)(BSTR* pbsJobIDs, long lNum);
	
	STDMETHOD(GetHistoryJobCount)(DWORD* pdwCount);
	STDMETHOD(GetHistoryJobs)(DWORD dwStartIndex, DWORD* pdwCount, JobInfo** ppJobList);
	STDMETHOD(GetHistoryJobInfo)(BSTR bsJobID, JobInfo* pJobInfo);
	STDMETHOD(GetHistoryJobPSSIInfo)(BSTR bsJobID, long* pLen, PSSIInfo** ppPSSIList);
	STDMETHOD(GetHistoryJobNetworkNodeInfo)(BSTR bsJobID, long* pLen, NetworkNode** ppNodeList);
	STDMETHOD(GetHistoryJobDetailInfo)(BSTR bsJobID, long* pLen, JobDetailStruct** ppDetailList);
	STDMETHOD(GetHistoryJobDiscImportImageInfo)(BSTR bsJobID, long* pLen, DiscImport_SeriesStruct** ppDISSList);
	STDMETHOD(DeleteHistoryJobs)(long lNum, BSTR* pbsJobIDList);
	STDMETHOD(DeleteAllHistoryJobs)();

	STDMETHOD(CompactDB)(BOOL bBackUp);

	// Print
    STDMETHOD(Print)(long lUIDNum, BSTR* pbsImageUIDList);
	STDMETHOD(GetPrintJobList)(JobInfo** ppJobInfoList, long* pLen);
	STDMETHOD(ShowFCProgressBar)(BOOL bShow);
	
	STDMETHOD(GetPrintNetworkNodes)(NetworkNode** ppNodesList, long* pLen);
	STDMETHOD(GetPrintErrorMsg)(int iErrCode, BSTR* bsErrMsg);
	
	STDMETHOD(GetPrintSubModuleState)(SubModuleState* pSubModuleState);

	// Burn
	STDMETHOD(BurnPrepare)(long lUIDNum, BSTR* pbsUIDList, PatientAdminUIDType enumUIDType);
	STDMETHOD(CancelBurnPrepare)();

	STDMETHOD(BurnByPA)(BurnJobSettingsByPA* pBurnJobSettingsByPA);
	STDMETHOD(GetBurnJobInfo)(BSTR bsJobID, JobInfo* pJobInfo, PSSIInfo** ppPSSIList, long* pPSSILen, JobDetailStruct** ppDetailList, long* pDetailLen);
	
	STDMETHOD(GetDevices)(BSTR** ppbsDevices, long* pLen);
	STDMETHOD(GetCurrentDeviceMediaInfo)();

	STDMETHOD(GetEstimatedSize)(BOOL bBMP, BOOL bJPEG, unsigned long* plSizeInMega);

	STDMETHOD(EnableCheckDevice)(BOOL bCheck);
	STDMETHOD(SetBurnMediaCheckRetry)(BOOL bRetry);

	STDMETHOD(SetBurnDevice)(BSTR bsDeviceName);

	STDMETHOD(IsUnfinishedBurnJobExist)(BOOL* pbExist);

	STDMETHOD(GetBurnErrorMsg)(int iErrCode, BSTR* bsErrMsg);

	STDMETHOD(GetBurnSubModuleState)(SubModuleState* pSubModuleState);

	// Transfer
    STDMETHOD(AutoTransfer)(BSTR bsUID, PatientAdminUIDType enumUIDType);
	STDMETHOD(ManualTransfer)(long lUIDNum, BSTR* pbsUIDList, PatientAdminUIDType enumUIDType, TransferJobSettingsByUID* pTransferJobSettings);
	STDMETHOD(ManualTransferWithMultiServers)(long lUIDNum, BSTR* pbsUIDList, PatientAdminUIDType enumUIDType, long lServerNum, TransferJobSettingsByUID* pTransferJobSettings);

	STDMETHOD(GetSendJobInfo)(BSTR bsJobID, JobInfo* pJobInfo, PSSIInfo** ppPSSIList, long* pPSSILen, NetworkNode** ppNodeList, long* pNodeLen, JobDetailStruct** ppDetailList, long* pDetailLen);

	STDMETHOD(GetTransferSubModuleState)(SubModuleState* pSubModuleState);

	STDMETHOD(IsUnfinishedTrnasferJobExist)(BOOL* pbExist);

	STDMETHOD(GetAutoServers)(NetworkNode** ppServers, long* pLen);
	STDMETHOD(IsAutoSendValid)(BOOL* pbValid);
	STDMETHOD(SetAutoServers)(NetworkNode* pServers, long lLen);
	STDMETHOD(GetManualServers)(NetworkNode** ppServers, long* pLen);
	STDMETHOD(SetManualServers)(NetworkNode* pServers, long lLen);

	STDMETHOD(ConnectTest)(NetworkNode* pServer, BOOL* pbResult);
	

	// DiscImport
	STDMETHOD(GetDiscImportDevices)(BSTR** ppbsDevices, long* pLen);
	STDMETHOD(GetImportDiscInfoNotify)(BSTR bsDevice);
	STDMETHOD(GetImportDiscInfo)(DiscImportPatientInfo** ppPatients,
								long* pPatientNum,
								DiscImportStudyInfo** ppStudies,
								long* pStudyNum,
								DiscImportSeriesInfo** ppSeries,
								long* pSeriesNum,
								DiscImportImageInfo** ppImages,
								long* pImageNum);
	STDMETHOD(CancelGetImportDiscInfo)();

	STDMETHOD(DiscImport)(long lUIDNum, BSTR* pbsUIDList, PatientAdminUIDType enumUIDType);

	STDMETHOD(GetDiscImportJobInfo)(BSTR bsJobID, DiscImport_SeriesStruct** ppSeriesList, long* pLen);

	STDMETHOD(IsUnfinishedDiscImportJobExist)(BOOL* pbExist);

	STDMETHOD(GetDiscImportSubModuleState)(SubModuleState* pSubModuleState);

	// Worklist and MPPS
	STDMETHOD(GetWlMppsSubModuleState)(SubModuleState* pSubModuleState);
	
	STDMETHOD(GetWorkList)();
	STDMETHOD(RefreshWorkList)(WorkListQueryCond* pWorkListQueryCond);
	STDMETHOD(GetImportPatientStudyInfo)(BSTR bsStudyInstanceUID, WLPatientStudyStruct* pStruct);
	STDMETHOD(IsStudyImported)(BSTR bsStudyInstanceUID, WLPatientStudyStatusInDB* pStatus);
	STDMETHOD(StudyImported)(BSTR bsStudyInstanceUID);
	STDMETHOD(DeleteAllImportedStudyRecords)();

	STDMETHOD(IsMPPSValid)(BOOL* pbValid);
	STDMETHOD(IsSetMPPSStatusEnabled)(BSTR bsStudyUID, BOOL* pbEnabled);
	STDMETHOD(GetStudyMPPSStatus)(BSTR bsStudyUID, WorkListStatus* penumStatus);
	STDMETHOD(SetMPPSStatus)(BSTR bsStudyUID, WorkListStatus enumStatus);

	STDMETHOD(IsWorkListWorking)(BOOL* pbWorking);
	STDMETHOD(IsMppsWorking)(BOOL* pbWorking);

	STDMETHOD(IsClosingStudyMPPS)(BSTR bsStudyUID, BOOL* pbClosing);
	STDMETHOD(IsSettingPatientOrStudyMPPS)(long lUIDNum, BSTR* pbsUIDs, PatientAdminUIDType enumUIDType, BOOL* pbSetting);
	
	STDMETHOD(GetWlServers)(NetworkNode** ppServers, long* pLen);
	STDMETHOD(SetWlServers)(NetworkNode* pServers, long lLen);
	STDMETHOD(WlServerConnectTest)(NetworkNode* pServer, BOOL* pbResult);

	STDMETHOD(GetMppsServers)(NetworkNode** ppServers, long* pLen);
	STDMETHOD(SetMppsServers)(NetworkNode* pServers, long lLen);
	STDMETHOD(MppsServerConnectTest)(NetworkNode* pServer, BOOL* pbResult);

	//设置、获取自动发送的状态  [ GaoXing 10/22/2009]
	STDMETHOD(SetEnableAutoTransferStatus)(BOOL bEnable);
	STDMETHOD(GetEnableAutoTransferStatus)(BOOL *bEnable);

	//设置、获取是否询问用户进行自动发送 [ GaoXing 1/11/2010]
	STDMETHOD(SetAskforAutoTransfer)(BOOL bAskfor);
	STDMETHOD(GetAskforAutoTransfer)(BOOL *bAskfor);

	
	BOOL StartUpProc();

	BOOL HandleBackGroundJobAcq();
	BOOL ResumeBackGroundJobAcq();

protected:
	virtual LONG HandleMessage(NSubject* pSubject, UINT uMessage, LPARAM lParam, WPARAM wParam);

private:

	BOOL SetStartUpResult(STARTUPRESULT Result);
	void GetErrorMsg(int iErrCode, BSTR* bsErrMsg);
	
	BOOL ShutDownProc();
	BOOL PushMsgToFireMsgQueue(FireMsgNode& MsgNode);
	
	BOOL SetWorkState(WORKSTATE State);
	
	BOOL IsInterfaceValid();
	BOOL IsPrintInterfaceValid();
	BOOL IsBurnInterfaceValid();
	BOOL IsTransferInterfaceValid();
	BOOL IsDiscImportInterfaceValid();
	BOOL IsWlMppsInterfaceValid();


private:

	CJobHandler*		m_pJobHandlerInstance;

	CPrinting*			m_pPrintInstance;
	CBurner*			m_pBurnInstance;
	CTransfer*			m_pTransferInstance;
	CDiscImport*		m_pDiscImportInstance;
	CWlMpps*			m_pWlMppsInstance;

	CUserGuidanceOpt*	m_pUGOptInstance;
	CDcmPartner			m_DcmPartner;

	CISController*		m_pISControllerInstance;
	CDBController*		m_pDBControllerInstance;

	CPADataBaseOpt*		m_pPADBOptInstance;

	CFireMsgQueueMng*	m_pFireMsgInstance;

	HANDLE				m_StartUpThreadHandle;

	CCriticalSection	m_CSLockInterface;
	CCriticalSection	m_CSLockModuleState;

	CCriticalSection	m_CSLockAcqEvent;

	STARTUPRESULT		m_StartUpResult;
	WORKSTATE			m_WorkState;

	CLanguageIniOpt*	m_pLanguageIniOptInstance;

};

#endif //__PA_H_
