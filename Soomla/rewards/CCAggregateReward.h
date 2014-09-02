//
// Created by Fedor on 03/06/14.
//


#ifndef __CCAggregateReward_H_
#define __CCAggregateReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCCoreConsts.h"
#include "CCReward.h"

namespace soomla {
    class CCAggregateReward : public CCReward {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCArray *, mRewards, Rewards, CCCoreConsts::JSON_REWARDS);
    public:
        CCAggregateReward() : CCReward(), mRewards(NULL) {
        };

        virtual bool init(
                cocos2d::CCString *id,
                cocos2d::CCString *name,
                cocos2d::CCArray *rewards,
                CCSchedule *schedule = NULL);

        virtual bool initWithDictionary(cocos2d::CCDictionary *dict);

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCAggregateReward();
    };
}

#endif //__CCAggregateReward_H_
