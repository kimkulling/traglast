//----------------------------------------------------------------------------------------------------------------------
///	\file		Logger.cpp
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class definition of Logger.
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
#include "StdAfx.h"
#include "Logger.h"
#include "DebugLogStream.h"
#include <cassert>
#include <string>

namespace Core
{

Logger *Logger::m_sLogger = NULL;

//----------------------------------------------------------------------------------------------------------------------
//	Returns the only instance.
Logger *Logger::get()
{
	if ( NULL == m_sLogger )
		m_sLogger = new Logger;
	return m_sLogger;
}

//----------------------------------------------------------------------------------------------------------------------
//	Kills the only instance.
void Logger::kill()
{
	if ( NULL != m_sLogger )
	{
		m_sLogger = NULL;
		delete m_sLogger;
	}
}

//----------------------------------------------------------------------------------------------------------------------
//	Logs a debug message.
void Logger::debug( const std::string &rMessage )
{
	std::string msg = std::string("Debug : ") + rMessage;
	write( msg );
}

//----------------------------------------------------------------------------------------------------------------------
//	Logs a debug message.
void Logger::info( const std::string &rMessage )
{
	std::string msg = "Info  : " + rMessage;
	write( msg );
}

//----------------------------------------------------------------------------------------------------------------------
//	Logs a warn message.
void Logger::warn( const std::string &rMessage )
{
	std::string msg = "Warn  : " + rMessage;
	write( msg );
}

//----------------------------------------------------------------------------------------------------------------------
//	Logs an error message.
void Logger::error( const std::string &rMessage )
{
	std::string msg = "Error : " + rMessage;
	write( msg );
}

//----------------------------------------------------------------------------------------------------------------------
//	Logs a fatal error message.
void Logger::fatal( const std::string &rMessage )
{
	std::string msg = "Fatal : " + rMessage;
	write( msg );
}

//----------------------------------------------------------------------------------------------------------------------
//	Logs a debug message.
void Logger::attachStream( ILogStream *pStream )
{
	assert( NULL != pStream );

	for ( std::vector<ILogStream*>::iterator it = m_LogStreams.begin();
		it != m_LogStreams.end();
		++it )
	{
		if ( *it == pStream )
			return;
	}
	m_LogStreams.push_back( pStream );
}

//----------------------------------------------------------------------------------------------------------------------
//	Logs a debug message.
void Logger::detatchStream( ILogStream *pStream )
{
	for ( std::vector<ILogStream*>::iterator it = m_LogStreams.begin();
		it != m_LogStreams.end();
		++it )
	{
		if ( *it == pStream )
		{
			it = m_LogStreams.erase( it );
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
//	Write method.
void Logger::write( const std::string &rMessage )
{
	for ( std::vector<ILogStream*>::iterator it = m_LogStreams.begin();
		it != m_LogStreams.end();
		++it )
	{
		if ( (*it)->isActive() )
		{
			std::string tmp = rMessage + ("\n");
			(*it)->write( tmp );
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
//	Constructor.
Logger::Logger() :
	m_LogStreams()
{
	m_LogStreams.push_back( new DebugLogStream );
}

//----------------------------------------------------------------------------------------------------------------------
//	Destructor.
Logger::~Logger()
{
	for ( std::vector<ILogStream*>::iterator it = m_LogStreams.begin();
		it != m_LogStreams.end();
		++it )
	{
		delete *it;
	}
}

//----------------------------------------------------------------------------------------------------------------------

} // Namespace Core
