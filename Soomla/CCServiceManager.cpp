//
// Created by Fedor Shubin on 6/25/14.
//

#include "CCServiceManager.h"
#include "CCNdkBridge.h"

USING_NS_CC;

namespace soomla {
    static CCServiceManager *sInstance = nullptr;

    CCServiceManager *CCServiceManager::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCServiceManager();
            sInstance->init();
            sInstance->retain();
        }
        return sInstance;
    }

    bool CCServiceManager::init() {
        CCCoreService::initShared();

        return true;
    }

    void CCServiceManager::setCommonParams(cocos2d::__Dictionary *commonParams) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCServiceManager::setCommonParams"), "method");
        params->setObject(commonParams, "params");
        CCNdkBridge::callNative(params, NULL);
    }
}

