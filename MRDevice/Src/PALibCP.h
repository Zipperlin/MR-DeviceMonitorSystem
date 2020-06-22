#ifndef _PALIBCP_H_
#define _PALIBCP_H_





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
class CProxyIPAUIEvent : public IConnectionPointImpl<T, &IID_IPAUIEvent, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_WorkStatus(SubUnit enumSubUnit, SubUnitStatus enumSubUnitStatus)
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
			IPAUIEvent* pIPAUIEvent = reinterpret_cast<IPAUIEvent*>(sp.p);
			if (pIPAUIEvent != NULL)
				ret = pIPAUIEvent->WorkStatus(enumSubUnit, enumSubUnitStatus);
		}	return ret;
	
	}

	HRESULT Fire_ReportRawToDICOMProgress(UINT Completed, UINT total)
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
			IPAUIEvent* pIPAUIEvent = reinterpret_cast<IPAUIEvent*>(sp.p);
			if (pIPAUIEvent != NULL)
				ret = pIPAUIEvent->ReportRawToDICOMProgress(Completed, total);
		}	return ret;
	
	}

	HRESULT Fire_ReportFilmComposerStatus(FilmComposerStatus enumFilmComposerStatus)
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
			IPAUIEvent* pIPAUIEvent = reinterpret_cast<IPAUIEvent*>(sp.p);
			if (pIPAUIEvent != NULL)
				ret = pIPAUIEvent->ReportFilmComposerStatus(enumFilmComposerStatus);
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
			IPAUIEvent* pIPAUIEvent = reinterpret_cast<IPAUIEvent*>(sp.p);
			if (pIPAUIEvent != NULL)
				ret = pIPAUIEvent->ReportBurnDeviceStatusChanged();
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
			IPAUIEvent* pIPAUIEvent = reinterpret_cast<IPAUIEvent*>(sp.p);
			if (pIPAUIEvent != NULL)
				ret = pIPAUIEvent->ReportBurnErrorCode(iErrCode);
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
			IPAUIEvent* pIPAUIEvent = reinterpret_cast<IPAUIEvent*>(sp.p);
			if (pIPAUIEvent != NULL)
				ret = pIPAUIEvent->ReportBurnPhase(bsBurnPhase);
		}	return ret;
	
	}


	HRESULT Fire_ReportBurnProgress(DWORD dwProgressPercent)
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
			IPAUIEvent* pIPAUIEvent = reinterpret_cast<IPAUIEvent*>(sp.p);
			if (pIPAUIEvent != NULL)
				ret = pIPAUIEvent->ReportBurnProgress(dwProgressPercent);
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
			IPAUIEvent* pIPAUIEvent = reinterpret_cast<IPAUIEvent*>(sp.p);
			if (pIPAUIEvent != NULL)
				ret = pIPAUIEvent->ReportBurnLogLine(bsBurnLogLine);
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
			IPAUIEvent* pIPAUIEvent = reinterpret_cast<IPAUIEvent*>(sp.p);
			if (pIPAUIEvent != NULL)
				ret = pIPAUIEvent->ReportBurnFileConflict(bsFirstFileName, bsSecondFileName);
		}	return ret;
	
	}

};
#endif