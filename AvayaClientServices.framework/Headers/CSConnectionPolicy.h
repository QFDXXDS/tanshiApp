/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSSignalingServerGroup.h"
#import "CSRegistrationGroup.h"
#import "CSSignalingServer.h"

/**
 * The SignalingEnvironment is a member of an @c CSConnectionPolicy
 * and defines how the connections to the server(s) are established
 * and recovered after failures.
 */
typedef NS_ENUM(NSUInteger, CSSignalingEnvironment) {
	/**
	 * The Avaya signaling environment, suitable for Aura and IPO servers (default)
	 */
	CSSignalingEnvironmentAvaya,
	
	/**
	 * Suitable for OpenSIPS servers.
	 */
	CSSignalingEnvironmentOpenSIPS
};

/**
 * Defines the server connection policy used by a @c CSUser.
 *
 * A connection policy is set during user creation and determines what servers a user will
 * register with and how it should interact with them in failover scenarios.
 */
@interface CSConnectionPolicy : NSObject

/**
 * The signaling server group used by this connection policy.
 */
@property (nonatomic, readonly) CSSignalingServerGroup *signalingServerGroup;

/**
 * The time interval at which a ping is sent to a server to verify that it is responsive.
 *
 * Set to zero to disabling server pings.
 */
@property (nonatomic) NSTimeInterval pingInterval;

/**
 * The amount of time to wait for a response to a server ping.
 *
 * Set to zero to disable validation of server pings. If server pings are enabled and the server
 * fails to response within the specified timeout, the connection to that server will be considered
 * lost.
 */
@property (nonatomic) NSTimeInterval pingTimeout;

/**
 * The TCP (transport level) keep-alive interval.
 *
 * Set to zero to disable TCP keep-alives.
 */
@property (nonatomic) NSTimeInterval keepAliveInterval;

/**
 * The number of unanswered TCP (transport-level) keep-alives after which the connection is
 * considered lost.
 */
@property (nonatomic) uint16_t keepAliveCount;

/**
 * The initial time interval between a connection failure and a reconnect attempt.
 *
 * If connection attempts continue to fail the reconnect interval will be progressively extended
 * using a backoff algorithm based on this initial reconnect interval.
 *
 * Set to zero to disable automatic reconnection attempts.
 */
@property (nonatomic) NSTimeInterval initialReconnectInterval;

/**
 * Property to set Minimum value of the local UDP Port in UDP port Range.
 *
 * If the port range is not specified or invalid then default port range
 * will be used for UDP registration.
 * Default Port Range is 5060 – 5070.
 * Default Minimum value of the local UDP Port is 5060.
 *
 * Port range will be considered as invalid if not matches with following:
 * Minimum port should be less than Maximum port.
 * Both Minimum and Maximum port should be configured.
 * Minimum port should be greater than 1024 and less than 65535.
 * Minimum or Maximum port should not be zero.
 *
 * Some Servers allow Port 5061 only for TLS connection hence port 5061 will be
 * skipped for UDP connection even includes in configured port range.
 *
 * localUDPPortMin - Minimum value of local UDP port to use for SIP signaling
 */
@property (nonatomic) NSUInteger localUDPPortMin;

/**
 * Property to set Maximum value of the local UDP Port in UDP port Range.
 *
 * If the port range is not specified or invalid then default port range
 * will be used for UDP registration.
 * Default Port Range is 5060 – 5070.
 * Default Maximum value of the local UDP Port is 5070.
 *
 * Port range will be considered as invalid if not matches with following:
 * Minimum port should be less than Maximum port.
 * Both Minimum and Maximum port should be configured.
 * Minimum port should be greater than 1024 and less than 65535.
 * Minimum or Maximum port should not be zero.
 *
 * Some Servers allow Port 5061 only for TLS connection hence port 5061 will be
 * skipped for UDP connection even includes in configured port range.
 *
 * localUDPPortMax - Maximum value of local UDP port to use for SIP signaling
 */
@property (nonatomic) NSUInteger localUDPPortMax;

/**
 * Information about the strategy to be used for establishing
 * and re-establishing connections after a failure.
 */
@property (nonatomic) CSSignalingEnvironment signalingEnvironment;

/**
 * Returns a new connection policy using the specified signaling server group.
 *
 * @param signalingServerGroup The signaling server group to use with this connection policy.
 */
+ (instancetype)connectionPolicyWithSignalingServerGroup:(CSSignalingServerGroup *)signalingServerGroup;

/**
 * Returns a new connection policy using the specified signaling server.
 *
 * @param signalingServer The signaling server to use with this connection policy.
 */
+ (instancetype)connectionPolicyWithSignalingServer:(CSSignalingServer *)signalingServer;

/**
 * Returns a new connection policy using the specified signaling server group
 * and signaling environment.
 *
 * @param signalingServerGroup The signaling server group to use with this connection policy.
 * @param signalingEnvironment The policy for (re)establishing connections.
 *	Note that if this policy is set to CSSignalingEnvironmentAlternate, then
 *	the encapsulated CSRegistrationGroups must be limited to a single 
 *	CSSignalingServer per group, and that those CSSignalingServer objects
 *	must use CSFailbackPolicyAutomatic.
 */
+ (instancetype)connectionPolicyWithSignalingServerGroup:(CSSignalingServerGroup *)signalingServerGroup signalingEnvironment:(CSSignalingEnvironment)signalingEnvironment;

/**
 * Returns a new connection policy using the specified signaling server
 * and signaling environment.
 *
 * @param signalingServer The signaling server to use with this connection policy.
 * @param signalingEnvironment The policy for (re)establishing connections.
 *	Note that if this policy is set to CSSignalingEnvironmentAlternate, then
 *	the signalingServer must use CSFailbackPolicyAutomatic.
 */
+ (instancetype)connectionPolicyWithSignalingServer:(CSSignalingServer *)signalingServer signalingEnvironment:(CSSignalingEnvironment)signalingEnvironment;

@end
