//----------------------------------------------------------------------------------------------------------------------
///	\file		TragwerkInfo.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2003
///	\brief		Class definition of TragwerkInfo ( Dialog handler ).
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
#include "TragwerkInfo.h"
#include "LocalizationServer.h"
#include "GUITextUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace FEStructure;
using namespace GUI;

extern int              iKnNr, iMatNr, iEleNr;
extern NodeStack		g_NodeStack;
extern LastStack		LastEingabe;
extern ElementStack		ElementEingabe;
extern MaterialStack	MaterialEingabe;	
extern Tragwerk			MyTragwerk;

//----------------------------------------------------------------------------------------------------------------------
CTragwerkInfo::CTragwerkInfo( CWnd* pParent ) :
	CDialog( CTragwerkInfo::IDD, pParent )
{
	//{{AFX_DATA_INIT(CTragwerkInfo)
	m_strKoordAnz = _T("");
	m_strMatAnz = _T("");
	m_strEleAnz = _T("");
	m_strLastAnz = _T("");
	//}}AFX_DATA_INIT
}

//----------------------------------------------------------------------------------------------------------------------
void CTragwerkInfo::DoDataExchange(CDataExchange* pDX)
{
	int iLastNr;
	int iM, iE;

	CDialog::DoDataExchange(pDX);
	iLastNr = LastEingabe.iLastNr;
	const Core::i32 iK = g_NodeStack.getNumberOfNodes();

	iM = MaterialEingabe.iAnz;
	iE = ElementEingabe.numberOfElements();

	m_strKoordAnz.Format("%d", iK);
	m_strMatAnz.Format("%d",   iM);
	m_strEleAnz.Format("%d",   iE);
	m_strLastAnz.Format("%d",  iLastNr);

	//{{AFX_DATA_MAP(CTragwerkInfo)
	DDX_Text(pDX, IDC_KOORDANZ, m_strKoordAnz);
	DDX_Text(pDX, IDC_MATANZ,   m_strMatAnz);
	DDX_Text(pDX, IDC_ELEANZ,   m_strEleAnz);
	DDX_Text(pDX, IDC_LASTANZ,  m_strLastAnz);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CTragwerkInfo::OnInitDialog()
{
	if ( !CDialog::OnInitDialog() ) 
		return FALSE;

	std::string id = "DialogOK";
	GUITextUtils::setWindowTextPerId( &m_ButtonOK, id );
	id = "DialogCancel";
	GUITextUtils::setWindowTextPerId( &m_ButtonCancel, id );		
	id = "StructureInfoDlg_Title";
	GUITextUtils::setWindowTextPerId( this, id );
	
	GUITextUtils::setLocalizedText( this, IDC_NOCOORDS, "StructureInfoDlg_NoCoords" );
	GUITextUtils::setLocalizedText( this, IDC_NOMATERIALS, "StructureInfoDlg_NoMaterials" );
	GUITextUtils::setLocalizedText( this, IDC_NOELEMENTS, "StructureInfoDlg_NoElements" );
	GUITextUtils::setLocalizedText( this, IDC_NOLOADS, "StructureInfoDlg_NoLoads" );
	
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CTragwerkInfo, CDialog)
	//{{AFX_MSG_MAP(CTragwerkInfo)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------------------------------
