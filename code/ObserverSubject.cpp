//----------------------------------------------------------------------------------------------------------------------
///	\file		ObserverSubject.cpp
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009
///	\brief		Class definition of ObserverSubject, provides an interface to oberser subjects.
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
#include "ObserverSubject.h"
#include "Observer.h"
#include <cassert>
#include <algorithm>

namespace Core
{

//----------------------------------------------------------------------------------------------------------------------
ObserverSubject::ObserverSubject() :
	m_RegisteredObservers()
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
ObserverSubject::~ObserverSubject()
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
void ObserverSubject::addObserver( Observer *pObserver )
{
	assert( NULL != pObserver );
	if ( NULL == pObserver )
		return;
	m_RegisteredObservers.push_back( pObserver );
}

//----------------------------------------------------------------------------------------------------------------------
void ObserverSubject::removeObserver( Observer *pObserver )
{
	assert( NULL != pObserver );
	if ( NULL != pObserver )
		return;
	std::vector<Observer*>::iterator it = std::find( m_RegisteredObservers.begin(), m_RegisteredObservers.end(), pObserver );
	if ( m_RegisteredObservers.end() == it )
		return;
	it = m_RegisteredObservers.erase( it );
}

//----------------------------------------------------------------------------------------------------------------------
void ObserverSubject::onStateChanged()
{
	for ( std::vector<Observer*>::iterator it = m_RegisteredObservers.begin();
		it != m_RegisteredObservers.end();
		++it )
	{
		(*it)->notifyStateChange();
	}
}

//----------------------------------------------------------------------------------------------------------------------

} // Namespace Core
