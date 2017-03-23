//----------------------------------------------------------------------------------------------------------------------
///	\file		CalcOption.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2001
///	\brief		Class definition of CalcOption ( Dialog handler ).
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
#include "CalcOption.h"
#include "LocalizationServer.h"
#include "GUITextUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int iOption;

using namespace FEStructure;
using namespace GUI;

extern Tragwerk MyTragwerk;

//----------------------------------------------------------------------------------------------------------------------
CCalcOption::CCalcOption(CWnd* pParent /*=NULL*/) :
	CDialog(CCalcOption::IDD, pParent),
	m_dMoment( 0.0 )
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
CCalcOption::~CCalcOption()
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
void CCalcOption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalcOption)
	//}}AFX_DATA_MAP
	DDX_Control( pDX, IDC_CHECK1, m_UseLog );
	DDX_Control( pDX, IDOK, m_ButtonOK );
	DDX_Control( pDX, IDCANCEL, m_ButtonCancel );
}

//----------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CCalcOption, CDialog)
	//{{AFX_MSG_MAP(CCalcOption)
	ON_BN_CLICKED( IDC_RADIO1, OnRadio1 )
	ON_BN_CLICKED( IDC_RADIO2, OnRadio2 )
	ON_BN_CLICKED( IDC_CHECK1, OnCheck1 )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------------------------------
BOOL CCalcOption::OnInitDialog()
{
	if ( !CDialog::OnInitDialog() )
		return FALSE;

	Localization::LocalizationServer *pLocalizationServer = Localization::LocalizationServer::get();
	assert( NULL != pLocalizationServer );

	std::string id = "CalcOptionDialogTitle";
	GUITextUtils::setWindowTextPerId( this, id );

	GUITextUtils::setLocalizedText( this, IDC_DLG_CALCOPTION_OPTIONS, "CalcOptionDialogGrpOptions" );
	GUITextUtils::setLocalizedText( this, IDC_DLG_CALCOPTION_LOG, "CalcOptionDialogGrpLog" );
	GUITextUtils::setLocalizedText( this, IDC_RADIO1, "CalcOptionDialogRBThFirstOrder" );
	GUITextUtils::setLocalizedText( this, IDC_RADIO2, "CalcOptionDialogRBMAxLoad" );
		
	id = "DialogOK";
	GUITextUtils::setWindowTextPerId( &m_ButtonOK, id );
	
	id = "DialogCancel";
	GUITextUtils::setWindowTextPerId( &m_ButtonCancel, id );

	id = "CalcOptionDlgItemLog";
	GUITextUtils::setWindowTextPerId( &m_UseLog, id );

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
void CCalcOption::OnRadio1() 
{
	iOption = 1;
}

//----------------------------------------------------------------------------------------------------------------------
void CCalcOption::OnRadio2() 
{
	iOption = 2;
}

//----------------------------------------------------------------------------------------------------------------------
void CCalcOption::OnOK() 
{
	CDialog::OnOK();
	MyTragwerk.iCalcOption = iOption;
	
	if (2 == iOption)
	{
		std::string errorText = Localization::LocalizationServer::get()->getText( "CalcOptionDialogErrorSection" );
		AfxMessageBox( CString( errorText.c_str() ) );
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CCalcOption::OnCheck1()
{
	MyTragwerk.bLogfile;
}

//----------------------------------------------------------------------------------------------------------------------

