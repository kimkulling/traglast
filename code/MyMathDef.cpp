/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : 
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

extern struct tm *pTimeNow;

namespace Math
{

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: round (double dX)
// Beschreibung	: Rundet Werte auf und ab
// Parameter
// dX			: Wert vom Typ double, der gerundet werden soll
// R�ckgabewert	: dX ohne Kommastellen
/////////////////////////////////////////////////////////////////////////////////////////////////
int round (double dX)
{
	return (int) ((fmod(dX,1.0) >= 0.5) ? ceil(dX) : floor(dX));
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funktion		: GetDate(void)
// Beschreibung	: In die globale VAtiable pTimeNow wird das momentane Datum hineingeschrieben
// R�ckgabewert	: TRUE, wenn erfolgreich
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL GetDate()
{
	time_t myTime;
	
	time (&myTime);
	pTimeNow = localtime(&myTime);

	return TRUE;
}

} // Namespace Math
