//
// Created by Fedor on 04/06/14.
//

#include "CCDomainFactory.h"
#include "CCCoreConsts.h"

USING_NS_CC;

using namespace soomla;

static CCDomainFactory *s_SharedDomainFactory = NULL;

CCDomainFactory *CCDomainFactory::getInstance() {
    if (!s_SharedDomainFactory) {
        s_SharedDomainFactory = new CCDomainFactory();
    }

    return s_SharedDomainFactory;
}

void CCDomainFactory::registerCreator(const char *key, SEL_DomainCreator creator) {
    mCreators[key] = creator;
}

CCDomain * CCDomainFactory::createWithDictionary(CCDictionary *dict) {
    CCObject *typeRef = dict->objectForKey(CCCoreConsts::JSON_JSON_TYPE);
    CC_ASSERT(typeRef != NULL);
    CCString *type = dynamic_cast<CCString *>(typeRef);
    CC_ASSERT(type != NULL);

    return this->createWithDictionaryAndType(dict, type->getCString());
}

soomla::CCDomain *CCDomainFactory::createWithDictionaryAndType(CCDictionary *dict, const char *type) {
    CC_ASSERT(type);
    if (type == NULL) {
        return NULL;
    }

    SEL_DomainCreator creator = mCreators[type];
    CC_ASSERT(creator);
    if (creator == NULL) {
        return NULL;
    }

    return creator(dict);
}
