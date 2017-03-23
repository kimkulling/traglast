//----------------------------------------------------------------------------------------------------------------------
///	\file		ChildView.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class definition of CChildView.
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
#include "MainFrm.h"
#include "ChildView.h"
#include "TScale.h"
#include "LocalizationServer.h"
#include "LocalizationObserver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace FEStructure;
using namespace Math;
using namespace Localization;

extern int              iKnNr, iEleNr;
extern Tragwerk			MyTragwerk;
extern NodeStack		g_NodeStack;
extern ElementStack		ElementEingabe;
extern LastStack		LastEingabe;
extern Vektor			SysSteif;
extern Vektor			SysLast1, VM, VQ, VN;
extern InzidenzStack	Inz;
extern PlotStack		DeformPlot, MomentPlot, QuerPlot, LaengsPlot;


//----------------------------------------------------------------------------------------------------------------------
CChildView::CChildView() :
	m_pStatusBar( NULL ),
	m_pLocalizationObserver( NULL ),
	m_pMainFrame( NULL )
{	
	// Leerer Konstruktor
}

//----------------------------------------------------------------------------------------------------------------------
CChildView::~CChildView()
{
	if ( NULL != m_pLocalizationObserver )
		LocalizationServer::get()->removeObserver( m_pLocalizationObserver );
	delete m_pLocalizationObserver;
	m_pLocalizationObserver = NULL;
}

//----------------------------------------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------------------------------
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if ( !CWnd::PreCreateWindow( cs ) )
		return FALSE;

	m_pLocalizationObserver = new LocalizationObserver( this );

	HCURSOR hMyCursor1    = AfxGetApp()->LoadCursor("MyCross.cur");
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style     &= ~WS_BORDER;
	cs.lpszClass  = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_CROSS), HBRUSH(COLOR_WINDOW+1), NULL);

	// Set pointer to statur bar
	m_pMainFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	m_pStatusBar =  m_pMainFrame->getStatusBar();
	
	HCURSOR hMyCursor = AfxGetApp()->LoadStandardCursor( IDC_CROSS );
    if ( !SetCursor( hMyCursor1 ) )
		TRACE0("Error while drawing the mouse cursor.\n");

	if ( !ShowCursor( TRUE ) )
		TRACE0( "Error while drawing the mouse cursor.\n" );

	LocalizationServer::get()->addObserver( m_pLocalizationObserver );
	
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
void CChildView::OnPaint() 
{		
	CRect myRect;
	GetClientRect( myRect );
	Core::d32 dScale = MyTragwerk.GetScale();
	CPaintDC myDC( this );
	myDC.SetMapMode(MM_LOENGLISH);	
	myDC.SetWindowOrg( 0, myRect.Height() );
	
	myDC.SetViewportOrg( 0, 0 );
	CPoint Org( 40, myRect.Height() / 2 );
	MyTragwerk.Org = Org;
	CChildView::KoordDraw(dScale);
	CChildView::DrawALL();
}

//----------------------------------------------------------------------------------------------------------------------
void CChildView::ClearScreen()
{
	CBrush *pBrush = new CBrush( RGB( 255, 255, 255 ) );
	CRect myclientRect;
	GetClientRect( myclientRect );
	CClientDC myDC( this );
	myDC.FillRect( &myclientRect, pBrush );
	delete pBrush; 
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CChildView::KoordDraw( double /* dScale */ )
{
	CPoint Org;
	CRect  myclientRect;
	int    iAufl, iX, iY;

	CClientDC myDC(this);		// Berechnung der Auflösung 
	GetClientRect(myclientRect);
	myDC.SetMapMode(MM_LOENGLISH);	
	iAufl = (myclientRect.Width() > myclientRect.Height()) 
			? myclientRect.Width() : myclientRect.Height();	
	myDC.SetWindowOrg(0,myclientRect.Height());
	myDC.SetViewportOrg(0, 0);

	Org = MyTragwerk.Org;
	iX = Org.x;
	iY = Org.y;

	myDC.MoveTo(iX, iY);
	myDC.LineTo(iX+70, iY);
	myDC.MoveTo(iX, iY);
	myDC.LineTo(iX, iY+70);
	myDC.MoveTo(iX+70, iY);
	myDC.LineTo(iX+65, iY-5);
	myDC.MoveTo(iX+70, iY);
	myDC.LineTo(iX+65, iY+5);
	myDC.MoveTo(iX, iY+70);
	myDC.LineTo(iX+5, iY+65);
	myDC.MoveTo(iX, iY+70);
	myDC.LineTo(iX-5,iY+65);
	myDC.MoveTo(iX-5, iY-5);
	myDC.LineTo(iX+5, iY+5);
	myDC.MoveTo(iX-5, iY+5);
	myDC.LineTo(iX+5, iY-5);

	myDC.TextOut(iX,iY+87,"Y");
	myDC.TextOut(iX+77,iY,"X");
	myDC.TextOut(iX-17,iY,"Z");
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CChildView::DrawNodes()
{
	CFont		NewFont;
	CString		strKnNr;
	CWnd		myWnd;
	int			iIndex, iXorg, iYorg, iI2;
	double		dX, dY, dRand[3], dXtemp, dYtemp;
	
	// Berechnung der Auflösung 
	CRect myclientRect;
	GetClientRect( myclientRect);
	CClientDC myDC(this);		
	myDC.SetMapMode(MM_LOENGLISH);
	/*int iAufl = (myclientRect.Width() > myclientRect.Height()) 
				? myclientRect.Width() : myclientRect.Height();	*/
	myDC.SetWindowOrg( 0,myclientRect.Height());
	myDC.SetViewportOrg(0, 0);
	
	// Neuen Font initialisieren
	NewFont.CreateFont(10, 10, 
		0, 0, FW_DONTCARE, 
		FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, 
		"Symbol");

	// Set new brush
	CFont *pOldFont;
	pOldFont = myDC.SelectObject( &NewFont );
	CBrush *pBrush = new CBrush( RGB( 255, 255, 255 ) );

	iXorg = MyTragwerk.Org.x;
	iYorg = MyTragwerk.Org.y;

	// Draw the nodes
	if (iKnNr>0) 
	{
		
		for ( iIndex=1; iIndex<=iKnNr; iIndex++ ) 
		{
			strKnNr.Format( "%d", iIndex );
			NodeStack::NodeDef node;
			g_NodeStack.getNode( iIndex, node );
			dX = MathUtils<Core::d32>::viewX( node.getPos( Node<Core::d32>::XPos ), MyTragwerk.dTScale, MyTragwerk.Org.x );
			dY = MathUtils<Core::d32>::viewY( node.getPos( Node<Core::d32>::YPos ), MyTragwerk.dTScale, MyTragwerk.Org.y );

			GetRandbed(iIndex, g_NodeStack, dRand);

			CChildView::DrawNode(dX, dY);
		
			// Wenn fest eingespannt
			if ((dRand[0]!=0) && (dRand[1]!=0) && (dRand[2]!=0)) 
			{
				myDC.Rectangle((int) dX-10, (int) dY-10,
					(int) dX+10, (int) dY+10);
			}
			else 
			{
				// Wenn nur in X gehalten
				if ((dRand[0]!=0) && (dRand[1]==0)) 
				{
					myDC.MoveTo((int) dX, (int) dY);
					myDC.LineTo((int) (dX-15), (int) (dY+10));
					myDC.LineTo((int) (dX-15), (int) (dY-10));
					myDC.LineTo((int) dX, (int) dY);
					myDC.MoveTo((int) (dX-18), (int) (dY+10));
					myDC.LineTo((int) (dX-18), (int) (dY-10));
				}
			
				// Wenn nur in Y gehalten
				if ((dRand[0]==0) && (dRand[1]!=0)) 
				{
					myDC.MoveTo ((int) dX, (int) dY);
					myDC.LineTo ((int) (dX-10), (int) (dY-15));
					myDC.LineTo ((int) (dX+10), (int) (dY-15));
					myDC.LineTo ((int) dX, (int) dY);
					myDC.MoveTo ((int) (dX-10), (int) (dY-18));
					myDC.LineTo ((int) (dX+10), (int) (dY-18));
				}
				
				// Wenn um X und um Y gehalten
				if ((dRand[0]!=0) && (dRand[1]!=0)) 
				{
					myDC.MoveTo((int) dX,(int) dY);
					myDC.LineTo((int) (dX-10), (int) (dY-15));
					myDC.LineTo((int) (dX+10), (int) (dY-15));
					myDC.LineTo((int) dX, (int) dY);
					dXtemp = dX - 10;
					dYtemp = dY;
					
					// Zeichne Schraffur
					for (iI2=1; iI2<=10; iI2++) 
					{
						dXtemp += 2;
						myDC.MoveTo((int) (dXtemp-2), (int) (dYtemp-18));
						myDC.LineTo((int) dXtemp, (int) dYtemp-15);
					}
				}
				// Wenn um Y gehalten
				if (dRand[2]!=0) 
				{
					myDC.MoveTo((int) dX, (int) dY);
					myDC.LineTo((int) (dX-20), (int) (dY-20));
				}
			}
			if (MyTragwerk.bKnNr)
			{
				myDC.TextOut((int) dX , (int) (dY - 3), strKnNr);
			}
		}
	}
	delete pBrush;

	return TRUE;
}

//---------------------------------------------------------------------------------------------------------------------
BOOL CChildView::DrawElements( double dScale )
{
	int			iXLaenge, iYLaenge;
	double		dX1, dY1, dX2, dY2, dK1[2], dK2[2];
	CFont		NewFont;
	CString		strNummer;
	CRect		myclientRect;
	
	CClientDC	myDC(this);
	GetClientRect(myclientRect);
	myDC.SetMapMode(MM_LOENGLISH);	
	myDC.SetWindowOrg(0,myclientRect.Height());
	myDC.SetViewportOrg(0, 0);

	int iXorg = MyTragwerk.Org.x; 
	int iYorg = MyTragwerk.Org.y;

	// Create the pens
	CPen *pBalkenPen   = new CPen(PS_SOLID, 2, RGB(10, 10, 10));	// Stift für Balken-Element
	CPen *pFachwerkPen = new CPen(PS_SOLID, 2, RGB(150, 150, 150));	// Stift für Fachwerk-Element
	
	// Initialisierung der Fonts
	NewFont.CreateFont(8, 8, 
		0, 0, FW_DONTCARE, 
		FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, 
		"Symbol");
	
	if ( iEleNr > 0 ) 
	{
		for ( int iIndex=1; iIndex<=iEleNr; iIndex++ ) 
		{
			GetKoord(iIndex, g_NodeStack, dK1, dK2);
			int iArt= ElementEingabe.ReadElement(iIndex, 4, iIndex);
			dX1	= MathUtils<Core::d32>::viewX( dK1[0], dScale, iXorg );
			dY1	= MathUtils<Core::d32>::viewY( dK1[1], dScale, iYorg );
			dX2	= MathUtils<Core::d32>::viewX( dK2[0], dScale, iXorg );
			dY2	= MathUtils<Core::d32>::viewY( dK2[1], dScale, iYorg );
			
			strNummer.Format("%d", iIndex);
			
			iXLaenge = (int) ((dX2 - dX1) / 2);
			iYLaenge = (int) ((dY2 - dY1) / 2);
			
			if (MyTragwerk.bEleNr)
				myDC.TextOut((int) (dX1 + iXLaenge), (int) (dY1 + iYLaenge), strNummer); 
			
			// Switch between kind of elements
			if (iArt==1)
				myDC.SelectObject(pFachwerkPen);

			if ((iArt==2) || (iArt==3) || (iArt==4))
				myDC.SelectObject(pBalkenPen);

			myDC.MoveTo((int) dX1, (int) dY1);
			myDC.LineTo((int) dX2, (int) dY2);
			
			// If a joint exist
			if (iArt==3)
				CChildView::DrawGelenk((int) dX1, (int) dY1);
			if (iArt==4)
				CChildView::DrawGelenk((int) dX2, (int) dY2);
		}
	}

	delete pBalkenPen;
	delete pFachwerkPen;

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CChildView::DrawForce(double dScale)
{
	CRect myclientRect;
	GetClientRect( myclientRect );
	CClientDC myDC( this );
	myDC.SetMapMode( MM_LOENGLISH );	
	myDC.SetWindowOrg( 0, myclientRect.Height() );
	myDC.SetViewportOrg( 0, 0 );
	
	const int iXorg = MyTragwerk.Org.x; 
	const int iYorg = MyTragwerk.Org.y;
	BOOL bFlag = TRUE;
	int iLastNr = LastEingabe.iLastNr;
	if ( 0 == iLastNr )	
		bFlag = FALSE;

	if ( bFlag ) 
	{
		for ( int iI=1; iI<=iLastNr; iI++ ) 
		{
			double dW[ 3 ];
			const Core::i32 iNode = round(LastEingabe.readLast(iI, 1));
			NodeStack::NodeDef node;
			g_NodeStack.getNode( iNode, node );
			const Core::d32 xPos = node.getPos( Node<Core::d32>::XPos );
			const Core::d32 yPos = node.getPos( Node<Core::d32>::YPos );
			const Core::d32 dX = MathUtils<Core::d32>::viewX( xPos, dScale, iXorg );
			const Core::d32 dY = MathUtils<Core::d32>::viewY( yPos, dScale, iYorg );
			for ( int iI2=1; iI2<=3; iI2++)
				dW[iI2-1] = LastEingabe.readLast(iI, iI2+1);
			
			// Draw the single load
			if (LastEingabe.readLast(iI, 5)==1) 
			{
				// In x direction
				if ( 0.0 != dW[ 0 ] )
					CChildView::DrawArrow(dScale, (int) dX, (int) dY, iXorg, iYorg, -50, 0, 0);
				
				// In y direction
				if ( 0.0 != dW[ 1 ] )
					CChildView::DrawArrow(dScale, (int) dX, (int) dY, iXorg, iYorg, 0, 50, 0);
				for ( int iI2=0; iI2<=2; iI2++)
					dW[ iI2 ]=0.0;
			}

			// If a line load
			if ( 2 == LastEingabe.readLast(iI, 5) ) 
			{
				if ( 0.0 != dW[ 0 ] )
					CChildView::DrawArrow( dScale, (int) dX, (int) dY, iXorg, iYorg, -50, 0, 1 );
				if ( 0.0 != dW[ 1 ] )
					CChildView::DrawArrow( dScale, (int) dX, (int) dY, iXorg, iYorg, 0, 50, 1 );
			}
		}
	}
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CChildView::DrawALL()
{
	const Core::d32	dScale = MyTragwerk.GetScale();
	const Core::i32 iLK = MyTragwerk.iLagerKno;

	CChildView::ClearScreen();

	if ( !CChildView::KoordDraw( dScale ) )
		TRACE0( "Error while drawing tripod.\n" );

	if ( !CChildView::DrawNodes() )
		TRACE0( "Error while drawing the nodes.\n" );

	if ( !CChildView::DrawElements( dScale ) )
		TRACE0( "Error while drawing the elements.\n");

	if ( !CChildView::DrawForce( dScale ) )
		TRACE0( "Error while drawing the loads.\n" );

	if (MyTragwerk.bCalc) 
	{
		if (MyTragwerk.bDef)
		{
			if (!CChildView::DrawDeform(MyTragwerk.dTScale, SysLast1, Inz))
			{
				TRACE0( "Error while drawing the deformations.\n");
			}
		}

		if (MyTragwerk.bM||MyTragwerk.bQ||MyTragwerk.bN)
		{
			if (!CChildView::DrawSchnittkraft(VM, VQ, VN))
			{
				TRACE0( "Error while drawing the moment area.\n" );
			}
		}
	}

	// Tragwerksdaten in der Statusbar anzeigen
	setLocalizedStatusTexts();

	return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
bool CChildView::onLanguageChange()
{
	setLocalizedStatusTexts();

	return true;
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CChildView::DrawDeform(double dScale, Vektor DeformVektor, InzidenzStack Inz)
{
	int       nI1, iAufl, nXorg, nYorg, nFG, nEleKn;
	int       nPos;
	double    dScale_X = 0, dScale_Y = 0, dDiff[2], dXdef, dYdef, dTempX, dTempY;
	CFont     NewFont;
	CString   strDeform;
	CPen     *pBiegePen = new CPen(PS_SOLID, 1, RGB(100, 100, 100));	// Stift für Biegelinie
	CPen     *pElementPen = new CPen(PS_SOLID, 1, RGB(10, 10, 10));		// Stift für Balken-Element
	CPoint	  Org = MyTragwerk.Org;
	CClientDC myDC(this);		
	CRect     myclientRect;
 
	const Core::i32 nKn = g_NodeStack.getNumberOfNodes();
	int nEleAnz = ElementEingabe.numberOfElements();
	GetClientRect(myclientRect);
	myDC.SetMapMode(MM_LOENGLISH);	// Berechnung der Auflösung
	iAufl = (myclientRect.Width() > myclientRect.Height()) 
				? myclientRect.Width() : myclientRect.Height();	
	myDC.SetWindowOrg(0,myclientRect.Height());
	myDC.SetViewportOrg(0, 0);

	NewFont.CreateFont(7, 7, 
		0, 0, FW_DONTCARE, 
		FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, 
		"Symbol");

	CFont *pOldFont = myDC.SelectObject( &NewFont );
	nFG = MyTragwerk.iFG;
	if (nFG==3)
		nEleKn = 2;
	nXorg  = Org.x;
	nYorg  = Org.y;
	dScale = MyTragwerk.GetScale();

	for (nI1=1; nI1<3; nI1++)
		dDiff[nI1-1] = DeformVektor.Getmax(nFG, 3) - DeformVektor.Getmin(nFG, 3);
	
	if ( dDiff[0]==0 )
		dDiff[0] = dDiff[1];
	if ( dDiff[1]==0 ) 
		dDiff[1] = dDiff[0];

	assert( 0.0 != dDiff[ 0 ] );
	dScale_X = 50 / dDiff[ 0 ];
	assert( 0.0 != dDiff[ 1 ] );
	dScale_Y = 50 / dDiff[ 1 ];
	if (dScale_X==0) 
		dScale_X = dScale_Y;
	if (dScale_Y==0) 
		dScale_Y = dScale_X;

	dTempX = 0;
	dTempY = 0;
	nPos   = 0;

	// Draw the nodes
	for (nI1=1; nI1<nKn+1; ++nI1) 
	{
		NodeStack::NodeDef node;
		g_NodeStack.getNode( nI1, node );

		const Core::d32 xPos = node.getPos( Node<Core::d32>::XPos );
		const Core::d32 yPos = node.getPos( Node<Core::d32>::YPos );
		int nX = (int) MathUtils<Core::d32>::viewX( xPos, dScale, nXorg );
		int nY = (int) MathUtils<Core::d32>::viewY( yPos, dScale, nYorg );
		myDC.MoveTo(nX, nY);
		dXdef = DeformPlot.ReadPlot(nI1, 3);
		dYdef = DeformPlot.ReadPlot(nI1, 4);
		strDeform.Format("%lf/%lf", dXdef, dYdef);
		myDC.TextOut(nX + (int) (dXdef * dScale_X), nY - (int) (dYdef * dScale_Y), strDeform);
		myDC.SelectObject(pBiegePen);
		myDC.LineTo(nX + (int) (DeformPlot.ReadPlot(nI1, 3) * dScale_X), nY
			- (int) (DeformPlot.ReadPlot(nI1, 4) * dScale_Y));
		DrawNode(nX + (int) (dXdef * dScale_X), nY - (int) (dYdef * dScale_Y));
	}

	// Draw the elements
	for (nI1=1; nI1<nEleAnz+1; ++nI1) 
	{
		int nTemp1 = ElementEingabe.ReadElement(nI1, 1, nI1);
		int nTemp2 = ElementEingabe.ReadElement(nI1, 2, nI1);
		int nX = (int) ( MathUtils<Core::d32>::viewX( DeformPlot.ReadPlot(nTemp1, 1), dScale, nXorg ) );
		int nY = (int) ( MathUtils<Core::d32>::viewY( DeformPlot.ReadPlot(nTemp1, 2), dScale, nYorg ) );
		dXdef  = DeformPlot.ReadPlot( nTemp1, 3 );
		if ( dXdef < DEFNULL ) 
			dXdef = 0.0;
		dYdef  = DeformPlot.ReadPlot( nTemp1, 4 );
		if ( dYdef < DEFNULL ) 
			dYdef = 0.0;

		myDC.MoveTo( nX + (int) (dXdef * dScale_X), nY - (int) ( dYdef * dScale_Y ) );
		nX    = (int) ( MathUtils<Core::d32>::viewX( DeformPlot.ReadPlot( nTemp2, 1 ), dScale, nXorg ) );
		nY    = (int) ( MathUtils<Core::d32>::viewY( DeformPlot.ReadPlot( nTemp2, 2 ), dScale, nYorg ) );
		dXdef = DeformPlot.ReadPlot( nTemp2, 3 );
		if ( dXdef < DEFNULL ) 
			dXdef = 0;
		dYdef  = DeformPlot.ReadPlot( nTemp2, 4 );
		if ( dYdef < DEFNULL ) 
			dYdef = 0.0;
		myDC.SelectObject( pElementPen );
		
		myDC.LineTo( nX + (int) ( dXdef * dScale_X ), nY - (int) (dYdef * dScale_Y ) );
	}
	
	delete pBiegePen;
	delete pElementPen;

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CChildView::DrawSchnittkraft(Vektor VM, Vektor VQ, Vektor VN)
{
	BOOL		bT = FALSE;
	int			iPos, nEleAnz, iFG;
	double		dK[5][2], dX, dY, dXdef, dYdef, dScale_X, dScale_Y, dDiff[2], 
				dXtemp[2], dYtemp[2], dCx, dCy, dMtemp, dQtemp, dNtemp;
	CClientDC	myDC(this);		
	CRect		myclientRect;
	CFont		NewFont;
	CPoint		Org = MyTragwerk.Org;

	// Set vars to zero
	dMtemp = 0.0;
	dQtemp = 0.0;
	dNtemp = 0.0;

	nEleAnz = ElementEingabe.numberOfElements();
	GetClientRect(myclientRect);
	myDC.SetMapMode(MM_LOENGLISH);	// Berechnung der Auflösung
	myDC.SetWindowOrg(0,myclientRect.Height());
	myDC.SetViewportOrg(0, 0);
	
	NewFont.CreateFont(7, 7, 
		0, 0, FW_DONTCARE, 
		FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, 
		"Symbol");
	
	CFont *pOldFont;
	pOldFont = myDC.SelectObject( &NewFont);

	// Getting needed values 
	iFG = MyTragwerk.iFG;
	
	// We want to draw the moments
	if (MyTragwerk.bM) 
	{
		// Momentenflaeche wird gezeichnet	
		iPos = 0;
		for ( int iI1=0; iI1<2; iI1++ )
			dDiff[iI1] = VM.Getmax(iFG, 3) - VM.Getmin(iFG, 3);

		GUI::Scale2D<Core::d32>( dDiff[0], dDiff[1], dScale_X, dScale_Y );

		for ( int iI1=1; iI1<=nEleAnz; iI1++ ) 
		{
			// Sooft machen, wie Knoten pro Element vorhanden
			for (int iI2=0; iI2<2; iI2++) 
			{
				iPos++;
				for ( int iI3=1; iI3<=5; iI3++ )
				{
					dK[iI3-1][iI2] = MomentPlot.ReadPlot(iPos, iI3);
				}
			}
			dX	= ( dK[ 0 ][ 1 ] - dK[ 0 ][ 0 ] );
			dY	= ( dK[ 1 ][ 1 ] - dK[ 1 ][ 0 ] );
			
			rescaleValue( dX, dY, dCx, dCy );

			int last = 0;
			for ( int iI2=0; iI2<2; iI2++ )  
			{	
				// Gehe zu Knoten
				dX = MathUtils<Core::d32>::viewX( dK[ 0 ][ iI2 ], MyTragwerk.dTScale, Org.x );
				dY = MathUtils<Core::d32>::viewY( dK[ 1 ][ iI2 ], MyTragwerk.dTScale, Org.y );
				myDC.MoveTo((int) dX, (int) dY);
			
				// Zeichne Linie zu Momentenwert
				if (abs(((int) dK[4][iI2])) > ((int) dMtemp)) 
					bT = TRUE;

				dXdef = dX + (dK[4][iI2]  * dCy * dScale_X);
				dYdef = dY - (dK[4][iI2]  * dCx * dScale_Y);
				myDC.LineTo((int) dXdef, (int) dYdef);
				dXtemp[iI2] = dXdef;
				dYtemp[iI2] = dYdef;
				last = iI2;
			}
			myDC.MoveTo((int) dXtemp[0], (int) dYtemp[0]);
			myDC.LineTo((int) dXtemp[1], (int) dYtemp[1]);
			dMtemp = dK[ 4 ][ last ];
		}
	}
	
	// Wenn Querkraftfläche gezeichnet werden soll
	if (MyTragwerk.bQ)	
	{
		// Querkarft-Flaeche wird gezeichnet	
		for ( int iI1=0; iI1<2; iI1++ )
			dDiff[iI1] = VQ.Getmax(iFG, 3) - VQ.Getmin(iFG, 3);

		// Skalierung der Querkräfte
		GUI::Scale2D<Core::d32>( dDiff[ 0 ], dDiff[ 1 ], dScale_X, dScale_Y );

		iPos = 0;
		for ( int iI1=1; iI1<=nEleAnz; iI1++ ) 
		{
			for ( int iI2=0; iI2<2; iI2++ ) 
			{
				iPos++;
				for ( int iI3=1; iI3<=5; iI3++ )
				{
					dK[iI3-1][iI2] = QuerPlot.ReadPlot(iPos, iI3);
				}
			}
			// Ermittlung der Länge und Winkelbeziehungen für das momentane Moment berechnen
			dX	= dK[0][1] - dK[0][0];
			dY	= dK[1][1] - dK[1][0];

			rescaleValue( dX, dY, dCx, dCy );

			int last = 0;
			for ( int iI2=0; iI2<2; iI2++ ) 
			{
				// Gehe zu Knoten
				dX = MathUtils<Core::d32>::viewX( dK[0][iI2], MyTragwerk.dTScale, Org.x );
				dY = MathUtils<Core::d32>::viewY( dK[1][iI2], MyTragwerk.dTScale, Org.y );
				myDC.MoveTo((int) dX, (int) dY);
			
				// Zeichne Linie zu Momentenwert
				if ( abs( (int) dK[3][iI2]) > dQtemp ) 
					bT = TRUE;
				dXdef = dX + (dK[3][iI2]  * dCy * dScale_X);
				dYdef = dY - (dK[3][iI2]  * dCx * dScale_Y);
				myDC.LineTo((int) dXdef, (int) dYdef);
				
				// Speichere Werte für die Darstellung der Umrißfläche
				dXtemp[iI2] = dXdef;
				dYtemp[iI2] = dYdef;
				last = iI2;
			}
			myDC.MoveTo((int) dXtemp[0], (int) dYtemp[0]);
			myDC.LineTo((int) dXtemp[1], (int) dYtemp[1]);
			dQtemp = dK[ 3 ][ last ];
		}
	}
	
	// Laengskraftflaeche wird gezeichnet
	if (MyTragwerk.bN) 
	{
		// Berechnung des Skalierungsfaktor für die Längskraftfläche
		for ( int iI1=0; iI1<2; iI1++ )
			dDiff[iI1] = VN.Getmax(iFG, 3) - VN.Getmin(iFG, 3);
	
		// Berechnung der Skalierung
		GUI::Scale2D<Core::d32>( dDiff[0], dDiff[1], dScale_X, dScale_Y );

		// Lese die Laengskraft-Daten
		iPos = 0;
		for ( int iI1=1; iI1<nEleAnz+1; iI1++ ) 
		{
			for ( int iI2=0; iI2<2; iI2++ ) 
			{
				iPos++;
				for ( int iI3=1; iI3<6; iI3++ )
				{
					dK[iI3-1][iI2] = LaengsPlot.ReadPlot(iPos, iI3);
				}
			}
			
			// Ermittlung der Abmaße und Winkelbeziehungen
			dX	= dK[0][1] - dK[0][0];
			dY	= dK[1][1] - dK[1][0];

			rescaleValue( dX, dY, dCx, dCy );

			
			// Draw the logitunal-cutting-force
			int last = 0;
			for ( int iI2=0; iI2<2; iI2++ ) 
			{
				// Bewege Zeichenstift zu Knoten
				dX = MathUtils<Core::d32>::viewX( dK[ 0 ][ iI2 ], MyTragwerk.dTScale, Org.x );
				dY = MathUtils<Core::d32>::viewY( dK[ 1 ][ iI2 ], MyTragwerk.dTScale, Org.y );
				myDC.MoveTo((int) dX, (int) dY);
			
				// Zeichne Linie zum Laengskraft-Wert
				if (abs((int) dK[2][iI2]) > dNtemp) 
				{
					// Wenn Maximum, schreibe Wert über Fläche
					bT = TRUE;
				}
				
				dXdef = dX + (dK[2][iI2]  * dCy * dScale_X);
				dYdef = dY - (dK[2][iI2]  * dCx * dScale_Y);

				myDC.LineTo((int) dXdef, (int) dYdef);
				dXtemp[iI2] = dXdef;
				dYtemp[iI2] = dYdef;
				last = iI2;
			}

			myDC.MoveTo((int) dXtemp[0], (int) dYtemp[0]);
			myDC.LineTo((int) dXtemp[1], (int) dYtemp[1]);
			dNtemp = dK[ 2 ][ last ];
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
LRESULT CChildView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	WORD      wXPos = LOWORD(lParam), wYPos = HIWORD(lParam);  
	CPoint    Org, Temp;
	HMENU     hm;
	POINT     p;
	CWnd      myWnd;
	CRect     myclientRect;
	CString	  strText;
	int       iIndex, iY, iX, iAufloesung;
	double    dScale = MyTragwerk.GetScale(), dX, dY;
	CClientDC myDC(this);

	GetClientRect(myclientRect);
	myDC.SetMapMode(MM_LOENGLISH);
	iAufloesung = (myclientRect.Width() > myclientRect.Height()) 
			? myclientRect.Width() : myclientRect.Height();	
	myDC.SetWindowOrg(0,myclientRect.Height());
	myDC.SetViewportOrg(0, 0);

	// Beginn des Message-Loops für das ChildWindow
	switch (message)
	{
	case WM_MOUSEMOVE:	
		// Wenn Maus bewegt wurde
		Org    = MyTragwerk.Org;
		Temp.x = wXPos; 
		Temp.y = wYPos; 
		dX     = MathUtils<Core::d32>::realX( wXPos, dScale, Org.x );
		strText.Format("X: %4.2f", dX);
		iIndex = m_pStatusBar->CommandToIndex( IDS_XPOS);
		m_pStatusBar->SetPaneText(iIndex, strText);
		dY = -1 * MathUtils<Core::d32>::realY( wYPos, dScale, Org.y );
		strText.Format("Y: %4.2f", dY);
		iIndex = m_pStatusBar->CommandToIndex(IDS_YPOS);
		m_pStatusBar->SetPaneText(iIndex, strText);
		if (MyTragwerk.bMove) 
		{
			if (MyTragwerk.Mtemp!=Temp)
			{
				int dummy = 0;
				dummy++;
			}
		}
		break;

	case WM_LBUTTONUP:	
		// Wenn linke Maustaste gedrückt
		wXPos = LOWORD(lParam); wYPos = HIWORD(lParam);
		iX = (int) ( MathUtils<Core::d32>::viewX( wXPos, MyTragwerk.dTScale, MyTragwerk.Org.x ) );
		iY = (int) ( MathUtils<Core::d32>::viewY( wYPos, MyTragwerk.dTScale, MyTragwerk.Org.y ) );
		break;

	case WM_RBUTTONUP:	// Bei rechter Maustaste öffne Popup-Menü
		hm = CreatePopupMenu();
		GetCursorPos(&p);
		/*AppendMenu(hm, MF_STRING, 1, "Neuer Knoten");
		AppendMenu(hm, MF_STRING, 2, "Neues Material");
		AppendMenu(hm, MF_STRING, 3, "Neues Element");
		AppendMenu(hm, MF_STRING, 4, "Beenden");*/
		CChildView::SetForegroundWindow();
		TrackPopupMenu(hm, TPM_LEFTALIGN, p.x, p.y, 0, CChildView::m_hWnd, NULL);
		if(GetMenu()) 
		{
			DestroyMenu(hm);
		}
		break;

	case WM_COMMAND:
		break;
	}
	
	return CWnd::WindowProc(message, wParam, lParam);
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CChildView::DrawArrow(double /*dScale*/, int iX, int iY, int /*iXorg*/, int /*iYorg*/, 
						   short sX, short sY, short sM)
{
	int			iDX, iDY, iAufl;
	CClientDC	myDC(this);
	CRect		myclientRect;

	// Berechnung der Auflösung 
	GetClientRect(myclientRect);
	myDC.SetMapMode(MM_LOENGLISH);	
	iAufl = (myclientRect.Width() > myclientRect.Height()) 
				? myclientRect.Width() : myclientRect.Height();	
	myDC.SetWindowOrg(0,myclientRect.Height());
	myDC.SetViewportOrg(0, 0);
	
	// Gehe zu Ausgangskoordinaten
	myDC.MoveTo(iX, iY);
	iDX = iX + sX;
	iDY = iY + sY;

	// Draw line
	myDC.LineTo(iDX ,iDY); 

	// Move to direction
	myDC.MoveTo(iX, iY);
	
	if (sX!=0) 
	{ 
		// Pfeil in X-Richtung
		myDC.LineTo(iX - 10, iY + 10);
		myDC.LineTo(iX - 10, iY - 10);
		myDC.LineTo(iX ,iY);
	}
	if (sY!=0) 
	{ 
		// Pfeil in Y-Richtung
		myDC.LineTo(iX + 10, iY + 10);
		myDC.LineTo(iX - 10, iY + 10);
		myDC.LineTo(iX, iY);
	}

	if (sM!=0)
	{
		// Doppelpfeil in X-Richtung		
		myDC.LineTo(iX - 10, iY + 10);
		myDC.LineTo(iX - 10, iY - 10);
		myDC.LineTo(iX ,iY);
		myDC.MoveTo(iX - 10, iY);
		myDC.LineTo(iX - 20, iY + 10);
		myDC.LineTo(iX - 20, iY - 10);
	}
	
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
inline BOOL CChildView::DrawGelenk(double dX, double dY)
{
	int				iAufl;
	CClientDC		myDC(this);
	CRect			myclientRect;
	GetClientRect	(myclientRect);
	
	// Berechne Aufloesung
	myDC.SetMapMode(MM_LOENGLISH);	
	iAufl = (myclientRect.Width() > myclientRect.Height()) 
				? myclientRect.Width() : myclientRect.Height();	
	myDC.SetWindowOrg(0,myclientRect.Height());
	myDC.SetViewportOrg(0, 0);
	
	// Zeichne Ellipse am Knoten, wo Gelenk liegt
	myDC.Ellipse((int) (dX-6), (int) (dY-6), (int) (dX+6), (int) (dY+6));
	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CChildView::DrawNode( double dX, double dY )
{
	CRect myclientRect;
	GetClientRect (myclientRect);
	CClientDC myDC( this );
	myDC.SetMapMode( MM_LOENGLISH );	
	myDC.SetWindowOrg( 0, myclientRect.Height() );
	myDC.SetViewportOrg( 0, 0 );
	myDC.Rectangle((int) (dX-2), (int) (dY-2), (int) (dX+2), (int) (dY+2));

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
void CChildView::rescaleValue( Core::d32 x, Core::d32 y, Core::d32 &dCx, Core::d32 &dCy )
{
	dCx = 0.0;
	dCy = 0.0;
	const Core::d32 dL = dL2D( x, y );
	if ( dL > 0.0 )
	{
		dCx	= x / dL;
		dCy	= y / dL;
	}
}

//----------------------------------------------------------------------------------------------------------------------
//	Sets the localized status texts.
void CChildView::setLocalizedStatusTexts()
{
	CString	strText( "" );
	
	if ( NULL == m_pStatusBar )
		m_pStatusBar = m_pMainFrame->getStatusBar();
	assert( NULL != m_pStatusBar );
	
	Core::i32 index = 0;
	std::string statusTxt( "" );
	index = m_pStatusBar->CommandToIndex(IDS_ANZNODE);
	statusTxt = LocalizationServer::get()->getText( "StatusTxt_Nodes" );
	strText.Format( "%s: %4d", statusTxt.c_str(), iKnNr );
	m_pStatusBar->SetPaneText(index, strText);
	
	index = m_pStatusBar->CommandToIndex( IDS_ANZELE );
	statusTxt = LocalizationServer::get()->getText( "StatusTxt_Elements" );
	strText.Format( "%s: %4d", statusTxt.c_str(), iEleNr );
	m_pStatusBar->SetPaneText(index, strText);
	
	const Core::i32 iLK = MyTragwerk.iLagerKno;
	index = m_pStatusBar->CommandToIndex(IDS_ANZLAGER);
	statusTxt = LocalizationServer::get()->getText( "StatusTxt_Cond" );
	strText.Format( "%s: %d", statusTxt.c_str(), iLK );
	m_pStatusBar->SetPaneText(index, strText );

}

//----------------------------------------------------------------------------------------------------------------------
