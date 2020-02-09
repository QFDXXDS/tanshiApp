/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSPresenceWatcher.h"
#import "CSPresenceACLPolicy.h"

@protocol CSPresenceWatcherRequestDelegate;
@protocol CSPresenceAccessControlDelegate;

/**
 * The class encapsulates presence access control list related features available to the user.
 * 
 * Access Control List (ACL) tracks local user's decisions regarding allowing or denying 
 * permission to other users who want to track the local user's presence.
 * Remote users are added to the list when local user allows or blocks incoming presence watcher requests 
 * in the case of configured \link CSPresenceACLPolicy::CSPresenceACLPolicyConfirm CSPresenceACLPolicyConfirm \endlink policy.
 * Local user is not able to delete presence watcher from access control list, 
 * but it is possible to change rules for remote watchers.
 */
@interface CSPresenceAccessControlList : NSObject

/**
 * The delegate responsible for handling events related to requests from other users in the system
 * when \link CSPresenceACLPolicy CSPresenceACLPolicy \endlink is configured to \link CSPresenceACLPolicy::CSPresenceACLPolicyConfirm CSPresenceACLPolicyConfirm \endlink
 * and remote user requests to track local user's presence.
 */
@property (nonatomic, weak) id<CSPresenceWatcherRequestDelegate> presenceWatcherRequestDelegate;

/**
 * The delegate responsible for handling events related to initial state 
 * and subsequent updates for the default \link CSPresenceACLPolicy CSPresenceACLPolicy \endlink
 * and the list of users either allowed to track local user's presence, or blocked from tracking local user's presence.
 */
@property (nonatomic, weak) id<CSPresenceAccessControlDelegate> presenceAccessControlDelegate;

/**
 * List of users allowed to track local user's presence.
 * nil is returned until \link CSPresenceAccessControlDelegate CSPresenceAccessControlDelegate \endlink is assigned.
 * In order to receive a list of allowed presence watchers assign delegate first 
 * and wait for delegate's events.
 */
@property (nonatomic, readonly) NSArray *allowedPresenceWatchers;

/**
 * List of users who are not allowed to track local user's presence.
 * nil is returned until \link CSPresenceAccessControlDelegate CSPresenceAccessControlDelegate \endlink is assigned.
 * In order to receive a list of allowed presence watchers assign delegate first 
 * and wait for delegate's events.
 */
@property (nonatomic, readonly) NSArray *blockedPresenceWatchers;

/**
 * Current \link CSPresenceACLPolicy CSPresenceACLPolicy \endlink.
 * \link CSPresenceACLPolicy::CSPresenceACLPolicyUndefined CSPresenceACLPolicyUndefined \endlink is returned until the information is retrieved from the network.
 * Will return \link CSPresenceACLPolicy::CSPresenceACLPolicyBlock CSPresenceACLPolicyBlock \endlink in the case if \link CSPresenceACLPolicy::CSPresenceACLPolicyConfirm CSPresenceACLPolicyConfirm \endlink is configured 
 * with current Presence Server implementation.
 */
@property (nonatomic, readonly) CSPresenceACLPolicy presenceACLPolicy;

/**
 * Used to allow either a pending or a previously blocked presence tracking request.
 *
 * @param presenceWatcher Remote user who will be allowed to track local user's presence.
 * @param completionHandler A completion handler to call when the operation has completed.
 */
- (void)allowPresenceWatcher:(CSPresenceWatcher *)presenceWatcher completionHandler:(void(^)(NSError *error))completionHandler;

/**
 * Used to block either a pending or a previously allow presence tracking request.
 *
 * @param presenceWatcher Remote user who will not be allowed to track local user's presence.
 * @param completionHandler A completion handler to call when the operation has completed.
 */
- (void)blockPresenceWatcher:(CSPresenceWatcher *)presenceWatcher completionHandler:(void(^)(NSError *error))completionHandler;

@end

@protocol CSPresenceWatcherRequestDelegate <NSObject>

/**
 * Sent when another user of the system would like to track local user's presence. 
 * The other user's information is provided in the \link CSPresenceWatcher CSPresenceWatcher \endlink parameter.
 *
 * @param presenceAccessControlList The presence access control list associated with the callback.
 * @param presenceWatcher Received presence watcher request.
 */ 
- (void)presenceAccessControlList:(CSPresenceAccessControlList *)presenceAccessControlList didReceiveRequestFromPresenceWatcher:(CSPresenceWatcher *)presenceWatcher;

/**
 * Sent when presence tracking request initiated by another user in the system has been cancelled. 
 * The other user's information is provided in the \link CSPresenceWatcher CSPresenceWatcher \endlink parameter.
 *
 * @param presenceAccessControlList The presence access control list associated with the callback.
 * @param presenceWatcher Cancelled presence watcher request.
 */ 
- (void)presenceAccessControlList:(CSPresenceAccessControlList *)presenceAccessControlList didCancelRequestFromPresenceWatcher:(CSPresenceWatcher *)presenceWatcher;

@end

@protocol CSPresenceAccessControlDelegate <NSObject>

/**
 * Sent when the list of users allowed to track local user's presence 
 * or a list of users blocked from tracking local user's presence have been changed.
 *
 * @param presenceAccessControlList The presence access control list associated with the callback.
 * @param allowedWatchers List of allowed presence watchers.
 * @param blockedWatchers List of blocked presence watchers.
 */ 
- (void)presenceAccessControlList:(CSPresenceAccessControlList *)presenceAccessControlList didChangeAllowedWatchers:(NSArray *)allowedWatchers blockedWatchers:(NSArray *)blockedWatchers;

/**
 * Called when the \link CSPresenceACLPolicy CSPresenceACLPolicy \endlink has been changed.
 *
 * @param presenceAccessControlList The presence access control list associated with the callback.
 * @param presenceACLPolicy Current presence access control list policy.
 */  
- (void)presenceAccessControlList:(CSPresenceAccessControlList *)presenceAccessControlList didChangeACLPolicy:(CSPresenceACLPolicy)presenceACLPolicy;

@end
