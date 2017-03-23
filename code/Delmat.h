/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : Delmat.h
// Desc.       : 
// Autor       : Kim Kulling
// Last mod.   : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DELMAT__H
#define __DELMAT__H
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// Klasse		: CDelMat	
// Beschreibung	: Initialisierung des Dialogs zur Materiallöschung
/////////////////////////////////////////////////////////////////////////////////////////////////

class CDelmat : public CDialog
{
public:
	CDelmat(CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CDelmat)
	enum { IDD = IDD_DELETEMAT };
	//}}AFX_DATA


// Überschreibungen
	//{{AFX_VIRTUAL(CDelmat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDelmat)
	virtual void OnOK();
	afx_msg void OnSelchangeList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CButton m_ButtonDelete;
	CButton m_ButtonCancel;
};

//{{AFX_INSERT_LOCATION}}

#endif // AFX_DELMAT_H__53382901_4638_11D5_86F9_5254AB1A2D1D__INCLUDED_
