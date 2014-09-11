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
                cocos2d::CCString *id,
                cocos2d::CCString *name,
                cocos2d::CCArray *rewards
        );

        SL_CREATE_WITH_DICTIONARY(CCSequenceReward);

        virtual ~CCSequenceReward();

        virtual const char *getType() const;
    public:
        CCReward *getLastGivenReward();
        bool hasMoreToGive();
        bool forceNextRewardToGive(CCReward *reward);

    protected:
        virtual bool takeInner();

        virtual bool giveInner();
    };
}

#endif //__CCSequenceReward_H_
