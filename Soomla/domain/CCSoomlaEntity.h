//
// Created by Fedor Shubin on 7/23/14.
//
#ifndef __CCSoomlaEntity_H_
#define __CCSoomlaEntity_H_

#include "cocos2d.h"
#include "CCDomain.h"
#include "CCCoreConsts.h"
#include "CCSoomlaMacros.h"

namespace soomla {
    class CCSoomlaEntity: public CCDomain {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mId, Id, CCCoreConsts::JSON_ITEM_ITEM_ID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mName, Name, CCCoreConsts::JSON_ITEM_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mDescription, Description, CCCoreConsts::JSON_ITEM_DESCRIPTION);
    public:
        CCSoomlaEntity(): mId(NULL), mName(NULL), mDescription(NULL) {}

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *name = NULL, cocos2d::CCString *description = NULL);
        virtual bool initWithDictionary(cocos2d::CCDictionary* dict);

        virtual ~CCSoomlaEntity();

        /**
        * Converts this `CCSoomlaEntity` to a `CCDictionary`.
        * @return `CCDictionary` representation of this `CCSoomlaEntity`.
        */
        virtual cocos2d::CCDictionary* toDictionary();

        virtual char const * getType() const = 0;

        virtual bool equals(CCObject *obj) const;

        virtual CCSoomlaEntity *clone(const char *newId);
    };
}


#endif //__CCSoomlaEntity_H_
