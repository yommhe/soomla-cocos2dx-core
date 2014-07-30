//
// Created by Fedor on 03/06/14.
//

#include "CCBadgeReward.h"

soomla::CCBadgeReward *soomla::CCBadgeReward::create(
        cocos2d::CCString *rewardId,
        cocos2d::CCString *name,
        cocos2d::CCBool *repeatable,
        cocos2d::CCString *iconUrl) {

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
        cocos2d::CCString *rewardId,
        cocos2d::CCString *name,
        cocos2d::CCBool *repeatable,
        cocos2d::CCString *iconUrl) {

    bool result = CCReward::init(rewardId, name, repeatable);

    if (result) {
        setIconUrl(iconUrl);
        return true;
    } else {
        return false;
    }
}

bool soomla::CCBadgeReward::initWithDictionary(cocos2d::CCDictionary *dict) {
    CCReward::initWithDictionary(dict);

    fillIconUrlFromDict(dict);

    return true;
}

cocos2d::CCDictionary *soomla::CCBadgeReward::toDictionary() {
    cocos2d::CCDictionary *dict = CCReward::toDictionary();

    putIconUrlToDict(dict);

    return dict;
}

soomla::CCBadgeReward::~CCBadgeReward() {
    CC_SAFE_RELEASE(mIconUrl);
}

const char *soomla::CCBadgeReward::getType() {
    return CCCommonConsts::JSON_JSON_TYPE_BADGE;
}
