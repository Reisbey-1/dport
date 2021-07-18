// MPortExplorerDoc.h : Schnittstelle der Klasse CMPortExplorerDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPORTEXPLORERDOC_H__A790CE29_C5A8_49F5_A7EA_FE7D8BC2E9BC__INCLUDED_)
#define AFX_MPORTEXPLORERDOC_H__A790CE29_C5A8_49F5_A7EA_FE7D8BC2E9BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMPortExplorerDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CMPortExplorerDoc();
	DECLARE_DYNCREATE(CMPortExplorerDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMPortExplorerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMPortExplorerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMPortExplorerDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MPORTEXPLORERDOC_H__A790CE29_C5A8_49F5_A7EA_FE7D8BC2E9BC__INCLUDED_)
