//
// Created by Fedor on 04/06/14.
//

#include "CCDomain.h"
#include "CCDomainHelper.h"
#include "CCCoreConsts.h"

cocos2d::CCArray *soomla::CCDomain::getDomainsFromDictArray(cocos2d::CCArray *dictArray) {
    return CCDomainHelper::getInstance()->getDomainsFromDictArray(dictArray);
}

cocos2d::CCArray *soomla::CCDomain::getDictArrayFromDomains(cocos2d::CCArray *domainArray) {
    return CCDomainHelper::getInstance()->getDictArrayFromDomains(domainArray);
}

cocos2d::CCDictionary *soomla::CCDomain::putTypeData(cocos2d::CCDictionary *dict, const char *type) {
    dict->setObject(cocos2d::CCString::create(type), CCCoreConsts::JSON_JSON_TYPE);
    return dict;
}
