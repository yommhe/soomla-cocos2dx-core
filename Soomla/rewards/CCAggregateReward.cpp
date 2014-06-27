//
// Created by Fedor on 03/06/14.
//

#include "CCAggregateReward.h"

bool soomla::CCAggregateReward::init(
        cocos2d::__String *rewardId,
        cocos2d::__String *name,
        cocos2d::__Bool *repeatable,
        cocos2d::__Array *rewards) {

    bool result = CCReward::init(rewardId, name, repeatable);

    if (result) {
        setRewards(rewards);
        return true;
    } else {
        return false;
    }
}

bool soomla::CCAggregateReward::initWithDictionary(cocos2d::__Dictionary *dict) {
    CCReward::initWithDictionary(dict);

    cocos2d::__Array *dictArray = dynamic_cast<cocos2d::__Array *>(dict->objectForKey(CCProfileConsts::JSON_REWARDS));
    CC_ASSERT(dictArray);
    setRewards(this->getDomainsFromDictArray(dictArray));

    return true;
}

cocos2d::__Dictionary *soomla::CCAggregateReward::toDictionary() {
    cocos2d::__Dictionary *dict = CCReward::toDictionary();

    cocos2d::__Array *dictArray = this->getDictArrayFromDomains(this->getDictArrayFromDomains(getRewards()));
    if (dictArray != nullptr) {
        dict->setObject(dictArray, CCProfileConsts::JSON_REWARDS);
    }

    return dict;
}

soomla::CCAggregateReward::~CCAggregateReward() {
    CC_SAFE_RELEASE(mRewards);
}
