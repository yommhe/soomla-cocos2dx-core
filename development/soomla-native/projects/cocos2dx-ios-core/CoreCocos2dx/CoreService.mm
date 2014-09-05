//
// Created by Fedor Shubin on 6/12/14.
//

#import "CoreService.h"
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

@interface CoreService ()
@end

@implementation CoreService {

}

+ (id)sharedCoreService {
    static CoreService *sharedCoreService = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedCoreService = [self alloc];
    });
    return sharedCoreService;
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
    [ndkGlue registerCallHandlerForKey:@"CCCoreService::init" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        [[CoreService sharedCoreService] init];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreService::getTimesGiven" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSDictionary *rewardDict = parameters[@"reward"];
        int res = [RewardStorage getTimesGivenForReward:[Reward fromDictionary:rewardDict]];
        retParameters[@"return"] = @(res);
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreService::setRewardStatus" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSDictionary *rewardDict = parameters[@"reward"];
        bool give = [parameters[@"give"] boolValue];
        bool notify = [parameters[@"notify"] boolValue];
        [RewardStorage setStatus:give forReward:[Reward fromDictionary:rewardDict] andNotify:notify];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreService::getLastSeqIdxGiven" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSDictionary *rewardDict = parameters[@"reward"];
        int res = [RewardStorage getLastSeqIdxGivenForReward:(SequenceReward *) [Reward fromDictionary:rewardDict]];
        retParameters[@"return"] = @(res);
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreService::setLastSeqIdxGiven" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSDictionary *rewardDict = parameters[@"reward"];
        int idx = [parameters[@"idx"] intValue];
        [RewardStorage setLastSeqIdxGiven:idx ForReward:(SequenceReward *) [Reward fromDictionary:rewardDict]];
    }];
    
    [ndkGlue registerCallHandlerForKey:@"CCCoreService::getValue" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *key = parameters[@"key"];
        NSString *res = [KeyValueStorage getValueForKey:key];
        retParameters[@"return"] = res;
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreService::setValue" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *key = parameters[@"key"];
        NSString *val = parameters[@"val"];
        [KeyValueStorage setValue:val forKey:key];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreService::deleteKeyValue" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        NSString *key = parameters[@"key"];
        [KeyValueStorage deleteValueForKey:key];
    }];
    [ndkGlue registerCallHandlerForKey:@"CCCoreService::purge" withBlock:^(NSDictionary *parameters, NSMutableDictionary *retParameters) {
        [KeyValueStorage purge];
    }];

    /* -= Callback handlers =- */
    [ndkGlue registerCallbackHandlerForKey:EVENT_REWARD_GIVEN withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"com.soomla.events.RewardGivenEvent";
        Reward *reward = (notification.userInfo)[DICT_ELEMENT_REWARD];
        parameters[@"reward"] = [[DomainHelper sharedDomainHelper] domainToDict:reward];
    }];
    [ndkGlue registerCallbackHandlerForKey:EVENT_REWARD_TAKEN withBlock:^(NSNotification *notification, NSMutableDictionary *parameters) {
        parameters[@"method"] = @"com.soomla.events.RewardTakenEvent";
        Reward *reward = (notification.userInfo)[DICT_ELEMENT_REWARD];
        parameters[@"reward"] = [[DomainHelper sharedDomainHelper] domainToDict:reward];
    }];

}

+ (void)initCreators {
    [[DomainHelper sharedDomainHelper] registerType:(NSString *) JSON_JSON_TYPE_BADGE
                                      withClassName:NSStringFromClass([BadgeReward class])];
    [[DomainHelper sharedDomainHelper] registerType:(NSString *) JSON_JSON_TYPE_RANDOM
                                      withClassName:NSStringFromClass([RandomReward class])];
    [[DomainHelper sharedDomainHelper] registerType:(NSString *) JSON_JSON_TYPE_SEQUENCE
                                      withClassName:NSStringFromClass([SequenceReward class])];
    [[DomainHelper sharedDomainHelper] registerType:(NSString *) JSON_JSON_TYPE_SCHEDULE
                                      withClassName:NSStringFromClass([Schedule class])];
    [[DomainHelper sharedDomainHelper] registerType:(NSString *) JSON_JSON_TYPE_DATE_TIME_RANGE
                                      withClassName:NSStringFromClass([DateTimeRange class])];
}

@end