/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSParticipant.h"
#import "CSChatMessage.h"
#import "CSDataCollectionChangeType.h"

// When support for DataSet in the public API is removed, delete this #define and any blocks of code that are
// being conditionally compiled by the DATASET_SUPPORTED define.
#define DATASET_SUPPORTED

@class CSDataSet;

@protocol CSChatDelegate;

/**
 * The CSChat object provides access to conference chat related capabilities and actions.
 * The CSChat object is accessible via CSConference and CSCollaboration. Client is notified 
 * about status updates concerning conference chat via CSChatDelegate object.
 *
 * @see CSChatDelegate
 * @see CSCollaboration
 * @see CSConference
 */
@interface CSChat : NSObject

/**
 * The delegate used to handle chat-related events.
 */
@property (nonatomic, weak) id<CSChatDelegate> delegate;

/**
 * An array of CSChatMessage objects representing the list of all messages in the chat.
 *
 * The returned array is a snapshot in time and is not dynamically updated as the list changes.
 * Updates to the message list (add, remove or update) are reported through the CSChatDelegate via the:
 * {@link CSChatDelegate::chat:allMessagesDidChange:changedMessages:}
 *
 * @see CSChat::publicMessages
 * @see CSChat::privateMessages
 */
@property (atomic, readonly, copy) NSArray *allMessages;

/**
 * An array of CSChatMessage objects representing the list of public messages in the chat.
 *
 * The returned array is a snapshot of public chat messages in time and is not dynamically updated as the list changes.
 * Updates to the message list (add, remove or update) are reported through the CSChatDelegate via the
 * {@link CSChatDelegate::chat:publicMessagesDidChange:changedMessages: publicMessagesDidChange}
 * message.
 *
 * @see CSChat::allMessages
 * @see CSChat::privateMessages
 */
@property (atomic, readonly, copy) NSArray *publicMessages;

/**
 * An array of CSChatMessage objects representing the list of private messages in the chat.
 *
 * The returned array is a snapshot of prvaite meassages in time and is not dynamically updated as the list changes.
 * Updates to the message list (add, remove or update) are reported through the CSChatDelegate via the
 * {@link CSChatDelegate::chat:privateMessagesDidChange:changedMessages: privateMessagesDidChange}
 * message.
 *
 * @see CSChat::allMessages
 * @see CSChat::publicMessages
 */
@property (atomic, readonly, copy) NSArray *privateMessages;

#ifdef DATASET_SUPPORTED
/**
 * CSDataSet object indicating the all chat messages.
 * @deprecated Use the {@link #allMessages} property instead.
 */
@property (nonatomic, readonly) CSDataSet *allChatMessages DEPRECATED_ATTRIBUTE;

/**
 * CSDataSet object indicating the private chat messages.
 * @deprecated Use the {@link #privateMessages} property instead.
 */
@property (nonatomic, readonly) CSDataSet *privateChatMessages DEPRECATED_ATTRIBUTE;

/**
 * CSDataSet object indicating the public chat messages.
 * @deprecated Use the {@link #publicMessages} property instead.
 */
@property (nonatomic, readonly) CSDataSet *publicChatMessages DEPRECATED_ATTRIBUTE;

#endif

/**
 * Sends private chat message to given participant. Client is notified about successful operation
 * also by CSChatDelegate apart from completion handler.
 *
 * @param message Message to be sent.
 * @param participant Receiver of private message.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSChat::sendPublicMessage:toParticipant:completionHandler:
 * @see CSChatDelegate
 */
- (void)sendPrivateMessage:(NSString*)message toParticipant:(CSParticipant*)participant
		 completionHandler:(void (^)(NSError *error))handler;

/**
 * Sends public chat message which can be seen by all conference participant. 
 * Client is notified about successful operation also by CSChatDelegate apart from completion handler.
 *
 * @param message Message to be sent.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *        @li @c message If the operation was successful this parameter contains sent message.
 *
 * @see CSChat::sendPrivateMessage:toParticipant:completionHandler:
 * @see CSChatDelegate
 */
- (void)sendPublicMessage:(NSString*)message
		completionHandler:(void (^)(NSError *error))handler;
		
/**
 * Return the participant list associated with the chat.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c participantList If the operation was successful this parameter contains list of collaboration participants otherwise it is empty.
 */
- (void) getChatParticipantsWithCompletionHandler:(void (^)(NSArray *participantList))handler;

@end


/**
 * Chat delegate provides updates about the status of chat.
 *
 * The client application is notified about status updates reported by the server
 * through the CSChatDelegate object. These updates may be the result of local operations
 * on the CSChat object as well as remote changes initiated by either the server or other
 * users on the conference call.
 *
 * @see CSChat::delegate
 */
@protocol CSChatDelegate <NSObject>

/**
 * Called when the chat session started and became available. Chat can become 
 * available/unavailable in case of network disruptions within one call.
 *
 * @param chat The chat sending the message.
 *
 * @see CSChat::chatDidReportServiceUnavailable:
 */
- (void)chatDidReportServiceAvailable:(CSChat *)chat;

/**
 * Called when the chat became unavailable what can be caused by network disruption. 
 * It doesn't mean that chat session has ended.
 *
 * @param chat The chat sending the message.
 *
 * @see CSChat::chatDidReportServiceAvailable:
 */
- (void)chatDidReportServiceUnavailable:(CSChat *)chat;

@optional

/**
 * Reports that chat received message. Method is deprecated. Use other
 * CSChatDelegate method notifying about received messages.
 *
 * @see CSChatDelegate::chat:allMessagesDidChange:changedMessages:
 * @see CSChatDelegate::chat:publicMessagesDidChange:changedMessages:
 * @see CSChatDelegate::chat:privateMessagesDidChange:changedMessages:
 */
- (void)chat:(CSChat *)chat didReceiveMessage:(CSChatMessage *)message DEPRECATED_ATTRIBUTE;

/**
 * Sent to report that the list of messages in the chat has changed.
 *
 * @param chat The chat sending the message.
 * @param changeType The type of change that has occurred to the message list.
 * @param changedMessages An array of CSChatMessage objects that have changed. For a delete change,
 *                     the supplied objects have been removed from the list.
 *                     For a "collection cleared" change, this array will be empty.
 *
 * @see CSChat::allMessages
 */
- (void)chat:(CSChat *)chat allMessagesDidChange:(CSDataCollectionChangeType)changeType changedMessages:(NSArray *)changedMessages;

/**
 * Sent to report that the list of public messages in the chat has changed.
 *
 * @param chat The chat sending the message.
 * @param changeType The type of change that has occurred to the message list.
 * @param changedMessages An array of CSChatMessage objects that have changed. For a delete change,
 *                     the supplied objects have been removed from the list.
 *                     For a "collection cleared" change, this array will be empty.
 *
 * @see CSChat::publicMessages
 */
- (void)chat:(CSChat *)chat publicMessagesDidChange:(CSDataCollectionChangeType)changeType changedMessages:(NSArray *)changedMessages;

/**
 * Sent to report that the list of private messages in the chat has changed.
 *
 * @param chat The chat sending the message.
 * @param changeType The type of change that has occurred to the message list.
 * @param changedMessages An array of CSChatMessage objects that have changed. For a delete change,
 *                     the supplied objects have been removed from the list.
 *                     For a "collection cleared" change, this array will be empty.
 *
 * @see CSChat::privateMessages
 */
- (void)chat:(CSChat *)chat privateMessagesDidChange:(CSDataCollectionChangeType)changeType changedMessages:(NSArray *)changedMessages;

@end
