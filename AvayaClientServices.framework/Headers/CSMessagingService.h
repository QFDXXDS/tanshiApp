/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCapability.h"
#import "CSDataRetrievalWatcher.h"
#import "CSMessagingConversation.h"
#import "CSMessagingEnums.h"
#import "CSMessagingQuery.h"
#import "CSMessagingCompletionHandler.h"
#import "CSMessagingLimits.h"

#if TARGET_OS_IPHONE
	#import "CSPushNotificationsEncryptionInfo.h"
#endif

@protocol CSMessagingServiceDelegate;

/**
 * The CSMessagingService object is accessible from the {@link CSUser} object, and
 * provides access to messaging related capabilities and actions.
 *
 * The CSMessagingService object provides a set of APIs that allow
 * application developers to manage text conversations along with rich media attachments.
 *
 * In general, the capabilities and the set of allowed operations
 * are dependent on the capabilities of the messaging server.
 * A messaging conversation doesn't have any moderator once it is started by any user.
 *
 * The client application is notified about status updates reported by the messaging server
 * through delegate that the application has added to the
 * CSMessagingService object. These updates may be the result of local operations
 * on the MessagingService object as well as remote changes initiated by either the server
 * or other participants of any conversation.
 */
@interface CSMessagingService : NSObject

/**
 * The delegate responsible for handling messaging service events.
 */
@property (nonatomic, weak) id<CSMessagingServiceDelegate> delegate;

/**
 * The refresh mode for polling.
 *
 * If there is one messaging provider configured this selector will operate on 
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * Push mode means continuous notifications in real time.
 *
 * @see #refreshWithCompletionHandler:
 */
@property (nonatomic, readonly) CSMessagingRefreshMode refreshMode;

/**
 * Generic list of all routable domains presented as NSStrings.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * This list helps to determine if a specific address can be used within the messaging component.
 *
 * @see ::CSMessagingServiceDelegate::messagingService:didChangeRoutableDomains:
 */
@property (nonatomic, readonly) NSArray *routableDomains;

/**
 * String value containing address of currently logged in user. This value
 * different than in other services.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @return String value containing address of currently logged in user.
 */
@property (nonatomic, readonly) NSString *selfAddress;

/**
 * The number of conversations with unread content for current user.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see ::CSMessagingServiceDelegate::messagingService:didChangeNumberOfConversationsWithUnreadContentSinceLastAccess:
 */
@property (nonatomic, readonly) NSUInteger numberOfConversationsWithUnreadContentSinceLastAccess;

/**
 * The number of conversations with unread content since last access of current user.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see ::CSMessagingServiceDelegate::messagingService:didChangeNumberOfConversationsWithUnreadContent:
 */
@property (nonatomic, readonly) NSUInteger numberOfConversationsWithUnreadContent;

/**
 * A {@link CSCapability} object allowing the client application to determine if it is currently possible to
 * create a new conversation.
 *
 * Typically this capability would only be disabled when the client is offline and cannot access the messaging server.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see #createConversation
 */
@property (nonatomic, readonly) CSCapability *createConversationCapability;

/**
 * A {@link CSCapability} object allowing the client application to determine if it is currently possible to
 * reporting delivery state updates for sent messages.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports send delivery receipts.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 */
@property (nonatomic, readonly) CSCapability *messageDeliveryReadStateMonitoringCapability;

/**
 * A {@link CSCapability} object allowing the client application to determine if it is currently possible to
 * reporting read state updates for sent messages.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports send read receipts.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 */
@property (nonatomic, readonly) CSCapability *messageReadReportingCapability;

/**
 * A {@link CSCapability} object that indicates if conversations can be retrieved from the server.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports retrieving conversations.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see #retrieveActiveConversationsForContact:watcher:
 */
@property (nonatomic, readonly) CSCapability *retrieveConversationCapability;

/**
 * A {@link CSCapability} object that indicates if conversations can be searched.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports searching conversations.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see #searchConversationsWithQuery:watcher:
 */
@property (nonatomic, readonly) CSCapability *searchConversationCapability;

/**
 * A {@link CSCapability} object that indicates if the refresh mode can be changed.
 *
 * This capability is <b>Allowed</b> when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports changing the refresh mode.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see -[setRefreshMode:completionHandler:]
 */
@property (nonatomic, readonly) CSCapability *updateRefreshModeCapability;

/**
 * A {@link CSCapability} object that indicates if participant addresses can be validated.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports validation of participant addresses.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see #validateAddresses:watcher:
 */
@property (nonatomic, readonly) CSCapability *validateParticipantAddressesCapability;

/**
 * A {@link CSCapability} object that indicates if local data can be cleared.
 *
 * This capability is currently always @b Allowed.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see #clearAllLocalDataWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *clearLocalDataCapability;

/**
 * A {@link CSCapability} object that indicates if conversation last access timestamps will be updated automatically.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports automatic update of conversation last access timestamps.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see ::CSMessagingConversation::lastAccessDate
 * @see ::CSMessagingConversation::updateLastAccessTimeWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *automaticallyUpdateLastAccessTimeCapability;

/**
 * Boolean value indicating if last connected messaging service supported message read
 * reporting.
 * @return YES if last connected messaging service supports message read reporting.
 */
@property (nonatomic, readonly, getter=isMessageReadReportingSupported) BOOL messageReadReportingSupported;

/**
 * Boolean value indicating if last connected messaging service supported message delivery
 * read state monitoring.
 * @return YES if messaging service supports delivery read state monitoring.
 */
@property (nonatomic, readonly, getter=isMessageDeliveryReadStateMonitoringSupported) BOOL messageDeliveryReadStateMonitoringSupported;

/**
 * Messaging limits, which contain information about the limits of the messaging component.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 */
@property (nonatomic, readonly) CSMessagingLimits *messagingLimits;

/**
 * A Boolean value indicating whether the messaging service is available.
 *
 * This value is closely connected with capabilities - if the service is not
 * running, usually all of the capabilities related to the service won't be allowed.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see ::CSMessagingServiceDelegate::messagingServiceAvailable:
 * @see ::CSMessagingServiceDelegate::messagingServiceUnavailable:
 */
@property (nonatomic, readonly) BOOL serviceAvailable;

/**
 * Creates a new draft conversation.
 *
 * The client application should query the #createConversationCapability method to determine when
 * it is possible to create a new conversation.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see #createConversationCapability
 * @see ::CSMessagingConversation::startWithCompletionHandler:
 * @see ::CSMessagingConversation::addParticipantAddresses:completionHandler:
 * @see ::CSMessagingConversation::createMessage
 */
- (CSMessagingConversation *)createConversation;

/**
 * Performs a retrieval of all active conversations for the currently logged in user and watches for changes to this collection.
 *
 * This method retrieves the dynamically-updated collection of conversations that are associated with the currently
 * logged in user.
 * Normally the client application will only need to call this method once to install a watcher
 * object to monitor the initial download of conversations and then continue to watch for updates to the collection.
 *
 * If the client application calls this method additional times, no actual download of conversations from the server
 * occurs, but any delegates installed on the *watcher* will receive messages that report progress
 * (i.e. "progress" and "completion" messages).
 * However, no additions to the conversation collection will occur as a result of the subsequent calls.
 * If a different watcher object is supplied in a subsequent call, the previous watcher object is "unlinked" from
 * the underlying conversation object collection and will never receive any additional updates.
 *
 * To determine when it is appropriate to call this method, the client application should
 * query the #retrieveConversationCapability property.
 *
 * @param watcher A CSDataRetrievalWatcher object, created by the application, to track the progress of the conversation retrieval.
 * Prior to calling this method, the application should have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher
 * object to receive notifications on the progress of the retrieval of the conversation collection and subsequent updates to
 * this collection.  A value of *nil* will remove any currently installed watcher object, stopping all notifications from being
 * sent to the previous watcher object.
 * The data items returned to the application via the watcher object will be of type {@link CSMessagingConversation}.
 *
 * @see #retrieveConversationCapability
 */
- (void)retrieveActiveConversationsWithWatcher:(CSDataRetrievalWatcher *)watcher;

/**
 * Searches the user's conversations using specified filter criteria.
 *
 * @param messagingQuery query object on which a search will be done.
 *
 * @param watcher A CSDataRetrievalWatcher object, created by the application, to track the progress of the search.
 * Prior to calling this method, the application should have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher
 * object to receive notifications on the progress of the search.
 * The data items returned to the application via the watcher object will be of type {@link CSMessagingConversation}.
 *
 * @see #searchConversationCapability
 */
- (void)searchConversationsWithQuery:(CSMessagingQuery *)messagingQuery watcher:(CSDataRetrievalWatcher *)watcher;

/**
 * Retrieves the list of active conversations for a specified contact.
 *
 * Note that unlike the {@link #retrieveActiveConversationsWithWatcher:} method, once the data retrieval has completed,
 * no further updates will be received through the supplied watcher argument.
 *
 * To determine when it is appropriate to call this method, the client application should query
 * the {@link #searchConversationCapability} property.
 *
 * @param contact The contact object for which matching conversations are to be retrieved.
 * @param watcher A CSDataRetrievalWatcher object, created by the application, to track the progress of the search.
 * Prior to calling this method, the application should have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher
 * object to receive notifications on the progress of the search.
 * The data items returned to the application via the watcher object will be of type {@link CSMessagingConversation}.
 *
 * @see #searchConversationCapability
 * @see #retrieveActiveConversationsWithWatcher:
 */
- (void)retrieveActiveConversationsForContact:(CSContact *)contact watcher:(CSDataRetrievalWatcher *)watcher;

#ifdef DATASET_SUPPORTED
/**
 * Get conversations
 * @return CSDataRetrieval object associated with this request
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link #retrieveActiveConversationsWithWatcher:} method instead.
 */
- (CSDataRetrieval *)conversations DEPRECATED_ATTRIBUTE;

/**
 * Search conversations
 * @param  messagingQuery - query object for search
 * @return CSDataRetrieval object associated with this request
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link searchConversationsWithQuery:watcher:} method instead.
 */
- (CSDataRetrieval *)searchConversations:(CSMessagingQuery *)messagingQuery DEPRECATED_ATTRIBUTE;

/**
 * Get all conversations for specified contact
 * @param  contact - contact for conversations
 * @return CSDataRetrieval object associated with this request
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link #retrieveActiveConversationsForContact:watcher:} method instead.
 */
- (CSDataRetrieval *)allConversationsForContact:(CSContact *)contact DEPRECATED_ATTRIBUTE;
#endif

/**
 * Perform a manual refresh of messaging data from the server. This method is
 * meant to be used when the RefreshMode parameter is set to manual.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 * @see -[refreshMode]
 */
- (void)refreshWithCompletionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Sets refresh mode with completion handler. Using this method and changing refresh
 * mode will impact how often client gets updates from the server. 
 * 
 * This selector operates on all configured providers.
 *
 * @param refreshMode new refresh type value.
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 */
- (void)setRefreshMode:(CSMessagingRefreshMode)refreshMode completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Validates a list of supplied addresses to determine if they are valid messaging addresses.
 *
 * As the addresses are validated, the 
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * message will be sent to any delegates installed on the supplied *watcher* object.  These messages will provide an array of
 * response objects for each of the addresses validated to indicate the validation results for each of the supplied addresses.
 *
 * @param addresses An array of NSString objects representing the addresses to validate.
 * @param watcher A CSDataRetrievalWatcher object, created by the application, to track the progress of the requested operation.
 * Prior to calling this method, the application should have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher
 * object to receive notifications on the progress of the address validation.
 * The data items returned to the application via the watcher object will be of type {@link CSMessagingAddressValidation}.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see #validateParticipantAddressesCapability
 */
- (void)validateAddresses:(NSArray *)addresses watcher:(CSDataRetrievalWatcher*)watcher;

/**
 * Validates a list of supplied contact to determine if they are valid messaging addresses.
 *
 * As the addresses are validated, the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * message will be sent to any delegates installed on the supplied *watcher* object.  These messages will provide an array of
 * response objects for each of the addresses validated to indicate the validation results for each of the supplied addresses.
 *
 * @param contact Contact object with the addresses to validate.
 * @param watcher A CSDataRetrievalWatcher object, created by the application, to track the progress of the requested operation.
 * Prior to calling this method, the application should have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher
 * object to receive notifications on the progress of the address validation.
 * The data items returned to the application via the watcher object will be of type {@link CSMessagingAddressValidation}.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see #validateParticipantAddressesCapability
 */
- (void)validateAddressesOfContact:(CSContact *)contact watcher:(CSDataRetrievalWatcher*)watcher;

/**
 * Leave a specified list of conversations.
 *
 * As conversations in the supplied list are processed, the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * message will be sent to any delegates installed on the supplied *watcher* object. These messages will provide an array of
 * response objects for each of the conversations that have been left.  In addition, for each conversation that is successfully
 * left, a similar message will be sent to the delegates of the *watcher* object provided by the application via the
 * {@link #retrieveActiveConversationsWithWatcher:} method indicating the deletion of the conversation.
 *
 * @param conversations An array of CSMessagingConversation objects representing the conversations to leave.
 * @param watcher A CSDataRetrievalWatcher object, created by the application, to track the progress of the requested operation.
 * Prior to calling this method, the application should have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher
 * object to receive notifications on the progress leaving the specified conversations.
 * The data items returned to the application via the watcher object will be of type {@link CSMessagingLeaveConversationResponse}.
 *
 * @see #leaveAllConversationsWithWatcher:
 * @see #retrieveActiveConversationsWithWatcher:
 */
- (void)leaveConversations:(NSArray *)conversations watcher:(CSDataRetrievalWatcher *)watcher;

#ifdef DATASET_SUPPORTED
/**
 * Validate users
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @param  addressesToValidate - Array of NSString(s) addresses to validate
 * @return CSDataRetrieval object associated with this request
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link #validateAddresses:watcher:} method instead.
 */
- (CSDataRetrieval *)validateUsers:(NSArray *)addressesToValidate DEPRECATED_ATTRIBUTE;

/**
 * Leave a specified list of conversations.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @param  conversations An array of CSMessagingConversation objects representing the conversations to leave.
 * @return CSDataRetrieval object associated with this request.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link leaveConversations:watcher:} method instead.
 */
- (CSDataRetrieval *)leaveConversations:(NSArray *)conversations DEPRECATED_ATTRIBUTE;
#endif

/**
 * Mark multiple messages as read.
 *
 * @param messages An array of {@link CSMessage} objects to mark as read.
 */
- (void)markMessagesAsRead:(NSArray *)messages;

/**
 * Leave all conversations for the currently logged in user.
 *
 * As each of the user's currently active conversations are processed, the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * message will be sent to any delegates installed on the supplied *watcher* object. These messages will provide an array of
 * response objects for each of the conversations that have been left.  In addition, for each conversation that is successfully
 * left, a similar message will be sent to the delegates of the *watcher* object provided by the application via the
 * {@link #retrieveActiveConversationsWithWatcher:} method indicating the deletion of the conversation.
 *
 * @param watcher A CSDataRetrievalWatcher object, created by the application, to track the progress of the requested operation.
 * Prior to calling this method, the application should have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher
 * object to receive notifications on the progress leaving the specified conversations.
 * The data items returned to the application via the watcher object will be of type {@link CSMessagingLeaveConversationResponse}.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @see #leaveConversations:watcher:
 * @see #retrieveActiveConversationsWithWatcher:
 */
- (void)leaveAllConversationsWithWatcher:(CSDataRetrievalWatcher *)watcher;

#ifdef DATASET_SUPPORTED
/**
 * Leave all conversations for this user
 *
 * This selector operates on all configured providers.
 *
 * @return CSDataRetrieval object associated with this request.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link leaveAllConversationsWithWatcher:} method instead.
 */
- (CSDataRetrieval *)leaveAllConversations DEPRECATED_ATTRIBUTE;
#endif

/**
 * Returns a {@link CSCapability} object that indicates if a specified conversation can be removed.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The conversation argument is a valid Conversation object.
 * @li The Conversation is in a "draft" state.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @return a {@link CSCapability} object that indicates if a specified conversation can be removed.
 *
 * @see #removeConversation:completionHandler:
 */
- (CSCapability *)removeConversationCapability:(CSMessagingConversation *)conversation;

/**
 * Removes a conversation.
 *
 * @param conversation the {@link CSMessagingConversation} to be removed.
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 */
- (void)removeConversation:(CSMessagingConversation *)conversation completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Removes all local data - messages, conversations and attachments.
 *
 * If there is one messaging provider configured this selector will operate on
 * configured provider. Otherwise the {@link CSMessagingProviderType#CSMessagingProviderTypeAvayaMultimediaMessaging}
 * provider will be used.
 *
 * @param  handler {@link CSMessagingCompletionHandler} for this operation.
 * @see -[clearLocalDataCapability]
 */
- (void)clearAllLocalDataWithCompletionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Generic list of all routable domains presented as NSStrings for the provider.
 *
 * This list helps to determine if a specific address can be used within the messaging component.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see ::CSMessagingServiceDelegate::messagingService:didChangeRoutableDomains:
 */
- (NSArray *)routableDomainsForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * String value containing address of currently logged in user for specific provider. This value may be
 * different than in other services.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @return String value containing address of currently logged in user.
 */
- (NSString *)selfAddressForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * The number of conversations with unread content for the provider.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see ::CSMessagingServiceDelegate::messagingService:didChangeNumberOfConversationsWithUnreadContentSinceLastAccess:
 */
- (NSUInteger)numberOfConversationsWithUnreadContentSinceLastAccessForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * The number of conversations with unread content since last access of current user for the provider.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see ::CSMessagingServiceDelegate::messagingService:didChangeNumberOfConversationsWithUnreadContent:
 */
- (NSUInteger)numberOfConversationsWithUnreadContentForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * A {@link CSCapability} object allowing the client application to determine if it is currently possible to
 * create a new conversation for the provider.
 *
 * Typically this capability would only be disabled when the client is offline and cannot access the messaging server.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see #createConversation
 */
- (CSCapability *)createConversationCapabilityForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * A {@link CSCapability} object allowing the client application to determine if it is currently possible to
 * reporting delivery state updates for sent messages for the provider.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server) for the provider.
 * @li The messaging server supports send delivery receipts.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 */
- (CSCapability *)messageDeliveryReadStateMonitoringCapabilityForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * A {@link CSCapability} object allowing the client application to determine if it is currently possible to
 * reporting read state updates for sent messages for the provider.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server) for the provider.
 * @li The messaging server supports send read receipts.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 */
- (CSCapability *)messageReadReportingCapabilityForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * A {@link CSCapability} object that indicates if conversations can be retrieved from the server for the provider.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports retrieving conversations.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see #retrieveActiveConversationsForContact:watcher:
 */
- (CSCapability *)retrieveConversationCapabilityForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * A {@link CSCapability} object that indicates if conversations can be searched within the provider.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports searching conversations.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see #searchConversationsWithQuery:watcher:
 */
- (CSCapability *)searchConversationCapabilityForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * A {@link CSCapability} object that indicates if the refresh mode can be changed for the provider.
 *
 * This capability is <b>Allowed</b> when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports changing the refresh mode.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see -[setRefreshMode:completionHandler:]
 */
- (CSCapability *)updateRefreshModeCapabilityForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * A {@link CSCapability} object that indicates if participant addresses can be validated against the provider database.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports validation of participant addresses.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see #validateAddresses:watcher:
 */
- (CSCapability *)validateParticipantAddressesCapabilityForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * A {@link CSCapability} object that indicates if local data can be cleared for the provider.
 *
 * This capability is currently always @b Allowed.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see #clearAllLocalDataWithCompletionHandler:
 */
- (CSCapability *)clearLocalDataCapabilityForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * A {@link CSCapability} object that indicates if conversation last access timestamps will be updated automatically for the provider.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 *
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports automatic update of conversation last access timestamps.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see ::CSMessagingConversation::lastAccessDate
 * @see ::CSMessagingConversation::updateLastAccessTimeWithCompletionHandler:
 */
- (CSCapability *)automaticallyUpdateLastAccessTimeCapabilityForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * Messaging limits, which contain information about the limits of the messaging provider.
 */
- (CSMessagingLimits *)messagingLimitsForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * A Boolean value indicating whether the messaging provider is available.
 *
 * This value is closely connected with capabilities - if the service is not
 * running, usually all of the capabilities related to the service won't be allowed.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see ::CSMessagingServiceDelegate::messagingServiceAvailable:
 * @see ::CSMessagingServiceDelegate::messagingServiceUnavailable:
 */
- (BOOL)serviceAvailableForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * Creates a new draft conversation for the provider.
 *
 * The client application should query the #createConversationCapability method to determine when
 * it is possible to create a new conversation.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see ::CSMessagingConversation::startWithCompletionHandler:
 * @see ::CSMessagingConversation::addParticipantAddresses:completionHandler:
 * @see ::CSMessagingConversation::createMessage
 */
- (CSMessagingConversation *)createConversationForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * Perform a manual refresh of messaging data from the server. This method is
 * meant to be used when the RefreshMode parameter is set to manual.
 *
 * @param handler {@link CSMessagingCompletionHandler} for this operation.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see -[refreshMode]
 */
- (void)refreshWithCompletionHandler:(CSMessagingCompletionHandler)handler forProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * Validates a list of supplied addresses to determine if they are valid messaging addresses for the specified provider.
 *
 * As the addresses are validated, the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * message will be sent to any delegates installed on the supplied *watcher* object.  These messages will provide an array of
 * response objects for each of the addresses validated to indicate the validation results for each of the supplied addresses.
 *
 * @param addresses An array of NSString objects representing the addresses to validate.
 * @param watcher A CSDataRetrievalWatcher object, created by the application, to track the progress of the requested operation.
 * Prior to calling this method, the application should have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher
 * object to receive notifications on the progress of the address validation.
 * The data items returned to the application via the watcher object will be of type {@link CSMessagingAddressValidation}.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see #validateParticipantAddressesCapability
 */
- (void)validateAddresses:(NSArray *)addresses watcher:(CSDataRetrievalWatcher*)watcher forProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * Validates a list of supplied contact to determine if they are valid messaging addresses for the specified provider.
 *
 * As the addresses are validated, the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * message will be sent to any delegates installed on the supplied *watcher* object.  These messages will provide an array of
 * response objects for each of the addresses validated to indicate the validation results for each of the supplied addresses.
 *
 * @param contact Contact object with the addresses to validate.
 * @param watcher A CSDataRetrievalWatcher object, created by the application, to track the progress of the requested operation.
 * Prior to calling this method, the application should have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher
 * object to receive notifications on the progress of the address validation.
 * The data items returned to the application via the watcher object will be of type {@link CSMessagingAddressValidation}.
 *
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see #validateParticipantAddressesCapability
 */
- (void)validateAddressesOfContact:(CSContact *)contact watcher:(CSDataRetrievalWatcher*)watcher forProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * Removes all local data - messages, conversations and attachments for the specified provider.
 * @param  handler {@link CSMessagingCompletionHandler} for this operation.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see -[clearLocalDataCapability]
 */
- (void)clearAllLocalDataWithCompletionHandler:(CSMessagingCompletionHandler)handler forProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * Gets a {@link CSMessagingConversation} associated with the provider conversation ID.
 *
 * This method can be used to find a conversation object corresponding to push notification.
 *
 * @param providerType type of the provider @{link CSMessagingProviderType}.
 * @param providerConversationId provider level conversation ID.
 * @param handler {@link CSConversationCompletionHandler} for this operation.
 */
- (void)conversationForProviderType:(CSMessagingProviderType)providerType providerConversationId:(NSString *)providerConversationId withCompletionHandler:(CSConversationCompletionHandler)handler;
@end

/**
 * Protocol of delegate that can be used to retrieve status updates from the {@link CSMessagingService}.
 */
@protocol CSMessagingServiceDelegate <NSObject>

/**
 * Report that the messaging service has successfully started or restored.
 *
 * @param messagingService the {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @see -[messagingServiceUnavailable]
 * @see -[CSMessagingService serviceAvailable]
 */
- (void)messagingServiceAvailable:(CSMessagingService *)messagingService;

/**
 * Report that the messaging service has been successfully closed or its
 * work was interrupted, for example by a network or server problem.
 *
 * @param messagingService the {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @see -[messagingServiceAvailable]
 * @see -[CSMessagingService serviceAvailable]
 */
- (void)messagingServiceUnavailable:(CSMessagingService *)messagingService;

/**
 * Report that messaging service capabilities have changed.
 *
 * @param messagingService the {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @see -[CSMessagingService createConversationCapability]
 * @see -[CSMessagingService retrieveConversationCapability]
 * @see -[CSMessagingService searchConversationCapability]
 * @see -[CSMessagingService updateRefreshModeCapability]
 * @see -[CSMessagingService validateParticipantAddressesCapability]
 * @see -[CSMessagingService clearLocalDataCapability]
 * @see -[CSMessagingService automaticallyUpdateLastAccessTimeCapability]
 * @see -[CSMessagingService removeConversationCapability]
 */
- (void)messagingServiceDidChangeCapabilities:(CSMessagingService *)messagingService;

/**
 * Called to report that the messaging limits have changed.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingLimits The updated limits.
 *
 * @see ::CSMessagingService::messagingLimits
 */
- (void)messagingService:(CSMessagingService *)messagingService didChangeMessagingLimits:(CSMessagingLimits *)messagingLimits;

/**
 * Called to report that messaging routable domains have changed.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param supportedDomains List of routable domains.
 *
 * @see ::CSMessagingService::routableDomains
 */
- (void)messagingService:(CSMessagingService *)messagingService didChangeRoutableDomains:(NSArray *)supportedDomains;

/**
 * Called to report that a NumberOfConversationsWithUnreadContent has changed.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param numberOfConversationsWithUnreadContent The number of conversations with unread content.
 *
 * @see ::CSMessagingService::numberOfConversationsWithUnreadContent
 */
- (void)messagingService:(CSMessagingService *)messagingService didChangeNumberOfConversationsWithUnreadContent:(NSUInteger)numberOfConversationsWithUnreadContent;

/**
 * Called to report that the NumberOfConversationsWithUnreadContentSinceLastAccess has changed.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param numberOfConversationsWithUnreadContentSinceLastAccess The number representing the number of conversations with unread content since the last time the user accessed them
 *
 * @see ::CSMessagingService::numberOfConversationsWithUnreadContent
 */
- (void)messagingService:(CSMessagingService *)messagingService didChangeNumberOfConversationsWithUnreadContentSinceLastAccess:(NSUInteger)numberOfConversationsWithUnreadContentSinceLastAccess;

/**
 * Called to report that messaging has failed.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param error The messaging fail reason
 */
- (void)messagingService:(CSMessagingService *)messagingService didFailWithError:(NSError *)error;

@optional // These are additions for multiple providers in messaging service support.

/**
 * Report that the messaging provider has successfully started or restored.
 *
 * @param messagingService the {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see -[messagingServiceUnavailable]
 * @see -[CSMessagingService serviceAvailable]
 */
- (void)messagingService:(CSMessagingService *)messagingService providerAvailable:(CSMessagingProviderType)messagingProviderType;

/**
 * Report that the messaging provider has been successfully closed or its
 * work was interrupted, for example by a network or server problem.
 *
 * @param messagingService the {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see -[messagingServiceAvailable]
 * @see -[CSMessagingService serviceAvailable]
 */
- (void)messagingService:(CSMessagingService *)messagingService providerUnavailable:(CSMessagingProviderType)messagingProviderType;

/**
 * Report that messaging provider capabilities have changed.
 *
 * @param messagingService the {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @see -[CSMessagingService createConversationCapability]
 * @see -[CSMessagingService retrieveConversationCapability]
 * @see -[CSMessagingService searchConversationCapability]
 * @see -[CSMessagingService updateRefreshModeCapability]
 * @see -[CSMessagingService validateParticipantAddressesCapability]
 * @see -[CSMessagingService clearLocalDataCapability]
 * @see -[CSMessagingService automaticallyUpdateLastAccessTimeCapability]
 * @see -[CSMessagingService removeConversationCapability]
 */
- (void)messagingService:(CSMessagingService *)messagingService providerDidChangeCapabilities:(CSMessagingProviderType)messagingProviderType;

/**
 * Called to report that the messaging provider limits have changed.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @param messagingLimits The updated limits.
 *
 * @see ::CSMessagingService::messagingLimits
 */
- (void)messagingService:(CSMessagingService *)messagingService provider:(CSMessagingProviderType)messagingProviderType didChangeMessagingLimits:(CSMessagingLimits *)messagingLimits;

/**
 * Called to report that messaging provider routable domains have changed.
 * This is not supported for Zang provider.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @param supportedDomains List of routable domains.
 *
 * @see ::CSMessagingService::routableDomains
 */
- (void)messagingService:(CSMessagingService *)messagingService provider:(CSMessagingProviderType)messagingProviderType didChangeRoutableDomains:(NSArray *)supportedDomains;

/**
 * Called to report that a NumberOfConversationsWithUnreadContent has changed for the provider.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @param numberOfConversationsWithUnreadContent The number of conversations with unread content.
 *
 * @see ::CSMessagingService::numberOfConversationsWithUnreadContent
 */
- (void)messagingService:(CSMessagingService *)messagingService provider:(CSMessagingProviderType)messagingProviderType didChangeNumberOfConversationsWithUnreadContent:(NSUInteger)numberOfConversationsWithUnreadContent;

/**
 * Called to report that the NumberOfConversationsWithUnreadContentSinceLastAccess has changed for the provider.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @param numberOfConversationsWithUnreadContentSinceLastAccess The number representing the number of conversations with unread content since the last time the user accessed them
 *
 * @see ::CSMessagingService::numberOfConversationsWithUnreadContent
 */
- (void)messagingService:(CSMessagingService *)messagingService provider:(CSMessagingProviderType)messagingProviderType didChangeNumberOfConversationsWithUnreadContentSinceLastAccess:(NSUInteger)numberOfConversationsWithUnreadContentSinceLastAccess;

/**
 * Called to report that provider has failed.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @param error The messaging fail reason
 */
- (void)messagingService:(CSMessagingService *)messagingService provider:(CSMessagingProviderType)messagingProviderType didFailWithError:(NSError *)error;

@optional // These are being deprecated.

/**
 * Called to report the messaging participant matched contacts changed.
 *
 * This could be a result of change on contact list (i.e. a new contact was added which
 * was present in an existing conversation). The matched contact can be used for an additional
 * operation, which is not available on the messaging participant - for example making a call, etc.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 */
- (void)messagingServiceParticipantMatchedContactsChanged:(CSMessagingService *)messagingService;

/**
 * Sent to indicate that conversations are added
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param addedConversations The conversations which got added
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Applications should use a CSDataRetrievalWatcher object passed to the CSMessagingService::retrieveActiveConversationsWithWatcher: method
 *             to be notified of new conversations instead.
 */
- (void)messagingService:(CSMessagingService *)messagingService didAddConversations:(NSArray *)addedConversations
	DEPRECATED_MSG_ATTRIBUTE("Use CSDataRetrievalWatcher instead.");

/**
 * Sent to indicate that conversations are removed
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param removedConversations The conversations which got removed
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Applications should use a CSDataRetrievalWatcher object passed to the CSMessagingService::retrieveActiveConversationsWithWatcher: method
 *             to be notified of removed conversations instead.
 */
- (void)messagingService:(CSMessagingService *)messagingService didRemoveConversations:(NSArray *)removedConversations
	DEPRECATED_MSG_ATTRIBUTE("Use CSDataRetrievalWatcher instead.");

#if defined PLATFORM_IOS
/**
 * Sent when the push notification for messaging provider is enabled.
 * This is not supported for Zang provider.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 */
- (void)messagingService:(CSMessagingService *)messagingService didEnablePushNotificationsForProviderType:(CSMessagingProviderType)messagingProviderType;

/**
 * Sent when the push notification for messaging provider is disabled.
 * For example, messaging notifications are disabled when a user
 * logs out.
 * This is not supported for Zang provider.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 */

- (void)messagingService:(CSMessagingService *)messagingService didDisablePushNotificationsForProviderType:(CSMessagingProviderType)messagingProviderType;
/**
 * Sent when the ClientSDK is unable to enable the messaging push notification
 * successfully.  The failure may be due to an issue on the network server side
 * or local.  For example, an error is reported when connectivity to the
 * messaging push notification network server is lost, or when the push notification could
 * not be enabled due to missing or invalid configuration information.
 * This is not supported for Zang provider.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @param error Error object describing the reason for the failure.
 * @param willRetry Boolean indicating whether service reactivation is
 * automatically reattempted by the ClientSDK.
 */
- (void)messagingService:(CSMessagingService *)messagingService didFailToEnablePushNotificationsForProviderType:(CSMessagingProviderType)messagingProviderType error:(NSError *)error willRetry:(BOOL)willRetry;

/**
 * Sent when the ClientSDK is unable to disable the messaging push notification
 * successfully.  The failure may be due to an issue on the network server side
 * or local.  For example, an error is reported when connectivity to the
 * messaging push notification network server is lost, or when the push notification could
 * not be disabled due to missing or invalid configuration information.
 * This is not supported for Zang provider.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 * @param error Error object describing the reason for the failure.
 * @param willRetry Boolean indicating whether service deactivation is
 * automatically reattempted by the ClientSDK. Currently, service deactivation
 * is not reattempted by the ClientSDK.
 */
-(void)messagingService:(CSMessagingService *)messagingService didFailToDisablePushNotificationsForProviderType:(CSMessagingProviderType)messagingProviderType error:(NSError *)error willRetry:(BOOL)willRetry;

/**
 * Sent after the encryption key is received from the messaging server.
 * This method is normally called after ClientSDK calls didEnablePushNotification() to inform that
 * the push notification is now active.
 * This is not supported for Zang provider.
 *
 * @param messagingService The {@link CSMessagingService} object that the
 *                         callback is associated with.
 * @param encryptionInfo Encryption information received from the server.
 * @param messagingProviderType type of the provider @{link CSMessagingProviderType}.
 */
- (void)messagingService:(CSMessagingService *)messagingService didReceivePushNotificationsEncryptionInfo:(CSPushNotificationsEncryptionInfo *)encryptionInfo forProviderType:(CSMessagingProviderType)messagingProviderType;
#endif
@end
