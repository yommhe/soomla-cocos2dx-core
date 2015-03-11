/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "CCNativeCoreBridge.h"
#include "CCNdkBridge.h"
#include "CCSoomlaUtils.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <string>

#define CLASS_NAME "com/soomla/cocos2dx/common/CoreBridgeBinder"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "CCCoreBridgeBinderIos.h"

#endif

namespace soomla {
    
    USING_NS_CC;
    
    #define TAG "SOOMLA NativeCoreBridge"
    
    bool CCNativeCoreBridge::init() {
        bool result = CCCoreBridge::init();
        
        if (!result) {
            return result;
        }
        
        this->bindNative();
        
        return true;
    }

    int CCNativeCoreBridge::getTimesGiven(CCReward *reward) {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCCoreBridge::getTimesGiven"), "method");
        params->setObject(reward->getId(), "reward");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return -1;
        }
        
        if (retParams == NULL) {
            return -1;
        }
        
        __Integer *retValue = (__Integer *) retParams->objectForKey("return");
        if (!retValue) {
            return -1;
        }
        
        return retValue->getValue();
    }

    void CCNativeCoreBridge::setRewardStatus(CCReward *reward, bool give, bool notify) {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCCoreBridge::setRewardStatus"), "method");
        params->setObject(reward->getId(), "reward");
        params->setObject(__Bool::create(give), "give");
        params->setObject(__Bool::create(notify), "notify");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    int CCNativeCoreBridge::getLastSeqIdxGiven(CCSequenceReward *sequenceReward) {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCCoreBridge::getLastSeqIdxGiven"), "method");
        params->setObject(sequenceReward->getId(), "reward");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return -1;
        }
        
        if (retParams == NULL) {
            return -1;
        }
        
        __Integer *retValue = (__Integer *) retParams->objectForKey("return");
        if (!retValue) {
            return -1;
        }
        
        return retValue->getValue();
    }

    void CCNativeCoreBridge::setLastSeqIdxGiven(CCSequenceReward *sequenceReward, unsigned int idx) {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCCoreBridge::setLastSeqIdxGiven"), "method");
        params->setObject(sequenceReward->getId(), "reward");
        params->setObject(__Integer::create(idx), "idx");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    const char *CCNativeCoreBridge::kvStorageGetValue(const char *key) const {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCCoreBridge::getValue"), "method");
        params->setObject(__String::create(key), "key");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
            return NULL;
        }
        
        if (retParams == NULL) {
            return NULL;
        }
        
        __String *retValue = (__String *) retParams->objectForKey("return");
        if (!retValue) {
            return NULL;
        }
        
        return retValue->getCString();
    }

    void CCNativeCoreBridge::kvStorageSetValue(const char *key, const char *val) {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCCoreBridge::setValue"), "method");
        params->setObject(__String::create(key), "key");
        params->setObject(__String::create(val), "val");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    void CCNativeCoreBridge::kvStorageDeleteKeyValue(const char *key) {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCCoreBridge::deleteKeyValue"), "method");
        params->setObject(__String::create(key), "key");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }

    void CCNativeCoreBridge::kvStoragePurge() {
        CCError *error = NULL;
        
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCCoreBridge::purge"), "method");
        CCNdkBridge::callNative (params, &error);
        
        if (error) {
            CCSoomlaUtils::logException(TAG, error);
            CC_ASSERT(false);
        }
    }
    
    void CCNativeCoreBridge::bindNative() {
        CCSoomlaUtils::logDebug(TAG, "Binding to native platform bridge...");
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo minfo;
        
        bool exists = JniHelper::getStaticMethodInfo(minfo, CLASS_NAME, "bind", "()V");
        
        if (exists)
        {
            minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        }
        else {
            CCSoomlaUtils::logError(TAG, "Unable to bind native bridge on Android");
        }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        soomla::CCCoreBridgeBinderIos::bind();
#endif
    }
}