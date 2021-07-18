#if !defined(AFX_DLG_RS232_H__C20D2F33_79BA_462F_A1A5_025454715F35__INCLUDED_)
#define AFX_DLG_RS232_H__C20D2F33_79BA_462F_A1A5_025454715F35__INCLUDED_

#include "Sink.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_RS232.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_RS232 

class CDlg_RS232 : public CDialog
{
// Konstruktion
public:
	CDlg_RS232(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlg_RS232();

// Dialogfelddaten
	//{{AFX_DATA(CDlg_RS232)
	enum { IDD = IDD_DIALOG_RS232 };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlg_RS232)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung

	CSink* m_pSink ;

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlg_RS232)
	afx_msg void OnButtonDo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_RS232_H__C20D2F33_79BA_462F_A1A5_025454715F35__INCLUDED_
