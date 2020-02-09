/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * The state of a communication call.
 */

typedef NS_ENUM(NSUInteger, CSCapabilityDenialReason) {
	CSCapabilityNotDenied,
	CSCapabilityInsufficientPermission,
	CSCapabilityNotSignedIn,
	CSCapabilityInvalidState,
	CSCapabilityNotSupported,
	CSCapabilityCallIsRemote,
	CSCapabilityCallIsNotRemote,
	CSCapabilityCallHasNoAudio,
	CSCapabilityCallHasNoVideo,
	CSCapabilityCellularCallInProgress,
	CSCapabilityOperationInProgress,
	CSCapabilityOtherOperationInProgress,
	CSCapabilityNotLicensed,
	CSCapabilityWifiUnavailable,
	CSCapabilityNetworkUnavailable,
	CSCapabilityConferenceWaitingAdmission,
	CSCapabilityRejectedByServer
};

/*
 * A class representing whether a certain operation can be supported based
 * on the current state of the object upon which the action is taken.
 * For instance, a CSCapability instance returned from a CSConference object
 * may indicate whether the conference call can support muting of a selected participant,
 * based on the participant control capabilities of the conferencing system and the
 * current role of the local user.
 */

@interface CSCapability : NSObject

/**
 * Whether the capability is allowed
 */

@property (nonatomic, readonly) BOOL allowed;

/**
 * Whether the capability is allowed
 */

@property (nonatomic, readonly) CSCapabilityDenialReason denialReason;

@end
