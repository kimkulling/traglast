//-------------------------------------------------------------------------------------------------
///	\file		DebugLogStream.h
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class declaration of DebugLogStream.
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
#ifndef TL_CORE_DEBUGLOGSTREAM_H_INC
#define TL_CORE_DEBUGLOGSTREAM_H_INC

#include "ILogStream.h"

namespace Core
{

//-------------------------------------------------------------------------------------------------
///	\class		DebugLogStream
///	\ingroup	Core
///
///	\brief	Provides a stream into the debug info message queue of windows.
//-------------------------------------------------------------------------------------------------
class DebugLogStream : public ILogStream
{
public:
	///	Constructor.
	DebugLogStream();
	///	Destructor.
	~DebugLogStream();
	///	Logs a message into the debug logging queue from windows.
	void write( const std::string &rMessage );
	///	Activates the stream.
	void activate();
	///	Desactivates the stream.
	void desactivate();
	///	Returns true, if stream is active.
	bool isActive() const;

private:
	bool m_bIsActive;
};

//-------------------------------------------------------------------------------------------------

} // Namespace Core

#endif // TL_CORE_DEBUGLOGSTREAM_H_INC
