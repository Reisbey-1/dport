// LeftView.cpp : Implementierung der Klasse CLeftView
//

#include "stdafx.h"
#include "MPortExplorer.h"

#include "MPortExplorerDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
		// HINWEIS - hier werden Umsetzungsmakros vom Klassen-Assistenten hinzugef�gt und entfernt.
		//    BEARBEITEN SIE NICHT, was Sie in diesen generierten Code-Bl�cken sehen!
	//}}AFX_MSG_MAP
	// Standard-Befehle zum Drucken
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView Erstellung/Zerst�rung

CLeftView::CLeftView()
{
	// ZU ERLEDIGEN: F�gen Sie hier den Erstellungs-Code hinzu

}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: �ndern Sie hier die Fensterklassse oder -formate, indem
	//  CREATESTRUCT cs �ndern

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView Darstellung

void CLeftView::OnDraw(CDC* pDC)
{
	CMPortExplorerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// ZU ERLEDIGEN: F�gen Sie hier den Zeichen-Code f�r systemeigene Daten hinzu
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView Drucken

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zus�tzliche Initialisierung vor dem Drucken hinzuf�gen
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Bereinigung hinter dem Drucken hinzuf�gen
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// ZU ERLEDIGEN: Sie k�nnen Ihre Baumansicht mit Elementen f�llen, indem Sie direkt
	//  auf dessen Baum-Steuerelement �ber einen Aufruf von GetTreeCtrl() zugreifen.
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView Diagnose

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMPortExplorerDoc* CLeftView::GetDocument() // Nicht-Debug-Version ist inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMPortExplorerDoc)));
	return (CMPortExplorerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView Nachrichten-Behandlungsroutinen
