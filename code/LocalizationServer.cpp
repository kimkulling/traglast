//----------------------------------------------------------------------------------------------------------------------
///	\file		LocalizationServer.cpp
///	\ingroup	Localization
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class definition of LocalizationServer.
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
#include "LocalizationServer.h"
#include "OSUtils.h"
#include <cassert>
#include "Logger.h"
#include "tinyxml.h"


namespace Localization
{

using namespace Core;

static const std::string NoLanguage = "none";
static const std::string XmlRootNode = "localization";
static const std::string XmlRootNodeLang = "lang";
static const std::string XmlChildTextNode = "textNode";
static const std::string XmlTextNodeAttrib_StringId = "stringId";
static const std::string XmlTextNodeAttrib_Text = "text";

LocalizationServer *LocalizationServer::m_sLocalizationServer = NULL;

//----------------------------------------------------------------------------------------------------------------------
LocalizationServer *LocalizationServer::create( const std::string &rLangPath )
{
	assert( NULL == m_sLocalizationServer );
	m_sLocalizationServer = new LocalizationServer( rLangPath );
	return m_sLocalizationServer;
}

//----------------------------------------------------------------------------------------------------------------------
LocalizationServer *LocalizationServer::get()
{
	assert( NULL != m_sLocalizationServer );
	return m_sLocalizationServer;
}

//----------------------------------------------------------------------------------------------------------------------
void LocalizationServer::kill()
{
	assert( NULL != m_sLocalizationServer );
	delete m_sLocalizationServer;
	m_sLocalizationServer = NULL;
}

//----------------------------------------------------------------------------------------------------------------------
void LocalizationServer::addText( const std::string &rStringId, const std::string &rText )
{
	assert( !rStringId.empty() );
	m_StringIdMap[ rStringId ] = rText;
}

//----------------------------------------------------------------------------------------------------------------------
std::string LocalizationServer::getText( const std::string &rStringId ) const
{
	assert( !rStringId.empty() );
	std::map<std::string, std::string>::const_iterator it = m_StringIdMap.find( rStringId );
	if ( m_StringIdMap.end() == it )
		return "";
	return (*it).second;
}

//----------------------------------------------------------------------------------------------------------------------
bool LocalizationServer::load( const std::string &rFilename )
{
	assert( !rFilename.empty() );

	TiXmlDocument document;
	if ( !document.LoadFile( rFilename.c_str() ) ) 
	{
		Logger::get()->error( "Cannot load file " + rFilename );
		return false;
	}
	
	bool result = false;
	TiXmlElement *pRoot = document.FirstChildElement( XmlRootNode.c_str() );
	if ( NULL != pRoot )
	{
		const Core::c8 *pLang = pRoot->Attribute( XmlRootNodeLang.c_str() );
		if ( NULL == pLang )
		{
			return false;
		}
		else
		{
			const std::string newLang = pLang;
			if ( m_CurrentLanguage == newLang )
				return true;
			else
			{
				if ( parseXmlToken( pRoot ) )
				{
					m_CurrentLanguage = newLang;
					this->onStateChanged();
					result = true;
				}
			}
		}
	}

	return result;
}

//----------------------------------------------------------------------------------------------------------------------
bool LocalizationServer::setLanguage( const std::string &rLanguage )
{
	for ( std::vector<language>::iterator it = m_SupportedLanguages.begin();
		it != m_SupportedLanguages.end();
		++it )
	{
		const std::string language = (*it).m_Info;
		if ( language == rLanguage )
		{
			return load( (*it).m_File );
		}
	}
	return false;
}

//----------------------------------------------------------------------------------------------------------------------
const std::string &LocalizationServer::getCurrentLanguage() const
{
	return m_CurrentLanguage;
}

//----------------------------------------------------------------------------------------------------------------------
Core::ui32 LocalizationServer::getSupportedLanguages( std::vector<std::string> &rLanguages )
{
	for ( Core::ui32 i=0; i<m_SupportedLanguages.size(); i++ )
	{
		rLanguages.push_back( m_SupportedLanguages[ i ].m_Info );
	}
	return (Core::ui32) rLanguages.size();
}

//----------------------------------------------------------------------------------------------------------------------
LocalizationServer::LocalizationServer( const std::string &rLangPath ) :
	m_LangPath( rLangPath ),
	m_StringIdMap(),
	m_SupportedLanguages(),
	m_CurrentLanguage( "none" )
{
	collectLanguages();
}

//----------------------------------------------------------------------------------------------------------------------
LocalizationServer::~LocalizationServer()
{
	// empty
}

//----------------------------------------------------------------------------------------------------------------------
bool LocalizationServer::collectLanguages()
{
	if ( m_LangPath.empty() )
		return false;
	
	std::vector<std::string> filelist;
	const Core::ui32 numberOfFiles = OS::OSUtils::getFilelist( m_LangPath, filelist );
	if ( 0 == numberOfFiles )
		return true;
	for ( std::vector<std::string>::iterator it = filelist.begin();
		it != filelist.end();
		++it )
	{
		std::string::size_type pos = (*it).find( ".xml" );
		if ( std::string::npos != pos )
		{
			const std::string lang = getLangFromXmlDocument( *it );
			if ( NoLanguage != lang )
			{
				language language;
				language.m_Info = lang;
				language.m_File = (*it);
				m_SupportedLanguages.push_back( language );
			}
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
std::string LocalizationServer::getLangFromXmlDocument( const std::string &rFilename )
{
	assert( !rFilename.empty() );

	TiXmlDocument document;
	if ( !document.LoadFile( rFilename.c_str() ) ) 
		return NoLanguage;
	
	TiXmlElement *pRoot = document.FirstChildElement( XmlRootNode.c_str() );
	if ( NULL == pRoot )
		return NoLanguage;

	std::string lang = NoLanguage;
	const Core::c8 *pLang = pRoot->Attribute( XmlRootNodeLang.c_str() );
	if ( NULL != pLang )
		lang = pLang;
	return lang;
}

//----------------------------------------------------------------------------------------------------------------------
bool LocalizationServer::parseXmlToken( TiXmlElement *pNode )
{
	assert( NULL != pNode );
	TiXmlElement *pTextNode = pNode->FirstChildElement( XmlChildTextNode.c_str() );
	if ( NULL != pTextNode )
	{
		for ( pTextNode; pTextNode; pTextNode=pTextNode->NextSiblingElement() )
		{
			const Core::c8 *pStringId = pTextNode->Attribute( XmlTextNodeAttrib_StringId.c_str() );
			const Core::c8 *pText = pTextNode->Attribute( XmlTextNodeAttrib_Text.c_str() );
			if ( NULL != pStringId && NULL != pText )
			{
				std::string id( pStringId );
				std::string text( pText );
				m_StringIdMap[ id ] = text;
			}
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------

} // Namespace Localization
