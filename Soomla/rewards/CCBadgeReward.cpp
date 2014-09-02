//
// Created by Fedor on 03/06/14.
//

#include "CCBadgeReward.h"

soomla::CCBadgeReward *soomla::CCBadgeReward::create(
        cocos2d::CCString *id,
        cocos2d::CCString *name,
        cocos2d::CCString *iconUrl) {

    CCBadgeReward *ret = new CCBadgeReward();
    if (ret->init(id, name, iconUrl)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool soomla::CCBadgeReward::init(
        cocos2d::CCString *id,
        cocos2d::CCString *name,
        cocos2d::CCString *iconUrl) {

    bool result = CCReward::init(id, name);

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

const char *soomla::CCBadgeReward::getType() const {
    return CCCoreConsts::JSON_JSON_TYPE_BADGE;
}


bool soomla::CCBadgeReward::takeInner() {
    // nothing to do here... the parent Reward takes in storage
    return true;
}

bool soomla::CCBadgeReward::giveInner() {
    // nothing to do here... the parent Reward gives in storage
    return true;
}
