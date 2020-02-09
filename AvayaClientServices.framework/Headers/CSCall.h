/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCallCreationInfo.h"
#import "CSAudioDetails.h"
#import "CSVideoDetails.h"
#import "CSConference.h"
#import "CSVideoChannel.h"
#import "CSVideoResolutionPreference.h"
#import "CSSignalingServer.h"
#import "CSCapability.h"
#import "CSMaxSupportedVideoResolutionsCapability.h"
#import "CSVideoMode.h"
#import "CSCallForwardingInformation.h"

@protocol CSCallDelegate;

/**
 * The reason for the denial of an incoming call.
 */
typedef NS_ENUM(NSUInteger, CSCallDenialReason) {
	CSCallDenialReasonForbidden,
	CSCallDenialReasonTemporarilyUnavailable,
	CSCallDenialReasonBusy
};

/**
 * The state of a call.
 */
typedef NS_ENUM(NSInteger, CSCallState) {
	/** Call hasn't been started. */
	CSCallStateIdle,
	/** Call initiated (outgoing only). No response from far-end has been received. */
	CSCallStateInitiating,
	/** Call is alerting locally (incoming call). */
	CSCallStateAlerting,
	/** Call is alerting remotely (outgoing call). */
	CSCallStateRemoteAlerting,
	/** Call has been established and is active (not held). */
	CSCallStateEstablished,
	/** Call is transitioning to the held state. */
	CSCallStateHolding,
	/** Call is on hold. */
	CSCallStateHeld,
	/** Call is transitioning from the held state back to the established state. */
	CSCallStateUnholding,
	/** Call's video is being updated. */
	CSCallStateVideoUpdating,
	/** Transfer initiated by the local user (outgoing). */
	CSCallStateTransferring,
	/** The call is being transferred by a remote party on the call. Incoming transfer request received. */
	CSCallStateBeingTransferred,
	/** Call is ignored locally (incoming call), later it can be accepted or denied. */
	CSCallStateIgnored,
	CSCallStateFailed,
	/** Request to end the call has been sent. */
	CSCallStateEnding,
	/** Call ended (by far-end, or end request has been responded to by the remote party). */
	CSCallStateEnded,
	/** Call renegotiating (requested by us). */
	CSCallStateRenegotiating,
	/** Call renegotiating (requested by far-end). */
	CSCallStateFarEndRenegotiating
};

/**
 * The status of an in-progress join.
 */
typedef NS_ENUM(NSInteger, CSJoinStatus) {
	/** Call join is not yet started, default initial value. */
	CSJoinStatusNone,
	/** Call join is started, Join requested is accepted. */
	CSJoinStatusStarted,
	/** 
	 * Call join is partially completed and waiting for local media resources to be available.
	 * e.g an EC500 call on cellular can be joined from application. Once join request is accepted;
	 * the cellular call will be ended and VoIP call from application will get access for shared audio device.
	 * while cellular call is ending and still holds media resources to play end tones
	 * you may get status waiting for media resources.
	 */
	CSJoinStatusWaitingForMediaResources,
	/** Call join is successful. */
	CSJoinStatusCompleted
};

/**
 * The status of an in-progress transfer.
 */
typedef NS_ENUM(NSInteger, CSTransferStatus) {
	/** The transfer is not yet started, default status. */
	CSTransferStatusNone,
	/** The transfer is started, transfer request is sent. */
	CSTransferStatusStarted,
	/** The transfer request is accepted. */
	CSTransferStatusAccepted,
	/** The transferee is attempting to call transfer target. */
	CSTransferStatusRemoteCallStarted,
	/** The call is ringing at the transfer target's end. */
	CSTransferStatusRemoteCallInProgress,
	/** The call is accepted by transfer target and call is established between transferor and transfer target. */
	CSTransferStatusRemoteCallEstablished,
	/** The transfer operation is completed and transferor's call will be ended. */
	CSTransferStatusCompleted
};

/**
 * DTMF tone types.
 */
typedef NS_ENUM(NSUInteger, CSDTMFTone) {
	/** Represents numeric 0. */
	CSDTMFToneZero = 0,
	/** Represents numeric 1. */
	CSDTMFToneOne,
	/** Represents numeric 2. */
	CSDTMFToneTwo,
	/** Represents numeric 3. */
	CSDTMFToneThree,
	/** Represents numeric 4. */
	CSDTMFToneFour,
	/** Represents numeric 5. */
	CSDTMFToneFive,
	/** Represents numeric 6. */
	CSDTMFToneSix,
	/** Represents numeric 7. */
	CSDTMFToneSeven,
	/** Represents numeric 8. */
	CSDTMFToneEight,
	/** Represents numeric 9. */
	CSDTMFToneNine,
	/** Represents special character *. */
	CSDTMFToneStar,
	/** Represents special character #. */
	CSDTMFTonePound,
	/** Represents alphabet A. */
	CSDTMFToneA,
	/** Represents alphabet B. */
	CSDTMFToneB,
	/** Represents alphabet C. */
	CSDTMFToneC,
	/** Represents alphabet D. */
	CSDTMFToneD
};

/**
 * Address digits for dialing in the off-hook state.
 */
typedef NS_ENUM(NSUInteger, CSAddressDigit) {
    /** Represents numeric 0. */
    CSAddressDigitZero,
    /** Represents numeric 1. */
    CSAddressDigitOne,
    /** Represents numeric 2. */
    CSAddressDigitTwo,
    /** Represents numeric 3. */
    CSAddressDigitThree,
    /** Represents numeric 4. */
    CSAddressDigitFour,
    /** Represents numeric 5. */
    CSAddressDigitFive,
    /** Represents numeric 6. */
    CSAddressDigitSix,
    /** Represents numeric 7. */
    CSAddressDigitSeven,
    /** Represents numeric 8. */
    CSAddressDigitEight,
    /** Represents numeric 9. */
    CSAddressDigitNine,
    /** Represents special character *. */
    CSAddressDigitStar,
    /** Represents special character #. */
    CSAddressDigitPound,
    /** Represents special character +. */
    CSAddressDigitPlus
};

/**
 * Incoming call alert types.
 */
typedef NS_ENUM(NSUInteger, CSAlertType) {
	/** Unspecified */
	CSAlertTypeUnspecified,
	/** None of the alert types */
	CSAlertTypeNone,
	/** Internal call alert type */
	CSAlertTypeInternal,
	/** External call alert type */
	CSAlertTypeExternal,
	/** Priority call alert type */
	CSAlertTypePriority,
	/** Intercom alert type */
	CSAlertTypeIntercom,
	/** Alert type indicating that it is auto callback */
	CSAlertTypeAutoCallback,
	/** Alert type indicating that it is recall after hold */
	CSAlertTypeHoldRecall,
	/** Alert type indicating that it is recall after transfer */
	CSAlertTypeTransferRecall,
	/** Alert type indicating that it is direct internal agent call */
	CSAlertTypeDirectAgentCallInternal,
	/** Alert type indicating that it is direct external agent call */
	CSAlertTypeDirectAgentCallExternal,
	/** Alert type indicating that it is direct priority call from agent */
	CSAlertTypeDirectAgentCallPriority,
	/** Alert type indicating that it is distributed automatic internal call */
	CSAlertTypeAutomaticCallDistributionInternal,
	/** Alert type indicating that it is distributed automatic external call */
	CSAlertTypeAutomaticCallDistributionExternal,
	/** Alert type of abbreviated ring */
	CSAlertTypeAbbreviatedRing,
	/** Alert type of delayed ring */
	CSAlertTypeDelayedRing
};

typedef NS_ENUM(NSUInteger, CSIncomingVideoStatus) {
	/**Caller's video request status is unknown.*/
	CSNetworkVideoUnknown,
	/** Caller did not request video.*/
	CSNetworkVideoUnsupported,
	/** Caller requested video.*/
	CSNetworkVideoSupported
};

typedef NS_ENUM(NSUInteger, CSCallEndReason) {
	/** Call ended locally. */
	CSCallEndReasonEndedLocally,
	/** Call disconnected from remote end. */
	CSCallEndReasonCallDisconnected,
	/** Call was in a conference and moderator has dropped this call. */
	CSCallEndReasonDisconnectedByConferenceModerator,
	/** Call ended due to session expired. */
	CSCallEndReasonSessionExpired
};

/**
 * Enumeration of different allowed video directions that can be used
 * by the local application for a call session.
 * Allowed video direction can be changed during call session and depends on call state,
 * network availability and server limitations.
 * Same time allowed video direction can be limited by conference server.
 * Example: call started with video in send-receive direction but server limited allowed direction
 * to receive only. Call will negotiate to receive only video and allowed video direction will be Receive only.
 */
typedef NS_ENUM(NSUInteger, CSAllowedVideoDirection) {
	/**
	 * Video is not allowed.
	 */
	CSAllowedVideoDirectionNone = 0,
	/**
	 * Bi-directional video allowed.
	 */
	CSAllowedVideoDirectionSendReceive,
	/**
	 * Receive-only video allowed.
	 */
	CSAllowedVideoDirectionReceiveOnly,
	/**
	 * Send-only video allowed.
	 */
	CSAllowedVideoDirectionSendOnly
};

/**
 * Call Precedence Level
 *
 * DoD(Department of defence) UC networks support Precedence-Based Assured Services (PBAS) for delivery of UC services.
 * Connections and resources that belong to a call from a user are marked with a precedence level
 * and domain identifier and can only be preempted by calls of higher precedence from users in the same service domain.
 * Precedence provides for preferred handling of PBAS service requests. PBAS involves assigning and validating priority
 * levels to calls, and prioritized treatment of service requests.
 *
 * There are five precedence levels; from lowest to highest
 * they are ROUTINE, PRIORITY, IMMEDIATE, FLASH, and FLASH OVERRIDE.
 *
 * Maximum precedence level of a user is set at the subscription time by the UC network administrator
 * based on the user’s validated need. When initiating a session, the user may select a precedence level
 * up to and including the maximum authorized precedence level for that user, on a per call basis.
 *
 * The network at the user's originating interface ensures that the selected precedence level
 * does not exceed the maximum level assigned to that extension.
 *
 * When JITC Multilevel call precedence and preemption (MLPP) is enabled at server, A call will
 * default automatically to the ROUTINE precedence unless a higher precedence is dialed.
 *
 **/

typedef NS_ENUM(NSUInteger, CSPrecedenceLevel) {
	/**
	 * Call precedence level is not specified,
	 * Used for non JITC(MLPP) based systems. This is also default value when no precedence is specified.
	 * However when when MLLP is enabled at server, A call will no precedence level will be automatically
	 * upgraded to the ROUTINE precedence unless a higher precedence is dialed.
	 */
	CSPrecedenceLevelNotSpecified,
	
	/**
	 * Call precedence level is routine.
	 * When jitc(MLLP) is enabled at server, A call will default automatically to the ROUTINE
	 * precedence unless a higher precedence is dialed.
	 */
	CSPrecedenceLevelRoutine,
	
	/**
	 * Call precedence level is priority.
	 */
	CSPrecedenceLevelPriority,
	
	/**
	 * Call precedence level is immediate.
	 */
	CSPrecedenceLevelImmediate,
	
	/**
	 * Call precedence level is flash.
	 */
	CSPrecedenceLevelFlash,
	
	/**
	 * Call precedence level is flash override.
	 */
	CSPrecedenceLevelFlashOverride
};

/**
 * Call Preemption reasons based on Reason Header for Preemption Events (RFC 4411) - IETF
 * and Department of Defense Unified Capabilities Requirements 2013.
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
 * Preemption may take one of two forms.
 * First, the called party may be busy with a lower precedence call that is preempted
 * in favor of completing the higher precedence call from the calling party.
 * Second, the network resources may be busy with calls; some of which are of lower
 * precedence than the call requested by the calling party. One or more of these lower
 * precedence calls are preempted in order to complete the higher precedence call.
 *
 */

typedef NS_ENUM(NSUInteger, CSPreemptionReason) {
	/**
	 * The call is not preempted.
	 */
	CSPreemptionReasonNone,
	
	/**
	 * The call has been preempted by a UA(User Agent).
	 * UA Preemption occurs when called party may be busy with a lower precedence
	 * call that is preempted in favor of completing the higher precedence call
	 * from the calling party.
	 */
	CSPreemptionReasonUAPreemption,
	
	/**
	 * The call preemption has been initiated within the network via a
	 * purposeful RSVP(Resource ReSerVation Protocol) preemption occurrence,
	 * and not a link error.
	 */
	CSPreemptionReasonReservedResourcesPreempted,
	
	/**
	 * This is a limited-use preemption indication to be used on the final leg
	 * to the preempted UA to generalize the event.
	 */
	CSPreemptionReasonGenericPreemption,
	
	/**
	 * The call preemption has occurred in a non-IP portion of the infrastructure,
	 * and this is the Reason cause code given by the SIP Gateway.
	 */
	CSPreemptionReasonNonIPPreemption,
	
	/**
	 * Reason-params in RFC 4411 fails to fully meet Department of Defense needs,
	 * the AS-SIP signaling appliances support a fifth Reason-param intended to
	 * characterize a network preemption event that occurs in the IP portion of the
	 * network but is not due to a RSVP preemption occurrence.
	 */
	CSPreemptionReasonNetworkPreemption,
};

/**
 * The Call class is a facade object that may be used to represent a 2-party or a
 * or a conference call. When a Call instance represents a 2-party call,
 * conference-related methods are unsupported.
 * The client application can call \link CSCall::conference conference \endlink method regardless of whether the call
 * is a point to point or a conference call. Calling conference operations on a pt-to-pt
 * call returns failure.
 * The Call also supports video control methods, which can be applied to either a
 * 2-party or a conference call.
 * @see to create new call \link CSCallService::createCall createCall \endlink.
 */
@interface CSCall : NSObject

/**
 * The delegate responsible for handling call-related events.
 */
@property (nonatomic, weak) id<CSCallDelegate> delegate;

/**
 * The unique numeric ID for this call.
 */
@property (nonatomic, readonly) NSInteger callId;

/**
 * Enum value indicating whether this is default registered service (SIP call through Aura) or Meetme call through Service gateway
 **/
@property (nonatomic, readonly) CSCallType callType;

/**
 * A Boolean value indicating whether the call is in presentation only mode.
 */
@property (nonatomic, readonly, getter=isPresentationOnlyMode) BOOL presentationOnlyMode;

/**
 * Returns true if the call is created as a result of invoking the call pickup feature
 * ::CSFeatureTypeGroupCallPickup, ::CSFeatureTypeDirectedCallPickup, ::CSFeatureTypeExtendedGroupCallPickup or ::CSFeatureTypeTeamButton pickup
 * @return indication as to whether the call is pickup call.
 */
@property (nonatomic, readonly, getter=isPickupCall) BOOL pickupCall;

/**
 * Returns true if the call is created as a result of invoking the Team Button feature.
 * @return indication whether the call is a team button call.
 */
@property (nonatomic, readonly, getter=isTeamButtonCall) BOOL teamButtonCall;

/**
 * The remote address for this call.
 *
 * For SIP this is the unescaped URI of the remote end of the call.
 */
@property (nonatomic, copy) NSString *remoteAddress;

/**
 * For a call in the off-hook dialing state, adds a digit to the remote address
 * being collected via a dial pad.
 *
 * When a match is found in the dial plan the call will automatically be
 * initiated and -[CSCallDelegate callDidCompleteDigitCollection] will be sent.
 * During digit collection the dial plan may indicate that dial tone should be
 * played, this will be indicated via
 * -[CSCallDelegate callDidRequestDialToneForDigitCollection].
 * @param digit The digit to be appended to the remote address.
 */
- (void)addRemoteAddressDigit:(CSAddressDigit)digit;

/**
 * The display name for the remote end of the call.
 */
@property (nonatomic, readonly) NSString *remoteDisplayName;

/**
 * The number for the remote end of the call. For outgoing calls, it's the
 * the post dialing rules string. For incoming SIP calls, it's the user part of the URI.
 */
@property (nonatomic, readonly) NSString *remoteNumber;

/**
* The remote call owner name.
*/
@property (nonatomic, readonly) NSString *lineAppearanceOwnerAddress;

/**
* The line id for the remote call.
*/
@property (nonatomic, readonly) NSUInteger lineAppearanceId;

/**
 * The information about the remote participant connected to the call.
 * The information in participant can be empty if call is not connected
 * OR the details are not available for remote party.
 */

@property (nonatomic, readonly) CSParticipant *remoteParticipant;

/**
 * The subject line associated with the call, if any.
 */
@property (nonatomic, copy) NSString *subject;

/**
 * For an incoming call, the associated alert type.
 */
@property (nonatomic, readonly) CSAlertType alertType;

/**
 * The current precedence level of call.
 * @see CSPrecedenceLevel
 */
@property (nonatomic, readonly) CSPrecedenceLevel precedenceLevel;

/**
 * The reason why this call was preempted.
 * @see CSPreemptionReason
 */
@property (nonatomic, readonly) CSPreemptionReason preemptionReason;

/**
 * The call's current state.
 */
@property (nonatomic, readonly) CSCallState state;

/**
 * A Boolean value indicating whether this is an incoming call.
 */
@property (nonatomic, readonly, getter=isIncoming) BOOL incoming;

/**
 * A Boolean value indicating whether this incoming call can be answered automatically.
 */
@property (nonatomic, readonly) BOOL canAutoAnswer;

/**
 * A Boolean value indicating whether this is a remote call.
 *
 * A remote call is one that does not exist on the local device but the user is aware of, such as
 * a call on a bridged line appearance.
 */
@property (nonatomic, readonly, getter=isRemote) BOOL remote;

/**
 * A Boolean value indicating whether the identity of the user who initiated the call wishes their
 * identity to be kept private.
 * For an incoming call, this property returns whether the remote user's address is private.
 * For an outgoing call, this property returns whether the local user's address is private (which
 * can happen if user chooses to make a private call).
 */
@property (nonatomic, readonly, getter=isCallerIdentityPrivate) BOOL callerIdentityPrivate;

/**
 * For an incoming call, a Boolean value indicating whether the call was missed.
 */
@property (nonatomic, readonly, getter=isMissed) BOOL missed;

/**
 * A Boolean value indicating whether this is an ignored call.
 */
@property (nonatomic, readonly, getter=isIgnored) BOOL ignored;

/**
 * A Boolean value indicating whether this is a conference call.
 */
@property (nonatomic, readonly) BOOL isConference;

/**
 * The conference instance associated with the call.
 * The CSConference object is returned regardless of whether the call is a conference call
 * or not. Invoking methods on the Conference object returns an error if the call is
 * not a conference call.
 */
@property (nonatomic, readonly) CSConference *conference;

/**
* A Boolean value indicating whether audio has been explicitly muted for this call.
*
* This does not reflect device-level mute state that may affect this call, but only the
* call-specific mute state controlled via -[CSCall muteAudio:].
*/
@property (nonatomic, readonly, getter=isAudioMuted) BOOL audioMuted;

/**
* A Boolean value indicating whether speaker has been explicitly silenced for this call.
*
* This does not reflect device-level speaker silence state that may affect this call, but only the
* call-specific speaker silence state controlled via -[CSCall silenceSpeaker:].
*/
@property (nonatomic, readonly, getter=isSpeakerSilenced) BOOL speakerSilenced;

/**
 * A Boolean value indicating whether there is an active signaling path available for this call.
 */
@property (nonatomic, readonly, getter=isServiceAvailable) BOOL serviceAvailable;

/**
 * The time the call was initially established.
 */
@property (nonatomic, readonly) NSDate *establishedDate;

/**
 * The time the call was last placed on hold.
 */
@property (nonatomic, readonly) NSDate *heldDate;

/**
 * A Boolean value indicating if the call was ever answered/accepted.
 *
 */
@property (nonatomic, readonly, getter=isAnswered) BOOL answered;

/**
 * A Boolean value indicating whether this is an emergency call.
 */
@property (nonatomic, readonly, getter=isEmergencyCall) BOOL emergencyCall;

/**
 * The ring cycles for abbreviated/delayed alerting for bridged call.
 */
@property (nonatomic, readonly) NSUInteger abbreviatedDelayedRingCycles;

/**
 * Starts an outgoing call to the current remote address.
 * Usage in Shared Control mode: UI should call this function only for
 * outgoing calls initiated from UC client. In all other call cases do not
 * invoke the Start function for any call or conference because calls are
 * initiated from the desk phone.
 */
- (void)start;

/**
 * Requests termination of the call.
 */
- (void)end;

/**
 * For an incoming call, requests acceptance of an incoming call.
 */
- (void)accept;

/**
 * Ignores an incoming call.
 *
 * The call is not ended, to the remote it will seem as if the call
 * is still alerting. The application can use this method to silent the
 * ringing of call without rejecting it. The call can still be accepted or rejected
 * after it is ignored.
 */
- (void)ignore;

/**
 * For an incoming call, denies the call using the default denial reason (busy).
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)denyWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * For an incoming call, denies the call for the specified reason.
 *
 * @param reason The reason for the denial.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nill. If an error occurred it
 *        contains an object describing the error.
 */
- (void)denyWithReason:(CSCallDenialReason)reason completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the call can be held.
 * It should be noted that a subsequent hold operation
 * depends on the state of the call that is being held.
 */
@property (nonatomic, readonly) CSCapability *holdCapability;

/**
 * Requests that an active call be held. If the hold is successful,
 * all CallListener are informed of the hold state change. If it
 * fails, the CompletionHandler is informed of the failure.
 * If the hold operation fails, the call state returns
 * to 'established' state, and any media channels previously ended to
 * handle hold request are resumed.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)holdWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the call can be unheld.
 * It should be noted that a subsequent unhold operation is not guaranteed to succeed
 * as this depends on the state of the call that is being unheld.
 */
@property (nonatomic, readonly) CSCapability *unholdCapability;

/**
 * Requests that a held call be unheld. If unhold is successful, The call
 * transition to 'established' state, and its media channel(s) are restored.
 * If unhold fails, the call stays in 'held' state, and its media channel(s)
 * are not restored.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)unholdWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the call can be joined.
 * It should be noted that a subsequent join operation is not guaranteed to succeed
 * as this depends on the characteristics of the remote call that is being joined.
 * For example, the remote call may have exclusion turned on, in which case the local
 * user will not be allowed to join.
 */
@property (nonatomic, readonly) CSCapability *joinCapability;

/**
 * Request that a remote call to be joined. When the join is successful,
 * the existing call object becomes a local call. This can be verified
 * by querying isRemote(), which returns false when the join is successful.
 * If the join operation fails, the call continues representing a remote
 * call. In this case, isRemote() returns true.
 *
 * @param handler A block to be called to report the status of the join operation.
 *        @li @c status The current status of the join operation.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)joinWithStatusHandler:(void (^)(CSJoinStatus status, NSError *error))handler;

/**
 * CSCapability object indicating whether this call can be unattended transferred.
 */
@property (nonatomic, readonly) CSCapability *transferCapability;

/**
 * Transfers this call to the specified remote address (an unattended transfer).
 *
 * If dialing rules have been configured via @link CSUserConfiguration::dialingRulesConfiguration CSUserConfiguration.dialingRulesConfiguration @endlink
 * they will be applied to the remote address. To control whether dialing rules
 * are applied use #transferToRemoteAddress:applyingDialingRules:statusHandler:
 * instead.
 *
 * @param address The remote address to transfer to.
 * @param handler A block to be called to report the status of the transfer operation.
 *        @li @c status The current status of the transfer operation.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)transferToRemoteAddress:(NSString *)address statusHandler:(void (^)(CSTransferStatus status, NSError *error))handler;

/**
 * Transfers this call to the specified remote address (an unattended transfer).
 *
 * @param address The remote address to transfer to.
 * @param applyDialingRules Controls whether any configured dialing rules will
 *        be applied to the remote address.
 * @param handler A block to be called to report the status of the transfer operation.
 *        @li @c status The current status of the transfer operation.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSUserConfiguration::dialingRulesConfiguration
 */
- (void)transferToRemoteAddress:(NSString *)address applyingDialingRules:(BOOL)applyDialingRules statusHandler:(void (^)(CSTransferStatus status, NSError *error))handler;

/**
 * CSCapability object indicating whether this call can be transferred to the call
 * specified in the input argument.
 * @param callToTarget Call to the transfer target
 * @return CSCapability object indicating whether call can be transferred.
 */

- (CSCapability *)transferToCallCapability:(CSCall *)callToTarget;

/**
 * Transfers this call to another call (an attended transfer).
 * In SIP, transfer operation is implemented using delegation technique where transferor
 * delegates transferee to reach out to transfer target in order to complete the transfer
 * operation. While the transfer is in progress, the transferor receives feedback from the
 * transferee about the status of the transfer. If a failure is reported by the transferee,
 * on the transferor's is notified of the error via the handler that was provided as input
 * argument.
 *
 * @param callToReplace The existing call to transfer to.
 * @param handler A block to be called to report the status of the transfer operation.
 *        @li @c status The current status of the transfer operation.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)transferToCall:(CSCall *)callToReplace statusHandler:(void (^)(CSTransferStatus status, NSError *error))handler;

/**
 * CSCapability object indicating whether DTMF tones can be sent over the call.
 * For example, the capability is denied, if the call is in ringing state without early media (VoIP).
 */
@property (nonatomic, readonly) CSCapability *sendDigitCapability;

/**
 * Sends the specified DTMF tone.
 *
 * @param tone The DTMF tone to send.
 */
- (void)sendDigit:(CSDTMFTone)tone;

/**
 * Reads detailed information about the audio channel associated with the call.
 *
 * If the audio channel has ended the audio details contain the information received from the
 * channel just before it was ended.
 * @param handler A block to be called to with audio details in CSAudioDetails.
 */
- (void)readAudioDetailsWithCompletionHandler:(void (^)(CSAudioDetails *audioDetails))handler;

/**
 * Reads list of CSVideoDetails objects representing details of all video streams in call.
 *
 * @param handler A block to be called to with video details in arrayOfVideoDetails.
 */
- (void)readVideoDetailsWithCompletionHandler:(void (^)(NSArray *arrayOfVideoDetails))handler;

/**
 * CSCapability object indicating whether the call's audio can be muted.
 */
@property (nonatomic, readonly) CSCapability *muteCapability;

/**
 * CSCapability object indicating whether the call's audio can be unmuted.
 */
@property (nonatomic, readonly) CSCapability *unmuteCapability;

/**
 * Mutes or unmutes the call's audio.
 *
 * @param mute YES to mute audio; NO to unmute.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @sa -[CSCallDelegate::call:didMuteAudio:]
 * @sa -[CSCallDelegate::call:muteAudioDidFailWithError:]
 */
- (void)muteAudio:(BOOL)mute completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether speaker can be silenced for the call.
 */
@property (nonatomic, readonly) CSCapability *silenceSpeakerCapability;

/**
 * CSCapability object indicating whether speaker can be unsilenced for the call.
 */
@property (nonatomic, readonly) CSCapability *unsilenceSpeakerCapability;

/**
 * Silences or unsilences speaker for the call.
 *
 * @param silence YES to silence speaker; NO to unsilence.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @sa -[CSCallDelegate::call:didSilenceSpeaker:]
 * @sa -[CSCallDelegate::call:silenceSpeakerDidFailWithError:]
 */
- (void)silenceSpeaker:(BOOL)silence completionHandler:(void (^)(NSError *error))handler;

/**
 * Determine if the incoming call has video.
 * @return CSIncomingVideoStatus indicating the video availability in an incoming call
 */
@property (nonatomic, readonly) CSIncomingVideoStatus incomingVideoStatus;

/**
 * CSCapability object indicating whether current video mode of the call can be updated
 * based on the current state and capabilities of the call.
 * The capability object indicates an error(denial) if the current call state does not allow video
 * mode update, or if local video is disabled, e.g., due to video licensing or local platform's
 * configuration.
 */
@property (nonatomic, readonly) CSCapability *updateVideoModeCapability;

/**
 * Property that provides the maximum number of receive only video streams that
 * can be supported, and the maximum resolution that can be supported for
 * each video stream.
 * The information returned is based on local bandwidth and video resolution configuration,
 * local CPU/platform's video decode capabilities, and other user's video related
 * information such as end user video preference, video licensing, etc.
 * However, after the call setup, if the call is not multi video stream enabled,
 * this CSCapability::allowed returns false, indicating that
 * calling CSCall::setReceiveVideoResolutionPreferences: will not succeed. Similarly, for
 * a call that is not multi video stream enabled,
 * CSMaxSupportedVideoResolutionsCapability::maxSupportedVideoResolutions: returns
 * an empty list.
 * @return Maximum number of receive only video streams that
 * can be supported, and their maximum resolution.
 **/
@property (nonatomic, readonly) CSMaxSupportedVideoResolutionsCapability *multiVideoChannelsCapability;

/**
 * The video channels associated with this call.
 */
@property (nonatomic, readonly) NSArray *videoChannels;

/**
 * A convenience method that returns if the call has active video session or not.
 * The method returns true if there is at least one video channel that is enabled,
 * and has a negotiated media direction of send-receive, receive-only or send-only.
 */
@property (nonatomic, readonly) BOOL videoActive;

/**
 * Returns the current video mode of the call, that is, whether video is enabled or disabled, and if
 * enabled, the video direction.
 */
@property (nonatomic, readonly) CSVideoMode videoMode;

/**
 * Returns allowed video direction for current call and its state.
 */
@property (nonatomic, readonly) CSAllowedVideoDirection allowedVideoDirection;

/**
 * A read - only map of extra call properties the application may be interested in.
 * For SIP - based calls, the map contains the list of SIP headers that are unknown to the SDK.
 * SIP header name is used as the map key, and the header content is used as to the value of the map entry.
 * During the lifetime of a call session, the extra properties of the call may be updated based on the
 * information received from the network.The extra properties field tracks cumulative list of properties added
 * to the call.For instance, an unknown SIP header of the form "header1: content1" is received, it is added to the map
 * (key = “header1”, value = “content1”)
 * A subsequent SIP message carrying two unknown headers "header1: contentA" and "header2: content2" will result in the
 * update of the existing property as well as addition of a new map entry, as follows :
 * (key = “header1”, value = “contentA”)
 * (key = “header2”, value = “content2”)
 * If there are multiple occurrences of an unknown SIP header, a unique map entry is created for each occurrence by
 * appending a unique integer to the header name.For instance, if a SIP message contains two occurrences of an unknown
 * SIP header, "unknownHeader:content1" and "unknownHeader:content2", then two separate map entries are created :
 * (key = ”unknownHeader”, value = ”content1”)
 * (key = ”unknownHeader2”, value = ”content2”)
 * The application will be notified of this change using the CSCallDelegate::call : didChangeExtraProperties : event.
 */
@property(nonatomic, readonly) NSDictionary *extraProperties;

/**
 * Information about forwarding details of current incoming call.
 * Information can be null if current incoming call was not forwarded.
 */
@property(nonatomic, readonly) CSCallForwardingInformation *forwardingInformation;


/**
 * Sets the overall video status for the call. This method can be used to enable bidirectional or
 * unidirectional video, or disable video.
 * @param videoMode Desired video status for the call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)setVideoMode:(CSVideoMode)videoMode completionHandler:(void (^)(NSError *error))handler;

/**
 * Used in conjunction with CSCall::setVideoMode: to set receive video resolutions the client
 * application wants to have for multi video stream calls. Calling this method is optional.
 *
 * If this method is not called and the local user wants to receive video, for a multi video stream conference
 * call the Client SDK negotiates the maximum number of video streams that can be supported with the server,
 * subject to the limitations of the local CPU/host capabilities and the locally provisioned video-related
 * bandwidth and resolution settings.
 * If this method is called, the number of video streams negotiated with the conference server and their resolution
 * will be the lesser of the information passed in the method and the maximum number of video streams that can be
 * supported subject to the limitations of the conference server's ability to multiple video streams,
 * the local CPU/platform limitations, and the locally provisioned video bandwidth and resolution settings.
 * For example, the conference server may be capable of sending up to nine 180p video streams, but the local platform
 * may only be able to decode up to one 360p and four 180p video streams. If this method is not called, when the server
 * escalates the single video stream call to multi stream video, the SDK negotiates one 360p stream and four 180p video
 * streams with the server. Depending on the number of video participants on the call and the capabilities of the
 * media server, the local SDK may receive anywhere from a single 360p video stream up to four 180p video streams.
 * In the same example, if the local application called this method to view up to three video streams, then only
 * three video streams are negotiated with the conference server.
 * If the application sets a lesser number of video streams to render than what can be supported maximum, some of
 * the video channel instances that can be supported but not requested by the application for rendering are marked
 * as disabled, and reported with disabled reason of "layout selection".
 * It should be noted that calling this method on a call that does not support multiple video channels has no effect.
 * But in this case successful response would be provided through completion handler.
 * However, a call normally starts as a point to point call, and is later escalated to have multi video channels.
 * In this case, any preference setting provided prior to the multiple video channels escalation is used during
 * processing of an incoming escalation request.
 * This method may be called mid-call.
 * @param videoResolutionPreferences The video resolution preferences requested by the application.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 * @sa -[CSCallDelegate call:didUpdateVideoChannels:]
 * @deprecated Use {@link setReceiveVideoResolutionPreferencesForMultiVideoStreaming:completionHandler:}
 **/

- (void)setReceiveVideoResolutionPreferences:(NSArray *)videoResolutionPreferences completionHandler:(void (^)(NSError *error))handler DEPRECATED_MSG_ATTRIBUTE("Use setReceiveVideoResolutionPreferencesForMultiVideoStreaming:completionHandler:");


/**
 * Used in conjunction with CSCall::setVideoMode: to set receive video resolutions the client
 * application wants to have for multi video stream calls. Calling this method is optional.
 *
 * If this method is not called and the local user wants to receive video, for a multi video stream conference
 * call the Client SDK negotiates the maximum number of video streams that can be supported with the server,
 * subject to the limitations of the local CPU/host capabilities and the locally provisioned video-related
 * bandwidth and resolution settings.
 * If this method is called, the number of video streams negotiated with the conference server and their resolution
 * will be the lesser of the information passed in the method and the maximum number of video streams that can be
 * supported subject to the limitations of the conference server's ability to multiple video streams,
 * the local CPU/platform limitations, and the locally provisioned video bandwidth and resolution settings.
 * For example, the conference server may be capable of sending up to nine 180p video streams, but the local platform
 * may only be able to decode up to one 360p and four 180p video streams. If this method is not called, when the server
 * escalates the single video stream call to multi stream video, the SDK negotiates one 360p stream and four 180p video
 * streams with the server. Depending on the number of video participants on the call and the capabilities of the
 * media server, the local SDK may receive anywhere from a single 360p video stream up to four 180p video streams.
 * In the same example, if the local application called this method to view up to three video streams, then only
 * three video streams are negotiated with the conference server.
 * If the application sets a lesser number of video streams to render than what can be supported maximum, some of
 * the video channel instances that can be supported but not requested by the application for rendering are marked
 * as disabled, and reported with disabled reason of "layout selection".
 * It should be noted that calling this method on a call that does not support multiple video channels has no effect.
 * But in this case successful response would be provided through completion handler.
 * However, a call normally starts as a point to point call, and is later escalated to have multi video channels.
 * In this case, any preference setting provided prior to the multiple video channels escalation is used during
 * processing of an incoming escalation request.
 * This method may be called mid-call.
 * @param videoResolutionPreferences The video resolution preferences requested by the application.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 * @sa -[CSCallDelegate call:didUpdateVideoChannels:]
 **/

- (void)setReceiveVideoResolutionPreferencesForMultiVideoStreaming:(NSArray *)videoResolutionPreferences completionHandler:(void (^)(NSError *error))handler;

/**
 * Used in conjunction with CSCall::setVideoMode: to set video resolution. The actual resolution
 * can be lower than the specified preference. It is subjected to the negotation result,
 * configuration limits, and hardware capability.
 * Calling this method is optional. This method may be called mid-call.
 * Note: This API adjusts the encoder and decoder resolution. It does not affect the capture resolution. Refer to the media engine documentation to adjust the video capture resolution.
 *
 * @param videoResolutionPreferences The video resolution preference requested by the application.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 * @sa -[CSCallDelegate call:didUpdateVideoChannels:]
 **/
- (void)setVideoResolutionPreferenceForMainVideoStreaming:(CSVideoResolutionPreferenceForMainVideoStreaming *)videoResolutionPreferences completionHandler:(void (^)(NSError *error))handler;

/**
 * Called to accept incoming video escalation. The video can be accepted to be bidirectional or
 * unidirectional.
 * @param videoMode Desired video status for the call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)acceptVideo:(CSVideoMode)videoMode completionHandler:(void (^)(NSError *error))handler;

/**
 * Denies the incoming request to add video.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)denyVideoWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the collaboration can be added to the call.
 */
@property (nonatomic, readonly) CSCapability *addCollaborationCapability;

/**
 * Adds a collaboration session to this call.
 *
 * If the call is a two-party call, the call becomes a conference.  If the call is already a conference,
 * the call is not modified.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)addCollaborationWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the call can be transferred to voicemail.
 * It should be noted that a subsequent transfer operation
 * depends on the state of the call that is being transferred.
 */
@property (nonatomic, readonly) CSCapability *transferToVoicemailCapability;

/**
 * Transfers this call to the specified remote address's voicemail (an unattended transfer).
 *
 * If dialing rules have been configured via @link CSUserConfiguration::dialingRulesConfiguration CSUserConfiguration.dialingRulesConfiguration @endlink
 * they will be applied to the remote address. To control whether dialing rules
 * are applied use #transferToVoicemailForRemoteAddress:applyingDialingRules:statusHandler:
 * instead.
 *
 * @param address The remote address whose voicemail transfer the call to.
 * @param handler A block to be called to report the status of the transfer operation.
 * @li @c status The current status of the transfer operation.
 * @li @c error If the operation was successful this parameter is nil. If an error occurred it
 * contains an object describing the error.
 */
- (void)transferToVoicemailForRemoteAddress:(NSString *)address statusHandler:(void (^)(CSTransferStatus status, NSError *error))handler;

/**
 * Transfers this call to the specified remote address's voicemail (an unattended transfer).
 *
 * @param address The remote address whose voicemail transfer the call to.
 * @param applyDialingRules Controls whether any configured dialing rules will
 *        be applied to the remote address.
 * @param handler A block to be called to report the status of the transfer operation.
 *        @li @c status The current status of the transfer operation.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSUserConfiguration::dialingRulesConfiguration
 */
- (void)transferToVoicemailForRemoteAddress:(NSString *)address applyingDialingRules:(BOOL)applyDialingRules statusHandler:(void (^)(CSTransferStatus status, NSError *error))handler;


@end

/**
 * Describes methods that are implemented by the delegate of a @c CSCall.
 */
@protocol CSCallDelegate <NSObject>

/**
 * Sent when the call has been started.
 *
 * @param call The call sending the message.
 */
- (void)callDidStart:(CSCall *)call;

/**
 * Sent when the outgoing call begins alerting at the remote end.
 *
 * In SIP this corresponds to the call receiving a 180 or 183 response from the network. It
 * should be noted that this method may be sent multiple times during initiating an outgoing
 * call as a result of changes to early media availability and/or redirections. Application
 * developers should not make assumptions about exact ordering of provisional responses, as the
 * sequence depends on different call routing features/topologies.
 *
 * @param call The call sending the message.
 * @param hasEarlyMedia Indicates whether early media is associated with the call.
 */
- (void)callDidBeginRemoteAlerting:(CSCall *)call withEarlyMedia:(BOOL)hasEarlyMedia;

/**
 * Sent when an outgoing call is queued by a network server.
 *
 * In SIP this callback happens as a result of receiving SIP 182 provisional response.
 * In Avaya's SIP solution, this response is received in contact center environment,
 * when the call is placed in a VDN queue, waiting to be connected to a live agent.
 *
 * @param call The call sending the message.
 */
- (void)callDidQueue:(CSCall *)call;

/**
 * Sent when an outgoing call is redirected by the network servers
 * to a different destination (e.g., when EC500 forking takes place or call is covered to
 * voice mail).
 *
 * In SIP, this callback happens when 181 provisional response is received.
 * It should be noted that this notice depends on the capabilities of the network servers, and
 * some servers may redirect a call without providing a specific redirection notice.
 *
 * @param call The call sending the message.
 */
- (void)callDidRedirect:(CSCall *)call;

/**
 * Sent when the outgoing call has been established.
 *
 * In SIP this corresponds to the call receiving a 200 response from the network.
 *
 * @param call The call sending the message.
 */
- (void)callDidEstablish:(CSCall *)call;

/**
 * Sent when the call has been held.
 *
 * @param call The call sending the message.
 */
- (void)callDidHold:(CSCall *)call;

/**
 * Sent when the call has been unheld.
 *
 * @param call The call sending the message.
 */
- (void)callDidUnhold:(CSCall *)call;

/**
 * Sent when the call has been held on the remote end.
 *
 * @param call The call sending the message.
 */
- (void)callDidRemoteHold:(CSCall *)call;

/**
 * Sent when the call has been unheld on the remote end.
 *
 * @param call The call sending the message.
 */
- (void)callDidRemoteUnhold:(CSCall *)call;

/**
 * Sent when the call has been successfully joined and transitioned from a remote call to a
 * local call.
 *
 * @param call The call sending the message.
 */
- (void)callDidJoin:(CSCall *)call;

/**
 * Sent when the incoming call has been ignored.
 *
 * @param call The call sending the message.
 */
- (void)callWasIgnored:(CSCall *)call;

/**
 * Sent when the incoming call has been successfully denied.
 *
 * @param call The call sending the message.
 */
- (void)callDidDeny:(CSCall *)call;

/**
 * Sent when the call has ended.
 *
 * @param call The call sending the message.
 * @param reason The reason of a call end.
 */
- (void)callDidEnd:(CSCall *)call reason:(CSCallEndReason)reason;

/**
 * Sent when the call has failed.
 *
 * This method is sent when the call has failed either as a result of a local error or as a result
 * of an error received from the network (e.g., when a call attempt to an unreachable address is
 * made). The specific reason for failure is identified by @c error. It should be noted that a
 * call that has failed is not automatically ended by the signaling engine. The application must
 * still call -[CSCall end] to end the failed call. This is done so that a UI implementation
 * that is line-oriented can keep the line appearance occupied while the call is in failed state.
 *
 * @param call The call sending the message.
 * @param error An error object describing the failure.
 */
- (void)call:(CSCall *)call didFailWithError:(NSError *)error;

/**
 * Sent when the call's audio is muted or unmuted.
 *
 * @param call The call sending the message.
 * @param muted The new audio mute state.
 */
- (void)call:(CSCall *)call didMuteAudio:(BOOL)muted;

/**
 * Sent when speaker is silenced or unsilenced for the call.
 *
 * @param call The call sending the message.
 * @param silenced The new speaker silence state.
 */
- (void)call:(CSCall *)call didSilenceSpeaker:(BOOL)silenced;

/**
 * Sent when the video channels have been updated.
 *
 * @param call The call sending the message.
 * @param videoChannels The updated video channels.
 */
- (void)call:(CSCall *)call didUpdateVideoChannels:(NSArray *)videoChannels;

/**
 * Sent when a video channel has been removed by the remote end.
 *
 * @param call The call sending the message.
 * @param videoChannel The removed video channel.
 */
- (void)call:(CSCall *)call didRemoteRemoveVideoChannel:(CSVideoChannel *)videoChannel;

/**
 * Sent when the remote end has requested that video be added to the call.
 *
 * @param call The call sending the message.
 */
- (void)callDidReceiveVideoAddRequest:(CSCall *)call;

/**
 * Sent when the incoming video add request has been accepted by the local end.
 *
 * @param videoChannel The video channel used to accept video.
 * @param call The call sending the message.
 */
- (void)call:(CSCall *)call didAcceptVideoAddRequest:(CSVideoChannel *)videoChannel;

/**
 * Sent when the incoming video add request has been denied by the local end.
 *
 * @param call The call sending the message.
 */
- (void)callDidDenyVideoAddRequest:(CSCall *)call;

/**
 * Sent when the incoming video add request has timed out.
 *
 * @param call The call sending the message.
 */
- (void)callDidTimeoutVideoAddRequest:(CSCall *)call;

#if TARGET_OS_IPHONE
/**
 * Sent to request the UI to connect media resources (e.g., audio devices)
 * to the session, then invoke Call.Accept() to establish media. The event is
 * only sent to the UI by the 3PCC feature upon remote answer.
 *
 * @param call The call sending the message.
 */
- (void)callDidRemoteControlAnswer:(CSCall *)call;
#endif

/**
 * Sent when the remote address or display name for the call has changed.
 *
 * @param call The call sending the message.
 * @param remoteAddress The new remote address.
 * @param displayName The new display name.
 */
- (void)call:(CSCall *)call didChangeRemoteAddress:(NSString *)remoteAddress displayName:(NSString *)displayName;

/**
 * Sent when the conference status of the call has changed.
 *
 * For example, as a result of adding a participant a two-party call may have been transitioned
 * to a conference call, or a conference call transitioned to a two-party call as result of
 * a participant being dropped.
 *
 * @param call The call sending the message.
 * @param isConference The new conference status.
 */
- (void)call:(CSCall *)call didChangeConferenceStatus:(BOOL)isConference;

/**
 * Sent when a signaling path has been established for the call.
 *
 * @param call The call sending the message.
 */

- (void)callServiceDidBecomeAvailable:(CSCall *)call;

/**
 * Sent when the signaling path for the call has been lost.
 *
 * @param call The call sending the message.
 */
- (void)callServiceDidBecomeUnavailable:(CSCall *)call;

/**
 * Sent when the the call's capabilities have changed,
 * e.g., as a result of a call state change or other internal events.
 *
 * @param call The call sending the message.
 */
- (void)callDidChangeCapabilities:(CSCall *)call;

/**
 * Sent when the the remote participant's matched contacts changed.
 * e.g., new contacts added, deleted or update.
 *
 * @param call The call sending the message.
 */
- (void)callParticipantMatchedContactsChanged:(CSCall *)call;

@optional

/**
 * For a call in the off-hook dialing state, indicates that the dial plan data
 * has specified that the application should resume playing dial tone until
 * another digit is entered.
 */
- (void)callDidRequestDialToneForDigitCollection:(CSCall *)call;

/**
 * For a call in the off-hook dialing state, indicates that digit collection
 * has completed and the call will now be initiated using the collected
 * digits.
 */
- (void)callDidCompleteDigitCollection:(CSCall *)call;

/**
 * Sent when the precedence level for the call has changed.
 *
 * @param call The call sending the message.
 * @param newPrecedenceLevel the new precedence level of call.
 * @see CSPrecedenceLevel
 */
- (void)call:(CSCall *)call didChangePrecedenceLevel:(CSPrecedenceLevel)newPrecedenceLevel;

/**
 * Sent to inform application about call being preempted.
 * This would trigger application to start either continuous preemption tone OR
 * three seconds preemption tone based on flag isPreemptionCompletionRequiredByClient
 * and call state.
 *
 * Call preemption occurs when a precedence call is sent to a preemptable endpoint
 * that is busy with a call of lower precedence and has no idle appearances.
 * This causes the lower precedence call to be preempted, regardless of whether
 * the lower precedence call and the new higher precedence call are of the same media type.
 * When preemption occurs, the active busy user receive a continuous preemption tone until user
 * acknowledges the preemption by invoking complete preemption method and the other party receives
 * a preemption tone for a minimum of 3 seconds.
 * After acknowledging the preemption, the extension to which the precedence call is directed will
 * be provided with precedence ringing and the calling party will receive an audible ringback
 * precedence tone.
 *
 * Application must start playing preemption tone upon receipt of event onCallPreempted and stop
 * preemption tone before calling ::CSCallFeatureService::completePreemptionForCall:completionHandler:
 * when user acknowledges the preemption.
 * However when other end receives preemption application must stop tone after 3 seconds and
 * ::CSCallFeatureService::completePreemptionForCall:completionHandler: is NOT needed
 * since there is no precedence call is directed at this end, other end is free and ready to receive
 * any other new call while tone is being played.
 *
 * @param call Call object that the callback is associated with, the same call object should be used
 *             for completing the preemption.
 *
 * @param preemptionReason the reason why this call was preempted.
 *
 * @param isPreemptionCompletionRequiredByClient indicates if application needs complete call preemption.
 *
 * When isPreemptionCompletionRequiredByClient is true, Application must inform system
 * when user acknowledges the preemption after continuous preemption tone is being played because active busy user's call is preempted.
 * This is done by calling method ::CSCallFeatureService::completePreemptionForCall:completionHandler:. After
 * user acknowledges the preemption, that also means application would stop preemption tone.
 *
 * When isPreemptionCompletionRequiredByClient is false, Application needs to
 * play three seconds preemption tone after active or outgoing alerting call is preempted.
 *
 * @see ::CSCallFeatureService::completePreemptionForCall:completionHandler:
 * @see ::CSPreemptionReason
 */
- (void)call:(CSCall *)call didPreempt:(CSPreemptionReason)preemptionReason isPreemptionCompletionRequiredByClient:(BOOL)isPreemptionCompletionRequiredByClient;

/**
 * Sent when the allowed video direction has changed.
 *
 * @param call The call sending the message.
 * @param videoDirection new allowed video direction.
 */
- (void)call:(CSCall *)call didChangeAllowedVideoDirection:(CSAllowedVideoDirection)videoDirection;

/**
 * Occurs when the extra properties associated with the call have changed. The list of
 * extra properties is provided as part of the callback, but can also be queried by accessing to
 * the extraProperties property.
 *
 * @param call The call sending the message.
 * @param extraProperties Complete list of extra properties associated with the call.
 */
- (void)call:(CSCall *)call didChangeExtraProperties:(NSDictionary *)extraProperties;

@end
