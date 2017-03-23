/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : 
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_STRECKENEINWIRKUNG_H__A1639A01_2794_11D5_86F9_5254AB1A2D1D__INCLUDED_)
#define AFX_STRECKENEINWIRKUNG_H__A1639A01_2794_11D5_86F9_5254AB1A2D1D__INCLUDED_


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CStreckeneinwirkung 

class CStreckeneinwirkung : public CDialog
{
// Konstruktion
public:
	CStreckeneinwirkung(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CStreckeneinwirkung)
	enum { IDD = IDD_STRECKENEINWIRKUNG };
	double	m_dWert;
	int		m_iKn2;
	int		m_iElement;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CStreckeneinwirkung)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CStreckeneinwirkung)
	virtual void OnOK();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_iCheck;
};

//{{AFX_INSERT_LOCATION}}

#endif // AFX_STRECKENEINWIRKUNG_H__A1639A01_2794_11D5_86F9_5254AB1A2D1D__INCLUDED_
