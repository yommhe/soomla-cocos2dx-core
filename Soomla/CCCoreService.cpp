//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCCoreService.h"
#include "CCNdkBridge.h"
#include "CCDomainFactory.h"
#include "CCBadgeReward.h"
#include "CCRandomReward.h"
#include "CCSequenceReward.h"
#include "CCCoreEventDispatcher.h"

using namespace cocos2d;

namespace soomla {

    USING_NS_CC;

    static CCCoreService *sInstance = NULL;

    CCCoreService *CCCoreService::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCCoreService();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCCoreService::initShared() {
        CCCoreService *coreService = CCCoreService::getInstance();
        if (!coreService->init()) {
            exit(1);
        }
    }

    CCCoreService::CCCoreService() {
    }

    bool CCCoreService::init() {

        CCCoreEventDispatcher::getInstance();    // to get sure it's inited

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::init"), "method");
        CCNdkBridge::callNative(params, NULL);

        CCDomainFactory::getInstance()->registerCreator(CCCommonConsts::JSON_JSON_TYPE_BADGE, (SEL_DomainCreator) CCBadgeReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCCommonConsts::JSON_JSON_TYPE_RANDOM, (SEL_DomainCreator) CCRandomReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCCommonConsts::JSON_JSON_TYPE_SEQUENCE, (SEL_DomainCreator) CCSequenceReward::createWithDictionary);

        return true;
    }
}
