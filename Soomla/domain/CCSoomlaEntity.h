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
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String*, mId, Id, CCCoreConsts::JSON_ITEM_ITEM_ID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String*, mName, Name, CCCoreConsts::JSON_ITEM_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String*, mDescription, Description, CCCoreConsts::JSON_ITEM_DESCRIPTION);
    public:
        CCSoomlaEntity(): mId(NULL), mName(NULL), mDescription(NULL) {}

        virtual bool init(cocos2d::__String *id, cocos2d::__String *name = NULL, cocos2d::__String *description = NULL);
        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual ~CCSoomlaEntity();

        /**
        * Converts this `CCSoomlaEntity` to a `CCDictionary`.
        * @return `CCDictionary` representation of this `CCSoomlaEntity`.
        */
        virtual cocos2d::__Dictionary* toDictionary();

        virtual const char *getType() = 0;

        virtual bool equals(cocos2d::Ref *obj);
    };
}


#endif //__CCSoomlaEntity_H_
