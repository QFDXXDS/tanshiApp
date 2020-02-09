/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Configuration information for Outbound Subscription.
 */
@interface CSOutboundSubscriptionConfiguration : NSObject

/**
 * A Boolean value indicating whether all subscriptions are disabled.
 *
 */
@property (nonatomic) BOOL allSubscriptionsDisabled;

/**
 * A Boolean value indicating whether CCS profile subscription is enabled.
 *
 */
@property (nonatomic, getter=isCCSProfileSubscriptionEnabled) BOOL CCSProfileSubscriptionEnabled;

/**
 * A Boolean value indicating whether registration info subscription is enabled.
 *
 */
@property (nonatomic, getter=isRegistrationInfoSubscriptionEnabled) BOOL registrationInfoSubscriptionEnabled;

/**
 * A Boolean value indicating whether dialog info subscription is enabled.
 *
 */
@property (nonatomic, getter=isDialogInfoSubscriptionEnabled) BOOL dialogInfoSubscriptionEnabled;

/**
 * A Boolean value indicating whether feature status subscription is enabled.
 *
 */
@property (nonatomic, getter=isFeatureStatusSubscriptionEnabled) BOOL featureStatusSubscriptionEnabled;

/**
 * A Boolean value indicating whether message summary subscription is enabled.
 *
 */
@property (nonatomic, getter=isMessageSummarySubscriptionEnabled) BOOL messageSummarySubscriptionEnabled;

/**
 * A Boolean value indicating whether call centre elite subscription is enabled.
 *
 */
@property (nonatomic, getter=isCCEliteSubscriptionEnabled) BOOL CCEliteSubscriptionEnabled;

@end
