/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSFeatureStatusParameters.h"
@class CSCallForwardingStatus;

/**
 * The parameters for Enhanced Call Forwarding feature invocation.
 */
@interface CSEnhancedCallForwardingStatus : NSObject

 /**
  * Constructs an CSEnhancedCallForwardingStatus object from the specified parameters.
  * The object is initialized with the status of all three call forwarding 
  * conditions i.e On-Busy/On-NoReply/Unconditional forward.
  * @param status The feature status.
  * @param extension The owner extension this feature is targeted for.
  * @param busyCallForwardingStatus Busy call forwarding status.
  * @param noReplyCallForwardingStatus No reply call forwarding status
  * @param unconditionalCallForwardingStatus Unconditional call forwarding status.
  */

- (instancetype)initWithFeatureStatus:(CSFeatureStatus)status
                       ownerExtension:(NSString*)extension
             busyCallForwardingStatus:(CSCallForwardingStatus*)busyCallForwardingStatus
          noReplyCallForwardingStatus:(CSCallForwardingStatus*)noReplyCallForwardingStatus
    unconditionalCallForwardingStatus:(CSCallForwardingStatus*)unconditionalCallForwardingStatus;

/**
 * The feature's status.
 */

@property (nonatomic, readonly) CSFeatureStatus status;

/**
 * The owner extension this feature status is targeted for.
 *
 * Populated only if different from the local user's extension.
 */

@property (nonatomic, readonly) NSString *ownerExtension;

/**
 * The busy call forward parameter for Enhanced call forward.
 */

@property (nonatomic, readonly) CSCallForwardingStatus *busyCallForwardingStatus;

/**
 * The no reply call forward parameter for Enhanced call forward.
 */

@property (nonatomic, readonly) CSCallForwardingStatus *noReplyCallForwardingStatus;

/**
 * The unconditional call forward parameter for Enhanced call forward.
 */

@property (nonatomic, readonly) CSCallForwardingStatus *unconditionalCallForwardingStatus;

@end
