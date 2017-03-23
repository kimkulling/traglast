//----------------------------------------------------------------------------------------------------------------------
///	\file		EnviromentServer.h
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class declaration of EnviromentServer.
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
#ifndef TL_CORE_ENVSERVER_H_INC
#define TL_CORE_ENVSERVER_H_INC

#include <string>
#include <map>

namespace Core
{

//----------------------------------------------------------------------------------------------------------------------
///	\class		EnviromentServer
///	\ingroup	Core
///
///	\brief	Provides an application-specific enviroment. You can use it like the enviroment 
///	variables in a console. Each enviroment variable must be unique. Assigned values can be any kind 
///	of strings.
//----------------------------------------------------------------------------------------------------------------------
class EnviromentServer
{
public:
	///	Creates a new enviromentserver instance.
	static EnviromentServer *create();
	///	Returns the only instance.
	static EnviromentServer *get();
	///	Destroys the only instance.
	static void kill();
	///	Sets a variable with a value. If the variable was not set before
	void setVariable( const std::string &rVariable, const std::string &rValue );
	bool hasValue( const std::string &rVariable ) const;
	const std::string &getValue( const std::string &rVariable ) const;

private:
	EnviromentServer();
	~EnviromentServer();

private:
	static EnviromentServer *m_sEnvServerInst;
	std::map<std::string, std::string> m_EnviromentMap;
};

//----------------------------------------------------------------------------------------------------------------------

} // Namespace Core

#endif // TL_CORE_ENVSERVER_H_INC
