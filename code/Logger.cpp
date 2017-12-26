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

namespace Core {

Logger *Logger::m_sLogger = nullptr;

Logger *Logger::get() {
    if ( nullptr == m_sLogger ) {
        m_sLogger = new Logger;
    }
	return m_sLogger;
}

void Logger::kill() {
	if ( nullptr != m_sLogger ) {
        delete m_sLogger;
        m_sLogger = nullptr;
	}
}

void Logger::debug( const std::string &rMessage ) {
	const std::string msg = std::string("Debug : ") + rMessage;
	write( msg );
}

void Logger::info( const std::string &rMessage ) {
	const std::string msg = "Info  : " + rMessage;
	write( msg );
}

void Logger::warn( const std::string &rMessage ) {
	const std::string msg = "Warn  : " + rMessage;
	write( msg );
}

void Logger::error( const std::string &rMessage ) {
	const std::string msg = "Error : " + rMessage;
	write( msg );
}

void Logger::fatal( const std::string &rMessage ) {
	const std::string msg = "Fatal : " + rMessage;
	write( msg );
}

void Logger::attachStream( ILogStream *pStream ) {
    if ( nullptr == pStream ) {
        return;
    }

	for ( std::vector<ILogStream*>::iterator it = m_LogStreams.begin(); it != m_LogStreams.end(); ++it ) {
		if ( *it == pStream )
			return;
	}
	m_LogStreams.push_back( pStream );
}
void Logger::detatchStream( ILogStream *pStream ) {
    if ( nullptr == pStream ) {
        return;
    }
    
    for ( std::vector<ILogStream*>::iterator it = m_LogStreams.begin(); it != m_LogStreams.end(); ++it ) {
		if ( *it == pStream ) {
			it = m_LogStreams.erase( it );
		}
	}
}

void Logger::write( const std::string &rMessage ) {
	for ( std::vector<ILogStream*>::iterator it = m_LogStreams.begin(); it != m_LogStreams.end(); ++it ) {
		if ( (*it)->isActive() ) {
			std::string tmp = rMessage + ("\n");
			(*it)->write( tmp );
		}
	}
}

Logger::Logger() 
: m_LogStreams() {
	m_LogStreams.push_back( new DebugLogStream );
}

Logger::~Logger() {
	for ( std::vector<ILogStream*>::iterator it = m_LogStreams.begin(); it != m_LogStreams.end(); ++it ) {
		delete *it;
	}
}

} // Namespace Core
