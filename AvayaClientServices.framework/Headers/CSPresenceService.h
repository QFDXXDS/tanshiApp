/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSPresence.h"
#import "CSPresenceAccessControlList.h"
#import "CSCapability.h"
#import "CSPresenceListSubscription.h"

@protocol CSPresenceServiceDelegate;

/**
 * The class encapsulates all of presence related features available to the user.
 *
 * The presence service encapsulates such features as publishing presence, subscribing for self-presence update events, and
 * creating presence list subscriptions to watch presence of other users.
 *
 * The service is configured with {@link CSPresenceConfiguration} object created by the client application
 * as part of the {@link CSUserConfiguration}.
 * In order to get the service object and leverage the available presence features ::CSUser::presenceService is used.
 */
@interface CSPresenceService : NSObject

/**
 * The delegate responsible for handling presence service related events.
 */
@property (nonatomic, weak) id<CSPresenceServiceDelegate> delegate;

/**
 * Exposes the service availability status.
 *
 * The service may become unavailable due to a number of reasons such as network issues, presence server issues, and configuration issues.
 */
@property (nonatomic, readonly) BOOL serviceAvailable;

/**
 * Exposes the service configuration status
 *
 * Reflects the fact that the service is not provided with a valid {@link CSPresenceConfiguration} object or couldn't automatically discover its configuration.
 */
@property (nonatomic, readonly) BOOL serviceConfigured;

/**
 * Publishes presence state, location mode and optional note for the local user.
 *
 * The result of the operation is delivered via {@link CSPresenceServiceDelegate}:
 *
 * @li If presence information is published successfully {@link CSPresenceServiceDelegate::presenceService:didPublishPresence:} gets invoked.
 * @li Otherwise, {@link CSPresenceServiceDelegate::presenceService:didFailToPublishPresence:error:} is reported representing the specific failure.
 *
 * @param presence Presence information to publish.
 */
- (void)publishPresence:(CSPresence *)presence;

/**
 * Sets the timeout for the user inactivity timer at runtime.
 *
 * Inactivity timer is used to automatically change the user's presence state to 'away'
 * if the user is inactive, i.e. not using the device with the installed application.
 * When the timer fires, the user's presence is set to the 'away' state.	
 * If zero value is specified, the inactivity timer is disabled.
 */
@property (nonatomic) NSTimeInterval autoAwayTimeout;

/**
 * Sets a link between "Do Not Disturb" presence state and "Send All Calls" call service feature at runtime.
 *
 * If the link is enabled and "Send All Calls" feature is available, the following behavior applies.
 *
 * @li Once the presence state of the user changes to "Do not Disturb", "Send All Calls" is automatically switched on.
 * @li If the presence state of the user changes from "Do not Disturb" to any other state, "Send All Calls" is automatically switched off.
 */
@property (nonatomic) BOOL sendAllCallsOnDoNotDisturb;

/**
 * Property to get current self-presence based on the last received presence data from the presence server.
 *
 * Self-presence describes overall presence status of the local user calculated by the presence server based on presence data information collected from various presence sources.
 * The sources are communication devices and applications running on behalf of the user.
 */
@property (nonatomic, readonly) CSPresence *selfPresence;

/**
 * Get the maximum text length value (in characters) accepted for presence note.
 *
 * @return the maximum text length value accepted for presence note.
 */
@property (nonatomic, readonly) NSUInteger presenceNoteMaxTextLength;

/**
 * Returns CSCapability object describing whether the Presence service supports Presence Access Control List(ACL).
 *
 * @return {@link CSCapability} object describing whether the Presence service supports Presence Access Control List(ACL).
 */
@property (nonatomic, readonly) CSCapability *presenceAccessControlListCapability;

/**
 * Returns CSCapability object describing whether the Presence service supports automatic mode for self-presence.
 *
 * @return {@link CSCapability} object describing whether the Presence service supports automatic mode for Self Presence.
 */
@property (nonatomic, readonly) CSCapability *automaticModeCapability;

/**
 * Returns array of all the supported automatic self-presence states.
 *
 * @return NSArray object with all the supported automatic self-presence states(CSPresenceState).
 */
@property (nonatomic, readonly) NSArray *automaticPresenceStates;

/**
 * Returns array of all the supported manual self-presence states.
 *
 * The client application should check for the supported manual self-presence states before initializing the presence states for UI/UX update.
 *
 * @return NSArray object with all the supported manual self-presence states(CSPresenceState).
 */
@property (nonatomic, readonly) NSArray *manualPresenceStates;

/**
 * Creates a new empty ad-hoc presence subscription object.
 *
 * An ad-hoc presence subscription object is used to manipulate the list of users the client application wants to know presence of.
 * A PresenceListSubscription object allows the application to subscribe for presence events of multiple users specified by their presence addresses.
 * Note that the preferred way of getting presence of other users is {@link CSContact::startPresenceWithAccessControlBehavior:completionHandler:}.
 *
 * @return An empty {@link CSPresenceListSubscription} object.
 */
- (CSPresenceListSubscription *)createPresenceListSubscription;

/**
 * Removes the specified presence list subscription.
 *
 * This method is used to stop getting presence updates for all of the users specified by the addresses added to the object.
 *
 * @param subscription Subscription to be removed.
 */
- (void)removePresenceListSubscription:(CSPresenceListSubscription *)subscription;

/**
 * Property representing \link CSPresenceAccessControlList CSPresenceAccessControlList \endlink.
 */
@property (nonatomic, readonly) CSPresenceAccessControlList *presenceAccessControlList;

@end

@protocol CSPresenceServiceDelegate <NSObject>

/**
 * Sent when the local user's presence has been published successfully.
 *
 * @param presenceService The presence service instance sending the message.
 * @param presence The presence information sent.
 */
- (void)presenceService:(CSPresenceService *)presenceService didPublishPresence:(CSPresence *)presence;

/**
 * Sent when the local user's presence failed to be published.
 *
 * @param presenceService The presence service instance sending the message.
 * @param presence The presence intended to send.
 * @param error The error containing the details of the failure.
 */
- (void)presenceService:(CSPresenceService *)presenceService didFailToPublishPresence:(CSPresence *)presence error:(NSError *)error;

/**
 * Sent when presence information is received for the local user.
 *
 * @param presenceService The presence service instance sending the message.
 * @param presence The presence information received.
 */
- (void)presenceService:(CSPresenceService *)presenceService didReceiveSelfPresence:(CSPresence *)presence;

#ifdef INCLUDE_WATCHER_REQUEST
/**
 * Sent when presence watcher request has been received.
 *
 * @param presenceService The presence service instance sending the message.
 * @param request The request received.
 */
- (void)presenceService:(CSPresenceService *)presenceService didReceivePresenceWatcherRequest:(CSPresenceWatcherRequest *)request;

/**
 * Sent when presence watcher request has been completed.
 *
 * @param presenceService The presence service instance sending the message.
 * @param request The request completed.
 * @param result The result.
 */
- (void)presenceService:(CSPresenceService *)presenceService didCompletePresenceWatcherRequest:(CSPresenceWatcherRequest *)request withResult:(CSPresenceWatcherRequestResult)result;

/**
 * Sent when presence watcher authorization response failed.
 *
 * @param presenceService The presence service instance sending the message.
 * @param request The request that failed to authorize.
 * @param result The result.
 * @param error The error containing the details of the failure.
 */
- (void)presenceService:(CSPresenceService *)presenceService didFailToAuthorizePresenceWatcherRequest:(CSPresenceWatcherRequest *)request withResult:(CSPresenceWatcherRequestResult)result error:(NSError *)error;
#endif

/**
 * Sent when the presence service becomes available.
 *
 * @param presenceService The presence service associated with the message.
 */
- (void)presenceServiceAvailable:(CSPresenceService *)presenceService;

/**
 * Called when the presence service becomes unavailable.
 *
 * The service may become unavailable due to a number of reasons such as network issues, presence server issues, and configuration issues.
 *
 * @param presenceService The presence service associated with the callback.
 */
- (void)presenceServiceUnavailable:(CSPresenceService *)presenceService;

@end
