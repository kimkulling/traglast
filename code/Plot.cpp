/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : Plot.cpp
// Desc.       : Implementations of class plot
// Author      : Kim Kulling
// Last mod.   : 13.12.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

using namespace std;
using namespace Core;
using namespace FEStructure;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Plot::Plot()
// Beschreibung	: Konstruktor der Klasse Plot
/////////////////////////////////////////////////////////////////////////////////////////////////
Plot::Plot()
{
	nPos	= 0;
	dXpos	= 0;
	dYpos	= 0;
	dXdef     = 0;
	dYdef     = 0;
	dRot      = 0;
	pNextPlot = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: Plot::~Plot()
// Beschreibung	: Destruktor der Klasse Plot
/////////////////////////////////////////////////////////////////////////////////////////////////
Plot::~Plot()
{
	//
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: PlotStack::PlotStack()
// BEschreibung	: Konstruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
PlotStack::PlotStack()
{
	pPlotAnker		= NULL;
	pPlotAktuell	= NULL;
	nAnz			= 0;
	dScaleX			= 0;
	dScaleY			= 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: PlotStack::~PlotStack()
// Beschreibung	: Destruktor
/////////////////////////////////////////////////////////////////////////////////////////////////
PlotStack::~PlotStack()
{
	//
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: PlotStack::AddPlotKoord(int nPos, double dXpos, double dYpos, double dXdef, 
//					double dYdef, double dRot)
// Beschreibung	: Addiert einen Eintrag ans Ende des Stacks
// Parameter
// iPos			: Position in der Liste
// dXpos		: X-Koordinate
// dYpos		: Y-Koordinate
// dXdef		: Deformation in X-Richtung
// dYdef		: Deformation in Y-Richtung
// dXrot		: Rotation um die X-Achse
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL PlotStack::AddPlotKoord(int nPos, double dXpos, double dYpos, 
							 double dXdef, double dYdef, double dRot)
{
	Plot *pIndex		= pPlotAnker;
	Plot *pNewPlot		= new Plot;

	nAnz++;
	pNewPlot->nPos		= nPos;
	pNewPlot->dXpos		= dXpos;
	pNewPlot->dYpos		= dYpos;
	pNewPlot->dXdef		= dXdef;
	pNewPlot->dYdef		= dYdef;
	pNewPlot->dRot		= dRot;
	pNewPlot->pNextPlot	= NULL;
	
	if (pPlotAnker==NULL)
		pPlotAnker = pNewPlot;
	else {
		while ((pIndex->pNextPlot)!=NULL)
			pIndex = pIndex->pNextPlot;
		pIndex->pNextPlot=pNewPlot;
	}
	pPlotAktuell = pNewPlot;

	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: PlotStack::ReadPlot(int nPos, int nArt)
// Beschreibung	: Ließt an der angegebenen Position die Tragwerksinformationen aus dem Stack
//					aus.
// Parameter
// iPos			: Position, aus der die Werte aus dem Stack gelesen werden soll
// iArt			: Art der Auslesung
// Rückgabewert	: Je nach Art, siehe switch-Anweisung
/////////////////////////////////////////////////////////////////////////////////////////////////
double PlotStack::ReadPlot(int iPos, int iArt)
{
	Plot *pIndex = pPlotAnker;
	
	if (pIndex!=NULL) 
	{
		while (pIndex->nPos!=iPos)
			pIndex = pIndex->pNextPlot;

		switch (iArt) 
		{
			case 1: return pIndex->dXpos;
			case 2: return pIndex->dYpos;
			case 3: return pIndex->dXdef;
			case 4: return pIndex->dYdef;
			case 5: return pIndex->dRot;
			default: 
				return -1;
		}
	}

	return ErrorHandler::WT_ERR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: PlotStack::DelList()
// Beschreibung	: Setzt den Stack auf NULL zurück
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL PlotStack::DelList()
{
	nAnz	= 0;
	dScaleX	= 0;
	dScaleY	= 0;

	if (pPlotAnker!=NULL)
		pPlotAnker = NULL;
	if (pPlotAktuell!=NULL)
		pPlotAktuell = NULL;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Methode		: PlotStack::SavePlot(const char *lpSaveName)
// Beschreibung	: Speichert den Plot
// Parameter
// lpSaveName	: Dateiname
// Rückgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL PlotStack::SavePlot(const char *lpSaveName)
{
	Plot *pIndex = pPlotAnker;

	ofstream Datei(lpSaveName);

	if (pPlotAnker!=NULL) {
		while ((pIndex->pNextPlot)!=NULL) {
			Datei << "Nr: " << pIndex->nPos;
			Datei << "  X:  " << pIndex->dXpos;
			Datei << "  Y:  " << pIndex->dYpos;
			Datei << "  Xdef: " << pIndex->dXdef;
			Datei << "  Ydef: " << pIndex->dYdef;
			Datei << "  Yrot: " << pIndex->dRot << endl;
			pIndex = pIndex->pNextPlot;
		}
		return TRUE;
	}

	return FALSE;
}