//
// Created by Fedor on 04/06/14.
//

#include "CCDomainFactory.h"
#include "CCCommonJSONConsts.h"

using namespace soomla;

static CCDomainFactory *s_SharedDomainFactory = nullptr;

CCDomainFactory *CCDomainFactory::getInstance() {
    if (!s_SharedDomainFactory) {
        s_SharedDomainFactory = new CCDomainFactory();
    }

    return s_SharedDomainFactory;
}

void CCDomainFactory::registerCreator(const char *key, TDomainCreator creator) {
    mCreators[key] = creator;
}

CCDomain * CCDomainFactory::createWithDictionary(cocos2d::__Dictionary *dict) {
    cocos2d::__String *type = dynamic_cast<cocos2d::__String *>(dict->objectForKey(JSON_JSON_TYPE));

    return this->createWithDictionaryAndType(dict, type->getCString());
}

soomla::CCDomain *CCDomainFactory::createWithDictionaryAndType(cocos2d::__Dictionary *dict, const char *type) {
    CC_ASSERT(type);
    if (type == nullptr) {
        return nullptr;
    }

    TDomainCreator creator = mCreators[type];
    CC_ASSERT(creator);
    if (creator == nullptr) {
        return nullptr;
    }

    return (*creator)(dict);
}
