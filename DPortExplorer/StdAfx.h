// stdafx.h : Include-Datei f�r Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die h�ufig benutzt, aber
//      in unregelm��igen Abst�nden ge�ndert werden.
//

#if !defined(AFX_STDAFX_H__23F7B4F8_8CC0_49D0_B0DF_F408D6C77D3D__INCLUDED_)
#define AFX_STDAFX_H__23F7B4F8_8CC0_49D0_B0DF_F408D6C77D3D__INCLUDED_
/**/


#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden

#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
#include <afxcview.h>
#include <afxdisp.h>        // MFC Automatisierungsklassen
#include <afxdtctl.h>		// MFC-Unterst�tzung f�r allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterst�tzung f�r g�ngige Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC-Socket-Erweiterungen

#include "../../dport/implement/Dport_include.h"
#include "../../TelegramFabric/implement/TelegramFabric_include.h"

#ifdef _DEBUG
#import "../../bin/TelegramFabricd.tlb"   raw_interfaces_only, raw_native_types, named_guids //, no_namespace
#else
#import "../../bin/TelegramFabric.tlb"   raw_interfaces_only, raw_native_types, named_guids, no_namespace
#endif
/**/
#include "MCommon_Include.h"
using namespace MCommon;

//#include  "DPort.h"



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_STDAFX_H__23F7B4F8_8CC0_49D0_B0DF_F408D6C77D3D__INCLUDED_)
