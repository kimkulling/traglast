//----------------------------------------------------------------------------------------------------------------------
///	\file		OSUtils.h
///	\ingroup	OS
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class declaration of OSUtils.
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
#ifndef OS_OSUTILS_H_INC
#define OS_OSUTILS_H_INC

#include "types.h"
#include <string>
#include <vector>

namespace OS
{

//----------------------------------------------------------------------------------------------------------------------
///	\class		OSUtils
///	\ingroup	OS
///
///	\brief	A utility class which provides os specific operations.
//----------------------------------------------------------------------------------------------------------------------
class OSUtils
{
public:
	///	Search in a given path for files and returns the number of it. All detected files will be
	///	added to the string vector instance.
	static Core::ui32 getFilelist( const std::string &rPath, std::vector<std::string> &rFilelist );

	///	Atachs a os-spezific file separator at the end of the file. For instance a file like 
	///	c:\temp will be c:\temp\ after calling this method function. If a separator was detected no 
	///	change will performed.
	static void attachFileSeparator( std::string &rAbsFile );

	static void separatePath( const std::string &rAbsFile, std::string &rAbsPath );
};

//----------------------------------------------------------------------------------------------------------------------

}// Namespace OS

#endif // OS_OSUTILS_H_INC
