// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "DPort_i.h"
#include "dllmain.h"

CDPortModule _AtlModule;

class CDPortApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CDPortApp, CWinApp)
END_MESSAGE_MAP()

//CDPortApp theApp;

BOOL CDPortApp::InitInstance()
{
//	CoInitialize(NULL);
	return CWinApp::InitInstance();
}

int CDPortApp::ExitInstance()
{
	 if(false) 
    {
        AFX_MANAGE_STATE(NULL);
    }
	return CWinApp::ExitInstance();
}
