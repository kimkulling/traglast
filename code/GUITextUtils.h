//----------------------------------------------------------------------------------------------------------------------
///	\file		GUITextUtils.h
///	\ingroup	GUI
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2001
///	\brief		Class declaration of GUI specific text utilities.
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
#ifndef TL_GUI_TEXTUTILS_H_INC
#define TL_GUI_TEXTUTILS_H_INC

#include "types.h"
#include <string>

// Class forward declarations
class CWnd;

namespace GUI
{

//----------------------------------------------------------------------------------------------------------------------
///	\class		GUITextUtils
///	\ingroup	GUI
///
///	\brief	Provides basic text utilities to make GUI handling with localized texts much easier.
//----------------------------------------------------------------------------------------------------------------------
class GUITextUtils
{
public:
	///	Sets a window text descriped by a localized text id.
	static bool setWindowTextPerId( CWnd *pWindow, std::string &rTextId );
	///	Sets a dialog text descriped by a localized text id.
	static bool setLocalizedText( CWnd *pDialog, Core::i32 controlId, const std::string &rTextId );
};

//----------------------------------------------------------------------------------------------------------------------

} // Namespace GUI

#endif
