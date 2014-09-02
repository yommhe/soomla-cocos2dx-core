#include "CCCoreEventDispatcher.h"
#include "CCDomainFactory.h"
#include "CCSoomlaEventDispatcher.h"

namespace soomla {

    USING_NS_CC;

    static CCCoreEventDispatcher *s_SharedInstance = NULL;

    CCCoreEventDispatcher *CCCoreEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCCoreEventDispatcher();
            s_SharedInstance->init();
        }

        return s_SharedInstance;
    }

    bool CCCoreEventDispatcher::init() {

        if (!CCAbstractAggregatedEventHandler::init()) {
            return false;
        }
        
        CCSoomlaEventDispatcher *eventDispatcher = CCSoomlaEventDispatcher::getInstance();

        eventDispatcher->registerEventHandler(CCCoreConsts::EVENT_REWARD_GIVEN,
                this, (SEL_EventHandler) (&CCCoreEventDispatcher::handle__EVENT_REWARD_GIVEN));
        eventDispatcher->registerEventHandler(CCCoreConsts::EVENT_REWARD_TAKEN,
                this, (SEL_EventHandler) (&CCCoreEventDispatcher::handle__EVENT_REWARD_TAKEN));

        return true;
    }

    void CCCoreEventDispatcher::onRewardGivenEvent(CCReward *reward) {
        FOR_EACH_EVENT_HANDLER(CCCoreEventHandler)
            eventHandler->onRewardGivenEvent(reward);
        }
    }

    void CCCoreEventDispatcher::onRewardTakenEvent(CCReward *reward) {
        FOR_EACH_EVENT_HANDLER(CCCoreEventHandler)
            eventHandler->onRewardTakenEvent(reward);
        }
    }


    void CCCoreEventDispatcher::handle__EVENT_REWARD_GIVEN(cocos2d::CCDictionary *parameters) {
        CCDictionary *rewardDict = dynamic_cast<CCDictionary *>(parameters->objectForKey("reward"));
        CC_ASSERT(rewardDict);
        CCReward *reward  = dynamic_cast<CCReward *>(CCDomainFactory::getInstance()->createWithDictionary(rewardDict));
        CC_ASSERT(reward);
        this->onRewardGivenEvent(reward);
    }

    void CCCoreEventDispatcher::handle__EVENT_REWARD_TAKEN(cocos2d::CCDictionary *parameters) {
        CCDictionary *rewardDict = dynamic_cast<CCDictionary *>(parameters->objectForKey("reward"));
        CC_ASSERT(rewardDict);
        CCReward *reward  = dynamic_cast<CCReward *>(CCDomainFactory::getInstance()->createWithDictionary(rewardDict));
        CC_ASSERT(reward);
        this->onRewardTakenEvent(reward);
    }
}
