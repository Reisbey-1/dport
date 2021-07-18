// MPortExplorerDoc.cpp : Implementierung der Klasse CMPortExplorerDoc
//

#include "stdafx.h"
#include "MPortExplorer.h"

#include "MPortExplorerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerDoc

IMPLEMENT_DYNCREATE(CMPortExplorerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMPortExplorerDoc, CDocument)
	//{{AFX_MSG_MAP(CMPortExplorerDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerDoc Konstruktion/Destruktion

CMPortExplorerDoc::CMPortExplorerDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CMPortExplorerDoc::~CMPortExplorerDoc()
{
}

BOOL CMPortExplorerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerDoc Serialisierung

void CMPortExplorerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Hier Code zum Laden einfügen
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerDoc Diagnose

#ifdef _DEBUG
void CMPortExplorerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMPortExplorerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerDoc Befehle
