
#import "CoreBridge.h"
#import "NdkGlue.h"
#import "Reward.h"
#import "SoomlaEventHandling.h"
#import "CommonConsts.h"
#import "BadgeReward.h"
#import "RandomReward.h"
#import "SequenceReward.h"
#import "DomainHelper.h"
#import "RewardStorage.h"
#import "Schedule.h"
#import "KeyValueStorage.h"
#import "DomainFactory.h"
#import "Soomla.h"

@interface CoreBridge ()
@end

@implementation CoreBridge {

}

+ (id)sharedCoreBridge {
    static CoreBridge *sharedCoreBridge = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedCoreBridge = [self alloc];
    });
    return sharedCoreBridge;
}

+ (void)initialize {
    [super initialize];
    [self initGlue];
    [self initCreators];
}

- (id)init {
    self = [super init];
    if (self) {
        [SoomlaEventHandling observeAllEventsWithObserver:[NdkGlue sharedInstance]
                                                  withSelector:@selector(dispatchNdkCallback:)];
    }

    return self;
}

+ (void)initGlue {
    NdkGlue *ndkGlue = [NdkGlue sharedInstance];

    /* -= Call handlers =- */
    [ndkGlue registerCallHandlerForKey:@"CCSoomla::initialize" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *soomlaSecret = parameters[@"soomlaSecret"];
        [Soomla initializeWithSecret:soomlaSecret];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreBridge::getTimesGiven" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *rewardId = parameters[@"reward"];
        int res = [RewardStorage getTimesGivenForReward:rewardId];
        retParameters[@"return"] = @(res);
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreBridge::setRewardStatus" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *rewardId = parameters[@"reward"];
        bool give = [parameters[@"give"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [RewardStorage setStatus:give forReward:rewardId andNotify:notify];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreBridge::getLastSeqIdxGiven" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *rewardId = parameters[@"reward"];
        int res = [RewardStorage getLastSeqIdxGivenForSequenceReward:rewardId];
        retParameters[@"return"] = @(res);
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreBridge::setLastSeqIdxGiven" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *rewardId = parameters[@"reward"];
        int idx = [parameters[@"idx"] intValue];
        [RewardStorage setLastSeqIdxGiven:idx ForSequenceReward:rewardId];
    }];

    [ndkGlue registerCallHandlerForKey:@"CCCoreBridge::getValue" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *key = parameters[@"key"];
        NSString *res = [KeyValueStorage getValueForKey:key];
        if (res) {
            retParameters[@"return"] = res;
        }
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreBridge::setValue" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *key = parameters[@"key"];
        NSString *val = parameters[@"val"];
        [KeyValueStorage setValue:val forKey:key];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreBridge::deleteKeyValue" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *key = parameters[@"key"];
        [KeyValueStorage deleteValueForKey:key];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreBridge::purge" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        [KeyValueStorage purge];
    }];

    /* -= Callback handlers =- */
    [ndkGlue registerCallbackHandlerForKey:EVENT_REWARD_GIVEN withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"com.soomla.events.RewardGivenEvent";
        NSString *rewardId = (notification.userInfo)[DICT_ELEMENT_REWARD];
        parameters[@"reward"] = rewardId;
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_REWARD_TAKEN withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"com.soomla.events.RewardTakenEvent";
        NSString *rewardId = (notification.userInfo)[DICT_ELEMENT_REWARD];
        parameters[@"reward"] = rewardId;
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_CUSTOM withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"com.soomla.events.CustomEvent";
        NSDictionary* userInfo = [notification userInfo];
        NSString *name = [userInfo objectForKey:DICT_ELEMENT_NAME];
        NSDictionary* extraDict = [userInfo objectForKey:DICT_ELEMENT_EXTRA];
        if (extraDict) {
            extraDict = [NSDictionary dictionary];
        }
        parameters[@"name"] = name;
        parameters[@"extra"] = extraDict;
    }];

}

+ (void)initCreators {
    [[DomainHelper sharedDomainHelper] registerType:(NSString *)JSON_JSON_TYPE_BADGE
                                      withClassName:NSStringFromClass([BadgeReward class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[BadgeReward alloc] initWithDictionary:dict];
                                           }];
    [[DomainHelper sharedDomainHelper] registerType:(NSString *)JSON_JSON_TYPE_RANDOM
                                      withClassName:NSStringFromClass([RandomReward class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[RandomReward alloc] initWithDictionary:dict];
                                           }];
    [[DomainHelper sharedDomainHelper] registerType:(NSString *)JSON_JSON_TYPE_SEQUENCE
                                      withClassName:NSStringFromClass([SequenceReward class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[SequenceReward alloc] initWithDictionary:dict];
                                           }];
    [[DomainHelper sharedDomainHelper] registerType:(NSString *)JSON_JSON_TYPE_SCHEDULE
                                      withClassName:NSStringFromClass([Schedule class])
                                           andBlock:^id(NSDictionary *dict) {
                                               return [[Schedule alloc] initWithDictionary:dict];
                                           }];
    [[DomainHelper sharedDomainHelper] registerType:(NSString *) JSON_JSON_TYPE_DATE_TIME_RANGE
                                      withClassName:NSStringFromClass([DateTimeRange class])];
}

@end
