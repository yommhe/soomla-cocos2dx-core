//
// Created by Fedor Shubin on 5/21/13.
//

#ifndef __CCError_H_
#define __CCError_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"

namespace soomla {

    class CCError : public cocos2d::CCObject {
    public:
        static CCError *createWithObject(cocos2d::CCObject *obj);
        const char *getInfo() {return mInfo.c_str();};
    private:
		/**
		   Extra information about what went wrong
		 */
        std::string mInfo;

        CCError():
            mInfo("") {}

        bool init(std::string &errorInfo);
    };
};


#endif //__CCError_H_
