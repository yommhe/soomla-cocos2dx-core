//
// Created by Fedor on 03/06/14.
//

#include "CCBadgeReward.h"

soomla::CCBadgeReward *soomla::CCBadgeReward::create(
        cocos2d::__String *rewardId,
        cocos2d::__String *name,
        cocos2d::__Bool *repeatable,
        cocos2d::__String *iconUrl) {

    CCBadgeReward *ret = new CCBadgeReward();
    if (ret->init(rewardId, name, repeatable, iconUrl)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool soomla::CCBadgeReward::init(
        cocos2d::__String *rewardId,
        cocos2d::__String *name,
        cocos2d::__Bool *repeatable,
        cocos2d::__String *iconUrl) {

    bool result = CCReward::init(rewardId, name, repeatable);

    if (result) {
        setIconUrl(iconUrl);
        return true;
    } else {
        return false;
    }
}

bool soomla::CCBadgeReward::initWithDictionary(cocos2d::__Dictionary *dict) {
    CCReward::initWithDictionary(dict);

    fillIconUrlFromDict(dict);

    return true;
}

cocos2d::__Dictionary *soomla::CCBadgeReward::toDictionary() {
    cocos2d::__Dictionary *dict = CCReward::toDictionary();

    putIconUrlToDict(dict);

    return dict;
}

soomla::CCBadgeReward::~CCBadgeReward() {
    CC_SAFE_RELEASE(mIconUrl);
}

const char *soomla::CCBadgeReward::getType() {
    return CCCommonConsts::JSON_JSON_TYPE_BADGE;
}
