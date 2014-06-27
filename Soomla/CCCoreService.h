//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCCoreService_H_
#define __CCCoreService_H_

#include "cocos2d.h"
#include "CCError.h"
#include "CCReward.h"
#include "CCUserProfile.h"

namespace soomla {

    class CCCoreService: public cocos2d::Ref {
    public:
		/**
		   This class is singleton, use this function to access it.
		*/
        static CCCoreService* getInstance();

        static void initShared(cocos2d::__Dictionary *profileParams);

        CCCoreService();

        virtual bool init(cocos2d::__Dictionary *profileParams);

    };
};

#endif // !__CCCoreService_H_
