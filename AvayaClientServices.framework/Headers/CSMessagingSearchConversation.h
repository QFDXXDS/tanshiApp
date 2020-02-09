/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSMessagingConversation.h"

#import "CSMessagingSearchConversation.h"
/*
 * Interface for conversation returned from
 * {@link -[CSMessagingService searchConversationsWithQuery:watcher:]} operation.
 *
 * <p>
 * This is a conversation object used for instances returned by a search operation.
 * It is a wrapper for regular conversation object with all provided selector and properties. In
 * addition it contains method to retrieve messages that match search query.
 * </p>
 */
@interface CSMessagingSearchConversation : CSMessagingConversation

/**
 * Returns reference to the conversation object corresponding to this search conversation.
 * If the underlying conversation is active and exists on the conversations list
 * returned reference will point to the same object that exists on the conversations list.
 */
@property (nonatomic, readonly) CSMessagingConversation *baseConversation;

/**
 * Get all messages matching search request in conversation.
 *
 * @param watcher A CSDataRetrievalWatcher object, created by the application, to track the progress of the message retrieval.
 * Prior to calling this method, the application should have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher
 * object to receive notifications on the progress of the retrieval of the message collection and subsequent updates to
 * this collection.  A value of *nil* will remove any currently installed watcher object, stopping all notifications from being
 * sent to the previous watcher object.
 * The data items returned to the application via the watcher object will be of type {@link CSMessage}.
 */
- (void)retrieveSearchMessagesWithWatcher:(CSDataRetrievalWatcher *)watcher;

@end
