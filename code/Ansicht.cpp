// Ansicht.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Win_Traglast.h"
#include "Ansicht.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CAnsicht 


CAnsicht::CAnsicht(CWnd* pParent /*=NULL*/)
	: CDialog(CAnsicht::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnsicht)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CAnsicht::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnsicht)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnsicht, CDialog)
	//{{AFX_MSG_MAP(CAnsicht)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CAnsicht 
