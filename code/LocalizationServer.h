//----------------------------------------------------------------------------------------------------------------------
///	\file		LocalizationServer.h
///	\ingroup	Localization
///	\author		Kimmi aka Kim Kulling
///				Copyright (C) 2009  
///	\brief		Class declaration of LocalizationServer.
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
#ifndef LOCAL_LOCALIZATIONSERVER_H_INC
#define LOCAL_LOCALIZATIONSERVER_H_INC

#include <string>
#include "types.h"
#include "ObserverSubject.h"

class TiXmlElement;

namespace Localization
{

//----------------------------------------------------------------------------------------------------------------------
///	\class		LocalizationServer
///	\ingroup	Localization
///
///	\brief	The localization server provides access to a set of localized texts. You can access each 
///	text by its unique id. The mapping of the id to the text is configured by a localize-xml file.
///	Here the localization mapping is configured by a node called <b>textNode</b> . You can access the 
///	LocalizationServer instance by a singleton get method call like:
///
///		LocalizationServer::get()->getText( idString );
///
///	So you can easily descripe several languages.
///
///	\example A simple example:
///
///	<?xml version="1.0" ?>
///	<localization lang="ger">
///		<textNode stringId="foo1" text="bar1"/>
///	</localization>
///	
//----------------------------------------------------------------------------------------------------------------------
class LocalizationServer : public Core::ObserverSubject
{
public:
	///	Creation method. Before calling this no get call is possible.
	static LocalizationServer *create( const std::string &rLangPath );
	///	Get method, creation must be performed before.
	static LocalizationServer *get(); 
	///	Kills the singleton instance, create call must be performed before.
	static void kill();
	///	Adds a new text id to text mapping.
	void addText( const std::string &rStringId, const std::string &rText );
	///	Returns the mapped text to a given text id. If this key isn't assigned to a text an empty string 
	///	will be returned.
	std::string getText( const std::string &rStringId ) const;
	///	Loads a new localization file. Will return false, if load was failed.
	bool load( const std::string &rFilename );
	///	Sets a new language, will return false, if requested language is not supported.
	bool setLanguage( const std::string &rLanguage );
	///	Returns the current loaded language.
	const std::string &getCurrentLanguage() const;
	///	Returns all supported languages.
	Core::ui32 getSupportedLanguages( std::vector<std::string> &rLanguages );
	///

private:
	LocalizationServer( const std::string &rLangPath );
	~LocalizationServer();
	bool collectLanguages();
	std::string getLangFromXmlDocument( const std::string &rFilename );
	bool parseXmlToken( TiXmlElement *pNode );

private:
	static LocalizationServer *m_sLocalizationServer;
	std::string m_LangPath;
	std::string m_CurrentLanguage;
	struct language
	{
		std::string m_Info;
		std::string m_File;
	};
	std::vector<language> m_SupportedLanguages;
	std::map<std::string, std::string> m_StringIdMap;
};

//----------------------------------------------------------------------------------------------------------------------

} // Namespace Localization

#endif // LOCAL_LOCALIZATIONSERVER_H_INC