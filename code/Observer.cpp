//----------------------------------------------------------------------------------------------------------------------
///	\file		Observer.cpp
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009
///	\brief		Class definition of Observers. Build derivated from this interface to provide your 
///				own observer classes.
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
#include "stdafx.h"
#include "Observer.h"

namespace Core
{

//----------------------------------------------------------------------------------------------------------------------
Observer::Observer()
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
Observer::~Observer()
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
void Observer::notifyStateChange()
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------

} // Namespace Core
