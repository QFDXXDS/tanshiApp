/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Class representing either a remote user who is already tracking local user's presence, 
 * or a remote user who is asking for permission to track local user's presence.
 */
@interface CSPresenceWatcher : NSObject

/**
 * Property to get presence watcher address.
 */
@property (nonatomic, readonly) NSString *presenceAddress;

/**
 * Property to get presence watcher display name.
 */
@property (nonatomic, readonly) NSString *displayName;

@end
