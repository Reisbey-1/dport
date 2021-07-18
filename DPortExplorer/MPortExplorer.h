// MPortExplorer.h : Haupt-Header-Datei für die Anwendung MPORTEXPLORER
//

#if !defined(AFX_MPORTEXPLORER_H__5F740265_8FE4_4B23_BBCB_4B0BFAD7D9B2__INCLUDED_)
#define AFX_MPORTEXPLORER_H__5F740265_8FE4_4B23_BBCB_4B0BFAD7D9B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerApp:
// Siehe MPortExplorer.cpp für die Implementierung dieser Klasse
//

class CMPortExplorerApp : public CWinApp
{
public:
	CMPortExplorerApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMPortExplorerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CMPortExplorerApp)
	afx_msg void OnAppAbout();
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MPORTEXPLORER_H__5F740265_8FE4_4B23_BBCB_4B0BFAD7D9B2__INCLUDED_)
