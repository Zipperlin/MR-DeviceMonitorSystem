/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 06 14:58:57 2018
 */
/* Compiler settings for PALib.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __PALib_i_h__
#define __PALib_i_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IGeneralInterface_FWD_DEFINED__
#define __IGeneralInterface_FWD_DEFINED__
typedef interface IGeneralInterface IGeneralInterface;
#endif 	/* __IGeneralInterface_FWD_DEFINED__ */


#ifndef __IGeneralEvent_FWD_DEFINED__
#define __IGeneralEvent_FWD_DEFINED__
typedef interface IGeneralEvent IGeneralEvent;
#endif 	/* __IGeneralEvent_FWD_DEFINED__ */


#ifndef __IGeneralSys_FWD_DEFINED__
#define __IGeneralSys_FWD_DEFINED__
typedef interface IGeneralSys IGeneralSys;
#endif 	/* __IGeneralSys_FWD_DEFINED__ */


#ifndef __IPing_FWD_DEFINED__
#define __IPing_FWD_DEFINED__
typedef interface IPing IPing;
#endif 	/* __IPing_FWD_DEFINED__ */


#ifndef __IUserGuidanceEvent_FWD_DEFINED__
#define __IUserGuidanceEvent_FWD_DEFINED__
typedef interface IUserGuidanceEvent IUserGuidanceEvent;
#endif 	/* __IUserGuidanceEvent_FWD_DEFINED__ */


#ifndef __IUserWorkingMode_FWD_DEFINED__
#define __IUserWorkingMode_FWD_DEFINED__
typedef interface IUserWorkingMode IUserWorkingMode;
#endif 	/* __IUserWorkingMode_FWD_DEFINED__ */


#ifndef __IPAGeneral_FWD_DEFINED__
#define __IPAGeneral_FWD_DEFINED__
typedef interface IPAGeneral IPAGeneral;
#endif 	/* __IPAGeneral_FWD_DEFINED__ */


#ifndef __IPAGeneralEvent_FWD_DEFINED__
#define __IPAGeneralEvent_FWD_DEFINED__
typedef interface IPAGeneralEvent IPAGeneralEvent;
#endif 	/* __IPAGeneralEvent_FWD_DEFINED__ */


#ifndef __IPAPrint_FWD_DEFINED__
#define __IPAPrint_FWD_DEFINED__
typedef interface IPAPrint IPAPrint;
#endif 	/* __IPAPrint_FWD_DEFINED__ */


#ifndef __IPAPrintEvent_FWD_DEFINED__
#define __IPAPrintEvent_FWD_DEFINED__
typedef interface IPAPrintEvent IPAPrintEvent;
#endif 	/* __IPAPrintEvent_FWD_DEFINED__ */


#ifndef __IPABurn_FWD_DEFINED__
#define __IPABurn_FWD_DEFINED__
typedef interface IPABurn IPABurn;
#endif 	/* __IPABurn_FWD_DEFINED__ */


#ifndef __IPABurnEvent_FWD_DEFINED__
#define __IPABurnEvent_FWD_DEFINED__
typedef interface IPABurnEvent IPABurnEvent;
#endif 	/* __IPABurnEvent_FWD_DEFINED__ */


#ifndef __IPATransfer_FWD_DEFINED__
#define __IPATransfer_FWD_DEFINED__
typedef interface IPATransfer IPATransfer;
#endif 	/* __IPATransfer_FWD_DEFINED__ */


#ifndef __IPATransferEvent_FWD_DEFINED__
#define __IPATransferEvent_FWD_DEFINED__
typedef interface IPATransferEvent IPATransferEvent;
#endif 	/* __IPATransferEvent_FWD_DEFINED__ */


#ifndef __IPADiscImport_FWD_DEFINED__
#define __IPADiscImport_FWD_DEFINED__
typedef interface IPADiscImport IPADiscImport;
#endif 	/* __IPADiscImport_FWD_DEFINED__ */


#ifndef __IPADiscImportEvent_FWD_DEFINED__
#define __IPADiscImportEvent_FWD_DEFINED__
typedef interface IPADiscImportEvent IPADiscImportEvent;
#endif 	/* __IPADiscImportEvent_FWD_DEFINED__ */


#ifndef __IPAWLMPPS_FWD_DEFINED__
#define __IPAWLMPPS_FWD_DEFINED__
typedef interface IPAWLMPPS IPAWLMPPS;
#endif 	/* __IPAWLMPPS_FWD_DEFINED__ */


#ifndef __IPAWLMPPSEvent_FWD_DEFINED__
#define __IPAWLMPPSEvent_FWD_DEFINED__
typedef interface IPAWLMPPSEvent IPAWLMPPSEvent;
#endif 	/* __IPAWLMPPSEvent_FWD_DEFINED__ */


#ifndef __PA_FWD_DEFINED__
#define __PA_FWD_DEFINED__

#ifdef __cplusplus
typedef class PA PA;
#else
typedef struct PA PA;
#endif /* __cplusplus */

#endif 	/* __PA_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_PALib_0000 */
/* [local] */ 

#ifndef __GENERALDEFINE_IDL__
#define __GENERALDEFINE_IDL__
typedef 
enum _STARTUPRESULT
    {	enumSTARTUPRESULT_UNKNOWN	= 0,
	enumSTARTUPRESULT_SUCCESS	= enumSTARTUPRESULT_UNKNOWN + 1,
	enumSTARTUPRESULT_FAILED	= enumSTARTUPRESULT_SUCCESS + 1
    }	STARTUPRESULT;

typedef 
enum _WORKSTATE
    {	enumWORKSTATE_UNKNOWN	= 0,
	enumWORKSTATE_UNINITIALIZED	= enumWORKSTATE_UNKNOWN + 1,
	enumWORKSTATE_INITIALIZING	= enumWORKSTATE_UNINITIALIZED + 1,
	enumWORKSTATE_READY	= enumWORKSTATE_INITIALIZING + 1,
	enumWORKSTATE_WORKING	= enumWORKSTATE_READY + 1,
	enumWORKSTATE_EMERGENCYSTOP	= enumWORKSTATE_WORKING + 1,
	enumWORKSTATE_RESTARTING	= enumWORKSTATE_EMERGENCYSTOP + 1,
	enumWORKSTATE_ERROR	= enumWORKSTATE_RESTARTING + 1,
	enumWORKSTATE_UNINITIALIZING	= enumWORKSTATE_ERROR + 1
    }	WORKSTATE;

#endif


extern RPC_IF_HANDLE __MIDL_itf_PALib_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PALib_0000_v0_0_s_ifspec;

#ifndef __IGeneralInterface_INTERFACE_DEFINED__
#define __IGeneralInterface_INTERFACE_DEFINED__

/* interface IGeneralInterface */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGeneralInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1FC1879-FC23-494d-8139-330BCE8508E9")
    IGeneralInterface : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStartupResult( 
            /* [out] */ STARTUPRESULT __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWorkState( 
            /* [out] */ WORKSTATE __RPC_FAR *pState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetError( 
            /* [out] */ INT __RPC_FAR *pError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGeneralInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGeneralInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGeneralInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGeneralInterface __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStartupResult )( 
            IGeneralInterface __RPC_FAR * This,
            /* [out] */ STARTUPRESULT __RPC_FAR *pResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWorkState )( 
            IGeneralInterface __RPC_FAR * This,
            /* [out] */ WORKSTATE __RPC_FAR *pState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetError )( 
            IGeneralInterface __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *pError);
        
        END_INTERFACE
    } IGeneralInterfaceVtbl;

    interface IGeneralInterface
    {
        CONST_VTBL struct IGeneralInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeneralInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGeneralInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGeneralInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGeneralInterface_GetStartupResult(This,pResult)	\
    (This)->lpVtbl -> GetStartupResult(This,pResult)

#define IGeneralInterface_GetWorkState(This,pState)	\
    (This)->lpVtbl -> GetWorkState(This,pState)

#define IGeneralInterface_GetError(This,pError)	\
    (This)->lpVtbl -> GetError(This,pError)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGeneralInterface_GetStartupResult_Proxy( 
    IGeneralInterface __RPC_FAR * This,
    /* [out] */ STARTUPRESULT __RPC_FAR *pResult);


void __RPC_STUB IGeneralInterface_GetStartupResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGeneralInterface_GetWorkState_Proxy( 
    IGeneralInterface __RPC_FAR * This,
    /* [out] */ WORKSTATE __RPC_FAR *pState);


void __RPC_STUB IGeneralInterface_GetWorkState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGeneralInterface_GetError_Proxy( 
    IGeneralInterface __RPC_FAR * This,
    /* [out] */ INT __RPC_FAR *pError);


void __RPC_STUB IGeneralInterface_GetError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGeneralInterface_INTERFACE_DEFINED__ */


#ifndef __IGeneralEvent_INTERFACE_DEFINED__
#define __IGeneralEvent_INTERFACE_DEFINED__

/* interface IGeneralEvent */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGeneralEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("92546B9A-954C-4d03-8BD6-25D971EAF524")
    IGeneralEvent : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportStartupResult( 
            /* [in] */ STARTUPRESULT enumResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportWorkState( 
            /* [in] */ WORKSTATE enumState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportError( 
            /* [in] */ INT iError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGeneralEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGeneralEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGeneralEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGeneralEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportStartupResult )( 
            IGeneralEvent __RPC_FAR * This,
            /* [in] */ STARTUPRESULT enumResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportWorkState )( 
            IGeneralEvent __RPC_FAR * This,
            /* [in] */ WORKSTATE enumState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportError )( 
            IGeneralEvent __RPC_FAR * This,
            /* [in] */ INT iError);
        
        END_INTERFACE
    } IGeneralEventVtbl;

    interface IGeneralEvent
    {
        CONST_VTBL struct IGeneralEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeneralEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGeneralEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGeneralEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGeneralEvent_ReportStartupResult(This,enumResult)	\
    (This)->lpVtbl -> ReportStartupResult(This,enumResult)

#define IGeneralEvent_ReportWorkState(This,enumState)	\
    (This)->lpVtbl -> ReportWorkState(This,enumState)

#define IGeneralEvent_ReportError(This,iError)	\
    (This)->lpVtbl -> ReportError(This,iError)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGeneralEvent_ReportStartupResult_Proxy( 
    IGeneralEvent __RPC_FAR * This,
    /* [in] */ STARTUPRESULT enumResult);


void __RPC_STUB IGeneralEvent_ReportStartupResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGeneralEvent_ReportWorkState_Proxy( 
    IGeneralEvent __RPC_FAR * This,
    /* [in] */ WORKSTATE enumState);


void __RPC_STUB IGeneralEvent_ReportWorkState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGeneralEvent_ReportError_Proxy( 
    IGeneralEvent __RPC_FAR * This,
    /* [in] */ INT iError);


void __RPC_STUB IGeneralEvent_ReportError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGeneralEvent_INTERFACE_DEFINED__ */


#ifndef __IGeneralSys_INTERFACE_DEFINED__
#define __IGeneralSys_INTERFACE_DEFINED__

/* interface IGeneralSys */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGeneralSys;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CFED7F4C-6E77-4cf6-A787-5599B380696D")
    IGeneralSys : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShutDown( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StartUp( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGeneralSysVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGeneralSys __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGeneralSys __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGeneralSys __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShutDown )( 
            IGeneralSys __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartUp )( 
            IGeneralSys __RPC_FAR * This);
        
        END_INTERFACE
    } IGeneralSysVtbl;

    interface IGeneralSys
    {
        CONST_VTBL struct IGeneralSysVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGeneralSys_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGeneralSys_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGeneralSys_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGeneralSys_ShutDown(This)	\
    (This)->lpVtbl -> ShutDown(This)

#define IGeneralSys_StartUp(This)	\
    (This)->lpVtbl -> StartUp(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGeneralSys_ShutDown_Proxy( 
    IGeneralSys __RPC_FAR * This);


void __RPC_STUB IGeneralSys_ShutDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGeneralSys_StartUp_Proxy( 
    IGeneralSys __RPC_FAR * This);


void __RPC_STUB IGeneralSys_StartUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGeneralSys_INTERFACE_DEFINED__ */


#ifndef __IPing_INTERFACE_DEFINED__
#define __IPing_INTERFACE_DEFINED__

/* interface IPing */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPing;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("811BB3A4-EA29-4e15-AF68-38732C9152DF")
    IPing : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Ping( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPing __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPing __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPing __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Ping )( 
            IPing __RPC_FAR * This);
        
        END_INTERFACE
    } IPingVtbl;

    interface IPing
    {
        CONST_VTBL struct IPingVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPing_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPing_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPing_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPing_Ping(This)	\
    (This)->lpVtbl -> Ping(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPing_Ping_Proxy( 
    IPing __RPC_FAR * This);


void __RPC_STUB IPing_Ping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPing_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_PALib_0212 */
/* [local] */ 

typedef 
enum UserGuidancePriority
    {	enumUG_PRIOR_L	= 0,
	enumUG_PRIOR_M	= 1,
	enumUG_PRIOR_H	= 2
    }	USER_GUIDANCE_PRIORITY;

typedef 
enum UserGuidanceType
    {	enumUG_TYPE_E	= 0,
	enumUG_TYPE_T	= 1,
	enumUG_TYPE_ET	= 2
    }	USER_GUIDANCE_TYPE;



extern RPC_IF_HANDLE __MIDL_itf_PALib_0212_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PALib_0212_v0_0_s_ifspec;

#ifndef __IUserGuidanceEvent_INTERFACE_DEFINED__
#define __IUserGuidanceEvent_INTERFACE_DEFINED__

/* interface IUserGuidanceEvent */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IUserGuidanceEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("438A08EB-58B9-4af8-9A9C-CCAF5DBA1D76")
    IUserGuidanceEvent : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UserGuidanceReporting( 
            /* [in] */ LONG iMessageID,
            /* [in] */ USER_GUIDANCE_TYPE enumType,
            /* [in] */ USER_GUIDANCE_PRIORITY enumPrior,
            /* [in] */ BOOL bActive) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUserGuidanceEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUserGuidanceEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUserGuidanceEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUserGuidanceEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UserGuidanceReporting )( 
            IUserGuidanceEvent __RPC_FAR * This,
            /* [in] */ LONG iMessageID,
            /* [in] */ USER_GUIDANCE_TYPE enumType,
            /* [in] */ USER_GUIDANCE_PRIORITY enumPrior,
            /* [in] */ BOOL bActive);
        
        END_INTERFACE
    } IUserGuidanceEventVtbl;

    interface IUserGuidanceEvent
    {
        CONST_VTBL struct IUserGuidanceEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUserGuidanceEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUserGuidanceEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUserGuidanceEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUserGuidanceEvent_UserGuidanceReporting(This,iMessageID,enumType,enumPrior,bActive)	\
    (This)->lpVtbl -> UserGuidanceReporting(This,iMessageID,enumType,enumPrior,bActive)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IUserGuidanceEvent_UserGuidanceReporting_Proxy( 
    IUserGuidanceEvent __RPC_FAR * This,
    /* [in] */ LONG iMessageID,
    /* [in] */ USER_GUIDANCE_TYPE enumType,
    /* [in] */ USER_GUIDANCE_PRIORITY enumPrior,
    /* [in] */ BOOL bActive);


void __RPC_STUB IUserGuidanceEvent_UserGuidanceReporting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUserGuidanceEvent_INTERFACE_DEFINED__ */


#ifndef __IUserWorkingMode_INTERFACE_DEFINED__
#define __IUserWorkingMode_INTERFACE_DEFINED__

/* interface IUserWorkingMode */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IUserWorkingMode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A14D9989-BA21-4049-A244-F55A912C6B5C")
    IUserWorkingMode : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Logout( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Login( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUserWorkingModeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUserWorkingMode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUserWorkingMode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUserWorkingMode __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Logout )( 
            IUserWorkingMode __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Login )( 
            IUserWorkingMode __RPC_FAR * This);
        
        END_INTERFACE
    } IUserWorkingModeVtbl;

    interface IUserWorkingMode
    {
        CONST_VTBL struct IUserWorkingModeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUserWorkingMode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUserWorkingMode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUserWorkingMode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUserWorkingMode_Logout(This)	\
    (This)->lpVtbl -> Logout(This)

#define IUserWorkingMode_Login(This)	\
    (This)->lpVtbl -> Login(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IUserWorkingMode_Logout_Proxy( 
    IUserWorkingMode __RPC_FAR * This);


void __RPC_STUB IUserWorkingMode_Logout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IUserWorkingMode_Login_Proxy( 
    IUserWorkingMode __RPC_FAR * This);


void __RPC_STUB IUserWorkingMode_Login_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUserWorkingMode_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_PALib_0214 */
/* [local] */ 

typedef 
enum _SubModule
    {	enumSubModule_PRINT	= 0,
	enumSubModule_TRANSFER	= 1,
	enumSubModule_BURN	= 2,
	enumSubModule_DISCIMPORT	= 3,
	enumSubModule_WLMPPS	= 4
    }	SubModule;

typedef 
enum _SubModuleState
    {	enumSubModuleState_UnInited	= 0,
	enumSubModuleState_Ready	= 1,
	enumSubModuleState_Work	= 2,
	enumSubModuleState_UnInitializing	= 3,
	enumSubModuleState_Error	= 4
    }	SubModuleState;

typedef 
enum _JobState
    {	enumJobState_Submitted	= 0,
	enumJobState_Executing	= 1,
	enumJobState_Completed	= 2,
	enumJobState_Cancelled	= 3,
	enumJobState_Failed	= 4
    }	JobState;

typedef 
enum _FilmComposerStatus
    {	enumFilmComposerUNKNOW	= 0,
	enumFilmComposerPRINTING	= 1,
	enumFilmComposerIdle	= 2
    }	FilmComposerStatus;

typedef 
enum _JobProgressUsing
    {	enumJobProgressUsing_None	= 0,
	enumJobProgressUsing_CompletedTotal	= 1,
	enumJobProgressUsing_Percentage	= 2
    }	JobProgressUsing;

typedef 
enum _JobDetailUsing
    {	enumJobDetailUsing_None	= 0,
	enumJobDetailUsing_UGID	= 1,
	enumJobDetailUsing_DetailInfo	= 2
    }	JobDetailUsing;

typedef 
enum _JobType
    {	enumJobType_InitJob	= 0,
	enumJobType_PrintJob	= 1,
	enumJobType_BurnJob	= 2,
	enumJobType_AutoSendJob	= 3,
	enumJobType_ManualSendJob	= 4,
	enumJobType_DiscImportJob	= 5
    }	JobType;

typedef struct  _tagJobInfo
    {
    BSTR bsJobID;
    BSTR bsIndex;
    BSTR bsType;
    JobType enumType;
    BSTR bsSubmitTime;
    BSTR bsState;
    BSTR bsPhase;
    BSTR bsProgress;
    BSTR bsDetail;
    }	JobInfo;

typedef 
enum _tagFileConflictHandle
    {	enumLeaveOldOne	= 0,
	enumUpdateOldOne	= 1,
	enumLeaveOldOneAlways	= 2,
	enumUpdateOldOneAlways	= 3,
	enumAbort	= 4,
	enumUnSet	= 5
    }	FileConflictHandle;

typedef 
enum _PABurnMediaType
    {	enumBurnMediaType_CD	= 0,
	enumBurnMediaType_DVD	= 1,
	enumBurnMediaType_UnSet	= 2,
	enumBurnMediaType_Unknow	= 3
    }	PABurnMediaType;

typedef 
enum _PatientAdminUIDType
    {	enumPatientAdminUIDType_Unknow	= 0,
	enumPatientAdminUIDType_Patient	= 1,
	enumPatientAdminUIDType_Study	= 2,
	enumPatientAdminUIDType_Series	= 3,
	enumPatientAdminUIDType_Image	= 4
    }	PatientAdminUIDType;

typedef struct  _tagBurnSpeedInfo
    {
    BSTR bsSpeedInfo;
    LONG lSpeed;
    }	BurnSpeedInfo;

typedef struct  _tagBurnMediaInfo
    {
    BSTR bsMediaType;
    BSTR bsMediaSize;
    BOOL bEmptyMedia;
    }	BurnMediaInfo;

typedef struct  _tagBurnSettings
    {
    BSTR bsDeviceName;
    BSTR bsDiscName;
    BOOL bFilesSet;
    DWORD dwFileCount;
    DWORD dwTotalFileSizeHighPart;
    DWORD dwTotalFileSizeLowPart;
    }	BurnSettings;

typedef 
enum _tagFileSelection
    {	enumFileSelection_CurrentPatient	= 0,
	enumFileSelection_CurrentStudy	= 1,
	enumFileSelection_CurrentRun	= 2
    }	FileSelection;

typedef 
enum _tagImageSelection
    {	enumImageSelection_All	= 0,
	enumImageSelection_Flagged	= 1,
	enumImageSelection_Unflagged	= 2
    }	ImageSelection;

typedef struct  _tagNetworkNode
    {
    BOOL bDefault;
    BSTR bsCalledAE;
    BSTR bsIP;
    BSTR bsPort;
    BSTR bsCallingAE;
    BOOL bRaw;
    BOOL bProcessed;
    BOOL bSendPS;
    }	NetworkNode;

typedef 
enum _tagDownscaleCriterion
    {	enumDownscaleCriterion_Unknow	= 0,
	enumDownscaleCriterion_1024_12_16	= 1,
	enumDownscaleCriterion_512_8_8	= 2
    }	DownscaleCriterion;

typedef struct  _tagPrintJobSettings
    {
    FileSelection enumFileSelection;
    ImageSelection enumImageSelection;
    }	PrintJobSettings;

typedef struct  _tagTransferJobSettings
    {
    FileSelection enumFileSelection;
    ImageSelection enumImageSelection;
    BSTR bsCalledAE;
    DownscaleCriterion enumDownscaleCriterion;
    }	TransferJobSettings;

typedef struct  _tagTransferJobSettingsByUID
    {
    BOOL bSelected;
    BSTR bsCalledAE;
    BOOL bRaw;
    BOOL bProcessed;
    BOOL bSendPS;
    }	TransferJobSettingsByUID;

typedef struct  _tagBurnJobSettings
    {
    FileSelection enumFileSelection;
    ImageSelection enumImageSelection;
    DownscaleCriterion enumDownscaleCriterion;
    BSTR bsDeviceName;
    LONG lBurnSpeed;
    }	BurnJobSettings;

typedef struct  _tagBurnJobSettingsByPA
    {
    LONG lBurnSpeed;
    BOOL bBMP;
    BOOL bJPEG;
    }	BurnJobSettingsByPA;

typedef struct  _tagJobProgressStruct
    {
    BSTR bsJobUID;
    JobProgressUsing enumJobProgressUsing;
    UINT uiCompleted;
    UINT uiTotal;
    DWORD dwPercentage;
    }	JobProgressStruct;

typedef struct  _tagJobDetailStruct
    {
    BSTR bsJobID;
    BSTR bsTime;
    BSTR bsDetail;
    }	JobDetailStruct;

typedef struct  _tagBurnPatientInfoStruct
    {
    BSTR bsPatientName;
    BSTR bsPatientID;
    INT iGender;
    DATE dtBirthDate;
    }	BurnPatientInfoStruct;

typedef struct  _tagBurnStudyInfoStruct
    {
    BSTR bsPatientName;
    BSTR bsPatientID;
    INT iStudyID;
    DATE dtStartStudyDateTime;
    }	BurnStudyInfoStruct;

typedef struct  _tagBurnSeriesInfoStruct
    {
    BSTR bsPatientName;
    BSTR bsPatientID;
    INT iStudyID;
    INT iSeriesID;
    }	BurnSeriesInfoStruct;

typedef struct  _tagBurnImageInfoStruct
    {
    BSTR bsPatientName;
    BSTR bsPatientID;
    INT iStudyID;
    INT iSeriesID;
    INT iImageID;
    }	BurnImageInfoStruct;

typedef struct  _tagDiscImportPatientInfo
    {
    BSTR bsPatientUID;
    BSTR bsPatientID;
    BSTR bsPatientName;
    INT iPatientGender;
    DATE dtBirthDate;
    UINT uStudyNum;
    }	DiscImportPatientInfo;

typedef struct  _tagDiscImportStudyInfo
    {
    BSTR bsStudyUID;
    BSTR bsPatientUID;
    BSTR bsStudyID;
    DATE dtStudyDateTime;
    BSTR bsRefPhisicianName;
    BSTR bsStudyDescription;
    UINT uSeriesNum;
    }	DiscImportStudyInfo;

typedef struct  _tagDiscImportSeriesInfo
    {
    BSTR bsSeriesUID;
    BSTR bsStudyUID;
    BSTR bsSeriesID;
    BSTR bsAprRegionName;
    UINT uImageNum;
    }	DiscImportSeriesInfo;

typedef struct  _tagDiscImporImageInfo
    {
    BSTR bsImageUID;
    BSTR bsSeriesUID;
    BSTR bsImageID;
    BSTR bsAprOrganName;
    UINT uRows;
    UINT uColumns;
    }	DiscImportImageInfo;

typedef struct  _tagPSSIInfo
    {
    BSTR bsPatientID;
    BSTR bsPatientName;
    BSTR bsStudyID;
    BSTR bsSeriesID;
    BSTR bsImageID;
    }	PSSIInfo;

typedef struct  _tagDiscImport_SeriesStruct
    {
    BSTR bsJobID;
    BSTR bsIndex;
    BSTR bsPatientID;
    BSTR bsPatientName;
    BSTR bsStudyID;
    BSTR bsSeriesID;
    BSTR bsImageID;
    BSTR bsState;
    BSTR bsProgress;
    BSTR bsDetailInfo;
    }	DiscImport_SeriesStruct;

typedef struct  _tagDiscImport_SeriesStateStruct
    {
    BSTR bsJobID;
    BSTR bsIndex;
    BSTR bsState;
    }	DiscImport_SeriesStateStruct;

typedef struct  _tagDiscImport_SeriesProgressStruct
    {
    BSTR bsJobID;
    BSTR bsIndex;
    BSTR bsProgress;
    }	DiscImport_SeriesProgressStruct;

typedef struct  _tagDiscImport_SeriesDetailStruct
    {
    BSTR bsJobID;
    BSTR bsIndex;
    BSTR bsDetailInfo;
    }	DiscImport_SeriesDetailStruct;

typedef 
enum _WorkListStatus
    {	enumWorkListStatus_NotImported	= 0,
	enumWorkListStatus_Imported	= 1,
	enumWorkListStatus_InProgress	= 2,
	enumWorkListStatus_Discontinued	= 3,
	enumWorkListStatus_Completed	= 4
    }	WorkListStatus;

typedef struct  _tagWorkListStruct
    {
    WorkListStatus enumStatus;
    BSTR bsSSAETitle;
    BSTR bsSPSDateTime;
    BSTR bsSPSDescription;
    BSTR bsSPSID;
    BSTR bsSPPhisicianName;
    BSTR bsPatientName;
    BSTR bsPatientID;
    BSTR bsAccessionNumber;
    BSTR bsPatientBirthDate;
    INT iPatientSex;
    BSTR bsRefPhisicianName;
    BSTR bsRPID;
    BSTR bsRPDescription;
    BSTR bsStudyInstanceUID;
    BSTR bsOtherPatientIDs;
    BSTR bsOtherPatientNames;
    BSTR bsPatientAge;
    BSTR bsOccupation;
    BSTR bsPatientSize;
    BSTR bsPatientWeight;
    BSTR bsEthnicGroup;
    BSTR bsPatientComments;
    }	WorkListStruct;

typedef struct  _MppsSetResult
    {
    BSTR bsStudyUID;
    WorkListStatus enumStatus;
    BOOL bResult;
    }	MppsSetResult;

typedef 
enum _PatientBirthDateAgeUsing
    {	enumBirthDateAgeUsing_None	= 0,
	enumBirthDateAgeUsing_BirthDate	= 1,
	enumBirthDateAgeUsing_Age	= 2,
	enumBirthDateAgeUsing_Both	= 3
    }	PatientBirthDateAgeUsing;

typedef struct  _tagWLPatientStudyStruct
    {
    BSTR bsStudyInstanceUID;
    BSTR bsPatientID;
    BSTR bsPatientFirstName;
    BSTR bsPatientMidName;
    BSTR bsPatientLastName;
    PatientBirthDateAgeUsing enumBirthDateAgeUsing;
    INT iPatientAge;
    INT iPatientAgeUnit;
    DATE dtPatientBirthDate;
    DATE dtRegDateTime;
    INT iPatientSex;
    BSTR bsOtherPatientName;
    BSTR bsOtherPatientIDs;
    BSTR bsEthnicGroup;
    BSTR bsOccupation;
    BSTR bsPatientComment;
    DATE dtStudyDateTime;
    BSTR bsRefferingPhsicianName;
    BSTR bsOperatorName;
    BSTR bsPerformingPhysicianName;
    BSTR bsPatientSize;
    BSTR bsPatientWeight;
    BSTR bsStudyDescription;
    BSTR bsPatientHistory;
    BSTR bsAccessionNumber;
    }	WLPatientStudyStruct;

typedef 
enum _WLQuerySPSStartDate
    {	enumWLQuery_SPS_SD_UnUse	= 0,
	enumWLQuery_SPS_SD_Today	= 1,
	enumWLQuery_SPS_SD_LastTwoDays	= 2,
	enumWLQuery_SPS_SD_LastOneWeek	= 3,
	enumWLQuery_SPS_SD_LastOneMonth	= 4,
	enumWLQuery_SPS_SD_LastOneYear	= 5,
	enumWLQuery_SPS_SD_All	= 6
    }	WLQuerySPSStartDate;

typedef struct  _WorkListQueryCond
    {
    WLQuerySPSStartDate enumWLQuerySPSStartDate;
    }	WorkListQueryCond;

typedef struct  _WLPatientStudyStatusInDB
    {
    BOOL bStudyExists;
    BOOL bPatientExists;
    BSTR bsPatientUID;
    BSTR bsPatientID;
    BSTR bsPatientFullName;
    INT iPatientSex;
    }	WLPatientStudyStatusInDB;



extern RPC_IF_HANDLE __MIDL_itf_PALib_0214_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PALib_0214_v0_0_s_ifspec;

#ifndef __IPAGeneral_INTERFACE_DEFINED__
#define __IPAGeneral_INTERFACE_DEFINED__

/* interface IPAGeneral */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPAGeneral;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2BDBA172-2C6C-4ed4-8274-E67EF25722BE")
    IPAGeneral : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPatientStudySeriesImageOccupyState( 
            /* [in] */ PatientAdminUIDType enumUIDType,
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
            /* [out] */ BOOL __RPC_FAR *pbOccupied) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportUserGuidance( 
            /* [in] */ LONG iMessageID,
            /* [in] */ USER_GUIDANCE_TYPE enumType,
            /* [in] */ USER_GUIDANCE_PRIORITY enumPrior,
            /* [in] */ BOOL bActive) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetJobList( 
            /* [size_is][size_is][out] */ JobInfo __RPC_FAR *__RPC_FAR *ppJobList,
            /* [out] */ long __RPC_FAR *pLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MoveJob( 
            /* [in] */ BSTR bsJobID,
            /* [in] */ BOOL bForward) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CancelJobs( 
            /* [size_is][in] */ BSTR __RPC_FAR *pbsJobIDs,
            /* [in] */ long lNum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteJobs( 
            /* [size_is][in] */ BSTR __RPC_FAR *pbsJobIDs,
            /* [in] */ long lNum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHistoryJobCount( 
            /* [out] */ DWORD __RPC_FAR *pdwCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHistoryJobs( 
            /* [in] */ DWORD dwStartIndex,
            /* [out][in] */ DWORD __RPC_FAR *pdwCount,
            /* [size_is][size_is][out] */ JobInfo __RPC_FAR *__RPC_FAR *ppJobList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHistoryJobInfo( 
            /* [in] */ BSTR bsJobID,
            /* [out] */ JobInfo __RPC_FAR *pJobInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHistoryJobPSSIInfo( 
            /* [in] */ BSTR bsJobID,
            /* [out] */ long __RPC_FAR *pLen,
            /* [size_is][size_is][out] */ PSSIInfo __RPC_FAR *__RPC_FAR *ppPSSIList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHistoryJobNetworkNodeInfo( 
            /* [in] */ BSTR bsJobID,
            /* [out] */ long __RPC_FAR *pLen,
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppNodeList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHistoryJobDetailInfo( 
            /* [in] */ BSTR bsJobID,
            /* [out] */ long __RPC_FAR *pLen,
            /* [size_is][size_is][out] */ JobDetailStruct __RPC_FAR *__RPC_FAR *ppDetailList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHistoryJobDiscImportImageInfo( 
            /* [in] */ BSTR bsJobID,
            /* [out] */ long __RPC_FAR *pLen,
            /* [size_is][size_is][out] */ DiscImport_SeriesStruct __RPC_FAR *__RPC_FAR *ppDISSList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteHistoryJobs( 
            /* [in] */ long lNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsJobIDList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteAllHistoryJobs( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CompactDB( 
            /* [in] */ BOOL bBackUp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPAGeneralVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPAGeneral __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPAGeneral __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPatientStudySeriesImageOccupyState )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ PatientAdminUIDType enumUIDType,
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
            /* [out] */ BOOL __RPC_FAR *pbOccupied);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportUserGuidance )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ LONG iMessageID,
            /* [in] */ USER_GUIDANCE_TYPE enumType,
            /* [in] */ USER_GUIDANCE_PRIORITY enumPrior,
            /* [in] */ BOOL bActive);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetJobList )( 
            IPAGeneral __RPC_FAR * This,
            /* [size_is][size_is][out] */ JobInfo __RPC_FAR *__RPC_FAR *ppJobList,
            /* [out] */ long __RPC_FAR *pLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveJob )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [in] */ BOOL bForward);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelJobs )( 
            IPAGeneral __RPC_FAR * This,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsJobIDs,
            /* [in] */ long lNum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteJobs )( 
            IPAGeneral __RPC_FAR * This,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsJobIDs,
            /* [in] */ long lNum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistoryJobCount )( 
            IPAGeneral __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistoryJobs )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ DWORD dwStartIndex,
            /* [out][in] */ DWORD __RPC_FAR *pdwCount,
            /* [size_is][size_is][out] */ JobInfo __RPC_FAR *__RPC_FAR *ppJobList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistoryJobInfo )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [out] */ JobInfo __RPC_FAR *pJobInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistoryJobPSSIInfo )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [out] */ long __RPC_FAR *pLen,
            /* [size_is][size_is][out] */ PSSIInfo __RPC_FAR *__RPC_FAR *ppPSSIList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistoryJobNetworkNodeInfo )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [out] */ long __RPC_FAR *pLen,
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppNodeList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistoryJobDetailInfo )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [out] */ long __RPC_FAR *pLen,
            /* [size_is][size_is][out] */ JobDetailStruct __RPC_FAR *__RPC_FAR *ppDetailList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHistoryJobDiscImportImageInfo )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [out] */ long __RPC_FAR *pLen,
            /* [size_is][size_is][out] */ DiscImport_SeriesStruct __RPC_FAR *__RPC_FAR *ppDISSList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteHistoryJobs )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ long lNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsJobIDList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteAllHistoryJobs )( 
            IPAGeneral __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CompactDB )( 
            IPAGeneral __RPC_FAR * This,
            /* [in] */ BOOL bBackUp);
        
        END_INTERFACE
    } IPAGeneralVtbl;

    interface IPAGeneral
    {
        CONST_VTBL struct IPAGeneralVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPAGeneral_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPAGeneral_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPAGeneral_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPAGeneral_GetPatientStudySeriesImageOccupyState(This,enumUIDType,lUIDNum,pbsUIDList,pbOccupied)	\
    (This)->lpVtbl -> GetPatientStudySeriesImageOccupyState(This,enumUIDType,lUIDNum,pbsUIDList,pbOccupied)

#define IPAGeneral_ReportUserGuidance(This,iMessageID,enumType,enumPrior,bActive)	\
    (This)->lpVtbl -> ReportUserGuidance(This,iMessageID,enumType,enumPrior,bActive)

#define IPAGeneral_GetJobList(This,ppJobList,pLen)	\
    (This)->lpVtbl -> GetJobList(This,ppJobList,pLen)

#define IPAGeneral_MoveJob(This,bsJobID,bForward)	\
    (This)->lpVtbl -> MoveJob(This,bsJobID,bForward)

#define IPAGeneral_CancelJobs(This,pbsJobIDs,lNum)	\
    (This)->lpVtbl -> CancelJobs(This,pbsJobIDs,lNum)

#define IPAGeneral_DeleteJobs(This,pbsJobIDs,lNum)	\
    (This)->lpVtbl -> DeleteJobs(This,pbsJobIDs,lNum)

#define IPAGeneral_GetHistoryJobCount(This,pdwCount)	\
    (This)->lpVtbl -> GetHistoryJobCount(This,pdwCount)

#define IPAGeneral_GetHistoryJobs(This,dwStartIndex,pdwCount,ppJobList)	\
    (This)->lpVtbl -> GetHistoryJobs(This,dwStartIndex,pdwCount,ppJobList)

#define IPAGeneral_GetHistoryJobInfo(This,bsJobID,pJobInfo)	\
    (This)->lpVtbl -> GetHistoryJobInfo(This,bsJobID,pJobInfo)

#define IPAGeneral_GetHistoryJobPSSIInfo(This,bsJobID,pLen,ppPSSIList)	\
    (This)->lpVtbl -> GetHistoryJobPSSIInfo(This,bsJobID,pLen,ppPSSIList)

#define IPAGeneral_GetHistoryJobNetworkNodeInfo(This,bsJobID,pLen,ppNodeList)	\
    (This)->lpVtbl -> GetHistoryJobNetworkNodeInfo(This,bsJobID,pLen,ppNodeList)

#define IPAGeneral_GetHistoryJobDetailInfo(This,bsJobID,pLen,ppDetailList)	\
    (This)->lpVtbl -> GetHistoryJobDetailInfo(This,bsJobID,pLen,ppDetailList)

#define IPAGeneral_GetHistoryJobDiscImportImageInfo(This,bsJobID,pLen,ppDISSList)	\
    (This)->lpVtbl -> GetHistoryJobDiscImportImageInfo(This,bsJobID,pLen,ppDISSList)

#define IPAGeneral_DeleteHistoryJobs(This,lNum,pbsJobIDList)	\
    (This)->lpVtbl -> DeleteHistoryJobs(This,lNum,pbsJobIDList)

#define IPAGeneral_DeleteAllHistoryJobs(This)	\
    (This)->lpVtbl -> DeleteAllHistoryJobs(This)

#define IPAGeneral_CompactDB(This,bBackUp)	\
    (This)->lpVtbl -> CompactDB(This,bBackUp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_GetPatientStudySeriesImageOccupyState_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ PatientAdminUIDType enumUIDType,
    /* [in] */ long lUIDNum,
    /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
    /* [out] */ BOOL __RPC_FAR *pbOccupied);


void __RPC_STUB IPAGeneral_GetPatientStudySeriesImageOccupyState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_ReportUserGuidance_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ LONG iMessageID,
    /* [in] */ USER_GUIDANCE_TYPE enumType,
    /* [in] */ USER_GUIDANCE_PRIORITY enumPrior,
    /* [in] */ BOOL bActive);


void __RPC_STUB IPAGeneral_ReportUserGuidance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_GetJobList_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [size_is][size_is][out] */ JobInfo __RPC_FAR *__RPC_FAR *ppJobList,
    /* [out] */ long __RPC_FAR *pLen);


void __RPC_STUB IPAGeneral_GetJobList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_MoveJob_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [in] */ BOOL bForward);


void __RPC_STUB IPAGeneral_MoveJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_CancelJobs_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [size_is][in] */ BSTR __RPC_FAR *pbsJobIDs,
    /* [in] */ long lNum);


void __RPC_STUB IPAGeneral_CancelJobs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_DeleteJobs_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [size_is][in] */ BSTR __RPC_FAR *pbsJobIDs,
    /* [in] */ long lNum);


void __RPC_STUB IPAGeneral_DeleteJobs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_GetHistoryJobCount_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwCount);


void __RPC_STUB IPAGeneral_GetHistoryJobCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_GetHistoryJobs_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ DWORD dwStartIndex,
    /* [out][in] */ DWORD __RPC_FAR *pdwCount,
    /* [size_is][size_is][out] */ JobInfo __RPC_FAR *__RPC_FAR *ppJobList);


void __RPC_STUB IPAGeneral_GetHistoryJobs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_GetHistoryJobInfo_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [out] */ JobInfo __RPC_FAR *pJobInfo);


void __RPC_STUB IPAGeneral_GetHistoryJobInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_GetHistoryJobPSSIInfo_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [out] */ long __RPC_FAR *pLen,
    /* [size_is][size_is][out] */ PSSIInfo __RPC_FAR *__RPC_FAR *ppPSSIList);


void __RPC_STUB IPAGeneral_GetHistoryJobPSSIInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_GetHistoryJobNetworkNodeInfo_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [out] */ long __RPC_FAR *pLen,
    /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppNodeList);


void __RPC_STUB IPAGeneral_GetHistoryJobNetworkNodeInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_GetHistoryJobDetailInfo_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [out] */ long __RPC_FAR *pLen,
    /* [size_is][size_is][out] */ JobDetailStruct __RPC_FAR *__RPC_FAR *ppDetailList);


void __RPC_STUB IPAGeneral_GetHistoryJobDetailInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_GetHistoryJobDiscImportImageInfo_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [out] */ long __RPC_FAR *pLen,
    /* [size_is][size_is][out] */ DiscImport_SeriesStruct __RPC_FAR *__RPC_FAR *ppDISSList);


void __RPC_STUB IPAGeneral_GetHistoryJobDiscImportImageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_DeleteHistoryJobs_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ long lNum,
    /* [size_is][in] */ BSTR __RPC_FAR *pbsJobIDList);


void __RPC_STUB IPAGeneral_DeleteHistoryJobs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_DeleteAllHistoryJobs_Proxy( 
    IPAGeneral __RPC_FAR * This);


void __RPC_STUB IPAGeneral_DeleteAllHistoryJobs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneral_CompactDB_Proxy( 
    IPAGeneral __RPC_FAR * This,
    /* [in] */ BOOL bBackUp);


void __RPC_STUB IPAGeneral_CompactDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPAGeneral_INTERFACE_DEFINED__ */


#ifndef __IPAGeneralEvent_INTERFACE_DEFINED__
#define __IPAGeneralEvent_INTERFACE_DEFINED__

/* interface IPAGeneralEvent */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPAGeneralEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A3FB2C6-0432-4f71-832B-DF9C79CE2CE4")
    IPAGeneralEvent : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportJobQueueChanged( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportJobState( 
            /* [in] */ BSTR bsJobID,
            /* [in] */ BSTR bsJobSate) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportJobPhase( 
            /* [in] */ BSTR bsJobID,
            /* [in] */ BSTR bsJobPhase) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportJobProgress( 
            /* [in] */ BSTR bsJobID,
            /* [in] */ BSTR bsJobProgress) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportJobDetail( 
            /* [in] */ JobDetailStruct __RPC_FAR *JobDetail) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPAGeneralEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPAGeneralEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPAGeneralEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPAGeneralEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportJobQueueChanged )( 
            IPAGeneralEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportJobState )( 
            IPAGeneralEvent __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [in] */ BSTR bsJobSate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportJobPhase )( 
            IPAGeneralEvent __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [in] */ BSTR bsJobPhase);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportJobProgress )( 
            IPAGeneralEvent __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [in] */ BSTR bsJobProgress);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportJobDetail )( 
            IPAGeneralEvent __RPC_FAR * This,
            /* [in] */ JobDetailStruct __RPC_FAR *JobDetail);
        
        END_INTERFACE
    } IPAGeneralEventVtbl;

    interface IPAGeneralEvent
    {
        CONST_VTBL struct IPAGeneralEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPAGeneralEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPAGeneralEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPAGeneralEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPAGeneralEvent_ReportJobQueueChanged(This)	\
    (This)->lpVtbl -> ReportJobQueueChanged(This)

#define IPAGeneralEvent_ReportJobState(This,bsJobID,bsJobSate)	\
    (This)->lpVtbl -> ReportJobState(This,bsJobID,bsJobSate)

#define IPAGeneralEvent_ReportJobPhase(This,bsJobID,bsJobPhase)	\
    (This)->lpVtbl -> ReportJobPhase(This,bsJobID,bsJobPhase)

#define IPAGeneralEvent_ReportJobProgress(This,bsJobID,bsJobProgress)	\
    (This)->lpVtbl -> ReportJobProgress(This,bsJobID,bsJobProgress)

#define IPAGeneralEvent_ReportJobDetail(This,JobDetail)	\
    (This)->lpVtbl -> ReportJobDetail(This,JobDetail)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneralEvent_ReportJobQueueChanged_Proxy( 
    IPAGeneralEvent __RPC_FAR * This);


void __RPC_STUB IPAGeneralEvent_ReportJobQueueChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneralEvent_ReportJobState_Proxy( 
    IPAGeneralEvent __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [in] */ BSTR bsJobSate);


void __RPC_STUB IPAGeneralEvent_ReportJobState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneralEvent_ReportJobPhase_Proxy( 
    IPAGeneralEvent __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [in] */ BSTR bsJobPhase);


void __RPC_STUB IPAGeneralEvent_ReportJobPhase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneralEvent_ReportJobProgress_Proxy( 
    IPAGeneralEvent __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [in] */ BSTR bsJobProgress);


void __RPC_STUB IPAGeneralEvent_ReportJobProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAGeneralEvent_ReportJobDetail_Proxy( 
    IPAGeneralEvent __RPC_FAR * This,
    /* [in] */ JobDetailStruct __RPC_FAR *JobDetail);


void __RPC_STUB IPAGeneralEvent_ReportJobDetail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPAGeneralEvent_INTERFACE_DEFINED__ */


#ifndef __IPAPrint_INTERFACE_DEFINED__
#define __IPAPrint_INTERFACE_DEFINED__

/* interface IPAPrint */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPAPrint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8BABE658-3016-47d2-B183-6E83C1BB05B4")
    IPAPrint : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Print( 
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsImageUIDList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowFCProgressBar( 
            /* [in] */ BOOL bShow) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPrintJobList( 
            /* [size_is][size_is][out] */ JobInfo __RPC_FAR *__RPC_FAR *ppJobInfoList,
            /* [out] */ long __RPC_FAR *pLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPrintNetworkNodes( 
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppNodesList,
            /* [out] */ long __RPC_FAR *pLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPrintErrorMsg( 
            /* [in] */ int iErrCode,
            /* [out] */ BSTR __RPC_FAR *bsErrMsg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPrintSubModuleState( 
            /* [out] */ SubModuleState __RPC_FAR *pSubModuleState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPAPrintVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPAPrint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPAPrint __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPAPrint __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Print )( 
            IPAPrint __RPC_FAR * This,
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsImageUIDList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowFCProgressBar )( 
            IPAPrint __RPC_FAR * This,
            /* [in] */ BOOL bShow);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrintJobList )( 
            IPAPrint __RPC_FAR * This,
            /* [size_is][size_is][out] */ JobInfo __RPC_FAR *__RPC_FAR *ppJobInfoList,
            /* [out] */ long __RPC_FAR *pLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrintNetworkNodes )( 
            IPAPrint __RPC_FAR * This,
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppNodesList,
            /* [out] */ long __RPC_FAR *pLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrintErrorMsg )( 
            IPAPrint __RPC_FAR * This,
            /* [in] */ int iErrCode,
            /* [out] */ BSTR __RPC_FAR *bsErrMsg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrintSubModuleState )( 
            IPAPrint __RPC_FAR * This,
            /* [out] */ SubModuleState __RPC_FAR *pSubModuleState);
        
        END_INTERFACE
    } IPAPrintVtbl;

    interface IPAPrint
    {
        CONST_VTBL struct IPAPrintVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPAPrint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPAPrint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPAPrint_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPAPrint_Print(This,lUIDNum,pbsImageUIDList)	\
    (This)->lpVtbl -> Print(This,lUIDNum,pbsImageUIDList)

#define IPAPrint_ShowFCProgressBar(This,bShow)	\
    (This)->lpVtbl -> ShowFCProgressBar(This,bShow)

#define IPAPrint_GetPrintJobList(This,ppJobInfoList,pLen)	\
    (This)->lpVtbl -> GetPrintJobList(This,ppJobInfoList,pLen)

#define IPAPrint_GetPrintNetworkNodes(This,ppNodesList,pLen)	\
    (This)->lpVtbl -> GetPrintNetworkNodes(This,ppNodesList,pLen)

#define IPAPrint_GetPrintErrorMsg(This,iErrCode,bsErrMsg)	\
    (This)->lpVtbl -> GetPrintErrorMsg(This,iErrCode,bsErrMsg)

#define IPAPrint_GetPrintSubModuleState(This,pSubModuleState)	\
    (This)->lpVtbl -> GetPrintSubModuleState(This,pSubModuleState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAPrint_Print_Proxy( 
    IPAPrint __RPC_FAR * This,
    /* [in] */ long lUIDNum,
    /* [size_is][in] */ BSTR __RPC_FAR *pbsImageUIDList);


void __RPC_STUB IPAPrint_Print_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAPrint_ShowFCProgressBar_Proxy( 
    IPAPrint __RPC_FAR * This,
    /* [in] */ BOOL bShow);


void __RPC_STUB IPAPrint_ShowFCProgressBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAPrint_GetPrintJobList_Proxy( 
    IPAPrint __RPC_FAR * This,
    /* [size_is][size_is][out] */ JobInfo __RPC_FAR *__RPC_FAR *ppJobInfoList,
    /* [out] */ long __RPC_FAR *pLen);


void __RPC_STUB IPAPrint_GetPrintJobList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAPrint_GetPrintNetworkNodes_Proxy( 
    IPAPrint __RPC_FAR * This,
    /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppNodesList,
    /* [out] */ long __RPC_FAR *pLen);


void __RPC_STUB IPAPrint_GetPrintNetworkNodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAPrint_GetPrintErrorMsg_Proxy( 
    IPAPrint __RPC_FAR * This,
    /* [in] */ int iErrCode,
    /* [out] */ BSTR __RPC_FAR *bsErrMsg);


void __RPC_STUB IPAPrint_GetPrintErrorMsg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAPrint_GetPrintSubModuleState_Proxy( 
    IPAPrint __RPC_FAR * This,
    /* [out] */ SubModuleState __RPC_FAR *pSubModuleState);


void __RPC_STUB IPAPrint_GetPrintSubModuleState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPAPrint_INTERFACE_DEFINED__ */


#ifndef __IPAPrintEvent_INTERFACE_DEFINED__
#define __IPAPrintEvent_INTERFACE_DEFINED__

/* interface IPAPrintEvent */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPAPrintEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("137677CA-B2ED-42f1-814D-78E13C0D6D9E")
    IPAPrintEvent : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportPrintWorkStatus( 
            /* [in] */ SubModule enumSubModule,
            /* [in] */ SubModuleState enumSubUnitStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportPrintFilmComposerStatus( 
            /* [in] */ FilmComposerStatus enumFilmComposerStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportPrintFilmComposerStartUp( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportEnableFilmComposer( 
            BOOL bEnable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPAPrintEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPAPrintEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPAPrintEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPAPrintEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportPrintWorkStatus )( 
            IPAPrintEvent __RPC_FAR * This,
            /* [in] */ SubModule enumSubModule,
            /* [in] */ SubModuleState enumSubUnitStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportPrintFilmComposerStatus )( 
            IPAPrintEvent __RPC_FAR * This,
            /* [in] */ FilmComposerStatus enumFilmComposerStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportPrintFilmComposerStartUp )( 
            IPAPrintEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportEnableFilmComposer )( 
            IPAPrintEvent __RPC_FAR * This,
            BOOL bEnable);
        
        END_INTERFACE
    } IPAPrintEventVtbl;

    interface IPAPrintEvent
    {
        CONST_VTBL struct IPAPrintEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPAPrintEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPAPrintEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPAPrintEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPAPrintEvent_ReportPrintWorkStatus(This,enumSubModule,enumSubUnitStatus)	\
    (This)->lpVtbl -> ReportPrintWorkStatus(This,enumSubModule,enumSubUnitStatus)

#define IPAPrintEvent_ReportPrintFilmComposerStatus(This,enumFilmComposerStatus)	\
    (This)->lpVtbl -> ReportPrintFilmComposerStatus(This,enumFilmComposerStatus)

#define IPAPrintEvent_ReportPrintFilmComposerStartUp(This)	\
    (This)->lpVtbl -> ReportPrintFilmComposerStartUp(This)

#define IPAPrintEvent_ReportEnableFilmComposer(This,bEnable)	\
    (This)->lpVtbl -> ReportEnableFilmComposer(This,bEnable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAPrintEvent_ReportPrintWorkStatus_Proxy( 
    IPAPrintEvent __RPC_FAR * This,
    /* [in] */ SubModule enumSubModule,
    /* [in] */ SubModuleState enumSubUnitStatus);


void __RPC_STUB IPAPrintEvent_ReportPrintWorkStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAPrintEvent_ReportPrintFilmComposerStatus_Proxy( 
    IPAPrintEvent __RPC_FAR * This,
    /* [in] */ FilmComposerStatus enumFilmComposerStatus);


void __RPC_STUB IPAPrintEvent_ReportPrintFilmComposerStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAPrintEvent_ReportPrintFilmComposerStartUp_Proxy( 
    IPAPrintEvent __RPC_FAR * This);


void __RPC_STUB IPAPrintEvent_ReportPrintFilmComposerStartUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAPrintEvent_ReportEnableFilmComposer_Proxy( 
    IPAPrintEvent __RPC_FAR * This,
    BOOL bEnable);


void __RPC_STUB IPAPrintEvent_ReportEnableFilmComposer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPAPrintEvent_INTERFACE_DEFINED__ */


#ifndef __IPABurn_INTERFACE_DEFINED__
#define __IPABurn_INTERFACE_DEFINED__

/* interface IPABurn */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPABurn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F36663B9-BE3C-4ca0-B36A-90AE3FC5528A")
    IPABurn : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDevices( 
            /* [size_is][size_is][out] */ BSTR __RPC_FAR *__RPC_FAR *ppbsDevices,
            /* [out] */ long __RPC_FAR *pLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCurrentDeviceMediaInfo( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBurnSubModuleState( 
            /* [out] */ SubModuleState __RPC_FAR *pSubModuleState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetBurnDevice( 
            /* [in] */ BSTR bsDeviceName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BurnByPA( 
            /* [in] */ BurnJobSettingsByPA __RPC_FAR *pBurnJobSettingsByPA) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BurnPrepare( 
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
            /* [in] */ PatientAdminUIDType enumUIDType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CancelBurnPrepare( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEstimatedSize( 
            /* [in] */ BOOL bBMP,
            /* [in] */ BOOL bJPEG,
            /* [out] */ unsigned long __RPC_FAR *plSizeInMega) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetBurnMediaCheckRetry( 
            BOOL bRetry) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBurnJobInfo( 
            /* [in] */ BSTR bsJobID,
            /* [out] */ JobInfo __RPC_FAR *pJobInfo,
            /* [size_is][size_is][out] */ PSSIInfo __RPC_FAR *__RPC_FAR *ppPSSIList,
            /* [out] */ long __RPC_FAR *pPSSILen,
            /* [size_is][size_is][out] */ JobDetailStruct __RPC_FAR *__RPC_FAR *ppDetailList,
            /* [out] */ long __RPC_FAR *pDetailLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsUnfinishedBurnJobExist( 
            /* [out] */ BOOL __RPC_FAR *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBurnErrorMsg( 
            /* [in] */ int iErrCode,
            /* [out] */ BSTR __RPC_FAR *bsErrMsg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPABurnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPABurn __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPABurn __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPABurn __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDevices )( 
            IPABurn __RPC_FAR * This,
            /* [size_is][size_is][out] */ BSTR __RPC_FAR *__RPC_FAR *ppbsDevices,
            /* [out] */ long __RPC_FAR *pLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentDeviceMediaInfo )( 
            IPABurn __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBurnSubModuleState )( 
            IPABurn __RPC_FAR * This,
            /* [out] */ SubModuleState __RPC_FAR *pSubModuleState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBurnDevice )( 
            IPABurn __RPC_FAR * This,
            /* [in] */ BSTR bsDeviceName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BurnByPA )( 
            IPABurn __RPC_FAR * This,
            /* [in] */ BurnJobSettingsByPA __RPC_FAR *pBurnJobSettingsByPA);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BurnPrepare )( 
            IPABurn __RPC_FAR * This,
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
            /* [in] */ PatientAdminUIDType enumUIDType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelBurnPrepare )( 
            IPABurn __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEstimatedSize )( 
            IPABurn __RPC_FAR * This,
            /* [in] */ BOOL bBMP,
            /* [in] */ BOOL bJPEG,
            /* [out] */ unsigned long __RPC_FAR *plSizeInMega);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBurnMediaCheckRetry )( 
            IPABurn __RPC_FAR * This,
            BOOL bRetry);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBurnJobInfo )( 
            IPABurn __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [out] */ JobInfo __RPC_FAR *pJobInfo,
            /* [size_is][size_is][out] */ PSSIInfo __RPC_FAR *__RPC_FAR *ppPSSIList,
            /* [out] */ long __RPC_FAR *pPSSILen,
            /* [size_is][size_is][out] */ JobDetailStruct __RPC_FAR *__RPC_FAR *ppDetailList,
            /* [out] */ long __RPC_FAR *pDetailLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsUnfinishedBurnJobExist )( 
            IPABurn __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBurnErrorMsg )( 
            IPABurn __RPC_FAR * This,
            /* [in] */ int iErrCode,
            /* [out] */ BSTR __RPC_FAR *bsErrMsg);
        
        END_INTERFACE
    } IPABurnVtbl;

    interface IPABurn
    {
        CONST_VTBL struct IPABurnVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPABurn_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPABurn_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPABurn_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPABurn_GetDevices(This,ppbsDevices,pLen)	\
    (This)->lpVtbl -> GetDevices(This,ppbsDevices,pLen)

#define IPABurn_GetCurrentDeviceMediaInfo(This)	\
    (This)->lpVtbl -> GetCurrentDeviceMediaInfo(This)

#define IPABurn_GetBurnSubModuleState(This,pSubModuleState)	\
    (This)->lpVtbl -> GetBurnSubModuleState(This,pSubModuleState)

#define IPABurn_SetBurnDevice(This,bsDeviceName)	\
    (This)->lpVtbl -> SetBurnDevice(This,bsDeviceName)

#define IPABurn_BurnByPA(This,pBurnJobSettingsByPA)	\
    (This)->lpVtbl -> BurnByPA(This,pBurnJobSettingsByPA)

#define IPABurn_BurnPrepare(This,lUIDNum,pbsUIDList,enumUIDType)	\
    (This)->lpVtbl -> BurnPrepare(This,lUIDNum,pbsUIDList,enumUIDType)

#define IPABurn_CancelBurnPrepare(This)	\
    (This)->lpVtbl -> CancelBurnPrepare(This)

#define IPABurn_GetEstimatedSize(This,bBMP,bJPEG,plSizeInMega)	\
    (This)->lpVtbl -> GetEstimatedSize(This,bBMP,bJPEG,plSizeInMega)

#define IPABurn_SetBurnMediaCheckRetry(This,bRetry)	\
    (This)->lpVtbl -> SetBurnMediaCheckRetry(This,bRetry)

#define IPABurn_GetBurnJobInfo(This,bsJobID,pJobInfo,ppPSSIList,pPSSILen,ppDetailList,pDetailLen)	\
    (This)->lpVtbl -> GetBurnJobInfo(This,bsJobID,pJobInfo,ppPSSIList,pPSSILen,ppDetailList,pDetailLen)

#define IPABurn_IsUnfinishedBurnJobExist(This,pbExist)	\
    (This)->lpVtbl -> IsUnfinishedBurnJobExist(This,pbExist)

#define IPABurn_GetBurnErrorMsg(This,iErrCode,bsErrMsg)	\
    (This)->lpVtbl -> GetBurnErrorMsg(This,iErrCode,bsErrMsg)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_GetDevices_Proxy( 
    IPABurn __RPC_FAR * This,
    /* [size_is][size_is][out] */ BSTR __RPC_FAR *__RPC_FAR *ppbsDevices,
    /* [out] */ long __RPC_FAR *pLen);


void __RPC_STUB IPABurn_GetDevices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_GetCurrentDeviceMediaInfo_Proxy( 
    IPABurn __RPC_FAR * This);


void __RPC_STUB IPABurn_GetCurrentDeviceMediaInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_GetBurnSubModuleState_Proxy( 
    IPABurn __RPC_FAR * This,
    /* [out] */ SubModuleState __RPC_FAR *pSubModuleState);


void __RPC_STUB IPABurn_GetBurnSubModuleState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_SetBurnDevice_Proxy( 
    IPABurn __RPC_FAR * This,
    /* [in] */ BSTR bsDeviceName);


void __RPC_STUB IPABurn_SetBurnDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_BurnByPA_Proxy( 
    IPABurn __RPC_FAR * This,
    /* [in] */ BurnJobSettingsByPA __RPC_FAR *pBurnJobSettingsByPA);


void __RPC_STUB IPABurn_BurnByPA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_BurnPrepare_Proxy( 
    IPABurn __RPC_FAR * This,
    /* [in] */ long lUIDNum,
    /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
    /* [in] */ PatientAdminUIDType enumUIDType);


void __RPC_STUB IPABurn_BurnPrepare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_CancelBurnPrepare_Proxy( 
    IPABurn __RPC_FAR * This);


void __RPC_STUB IPABurn_CancelBurnPrepare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_GetEstimatedSize_Proxy( 
    IPABurn __RPC_FAR * This,
    /* [in] */ BOOL bBMP,
    /* [in] */ BOOL bJPEG,
    /* [out] */ unsigned long __RPC_FAR *plSizeInMega);


void __RPC_STUB IPABurn_GetEstimatedSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_SetBurnMediaCheckRetry_Proxy( 
    IPABurn __RPC_FAR * This,
    BOOL bRetry);


void __RPC_STUB IPABurn_SetBurnMediaCheckRetry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_GetBurnJobInfo_Proxy( 
    IPABurn __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [out] */ JobInfo __RPC_FAR *pJobInfo,
    /* [size_is][size_is][out] */ PSSIInfo __RPC_FAR *__RPC_FAR *ppPSSIList,
    /* [out] */ long __RPC_FAR *pPSSILen,
    /* [size_is][size_is][out] */ JobDetailStruct __RPC_FAR *__RPC_FAR *ppDetailList,
    /* [out] */ long __RPC_FAR *pDetailLen);


void __RPC_STUB IPABurn_GetBurnJobInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_IsUnfinishedBurnJobExist_Proxy( 
    IPABurn __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbExist);


void __RPC_STUB IPABurn_IsUnfinishedBurnJobExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurn_GetBurnErrorMsg_Proxy( 
    IPABurn __RPC_FAR * This,
    /* [in] */ int iErrCode,
    /* [out] */ BSTR __RPC_FAR *bsErrMsg);


void __RPC_STUB IPABurn_GetBurnErrorMsg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPABurn_INTERFACE_DEFINED__ */


#ifndef __IPABurnEvent_INTERFACE_DEFINED__
#define __IPABurnEvent_INTERFACE_DEFINED__

/* interface IPABurnEvent */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPABurnEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2012F420-5CB4-4a89-9C35-E62B0E9EA5ED")
    IPABurnEvent : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnWorkStatus( 
            /* [in] */ SubModule enumSubModule,
            /* [in] */ SubModuleState enumSubModuleStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnDeviceStatusChanged( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnErrorCode( 
            /* [in] */ int iErrCode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnPhase( 
            /* [in] */ BSTR bsBurnPhase) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnLogLine( 
            /* [in] */ BSTR bsBurnLogLine) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnFileConflict( 
            /* [in] */ BSTR bsFirstFileName,
            /* [in] */ BSTR bsSecondFileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnPatientList( 
            /* [in] */ long lItemNum,
            /* [size_is][in] */ BurnPatientInfoStruct __RPC_FAR *pBurnPatientList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnStudyList( 
            /* [in] */ long lItemNum,
            /* [size_is][in] */ BurnStudyInfoStruct __RPC_FAR *pBurnStudyList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnSeriesList( 
            /* [in] */ long lItemNum,
            /* [size_is][in] */ BurnSeriesInfoStruct __RPC_FAR *pBurnSeriesList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnImageList( 
            /* [in] */ long lItemNum,
            /* [size_is][in] */ BurnImageInfoStruct __RPC_FAR *pBurnImageList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportDeviceSpeedInfo( 
            /* [in] */ long lItemNum,
            /* [size_is][in] */ BurnSpeedInfo __RPC_FAR *pSpeedInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportMediaInfo( 
            /* [in] */ BurnMediaInfo __RPC_FAR *pMediaInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportBurnMediaNotReady( 
            /* [in] */ BSTR bsInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPABurnEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPABurnEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPABurnEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnWorkStatus )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ SubModule enumSubModule,
            /* [in] */ SubModuleState enumSubModuleStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnDeviceStatusChanged )( 
            IPABurnEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnErrorCode )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ int iErrCode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnPhase )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ BSTR bsBurnPhase);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnLogLine )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ BSTR bsBurnLogLine);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnFileConflict )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ BSTR bsFirstFileName,
            /* [in] */ BSTR bsSecondFileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnPatientList )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ long lItemNum,
            /* [size_is][in] */ BurnPatientInfoStruct __RPC_FAR *pBurnPatientList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnStudyList )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ long lItemNum,
            /* [size_is][in] */ BurnStudyInfoStruct __RPC_FAR *pBurnStudyList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnSeriesList )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ long lItemNum,
            /* [size_is][in] */ BurnSeriesInfoStruct __RPC_FAR *pBurnSeriesList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnImageList )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ long lItemNum,
            /* [size_is][in] */ BurnImageInfoStruct __RPC_FAR *pBurnImageList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportDeviceSpeedInfo )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ long lItemNum,
            /* [size_is][in] */ BurnSpeedInfo __RPC_FAR *pSpeedInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportMediaInfo )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ BurnMediaInfo __RPC_FAR *pMediaInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportBurnMediaNotReady )( 
            IPABurnEvent __RPC_FAR * This,
            /* [in] */ BSTR bsInfo);
        
        END_INTERFACE
    } IPABurnEventVtbl;

    interface IPABurnEvent
    {
        CONST_VTBL struct IPABurnEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPABurnEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPABurnEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPABurnEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPABurnEvent_ReportBurnWorkStatus(This,enumSubModule,enumSubModuleStatus)	\
    (This)->lpVtbl -> ReportBurnWorkStatus(This,enumSubModule,enumSubModuleStatus)

#define IPABurnEvent_ReportBurnDeviceStatusChanged(This)	\
    (This)->lpVtbl -> ReportBurnDeviceStatusChanged(This)

#define IPABurnEvent_ReportBurnErrorCode(This,iErrCode)	\
    (This)->lpVtbl -> ReportBurnErrorCode(This,iErrCode)

#define IPABurnEvent_ReportBurnPhase(This,bsBurnPhase)	\
    (This)->lpVtbl -> ReportBurnPhase(This,bsBurnPhase)

#define IPABurnEvent_ReportBurnLogLine(This,bsBurnLogLine)	\
    (This)->lpVtbl -> ReportBurnLogLine(This,bsBurnLogLine)

#define IPABurnEvent_ReportBurnFileConflict(This,bsFirstFileName,bsSecondFileName)	\
    (This)->lpVtbl -> ReportBurnFileConflict(This,bsFirstFileName,bsSecondFileName)

#define IPABurnEvent_ReportBurnPatientList(This,lItemNum,pBurnPatientList)	\
    (This)->lpVtbl -> ReportBurnPatientList(This,lItemNum,pBurnPatientList)

#define IPABurnEvent_ReportBurnStudyList(This,lItemNum,pBurnStudyList)	\
    (This)->lpVtbl -> ReportBurnStudyList(This,lItemNum,pBurnStudyList)

#define IPABurnEvent_ReportBurnSeriesList(This,lItemNum,pBurnSeriesList)	\
    (This)->lpVtbl -> ReportBurnSeriesList(This,lItemNum,pBurnSeriesList)

#define IPABurnEvent_ReportBurnImageList(This,lItemNum,pBurnImageList)	\
    (This)->lpVtbl -> ReportBurnImageList(This,lItemNum,pBurnImageList)

#define IPABurnEvent_ReportDeviceSpeedInfo(This,lItemNum,pSpeedInfo)	\
    (This)->lpVtbl -> ReportDeviceSpeedInfo(This,lItemNum,pSpeedInfo)

#define IPABurnEvent_ReportMediaInfo(This,pMediaInfo)	\
    (This)->lpVtbl -> ReportMediaInfo(This,pMediaInfo)

#define IPABurnEvent_ReportBurnMediaNotReady(This,bsInfo)	\
    (This)->lpVtbl -> ReportBurnMediaNotReady(This,bsInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnWorkStatus_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ SubModule enumSubModule,
    /* [in] */ SubModuleState enumSubModuleStatus);


void __RPC_STUB IPABurnEvent_ReportBurnWorkStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnDeviceStatusChanged_Proxy( 
    IPABurnEvent __RPC_FAR * This);


void __RPC_STUB IPABurnEvent_ReportBurnDeviceStatusChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnErrorCode_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ int iErrCode);


void __RPC_STUB IPABurnEvent_ReportBurnErrorCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnPhase_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ BSTR bsBurnPhase);


void __RPC_STUB IPABurnEvent_ReportBurnPhase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnLogLine_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ BSTR bsBurnLogLine);


void __RPC_STUB IPABurnEvent_ReportBurnLogLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnFileConflict_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ BSTR bsFirstFileName,
    /* [in] */ BSTR bsSecondFileName);


void __RPC_STUB IPABurnEvent_ReportBurnFileConflict_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnPatientList_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ long lItemNum,
    /* [size_is][in] */ BurnPatientInfoStruct __RPC_FAR *pBurnPatientList);


void __RPC_STUB IPABurnEvent_ReportBurnPatientList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnStudyList_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ long lItemNum,
    /* [size_is][in] */ BurnStudyInfoStruct __RPC_FAR *pBurnStudyList);


void __RPC_STUB IPABurnEvent_ReportBurnStudyList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnSeriesList_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ long lItemNum,
    /* [size_is][in] */ BurnSeriesInfoStruct __RPC_FAR *pBurnSeriesList);


void __RPC_STUB IPABurnEvent_ReportBurnSeriesList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnImageList_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ long lItemNum,
    /* [size_is][in] */ BurnImageInfoStruct __RPC_FAR *pBurnImageList);


void __RPC_STUB IPABurnEvent_ReportBurnImageList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportDeviceSpeedInfo_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ long lItemNum,
    /* [size_is][in] */ BurnSpeedInfo __RPC_FAR *pSpeedInfo);


void __RPC_STUB IPABurnEvent_ReportDeviceSpeedInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportMediaInfo_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ BurnMediaInfo __RPC_FAR *pMediaInfo);


void __RPC_STUB IPABurnEvent_ReportMediaInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPABurnEvent_ReportBurnMediaNotReady_Proxy( 
    IPABurnEvent __RPC_FAR * This,
    /* [in] */ BSTR bsInfo);


void __RPC_STUB IPABurnEvent_ReportBurnMediaNotReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPABurnEvent_INTERFACE_DEFINED__ */


#ifndef __IPATransfer_INTERFACE_DEFINED__
#define __IPATransfer_INTERFACE_DEFINED__

/* interface IPATransfer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPATransfer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8FDD9FF8-2B05-4ef6-B4B4-38AAA485B619")
    IPATransfer : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AutoTransfer( 
            /* [in] */ BSTR bsUID,
            /* [in] */ PatientAdminUIDType enumUIDType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ManualTransfer( 
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
            /* [in] */ PatientAdminUIDType enumUIDType,
            /* [in] */ TransferJobSettingsByUID __RPC_FAR *pTransferJobSettings) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ManualTransferWithMultiServers( 
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
            /* [in] */ PatientAdminUIDType enumUIDType,
            /* [in] */ long lServerNum,
            /* [size_is][in] */ TransferJobSettingsByUID __RPC_FAR *pTransferJobSettings) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSendJobInfo( 
            /* [in] */ BSTR bsJobID,
            /* [out] */ JobInfo __RPC_FAR *pJobInfo,
            /* [size_is][size_is][out] */ PSSIInfo __RPC_FAR *__RPC_FAR *ppPSSIList,
            /* [out] */ long __RPC_FAR *pPSSILen,
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppNodeList,
            /* [out] */ long __RPC_FAR *pNodeLen,
            /* [size_is][size_is][out] */ JobDetailStruct __RPC_FAR *__RPC_FAR *ppDetailList,
            /* [out] */ long __RPC_FAR *pDetailLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTransferSubModuleState( 
            /* [out] */ SubModuleState __RPC_FAR *pSubModuleState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsUnfinishedTrnasferJobExist( 
            /* [out] */ BOOL __RPC_FAR *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAutoServers( 
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
            /* [out] */ long __RPC_FAR *pLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAutoServers( 
            /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
            /* [in] */ long lLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsAutoSendValid( 
            /* [out] */ BOOL __RPC_FAR *pbValid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetManualServers( 
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
            /* [out] */ long __RPC_FAR *pLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetManualServers( 
            /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
            /* [in] */ long lLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConnectTest( 
            /* [in] */ NetworkNode __RPC_FAR *pServer,
            /* [out] */ BOOL __RPC_FAR *pbResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetEnableAutoTransferStatus( 
            /* [in] */ BOOL bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEnableAutoTransferStatus( 
            /* [out] */ BOOL __RPC_FAR *bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAskforAutoTransfer( 
            /* [in] */ BOOL bAskfor) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAskforAutoTransfer( 
            /* [out] */ BOOL __RPC_FAR *bAskfor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPATransferVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPATransfer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPATransfer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPATransfer __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AutoTransfer )( 
            IPATransfer __RPC_FAR * This,
            /* [in] */ BSTR bsUID,
            /* [in] */ PatientAdminUIDType enumUIDType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ManualTransfer )( 
            IPATransfer __RPC_FAR * This,
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
            /* [in] */ PatientAdminUIDType enumUIDType,
            /* [in] */ TransferJobSettingsByUID __RPC_FAR *pTransferJobSettings);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ManualTransferWithMultiServers )( 
            IPATransfer __RPC_FAR * This,
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
            /* [in] */ PatientAdminUIDType enumUIDType,
            /* [in] */ long lServerNum,
            /* [size_is][in] */ TransferJobSettingsByUID __RPC_FAR *pTransferJobSettings);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSendJobInfo )( 
            IPATransfer __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [out] */ JobInfo __RPC_FAR *pJobInfo,
            /* [size_is][size_is][out] */ PSSIInfo __RPC_FAR *__RPC_FAR *ppPSSIList,
            /* [out] */ long __RPC_FAR *pPSSILen,
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppNodeList,
            /* [out] */ long __RPC_FAR *pNodeLen,
            /* [size_is][size_is][out] */ JobDetailStruct __RPC_FAR *__RPC_FAR *ppDetailList,
            /* [out] */ long __RPC_FAR *pDetailLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransferSubModuleState )( 
            IPATransfer __RPC_FAR * This,
            /* [out] */ SubModuleState __RPC_FAR *pSubModuleState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsUnfinishedTrnasferJobExist )( 
            IPATransfer __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAutoServers )( 
            IPATransfer __RPC_FAR * This,
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
            /* [out] */ long __RPC_FAR *pLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAutoServers )( 
            IPATransfer __RPC_FAR * This,
            /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
            /* [in] */ long lLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsAutoSendValid )( 
            IPATransfer __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbValid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetManualServers )( 
            IPATransfer __RPC_FAR * This,
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
            /* [out] */ long __RPC_FAR *pLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetManualServers )( 
            IPATransfer __RPC_FAR * This,
            /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
            /* [in] */ long lLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectTest )( 
            IPATransfer __RPC_FAR * This,
            /* [in] */ NetworkNode __RPC_FAR *pServer,
            /* [out] */ BOOL __RPC_FAR *pbResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEnableAutoTransferStatus )( 
            IPATransfer __RPC_FAR * This,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEnableAutoTransferStatus )( 
            IPATransfer __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAskforAutoTransfer )( 
            IPATransfer __RPC_FAR * This,
            /* [in] */ BOOL bAskfor);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAskforAutoTransfer )( 
            IPATransfer __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *bAskfor);
        
        END_INTERFACE
    } IPATransferVtbl;

    interface IPATransfer
    {
        CONST_VTBL struct IPATransferVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPATransfer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPATransfer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPATransfer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPATransfer_AutoTransfer(This,bsUID,enumUIDType)	\
    (This)->lpVtbl -> AutoTransfer(This,bsUID,enumUIDType)

#define IPATransfer_ManualTransfer(This,lUIDNum,pbsUIDList,enumUIDType,pTransferJobSettings)	\
    (This)->lpVtbl -> ManualTransfer(This,lUIDNum,pbsUIDList,enumUIDType,pTransferJobSettings)

#define IPATransfer_ManualTransferWithMultiServers(This,lUIDNum,pbsUIDList,enumUIDType,lServerNum,pTransferJobSettings)	\
    (This)->lpVtbl -> ManualTransferWithMultiServers(This,lUIDNum,pbsUIDList,enumUIDType,lServerNum,pTransferJobSettings)

#define IPATransfer_GetSendJobInfo(This,bsJobID,pJobInfo,ppPSSIList,pPSSILen,ppNodeList,pNodeLen,ppDetailList,pDetailLen)	\
    (This)->lpVtbl -> GetSendJobInfo(This,bsJobID,pJobInfo,ppPSSIList,pPSSILen,ppNodeList,pNodeLen,ppDetailList,pDetailLen)

#define IPATransfer_GetTransferSubModuleState(This,pSubModuleState)	\
    (This)->lpVtbl -> GetTransferSubModuleState(This,pSubModuleState)

#define IPATransfer_IsUnfinishedTrnasferJobExist(This,pbExist)	\
    (This)->lpVtbl -> IsUnfinishedTrnasferJobExist(This,pbExist)

#define IPATransfer_GetAutoServers(This,ppServers,pLen)	\
    (This)->lpVtbl -> GetAutoServers(This,ppServers,pLen)

#define IPATransfer_SetAutoServers(This,pServers,lLen)	\
    (This)->lpVtbl -> SetAutoServers(This,pServers,lLen)

#define IPATransfer_IsAutoSendValid(This,pbValid)	\
    (This)->lpVtbl -> IsAutoSendValid(This,pbValid)

#define IPATransfer_GetManualServers(This,ppServers,pLen)	\
    (This)->lpVtbl -> GetManualServers(This,ppServers,pLen)

#define IPATransfer_SetManualServers(This,pServers,lLen)	\
    (This)->lpVtbl -> SetManualServers(This,pServers,lLen)

#define IPATransfer_ConnectTest(This,pServer,pbResult)	\
    (This)->lpVtbl -> ConnectTest(This,pServer,pbResult)

#define IPATransfer_SetEnableAutoTransferStatus(This,bEnable)	\
    (This)->lpVtbl -> SetEnableAutoTransferStatus(This,bEnable)

#define IPATransfer_GetEnableAutoTransferStatus(This,bEnable)	\
    (This)->lpVtbl -> GetEnableAutoTransferStatus(This,bEnable)

#define IPATransfer_SetAskforAutoTransfer(This,bAskfor)	\
    (This)->lpVtbl -> SetAskforAutoTransfer(This,bAskfor)

#define IPATransfer_GetAskforAutoTransfer(This,bAskfor)	\
    (This)->lpVtbl -> GetAskforAutoTransfer(This,bAskfor)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_AutoTransfer_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [in] */ BSTR bsUID,
    /* [in] */ PatientAdminUIDType enumUIDType);


void __RPC_STUB IPATransfer_AutoTransfer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_ManualTransfer_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [in] */ long lUIDNum,
    /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
    /* [in] */ PatientAdminUIDType enumUIDType,
    /* [in] */ TransferJobSettingsByUID __RPC_FAR *pTransferJobSettings);


void __RPC_STUB IPATransfer_ManualTransfer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_ManualTransferWithMultiServers_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [in] */ long lUIDNum,
    /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
    /* [in] */ PatientAdminUIDType enumUIDType,
    /* [in] */ long lServerNum,
    /* [size_is][in] */ TransferJobSettingsByUID __RPC_FAR *pTransferJobSettings);


void __RPC_STUB IPATransfer_ManualTransferWithMultiServers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_GetSendJobInfo_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [out] */ JobInfo __RPC_FAR *pJobInfo,
    /* [size_is][size_is][out] */ PSSIInfo __RPC_FAR *__RPC_FAR *ppPSSIList,
    /* [out] */ long __RPC_FAR *pPSSILen,
    /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppNodeList,
    /* [out] */ long __RPC_FAR *pNodeLen,
    /* [size_is][size_is][out] */ JobDetailStruct __RPC_FAR *__RPC_FAR *ppDetailList,
    /* [out] */ long __RPC_FAR *pDetailLen);


void __RPC_STUB IPATransfer_GetSendJobInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_GetTransferSubModuleState_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [out] */ SubModuleState __RPC_FAR *pSubModuleState);


void __RPC_STUB IPATransfer_GetTransferSubModuleState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_IsUnfinishedTrnasferJobExist_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbExist);


void __RPC_STUB IPATransfer_IsUnfinishedTrnasferJobExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_GetAutoServers_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
    /* [out] */ long __RPC_FAR *pLen);


void __RPC_STUB IPATransfer_GetAutoServers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_SetAutoServers_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
    /* [in] */ long lLen);


void __RPC_STUB IPATransfer_SetAutoServers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_IsAutoSendValid_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbValid);


void __RPC_STUB IPATransfer_IsAutoSendValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_GetManualServers_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
    /* [out] */ long __RPC_FAR *pLen);


void __RPC_STUB IPATransfer_GetManualServers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_SetManualServers_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
    /* [in] */ long lLen);


void __RPC_STUB IPATransfer_SetManualServers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_ConnectTest_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [in] */ NetworkNode __RPC_FAR *pServer,
    /* [out] */ BOOL __RPC_FAR *pbResult);


void __RPC_STUB IPATransfer_ConnectTest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_SetEnableAutoTransferStatus_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IPATransfer_SetEnableAutoTransferStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_GetEnableAutoTransferStatus_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *bEnable);


void __RPC_STUB IPATransfer_GetEnableAutoTransferStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_SetAskforAutoTransfer_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [in] */ BOOL bAskfor);


void __RPC_STUB IPATransfer_SetAskforAutoTransfer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransfer_GetAskforAutoTransfer_Proxy( 
    IPATransfer __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *bAskfor);


void __RPC_STUB IPATransfer_GetAskforAutoTransfer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPATransfer_INTERFACE_DEFINED__ */


#ifndef __IPATransferEvent_INTERFACE_DEFINED__
#define __IPATransferEvent_INTERFACE_DEFINED__

/* interface IPATransferEvent */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPATransferEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FA5E8DD5-2A58-478c-A9A6-EB884A758B71")
    IPATransferEvent : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportTransferWorkStatus( 
            /* [in] */ SubModule enumSubModule,
            /* [in] */ SubModuleState enumSubUnitStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportUITransferChangeDB( 
            /* [in] */ BSTR bstPatientUID,
            /* [in] */ BSTR bstStudyUID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPATransferEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPATransferEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPATransferEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPATransferEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportTransferWorkStatus )( 
            IPATransferEvent __RPC_FAR * This,
            /* [in] */ SubModule enumSubModule,
            /* [in] */ SubModuleState enumSubUnitStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportUITransferChangeDB )( 
            IPATransferEvent __RPC_FAR * This,
            /* [in] */ BSTR bstPatientUID,
            /* [in] */ BSTR bstStudyUID);
        
        END_INTERFACE
    } IPATransferEventVtbl;

    interface IPATransferEvent
    {
        CONST_VTBL struct IPATransferEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPATransferEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPATransferEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPATransferEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPATransferEvent_ReportTransferWorkStatus(This,enumSubModule,enumSubUnitStatus)	\
    (This)->lpVtbl -> ReportTransferWorkStatus(This,enumSubModule,enumSubUnitStatus)

#define IPATransferEvent_ReportUITransferChangeDB(This,bstPatientUID,bstStudyUID)	\
    (This)->lpVtbl -> ReportUITransferChangeDB(This,bstPatientUID,bstStudyUID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransferEvent_ReportTransferWorkStatus_Proxy( 
    IPATransferEvent __RPC_FAR * This,
    /* [in] */ SubModule enumSubModule,
    /* [in] */ SubModuleState enumSubUnitStatus);


void __RPC_STUB IPATransferEvent_ReportTransferWorkStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPATransferEvent_ReportUITransferChangeDB_Proxy( 
    IPATransferEvent __RPC_FAR * This,
    /* [in] */ BSTR bstPatientUID,
    /* [in] */ BSTR bstStudyUID);


void __RPC_STUB IPATransferEvent_ReportUITransferChangeDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPATransferEvent_INTERFACE_DEFINED__ */


#ifndef __IPADiscImport_INTERFACE_DEFINED__
#define __IPADiscImport_INTERFACE_DEFINED__

/* interface IPADiscImport */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPADiscImport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05728D18-93CE-47b0-B0E4-C5BD332C9B1C")
    IPADiscImport : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDiscImportDevices( 
            /* [size_is][size_is][out] */ BSTR __RPC_FAR *__RPC_FAR *ppbsDevices,
            /* [out] */ long __RPC_FAR *pLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImportDiscInfoNotify( 
            BSTR bsDevice) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImportDiscInfo( 
            /* [size_is][size_is][out] */ DiscImportPatientInfo __RPC_FAR *__RPC_FAR *ppPatients,
            /* [out] */ long __RPC_FAR *pPatientNum,
            /* [size_is][size_is][out] */ DiscImportStudyInfo __RPC_FAR *__RPC_FAR *ppStudies,
            /* [out] */ long __RPC_FAR *pStudyNum,
            /* [size_is][size_is][out] */ DiscImportSeriesInfo __RPC_FAR *__RPC_FAR *ppSeries,
            /* [out] */ long __RPC_FAR *pSeriesNum,
            /* [size_is][size_is][out] */ DiscImportImageInfo __RPC_FAR *__RPC_FAR *ppImages,
            /* [out] */ long __RPC_FAR *pImageNum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CancelGetImportDiscInfo( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DiscImport( 
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
            /* [in] */ PatientAdminUIDType enumUIDType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDiscImportJobInfo( 
            /* [in] */ BSTR bsJobID,
            /* [size_is][size_is][out] */ DiscImport_SeriesStruct __RPC_FAR *__RPC_FAR *ppSeriesList,
            /* [out] */ long __RPC_FAR *pLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsUnfinishedDiscImportJobExist( 
            /* [out] */ BOOL __RPC_FAR *pbExist) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDiscImportSubModuleState( 
            /* [out] */ SubModuleState __RPC_FAR *pSubModuleState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPADiscImportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPADiscImport __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPADiscImport __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPADiscImport __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDiscImportDevices )( 
            IPADiscImport __RPC_FAR * This,
            /* [size_is][size_is][out] */ BSTR __RPC_FAR *__RPC_FAR *ppbsDevices,
            /* [out] */ long __RPC_FAR *pLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImportDiscInfoNotify )( 
            IPADiscImport __RPC_FAR * This,
            BSTR bsDevice);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImportDiscInfo )( 
            IPADiscImport __RPC_FAR * This,
            /* [size_is][size_is][out] */ DiscImportPatientInfo __RPC_FAR *__RPC_FAR *ppPatients,
            /* [out] */ long __RPC_FAR *pPatientNum,
            /* [size_is][size_is][out] */ DiscImportStudyInfo __RPC_FAR *__RPC_FAR *ppStudies,
            /* [out] */ long __RPC_FAR *pStudyNum,
            /* [size_is][size_is][out] */ DiscImportSeriesInfo __RPC_FAR *__RPC_FAR *ppSeries,
            /* [out] */ long __RPC_FAR *pSeriesNum,
            /* [size_is][size_is][out] */ DiscImportImageInfo __RPC_FAR *__RPC_FAR *ppImages,
            /* [out] */ long __RPC_FAR *pImageNum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelGetImportDiscInfo )( 
            IPADiscImport __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DiscImport )( 
            IPADiscImport __RPC_FAR * This,
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
            /* [in] */ PatientAdminUIDType enumUIDType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDiscImportJobInfo )( 
            IPADiscImport __RPC_FAR * This,
            /* [in] */ BSTR bsJobID,
            /* [size_is][size_is][out] */ DiscImport_SeriesStruct __RPC_FAR *__RPC_FAR *ppSeriesList,
            /* [out] */ long __RPC_FAR *pLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsUnfinishedDiscImportJobExist )( 
            IPADiscImport __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbExist);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDiscImportSubModuleState )( 
            IPADiscImport __RPC_FAR * This,
            /* [out] */ SubModuleState __RPC_FAR *pSubModuleState);
        
        END_INTERFACE
    } IPADiscImportVtbl;

    interface IPADiscImport
    {
        CONST_VTBL struct IPADiscImportVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPADiscImport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPADiscImport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPADiscImport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPADiscImport_GetDiscImportDevices(This,ppbsDevices,pLen)	\
    (This)->lpVtbl -> GetDiscImportDevices(This,ppbsDevices,pLen)

#define IPADiscImport_GetImportDiscInfoNotify(This,bsDevice)	\
    (This)->lpVtbl -> GetImportDiscInfoNotify(This,bsDevice)

#define IPADiscImport_GetImportDiscInfo(This,ppPatients,pPatientNum,ppStudies,pStudyNum,ppSeries,pSeriesNum,ppImages,pImageNum)	\
    (This)->lpVtbl -> GetImportDiscInfo(This,ppPatients,pPatientNum,ppStudies,pStudyNum,ppSeries,pSeriesNum,ppImages,pImageNum)

#define IPADiscImport_CancelGetImportDiscInfo(This)	\
    (This)->lpVtbl -> CancelGetImportDiscInfo(This)

#define IPADiscImport_DiscImport(This,lUIDNum,pbsUIDList,enumUIDType)	\
    (This)->lpVtbl -> DiscImport(This,lUIDNum,pbsUIDList,enumUIDType)

#define IPADiscImport_GetDiscImportJobInfo(This,bsJobID,ppSeriesList,pLen)	\
    (This)->lpVtbl -> GetDiscImportJobInfo(This,bsJobID,ppSeriesList,pLen)

#define IPADiscImport_IsUnfinishedDiscImportJobExist(This,pbExist)	\
    (This)->lpVtbl -> IsUnfinishedDiscImportJobExist(This,pbExist)

#define IPADiscImport_GetDiscImportSubModuleState(This,pSubModuleState)	\
    (This)->lpVtbl -> GetDiscImportSubModuleState(This,pSubModuleState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImport_GetDiscImportDevices_Proxy( 
    IPADiscImport __RPC_FAR * This,
    /* [size_is][size_is][out] */ BSTR __RPC_FAR *__RPC_FAR *ppbsDevices,
    /* [out] */ long __RPC_FAR *pLen);


void __RPC_STUB IPADiscImport_GetDiscImportDevices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImport_GetImportDiscInfoNotify_Proxy( 
    IPADiscImport __RPC_FAR * This,
    BSTR bsDevice);


void __RPC_STUB IPADiscImport_GetImportDiscInfoNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImport_GetImportDiscInfo_Proxy( 
    IPADiscImport __RPC_FAR * This,
    /* [size_is][size_is][out] */ DiscImportPatientInfo __RPC_FAR *__RPC_FAR *ppPatients,
    /* [out] */ long __RPC_FAR *pPatientNum,
    /* [size_is][size_is][out] */ DiscImportStudyInfo __RPC_FAR *__RPC_FAR *ppStudies,
    /* [out] */ long __RPC_FAR *pStudyNum,
    /* [size_is][size_is][out] */ DiscImportSeriesInfo __RPC_FAR *__RPC_FAR *ppSeries,
    /* [out] */ long __RPC_FAR *pSeriesNum,
    /* [size_is][size_is][out] */ DiscImportImageInfo __RPC_FAR *__RPC_FAR *ppImages,
    /* [out] */ long __RPC_FAR *pImageNum);


void __RPC_STUB IPADiscImport_GetImportDiscInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImport_CancelGetImportDiscInfo_Proxy( 
    IPADiscImport __RPC_FAR * This);


void __RPC_STUB IPADiscImport_CancelGetImportDiscInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImport_DiscImport_Proxy( 
    IPADiscImport __RPC_FAR * This,
    /* [in] */ long lUIDNum,
    /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDList,
    /* [in] */ PatientAdminUIDType enumUIDType);


void __RPC_STUB IPADiscImport_DiscImport_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImport_GetDiscImportJobInfo_Proxy( 
    IPADiscImport __RPC_FAR * This,
    /* [in] */ BSTR bsJobID,
    /* [size_is][size_is][out] */ DiscImport_SeriesStruct __RPC_FAR *__RPC_FAR *ppSeriesList,
    /* [out] */ long __RPC_FAR *pLen);


void __RPC_STUB IPADiscImport_GetDiscImportJobInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImport_IsUnfinishedDiscImportJobExist_Proxy( 
    IPADiscImport __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbExist);


void __RPC_STUB IPADiscImport_IsUnfinishedDiscImportJobExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImport_GetDiscImportSubModuleState_Proxy( 
    IPADiscImport __RPC_FAR * This,
    /* [out] */ SubModuleState __RPC_FAR *pSubModuleState);


void __RPC_STUB IPADiscImport_GetDiscImportSubModuleState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPADiscImport_INTERFACE_DEFINED__ */


#ifndef __IPADiscImportEvent_INTERFACE_DEFINED__
#define __IPADiscImportEvent_INTERFACE_DEFINED__

/* interface IPADiscImportEvent */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPADiscImportEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5117A6B0-DD8B-4fef-A71D-E119B16EA736")
    IPADiscImportEvent : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportDiscImportWorkStatus( 
            /* [in] */ SubModule enumSubModule,
            /* [in] */ SubModuleState enumSubModuleStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportDiscImportDiscInfo( 
            /* [in] */ BOOL bReady) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportDiscImportDiscInfoState( 
            /* [in] */ BSTR bsState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportDiscImportSeriesStateChanged( 
            /* [in] */ DiscImport_SeriesStateStruct __RPC_FAR *pState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportDiscImportSeriesProgressChanged( 
            /* [in] */ DiscImport_SeriesProgressStruct __RPC_FAR *pProgress) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportDiscImportSeriesDetailChanged( 
            /* [in] */ DiscImport_SeriesDetailStruct __RPC_FAR *pDetail) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportDiscImportOneImageImported( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportDiscImportOneJobFinished( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPADiscImportEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPADiscImportEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPADiscImportEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPADiscImportEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportDiscImportWorkStatus )( 
            IPADiscImportEvent __RPC_FAR * This,
            /* [in] */ SubModule enumSubModule,
            /* [in] */ SubModuleState enumSubModuleStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportDiscImportDiscInfo )( 
            IPADiscImportEvent __RPC_FAR * This,
            /* [in] */ BOOL bReady);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportDiscImportDiscInfoState )( 
            IPADiscImportEvent __RPC_FAR * This,
            /* [in] */ BSTR bsState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportDiscImportSeriesStateChanged )( 
            IPADiscImportEvent __RPC_FAR * This,
            /* [in] */ DiscImport_SeriesStateStruct __RPC_FAR *pState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportDiscImportSeriesProgressChanged )( 
            IPADiscImportEvent __RPC_FAR * This,
            /* [in] */ DiscImport_SeriesProgressStruct __RPC_FAR *pProgress);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportDiscImportSeriesDetailChanged )( 
            IPADiscImportEvent __RPC_FAR * This,
            /* [in] */ DiscImport_SeriesDetailStruct __RPC_FAR *pDetail);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportDiscImportOneImageImported )( 
            IPADiscImportEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportDiscImportOneJobFinished )( 
            IPADiscImportEvent __RPC_FAR * This);
        
        END_INTERFACE
    } IPADiscImportEventVtbl;

    interface IPADiscImportEvent
    {
        CONST_VTBL struct IPADiscImportEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPADiscImportEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPADiscImportEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPADiscImportEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPADiscImportEvent_ReportDiscImportWorkStatus(This,enumSubModule,enumSubModuleStatus)	\
    (This)->lpVtbl -> ReportDiscImportWorkStatus(This,enumSubModule,enumSubModuleStatus)

#define IPADiscImportEvent_ReportDiscImportDiscInfo(This,bReady)	\
    (This)->lpVtbl -> ReportDiscImportDiscInfo(This,bReady)

#define IPADiscImportEvent_ReportDiscImportDiscInfoState(This,bsState)	\
    (This)->lpVtbl -> ReportDiscImportDiscInfoState(This,bsState)

#define IPADiscImportEvent_ReportDiscImportSeriesStateChanged(This,pState)	\
    (This)->lpVtbl -> ReportDiscImportSeriesStateChanged(This,pState)

#define IPADiscImportEvent_ReportDiscImportSeriesProgressChanged(This,pProgress)	\
    (This)->lpVtbl -> ReportDiscImportSeriesProgressChanged(This,pProgress)

#define IPADiscImportEvent_ReportDiscImportSeriesDetailChanged(This,pDetail)	\
    (This)->lpVtbl -> ReportDiscImportSeriesDetailChanged(This,pDetail)

#define IPADiscImportEvent_ReportDiscImportOneImageImported(This)	\
    (This)->lpVtbl -> ReportDiscImportOneImageImported(This)

#define IPADiscImportEvent_ReportDiscImportOneJobFinished(This)	\
    (This)->lpVtbl -> ReportDiscImportOneJobFinished(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImportEvent_ReportDiscImportWorkStatus_Proxy( 
    IPADiscImportEvent __RPC_FAR * This,
    /* [in] */ SubModule enumSubModule,
    /* [in] */ SubModuleState enumSubModuleStatus);


void __RPC_STUB IPADiscImportEvent_ReportDiscImportWorkStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImportEvent_ReportDiscImportDiscInfo_Proxy( 
    IPADiscImportEvent __RPC_FAR * This,
    /* [in] */ BOOL bReady);


void __RPC_STUB IPADiscImportEvent_ReportDiscImportDiscInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImportEvent_ReportDiscImportDiscInfoState_Proxy( 
    IPADiscImportEvent __RPC_FAR * This,
    /* [in] */ BSTR bsState);


void __RPC_STUB IPADiscImportEvent_ReportDiscImportDiscInfoState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImportEvent_ReportDiscImportSeriesStateChanged_Proxy( 
    IPADiscImportEvent __RPC_FAR * This,
    /* [in] */ DiscImport_SeriesStateStruct __RPC_FAR *pState);


void __RPC_STUB IPADiscImportEvent_ReportDiscImportSeriesStateChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImportEvent_ReportDiscImportSeriesProgressChanged_Proxy( 
    IPADiscImportEvent __RPC_FAR * This,
    /* [in] */ DiscImport_SeriesProgressStruct __RPC_FAR *pProgress);


void __RPC_STUB IPADiscImportEvent_ReportDiscImportSeriesProgressChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImportEvent_ReportDiscImportSeriesDetailChanged_Proxy( 
    IPADiscImportEvent __RPC_FAR * This,
    /* [in] */ DiscImport_SeriesDetailStruct __RPC_FAR *pDetail);


void __RPC_STUB IPADiscImportEvent_ReportDiscImportSeriesDetailChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImportEvent_ReportDiscImportOneImageImported_Proxy( 
    IPADiscImportEvent __RPC_FAR * This);


void __RPC_STUB IPADiscImportEvent_ReportDiscImportOneImageImported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPADiscImportEvent_ReportDiscImportOneJobFinished_Proxy( 
    IPADiscImportEvent __RPC_FAR * This);


void __RPC_STUB IPADiscImportEvent_ReportDiscImportOneJobFinished_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPADiscImportEvent_INTERFACE_DEFINED__ */


#ifndef __IPAWLMPPS_INTERFACE_DEFINED__
#define __IPAWLMPPS_INTERFACE_DEFINED__

/* interface IPAWLMPPS */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPAWLMPPS;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1DA2C81-616B-4a34-A2BE-0439A93E9A47")
    IPAWLMPPS : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWlMppsSubModuleState( 
            /* [out] */ SubModuleState __RPC_FAR *pSubModuleState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWorkList( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RefreshWorkList( 
            /* [in] */ WorkListQueryCond __RPC_FAR *pWorkListQueryCond) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImportPatientStudyInfo( 
            /* [in] */ BSTR bsStudyInstanceUID,
            /* [out] */ WLPatientStudyStruct __RPC_FAR *pStruct) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsStudyImported( 
            /* [in] */ BSTR bsStudyInstanceUID,
            /* [out] */ WLPatientStudyStatusInDB __RPC_FAR *pStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StudyImported( 
            /* [in] */ BSTR bsStudyInstanceUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteAllImportedStudyRecords( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsMPPSValid( 
            /* [out] */ BOOL __RPC_FAR *pbValid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsSetMPPSStatusEnabled( 
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ BOOL __RPC_FAR *pbEnabled) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStudyMPPSStatus( 
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ WorkListStatus __RPC_FAR *penumStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMPPSStatus( 
            /* [in] */ BSTR bsStudyUID,
            /* [in] */ WorkListStatus enumStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsWorkListWorking( 
            /* [out] */ BOOL __RPC_FAR *pbWorking) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsMppsWorking( 
            /* [out] */ BOOL __RPC_FAR *pbWorking) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsClosingStudyMPPS( 
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ BOOL __RPC_FAR *pbClosing) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsSettingPatientOrStudyMPPS( 
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDs,
            /* [in] */ PatientAdminUIDType enumUIDType,
            /* [out] */ BOOL __RPC_FAR *pbSetting) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWlServers( 
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
            /* [out] */ long __RPC_FAR *pLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetWlServers( 
            /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
            /* [in] */ long lLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE WlServerConnectTest( 
            /* [in] */ NetworkNode __RPC_FAR *pServer,
            /* [out] */ BOOL __RPC_FAR *pbResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMppsServers( 
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
            /* [out] */ long __RPC_FAR *pLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMppsServers( 
            /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
            /* [in] */ long lLen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MppsServerConnectTest( 
            /* [in] */ NetworkNode __RPC_FAR *pServer,
            /* [out] */ BOOL __RPC_FAR *pbResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPAWLMPPSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPAWLMPPS __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPAWLMPPS __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWlMppsSubModuleState )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [out] */ SubModuleState __RPC_FAR *pSubModuleState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWorkList )( 
            IPAWLMPPS __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RefreshWorkList )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ WorkListQueryCond __RPC_FAR *pWorkListQueryCond);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImportPatientStudyInfo )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ BSTR bsStudyInstanceUID,
            /* [out] */ WLPatientStudyStruct __RPC_FAR *pStruct);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsStudyImported )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ BSTR bsStudyInstanceUID,
            /* [out] */ WLPatientStudyStatusInDB __RPC_FAR *pStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StudyImported )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ BSTR bsStudyInstanceUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteAllImportedStudyRecords )( 
            IPAWLMPPS __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsMPPSValid )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbValid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSetMPPSStatusEnabled )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ BOOL __RPC_FAR *pbEnabled);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStudyMPPSStatus )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ WorkListStatus __RPC_FAR *penumStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMPPSStatus )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [in] */ WorkListStatus enumStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsWorkListWorking )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbWorking);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsMppsWorking )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbWorking);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsClosingStudyMPPS )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [out] */ BOOL __RPC_FAR *pbClosing);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSettingPatientOrStudyMPPS )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ long lUIDNum,
            /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDs,
            /* [in] */ PatientAdminUIDType enumUIDType,
            /* [out] */ BOOL __RPC_FAR *pbSetting);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWlServers )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
            /* [out] */ long __RPC_FAR *pLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWlServers )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
            /* [in] */ long lLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WlServerConnectTest )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ NetworkNode __RPC_FAR *pServer,
            /* [out] */ BOOL __RPC_FAR *pbResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMppsServers )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
            /* [out] */ long __RPC_FAR *pLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMppsServers )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
            /* [in] */ long lLen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MppsServerConnectTest )( 
            IPAWLMPPS __RPC_FAR * This,
            /* [in] */ NetworkNode __RPC_FAR *pServer,
            /* [out] */ BOOL __RPC_FAR *pbResult);
        
        END_INTERFACE
    } IPAWLMPPSVtbl;

    interface IPAWLMPPS
    {
        CONST_VTBL struct IPAWLMPPSVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPAWLMPPS_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPAWLMPPS_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPAWLMPPS_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPAWLMPPS_GetWlMppsSubModuleState(This,pSubModuleState)	\
    (This)->lpVtbl -> GetWlMppsSubModuleState(This,pSubModuleState)

#define IPAWLMPPS_GetWorkList(This)	\
    (This)->lpVtbl -> GetWorkList(This)

#define IPAWLMPPS_RefreshWorkList(This,pWorkListQueryCond)	\
    (This)->lpVtbl -> RefreshWorkList(This,pWorkListQueryCond)

#define IPAWLMPPS_GetImportPatientStudyInfo(This,bsStudyInstanceUID,pStruct)	\
    (This)->lpVtbl -> GetImportPatientStudyInfo(This,bsStudyInstanceUID,pStruct)

#define IPAWLMPPS_IsStudyImported(This,bsStudyInstanceUID,pStatus)	\
    (This)->lpVtbl -> IsStudyImported(This,bsStudyInstanceUID,pStatus)

#define IPAWLMPPS_StudyImported(This,bsStudyInstanceUID)	\
    (This)->lpVtbl -> StudyImported(This,bsStudyInstanceUID)

#define IPAWLMPPS_DeleteAllImportedStudyRecords(This)	\
    (This)->lpVtbl -> DeleteAllImportedStudyRecords(This)

#define IPAWLMPPS_IsMPPSValid(This,pbValid)	\
    (This)->lpVtbl -> IsMPPSValid(This,pbValid)

#define IPAWLMPPS_IsSetMPPSStatusEnabled(This,bsStudyUID,pbEnabled)	\
    (This)->lpVtbl -> IsSetMPPSStatusEnabled(This,bsStudyUID,pbEnabled)

#define IPAWLMPPS_GetStudyMPPSStatus(This,bsStudyUID,penumStatus)	\
    (This)->lpVtbl -> GetStudyMPPSStatus(This,bsStudyUID,penumStatus)

#define IPAWLMPPS_SetMPPSStatus(This,bsStudyUID,enumStatus)	\
    (This)->lpVtbl -> SetMPPSStatus(This,bsStudyUID,enumStatus)

#define IPAWLMPPS_IsWorkListWorking(This,pbWorking)	\
    (This)->lpVtbl -> IsWorkListWorking(This,pbWorking)

#define IPAWLMPPS_IsMppsWorking(This,pbWorking)	\
    (This)->lpVtbl -> IsMppsWorking(This,pbWorking)

#define IPAWLMPPS_IsClosingStudyMPPS(This,bsStudyUID,pbClosing)	\
    (This)->lpVtbl -> IsClosingStudyMPPS(This,bsStudyUID,pbClosing)

#define IPAWLMPPS_IsSettingPatientOrStudyMPPS(This,lUIDNum,pbsUIDs,enumUIDType,pbSetting)	\
    (This)->lpVtbl -> IsSettingPatientOrStudyMPPS(This,lUIDNum,pbsUIDs,enumUIDType,pbSetting)

#define IPAWLMPPS_GetWlServers(This,ppServers,pLen)	\
    (This)->lpVtbl -> GetWlServers(This,ppServers,pLen)

#define IPAWLMPPS_SetWlServers(This,pServers,lLen)	\
    (This)->lpVtbl -> SetWlServers(This,pServers,lLen)

#define IPAWLMPPS_WlServerConnectTest(This,pServer,pbResult)	\
    (This)->lpVtbl -> WlServerConnectTest(This,pServer,pbResult)

#define IPAWLMPPS_GetMppsServers(This,ppServers,pLen)	\
    (This)->lpVtbl -> GetMppsServers(This,ppServers,pLen)

#define IPAWLMPPS_SetMppsServers(This,pServers,lLen)	\
    (This)->lpVtbl -> SetMppsServers(This,pServers,lLen)

#define IPAWLMPPS_MppsServerConnectTest(This,pServer,pbResult)	\
    (This)->lpVtbl -> MppsServerConnectTest(This,pServer,pbResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_GetWlMppsSubModuleState_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [out] */ SubModuleState __RPC_FAR *pSubModuleState);


void __RPC_STUB IPAWLMPPS_GetWlMppsSubModuleState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_GetWorkList_Proxy( 
    IPAWLMPPS __RPC_FAR * This);


void __RPC_STUB IPAWLMPPS_GetWorkList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_RefreshWorkList_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ WorkListQueryCond __RPC_FAR *pWorkListQueryCond);


void __RPC_STUB IPAWLMPPS_RefreshWorkList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_GetImportPatientStudyInfo_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ BSTR bsStudyInstanceUID,
    /* [out] */ WLPatientStudyStruct __RPC_FAR *pStruct);


void __RPC_STUB IPAWLMPPS_GetImportPatientStudyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_IsStudyImported_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ BSTR bsStudyInstanceUID,
    /* [out] */ WLPatientStudyStatusInDB __RPC_FAR *pStatus);


void __RPC_STUB IPAWLMPPS_IsStudyImported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_StudyImported_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ BSTR bsStudyInstanceUID);


void __RPC_STUB IPAWLMPPS_StudyImported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_DeleteAllImportedStudyRecords_Proxy( 
    IPAWLMPPS __RPC_FAR * This);


void __RPC_STUB IPAWLMPPS_DeleteAllImportedStudyRecords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_IsMPPSValid_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbValid);


void __RPC_STUB IPAWLMPPS_IsMPPSValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_IsSetMPPSStatusEnabled_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [out] */ BOOL __RPC_FAR *pbEnabled);


void __RPC_STUB IPAWLMPPS_IsSetMPPSStatusEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_GetStudyMPPSStatus_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [out] */ WorkListStatus __RPC_FAR *penumStatus);


void __RPC_STUB IPAWLMPPS_GetStudyMPPSStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_SetMPPSStatus_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [in] */ WorkListStatus enumStatus);


void __RPC_STUB IPAWLMPPS_SetMPPSStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_IsWorkListWorking_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbWorking);


void __RPC_STUB IPAWLMPPS_IsWorkListWorking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_IsMppsWorking_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbWorking);


void __RPC_STUB IPAWLMPPS_IsMppsWorking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_IsClosingStudyMPPS_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [out] */ BOOL __RPC_FAR *pbClosing);


void __RPC_STUB IPAWLMPPS_IsClosingStudyMPPS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_IsSettingPatientOrStudyMPPS_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ long lUIDNum,
    /* [size_is][in] */ BSTR __RPC_FAR *pbsUIDs,
    /* [in] */ PatientAdminUIDType enumUIDType,
    /* [out] */ BOOL __RPC_FAR *pbSetting);


void __RPC_STUB IPAWLMPPS_IsSettingPatientOrStudyMPPS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_GetWlServers_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
    /* [out] */ long __RPC_FAR *pLen);


void __RPC_STUB IPAWLMPPS_GetWlServers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_SetWlServers_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
    /* [in] */ long lLen);


void __RPC_STUB IPAWLMPPS_SetWlServers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_WlServerConnectTest_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ NetworkNode __RPC_FAR *pServer,
    /* [out] */ BOOL __RPC_FAR *pbResult);


void __RPC_STUB IPAWLMPPS_WlServerConnectTest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_GetMppsServers_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [size_is][size_is][out] */ NetworkNode __RPC_FAR *__RPC_FAR *ppServers,
    /* [out] */ long __RPC_FAR *pLen);


void __RPC_STUB IPAWLMPPS_GetMppsServers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_SetMppsServers_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [size_is][in] */ NetworkNode __RPC_FAR *pServers,
    /* [in] */ long lLen);


void __RPC_STUB IPAWLMPPS_SetMppsServers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPS_MppsServerConnectTest_Proxy( 
    IPAWLMPPS __RPC_FAR * This,
    /* [in] */ NetworkNode __RPC_FAR *pServer,
    /* [out] */ BOOL __RPC_FAR *pbResult);


void __RPC_STUB IPAWLMPPS_MppsServerConnectTest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPAWLMPPS_INTERFACE_DEFINED__ */


#ifndef __IPAWLMPPSEvent_INTERFACE_DEFINED__
#define __IPAWLMPPSEvent_INTERFACE_DEFINED__

/* interface IPAWLMPPSEvent */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPAWLMPPSEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A51CEFB-ABF4-42a6-81D7-9D3418CA493B")
    IPAWLMPPSEvent : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportWlMppsWorkStatus( 
            /* [in] */ SubModule enumSubModule,
            /* [in] */ SubModuleState enumSubModuleStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportWorkList( 
            /* [in] */ long lItemNum,
            /* [size_is][in] */ WorkListStruct __RPC_FAR *pWorkList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportSetMPPSStatusFinished( 
            /* [in] */ MppsSetResult __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportMPPSStatusChanged( 
            /* [in] */ BSTR bsStudyUID,
            /* [in] */ WorkListStatus enumStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPAWLMPPSEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPAWLMPPSEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPAWLMPPSEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPAWLMPPSEvent __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportWlMppsWorkStatus )( 
            IPAWLMPPSEvent __RPC_FAR * This,
            /* [in] */ SubModule enumSubModule,
            /* [in] */ SubModuleState enumSubModuleStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportWorkList )( 
            IPAWLMPPSEvent __RPC_FAR * This,
            /* [in] */ long lItemNum,
            /* [size_is][in] */ WorkListStruct __RPC_FAR *pWorkList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportSetMPPSStatusFinished )( 
            IPAWLMPPSEvent __RPC_FAR * This,
            /* [in] */ MppsSetResult __RPC_FAR *pResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReportMPPSStatusChanged )( 
            IPAWLMPPSEvent __RPC_FAR * This,
            /* [in] */ BSTR bsStudyUID,
            /* [in] */ WorkListStatus enumStatus);
        
        END_INTERFACE
    } IPAWLMPPSEventVtbl;

    interface IPAWLMPPSEvent
    {
        CONST_VTBL struct IPAWLMPPSEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPAWLMPPSEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPAWLMPPSEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPAWLMPPSEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPAWLMPPSEvent_ReportWlMppsWorkStatus(This,enumSubModule,enumSubModuleStatus)	\
    (This)->lpVtbl -> ReportWlMppsWorkStatus(This,enumSubModule,enumSubModuleStatus)

#define IPAWLMPPSEvent_ReportWorkList(This,lItemNum,pWorkList)	\
    (This)->lpVtbl -> ReportWorkList(This,lItemNum,pWorkList)

#define IPAWLMPPSEvent_ReportSetMPPSStatusFinished(This,pResult)	\
    (This)->lpVtbl -> ReportSetMPPSStatusFinished(This,pResult)

#define IPAWLMPPSEvent_ReportMPPSStatusChanged(This,bsStudyUID,enumStatus)	\
    (This)->lpVtbl -> ReportMPPSStatusChanged(This,bsStudyUID,enumStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPSEvent_ReportWlMppsWorkStatus_Proxy( 
    IPAWLMPPSEvent __RPC_FAR * This,
    /* [in] */ SubModule enumSubModule,
    /* [in] */ SubModuleState enumSubModuleStatus);


void __RPC_STUB IPAWLMPPSEvent_ReportWlMppsWorkStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPSEvent_ReportWorkList_Proxy( 
    IPAWLMPPSEvent __RPC_FAR * This,
    /* [in] */ long lItemNum,
    /* [size_is][in] */ WorkListStruct __RPC_FAR *pWorkList);


void __RPC_STUB IPAWLMPPSEvent_ReportWorkList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPSEvent_ReportSetMPPSStatusFinished_Proxy( 
    IPAWLMPPSEvent __RPC_FAR * This,
    /* [in] */ MppsSetResult __RPC_FAR *pResult);


void __RPC_STUB IPAWLMPPSEvent_ReportSetMPPSStatusFinished_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPAWLMPPSEvent_ReportMPPSStatusChanged_Proxy( 
    IPAWLMPPSEvent __RPC_FAR * This,
    /* [in] */ BSTR bsStudyUID,
    /* [in] */ WorkListStatus enumStatus);


void __RPC_STUB IPAWLMPPSEvent_ReportMPPSStatusChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPAWLMPPSEvent_INTERFACE_DEFINED__ */



#ifndef __PALib_LIBRARY_DEFINED__
#define __PALib_LIBRARY_DEFINED__

/* library PALib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PALib;

EXTERN_C const CLSID CLSID_PA;

#ifdef __cplusplus

class DECLSPEC_UUID("0A91E11A-C2AA-432B-A4E2-3ADF62B2F2B6")
PA;
#endif
#endif /* __PALib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
