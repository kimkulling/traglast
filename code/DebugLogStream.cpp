//-------------------------------------------------------------------------------------------------
///	\file		DebugLogStream.cpp
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class definition of DebugLogStream.
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
#include "StdAfx.h"
#include "DebugLogStream.h"
#include <windows.h>

namespace Core
{

//-------------------------------------------------------------------------------------------------
//	Constructor.
DebugLogStream::DebugLogStream() :
	m_bIsActive( true )
{
	// empty
}

//-------------------------------------------------------------------------------------------------
//	Destructor.
DebugLogStream::~DebugLogStream()
{
	// empty
}

//-------------------------------------------------------------------------------------------------
//	Writes strings into output device.
void DebugLogStream::write( const std::string &rMessage )
{
	OutputDebugString( rMessage.c_str() );
}

//-------------------------------------------------------------------------------------------------
//	Activates the stream.
void DebugLogStream::activate()
{
	m_bIsActive = true;
}

//-------------------------------------------------------------------------------------------------
//	Desactivates the stream.
void DebugLogStream::desactivate()
{
	m_bIsActive = false;
}

//-------------------------------------------------------------------------------------------------
//	Returns true, if stream is active.
bool DebugLogStream::isActive() const
{
	return m_bIsActive;
}

//-------------------------------------------------------------------------------------------------

} // Namespace Core
