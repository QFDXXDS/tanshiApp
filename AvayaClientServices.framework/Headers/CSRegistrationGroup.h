/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSSignalingServer.h"

/**
 * A group of signaling servers to register with simultaneously.
 */
@interface CSRegistrationGroup : NSObject

/**
 * Array of @c CSSignalingServer instances in this group, in priority order.
 */
@property (nonatomic, readonly, copy) NSArray *servers;

/**
 * The maximum number of servers in this group to register with at once.
 */
@property (nonatomic, readonly) NSUInteger simultaneousRegistrationLimit;

/**
 * Returns a new registration group with the specified servers and registration limit.
 *
 * @param servers Array of @c CSSignalingServer instances to include in the group, in priority
 *        order. Although registration with servers in the group will occur simultaneously,
 *        operations other than registration will be performed against servers in priority order.
 * @param simultaneousRegistrationLimit The maximum number of servers to allow simultaneous
 *        registration with. If this value is less than the number of servers in the group, the
 *        servers will be registered with in priority order. Registration to the remaining servers
 *        will only be attempted if connections to higher-priority servers are lost.
 */
+ (instancetype)registrationGroupWithSignalingServers:(NSArray *)servers simultaneousRegistrationLimit:(NSUInteger)simultaneousRegistrationLimit;

/**
 * Returns a new registration group with the specified servers.
 *
 * @param servers Array of @c CSSignalingServer instances to include in the group, in priority
 *        order. Although registration with servers in the group will occur simultaneously,
 *        operations other than registration will be performed against servers in priority order.
 */
+ (instancetype)registrationGroupWithSignalingServers:(NSArray *)servers;

/**
 * Returns a new registration group with the specified server.
 *
 * @param server The signaling server to use in the group.
 */
+ (instancetype)registrationGroupWithSignalingServer:(CSSignalingServer *)server;

@end
