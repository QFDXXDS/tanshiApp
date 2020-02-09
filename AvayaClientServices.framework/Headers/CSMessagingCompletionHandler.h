/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@class CSMessage;
@class CSMessagingConversation;
@class CSMessageDeliveryDetails;

/**
 * Type of block used to report status of background task.
 */
typedef void (^CSMessagingCompletionHandler)(NSError *error);
typedef void (^CSMessagingMessageCompletionHandler)(CSMessage *message, NSError *error);
typedef void (^CSMessagingMessageDeliveryDetailsCompletionHandler)(CSMessageDeliveryDetails *deliveryDetails, NSError *error);

/**
 * Type of block used to report completion or failure of picture retrieval.
 *
 * @param pictureData picture in JPEG or PNG format.
 * @param error if operation fails, contains information about failure, nil otherwise.
 */
typedef void (^CSMessagingParticipantRetrievePictureCompletionHandler)(NSData *pictureData, NSError *error);

/**
 * Type of block used to report success completion of getting conversation by providerId process.
 *
 * @param conversation conversation object.
 * @param error if operation fails, contains information about failure, nil otherwise.
 */
typedef void (^CSConversationCompletionHandler)(CSMessagingConversation *conversation, NSError *error);
