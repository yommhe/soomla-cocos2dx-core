/*
 Copyright (C) 2012-2015 Soomla Inc.

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

#include "CCSoomlaConfigBuilder.h"

using namespace soomla;

bool CCSoomlaConfigBuilder::init() {
    _rawConfig = new cocos2d::__Dictionary();
    return true;
}

CCSoomlaConfigBuilder *CCSoomlaConfigBuilder::create() {
    CCSoomlaConfigBuilder *instance = new CCSoomlaConfigBuilder();
    if (instance->init()) {
        instance->autorelease();
    }
    else {
        CC_SAFE_DELETE(instance);
    }
    return instance;
}

cocos2d::__Dictionary *CCSoomlaConfigBuilder::build() {
    return this->_rawConfig;
}