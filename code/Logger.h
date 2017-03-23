//-------------------------------------------------------------------------------------------------
///	\file		Logger.h
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class declaration of Logger.
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
#ifndef TL_CORE_LOGGER_H_INC
#define TL_CORE_LOGGER_H_INC

#include <vector>

namespace Core
{

class ILogStream;

//-------------------------------------------------------------------------------------------------
///	\class		Logger
///	\ingroup	Core
///
///	\brief	Provides logging for debug, info and errors. You can attach your 
///	own logstreams.
//-------------------------------------------------------------------------------------------------
class Logger
{
public:
	///	Returns only instance of logger.
	static Logger *get();
	///	Kills the only instance.
	static void kill();
	///	Logs a debug message.
	void debug( const std::string &rMessage );
	///	Logs an info message.
	void info( const std::string &rMessage );
	///	Logs a warn message.
	void warn( const std::string &rMessage );
	///	Logs an error message.
	void error( const std::string &rMessage );
	///	Logs a fatal message.
	void fatal( const std::string &rMessage );
	///	Attachs a new stream.
	void attachStream( ILogStream *pStream );
	///	Detatch a stream for the stream list.
	void detatchStream( ILogStream *pStream );

private:
	void write( const std::string &rMessage );
	Logger();
	~Logger();

private:
	static Logger *m_sLogger;
	std::vector<ILogStream*> m_LogStreams;
};

//-------------------------------------------------------------------------------------------------

} // Namespace Core

#endif	// TL_CORE_LOGGER_H_INC
