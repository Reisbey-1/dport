#pragma once
#include "DPort_i.h"
/*
	
	CSmartConnector :
	=================
	1) Singleton class
	2) creates SerialPort object	(m_pISerialPort)
	3) creates SerialSink object	(m_pISink)
	4) register	application defined
	   callback function on the
	   sink objeck  {LONG(*f)()}
	
	calling convention:
	===================
	LONG (*f)() ;
	CSmartConnector::Get_SmartConnector(f) ;  // creates objects and register callback function 
	CSmartConnector::Kill_SmartConnector() ;  // clean up objects

*/

class DPORT_API CSmartConnector
{
public:
	enum protocolSwitch { PS_KEINE = 0, PS_DETEL, PS_MODBUS_ASCII, PS_MODBUS_RTU } ;

	//DPORTLib
	
	ISerialPort*	m_pISerialPort;

	static CSmartConnector* Get_SmartConnector(LONG(*f)()=0, SHORT sProtocoSwitch = PS_DETEL);
	static void  Kill_SmartConnector();
	
	int Send_F_Buffer(unsigned char sBuf[], int nSize);
	int Send_R_Buffer(unsigned char sBuf[], int nSize);

	int DPort_Sink_Read(unsigned char **sBuf, short& nSize);
	void DPort_Sink_Clear();
	void SetProtcolSwitch(protocolSwitch ps);// { if (m_pISerialPort) {}}
	protocolSwitch GetProtcolSwitch();

	void GetSink(IUnknown ** ppSink);
	 

protected:	
	
	ISerialSink*	m_pISink;
	BOOL Init(LONG(*f)(), SHORT sProtocoSwitch = PS_DETEL);
	CSmartConnector();
	~CSmartConnector();
	static CSmartConnector* m_pSmartConnector;
	void CleanUp();
	unsigned char *m_nReceiveds;
	DWORD m_dwCokie;
	IConnectionPointContainer* m_pIContainer;
	IConnectionPoint* m_pIConnectionPoint;	
};

