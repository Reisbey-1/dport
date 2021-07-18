// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#define WINVER 0x0700
#define _WIN32_WINNT _WIN32_WINNT_MAXVER

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#include <afxwin.h>
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>

using namespace ATL;


#ifdef DPORT_EXPORTS
#define DPORT_API __declspec(dllexport)
#else
#define DPORT_API __declspec(dllimport)
#endif
/*
#include "EagCommon_Include.h"
using namespace eag ;


#include "MdCommon_Include.h"
using namespace MdCommon ;
*/
#include  "LexAnlysr_Include.h"
using namespace LexAnlysr ;

/*
#include "messangerInclude.h"
using namespace messanger ;
*/
#ifdef _DEBUG
#import "../../bin/TelegramFabricd.tlb"   raw_interfaces_only, raw_native_types, named_guids, no_namespace
#else
#import "../../bin/TelegramFabric.tlb"   raw_interfaces_only, raw_native_types, named_guids, no_namespace
#endif

//using namespace TelegramFabricLib;
extern "C" const GUID ;