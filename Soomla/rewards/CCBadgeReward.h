//
// Created by Fedor on 03/06/14.
//


#ifndef __CCBadgeReward_H_
#define __CCBadgeReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCReward.h"

namespace soomla {
    class CCBadgeReward : public CCReward {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mIconUrl, IconUrl, CCCoreConsts::JSON_ICON_URL);
    public:
        CCBadgeReward() : CCReward(), mIconUrl(NULL) {
        };

        static CCBadgeReward *create(
                cocos2d::CCString *id,
                cocos2d::CCString *name,
                cocos2d::CCString *iconUrl = NULL);

        SL_CREATE_WITH_DICTIONARY(CCBadgeReward);

        virtual bool init(
                cocos2d::CCString *id,
                cocos2d::CCString *name,
                cocos2d::CCString *iconUrl = NULL);

        virtual bool initWithDictionary(cocos2d::CCDictionary *dict);

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCBadgeReward();

        virtual const char *getType() const;

    protected:
        virtual bool takeInner() override;

        virtual bool giveInner() override;
    };
}

#endif //__CCBadgeReward_H_
