//----------------------------------------------------------------------------------------------------------------------
///	\file		EinzelEinwirkung.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2003
///	\brief		Class definition of Einzeleinwirkung ( Dialog handler ).
///
/// This program is free software: you can redistribute it and/or modify
///	it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "Win_Traglast.h"
#include "Einzeleinwirkung.h"
#include "LocalizationServer.h"
#include "GUITextUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace FEStructure;
using namespace GUI;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Lokale und globale Variablen und Klassen-Deklarationen
/////////////////////////////////////////////////////////////////////////////////////////////////

extern int iKnNr;
extern LastStack	LastEingabe;
extern NodeStack	g_NodeStack;

//----------------------------------------------------------------------------------------------------------------------
CEinzeleinwirkung::CEinzeleinwirkung(CWnd* pParent /*=NULL*/)
	: CDialog( CEinzeleinwirkung::IDD, pParent ),
	m_iChoose( -1 )
{
	//{{AFX_DATA_INIT(CEinzeleinwirkung)
	m_dEinwirkung = 0.0;
	m_iN = 0;
	//}}AFX_DATA_INIT
}

//----------------------------------------------------------------------------------------------------------------------
void CEinzeleinwirkung::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEinzeleinwirkung)
	DDX_Text(pDX, IDC_EDIT1, m_dEinwirkung);
	DDV_MinMaxDouble(pDX, m_dEinwirkung, -100000., 100000.);
	DDX_Text(pDX, IDC_EDIT2, m_iN);
	DDV_MinMaxInt(pDX, m_iN, 0, 10000);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CEinzeleinwirkung::OnInitDialog()
{
	if ( !CDialog::OnInitDialog() ) 
		return FALSE;

	std::string id = "DialogOK";
	GUITextUtils::setWindowTextPerId( &m_ButtonOK, id );
	id = "DialogCancel";
	GUITextUtils::setWindowTextPerId( &m_ButtonCancel, id );		
	id = "PointLoadDlg_Title";
	GUITextUtils::setWindowTextPerId( this, id );		

	GUITextUtils::setLocalizedText( this, IDC_SELECTDIR_GRP, "PointLoadDlg_SelectDir" );
	GUITextUtils::setLocalizedText( this, IDC_VALUEGRP, "PointLoadDlg_ValueGroup" );
	GUITextUtils::setLocalizedText( this, IDC_NODESELECTGRP, "PointLoadDlg_NodeGroup" );

	GUITextUtils::setLocalizedText( this, IDC_RADIO1, "PointLoadDlg_LoadX" );
	GUITextUtils::setLocalizedText( this, IDC_RADIO2, "PointLoadDlg_LoadY" );
	GUITextUtils::setLocalizedText( this, IDC_RADIO3, "PointLoadDlg_LoadM" );

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CEinzeleinwirkung, CDialog)
	//{{AFX_MSG_MAP(CEinzeleinwirkung)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------------------------------------------------
inline void CEinzeleinwirkung::OnRadio1() 
{
	m_iChoose = 1;
}

//----------------------------------------------------------------------------------------------------------------------
inline void CEinzeleinwirkung::OnRadio2() 
{
	m_iChoose = 2;
}

//----------------------------------------------------------------------------------------------------------------------
inline void CEinzeleinwirkung::OnRadio3() 
{
	m_iChoose = 3;
}

//----------------------------------------------------------------------------------------------------------------------
inline void CEinzeleinwirkung::OnOK() 
{
	CString strError;
	double  dXWert = 0, dYWert = 0, dMWert = 0, dW;
	BOOL    bFlag = TRUE;

	const Core::i32 iKn = g_NodeStack.getNumberOfNodes();
	UpdateData (TRUE);
	dW = m_dEinwirkung;
	
	if ((m_iChoose<1)||(m_iChoose>3))
	{ 
		// Keine Last gewählt
		strError.Format("Richtung der Last wählen!");
		bFlag = FALSE;
	}

	if ((m_iN<0)||(m_iN>iKn)) 
	{
		// Knoten existiert nicht
		strError.Format("Knoten existiert nicht!\n");
		bFlag = FALSE;
	}
	
	// Wenn Eingabe in Ordnung, setzte Last in die Liste
	if (bFlag) 
	{
		switch (m_iChoose)
		{
		case 1:
			dXWert = dW;
			break;

		case 2:
			dYWert = dW;
			break;

		case 3:
			dMWert = dW;
			break;
		}

		LastEingabe.addLast(m_iN, dXWert, dYWert, dMWert, 1);
		CDialog::OnOK();
	}
	else
		AfxMessageBox(strError);
}

//----------------------------------------------------------------------------------------------------------------------
