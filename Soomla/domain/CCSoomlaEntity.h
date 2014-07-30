//
// Created by Fedor Shubin on 7/23/14.
//
#ifndef __CCSoomlaEntity_H_
#define __CCSoomlaEntity_H_

#include "cocos2d.h"
#include "CCDomain.h"
#include "CCCommonConsts.h"
#include "CCSoomlaMacros.h"

namespace soomla {
    class CCSoomlaEntity : public CCDomain {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mName, Name, CCCommonConsts::JSON_ITEM_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mDescription, Description, CCCommonConsts::JSON_ITEM_DESCRIPTION);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mId, Id, CCCommonConsts::JSON_ITEM_ITEM_ID);

    public:
        CCSoomlaEntity(): mName(NULL), mDescription(NULL), mId(NULL) {}

        virtual bool init(cocos2d::CCString *name, cocos2d::CCString *description, cocos2d::CCString *id);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual ~CCSoomlaEntity();

        /**
        * Converts this `CCSoomlaEntity` to a `CCDictionary`.
        * @return `CCDictionary` representation of this `CCSoomlaEntity`.
        */
        virtual cocos2d::CCDictionary* toDictionary();
    };
}


#endif //__CCSoomlaEntity_H_
