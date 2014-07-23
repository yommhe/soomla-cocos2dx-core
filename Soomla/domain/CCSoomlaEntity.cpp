//
// Created by Fedor Shubin on 7/23/14.
//

#include "CCSoomlaEntity.h"

namespace soomla {

    using namespace cocos2d;

    bool CCSoomlaEntity::init(cocos2d::__String *name, cocos2d::__String *description, cocos2d::__String *id) {
        setName(name);
        setDescription(description);
        setId(id);

        return true;
    }

    bool CCSoomlaEntity::initWithDictionary(cocos2d::__Dictionary *dict) {
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

    cocos2d::__Dictionary *CCSoomlaEntity::toDictionary() {
        __Dictionary* dict = __Dictionary::create();
        putNameToDict(dict);
        putDescriptionToDict(dict);
        putIdToDict(dict);

        return dict;
    }
}