#ifndef __PALIBCONNECTIONPOINT_H__
#define __PALIBCONNECTIONPOINT_H__

template <class T>
class CProxyIGeneralEvent : public IConnectionPointImpl<T, &IID_IGeneralEvent, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_ReportStartupResult(_STARTUPRESULT enumResult)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IGeneralEvent* pIGeneralEvent = reinterpret_cast<IGeneralEvent*>(sp.p);
			if (pIGeneralEvent != NULL)
				ret = pIGeneralEvent->ReportStartupResult(enumResult);
		}	return ret;
	
	}
	HRESULT Fire_ReportWorkState(_WORKSTATE enumState)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IGeneralEvent* pIGeneralEvent = reinterpret_cast<IGeneralEvent*>(sp.p);
			if (pIGeneralEvent != NULL)
				ret = pIGeneralEvent->ReportWorkState(enumState);
		}	return ret;
	
	}
	HRESULT Fire_ReportError(INT iError)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IGeneralEvent* pIGeneralEvent = reinterpret_cast<IGeneralEvent*>(sp.p);
			if (pIGeneralEvent != NULL)
				ret = pIGeneralEvent->ReportError(iError);
		}	return ret;
	
	}
};

template <class T>
class CProxyIPAGeneralEvent : public IConnectionPointImpl<T, &IID_IPAGeneralEvent, CComDynamicUnkArray>
{
//	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_ReportJobState(BSTR bsJobID, BSTR bsJobSate)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAGeneralEvent* pIPAGeneralEvent = reinterpret_cast<IPAGeneralEvent*>(sp.p);
			if (pIPAGeneralEvent != NULL)
				ret = pIPAGeneralEvent->ReportJobState(bsJobID, bsJobSate);
		}	return ret;
	
	}

	HRESULT Fire_ReportJobPhase(BSTR bsJobID, BSTR bsJobPhase)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAGeneralEvent* pIPAGeneralEvent = reinterpret_cast<IPAGeneralEvent*>(sp.p);
			if (pIPAGeneralEvent != NULL)
				ret = pIPAGeneralEvent->ReportJobPhase(bsJobID, bsJobPhase);
		}	return ret;
	
	}

	HRESULT Fire_ReportJobProgress(BSTR bsJobID, BSTR bsJobProgress)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAGeneralEvent* pIPAGeneralEvent = reinterpret_cast<IPAGeneralEvent*>(sp.p);
			if (pIPAGeneralEvent != NULL)
				ret = pIPAGeneralEvent->ReportJobProgress(bsJobID, bsJobProgress);
		}	return ret;
	
	}

	HRESULT Fire_ReportJobDetail(JobDetailStruct* JobDetail)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAGeneralEvent* pIPAGeneralEvent = reinterpret_cast<IPAGeneralEvent*>(sp.p);
			if (pIPAGeneralEvent != NULL)
				ret = pIPAGeneralEvent->ReportJobDetail(JobDetail);
		}	return ret;
	
	}

	HRESULT Fire_ReportJobQueueChanged()
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAGeneralEvent* pIPAGeneralEvent = reinterpret_cast<IPAGeneralEvent*>(sp.p);
			if (pIPAGeneralEvent != NULL)
				ret = pIPAGeneralEvent->ReportJobQueueChanged();
		}	return ret;
	
	}



};

template <class T>
class CProxyIPAPrintEvent : public IConnectionPointImpl<T, &IID_IPAPrintEvent, CComDynamicUnkArray>
{
//	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_ReportPrintWorkStatus(SubModule enumSubModule, SubModuleState enumSubModuleStatus)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAPrintEvent* pIPAPrintEvent = reinterpret_cast<IPAPrintEvent*>(sp.p);
			if (pIPAPrintEvent != NULL)
				ret = pIPAPrintEvent->ReportPrintWorkStatus(enumSubModule, enumSubModuleStatus);
		}	return ret;
	
	}


	HRESULT Fire_ReportPrintFilmComposerStatus(FilmComposerStatus enumFilmComposerStatus)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAPrintEvent* pIPAPrintEvent = reinterpret_cast<IPAPrintEvent*>(sp.p);
			if (pIPAPrintEvent != NULL)
				ret = pIPAPrintEvent->ReportPrintFilmComposerStatus(enumFilmComposerStatus);
		}	return ret;
	
	}

	HRESULT Fire_ReportPrintFilmComposerStartUp()
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAPrintEvent* pIPAPrintEvent = reinterpret_cast<IPAPrintEvent*>(sp.p);
			if (pIPAPrintEvent != NULL)
				ret = pIPAPrintEvent->ReportPrintFilmComposerStartUp();
		}	return ret;
	
	}

	HRESULT Fire_ReportEnableFilmComposer(BOOL bEnable)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAPrintEvent* pIPAPrintEvent = reinterpret_cast<IPAPrintEvent*>(sp.p);
			if (pIPAPrintEvent != NULL)
				ret = pIPAPrintEvent->ReportEnableFilmComposer(bEnable);
		}	return ret;
	
	}

};


template <class T>
class CProxyIPABurnEvent : public IConnectionPointImpl<T, &IID_IPABurnEvent, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_ReportBurnWorkStatus(SubModule enumSubModule, SubModuleState enumSubModuleStatus)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnWorkStatus(enumSubModule, enumSubModuleStatus);
		}	return ret;
	
	}


	HRESULT Fire_ReportBurnDeviceStatusChanged()
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnDeviceStatusChanged();
		}	return ret;
	
	}

	HRESULT Fire_ReportBurnErrorCode(int iErrCode)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnErrorCode(iErrCode);
		}	return ret;
	
	}


	HRESULT Fire_ReportBurnPhase(BSTR bsBurnPhase)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnPhase(bsBurnPhase);
		}	return ret;
	
	}


	HRESULT Fire_ReportBurnLogLine(BSTR bsBurnLogLine)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnLogLine(bsBurnLogLine);
		}	return ret;
	
	}

	HRESULT Fire_ReportBurnFileConflict(BSTR bsFirstFileName, BSTR bsSecondFileName)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnFileConflict(bsFirstFileName, bsSecondFileName);
		}	return ret;
	
	}


	HRESULT Fire_ReportBurnPatientList(long lItemNum, BurnPatientInfoStruct* pBurnPatientList)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnPatientList(lItemNum, pBurnPatientList);
		}	return ret;
	
	}

	HRESULT Fire_ReportBurnStudyList(long lItemNum, BurnStudyInfoStruct* pBurnStudyList)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnStudyList(lItemNum, pBurnStudyList);
		}	return ret;
	
	}

	HRESULT Fire_ReportBurnSeriesList(long lItemNum, BurnSeriesInfoStruct* pBurnSeriesList)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnSeriesList(lItemNum, pBurnSeriesList);
		}	return ret;
	
	}

	HRESULT Fire_ReportBurnImageList(long lItemNum, BurnImageInfoStruct* pBurnImageList)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnImageList(lItemNum, pBurnImageList);
		}	return ret;
	
	}

	HRESULT Fire_ReportDeviceSpeedInfo(long lItemNum, BurnSpeedInfo* pSpeedInfo)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportDeviceSpeedInfo(lItemNum, pSpeedInfo);
		}	return ret;
	
	}

	HRESULT Fire_ReportMediaInfo(BurnMediaInfo* pMediaInfo)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportMediaInfo(pMediaInfo);
		}	return ret;
	
	}
	
	HRESULT Fire_ReportBurnMediaNotReady(BSTR bsInfo)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPABurnEvent* pIPABurnEvent = reinterpret_cast<IPABurnEvent*>(sp.p);
			if (pIPABurnEvent != NULL)
				ret = pIPABurnEvent->ReportBurnMediaNotReady(bsInfo);
		}	return ret;
	
	}

};

template <class T>
class CProxyIPATransferEvent : public IConnectionPointImpl<T, &IID_IPATransferEvent, CComDynamicUnkArray>
{
//	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_ReportTransferWorkStatus(SubModule enumSubModule, SubModuleState enumSubModuleStatus)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPATransferEvent* pIPATransferEvent = reinterpret_cast<IPATransferEvent*>(sp.p);
			if (pIPATransferEvent != NULL)
				ret = pIPATransferEvent->ReportTransferWorkStatus(enumSubModule, enumSubModuleStatus);
		}	return ret;
	
	}

	HRESULT Fire_ReportUITransferChangeDB(BSTR bstPatientUID, BSTR bstStudyUID)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		PRINTTRACE_INFO("enter Fire_ReportUITransferChangeDB");
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPATransferEvent* pIPATransferEvent = reinterpret_cast<IPATransferEvent*>(sp.p);
			if (pIPATransferEvent != NULL)
			{
				PRINTTRACE_INFO("pIPATransferEvent->ReportUITransferChangeDB");
				ret = pIPATransferEvent->ReportUITransferChangeDB(bstPatientUID, bstStudyUID);
			}
		}	return ret;
	
	}

};


template <class T>
class CProxyIPADiscImportEvent : public IConnectionPointImpl<T, &IID_IPADiscImportEvent, CComDynamicUnkArray>
{
//	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_ReportDiscImportWorkStatus(SubModule enumSubModule,SubModuleState enumSubModuleStatus)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPADiscImportEvent* pIPADiscImportEvent = reinterpret_cast<IPADiscImportEvent*>(sp.p);
			if (pIPADiscImportEvent != NULL)
				ret = pIPADiscImportEvent->ReportDiscImportWorkStatus(enumSubModule, enumSubModuleStatus);
		}	return ret;
	}

	HRESULT Fire_ReportDiscImportDiscInfo(BOOL bReady)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPADiscImportEvent* pIPADiscImportEvent = reinterpret_cast<IPADiscImportEvent*>(sp.p);
			if (pIPADiscImportEvent != NULL)
				ret = pIPADiscImportEvent->ReportDiscImportDiscInfo(bReady);
		}	return ret;
	
	}

	HRESULT Fire_ReportDiscImportDiscInfoState(BSTR bsState)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPADiscImportEvent* pIPADiscImportEvent = reinterpret_cast<IPADiscImportEvent*>(sp.p);
			if (pIPADiscImportEvent != NULL)
				ret = pIPADiscImportEvent->ReportDiscImportDiscInfoState(bsState);
		}	return ret;
	
	}


	HRESULT Fire_ReportDiscImportSeriesStateChanged(DiscImport_SeriesStateStruct* pState)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPADiscImportEvent* pIPADiscImportEvent = reinterpret_cast<IPADiscImportEvent*>(sp.p);
			if (pIPADiscImportEvent != NULL)
				ret = pIPADiscImportEvent->ReportDiscImportSeriesStateChanged(pState);
		}	return ret;
	
	}

	
	HRESULT Fire_ReportDiscImportSeriesProgressChanged(DiscImport_SeriesProgressStruct* pProgress)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPADiscImportEvent* pIPADiscImportEvent = reinterpret_cast<IPADiscImportEvent*>(sp.p);
			if (pIPADiscImportEvent != NULL)
				ret = pIPADiscImportEvent->ReportDiscImportSeriesProgressChanged(pProgress);
		}	return ret;
	
	}


	HRESULT Fire_ReportDiscImportSeriesDetailChanged(DiscImport_SeriesDetailStruct* pDetail)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPADiscImportEvent* pIPADiscImportEvent = reinterpret_cast<IPADiscImportEvent*>(sp.p);
			if (pIPADiscImportEvent != NULL)
				ret = pIPADiscImportEvent->ReportDiscImportSeriesDetailChanged(pDetail);
		}	return ret;
	
	}

	HRESULT Fire_ReportDiscImportOneImageImported()
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPADiscImportEvent* pIPADiscImportEvent = reinterpret_cast<IPADiscImportEvent*>(sp.p);
			if (pIPADiscImportEvent != NULL)
				ret = pIPADiscImportEvent->ReportDiscImportOneImageImported();
		}	return ret;
	
	}

	HRESULT Fire_ReportDiscImportOneJobFinished()
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPADiscImportEvent* pIPADiscImportEvent = reinterpret_cast<IPADiscImportEvent*>(sp.p);
			if (pIPADiscImportEvent != NULL)
				ret = pIPADiscImportEvent->ReportDiscImportOneJobFinished();
		}	return ret;
	
	}

};


template <class T>
class CProxyIPAWLMPPSEvent : public IConnectionPointImpl<T, &IID_IPAWLMPPSEvent, CComDynamicUnkArray>
{
//	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_ReportWlMppsWorkStatus(SubModule enumSubModule,SubModuleState enumSubModuleStatus)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAWLMPPSEvent* pIPAWLMPPSEvent = reinterpret_cast<IPAWLMPPSEvent*>(sp.p);
			if (pIPAWLMPPSEvent != NULL)
				ret = pIPAWLMPPSEvent->ReportWlMppsWorkStatus(enumSubModule, enumSubModuleStatus);
		}	return ret;
	}

	HRESULT Fire_ReportWorkList(long lItemNum, WorkListStruct* pWorkList)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAWLMPPSEvent* pIPAWLMPPSEvent = reinterpret_cast<IPAWLMPPSEvent*>(sp.p);
			if (pIPAWLMPPSEvent != NULL)
				ret = pIPAWLMPPSEvent->ReportWorkList(lItemNum, pWorkList);
		}	return ret;
	}

	HRESULT Fire_ReportSetMPPSStatusFinished(MppsSetResult* pResult)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAWLMPPSEvent* pIPAWLMPPSEvent = reinterpret_cast<IPAWLMPPSEvent*>(sp.p);
			if (pIPAWLMPPSEvent != NULL)
				ret = pIPAWLMPPSEvent->ReportSetMPPSStatusFinished(pResult);
		}	return ret;
	}

	HRESULT Fire_ReportMPPSStatusChanged(BSTR bsStudyUID, WorkListStatus enumStatus)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPAWLMPPSEvent* pIPAWLMPPSEvent = reinterpret_cast<IPAWLMPPSEvent*>(sp.p);
			if (pIPAWLMPPSEvent != NULL)
				ret = pIPAWLMPPSEvent->ReportMPPSStatusChanged(bsStudyUID, enumStatus);
		}	return ret;
	}

};


template <class T>
class CProxyIUserGuidanceEvent : public IConnectionPointImpl<T, &IID_IUserGuidanceEvent, CComDynamicUnkArray>
{
//	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_UserGuidanceReporting(LONG iMessageID, USER_GUIDANCE_TYPE enumType, USER_GUIDANCE_PRIORITY enumPrior, BOOL bActive)
	{
		HRESULT ret;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IUserGuidanceEvent* pIUserGuidanceEvent = reinterpret_cast<IUserGuidanceEvent*>(sp.p);
			if (pIUserGuidanceEvent != NULL)
				ret = pIUserGuidanceEvent->UserGuidanceReporting(iMessageID, enumType, enumPrior, bActive);
		}	return ret;
	
	}


};

#endif //__PALIBCONNECTIONPOINT_H__