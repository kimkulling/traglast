/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : 
// Beschreibung	: 
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __LAST_INCLUDED__H
#define __LAST_INCLUDED__H


/////////////////////////////////////////////////////////////////////////////////////////////////
// Klasse		: Last
// Beschreibung	: Klasse zum Sichern einzelner Lastdaten
/////////////////////////////////////////////////////////////////////////////////////////////////
class Last
{
public:
	int Nr;					// Nummer der Last 
	int KnNr;				// Knotennummer, auf dem die Last sitzt
	double dXWert;			// Wert der Last in X-Richtung
	double dYWert;			// Wert der Last in Y-Richtung
	double dMWert;			// Wert des Momentes um die Y-Achse
	int iArt;				// Wert zu Ermittlung der Art der Last
	Last *pNext_Last;		// Pointer auf den n�chsten Eintrag
	// Konstruktor
	Last();

	// Destruktor
	~Last();
};

/////////////////////////////////////////////////////////////////////////////////////////////////
// Klasse		: LastStack
// Beschreibung	: Klasse zum Anlegen einer Liste von Lastdaten 
/////////////////////////////////////////////////////////////////////////////////////////////////

class LastStack
{
private:
	Last *pLastAnker;
	Last *pLastAktuell;

public:
	int iLastNr;	
	
	// Konstruktor
	LastStack();

	// Destruktor
	~LastStack();

	// Methode zum Anf�gen eines lasteintrages
	void addLast(int iKnNr, double dXWert, double dYWert, double dMWert, int iArt);
	
	// Methode zum Auslesen
	double readLast(int Pos, int art);

	// Methode zum �berarbeiten einzelner Eintr�ge
	BOOL setLast(int Nr, int iKnNr, double dXWert, double dYWert, double dMWert, BOOL bX, BOOL bY, BOOL bZ);

	// Methode zum Anzeigen des LastStacks
	void ShowLast(int Anz);
};

#endif