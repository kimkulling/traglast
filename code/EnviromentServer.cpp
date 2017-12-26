//----------------------------------------------------------------------------------------------------------------------
///	\file		EnviromentServer.cpp
///	\ingroup	Core
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class definition of EnviromentServer.
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
#include "EnviromentServer.h"
#include <cassert>

namespace Core {

EnviromentServer *EnviromentServer::m_sEnvServerInst = nullptr;

EnviromentServer *EnviromentServer::create() {
	assert( NULL == m_sEnvServerInst );
    if ( nullptr == m_sEnvServerInst ) {
        m_sEnvServerInst = new EnviromentServer;
    }
	return m_sEnvServerInst;
}

EnviromentServer *EnviromentServer::get() {
	return m_sEnvServerInst;
}

void EnviromentServer::kill() {
    if ( nullptr != m_sEnvServerInst ) {
        delete m_sEnvServerInst;
        m_sEnvServerInst = nullptr;
    }
}

void EnviromentServer::setVariable( const std::string &variable, const std::string &value ) {
    if ( variable.empty() || value.empty() ) {
        return;
    }
	m_EnviromentMap[ variable ] = value;
}

bool EnviromentServer::hasValue( const std::string &rVariable ) const {
	std::map<std::string, std::string>::const_iterator it = m_EnviromentMap.find( rVariable );
    if ( m_EnviromentMap.end() == it ) {
        return false;
    }
	return true;
}

const std::string &EnviromentServer::getValue( const std::string &rVariable ) const {
	const static std::string empty( "" );
	std::map<std::string, std::string>::const_iterator it = m_EnviromentMap.find( rVariable );
    if ( m_EnviromentMap.end() == it ) {
        return empty;
    }
	return it->second;
}

EnviromentServer::EnviromentServer() 
: m_EnviromentMap() {
	// empty
}

EnviromentServer::~EnviromentServer() {
	m_EnviromentMap.clear();
}

} // Namespace Core
