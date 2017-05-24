//----------------------------------------------------------------------------------------------------------------------
///	\file		MainFrm.cpp
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2001
///	\brief		Class definition of MainFrm, implements the main window handling.
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
#include <windows.h>
#include <strsafe.h>
#include "Win_Traglast.h"
#include "MainFrm.h"
#include "KoordWork.h"
#include "MaterialWork.h"
#include "ElementWork.h"
#include "Einzeleinwirkung.h"
#include "TragwerkInfo.h"
#include "Eigenschaften.h"
#include "Streckeneinwirkung.h"
#include "Delmat.h"
#include "Calculate.h"
#include "LocalizationServer.h"
#include "LocalizationObserver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace FEStructure;
using namespace Localization;

extern int           iKnNr, iMatNr, iEleNr, iLastNr;
extern Tragwerk      MyTragwerk;
extern NodeStack	g_NodeStack;
extern MaterialStack MaterialEingabe;
extern ElementStack  ElementEingabe;
extern Vektor        SysLast1, VM, VQ, VN;
extern LastStack     LastEingabe;
extern InzidenzStack Inz;

enum 
{
	FileMenuPos = 0,
	EditMenuPos = 1,
	ViewMenuPos = 2,
	StructureMenuPos = 3,
	CalcMenuPos = 4,
	HelpMenuPos = 5,
	ExportMenuPos = 6,
	NodesMenuPos = 7
};

//----------------------------------------------------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_TRAGWERK_KOORDINATENBEARBEITEN, OnTragwerkKoordinatenbearbeiten)
	ON_COMMAND(ID_TRAGWERK_MATERIALBEARBEITEN, OnTragwerkMaterialbearbeiten)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_TRAGWERK_TRAGWERKSINFO, OnTragwerkTragwerksinfo)
	ON_COMMAND(ID_TRAGWERK_ELEMENTEBEARBEITEN_NUMERISCH, OnTragwerkElementebearbeitenNumerisch)
	ON_COMMAND(ID_DATEI_FFNEN, OnDateiFfnen)
	ON_COMMAND(ID_DATEI_SPEICHERN, OnDateiSpeichern)
	ON_COMMAND(ID_TRAGWERK_LASTENBEARBEITEN_EINZELLASTENBEARBEITEN, OnTragwerkLastenbearbeitenEinzellastenbearbeiten)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_BERECHNUNG_BERECHNUNGSTARTEN, OnBerechnungBerechnungstarten)
	ON_COMMAND(ID_BUTTON32778, OnButton32778)
	ON_COMMAND(ID_BUTTON32780, OnButton32780)
	ON_COMMAND(ID_BUTTON32779, OnButton32779)
	ON_COMMAND(ID_ANSICHT_ZOOM_ZOOMIN, OnAnsichtZoomZoomin)
	ON_COMMAND(ID_ANSICHT_ZOOM_ZOOMOUT, OnAnsichtZoomZoomout)
	ON_COMMAND(ID_BUTTON32787, OnButton32787)
	ON_COMMAND(ID_BUTTON32789, OnButton32789)
	ON_COMMAND(ID_BUTTON32788, OnButton32788)
	ON_COMMAND(ID_BUTTON32790, OnButton32790)
	ON_COMMAND(ID_BUTTON32793, OnButton32793)
	ON_COMMAND(ID_BERECHNUNG_ERGEBNISSE_DURCHBIEGUNG, OnBerechnungErgebnisseDurchbiegung)
	ON_COMMAND(ID_BERECHNUNG_ERGEBNISSE_LNGSKRAFT, OnBerechnungErgebnisseLngskraft)
	ON_COMMAND(ID_BERECHNUNG_ERGEBNISSE_MOMENT, OnBerechnungErgebnisseMoment)
	ON_COMMAND(ID_BERECHNUNG_ERGEBNISSE_QUERKRAFT, OnBerechnungErgebnisseQuerkraft)
	ON_COMMAND(ID_BERECHNUNG_ERGEBNISSELSCHEN, OnBerechnungErgebnisselschen)
	ON_COMMAND(ID_BUTTON32799, OnButton32799)
	ON_COMMAND(ID_BUTTON32800, OnButton32800)
	ON_COMMAND(ID_OPEN, OnOpen)
	ON_COMMAND(ID_ANSICHT_EINSTELLUNGEN, OnAnsichtEinstellungen)
	ON_COMMAND(ID_TRAGWERK_LASTENBEARBEITEN_LINIENEINWIRKUNGERZEUGEN, OnTragwerkLastenbearbeitenLinieneinwirkungerzeugen)
	ON_COMMAND(ID_BUTTON32798, OnButton32798)
	ON_COMMAND(ID_DATEI_NEU, OnDateiNeu)
	ON_COMMAND(ID_TRAGWERK_MATERIALBEARBEITEN_MATERIALERZEUGEN, OnTragwerkMaterialbearbeitenMaterialerzeugen)
	ON_COMMAND(ID_TRAGWERK_MATERIALBEARBEITEN_MATERIALLSCHEN, OnTragwerkMaterialbearbeitenMateriallschen)
	ON_COMMAND(ID_BUTTONCALC, OnButtoncalc)
	ON_COMMAND(ID_BUTTONMOMENT, OnButtonmoment)
	ON_COMMAND(ID_BUTTONQUER, OnButtonquer)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BUTTONLAENGS, OnButtonlaengs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------------------------------
static UINT indicators[] =
{
	ID_SEPARATOR,// Statusleistenanzeige
	IDS_COMMAND,
	IDS_ANZNODE,
	IDS_ANZELE,
	IDS_ANZLAGER,
	IDS_XPOS,
	IDS_YPOS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

//----------------------------------------------------------------------------------------------------------------------
//	Constructor.
CMainFrame::CMainFrame() :
	m_pStatusBar( NULL ),
	m_pLocalizationObserver( NULL )
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
//	Destructor.
CMainFrame::~CMainFrame()
{
	if ( NULL != m_pLocalizationObserver )
		LocalizationServer::get()->removeObserver( m_pLocalizationObserver );
	delete m_pLocalizationObserver;
	m_pLocalizationObserver = NULL;
}

//----------------------------------------------------------------------------------------------------------------------
bool CMainFrame::onLanguageChange()
{
	CMenu *pMenu = CMainFrame::GetMenu();
	if ( NULL == pMenu )
	{
		return false;
	}
	
	// Toolbars
	std::string newStr( "" );
	newStr = LocalizationServer::get()->getText( "Toolbar_Tools" );
	m_wndToolBar.SetWindowText( newStr.c_str() );
	newStr = LocalizationServer::get()->getText( "Toolbar_Nodes" );
	m_wndKoordBar.SetWindowText( newStr.c_str() );
	newStr = LocalizationServer::get()->getText( "Toolbar_Loads" );
	m_wndForceBar.SetWindowText( newStr.c_str() );
	newStr = LocalizationServer::get()->getText( "Toolbar_Results" );
	m_wndResultBar.SetWindowText( newStr.c_str() );

	// Menus
	langSetupFileMenu( pMenu );

	newStr = LocalizationServer::get()->getText( "Menu_Edit_Title" );
	pMenu->ModifyMenu( EditMenuPos, MF_BYPOSITION, 0, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Edit_Undo" );
	pMenu->ModifyMenuA( ID_EDIT_UNDO, 0, ID_EDIT_UNDO, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Edit_Cut" );
	pMenu->ModifyMenuA( ID_EDIT_CUT, 0, ID_EDIT_CUT, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Edit_Copy" );
	pMenu->ModifyMenuA( ID_EDIT_COPY, 0, ID_EDIT_COPY, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Edit_Paste" );
	pMenu->ModifyMenuA( ID_EDIT_PASTE, 0, ID_EDIT_PASTE, newStr.c_str() );
	
	newStr = LocalizationServer::get()->getText( "Menu_View_Title" );
	pMenu->ModifyMenu( ViewMenuPos, MF_BYPOSITION, 0, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_View_ViewBar" );
	pMenu->ModifyMenuA( ID_VIEW_TOOLBAR, 0, ID_VIEW_TOOLBAR, newStr.c_str() );
	
	newStr = LocalizationServer::get()->getText( "Menu_View_StatusBar" );
	pMenu->ModifyMenuA( ID_VIEW_STATUS_BAR, 0, ID_VIEW_STATUS_BAR, newStr.c_str() );
	
	newStr = LocalizationServer::get()->getText( "Menu_View_ZoomAll" );
	pMenu->ModifyMenuA( ID_ANSICHT_ZOOM_ZOOMALLES, 0, ID_ANSICHT_ZOOM_ZOOMALLES, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_View_ZoomIn" );
	pMenu->ModifyMenuA( ID_ANSICHT_ZOOM_ZOOMIN, 0, ID_ANSICHT_ZOOM_ZOOMIN, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_View_ZoomOut" );
	pMenu->ModifyMenuA( ID_ANSICHT_ZOOM_ZOOMOUT, 0, ID_ANSICHT_ZOOM_ZOOMOUT, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_View_View" );
	pMenu->ModifyMenuA( ID_ANSICHT_ANSICHT, 0, ID_ANSICHT_ANSICHT, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_View_Properties" );
	pMenu->ModifyMenuA( ID_ANSICHT_EINSTELLUNGEN, 0, ID_ANSICHT_EINSTELLUNGEN, newStr.c_str() );
	
	langSetupStructureMenu( pMenu );	
	langSetupComputationMenu( pMenu );
	
	newStr = LocalizationServer::get()->getText( "Menu_Help_Info" );
	pMenu->ModifyMenuA( ID_APP_ABOUT, 0, ID_APP_ABOUT, newStr.c_str() );

	return true;
}

//----------------------------------------------------------------------------------------------------------------------
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Creating toolbars
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL)) 
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) 
	{
		TRACE0( "Cannot create symbol bar.\n");
		return -1;
	}

	if ( !m_wndStatusBar.Create( this ) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators) / sizeof(UINT))) 
	{
		TRACE0( "Cannot create status bar!\n" );
		return -1;
	}
	m_pStatusBar = &m_wndStatusBar;

	if (!m_wndKoordBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || 
		!m_wndKoordBar.LoadToolBar(IDR_KOORDBAR)) 
	{
		TRACE0( "Cannot create coord bar.\n" );
		return -1;
	}

	if (!m_wndForceBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndForceBar.LoadToolBar(IDR_FORCEBAR)) 
	{
		TRACE0( "Cannot create loading utility bar.\n");
		return -1;
	}

	if (!m_wndResultBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndResultBar.LoadToolBar(IDR_RESULTBAR)) 
	{
		TRACE0( "Cannnot create result bar.\n" );
		return -1;
	}
	
	// Set the titles of the toolbars	
	std::string newStr( "" );
	newStr = LocalizationServer::get()->getText( "Toolbar_Tools" );
	m_wndToolBar.SetWindowText( newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Toolbar_Nodes" );
	m_wndKoordBar.SetWindowText( newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Toolbar_Loads" );
	m_wndForceBar.SetWindowText( newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Toolbar_Results" );
	m_wndResultBar.SetWindowText( newStr.c_str() );

	// Docking of toolbars
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY); 
	m_wndKoordBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndForceBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndResultBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndKoordBar);
	DockControlBar(&m_wndForceBar);
	DockControlBar(&m_wndResultBar);

	TCHAR sz[160]; 
	LoadString( GetModuleHandle( NULL ), IDS_XPOS, sz, sizeof( sz ) );
	m_pLocalizationObserver = new LocalizationObserver( this );
	LocalizationServer::get()->addObserver( m_pLocalizationObserver );

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

//----------------------------------------------------------------------------------------------------------------------
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif 

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/ )
{
	m_wndView.SetFocus();
}

//----------------------------------------------------------------------------------------------------------------------
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if ( m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo ) )
		return TRUE;
	
	return CFrameWnd::OnCmdMsg( nID, nCode, pExtra, pHandlerInfo );
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CFrameWnd::OnLButtonUp(nFlags, point);
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnTragwerkKoordinatenbearbeiten() 
{
	CKoordWork myDlg;
	if ( IDOK == myDlg.DoModal() ) 
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnTragwerkMaterialbearbeiten() 
{
	CMaterialWork myDlg;
	if ( IDOK == myDlg.DoModal() ) 
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnTragwerkTragwerksinfo() 
{
	CTragwerkInfo	myDlg;
	if ( IDOK == myDlg.DoModal() ) 
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnTragwerkElementebearbeitenNumerisch() 
{
	CElementWork	myDlg;
	if ( IDOK == myDlg.DoModal() )
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnDateiFfnen() 
{
	CMainFrame::ReadProblem();
}


//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnOpen() 
{
	CMainFrame::ReadProblem();
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::ReadProblem()
{
	CString strPathName, strFileName;

	CFileDialog	MyFileDlg(TRUE, _T("dat"), NULL, 
		OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, 
		_T("Tragwerk (*.dat) |*.dat|Alle Dateien(*.*)|*.*||"));

	if ( MyFileDlg.DoModal() == IDOK ) 
	{
		strPathName = MyFileDlg.GetPathName();
		if ( !MyTragwerk.LoadTragwerk( strPathName ) )
		{
			std::string errMsg = LocalizationServer::get()->getText( "ErrMsg_ErrOpnFile" );
			AfxMessageBox( errMsg.c_str() );
		}
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnDateiSpeichern() 
{
	CMainFrame::WriteProblem();
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32800() 
{
	CMainFrame::WriteProblem();
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::WriteProblem()
{
	CFileDialog	MyFileDlg(FALSE, _T("dat"), NULL, 
		OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, _T("Tragwer(*.dat)|*.dat|Alle Dateien(*.*)|*.*||"));

	if ( IDOK == MyFileDlg.DoModal() ) 
	{
		CString strFileName = MyFileDlg.GetFileName();
		if (!MyTragwerk.SaveTragwerk( strFileName )) 
		{
			std::string errMsg = LocalizationServer::get()->getText( "ErrMsg_ErrSavFile" );
			AfxMessageBox( errMsg.c_str());
		}
		m_wndView.DrawALL();
	}
}

//---------------------------------------------------------------------------------------------------------------------
CStatusBar *CMainFrame::getStatusBar() const
{
	return m_pStatusBar;
}

//---------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnTragwerkLastenbearbeitenEinzellastenbearbeiten() 
{
	CEinzeleinwirkung myDlg;
	if (myDlg.DoModal()==IDOK) 
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnBerechnungBerechnungstarten() 
{
	CCalculate	myDlg;
	if (myDlg.DoModal()==IDOK) 
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButtoncalc() 
{
	CCalculate myDlg;
	if (myDlg.DoModal()==IDOK) 
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32778() 
{
	CRect	myclientRect;
	GetClientRect( myclientRect );
	if ( iKnNr > 0 ) 
	{
		const Core::d32 xDiff = g_NodeStack.getXMax() - g_NodeStack.getXMin();
		const Core::d32 yDiff = g_NodeStack.getYMax() - g_NodeStack.getYMin();
		const Core::d32 dScale = GetScale( myclientRect.Width(), myclientRect.Height(), xDiff, yDiff );
		
		MyTragwerk.ScaleSet(dScale);
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32780() 
{
	MyTragwerk.ScaleSub();
	m_wndView.DrawALL();
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32779() 
{
	MyTragwerk.ScaleAdd();	
	m_wndView.DrawALL();
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnAnsichtZoomZoomin()
{
	MyTragwerk.ScaleSub();
	m_wndView.DrawALL();	
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnAnsichtZoomZoomout() 
{
	MyTragwerk.ScaleAdd();	
	m_wndView.DrawALL();		
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32787() 
{
	CKoordWork myDlg;
	if (myDlg.DoModal()==IDOK) 
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32789() 
{
	CMaterialWork myDlg;
	if (myDlg.DoModal()==IDOK)
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32788() 
{
	CElementWork myDlg;
	if (myDlg.DoModal()==IDOK) 
	{
		m_wndView.DrawALL();
	}	
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32790() 
{
	CEinzeleinwirkung myDlg;

	if (myDlg.DoModal()==IDOK) 
	{
		m_wndView.DrawALL();
	}	
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32793() 
{
	bool bF = (!MyTragwerk.bMove);
	MyTragwerk.bMove = bF;
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnBerechnungErgebnisseDurchbiegung() 
{
	InzidenzStack Inz;
	double dS = MyTragwerk.dTScale;

	MyTragwerk.bDef = TRUE;
	m_wndView.DrawALL();
	m_wndView.DrawDeform(dS, SysLast1, Inz);
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnBerechnungErgebnisseMoment() 
{
	MyTragwerk.bQ	= FALSE;
	MyTragwerk.bN	= FALSE;
	MyTragwerk.bM	= TRUE;
	MyTragwerk.bDef	= FALSE;
	if (MyTragwerk.bCalc) 
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnBerechnungErgebnisseQuerkraft() 
{
	MyTragwerk.bQ	= TRUE;
	MyTragwerk.bN	= FALSE;
	MyTragwerk.bM	= FALSE;
	MyTragwerk.bDef	= FALSE;
	if (MyTragwerk.bCalc)
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnBerechnungErgebnisseLngskraft() 
{
	MyTragwerk.bQ	= FALSE;
	MyTragwerk.bN	= TRUE;
	MyTragwerk.bM	= FALSE;
	MyTragwerk.bDef = FALSE;
	if (MyTragwerk.bCalc)
	{
		m_wndView.DrawALL();
	}	
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnBerechnungErgebnisselschen() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32799() 
{
	InzidenzStack Inz;
	double dS = MyTragwerk.dTScale;
	m_wndView.DrawALL();
	if (MyTragwerk.bCalc)
	{
		MyTragwerk.bDef = TRUE;
		MyTragwerk.bN	= FALSE;
		MyTragwerk.bQ	= FALSE;
		MyTragwerk.bM	= FALSE;
		m_wndView.DrawALL();
		m_wndView.DrawDeform(dS, SysLast1, Inz);
	}
	else
	{
		std::string errMsg = LocalizationServer::get()->getText( "ErrMsg_NoRes" );
		AfxMessageBox( errMsg.c_str() );
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnAnsichtEinstellungen() 
{
	CEigenschaften myDlg;
	myDlg.DoModal();	
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnTragwerkLastenbearbeitenLinieneinwirkungerzeugen() 
{
	CStreckeneinwirkung myDlg;	
	myDlg.DoModal();
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButton32798() 
{
	CStreckeneinwirkung myDlg;	
	myDlg.DoModal();	
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnDateiNeu() 
{
	MyTragwerk.iNodeNr		= 0;
	MyTragwerk.iMaterialNr	= 0;
	MyTragwerk.iElementNr	= 0;
	MyTragwerk.iFG			= 0;
	MyTragwerk.iLagerKno	= 0;
	MyTragwerk.iLastNr		= 0;
	iEleNr					= 0;
	iKnNr					= 0;
	iMatNr					= 0;
	iLastNr					= 0;
	LastEingabe.iLastNr		= 0;
	VM.iAnz					= 0;
	VQ.iAnz					= 0;
	VN.iAnz					= 0;
	MyTragwerk.bCalc		= FALSE;
	MyTragwerk.bM			= FALSE;
	MyTragwerk.bQ			= FALSE;
	MyTragwerk.bN			= FALSE;
	MyTragwerk.bDef			= FALSE;
	MyTragwerk.dPl			= 0;

	g_NodeStack.clear();
	MaterialEingabe.DelList();
	ElementEingabe.DelList();
	VM.DelList();
	VQ.DelList();
	VN.DelList();
	Inz.DelList();
	m_wndView.DrawALL();
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnTragwerkMaterialbearbeitenMaterialerzeugen() 
{
	CMaterialWork	myDlg;
	if (myDlg.DoModal()==IDOK)
	{
		m_wndView.DrawALL();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnTragwerkMaterialbearbeitenMateriallschen() 
{
	CDelmat		myDlg;

	if (myDlg.DoModal()==IDOK)
		m_wndView.DrawALL();
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButtonmoment()
{
	MyTragwerk.bQ	= FALSE;
	MyTragwerk.bN	= FALSE;
	MyTragwerk.bM	= TRUE;
	MyTragwerk.bDef	= FALSE;
	if (MyTragwerk.bCalc)
	{
		m_wndView.DrawALL();
	}
	else
	{
		std::string errMsg = LocalizationServer::get()->getText( "ErrMsg_NoRes" );
		AfxMessageBox( errMsg.c_str() );
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButtonquer() 
{
	MyTragwerk.bQ	= TRUE;
	MyTragwerk.bN	= FALSE;
	MyTragwerk.bM	= FALSE;
	MyTragwerk.bDef	= FALSE;
	if (MyTragwerk.bCalc)
	{
		m_wndView.DrawALL();
	}
	else
	{
		std::string errMsg = LocalizationServer::get()->getText( "ErrMsg_NoRes" );
		AfxMessageBox( errMsg.c_str() );
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::OnButtonlaengs() 
{
	MyTragwerk.bQ	= FALSE;
	MyTragwerk.bN	= TRUE;
	MyTragwerk.bM	= FALSE;
	MyTragwerk.bDef	= FALSE;
	if (MyTragwerk.bCalc)
	{
		m_wndView.DrawALL();
	}
	else
	{
		std::string errMsg = LocalizationServer::get()->getText( "ErrMsg_NoRes" );
		AfxMessageBox( errMsg.c_str() );
	}
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::langSetupFileMenu( CMenu *pMenu )
{
	ASSERT( NULL != pMenu );

	std::string newStr( "" );
	
	newStr = LocalizationServer::get()->getText( "Menu_File_Title" );
	pMenu->ModifyMenu( FileMenuPos, MF_BYPOSITION, 0, newStr.c_str() );
	
	setLangStringInMenu( pMenu, "Menu_File_New", ID_DATEI_NEU );
	setLangStringInMenu( pMenu, "Menu_File_Open", ID_DATEI_FFNEN );
	setLangStringInMenu( pMenu, "Menu_File_Save", ID_DATEI_SPEICHERN );
 	setLangStringInMenu( pMenu, "Menu_File_SaveAs", ID_DATEI_SPEICHERNUNTER );
 	
	newStr = LocalizationServer::get()->getText( "Menu_File_Export" );
	pMenu->ModifyMenu( ExportMenuPos, MF_BYPOSITION, 0, newStr.c_str() );

 	setLangStringInMenu( pMenu, "Menu_File_ExportAscii", ID_DATEI_EXPORT_ASCII );
 	setLangStringInMenu( pMenu, "Menu_File_Print", ID_DATEI_DRUCKEN );
	
 	setLangStringInMenu( pMenu, "Menu_File_Quit", ID_APP_EXIT );
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::langSetupStructureMenu( CMenu *pMenu )
{
	ASSERT( NULL != pMenu );

	std::string newStr( "" );

	newStr = LocalizationServer::get()->getText( "Menu_Structure_Title" );
	pMenu->ModifyMenu( StructureMenuPos, MF_BYPOSITION, 0, newStr.c_str() );

	
	newStr = LocalizationServer::get()->getText( "Menu_Structure_Coord" );
	pMenu->ModifyMenu( NodesMenuPos, MF_BYPOSITION, 0, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Structure_Coord_Numeric" );
	pMenu->ModifyMenuA( ID_TRAGWERK_KOORDINATENBEARBEITEN, 0, ID_TRAGWERK_KOORDINATENBEARBEITEN, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Structure_Material_Input" );
	pMenu->ModifyMenuA( ID_TRAGWERK_MATERIALBEARBEITEN_MATERIALERZEUGEN, 0, ID_TRAGWERK_MATERIALBEARBEITEN_MATERIALERZEUGEN, newStr.c_str() );
	
	newStr = LocalizationServer::get()->getText( "Menu_Structure_Material_Delete" );
	pMenu->ModifyMenuA( ID_TRAGWERK_MATERIALBEARBEITEN_MATERIALLSCHEN, 0, ID_TRAGWERK_MATERIALBEARBEITEN_MATERIALLSCHEN, newStr.c_str() );
	
	newStr = LocalizationServer::get()->getText( "Menu_Structure_Elemnts_Numeric" );
	pMenu->ModifyMenuA( ID_TRAGWERK_ELEMENTEBEARBEITEN_NUMERISCH, 0, ID_TRAGWERK_ELEMENTEBEARBEITEN_NUMERISCH, newStr.c_str() );
	
	newStr = LocalizationServer::get()->getText( "Menu_Structure_Loads_PointLoads" );
	pMenu->ModifyMenuA( ID_TRAGWERK_LASTENBEARBEITEN_EINZELLASTENBEARBEITEN, 0, ID_TRAGWERK_LASTENBEARBEITEN_EINZELLASTENBEARBEITEN, newStr.c_str() );
	
	newStr = LocalizationServer::get()->getText( "Menu_Structure_Loads_LineLoads" );
	pMenu->ModifyMenuA( ID_TRAGWERK_LASTENBEARBEITEN_LINIENEINWIRKUNGERZEUGEN, 0, ID_TRAGWERK_LASTENBEARBEITEN_LINIENEINWIRKUNGERZEUGEN, newStr.c_str() );
	
	newStr = LocalizationServer::get()->getText( "Menu_Structure_Info" );
	pMenu->ModifyMenuA( ID_TRAGWERK_TRAGWERKSINFO, 0, ID_TRAGWERK_TRAGWERKSINFO, newStr.c_str() );
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::langSetupComputationMenu( CMenu *pMenu )
{
	ASSERT( NULL != pMenu );
	
	std::string newStr( "" );

	newStr = LocalizationServer::get()->getText( "Menu_Computation_Title" );
	pMenu->ModifyMenu( CalcMenuPos, MF_BYPOSITION, 0, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Computation_StartCalc" );
	pMenu->ModifyMenuA( ID_BERECHNUNG_BERECHNUNGSTARTEN, 0, ID_BERECHNUNG_BERECHNUNGSTARTEN, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Computation_ResultDeform" );
	pMenu->ModifyMenuA( ID_BERECHNUNG_ERGEBNISSE_DURCHBIEGUNG, 0, ID_BERECHNUNG_ERGEBNISSE_DURCHBIEGUNG, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Computation_ResultMoment" );
	pMenu->ModifyMenuA( ID_BERECHNUNG_ERGEBNISSE_MOMENT, 0, ID_BERECHNUNG_ERGEBNISSE_MOMENT, newStr.c_str() );
	
	newStr = LocalizationServer::get()->getText( "Menu_Computation_ResultShearForce" );
	pMenu->ModifyMenuA( ID_BERECHNUNG_ERGEBNISSE_QUERKRAFT, 0, ID_BERECHNUNG_ERGEBNISSE_QUERKRAFT, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Computation_ResultNormalForce" );
	pMenu->ModifyMenuA( ID_BERECHNUNG_ERGEBNISSE_LNGSKRAFT, 0, ID_BERECHNUNG_ERGEBNISSE_LNGSKRAFT, newStr.c_str() );

	newStr = LocalizationServer::get()->getText( "Menu_Computation_DelResults" );
	pMenu->ModifyMenuA( ID_BERECHNUNG_ERGEBNISSELSCHEN, 0, ID_BERECHNUNG_ERGEBNISSELSCHEN, newStr.c_str() );
}

//----------------------------------------------------------------------------------------------------------------------
bool CMainFrame::setLangStringInMenu( CMenu *pMenu, const std::string &rTag, UINT id )
{
	if ( rTag.empty() )
		return false;
	
	std::string newStr = LocalizationServer::get()->getText( rTag );
	if ( !pMenu->ModifyMenuA( id, 0, id, newStr.c_str() ) )
	{
		showLastError( "CMainFrame::setLangString" );
		return false;
	}

	return true;
}

//----------------------------------------------------------------------------------------------------------------------
void CMainFrame::showLastError(LPTSTR lpszFunction)
{
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox( (LPCTSTR)lpDisplayBuf ); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}
