//
// Created by Fedor on 03/06/14.
//

#include "CCRandomReward.h"

soomla::CCRandomReward *soomla::CCRandomReward::create(
        cocos2d::__String *rewardId,
        cocos2d::__String *name,
        cocos2d::__Bool *repeatable,
        cocos2d::__Array *rewards) {

    CCRandomReward *ret = new CCRandomReward();
    if (ret->init(rewardId, name, repeatable, rewards)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

soomla::CCRandomReward::~CCRandomReward() {
}

const char *soomla::CCRandomReward::getType() {
    return CCCommonConsts::JSON_JSON_TYPE_RANDOM;
}
