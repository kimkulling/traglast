//-------------------------------------------------------------------------------------------------
///	\file		ElementStack.h
///	\ingroup	FEStructure
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class declaration of ElementStack.
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
#ifndef TL_FESTRUCTURE_ELEMENTSTACK_H_INC
#define TL_FESTRUCTURE_ELEMENTSTACK_H_INC

#include <map>

namespace FEStructure
{


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class ElementStack
{
public:
	class Element
	{
	public:
		int ElementNr;			// Nummer des Element
		int KnNr1;				// Knotennummer Elementanfang
		int KnNr2;				// Knotennummer Elementende
		int MatNr;				// Materialnummer
		int Balkenart;			// Art des Elementes (1, 2, 3 oder 4)

		///	Constructor.
		Element() : ElementNr( 0 ),	KnNr1( 0 ),	KnNr2( 0 ),	MatNr( 0 ),	Balkenart( 0 ) {}
		///	Destructor.
		~Element() {}	
	};

public:
	///	Constructor
	ElementStack();
	///	Destruktor
	~ElementStack();
	///	Method to add a new element entry.
	void addElement(int EleNr, int n1, int n2, int mat, int art);
	///	Deletes an element.
	bool delElement(int iEleNr);
	///	Modifies an already existing element.
	bool setElement(int iEleNr, int iKn1, int iKn2, int iMat, int iArt);
	///	Chekc for existance of an element definition.
	int CheckNode(int iNode, int iArt);
	///	Return element data.
	int ReadElement(int Nr, int SWert, int EleNr);
	///	Removes all elements.
	void DelList();
	///	Returns the number of elements.
	Core::ui32 numberOfElements() const;

private:
	std::map<Core::i32, Element> m_ElementMap;
};

//-------------------------------------------------------------------------------------------------

} // Namespace FEStructure

#endif // TL_FESTRUCTURE_ELEMENTSTACK_H_INC
