/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSAutodial.h"
#import "CSBusyIndicator.h"
#import "CSCapability.h"
#import "CSFeatureInvocationParameters.h"
#import "CSFeatureParameters.h"
#import "CSFeatureStatusParameters.h"
#import "CSEnhancedCallForwardingStatus.h"
#import "CSFeatureType.h"
#import "CSTeamButton.h"

@protocol CSCallFeatureServiceDelegate;
@class CSCallPickupAlertStatus;
@class CSCall;

/**
 * The CSCallFeatureService object is accessible from the CSUser object, 
 * providing access to additional business communication features.
 * The CSCallFeatureService object provides a set of APIs that allow
 * application developers to implement advanced SIP telephony features.
 *
 * In general, administered features can be invoked depending upon the 
 * current state of the system.
 *
 * The client application is notified about status updates on features 
 * reported by the call feature service through handlers that the 
 * application has registered on the CSCallFeatureService object. 
 * These updates may be the result of local operations on the 
 * CSCallFeatureService object as well as remote changes initiated by either 
 * the service/server or other end users.
 */
@interface CSCallFeatureService : NSObject

/**
 * The delegate responsible for handling call feature events.
 */
@property (nonatomic, weak) id<CSCallFeatureServiceDelegate> delegate;

/**
 * Gets all the calls features available to the user.
 *
 * @return An NSArray of CSFeatureStatusParameters objects describing the
 *         available features.
 */
- (NSArray *)availableFeatures;

/**
 * Gets all the busy indicators available to the user.
 *
 * @return An NSArray of CSBusyIndicator objects.
 *
 */
- (NSArray *)availableBusyIndicators;

/**
 * Gets all the autodials available to the user.
 *
 * @return An NSArray of CSAutodial objects.
 *
 */
- (NSArray *)availableAutodials;

/**
 * Gets a list of configured hunt-group-busy-position feature buttons for the user.
 *
 * @return An NSArray of CSFeatureStatusParameters objects describing the 
 *          available hunt-group-busy-position features.
 *
 */
- (NSArray<CSFeatureStatusParameters *> *)availableHuntGroupBusyPositionFeatures;

/**
 * Sends out a request in the network to update a configured Autodial button
 *
 * @param updatedAutodial User modified autodial button
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)updateAutodial:(CSAutodial *)updatedAutodial completionHandler:(void (^)(NSError *error))handler;

/**
 * Returns a Boolean value indicating whether the specified feature is available.
 *
 * @param featureType The feature to query.
 */
- (BOOL)isFeatureAvailable:(CSFeatureType)featureType;

/**
 * Returns a capability object indicating whether the specified feature is
 * available.
 *
 * @param featureType The feature to query.
 */
- (CSCapability *)capabilityForFeature:(CSFeatureType)featureType;

/**
* Returns feature status parameters for a specified extension and feature type.
* If feature type is not configured for specified extension, this API will return
* empty object of type FeatureStatusParameters with CSFeatureStatusUndefined status in it.
* Other status are CSFeatureStatusOn/CSFeatureStatusOff/CSFeatureStatusAlerting.
*
* @param featureType The feature to query.
* @param ownerExtension Extension number
*
* This method is deprecated please use \a featureStatusParametersForFeature: .
*/
-(CSFeatureStatusParameters *)featureStatusParametersForType:(CSFeatureType)featureType withExtension:(NSString*)ownerExtension DEPRECATED_MSG_ATTRIBUTE("Use featureStatusParametersForFeature: instead");

/**
 * Returns feature status parameters for a specified CSFeatureParameters object.
 * If feature type is not configured for specified extension, this API will return
 * empty object of type FeatureStatusParameters with CSFeatureStatusUndefined status in it.
 * Other status are CSFeatureStatusOn/CSFeatureStatusOff/CSFeatureStatusAlerting.
 *
 * @param featureParams The CSFeatureParameters object to query feature status.
 */
-(CSFeatureStatusParameters *)featureStatusParametersForFeature:(CSFeatureParameters *)featureParams;

/**
 * Invokes a feature that takes no parameters.
 *
 * @param featureType The feature to invoke.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)invokeFeature:(CSFeatureType)featureType completionHandler:(void (^)(NSError *error))handler;

/**
 * Invokes a feature.
 *
 * @code
 * Feature                                  Parameters
 * ---------------------------------------------------------------------------------
 * CSFeatureTypeSendAllCalls                [action] [owner-extension]
 * CSFeatureTypeForwardAllCalls             [action] [destination] [owner-extension]
 * CSFeatureTypeForwardBusyNoAnswerCalls    [action] [destination] [owner-extension]
 * CSFeatureTypeExclusion                   [action]
 * CSFeatureTypeEC500                       [action]
 * CSFeatureTypeExtendCall
 * CSFeatureTypeCallPark
 * CSFeatureTypeCallUnpark                  [extension]
 * CSFeatureTypeAutoCallback                [action]
 * CSFeatureTypeWhisperPage                 [extension]
 * CSFeatureTypeGroupCallPickup
 * CSFeatureTypeExtendedGroupCallPickup     [pickup-number]
 * CSFeatureTypeCallingPartyNumberBlock     [destination]
 * CSFeatureTypeCallingPartyNumberUnblock   [destination]
 * CSFeatureTypeOneTouchRecording           [action] [extension]
 * CSFeatureTypeDirectedCallPickup          [extension]
 * CSFeatureTypePriorityCall                [destination]
 * CSFeatureTypeHuntGroupBusyPosition       [action] [hunt-group number]
 * @endcode
 *
 * @param featureType The feature to invoke.
 * @param featureParameters The parameters supporting this feature invocation.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)invokeFeature:(CSFeatureType)featureType parameters:(CSFeatureInvocationParameters *)featureParameters completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the send all calls feature is
 * available for the user's local extension.
 */
@property (readonly) CSCapability *sendAllCallsCapability;

/**
 * A capability object indicating whether the send all calls feature is
 * available for the specified extention.
 *
 * @param extension The extension for which to query the availability of the
 *        feature.
 */
- (CSCapability *)sendAllCallsCapabilityForExtension:(NSString *)extension;

/**
 * A Boolean value indicating whether the send all calls feature is enabled for
 * the user's local extension.
 */
@property (readonly, getter=isSendAllCallsEnabled) BOOL sendAllCallsEnabled;

/**
 * Returns a Boolean value indicating whether the send all calls feature is
 * enabled for the specified extension.
 *
 * @param extension The extension for which to query the status of the feature.
 */
- (BOOL)isSendAllCallsEnabledForExtension:(NSString *)extension;

/**
 * Enables or disables sending all calls to coverage.
 *
 * @param enabled If @c YES send all calls is enabled. If @c NO send all calls
 *        is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setSendAllCallsEnabled:(BOOL)enabled completionHandler:(void (^)(NSError *error))handler;

/**
 * Enables or disables sending all calls to coverage for another extension.
 *
 * @param enabled If @c YES send all calls is enabled. If @c NO send all calls
 *        is disabled.
 * @param extension The extension to enable or disable send all calls for.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setSendAllCallsEnabled:(BOOL)enabled forExtension:(NSString *)extension completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the call forwarding feature is
 * available for the user's local extension.
 */
@property (readonly) CSCapability *callForwardingCapability;

/**
 * A Boolean value indicating whether the call forwarding feature is enabled for
 * the user's local extension.
 */
@property (readonly, getter=isCallForwardingEnabled) BOOL callForwardingEnabled;

/**
 * The call forwarding destination for the user's local extension, if any.
 */
@property (readonly) NSString *callForwardingDestination;

/**
 * A capability object indicating whether the call forwarding feature is
 * available for the specified extension.
 *
 * @param extension The extension for which to query the availability of the
 *        feature.
 */
- (CSCapability *)callForwardingCapabilityForExtension:(NSString *)extension;

/**
 * Returns a Boolean value indicating whether the call forwarding feature is
 * enabled for the specified extension.
 *
 * @param extension The extension for which to query the status of the feature.
 */
- (BOOL)isCallForwardingEnabledForExtension:(NSString *)extension;

/**
 * Returns the call forwarding destination for the specified extension, if any.
 *
 * @param extension The extension for which to query the forwarding destination.
 */
- (NSString *)callForwardingDestinationForExtension:(NSString *)extension;

/**
 * Enables or disables forwarding of all calls to the specified destination.
 *
 * @param enabled If @c YES forwarding is enabled. If @c NO forwarding is
 *        disabled.
 * @param destination The destination number to forward calls to.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setCallForwardingEnabled:(BOOL)enabled destination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * Enables or disables forwarding of all calls to the specified destination for
 * another extension.
 *
 * @param enabled If @c YES forwarding is enabled. If @c NO forwarding is
 *        disabled.
 * @param extension The extension to enable or disable forwarding for.
 * @param destination The destination number to forward calls to.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setCallForwardingEnabled:(BOOL)enabled forExtension:(NSString *)extension destination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the call forwarding busy-no-answer
 * feature is available for the user's local extension.
 */
@property (readonly) CSCapability *callForwardingBusyNoAnswerCapability;

/**
 * A Boolean value indicating whether the call forwarding busy-no-answer feature
 * is enabled for the user's local extension.
 */
@property (readonly, getter=isCallForwardingBusyNoAnswerEnabled) BOOL callForwardingBusyNoAnswerEnabled;

/**
 * The call forwarding busy-no-answer destination for the user's local
 * extension, if any.
 */
@property (readonly) NSString *callForwardingBusyNoAnswerDestination;

/**
 * A capability object indicating whether the call forwarding busy-no-answer
 * feature is available for the specified extension.
 *
 * @param extension The extension for which to query the availability of the
 *        feature.
 */
- (CSCapability *)callForwardingBusyNoAnswerCapabilityForExtension:(NSString *)extension;

/**
 * Returns a Boolean value indicating whether the call forwarding busy-no-answer
 * feature is enabled for the specified extension.
 *
 * @param extension The extension for which to query the status of the feature.
 */
- (BOOL)isCallForwardingBusyNoAnswerEnabledForExtension:(NSString *)extension;

/**
 * Returns the call forwarding busy-no-answer destination for the specified
 * extension, if any.
 *
 * @param extension The extension for which to query the forwarding destination.
 */
- (NSString *)callForwardingBusyNoAnswerDestinationForExtension:(NSString *)extension;

/**
 * Enables or disables forwarding of calls that receive a busy signal or are not
 * answered to the specified destination.
 *
 * @param enabled If @c YES forwarding is enabled. If @c NO forwarding is
 *        disabled.
 * @param destination The destination number to forward calls to.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setCallForwardingBusyNoAnswerEnabled:(BOOL)enabled destination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * Enables or disables forwarding of calls that receive a busy signal or are not
 * answered to the specified destination for another extension.
 *
 * @param enabled If @c YES forwarding is enabled. If @c NO forwarding is
 *        disabled.
 * @param extension The extension to update call forwarding settings for.
 * @param destination The destination number to forward calls to.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setCallForwardingBusyNoAnswerEnabled:(BOOL)enabled forExtension:(NSString *)extension destination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the Enhanced Call Forwarding feature
 * is available for the user's local extension.
 */
@property (readonly) CSCapability *enhancedCallForwardingCapability;

/**
 * A capability object indicating whether the Enhanced Call Forwarding feature
 * is available for the specified extension.
 *
 * @param extension The extension for which to query the availability of the
 *        feature.
 */
- (CSCapability *)enhancedCallForwardingCapabilityForExtension:(NSString *)extension;

/**
 * The Enhanced Call Forwarding status for the user's local extension, if any.
 */
@property (nonatomic, readonly) CSEnhancedCallForwardingStatus *enhancedCallForwardingStatus;

/**
 * Returns the Enhanced Call Forwarding status for the specified extension.
 *
 * @return A CSEnhancedCallForwardingStatus object describing the busy, no
 *         reply, and unconditional call forwarding settings.
 */
- (CSEnhancedCallForwardingStatus *)enhancedCallForwardingStatusForExtension:(NSString *)extension;

/**
 * Sets the Enhanced Call Forwarding status for the user's local extension.
 *
 * @param enhancedCallForwardingStatus The new enhanced call forwarding status,
 *        specifying the busy, no reply, and unconditional call forwarding
 *        settings.
 *        For IP Office, the same destination number should be provided
 *        for call forward busy and no reply.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setEnhancedCallForwardingStatus:(CSEnhancedCallForwardingStatus *)enhancedCallForwardingStatus completionHandler:(void (^)(NSError *error))handler;

/**
 * Sets the Enhanced Call Forwarding status for another extension.
 *
 * @param enhancedCallForwardingStatus The new enhanced call forwarding status,
 *        specifying the busy, no reply, and unconditional call forwarding
 *        settings.
 *        For IP Office, the same destination number should be provided
 *        for call forward busy and no reply.
 * @param extension The extension to update call forwarding settings for.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setEnhancedCallForwardingStatus:(CSEnhancedCallForwardingStatus *)enhancedCallForwardingStatus forExtension:(NSString *)extension completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the exclusion feature is available.
 */
@property (readonly) CSCapability *exclusionCapability;

/**
 * Enables or disables exclusion for the active call.
 *
 * Exclusion prevents any other users from bridging onto the call, and drops any
 * other users who are already bridged onto the call.
 *
 * @param enabled If @c YES exclusion is enabled. If @c NO exclusion is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setExclusionEnabled:(BOOL)enabled completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the EC500 feature is available.
 */
@property (readonly) CSCapability *EC500Capability;

/**
 * A Boolean value indicating whether the EC500 feature is enabled.
 */
@property (readonly, getter=isEC500Enabled) BOOL EC500Enabled;

/**
 * Enables or disables EC500.
 *
 * @param enabled If @c YES EC500 is enabled. If @c NO EC500 is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setEC500Enabled:(BOOL)enabled completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the extend call feature is available.
 */
@property (readonly) CSCapability *extendCallCapability;

/**
 * Extends the active call to the off-pbx destinations configured for the user's
 * extension, namely EC500.
 *
 * An invocation of @c extendCallWithCompletionHandler: is not considered
 * successful until the call has been answered on one of the user's off-pbx
 * destinations. Until this occurs @c cancelExtendCallWithCompletionHandler: may
 * be used to cancel the pending extension of the active call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 *
 * @see cancelExtendCallWithCompletionHandler:
 */
- (void)extendCallWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Cancels a pending extension of the active call to the off-pbx destinations
 * configured for the user's extension.
 *
 * An invocation of @c extendCallWithCompletionHandler: is not considered
 * successful until the call has been answered on one of the user's off-pbx
 * destinations. Until this occurs @c cancelExtendCallWithCompletionHandler: may
 * be used to cancel the pending extension of the active call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 *
 * @see extendCallWithCompletionHandler:
 */
- (void)cancelExtendCallWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the call park feature is available.
 */
@property (readonly) CSCapability *parkCallCapability;

/**
 * Parks the active call.
 *
 * A parked call may later be unparked from another extension.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)parkCallWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the call unpark feature is available.
 */
@property (readonly) CSCapability *unparkCallCapability;

/**
 * Unparks a call previously parked at the user's extension.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)unparkCallWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Unparks a call previously parked at the specified extension.
 *
 * @param extension The extension from which to retrieve the parked call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)unparkCallAtExtension:(NSString *)extension completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the auto callback feature is
 * available.
 */
@property (readonly) CSCapability *autoCallbackCapability;

/**
 * A Boolean value indicating whether the auto callback feature is enabled.
 */
@property (readonly, getter=isAutoCallbackEnabled) BOOL autoCallbackEnabled;

/**
 * Enables an automatic callback for the last call if it received a busy signal
 * or was unanswered.
 *
 * When the station becomes able to receive a call the user who invoked this
 * feature will be called back automatically.
 *
 * @param enabled If @c YES automatic callback is enabled. If @c NO automatic
 *        callback is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setAutoCallbackEnabled:(BOOL)enabled completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the whisper page feature is available.
 */
@property (readonly) CSCapability *whisperPageCapability;

/**
 * Starts a whisper page to another user that is on an active call.
 *
 * @param extension The extension to start a whisper page to.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)whisperPageToExtension:(NSString *)extension completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the directed call pickup feature is
 * available.
 */
@property (readonly) CSCapability *pickupCallAtExtensionCapability;

/**
 * Picks up a call ringing at the specified extension (directed call pickup).
 *
 * @param extension The extension to pick up the call from.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)pickupCallAtExtension:(NSString *)extension completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the group call pickup feature is
 * available.
 */
@property (readonly) CSCapability *pickupGroupCallCapability;

/**
 * Picks up a call for the user's pickup group (group call pickup).
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)pickupGroupCallWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the extended group call pickup feature
 * is available.
 */
@property (readonly) CSCapability *pickupCallForGroupCapability;

/**
 * Picks up a call for the specified pickup group (extended group call pickup).
 *
 * @param groupNumber The group number to pick up the call from.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)pickupCallForGroup:(NSInteger)groupNumber completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the block calling party number feature
 * is available.
 */
@property (readonly) CSCapability *blockCallingPartyNumberCapability;

/**
 * Starts a call to the specified destination with the user's calling party
 * number information blocked if the call is made over a trunk.
 *
 * @param destination The destination to call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)blockCallingPartyNumberToDestination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the unblock calling party number
 * feature is available.
 */
@property (readonly) CSCapability *unblockCallingPartyNumberCapability;

/**
 * Starts a call to the specified destination with the user's calling party
 * number information unblocked if it would normally be blocked.
 *
 * @param destination The destination to call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)unblockCallingPartyNumberToDestination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the priority call feature is
 * available.
 */
@property (readonly) CSCapability *priorityCallCapability;

/**
 * List of team buttons assigned to the station.
 * This list represents those addresses/endpoints/users participated in this leg of the call and does not
 * represent the union of all users who participated in this call. The local user may
 * have conversed with those remoteParticipants listed in callEvents records.
 *
 * @see CSCallFeatureService::didChangeTeamButtons:
 */
@property (nonatomic, readonly) NSArray<CSTeamButton *> *teamButtons;

/**
 * Starts a priority call to the specified destination.
 *
 * Priority calls have distinct alerting and typically do not go to coverage.
 *
 * @param destination The destination to call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)startPriorityCallToDestination:(NSString *)destination completionHandler:(void (^)(NSError *error))handler;

/**
 * Completes call preemption after user acknowledges the continuous preemption tone.
 *
 * Call preemption occurs when a precedence call is sent to a preemptable endpoint
 * that is busy with a call of lower precedence and has no idle appearances.
 * This causes the lower precedence call to be preempted, regardless of whether
 * the lower precedence call and the new higher precedence call are of the same media type.
 * When preemption occurs, the active busy user receive a continuous preemption tone until user
 * acknowledges the preemption by invoking complete preemption method and the other party receives
 * a preemption tone for a minimum of 3 seconds.
 * After acknowledging the preemption, the extension to which the precedence call is directed will
 * be provided with precedence ringing and the calling party will receive an audible ring-back
 * precedence tone.
 *
 * Application must start playing preemption tone upon receipt of event ::CSCallDelegate::call:didPreempt:isPreemptionCompletionRequiredByClient:
 * and stop preemption tone before calling completeCallPreemption when user acknowledges the preemption.
 * However when other end receives preemption application must stop tone after 3 seconds and
 * ::CSCallDelegate::call:didPreempt:isPreemptionCompletionRequiredByClient: is NOT needed since there is no precedence call is directed at this
 * end, other end is free and ready to receive any other new call while tone is being played.
 *
 * @param preemptedCall call which was preempted and received didPreempt event.
 * @param handler A completion handler that receives the result of
 *                          the operation.
 *
 * @see ::CSCallDelegate::call:didPreempt:isPreemptionCompletionRequiredByClient:
 */

- (void)completePreemptionForCall:(CSCall*)preemptedCall completionHandler:(void (^)(NSError *error))handler;

/**
 * Enables or Disables Hunt Group Busy Position feature for a specified hunt group number.
 * When enabled, user will not receive any calls targeted for that hunt group.
 * In order to receive calls on the hunt group, feature needs to be disabled again.
 *
 * @param enabled If @c YES hunt group busy position is enabled. 
 *                If @c NO hunt group busy position is disabled.
 * @param huntGroupNumber The hunt group number for which feature is enabled or disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setHuntGroupBusyPositionEnabled:(BOOL)enabled forHuntGroup:(NSInteger)huntGroupNumber completionHandler:(void (^)(NSError *error))handler;

/**
 * Updates the feature with personalized label given by user.
 *
 * @param featureLabel The personalized label to be set.
 * @param featureParams The CSFeatureParameters object providing details about feature to update.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 */
- (void)setPersonalizedLabel:(NSString *)featureLabel forFeature:(CSFeatureParameters *)featureParams completionHandler:(void (^)(NSError *error))handler;

/**
 * A capability object indicating whether the hunt-group-busy-position feature is
 * available for the specified hunt group number.
 *
 * @param huntGroupNumber The hunt group number for which to query the availability of the
 *        feature.
 */
- (CSCapability *)huntGroupBusyPositionCapabilityForHuntGroupNumber:(NSInteger)huntGroupNumber;
@end

@protocol CSCallFeatureServiceDelegate <NSObject>
@optional

/**
 * Sent to indicate that call feature service is available.
 *
 * @param callFeatureService The call feature service instance sending the message.
 */
- (void)callFeatureServiceDidBecomeAvailable:(CSCallFeatureService *)callFeatureService;

/**
 * Sent to indicate that call feature service is unavailable.
 *
 * @param callFeatureService The call feature service instance sending the message.
 */
- (void)callFeatureServiceDidBecomeUnavailable:(CSCallFeatureService *)callFeatureService;

/**
 * Sent when the capability of a feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param featureType The feature for which capability has changed.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeFeatureCapability:(CSFeatureType)featureType;

/**
 * Sent when the status of a feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param featureStatus The updated feature status information.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeFeatureStatus:(CSFeatureStatusParameters *)featureStatus;

/**
 * Sent when the list of available features has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 */
-(void)callFeatureServiceDidChangeAvailableFeatures:(CSCallFeatureService *)callFeatureService;

/**
 * Sent when the status of the send all calls feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param enabled The new state of the feature.
 * @param extension The extension for which the feature has been enabled or
 *        disabled. The value is nil if the feature has been enabled or disabled
 *        for the user's local extension.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeSendAllCallsStatus:(BOOL)enabled forExtension:(NSString *)extension;

/**
 * Sent when the status of the call forwarding feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param enabled The new state of the feature.
 * @param extension The extension for which the feature has been enabled or
 *        disabled. The value is nil if the feature has been enabled or disabled
 *        for the user's local extension.
 * @param destination The new forwarding destination.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeCallForwardingStatus:(BOOL)enabled forExtension:(NSString *)extension destination:(NSString *)destination;

/**
 * Sent when the status of the call forwarding busy-no-answer feature has
 * changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param enabled The new state of the feature.
 * @param extension The extension for which the feature has been enabled or
 *        disabled. The value is nil if the feature has been enabled or disabled
 *        for the user's local extension.
 * @param destination The new forwarding destination.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeCallForwardingBusyNoAnswerStatus:(BOOL)enabled forExtension:(NSString *)extension destination:(NSString *)destination;

/**
 * Sent when the status of the Enhanced Call Forwarding feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param featureStatus The updated feature status information.
 * @param extension The extension for which the feature has been enabled or
 *        disabled. The value is nil if the feature has been enabled or disabled
 *        for the user's local extension.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeEnhancedCallForwardingStatus:(CSEnhancedCallForwardingStatus *)featureStatus forExtension:(NSString *)extension;

/**
 * Sent when the status of the EC500 feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param enabled The new state of the feature.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeEC500Status:(BOOL)enabled;

/**
 * Sent when the status of the auto callback feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param enabled The new state of the feature.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeAutoCallbackStatus:(BOOL)enabled;

/**
 * Sent when the status of the busy indicator object has changed.
 *
 * @param callFeatureService The call feature service instance that the
 *        callback is associated with.
 * @param busyIndicator The changed busy indicator object.
 */

- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeBusyIndicator:(CSBusyIndicator *)busyIndicator;

/**
 * Sent when the status of the call pickup feature has changed.
 *
 * @param callFeatureService The call feature service instance sending the message.
 * @param callPickupFeatureStatus The call pickup feature alert status
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeCallPickupAlertStatus:(CSCallPickupAlertStatus *)callPickupFeatureStatus;

/**
 * Occurs when the available team buttons list are updated.
 *
 * @see CSCallFeatureService::teamButtons
 */
- (void)didChangeTeamButtons:(CSCallFeatureService *)callFeatureService;

/**
 * Occurs if the Team Button busy status is changed when the monitored station
 * either dials or has an active call.
 * A Team Button is considered Idle if all call appearances on the monitored  station
 * are either in the Idle or Ringing states. If there are bridged call appearances on
 * the monitored station, the states "Alerting" and "In-Use" are interpreted by the CM
 * as equivalent to Idle.
 * @param callFeatureService The call feature service instance reporting the callback.
 * @param teamButton The team button with busy status updated.
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeBusyStatusForTeamButton:(CSTeamButton *)teamButton;

/**
 * Occurs when the monitored station of Team Button has an incoming ringing call.
 * The Team Button notification alert status depends on {@link CSTeamButton::pickupRingType}.
 *
 * {@link CSTeamButtonIncomingCall} started ringing at the monitored station is provided.
 * {@link CSTeamButtonIncomingCall::pickupWithCompletionHandler:} functionality is available.
 * @param callFeatureService The call feature service instance reporting the callback.
 * @param teamButton The team button that has alerting calls.
 * @param call The team button call that started alerting.
 * @see CSTeamButton::pickupCapability
 * @see CSTeamButton::speedDialCapability
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didAddIncomingCall:(CSTeamButtonIncomingCall *)call forTeamButton:(CSTeamButton *)teamButton;

/**
 * Occurs when the incoming call to monitored station stops ringing.
 *
 * {@link CSTeamButtonIncomingCall} stopped ringing at the monitored station is provided.
 * {@link CSTeamButtonIncomingCall::pickupWithCompletionHandler:} functionality is available.
 * @param callFeatureService The call feature service instance reporting the callback.
 * @param teamButton The team button that has alerting calls.
 * @param call The team button call that stopped alerting.
 * @see CSTeamButton::pickupCapability
 * @see CSTeamButton::speedDialCapability
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didRemoveIncomingCall:(CSTeamButtonIncomingCall *)call forTeamButton:(CSTeamButton *)teamButton;

/**
 * Occurs when the forwarding status of Team Button monitored station is changed.
 * @see CSTeamButton::forwardingEnabled
 * @see CSTeamButton::forwardingDestination
 */
- (void)callFeatureService:(CSCallFeatureService *)callFeatureService didChangeForwardingStatusForTeamButton:(CSTeamButton *)teamButton;

@end
