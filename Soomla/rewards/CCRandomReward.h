//
// Created by Fedor on 03/06/14.
//


#ifndef __CCRandomReward_H_
#define __CCRandomReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCAggregateReward.h"

namespace soomla {
    class CCRandomReward : public CCAggregateReward {
    public:
        CCRandomReward() : CCAggregateReward() {
        };

        static CCRandomReward *create(
                cocos2d::CCString *rewardId,
                cocos2d::CCString *name,
                cocos2d::CCBool *repeatable,
                cocos2d::CCArray *rewards);

        SL_CREATE_WITH_DICTIONARY(CCRandomReward);

        virtual ~CCRandomReward();

        virtual const char *getType();
    };
}

#endif //__CCRandomReward_H_
