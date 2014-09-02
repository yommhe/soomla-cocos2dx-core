//
// Created by Fedor on 04/06/14.
//

#include "CCDomainFactory.h"
#include "CCCoreConsts.h"

USING_NS_CC;

using namespace soomla;

static CCDomainFactory *s_SharedDomainFactory = nullptr;

CCDomainFactory *CCDomainFactory::getInstance() {
    if (!s_SharedDomainFactory) {
        s_SharedDomainFactory = new CCDomainFactory();
    }

    return s_SharedDomainFactory;
}

void CCDomainFactory::registerCreator(const char *key, std::function<soomla::CCDomain *(CCDictionary *)> creator) {
    mCreators[key] = creator;
}

CCDomain * CCDomainFactory::createWithDictionary(CCDictionary *dict) {
    Ref *typeRef = dict->objectForKey(CCCoreConsts::JSON_JSON_TYPE);
    CC_ASSERT(typeRef != nullptr);
    CCString *type = dynamic_cast<CCString *>(typeRef);
    CC_ASSERT(type != nullptr);

    return this->createWithDictionaryAndType(dict, type->getCString());
}

soomla::CCDomain *CCDomainFactory::createWithDictionaryAndType(CCDictionary *dict, const char *type) {
    CC_ASSERT(type);
    if (type == nullptr) {
        return nullptr;
    }

    std::function<soomla::CCDomain *(CCDictionary *)> creator = mCreators[type];
    CC_ASSERT(creator);
    if (creator == nullptr) {
        return nullptr;
    }

    return creator(dict);
}
