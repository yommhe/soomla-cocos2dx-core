//
// Created by Fedor on 03/06/14.
//

#include "CCAggregateReward.h"

bool soomla::CCAggregateReward::init(
        cocos2d::CCString *id,
        cocos2d::CCString *name,
        cocos2d::CCArray *rewards,
        CCSchedule *schedule) {

    bool result = CCReward::init(id, name, schedule);

    if (result) {
        setRewards(rewards);
        return true;
    } else {
        return false;
    }
}

bool soomla::CCAggregateReward::initWithDictionary(cocos2d::CCDictionary *dict) {
    CCReward::initWithDictionary(dict);

    cocos2d::CCArray *dictArray = dynamic_cast<cocos2d::CCArray *>(dict->objectForKey(CCCoreConsts::JSON_REWARDS));
    CC_ASSERT(dictArray);
    setRewards(this->getDomainsFromDictArray(dictArray));

    return true;
}

cocos2d::CCDictionary *soomla::CCAggregateReward::toDictionary() {
    cocos2d::CCDictionary *dict = CCReward::toDictionary();

    cocos2d::CCArray *dictArray = this->getDictArrayFromDomains(this->getDictArrayFromDomains(getRewards()));
    if (dictArray != nullptr) {
        dict->setObject(dictArray, CCCoreConsts::JSON_REWARDS);
    }

    return dict;
}

soomla::CCAggregateReward::~CCAggregateReward() {
    CC_SAFE_RELEASE(mRewards);
}
