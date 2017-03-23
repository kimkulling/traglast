//----------------------------------------------------------------------------------------------------------------------
///	\file		MaterialWork.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2003
///	\brief		Class definition of MaterialWork ( Dialog handler ).
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
#include "MaterialWork.h"
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
// Globale Variablen- und Klassendefinitionen
/////////////////////////////////////////////////////////////////////////////////////////////////

extern int iMatNr;

extern MaterialStack MaterialEingabe;

//----------------------------------------------------------------------------------------------------------------------
CMaterialWork::CMaterialWork(CWnd* pParent /*=NULL*/)
	: CDialog(CMaterialWork::IDD, pParent),
	m_dEmodul( 0.0 ),
	m_dFlaeche( 0.0 ),
	m_dIy( 0.0 ),
	m_dMpl( 0.0 ),
	m_strMatName( "" )
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
void CMaterialWork::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialWork)
	DDX_Text(pDX, IDC_EDIT1, m_dEmodul);
	DDV_MinMaxDouble(pDX, m_dEmodul, 0., 1000000.);
	DDX_Text(pDX, IDC_EDIT2, m_dFlaeche);
	DDV_MinMaxDouble(pDX, m_dFlaeche, 0., 1000000.);
	DDX_Text(pDX, IDC_EDIT3, m_dIy);
	DDV_MinMaxDouble(pDX, m_dIy, 0., 1000000.);
	DDX_Text(pDX, IDC_PLMOMENT, m_dMpl);
	DDV_MinMaxDouble(pDX, m_dMpl, 0., 1000000.);
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_MATNAME, m_strMatName );
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CMaterialWork::OnInitDialog()
{
	if ( !CDialog::OnInitDialog() ) 
		return FALSE;

	std::string id = "MaterialDlg_Title";
	GUITextUtils::setWindowTextPerId( this, id );		
	id = "DialogOK";
	GUITextUtils::setWindowTextPerId( &m_ButtonOK, id );
	id = "DialogCancel";
	GUITextUtils::setWindowTextPerId( &m_ButtonCancel, id );		

	GUITextUtils::setLocalizedText( this, IDC_ELASTICGRP, "MaterialDlg_ElasticGroup" );

	GUITextUtils::setLocalizedText( this, IDC_MATERTIALNAME, "MaterialDlg_MaterialName" );
	GUITextUtils::setLocalizedText( this, IDC_MATERIALEMOD, "MaterialDlg_E_Module" );
	GUITextUtils::setLocalizedText( this, IDC_MATERIALAREA, "MaterialDlg_Area" );
	GUITextUtils::setLocalizedText( this, IDC_STATICMOMENTY, "MaterialDlg_Iy" );

	GUITextUtils::setLocalizedText( this, IDC_PLASTICGRP, "MaterialDlg_PlasticGroup" );
	GUITextUtils::setLocalizedText( this, IDC_MPLASTIC, "MaterialDlg_PlasticMoment" );
		
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CMaterialWork, CDialog)
	//{{AFX_MSG_MAP(CMaterialWork)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------------------------------
void CMaterialWork::OnOK() 
{
	UpdateData( TRUE );
	
	const Core::d32 dEM = m_dEmodul; 
	const Core::d32 dA = m_dFlaeche; 
	const Core::d32 dIy = m_dIy;
	const Core::d32 Mpl = m_dMpl;
	
	bool error = true;
	CString	strError;
	if ( 0.0 == dEM ) 
	{
		strError.Format("Wert für E-Modul eingeben!");
		error = false;
	}
	if ( 0.0 == dA ) 
	{
		strError.Format("Wert für Querschnittsfläche eingeben!");
		error = false;
	}
	if ( 0.0 == dIy ) 
	{
		strError.Format( "Wert für das Trägheitsmoment 2.er Ordnung eingeben!" );
		error = false;
	}
	if ( 0.0 == Mpl ) 
	{
		strError.Format( "Wert für das plastische Moment eingeben!" );
		error = false;
	}
	
	if ( error ) 
	{
		iMatNr++;
		std::string name = this->m_strMatName;
		MaterialEingabe.addMaterial( name, iMatNr, m_dEmodul, m_dFlaeche, m_dIy, m_dMpl );
		CDialog::OnOK();
	}
	else
	{
		AfxMessageBox( strError );
	}
}

//----------------------------------------------------------------------------------------------------------------------
