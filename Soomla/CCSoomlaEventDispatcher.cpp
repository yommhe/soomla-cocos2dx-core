#include "CCSoomlaEventDispatcher.h"

#ifdef COCOS2D_JAVASCRIPT
#include "JSBinding.h"
#endif

namespace soomla {

    USING_NS_CC;

    static CCSoomlaEventDispatcher *s_SharedInstance = NULL;

    CCSoomlaEventDispatcher *CCSoomlaEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCSoomlaEventDispatcher();
        }

        return s_SharedInstance;
    }

	void CCSoomlaEventDispatcher::registerEventHandler(const char *key, cocos2d::CCObject *target, SEL_EventHandler selector) {
		mEventHandlers[key] = new StructEventHandler(target, selector);
	}

    void CCSoomlaEventDispatcher::unregisterEventHandler(const char *key) {
        if (mEventHandlers.find(key) != mEventHandlers.end()) {
            StructEventHandler *handler = mEventHandlers[key];
            mEventHandlers.erase(key);
            delete handler;
        }
    }

    void CCSoomlaEventDispatcher::ndkCallback(CCDictionary *parameters) {
#ifdef COCOS2D_JAVASCRIPT
        Soomla::JSBinding::ndkCallback(parameters);
#else
        CCString *eventName = dynamic_cast<CCString *>(parameters->objectForKey("method"));
        CC_ASSERT(eventName);
        
        if (mEventHandlers.find(eventName->getCString()) != mEventHandlers.end()) {
            StructEventHandler *handler = mEventHandlers[eventName->getCString()];
            ((handler->target)->*(handler->selector))(parameters);
        }
        else {
            CCLog("Unregistered event happened: %s", eventName->getCString());
        }
#endif
    }

    CCSoomlaEventDispatcher::~CCSoomlaEventDispatcher() {
        std::map<std::string, StructEventHandler *>::iterator iter;
        for (iter = mEventHandlers.begin(); iter != mEventHandlers.end(); ++iter) {
            this->unregisterEventHandler(iter->first.c_str());
        }
    }
}
