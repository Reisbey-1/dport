#include "stdafx.h"
#include "SmartConnector.h"
CSmartConnector* CSmartConnector::m_pSmartConnector = NULL;

CSmartConnector::CSmartConnector()
{
	m_pISerialPort = NULL;
	m_pIContainer = NULL;
	m_pIConnectionPoint = NULL;
	m_pISink = NULL;
	m_nReceiveds = NULL;
	m_dwCokie = 0;
}

CSmartConnector::~CSmartConnector()
{
}

CSmartConnector* CSmartConnector::Get_SmartConnector(LONG(*f)(), SHORT sProtocolSwitch)
{
	if (m_pSmartConnector == NULL)
	{
		m_pSmartConnector = new CSmartConnector;
		m_pSmartConnector->Init(f, sProtocolSwitch);
	}

	return m_pSmartConnector;
}
void  CSmartConnector::Kill_SmartConnector()
{
	if (m_pSmartConnector)
	{
		m_pSmartConnector->CleanUp();
		delete m_pSmartConnector;
		m_pSmartConnector = NULL;
	}

}

void CSmartConnector::SetProtcolSwitch(protocolSwitch ps)
{
	if (m_pISerialPort) 
	{
		m_pISerialPort->put_ProtocolSwitch(ps);
	}
	if (m_pISink)
	{
		m_pISink->put_ProtocolSwitch(ps);
	}

}

CSmartConnector::protocolSwitch CSmartConnector::GetProtcolSwitch()
{
	CSmartConnector::protocolSwitch  sw;
	if (m_pISerialPort)
	{
		m_pISerialPort->get_ProtocolSwitch((SHORT*)&sw);
		return sw;
	}
	return CSmartConnector::PS_KEINE;
}

void CSmartConnector::GetSink(IUnknown ** ppSink)
{
	*ppSink = m_pISink; 
}

BOOL CSmartConnector::Init(LONG(*f)(), SHORT sProtocoSwitch)
{
	CString csMessage;
	// serial port 2  
	HRESULT hr = CoCreateInstance(
		//DPORTLib::
		CLSID_SerialPort,
		NULL,
		CLSCTX_INPROC_SERVER,
		//DPORTLib::
		IID_ISerialPort,
		(void**)&m_pISerialPort
	);

	if (hr == S_OK)
	{

		// serial sin  S_OK
		hr = CoCreateInstance(
			///DPORTLib::
			CLSID_SerialSink,
			NULL,
			CLSCTX_INPROC_SERVER,
			//DPORTLib::
			IID_ISerialSink,
			(void**)&m_pISink
		);

		if (hr == S_OK)
		{
			// add call back function
			m_pISink->AddCallBackFunction((LONG*)f);						

			// connection to serial port
			hr = m_pISerialPort->QueryInterface(IID_IConnectionPointContainer, (void**)&m_pIContainer);

			// find connection point
			hr = m_pIContainer->FindConnectionPoint(IID__ISerialPortEvents, &m_pIConnectionPoint);

			// cokie
			hr = m_pIConnectionPoint->Advise(m_pISink, &m_dwCokie);
			//m_pISerialPort->put_ProtocolSwitch(PS_DETEL);						// protokol switch modbus sProtocoSwitch
			m_pISerialPort->put_ProtocolSwitch(sProtocoSwitch);					// protokol switch modbus sProtocoSwitch
			m_pISink->put_ProtocolSwitch(sProtocoSwitch);					// protokol switch modbus sProtocoSwitch


			m_pISerialPort->put_WaitForSingleObjectConstant(100L);
			
			//csMessage.Format(L"%d", sProtocoSwitch);
			//AfxMessageBox(csMessage);
		}

		else
		{

			CString csWarning;
			csWarning.Format(L"IDS_WARNING_CAN_NOT_CONNECT_SINK_TO_PORT");
			//EAG_LOG_WARNING(csWarning)
			return FALSE;
		}

	}
	else
	{
		CString csEror;
		csEror.Format(L"IDS_WARNING_CAN_NOT_OPEN_PORT");
		//EAG_LOG_ERROR(csEror)
		return FALSE;
	}

	//pass call back funtion to sink
	//
	//typedef  LONG(*f)();
	//f func = &CModBusMasterDlg::CallBackFunction;
//	CSmartConnector::Get_SmartConnector()->m_pISink->AddCallBackFunction((LONG*)f);


	return TRUE;

}
void CSmartConnector::CleanUp()
{
	//EAG_LOG_DEBUG(L"CSmartConnector::CleanUp - start")
	// close port if it is open
	if (S_OK == m_pISerialPort->CanDo())
		m_pISerialPort->ClosePort();

	long rCount =0;
	/// connection point
	try
	{
		if (m_pIConnectionPoint)
		{

			m_pIConnectionPoint->Unadvise(m_dwCokie);

			//while (rCount )
			rCount = m_pIConnectionPoint->Release();
		}
	}
	catch (...)
	{
	}

	// container
	//rCount = 1;
	try
	{
		if (m_pIContainer)
		{

			//while (rCount)
			rCount = m_pIContainer->Release();

		}
	}
	catch (...)
	{
	}


	// serial port
	//rCount = 1;
	try
	{
		if (m_pISerialPort)
		{
			//while (rCount)
			rCount = m_pISerialPort->Release();

		}
	}
	catch (...)
	{
	}



	// sink
	rCount = 1;
	try
	{
		if (m_pISink)
		{
		//	while (rCount)
			rCount = m_pISink->Release();
		}
	}
	catch (...)
	{
		int nHalt = 0;
	}

}

/*
	CSmartConnector::DPort_Send__Buffer(unsigned char sBuf[], int nSize)
	retuns CModBusPackageAnalisator error code
*/
int CSmartConnector::Send_F_Buffer(unsigned char sBuf[], int nSize)
{
	/**/
//	EAG_LOG_DEBUG(L"CSmartConnector::Send_F_Buffer(char sBuf[]) - start")

	CString csMsg;
	CSmartConnector::Get_SmartConnector()->m_pISerialPort->Purge();					// prepare port to sent
	CSmartConnector::Get_SmartConnector()->m_pISink->ClearError();					// prepare sink to receive


	int nReadValue = -1;
	short sLngth;

	if (S_FALSE == CSmartConnector::Get_SmartConnector()->m_pISerialPort->WriteBuffer((unsigned char*)sBuf, nSize))
	{
		nReadValue = -1;
	}
	else
	{
/*		unsigned char BUFFER[1028];
		Sleep(500);
		unsigned char *buf = BUFFER;
		CSmartConnector::Get_SmartConnector()->m_pISink->get_ReceiveBuffer(buf);
		CSmartConnector::Get_SmartConnector()->m_pISink->get_lengthReceivedChars(&sLngth);

		int ix = 0;
		CString ms;
		CModBusResponseAnalisator analisator(buf, (int)sLngth);
		if (analisator.GetErrorCode()> 0) {
			analisator.print();
			return -1;
		}

		nReadValue = analisator.GetDataAsChar(0);
		if (analisator.GetDataFillLevel() > 1)
		{
			nReadValue = analisator.GetDataAsWord(0);

		}

		*/
	}

	return  nSize;
}
int CSmartConnector::Send_R_Buffer(unsigned char sBuf[], int nSize)
{
	/**/
	EAG_LOG_INFO(L"CSmartSlaveConnector::Send_R_Buffer(char sBuf[]) - start")

		CString csMsg;
	CSmartConnector::Get_SmartConnector()->m_pISerialPort->Purge();					// prepare port to sent
	CSmartConnector::Get_SmartConnector()->m_pISink->ClearError();					// prepare sink to receive

	int nReadValue = -1;
	short sLngth;

	if (S_FALSE == CSmartConnector::Get_SmartConnector()->m_pISerialPort->WriteBuffer((unsigned char*)sBuf, nSize))
	{
		nReadValue = -1;
	}
	else
	{

	}

	return  0;
}
int CSmartConnector::DPort_Sink_Read(unsigned char**sBuf, short& nSize)
{
	if (m_pISink)
	{
		//unsigned char BUFFER[1028];
		//Sleep(500);
		//unsigned char *buf = BUFFER;
		m_pISink->get_ReceiveBuffer(sBuf);
		m_pISink->get_lengthReceivedChars(&nSize);
	//	CSmartConnector::Get_SmartConnector()->m_pISink->ClearError();		
	//	CSmartConnector::Get_SmartConnector()->m_pISerialPort->Purge();					// prepare port to receive
	}
	return 0;
}
void CSmartConnector::DPort_Sink_Clear()
{
	if (m_pISink)
	{
		//unsigned char BUFFER[1028];
		//Sleep(500);
		//unsigned char *buf = BUFFER;
		//m_pISink->get_ReceiveBuffer(sBuf);
		//m_pISink->get_lengthReceivedChars(&nSize);
		m_pISink->ClearError();		
		m_pISerialPort->Purge();					// prepare port to receive
	}
}