//-------------------------------------------------------------------------------------------------
///	\file		Element.cpp
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class definition of Element and ElementStack.
///
/// This program is free software: you can redistribute it and/or modify
///	it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//-------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "ElementStack.h"

using namespace Core;
using namespace FEStructure;

//-------------------------------------------------------------------------------------------------
//	Default constructor.
ElementStack::ElementStack() :
	m_ElementMap()
{
	// empty
}

//-------------------------------------------------------------------------------------------------
//	Destructor.
ElementStack::~ElementStack()
{
	// empty
}

//-------------------------------------------------------------------------------------------------
//	Adds a new element definition.
void ElementStack::addElement(int iEleNr, int iN1, int iN2, int iMat, int iArt)
{
	Element pNewElement;
	
	pNewElement.ElementNr    = iEleNr;
	pNewElement.KnNr1        = iN1;
	pNewElement.KnNr2        = iN2;
	pNewElement.MatNr        = iMat;
	pNewElement.Balkenart    = iArt;
	m_ElementMap[ iEleNr ] = pNewElement;
}

//-------------------------------------------------------------------------------------------------
//	Deletes a element definition
bool ElementStack::delElement(int iEleNr)
{
	std::map<Core::i32, Element>::iterator it = m_ElementMap.find( iEleNr );
	if ( m_ElementMap.end() != it )
	{
		m_ElementMap.erase( it );
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
//	Modifiy an existent element definition.
bool ElementStack::setElement(int iEleNr, int iKn1, int iKn2, int iMat, int iArt)
{
	std::map<Core::i32, Element>::iterator it = m_ElementMap.find( iEleNr );
	if ( m_ElementMap.end() != it )
	{
		Element element = (*it).second;
		if (iArt!=0)
			element.Balkenart	= iArt;
		if (iEleNr!=0)
			element.ElementNr	= iEleNr;
		if (iKn1!=0)
			element.KnNr1		= iKn1;
		if (iKn2!=0)
			element.KnNr2		= iKn2;
		if (iMat!=0)
			element.MatNr		= iMat;
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
//	Check type of usage of a node in a existent element definition.
int ElementStack::CheckNode(int iNode, int iArt)
{
	std::map<Core::i32, Element>::iterator it = m_ElementMap.find( iNode );
	if ( m_ElementMap.end() != it )
	{
		Element element = (*it).second;
		if (iArt==1)
			return element.ElementNr;

		if (iArt==2) 
		{
			if (element.KnNr1==iNode)
				return 1;
			if (element.KnNr2==iNode) 
				return 2;
		}
	}
	return -1;
	/*Element *pIndex = pElementAnker;
	
	if (pElementAnker!=NULL) {
		while ((pIndex->KnNr1!=iNode) || (pIndex->KnNr2!=iNode) || (pIndex->pNextElement!=NULL)) {	
			if ((pIndex->KnNr1==iNode)||(pIndex->KnNr2==iNode)) { // Wenn Kn1. oder Kn2 == iNode
				if (iArt==1)
					return pIndex->ElementNr;

				if (iArt==2) {
					if (pIndex->KnNr1==iNode)
						return 1;
					if (pIndex->KnNr2==iNode) 
						return 2;
				}
			}
			
			// Fehlerüberprüfung
			if (pIndex->pNextElement==NULL)
				return -1;
			pIndex = pIndex->pNextElement;
		}
	}

	return -1;*/
}


//-------------------------------------------------------------------------------------------------
int ElementStack::ReadElement(int iNode, int SWert, int /*iEleNr*/ )
{
	std::map<Core::i32, Element>::iterator it = m_ElementMap.find( iNode );
	if ( m_ElementMap.end() != it )
	{
		Element element = (*it).second;
		Core::i32 i =  0;
		switch (SWert) 
		{
		case 1:				// Knotennummer Elementanfang
			i = element.KnNr1;
			return i;
			
		case 2:				// Knotennummer Elementende
			i = element.KnNr2;
			return i;

		case 3:				// Materialmatrix-Nummer
			i = element.MatNr;
			return i;
			
		case 4:				// Art des Elements (1: Fachwerkstab; 2: Balken, 3&4 Balken mit Gelenk)
			i = element.Balkenart;
			return i;

		case 0:				// gar nichts zurückgeben	
			return 0;

		default:
			return ErrorHandler::WT_FATAL_ERR;
		}		
	}
	
	return ErrorHandler::WT_ERR;
}

//-------------------------------------------------------------------------------------------------
//	Clears all stored elements.
void ElementStack::DelList()
{
	m_ElementMap.clear();
}

//-------------------------------------------------------------------------------------------------
//	Returns the number of elements.
Core::ui32 ElementStack::numberOfElements() const
{
	return m_ElementMap.size();
}

//-------------------------------------------------------------------------------------------------
