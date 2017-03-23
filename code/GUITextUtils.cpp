#include "stdafx.h"
#include "GUITextUtils.h"
#include "afxwin.h"
#include "LocalizationServer.h"

namespace GUI
{

//----------------------------------------------------------------------------------------------------------------------
bool GUITextUtils::setWindowTextPerId( CWnd *pWindow, std::string &rTextId )
{
	assert( !rTextId.empty() );

	Localization::LocalizationServer *pLocalizationServer = Localization::LocalizationServer::get();
	std::string localizedText = pLocalizationServer->getText( rTextId );
	bool result = true;
	if ( !localizedText.empty() )
		pWindow->SetWindowTextA( localizedText.c_str() );
	else
		result = false;
	return result;
}

//----------------------------------------------------------------------------------------------------------------------
bool GUITextUtils::setLocalizedText( CWnd *pDialog, Core::i32 controlId, const std::string &rTextId )
{
	assert( NULL != pDialog );
	assert( -1 != controlId );
	assert( !rTextId.empty() );

	Localization::LocalizationServer *pLocalizationServer = Localization::LocalizationServer::get();
	CWnd *pControl = pDialog->GetDlgItem( controlId );
	bool result = true;
	if ( NULL != pControl )
	{
		std::string text = pLocalizationServer->getText( rTextId );
		if ( !text.empty() )
			pControl->SetWindowTextA( text.c_str() );
		else
			result = false;
	}
	else 
		result = false;

	return result;
}

//----------------------------------------------------------------------------------------------------------------------

} // Namespace GUI
