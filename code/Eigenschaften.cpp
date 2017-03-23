//----------------------------------------------------------------------------------------------------------------------
///	\file		Eigenschaften.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2001
///	\brief		Class definition of Eigenschaften ( Dialog handler ).
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
#include "Eigenschaften.h"
#include "LocalizationServer.h"
#include "GUITextUtils.h"
#include "Logger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace Core;
using namespace Localization;
using namespace GUI;

//----------------------------------------------------------------------------------------------------------------------
CEigenschaften::CEigenschaften( CWnd* pParent )
	: CDialog( CEigenschaften::IDD, pParent ),
	m_ProvidedLanguages()
{
	//{{AFX_DATA_INIT(CEigenschaften)
	//}}AFX_DATA_INIT
}

//----------------------------------------------------------------------------------------------------------------------
void CEigenschaften::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEigenschaften)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO1, m_LangSelector);
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CEigenschaften::OnInitDialog()
{	
	if ( !CDialog::OnInitDialog() )
		return FALSE;

	std::vector<std::string> languages;
	LocalizationServer::get()->getSupportedLanguages( languages );
	if ( languages.empty() )
	{
		Logger::get()->warn( "No languages found in enviroment." );
		return FALSE;
	}

	Core::i32 index = 0;
	for ( std::vector<std::string>::iterator it = languages.begin();
		it != languages.end();
		++it )
	{
		CString tmp = (*it).c_str();
		m_LangSelector.AddString( tmp );
		m_ProvidedLanguages[ index ] = *it;
		index++;
	}
	m_LangSelector.SetCurSel( 0 );
	
	std::string id = "PropertiesDialogTitle";
	GUITextUtils::setWindowTextPerId( this, id );

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CEigenschaften, CDialog)
	//{{AFX_MSG_MAP(CEigenschaften)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO1, &CEigenschaften::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------------------------------
void CEigenschaften::OnCbnSelchangeCombo1()
{
	CString language( "" );
	Core::i32 selection = m_LangSelector.GetCurSel();
	Core::ui32 len = m_LangSelector.GetLBTextLen( selection );
	m_LangSelector.GetLBText( selection, language.GetBuffer( len ) );
	std::string stdLangStr( language.GetBuffer() );
	if ( !stdLangStr.empty() )
	{
		LocalizationServer::get()->setLanguage( stdLangStr );
	}
}

//----------------------------------------------------------------------------------------------------------------------
