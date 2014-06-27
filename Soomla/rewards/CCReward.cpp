//
// Created by Fedor on 03/06/14.
//

#include "CCReward.h"
#include "CCDomainFactory.h"

bool soomla::CCReward::init(cocos2d::__String *rewardId, cocos2d::__String *name, cocos2d::__Bool *repeatable) {
    setRewardId(rewardId);
    setName(name);
    setRepeatable(repeatable);

    return true;
}

bool soomla::CCReward::initWithDictionary(cocos2d::__Dictionary *dict) {
    fillRewardIdFromDict(dict);
    fillNameFromDict(dict);
    fillRepeatableFromDict(dict);

    return true;
}

cocos2d::__Dictionary *soomla::CCReward::toDictionary() {
    cocos2d::__Dictionary* dict = cocos2d::__Dictionary::create();

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
