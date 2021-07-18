// DPort_include.h
//
#if !defined(DPORTS_H_1234kjüso_INCLUDED_)
#define DPORTS_H_1234kjüso_INCLUDED_

// The following will ensure that we are exporting our C++ classes when 
// building the DLL and importing the classes when build an application 
// using this DLL.
#ifdef DPORT_EXPORTS
#define DPORT_API __declspec(dllexport)
#else
#define DPORT_API __declspec(dllimport)
#endif

///////////////////////////////////////////////////////
#include "SmartConnector.h"

////////////////////////////////////////////////////////

// The following will ensure that when building an application (or another DLL)
// using this DLL, the appropriate .LIB file will automatically be used
// when linking.
#ifndef _MYLIB_NOAUTOLIB_
#ifdef _DEBUG
#pragma comment(lib, "DPortd.lib")
#else
#pragma comment(lib, "DPort.lib")
#endif
#endif

#endif // DPORTS_H_1234kjüso_INCLUDED_
