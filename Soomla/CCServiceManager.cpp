//
// Created by Fedor Shubin on 6/25/14.
//

#include "CCServiceManager.h"
#include "CCNdkBridge.h"

USING_NS_CC;

namespace soomla {
    static CCServiceManager *sInstance = NULL;

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

    void CCServiceManager::setCommonParams(cocos2d::CCDictionary *commonParams) {
        CCString *customSecret = dynamic_cast<CCString *>(commonParams->objectForKey("customSecret"));
        if (customSecret == NULL || customSecret->length()==0) {
            CCString *message = CCString::createWithFormat("Can't initialize CCStoreService without customSecret");
            CCLOGERROR("%s %s", "CCServiceManager", message->getCString());

            return;
        }

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCServiceManager::setCommonParams"), "method");
        params->setObject(commonParams, "params");
        CCNdkBridge::callNative(params, NULL);
    }
}

