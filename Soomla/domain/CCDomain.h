//
// Created by Fedor on 04/06/14.
//


#ifndef __CCDomain_H_
#define __CCDomain_H_

#include "cocos2d.h"

namespace soomla {
    class CCDomain: public cocos2d::CCObject {
    public:
        virtual bool initWithDictionary(cocos2d::CCDictionary *dict) = 0;
        virtual cocos2d::CCDictionary *toDictionary() = 0;
        virtual ~CCDomain() {};
    protected:
        cocos2d::CCArray *getDomainsFromDictArray(cocos2d::CCArray *dictArray);
        cocos2d::CCArray *getDictArrayFromDomains(cocos2d::CCArray *domainArray);
        cocos2d::CCDictionary *putTypeData(cocos2d::CCDictionary *dict, const char* type);
    };
}

#endif //__CCDomain_H_
