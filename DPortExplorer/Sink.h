// Sink.h: Schnittstelle für die Klasse ISerialPortEvents.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if !defined(AFX_ISERIALPORTEVENTS_H__EE0A4FEB_D35B_42CF_8614_DD14D0266CE9__INCLUDED_)
#define AFX_ISERIALPORTEVENTS_H__EE0A4FEB_D35B_42CF_8614_DD14D0266CE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSink  : public _ISerialPortEvents 
{
public :
	CSink();
	~CSink();
	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		if (riid==__uuidof(_ISerialPortEvents))  
		{
			*ppvObject = this;
			return S_OK ;
		}
		
		return S_FALSE ;
	}
    
	virtual ULONG STDMETHODCALLTYPE AddRef(void)
	{
		m_nCount++ ;
		return m_nCount;
	};
    
    virtual ULONG STDMETHODCALLTYPE Release(void) 
	{
		m_nCount-- ;
		if (m_nCount==0)
			delete this;
		return m_nCount;	
	};
	
	////////////////////////////////////////////////
	virtual HRESULT __stdcall OnReceiveChar (
        unsigned char chrter,
        unsigned char port );
    virtual HRESULT __stdcall OnBreakDetected (
        unsigned char port ) ;
    virtual HRESULT __stdcall OnCTSDetected (
        unsigned char port ) ;
    virtual HRESULT __stdcall OnERRDetected (
        BSTR wparam,
        unsigned char port ) ;
    virtual HRESULT __stdcall OnRINGDetected (
        unsigned char port ) ;
    virtual HRESULT __stdcall OnRXFLAGDetected (
        unsigned char port ) ;
    virtual HRESULT __stdcall NotifyTelegramSend (
        unsigned char port ) ;
    virtual HRESULT __stdcall OnReceiveDeTel (
        unsigned char * dataBuffer,
        long dataLengt,
        unsigned char port );

protected:
	static long m_nCount;
};

#endif // !defined(AFX_ISERIALPORTEVENTS_H__EE0A4FEB_D35B_42CF_8614_DD14D0266CE9__INCLUDED_)
