//
// Created by Fedor on 04/06/14.
//

#include "CCDomainFactory.h"
#include "CCCommonConsts.h"

USING_NS_CC;

using namespace soomla;

static CCDomainFactory *s_SharedDomainFactory = NULL;

CCDomainFactory *CCDomainFactory::getInstance() {
    if (!s_SharedDomainFactory) {
        s_SharedDomainFactory = new CCDomainFactory();
    }

    return s_SharedDomainFactory;
}

void CCDomainFactory::registerCreator(const char *key, SEL_DomainCreator selector) {
    mCreators[key] = selector;
}

CCDomain * CCDomainFactory::createWithDictionary(CCDictionary *dict) {
    CCObject *typeRef = dict->objectForKey(CCCommonConsts::JSON_JSON_TYPE);
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
