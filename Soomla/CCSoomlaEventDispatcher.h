#ifndef __CCEventDispatcher_H_
#define __CCEventDispatcher_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"

namespace soomla {

    typedef void (cocos2d::CCObject::*SEL_EventHandler)(cocos2d::CCDictionary*);

    struct StructEventHandler {
        StructEventHandler(cocos2d::CCObject *target, SEL_EventHandler selector)
                : target(target), selector(selector) {
        }

        cocos2d::CCObject *target;
        SEL_EventHandler selector;
    };

    class CCSoomlaEventDispatcher : public cocos2d::CCObject {
    private:
        std::map<std::string, StructEventHandler *> mEventHandlers;
    public:
        static CCSoomlaEventDispatcher *getInstance();

        void ndkCallback(cocos2d::CCDictionary *parameters);

        void registerEventHandler(const char *key, cocos2d::CCObject *target, SEL_EventHandler selector);

        void unregisterEventHandler(const char *key);

        virtual ~CCSoomlaEventDispatcher();
    };
};

#endif //__CCEventDispatcher_H_
