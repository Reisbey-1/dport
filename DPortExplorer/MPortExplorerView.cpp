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
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einf�gen,

}

CMPortExplorerView::~CMPortExplorerView()
{
}

BOOL CMPortExplorerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: �ndern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
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
	// ZU ERLEDIGEN: Hier Code zum Zeichnen der urspr�nglichen Daten hinzuf�gen
}

void CMPortExplorerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// ZU ERLEDIGEN: Sie k�nnen Elemente in Ihre ListView eintragen, indem Sie direkt 
	//  �ber einen Aufruf von GetListCtrl() auf ihre Listensteuerung zugreifen.
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
	// ZU ERLEDIGEN: Zus�tzliche Initialisierung vor dem Drucken hier einf�gen
}

void CMPortExplorerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einf�gen
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

CMPortExplorerDoc* CMPortExplorerView::GetDocument() // Die endg�ltige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMPortExplorerDoc)));
	return (CMPortExplorerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMPortExplorerView Nachrichten-Handler
void CMPortExplorerView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//ZU ERLEDIGEN: Code hinzuf�gen, der auf die �nderung des Benutzers des Ansichtsformats Ihres Fensters reagiert
}

