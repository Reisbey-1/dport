// MPortExplorerView.h : Schnittstelle der Klasse CMPortExplorerView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPORTEXPLORERVIEW_H__D49286ED_7450_4A40_8E3F_9FAAA0A910EA__INCLUDED_)
#define AFX_MPORTEXPLORERVIEW_H__D49286ED_7450_4A40_8E3F_9FAAA0A910EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMPortExplorerView : public CListView
{
protected: // Nur aus Serialisierung erzeugen
	CMPortExplorerView();
	DECLARE_DYNCREATE(CMPortExplorerView)

// Attribute
public:
	CMPortExplorerDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMPortExplorerView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // das erste mal nach der Konstruktion aufgerufen
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CMPortExplorerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CMPortExplorerView)
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in MPortExplorerView.cpp
inline CMPortExplorerDoc* CMPortExplorerView::GetDocument()
   { return (CMPortExplorerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MPORTEXPLORERVIEW_H__D49286ED_7450_4A40_8E3F_9FAAA0A910EA__INCLUDED_)
