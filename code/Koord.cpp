/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : 
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"

using namespace FEStructure;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Koord::Koord
// Beschreibung	: Konstruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
Koord::Koord()
{
	Nr			= 0;
	XPos		= 0;
	YPos		= 0;
	Xhold		= 0;
	Yhold		= 0;
	Zhold		= 0;
	NrXhold		= 0;
	NrYhold		= 0;
	NrZhold		= 0;
	pNext_Koord	= NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Koord::~Koord
// Beschreibung	: Destruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
Koord::~Koord(void)
{
/*	if (pNext_Koord!=NULL)
		delete pNext_Koord;*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::KoordStack
// Beschreibung	: Konstruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
KoordStack::KoordStack(void)
{
	iAnz = 0;
	pKoordAnker		= NULL;
	pKoordAktuell	= NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::~KoordStack
// Beschreibung	: Destruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
KoordStack::~KoordStack(void)
{
	// empty
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method : KoordStack::GetNumber(void)
// Desc.  :
// <-- : Number of coords
/////////////////////////////////////////////////////////////////////////////////////////////////
int KoordStack::GetNumber(void)
{
	if (iAnz==0)
		return 0;

	return iAnz;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::addKoord
// Beschreibung	: Fügt neue Koordinateneinträge der Liste hinzu
/////////////////////////////////////////////////////////////////////////////////////////////////
void KoordStack::addKoord(double dX, double dY, int iKn)
{
	Koord *pIndex = NULL;
	Koord *pNewKoord = new Koord;

	pNewKoord->Nr   = iKn;
	pNewKoord->XPos = dX;
	pNewKoord->YPos = dY;
	pNewKoord->pNext_Koord = NULL;
	iAnz++;
	if (pKoordAnker==NULL) 
		pKoordAnker = pNewKoord;
	else {
		pIndex = pKoordAnker;
		while ((pIndex->pNext_Koord)!=NULL) 
			pIndex = pIndex->pNext_Koord; // gehe ans Ende der Liste
		pIndex -> pNext_Koord = pNewKoord;
	}
	
	pKoordAktuell = pNewKoord;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::setKoord(double x, double y, int kn)
// Beschreibung	: Ersetzt die Knoten
/////////////////////////////////////////////////////////////////////////////////////////////////
void KoordStack::setKoord(double x, double y, int kn, BOOL bX, BOOL bY, BOOL bZ)
{
	Koord	*pIndex = pKoordAnker;
	BOOL	bF = FALSE;

	if (pIndex!=NULL) {
		if (pIndex->Nr==kn)
			bF = TRUE;
		else {
			if (!bF)
				while ((pIndex->Nr)!=kn)
					pIndex = pIndex->pNext_Koord;
			pIndex->XPos = x;
			pIndex->YPos = y;
			if (bX)
				pIndex->Xhold = 1;
			else
				pIndex->Xhold = 0;
			if (bY)
				pIndex->Yhold = 1;
			else
				pIndex->Yhold = 0;
			if (bZ)
				pIndex->Zhold = 1;
			else
				pIndex->Zhold = 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::delKoord(int nr, int ak)
// Beschreibung	: Löscht die angegebene Nummer
// Parameter
// nr			: Knotennummer des Knotens, der gelscht werden soll
/////////////////////////////////////////////////////////////////////////////////////////////////
void KoordStack::delKoord(int nr)		// Koordinate Nummer nr löschen
{
	Koord *pIndex;								// die anderen Knotennummern werden nicht zurückgesetzt!
	bool flag = true;

	if (nr>=iAnz) 
		flag = false;

	if (flag) {
		if (pKoordAktuell==pKoordAnker) {
			pKoordAnker = pKoordAktuell-> pNext_Koord;
			delete pKoordAktuell;
			pKoordAktuell = pKoordAnker;
		}
		else {
			pIndex = pKoordAnker;
			while ((pIndex!=NULL) && (pIndex->pNext_Koord!=pKoordAktuell)) 
				pIndex=pIndex->pNext_Koord;
			pIndex->pNext_Koord = pKoordAktuell;
			delete pKoordAktuell;
			pKoordAktuell = pIndex;
		}
		Koord *pLoeschKoord = pKoordAnker;
		pKoordAnker = pKoordAnker->pNext_Koord;
		delete pLoeschKoord;	
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::CheckKoord(double dX, double dY)
// Beschreibung	: Gibt die Koordinate an der angegebenen Position zurück oder 0, wenn es noch
//					keine Koordiate an der Position gibt
// Parameter
// dX			: X-Koordinate
// dY			: Y-Koordinate
// Rückgabewert	: Nummer der Koordinate oder 0
/////////////////////////////////////////////////////////////////////////////////////////////////
int KoordStack::CheckKoord(double dX, double dY)
{
	Koord *pIndex = pKoordAnker;
	
	if (pKoordAnker!=NULL) {
		while ((pIndex->pNext_Koord)!=NULL) 
			if ((pIndex->XPos==dX)&&(pIndex->YPos==dY)) 
				return pIndex->Nr;

			return 0;
	}
	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::ReadKoord
// Beschreibung	: Liest die jeweiligen Daten aus dem Listeneintrag
// Parameter	:
// nr			: Nummer der Koordinate
// art			: Art der zurückgegebenen Informationen
// 1			: X-Position
// 2			: Y-Position
/////////////////////////////////////////////////////////////////////////////////////////////////
double KoordStack::ReadKoord(int nr, int art)
{
    Koord	*pIndex = pKoordAnker;
	
	if (pIndex==NULL) 
		return 0;

	while ((pIndex->Nr)!=nr) 
		pIndex=pIndex->pNext_Koord;
	switch (art) {
		case 1:			
			return pIndex->XPos;
			break;

		case 2:
			return pIndex->YPos;
			break;

		default:
			TRACE0("Fehler beim Lesen der Koordinaten-Daten!\n");
			break;
	}

	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::GetXMin
// Beschreibung	: Gibt den kleinsten X-Wert zurück
// Rückgabewert	: Kleinster X-Wert der Liste
/////////////////////////////////////////////////////////////////////////////////////////////////
double KoordStack::GetXMin()
{
	Koord	*pIndex = pKoordAnker;
	double	dTemp = pIndex->XPos;

	while ((pIndex->pNext_Koord)!=NULL) {
		pIndex = pIndex->pNext_Koord;
		if (pIndex->XPos<dTemp)
			dTemp = pIndex->XPos;
	}
	return dTemp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::GetXMax
// Beschreibung	: Gibt den größten X-Wert zurück
// Rückgabewert	: Maximaler X-Wert
/////////////////////////////////////////////////////////////////////////////////////////////////
double KoordStack::GetXMax(void)
{
	Koord	*pIndex = pKoordAnker;
	double	dTemp = pIndex->XPos;

	while ((pIndex->pNext_Koord)!=NULL) {
		pIndex = pIndex->pNext_Koord;
		if (pIndex->XPos>dTemp)
			dTemp = pIndex->XPos;
	}
	return dTemp;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::GetYMin()
// Beschreibung	: Gibt den kleinsten Y-Wert zurück
/////////////////////////////////////////////////////////////////////////////////////////////////
double KoordStack::GetYMin(void)
{
	Koord	*pIndex = pKoordAnker;
	double	dTemp = pIndex->YPos;

	while ((pIndex->pNext_Koord)!=NULL) {
		pIndex = pIndex->pNext_Koord;
		if (pIndex->YPos<dTemp)
			dTemp = pIndex->YPos;
	}
	return dTemp;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::GetYMax()
// Beschreibung	: Gibt den größten Y-Wert zurück
// Rückgabewert	: Maximaler Y-Wert
/////////////////////////////////////////////////////////////////////////////////////////////////
double KoordStack::GetYMax()
{
	Koord	*pIndex = pKoordAnker;
	double	dTemp = pIndex->YPos;

	while ((pIndex->pNext_Koord)!=NULL)
	{
		pIndex = pIndex->pNext_Koord;
		if (pIndex->YPos>dTemp)
			dTemp = pIndex->YPos;
	}
	return dTemp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::ShowKoord
// Beschreibung	: Zeigt die Liste von Einträgen an
// Parameter	:
// KnNr			: Anzahl der Koordinaten
/////////////////////////////////////////////////////////////////////////////////////////////////
int KoordStack::ShowKoord(int /*KnNr*/)
{
	bool	bFlag=TRUE;
	int		xh =0, yh = 0, zh = 0;
	int		n; double x,y;
	Koord	*pIndex = pKoordAnker;

	if (pKoordAnker==NULL) 
		bFlag = FALSE;

	if (bFlag) {	
		n = pIndex->Nr; x= pIndex->XPos; y = pIndex->YPos;
		while (pIndex->pNext_Koord!=NULL) {
			pIndex = pIndex -> pNext_Koord;
			n  = pIndex->Nr;
			x  = pIndex->XPos;
			y  = pIndex->YPos;
			if(pIndex->Xhold) 
				xh = 1;
			if(pIndex->Yhold) 
				yh = 1;
			if(pIndex->Zhold) 
				zh = 1;
		}
	}
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KordSatck::SetRandbed
// Beschreibung	: setzt die Randbedingungen auf true oder false (bool-Werte)
// Parameter	:
// KnNr			: die Nummer des Knotens
// x,y,z		: Ranbedingung für FG x,y,z (true/false)
/////////////////////////////////////////////////////////////////////////////////////////////////
void KoordStack::SetRandbed(int KnNr, int x, int y, int z)
{
	Koord *pIndex = pKoordAnker;
	
	if ((pIndex->pNext_Koord)==NULL) 
		pIndex = pKoordAnker;
	else
	{
		while (((pIndex->Nr)!=KnNr)||(pIndex==NULL)) 
			pIndex =pIndex->pNext_Koord;
	}
	pIndex -> Xhold = x;
	pIndex -> Yhold = y;
	pIndex -> Zhold = z;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::ReadRandbed
// Beschreibung	: Liest die Randbedingungen zum Zusammenbau der K-Matrix aus
// Parameter	:
// KnNr			: Knotennummer 
// art			: Art der Randbedingung
// 1			: in X-Richtung
// 2			: in Y-Richtung
// 3			: Um X drehend
// Rückgabewert	: Randbedingung der angegebenen Koordinate und Art
/////////////////////////////////////////////////////////////////////////////////////////////////
int KoordStack::ReadRandbed(int KnNr, int art)
{
	Koord *pWork = pKoordAnker;
	if (KnNr==0 ||art==0)
		return FALSE;

	while ((pWork->Nr)!= KnNr) 
		pWork = pWork->pNext_Koord;
	switch (art) {
		case 1: return pWork->Xhold;
		case 2: return pWork->Yhold;
		case 3: return pWork->Zhold;
		default:return FALSE;
			
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KordStatck::top
// Beschreibung	: Gibt den obersten Wert zurück
// Parameter
// KnNr			: die Nummer des Knotens
// x,y,z		: Ranbedingung für FG x,y,z (true/false)
// Rückgabewert	: Erster EIntrag in der Liste
/////////////////////////////////////////////////////////////////////////////////////////////////
int KoordStack::top(void)
{
	return pKoordAnker->Nr;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: KoordStack::DelList()
// Beschreibung	: Löscht die gesamte Liste
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL KoordStack::DelList()
{
	if (pKoordAnker!=NULL) {
		iAnz			= 0;
		pKoordAnker		= NULL;
		pKoordAktuell	= NULL;
		return TRUE;
	}
	return FALSE;
}