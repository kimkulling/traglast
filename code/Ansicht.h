#if !defined(AFX_ANSICHT_H__AECB0664_461B_11D5_86F9_5254AB1A2D1D__INCLUDED_)
#define AFX_ANSICHT_H__AECB0664_461B_11D5_86F9_5254AB1A2D1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ansicht.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CAnsicht 

class CAnsicht : public CDialog
{
// Konstruktion
public:
	CAnsicht(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CAnsicht)
	enum { IDD = IDD_ANSICHT };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAnsicht)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CAnsicht)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_ANSICHT_H__AECB0664_461B_11D5_86F9_5254AB1A2D1D__INCLUDED_
