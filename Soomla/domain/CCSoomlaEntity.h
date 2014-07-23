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
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String*, mName, Name, CCCommonConsts::JSON_ITEM_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String*, mDescription, Description, CCCommonConsts::JSON_ITEM_DESCRIPTION);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String*, mId, Id, CCCommonConsts::JSON_ITEM_ITEM_ID);

    public:
        CCSoomlaEntity(): mName(NULL), mDescription(NULL), mId(NULL) {}

        virtual bool init(cocos2d::__String *name, cocos2d::__String *description, cocos2d::__String *id);
        virtual bool initWithDictionary(cocos2d::__Dictionary* dict);

        virtual ~CCSoomlaEntity();

        /**
        * Converts this `CCSoomlaEntity` to a `CCDictionary`.
        * @return `CCDictionary` representation of this `CCSoomlaEntity`.
        */
        virtual cocos2d::__Dictionary* toDictionary();
    };
}


#endif //__CCSoomlaEntity_H_
