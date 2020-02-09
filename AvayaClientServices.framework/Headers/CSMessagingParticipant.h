/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSMessagingEnums.h"
#import "CSParticipant.h"
#import "CSMessagingCompletionHandler.h"
#import "CSMessagingParticipantPhoneNumber.h"

/**
 * Interface for all messaging participant related tasks and properties.
 * <p>Every participant of message is a registered user on the messaging server. It is basically
 * the most important data about the participant of a conversation, used for not including the whole
 * contact object. If a particular contact is available on the current user list, it can be
 * obtained by the {@link #bestContactMatch} property.</p>
 */
@interface CSMessagingParticipant : CSParticipant<NSCopying>

/**
 * Returns the messaging participant type.
 * @return the messaging participant type.
 */
@property (nonatomic, readonly) CSMessagingParticipantType type;

/**
 * Returns the last name for the participant.
 * @return the last name for the participant.
 */
@property (nonatomic, readonly) NSString *lastName;

/**
 * Returns the first name for the participant.
 * @return the first name for the participant.
 */
@property (nonatomic, readonly) NSString *firstName;

/**
 * Get the participant name display order.
 * @return the participant name display order.
 */
@property (nonatomic) CSMessagingDisplayOrder displayOrder;

/**
 * Equality operator
 * @param object The other participant to compare to
 */
- (BOOL)isEqual:(id)object;

/**
 * Returns contact modalities set. See also @{CSMessagingModality}
 */
@property (nonatomic, readonly) NSSet *modalities;

/**
 * Indicates whether the participant has a picture.
 * @return true if participant has picture, false otherwise.
 */
@property (nonatomic, readonly) BOOL hasPicture;

/**
 * Returns the participant source type.
 * @return the participant source type.
 */
@property (nonatomic, readonly) CSMessagingParticipantSourceType sourceType;

/**
 * Retrieves picture for participant.
 *
 * @param handler The completion handler associated with this operation.
 */
- (void)retrievePictureWithCompletionHandler:(CSMessagingParticipantRetrievePictureCompletionHandler)handler;

/**
 * Returns array of {@link CSMessagingParticipantPhoneNumber} containing all phone numbers.
 * @return array of {@link CSMessagingParticipantPhoneNumber}.
 */
@property (nonatomic, readonly) NSArray* phoneNumbers;

@end
