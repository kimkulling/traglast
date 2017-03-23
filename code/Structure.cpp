/////////////////////////////////////////////////////////////////////////////////////////////////
// Programmfile : Structure.cpp
// Beschreibung	: Implementations of the methods from the class Structure
// Autor		: Kim Kulling
// Last mod.    : 06.12.2003
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"

using namespace Core;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method : Structure::Structure(void)
// Desc.  : Constructor of the 
/////////////////////////////////////////////////////////////////////////////////////////////////
Structure::Structure()
{
	pErr       = NULL;
	pCoords    = NULL;
	pElements  = NULL;
	pMaterials = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method : Structure::InitInstances(void)
// Desc.  :
/////////////////////////////////////////////////////////////////////////////////////////////////
int Structure::InitInstances()
{
	if ((pErr = new ErrorHandler) == NULL)
		return ErrorHandler::WT_OUT_OF_MEM;
	if ((pCoords = new Vektor)==NULL)
		return ErrorHandler::WT_OUT_OF_MEM;
	if ((pElements = new Vektor)==NULL)
		return ErrorHandler::WT_OUT_OF_MEM;
	if ((pMaterials = new Vektor)==NULL)
		return ErrorHandler::WT_OUT_OF_MEM;

	return ErrorHandler::WT_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method : Structure::~Structure(void)
// Desc.  :
// Input:
//   iNum    :
//   iIndex  :
//   iStart  :
//   *pBlock :
/////////////////////////////////////////////////////////////////////////////////////////////////
int Structure::SetData_Blocked(int iNum, int iIndex, int iStart, double *pBlock)
{
	// Checking for errors
	if (pBlock==NULL || iNum==0 || iIndex<0)
		return ErrorHandler::WT_ERR;

	switch (iIndex) {
	case 1: // Coorddata
		if (!pCoords->SetBlock(iNum, iStart, pBlock))
			return ErrorHandler::WT_ERR;
		break;

	case 2: // Elementdatas
		if (!pElements->SetBlock(iNum, iStart, pBlock))
			return ErrorHandler::WT_ERR;
		break;

	case 3: // Materialdatas
		if (!pMaterials->SetBlock(iNum, iStart, pBlock))
			return ErrorHandler::WT_ERR;
		break;

	default:
		return ErrorHandler::WT_ERR;

	}

	return ErrorHandler::WT_OK;
}	

/////////////////////////////////////////////////////////////////////////////////////////////////
// Method : Structure::~Structure(void)
// Desc.  :
/////////////////////////////////////////////////////////////////////////////////////////////////
Structure::~Structure(void)
{
	if (pErr!=NULL)
		delete pErr;
	if (pCoords!=NULL)
		delete pCoords;
	if (pElements!=NULL)
		delete pElements;
	if (pMaterials!=NULL)
		delete pMaterials;
}