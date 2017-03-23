//----------------------------------------------------------------------------------------------------------------------
///	\file		OSUtils.cpp
///	\ingroup	OS
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class definition of OSUtils.
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
#include "OSUtils.h"
#ifdef _WIN32
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#endif

namespace OS
{

//----------------------------------------------------------------------------------------------------------------------
#ifdef _WIN32
Core::ui32 OSUtils::getFilelist( const std::string &rPath, std::vector<std::string> &rFilelist )
{
	TCHAR szDir[ MAX_PATH ] = {0};
	StringCchCopy( szDir, MAX_PATH, rPath.c_str() );
	StringCchCat( szDir, MAX_PATH, TEXT("\\*") );
	
	// Find the first file in the directory.
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile( szDir, &ffd );
	if ( INVALID_HANDLE_VALUE == hFind ) 
	{
		DWORD err = ::GetLastError();
		return 0;
	}
   
	// List all the files in the directory with some info about them.
	do
	{
		if ( ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			// empty, should it contain something?
		}
		else
		{
			std::string tmp = rPath;
			tmp += '\\';
			tmp += ffd.cFileName;
			rFilelist.push_back( tmp );
		}
   }
   while ( FindNextFile(hFind, &ffd ) != 0 );
   FindClose(hFind);
   return ( Core::ui32 ) rFilelist.size();
}
#else
#error "Not supported!"
#endif

//----------------------------------------------------------------------------------------------------------------------
void OSUtils::attachFileSeparator( std::string &rAbsFile )
{
#ifdef _WIN32
	static const std::string sep = "\\";
#else
#error "OSUtils::attachFileSeparator not supported!"
#endif
	if ( rAbsFile[ rAbsFile.size() - 1 ] != sep[0] )
	{
		rAbsFile += sep;
	}
}

//----------------------------------------------------------------------------------------------------------------------
void OSUtils::separatePath( const std::string &rAbsFile, std::string &rAbsPath )
{
	rAbsPath = "";
	if ( rAbsFile.empty() )
		return;
	std::string::size_type pos = rAbsFile.find_last_of( "\\" );
	if ( std::string::npos == pos )
		return;

	rAbsPath = rAbsFile.substr( 0, pos );
}

//----------------------------------------------------------------------------------------------------------------------

} // Namespace OS

