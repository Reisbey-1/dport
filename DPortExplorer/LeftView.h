// LeftView.h : Schnittstelle der Klasse CLeftView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__1717EEDC_2BC2_4403_9755_93276DE5143F__INCLUDED_)
#define AFX_LEFTVIEW_H__1717EEDC_2BC2_4403_9755_93276DE5143F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMPortExplorerDoc;

class CLeftView : public CTreeView
{
protected: // Nur aus Serialisierung erstellen
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attribute
public:
	CMPortExplorerDoc* GetDocument();

// Operationen
public:

// �berladungen
	// �berladungen der vom Klassen-Assistenten erstellten virtuellen Funktion
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // �berladen, um diese Ansicht darzustellen
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // Erster Aufruf nach Erstellung
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Erstellte Funktionen f�r die Nachrichtenumsetzung
protected:
	//{{AFX_MSG(CLeftView)
		// HINWEIS - Hier werden Member-Funktionen vom Klassen-Assistenten hinzugef�gt und entfernt.
		//    BEARBEITEN SIE NICHT, was Sie in diesen generierten Code-Bl�cken sehen!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Debug-Version in LeftView.cpp
inline CMPortExplorerDoc* CLeftView::GetDocument()
   { return (CMPortExplorerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_LEFTVIEW_H__1717EEDC_2BC2_4403_9755_93276DE5143F__INCLUDED_)
