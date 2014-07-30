//
// Created by Fedor on 03/06/14.
//

#include "CCRandomReward.h"

soomla::CCRandomReward *soomla::CCRandomReward::create(
        cocos2d::CCString *rewardId,
        cocos2d::CCString *name,
        cocos2d::CCBool *repeatable,
        cocos2d::CCArray *rewards) {

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
