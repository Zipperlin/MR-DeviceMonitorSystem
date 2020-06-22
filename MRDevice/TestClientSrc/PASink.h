// PASink.h: interface for the CPASink class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_PASINK_H__FB969BDC_929F_4297_A9AB_EB403748DEB6__INCLUDED_)
#define AFX_PASINK_H__FB969BDC_929F_4297_A9AB_EB403748DEB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPASink : public IPAGeneralEvent,
				public IPAPrintEvent,
				public IPABurnEvent,
				public IPATransferEvent,
				public IPADiscImportEvent,
				public IPAWLMPPSEvent,
				public IGeneralEvent,
				public IUserGuidanceEvent
{
public:
	CPASink();
	virtual ~CPASink();
	DWORD				m_dwCookie;			//Record the cookie of link
	IUnknown*			m_ICallBack;		//Define the interface for callback
	IConnectionPoint*	m_pConnectionPoint;	//Record the connection point for link

	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall QueryInterface(REFIID iid, void** ppv);

	//Create a link to the server
	BOOL SetConnection(REFCLSID rclsid, REFIID callid);	
	//Release the link to the server
	BOOL ReleaseConnection();

	// IPAGeneralEvent
	STDMETHOD(ReportJobQueueChanged)();
	STDMETHOD(ReportJobState)(BSTR bsJobID, BSTR bsJobState);
	STDMETHOD(ReportJobPhase)(BSTR bsJobID, BSTR bsJobPhase);
	STDMETHOD(ReportJobProgress)(BSTR bsJobID, BSTR bsJobProgress);
	STDMETHOD(ReportJobDetail)(JobDetailStruct* pJobDetail);

	// IPAPrintEvent
	STDMETHOD(ReportPrintWorkStatus)(/*[in]*/SubModule enumSubModule, /*[in]*/SubModuleState enumSubUnitStatus);
	STDMETHOD(ReportPrintFilmComposerStatus)(FilmComposerStatus enumFilmComposerStatus);
	STDMETHOD(ReportPrintFilmComposerStartUp)();
	STDMETHOD(ReportEnableFilmComposer)(BOOL bEnable);

	// IPABurnEvent
	STDMETHOD(ReportBurnWorkStatus)(/*[in]*/SubModule enumSubModule, /*[in]*/SubModuleState enumSubUnitStatus);
	STDMETHOD(ReportBurnDeviceStatusChanged)();
	STDMETHOD(ReportBurnErrorCode)(int iErrCode);
	STDMETHOD(ReportBurnPhase)(BSTR bsBurnPhase);
//	STDMETHOD(ReportBurnProgress)(DWORD dwProgressPercent);
	STDMETHOD(ReportBurnLogLine)(BSTR bsBurnLogLine);
	STDMETHOD(ReportBurnFileConflict)(BSTR bsFirstFileName, BSTR bsSecondFileName);

	STDMETHOD(ReportBurnPatientList)(long lItemNum, BurnPatientInfoStruct* pBurnPatientList);
	STDMETHOD(ReportBurnStudyList)(long lItemNum, BurnStudyInfoStruct* pBurnStudyList);
	STDMETHOD(ReportBurnSeriesList)(long lItemNum, BurnSeriesInfoStruct* pBurnSeriesList);
	STDMETHOD(ReportBurnImageList)(long lItemNum, BurnImageInfoStruct* pBurnImageList);

	STDMETHOD(ReportDeviceSpeedInfo)(long lItemNum, BurnSpeedInfo* pSpeedInfo);
	STDMETHOD(ReportMediaInfo)(BurnMediaInfo* pMediaInfo);
	STDMETHOD(ReportBurnMediaNotReady)(BSTR bsInfo);

	// IPATransferEvent
	STDMETHOD(ReportTransferWorkStatus)(/*[in]*/SubModule enumSubModule, /*[in]*/SubModuleState enumSubUnitStatus);
	STDMETHOD(ReportUITransferChangeDB)(/*[in]*/BSTR bstPatientUID,  /*[in]*/BSTR bstStudyUID);


	// IPADiscImport
	STDMETHOD(ReportDiscImportWorkStatus)(SubModule enumSubModule, SubModuleState enumSubModuleStatus);

	STDMETHOD(ReportDiscImportDiscInfo)(BOOL bReady);
	STDMETHOD(ReportDiscImportDiscInfoState)(BSTR bsState);
	
	STDMETHOD(ReportDiscImportSeriesStateChanged)(DiscImport_SeriesStateStruct* pState);
	STDMETHOD(ReportDiscImportSeriesProgressChanged)(DiscImport_SeriesProgressStruct* pProgress);
	STDMETHOD(ReportDiscImportSeriesDetailChanged)(DiscImport_SeriesDetailStruct* pDetail);
	STDMETHOD(ReportDiscImportOneImageImported)();
	STDMETHOD(ReportDiscImportOneJobFinished)();

	// IPAWlMppsEvent
	STDMETHOD(ReportWlMppsWorkStatus)(SubModule enumSubModule, SubModuleState enumSubModuleStatus);
	STDMETHOD(ReportWorkList)(long lItemNum, WorkListStruct* pWorkList);
	STDMETHOD(ReportSetMPPSStatusFinished)(MppsSetResult* pResult);
	STDMETHOD(ReportMPPSStatusChanged)(BSTR bsStudyUID, WorkListStatus enumStatus);

	// IGeneralEvent
	STDMETHOD(ReportStartupResult)(STARTUPRESULT enumResult);
	STDMETHOD(ReportWorkState)(WORKSTATE enumState);	
	STDMETHOD(ReportError)(INT iError);

	// IUserGuidanceEvent
	STDMETHOD(UserGuidanceReporting)(LONG iMessageID, USER_GUIDANCE_TYPE enumType, USER_GUIDANCE_PRIORITY enumPrior, BOOL bActive);

};

#endif // !defined(AFX_PASINK_H__FB969BDC_929F_4297_A9AB_EB403748DEB6__INCLUDED_)
