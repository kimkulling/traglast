/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : 
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

using namespace Core;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Last::Last()
// Beschreibung	: Konstruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
Last::Last()
{
	Nr			= 0;
	KnNr		= 0;
	dXWert		= 0;
	dYWert		= 0;
	dMWert		= 0;
	iArt		= 0;
	pNext_Last	= NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Last::~Last()
// Beschreibung	: Destruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
Last::~Last(void)
{
	if (pNext_Last==NULL)
		delete pNext_Last;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: LastStack::LastStack()
// Beschreibung	: Konstruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
LastStack::LastStack()
{
	iLastNr		= 0; 
	pLastAnker	= NULL;
	pLastAktuell= NULL;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: LastStack::~LastStack()
// Beschreibung	: Destruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
LastStack::~LastStack()
{
//	delete pLastAnker;
//	delete pLastAktuell;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: LastStack::addLast()
// Beschreibung	: Fügt einen neuen Lasteintrag in den LastStack ein
// Parameter
// iNr			: Knotennummer, auf den die Last wirkt
// dXWert		: Wert der Knotenlast in X-Richtung
// dYWert		: Wert der Knotenlast in Y-Richtung
// dMWert		: Wert des Momentes um die Y-Achse
/////////////////////////////////////////////////////////////////////////////////////////////////
void LastStack::addLast(int iKnNr, double dXWert, double dYWert, double dMWert, int iArt)
{
	BOOL bAdded = FALSE;
	Last *pIndex = pLastAnker;
	Last *pNewLast = new Last;

	pNewLast->KnNr   = iKnNr;
	pNewLast->dXWert = dXWert;
	pNewLast->dYWert = dYWert;
	pNewLast->dMWert = dMWert;
	pNewLast->iArt 	 = iArt;
	pNewLast->pNext_Last = NULL;
	
	if (pIndex==NULL) { // Es ist der erste Eintrag
		pNewLast->Nr = 1;
		pLastAnker   = pNewLast;
		iLastNr++;
	}
	else { // Es gibt schon Einträge
		while ((pIndex->pNext_Last)!=NULL) {
			pIndex = pIndex->pNext_Last;
			if (iKnNr==pIndex->KnNr) { // Wenn auf  alten Knoten neue Last
				pIndex->dXWert += dXWert;
				pIndex->dYWert += dYWert;
				pIndex->dMWert += dMWert;
				bAdded = TRUE;
			}
		}
		if (!bAdded) { // Wenn Ende der Liste erreicht
			iLastNr++;
			pNewLast->Nr       = iLastNr;
			pIndex->pNext_Last = pNewLast;
			pLastAktuell       = pNewLast;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: LastStack::readLast()
// Beschreibung	: gibt die jeweilige Belastung zurück
// Parameter
// Pos			: Position des Eintrages im Lastvektor
// art			: Art des Rückgabewertes
// 1			: Gebe den Wert der Last in X-Richtung zurück
// 2			: Gebe den Wert der Last in Y-Richtung zurück
// 3			: Gebe den Wert des Momentes zurück
// 4			: Gebe die Knotennummer zurück
// 5			: Gibt die Art der Last zurück (1->Einzellast / 2->Streckenlast)
// Rückgabewert	: Gesuchte Last
/////////////////////////////////////////////////////////////////////////////////////////////////
double LastStack::readLast(int Pos, int art)
{
	Last *pWork = pLastAnker;

	if (pLastAnker==NULL)
		return 0;
	else
		while ((pWork->Nr)!=Pos) 
			pWork = pWork->pNext_Last;

	switch (art) {
		case 1: return pWork->KnNr;
		case 2: return pWork->dXWert;
		case 3: return pWork->dYWert;
		case 4: return pWork->dMWert;
		case 5: return pWork->iArt;
		default: return 0;
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: LastStack::setLast()
// Beschreibung	: setzt die Last an der angegebenen Position um
// Parameter
// Nr			: Nummer des Lasteintrages (dient der Navigation im Vektor)
// KnNr			: Knotennummer des Lasteintrages
// Wert			: Neuer WErt des Lasteintrages
// art			: Art des Vertauschens
// 1			: X-Wert zurückgeben
// 2			: Y-Wert zurückgeben
// 3			: Moment um die Y-Achse zurückgeben
// 4			: Knotennummer zurückgeben
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////

BOOL LastStack::setLast(int Nr, int iKnNr, double dXWert, double dYWert, double dMWert,
						BOOL bX, BOOL bY, BOOL bZ)
{
	Last *pIndex = pLastAnker;
	
	if (pIndex!=NULL) {
		// Wenn Lastnummer als Parameter übergeben wurde
		if (Nr!=0) {
			while ((pIndex->Nr)!=Nr) 
				pIndex = pIndex->pNext_Last;
		}

		// Wenn Knotennummer als Parameter übergeben wurde
		if ((iKnNr!=0)&&(Nr==0)) {
			while ((pIndex->KnNr)!=iKnNr)
				pIndex = pIndex->pNext_Last;
		}
		if (bX)
			pIndex->dXWert = dXWert;
		if (bY)
			pIndex->dYWert = dYWert;
		if (bZ)
			pIndex->dMWert = dMWert;
		
		return TRUE;
	}
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: LastStack::ShowLast()
// Beschreibung	: Zeigt alle Lasten an
// Parameter
// iAnz			: Anzahl der Lasten
/////////////////////////////////////////////////////////////////////////////////////////////////
void LastStack::ShowLast(int Anz)
{
	Last *pIndex = pLastAnker;
	int Nr, KnNr, i;
	double dXWert, dYWert;
	bool flag = true;
	if (pLastAnker==NULL) {
		TRACE0("Es sind noch keine Lasten eingegeben worden!");
		flag = false;
	}
	if (flag) {
		for (i=1; i<=Anz; i++) {
			Nr   = pIndex->Nr;
			KnNr = pIndex->KnNr;
			dXWert = pIndex->dXWert;
			dYWert = pIndex->dYWert;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: CalcEinzelMoment(double dMoment, double dL, double dA, double dB, 
//					double *dQ, double *dM)
// Beschreibung	: Die Funktion errechnet die arbeitsäquvalenten Fnotenlasten für ein einzelnes
//					Moment auf einem Balken
// Parameter
// dMoment		: Größe des Momentes
// dL			: Länge des Momentes
// dA			: Abstand Moment Knoten 1
// dB			: Abstand Moment Knoten 2
// *dQ			: Pointer auf Querkraft
// *dM			: Pointer auf Momente
/////////////////////////////////////////////////////////////////////////////////////////////////
int CalcEinzelMoment(double dMoment, double dL, double dA, double dB, double *dQ, double *dM)
{
	double dAlpha, dBeta;

	dAlpha	= dA / dL;
	dBeta	= dB / dL;

	dQ[0]	= dMoment * (6/dL) * dAlpha * dBeta;
	dQ[1]	= -1 * dMoment * (6/dL) * dAlpha * dBeta;

	dM[0]	= dMoment * dBeta * (3 * dAlpha - 1);
	dM[1]	= dMoment * dAlpha * (3 * dBeta - 1);

	return ErrorHandler::WT_OK;
}