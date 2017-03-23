/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : 
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Win_Traglast.h"
#include "Streckeneinwirkung.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace FEStructure;

extern NodeStack	g_NodeStack;
extern ElementStack	ElementEingabe;
extern LastStack	LastEingabe;

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CStreckeneinwirkung 


CStreckeneinwirkung::CStreckeneinwirkung(CWnd* pParent /*=NULL*/)
	: CDialog(CStreckeneinwirkung::IDD, pParent),
	m_iCheck(0)
{
	//{{AFX_DATA_INIT(CStreckeneinwirkung)
	m_dWert = 0.0;
	m_iKn2 = 0;
	m_iElement = 0;
	//}}AFX_DATA_INIT
}


void CStreckeneinwirkung::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStreckeneinwirkung)
	DDX_Text(pDX, IDC_EDIT1, m_dWert);
	DDX_Text(pDX, IDC_EDIT2, m_iElement);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStreckeneinwirkung, CDialog)
	//{{AFX_MSG_MAP(CStreckeneinwirkung)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CStreckeneinwirkung 

//-------------------------------------------------------------------------------------------------------------------
// Methode		:
// Beschreibung	:
//-------------------------------------------------------------------------------------------------------------------

void CStreckeneinwirkung::OnOK() 
{
	BOOL bFlag = TRUE;
	double dL, dQ;

	UpdateData( TRUE );
	CString	strError;
	if ((m_dWert==0)||(m_iElement==0)||(m_iElement<(Core::i32)ElementEingabe.numberOfElements())||
		(m_iElement>(Core::i32)ElementEingabe.numberOfElements()))
	{
		strError.Format("Fehler bei der Eingabe!");
		bFlag = FALSE;
	}

	if (bFlag)
	{
		const Core::i32 iKn1 = ElementEingabe.ReadElement(m_iElement, 1, m_iElement);
		const Core::i32 iKn2 = ElementEingabe.ReadElement(m_iElement, 2, m_iElement);
		
		NodeStack::NodeDef node1, node2;
		g_NodeStack.getNode( iKn1, node1 );
		g_NodeStack.getNode( iKn2, node2 );
		Core::d32 xPos1( 0.0 ), xPos2( 0.0 ), yPos1( 0.0 ), yPos2( 0.0 );
		node1.getPosition( xPos1, yPos1 );
		node2.getPosition( xPos2, yPos2 );
		const Core::d32 dX21 = xPos2 - xPos1;
		const Core::d32 dY21 = yPos2 - yPos1;
		dL   = dL2D( dX21, dY21 );
		if (m_iCheck==1)
		{
			dQ = (m_dWert * dL / 2);
			LastEingabe.addLast(iKn1, dQ, 0, 0, 2);
			LastEingabe.addLast(iKn2, dQ, 0, 0, 2);
		}

		if (m_iCheck==2)
		{
			dQ = (m_dWert * dL / 2);
			LastEingabe.addLast(iKn1, 0, dQ, 0, 2);
			LastEingabe.addLast(iKn2, 0, dQ, 0, 2);
		}

		if (m_iCheck==3)
		{
			dQ = (m_dWert * (dL * dL) / 12);
			LastEingabe.addLast(iKn1, 0, 0, dQ, 2);
			LastEingabe.addLast(iKn2, 0 ,0, (-1 * dQ), 2);
		}

		CDialog::OnOK();
	}
	else
		AfxMessageBox(strError);
}

//-------------------------------------------------------------------------------------------------------------------
// Methode		: CStreckeneinwirkung::OnRadio1() 
// beschreibung	: 
//-------------------------------------------------------------------------------------------------------------------

void CStreckeneinwirkung::OnRadio1() 
{
	m_iCheck = 1;
}

//-------------------------------------------------------------------------------------------------------------------
// Methode		: CStreckeneinwirkung::OnRadio2()
// Beschreibung	:
//-------------------------------------------------------------------------------------------------------------------

void CStreckeneinwirkung::OnRadio2() 
{
	m_iCheck = 2;
}

//---------------------------------------------------------------------------------------------------------------------
void CStreckeneinwirkung::OnRadio3() 
{
	m_iCheck = 3;
}
