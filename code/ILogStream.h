//-------------------------------------------------------------------------------------------------
///	\file		ILogStream.h
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class declaration of ILogStream.
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
#ifndef TL_CORE_ILOGSTREAM_H_INC
#define TL_CORE_ILOGSTREAM_H_INC

namespace Core
{

//-------------------------------------------------------------------------------------------------
///	\class		ILogStream
///	\ingroup	Core
///
///	\brief	Interface for logstreams. A logstream provides a write mechanism 
///	into its supported output device like a file or a special window. You can 
///	activate / desactivate each logstream to control it.
//-------------------------------------------------------------------------------------------------
class ILogStream
{
public:
	///	\brief	Destructor, virtual.
	virtual ~ILogStream();

	///	\brief	Writes a message into the output device.
	///	\param	rMessage	Message to write.
	virtual void write( const std::string &rMessage ) = 0;
	
	///	\brief	Activates the stream.
	virtual void activate() = 0;
	
	///	\brief	Desactivates the stream.
	virtual void desactivate() = 0;

	///	\brief	Returns true, if this stream is avtive.
	///	\return	True, if stream is active.
	virtual bool isActive() const = 0;

protected:
	///	\brief	Default constructor.
	ILogStream();
};

//-------------------------------------------------------------------------------------------------
//	Default constructor.
inline ILogStream::ILogStream()
{
	// empty
}

//-------------------------------------------------------------------------------------------------
//	Destructor.
inline ILogStream::~ILogStream()
{
	// empty
}

//-------------------------------------------------------------------------------------------------

} // Namespace Core

#endif // TL_CORE_ILOGSTREAM_H_INC
