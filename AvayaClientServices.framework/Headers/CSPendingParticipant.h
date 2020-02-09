/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSParticipant.h"
#import "CSPendingParticipantAdmissionCancellationReason.h"

@class CSParticipantData, CSCapability;
@class CSPendingParticipant;

/**
 * Describes methods that are implemented by the delegate of a @c CSPendingParticipant.
 */
@protocol CSPendingParticipantDelegate <CSParticipantDelegate>

/**
 * Report that a pending participant's request to join the conference call
 * has been accepted either by the local user, if the local user is a moderator,
 * or by a moderator on the call.
 * @param participant Pending participant who has been accepted.
 */
-(void)pendingParticipantWasAccepted:(CSPendingParticipant *)participant;

/**
 * Report that a user is no longer waiting to be admitted to the conference call.
 * @param participant A user who is no longer waiting to be admitted to the conference call.
 * @param reason A reason of cancellation.
 */
-(void)pendingParticipantWasCancelled:(CSPendingParticipant *)participant withReason:(CSPendingParticipantAdmissionCancellationReason *)reason;

/**
 * Report that a pending participant's request to join the conference call
 * has been denied either by the local user, if the local user is a moderator,
 * or by a moderator on the call.
 * @param participant Pending participant who has been denied.
 */
-(void)pendingParticipantWasDenied:(CSPendingParticipant *)participant;

@end

/**
 * **Unsupported:**
 * The pending participant feature is currently not supported.
 * The CSPendingParticipant class represents a participant pending to join the conference.
 *
 * When a conference call is locked, a person who wishes to join the call may "knock on the
 * conference room door" using conference server's knock on the door feature. This person is
 * described as a pending participant, because the person is waiting to join the call.
 * The conference moderator(s) may choose to grant or reject the pending participant's request.
 * Access grant and rejection are controlled by acceptWithCompletionHandler() and
 * and denyWithCompletionHandler() methods defined on CSPendingParticipant, respectively.
 * It should be noted that not all conference server releases support this feature.
 * The client application should check CSConference object's acceptDenyPendingParticipantCapability,
 * to find out whether the conference server supports this feature, and the local user
 * has permission to accept/reject entry to pending participants.
 * ---
 * **Unsupported:**
 * This class and all of its supporting classes are for internal Avaya use only and should not be
 * used by third party applications at this time. This is an incubating feature that is currently
 * under development and the classes and methods associated with this feature are subject to change
 * at any time. Use of this feature will not be supported by Avaya until such time that it is
 * officially released.
 */
@interface CSPendingParticipant : CSParticipant<NSCopying>

/**
 * **Unsupported:**
 * The pending participant feature is currently not supported.
 * The delegate used to handle pending participant related events.
 */
@property (nonatomic, weak) id<CSPendingParticipantDelegate> delegate;

/**
 * Participant's entry time to the conference.
 * Represents the time when participant has requested admission to join the conference
 */
@property (nonatomic, readonly) NSDate *enterDate;

/**
 * Accepts a participant's conference join request.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)acceptWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Denies a participant's conference join request.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)denyWithCompletionHandler:(void (^)(NSError *error))handler;

@end

