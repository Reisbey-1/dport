// MPortExplorerView.cpp : Implementierung der Klasse CMPortExplorerView
//

#include "stdafx.h"
#include "MPortExplorer.h"

#include "MPortExplorerDoc.h"
#include "MPortExplorerView.h"
#include "Dlg_RS232.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerView

IMPLEMENT_DYNCREATE(CMPortExplorerView, CListView)

BEGIN_MESSAGE_MAP(CMPortExplorerView, CListView)
	//{{AFX_MSG_MAP(CMPortExplorerView)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerView Konstruktion/Destruktion

CMPortExplorerView::CMPortExplorerView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,

}

CMPortExplorerView::~CMPortExplorerView()
{
}

BOOL CMPortExplorerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerView Zeichnen

void CMPortExplorerView::OnDraw(CDC* pDC)
{
	CMPortExplorerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der ursprünglichen Daten hinzufügen
}

void CMPortExplorerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// ZU ERLEDIGEN: Sie können Elemente in Ihre ListView eintragen, indem Sie direkt 
	//  über einen Aufruf von GetListCtrl() auf ihre Listensteuerung zugreifen.
}

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerView Drucken

BOOL CMPortExplorerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CMPortExplorerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CMPortExplorerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerView Diagnose

#ifdef _DEBUG
void CMPortExplorerView::AssertValid() const
{
	CListView::AssertValid();
}

void CMPortExplorerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CMPortExplorerDoc* CMPortExplorerView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMPortExplorerDoc)));
	return (CMPortExplorerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerView Nachrichten-Handler
void CMPortExplorerView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//ZU ERLEDIGEN: Code hinzufügen, der auf die Änderung des Benutzers des Ansichtsformats Ihres Fensters reagiert
}

