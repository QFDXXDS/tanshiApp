/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSParticipant.h"

@class CSCapability;
@class CSDroppedParticipant;

/**
 * Describes methods that are implemented by the delegate of a @c CSDroppedParticipant.
 */
@protocol CSDroppedParticipantDelegate <CSParticipantDelegate>

/**
 * Called when the underlying participantData has been changed.
 * @param participant The participant whose data has been changed.
 */
- (void)droppedParticipantDidChangeData:(CSDroppedParticipant *)participant;

@end

@interface CSDroppedParticipant : CSParticipant<NSCopying>

/**
 * The delegate used to handle dropped participant related events.
 */
@property (nonatomic, weak) id<CSDroppedParticipantDelegate> delegate;

/** Participant's entry time to the conference. */
@property (nonatomic, readonly) NSDate* enterDate;

/** Participant's leave time from the conference. */
@property (nonatomic, readonly) NSDate* leaveDate;

/**
 * ReInvite the participant to join the conference.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)reInviteWithCompletionHandler:(void (^)(NSError *error))handler;

@end

