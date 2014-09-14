//
// Created by Fedor on 03/06/14.
//


#ifndef __CCReward_H_
#define __CCReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCDomain.h"
#include "CCCoreConsts.h"
#include "CCSchedule.h"
#include "CCSoomlaEntity.h"

namespace soomla {
    class CCReward : public CCSoomlaEntity {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(CCSchedule *, mSchedule, Schedule, CCCoreConsts::JSON_SCHEDULE);
    public:
        CCReward() : CCSoomlaEntity(), mSchedule(NULL) {
        };

        virtual bool init(cocos2d::CCString *id, cocos2d::CCString *name, CCSchedule *schedule = NULL);

        virtual bool initWithDictionary(cocos2d::CCDictionary *dict);

        virtual cocos2d::CCDictionary *toDictionary();

        virtual ~CCReward();

    public:
        virtual bool take();
        virtual bool give();
        bool isOwned();

    protected:
        virtual bool takeInner() = 0;
        virtual bool giveInner() = 0;
    };
}

#endif //__CCReward_H_
