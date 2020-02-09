/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>


/**
 * Admission request cancellation code enumeration.
 */
typedef NS_ENUM(NSUInteger, CSPendingParticipantAdmissionCancellationReasonCode) {
	/**
	 * Admission request has been cancelled by originator
	 */
	CSPendingParticipantAdmissionCancelled,
	/**
	 * Admission request has been cancelled by timeout
	 */
	CSPendingParticipantAdmissionTimeout,
	/**
	 * Admission request has been accepted by another moderator
	 */
	CSPendingParticipantAdmissionAcceptedByAnotherModerator,
	/**
	 * Admission request has been rejected by another moderator
	 */
	CSPendingParticipantAdmissionRejectedByAnotherModerator
};

/**
 * CSPendingParticipantAdmissionCancellationReason class represents a reason of admission cancellation.
 */
@interface CSPendingParticipantAdmissionCancellationReason : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 * Admission cancellation reason code.
 */
@property (nonatomic, readonly) CSPendingParticipantAdmissionCancellationReasonCode reasonCode;

/**
 * Admission cancellation reason string
 */
@property (readonly) NSString *reasonString;

/**
 * The name of another moderator who has admitted/rejected participant admission request.
 * Filled in case of AcceptedByAnotherModerator or RejectedByAnotherModerator
 * Empty by default
 */
@property (readonly) NSString *anotherModeratorName;

@end
