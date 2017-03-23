//----------------------------------------------------------------------------------------------------------------------
///	\file		KoordWork.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2001
///	\brief		Class definition of KoordWork ( Dialog handler ).
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
#include "ChildView.h"
#include "KoordWork.h"
#include "LocalizationServer.h"
#include "GUITextUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace FEStructure;
using namespace GUI;

extern int	iKnNr, iRandNr, iLagerKno;

extern		NodeStack	g_NodeStack;
extern		Tragwerk	MyTragwerk;

//----------------------------------------------------------------------------------------------------------------------
//	Constructor.
CKoordWork::CKoordWork( CWnd* pParent ) : 
	CDialog(CKoordWork::IDD, pParent),
	m_dXKoord( 0.0 ),
	m_dYKoord( 0.0 ),
	lX( 0 ),
	lY( 0 ),
	lZ( 0 )
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
//	Destructor.
CKoordWork::~CKoordWork()
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
//	Will be called on init dialog.
BOOL CKoordWork::OnInitDialog()
{
	if ( !CDialog::OnInitDialog() )
		return FALSE;

	Localization::LocalizationServer *pLocalizationServer = Localization::LocalizationServer::get();
	assert( NULL != pLocalizationServer );

	std::string id = "CoordWorkDialogTitle";
	GUITextUtils::setWindowTextPerId( this, id );

	GUITextUtils::setLocalizedText( this, IDC_XCOMP, "CoordWorkDlg_XComp" );
	GUITextUtils::setLocalizedText( this, IDC_YCOMP, "CoordWorkDlg_YComp" );
	GUITextUtils::setLocalizedText( this, IDC_BOUNDARY_GRP, "CoordWorkDlg_BoundaryGrp" );
	GUITextUtils::setLocalizedText( this, IDC_CHECK1, "CoordWorkDlg_BoundaryX" );
	GUITextUtils::setLocalizedText( this, IDC_CHECK2, "CoordWorkDlg_BoundaryY" );
	GUITextUtils::setLocalizedText( this, IDC_CHECK3, "CoordWorkDlg_BoundaryZ" );
	
	id = "DialogOK";
	GUITextUtils::setWindowTextPerId( &m_ButtonOK, id );
	
	id = "DialogCancel";
	GUITextUtils::setWindowTextPerId( &m_ButtonCancel, id );		
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
void CKoordWork::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CKoordWork)
	DDX_Text(pDX, IDC_EDIT1, m_dXKoord);
	DDV_MinMaxDouble(pDX, m_dXKoord, -1000., 1000.);
	DDX_Text(pDX, IDC_EDIT2, m_dYKoord);
	DDV_MinMaxDouble(pDX, m_dYKoord, -1000., 1000.);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
	DDX_Control(pDX, IDC_BUTTON1, m_ButtonNext);
}


//----------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CKoordWork, CDialog)
	//{{AFX_MSG_MAP(CKoordWork)
	ON_BN_CLICKED(IDC_BUTTON1, OnNext)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------------------------------------------------
void CKoordWork::OnOK() 
{	
	UpdateData(TRUE);
	
	Core::i32 iLK = MyTragwerk.iLagerKno;
	iKnNr++;
	if ( lX > 0 )
		iRandNr++;
	if ( lY > 0 )
		iRandNr++;
	if ( lZ > 0 ) 
		iRandNr++;
	if ( ( lX!=0 ) || ( lY!=0 ) || ( lZ!=0 ) )
		iLK++;

	MyTragwerk.LagerKnoSet(iLK);

	g_NodeStack.addNode( iKnNr, m_dXKoord, m_dYKoord, lX, iKnNr, lY, iKnNr, lZ, iKnNr );

	CDialog::OnOK();
}

//----------------------------------------------------------------------------------------------------------------------
void CKoordWork::OnNext() 
{
	// TODO: Implement me!
}


//----------------------------------------------------------------------------------------------------------------------
//	Marks on x hold.
void CKoordWork::OnCheck1()
{
	CButton *pCheck = (CButton*) GetDlgItem(IDC_CHECK1);
	assert( NULL != pCheck );
	if ( NULL != pCheck )
	{
		bool b = pCheck->GetCheck();
		if ( b )
		{
			lX = 1;
		}
		else
		{
			lX = 0;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
//	Marks on y hold.
void CKoordWork::OnCheck2()
{
	BOOL b;
	CButton *pCheck = (CButton*) GetDlgItem(IDC_CHECK2);
	assert( NULL != pCheck );
	if ( NULL != pCheck )
	{
		b = pCheck->GetCheck();
		if (b)
			lY = 1;
		else
			lY = 0;
	}
}


//----------------------------------------------------------------------------------------------------------------------
//	Marks on z hold.
void CKoordWork::OnCheck3() // um Z gehalten
{
	BOOL b;
	CButton *pCheck = (CButton*) GetDlgItem(IDC_CHECK3);
	assert( NULL != pCheck );
	if ( NULL != pCheck )
	{
		b = pCheck ->GetCheck();
		if (b)
			lZ = 1;
		else
			lZ = 0;
	}
}

//----------------------------------------------------------------------------------------------------------------------
