//
// Created by Fedor on 04/06/14.
//


#ifndef __CCDomainFactory_H_
#define __CCDomainFactory_H_

#include "cocos2d.h"
#include "CCDomain.h"

namespace soomla {
    typedef soomla::CCDomain *(*TDomainCreator)(cocos2d::__Dictionary *dict);

    class CCDomainFactory {
    public:
        static CCDomainFactory* getInstance();
        void registerCreator(const char* key, TDomainCreator creator);
        soomla::CCDomain *createWithDictionary(cocos2d::__Dictionary *dict);
        soomla::CCDomain *createWithDictionaryAndType(cocos2d::__Dictionary *dict, const char *type);
    private:
        std::map<std::string, TDomainCreator> mCreators;
    };
}


#endif //__CCDomainFactory_H_
