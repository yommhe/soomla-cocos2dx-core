//
// Created by Fedor on 04/06/14.
//

#include "CCSequenceReward.h"

soomla::CCSequenceReward *soomla::CCSequenceReward::create(
        cocos2d::__String *rewardId,
        cocos2d::__String *name,
        cocos2d::__Bool *repeatable,
        cocos2d::__Array *rewards) {

    CCSequenceReward *ret = new CCSequenceReward();
    if (ret->init(rewardId, name, repeatable, rewards)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

soomla::CCSequenceReward::~CCSequenceReward() {
}

const char *soomla::CCSequenceReward::getType() {
    return CCCommonConsts::JSON_JSON_TYPE_SEQUENCE;
}
