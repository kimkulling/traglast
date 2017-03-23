/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : Band.h
// Desc.       : Prototypes for functions
// Autor       : Kim Kulling
// Last mod.   : 13.12.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __BAND_INCLUDED__H
#define __BAND_INCLUDED__H

#include "NodeStack.h"

#ifdef _WIN32
#if _MSC_VER > 1000
#pragma once
#endif
#endif

// Funktions-Prototypen /////////////////////////////////////////////////////////////////////////
int Band( int iGesEle,  int iFGKno,  int iEleKn, InzidenzStack In );
Vektor    MakeStuetzStack( Vektor MyLager, FEStructure::NodeStack nodes );
Vektor    MakeLastVektor(LastStack LastEingabe, int iFGKno);
Vektor    SystemAuf (const int EleNummer, const int FGKno, const int EleKno, const int Band,
					InzidenzStack Inz, Vektor EleSteif, Vektor SysSteif);
Vektor    Stuetzung(int LagerKno, int FGKno, int Band, Vektor Lager, Vektor SysSteif);
Vektor    Knotenlast(int LastKno, int FGKno, Vektor Last,Vektor SysLast );
int       Elementlast(int EleNummer, int EleKno, int FGKno, InzidenzStack Inz, Vektor EleLast);
void ElementDef(int EleNummer, int EleKno, int FGKno, InzidenzStack Inz, Vektor SysDef, double *dDef);
int       GetKoord (int iNr, FEStructure::NodeStack Koor, double *dK1, double *dK2);
int       GetRandbed(int iKnNr, FEStructure::NodeStack Koord, double *dRand);
//int       GetRandbed(int iKnNr, FEStructure::KoordStack Koord, double *dRand);
int       GetMaterial (int iNr, FEStructure::MaterialStack Mat, double *dM);
int       GetElement(int iNr, FEStructure::ElementStack Ele, int *iEle);
LastStack GetIterLast(LastStack Last);
LastStack AddIterLast(LastStack Last, double dWert, Vektor Knoten );
double    GetScale(int iAuflX, int iAuflY, double dXD, double dYD);
int       ClearDoubleArray(double *dArray, int iLenght);
LastStack SetPlastMoment (int iEle1, int iKn, InzidenzStack Inz, double dMpl, 
					 FEStructure::ElementStack Element, int iNeg);
double    CalcAdd(double dMax, double dDiff, double dMpl, double dW);
double    GetMaxLast(Vektor Vtemp, int iAnz, int iPos, Vektor Knoten, InzidenzStack Inz);
int       CalcEinzelMoment(double dMoment, double dL, double dA, double dB, double *dQ, double *dM);

#endif