// Sink.cpp: Schnittstelle für die Klasse ISerialPortEvents.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sink.h"

long CSink::m_nCount = 0;

CSink::CSink()
{
	m_nCount++;
};
CSink::~CSink()
{
	
};

HRESULT __stdcall CSink::OnReceiveChar (
unsigned char chrter,
unsigned char port )
{ 
	CString cs;
	cs.Format("character : %c, port %i", chrter, port);
	AfxMessageBox(cs);
	return S_OK;

}


HRESULT __stdcall CSink::OnBreakDetected (
unsigned char port ) { return S_OK;}

HRESULT __stdcall CSink::OnCTSDetected (
unsigned char port ) { return S_OK;}

HRESULT __stdcall CSink::OnERRDetected (
BSTR wparam,
unsigned char port ) { return S_OK;}

HRESULT __stdcall CSink::OnRINGDetected (
unsigned char port ) { return S_OK;}

HRESULT __stdcall CSink::OnRXFLAGDetected (
unsigned char port ) { return S_OK;}

HRESULT __stdcall CSink::NotifyTelegramSend (
unsigned char port ) { return S_OK;}

HRESULT __stdcall CSink::OnReceiveDeTel (
    unsigned char * dataBuffer,
    long dataLengt,
    unsigned char port )
{ 
	
	CString csMessage;
	CString cs;
	
	for (int i = 0; i< dataLengt; i++)
	{
		
		//cs.Format("character : %c, port %i", dataBuffer[i], port);
		cs.Format(" %c ", dataBuffer[i]);
		csMessage += cs;
	}
	
		AfxMessageBox(csMessage);

	
	return S_OK;
	
}