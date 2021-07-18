// SerialSink.cpp : Implementation of CSerialSink

#include "stdafx.h"
#include "SerialSink.h"


// CSerialSink

/////////////////////////////////////////////////////////////////////////////
// CSerialSink

CSerialSink::CSerialSink()
{
	m_bError = FALSE;
	m_csMessage = "";
	memset((void*) m_nReceiveds, '\0', (size_t) 1028);
	m_nLength = 0;
	m_nReceivedByteCounter = 0;
	m_usProtocolSwitch = 0;
	m_nLastReceived = '\0';

}


STDMETHODIMP CSerialSink::OnReceiveChar(BYTE chrter, BYTE port)  
{
	//if (m_nReceivedByteCounter > 1027)
	//	return S_FALSE;
	
	m_nReceiveds[m_nReceivedByteCounter] = chrter;
	m_nReceivedByteCounter ++;

	m_nReceivedByteCounter = m_nReceivedByteCounter % SIZE_RECEIVE_BUFFER;
	m_nLastReceived = chrter;

	/*
	///AfxMessageBox(L"--------");
	CString csDumy;
	csDumy.Format(_T("%02x ."), chrter);
	EAG_LOG_INFO(csDumy);
	*/

	if (m_pf > 0)
		(*m_pf)();

	return S_OK;
}
STDMETHODIMP CSerialSink::OnBreakDetected(BYTE port)
{
	//EAG_LOG_ALERT(L"CSerialSink::OnBreakDetected - break detected !")
	return S_OK;
}
STDMETHODIMP CSerialSink::OnCTSDetected(BYTE port)
{
	return E_NOTIMPL;
}
STDMETHODIMP CSerialSink::OnERRDetected(BSTR wparam, BYTE port)
{
	return E_NOTIMPL;
}
STDMETHODIMP CSerialSink::OnRINGDetected(BYTE port)
{
	return E_NOTIMPL;
}
STDMETHODIMP CSerialSink::OnRXFLAGDetected(BYTE port)
{
	return E_NOTIMPL;
}
STDMETHODIMP CSerialSink::OnReceiveDeTel(BYTE * dataBuffer, LONG dataLengt, BYTE port)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString csDumy;
	CString csError;
	int index = 0;
	BYTE dataH;
	BYTE dataL;

	// assume no error
	m_bError = FALSE;

	if (m_usProtocolSwitch == PS_MODBUS_ASCII)
	{
		// keep coming values 
		memset((void*) m_nReceiveds, '\0', (size_t) LENGTH_DETEL_RECEIVE);
		memcpy((void*) m_nReceiveds, (void*) dataBuffer, (size_t) dataLengt);
		m_nLength = dataLengt;

	}
	else if (m_usProtocolSwitch == PS_DETEL)
	{
		memset((void* )m_nReceiveds, '\0', (size_t) LENGTH_DETEL_RECEIVE);
		m_nReceiveds[index] = dataBuffer[index];
	
		for (int i = 1; i < dataLengt - 1; i++)
		{
			dataH = dataBuffer[i];
			dataL = dataBuffer[i+1];
			i++;
			index++;
			m_nReceiveds[index] = dataH | dataL;				// update received buffer
		}
		index++;
		m_nReceiveds[index] = dataBuffer[dataLengt-1];
		m_nLength = index+1;					// update length
	}

	m_pf();										// callback
	return S_OK;

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	// format coming values
	m_csMessage = "";
	int nControlLineLength = 12;
	index = 0;
	for (int i = 0; i< dataLengt; i++)
	{
		index++;
		csDumy.Format(_T("%02x - "), dataBuffer[i]);
		m_csMessage += csDumy;
		if(index == nControlLineLength) 
		{
			nControlLineLength = 16; 
		//	m_csMessage += " \n " ;
			index = 0;
		}
	}
	m_csMessage += "\n";

	//EAG_LOG_DEBUG(L"CSerialSink::OnReceiveDeTel\n" + m_csMessage)
	//EAG_LOG_INFO(L"CSerialSink::OnReceiveDeTel : " + m_csMessage)
	
	/*
	MSG msg;
	while(!GetMessage(&msg,0,0,0))	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}		
*/	
	/*
	
	  ///		ER_XON		= 0xA1,		// : invalid XON  at Telegram start in RAM.  
	  ///		ER_XOFF     = 0xA2,		// : invalid XOFF at Telegram end in RAM.
	  ///		ER_NVCD     = 0xA3,		// : no valid command found. 
	  ///		ER_CODE     = 0xA4,		// : code error - module id false.        
	  ///		ER_WFLS     = 0xA5,		// : lash write error.
	  ///		ER_HALT     = 0xA6		// : code error - system is not in halt modus.        
	*/
	/*
	csAssCode	+= ";*  NTF_EBT = 0xD1  Enter to boot section.	                    *\r\n"; 
	csAssCode	+= ";*  NTF_LBT = 0xD2  Leave Bot section.						    *\r\n"; 
	csAssCode	+= ";*  NTF_PME = 0xE0  programming mode entered. 'p'               *\r\n";
	csAssCode	+= ";*  NTF_IVA = 0xE1  interrupts vectors to application sector 'a'*\r\n";
	csAssCode	+= ";*  NTF_IVB = 0xE2  interrupts vectors to boot sector 'b'       *\r\n";
	csAssCode	+= ";*  NTF_STT = 0xE3  timer stopped  'c'                          *\r\n";
	csAssCode	+= ";*  NTF_SRT = 0xE4  timer started 'd'                           *\r\n";
	
	  csAssCode	+= ";*  NTF_HLP = 0xE5  help string is returned 'h'                 *\r\n";
	  csAssCode	+= ";*  NTF_DTW = 0xE6  data telegram is written 'x'                *\r\n";
	*/
	
	BOOL bError			= FALSE ;
	BOOL bNotify		= FALSE ;
	BOOL bNotifyInternal= FALSE ;
	if (m_nReceiveds[0] == XON && m_nReceiveds[2] == XOF )  
	{
		switch (m_nReceiveds[1])
		{
		case ER_XON:
			csError.LoadString(IDS_INVALID_TELEGRAM_START);			
			bError = TRUE ;
			break;
		case ER_XOF:
			csError.LoadString(IDS_INVALID_TELEGRAM_END);			
			bError = TRUE ;
		case ER_NVCD:
			csError.LoadString(IDS_NO_VALID_COMMAND);			
			bError = TRUE ;
		case ER_CODE:
			csError.LoadString(IDS_CODE_ERROR);			
			bError = TRUE ;
		case ER_WFLS:
			csError.LoadString(IDS_FLASH_WRITE_ERROR);			
			bError = TRUE ;
		case ER_HALT:
			csError.LoadString(IDS_SYSTEM_IS_NOT_IN_HALT_MODUS);			
			bError = TRUE ;

		case NTF_EBT:
			csError.LoadString(IDS_NOTFY_ENTERBOOTSECTION);			
			bNotify = TRUE ;
		case NTF_LBT:
			csError.LoadString(IDS_NOTFY_LEAVEBOOTSECTION);			
			bNotify = TRUE ;
		case NTF_PME:
			csError.LoadString(IDS_NOTFY_PROGRAMMING_MODE_ENTERED);			
			bNotify = TRUE ;
		case NTF_IVA:
			csError.LoadString(IDS_NOTFY_INTTERRUPTS_APPLICATION);			
			bNotify = TRUE ;
		case NTF_IVB:
			csError.LoadString(IDS_NOTFY_INTTERRUPTS_BOOT);			
			bNotify = TRUE ;
		case NTF_STT:
			csError.LoadString(IDS_NOTFY_TIMER_STOPPED);			
			bNotify = TRUE ;
		case NTF_SRT:
			csError.LoadString(IDS_NOTFY_TIMER_STARTED);			
			bNotify = TRUE ;
		case NTF_DTW:
			csError.LoadString(IDS_NOTFY_DATA_WRITTEN);			
			bNotify = TRUE ;

		default:
			;
			
		} 
		
		if (bError)
		{
			csDumy.Format(_T("CSerialSink::OnReceiveDeTel -  [0x%04x  <--- ]    %s"), m_nReceiveds[1], csError);
			//EAG_LOG_ERROR(csDumy);
			m_bError = TRUE;
			return S_FALSE ; 
		}

	else if (m_nReceiveds[0] == XON && m_nReceiveds[3] == XOF )
	{
	
		switch (m_nReceiveds[1])
		{
		case NT_INPUTS:
			csError= "host notification message i (input)"; 		
			bNotifyInternal = TRUE ;
		case NT_OUTPUTS:
			csError= "host notification message o (output)"; 		
			bNotifyInternal = TRUE ;
		case NT_SPECIAL:
			csError= "host notification message s (special)"; 		
			bNotifyInternal = TRUE ;
		default:
			;
	
		}
		if (bNotifyInternal)
		{
			csDumy.Format(_T("CSerialSink::OnReceiveDeTel -  [0x%04x  <--- ]    %s"), m_nReceiveds[1], csError);
			///EAG_LOG_NOTIFY(csDumy);
		}
	
	}

	}
	
	else	
	{
		csError = m_csMessage ;
		csDumy.Format(_T("CSerialSink::OnReceiveDeTel.. -  received : %s"), csError);
		//??EAG_LOG_DEBUG(csDumy)
	}
	
	return S_OK;
}
STDMETHODIMP CSerialSink::OnReceiveModBus(BYTE * dataBuffer, LONG dataLengt, BYTE port)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//??EAG_LOG_DEBUG(L"CSerialSink::OnReceiveModBus - ")

	
	// keep coming values 
	//memset((void*) m_nReceiveds, '\0', (size_t) LENGTH_DETEL_RECEIVE);
	
	memset((void*) m_nReceiveds, '\0', 15000);

	memcpy((void*) m_nReceiveds, (void*) dataBuffer, (size_t) dataLengt);
	m_nLength = dataLengt;

	CString csDumy(dataBuffer);// = L"CSerialSink::OnReceiveModBus - modbus telegram : ";
	/*
	m_csMessage = L"CSerialSink::OnReceiveModBus - modbus telegram : ";
	for (int i = 0; i< dataLengt; i++)
	{
		csDumy.Format(_T("%02s - "), dataBuffer[i]);
		m_csMessage += csDumy;
	}

	//??EAG_LOG_DEBUG(m_csMessage)
	m_csMessage.Empty();
*/
		if (m_pf > 0)
			(*m_pf)();	
	
	return S_OK;
}
STDMETHODIMP CSerialSink::NotifyTelegramSend(BYTE port)
{
	return E_NOTIMPL;
}

STDMETHODIMP CSerialSink::get_error(BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		*pVal = m_bError;
	return S_OK;
}
STDMETHODIMP CSerialSink::ClearError()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_bError = FALSE;
	m_csMessage.Empty();
	
	memset((void*) m_nReceiveds, '\0', (size_t) 1028);
	m_nLength = 0;
	m_nReceivedByteCounter = 0;
	m_nLength = 0;
	
	return S_OK;
}
//?? BSTR must be cleared by caller  
STDMETHODIMP CSerialSink::get_Message(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		*pVal = CStringUtility::cStringToBSTR(m_csMessage);
	return S_OK;
}
STDMETHODIMP CSerialSink::get_ReceiveBuffer(unsigned char **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
		*pVal =  (unsigned char*) &m_nReceiveds[0]; // m_nReceivedByteCounter
		//memcpy(pVal, m_nReceiveds, m_nLength); //LENGTH_DETEL_RECEIVE
	    //memcpy(pVal, m_nReceiveds, LENGTH_DETEL_RECEIVE); //LENGTH_DETEL_RECEIVE

	return S_OK;
}

STDMETHODIMP CSerialSink::get_ProtocolSwitch(USHORT* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pVal = m_usProtocolSwitch;
	// TODO: Add your implementation code here

	return S_OK;
}
STDMETHODIMP CSerialSink::put_ProtocolSwitch(USHORT newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here
	m_usProtocolSwitch = newVal;
	return S_OK;
}

STDMETHODIMP CSerialSink::get_lengthReceivedChars( SHORT* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	*pVal = m_nLength;

	return S_OK;
}

fp CSerialSink::m_pf = NULL;
STDMETHODIMP CSerialSink::AddCallBackFunction(LONG(*f) )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//static void(*my_ptr_fun)(void);
	
	//m_pf  = &CSerialSink::test;
	m_pf = (fp) (f);
	//LONG (CSerialSink::*f2) = &CSerialSink::test;

	// call-back function
	//if (m_pf > 0)
	//	(*m_pf)();

	return S_OK;
}
LONG CSerialSink::test() 
{ 
	AfxMessageBox(L"hhh");
	return 1;
}

STDMETHODIMP CSerialSink::get_LastReceived(CHAR* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_nLastReceived;
	return S_OK;
}
