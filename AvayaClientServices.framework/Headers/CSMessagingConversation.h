/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSDataRetrievalWatcher.h"
#import "CSCapability.h"
#import "CSMessage.h"
#import "CSMessagingEnums.h"
#import "CSMessagingParticipant.h"
#import "CSMessagingCompletionHandler.h"

/**
 * Type of block used to report change in conversation participants.
 * @param participants Array of CSMessagingParticipant objects or nil in case of error.
 * @param error Error object or nil if operation succeeded.
 */
typedef void (^CSMessagingParticipantsChangedCompletionHandler)(NSArray* participants, NSError *error);

@protocol CSMessagingConversationDelegate;

@protocol CSMessagingComposingParticipantsWatcherDelegate;

/**
 * Interface for all conversation related tasks and properties.
 *
 * A conversation is managing a list of messages which are sent between its participants.
 *
 * Beside messages, a conversation also contains a lot of its own parameters.
 * Almost all of them can be set only before it is published.
 * After that, one can only send a message, add a new participant, change subject, etc.
 *
 * It is important to understand that all conversation participants have the same privileges.
 * Once the first user starts a conversation it cannot be closed by that user; every user can leave only
 * by themselves, and add new participants as desired.
 *
 * After creating new conversation object call #addParticipantAddresses:completionHandler:
 * method for adding new participants. Before sending first message set all other required parameters,
 * like Subject and call #startWithCompletionHandler: method.
 */
@interface CSMessagingConversation : NSObject

/**
 * The delegate responsible for handling conversation events
 */
@property (nonatomic, weak) id<CSMessagingConversationDelegate> delegate;

/**
 * The delegate responsible for handling messages signalling a change in the list of composing participants.
 *
 * The application should set a delegate only when needed, to reduce the network traffic associated with updating
 * the composing participants list.  When no longer interested in this information (i.e. the user has left the 
 * conversation window), the application should set this delegate to **nil** to remove the installed delegate.
 *
 * When there is no delegate set, the {@link #composingParticipants} property will always return an empty array,
 * since the lack of an installed delegate indicates that the application is not interested in this information.
 */
@property (nonatomic, weak) id<CSMessagingComposingParticipantsWatcherDelegate> composingParticipantsWatcherDelegate;

/**
 * The unique conversation identifier.
 */
@property (nonatomic, readonly) NSString *conversationId;

/**
 * This is the conversation ID from the underlying provider (e.g., the AMM server) as-is.
 * It will be consistent across clients and application launches, but is only
 * guaranteed to be unique for conversations of that provider type.
 * It will be empty for draft conversation.
 */
@property (nonatomic, readonly) NSString *providerConversationId;

/**
 * The sensitivity of the conversation.
 *
 * @see #privateConversation
 * @see #setSensitivity:completionHandler:
 * @see ::CSMessagingSensitivityLevel
 */
@property (nonatomic) CSMessagingSensitivityLevel sensitivity;

/**
 * A Boolean value indicating whether the conversation is active.
 *
 * An active conversation is one that allows new contributions from any of the current
 * participants and has the local user as an active participant (i.e. the local user has not
 * left the conversation).
 */
@property (nonatomic, readonly, getter=isActive) BOOL active;

/**
 * A Boolean value indicating whether the conversation is closed.
 *
 * A closed conversation prohibits new contributions (or activity of any kind) from any
 * participants. Such conversations are candidates for being deleted (after backup) as part of
 * storage management activities.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangeClosedStatus:
 */
@property (nonatomic, readonly, getter=isClosed) BOOL closed;

/**
 * The multi-party status of the conversation.
 *
 * A conversation is considered to be a multi-party conversation if there are more than two
 * active participants in the conversation.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangeMultiPartyStatus:
 */
@property (nonatomic, readonly, getter=isMultiParty) BOOL multiParty;

/**
 * The conversation is private when the #sensitivity of the conversation is set to
 * {@link CSMessagingSensitivityLevelPrivate}.
 *
 * @return true if the conversation is private.
 */
@property (nonatomic, readonly, getter=isPrivateConversation) BOOL privateConversation;

/**
 * A Boolean value indicating whether the conversation has unread messages since the time the conversation was last accessed.
 *
 * @see #lastAccessDate
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangeLastAccessedTime:]
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangeTotalUnreadMessageCount:
 * @see #retrieveMessagesWithWatcher:
 */
@property (nonatomic, readonly) BOOL hasUnreadMessagesSinceLastAccess;

/**
 * A Boolean value indicating whether the conversation has any unread messages.
 *
 * @see #unreadMessageCount
 * @see #retrieveMessagesWithWatcher:
 */
@property (nonatomic, readonly) BOOL hasUnreadMessages;

/**
 * A Boolean value indicating whether the conversation has any unread attachments.
 *
 * @see #unreadAttachmentCount
 */
@property (nonatomic, readonly) BOOL hasUnreadAttachments;

/**
 * A Boolean value indicating whether the conversation has any attachments on any of its messages.
 *
 * @see #attachmentCount
 */
@property (nonatomic, readonly) BOOL hasAttachments;

/**
 * Returns YES if a specified participant is active in this conversation.
 *
 * @param messagingParticipant the participant to query for
 * @return YES if the specified participant is an active participant of the conversation.
 */
- (BOOL)isParticipantActive:(CSMessagingParticipant *)messagingParticipant;

/**
 * The date the conversation was last accessed.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangeLastAccessedTime:
 */
@property (nonatomic, readonly) NSDate *lastAccessDate;

/**
 * The date the conversation was last updated.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangeLastUpdatedTime:
 */
@property (nonatomic, readonly) NSDate *lastUpdatedDate;

/**
 * The last entry timestamp of the conversation. This is the timestamp of the most
 * recent message in the conversation.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangeLatestEntryTime:
 */
@property (nonatomic, readonly) NSDate *latestEntryDate;

/**
 * An array of composing participants contained in this conversation.
 */
@property (nonatomic, readonly) NSArray *composingParticipants;

/**
 * A list of participants contained in this conversation.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didAddParticipants:
 * @see ::CSMessagingConversationDelegate::messagingConversation:didRemoveParticipants:
 */
@property (nonatomic, readonly) NSArray *allParticipants;

/**
 * A list of active participants contained in this conversation.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didAddParticipants:
 * @see ::CSMessagingConversationDelegate::messagingConversation:didRemoveParticipants:
 */
@property (nonatomic, readonly) NSArray *activeParticipants;

/**
 * The conversation type.
 *
 * @see ::CSMessagingConversationType
 */
@property (nonatomic) CSMessagingConversationType type;

/**
 * The preview text of the conversation.
 *
 * Preview text is a body of the latest message in the conversation.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangePreviewText:
 */
@property (nonatomic, readonly) NSString *previewText;

/**
 * The total number of messages in the conversation.
 *
 * @see ::CSMessagingConversationDelegate messagingConversation:didChangeTotalMessageCount:
 */
@property (nonatomic, readonly) NSUInteger totalMessageCount;

/**
 * The total number of attachments in all messages of the conversation.
 *
 * @see ::CSMessagingConversationDelegate messagingConversation:didChangeTotalAttachmentCount:
 */
@property (nonatomic, readonly) NSUInteger attachmentCount;

/**
 * The total number of unread attachments in all messages of the conversation.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangeTotalUnreadAttachmentCount:
 */
@property (nonatomic, readonly) NSUInteger unreadAttachmentCount;

/**
 * The number of unread messages in the conversation.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangeTotalUnreadMessageCount:
 */
@property (nonatomic, readonly) NSUInteger unreadMessageCount;

/**
 * The subject of the conversation if one is provided by the server.
 *
 * @see ::CSMessagingConversationDelegate messagingConversation:didChangeSubject:
 * @see #setSubject:completionHandler:
 */
@property (nonatomic, readonly) NSString *subject;

/**
 * The last {@link CSMessagingParticipant} that updated this conversation.
 */
@property (nonatomic, readonly) CSMessagingParticipant *lastUpdatedByParticipant;

/**
 * The server reconciled status of the conversation.
 *
 * @see ::CSMessagingConversationDelegate::messagingConversation:didChangeStatus:
 */
@property (nonatomic, readonly) CSMessagingConversationStatus status;

/**
 * Creates a new message in this conversation.
 *
 * @return A new {@link CSMessage} object, or nil if a new message could not be created.
 *
 * @see #createMessageCapability
 */
- (CSMessage *)createMessage;

/**
 * Removes a {@link CSMessage} (only draft messages can be removed).
 *
 * @param messageToRemove The {@link CSMessage} to be removed.
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 */
- (void)removeMessage:(CSMessage *)messageToRemove completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Invokes a start request for this conversation.
 *
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 */
- (void)startWithCompletionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Invokes an add participant request for this conversation for provided contact object.
 *
 * @param contact - Contact representing the participant to add
 * @param handler {@link CSMessagingParticipantsChangedCompletionHandler} for this operation.
 *
 * @see #addParticipantsCapability
 */
- (void)addParticipantWithContact:(CSContact *)contact completionHandler:(CSMessagingParticipantsChangedCompletionHandler)handler;

/**
 * Invokes an add participant request for this conversation for each of the provided addresses.
 *
 * @param addressesToAdd - NSArray of NSStrings representing the participant addresses to add
 * @param handler {@link CSMessagingParticipantsChangedCompletionHandler} for this operation.
 *
 * @see #addParticipantsCapability
 */
- (void)addParticipantAddresses:(NSArray *)addressesToAdd completionHandler:(CSMessagingParticipantsChangedCompletionHandler)handler;

/**
 * Invokes a remove participant request for this conversation for each of the provided addresses.
 *
 * @param addressesToRemove - NSArray of NSStrings representing the participant addresses to remove
 * @param handler {@link CSMessagingParticipantsChangedCompletionHandler} for this operation.
 *
 * @see #removeParticipantsCapability
 */
- (void)removeParticipantAddresses:(NSArray *)addressesToRemove completionHandler:(CSMessagingParticipantsChangedCompletionHandler)handler;

/**
 * Invokes a remove participant request for this conversation.
 *
 * @param messagingParticipant the participant to remove from this conversation.
 * @param handler {@link CSMessagingParticipantsChangedCompletionHandler} for this operation.
 *
 * @see #removeParticipantCapability
 */
 - (void)removeParticipant:(CSMessagingParticipant *)messagingParticipant completionHandler:(CSMessagingParticipantsChangedCompletionHandler)handler;


/**
 * Adds participants
 *
 * @param participantsToAdd NSArray of CSMessagingParticipant(s) to add
 * @param handler The completion handler associated with this operation
 *
 * @see #addParticipantsCapability
 */
- (void)addParticipants:(NSArray *)participantsToAdd completionHandler:(CSMessagingParticipantsChangedCompletionHandler)handler;

/**
 * Starts the retrieval of messages associated with this conversation. This initial retrieval
 * represents the most recent messages in the conversation and is limited to a maximum number
 * that is specified by the messaging server. This is not necessarily the entire historical
 * message content of the conversation.
 *
 * This method begins the retrieval of the dynamically-updated collection of messages
 * associated with this conversation. Normally the client application will only need to call
 * this method once to install a watcher object to monitor the initial download of messages and
 * then continue to watch for updates to the collection.
 *
 * If older messages are required to be downloaded,
 * the #retrieveMessagesBeforeMessage:maxCount: and/or
 * #retrieveMessagesAfterMessage:maxCount:] methods can be used
 * to retrieve additional message history. Note, however, that #retrieveMessagesWithWatcher: must be called
 * first to install the {@link CSDataRetrievalWatcher} object that will monitor the retrieval,
 * since these other methods work on a shared collection managed internally by the
 * CSMessagingConversation object. The application should use the
 * ::CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems:
 * callback to build up and maintain a local collection of messages associated with this conversation.
 *
 * When using these message retrieval methods, it is important to note that there can only
 * be a single retrieval operation in progress at any given time. If there is a retrieval
 * operation in progress when once of these three message retrieval methods are called, the
 * currently running retrieval will be cancelled before starting the next operation.
 *
 * If the client application calls this method additional times, no actual download of
 * messages from the server occurs, but the watcher listener callbacks that report progress
 * will fire (i.e. "progress" and "done" callbacks). However, no additions to the message
 * collection will occur as a result of the subsequent calls. If a different watcher object
 * is supplied in a subsequent call, the previous watcher object is "unlinked" from the
 * underlying message object collection and will never receive any additional updates.
 *
 * @param watcher {@link CSDataRetrievalWatcher} object, created by the application,
 *        to track the progress of the requested operation.
 *
 * @see #retrieveMessagesBeforeMessage:maxCount:
 * @see #retrieveMessagesAfterMessage:maxCount:
 */
- (void)retrieveMessagesWithWatcher:(CSDataRetrievalWatcher *)watcher;

/**
 * Retrieves a list of the conversation messages after the specified message. This list
 * represents a list of contiguous messages which have been, or are being, downloaded.
 *
 * This method is used in conjunction with the #retrieveMessagesWithWatcher:
 * method to retrieve older message content associated with the conversation. Please refer to
 * the description of that method for detailed usage information.
 *
 * To determine when it is appropriate to call the retrieveMessagesAfter method, the client
 * application should query the #olderContentCapability method.
 *
 * @param maxMessagesToRetrieve the maximum number of messages to retrieve. The actual number
 *                 retrieved may be less than this if the maximum number
 *                 of messages allowed per retrieval request, as configured on
 *                 the server, is less than the specified value, or if the end
 *                 of the message list is reached.
 * @param message the starting point in the retrieval. Messages immediately
 *                after this one will be retrieved.
 *
 * @see #retrieveMessagesWithWatcher:
 * @see #retrieveMessagesBeforeMessage:maxCount:
 */
- (void)retrieveMessagesAfterMessage:(CSMessage *)message maxCount:(NSUInteger)maxMessagesToRetrieve;

/**
 * Retrieves a list of the conversation messages before the specified message. This list
 * represents a list of contiguous messages which have been, or are being, downloaded.
 *
 * This method is used in conjunction with the #retrieveMessagesWithWatcher:
 * method to retrieve older message content associated with the conversation. Please refer to
 * the description of that method for detailed usage information.
 *
 * To determine when it is appropriate to call the retrieveMessagesBefore method, the client
 * application should query the #olderContentCapability method.
 *
 * @param maxMessagesToRetrieve The maximum number of messages to retrieve. The actual number
 *                 retrieved may be less than this if the maximum number
 *                 of messages allowed per retrieval request, as configured
 *                 on the server is less than the specified value, or if the
 *                 start of the message list is reached.
 * @param message the starting point in the retrieval. Messages immediately
 *                before this one will be retrieved.
 *
 * @see #retrieveMessagesWithWatcher:
 * @see #retrieveMessagesAfterMessage:maxCount:
 */
- (void)retrieveMessagesBeforeMessage:(CSMessage *)message maxCount:(NSUInteger)maxMessagesToRetrieve;

#ifdef DATASET_SUPPORTED
/**
 * Retrieve conversation messages.
 *
 * @return CSDataRetrieval object associated with this request.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link #retrieveMessagesWithWatcher:} method instead.
 */
- (CSDataRetrieval *)messages DEPRECATED_ATTRIBUTE;

/**
 * Retrieve conversation messages after the specified message.
 *
 * @param message - messages to retrieve after this message.
 * @param maxMessagesToRetrieve - max messages to retrieve.
 * @return CSDataRetrieval object associated with this request.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link #retrieveMessagesAfterMessage:maxCount:} method instead.
 */
- (CSDataRetrieval *)messagesAfterMessage:(CSMessage *)message maxCount:(NSUInteger)maxMessagesToRetrieve DEPRECATED_ATTRIBUTE;

/**
 * Retrieve conversation messages before the specified message.
 *
 * @param message - messages to retrieve before this message .
 * @param maxMessagesToRetrieve - max messages to retrieve.
 * @return CSDataRetrieval object associated with this request.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link #retrieveMessagesBeforeMessage:maxCount:} method instead.
 */
- (CSDataRetrieval *)messagesBeforeMessage:(CSMessage *)message maxCount:(NSUInteger)maxMessagesToRetrieve DEPRECATED_ATTRIBUTE;
#endif

/**
 * Invokes a set last access time request for this conversation.
 *
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 *
 * @see #updateLastAccessedTimeCapability
 * @see #lastAccessDate
 */
- (void)updateLastAccessTimeWithCompletionHandler:(CSMessagingCompletionHandler)handler;
	
/**
 * Sets the subject for this conversation.
 *
 * @param subject the new subject of this conversation.
 * @param handler The Application/client context associated with this operation
 *
 * @see #updateSubjectCapability
 */
- (void)setSubject:(NSString *)subject completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Set conversation sensitivity level
 *
 * @param sensitivity {@link CSMessagingSensitivityLevel} the new conversation sensitivity.
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 *
 * @see #updateSensitivityCapability
 */
- (void)setSensitivity:(CSMessagingSensitivityLevel)sensitivity completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Sets the conversation type.
 *
 * @param type {@link CSMessagingConversationType} the new conversation type.
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 *
 * @see #updateTypeCapability
 */
- (void)setType:(CSMessagingConversationType)type completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Invokes a leave request for this conversation.
 *
 * After leaving, participant can no longer contribute to the conversation unless he is added once again.
 *
 * When last participant is leaving the conversation it will become closed after a while.
 *
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 *
 * @see #leaveCapability
 */
- (void)leaveWithCompletionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Clear conversation local attachment data.
 *
 * This method clears only application data and it is not applicable to any content downloaded to a user’s device.
 *
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 */
- (void)clearLocalAttachmentDataWithCompletionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Marks all content in this conversation as read.
 *
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 * @see -[markAllContentAsReadCapability]
 */
- (void)markAllContentAsReadWithCompletionHandler:(CSMessagingCompletionHandler)handler;

/**
 * A {@link CSCapability} object that indicates if the subject property of the
 * conversation can be updated.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports changing the subject of a conversation.
 * @li The conversation is active and is not transitioning between draft and published states.
 * @li The conversation is not currently being left.
 *
 * @see #setSubject:completionHandler:
 * @see #active
 */
@property (nonatomic, readonly) CSCapability *updateSubjectCapability;

/**
 * A {@link CSCapability} object that indicates if the type of the conversation can be updated.
 *
 * This capability is currently always disabled because the messaging server only supports conversations
 * of type "thread".
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The conversation is in a published state.
 * @li The conversation is not currently being left.
 *
 * @see #updateLastAccessTimeWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateLastAccessedTimeCapability;

/**
 * A {@link CSCapability} object that indicates if the sensitivity of the conversation can
 * be updated.
 *
 * This capability is @b Allowed when the conversation is in the draft state.
 *
 * @see #setSensitivity:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateSensitivityCapability;

/**
 * A {@link CSCapability} object that indicates if the type of the conversation can be updated.
 *
 * This capability is currently always disabled because the messaging server only supports conversations
 * of type "thread".
 *
 * @see #setType:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateTypeCapability;

/**
 * A {@link CSCapability} object that indicates whether the user can "scroll to get more
 * messages", i.e. there are additional messages not yet downloaded from the server.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The conversation is in the published state.
 * @li The conversation is not currently being left.
 *
 * @see #retrieveMessagesAfterMessage:maxCount:
 * @see #retrieveMessagesBeforeMessage:maxCount:
 */
@property (nonatomic, readonly) CSCapability *olderContentCapability;

/**
 * A {@link CSCapability} object that indicates if new participants can be added to
 * the conversation.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The Conversation is active (see #active).
 *
 * @see #addParticipantAddresses:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *addParticipantsCapability;

/**
 * A {@link CSCapability} object that indicates if participants can be removed from
 * the conversation.
 *
 * This capability is @b Allowed when the conversation is in draft state and is not transitioning
 * to the published state.
 *
 * @see #removeParticipantAddresses:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *removeParticipantsCapability;

/**
 * A {@link CSCapability} object that indicates if a participant can be removed from
 * the conversation.
 *
 * This capability is @b Allowed when one of the following conditions are true:
 *
 * @li This conversation is in the draft state.
 * @li This conversation is published and messaging server allows to remove participants from it.
 *
 * @see #removeParticipant:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *removeParticipantCapability;

/**
 * A {@link CSCapability} object that indicates if a new message can be created in
 * the conversation.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The conversation is in the draft state and has been started or is in the published state.
 * @li The Conversation does not have unsent messages.
 * @li The Conversation is not currently being left.
 *
 * @see #createMessage
 * @see #startWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *createMessageCapability;

/**
 * A {@link CSCapability} object that indicates if all messages in the conversation can
 * be marked as read
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports marking all conversation content as read.
 * @li The conversation is in the published state.
 * @li The conversation is not being left.
 *
 * @see #markAllContentAsReadWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *markAllContentAsReadCapability;

/**
 * A {@link CSCapability} object that indicates if the conversation can be left.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The conversation is in the published state.
 * @li The conversation is not being left.
 *
 * @see #leaveWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *leaveCapability;

/**
 * A {@link CSCapability} object that indicates if the conversation can be started.
 *
 * This capability is @b Allowed when the conversation is in draft state and has not yet been started.
 *
 * @see #startWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *startCapability;

/**
 * A {@link CSCapability} object that indicates if the conversation can be removed.
 *
 * This capability is @b Allowed when the conversation is in draft state.
 *
 * @see ::CSMessagingService::removeConversation:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *removeCapability;

/**
 * A {@link CSCapability} object that indicates if typing status reporting is avaliable.
 */
@property (nonatomic, readonly) CSCapability *isTypingCapability;

/**
 * Returns a capability indicating whether this conversation is capable of reporting read state updates for sent messages.
 *
 * @return A CSCapability indicating whether this conversation is capable of reporting read state updates for sent messages.
 */
@property (nonatomic, readonly) CSCapability *messageReadStateCapability;

/**
 * Returns a capability indicating whether this conversation is capable of reporting delivery state updates for sent messages.
 *
 * @return A CSCapability indicating whether this conversation is capable of reporting delivery state updates for sent messages.
 */
@property (nonatomic, readonly) CSCapability *messageDeliveryStateCapability;

/**
 * A {@link CSMessagingProviderType} object that contains information about source of the conversation.
 */
@property (nonatomic, readonly) CSMessagingProviderType providerType;

@end

/*
 * Protocol of delegate that can be used to retrieve status updates for a conversation. 
 */
@protocol CSMessagingConversationDelegate <NSObject>

/**
 * Called to report that the conversation's active status has changed in response to a local
 * or remote operation.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the active state has changed.
 * @param isActive the new value of the isActive flag.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeActiveStatus:(BOOL)isActive;

/**
 * Called to report that the closed state of the conversation has changed in response to a local
 * or remote operation.
 *
 * @param messagingConversation The conversation for which the the active state changed
 * @param isClosed the new value of the isClosed flag.
 * @see -[CSMessagingConversation closed]
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeClosedStatus:(BOOL)isClosed;

/**
 * Called to report that the isMultiparty state of the conversation has changed in response to
 * new participants being added or existing participants being removed.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the mutliparty state has changed.
 * @param isMultiParty The new value of the isMultiParty flag
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeMultiPartyStatus:(BOOL)isMultiParty;

/**
 * Called to report that the last accessed time of the conversation has changed in response to
 * messages in the conversation being marked as read, or by an explicit invocation of the
 * ::CSMessagingConversation::updateLastAccessTimeWithCompletionHandler: method.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the last accessed time has changed.
 * @param time The new time.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeLastAccessedTime:(NSDate *)time;

/**
 * Called to report that the last updated time of the conversation has changed.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the time has changed.
 * @param time The new time.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeLastUpdatedTime:(NSDate *)time;

/**
 * Called to report that the latest entry time of the conversation has changed in response to
 * new messages being added to the conversation.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the last entry time has changed.
 * @param time The new time.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeLatestEntryTime:(NSDate *)time;

/**
 * Called to report that resource status of the conversation has changed.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the resource status has changed.
 * @param status The new value of the resource status
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeStatus:(CSMessagingConversationStatus)status;

/**
 ** Called to report that the preview text for the conversation has changed.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the preview text has changed.
 * @param previewText The new value of the preview text
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangePreviewText:(NSString *)previewText;

/**
 * Called to report that the total number of messages in the conversation has changed.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the total number of messages has changed.
 * @param totalMsgCount The new value representing the total message count.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeTotalMessageCount:(NSUInteger)totalMsgCount;

/**
 * Called to report that the total number of attachments in the conversation has changed.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the total number of messages has changed.
 * @param totalAttachmentCount The new value representing the total attachment count.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeTotalAttachmentCount:(NSUInteger)totalAttachmentCount;

/**
 * Called to report that the number of unread messages in the conversation has changed.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the total number of messages has changed.
 * @param totalUnreadMsgCount The new value representing the unread message count.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeTotalUnreadMessageCount:(NSUInteger)totalUnreadMsgCount;

/**
 * Called to report that total number of unread attachments in the conversation has changed.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the total number of messages has changed.
 * @param totalUnreadAttachmentCount The new value representing the unread attachment count.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeTotalUnreadAttachmentCount:(NSUInteger)totalUnreadAttachmentCount;

/**
 * Called to report that the sensitivity of the conversation has changed via either a
 * local or remote operation.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the sensitivity has changed.
 * @param sensitivity The new sensitivity's value.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeSensitivity:(CSMessagingSensitivityLevel)sensitivity;

/**
 * Called to report that the subject of the conversation has changed via either a
 * local or remote operation.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the subject has changed.
 * @param subject The new subject's value
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeSubject:(NSString *)subject;

/**
 * Called to report that the type of the conversation has changed. This is called
 * when a user changes the conversation's type.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the subject has changed.
 * @param conversationType The new type's value
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeType:(CSMessagingConversationType)conversationType;

/**
 * Called to report that one or more messages have been added to the conversation.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the messages were added.
 * @param messages The new messages which have been added.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didAddMessages:(NSArray *)messages;

/**
 * Sent to indicate that new messages have been removed from the conversation. This is called
 * when a user removes a message from a conversation. This is generally only avaliable for messages which
 * haven't been reconciled with the server.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the messages were removed.
 * @param messages The new messages which have been removed.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didRemoveMessages:(NSArray *)messages;

/**
 * Called to report that one or more of the capabilities of the conversation has changed.
 * The application should query each of the capabilities and enable/disable elements of the
 * user interface based on the new capability settings. Capabilities can change as a result
 * of local or remote actions.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the callback is associated with.
 *
 * @see ::CSMessagingConversation::updateSubjectCapability
 * @see ::CSMessagingConversation::updateLastAccessedTimeCapability
 * @see ::CSMessagingConversation::updateSensitivityCapability
 * @see ::CSMessagingConversation::updateTypeCapability
 * @see ::CSMessagingConversation::olderContentCapability
 * @see ::CSMessagingConversation::addParticipantsCapability
 * @see ::CSMessagingConversation::removeParticipantsCapability
 * @see ::CSMessagingConversation::createMessageCapability
 * @see ::CSMessagingConversation::markAllContentAsReadCapability
 * @see ::CSMessagingConversation::leaveCapability
 * @see ::CSMessagingConversation::startCapability
 * @see ::CSMessagingConversation::removeCapability
 * @see ::CSMessagingConversation::messageReadStateCapability
 */
- (void)messagingConversationDidChangeCapabilities:(CSMessagingConversation *)messagingConversation;

/**
 * Called to report that one or more participants have been added to the conversation.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the participants were added.
 * @param participants list of {@link CSMessagingParticipant} added to the conversation.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didAddParticipants:(NSArray *)participants;

/**
 * Called to report that one or more participants have been removed from the conversation.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the participants were removed.
 * @param participants the list of {@link CSMessagingParticipant} deleted from the conversation.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didRemoveParticipants:(NSArray *)participants;

@end

@protocol CSMessagingComposingParticipantsWatcherDelegate <NSObject>

/**
 * Sent to indicate that the list of remote participants currently composing
 * a message on this conversation has changed.
 *
 * @param messagingConversation the {@link CSMessagingConversation} for which the composing participants list has changed.
 * @param participants The new list of composing participants.
 */
- (void)messagingConversation:(CSMessagingConversation *)messagingConversation didChangeComposingParticipants:(NSArray *)participants;

@end
