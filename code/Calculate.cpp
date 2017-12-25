//----------------------------------------------------------------------------------------------------------------------
///	\file		Calculate.cpp
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
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Win_Traglast.h"
#include "Calculate.h"
#include "CalcOption.h"
#include "BandOp.h"
#include "SystemStiffnessBuilder.h"
#include "Logger.h"
#include "LocalizationServer.h"
#include "GUITextUtils.h"

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
// Lokale und globale Variablen und Klassen-Deklarationen
/////////////////////////////////////////////////////////////////////////////////////////////////
bool		bPosDef = TRUE;
int			iIter, iKn;

extern int	iKnNr, iMatNr, iEleNr, iRandNr, iGesamtFG;

extern Tragwerk			MyTragwerk;
extern NodeStack		g_NodeStack;
extern MaterialStack	MaterialEingabe;
extern ElementStack		ElementEingabe;
extern LastStack		LastEingabe;
extern Vektor			SysVektor, K, EleMatVektor, SysLast1;
extern PlotStack		DeformPlot, MomentPlot, QuerPlot, LaengsPlot;
extern Vektor			VM, VQ, VN;
extern InzidenzStack	Inz;


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: CCalculate::CCalculate()
// Beschreibung	: Konstruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
CCalculate::CCalculate(CWnd* pParent ) :
	CDialog(CCalculate::IDD, pParent),
	m_iBand( _T( "0" ) ),
	m_strFG( _T("0") ),
	m_strKnAnz( _T("0") ),
	m_strMem( _T("0") ),
	m_strEleAnz( _T("0") ),
	m_strProcess( _T("") )
{
	// empty
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: CCalculate::DoDataExchange()
// Beschreibung	: wird zum Austausch von Daten benutzt
/////////////////////////////////////////////////////////////////////////////////////////////////
void CCalculate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalculate)
	DDX_Text(pDX, IDC_BANDBREITE, m_iBand);
	DDX_Text(pDX, IDC_FG, m_strFG);
	DDX_Text(pDX, IDC_KNANZ, m_strKnAnz);
	DDX_Text(pDX, IDC_MEM, m_strMem);
	DDX_Text(pDX, IDC_ELEANZ, m_strEleAnz);
	DDX_Text(pDX, IDC_PROCESS, m_strProcess);
	//}}AFX_DATA_MAP

	DDX_Control( pDX, IDOK, m_ButtonOK );
	DDX_Control( pDX, IDCANCEL, m_ButtonCancel );
	DDX_Control( pDX, IDC_BUTTONOPTIONS, m_ButtonOptions );
	DDX_Control( pDX, IDC_BUTTONCLOSE, m_ButtonClose );
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Definition der Message-Map für den Programmteil Calculate.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CCalculate, CDialog)
	//{{AFX_MSG_MAP(CCalculate)
	ON_BN_CLICKED(IDC_BUTTONCLOSE, OnButton2)
	ON_BN_CLICKED(IDC_BUTTONOPTIONS, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//----------------------------------------------------------------------------------------------------------------------
//	Language setup.
BOOL CCalculate::OnInitDialog()
{
	if ( !CDialog::OnInitDialog() )
		return FALSE;

	Localization::LocalizationServer *pLocalizationServer = Localization::LocalizationServer::get();
	assert( NULL != pLocalizationServer );
	
	std::string id = "CalcDialogTitle";
	GUITextUtils::setWindowTextPerId( this, id );

	id = "DialogOK";
	GUITextUtils::setWindowTextPerId( &m_ButtonOK, id );
	
	id = "DialogCancel";
	GUITextUtils::setWindowTextPerId( &m_ButtonCancel, id );
	
	id = "CalcDialogOptionsButton";
	GUITextUtils::setWindowTextPerId( &m_ButtonOptions, id );
	
	id = "CalcDialogCloseButton";
	GUITextUtils::setWindowTextPerId( &m_ButtonClose, id );

	GUITextUtils::setLocalizedText( this, IDC_FORTSCHRITT, "CalcDialog_CalcState" );
	GUITextUtils::setLocalizedText( this, IDC_CALCPROGRESS, "CalcDialog_Progess" );
	GUITextUtils::setLocalizedText( this, IDC_BERECHNUNG, "CalcDialog_Calc" );
	GUITextUtils::setLocalizedText( this, IDC_CURRENTPROCESS, "CalcDialog_Process" );
	GUITextUtils::setLocalizedText( this, IDC_BANDWIDTH, "CalcDialog_BandWidth" );
	GUITextUtils::setLocalizedText( this, IDC_MAXDOF, "CalcDialog_MaxDOF" );
	GUITextUtils::setLocalizedText( this, IDC_NODES, "CalcDialog_Nodes" );
	GUITextUtils::setLocalizedText( this, IDC_ELEMENTS, "CalcDialog_Elements" );
	GUITextUtils::setLocalizedText( this, IDC_MEMORY, "CalcDialog_Memory" );

	return TRUE;
}


//----------------------------------------------------------------------------------------------------------------------
// Methode		: CCalculate::OnOK()
// Beschreibung	: Methode zur Berechnung des Tragwerkes
//----------------------------------------------------------------------------------------------------------------------
void CCalculate::OnOK() 
{
	CString strError, strCalcParam, strLogName;
	BOOL    bFehler = TRUE, bPlastC = FALSE;
	double  dK1[2], dWert, dXdef(0.0), dYdef(0.0), dPl = 0, dT1, dT2;
	int     iEleIndex, iFGKno, iEleKn, iLagerKno, iPos, iLastNr = 0, iKn1, iEleNum,
			iCoordNum, iI1, iI2;
	Vektor  LastCalc, MyLager, SysSteif, Temp, VTemp, K, Erg, Last2;
    // Get the 
	CProgressCtrl*	pProgressCtrl = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
	UpdateData(TRUE);

	// Lese Element- und Last-Anzahl 
	iEleNr    = ElementEingabe.numberOfElements();
	iLastNr   = LastEingabe.iLastNr;
	iEleNum   = 0;
	iCoordNum = 0;

	// Überprüfung der Eingabe
	if (MyTragwerk.iCalcOption==0) 
	{
		std::string errMsg = LocalizationServer::get()->getText( "StatusTxt_Nodes" );
		strError.Format("%s", errMsg.c_str() );
		bFehler = FALSE;
	}

	if ((iKnNr==0) || (iEleNr==0) || (iMatNr==0) || (iLastNr==0)) 
	{
		std::string errMsg = LocalizationServer::get()->getText( "ErrMsg_StrucIncompl" );
		strError.Format( "%s", errMsg.c_str() );
		bFehler	= FALSE;
	}

	// Wenn Eingabe in Ordnung
	if (bFehler) 
	{
		dT1	= GetTickCount();
		// Berechnung der Gesamtunbekannten		
		iFGKno		= 3;		// Freiheitsgrade der Elemene = 3
		iEleKn		= 2;		// 2 Elementknoten vorhanden
		iLagerKno	= MyTragwerk.iLagerKno;
		
		if (MyTragwerk.iCalcOption==1) 
		{
			pProgressCtrl->SetPos(40);

			Erg = LinCalc(LastEingabe, iEleNr, iLastNr, iEleKn, 
				iFGKno, iLagerKno, ElementEingabe);		

			pProgressCtrl->SetPos(100);
			
			// Berechnung der Schnittkräfte
		}
		if (MyTragwerk.iCalcOption==2) 
		{
			dT1 = GetTickCount();
			if (Inz.iAnz!=0)
				Inz.DelList();

			// calculating plast-load
			Erg = PlastCalc();	
			if (!bPosDef) 
			{
				dPl = MyTragwerk.dPl;
				bPlastC = TRUE;
				std::string msg = LocalizationServer::get()->getText( "Msg_LimitLoad" );
				strCalcParam.Format( "%s %lf", msg.c_str(), dPl );
			}
		}
		
		if (bPosDef||bPlastC) 
		{
			// Set the status to 0
			pProgressCtrl->SetPos(0);
			// Calculating cuttingforces
			SchnittKraft(iEleKn, iFGKno, Erg);
			
			MyTragwerk.bCalc = TRUE;	
			
			pProgressCtrl->SetPos(100);
		
			// Berechnung der Koordinaten für den Deform-Plot
			iPos      = 0;
			iCoordNum = g_NodeStack.getNumberOfNodes();
			for (iI1=1; iI1<=iCoordNum; iI1++) 
			{
				for (iI2=1; iI2<=iFGKno; iI2++) 
				{
					iPos++;
					if (iI2==1) 
					{
						dXdef = Erg.readVektor(iPos);
						if (dXdef<DEFNULL) 
							dXdef=0;
					}
					if (iI2==2) 
					{	
						dYdef = Erg.readVektor(iPos);
						if (dYdef<DEFNULL) 
							dYdef = 0;
					}
				}
				NodeStack::NodeDef node;
				g_NodeStack.getNode( iI1, node );
				double x = 0.0,y = 0.0;
				node.getPosition( x, y );
				DeformPlot.AddPlotKoord( iI1, x, y, dXdef, dYdef, 0 );
			}
			pProgressCtrl->SetPos(60);
			
			// Berechnung der Koordinaten für die Schnittkraftplots
			iPos = 0;
			iEleNum = ElementEingabe.numberOfElements();
			for (iEleIndex=1; iEleIndex<=iEleNum; iEleIndex++) 
			{
				for (iI1=1; iI1<=iEleKn; iI1++) 
				{
					iPos++;
					iKn1   = ElementEingabe.ReadElement(iEleIndex, iI1, ElementEingabe.numberOfElements() );
					
					NodeStack::NodeDef node;
					g_NodeStack.getNode( iKn1, node );
					node.getPosition( dK1[0], dK1[1] );
					dWert  = VM.readVektor(iPos);

					// Set moment at node for rendering
					MomentPlot.AddPlotKoord(iPos, dK1[0], dK1[1], 0, 0, dWert);
					dWert	= VQ.readVektor(iPos);

					// Set shear force at node for rendering
					QuerPlot.AddPlotKoord(iPos, dK1[0], dK1[1], 0, dWert, 0);
					dWert	= VN.readVektor(iPos);
					
					// Set normal force at node for rendering
					LaengsPlot.AddPlotKoord(iPos, dK1[0], dK1[1], dWert, 0, 0);
				}
			}
			
			pProgressCtrl->SetPos(100);
		}
		
		dT2 =	GetTickCount();

		std::string msg = LocalizationServer::get()->getText( "Msg_CompTime" );
		double diff = dT2 - dT1;
		strCalcParam.Format("%s %lf",msg.c_str(), diff );
		AfxMessageBox( strCalcParam );
	}	
	else
	{
		AfxMessageBox( strError );
	}
}

//----------------------------------------------------------------------------------------------------------------------
// On close request a message box will be shown, if you want to save the results.
void CCalculate::OnButton2() 
{
	if (MyTragwerk.bCalc) 
	{
		std::string msg = LocalizationServer::get()->getText( "Msg_SaveRes" );
		Core::i32 iMsg = AfxMessageBox( msg.c_str(), MB_OKCANCEL );
		if ( iMsg==IDOK )
		{
			CCalculate::SaveData();
		}
		else
		{
			CDialog::OnOK();
		}
	}
	CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: CCalculate::SaveData()
// Beschreibung	: Speichert die Ergebnisse in eine Datei vom Typ '*.erg'
/////////////////////////////////////////////////////////////////////////////////////////////////
inline void CCalculate::SaveData()
{
	CString		strPathName;

	CFileDialog	MyFileDlg(FALSE, _T("erg"), NULL, 
				OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, _T("Tragwer(*.erg)|*.erg|Alle Dateien(*.*)|*.*||"));
	if (MyFileDlg.DoModal()==IDOK) 
	{
		strPathName = MyFileDlg.GetPathName();
		MyTragwerk.SaveCalc(SysLast1, VM, VQ, VN, strPathName );
		CDialog::OnOK();
	}
	else
		CDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: CCalculate::OnButton1() 
// Beschreibung	: Öffnet den Dialog CCalcOption, mit dem man die Berechnungsoptionen anwählen kann
/////////////////////////////////////////////////////////////////////////////////////////////////
inline void CCalculate::OnButton1() 
{
	CCalcOption	myDlg;
	myDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: CCalculate::LinCalc(int iEleNr, int iLastNr, int iEleKn, 
//					int iFGKno, int iLagerKno)
// Beschreibung	: Berechnet die Durchbiegungen nach dem linearen Ansatz
// Parameter
// iEleNr		: Anzahl der Elemente
// iLastNr		: Anzahl der Lasten
// iEleKn		: Anzahl der Elementknoten
// iFGKno		: Freiheitsgrade pro Knoten
// iLagerKno	: Anzahl der gelagerten Knoten
// Rückgabewert	: Durchbiegung im Vektor Erg
/////////////////////////////////////////////////////////////////////////////////////////////////
inline Vektor CCalculate::LinCalc(LastStack Last, int iEleNr, int iLastNr, int iEleKn, 
									   int iFGKno, int iLagerKno, ElementStack Element)
{
	Vektor	Erg, K, MyLager, LastCalc, Error, SysSteif;
	CString	strCalcParam, strError, strErrorTitel;
	BOOL	bFlag = TRUE, bError = TRUE;
	int		iRange = 0, iEleIndex, iBand = 0, iFGEle, iRam = 0, iEle[5], iEleNum;
	double	dK1[2], dK2[2], dMat[4];

	// Initialisierung des Error-Vektors
	Error.initVector(1);
	
	// Anzeige der allgemeinen Tragwerksinformationen
	strCalcParam.Format("%d", g_NodeStack.getNumberOfNodes() );
	SetDlgItemText(IDC_KNANZ, strCalcParam);
	strCalcParam.Format( "%d", ElementEingabe.numberOfElements() );
	SetDlgItemText(IDC_ELEANZ, strCalcParam);
	strCalcParam.Format("Deform");
	SetDlgItemText(IDC_PROCESS, strCalcParam);

	// Berechnung der grundlegenden Freiheitsgrade für die lineare BErechnung
	MyTragwerk.iFG = iFGKno;
	iGesamtFG      = iKnNr  * iFGKno;
	iFGEle         = iEleKn * iFGKno;
	iEleNum        = ElementEingabe.numberOfElements();

	// Erstellung der Inzidenz-Matrix
	Inz = MakeInzidenz (iEleNr, iEleKn, ElementEingabe, Inz);
	
	// Berechnung der Bandbreite der Steifigkeitsmatrix
	Solver::BandOp band( iEleKn, iEleNr, Inz, iFGKno );
	if ( band.start() )
		iBand = band.getBandWitdh();
	else
	{
		Logger::get()->error( "Error while calculating band width!" );
		return Error;
	}
	
	// Anzeige der Bandbreite und minimaler Freiheitsgrade
	strCalcParam.Format("%d", iBand);
	SetDlgItemText(IDC_BANDBREITE, strCalcParam);
	strCalcParam.Format("%d", iFGKno);
	SetDlgItemText(IDC_FG, strCalcParam);
	
	// Berechnung der benötigten Matrizeneinträge zur Erstellung der Steifigkeitsmatrix
	iRange = iGesamtFG * iBand;
	
	// Berechnung und Anzeige des belegten Speichers im Dialog
	iRam = (iGesamtFG + iRange) * sizeof(double) ;
	iRam = (int) iRam / 1024;

	strCalcParam.Format("%d", iRam);
	SetDlgItemText(IDC_MEM, strCalcParam);

	// Vorbereitung der Systemsteifigkeitsmatrix
	SysSteif.initVector(iRange);
	
	// Beginn des Tragwerkszusammenbaues
	Logger::get()->info( "Begin building stiffness-matrix" );

	for (iEleIndex=1; iEleIndex<iEleNum+1; iEleIndex++) 
	{
		// Read element-datas
		GetElement(iEleIndex, ElementEingabe, iEle);
		
		// Read coords
		GetKoord(iEleIndex, g_NodeStack, dK1, dK2);

		// Read actual needed material into element
		GetMaterial(iEle[2], MaterialEingabe, dMat);

		// Erstelle Elementsteifigkeitsmatrix für das momentan berechnete Element
		// Wenn keine Gelenke vorhanden
		switch (iEle[3]) 
		{
		case FACHWERK:	// A fachwerk-element
			K = Fachwerk(dMat[0], dMat[1], dK1[0], dK2[0], dK1[1], dK2[1], K);
			break;

		case 2: // Wenn Balkenelement
			K = Balken(dMat[0], dMat[1], dMat[2], dK1[0], dK2[0], dK1[1], dK2[1]);
			break;

		case 3: // Wenn Balkenelement mit Gelenk links
			K = BalkenGelenk(1, dK1[0], dK2[0], dK1[1], dK2[1], dMat[0], dMat[1], dMat[2]);
			break;

		case 4: // Wenn Balkenelement mit Gelenk rechts
			K = BalkenGelenk(2, dK1[0], dK2[0], dK1[1], dK2[1], dMat[0], dMat[1], dMat[2]);
			break;

		default: // If an error occurs
			strErrorTitel.Format("Error!");
			strError.Format("Fehler beim Identifizieren der Elemente");
			bError = FALSE;
			break;
		}

		// Baue die Elementsteigigkeitmatrix in die Systemsteifigkeitsmatrix ein
		if (bError)
		{
			//Solver::SystemStiffnessBuilder systemBuilder( iEleIndex, iEleKn, iGesamtFG, iBand, Inz, K, SysSteif );
			//bool result = systemBuilder.start();
			//SysSteif = systemBuilder.getSystemStiffness();
			SysSteif = SystemAuf(iEleIndex, iFGKno, iEleKn, iBand, Inz, K, SysSteif);
		}
		else 
			AfxMessageBox(strError);
	} 
	Logger::get()->info( "Finish building stiffness-matrix" );

	// Die Stützungsinformationen werden erstellt
	Logger::get()->info( "Begin building boundary" );
	MyLager = MakeStuetzStack(MyLager, g_NodeStack);

	// Die Stützungen werden in die Systemsteifigkeitsmatrix eingebaut
	SysSteif = Stuetzung( iLagerKno, iFGKno, iBand, MyLager, SysSteif );
	Logger::get()->info( "Finish building boundary" );

	// Durchführung der Links-Rechts-Zerlegung nach Cholesky
	Logger::get()->info( "Begin cholescy-triangulation" );	
	SysSteif = Cholesky(iGesamtFG, iBand, SysSteif );
	Logger::get()->info( "Finish cholescy-triangulation" );

	// Wenn die Steifigkeitsmatrix singulär
	if (!bPosDef) {
		strError.Format("Steifigkeitsmatrix singulär!");
		AfxMessageBox(strError);

		bFlag = FALSE;
	}
	
	// Wenn Steifigkeitsmatrix nicht singulär
	if (bFlag) 
	{
		// Erstellung des Lastvektors
		LastCalc = MakeLastVektor(Last, iFGKno);	
		
		// Deklaration des Belastungsvektors für die globalen Knotenlasten
		if (SysLast1.Size()==0)
			SysLast1.initVector(iGesamtFG);
		
		// Erstellung des Belastungsvektors für die globalen Knotenlasten
		SysLast1 = Knotenlast(iLastNr, iFGKno, LastCalc, SysLast1);
		
		// Lösung des Gleichungssystems
		Logger::get()->info( "Begin substitution" );
		Erg = VorRueck (iGesamtFG, iBand, SysSteif, SysLast1);		
		Logger::get()->info( "Finish substitution" );

		return Erg;
	}

	return Error;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: CCalculate::SchnittKraft(int iEleKn, int iFGKno, VektorStack Erg)
// Beschreibung	: Errechnet die Schnittkräfte aus dem Verformungsvektor
// Parameter
// iEleKn		: Anzahl der Elementknoten
// iFGKno		: Maximale Freiheitsgrade eines Knotens
// Erg			: Lösungsvektor der linearen Berechnung 
/////////////////////////////////////////////////////////////////////////////////////////////////
inline void CCalculate::SchnittKraft(int iEleKn, int iFGKno, Vektor Erg)
{
	BOOL           bFlag = FALSE;
	int            iPos, iEleIndex, iI1, iWert, iEle[5];
	double         dK1[2], dK2[2], dWert = 0, dMat[4], dM[2], dQ[2], dN[2], dDef[6];
	CString        strCalcParam;
	Vektor         Temp, VTemp;
	CProgressCtrl* pProgressCtrl = (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);

	const Core::i32 iEleNr = ElementEingabe.numberOfElements();

	// Beginn der Berechnung der Schnittkräfte
	strCalcParam.Format("Force");
	SetDlgItemText(IDC_PROCESS, strCalcParam);
	Temp.initVector(iFGKno * iEleKn);
	iI1 = iEleNr * iEleKn;			
		
	// Initialisierung der Schnittkraft-Vektoren VM, VQ, VN
	VM.initVector(iI1);
	VQ.initVector(iI1);
	VN.initVector(iI1);
	VTemp.initVector(2);
		
	iPos = 0;
		
	// Berechnung der Schnittkräfte, wenn Deformationen bereits berechnet
	pProgressCtrl->SetPos(20);
	
	if (bPosDef) 
	{
		for (iEleIndex=1; iEleIndex<=iEleNr; iEleIndex++) 
		{
			// Ermittlung der Elementdaten
			GetElement(iEleIndex, ElementEingabe, iEle);

			// Ermittlung der Koordinaten
			GetKoord(iEleIndex, g_NodeStack, dK1, dK2);

			// Ermittlung der Materialdaten
			GetMaterial(iEle[2], MaterialEingabe, dMat);

			// Ermittlung der benötigten Verformungsparameter
			ElementDef(iEleIndex, iEleKn, iFGKno, Inz, Erg, dDef);
				
			// Ermittlung der Länge des Elementes
			dWert = dL2D((dK2[0] - dK1[0]), (dK2[1] - dK1[1]));
		
			// Berechnung der Momente und Querkräfte
			switch (iEle[3]) 
			{
			case FACHWERK:	// Wenn Element Fachwerkstab
				break;

			case NOGEL:		// Wenn Element beidseitig starr angeschlossener Balken
				CalcMoment(dDef, dK1, dK2, dWert, dMat[0], dMat[2], dM);
				CalcQuer(dDef, dK1, dK2, dWert, dMat[0], dMat[2], dQ);
				bFlag = TRUE;
				break;

			case GELLEFT:	// Wenn Element links gelenkig angeschlossener Balken
				CalcMomentGelenk(dDef, dK1, dK2, dWert, dMat[0], dMat[2], dM, 3);
				CalcQuerGelenk(dDef, dK1, dK2, dWert, dMat[0], dMat[2], dQ, 3);
				bFlag = TRUE;
				break;

			case GELRIGHT:	// Wenn element rechts gelenkig angeschlossener Balken
				CalcMomentGelenk(dDef, dK1, dK2, dWert, dMat[0], dMat[2], dM, 4);
				CalcQuerGelenk(dDef, dK1, dK2, dWert, dMat[0], dMat[2], dQ, 4);
				bFlag = TRUE;
				break;	

			default:
				{
					// In case of an error
					std::string errMsg = LocalizationServer::get()->getText( "ErrMsg_ErrCuttingForce" );
					AfxMessageBox( errMsg.c_str() );
					bFlag = FALSE;
				}
				break;
			}
		
			// Berechnung der Laengskraefte
			CalcLaeng(dDef, dK1, dK2, dWert, dMat[0], dMat[1], dN);				
		
			// Kopieren der Schnittkräfte in die vorbereiteten Vektoren VM, VQ und VN
			if (bFlag) 
			{
				for (iI1=1; iI1<=iEleKn; iI1++) 
				{
					iPos++;
					VM.setVektor(iPos, dM[iI1-1]);
					VQ.setVektor(iPos, dQ[iI1-1]);	
					VN.setVektor(iPos, dN[iI1-1]);
				}
			}
	
			// Anzeige des Status der Berechnung
			iWert = Math::round( ( iI1 * 100) / iEleNr );
			pProgressCtrl->SetPos(iWert);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: CCalculate::PlastCalc()
// Beschreibung	: Die plastische Grenzlast wird durch schrittweise elastische Berechnung
//					ermittelt.
// Rückgabewert	: Berechnete platische Grenzlast
/////////////////////////////////////////////////////////////////////////////////////////////////
inline Vektor CCalculate::PlastCalc()
{
	BOOL			bFlag = TRUE, bLager, bMdef = FALSE, bError = FALSE, bSet = TRUE; 
	register int	iI1, iI2, iI3, iKnNr;
	int				iPos, iEle[5], iEleKno, iFGKno, iPosGel, iAnz = 0, iLagerArt[ 3 ]; 
	double			dMax, *dMpl, dDiff, dW, dK1[2], dK2[2], dM[2], dMat[5], dL,
					dDef[6], dTrans[6], dPl[3], dCx, dCy;
	Vektor			Erg, ErgTemp, Temp, Vtemp, Knoten, Err;
	LastStack		myLast, PlastLast, CalcLast;

	CString			strFileName, strPathName, strCalcParam, strCalcError;

	// If any results already there ask for saving them
	if ( MyTragwerk.bCalc ) 
	{
		std::string msg = LocalizationServer::get()->getText( "Msg_SaveRes" );
		Core::i32 iMsg = AfxMessageBox( msg.c_str(), MB_OKCANCEL );
		if ( IDOK == iMsg )
		{
			CCalculate::SaveData();		
		}
	}

	// Initialisation of data and storing of main-informations
	dMpl = new double[MaterialEingabe.iAnz];
	MyTragwerk.dPl = 0;
	iEleKno = 2;
	iFGKno	= 3;

	// Init of temporary vectors
	Vtemp.initVector( ElementEingabe.numberOfElements() * iEleKno );
	
	// calculation the loading for interation
	myLast   = GetIterLast(LastEingabe);
	CalcLast = myLast;

	// Start of calculation
	for (iI1=0; iI1<MaterialEingabe.iAnz; iI1++)
		dMpl[iI1] = MaterialEingabe.ReadMaterial((iI1+1), 4);

	iAnz	= 0;
	iIter	= 0;
	dW      = 0;

	while (bPosDef && !bError) 
	{
		// Consolidation of needed structure-dats
		Core::i32 iEleNr = ElementEingabe.numberOfElements();

		if (bError)
			break;

		// Begin linear claculation
		iIter++;		// Add iteration-index for next step

		while(!bMdef && !bError) 
		{
			// Schrittweises Erhöhen der Last
			// Wenn nicht die erste Iteration, lösche vorhergehende Ergebnisse
			if (Erg.Size()!=0) 
			{
				dMax  = 0;
				dDiff = 0;
			}		
			// Start linear calculation
			Erg	= CCalculate::LinCalc(CalcLast, iEleNr, CalcLast.iLastNr, iEleKno, iFGKno, 
										MyTragwerk.iLagerKno, ElementEingabe);
			if (!bPosDef)
				bError = TRUE;
				
			// Ermittlung der Schnittkräfte, nur wenn Steifigkeitsmatrix nicht singulär
			iPos    =  0;
			iPosGel =  0;
			dMax    = (double) 0.0;
			if (bPosDef) 
			{
				ErgTemp = Erg;
				for (iI1=1; iI1<=(Core::i32)ElementEingabe.numberOfElements(); iI1++) 
				{
					// Einlesen der Elementverformungen für das momentane Element
					ElementDef(iI1, iEleKno, MyTragwerk.iFG, Inz, Erg, dDef);
				
					// Einlesen der Elementdaten für das momentane Element
					GetElement(iI1, ElementEingabe, iEle);

					// Einlesen der Koordinaten der Elementknoten
					GetKoord(iI1, g_NodeStack, dK1, dK2);	
				
					// Einlesen der Materialdaten des momentanen Elementes
					GetMaterial(iEle[2], MaterialEingabe, dMat);
								
					// Berechnung der Länge des Elementes
					dL = dL2D((dK2[0] - dK1[0]), (dK2[1] - dK1[1]));
				
					// Berechnung der Momente für die Elementknoten					
					if (iEle[3]==2)	// Wenn starr verbunden
						CalcMoment(dDef	,dK1, dK2, dL, dMat[0], dMat[2], dM);
				
					if ((iEle[3]==3)||(iEle[3]==4))	// Wenn links oder rechts gelenkig angeschlossen
						CalcMomentGelenk(dDef, dK1, dK2, dL, dMat[0], dMat[2], dM, iEle[3]);
	
					// Eintrag in den Vektor Vtemp, in dem der Vektor gespeichert wird
					for (iI2=0; iI2<iEleKno; iI2++) 
					{
						iPos++;
						Vtemp.setVektor(iPos, dM[iI2]);
					}
				}
					
				// Auslesen der absolut maximal berechneten Schnittkräfte
				dMax = GetMaxLast(Vtemp, iAnz, iPos, Knoten, Inz);

				// Überprüfung der berechneten Maximalwerte und evtl. Tragwerksumbau
				for (iI1=1; iI1<=MaterialEingabe.iAnz; iI1++) 
				{
					// Wenn maximaler Momentenwert gleich plastischen Moment, Last
					// nicht erhöhen
					// Ermittlung der Differenz
					dDiff = dMpl[iI1-1] - fabs( dMax );

					if ( fabs( dDiff ) > DIFFERENZ ) 
					{
						// Increment the load
						dW     = CalcAdd(dMax, dDiff, dMpl[iI1-1], dW);
						myLast = AddIterLast( myLast, dW, Knoten );
						
						Erg.DelList();

						std::string inc = LocalizationServer::get()->getText( "Msg_TraglastIncLoad" );
						std::string maxM = LocalizationServer::get()->getText( "Msg_TraglastMaxMoment" );
						std::string plastM = LocalizationServer::get()->getText( "Msg_TraglastMaxPlast" );
						strCalcParam.Format("%s %lf. %s %lf. %s: %lf", inc.c_str(), dW, maxM.c_str(), dMax, plastM.c_str(), MyTragwerk.dPl );
						AfxMessageBox( strCalcParam );
					}	
					else	 
					{
						bMdef = TRUE;
					}
				}
			}
			else
			{
				break;
			}
		}
		
		if (bPosDef) 
		{
			// Dump number of current iteration step
			std::string itStep = LocalizationServer::get()->getText( "Msg_NumIt" );
			strCalcParam.Format( "%s %d",itStep.c_str(), iIter );
			AfxMessageBox( strCalcParam );
	
			// Starting reassembly of structure
			iKn = 0;
		
			// If the plast moment was reached
			if (bMdef) 
			{
				bFlag = TRUE;
				iPos = 0;
				iI1  = 0;

				// Auslesen der Knotennummer, an der das maximale Moment aufgetaucht ist
				while ( ( iI1<(Core::i32)(ElementEingabe.numberOfElements() )) && bFlag)
				{
					iI1++;
					for (iI2=1; iI2<=iEleKno; iI2++) 
					{
						iPos++;
						dDiff = fabs(dMpl[0]) - fabs(Vtemp.readVektor(iPos));
		
						// Wenn Knoten erreicht, speichere Knotenummer aus der Inzidenztabelle
						bSet = TRUE;
						if (fabs(dDiff)<=DIFFERENZ) 
						{
							for (iI3=1; iI3<=Knoten.Size(); iI3++) 
							{
								if (Inz.ReadInz(iPos)==Knoten.readVektor(iI3))
									bSet = FALSE;
							}
							if (bSet) 
							{
								iEleNr	= iI1;				// Lese Elementnummer
								iKn		= Inz.ReadInz(iPos);// Lese Knotennummer aus Inzidenztabelle
	
								bLager = FALSE;
								iI3 = 0;
							
								// Auslesen der Randbedingungen
								NodeStack::NodeDef node;
								g_NodeStack.getNode( iKn, node );
								std::vector<Core::d32> holds;
								std::vector<Core::i32> ids;
								node.getBoundaryConditions( holds, ids );
								while (iI3<4) 
								{
									iI3++;

									//if (KoordEingabe.ReadRandbed(iKn, iI3)!=0) {
									if (holds[iI3-1]!=0) 
									{
										bLager = TRUE;
										iLagerArt[iI3-1] = (Core::i32) FEDER;
									}
									else {
										bLager = FALSE;
										iLagerArt[iI3-1] = 0;
									}
								}
								bFlag	= FALSE;			// Beende Schleife
							}
						}
					}
				}

				// Tragwerksumbau 
				iPosGel = ElementEingabe.CheckNode(iKn, 2);	// Maximales Moment an Knoten 1 oder 2
				iI3     = 0;

				// Baue Gelenk in Tragwerk ein
				NodeStack::NodeDef node;
				g_NodeStack.getNode( iKn, node );
				switch(iPosGel) 
				{ 
				case 1:	// Wenn Element links	
					if (iLagerArt[2]!=0) 
					{
						// Wenn Knoten Auflager und eingespannt
						node.setBoundaryConditions( iLagerArt[0], iKn, iLagerArt[1], iKn, 0, iKn );
						
						std::string msg = LocalizationServer::get()->getText( "Msg_RemoveCond" );
						strCalcParam.Format( "%s %d.", msg.c_str(), iKn );
					}
					else 
					{
						ElementEingabe.setElement(iEleNr, 0, 0, 0, GELLEFT);// Setze Gelenk links
						
						std::string msg = LocalizationServer::get()->getText( "Msg_AddJoint" );
						strCalcParam.Format( "%s %d.", msg.c_str(), iKn );
					}
					break;

				case 2:		// Wenn Element rechts				
					if (iLagerArt[2]!=0) 
					{
						// Wenn Knoten Auflager und eingespannt
						std::string msg = LocalizationServer::get()->getText( "Msg_RemoveCond" );
						strCalcParam.Format( "%s %d.", msg.c_str(), iKn );
						node.setBoundaryConditions( iLagerArt[0], iKn, iLagerArt[1], iKn, 0, iKn );
						//KoordEingabe.SetRandbed(iKn, iLagerArt[0], iLagerArt[1], 0);
					}
					else 
					{
						ElementEingabe.setElement(iEleNr, 0, 0, 0, GELRIGHT);// Setzte Gelenk rechts
						std::string msg = LocalizationServer::get()->getText( "Msg_AddJoint" );
						strCalcParam.Format( "%s %d.", msg.c_str(), iKn );
					}
					break;
				}
				AfxMessageBox(strCalcParam);
				
				ElementDef(iEleNr, iEleKno, iFGKno, Inz, Erg, dDef);
				
				GetKoord(iEleNr, g_NodeStack, dK1, dK2);				
				//GetKoord(iEleNr, KoordEingabe, dK1, dK2);
				dL  = dL2D((dK2[0] - dK1[0]), (dK2[1] - dK1[1]));
				dCx = (dK2[0] - dK1[0]) / dL;
				dCy = (dK2[1] - dK1[1]) / dL;
				TransformDeform(dDef, dCx, dCy, dTrans, TRANS);

				if ((dK1[1] - dK2[1])>0) 
					dCx = -dCx;
				if ((dK1[0] - dK2[0])<0) 
					dCy = -dCy;
				// Setze Moment an das Gelenk	
				if (iPosGel==1) {
					if (dDef[2]>0)
						iI3 = (int) NEGATIV;
					else
						iI3 = (int) POSITIV;
				}	
				if (iPosGel==2) 
				{
					if (dDef[5]>0)
						iI3 = (int) NEGATIV;
					else
						iI3 = (int) POSITIV;
				}
				
				PlastLast = SetPlastMoment(iEleNr, iKn, Inz, dMpl[0], ElementEingabe, iI3);

				// Anfügen der letzten Ersatzlast
				for (iI1=1; iI1<=PlastLast.iLastNr; iI1++) 
				{
					iAnz = Knoten.Size() + 1;
					iKnNr  = (int) PlastLast.readLast(iI1, 1);
					Knoten.addVektor(iKnNr);
					dPl[0] = PlastLast.readLast(iI1, 2);
					dPl[1] = PlastLast.readLast(iI1, 3);
					dPl[2] = PlastLast.readLast(iI1, 4);
					CalcLast.addLast(iKnNr, dPl[0], dPl[1], dPl[2], KNOTENLAST);	
				}
				
				// setting back the values
				iI1   = 0;
				bFlag = FALSE;				
				dW    = 0;
				bMdef = FALSE;
			}		
		}
	}

	// When an error occurs
	if (MyTragwerk.dPl==(double) 0.0) 
	{		
		std::string errMsg = LocalizationServer::get()->getText( "ErrMsg_ErrCalcLimitForce" );
		strCalcError.Format("%s", errMsg.c_str() );
		AfxMessageBox( strCalcError );

		return Err;
	}
	// If plastical loading was calculated
	if ( 0.0 != MyTragwerk.dPl ) 
	{
		std::string msg = LocalizationServer::get()->getText( "Msg_LimitLoad" );
		strCalcParam.Format( "%s %lf", msg.c_str(), MyTragwerk.dPl );
		AfxMessageBox(strCalcParam);
		MyTragwerk.bCalc = TRUE;
		VM = Vtemp;
		return ErgTemp;
	}
	
	// free memory reserved on the heap
	delete [] dMpl;
	return Err;	
}
