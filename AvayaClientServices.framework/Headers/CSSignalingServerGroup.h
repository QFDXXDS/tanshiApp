/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSRegistrationGroup.h"

/**
 * A group of registration groups to register with individually.
 *
 * When all connections in one registration group are lost the next registration group will be
 * activated and an attempt made to re-establish service using the servers in that group. Only one
 * registration group is active at a time.
 */
@interface CSSignalingServerGroup : NSObject

/**
 * Array of @c CSRegistrationGroup instances in this group, in priority order.
 */
@property (nonatomic, readonly, copy) NSArray *registrationGroups;

/**
 * Returns a new signaling server group with the specified registration groups.
 *
 * @param registrationGroups Array of @c CSRegistrationGroup instances to include in the signaling
 *        server group, in priority order.
 */
+ (instancetype)signalingServerGroupWithRegistrationGroups:(NSArray *)registrationGroups;

/**
 * Returns a new signaling server group with the specified server.
 *
 * @param signalingServer The signaling server to use in the group.
 */
+ (instancetype)signalingServerGroupWithServer:(CSSignalingServer *)signalingServer;

@end
