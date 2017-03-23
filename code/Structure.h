/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : Structure.h
// Beschreibung	: Class-Definitions of structure
// Autor		: Kim Kulling
// Last mod.    : 28.04.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STRUCTURE__H
#define __STRUCTURE__H

/////////////////////////////////////////////////////////////////////////////////////////////////
// Class : Structure
// Desc. : 
/////////////////////////////////////////////////////////////////////////////////////////////////
class Structure
{
private:
	Core::ErrorHandler *pErr;
	Vektor         *pCoords;
	Vektor         *pElements;
	Vektor         *pMaterials;

public:
	// Constructor
	Structure(void);

	// Method to init the instances of the classes
	int InitInstances(void);

	// Method to set coords blocksized
	int SetData_Blocked(int iNum, int iIndex, int iStart, double *pBlock);

	// Method to get coords blocksized
	int GetData_Blocked(int iNum, int iIndex, int iStart, double *pBlock);

	// Destructor
	~Structure(void);
};

#endif