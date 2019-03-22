*This project is a part of The [SOOMLA](http://www.soom.la) Framework, which is a series of open source initiatives with a joint goal to help mobile game developers do more together. SOOMLA encourages better game design, economy modeling, social engagement, and faster development.*

soomla-cocos2dx-core
===============

When using the SOOMLA framework, you always start by initializing the core module:
```c++
    soomla::CCSoomla::initialize("customSecret");
```

This sets up the local on-device database used by SOOMLA.  The secret is used for encrypting the data, make sure to choose a good one.

This core library holds common features and utilities used by all other modules of the SOOMLA framework.
It includes:
* An encrypted key-value storage (SQLite based) for persisting data locally on devices.
* Utilities for JSON and __Dictionary manipulation.
* Utilities for Logging and encryption.
* Reward domain objects and events - used to grant your users rewards.

SOOMLA modules internally use these features, though we encourage you to use them for your own needs as well.  For example, use our key-value storage for custom game data for usage across game sessions.

You can start by using the more common features in core by including the `Cocos2dxCore.h` header.
````cpp
  #include "Cocos2dxCore.h"
````

## Download

#### From sources:
 - Clone this repository recursively: `git clone --recursive https://github.com/yommhe/soomla-cocos2dx-core.git`
 or, if you have repositories already cloned, fetch the submodules with this command:
    ```
    $ git submodule update --init --recursive
    ```

 - Run `./build_all` from project directory
 - Take created binaries from `build` directory and use it!

#### Topics:
- For some reason if you got something like this:
```
[javac] error: error reading {your project root}/cocos2d/extensions/soomla-cocos2dx-core/development/submodules/soomla-android-core/libs/square-otto-1.3.2.jar; error in opening zip file
```
You can download Square Otto directly from here:
[square-otto-1.3.2.jar](https://github.com/downloads/square/otto/square-otto-1.3.2.jar)

- You also need clone this into the `external` directory at the root of your Cocos2d-x framework.

	```
	$ git clone git@github.com:soomla/jansson.git external/jansson
	```

Our way of saying "Thanks !"
---

Other open-source projects that we use:

* [FBEncryptor](https://github.com/dev5tec/FBEncryptor)

Contribution
---
SOOMLA appreciates code contributions! You are more than welcome to extend the capabilities of SOOMLA.

Fork -> Clone -> Implement -> Add documentation -> Test -> Pull-Request.

IMPORTANT: If you would like to contribute, please follow our [Documentation Guidelines](https://github.com/soomla/cocos2dx-store/blob/master/documentation.md
). Clear, consistent comments will make our code easy to understand.

## SOOMLA, Elsewhere ...

+ [Framework Website](http://www.soom.la/)
+ [Knowledge Base](http://know.soom.la/)


<a href="https://www.facebook.com/pages/The-SOOMLA-Project/389643294427376"><img src="http://know.soom.la/img/tutorial_img/social/Facebook.png"></a><a href="https://twitter.com/Soomla"><img src="http://know.soom.la/img/tutorial_img/social/Twitter.png"></a><a href="https://plus.google.com/+SoomLa/posts"><img src="http://know.soom.la/img/tutorial_img/social/GoogleP.png"></a><a href ="https://www.youtube.com/channel/UCR1-D9GdSRRLD0fiEDkpeyg"><img src="http://know.soom.la/img/tutorial_img/social/Youtube.png"></a>

License
---
Apache License. Copyright (c) 2012-2014 SOOMLA. http://project.soom.la
+ http://opensource.org/licenses/Apache-2.0
