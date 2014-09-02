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
#include "CCSoomlaUtils.h"

using namespace cocos2d;

namespace soomla {

    USING_NS_CC;

#define TAG "SOOMLA CoreService"

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
        CCNdkBridge::callNative(params, nullptr);

        CCDomainFactory::getInstance()->registerCreator(CCCoreConsts::JSON_JSON_TYPE_BADGE,
                &CCBadgeReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCCoreConsts::JSON_JSON_TYPE_RANDOM,
                &CCRandomReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCCoreConsts::JSON_JSON_TYPE_SEQUENCE,
                &CCSequenceReward::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCCoreConsts::JSON_JSON_TYPE_SCHEDULE,
                &CCSchedule::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCCoreConsts::JSON_JSON_TYPE_DATE_TIME_RANGE,
                &CCSchedule::CCDateTimeRange::createWithDictionary);

        return true;
    }

    int CCCoreService::getTimesGiven(CCReward *reward) {
        CCError *error = NULL;

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::getTimesGiven"), "method");
        params->setObject(reward->toDictionary(), "reward");
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return -1;
        }

        if (retParams == NULL) {
            return -1;
        }

        CCInteger *retValue = (CCInteger *) retParams->objectForKey("return");
        if (!retValue) {
            return -1;
        }

        return retValue->getValue();
    }

    void CCCoreService::setRewardStatus(CCReward *reward, bool give, bool notify) {
        CCError *error = NULL;

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::setRewardStatus"), "method");
        params->setObject(reward->toDictionary(), "reward");
        params->setObject(__Bool::create(give), "give");
        params->setObject(__Bool::create(notify), "notify");
        (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    int CCCoreService::getLastSeqIdxGiven(CCSequenceReward *sequenceReward) {
        CCError *error = NULL;

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::getLastSeqIdxGiven"), "method");
        params->setObject(sequenceReward->toDictionary(), "reward");
        CCDictionary *retParams = (CCDictionary *) CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return -1;
        }

        if (retParams == NULL) {
            return -1;
        }

        CCInteger *retValue = (CCInteger *) retParams->objectForKey("return");
        if (!retValue) {
            return -1;
        }

        return retValue->getValue();
    }

    void CCCoreService::setLastSeqIdxGiven(CCSequenceReward *sequenceReward, unsigned int idx) {
        CCError *error = NULL;

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCCoreService::setLastSeqIdxGiven"), "method");
        params->setObject(sequenceReward->toDictionary(), "reward");
        params->setObject(CCInteger::create(idx), "idx");
        CCNdkBridge::callNative (params, &error);

        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }
}
