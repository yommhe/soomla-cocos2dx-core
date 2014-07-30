//
// Created by Fedor on 03/06/14.
//

#include "CCReward.h"

bool soomla::CCReward::init(cocos2d::CCString *rewardId, cocos2d::CCString *name, cocos2d::CCBool *repeatable) {
    setRewardId(rewardId);
    setName(name);
    setRepeatable(repeatable);

    return true;
}

bool soomla::CCReward::initWithDictionary(cocos2d::CCDictionary *dict) {
    fillRewardIdFromDict(dict);
    fillNameFromDict(dict);
    fillRepeatableFromDict(dict);

    return true;
}

cocos2d::CCDictionary *soomla::CCReward::toDictionary() {
    cocos2d::CCDictionary* dict = cocos2d::CCDictionary::create();

    putRewardIdToDict(dict);
    putNameToDict(dict);
    putRepeatableToDict(dict);

    return putTypeData(dict, getType());
}

soomla::CCReward::~CCReward() {
    CC_SAFE_RELEASE(mRewardId);
    CC_SAFE_RELEASE(mName);
    CC_SAFE_RELEASE(mRepeatable);
}
