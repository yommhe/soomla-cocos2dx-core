//
// Created by Fedor Shubin on 5/21/13.
//


#include "CCError.h"

USING_NS_CC;

namespace soomla {
    #define CANNOT_EXTRACT "Cannot extract error data"
    #define JSON_ERROR_INFO "errorInfo"

    #define TAG "CCError"

    CCError *CCError::createWithObject(cocos2d::CCObject *obj) {
        if (obj == NULL) {
            return NULL;
        }

        CCDictionary *dict = static_cast<CCDictionary *>(obj);
        if (dict->objectForKey(JSON_ERROR_INFO) == NULL) {
            return NULL;
        }

        std::string errorInfo;
        CCString *errorInfoStr = dynamic_cast<CCString *>(dict->objectForKey(JSON_ERROR_INFO));
        if (errorInfoStr) {
            errorInfo = errorInfoStr->getCString();
        } else {
            errorInfo = CANNOT_EXTRACT;
        }

        CCError *ret = new CCError();
        if (ret->init(errorInfo)) {
            ret->autorelease();
        } else {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }

    bool CCError::init(std::string &errorInfo) {
        mInfo = errorInfo;

        return true;
    }
}
