// SerialSink.h : Declaration of the CSerialSink

#pragma once
#include "resource.h"       // main symbols
#include "DPort_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif
//class CSerialSink;
typedef  LONG (*fp) ();

// CSerialSink
class ATL_NO_VTABLE CSerialSink :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSerialSink, &CLSID_SerialSink>,
	public IDispatchImpl<ISerialSink, &IID_ISerialSink, &LIBID_DPortLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<_ISerialPortEvents, &__uuidof(_ISerialPortEvents), &LIBID_DPortLib, /* wMajor = */ 1, /* wMinor = */ 0>
{
public:
	enum protocolSwitch { PS_KEINE = 0, PS_DETEL, PS_MODBUS_ASCII, PS_MODBUS_RTU };

	CSerialSink();

	DECLARE_REGISTRY_RESOURCEID(IDR_SERIALSINK)

	BEGIN_COM_MAP(CSerialSink)
		COM_INTERFACE_ENTRY(ISerialSink)
		COM_INTERFACE_ENTRY2(IDispatch, _ISerialPortEvents)
		COM_INTERFACE_ENTRY(_ISerialPortEvents)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

protected:
	BOOL	m_bError;
	int		m_nLength;
	CString m_csMessage;
	//BYTE m_nReceiveds[LENGTH_DETEL_RECEIVE];
	BYTE m_nReceiveds[SIZE_RECEIVE_BUFFER];
	CHAR m_nLastReceived;

private:
	int m_nReceivedByteCounter;
	USHORT m_usProtocolSwitch;

public:
	// ISerialSink
	
	STDMETHOD(get_ReceiveBuffer)(/*[out, retval]*/ unsigned char **pVal);
	STDMETHOD(get_Message)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_error)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(ClearError)();
	
	STDMETHOD(get_LastReceived)(CHAR* pVal);

	STDMETHOD(get_ProtocolSwitch)(USHORT* pVal);
	STDMETHOD(put_ProtocolSwitch)(USHORT  newVal);
	STDMETHOD(get_lengthReceivedChars)(SHORT* pVal);
	STDMETHOD(AddCallBackFunction)(LONG (*f) );
	
public:
	// _ISerialPortEvents Methods
	STDMETHOD(OnReceiveChar)( BYTE chrter,  BYTE port);
	STDMETHOD(OnBreakDetected)( BYTE port);
	STDMETHOD(OnCTSDetected)( BYTE port);
	STDMETHOD(OnERRDetected)( BSTR wparam,  BYTE port);
	STDMETHOD(OnRINGDetected)( BYTE port);
	STDMETHOD(OnRXFLAGDetected)( BYTE port);
	STDMETHOD(NotifyTelegramSend)( BYTE port);
	STDMETHOD(OnReceiveDeTel)(BYTE * dataBuffer, LONG dataLengt, BYTE port); 
	STDMETHOD(OnReceiveModBus)(BYTE * dataBuffer, LONG dataLengt, BYTE port); 

	//typedef  LONG(*fp)();
	static fp  m_pf  ;

	static LONG  test();// { AfxMessageBox(L"hhh"); return 1; }
	//LONG test() { AfxMessageBox(L"hhh"); return 1; }
	
};

//OBJECT_ENTRY_AUTO(__uuidof(SerialSink), CSerialSink)
OBJECT_ENTRY_AUTO(CLSID_SerialSink, CSerialSink)
