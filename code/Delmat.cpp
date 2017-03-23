/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : 
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Win_Traglast.h"
#include "Delmat.h"
#include "LocalizationServer.h"
#include "GUITextUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace FEStructure;
using namespace GUI;

extern MaterialStack	MaterialEingabe;

int iC = 0;

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDelmat 


CDelmat::CDelmat(CWnd* pParent /*=NULL*/)
	: CDialog(CDelmat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDelmat)
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
void CDelmat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDelmat)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_ButtonDelete);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: CDelmat::OnInitDialog()
// Beschreibung	: Initialisiert den Dialog
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CDelmat::OnInitDialog()
{
	if ( !CDialog::OnInitDialog() ) 
		return FALSE;

	CListBox *pListBox1 = (CListBox*) GetDlgItem(IDC_LIST1);
	assert( NULL != pListBox1 );
	if ( NULL == pListBox1 )
		return FALSE;
	
	std::string id = "DialogDelete";
	GUITextUtils::setWindowTextPerId( &m_ButtonDelete, id );
	id = "DialogCancel";
	GUITextUtils::setWindowTextPerId( &m_ButtonCancel, id );		

	id = "EleDelMatDlg_Title";
	GUITextUtils::setWindowTextPerId( this, id );		

	GUITextUtils::setLocalizedText( this, IDC_SELECLMATERIALGRP, "EleDelMatDlg_SelectMat" );

	int iMat = MaterialEingabe.iAnz+1;
	for ( int i=1; i<iMat; i++) 
	{
		std::string materialName( "" );
		double dEM( 0.0 ), dA( 0.0 ), dIy( 0.0 ), dMpl( 0.0 );
		if ( MaterialEingabe.readMaterial( i, materialName, dEM, dA, dIy, dMpl ) )
		{		
			pListBox1->AddString( materialName.c_str() );
		}
	}
	
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDelmat, CDialog)
	//{{AFX_MSG_MAP(CDelmat)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDelmat 

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		:
// Bescreibung	:
/////////////////////////////////////////////////////////////////////////////////////////////////
inline void CDelmat::OnOK() 
{	
	CDialog::OnOK();

	if (iC!=0) {
		MaterialEingabe.DelMaterial(iC, MaterialEingabe.iAnz);
		CDialog::OnOK();
	}
	else
		CDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: void CDelmat::OnSelchangeList1() 
// Beschreibung	: Ermittelt die Nummer desgewählten Querschnitts
/////////////////////////////////////////////////////////////////////////////////////////////////
inline void CDelmat::OnSelchangeList1(void) 
{
	CListBox	*pListBox1 = (CListBox*) GetDlgItem(IDC_LIST1);
	iC = (pListBox1->GetCurSel()) + 1;	
}
