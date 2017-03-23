//----------------------------------------------------------------------------------------------------------------------
///	\file		Observer.h
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009
///	\brief		Class declaration of Observers. Build derivated from this interface to provide your 
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
#ifndef TL_CORE_OBSERVER_H_INC
#define TL_CORE_OBSERVER_H_INC

namespace Core
{

//----------------------------------------------------------------------------------------------------------------------
///	\class		Observer
///	\ingroup	Core
///
///	\brief	Base class for observer implementations.
//----------------------------------------------------------------------------------------------------------------------
class Observer
{
public:
	///	Destructor, virtual.
	virtual ~Observer();
	///	Will be called on state changed.
	virtual void notifyStateChange();

protected:
	///	Default constructor.
	Observer();
};

//----------------------------------------------------------------------------------------------------------------------

} // Namespace Core

#endif // TL_CORE_OBSERVER_H_INC
