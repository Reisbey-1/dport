// SerialPort.h : Declaration of the CSerialPort

#pragma once
#include "resource.h"       // main symbols

#include "DPort_i.h"
#include "_ISerialPortEvents_CP.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CSerialPort

class ATL_NO_VTABLE CSerialPort :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSerialPort, &CLSID_SerialPort>,
	public IConnectionPointContainerImpl<CSerialPort>,
	public CProxy_ISerialPortEvents<CSerialPort>,
	public IDispatchImpl<ISerialPort, &IID_ISerialPort, &LIBID_DPortLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	enum protocolSwitch { PS_KEINE = 0, PS_DETEL, PS_MODBUS_ASCII, PS_MODBUS_RTU};

	CSerialPort();
	~CSerialPort();

	DECLARE_REGISTRY_RESOURCEID(IDR_SERIALPORT)

	BEGIN_COM_MAP(CSerialPort)
		COM_INTERFACE_ENTRY(ISerialPort)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CSerialPort)
		CONNECTION_POINT_ENTRY(__uuidof(_ISerialPortEvents))
	END_CONNECTION_POINT_MAP()
		DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
	}

public:

	STDMETHOD(get_WaitForSingleObjectConstant)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_WaitForSingleObjectConstant)(/*[in]*/ long newVal);
	
	STDMETHOD(WriteBuffer)(/*[in]*/ BYTE* buffer, int nsize);
	STDMETHOD(Purge)();
	STDMETHOD(StopMonitoring)();
	STDMETHOD(RestartMonitoring)();
	STDMETHOD(get_WriteBufferSize)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_WriteBufferSize)(/*[in]*/ DWORD newVal);
	STDMETHOD(get_ComEvents)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_ComEvents)(/*[in]*/ DWORD newVal);
	STDMETHOD(ClosePort)();
	STDMETHOD(CanDo)();
	STDMETHOD(StartMonitoring)();
	STDMETHOD(Kill)();
	STDMETHOD(OpenPort)(/*[in]*/BSTR* initStr , /*[in]*/ BYTE portnr);
	STDMETHOD(SendDeTelTelegram)(/*[in]*/IUnknown* pTelegram);
	STDMETHOD(get_ProtocolSwitch)(SHORT* pVal);
	STDMETHOD(put_ProtocolSwitch)(SHORT newVal);

private:
	// tokonizer
	CLexicalAnalyser	m_LexSer;
	void ParseInitString(CString csInitString);

	BYTE  m_XON;				// thise characters are made member to give user the  
	BYTE  m_XOF;				// chanche to alter control characters
	BOOL  m_bFirstDebugRun;		// internal debug utility
	SHORT m_nProtocolSwitch; 	// internal switch signaling simple write action without protocol

	int	 m_nDeTelCounter;		// incremented by one at construction of telegram in
								// receiving character	
	BOOL	m_bStrobe;
	BOOL	m_bLowNible ;
	BYTE    m_dataHighNible;

	BOOL m_bNewTelegramReceived;	// bDetelTelegram

protected:
	void ProceedMsg()  ;
	void ProcessErrorMessage(char* ErrorText);
	BOOL SendDeTelDublex(DeTel& telegram, BYTE* pBuffer);
	BOOL SendDeTelSingle(DeTel& telegram, BYTE* pBuffer);

	//BOOL SendDeTelAscii(DeTel& telegram, BYTE* pBuffer);
	BOOL SendDeTelAscii(DeTel& telegram);
	// thread
	virtual void    NotifyCharSend(DWORD BytesSent) {return ;}	
	int				BuildTelegram(unsigned char ch, BYTE PortNr); 
	static  UINT CommThread(LPVOID pParam);
	void   RunMe();
	void   ReceiveChar(COMSTAT comstat);
	void   WriteBuffer();
	CWinThread*		m_pThread;
	
	CPerformanceCounter * m_pPerformaceCounter;
	static LONG CallBackFunction();					// Callback function to pass Performance counter
	static CSerialPort * theSeialPortObjectPtr;		// objet pointer to itself
	void   update();								// called by CallBackFunction over theObjectPtr
	
	// synchronisation objects
	CRITICAL_SECTION	m_csCommunicationSync;
	BOOL				m_bThreadAlive;
	// handles
	HANDLE	m_hCharReceived;
	HANDLE	m_hWriteIsCompleted;
	HANDLE	m_hShutdownEvent;
	HANDLE	m_hComm;
	HANDLE	m_hWriteEvent;
	HANDLE	m_IshShutdown;
	HANDLE	m_hThreadStartet;
	HANDLE  m_hTelegramReceived; 

	// Event array. 
	// One element is used for each event. There are two event handles for each port.
	// A Write event and a receive character event which is located in the overlapped structure (m_ov.hEvent).
	// There is a general shutdown when the port is closed. 
	HANDLE				m_hEventArray[3];
	// structures
	OVERLAPPED			m_ov;
	COMMTIMEOUTS		m_CommTimeouts;
	DCB					m_dcb;
	CWnd*				m_pOwner;							// owner window
	BYTE				m_nPortNr;
	DWORD				m_dwWriteBufferSize;				// write buffer dynamic variable length
	//BYTE 				m_szWriteBuffer [MAXIMUM_DATA_BYTE * 2 + LENGTH_CONROLBITS];
	BYTE 				m_szWriteBuffer [SIZE_RECEIVE_BUFFER];

	//BYTE 				m_szReceiveBuffer[LENGTH_DETEL_RECEIVE];	// receive buffer fixed length
	BYTE 				m_szReceiveBuffer[SIZE_RECEIVE_BUFFER];	// receive buffer fixed length

	DWORD				m_dwCommEvents;
	UINT				m_nBaud ;
	CString				m_cParity;							//wchar_t m_cParity;
	UINT				m_nDatabits;
	CString				m_csstopbits;						//UINT m_nstopbits;
	long				m_nWaitForSingleObjectConstant;

public:
	
	
};

OBJECT_ENTRY_AUTO(CLSID_SerialPort, CSerialPort) 
