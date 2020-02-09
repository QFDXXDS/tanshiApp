/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCapability.h"
#import "CSMessagingEnums.h"
#import "CSMessagingParticipant.h"
#import "CSMessagingAttachment.h"
#import "CSMessagingCompletionHandler.h"

@protocol CSMessageDelegate;

/**
 * Interface for all Message related tasks and properties.
 *
 * Message is a crucial part of the conversation. It can store not only text content or attachments,
 * but is also used to inform about any event that occurred in the conversation, like a new participant or
 * subject change. It is important to notice that the body cannot be empty for a usual message,
 * unless an attachment is present.
 *
 * To create a new message, call the {@link CSMessagingConversation::createMessage -[CSMessagingConversation createMessage]} method,
 * which will return a new object. After filling out the message and its other parameters,
 * use the {@link sendWithCompletionHandler:} operation in order to send a message.
 *
 * An important part of the message is also attachments. In order to create a new attachment
 * in a message object, use the {@link createAttachment} method.
 *
 * Besides normal messages with text body there are also messages informing about events.
 * {@link CSMessagingType} is informing about an event type and these objects do not contain any text body.
 * They can have some additional data about an event, i.e. {@link addedParticipants}, {@link removedParticipants}, etc.
 */
@interface CSMessage : NSObject

/**
 * The delegate responsible for handling message-related events.
 */
@property (nonatomic, weak) id<CSMessageDelegate> delegate;

/**
 * The unique message identifier.
 */
@property (nonatomic, readonly) NSString *messageId;

/**
 * This is the message ID from the underlying provider (e.g., the AMM server) as-is.
 * It will be consistent across clients and application launches, but is only
 * guaranteed to be unique for messages of that provider type. It will be empty for draft
 * message.
 */
@property (nonatomic, readonly) NSString *providerMessageId;

/**
 * The message type.
 */
@property (nonatomic, readonly) CSMessagingType type;

/**
 * Message reason type (specific to ::CSMessagingTypeClosed and ::CSMessagingTypeLeft message types)
 *
 * @b CSMessagingTypeClosed: Reason type of conversation close event.
 * @li ::CSMessagingReasonTypeManual: The conversation was closed by participant.
 * @li ::CSMessagingReasonTypeAuto: The conversation was closed by the system (e.g. auto-closed after 30 days of inactivity).
 *
 * @b CSMessagingTypeLeft: Reason type of participants leave event.
 * @li ::CSMessagingReasonTypeManual: Participant left on their own.
 * @li ::CSMessagingReasonTypeAuto: There was some problem to communicate external user (user does not exist, or unavailable, or some other error).
 *           Such leave reason should display an error message like "[username] is unreachable/unable to join"
 *           rather than regular "[username] left the conversation".
 */
@property (nonatomic, readonly) CSMessagingReasonType reasonType;

/**
 * The messaging provider type (AMM, Zang).
 */
@property (nonatomic, readonly) CSMessagingProviderType providerType;

/**
 * The message status.
 */
@property (nonatomic, readonly) CSMessagingMessageStatus status;

/**
 * The subject of the conversation at the time the message was sent.
 *
 * @see ::CSMessagingConversation::subject
 */
@property (nonatomic, readonly) NSString *subject;

/**
 * The body of the message.
 *
 * @see #setBodyAndReportTyping:completionHandler:
 */
@property (nonatomic, readonly) NSString *body;

/**
 * The unique identifier of the conversation to which this message belongs.
 *
 * @see ::CSMessagingConversation::conversationId
 */
@property (nonatomic, readonly) NSString *conversationId;

/**
 * The date and time that the message was last modified.
 */
@property (nonatomic, readonly) NSDate *lastModifiedDate;

/**
 * The date and time that the message was received.
 */
@property (nonatomic, readonly) NSDate *receivedDate;

/**
 * Returns the coalesced status of the message, which is defining if two consecutive messages can be merged.
 *
 * Message is coalesced if:
 * @li There is a previous message.
 * @li This and the previous message have both been published.
 * @li This and the previous message are from the same participant.
 * @li This and the previous message have no attachments.
 * @li This and the previous message have the same sensitivity setting.
 * @li This message was sent no longer than 1 minute after the previous message.
 * @li Has the same sensitivity as previous message.
 * @li Was sent not longer than 1 minute after previous message.
 *
 * @return The coalesced status of the message.
 *
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 */
@property (nonatomic, readonly, getter=isCoalesced) BOOL coalesced DEPRECATED_ATTRIBUTE;

/**
 * A Boolean value indicating whether the current user is the sender of the message.
 */
@property (nonatomic, readonly, getter=isFromMe) BOOL fromMe;

/**
 * A Boolean value indicating if the message has one or more attachments.
 *
 * @see #attachments
 * @see #createAttachment
 * @see #removeAttachment:completionHandler:
 */
@property (nonatomic, readonly) BOOL hasAttachment;

/**
 * A Boolean value indicating if the message has a least one attachment that has not been viewed.
 *
 * @see #attachments
 */
@property (nonatomic, readonly) BOOL hasUnreadAttachment;

/**
 * A Boolean value indicating if the message has an in-reply-to message (does not mean it is in cache).
 */
@property (nonatomic, readonly) BOOL hasInReplyTo;

/**
 * A Boolean value indicating if the message is marked as a private message.
 *
 * @see #sensitivity
 */
@property (nonatomic, readonly, getter=isPrivateMessage) BOOL privateMessage;

/**
 * The do-not-forward status of the message, which indicates if the sender
 * of this message had disallowed forwarding of this particular message.
 */
@property (nonatomic, readonly) BOOL doNotForward;

/**
 * A Boolean value indicating if the message has been read.
 *
 * @see #markAsRead
 * @see ::CSMessagingConversation::markAllContentAsReadWithCompletionHandler:
 * @deprecated This method is deprecated. Use ReadState instead.
 */
@property (nonatomic, readonly, getter=isRead) BOOL read DEPRECATED_ATTRIBUTE;

/**
 * Get message Read state
 * 
 * @return Read state (eg. Unknown, NotRead, Read, PartiallyRead)
 * 
 * @see ::CSMessagingMessageReadState
 * @see ::CSMessagingConversation::messageReadStateCapability
 */
@property (nonatomic, readonly) CSMessagingMessageReadState readState;


/**
 * The message delivery state describing whether this message is sent or delivered to one or more recipients.
 * 
 * Delivery state will not update from Sent to Delivered in case MessageDeliveryReadStateMonitoring is disabled or not supported by messaging server.
 * @return Delivery state (eg. Unsent, Sent, Delivered).
 * 
 * @see ::CSMessagingMessageDeliveryState
 * @see ::CSMessagingConversation::messageDeliveryStateCapability
 */
@property (nonatomic, readonly) CSMessagingMessageDeliveryState deliveryState;
/**
 * The participant who sent the message.
 *
 * @see #recipients
 */
@property (nonatomic, readonly) CSMessagingParticipant *fromParticipant;

/**
 * The attachments for this message.
 *
 * @see #createAttachment
 * @see #removeAttachment:completionHandler:
 */
@property (nonatomic, readonly) NSArray *attachments;

/**
 * The message importance.
 */
@property (nonatomic, readonly) CSMessagingImportance importance;

/**
 * The message sensitivity.
 */
@property (nonatomic, readonly) CSMessagingSensitivityLevel sensitivity;

/**
 * When the message type is ::CSMessagingTypeJoined, this property returns the list of participants
 * that were added to the conversation.
 *
 * Property of incoming messages only.
 *
 * @return When the message type is ::CSMessagingTypeJoined, this property returns the list
 *         of participants that were added to the conversation.
 *
 * @see #type
 */
@property (nonatomic, readonly) NSArray *addedParticipants;

/**
 * When the message type is ::CSMessagingTypeLeft, this property returns the list of participants
 * that were removed from the conversation.
 *
 * Property of incoming messages only.
 *
 * @return When the message type is ::CSMessagingTypeLeft, this property returns the list
 *         of participants that were removed from the conversation.
 *
 * @see #type
 */
@property (nonatomic, readonly) NSArray *removedParticipants;

/**
 * The list of participants, including the sender, that the message was sent to.
 *
 * Property of incoming messages only.
 *
 * @return The list of {@link CSMessagingParticipant CSMessagingParticipants}, including the sender, that the message was
 *         sent to.
 *
 * @see #fromParticipant
 * @see #fromMe
 */
@property (nonatomic, readonly) NSArray *recipients;

/**
 * Invokes a send request for this message.
 *
 * @param handler The completion handler for this operation.
 *
 * @see #sendCapability
 */
- (void)sendWithCompletionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Sets the body of the draft message and the "is typing" chat state.
 *
 * @param messageBody The body of the message.
 * @param handler The completion handler associated with this operation.
 */
- (void)setBodyAndReportTyping:(NSString *)messageBody completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Sets or clears the "is typing" chat state.  This is a "fire and forget" operation.
 *
 * @param typing YES to indicate that the user is typing, NO if not.
 */
- (void)reportTyping:(BOOL)typing;

/**
 * Sets the in-reply-to message for draft message.
 *
 * @param inReplyToMessage The in-reply-to message of this draft message.
 * @param handler The completion handler associated with this operation.
 */
- (void)setInReplyTo:(CSMessage *)inReplyToMessage completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Gets the in-reply-to message of this message.
 *
 * @param handler The completion handler associated with this operation.
 */
- (void)getInReplyToMessageWithCompletionHandler:(CSMessagingMessageCompletionHandler)handler;

/**
 * Gets MessageDeliveryDetails or error. Delivery details are returned via completion handler.
 *
 * @param handler The completion handler associated with this operation.
 */
- (void)getDeliveryDetailsWithCompletionHandler:(CSMessagingMessageDeliveryDetailsCompletionHandler)handler;

/**
 * Sets the do-not-forward state for the message.
 *
 * @param doNotForward The new do-not-forward status of the message.
 * @param handler The completion handler associated with this operation.
 */
- (void)setDoNotForward:(BOOL)doNotForward completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Sets the importance of the message.
 *
 * @param importance The new importance of the message.
 * @param handler The completion handler associated with this operation.
 */
- (void)setImportance:(CSMessagingImportance)importance completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Marks this message as read.
 */
- (void)markAsRead;

/**
 * Creates a ::CSMessagingAttachment for this message.
 *
 * @return A new ::CSMessagingAttachment object for this message that is in the draft state.
 *
 * @see #createAttachmentCapability
 * @see #attachments
 * @see #removeAttachment:completionHandler:
 */
- (CSMessagingAttachment *)createAttachment;

/**
 * Removes a specified attachment from this message.
 *
 * @param attachment The ::CSMessagingAttachment to remove from the message.
 * @param handler The completion handler associated with this operation.
 */
- (void)removeAttachment:(CSMessagingAttachment *)attachment completionHandler:(CSMessagingCompletionHandler)handler;

/**
 * Returns a ::CSCapability object that indicates if the body text or "is typing" status of the
 * message can be updated.
 *
 * This capability is @b Allowed when the message has not yet been sent, or a send failure has occurred.
 *
 * @return A ::CSCapability object that indicates if the body text or "is typing" status of
 *         the message can be updated.
 *
 * @see #setBodyAndReportTyping:completionHandler:
 * @see #reportTyping:
 */
@property (nonatomic, readonly) CSCapability *updateBodyCapability;

/**
 * Returns a ::CSCapability object that indicates if the in-reply-to attribute of the message
 * can be updated.
 *
 * This capability is @b Allowed when the CSMessage has not yet been sent, or a send failure has occurred.
 *
 * @return A ::CSCapability object that indicates if the in-reply-to attribute of the message
 *         can be updated.
 *
 * @see #setInReplyTo:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateInReplyToCapability;

/**
 * Returns a ::CSCapability object that indicates if the DoNotForward attribute of the message
 * can be updated.
 *
 * This capability is @b Allowed when the Message has not yet been sent, or a send failure has occurred.
 *
 * @return A ::CSCapability object that indicates if the DoNotForward attribute of the message
 *         can be updated.
 *
 * @see #setDoNotForward:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateDoNotForwardCapability;

/**
 * Returns a ::CSCapability object that indicates if the importance attribute of the message
 * can be updated.
 *
 * This capability is @b Allowed when the message has not yet been sent, or a send failure has occurred.
 *
 * @return A ::CSCapability object that indicates if the Importance attribute of the message
 *         can be updated.
 *
 * @see #setImportance:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateImportanceCapability;

/**
 * Returns a ::CSCapability object that indicates if an attachment can be added to the message.
 *
 * This capability is @b Allowed when the Message has not yet been sent, or a send failure has occurred.
 *
 * @return A ::CSCapability object that indicates if an attachment can be added to the message.
 *
 * @see #createAttachment
 */
@property (nonatomic, readonly) CSCapability *createAttachmentCapability;

/**
 * Returns a ::CSCapability object that indicates if the message can be sent.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 * @li The messaging service is online (has an active connection to the server).
 * @li The message has not yet been sent, or a send failure has occurred.
 * @li The message has no body text or the messaging server supports the sending of
 * messages containing text.
 * @li The message has body text whose length does not exceed the maximum text length set on the messaging server.
 * @li The message has no attachments or the messaging server supports the sending of
 * messages having attachments.
 * @li The message has no "thumbnail" attachments or the messaging server supports the sending of
 * messages having "thumbnail" attachments.
 *
 * @return A ::CSCapability object that indicates whether the message can be sent.
 *
 * @see #sendWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *sendCapability;

/**
 * Returns a ::CSCapability object that indicates if the message can be marked as read.
 *
 * This capability is @b Allowed when all of the following conditions are true:
 * @li The messaging service is online (has an active connection to the server).
 * @li The messaging server supports marking messages as read.
 * @li The Message is in the published state or the conversation of which the message is a part is inactive.
 *
 * @return A ::CSCapability object that indicates whether the message can be marked as read.
 *
 * @see #markAsRead:
 */
@property (nonatomic, readonly) CSCapability *markAsReadCapability;

/**
 * Returns a ::CSCapability object that indicates if the message can be removed.
 *
 * This capability is @b Allowed when the Message has not yet been sent, or a send failure has occurred.
 *
 * @return A ::CSCapability object that indicates if the message can be removed.
 *
 * @see ::CSMessagingConversation::removeMessage:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *removeCapability;

/**
 * Returns a ::CSCapability object that indicates if the message can provide its delivery details.
 *
 * @return A ::CSCapability object that indicates if the message can provide its delivery details.
 */
@property (nonatomic, readonly) CSCapability *deliveryDetailsCapability;

/**
 * The participant is the initiator of an event message, such as LEFT message
 * when a participant is removed from a conversation by other participant(initiator)
 */
@property (nonatomic, readonly) CSMessagingParticipant *initiatorParticipant;

@end

/**
 * Delegate that can be used to retrieve status updates for a message. Delegate can be
 * registered to retrieve status updates on the messages’ various attributes.
 */
@protocol CSMessageDelegate <NSObject>

/**
 * Called to report that the message's body text has changed in response to a local
 * ::CSMessage::setBodyAndReportTyping:completionHandler: operation.
 *
 * @param message The message for which the body has changed.
 * @param body the new value of the body.
 *
 * @see ::CSMessage::body
 */
- (void)message:(CSMessage *)message didChangeBody:(NSString *)body;

/**
 * Called to report that the message's in-reply-to attribute has changed in response to a local
 * ::CSMessage::setInReplyTo:completionHandler: operation.
 *
 * @param message The message for which the in-reply-to attribute has changed.
 * @param newMessage The new in-reply-to message.
 *
 * @see ::CSMessage::hasInReplyTo
 * @see ::CSMessage::getInReplyToMessageWithCompletionHandler:
 */
- (void)message:(CSMessage *)message didChangeInReplyTo:(CSMessage *)newMessage;

/**
 * Called to report that the last modified date attribute of the message has changed.
 *
 * @param message The message for which the last modified date has changed.
 * @param date The new date.
 *
 * @see CSMessage::lastModifiedDate
 */
- (void)message:(CSMessage *)message didChangeLastModifiedDate:(NSDate *)date;

/**
 * Called to report that the list of attachments associated with the message has changed.
 *
 * @param message The message for which the hasAttachment has changed.
 * @param hasAttachment The new value of the hasAttachment flag.
 */
- (void)message:(CSMessage *)message didChangeHasAttachmentStatus:(BOOL)hasAttachment;

/**
 * Called to report that the unread attachment status of the message has changed.
 *
 * @param message The {@link CSMessage} for which the unread attachment status has changed.
 * @param hasUnreadAttachment The new value of the hasUnreadAttachment flag.
 *
 * @see ::CSMessage::hasUnreadAttachment
 */
- (void)message:(CSMessage *)message didChangeHasUnreadAttachmentStatus:(BOOL)hasUnreadAttachment;

/**
 * Called to report that the "do not forward" status of the message has changed.
 *
 * @param message The {@link CSMessage} for which the "do not forward" status has changed.
 * @param doNotForward The new value of the do-not-forward flag.
 *
 * @see ::CSMessage::doNotForward
 */
- (void)message:(CSMessage *)message didChangeDoNotForwardStatus:(BOOL)doNotForward;

/**
 * Called to report that the read state of the message has changed.
 *
 * @param message The {@link CSMessage} for which the "read" state has changed.
 * @param state the new value of the read state.
 *
 * @see ::CSMessage::readState
 */
- (void)message:(CSMessage *)message didChangeReadState:(CSMessagingMessageReadState)state;

/**
 * Called to report that the delivery state of the message has changed.
 *
 * @param message The {@link CSMessage} for which the "delivery" state has changed.
 * @param state the new value of the delivery state.
 *
 * @see ::CSMessagingMessageDeliveryState
 */
- (void)message:(CSMessage *)message didChangeDeliveryState:(CSMessagingMessageDeliveryState)state;

/**
 * Called to report that the status of the message has changed.
 *
 * @param message The {@link CSMessage} for which the status has changed.
 * @param status The new value of the message status.
 *
 * @see ::CSMessage::status
 */
- (void)message:(CSMessage *)message didChangeStatus:(CSMessagingMessageStatus)status;

/**
 * Called to report that the importance of the message has changed.
 *
 * @param message The {@link CSMessage} for which the importance has changed.
 * @param importance The new value of the importance level.
 *
 * @see ::CSMessage::importance
 * @see ::CSMessagingImportance
 */
- (void)message:(CSMessage *)message didChangeImportance:(CSMessagingImportance)importance;

/**
 * Called to report that one or more of the capabilities of the message has changed.
 * The application should query each of the capabilities and enable/disable elements of the
 * user interface based on the new capability settings. Capabilities can change as a result
 * of local or remote actions.
 *
 * @param message The {@link CSMessage} that the callback is associated with.
 *
 * @see ::CSCapability
 * @see ::CSMessage::removeCapability
 * @see ::CSMessage::createAttachmentCapability
 * @see ::CSMessage::markAsReadCapability
 * @see ::CSMessage::sendCapability
 * @see ::CSMessage::updateBodyCapability
 * @see ::CSMessage::updateDoNotForwardCapability
 * @see ::CSMessage::updateImportanceCapability
 * @see ::CSMessage::updateInReplyToCapability
 */
- (void)messageDidChangeCapabilities:(CSMessage *)message;

@optional

/**
 * Called to report that the message's coalesced status has changed in response to receiving
 * additional messages.
 *
 * @param message The message for which the coalesced status has changed.
 * @param isCoalesced The new value of the isCoalesced flag.
 *
 * @see ::CSMessage::coalesced
 *
 * @deprecated THIS METHOD WILL BE REMOVED IN RELEASE VERSION 3.3.
 */
- (void)message:(CSMessage *)message didChangeIsCoalescedStatus:(BOOL)isCoalesced DEPRECATED_ATTRIBUTE;

/**
 * Called to report that the "is read" status of the message has changed.
 *
 * @param message The message for which the "is read" status has changed.
 * @param isRead The new value of the isRead flag.
 *
 * @see ::CSMessage::read
 * @deprecated use {@link CSMessageDelegate::message:didChangeReadState:} selector instead.
 */
- (void)message:(CSMessage *)message didChangeIsReadStatus:(BOOL)isRead DEPRECATED_ATTRIBUTE;

@end
