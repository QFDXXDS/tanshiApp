/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSMessagingEnums.h"
#import "CSMessagingParticipant.h"

/**
 * Represents delivery state of a message at the individual chat participant (i.e.recipient) level.
 */
typedef NS_ENUM(NSInteger, CSRecipientMessageState) {
	CSRecipientMessageStateUnknown,         /**< If the state of a remote recipient could not be determined, for example if the remote cluster is down or could not be reached. */
	CSRecipientMessageStateDelivered,       /**< Delivered to recipient. */
	CSRecipientMessageStateRead,            /**< Read by recipient. */
};

/**
 * This class defines delivery details of message.
 */
@interface CSMessageDeliveryDetails : NSObject

/**
 * The message delivery state describing whether this message is being sent or delivered.
 * @return Delivery state (eg. Unsent, Sent, Delivered).
 */
@property (nonatomic, readonly) CSMessagingMessageDeliveryState deliveryState;

/**
 * The message read state describing whether this message is read, partially read or not read.
 * @return Read state (eg. Unknown, NotRead, Read, PartiallyRead).
 */
@property (nonatomic, readonly) CSMessagingMessageReadState readState;

/**
 * Dictionary of message states associated with recipients.
 * @return Dictionary keyed by CSMessagingParticipant associated with CSRecipientMessageState
 */
@property (nonatomic, readonly) NSDictionary<CSMessagingParticipant *, NSNumber *> *recipientMessageStates;

@end
