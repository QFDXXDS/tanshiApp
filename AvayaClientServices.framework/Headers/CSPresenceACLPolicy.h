/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Enumeration that describes different access control list policies.
 *
 * When a request to start watching the presence of some user is issued by the client,
 * Access Control List policy is used to decide whether the requesting user has permissions 
 * to get the presence of the desired user.
 */
typedef NS_ENUM(NSInteger, CSPresenceACLPolicy) {
	/**
	 * Presence access control list policy is undefined.
	 * This means that policy is unknown to us.
	 * Returned until the information is retrieved from the network.
	 */
	CSPresenceACLPolicyUndefined = 0,
	
	/**
	 * Presence access control list policy is in allowed state.
	 * Presence access control list policy is set to allow anyone 
	 * with permission to track local user's presence. 
	 * Previously blocked users are not affected by this policy setting.
	 */
	CSPresenceACLPolicyAllow,
	
	/**
	 * Presence access control list policy is in blocked state.
	 * Presence access control list policy is set to block anyone 
	 * from tracking local user's presence. 
	 * Previously allowed users are not affected by this policy setting.
	 */
	CSPresenceACLPolicyBlock,
	
	/**
	 * Presence access control list policy is in confirm state.
	 * Presence access control list policy is set to prompt local user regarding anyone 
	 * who wants to track local user's presence in the system. 
	 * The local user may allow or deny the incoming presence tracking request
	 * using \link CSPresenceAccessControlList::allowPresenceWatcher:completionHandler: allowPresenceWatcher \endlink
	 * or \link CSPresenceAccessControlList::blockPresenceWatcher:completionHandler: blockPresenceWatcher \endlink.
	 */
	CSPresenceACLPolicyConfirm
};
