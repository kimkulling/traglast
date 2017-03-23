//----------------------------------------------------------------------------------------------------------------------
///	\file		ElementWork.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2003
///	\brief		Class definition of ElementWork ( Dialog handler ).
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
#include "ElementWork.h"
#include "LocalizationServer.h"
#include "GUITextUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace FEStructure;
using namespace GUI;

extern int iEleNr, iMatNr, iKnNr;

extern Tragwerk			MyTragwerk;
extern KoordStack		KoordEingabe;
extern MaterialStack	MaterialEingabe;
extern ElementStack		ElementEingabe;

//----------------------------------------------------------------------------------------------------------------------
CElementWork::CElementWork( CWnd* pParent ) :
	CDialog( CElementWork::IDD, pParent ),
	iChoosed( -1 ),
	iArt( -1 ),
	iLager( -1 )
{
	//{{AFX_DATA_INIT(CElementWork)
	m_iKn1 = 0;
	m_iKn2 = 0;
	m_iEleAnz = 1;
	m_strC = _T("");
	//}}AFX_DATA_INIT
}

//----------------------------------------------------------------------------------------------------------------------
void CElementWork::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange( pDX );
	//{{AFX_DATA_MAP(CElementWork)
	DDX_Text(pDX, IDC_EDIT2, m_iKn1);
	DDV_MinMaxInt(pDX, m_iKn1, 1, 10000);
	DDX_Text(pDX, IDC_EDIT3, m_iKn2);
	DDV_MinMaxInt(pDX, m_iKn2, 1, 100000);
	DDX_Text(pDX, IDC_EDIT5, m_iEleAnz);
	DDV_MinMaxInt(pDX, m_iEleAnz, 1, 100);
	DDX_Text(pDX, IDC_STATIC1, m_strC);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_ButtonOK);
	DDX_Control(pDX, IDCANCEL, m_ButtonCancel);
}

//----------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CElementWork, CDialog)
	//{{AFX_MSG_MAP(CElementWork)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_LBN_SELCHANGE(IDC_LIST3, OnSelchangeList3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------------------------------
BOOL CElementWork::OnInitDialog() 
{
	if ( !CDialog::OnInitDialog() ) 
		return FALSE;

	std::string id = "DialogOK";
	GUITextUtils::setWindowTextPerId( &m_ButtonOK, id );
	id = "DialogCancel";
	GUITextUtils::setWindowTextPerId( &m_ButtonCancel, id );		

	GUITextUtils::setLocalizedText( this, IDC_NODEGROUP, "EleWorkDlg_NodeGroup" );
	GUITextUtils::setLocalizedText( this, IDC_ELENODE1, "EleWorkDlg_EleNode1" );
	GUITextUtils::setLocalizedText( this, IDC_ELENODE2, "EleWorkDlg_EleNode2" );

	GUITextUtils::setLocalizedText( this, IDC_MESHGROUP, "EleWorkDlg_MeshGroup" );
	GUITextUtils::setLocalizedText( this, IDC_MESHOPTION_DESC, "EleWorkDlg_MeshIntervall" );
	GUITextUtils::setLocalizedText( this, IDC_MATERIALGROUP, "EleWorkDlg_MaterialGroup" );
	GUITextUtils::setLocalizedText( this, IDC_ELEMENTTYPEGROUP, "EleWorkDlg_EleTypeGroup" );

	GUITextUtils::setLocalizedText( this, IDC_RADIO1, "EleWorkDlg_BarEle" );
	GUITextUtils::setLocalizedText( this, IDC_RADIO2, "EleWorkDlg_BeamEle" );
	
	CListBox *pListBox1 = (CListBox*) GetDlgItem( IDC_LIST1 );
	assert( NULL != pListBox1 );
	CListBox *pListBox2 = (CListBox*) GetDlgItem( IDC_LIST3 );
	assert( NULL != pListBox2 );
	CString strListItem( "" );
	for ( Core::i32 idx = 0; idx<MaterialEingabe.iAnz; idx++)
	{
		double dummy[ 4 ];
		std::string rMaterialName( "" );
		if ( MaterialEingabe.readMaterial( idx+1, rMaterialName, dummy[0], dummy[1], dummy[2], dummy[3] ) )
		{
			strListItem.Format("%s", rMaterialName.c_str() );
			pListBox1->AddString (strListItem );
		}
	}
	std::string tmp = Localization::LocalizationServer::get()->getText( "EleWorkDlg_BoundaryOption1" );
	pListBox2->AddString( tmp.c_str() );

	tmp = Localization::LocalizationServer::get()->getText( "EleWorkDlg_BoundaryOption2" );
	pListBox2->AddString( tmp.c_str() );
	
	tmp = Localization::LocalizationServer::get()->getText( "EleWorkDlg_BoundaryOption3" );
	pListBox2->AddString( tmp.c_str() );

	return TRUE;  
}

//----------------------------------------------------------------------------------------------------------------------
void CElementWork::OnSelect() 
{
	// Code folgt später
}

//----------------------------------------------------------------------------------------------------------------------
void CElementWork::OnOK() 
{
	int iN1, iN2, iMat, iEleAnz;
	BOOL bFlag	= TRUE;
	CString strError;

	UpdateData(TRUE);

	iN1		=	m_iKn1;
	iN2		=	m_iKn2;
	iMat	=	iChoosed;
	iEleAnz	=	m_iEleAnz;
	
	// Fehlerbehandlung
	if ((iLager<0)||(iLager>3))
	{
		strError.Format("Art der Lagerung wählen!");
		bFlag = FALSE;
	}

	if (iN1 == iN2)
	{
		strError.Format("2 verschiedene Knoten Wählen");
		bFlag	= FALSE;
	}

	if (m_iEleAnz<=0)
	{
		strError.Format("Anzahl der Elemente muß größer als 1 sein!");
		bFlag = FALSE;
	}

	if (iChoosed==0)
	{
		strError.Format("Material wählen!");
		bFlag = FALSE;
	}
	
	if (iArt==0)
	{
		strError.Format("Art des Elementes wählen!");
		bFlag = FALSE;
	}

	// Erzeugung der Elemente
	if (bFlag)
	{
		if ((iLager==1)&&(iArt==1))	// Fachwerkstab
			iArt = 1;
		if ((iLager==1)&&(iArt==2))	// Balken, starr angeschlossen
			iArt = 2;
		if ((iLager==2)&&(iArt==2))	// Balken, links mit Gelenk
			iArt = GELLEFT;
		if ((iLager==3)&&(iArt==2))	// Balken, rechts mit Gelenk
			iArt = GELRIGHT;

		if (iEleAnz==1)		// Wenn nur ein Element erzeugt werden soll
		{
			iEleNr++;
			ElementEingabe.addElement(iEleNr, m_iKn1, m_iKn2, iMat, iArt);
		}
		else				// Wenn mehr als ein Element zur Vernetzung benutzt wird
			MyTragwerk.meshElement(m_iKn1, m_iKn2, iEleAnz, iMat, iArt );
		
		CDialog::OnOK();
	}
	else
		AfxMessageBox(strError);
}

//----------------------------------------------------------------------------------------------------------------------
void CElementWork::OnSelchangeList1() 
{
	CListBox *pMyListBox = (CListBox*) GetDlgItem(IDC_LIST1);
	if ( NULL != pMyListBox )
	{
		CString strC;
		iChoosed = (pMyListBox->GetCurSel())+1;
		strC.Format("%d", iChoosed);
		SetDlgItemText(IDC_STATIC1, strC);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CElementWork::OnRadio1() 
{
	iArt = 1;
}

//----------------------------------------------------------------------------------------------------------------------
void CElementWork::OnRadio2() 
{
	iArt = 2;
}

//----------------------------------------------------------------------------------------------------------------------
void CElementWork::OnSelchangeList3() 
{
	CString strC;

	CListBox *pMyListBox = (CListBox*) GetDlgItem(IDC_LIST3);
	if ( NULL != pMyListBox )
	{
		iLager = pMyListBox->GetCurSel() + 1;
		strC.Format( "%d", iLager );
		SetDlgItemText(IDC_STATIC1, strC);
	}
}

//----------------------------------------------------------------------------------------------------------------------

