// Dlg_RS232.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "MPortExplorer.h"
#include "Dlg_RS232.h"
#include "Sink.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_RS232 


CDlg_RS232::CDlg_RS232(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_RS232::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_RS232)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	m_pSink = NULL;
}

CDlg_RS232::~CDlg_RS232()
{
	delete m_pSink;
}


void CDlg_RS232::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_RS232)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_RS232, CDialog)
	//{{AFX_MSG_MAP(CDlg_RS232)
	ON_BN_CLICKED(IDC_BUTTON_DO, OnButtonDo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlg_RS232 

void CDlg_RS232::OnButtonDo() 
{
	
	ISerialPort * pSerPort; 
	
	CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(
		CLSID_SerialPort,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ISerialPort,
		(void**) &pSerPort
		) ;


	//delete m_pSink;
	if (m_pSink)
		m_pSink->Release();
	
//	m_pSink = new CSink;

	IConnectionPointContainer* pContainer;
	hr = pSerPort->QueryInterface(IID_IConnectionPointContainer, (void**) &pContainer);

	// find connection poin
	IConnectionPoint* pConnectionPoint;

	hr = pContainer->FindConnectionPoint(__uuidof(_ISerialPortEvents), &pConnectionPoint);
	
	DWORD cokie;


	hr = pConnectionPoint->Advise(m_pSink, &cokie);

	if (S_OK == hr)
	{
		BSTR bstr;

		CString csInitStrin = "<baud=9600> <parity=N> <databits=8><stopbits=1>";
		bstr = csInitStrin.AllocSysString();
		pSerPort->OpenPort(&bstr, 1);
	}
}
