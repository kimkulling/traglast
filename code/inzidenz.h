/////////////////////////////////////////////////////////////////////////////////////////////////
// Programfile : inzidenz.h
// Desc.       : 
// Author      : Kim Kulling
// Last mod.   : 09.01.2004
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __INZIDENZ_INCLUDED__H
#define __INZIDENZ_INCLUDED__H

/////////////////////////////////////////////////////////////////////////////////////////////////
///	\class	Inzidenz
///	\brief	Incidence stack entry.
/////////////////////////////////////////////////////////////////////////////////////////////////
class Inzidenz
{
public:
	int Nr;         ///< Number
	int Pos;        ///< Position
	Inzidenz *next; ///< Pointer to next inzidenz entry

public:
	/// Constructor
	Inzidenz();

	/// Destructor
	~Inzidenz();
};

/////////////////////////////////////////////////////////////////////////////////////////////////
///	\class	Inzidenzstack
///	\brief	Incodece data stack.
/////////////////////////////////////////////////////////////////////////////////////////////////
class InzidenzStack
{
private:
	Inzidenz *pInzAnker;				///< Pointer auf den ersten Eintrag in der liste
	Inzidenz *pInzidenzAktuell;			///< Pointer auf den momentanen Listeneintrag

public:
	int iAnz; 	///< Anzahl der Einträge

public:	
	// Constructor
	InzidenzStack();
	
	// Destruktor
	~InzidenzStack();

	// Hänge Eintrag an Liste an			
	int addInz(int n, int p); 
	
	///	Validates data.
	BOOL CheckInz();
	
	///	Returns the number of entries.
	int GetNumber() const 
	{
		return iAnz;
	}

	/// Methode, die prüft, ob es bereits Listeneinträge gibt
	int isEmpty() const 
	{
		if ( 0 == iAnz )
			return false; 
		return true;
	}

	//! Init a inzidenz-list
	BOOL DeklInz(int iAnz);	
	
	/// Read entry from list
	int ReadInz(int Pos);
	
	/// Setze Liste an Stelle Pos
	void SetInz (int Pos, int Wert);
	
	/// Zeige komplette Liste
	void ShowInz(void);
	
	/// Lösche einen Eitrag aus der Liste
	void DelInz(int iPos);
	
	/// Delete the complete List
	BOOL DelList();
};

/////////////////////////////////////////////////////////////////////////////////////////////////
// Functions-prototypes
/////////////////////////////////////////////////////////////////////////////////////////////////
///	Creates an inzidence data stack.
InzidenzStack MakeInzidenz(int iAnzEle, int iEleKno, FEStructure::ElementStack ElementEingabe, InzidenzStack Inz);

#endif