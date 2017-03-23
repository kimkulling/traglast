/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : element_berechnen.cpp
// Desc.       : Calculation of several element stiffness matrices
// Autor       : Kim Kulling
// Last mod.   : 11.01.2004
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "types.h"
#include "Logger.h"

using namespace Core;
using namespace Math;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: Fachwerk()
// Beschreibung	: Berechnet die Steifigkeitmatrix K für ein Fachwerk-Element 
// Parameter
// dEM			: E-Modul des Querschnittes
// dA			: Fläche des Querschnitts
// dX1			: X-Koordinate des 1. Knotens
// dX1			: X-Koordinate des 2. Knotens
// dY1			: Y-Koordinate des 1. Knotens
// dY2			: Y-Koordinate des 2. Knotens
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor Fachwerk(double dEM, double dA, double dX1, double dX2, double dY1, 
					 double dY2, Vektor K)
{
	K.DeclVektor(21);

	// Ermittlung der Steifigkeitsparameter
	d32 dL = MathUtils<Core::d32>::getLength( (dX2 - dX1), (dY2 - dY1) );
	d32 dF1 = (dEM * dA) / dL;
	
	// Ermittlung der Elementsteifigkeitsmatrix
/*	dV[0] = 
	dV[1] = 
	dV[2]  = 
	dV[3]  = 
	dV[4]  = 
	dV[5]  = 
	dV[6]  = 
	dV[7]  = 
	dV[8]  = 
	dV[9]  = 
	dV[10] = 
	dV[11] = 
	dV[12] = 
	dV[13] = 
	dV[14] = 
	dV[15] = 
	dV[16] = 
	dV[17] = 
	dV[18] = 
	dV[19] = 
	dV[20] = */

	K.setVektor(1, dF1);
	K.setVektor(2, 0);
	K.setVektor(3, 0);
	K.setVektor(4, (-1 * dF1));
	K.setVektor(5, 0);
	K.setVektor(6, 0);
	K.setVektor(7, 0);
	K.setVektor(8, 0);
	K.setVektor(9, 0);
	K.setVektor(10, 0);
	K.setVektor(11, 0);
	K.setVektor(12, 0);
	K.setVektor(13, 0);
	K.setVektor(14, 0);
	K.setVektor(15, 0);
	K.setVektor(16, dF1);
	K.setVektor(17, 0);
	K.setVektor(18, 0);
	K.setVektor(19, 0);
	K.setVektor(20, 0);
	K.setVektor(21, 0);
	
	return K;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: Balken()
// Beschreibung	: Berechnet den Steifigkeitsvektor für ein Balkenelement
// Parameter
// dEmodul		: E-Modul des Querschnitts
// dFlaeche		: Fläche 
// dIy			: Trägheitsmoment 2.er Ordnung
// dX1			: X-Koordinate von Punkt 1
// dX2			: X-Koordinate von Punkt 2
// dY1			: Y-Koordinate von Punkt 1
// dY2			: Y-Koordinate von Punkt 2
// K			: Steifigkeitsmatrix des Elementes wird zurückgegeben
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor Balken(double dEmodul, double dFlaeche, double dIy, double dX1, double dX2, 
				   double dY1, double dY2)
{
	Vektor K;
	K.DeclVektor(21);
	d32 dV[21];
	memset(dV, 0, sizeof(double) * 21);

	// Calculationg parameters for stiffness
	d32 dX21	= dX2 - dX1;
	d32 dY21	= dY2 - dY1;
	d32 dLaenge	= MathUtils<Core::d32>::getLength( dX21, dY21 );
	d32 dCx		= dX21 / dLaenge;
	d32 dCy		= dY21 / dLaenge;
	
	if ((dY1 - dY2)>0) 
		dCx = -dCx;
	if ((dX1 - dX2)<0) 
		dCy = -dCy;
	
	/* Ermittlung der Steifigkeits-Parameter */
	d32 dF1 = (dEmodul * dFlaeche) / dLaenge;
	d32 dF2 = (dEmodul * dIy) / (dLaenge * dLaenge * dLaenge);
	
	/* Berechnung der transformierten Steifigkeitsmatrix
	 Transformierte Steifigkeitsmatrix 
	 mit k[1..21] gespeichert als Dreiecksmatrix:
  	  0  1  2  3  4  5
	     6  7  8  9 10
	       11 12 13 14
		      15 16 17
		  	     18 19
			        20 */
	dV[0]  = ((dCx * dCx) * dF1 + (dCy * dCy) * 12 * dF2);
	dV[1]  = (dCx * dCy) * (dF1 - (12 * dF2));
	dV[2]  = (-dCy * 6 * dLaenge * dF2);
	dV[3]  = ((dCx * dCx) * -dF1 + (dCy * dCy) * -12 * dF2);
	dV[4]  = (dCx * dCy) * (-dF1 - (-12) * dF2);
	dV[5]  = (-dCy * (6 * dLaenge * dF2));
	dV[6]  = (((dCy * dCy) * dF1) + ((dCx * dCx) * 12 * dF2));
	dV[7]  = (dCx * 6 * dLaenge * dF2);
	dV[8]  = (dCx * dCy) * (-dF1 - (-12 * dF2));
	dV[9]  = ((dCy * dCy) * (-dF1) + (dCx * dCx) * (-12 * dF2));
	dV[10] = (dCx * 6 * dLaenge * dF2);
	dV[11] = (4 * ((dLaenge * dLaenge)) * dF2);
	dV[12] = (-1 * dCy * (-6 * dLaenge * dF2));
	dV[13] = (dCx * (-6 * dLaenge * dF2));
	dV[14] = ((2 * ((dLaenge * dLaenge)) * dF2));
	dV[15] = ((dCx * dCx) * dF1 + (dCy * dCy) * 12 * dF2);
	dV[16] = ((dCx * dCy) * (dF1 - (12 * dF2)));
	dV[17] = (-dCy * (-6 * dLaenge * dF2));
	dV[18] = (((dCy * dCy) * dF1) + ((dCx * dCx) * 12 * dF2));
	dV[19] = (dCx * (-6 * dLaenge * dF2));
	dV[20] = ((4 * ((dLaenge * dLaenge)) * dF2)); 
	
	K.SetBlock(21,0,dV);
	
	return K;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: VektorStack BalkenGelenk(int nPos, double dX1, double dX2, double dY1, 
//					double dY2, double dEM, double dA, double dIy)
// Beschreibung	: Ermittelt die Steifigkeitsmatrix für ein Balkenelement mit Gelenk
// Parameter
// iPos			: Position des Gelenks (1->links/ 2->rechts)
// dX1			: X-Position Kn.1
// dY1			: Y-Position Kn.1
// dX2			: X-Position Kn.2
// dY2			: Y-Position Kn.2
/////////////////////////////////////////////////////////////////////////////////////////////////
Vektor BalkenGelenk(int iPos, double dX1, double dX2, double dY1, double dY2, 
						 double dEM, double dA, double dIy)
{
	Vektor	K;
	double dT[ 7 ];
	
	// Ermittlung der Winkelbeziehungen
	d32 dX21 = dX2 - dX1;
	d32 dY21 = dY2 - dY1;
	d32 dL = MathUtils<Core::d32>::getLength( dX21, dY21 );
	d32 dF1 = (dEM * dA) / dL; 
	d32 dCx  = dX21 / dL;
	d32 dCy  = dY21 / dL;

	// Initialisierung der Elementsteifugkeitsmatrix
	K.DeclVektor( 21 );
	dT[ 0 ] = 0;
	dT[ 1 ] = dCx * dCx;	// cos^2
	dT[ 2 ] = dCx * dCy;	// cos * sin
	dT[ 3 ] = dCy * dCy;	// sin^2

	// Definition der Elementsteifigkeitsmatrix für ein Balkenelement mit 
	// einem Gelenk links
	if (iPos==1) 
	{
/*	dV[0] = (dT[1] * dF1 + dT[3] * ((3 * dEM * dIy) / (dL * dL * dL)));
	dV[1] = (dT[2] * (dF1 - ((3 * dEM * dIy) / (dL * dL * dL))));
	dV[2]  = 0;
	dV[3]  = (dT[1] * -1 * dF1 + dT[3] * ((-3 * dEM * dIy) / (dL * dL * dL)));
	dV[4]  = (dT[2] * (-1 * dF1 - ((-3 * dEM * dIy) / (dL * dL * dL))));
	dV[5]  = (-dCy * ((3 * dEM * dIy) / (dL * dL)));
	dV[6]  = (dT[3] * dF1 + dT[1] * ((3 * dEM * dIy) / (dL * dL * dL)));
	dV[7]  = 0;
	dV[8]  = (dT[2] * (-1 * dF1 - ((-3 * dEM * dIy) / (dL * dL * dL))));
	dV[9]  = (dT[3] * -1 * dF1 + dT[1] * ((-3 * dEM * dIy) / (dL * dL * dL)));
	dV[10] = (dCx * ((3 * dEM * dIy) / (dL * dL)));
	dV[11] = (double) 0.001;
	dV[12] = 0;
	dV[13] = 0;
	dV[14] = 0;
	dV[15] = (dT[1] * dF1 + dT[3] * ((3 * dEM * dIy) / (dL * dL * dL)));
	dV[16] = (dT[2]*(dF1 - ((3 * dEM * dIy) / (dL * dL * dL))));
	dV[17] = (-dCy * ((-3 * dEM * dIy) / (dL * dL)));
	dV[18] = (dT[3] * dF1 + dT[1] * ((3 * dEM * dIy) / (dL * dL * dL)));
	dV[19] = (dCx * ((-3 * dEM * dIy) / (dL * dL)));
	dV[20] = ((3 * dEM * dIy) / dL);*/

		K.setVektor(1, (dT[1] * dF1 + dT[3] * ((3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(2, (dT[2] * (dF1 - ((3 * dEM * dIy) / (dL * dL * dL)))));
		K.setVektor(3, 0);
		K.setVektor(4, (dT[1] * -1 * dF1 + dT[3] * ((-3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(5, (dT[2] * (-1 * dF1 - ((-3 * dEM * dIy) / (dL * dL * dL)))));
		K.setVektor(6, (-dCy * ((3 * dEM * dIy) / (dL * dL))));
		K.setVektor(7, (dT[3] * dF1 + dT[1] * ((3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(8, 0);
		K.setVektor(9, (dT[2] * (-1 * dF1 - ((-3 * dEM * dIy) / (dL * dL * dL)))));
		K.setVektor(10, (dT[3] * -1 * dF1 + dT[1] * ((-3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(11, (dCx * ((3 * dEM * dIy) / (dL * dL))));
		K.setVektor(12, 0.001);
		K.setVektor(13, 0);
		K.setVektor(14, 0);
		K.setVektor(15, 0);
		K.setVektor(16, (dT[1] * dF1 + dT[3] * ((3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(17, (dT[2]*(dF1 - ((3 * dEM * dIy) / (dL * dL * dL)))));
		K.setVektor(18, (-dCy * ((-3 * dEM * dIy) / (dL * dL))));
		K.setVektor(19, (dT[3] * dF1 + dT[1] * ((3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(20, (dCx * ((-3 * dEM * dIy) / (dL * dL))));
		K.setVektor(21, ((3 * dEM * dIy) / dL));
	}

	// Definitin der ElementSteifigkeitsmatrix für ein Balkenelement
	// mit einem Gelenk rechts
	if (iPos==2) {
/*	dV[0] = 
	dV[1] = 
	dV[2]  = 
	dV[3]  = 
	dV[4]  = 
	dV[5]  = 
	dV[6]  = 
	dV[7]  = 
	dV[8]  = 
	dV[9]  = 
	dV[10] = 
	dV[11] = 
	dV[12] = 
	dV[13] = 
	dV[14] = 
	dV[15] = 
	dV[16] = 
	dV[17] = 
	dV[18] = 
	dV[19] = 
	dV[20] = */

		K.setVektor(1, (dT[1] * dF1 + dT[3] * ((3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(2, (dT[2] * (dF1 - ((3 * dEM * dIy) / (dL * dL * dL)))));
		K.setVektor(3, (-dCy * ((3 * dEM * dIy) / (dL * dL))));
		K.setVektor(4, (dT[1] * -1 * dF1 + dT[3] * ((-3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(5, (dT[2] * (-1 * dF1 - ((-3 * dEM * dIy) / (dL * dL * dL)))));
		K.setVektor(6, 0);
		K.setVektor(7, (dT[3] * dF1 + dT[1] * ((3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(8, (dCx * ((3 * dEM * dIy) / (dL * dL))));
		K.setVektor(9, (dT[2] * (-1 * dF1 - 0)));
		K.setVektor(10, (dT[3] * -1 * dF1 + dT[1] * ((-3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(11, 0);
		K.setVektor(12, (((3 * dEM * dIy) / dL)));
		K.setVektor(13, (-dCy * ((-3 * dEM * dIy) /(dL * dL))));
		K.setVektor(14, (dCx * ((-3 * dEM * dIy) /(dL * dL))));
		K.setVektor(15, 0);
		K.setVektor(16, (dT[1] * dF1 + dT[3] * ((3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(17, (dT[2] * (dF1 - ((3 * dEM * dIy) / (dL * dL * dL)))));
		K.setVektor(18, 0);
		K.setVektor(19, (dT[3] * dF1 + dT[1] * ((3 * dEM * dIy) / (dL * dL * dL))));
		K.setVektor(20, 0);
		K.setVektor(21, 0);
	}

	return K;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: CalcMoment()
// Beschreibung	: Berechnet das Moment am Anfang und am Ende für ein Balken-Element
// Parameter
// Deform		: Vektor, in dem die Verformungsparamter des Elementes gesichert sind
// dL			: Länge des Elementes
// dEM			: E-Modul des Elementes
// dIy			: Trägheitsmoment 2.er Ordnung
// dM			: Array, in dem die berechneten Querschnitte gespeichert werden 
/////////////////////////////////////////////////////////////////////////////////////////////////
void CalcMoment(double *dDef, double dK1[2], double dK2[2], double dL, double dEM, 
				  double dIy, double *dM)
{
	int    iI1;
	double dF, dV[6], dX21, dY21, dCx, dCy, dTrans[6];

	// Ermittlung der Biegesteifigkeit
	dF = -dEM * dIy;

	// Ermittlung der Längen 
	dX21 = dK2[0] - dK1[0];
	dY21 = dK2[1] - dK1[1];
	
	// Ermittlung von sin und cos 
	dCx	= dX21 / dL;
	dCy	= dY21 / dL;
	
	if ((dK1[1] - dK2[1])>0) 
		dCx = -dCx;
	if ((dK1[0] - dK2[0])<0) 
		dCy = -dCy;

	TransformDeform(dDef, dCx, dCy, dTrans, TRANS);

	// Ermittlung des Momentes am Knoten 1
	dM[0] = 0;
	dV[0] = dV[3] = 0;
	dV[1] = (-6 * dF) / (dL * dL);
	dV[2] = (-4 * dF) / dL;
	dV[4] = (6  * dF) / (dL * dL);
	dV[5] = (-2 * dF) / dL;
	for (iI1=0; iI1<6; iI1++)
		dM[0] = dM[0] + (dV[iI1] * dTrans[iI1]);

	// Ermittlung des Momentes am Knoten 2
	dM[1] = 0;
	dV[0] = dV[3] = 0;
	dV[1] = (6  * dF) / (dL * dL);
	dV[2] = (2  * dF) / dL;
	dV[4] = (-6 * dF) / (dL * dL);
	dV[5] = (4  * dF) / dL;
	for (iI1=0; iI1<6; iI1++)	
		dM[1] = dM[1] + (dV[iI1] * dTrans[iI1]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: CalcQuer()
// Beschreibung	: Berechnet die Querkraft am Anfang und am Ende für ein Balken-Element
// Parameter
// Deform		: Vektor, in dem die Verformungsparamter des Elementes gesichert sind
// dL			: Länge des Elementes
// dEM			: E-Modul des Elementes
// dIy			: Trägheitsmoment 2.er Ordnung
// dQ			: Array, in dem die berechneten Querkräfte gespeichert werden
/////////////////////////////////////////////////////////////////////////////////////////////////
void CalcQuer (double *dDef, double dK1[2], double dK2[2], double dL, double dEM, 
				 double dIy, double *dQ)
{
	int    iI1;
	double dF, dV[6], dX21, dY21, dCx, dCy, dTrans[6];
	
	// Berechnung Faktoren
	dF	 = -dEM * dIy;	
	dX21 = dK2[0] - dK1[0];
	dY21 = dK2[1] - dK1[1];
	
	// Berechnung der Winkelbeziehungen
	dCx	= dX21 / dL;
	dCy	= dY21 / dL;
	
	if ((dK1[1] - dK2[1])>0) 
		dCx = -dCx;
	if ((dK1[0] - dK2[0])<0) 
		dCy = -dCy;

	// Transformation der Koordinaten
	TransformDeform(dDef, dCx, dCy, dTrans, TRANS);

	// Berechnung Querkraft Knoten 1
	dQ[0] = 0;
	dV[0] = dV[3] = 0;
	dV[1] = (12  * dF) / (dL * dL *dL);
	dV[2] = (6   * dF) / (dL * dL);
	dV[4] = (-12 * dF) / (dL * dL * dL);
	dV[5] = (6   * dF) / (dL * dL);
	for (iI1=0; iI1<6; iI1++)
		dQ[0] += (dV[iI1] * dTrans[iI1]);

	// Berechnung Querkraft Knoten 2
	dQ[1] = 0;
	dV[0] = dV[3] = 0;
	dV[1] = (12  * dF) / (dL * dL * dL);
	dV[2] = (6   * dF) / (dL * dL);
	dV[4] = (-12 * dF) / (dL * dL * dL);
	dV[5] = (6   * dF) / (dL * dL);
	for (iI1=0; iI1<6; iI1++)
		dQ[1] += (dV[iI1] * dTrans[iI1]);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: CalcLaeng
// Beschreibung	: Berechnet die konstante Längskraft für ein Balken-Element
// Parameter
// Deform		: Vektor, in dem die Verformungsparamter des Elementes gesichert sind
// dL			: Länge des Elementes
// dEM			: E-Modul des Elementes
// dA			: Querschnittsfläche des Balkenelementes
// dN			: Array, in dem die Laengskräfte gespeichert werden
/////////////////////////////////////////////////////////////////////////////////////////////////
void CalcLaeng (double *dDef, double dK1[2], double dK2[2], double dL, double dEM,
				  double dA, double *dN)
{
	register int iI1;
	double       dF, dV[6], dX21, dY21, dCx, dCy, dTrans[6];

	// Berechnung der Steifigkeiten
	dF   = dEM * dA;
	dX21 = dK2[0] - dK1[0];
	dY21 = dK2[1] - dK1[1];
	
	// Berechnung der Winkelbeziehngen
	dCx		= dX21 / dL;
	dCy		= dY21 / dL;
	if ((dK1[1] - dK2[1])>0) 
		dCx = -dCx;
	if ((dK1[0] - dK2[0])<0) 
		dCy = -dCy;

	// Transformation der Deformationen
	TransformDeform(dDef, dCx, dCy, dTrans, TRANS);

	// Berechnung Längskraft Knoten 1 und 2
	dN[0] = dN[1] = 0;
	dV[1] = dV[2] = dV[4] = dV[5] = 0;
	dV[0] = (-1 * dF) / dL;
	dV[3] = (1  * dF) / dL;
	for (iI1=0; iI1<6; iI1++)
		dN[0] += (dV[iI1] * dTrans[iI1]);
	
	dN[1] = dN[0];
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: CalcMomentGelenk (VektorStack Deform, double dL, double dEm, 
//					double dIy, int iArt)
// Beschreibung	: Ermittelt den Momentenwert bei einem Balkenelement mit Gelenk
// Parameter
// dDef			: Array mit den Elementverformungen
// dK1			: Koordinaten für Knoten 1
// dK2			: Koordinaten für Knoten 2
// dL			: Länge des Elements
// dEm			: E-Modul des Querschnitts
// dIy			: Trägheitsmodul 2.er Ordnung
// *dM			: Pointer auf Array, in dem die Momente geschrieben werden
// iArt			: Art des Elementes (3->Gelenk lings/4->Gelenk rechts)
/////////////////////////////////////////////////////////////////////////////////////////////////
void CalcMomentGelenk (double *dDef, double dK1[2], double dK2[2], double dL, 
					   double dEm, double dIy, double *dM, int iArt )
{
	double dV[6], dTrans[6];

	// Ermittlung der Steifigkeits-Parameter
	const double dF = (-3 * dEm * dIy) / (dL * dL);	
	
	// Ermittlung der Winkelbeziehungen
	Core::d32 dCx = (dK2[0] - dK1[0]) / dL;
	Core::d32 dCy = (dK2[1] - dK1[1]) / dL;

	if ((dK1[1] - dK2[1])>0) 
		dCx = -dCx;
	if ((dK1[0] - dK2[0])<0) 
		dCy = -dCy;

	TransformDeform( dDef, dCx, dCy, dTrans, TRANS );
	
	if (iArt==GELLEFT) 
	{ 
		// Wenn Gelenk links 
		dM[ 0 ] = 0.0;					// Moment am Knoten 1 = 0
		dV[ 0 ] = 0.0;	// Berechnung Knoten 2
		dV[ 1 ] = dF * 1.0;
		dV[ 2 ] = 0.0;
		dV[ 3 ] = 0.0;
		dV[ 4 ] = -1.0 * dF;
		dV[ 5 ] = dL * dF;
		for ( Core::i32 i=0; i<6; i++)
			dM[ 1 ] += ( dV[ i ] * dTrans[ i ] );
	}

	if (iArt==GELRIGHT) 
	{ // Wenn Berechnung rechts
		dM[ 1 ] = 0.0;			// Moment am Knoten 2 = 0
		dV[ 0 ] = 0.0;			// Berechnung Knoten 1
		dV[ 1 ] = 1 * dF;
		dV[ 2 ] = dL * dF;
		dV[ 3 ] = 0.0;
		dV[ 4 ] = -dF * 1;
		dV[ 5 ] = 0.0;
		for ( Core::i32 i=0; i<6; i++)
			dM[ 0 ] += ( dV[ i ] * dTrans[ i ] );
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		:CalcQuerGelenk (double *dDef, double dK1[2], double dK2[2], double dL, 
//					 double dEm, double dIy, double *dQ, int iArt)
// Beschreibung	: Berechnet die Querkräfte für die Knoten eines Elementes mit Gelenk links oder 
//					rechts
// Parameter
// *dDef		: Pointer auf den Array, in dem die Knotendeformationen gespeichert sind
// dK1[]		: Array, in dem die Koordinaten des 1.Knotens gespeichert sind
// dK2[]		: Array, in dem die Koordianten des 2.Knotens gespeichert sind
// dL			: Länge des Elementes
// dEm			: E-Modul des Elementes
// dIy			: Trägheitsmoment 2.er Ordnung des Elementes
// *dQ			: Pointer auf dem Array, in dem die berechneten Querkräfte gespeichert werden
// iArt			: Parameter für die Position des Elementes
/////////////////////////////////////////////////////////////////////////////////////////////////
void CalcQuerGelenk (double *dDef, double dK1[2], double dK2[2], double dL, 
					 double dEm, double dIy, double *dQ, int iArt)
{
	register int	iI1;
	double			dF = 0, dTrans[6], dV[6], dCx, dCy;
	
	// Ermittlung der Steifigkeits-Parameter
	dF = (-3 * dEm * dIy) / (dL * dL * dL);
	
	// Ermittlung der Winkelbeziehungen
	dCx = (dK2[0] - dK1[0]) / dL;
	dCy = (dK2[1] - dK1[1]) / dL;
	if ((dK1[1] - dK2[1])>0) 
		dCx = -dCx;
	if ((dK1[0] - dK2[0])<0) 
		dCy = -dCy;

	// Transformation der globalen Knotenkoordinaten in lokale Knotenkoordinaten
	TransformDeform(dDef, dCx, dCy, dTrans, TRANS);
	dQ[0] = dQ[1] = 0;
	
	// Berechnung der Querkräfte, wenn Gelenk am lokalen Knoten 1
	if (iArt==GELLEFT) {
		dV[0] =  0;		// Erstellung der Vektoren
		dV[1] = 1 * dF;
		dV[2] = 0;
		dV[3] = 0;
		dV[4] = -1 * dF;
		dV[5] = dF * dL;
		for (iI1=0; iI1<=5; iI1++)	// Berechnung der Querkraft am Kn.1
			dQ[0] += (dV[iI1] *dTrans[iI1]);

		dV[0] = 0;	// Erstellung des Vektors
		dV[1] = dF * -1;
		dV[2] = dF * dL;
		dV[3] = 0;
		dV[4] = -1 * dF;
		dV[5] = 0;
		for (iI1=0; iI1<=5; iI1++)	// Berechnung der Querkraft am Kn.2
			dQ[1] += (dV[iI1] * dTrans[iI1]);
	}

	// Berechnung der Querkräfte, wenn Gekenk am lokalen Knoten 2
	if (iArt==GELRIGHT) {
		dV[0] = dV[2] = dV[5] = 0;	// Erstellung des Vektors
		dV[1] = dF * dL;
		dV[3] = -1 * dF;
		dV[4] = dF;
		for (iI1=0; iI1<=5; iI1++)	// Berechnung der Querkraft am Kn.1
			dQ[0] += (dV[iI1] * dTrans[iI1]);

		dV[0] = dV[2] = dV[5] = 0;
		dV[1] = dF;
		dV[3] = -1 * dF;
		dV[4] = dF * dL;
		for (iI1=0; iI1<=5; iI1++)	// berechnung der querkraft am Kn.2
			dQ[1] += (dV[iI1] * dTrans[iI1]);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: TransformDeform (VektorStack Deform, double dCx, double dCy)
// Beschreibung	: Transformiert die globalen Deformationen in die lokalen Deformationen 
//					des Elementes um
// Parameter
// dDef			: Array, in dem die globalen Knotendeformationen gespeichert sind
// dCx			: Der COS
// dCy			: der SIN
// dTrans		: Array, in dem die lokalen Knotendeformationen gespeichert sind
////////////////////////////////////////////////////////////////////////////////////////////////
void TransformDeform (double *dDef, double dCx, double dCy, double *dTrans, int iT)
{		
	Core::i32 ret_code = 0;
	switch ( iT ) 
	{
	case TRANS:
		{
			dTrans[0] = dDef[0] * dCx + dDef[1] * dCy;	// Berechnung der lokalen Deformationen
			dTrans[1] = -1 * dDef[0] * dCy + dDef[1] * dCx;
			dTrans[2] = dDef[2];
			dTrans[3] = dDef[3] * dCx + dDef[4] * dCy;
			dTrans[4] = -1 * dDef[3] * dCy + dDef[4] * dCx;
			dTrans[5] = dDef[5];
			ret_code = ErrorHandler::WT_OK;
		}
		break;

	case RETRANS:
		{
			dTrans[0] = dDef[0] * dCx - dDef[1] * dCy;	// Berechnung der lokalen Deformationen
			dTrans[1] = dDef[0] * dCy + dDef[1] * dCx;
			dTrans[2] = dDef[2];
			dTrans[3] = dDef[3] * dCx - dDef[4] * dCy;
			dTrans[4] = dDef[3] * dCy + dDef[4] * dCx;
			dTrans[5] = dDef[5];
			ret_code = ErrorHandler::WT_OK;

		}
		break;

	default:
		Logger::get()->fatal( "Not supported mode detected" );
		break;
	}
}
