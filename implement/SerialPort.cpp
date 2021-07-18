// SerialPort.cpp : Implementation of CSerialPort
//#include <iostream>
#include <chrono>
#include "stdafx.h"
#include "SerialPort.h"



/////////////////////////////////////////////////////////////////////////////
// CSerialPort
CSerialPort * CSerialPort::theSeialPortObjectPtr = 0;
CSerialPort::CSerialPort()
{
	//??EAG_LOG_DEBUG(L"CSerialPort::CSerialPort - start")

	InitializeCriticalSection(&m_csCommunicationSync);
	InitializeCriticalSection(&m_csCommunicationSync);

	// port number
	m_hComm = NULL;
	
	// initialize overlapped structure members to zero
	m_ov.Offset = 0;
	m_ov.OffsetHigh = 0;
	
	// create events
	m_hCharReceived 	= CreateEvent(NULL, TRUE, FALSE, NULL); 
	m_hWriteIsCompleted = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hWriteEvent		= CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hShutdownEvent	= CreateEvent(NULL, TRUE, FALSE, NULL);
	m_ov.hEvent			= CreateEvent(NULL, TRUE, FALSE, NULL);
	m_IshShutdown		= CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hTelegramReceived = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hThreadStartet	= CreateEvent(NULL, TRUE, FALSE, NULL);
	
	// defaults 
	m_nPortNr = 1;				// COM1
	m_nBaud = 9600; 
	m_cParity = 'N';
	m_nDatabits = 8; 
	m_csstopbits = '2';
	m_dwCommEvents = (EV_RXCHAR | EV_CTS | EV_EVENT1),

	///m_szWriteBuffer = NULL;
	///m_dwWriteBufferSize = 256 + 128;
	m_dwWriteBufferSize = MAXIMUM_DATA_BYTE * 2 + LENGTH_CONROLBITS;
	
	// no thread yet 
	m_bThreadAlive = FALSE;
	
	
	// telegram 
	m_XON = XON ;
	m_XOF = XOF ;
	m_nDeTelCounter = 0;
	
	m_bStrobe = FALSE;
	m_bLowNible = TRUE;
	m_dataHighNible = 0;
	m_bNewTelegramReceived = FALSE;

	// initialize the event objects
	m_hEventArray[0] = m_hShutdownEvent;	// highest priority
	m_hEventArray[1] = m_ov.hEvent;
	m_hEventArray[2] = m_hWriteEvent;

	m_nWaitForSingleObjectConstant = 2000;	// in milli second
		
	m_bFirstDebugRun = FALSE;				/// debug utility
	m_nProtocolSwitch = PS_NONE;			// internal switch signaling simple write action without protocol

	m_pPerformaceCounter = 0;				// performance counter

	theSeialPortObjectPtr = this;			// object pointer to itself
	
}

CSerialPort::~CSerialPort()
{
	int n = 0;
	if (m_pPerformaceCounter)
		delete m_pPerformaceCounter;
}

void CSerialPort::ProceedMsg()  
{
	MSG msg;
	while(!GetMessage(&msg,0,0,0))	
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}	
}

void CSerialPort::ProcessErrorMessage(char* ErrorText)
{
	char *Temp = new char[200];
	
	LPVOID lpMsgBuf;
	
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		//MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language SUBLANG_ENGLISH_UK
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK), // Default language SUBLANG_ENGLISH_UK
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		);
	


	sprintf(Temp, "WARNING:  %s Failed with the following error: \n%s\nPort: %d\n", (char*)ErrorText, lpMsgBuf, m_nPortNr); 
	
	if (lpMsgBuf) {
		CString csError = (LPTSTR)Temp;
		AfxMessageBox(csError);
		LocalFree(lpMsgBuf);   
	}
	//MessageBox(NULL, CStringUtility::CHARToWCHAR(Temp), _T("Application Error"), MB_ICONSTOP);
	

	delete[] Temp;
}
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  The CommThread (communication thread ) Function.                       //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
UINT CSerialPort::CommThread( LPVOID pParam )
{
	// Cast the void pointer passed to the thread back to
	// a pointer of CSerialPort class
	CSerialPort *port = (CSerialPort*)pParam;
	
	// Set the status variable in the dialog class to
	// TRUE to indicate the thread is running.
	port->RunMe();	
	return 0;
}
void CSerialPort::RunMe()
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(L"CSerialPort::RunMe - start ")
	// Misc. variables
	DWORD	BytesTransfered = 0; 
	DWORD	Event = 0;
	DWORD	CommEvent = 0;
	DWORD	dwError = 0;
	COMSTAT comstat;

	BOOL  bResult = TRUE;
	m_bThreadAlive = TRUE;
	memset(&comstat, 0, sizeof(COMSTAT));
	// signal thread is startet 
	SetEvent(m_hThreadStartet);
	
	// Clear comm buffers at startup
	if (m_hComm)		// check if the port is opened
		PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	
	// begin forever loop.  This loop will run as long as the thread is alive.
	for (;;) 
	{ 
		/*
		if (m_bFirstDebugRun == TRUE)
		{
			m_bFirstDebugRun = FALSE;
		}
		*/
	
		
		// Make a call to WaitCommEvent().  This call will return immediatly
		// because our port was created as an async port (FILE_FLAG_OVERLAPPED
		// and an m_OverlappedStructerlapped structure specified).  This call will cause the 
		// m_OverlappedStructerlapped element m_OverlappedStruct.hEvent, which is part of the m_hEventArray to 
		// be placed in a non-signeled state if there are no bytes available to be read,
		// or to a signeled state if there are bytes available.  If this event handle 
		// is set to the non-signeled state, it will be set to signeled when a 
		// character arrives at the port.
		
		// we do this for each port!
		
		bResult = WaitCommEvent(m_hComm, &Event, &m_ov);
		
		if (!bResult)  
		{ 
			// If WaitCommEvent() returns FALSE, process the last error to determin
			// the reason..
			switch (dwError = GetLastError()) 
			{ 
			case ERROR_IO_PENDING: 	 
				{ 
					// This is a normal return value if there are no bytes
					// to read at the port.
					// Do nothing and continue
					break;
				}

			case 87:
				{
					// Under Windows NT, this value is returned for some reason.
					// I have not investigated why, but it is also a valid reply
					// Also do nothing and continue.
					break;
				}
			default:
				{
					// All other error codes indicate a serious error has
					// occured.  Process this error.
					ProcessErrorMessage("WaitCommEvent()");
					
					break;
				}
			}
		}
		else
		{
			// If WaitCommEvent() returns TRUE, check to be sure there are
			// actually bytes in the buffer to read.  
			//
			// If you are reading more than one byte at a time from the buffer 
			// (which this program does not do) you will have the situation occur 
			// where the first byte to arrive will cause the WaitForMultipleObjects() 
			// function to stop waiting.  The WaitForMultipleObjects() function 
			// resets the event handle in m_OverlappedStruct.hEvent to the non-signelead state
			// as it returns.  
			//
			// If in the time between the reset of this event and the call to 
			// ReadFile() more bytes arrive, the m_OverlappedStruct.hEvent handle will be set again
			// to the signaled state. When the call to ReadFile() occurs, it will 
			// read all of the bytes from the buffer, and the program will
			// loop back around to WaitCommEvent().
			// 
			// At this point you will be in the situation where m_OverlappedStruct.hEvent is set,
			// but there are no bytes available to read.  If you proceed and call
			// ReadFile(), it will return immediatly due to the async port setup, but
			// GetOverlappedResults() will not return until the next character arrives.
			//
			// It is not desirable for the GetOverlappedResults() function to be in 
			// this state.  The thread shutdown event (event 0) and the WriteFile()
			// event (Event2) will not work if the thread is blocked by GetOverlappedResults().
			//
			// The solution to this is to check the buffer with a call to ClearCommError().
			// This call will reset the event handle, and if there are no bytes to read
			// we can loop back through WaitCommEvent() again, then proceed.
			// If there are really bytes to read, do nothing and proceed.
			
			bResult = ClearCommError(m_hComm, &dwError, &comstat);
			
			if (comstat.cbInQue == 0)
				continue;
		}	// end if bResult

		// Main wait function.  This function will normally block the thread
		// until one of nine events occur that require action.
		//LOG_OUT_CRITICAL(L"-")
		Event = WaitForMultipleObjects(3, m_hEventArray, FALSE, INFINITE);
		
		switch (Event)
		{

		case 0:
			{
				// Shutdown event.  This is event zero so it will be
				// the higest priority and be serviced first.
				m_bThreadAlive = FALSE;
				SetEvent(m_IshShutdown);
				// Kill this thread.  break is not needed, but makes me feel better.
				AfxEndThread(100);
				break;
			}
		case 1:	// read event
			{
				//BSTR wparam = NULL;
				//BYTE port = BYTEong (m_nPortNr));
				GetCommMask(m_hComm, &CommEvent);
				BSTR error = NULL;
				if (CommEvent & EV_CTS) 
				{
					Fire_OnCTSDetected(m_nPortNr);
				}
				
				if (CommEvent & EV_RXFLAG)
				{
					Fire_OnRXFLAGDetected(m_nPortNr);
				}
				
				
				if (CommEvent & EV_BREAK)
				{
					Fire_OnBreakDetected(m_nPortNr);
				}
				
				if (CommEvent & EV_ERR)
				{
					Fire_OnERRDetected(error, m_nPortNr);
				}
				
				if (CommEvent & EV_RING)
				{
					Fire_OnRINGDetected(m_nPortNr);
				}
				
				if (CommEvent & EV_RXCHAR)
					// Receive character event from port.
					ReceiveChar(comstat);
				break;
			}  
		case 2: // WRITE
			{
				// Write character to port
				//??EAG_LOG_CRITICAL(L"CSerialPort::RunMe - WRITE")
				WriteBuffer();
				break;
			}
		} // end switch
	} // close forever loop
	
	return ;
}

//
// Write a character.
//

// Character received. Inform the owner
//
void CSerialPort::ReceiveChar(COMSTAT comstat)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	HRESULT hr;
	BOOL  bRead = TRUE; 
	BOOL  bResult = TRUE;
	DWORD dwError = 0;
	DWORD BytesRead = 0;
	DWORD CommEvent;
	
	unsigned char RXBuff;
	//unsigned char PortNr;
	
	
	for (;;) 
	{ 
		// EAG_LOG_INFO(L"for loop --");
		// Gain ownership of the comm port critical section.
		// This process guarantees no other part of this program 
		// is using the port object. 
		
		EnterCriticalSection(&m_csCommunicationSync);
		// ClearCommError() will update the COMSTAT structure and
		// clear any other errors.
		bResult = ClearCommError(m_hComm, &dwError, &comstat);
		
		LeaveCriticalSection(&m_csCommunicationSync);
		
		// start forever loop.  I use this type of loop because I
		// do not know at runtime how many loops this will have to
		// run. My solution is to start a forever loop and to
		// break out of it when I have processed all of the
		// data available.  Be careful with this approach and
		// be sure your loop will exit.
		// My reasons for this are not as clear in this sample 
		// as it is in my production code, but I have found this 
		// solution to be the most efficient way to do this.
		
		if (comstat.cbInQue == 0)
		{
			// break out when all bytes have been read
		//	EAG_LOG_INFO(L"bre--");
			break;
		}
		
		EnterCriticalSection(&m_csCommunicationSync);
		
		if (bRead)
		{
			bResult = ReadFile(m_hComm,		// Handle to COMM port 
				&RXBuff,					// RX Buffer Pointer
				1,							// Read one byte
				&BytesRead,					// Stores number of bytes read
				&m_ov);						// pointer to the m_ov structure
	
			// deal with the error code 
			if (!bResult)  
			{ 
				//EAG_LOG_INFO(L"-e-");
				switch (dwError = GetLastError()) 
				{ 
				case ERROR_IO_PENDING: 	
					{ 
						// asynchronous i/o is still in progress 
						// Proceed on to GetOverlappedResults();
						bRead = FALSE;
						break;
					}
				default:
					{
						// Another error has occured.  Process this error.
					CString csEr;
					csEr.Format(L"%d", dwError);
					AfxMessageBox(csEr);
					///ProcessErrorMessage("ReadFile() " );
					break;
					} 
				}
			}
			else
			{
				// ReadFile() returned complete. It is not necessary to call GetOverlappedResults()
				bRead = TRUE;
			}
		}  // close if (bRead)
		
		if (!bRead)
		{
			bRead = TRUE;
			bResult = GetOverlappedResult(
				m_hComm,	// Handle to COMM port
				&m_ov,		// Overlapped structure
				&BytesRead,	// Stores number of bytes read
				TRUE); 			// Wait flag
			
			// deal with the error code 
			if (!bResult)  
			{
				ProcessErrorMessage("GetOverlappedResults() in ReadFile()");
			}	
		}  // close if (!bRead)
		
		LeaveCriticalSection(&m_csCommunicationSync);
		
		// notify parent that a byte was received // 0x80020003  S_OK
		//
		
		// hr = Fire_OnReceiveChar((BYTE)RXBuff, (BYTE)m_nPortNr); // 
		if (BytesRead > 1)	{
			ProcessErrorMessage("hopla...");
			AfxMessageBox(L"hopla...");
			// ignore !!!
		}

		SetEvent(m_hCharReceived);
		// start with Telegram construction;		h
		
		// build telegram
		//BuildTelegram(RXBuff, (BYTE)m_nPortNr);

		/**/
		GetCommMask(m_hComm, &CommEvent);
		if (CommEvent & EV_EVENT1) 
		{
			BuildTelegram(RXBuff, (BYTE)m_nPortNr);
		}
		
	} // end forever loop
	
}
void CSerialPort::update()
{/**/
	m_bNewTelegramReceived = TRUE;
	Fire_OnReceiveModBus(m_szReceiveBuffer, m_nDeTelCounter, m_nPortNr);
	SetEvent(m_hTelegramReceived);
	// reset counter 
	m_nDeTelCounter = 0;
}

LONG CSerialPort::CallBackFunction()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CSerialPort* pSelf = theSeialPortObjectPtr;
	pSelf->update();
	return 1;
}

////////////////////////////////////////////////////////////
// build telegram and return lenght of builded
// telegram
int CSerialPort::BuildTelegram(unsigned char ch, BYTE PortNr) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	static char cPrevious = '\0';
	static bool sbAsciReceive = false;
	try
	{	
	#ifdef DEBUG
	//	csdumy.Format(L"0x%02x", nData);
	//	EAG_LOG_DEBUG(csdumy);
	#endif

		// test for modbus answer
		if (m_nProtocolSwitch == PS_MODBUS_ASCII)
		{	
			if (ch == ':') {
				sbAsciReceive = true;
				m_nDeTelCounter = 0;
				//memset((void*) m_szReceiveBuffer, '\0', (size_t) LENGTH_DETEL_RECEIVE);
				memset((void*)m_szReceiveBuffer, '\0', 15000);

				// m_szReceiveBuffer[m_nDeTelCounter++] = ch;
			}
			if (sbAsciReceive == true) {
				// now it critical!
				// *********************************************
				EnterCriticalSection(&m_csCommunicationSync);
				m_szReceiveBuffer[m_nDeTelCounter++] = ch;
				LeaveCriticalSection(&m_csCommunicationSync);
				// *********************************************
			}

		if (ch == 0x0A & cPrevious == 0x0D & m_szReceiveBuffer[0] ==':')		// CR=0x0A,  LF=0x0D,  ':'=0x3A
			{ // ASCII MODE
				m_bNewTelegramReceived = TRUE;
				Fire_OnReceiveModBus(m_szReceiveBuffer, m_nDeTelCounter, PortNr);
				SetEvent(m_hTelegramReceived);
				sbAsciReceive = false;
			}
		/*else
		{	// RTU MODE
			
			if (m_nDeTelCounter == 6)
			{
				if (m_szReceiveBuffer[1] <= 0x3) 
				{  // read functions

					wSizeReceivedData = m_szReceiveBuffer[4];  // high
					wSizeReceivedData << 8;
					wSizeReceivedData = wSizeReceivedData | m_szReceiveBuffer[5];
				}
			}

			if (m_nDeTelCounter == wSizeReceivedData + 5 )  // size reached
			{

				SetEvent(m_hTelegramReceived);
			}

		}*/
		}
		else if (m_nProtocolSwitch == PS_MODBUS_RTU )
		{
			//	create performance counter and
			//	pass call back funtion to it
			//
			if (m_pPerformaceCounter == 0)
			{
				m_pPerformaceCounter = new CPerformanceCounter;
				typedef  LONG(*f)();
				f func = &CSerialPort::CallBackFunction;
				m_pPerformaceCounter->AddCallBackFunction((LONG*)func);
				m_pPerformaceCounter->StartThread();
				m_nDeTelCounter = 0;
				
			}
			m_pPerformaceCounter->Reset();
	
			// store coming byte 
			// *********************************************
			EnterCriticalSection(&m_csCommunicationSync);
			m_szReceiveBuffer[m_nDeTelCounter++] = ch;
			LeaveCriticalSection(&m_csCommunicationSync);
			// *********************************************


			// it in rtu mode ascii frame came
			// then m_nDeTelCounter should be cleared
			// 
			if (ch == 0x0A & cPrevious == 0x0D & m_szReceiveBuffer[0] == ':')
			{
				m_nDeTelCounter = 0;
			}

		}
		else if (m_nProtocolSwitch == PS_DETEL)
		{  // detel
		
			switch (ch)
			{
			case XON:
				m_nDeTelCounter = 0;

				m_bNewTelegramReceived = FALSE;
				m_bStrobe = TRUE;
				m_bLowNible = FALSE;
				memset((void*) m_szReceiveBuffer, '\0', (size_t) LENGTH_DETEL_RECEIVE);
				m_szReceiveBuffer[m_nDeTelCounter] = m_XON;
				m_nDeTelCounter = 1;
	

				break;

			case XOF:
				if (m_bStrobe == TRUE)
				{
	
					m_bNewTelegramReceived = TRUE;
					m_bStrobe = FALSE;

					// now it critical!
					// *********************************************
					EnterCriticalSection(&m_csCommunicationSync);
					m_szReceiveBuffer[m_nDeTelCounter] = m_XOF;
					LeaveCriticalSection(&m_csCommunicationSync);
					// *********************************************
					m_nDeTelCounter++;
					Fire_OnReceiveDeTel(m_szReceiveBuffer, m_nDeTelCounter, PortNr);
					SetEvent(m_hTelegramReceived);

				}
				break;

			default:
				if (m_bStrobe == TRUE)
				{
					/*
					if (!m_bLowNible)					// high nibble
					{
						//ch = ch & 0xF0;
	//					m_dataHighNible = (ch & 0xF0);
						m_dataHighNible = ch ;
						m_bLowNible = TRUE;				// the next should be low nibble
					}
					else
					{
						m_bLowNible = FALSE;			// the next should be high nibble
						//ch = ch & 0x0F;
						//ch = m_dataHighNible | ch;

						// now it critical!
						// *********************************************
						EnterCriticalSection(&m_csCommunicationSync);
						// m_szReceiveBuffer[m_nDeTelCounter++] = (m_dataHighNible | (ch & 0x0F));
						m_szReceiveBuffer[m_nDeTelCounter++] = (m_dataHighNible | ch );
						LeaveCriticalSection(&m_csCommunicationSync);
						// *********************************************


					}
					*/
					// now it critical!
					// *********************************************
					EnterCriticalSection(&m_csCommunicationSync);
					m_szReceiveBuffer[m_nDeTelCounter] = ch;
					LeaveCriticalSection(&m_csCommunicationSync);
					// *********************************************
					m_nDeTelCounter++;

				}
				break;
			}
		}  
		else 
		{
			// no protocol selected !
			Fire_OnReceiveChar(ch, PortNr);
			; //no protocol selected !
		}
	}
	catch(...)
	{
		//??EAG_LOG_ERROR(_T("CSerialPort::BuildTelegram - unkown error ! "));
	}

	cPrevious = ch;				// keep previous
	return 0;
}
//////////////////////////////////////////////////////////////
// 
// data part of the telegram is sent in  two byte
// first low nible is sent
// receiving slave must combine them. 
//
//  example  : 
//  data to be sent  :  0xAB
//  
//  two bytes actualy sent  ;   0x0B (low part first)
//                              0xA0 (high part next)   
//                          
//                           
////////////////////////////////////////////////////////////////
BOOL CSerialPort::SendDeTelDublex(DeTel& telegram, BYTE* pBuffer)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("SendDeTelDublex::SendDeTelTelegram - start "))

	if (m_bThreadAlive == FALSE)
	{
		//??EAG_LOG_ERROR(_T("CSerialPort::SendDeTelDublex - thread is not alive ! "))
		return FALSE;
	}
	Purge();
	// wait on write will soon start...
	ResetEvent(m_hWriteIsCompleted);
	ResetEvent(m_hWriteEvent);
	try
	{
		int nSize = 0;	
		// send buffer 
		BYTE buffer[MAXIMUM_DATA_BYTE*2+LENGTH_CONROLBITS] ; // data byte
		
		// ----- start to construct telegram -----
		buffer[nSize++] = telegram.XON;  
		buffer[nSize++] = telegram.cm1; 
		buffer[nSize++] = telegram.cm2; 
		buffer[nSize++] = telegram.ad0; 
		buffer[nSize++] = telegram.ad1; 
		buffer[nSize++] = telegram.ad2; 
		buffer[nSize++] = telegram.ad3; 
		buffer[nSize++] = telegram.nil; 
		buffer[nSize++] = telegram.rs0; 
		buffer[nSize++] = telegram.rs1; 
		buffer[nSize++] = telegram.rs2; 
		buffer[nSize++] = telegram.cnt;  
		
		BYTE data[MAXIMUM_DATA_BYTE];
		
		// copy data buffer 
		memcpy((void*)data, (void*)pBuffer, (size_t) telegram.cnt);
		
		for (BYTE i = 0; i < telegram.cnt; i++) 
		{
			// implement half mode tranmission scheme
			buffer[nSize++]	= data[i] & 0xF0;     // low nible;
			buffer[nSize++]	= data[i] & 0x0F;     // high nible;
		}	
		
		buffer[nSize++] = telegram.XOF;   
		// ----- end of telegram -----
		
		// increase write buffer size to nSize
		m_dwWriteBufferSize = nSize;

		CCriticalSection cs;
		//*********************************************;
		// criticalsection start 
		cs.Lock() ;
		// fill write buffer
		memcpy((void*)m_szWriteBuffer, (void*)buffer, (size_t) nSize);
		memset((void*)m_szWriteBuffer, '\0', (size_t)300);								// clear write buffer
		memcpy((void*)m_szWriteBuffer, (void*)buffer, (size_t)nSize);					// fill write buffer

	
		// criticalsection end 
		cs.Unlock();
		//*********************************************;
		
		// WRITE 
		SetEvent(m_hWriteEvent);

		Sleep(1);
/**/	MSG msg;
		while (!GetMessage(&msg, 0, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1);

		DWORD rt = WaitForSingleObject(m_hWriteIsCompleted, 2*m_nWaitForSingleObjectConstant);
		if (rt == WAIT_OBJECT_0) {
			//??EAG_LOG_CRITICAL(_T("CSerialPort::SendDeTelDublex - signaled "))
		}else if (rt = WAIT_TIMEOUT)	{
			//??EAG_LOG_ERROR(_T("CSerialPort::SendDeTelDublex - wait time is out for writing telegram "))
			return FALSE;
		}		
			
	}
	catch(...)
	{
		//??EAG_LOG_ERROR(_T("CSerialPort::SendDeTelDublex - exception "))
		return FALSE;
	}

	// make notify to process received telegram;
	Fire_NotifyTelegramSend(m_nPortNr);
	return TRUE;
}
BOOL  CSerialPort::SendDeTelSingle(DeTel& telegram,  BYTE* pBuffer)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::SendDeTelSingle - not yet implemented ! "))
	return FALSE;

	// test if Thread is alive
	if (!m_bThreadAlive)
	{
		//??EAG_LOG_ERROR(_T("CSerialPort::SendDeTelSingle - thread is not alive ! "))
		return FALSE;
	}
	ResetEvent(m_hWriteEvent); 
	try
	{
		
		int nSize = 0;	
		
		// global send buffer 
		BYTE buffer[528] ;
		
		// ----- start to construct telegram -----
		buffer[nSize++] = telegram.XON; 
		buffer[nSize++] = telegram.cm1; 
		buffer[nSize++] = telegram.cm2; 
		buffer[nSize++] = telegram.ad0; 
		buffer[nSize++] = telegram.ad1; 
		buffer[nSize++] = telegram.ad2; 
		buffer[nSize++] = telegram.ad3; 
		buffer[nSize++] = telegram.nil; 
		buffer[nSize++] = telegram.rs0; 
		buffer[nSize++] = telegram.rs1; 
		buffer[nSize++] = telegram.rs2; 
		buffer[nSize++] = telegram.cnt; 
		
		BYTE data[256];
		
		memcpy((void*)data, (void*)pBuffer, (size_t) telegram.cnt);
		
		for (BYTE i = 0; i < telegram.cnt; i++) 
		{
			// implement single protocol
			buffer[nSize++] = data[i];
		}	
		
		buffer[nSize++] = telegram.XOF;  
		// ----- end of telegram -----
		
		// increase buffer size to nSize
		m_dwWriteBufferSize = nSize;
		
		CCriticalSection cs;
		//*********************************************;
		// criticalsection
		cs.Lock();
		memcpy((void*) m_szWriteBuffer, (void*) buffer, (size_t) nSize);
		
		cs.Unlock();
		//*********************************************;
		
		// reset 
		ResetEvent(m_hWriteIsCompleted);
		ResetEvent(m_hTelegramReceived);
		
		// clear receive buffer
		memset((void*) m_szReceiveBuffer, '0', (size_t) LENGTH_DETEL_RECEIVE);
		// set event for write
		SetEvent(m_hWriteEvent); 
		SetEvent(m_hWriteEvent); 
		
		
	}
	catch(...)
	{
		//??EAG_LOG_ERROR(_T("CSerialPort::SendDeTelSingle - exception "))
		return FALSE;
	}
	
	MSG msg;
	while(!GetMessage(&msg,0,0,0))	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}	

	// wait until respons to telegram is obtained
	if (WaitForSingleObject(m_hTelegramReceived, m_nWaitForSingleObjectConstant) == WAIT_TIMEOUT)
	{
		return FALSE;
	}
	// make notify to process received telegram;
	Fire_NotifyTelegramSend(m_nPortNr);
	return TRUE;
}

//BOOL  CSerialPort::SendDeTelAscii(DeTel& telegram, BYTE* pBuffer)
BOOL  CSerialPort::SendDeTelAscii(DeTel& telegram)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::SendDeTelSingle - not yet implemented ! "))
	// return FALSE;

	// test if Thread is alive
	if (!m_bThreadAlive)
	{
		//??EAG_LOG_ERROR(_T("CSerialPort::SendDeTelSingle - thread is not alive ! "))
		return FALSE;
	}
	ResetEvent(m_hWriteEvent);

	try
	{

		int nSize = 0;
		char cL, cH;

		// global send buffer 
		BYTE buffer[300];
		memset(buffer, 0, 300);

		buffer[nSize++] = ':';// start
		// ----- start to construct telegram -----
		CNumberUtility::put_In_Hex(telegram.XON, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.cm1, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.cm2, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.ad0, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.ad1, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.ad2, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.ad3, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.nil, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.rs0, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.rs1, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.rs2, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		CNumberUtility::put_In_Hex(telegram.cnt, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;

//		BYTE data[MAXIMUM_DATA_BYTE = 128];

		for (BYTE i = 0; i < MAXIMUM_DATA_BYTE; i++)
		{
			// implement single protocol
			CNumberUtility::put_In_Hex(telegram.db[i], cL, cH);  
			buffer[nSize++] = cH; 
			buffer[nSize++] = cL;
		}
		
		// buffer[nSize++] = telegram.XOF;
		CNumberUtility::put_In_Hex(telegram.XOF, cL, cH);  buffer[nSize++] = cH; buffer[nSize++] = cL;
		
		// parity must be includend

		// end up
		buffer[nSize++] = '\n';
		buffer[nSize++] = '\r';

		// ----- end of telegram -----

		// increase buffer size to nSize
		m_dwWriteBufferSize = nSize;


		/// convert to ascii
	
		// reset 
		ResetEvent(m_hWriteIsCompleted);

		CCriticalSection cs;
		//*********************************************;
		// criticalsection
		cs.Lock();
		
		memset((void*)m_szReceiveBuffer, '\0', (size_t)LENGTH_DETEL_RECEIVE);			// clear receive buffer
		memset((void*) m_szWriteBuffer, '\0', (size_t)300);								// clear write buffer
		memcpy((void*) m_szWriteBuffer, (void*)buffer, (size_t)nSize);					// fill write buffer
		cs.Unlock();
		//*********************************************;

		// set event for write
		SetEvent(m_hWriteEvent);

	}
	catch (...)
	{
		//??EAG_LOG_ERROR(_T("CSerialPort::SendDeTelSingle - exception "))
		return FALSE;
	}

	MSG msg;
	while (!GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// wait until respons to telegram is obtained
	if (WaitForSingleObject(m_hWriteIsCompleted, m_nWaitForSingleObjectConstant) == WAIT_TIMEOUT)
	{
		return FALSE;
	}
	// make notify to process received telegram;
	Fire_NotifyTelegramSend(m_nPortNr);
	/**/	
	return TRUE;
}
void CSerialPort::WriteBuffer()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(L"CSerialPort::WriteBuffer - start")

	CString csMessage;
	BOOL bWrite = TRUE;
	BOOL bResult = TRUE;

	DWORD BytesSent = 0;

	ResetEvent(m_hWriteEvent);

	// Gain ownership of the critical section
	EnterCriticalSection(&m_csCommunicationSync);

	////////////////////////// start of write history //////////////
	//	CString csMsg(m_szWriteBuffer);
	// Initailize variables
	for (int nVersuch = 0; nVersuch < 1; nVersuch++)
	{
		m_ov.Offset = 0;
		m_ov.OffsetHigh = 0;

		// Clear buffer
		PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

		size_t t = (size_t)m_dwWriteBufferSize;
		bResult = WriteFile(
			m_hComm,			// Handle to COMM Port
			m_szWriteBuffer,	// Pointer to message buffer in calling function
			t,					// Length of message to send
			&BytesSent,			// Where to store the number of bytes sent
			&m_ov				// Overlapped structure
		);


		// deal with any error codes
		if (!bResult)
		{
			DWORD dwError = GetLastError();
			switch (dwError)
			{
			case ERROR_IO_PENDING:
			{
				// continue to GetOverlappedResults()
				BytesSent = 0;
				bWrite = FALSE;
				break;
			}
			default:
			{
				// all other error codes
				ProcessErrorMessage("CSerialPort::WriteBuffer - WriteFile()");
			}
			}

		}
		else {
			break;
		}

		if (!bWrite) {
			bResult = GetOverlappedResult(
				m_hComm,		// Handle to COMM port 
				&m_ov,			// Overlapped structure
				&BytesSent,		// Stores number of bytes sent
				TRUE			// Wait flag
			);
			// deal with the error code 
			if (!bResult) {
				ProcessErrorMessage("CSerialPort::WriteBuffer - GetOverlappedResults() fails !");
				continue;
			}
		}

	} // versuch loop

	  ////////////////////////// end of write history //////////////

	LeaveCriticalSection(&m_csCommunicationSync);
	if (!bResult) {
		//csMessage.Format(_T("CSerialPort::WriteBuffer - write is incomplete !!"));
		//??EAG_LOG_ERROR(csMessage);
		return;
	}

	SetEvent(m_hWriteIsCompleted); // signal write event 

	NotifyCharSend(BytesSent);
}
void CSerialPort::ParseInitString(CString csInitString)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::ParseInitString - init "))

#define START 1 + 100 
#define END 2 + 100
#define EQUAL 3 + 100
	CToken token;
	
	CSymbol symSTART(L"<", START);
	CSymbol symEND(L">", END);
	CSymbol symEQUAL(L"=", END);
	
	m_LexSer.SetSymbol(symSTART);
	m_LexSer.SetSymbol(symEND);
	m_LexSer.SetSymbol(symEQUAL);
	
	
	BOOL bError = FALSE;
	CString csIdentifier;
	CString csValue;
	
	m_LexSer.String2TokenSequence(csInitString);
	POSITION pos;
	pos = m_LexSer.m_TokenSequence.GetHeadPosition();
	while (pos)
	{
		bError = FALSE;
		
		token = m_LexSer.m_TokenSequence.GetNext(pos);
		
		try
		{
			if (token.getTokenName().CompareNoCase(_T("<"))!=0)
			{
				bError = TRUE;
				continue;
			}
			
			token = m_LexSer.m_TokenSequence.GetNext(pos);
			if (token.getTokenType() != idT)
			{
				bError = TRUE;
				continue;
				
			}
			
			csIdentifier = token.getTokenName();
			
			token = m_LexSer.m_TokenSequence.GetNext(pos);
			if (token.getTokenName().CompareNoCase(_T("="))!=0)
			{
				bError = TRUE;
				continue;
				
			}  
			
			token = m_LexSer.m_TokenSequence.GetNext(pos);
			if ( !( token.getTokenType() == idT
				||token.getTokenType() == intT 
				||token.getTokenType() == realT ) 	)
			{
				bError = TRUE;
				continue;
				
			}
			
			csValue = token.getTokenName();
			
		}
		catch(...) 
		{
			bError = FALSE;
		}
		
		// only do if no error
		if (!bError)
		{
			if(csIdentifier.CompareNoCase(_T("baud"))==0)
			{
				m_nBaud = _wtoi(csValue.GetBuffer(0));
			}
			
			else if(csIdentifier.CompareNoCase(_T("parity"))==0)
			{
				if (csValue.CompareNoCase(_T("NONE"))==0)
					m_cParity = 'N';
				if (csValue.CompareNoCase(_T("ODD"))==0)
					m_cParity = 'O';
				if (csValue.CompareNoCase(_T("EVEN"))==0)
					m_cParity = 'E';
			}
			
			else if(csIdentifier.CompareNoCase(_T("databits"))==0)
			{
				m_nDatabits = _wtoi(csValue.GetBuffer(0));
			}
			
			else if(csIdentifier.CompareNoCase(_T("stopbits"))==0)
			{
				//m_nstopbits = atoi(csValue.GetBuffer(0));
				m_csstopbits = csValue;
			}
			
		}
		
	}  // while 
	
//	int nHalt = 0;
	
}//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////// I N T E R F A C E ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CSerialPort::SendDeTelTelegram(IUnknown *pTelegram)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::SendDeTelTelegram - start ")) SendDeTelTelegram
	BOOL rt;
	BYTE buffer[MAXIMUM_DATA_BYTE]; //[500];
	int nSize;
	DeTel detel_;
	DeTel *pdetel = &detel_ ;
	IMTelegram *pIsMTelegram = NULL ; //(IMTelegram*)pTelegram ;
	
	HRESULT hr = pTelegram->QueryInterface(IID_IMTelegram,(void**)&pIsMTelegram);
	if (hr == S_OK)
		pIsMTelegram->Release();
	else return hr;

	//pMTelegram->GetBuffer(buffer, &nSize);
	((IMTelegram *)pTelegram)->GetDeTel((unsigned char **)&pdetel);
	
//	Purge();	// temizle

		
//	ResetEvent(m_hTelegramReceived);
	if (m_nProtocolSwitch == PS_DETEL)
	{	
		rt = SendDeTelDublex(detel_, buffer);
	}
	else if (m_nProtocolSwitch == PS_MODBUS_ASCII)
	{
		rt = SendDeTelAscii(detel_);
	}

		
		MSG msg;
		while(!GetMessage(&msg,0,0,0))	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}	

		Sleep(1);

		if (rt)
			return S_OK;
		else
			return S_FALSE;
		
}
STDMETHODIMP CSerialPort::OpenPort(BSTR* initStr, BYTE portnr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	EAG_LOG_INFO(_T("CSerialPort::OpenPort - start "))
	
	CString csMessage;
	CString csInitString = CStringUtility::bstrToCString (*initStr);



	// csMessage.Format(L"CSerialPort::OpenPort - init string: %s",csInitString );
	//??EAG_LOG_INFO(csMessage)
	ParseInitString(csInitString);
	m_nPortNr = portnr;		


	// if the thread is alive: return
	if(m_bThreadAlive)
	{
		return S_OK ;
	}

	// initialize events
	if (m_ov.hEvent != NULL)
		ResetEvent(m_ov.hEvent);
	
	if (m_hWriteEvent != NULL)
		ResetEvent(m_hWriteEvent);
	
	if (m_hShutdownEvent != NULL)
		ResetEvent(m_hShutdownEvent);
	
	
	// initialize critical section
	InitializeCriticalSection(&m_csCommunicationSync);
	

	BOOL bResult = FALSE;
	//char *szPort = new char[50];
	//char *szBaud = new char[2*50];
	char szPort[50];
	char szBaud[2*50];

	// now it critical!
	// *********************************************
	EnterCriticalSection(&m_csCommunicationSync);
	
	// if the port is already opened: close it
	if (m_hComm != NULL)
	{
		CloseHandle(m_hComm);
		m_hComm = NULL;
	}
	
	// prepare port strings
	sprintf((char*)&szPort, "\\\\.\\COM%d", m_nPortNr);
	sprintf((char*)&szBaud, "baud=%d parity=%s data=%d stop=%s", m_nBaud, m_cParity, m_nDatabits, m_csstopbits);


	// get a handle to the port
	wchar_t * pwcPort = CStringUtility::CHARToWCHAR(szPort);

	m_hComm = CreateFileW(
		pwcPort ,								// communication port string (COMX)
		GENERIC_READ | GENERIC_WRITE,			// read/write types
		0,										// comm devices must be opened with exclusive access
		NULL,									// no security attributes
		OPEN_EXISTING,							// comm devices must use OPEN_EXISTING
		FILE_FLAG_OVERLAPPED,					// Async I/O
		NULL									// template must be 0 for comm devices
	);	
	// deallocate
	delete pwcPort;
	
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		// port not found
		//delete [] szPort;
		//delete [] szBaud;
		
		// release critical section
		LeaveCriticalSection(&m_csCommunicationSync);
		csMessage.Format(_T("CSerialPort::OpenPort - invalid handle valule"));
		//??EAG_LOG_ERROR(csMessage)
		return E_FAIL;
	}
	
	// set the timeout values
	m_CommTimeouts.ReadIntervalTimeout = 50; // 100;
	m_CommTimeouts.ReadTotalTimeoutConstant = 50 ;// 1000;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 50; // 1000;
	m_CommTimeouts.WriteTotalTimeoutConstant = 50; //  1000;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 10000;// 1000;


	// configure
	if (SetCommTimeouts(m_hComm, &m_CommTimeouts)) 
	{						   
		if (SetCommMask(m_hComm, m_dwCommEvents))
		{
			if (GetCommState(m_hComm, &m_dcb)) 
			{
				m_dcb.fRtsControl = RTS_CONTROL_ENABLE;		// set RTS bit high!
				wchar_t* wcBBaud = CStringUtility::CHARToWCHAR((char*)&szBaud);
				if (BuildCommDCB(wcBBaud, &m_dcb))
				{
					if (SetCommState(m_hComm, &m_dcb))
						; // normal operation... continue
					else
						ProcessErrorMessage("SetCommState()");
				}
				else
					ProcessErrorMessage("BuildCommDCB()");

				// clear buffer
				delete wcBBaud;
			}
			else
				ProcessErrorMessage("GetCommState()");
		}
		else
			ProcessErrorMessage("SetCommMask()");
	}
	else
		ProcessErrorMessage("SetCommTimeouts()");
	
//	delete [] szPort;
//	delete [] szBaud;

	// flush the port
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	
	// release critical section
	// *********************************************
	LeaveCriticalSection(&m_csCommunicationSync);
	
	TRACE(L"Initialisation for communicationport %d completed.\nUse Startmonitor to communicate.\n", portnr);
	return S_OK;
}

STDMETHODIMP CSerialPort::Kill()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::Kill - start "))

	// if the thread is alive: Kill
	if (m_bThreadAlive)
	{
		
		// clear IsShutDown event 
		ResetEvent(m_IshShutdown);
		
		// make shutdown
		SetEvent(m_hShutdownEvent); 
		/*
		do 
		{
		ProceedMsg();
		} while(m_bThreadAlive);
		*/

		MSG msg;
		while(!GetMessage(&msg,0,0,0))	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}	

		//wait until thread is shut down
		if (WaitForSingleObject(m_IshShutdown, 5000) == WAIT_TIMEOUT)
		{
			TRACE(_T("can not kill thread , wait time is out"));
			//??EAG_LOG_ERROR(_T("CSerialPort::Kill - Thread is ended"))
			return S_FALSE;
		}
		/*	*/
		//??EAG_LOG_INFO(_T("CSerialPort::Kill - Thread is ended"))
	}
	else 
	{
		//??EAG_LOG_INFO(_T("CSerialPort::Kill - Thread is already ended"))
	}
	return S_OK;
}
STDMETHODIMP CSerialPort::StartMonitoring()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::StartMonitoring - start "))

	if (S_OK == CanDo())
	{
		//??EAG_LOG_INFO(_T("CSerialPort::StartMonitoring - already started  !"))
		return S_OK;
	}
	
	ResetEvent(m_hThreadStartet);
	if (!(m_pThread = AfxBeginThread(CommThread, this)))
	{
		//??EAG_LOG_WARNING(_T("CSerialPort::StartMonitoring - can not start monitoring, S_FALSE returned !"))
		return S_FALSE;
	}
	
	// wait until respons to telegram is obtained
	if (WaitForSingleObject(m_hThreadStartet, m_nWaitForSingleObjectConstant) == WAIT_TIMEOUT)
	{
		//??EAG_LOG_ERROR(_T("CSerialPort::StartMonitoring - can not start montoring, time is out !  "))
		return E_FAIL;
	}	
	
	m_pThread->SetThreadPriority(THREAD_PRIORITY_HIGHEST);
	
	//??EAG_LOG_INFO(_T("CSerialPort::StartMonitoring - thread started OK  "))
	//TRACE("Thread started\n");
	return S_OK;	
		
}
STDMETHODIMP CSerialPort::CanDo() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::CanDo - start "))
	return ( (m_bThreadAlive) ? S_OK : S_FALSE );
}
STDMETHODIMP CSerialPort::ClosePort()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_INFO(_T("CSerialPort::CanDo - ClosePort "))
	Purge();
	if (S_OK == Kill())
	{
		CloseHandle(m_hComm);
		m_hComm = NULL;
		//??EAG_LOG_INFO(_T("CSerialPort::ClosePort - ends"))
		return S_OK;
	}
	
	//??EAG_LOG_ERROR(_T("CSerialPort::ClosePort - can not close port"))
	return S_FALSE;
}
STDMETHODIMP CSerialPort::get_ComEvents(DWORD *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::get_ComEvents - ClosePort "))
		*pVal = m_dwCommEvents ;
	return S_OK;
}
STDMETHODIMP CSerialPort::put_ComEvents(DWORD newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::put_ComEvents - ClosePort "))
	m_dwCommEvents = newVal;
	return S_OK;
}
STDMETHODIMP CSerialPort::get_WriteBufferSize(DWORD *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::get_WriteBufferSize - ClosePort "))
	*pVal = m_dwWriteBufferSize;
	return S_OK;
}
STDMETHODIMP CSerialPort::put_WriteBufferSize(DWORD newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(_T("CSerialPort::get_WriteBufferSize - ClosePort "))
	m_dwWriteBufferSize = newVal;
	return S_OK;
}
STDMETHODIMP CSerialPort::RestartMonitoring()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(L"CSerialPort::RestartMonitoring - start ")
	TRACE("Thread resumed\n");
	if (m_bThreadAlive)
	{
		m_pThread->ResumeThread();
		//??EAG_LOG_INFO(_T("CSerialPort::RestartMonitoring - ends"))
		return S_OK;
	}
	//??EAG_LOG_ERROR(_T("CSerialPort::RestartMonitoring - thread is not alive !"))
	return S_FALSE;
}
STDMETHODIMP CSerialPort::StopMonitoring()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(L"CSerialPort::StopMonitoring - start ")

	TRACE("Thread suspended\n");
	if (m_bThreadAlive)
	{
		m_pThread->SuspendThread(); 
		//??EAG_LOG_INFO(_T("CSerialPort::StopMonitoring - ends"))
		return S_OK;
	}
	//??EAG_LOG_ERROR(_T("CSerialPort::StopMonitoring - thread is not alive !"))
	return S_FALSE;
	
}
STDMETHODIMP CSerialPort::Purge()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??//??EAG_LOG_DEBUG(L"CSerialPort::Purge - start ")

	// flush the port
	try
	{
		PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	}
	catch(...)
	{
		;
	}
	m_nDeTelCounter = 0;
	return S_OK;
}
STDMETHODIMP CSerialPort::WriteBuffer(BYTE *buffer, int nsize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(L"CSerialPort::WriteBuffer(buffer, nsize) - start ")
	Purge();
	if (m_bThreadAlive == FALSE)
	{
		//??EAG_LOG_ERROR(_T("CSerialPort::WriteBuffer - thread is not alive ! "))
		return FALSE;
	}
		
	try
	{
		// wait on write completed
		ResetEvent(m_hTelegramReceived); 
		ResetEvent(m_hWriteIsCompleted);
		ResetEvent(m_hWriteEvent);  
		
		CCriticalSection cs;
		//*********************************************;
		// criticalsection
		cs.Lock() ;		
		
		memset((void*) m_szReceiveBuffer, '0', (size_t)LENGTH_DETEL_RECEIVE);
		// increase buffer size to nSize
		m_dwWriteBufferSize = nsize;

	//	m_szWriteBuffer[nsize] = '\0';
		memcpy((void*) m_szWriteBuffer, (void*) buffer, (size_t) nsize);
		m_nDeTelCounter = 0;		// incoming char counter reset

		// criticalsection end 
		cs.Unlock();
		///////////////////////////
		
		/// test 
		//CString csMsg;// 
		//CNumberUtility::BYTEStreamToString(m_szWriteBuffer, nsize, csMsg);
		//CNumberUtility::BYTEStreamToChar(m_szWriteBuffer, nsize, csMsg);
		//csMsg = L"CSerialPort::WriteBuffer - m_szWriteBuffer =  " + csMsg;
		//??EAG_LOG_INFO(csMsg)

				// set event for write
		SetEvent(m_hWriteEvent);

/*
		// WRITE
		m_bFirstDebugRun = TRUE;
		Sleep(1);
		SetEvent(m_hWriteEvent);	// write -  event already reset
		Sleep(10);


	
		MSG msg;
		while (!GetMessage(&msg, 0, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(10);
	
		// check result
		DWORD rt = WaitForSingleObject(m_hWriteIsCompleted, m_nWaitForSingleObjectConstant);

		if (rt == WAIT_OBJECT_0) {
			//??EAG_LOG_INFO(_T("CSerialPort::WriteBuffer - signaled "))
		}
		else if (rt = WAIT_TIMEOUT) {
			//??EAG_LOG_ERROR(_T("CSerialPort::WriteBuffer - wait time is out for writing telegram "))
			return FALSE;
		}
*/	
	}

	catch(...)
	{
		//??EAG_LOG_ERROR(_T("CSerialPort::WriteBuffer - exception "))
		return S_FALSE;
	}

	// wait until respons to telegram is obtained
	if (WaitForSingleObject(m_hWriteEvent, m_nWaitForSingleObjectConstant) == WAIT_TIMEOUT)
	{
		return FALSE;
	}
	// make notify to process received telegram;
	//Fire_NotifyTelegramSend(m_nPortNr);
	return S_OK;
}
STDMETHODIMP CSerialPort::get_WaitForSingleObjectConstant(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = m_nWaitForSingleObjectConstant;
	return S_OK;
}
STDMETHODIMP CSerialPort::put_WaitForSingleObjectConstant(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_nWaitForSingleObjectConstant = newVal;
	return S_OK;
}
STDMETHODIMP CSerialPort::get_ProtocolSwitch(SHORT* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		//??EAG_LOG_DEBUG(L"CSerialPort::get_ProtocolSwitch - start ")

	*pVal = m_nProtocolSwitch;

	return S_OK;
}
STDMETHODIMP CSerialPort::put_ProtocolSwitch(SHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_nProtocolSwitch = newVal;
	switch (m_nProtocolSwitch)  
	{
	case PS_KEINE :
		break;
	case  PS_DETEL :
		//??EAG_LOG_INFO(L"CSerialPort::put_ProtocolSwitch - DETEL ")
			break;
	case PS_MODBUS_ASCII:
		//??EAG_LOG_INFO(L"CSerialPort::put_ProtocolSwitch - MODBUS_ASCII")
			break;
	case PS_MODBUS_RTU:
		//??EAG_LOG_INFO(L"CSerialPort::put_ProtocolSwitch - MODBUS_RTU")

		break;
		;
	default:
		;
	}

	return S_OK;
}






