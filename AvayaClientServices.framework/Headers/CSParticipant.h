/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContact.h"

/**
* Describes methods that are implemented by the delegate of a @c CSParticipant.
*/
@protocol CSParticipantDelegate;

/**
 * Base interface object representing a participant on a conference call.
 */
@interface CSParticipant : NSObject

- (instancetype)initWithParticipantId:(NSString*)participantId;

/**
 * The delegate used to handle participant events, common to all participant subclasses.
 */
@property (nonatomic, weak) id<CSParticipantDelegate> delegate;

/**
 * Participant's network provided display name, as known to the conferencing system.
 */
@property (nonatomic, readonly) NSString *displayName;

/**
 * Participant's network-provided address, as known to the conferencing system.
 */
@property (nonatomic, readonly) NSString *address;

/**
 * Whether the participant is the local user.
 */
@property (nonatomic, readonly, getter=isLocalUser) BOOL localUser;

/**
 * Unique identification of the participant.
 */
@property (nonatomic, readonly) NSString *participantId;

/**
 * Return best possible contact match. if no match is found, a nil is returned.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * It is recommended to use the ::CSContactService::resolveContacts: method instead.
 */
- (CSContact *)bestContactMatch DEPRECATED_ATTRIBUTE;

/**
 * Return all possible contact matches with level of matching.
 * Key is the enum of level matching, values is the list of matched contacts
 * Return emply dictionary if there is no match.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * It is recommended to use the ::CSContactService::resolveContacts: method instead.
 */
- (NSDictionary *)allPossibleContactMatches DEPRECATED_ATTRIBUTE;

/**
 * Sends private message to this participant.
 *
 * @param message Message to be sent.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)sendPrivateChatMessage:(NSString*)message completionHandler:(void (^)(NSError *error))handler;

@end

/**
 * Describes methods that are implemented by the delegate of a @c CSParticipant.
 */
@protocol CSParticipantDelegate <NSObject>

/**
 * Sent when the contacts matched to this participant have changed.
 * @param participant The participant whose data has been changed.
 */
- (void)participantDidChangeMatchedContacts:(CSParticipant *)participant;

@end

