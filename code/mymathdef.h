//----------------------------------------------------------------------------------------------------------------------
///	\file		mymathdef.h
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2001
///	\brief		Math declarations.
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
//----------------------------------------------------------------------------------------------------------------------
#ifndef TL_CORE_MYMATHDEF_H_INC
#define TL_CORE_MYMATHDEF_H_INC

namespace Math
{

#define VERSION		"V 0.01"
#define DIFFERENZ	0.1
#define POSITIV		1E-6
#define DEFNULL		1E-20
#define FEDER		1E20
#define FACHWERK	1
#define NOGEL		2	
#define GELLEFT		3
#define GELRIGHT	4
#define KNOTENLAST	1
#define LINIENLAST	2
#define TRANS		1
#define RETRANS		2
#define NEGATIV		-1

#define SINGULAR	1
#define dL2D(dx, dy)		sqrt((dx * dx) + (dy * dy)) // Länge eines Elementes


//----------------------------------------------------------------------------------------------------------------------
///	\class		MathUtils
///	\ingroup	Math
///
///	\brief	Utilitiy class to provide basic math operations.
//----------------------------------------------------------------------------------------------------------------------
template<class type>
class MathUtils
{
public:
	///	Scales a X-coordinade in 2D.
	static type viewX( type x, type scale, type xorg )
	{
		return ( x * scale + xorg );
	}
	///	Scales a Y-coordinade in 2D.
	static type viewY( type y, type scale, type xorg )
	{
		return (y * scale + xorg);
	}
	///	Transforms a X-coordinate back to a world coordinate.
	static type realX( int x, type scale, int x0 )
	{
		return ( ( x - x0 ) / scale);
	}
	///	Transforms a Y-coordinate back to a world coordinate.
	static type realY( int y, type scale, int x0 )
	{
		return ( ( y - x0 ) / scale);
	}
	///	Computes the length of a vector in 2D.
	static type getLength( type x, type y )
	{
		return ( sqrt( ( x * x ) + ( y * y ) ) );
	}
	///	Computes the cubic suare of a value.
	static type sqr3( type x )
	{
		return ( ( x ) * ( x)  * ( x ) );
	}
};

//----------------------------------------------------------------------------------------------------------------------

#ifndef __2D_CALC__
#  define __2D_CALC__
#endif

#define Linie "-------------------------------------------------------------------"

///	Performs a round operation.
int round( double x );
BOOL GetDate();

} // Namespace Math

#endif // TL_CORE_MYMATHDEF_H_INC
