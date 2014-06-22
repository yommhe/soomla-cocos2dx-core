#include "CCEventDispatcher.h"

namespace soomla {

    USING_NS_CC;

    static CCEventDispatcher *s_SharedInstance = NULL;

    CCEventDispatcher *CCEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCEventDispatcher();
        }

        return s_SharedInstance;
    }

	void CCEventDispatcher::registerEventHandler(const char *key, std::function<void(__Dictionary *)> handler) {
		mEventHandlers[key] = handler;
	}

    void CCEventDispatcher::unregisterEventHandler(const char *key) {
        mEventHandlers.erase(key);
    }

    void CCEventDispatcher::ndkCallback(__Dictionary *parameters) {
        __String *eventName = dynamic_cast<__String *>(parameters->objectForKey("method"));
        CC_ASSERT(eventName);

        std::function<void(__Dictionary *)> handler = mEventHandlers[eventName->getCString()];

        if (handler) {
            handler(parameters);
        }
		else {
            log("Unregistered event happened: %s", eventName->getCString());
        }
    }
}
