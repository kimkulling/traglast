/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : Band.cpp
// Desc.       : Functions for fe-specific 
// Autor       : Kim Kulling
// Last mod.   : 09.01.2004
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "NodeStack.h"

using namespace Core;
using namespace FEStructure;
using namespace Math;


// Global vars and instances
extern int			iSysLastNr, iKn;
extern NodeStack	g_NodeStack;
extern ElementStack	ElementEingabe;
extern Tragwerk		MyTragwerk;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: Band(int iGesEle, int iFGKno, int iEleKn, InzidenzStack In)
// Beschreibung	: Berechnet die Bandbreite der Steifigkeitsmatrix, in dem die Differenz der 
//					beiden Knoten gebildet wird, die am weitesten im eigegebenen Tragwerk 
//					auseinanderliegen
// Parameter	:
// iGesEle		: Gesamtzahl der Elemente des Systems
// iFGKno		: Anzahl der Knotenfreiheitsgrade
// iEleKn		: Anzahl der Elementknoten
// Rückgabewert	: Bandbreite des Systems
/////////////////////////////////////////////////////////////////////////////////////////////////
int Band( int iGesEle,  int iFGKno,  int iEleKn, InzidenzStack In )
{
	InzidenzStack EleKnoInz;	
	int	          iDiff, i, j, k, s = 0, InzRead, iBand = 0;

	// Initialisiere Inzidenz-Objekt
	for (i=1; i<=iEleKn; i++)
		EleKnoInz.addInz(i, 0);

	for (i=1; i<=iGesEle; i++) 
	{
		int r=0;
		// Ermittlung der einzelnen Element-Inzidenztabelle zur Berechnung der Differenz
		for (j=1; j<iEleKn+1; j++) 
		{	
			r++;		
			s++;
			InzRead = In.ReadInz(s);
			EleKnoInz.SetInz(r, InzRead);
		}

		for (j=1; j<iEleKn+1; j++ )
		{
			for (k=j; k<iEleKn+1; k++ ) 
			{
				// Calculating difference between the maximum node-numbers
				iDiff = abs(EleKnoInz.ReadInz(j) - (EleKnoInz.ReadInz(k)));
				// If an greater value was calculated, save it
				if (iDiff > iBand) 
					iBand = iDiff;
			}
		}
	}
	// Calc bandwidth of matrix
	iBand = (iBand + 1) * iFGKno;

	return iBand;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: SystemAuf (int EleNummer, int FGKno, int EleKno, int Band, 
//					InzidenzStack Inz, VektorStack EleSteif, VektorStack SysSteif)
// Beschreibung	: Baut die Gesamtsteifigkeitsmatrix zusammen
// Parameter	:
// EleNummer	: Anzahl der Elemente
// FGKno		: Anzahl der Freiheitsgrade pro Knoten
// EleKno		: Anzahl der Elementknoten
// Band			: Bandbreite der Steifigkeitsmatrix
// Inz			: Inzidenzmatrix als Vektor gespeichert
// EleSteif		: Elementsteifigkeitsmatrix
// Rückgabewert	: zusammengesetzte Steifigkeitsmatrix
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor SystemAuf (const int EleNummer, const int FGKno, const int EleKno, const int Band, 
				InzidenzStack Inz, Vektor EleSteif, Vektor SysSteif)
{
	InzidenzStack EleKnoInz, EleInz;
	int           FGEle, jj,s,t,p,o,u, k, r, iVal;
	double        dW, dRes;

	// Berechnung der Elementknoten-Inzidenzmatrix
	for ( int i=1; i<EleKno+1; i++ ) 
	{
		const int j    = (EleNummer - 1) * EleKno + i;
		iVal = Inz.ReadInz( j );
		EleKnoInz.addInz( i, iVal );
	}
	
	// Ermittlung der Gesamt-Freiheitsgrade eines Elementes
	FGEle = EleKno * FGKno;

	// Inizialisierung der Inzidenztabelle zur Speicherung der Freiheitsgrade des Elementes
	EleInz.DeklInz(FGEle);

	// Ermittlung der ElementInzidenzmatrix zur Zuordnung der Freiheitsgrade
	for ( int i=1; i<=EleKno; i++ ) 
	{
		s = (EleKnoInz.ReadInz(i) - 1) * FGKno;
		p = 1 + (i - 1) * FGKno;
		r = 0;
		for (k=p; k<=(p + FGKno - 1); k++) {
			r++;
			dRes = s+r;
			EleInz.SetInz(k,(int) dRes);
		}
	}
	
	o = 0;
	for ( int r=1; r<=FGEle; r++) 
	{
		int i  = EleInz.ReadInz(r);	// Lese Nummer des Freiheitsgrades
		jj = 0;
		u  = r;					// Nummer des Freiheitsgrades
		for (s=1; s<=FGEle; s++) {
			int j = EleInz.ReadInz(s);	// Nummer des Freiheitsgrades des jeweiligen Elements
			if (s<r) {				// Wenn kleiner der gesamten Freiheitsgrade des Elemente
				u  += jj;			// 
				jj = FGEle - s;			// 
			}
			else 
				o++;

			if (j>=i) {// Wenn Nummer des weiteren Freiheitsgrades > jeweiligen Freiheitsgrad des Elementes
				t = (i - 1) * Band + j - i + 1;
				if (s<r)
					k = u;
				else
					k = o;
				dW = SysSteif.readVektor(t);
				// Addiere die Steifigkeit des Elements zur Gesamtsteifigkeitsmatrix an der 
				// berechneten Stelle
				dRes = dW + EleSteif.readVektor(k);
				SysSteif.setVektor(t, dRes);
			}
		}
	}

	// Gebe neue Systemsteifigkeitsmatrix zurück
	return SysSteif;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function : MakeStuetzStack (VektorStack MyLager, KoordStack KoordEingabe, int nAnzKno)
// Desc.    : Ermittelt die Stützungen, welche im KoordStack gespeichert sind, danach werden 
//					die Daten in einem Vektor gespeichert und zurückgegeben
// Parameter
// MyLager      : Lagerungen
// nAnzKno      : Anzahl der gelagerten Knoten
// KoordEingabe : Liste der Kordinaten
// Returns      : Liste der Lager, welche gehalten sind
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor MakeStuetzStack(Vektor MyLager, NodeStack nodes )
{
	bool bFlag = false;
	int  iLager,iI1, iI2, iI3;

	// Init of memory
	iI3=0;
	MyLager.initVector( nodes.getNumberOfNodes() * 4 );

	// Lese alle Koordinaten aus
	NodeStack::NodeDef node;
	//for (iI1=1; iI1<KoordEingabe.iAnz+1; iI1++) {
	for ( iI1=1; iI1<nodes.getNumberOfNodes() + 1; iI1++ )
	{
		nodes.getNode( iI1, node );
		Core::d32 hold[ 3 ];
		std::vector<Core::d32> holds;
		std::vector<Core::i32> ids;
		node.getBoundaryConditions( holds, ids );
		for (iI2=1; iI2<4; iI2++) 
		{
			// If a boundary condition was found
			if ( hold[ iI2-1 ] != 0 )
			{
				bFlag = true;
				break;
			}
			//if (KoordEingabe.ReadRandbed(iI1, iI2) != (int) 0) 
				//bFlag = true;
		}

		if (bFlag) 
		{
			iI3++;
			MyLager.setVektor(iI3, iI1); // Setzte Knotennummer in den Array
			NodeStack::NodeDef node;
			nodes.getNode( iI1, node );
			std::vector<Core::d32> holds;
			std::vector<Core::i32> ids;
			node.getBoundaryConditions( holds, ids );
			for (iI2=1; iI2<4; iI2++)
			{ // Lese die einzelnen Freiheitsgrade aus
				iI3++;
				iLager = (Core::i32) holds[ iI2-1 ];
				//iLager = KoordEingabe.ReadRandbed(iI1, iI2);// Lese einzelne Lagerbedingungen aus
				if ( iLager > 0 )  
					MyLager.setVektor( iI3, FEDER );
				else 
					MyLager.setVektor(iI3, (double) 0.0);
			}
			// Setzte Flag zurück
			bFlag = false;
		}
	}
	
	// Return array, which contains the boundary conditions
	return MyLager;			
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: MakeLastVektor(LastStack LastEingabe, int iFGKno)
// Beschreibung	: Erstellt aus den Eingabedaten, welche in einer Klasse vom Typ LastStack
//					gespeichert wurden, den für die Berechnung benötigten Lastvektor
// Parameter
// LastEingabe	: Stack, in dem die eingegebenen Lastdaten gespeichert sind
// iFGKno		: Maximaler Freiheitsgrad eines Knotens
// Rückgabewert	: Array vom Typ VektorStack, in dem die Lastdaten gespeichert sind
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor MakeLastVektor(LastStack LastEingabe, int iFGKno)
{
	Vektor LastCalc;
	int    iPos = 0, iLastNr,iI1, iI2;
	double dWert, dRes;
	
	// Read number of loading definitions
	iLastNr = LastEingabe.iLastNr;

	// Initialisiere Speicher für den Lastvektor
	dRes = iLastNr * (iFGKno + 1);
	LastCalc.initVector( (i32) dRes );

	for (iI1=1; iI1<=iLastNr; iI1++) { // Wiederhole so oft, wie Lasten eingegeben wurden
		for (iI2=1; iI2<=(iFGKno+1); iI2++) {
			dWert = LastEingabe.readLast(iI1, iI2);	// LEse Knotennummer und Lasten aus dem LastStack aus
			iPos++;
			LastCalc.setVektor(iPos, dWert);		// Setze ausgelesenen Wert in den Array ein
		}
	}
	
	return LastCalc;								// Gebe Array zurück
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Stuetzung(int LagerKno, int FGKno, int Band, VektorStack Lager, 
//					VektorStack SysSteif)
// Beschreibung	: Stützungen werden durch Eingabe großen Werten (Federsteifigkeiten) simuliert
// Parameter
// LagerKno		: Anzahl der gestützten Systemknoten
// FGKno		: Anzahl der Knotenfreiheitsgrade
// Band			: Bandbreite des Systems
// Rückgabewert	: Vektor mit den vorhandenen Stützungen
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor Stuetzung(int LagerKno, int FGKno, int Band, Vektor Lager, Vektor SysSteif)
{
	int    Num, jj, kk, r, rr, s, k, j;
	double dWert1=0;

	kk = 1;
	for (k=1; k<=LagerKno; k++) {             // Sooft machen, wie Knoten gelagert sind
		Num =(int) Lager.readVektor(kk);    // Lese Nummer des Lagers
		rr  = (Num - 1) * FGKno * Band + 1; // Errechne Position
		jj  = 0;
		for (j=1; j<=FGKno; j++) { // Sooft machen, wie Freiheitsgrade vorhanden
			s      = kk + j;
			r      = rr + jj;
			dWert1 = SysSteif.readVektor(r);// Lese Wert aus der Systemsteifigkeitsmatrix	
			SysSteif.setVektor(r, (dWert1 + Lager.readVektor(s))); // Addiere Wert mit Lagerwert
			jj    += Band;
		}
		kk += FGKno + 1;
	}
	
	return SysSteif;						// Gebe neue Systemsteifigkeitsmatrix zurück
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktiom		: Knotenlast (int LastKno, int FGKno, VektorStack Last, VektorStack SysLast)
// Beschreibung	: Lasten werden direkt auf die Knoten gesetzt, 
//				  es werden ab sofort die globalen Knoten verwendet
// Parameter
// LastKno		: Anzahl der belasteten Knoten
// FGKno		: Anzahl der Knotenfreiheitsgrade
// Last			: Lastvektor
// SysLast		: Belastungsvektor für die lineare Berechnung
// Rückgabewert	: Berechneter Belastungsvektor
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor Knotenlast(int LastKno, int FGKno, Vektor Last, Vektor SysLast)
{
	int    ikk, iNum, ir, irr, is, ik, ij;
	double dWert = 0.0, dRes=0.0;

	ikk = 1;
	for (ik=1; ik<LastKno+1; ik++) {
		iNum = (int) Last.readVektor(ikk); // Lese Nummer der Last
		irr  = (iNum - 1) * FGKno + 1;    // Fehler
		ir   = irr;
		for (ij=1; ij<=FGKno; ij++) {
			is    = ikk + ij;
			dWert = SysLast.readVektor(ir);
			dRes  = Last.readVektor(is) + dWert;
			SysLast.setVektor(ir, dRes);
			++ir;
		}
		ikk += FGKno + 1;
	}
	return SysLast;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Routine		: Elementlast(int EleNummer, int EleKno, int FGKno, InzidenzStack Inz, 
//					VektorStack EleLast)
// Beschreibung	: Beliebige Lasten werden in arbeitsäquivalente Elementknoten- 
//	   			  lasten umgerechnet und in dem Vektor EleLast gespeichert 
//				  werden. Unter Zuhilfename der Knoteninzidenzen, welche aus der
//				  Inzidenzmatrize Inz eindimensional gespeichert ist, wird der 
//				  Belastungsvektor SysLast erzeugt
// Parameter
// EleNummer	: Elementnummer
// EleKno		: Anzahl der Elementknoten
// FGKno		: Anzahl der Knotenfreiheitsgrade
/////////////////////////////////////////////////////////////////////////////////////////////////
int Elementlast(int EleNummer, int EleKno, int FGKno, InzidenzStack Inz, Vektor EleLast)
{
	int    Num, a, r, rr, s, i, k, j;
	double dRes;
	Vektor SysLast;

	dRes = (double) 0.0;
	s = 0;
	a = (EleNummer-1) * EleKno;
	for (k=1; k<EleKno+1; k++) {
		i   = a+k;
		Num = (int)Inz.ReadInz(i);
		for (j=1; j<=FGKno; j++) {
			s++;
			rr   = (Num - 1) * FGKno;
			r    = rr+j;
			dRes = SysLast.readVektor(r) + EleLast.readVektor(s);
			SysLast.setVektor(r, dRes);
		}
	}
	
	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktiom		: ElementDef  (int EleNummer, int EleKno, int FGKno, InzidenzStack Inz, 
//					VektorStack SysDef)
// Beschreibung	: Zur Berechnung der Schnittkräfte im Element werden die
//				  Elementverformungsparameter benötigt. Aus dem Lösungsvektor 
//				  SysDef werden die Elementverformungen berechnet und auf dem Vektor 
//				  EleDef abgelegt.
// Parameter
// EleNummer	: Elementnumer
// EleKno		: Anzahl der Elementknoten 
// FGKno		: Anzahl der Knotenfreiheitsgrade
// Rückgabewert	: Vektor, in dem die Verformungen des Elementes gespeichert wurden
/////////////////////////////////////////////////////////////////////////////////////////////////
void ElementDef (int iEleNummer, int iEleKno, int iFGKno, 
						InzidenzStack Inz, Vektor SysDef, double *dDef)
{
	int    iNum, a, r, rr, s, i, j, k;
	Vektor EleDef;
	
	s = 0;
	a = (iEleNummer - 1) * iEleKno;

	// Do it for every node
	for (k=1; k<=iEleKno; k++) 
	{
		i    = a + k;
		iNum = Inz.ReadInz(i);
		for (j=1; j<=iFGKno; j++) 
		{
			// Sooft machen, wie Freiheitsgrade da sind
			s++;
			rr = (iNum - 1) * iFGKno;
			r  = rr + j;
			dDef[s-1] = SysDef.readVektor(r);	// Lese Deformationen aus globalen Deformatinen
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: GetKoord(int iNr, KoordStack Koord, double *dK)
// Beschreibung	: Ermittelt die Koordinaten des angegebenen Elementes und speichert sie im Array
//					dK
// Parameter
// iNr			: Elementnummer
// Koord		: Liste der Koordinaten
/////////////////////////////////////////////////////////////////////////////////////////////////
int GetKoord(int iNr, NodeStack nodeStack, double *dK1, double *dK2)
{
	int iKn[2], iI1;

	if (iNr<0 || dK1==NULL || dK2==NULL)
		return -1;

	for (iI1=0; iI1<2; iI1++)		// Lese Knotennummern aus Elementdaten
		iKn[iI1] = (int) ElementEingabe.ReadElement(iNr, (iI1+1), iNr);

	NodeStack::NodeDef node1, node2;
	nodeStack.getNode( iKn[0], node1 );
	nodeStack.getNode( iKn[1], node2 );

	node1.getPosition( dK1[ 0 ], dK1[ 1 ]	);
	node2.getPosition( dK2[ 0 ], dK2[ 1 ]	);
	/*for (iI1=1; iI1<=2; iI1++) 
	{
		dK1[iI1-1] = Koord.ReadKoord(iKn[0], iI1);
		dK2[iI1-1] = Koord.ReadKoord(iKn[1], iI1);
	}*/

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: GetRandbed(int iKnNr, KoordStack Koord, double dRand[3])
// Beschreibung	: Liest die vorhandenen Randbedingungen des Knotens aus und schreibt sie
//					in den Array dRand
// Parameter
// iKnNr		: Knotennummer des auszulesenden Knotens
// Koord		: Liste vom Typ KoordStack, in der die Koordinate steht
// *dRand		: Pointer auf den Array, in dem die Randbedingungen hineingeschrieben werden
/////////////////////////////////////////////////////////////////////////////////////////////////
//int GetRandbed( int iKnNr, KoordStack Koord, double *dRand )
int GetRandbed( int iKnNr, NodeStack nodes, double *dRand )
{
	NodeStack::NodeDef node;
	nodes.getNode( iKnNr, node );
	std::vector<Core::d32> holds;
	std::vector<Core::i32> ids;
	node.getBoundaryConditions( holds, ids );

	for ( size_t idx=0; idx < holds.size(); idx++ )
		dRand[ idx ] = holds[ idx ];
	//for (int iI1=0; iI1<3; iI1++)		// Lese Randbedingungen
	//	dRand[iI1] = Koord.ReadRandbed(iKnNr, iI1+1);
	
	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: GetMaterial(int iNr, MaterialStack Mat, double *dM)
// Beschreibung	: Schreibt die Materialkennwerte in den Array dM
// Parameter
// iNr			: Nummer des Querschnittes
// Mat			: Übergebender MaterialStack
// *dM			: Pointer auf Array
/////////////////////////////////////////////////////////////////////////////////////////////////
int GetMaterial(int iNr, MaterialStack Mat, double *dM)
{
	for (int iI1=0; iI1<4; iI1++)
		dM[iI1] = Mat.ReadMaterial(iNr, (iI1+1));

	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: GetElement(int iNr, ElementStack Ele, int *iEle)
// Beschreibung	: Schreibt die Elementkennwerte in den Array iEle
// Parameter
// Parameter
// iNr			: Nummer des Elementstacks
// Ele			: Übergebender ElementStack
// *iEle		: Pointer auf den Array
/////////////////////////////////////////////////////////////////////////////////////////////////
int GetElement(int iNr, ElementStack Ele, int *iEle)
{
	// Read elementdata
	for (int iI1=1; iI1<5; iI1++)
		iEle[iI1-1] = Ele.ReadElement(iNr, iI1, iNr);

	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: GetLast(int iNr, LastStack Last, double *dLast)
// Beschreibung	: Ermittelt die Lastdaten aus der Klasse LatStack
// Parameter
// iNr			: Nummer der auszulesenden Last
// Last			: Übergebende Klasse vom Typ LastStack
// *dLast		: Pointer auf den Array, in welchen die Lastdaten gespeichert werden
/////////////////////////////////////////////////////////////////////////////////////////////////
int GetLast(int iNr, LastStack Last, double *dLast)
{
	for (int iI1=1; iI1<5; ++iI1)
		dLast[iI1-1] = Last.readLast(iNr, iI1);

	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: GetScale(int iAuflX, int iAuflY, double dXD, double dYD)
// Beschreibung	: Berechnet den Skalierungsfaktor aus den eingehenden Parameter
// Parameter
// iAuflX		: Auflösung in X
// iAuflY		: Auflösung in Y
// dXD			: Maximaler Abstand in X
// dYD			: MAximaler Abstand in Y
// Rückgabewert	: Skalierungsfaktor			
/////////////////////////////////////////////////////////////////////////////////////////////////
double GetScale(int iAuflX, int iAuflY, double dXD, double dYD)
{
	int    iMax;
	double dMax, dS;

	if (iAuflX>iAuflY)	// Ermittle minimalen Auflösungswert
		iMax = iAuflX;
	else
		iMax = iAuflY;

	if (dXD>dYD)		// Ermittle minimalen Abstand zwischen Koordinaten
		dMax = dXD;
	else
		dMax = dYD;

	dS = iMax/dMax;     // Berechne Skalierungsfaktor

	return dS;			// Gebe Skalierungsfaktor zurück
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: GetIterLast(LastStack Last)
// Beschreibung	: Ermittelt die für die plastische Berechnung benötigten Lastdaten,in dem der
//					Maximalwert (in X- oder Y-Richtung) ermittelt wird. Danach wird dieser 
//					durch eingegebenen Kräfte dividiert, so daß jede Kraft durch die Maximal-
//					Kraft beschrieben werden kann.
// Parameter
// Last			: Liste der eingegebenen Lasten
// Rückgabewert	: Die für die plastische Berechnung benötigten Lastdaten 
/////////////////////////////////////////////////////////////////////////////////////////////////
LastStack GetIterLast(LastStack Last)
{
	int    iAnz, iKn, iI1, iI2;
	double dLastWert, dMax, dMin, dX, dY;

	// Init vars
	iAnz = Last.iLastNr;
	dLastWert   = 0;
	dMax = dMin = 0;
	
	// Ermittlung der maximalen und minimalen Knotenkräfte im Tragwerk
	for (iI1=1; iI1<=iAnz; iI1++) {
		for (iI2=1; iI2<=2; iI2++) {
			dLastWert = Last.readLast(iI1, (iI2+1));	// Lese Lastwert
			
			if (dLastWert>dMax)			// Ermittle maximalen Lastewert
				dMax = dLastWert;
			if (dLastWert<dMin)			// Ermittle minimalen Lastwert
				dMin = dLastWert;
		}
	}
	
	if (abs((int) dMin) > abs((int) dMax)) // Ermittle maximalen absoluten Lastwert
		dMax = dMin;

	// Kehrwert der Lasteingaben bilden
	for (iI1=1; iI1<=iAnz; iI1++) {
		iKn = (int) (Last.readLast(iI1, 1));
		dX	= Last.readLast(iI1, 2);
		dY	= Last.readLast(iI1, 3);
		if (dX!=0.0)        // Wenn x!=0, bilde Kehrwert
			dX = dMax / dX;
		
		if (dY!=0)          // Wenn y!=0, bilde Kehrwert
			dY = dMax / dY;
		
		Last.setLast(iI1, iKn, dX, dY, 0, TRUE, TRUE, TRUE);
	}
			
	return Last;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: AddIterLast(LastStack Last, double dWert)
// Beschreibung	: Erhöht die LAsten um den dWert
// Parameter
// Last			: LastStack der Berechnung
// dWert		: Wert, um den die eingegeben Lasten inkrement bzw. dekrementiert werden sollen
// Rückgabewert	: Der neu berechnete LastStack
/////////////////////////////////////////////////////////////////////////////////////////////////
LastStack AddIterLast(LastStack Last, double dWert, Vektor Knoten )
{
	int    iKn, iI1;
	double dX, dY;

	if (dWert!=0) {
		Last = GetIterLast(Last);
		MyTragwerk.dPl = MyTragwerk.dPl + dWert;		
		
		for (iI1=1; iI1<=Last.iLastNr; iI1++) {
			// Lese Lastdaten
			iKn = (int) (Last.readLast(iI1, 1));
			dX  = Last.readLast(iI1, 2);
			dY	= Last.readLast(iI1, 3);

			if (dX!=0)			// Wenn X-Wert > Null
				dX = dX * MyTragwerk.dPl;	// addiere Wert auf alten Eintrag
			if (dY!=0)			// Wenn Y-Wert > Null
				dY = dY * MyTragwerk.dPl;	// addiere Wert auf alten EIntrag
				
				// Erhöhung der Last	
			Last.setLast(iI1, iKn, dX, dY, 0, TRUE, TRUE, TRUE);
		}
	}
	
	return Last;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: ClearDArray(double *dArray, int iLenght)
// Beschreibung	: Setzt den übergebenen Array auf 0
// Parameter
// dArray		: Pointer auf den Array
// iLenght		: Läng des Arrays
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
int ClearDoubleArray(double *dArray, int iLength)
{
	if (iLength<1)
		return TRUE;

	// Init the overgiven array with zeros
	memset(dArray, 0, sizeof(double) * iLength);
	
	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: SetPlastMoment (int iKnNr, double dPlast)
// Beschreibung	: Zwei Momente in Höhe des plastischen Momentes werden an den entsprechenden
//					Knoten gelegt, um ein plastische Element zu simulieren
// Parameter
// iEle1		: Element 1 (links vom Knoten)
// iEle2		: Element 2 (rechts vom Knoten)
// dMpl			: Plastisches Moment des jeweiligen Querschnitts
// Last			: LastStack, in dem die eingegebenen Lasten gespeichert sind
// Element		: ElementStack, in dem die Elementdaten gespeichert werden
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
LastStack SetPlastMoment (int iEle1, int iKn, InzidenzStack Inz, double dMpl, 
						  ElementStack Element, int iNeg)
{
	int       iEle2 = 0, iKn1, iKn2, iKn3,  iI2, iAnz = 0, iPos;
	double    dKoord1[2], dKoord2[2], dF1, dF2, dF3, dM1, dM2, dM3, dXneu, dYneu;
	LastStack Last;

	iAnz = 0;
	iPos = 0;
	dF1 = dF2 = dF3 = dM1 = dM2 = dM3 = 0.0;
	for ( ui32 iI1=1; iI1<=ElementEingabe.numberOfElements(); iI1++) 
	{
		for (iI2=1; iI2<=2; iI2++) 
		{
			iPos++;
			if (Inz.ReadInz(iPos)==iKn) 
			{
				iAnz++;
			}
		}
	}

	if (iAnz==1) { // Wenn eingespannt
		dMpl = dMpl * iNeg;
		Last.addLast(iKn, 0, 0, dMpl, KNOTENLAST);
	}

	if (iAnz==2) { // Wenn Knoten zwischen 2 Elementen
		dMpl = dMpl * iNeg;
		// Ermittlung des 2. Elementes
		for ( ui32 iI1=1; iI1<=Element.numberOfElements(); iI1++) {
			if (Element.ReadElement(iI1, 1, iI1)==iKn)
				iEle2 = iI1;
		}
		// Auslesen der benutzten Elementknoten
		iKn1 = Element.ReadElement(iEle1, 1, iEle1);
		iKn2 = Element.ReadElement(iEle1, 2, iEle1);
		iKn3 = Element.ReadElement(iEle2, 2, iEle2);

		GetKoord (iEle1, g_NodeStack, dKoord1, dKoord2);
		dXneu = 0.9 * (dKoord2[0] - dKoord1[0]);
		dYneu = 0.9 * (dKoord2[1] - dKoord1[1]);

		g_NodeStack.setNode( iKn1, dKoord1[0] + dXneu, dKoord1[1] + dYneu, iKn1, 0, iKn1, 0, iKn1, 0 );
		//KoordEingabe.setKoord(dKoord1[0] + dXneu, dKoord1[1] + dYneu, iKn1, FALSE, FALSE, FALSE);
		Last.addLast(iKn1, 0, dF1, dMpl, KNOTENLAST);
		Last.addLast(iKn2, 0, dF2, -1*dMpl, KNOTENLAST);
	}

	return Last;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: CalcAdd(double dDiff, double dW)
// Beschreibung	: Die Funktion ermittelt die nächsten Erhöhungsschritt
// Parameter
// dMax			: Maximales Moment
// dDiff		: Differenz zwischen dem maximalen Moment und dem plastischen
// dW			: Berechneter Wert 
// Rückgabewert	: Wert, der auf den Lastvektor addiert werden soll
/////////////////////////////////////////////////////////////////////////////////////////////////
double CalcAdd(double dMax, double dDiff, double dMpl, double dW)
{
	// Ermittlung des Faktors, der auf den Lastvektor aufaddiert wird
	if (fabs(dDiff)!=50.0) {
		if (fabs(dW)==0)
			dW = 0.5;
		dW = (fabs(dW) * fabs(dMpl)) / fabs(dMax);
	}
	if (fabs(dDiff)<30)
		dW = 2.5;
	if (fabs(dDiff)<20)
		dW = 0.9;
	if (fabs(dDiff)<10)
		dW = 0.5;
	if (fabs(dDiff)<7)
		dW = 0.4;
	if (fabs(dDiff)<5)
		dW = 0.25;
	if (fabs(dDiff)<2.5)
		dW = 0.1;
	if (fabs(dDiff)<1)
		dW = 0.05;
	if (fabs(dDiff)<0.5)
		dW = 0.03;
	if (fabs(dDiff)<0.25)
		dW = 0.01;
	if (fabs(dDiff)<0.1)
		dW = 0.005;
	if (dDiff<0)
		dW = dW * -1;

	return dW;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: GetMaxLast(VektorStack Vtemp, int iAnz, int iPos, 
//					int *iKnGel, InzidenzStack Inz)
// Beschreibung	: Der maximale Momenten-Wert wird aus dem Vektor gelesen, sofern an der 
//					Stelle noch kein plastisches Gelenk vorhanden ist
// Parameter
// Vtemp		: Vektor, in dem der Momentenverlauf gespeichert ist
// iAnz			: Anzahl von Knoten, die bereits umgebaut wurden
// iPos			: Anzahl von Inzidenzeinträgen
// Knoten		: Vektor, in dem die bereits umgebauten Knoten gespeihert wurden
// Inz			: Inzdenztabelle des Tragwerks
// Rückgabewert	: Maximales Moment im Tragwerk
/////////////////////////////////////////////////////////////////////////////////////////////////
double GetMaxLast(Vektor Vtemp, int /*iAnz*/, int iPos, Vektor Knoten, 
				  InzidenzStack Inz)
{
	int    iI1, iI2;
	double dMax, dW;
	bool   bFlag = true;

	dMax = 0;
	// Wenn noch keine plastischen Momente vorhanden
	if (Knoten.isEmpty() ) 	{ 
		// Sooft machen, wie Schnittkräfte berechnet wurden
		for (iI1=1; iI1<=iPos; iI1++) 
		{ 
			dW = Vtemp.readVektor(iI1);
			if (fabs(dW)>fabs(dMax))
				dMax = dW;	
		}
	}
	else 
	{ // Wenn breits plastische gelenke vorhanden	
		for (iI1=1; iI1<=iPos; iI1++)
		{	
			iKn = Inz.ReadInz(iI1);		// Lese Knotennummer aus Inzidenztabelle
			dW = Vtemp.readVektor(iI1);
			bFlag = TRUE;
			for (iI2=1; iI2<=Knoten.Size(); iI2++) 
			{	
				// Wenn Knoten kein pl.Gelenk 
                double res = Math::round( ( double )Knoten.readVektor( iI2 ) );
                if (res==iKn)
					bFlag = false;
			}
			if ((fabs(dW)>fabs(dMax))&&bFlag)
				dMax = dW;
		}
	}
	
	return dMax;
}
