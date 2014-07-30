//
// Created by Fedor on 03/06/14.
//

#include "CCAggregateReward.h"

bool soomla::CCAggregateReward::init(
        cocos2d::CCString *rewardId,
        cocos2d::CCString *name,
        cocos2d::CCBool *repeatable,
        cocos2d::CCArray *rewards) {

    bool result = CCReward::init(rewardId, name, repeatable);

    if (result) {
        setRewards(rewards);
        return true;
    } else {
        return false;
    }
}

bool soomla::CCAggregateReward::initWithDictionary(cocos2d::CCDictionary *dict) {
    CCReward::initWithDictionary(dict);

    cocos2d::CCArray *dictArray = dynamic_cast<cocos2d::CCArray *>(dict->objectForKey(CCCommonConsts::JSON_REWARDS));
    CC_ASSERT(dictArray);
    setRewards(this->getDomainsFromDictArray(dictArray));

    return true;
}

cocos2d::CCDictionary *soomla::CCAggregateReward::toDictionary() {
    cocos2d::CCDictionary *dict = CCReward::toDictionary();

    cocos2d::CCArray *dictArray = this->getDictArrayFromDomains(this->getDictArrayFromDomains(getRewards()));
    if (dictArray != NULL) {
        dict->setObject(dictArray, CCCommonConsts::JSON_REWARDS);
    }

    return dict;
}

soomla::CCAggregateReward::~CCAggregateReward() {
    CC_SAFE_RELEASE(mRewards);
}
