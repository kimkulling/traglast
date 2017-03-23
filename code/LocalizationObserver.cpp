#include "stdafx.h"
#include "LocalizationObserver.h"
#include "LocalizationObserverSubject.h"
#include <cassert>

namespace Localization
{

LocalizationObserver::LocalizationObserver( LocalizationObserverSubject *pWindow ) :
	m_pSubject( pWindow )
{
	assert( NULL != m_pSubject );
}
	
LocalizationObserver::~LocalizationObserver()
{
	m_pSubject = NULL;
}
	
void LocalizationObserver::notifyStateChange()
{
	assert( NULL != m_pSubject );
	if ( NULL != m_pSubject )
	{
		m_pSubject->onLanguageChange();
	}
}

} // Namespace Localization
