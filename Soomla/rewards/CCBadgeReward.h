//
// Created by Fedor on 03/06/14.
//


#ifndef __CCBadgeReward_H_
#define __CCBadgeReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCCommonConsts.h"
#include "CCReward.h"

namespace soomla {
    class CCBadgeReward : public CCReward {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mIconUrl, IconUrl, CCCommonConsts::JSON_ICON_URL);
    public:
        CCBadgeReward() : CCReward(), mIconUrl(NULL) {
        };

        static CCBadgeReward *create(
                cocos2d::CCString *rewardId,
                cocos2d::CCString *name,
                cocos2d::CCBool *repeatable,
                cocos2d::CCString *iconUrl);

        SL_CREATE_WITH_DICTIONARY(CCBadgeReward);

        virtual bool init(
                cocos2d::CCString *rewardId,
                cocos2d::CCString *name,
                cocos2d::CCBool *repeatable,
                cocos2d::CCString *iconUrl);

        virtual bool initWithDictionary(cocos2d::CCDictionary *dict);

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCBadgeReward();

        virtual const char *getType();
    };
}

#endif //__CCBadgeReward_H_
