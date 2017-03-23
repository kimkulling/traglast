//-------------------------------------------------------------------------------------------------
///	\file		TScale.h
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Templates for scaling.
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
#ifndef TL_GUI_TSCALE_H_INC
#define TL_GUI_TSCALE_H_INC

namespace GUI
{

//-------------------------------------------------------------------------------------------------
///	\class		Scale2D
///	\ingroup	GUI
///
///	\brief	Prforms a rescale operation in a given limitation. 
///	\param	x		Maximal x distance.
///	\param	y		Maximal y distance.
///	\param	scaleX	Computes scaling factor for x.
///	\param	scaleY	Computes scaling factor for Y.
//-------------------------------------------------------------------------------------------------
template<class type>
void Scale2D( type x, type y, type &scaleX, type &scaleY )
{
	if ( x != 0 )	
		scaleX = 100 / x;
	else
		x = 0;
	if ( y != 0 )
		scaleY = 100 / y;
	else
		y = 0;
}

} // Namespace GUI

#endif // TL_GUI_TSCALE_H_INC
