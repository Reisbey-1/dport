

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for DPort.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DPort_i_h__
#define __DPort_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISerialSink_FWD_DEFINED__
#define __ISerialSink_FWD_DEFINED__
typedef interface ISerialSink ISerialSink;

#endif 	/* __ISerialSink_FWD_DEFINED__ */


#ifndef __ISerialPort_FWD_DEFINED__
#define __ISerialPort_FWD_DEFINED__
typedef interface ISerialPort ISerialPort;

#endif 	/* __ISerialPort_FWD_DEFINED__ */


#ifndef ___ISerialPortEvents_FWD_DEFINED__
#define ___ISerialPortEvents_FWD_DEFINED__
typedef interface _ISerialPortEvents _ISerialPortEvents;

#endif 	/* ___ISerialPortEvents_FWD_DEFINED__ */


#ifndef __SerialSink_FWD_DEFINED__
#define __SerialSink_FWD_DEFINED__

#ifdef __cplusplus
typedef class SerialSink SerialSink;
#else
typedef struct SerialSink SerialSink;
#endif /* __cplusplus */

#endif 	/* __SerialSink_FWD_DEFINED__ */


#ifndef __SerialPort_FWD_DEFINED__
#define __SerialPort_FWD_DEFINED__

#ifdef __cplusplus
typedef class SerialPort SerialPort;
#else
typedef struct SerialPort SerialPort;
#endif /* __cplusplus */

#endif 	/* __SerialPort_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISerialSink_INTERFACE_DEFINED__
#define __ISerialSink_INTERFACE_DEFINED__

/* interface ISerialSink */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISerialSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BC614BD5-D5DD-4C23-838F-14D6203A8D25")
    ISerialSink : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_error( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Message( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReceiveBuffer( 
            /* [retval][out] */ unsigned char **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearError( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolSwitch( 
            /* [retval][out] */ USHORT *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ProtocolSwitch( 
            /* [in] */ USHORT newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_lengthReceivedChars( 
            /* [retval][out] */ SHORT *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddCallBackFunction( 
            /* [in] */ LONG *f) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_LastReceived( 
            /* [retval][out] */ CHAR *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISerialSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISerialSink * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISerialSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISerialSink * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISerialSink * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISerialSink * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISerialSink * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISerialSink * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_error )( 
            ISerialSink * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Message )( 
            ISerialSink * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ReceiveBuffer )( 
            ISerialSink * This,
            /* [retval][out] */ unsigned char **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearError )( 
            ISerialSink * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProtocolSwitch )( 
            ISerialSink * This,
            /* [retval][out] */ USHORT *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProtocolSwitch )( 
            ISerialSink * This,
            /* [in] */ USHORT newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_lengthReceivedChars )( 
            ISerialSink * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AddCallBackFunction )( 
            ISerialSink * This,
            /* [in] */ LONG *f);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastReceived )( 
            ISerialSink * This,
            /* [retval][out] */ CHAR *pVal);
        
        END_INTERFACE
    } ISerialSinkVtbl;

    interface ISerialSink
    {
        CONST_VTBL struct ISerialSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISerialSink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISerialSink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISerialSink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISerialSink_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISerialSink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISerialSink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISerialSink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISerialSink_get_error(This,pVal)	\
    ( (This)->lpVtbl -> get_error(This,pVal) ) 

#define ISerialSink_get_Message(This,pVal)	\
    ( (This)->lpVtbl -> get_Message(This,pVal) ) 

#define ISerialSink_get_ReceiveBuffer(This,pVal)	\
    ( (This)->lpVtbl -> get_ReceiveBuffer(This,pVal) ) 

#define ISerialSink_ClearError(This)	\
    ( (This)->lpVtbl -> ClearError(This) ) 

#define ISerialSink_get_ProtocolSwitch(This,pVal)	\
    ( (This)->lpVtbl -> get_ProtocolSwitch(This,pVal) ) 

#define ISerialSink_put_ProtocolSwitch(This,newVal)	\
    ( (This)->lpVtbl -> put_ProtocolSwitch(This,newVal) ) 

#define ISerialSink_get_lengthReceivedChars(This,pVal)	\
    ( (This)->lpVtbl -> get_lengthReceivedChars(This,pVal) ) 

#define ISerialSink_AddCallBackFunction(This,f)	\
    ( (This)->lpVtbl -> AddCallBackFunction(This,f) ) 

#define ISerialSink_get_LastReceived(This,pVal)	\
    ( (This)->lpVtbl -> get_LastReceived(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISerialSink_INTERFACE_DEFINED__ */


#ifndef __ISerialPort_INTERFACE_DEFINED__
#define __ISerialPort_INTERFACE_DEFINED__

/* interface ISerialPort */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISerialPort;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4BB8490C-5955-41CF-B5C3-AA41DCC2FF96")
    ISerialPort : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendDeTelTelegram( 
            /* [in] */ IUnknown *pTelegram) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenPort( 
            /* [in] */ BSTR *initStr,
            /* [in] */ BYTE portnr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Kill( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartMonitoring( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CanDo( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClosePort( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ComEvents( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ComEvents( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WriteBufferSize( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WriteBufferSize( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RestartMonitoring( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopMonitoring( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Purge( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteBuffer( 
            /* [in] */ BYTE *buffer,
            int nsize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WaitForSingleObjectConstant( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WaitForSingleObjectConstant( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolSwitch( 
            /* [retval][out] */ SHORT *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_ProtocolSwitch( 
            /* [in] */ SHORT newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISerialPortVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISerialPort * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISerialPort * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISerialPort * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISerialPort * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISerialPort * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISerialPort * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISerialPort * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendDeTelTelegram )( 
            ISerialPort * This,
            /* [in] */ IUnknown *pTelegram);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OpenPort )( 
            ISerialPort * This,
            /* [in] */ BSTR *initStr,
            /* [in] */ BYTE portnr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Kill )( 
            ISerialPort * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartMonitoring )( 
            ISerialPort * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CanDo )( 
            ISerialPort * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClosePort )( 
            ISerialPort * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ComEvents )( 
            ISerialPort * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ComEvents )( 
            ISerialPort * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WriteBufferSize )( 
            ISerialPort * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WriteBufferSize )( 
            ISerialPort * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RestartMonitoring )( 
            ISerialPort * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopMonitoring )( 
            ISerialPort * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Purge )( 
            ISerialPort * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WriteBuffer )( 
            ISerialPort * This,
            /* [in] */ BYTE *buffer,
            int nsize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WaitForSingleObjectConstant )( 
            ISerialPort * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WaitForSingleObjectConstant )( 
            ISerialPort * This,
            /* [in] */ long newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProtocolSwitch )( 
            ISerialPort * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProtocolSwitch )( 
            ISerialPort * This,
            /* [in] */ SHORT newVal);
        
        END_INTERFACE
    } ISerialPortVtbl;

    interface ISerialPort
    {
        CONST_VTBL struct ISerialPortVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISerialPort_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISerialPort_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISerialPort_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISerialPort_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISerialPort_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISerialPort_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISerialPort_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISerialPort_SendDeTelTelegram(This,pTelegram)	\
    ( (This)->lpVtbl -> SendDeTelTelegram(This,pTelegram) ) 

#define ISerialPort_OpenPort(This,initStr,portnr)	\
    ( (This)->lpVtbl -> OpenPort(This,initStr,portnr) ) 

#define ISerialPort_Kill(This)	\
    ( (This)->lpVtbl -> Kill(This) ) 

#define ISerialPort_StartMonitoring(This)	\
    ( (This)->lpVtbl -> StartMonitoring(This) ) 

#define ISerialPort_CanDo(This)	\
    ( (This)->lpVtbl -> CanDo(This) ) 

#define ISerialPort_ClosePort(This)	\
    ( (This)->lpVtbl -> ClosePort(This) ) 

#define ISerialPort_get_ComEvents(This,pVal)	\
    ( (This)->lpVtbl -> get_ComEvents(This,pVal) ) 

#define ISerialPort_put_ComEvents(This,newVal)	\
    ( (This)->lpVtbl -> put_ComEvents(This,newVal) ) 

#define ISerialPort_get_WriteBufferSize(This,pVal)	\
    ( (This)->lpVtbl -> get_WriteBufferSize(This,pVal) ) 

#define ISerialPort_put_WriteBufferSize(This,newVal)	\
    ( (This)->lpVtbl -> put_WriteBufferSize(This,newVal) ) 

#define ISerialPort_RestartMonitoring(This)	\
    ( (This)->lpVtbl -> RestartMonitoring(This) ) 

#define ISerialPort_StopMonitoring(This)	\
    ( (This)->lpVtbl -> StopMonitoring(This) ) 

#define ISerialPort_Purge(This)	\
    ( (This)->lpVtbl -> Purge(This) ) 

#define ISerialPort_WriteBuffer(This,buffer,nsize)	\
    ( (This)->lpVtbl -> WriteBuffer(This,buffer,nsize) ) 

#define ISerialPort_get_WaitForSingleObjectConstant(This,pVal)	\
    ( (This)->lpVtbl -> get_WaitForSingleObjectConstant(This,pVal) ) 

#define ISerialPort_put_WaitForSingleObjectConstant(This,newVal)	\
    ( (This)->lpVtbl -> put_WaitForSingleObjectConstant(This,newVal) ) 

#define ISerialPort_get_ProtocolSwitch(This,pVal)	\
    ( (This)->lpVtbl -> get_ProtocolSwitch(This,pVal) ) 

#define ISerialPort_put_ProtocolSwitch(This,newVal)	\
    ( (This)->lpVtbl -> put_ProtocolSwitch(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISerialPort_INTERFACE_DEFINED__ */


#ifndef ___ISerialPortEvents_INTERFACE_DEFINED__
#define ___ISerialPortEvents_INTERFACE_DEFINED__

/* interface _ISerialPortEvents */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__ISerialPortEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12A8852F-CE62-4FDF-A7A8-E3FAFBCE7DE8")
    _ISerialPortEvents : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnReceiveChar( 
            /* [in] */ BYTE chrter,
            /* [in] */ BYTE port) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnBreakDetected( 
            /* [in] */ BYTE port) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnCTSDetected( 
            /* [in] */ BYTE port) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnERRDetected( 
            /* [in] */ BSTR wparam,
            /* [in] */ BYTE port) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnRINGDetected( 
            /* [in] */ BYTE port) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnRXFLAGDetected( 
            /* [in] */ BYTE port) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE NotifyTelegramSend( 
            /* [in] */ BYTE port) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnReceiveDeTel( 
            /* [in] */ BYTE *dataBuffer,
            /* [in] */ LONG dataLengt,
            /* [in] */ BYTE port) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnReceiveModBus( 
            /* [in] */ BYTE *dataBuffer,
            /* [in] */ LONG dataLengt,
            /* [in] */ BYTE port) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct _ISerialPortEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ISerialPortEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ISerialPortEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ISerialPortEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ISerialPortEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ISerialPortEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ISerialPortEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ISerialPortEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnReceiveChar )( 
            _ISerialPortEvents * This,
            /* [in] */ BYTE chrter,
            /* [in] */ BYTE port);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnBreakDetected )( 
            _ISerialPortEvents * This,
            /* [in] */ BYTE port);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnCTSDetected )( 
            _ISerialPortEvents * This,
            /* [in] */ BYTE port);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnERRDetected )( 
            _ISerialPortEvents * This,
            /* [in] */ BSTR wparam,
            /* [in] */ BYTE port);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnRINGDetected )( 
            _ISerialPortEvents * This,
            /* [in] */ BYTE port);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnRXFLAGDetected )( 
            _ISerialPortEvents * This,
            /* [in] */ BYTE port);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NotifyTelegramSend )( 
            _ISerialPortEvents * This,
            /* [in] */ BYTE port);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnReceiveDeTel )( 
            _ISerialPortEvents * This,
            /* [in] */ BYTE *dataBuffer,
            /* [in] */ LONG dataLengt,
            /* [in] */ BYTE port);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnReceiveModBus )( 
            _ISerialPortEvents * This,
            /* [in] */ BYTE *dataBuffer,
            /* [in] */ LONG dataLengt,
            /* [in] */ BYTE port);
        
        END_INTERFACE
    } _ISerialPortEventsVtbl;

    interface _ISerialPortEvents
    {
        CONST_VTBL struct _ISerialPortEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISerialPortEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ISerialPortEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ISerialPortEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ISerialPortEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ISerialPortEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ISerialPortEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ISerialPortEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define _ISerialPortEvents_OnReceiveChar(This,chrter,port)	\
    ( (This)->lpVtbl -> OnReceiveChar(This,chrter,port) ) 

#define _ISerialPortEvents_OnBreakDetected(This,port)	\
    ( (This)->lpVtbl -> OnBreakDetected(This,port) ) 

#define _ISerialPortEvents_OnCTSDetected(This,port)	\
    ( (This)->lpVtbl -> OnCTSDetected(This,port) ) 

#define _ISerialPortEvents_OnERRDetected(This,wparam,port)	\
    ( (This)->lpVtbl -> OnERRDetected(This,wparam,port) ) 

#define _ISerialPortEvents_OnRINGDetected(This,port)	\
    ( (This)->lpVtbl -> OnRINGDetected(This,port) ) 

#define _ISerialPortEvents_OnRXFLAGDetected(This,port)	\
    ( (This)->lpVtbl -> OnRXFLAGDetected(This,port) ) 

#define _ISerialPortEvents_NotifyTelegramSend(This,port)	\
    ( (This)->lpVtbl -> NotifyTelegramSend(This,port) ) 

#define _ISerialPortEvents_OnReceiveDeTel(This,dataBuffer,dataLengt,port)	\
    ( (This)->lpVtbl -> OnReceiveDeTel(This,dataBuffer,dataLengt,port) ) 

#define _ISerialPortEvents_OnReceiveModBus(This,dataBuffer,dataLengt,port)	\
    ( (This)->lpVtbl -> OnReceiveModBus(This,dataBuffer,dataLengt,port) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___ISerialPortEvents_INTERFACE_DEFINED__ */



#ifndef __DPortLib_LIBRARY_DEFINED__
#define __DPortLib_LIBRARY_DEFINED__

/* library DPortLib */
/* [helpstring][version][uuid] */ 

typedef /* [uuid] */  DECLSPEC_UUID("BD9678DB-B8F7-424F-9062-79D3CFFE9D5F") 
enum tagPortConstants
    {
        SIZE_RECEIVE_BUFFER	= ( 8 * 1500 ) 
    } 	PortConstants;


EXTERN_C const IID LIBID_DPortLib;

EXTERN_C const CLSID CLSID_SerialSink;

#ifdef __cplusplus

class DECLSPEC_UUID("A0C0A43D-C3F9-408B-8F99-9D33A07A4F66")
SerialSink;
#endif

EXTERN_C const CLSID CLSID_SerialPort;

#ifdef __cplusplus

class DECLSPEC_UUID("AF34303D-CB9F-4019-ADFF-915B0EC1C545")
SerialPort;
#endif
#endif /* __DPortLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


