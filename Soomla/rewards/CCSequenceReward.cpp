//
// Created by Fedor on 04/06/14.
//

#include "CCSequenceReward.h"

soomla::CCSequenceReward *soomla::CCSequenceReward::create(
        cocos2d::CCString *rewardId,
        cocos2d::CCString *name,
        cocos2d::CCBool *repeatable,
        cocos2d::CCArray *rewards) {

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
