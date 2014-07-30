//
// Created by Fedor Shubin on 7/23/14.
//

#include "CCSoomlaEntity.h"

namespace soomla {

    using namespace cocos2d;

    bool CCSoomlaEntity::init(cocos2d::CCString *name, cocos2d::CCString *description, cocos2d::CCString *id) {
        setName(name);
        setDescription(description);
        setId(id);

        return true;
    }

    bool CCSoomlaEntity::initWithDictionary(cocos2d::CCDictionary *dict) {
        fillNameFromDict(dict);
        fillDescriptionFromDict(dict);
        fillIdFromDict(dict);

        return true;
    }


    CCSoomlaEntity::~CCSoomlaEntity() {
        CC_SAFE_RELEASE(mName);
        CC_SAFE_RELEASE(mDescription);
        CC_SAFE_RELEASE(mId);
    }

    cocos2d::CCDictionary *CCSoomlaEntity::toDictionary() {
        CCDictionary* dict = CCDictionary::create();
        putNameToDict(dict);
        putDescriptionToDict(dict);
        putIdToDict(dict);

        return dict;
    }
}