/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, CSCallForwardingCause) {
    /** 
     * Immediate cause - the current call was forwarded due the configured 
     * call forwarding feature (on target user SIP softphone/hardphone) or forwarded by target user itself.  
     */
    CSCallForwardingCauseImmediate = 0,

    /** 
     * Busy cause - the current call was forwarded due the busy status of user who forwarded the call. 
     */
    CSCallForwardingCauseBusy,
    
    /** 
     * NoReply cause - the current call was forwarded due the user who forwarded the call does not reply this call
     * or user who forwarded the call is unavailable. 
     */
    CSCallForwardingCauseNoReply,

    /** 
     * CallDeflection cause - the current call was forwarded because it was declined by the previous recipient.
     */
    CSCallForwardingCauseCallDeflection,

    /** 
     * Hunting cause - support CM HUNT feature.
     */
    CSCallForwardingCauseHunting,

    /** 
     * Normal cause - normal redirection of this call.
     */
    CSCallForwardingCauseNormal
};

/**
 * Interface representing forwarding information of an incoming call.
 */
@interface CSCallForwardingInformation : NSObject

/**
 * Display name of the user who forwarded the call to the local user
 */
@property (nonatomic, readonly) NSString *forwarderDisplayName;

/**
 * The forward cause of incoming call.
 */
@property (nonatomic, readonly) CSCallForwardingCause cause;

@end
