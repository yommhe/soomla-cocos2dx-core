//
// Created by Fedor on 04/06/14.
//


#ifndef __CCDomainHelper_H_
#define __CCDomainHelper_H_

#include "cocos2d.h"
#include "CCDomain.h"

namespace soomla {
    class CCDomainHelper {
    public:
        static CCDomainHelper* getInstance();
        cocos2d::CCArray *getDomainsFromDictArray(cocos2d::CCArray *dictArray, const char *type = NULL);
        cocos2d::CCArray *getDictArrayFromDomains(cocos2d::CCArray *domainArray);
    };
}


#endif //__CCDomainHelper_H_
