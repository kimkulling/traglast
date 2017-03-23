//----------------------------------------------------------------------------------------------------------------------
///	\file		ObserverSubject.h
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009
///	\brief		Class declaration of ObserverSubject, provides an interface to oberser subjects.
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
#ifndef TL_CORE_OBSERVEROBJECT_H_INC
#define TL_CORE_OBSERVEROBJECT_H_INC

#include <vector>

namespace Core
{

//	Class forward declarations.
class Observer;

//----------------------------------------------------------------------------------------------------------------------
///	\class		ObserverSubject
///	\ingroup	Core
///
///	\brief	Interface class to provide observer subjects. Build derived classes from this interface 
///	to provide observer methods.
//----------------------------------------------------------------------------------------------------------------------
class ObserverSubject
{
public:
	///	Destructor, virtual.
	virtual ~ObserverSubject();
	///	Adds a new observer object to the subject.
	virtual void addObserver( Observer *pObserver );
	///	Removes an already attached bserver object from the subject.
	virtual void removeObserver( Observer *pObserver );
	///	All observers will be nodified.
	virtual void onStateChanged();

protected:
	///	Constructor.
	ObserverSubject();

private:
	std::vector<Observer*> m_RegisteredObservers;
};

//----------------------------------------------------------------------------------------------------------------------

} // Namespace Core

#endif // TL_CORE_OBSERVEROBJECT_H_INC
