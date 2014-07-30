//
// Created by Fedor on 04/06/14.
//


#ifndef __CCDomainFactory_H_
#define __CCDomainFactory_H_

#include "cocos2d.h"
#include "CCDomain.h"

namespace soomla {
    typedef soomla::CCDomain *(*SEL_DomainCreator)(cocos2d::CCDictionary*);

    class CCDomainFactory {
    public:
        static CCDomainFactory* getInstance();
        void registerCreator(const char *key, SEL_DomainCreator selector);
        soomla::CCDomain *createWithDictionary(cocos2d::CCDictionary *dict);
        soomla::CCDomain *createWithDictionaryAndType(cocos2d::CCDictionary *dict, const char *type);
    private:
        std::map<std::string, SEL_DomainCreator> mCreators;
    };
}


#endif //__CCDomainFactory_H_
