#ifndef LOCAL_LOCALLIZATIONOBSERVER_H_INC
#define LOCAL_LOCALLIZATIONOBSERVER_H_INC

#include "Observer.h"

namespace Localization
{

class LocalizationObserverSubject;

class LocalizationObserver : public Core::Observer
{
public:
	LocalizationObserver( LocalizationObserverSubject *pWindow );
	~LocalizationObserver();
	void notifyStateChange();

private:
	LocalizationObserverSubject *m_pSubject;
};

}

#endif // LOCAL_LOCALLIZATIONOBSERVER_H_INC
