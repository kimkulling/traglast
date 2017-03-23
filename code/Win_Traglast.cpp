/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : WinTraglast V0.2
// Desc.       : Traglastberechnungen unter Win32 (mit MFC), Entwicklungsfassung
// Author      : Kim Kulling
// Last mod.   : 13.12.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Win_Traglast.h"
#include "MainFrm.h"
#include "NodeStack.h"
#include "LocalizationServer.h"
#include "EnviromentServer.h"
#include "GUITextUtils.h"
#include "Logger.h"
#include "OSUtils.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace FEStructure;
using namespace Localization;
using namespace Core;
using namespace GUI;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Local and global definitions of vars and instances
/////////////////////////////////////////////////////////////////////////////////////////////////
int				iKnNr		= 0;	// Anzahl Knoten
int				iMatNr		= 0;	// Anzahl Material
int				iEleNr		= 0;	// Anzahl Elemente
int				iLastNr		= 0;	// Anzahl Lasten
int				iRandNr		= 0;	// Anzahl Randbedingungen
int				iLagerKno	= 0;	// Anzahl der gestützten Lagerknoten
int				iSysLastNr	= 0;	// Anzahl SysLast (für die Berechnung)
int				iGesamtFG	= 0;	// Anzahl der Unbekannter
struct			tm *pTimeNow;		// Momentanes Datum
Tragwerk		MyTragwerk;			// Klasse zum Sichern von allgemeinen Tragwerksinformationen
MaterialStack	MaterialEingabe;	// Klasse für Materialien
NodeStack		g_NodeStack;		// Klasse für Koordinaten
ElementStack	ElementEingabe;		// Klasse für Elemente
LastStack		LastEingabe;		// Klasse für Lasten
InzidenzStack	Inz;				// Klassen für Inzidenz-Tabellen
Vektor			SysSteif;			// Klasse zum Speicher der Systemsteigigkeitsmatrix
Vektor			SysLast1;			// Vektor für Systemlast-Vektor
Vektor			EleMatVektor;		// Vektor zum Sichern der Materialkennwerte
PlotStack		DeformPlot, MomentPlot, QuerPlot, LaengsPlot;
Vektor			VM, VQ, VN;

/////////////////////////////////////////////////////////////////////////////
// CWin_TraglastApp

BEGIN_MESSAGE_MAP(CWin_TraglastApp, CWinApp)
	//{{AFX_MSG_MAP(CWin_TraglastApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWin_TraglastApp Konstruktion
CWin_TraglastApp::CWin_TraglastApp()
{
	// empty	
}

CWin_TraglastApp::~CWin_TraglastApp()
{
	LocalizationServer::kill();
	EnviromentServer::kill();
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CWin_TraglastApp-Objekt

CWin_TraglastApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWin_TraglastApp Initialisierung

BOOL CWin_TraglastApp::InitInstance()
{
	AfxEnableControlContainer();

	SetRegistryKey( _T( "Traglast for Windows" ) );
	EnviromentServer *pEnviroment = EnviromentServer::create();
	assert( NULL != pEnviroment );
	if ( NULL == pEnviroment )
	{
		Core::Logger::get()->fatal( "No enviroment server instance found." );
		return FALSE;
	}
	
	TCHAR szBuffer[MAX_PATH];
	::GetModuleFileName( NULL, szBuffer, MAX_PATH );
	

	std::string stdApp( szBuffer ), absPath;
	OS::OSUtils::separatePath( stdApp, absPath );
	OS::OSUtils::attachFileSeparator( absPath );
	
	std::string localizationPath = absPath + "config\\localization";
	OS::OSUtils::attachFileSeparator( localizationPath );

	const std::string filename = "ger_localization.xml";
	Core::Logger::get()->info( "path: " + localizationPath );
	LocalizationServer *pServer = LocalizationServer::create( localizationPath );
	assert( NULL != pServer );
	if ( NULL == pServer )
	{
		Core::Logger::get()->fatal( "No localisation server instance found." );
		return FALSE;
	}
	std::string absFileName = localizationPath + filename;
	if ( !pServer->load( absFileName ) )
	{
		Core::Logger::get()->error( "Cannot parse localization-file " + filename );
	}

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// Rahmen mit Ressourcen erstellen und laden
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	// Das einzige Fenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// CWin_TraglastApp Nachrichten-Handler

/////////////////////////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialog für Info über Anwendung

/////////////////////////////////////////////////////////////////////////////////////////////////
// Klasse		: CAboutDlg
// Beschreibung : Initialisiert den About-Dialog, die Standart-Methoden werden inline 
//					implementiert
/////////////////////////////////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogdaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Überladungen für virtuelle Funktionen, die vom Anwendungs-Assistenten erzeugt wurden
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
private:
	CButton m_ButtonOK;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_ButtonOK);
}

BOOL CAboutDlg::OnInitDialog()
{
	if ( !CDialog::OnInitDialog() ) 
		return FALSE;

	std::string id = "AboutDlg_Title";
	GUITextUtils::setWindowTextPerId( this, id );

	id = "DialogOK";
	GUITextUtils::setWindowTextPerId( &m_ButtonOK, id );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////////////////////////
// Anwendungsbefehl zum Ausführen des Dialogfelds
/////////////////////////////////////////////////////////////////////////////////////////////////
void CWin_TraglastApp::OnAppAbout()
{
	CBitmap   Bitmap;
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// CWin_TraglastApp-Nachrichtenbehandlungsroutinen
/////////////////////////////////////////////////////////////////////////////////////////////////
void CAboutDlg::OnBnClickedOk()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	OnOK();
}
