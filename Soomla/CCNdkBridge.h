//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCNdkBridge_H_
#define __CCNdkBridge_H_

#include "cocos2d.h"
#include "CCError.h"

namespace soomla {
	/** \class CCNdkBridge
		\brief The bridge between the application and the Cocos2d-x code.

		This class receives calls from the native application and sends them 
		over to the Cocos2d-x code, and vice versa.
	 */
    class CCNdkBridge {
    public:
		/**
		   Call a native application function.
		   \param params A CCDictionary containing the name of the function to call and parameters to pass to it.
		   \param pError A CCError that can be used to tell if there was an error.
		   \return The return value of the called function as a cocos2d::CCObject.
		 */
        static cocos2d::CCObject *callNative(cocos2d::CCDictionary *params, CCError **pError);
    };
};


#endif //__CCNdkBridge_H_
