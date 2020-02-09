/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSMessagingConversation.h"

/**
 * Interface for leave conversation response.
 *
 * This class is used to return the results of a conversation leave operation.
 *
 * @see ::CSMessagingService::leaveConversations:watcher:
 */
@interface CSMessagingLeaveConversationResponse : NSObject

/**
 * The {@link CSMessagingConversation} object associated with leave operation.
 */
@property (nonatomic, readonly) CSMessagingConversation *conversation;

/**
 * The left status of the conversation. NO indicates that an error occurred.
 */
@property (nonatomic, readonly) BOOL leftStatus;

@end
