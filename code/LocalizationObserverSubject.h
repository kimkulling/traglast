//----------------------------------------------------------------------------------------------------------------------
///	\file		LocalizationObserverSubject.h
///	\ingroup	Localization
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class declaration of abstract interface LocalizationObserverSubject.
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
#ifndef LOCAL_LOCALIZATIONOBSERVERSUBJECT_H_INC
#define LOCAL_LOCALIZATIONOBSERVERSUBJECT_H_INC

#include "ObserverSubject.h"

namespace Localization
{

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class LocalizationObserverSubject : Core::ObserverSubject
{
public:
	virtual ~LocalizationObserverSubject();
	virtual bool onLanguageChange() = 0;

protected:
	LocalizationObserverSubject();
};

//----------------------------------------------------------------------------------------------------------------------
inline LocalizationObserverSubject::LocalizationObserverSubject()
{
}

//----------------------------------------------------------------------------------------------------------------------
inline LocalizationObserverSubject::~LocalizationObserverSubject()
{
}

//----------------------------------------------------------------------------------------------------------------------

} // Namespace Localization

#endif // LOCAL_LOCALIZATIONOBSERVERSUBJECT_H_INC
