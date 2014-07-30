//
// Created by Fedor on 04/06/14.
//


#include "CCReward.h"

#ifndef __CCSequenceReward_H_
#define __CCSequenceReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCAggregateReward.h"

namespace soomla {
    class CCSequenceReward : public CCAggregateReward {
    public:
        CCSequenceReward() : CCAggregateReward() {
        };

        static CCSequenceReward *create(
                cocos2d::CCString *rewardId,
                cocos2d::CCString *name,
                cocos2d::CCBool *repeatable,
                cocos2d::CCArray *rewards);

        SL_CREATE_WITH_DICTIONARY(CCSequenceReward);

        virtual ~CCSequenceReward();

        virtual const char *getType();
    };
}

#endif //__CCSequenceReward_H_
