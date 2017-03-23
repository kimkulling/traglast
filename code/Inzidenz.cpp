/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : Inzidenz.cpp
// Beschreibung	: Implementierung für die Klasse InzidenzStack
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

using namespace Core;
using namespace FEStructure;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Inzidenz::Inzidenz()
// Beschreibung	: Konstruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
Inzidenz::Inzidenz()
{
	Nr		= 0;
	Pos		= 0;
	next	= NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Inzidenz::~Inzidenz()
// Beschreibung	: Destruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
Inzidenz::~Inzidenz()
{
	delete this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: InzidenzStack::InzidenzStack()
// Beschreibung	: Konstruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
InzidenzStack::InzidenzStack()
{
	iAnz				= 0;
	pInzAnker			= NULL;
	pInzidenzAktuell	= NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: InzidenzStack::InzidenzStack()
// Beschreibung	: Destruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
InzidenzStack::~InzidenzStack()
{
	// Leerer Destruktor
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: InzidenzStack::addInz()
// beschreibung	: Fügt einen neuen Inzidenzeintrag zum InzidenzStack hinzu
// Parameter
// n			: fortlaufende Nummer in der Liste
// p			: Zugeordnete Position in der Liste
/////////////////////////////////////////////////////////////////////////////////////////////////
int InzidenzStack::addInz(int n, int p)			
{
	Inzidenz *pIndex = pInzAnker;
	Inzidenz *pNewInzidenz = NULL;

	if ((pNewInzidenz = new Inzidenz)==NULL)
		return ErrorHandler::WT_FATAL_ERR;
	
	iAnz++;
	pNewInzidenz->Nr   = n;
	pNewInzidenz->Pos  = p;
	pNewInzidenz->next = NULL;
	
	if (pInzAnker==NULL) 
		pInzAnker = pNewInzidenz;
	else {
		while ((pIndex->next)!=NULL) 
			pIndex = pIndex->next;
		pIndex->next = pNewInzidenz;		
	}
	
	pInzidenzAktuell = pNewInzidenz;

	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: InzidenzStack::CheckInz(void)
// Beschreibung	: Überprüft, ob die Liste bereits Einträge enthält
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL InzidenzStack::CheckInz(void)
{
	Inzidenz *pIndex = pInzAnker;

	if (pIndex!=NULL)
		return ErrorHandler::WT_OK;
	
	return ErrorHandler::WT_ERR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: InzidenzStack::DeklInz(int iAnz)
// Beschreibung	: Erzeugt eine Liste von Inzidenzeinträgen mit 0
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL InzidenzStack::DeklInz(int iAnz)
{
	int iI;

	if (iAnz<=0) 
		return ErrorHandler::WT_ERR;

	for (iI=1; iI<iAnz+1; iI++)
		InzidenzStack::addInz(iI, 0);

	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: InzidenzStack::ReadInz()
// Beschreibung	: Liest den Eintrag an der angegebenen Position aus
// Parameter
// Pos			: Nummer des Inzidenzeintrags
/////////////////////////////////////////////////////////////////////////////////////////////////
int InzidenzStack::ReadInz(int iNr)
{
	
	if (pInzAnker==NULL)
		return 0;
	Core::i32 pos = -1;
	Inzidenz *pIndex = pInzAnker;
	if ((pIndex->Nr)==iNr) 
		pos = pIndex->Pos;
	else 
	{
		while ( ( pIndex->Nr)!=iNr )
			pIndex = pIndex->next;
		pos = pIndex->Pos;
	}

	return pos;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: InzidenzStack::SetInz ()
// Beschreibung	: Setzt den Inzidenzeintrag an der angegebene Stelle um
// Parameter
// Pos			: Position (Nummer) des Eintrages in der Liste
// Wert			: Knotennummer des Eintrages (zum Zuordnen)
/////////////////////////////////////////////////////////////////////////////////////////////////
void InzidenzStack::SetInz (int Pos, int Wert)
{
	Inzidenz *pIndex = pInzAnker;

	if (pIndex!=NULL) 
	{
		while ((pIndex->Nr)!=Pos)
			pIndex=pIndex->next;
		pIndex->Pos = Wert;
	}
}

	
/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: InzidenzStack::ShowInz()
// Beschreibung	: Zeigt den vorhandenen Inzidenzstack auf
/////////////////////////////////////////////////////////////////////////////////////////////////
void InzidenzStack::ShowInz(void)
{
	Inzidenz *pIndex = pInzAnker;
	if ( NULL == pInzAnker )
	{
		TRACE0( "Noch keine Inzidenzmatrix eingegeben!\n" );
		return;
	}

	int i1 = pIndex -> Nr;
	int i2 = pIndex -> Pos;
	while ((pIndex->next)!=NULL) {
		pIndex = pIndex->next;
		i1     = pIndex->Nr;
		i2     = pIndex->Pos;
	}

	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: InzidenzStack::DelInz(int iPos)
// Beschreibung	: Löscht einelne Inzidenzeinträge aus der Liste
// Parameter	
// iPos			: Position des Listeneintrages, der gelöscht werden soll
/////////////////////////////////////////////////////////////////////////////////////////////////
void InzidenzStack::DelInz(int iPos)
{
	Inzidenz *pIndex = pInzAnker;
	
	if (pInzAnker!=NULL) {
		while (((pIndex->next)!=NULL)||((pIndex->Nr)!=iPos))
			pIndex = pIndex->next;
		pInzidenzAktuell = pIndex->next;
		delete pIndex;
		pIndex = pInzAnker;
		while ((pIndex->Nr)!=(iPos-1))
			pIndex = pIndex->next;
		pIndex->next = pInzidenzAktuell;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: InzidenzStack::DelList(void)
// Beschreibung	: Löscht die gesamte Inzidenzliste
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL InzidenzStack::DelList()
{
	Inzidenz *pIndex = pInzAnker;

	if (pIndex==NULL)
		return ErrorHandler::WT_ERR;

	if (pIndex!=NULL) {
		iAnz				= 0;
		pInzAnker			= NULL;
		pInzidenzAktuell	= NULL;
	}

	return ErrorHandler::WT_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode zur Erstellung der Element-Inzidenztabelle. Hierzu werden die Anfangs- und Endknoten
// aus den Elementklassen gelesen und in die Inzidenztabelle Inz eingetragen
// Eingehende Parameter:
// AnzEle					: Anzahl der Elemente
// iFGKno					: Freiheitsgrade der Knoten
// Inz						: Inzidenztabelle
// pWork					: Zeiger auf die Elemente
/////////////////////////////////////////////////////////////////////////////////////////////////
InzidenzStack MakeInzidenz(int iAnzEle, int iEleKno, ElementStack ElementEingabe,
						   InzidenzStack Inz)
{
	BOOL	bFlag = TRUE;
	int		i=0, ii=0, n1=0, n2=0, iI1, iInit=0;
	
	// Checking for errors
	if ( 0 == iAnzEle ) 
	{
		TRACE0("Es sind noch keine Elemente eigegeben worden!\n");
		bFlag = FALSE;
	}	
	
	if (!Inz.CheckInz()) {
		iInit = (iAnzEle * iEleKno);
		for (iI1=1; iI1<=iInit; iI1++)
			Inz.addInz(iI1, 0);
	}

	// Wenn nicht die erste Berechnung
	if (bFlag) { // Wenn keine Fehler vorhanden, dann erstelle Inzidenztabelle
		for (i=1; i<=iAnzEle; i++) { // Sooft durchlaufen, wie Elemente da sind
			for(ii=1; ii<=iEleKno; ii++) { // Schleife für Anfangs und Endknoten
				n1++;
				n2 = ElementEingabe.ReadElement(i,ii, iAnzEle);		// Lese Anfangs- und Endknoten
				Inz.SetInz(n1,n2);							// Füge Element der Liste hinzu
			}
		}		
	}

	return Inz;
}