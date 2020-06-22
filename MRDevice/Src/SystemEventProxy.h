#ifndef _SYSTEM_EVENT_PROXY_
#define _SYSTEM_EVENT_PROXY_

#include "StdAfx.h"

#define PostUG(_xx)

#define OBJ_DEFINE(_obj_name,_fun_name)	struct C##_obj_name													\
	{																	\
		C##_obj_name(CSystemEventProxy *pProxy,UINT nUG = 0){m_pProxy = pProxy;ug = nUG;}		\
		C##_obj_name& operator++(int)										\
		{																\
			do{															\
				Result = false;											\
				if ( !m_pProxy )										\
				{														\
					PRINTTRACE_ERROR(_T("proxy pointer not set"));		\
					break;												\
				}														\
				if ( !m_pProxy->m_pInterface )							\
				{														\
					PRINTTRACE_ERROR(_T("interface not initialized."));	\
					break;												\
				}														\
				HRESULT hr = m_pProxy->m_pInterface->_fun_name();		\
				if (hr != S_OK)											\
				{														\
					postug();											\
					PRINTTRACE_ERROR(_T("call add failed."));			\
					break;												\
				}														\
				Result = true;											\
			} while (0);												\
			return *this;												\
		}																\
		void postug(){if(!Result)if(ug)PostUG(ug);}						\
		bool Result;													\
		CSystemEventProxy *m_pProxy;									\
		UINT ug;														\
	}


#define OBJ_DIM_INNER(_obj_name,_obj_type,_ug_id) static _obj_type _obj_name(sysProxyPtr,_ug_id)

#define OBJ_DIM(_obj_name,_function_name,_ug_id) OBJ_DEFINE(_obj_name,_function_name);OBJ_DIM_INNER(_obj_name,C##_obj_name,_ug_id)

#define sysProxy (*CSystemEventProxy::GetInstance())
#define sysProxyPtr (CSystemEventProxy::GetInstance())



template< class T,class U >
class CProxyBase  
{
public:
	CProxyBase() : m_pInterface(NULL){};
	virtual ~CProxyBase(){Finalize();}
public:
	bool Initialize()
	{
		bool bRet = false;
		PRINTTRACE_ENTER_FUNCTION
		
		do 
		{
			if ( m_pInterface )
			{
				PRINTTRACE_ERROR(_T("interface pointer has been initialized"));
				bRet = true;
				break;
			}
			
			HRESULT hResult = ::CoCreateInstance( __uuidof(U),NULL,CLSCTX_LOCAL_SERVER,__uuidof(T),(LPVOID*)&m_pInterface);
			
			if ( (S_OK != hResult) || (NULL == m_pInterface) )
			{	
				PRINTTRACE_ERROR(_T("CoCreateInstance Failed"));
				break;
			}	
			
		} while ( 0 );
		
		PRINTTRACE_LEAVE_FUNCTION
		return bRet;
	}
	void Finalize()
	{
		if ( m_pInterface )
		{
			m_pInterface->Release();
			m_pInterface = NULL;
		}
	}
public:
	T *m_pInterface;
};

class CSystemEventProxy : public CProxyBase<IStatisticsWorkflowLevel,CoSystemEventDB>
{
public:
	static CSystemEventProxy* GetInstance(){static CSystemEventProxy _inst;return &_inst;}
	virtual ~CSystemEventProxy(void);
private:
	CSystemEventProxy(void);
};






#endif