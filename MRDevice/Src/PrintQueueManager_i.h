/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 06 14:58:56 2018
 */
/* Compiler settings for PrintQueueManager.idl:
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

#ifndef __PrintQueueManager_i_h__
#define __PrintQueueManager_i_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPrintQueue_FWD_DEFINED__
#define __IPrintQueue_FWD_DEFINED__
typedef interface IPrintQueue IPrintQueue;
#endif 	/* __IPrintQueue_FWD_DEFINED__ */


#ifndef __IPrintJob_FWD_DEFINED__
#define __IPrintJob_FWD_DEFINED__
typedef interface IPrintJob IPrintJob;
#endif 	/* __IPrintJob_FWD_DEFINED__ */


#ifndef ___IPrintQueueChangeEvents_FWD_DEFINED__
#define ___IPrintQueueChangeEvents_FWD_DEFINED__
typedef interface _IPrintQueueChangeEvents _IPrintQueueChangeEvents;
#endif 	/* ___IPrintQueueChangeEvents_FWD_DEFINED__ */


#ifndef __PrintQueue_FWD_DEFINED__
#define __PrintQueue_FWD_DEFINED__

#ifdef __cplusplus
typedef class PrintQueue PrintQueue;
#else
typedef struct PrintQueue PrintQueue;
#endif /* __cplusplus */

#endif 	/* __PrintQueue_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_PrintQueueManager_0000 */
/* [local] */ 

typedef /* [public][public][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_PrintQueueManager_0000_0001
    {	PRINT_JOB_READY	= 0,
	PRINT_JOB_PRINTING	= PRINT_JOB_READY + 1,
	PRINT_JOB_COMPLETE	= PRINT_JOB_PRINTING + 1,
	PRINT_JOB_FAILURE	= PRINT_JOB_COMPLETE + 1,
	PRINT_JOB_SUSPEND	= PRINT_JOB_FAILURE + 1
    }	PQ_EPrintJobStatus;

typedef /* [public][public][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_PrintQueueManager_0000_0002
    {	STATUS_CHANGE_NEW_JOB	= 0,
	STATUS_CHANGE_SUSPEND_2_READY	= STATUS_CHANGE_NEW_JOB + 1,
	STATUS_CHANGE_READY_2_PRINTING	= STATUS_CHANGE_SUSPEND_2_READY + 1,
	STATUS_CHANGE_PRINTING_2_COMPLETE	= STATUS_CHANGE_READY_2_PRINTING + 1,
	STATUS_CHANGE_PRINTING_2_FAILURE	= STATUS_CHANGE_PRINTING_2_COMPLETE + 1,
	STATUS_CHANGE_PRINTING_2_SUSPEND	= STATUS_CHANGE_PRINTING_2_FAILURE + 1,
	STATUS_CHANGE_FAILURE_2_READY	= STATUS_CHANGE_PRINTING_2_SUSPEND + 1,
	STATUS_CHANGE_ONEFILM_COMPLETE	= STATUS_CHANGE_FAILURE_2_READY + 1,
	STATUS_CHANGE_JOB_REMOVE	= STATUS_CHANGE_ONEFILM_COMPLETE + 1,
	STATUS_CHANGE_JOB_REMOVEALL	= STATUS_CHANGE_JOB_REMOVE + 1,
	STATUS_CHANGE_JOB_MOVEDOWN	= STATUS_CHANGE_JOB_REMOVEALL + 1,
	STATUS_CHANGE_JOB_MOVEUP	= STATUS_CHANGE_JOB_MOVEDOWN + 1,
	STATUS_CHANGE_JOB_MOVE2TOP	= STATUS_CHANGE_JOB_MOVEUP + 1,
	STATUS_CHANGE_JOB_STOP_PRINTING	= STATUS_CHANGE_JOB_MOVE2TOP + 1,
	STATUS_CHANGE_JOB_STOP_NOT_PRINTING	= STATUS_CHANGE_JOB_STOP_PRINTING + 1
    }	PQ_EPrintJobStatusChange;



extern RPC_IF_HANDLE __MIDL_itf_PrintQueueManager_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PrintQueueManager_0000_v0_0_s_ifspec;

#ifndef __IPrintQueue_INTERFACE_DEFINED__
#define __IPrintQueue_INTERFACE_DEFINED__

/* interface IPrintQueue */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPrintQueue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF599785-6256-41B4-B0FF-78FE7BD53C80")
    IPrintQueue : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetJobUIDList( 
            /* [retval][out] */ VARIANT __RPC_FAR *pUIDList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPrintJob( 
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pPrintJob) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetReprintParameter( 
            /* [in] */ long reprintTimes,
            /* [in] */ long timeInterval,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Suspend( 
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Resume( 
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Move2Top( 
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveUp( 
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveDown( 
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( 
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Submit( 
            /* [in] */ VARIANT vp,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Relive( 
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect2Printer( 
            /* [in] */ BSTR HostAE,
            /* [in] */ BSTR ServerAE,
            /* [in] */ long ServerPort,
            /* [in] */ BSTR ServerIP,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect2GrayPrinter( 
            /* [in] */ BSTR HostAE,
            /* [in] */ BSTR ServerAE,
            /* [in] */ long ServerPort,
            /* [in] */ BSTR ServerIP,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect2ColorPrinter( 
            /* [in] */ BSTR HostAE,
            /* [in] */ BSTR ServerAE,
            /* [in] */ long ServerPort,
            /* [in] */ BSTR ServerIP,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RunPQ( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPrintQueueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPrintQueue __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPrintQueue __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPrintQueue __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetJobUIDList )( 
            IPrintQueue __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pUIDList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrintJob )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ LPDISPATCH __RPC_FAR *pPrintJob);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetReprintParameter )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ long reprintTimes,
            /* [in] */ long timeInterval,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Suspend )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resume )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move2Top )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveUp )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveDown )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )( 
            IPrintQueue __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Submit )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ VARIANT vp,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Relive )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR jobUID,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect2Printer )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR HostAE,
            /* [in] */ BSTR ServerAE,
            /* [in] */ long ServerPort,
            /* [in] */ BSTR ServerIP,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect2GrayPrinter )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR HostAE,
            /* [in] */ BSTR ServerAE,
            /* [in] */ long ServerPort,
            /* [in] */ BSTR ServerIP,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect2ColorPrinter )( 
            IPrintQueue __RPC_FAR * This,
            /* [in] */ BSTR HostAE,
            /* [in] */ BSTR ServerAE,
            /* [in] */ long ServerPort,
            /* [in] */ BSTR ServerIP,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RunPQ )( 
            IPrintQueue __RPC_FAR * This);
        
        END_INTERFACE
    } IPrintQueueVtbl;

    interface IPrintQueue
    {
        CONST_VTBL struct IPrintQueueVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrintQueue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPrintQueue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPrintQueue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPrintQueue_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPrintQueue_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPrintQueue_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPrintQueue_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPrintQueue_GetJobUIDList(This,pUIDList)	\
    (This)->lpVtbl -> GetJobUIDList(This,pUIDList)

#define IPrintQueue_GetPrintJob(This,jobUID,pPrintJob)	\
    (This)->lpVtbl -> GetPrintJob(This,jobUID,pPrintJob)

#define IPrintQueue_SetReprintParameter(This,reprintTimes,timeInterval,pResult)	\
    (This)->lpVtbl -> SetReprintParameter(This,reprintTimes,timeInterval,pResult)

#define IPrintQueue_Suspend(This,jobUID,pResult)	\
    (This)->lpVtbl -> Suspend(This,jobUID,pResult)

#define IPrintQueue_Resume(This,jobUID,pResult)	\
    (This)->lpVtbl -> Resume(This,jobUID,pResult)

#define IPrintQueue_Move2Top(This,jobUID,pResult)	\
    (This)->lpVtbl -> Move2Top(This,jobUID,pResult)

#define IPrintQueue_MoveUp(This,jobUID,pResult)	\
    (This)->lpVtbl -> MoveUp(This,jobUID,pResult)

#define IPrintQueue_MoveDown(This,jobUID,pResult)	\
    (This)->lpVtbl -> MoveDown(This,jobUID,pResult)

#define IPrintQueue_Remove(This,jobUID,pResult)	\
    (This)->lpVtbl -> Remove(This,jobUID,pResult)

#define IPrintQueue_RemoveAll(This,pResult)	\
    (This)->lpVtbl -> RemoveAll(This,pResult)

#define IPrintQueue_Submit(This,vp,pResult)	\
    (This)->lpVtbl -> Submit(This,vp,pResult)

#define IPrintQueue_Relive(This,jobUID,pResult)	\
    (This)->lpVtbl -> Relive(This,jobUID,pResult)

#define IPrintQueue_Connect2Printer(This,HostAE,ServerAE,ServerPort,ServerIP,pResult)	\
    (This)->lpVtbl -> Connect2Printer(This,HostAE,ServerAE,ServerPort,ServerIP,pResult)

#define IPrintQueue_Connect2GrayPrinter(This,HostAE,ServerAE,ServerPort,ServerIP,pResult)	\
    (This)->lpVtbl -> Connect2GrayPrinter(This,HostAE,ServerAE,ServerPort,ServerIP,pResult)

#define IPrintQueue_Connect2ColorPrinter(This,HostAE,ServerAE,ServerPort,ServerIP,pResult)	\
    (This)->lpVtbl -> Connect2ColorPrinter(This,HostAE,ServerAE,ServerPort,ServerIP,pResult)

#define IPrintQueue_RunPQ(This)	\
    (This)->lpVtbl -> RunPQ(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_GetJobUIDList_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pUIDList);


void __RPC_STUB IPrintQueue_GetJobUIDList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_GetPrintJob_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR jobUID,
    /* [retval][out] */ LPDISPATCH __RPC_FAR *pPrintJob);


void __RPC_STUB IPrintQueue_GetPrintJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_SetReprintParameter_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ long reprintTimes,
    /* [in] */ long timeInterval,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_SetReprintParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_Suspend_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR jobUID,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_Suspend_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_Resume_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR jobUID,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_Move2Top_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR jobUID,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_Move2Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_MoveUp_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR jobUID,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_MoveUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_MoveDown_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR jobUID,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_MoveDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_Remove_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR jobUID,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_RemoveAll_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_Submit_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ VARIANT vp,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_Submit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_Relive_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR jobUID,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_Relive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_Connect2Printer_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR HostAE,
    /* [in] */ BSTR ServerAE,
    /* [in] */ long ServerPort,
    /* [in] */ BSTR ServerIP,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_Connect2Printer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_Connect2GrayPrinter_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR HostAE,
    /* [in] */ BSTR ServerAE,
    /* [in] */ long ServerPort,
    /* [in] */ BSTR ServerIP,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_Connect2GrayPrinter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_Connect2ColorPrinter_Proxy( 
    IPrintQueue __RPC_FAR * This,
    /* [in] */ BSTR HostAE,
    /* [in] */ BSTR ServerAE,
    /* [in] */ long ServerPort,
    /* [in] */ BSTR ServerIP,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IPrintQueue_Connect2ColorPrinter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPrintQueue_RunPQ_Proxy( 
    IPrintQueue __RPC_FAR * This);


void __RPC_STUB IPrintQueue_RunPQ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPrintQueue_INTERFACE_DEFINED__ */


#ifndef __IPrintJob_INTERFACE_DEFINED__
#define __IPrintJob_INTERFACE_DEFINED__

/* interface IPrintJob */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPrintJob;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E7C906C2-210C-4b21-B5C5-ABC2D519DB0E")
    IPrintJob : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_JobUID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PatientName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PatientID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StudyID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeStamp( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ PQ_EPrintJobStatus __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CopyNum( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FilmCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentFilm( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReprintComplete( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPrintJobVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPrintJob __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPrintJob __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPrintJob __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPrintJob __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPrintJob __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPrintJob __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPrintJob __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_JobUID )( 
            IPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PatientName )( 
            IPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PatientID )( 
            IPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StudyID )( 
            IPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeStamp )( 
            IPrintJob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IPrintJob __RPC_FAR * This,
            /* [retval][out] */ PQ_EPrintJobStatus __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CopyNum )( 
            IPrintJob __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FilmCount )( 
            IPrintJob __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentFilm )( 
            IPrintJob __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReprintComplete )( 
            IPrintJob __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } IPrintJobVtbl;

    interface IPrintJob
    {
        CONST_VTBL struct IPrintJobVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrintJob_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPrintJob_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPrintJob_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPrintJob_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPrintJob_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPrintJob_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPrintJob_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPrintJob_get_JobUID(This,pVal)	\
    (This)->lpVtbl -> get_JobUID(This,pVal)

#define IPrintJob_get_PatientName(This,pVal)	\
    (This)->lpVtbl -> get_PatientName(This,pVal)

#define IPrintJob_get_PatientID(This,pVal)	\
    (This)->lpVtbl -> get_PatientID(This,pVal)

#define IPrintJob_get_StudyID(This,pVal)	\
    (This)->lpVtbl -> get_StudyID(This,pVal)

#define IPrintJob_get_TimeStamp(This,pVal)	\
    (This)->lpVtbl -> get_TimeStamp(This,pVal)

#define IPrintJob_get_Status(This,pVal)	\
    (This)->lpVtbl -> get_Status(This,pVal)

#define IPrintJob_get_CopyNum(This,pVal)	\
    (This)->lpVtbl -> get_CopyNum(This,pVal)

#define IPrintJob_get_FilmCount(This,pVal)	\
    (This)->lpVtbl -> get_FilmCount(This,pVal)

#define IPrintJob_get_CurrentFilm(This,pVal)	\
    (This)->lpVtbl -> get_CurrentFilm(This,pVal)

#define IPrintJob_get_ReprintComplete(This,pVal)	\
    (This)->lpVtbl -> get_ReprintComplete(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPrintJob_get_JobUID_Proxy( 
    IPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPrintJob_get_JobUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPrintJob_get_PatientName_Proxy( 
    IPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPrintJob_get_PatientName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPrintJob_get_PatientID_Proxy( 
    IPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPrintJob_get_PatientID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPrintJob_get_StudyID_Proxy( 
    IPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPrintJob_get_StudyID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPrintJob_get_TimeStamp_Proxy( 
    IPrintJob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IPrintJob_get_TimeStamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPrintJob_get_Status_Proxy( 
    IPrintJob __RPC_FAR * This,
    /* [retval][out] */ PQ_EPrintJobStatus __RPC_FAR *pVal);


void __RPC_STUB IPrintJob_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPrintJob_get_CopyNum_Proxy( 
    IPrintJob __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPrintJob_get_CopyNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPrintJob_get_FilmCount_Proxy( 
    IPrintJob __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPrintJob_get_FilmCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPrintJob_get_CurrentFilm_Proxy( 
    IPrintJob __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IPrintJob_get_CurrentFilm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IPrintJob_get_ReprintComplete_Proxy( 
    IPrintJob __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IPrintJob_get_ReprintComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPrintJob_INTERFACE_DEFINED__ */



#ifndef __PRINTQUEUEMANAGERLib_LIBRARY_DEFINED__
#define __PRINTQUEUEMANAGERLib_LIBRARY_DEFINED__

/* library PRINTQUEUEMANAGERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PRINTQUEUEMANAGERLib;

#ifndef ___IPrintQueueChangeEvents_DISPINTERFACE_DEFINED__
#define ___IPrintQueueChangeEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IPrintQueueChangeEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IPrintQueueChangeEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("718D4637-708B-4FEA-88B7-BB51332525AF")
    _IPrintQueueChangeEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPrintQueueChangeEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IPrintQueueChangeEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IPrintQueueChangeEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IPrintQueueChangeEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IPrintQueueChangeEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IPrintQueueChangeEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IPrintQueueChangeEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IPrintQueueChangeEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IPrintQueueChangeEventsVtbl;

    interface _IPrintQueueChangeEvents
    {
        CONST_VTBL struct _IPrintQueueChangeEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPrintQueueChangeEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IPrintQueueChangeEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IPrintQueueChangeEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IPrintQueueChangeEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IPrintQueueChangeEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IPrintQueueChangeEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IPrintQueueChangeEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPrintQueueChangeEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PrintQueue;

#ifdef __cplusplus

class DECLSPEC_UUID("65DA6714-B467-4195-B211-231022BB00C2")
PrintQueue;
#endif
#endif /* __PRINTQUEUEMANAGERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
