#if !defined(AFX_PLASTCALCCTRL_H__3EDA1701_38D4_11D5_86F9_5254AB1A2D1D__INCLUDED_)
#define AFX_PLASTCALCCTRL_H__3EDA1701_38D4_11D5_86F9_5254AB1A2D1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlastCalcCtrl.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPlastCalcCtrl 

class CPlastCalcCtrl : public CDialog
{
// Konstruktion
public:
	CPlastCalcCtrl(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CPlastCalcCtrl)
	enum { IDD = IDD_PLASTCALCCTRL };
	CString	m_strPlastName;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CPlastCalcCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CPlastCalcCtrl)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_PLASTCALCCTRL_H__3EDA1701_38D4_11D5_86F9_5254AB1A2D1D__INCLUDED_
