/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCallPickupFeatureRinger.h"
#import "CSCapability.h"
#import "CSFeatureInvocationParameters.h"
#import "CSForwardingOverride.h"
#import "CSTeamButtonIncomingCall.h"

/**
 * Represents team button feature. A monitoring station can perform speed dial
 * or pick up an incoming call ringing on the monitoring extension. This object
 * is provided with notification whenever the status changes.
 */
@interface CSTeamButton : NSObject

/**
 * Returns the the label of team button.
 */
@property (nonatomic, readonly) NSString *label;

/**
 * Returns the extension of monitored station.
 */
@property (nonatomic, readonly) NSString *ownerExtension;

/**
 * Specifies whether the forwarding destination of monitored station
 * will be ignored by Team Button speed dial invocation if any of
 * forwarding features are enabled on the monitored station.
 * If set to ask, the client can override the forwarding destination
 * using the override argument of {@link CSTeamButton::speedDialWithOverride:completionHandler:}
 * @see CSTeamButton::forwardingEnabled
 * @see CSTeamButton::forwardingDestination
 */
@property (nonatomic, readonly) CSForwardingOverride forwardingOverride;

/**
 * Returns the rerouting destination of the monitored station.
 * @see CSTeamButton::forwardingEnabled
 */
@property (nonatomic, readonly) NSString *forwardingDestination;

/**
 * Shows whether the monitored station has forwarding enabled.
 * Rerouting is considered active if Send All Calls, Call Forward
 * or Enhanced Call Forward have active forwarding.
 * @see CSTeamButton::forwardingDestination
 */
@property (nonatomic, readonly, getter=isForwardingEnabled) BOOL forwardingEnabled;

/**
 * Indicates whether to pickup the currently selected call in the screen
 * after going off hook when the Team Pickup screen is displayed.
 */
@property (nonatomic, readonly, getter=isPickupByGoingOffHookEnabled) BOOL pickupByGoingOffHookEnabled;

/**
 * Indicates whether the Team Button audible alert should not be played
 * if the monitoring station has at least one call appearance active.
 */
@property (nonatomic, readonly, getter=isSilentIfActive) BOOL silentIfActive;

/**
 * Indicates whether the monitored station has an active call.
 */
@property (nonatomic, readonly, getter=isBusy) BOOL busy;

/**
 * Specifies the delay interval in seconds the team button alert should be delayed by
 * if the {@link CSTeamButton::pickupRingType} is set to DELAYED.
 * @deprecated Please use {@link CSTeamButtonIncomingCall::delayInterval} instead.
 */
@property (nonatomic, readonly) NSTimeInterval delayInterval DEPRECATED_MSG_ATTRIBUTE("Use CSTeamButtonIncomingCall.delayInterval instead");

/**
 * Returns the team button call pickup ring types if configured.
 * The possible values are with the according CM setting values:
 * Off - No ringing - 'n'
 * On - Continuous ringing - 'r'
 * Delayed - Delayed ringing - 'd'
 * Abbreviated - Abbreviated (single) ringing - 'a'
 * InterCom - Intercom ringing - 'i'
 * Delayed ring type means the team button alert should be delayed by
 * delay time specified {@link CSTeamButton::delayInterval}.
 * @see CSTeamButton::CSRingType
 */
@property (nonatomic, readonly) CSRingType pickupRingType;

/**
 * List of the incoming calls alerting on monitored extension.
 * @see CSIncomingTeamButtonCall
 */
@property (nonatomic, readonly) NSArray<CSTeamButtonIncomingCall *> *teamButtonIncomingCalls;

/**
 * A capability object indicating whether the user can pick up the Team button call.
 * Allowed when the monitoring station has at least one incoming ringing call.
 * Mutual exclusive with {@link CSTeamButton::speedDialCapability}.
 */
@property (readonly) CSCapability *pickupCapability;

/**
 * A capability object indicating whether the user can initiate speed dial using the Team button.
 * Allowed when the monitoring station has no incoming ringing calls.
 * Mutual exclusive with {@link CSTeamButton::pickupCapability}.
 */
@property (readonly) CSCapability *speedDialCapability;

/**
 * Initiates team button speed dial.
 *
 * @param overrideDestination Specifies whether the forwarding destination of monitored station will be overridden depending on the  override policy.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 * @see CSTeamButton::forwardingOverride
 */
- (void)speedDialWithOverride: (BOOL)overrideDestination completionHandler:(void (^)(NSError *error))handler;

/**
 * Updates the Team Button with personalized label given by user.
 *
 * @param featureLabel The personalized label to be set.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setPersonalizedLabel:(NSString *)featureLabel
           completionHandler:(void (^)(NSError *error))handler;

@end
