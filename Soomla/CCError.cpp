//
// Created by Fedor Shubin on 5/21/13.
//


#include "CCError.h"

USING_NS_CC;

namespace soomla {
    #define JSON_ERROR_INFO "errorInfo"

    #define TAG "CCError"

    CCError *CCError::createWithObject(cocos2d::Ref *obj) {
        __Dictionary *dict = dynamic_cast<__Dictionary *>(obj);
        if (dict != NULL && dict->objectForKey(JSON_ERROR_INFO) != NULL) {
            __String *errorInfo = dynamic_cast<__String *>(dict->objectForKey(JSON_ERROR_INFO));
            CC_ASSERT(errorInfo);

            CCError *ret = new CCError();
            ret->autorelease();
            ret->init(errorInfo);
            return ret;
        } else {
            return NULL;
        }
    }

    bool CCError::init(cocos2d::__String *errorInfo) {
        mInfo = errorInfo->getCString();

        return true;
    }
}
