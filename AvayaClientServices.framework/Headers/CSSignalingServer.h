/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSTypes.h"

/**
 * Defines how failing back to a server with a higher priority than the current server is handled.
 *
 * When the connection to a primary server is lost the signaling engine will "fail over" to an
 * alternate server if one is available. This policy determines how the signaling engine "fails
 * back" to the primary server when the connection with the primary server is re-established.
 */
typedef NS_ENUM(NSUInteger, CSFailbackPolicy) {
	/**
	 * Failback occurs automatically as soon as a connection with the primary server is
	 * re-established.
	 */
	CSFailbackPolicyAutomatic,

	/**
	 * Failback will not occur until the administrator triggers a manual failback, or connection
	 * with this server is lost.
	 */
	CSFailbackPolicyManual
};

/**
 * Represents a call server to communicate with.
 */
@interface CSSignalingServer : NSObject

/**
 * The server's host name.
 *
 * This may by a fully qualified domain name or an IP address.
 */
@property (nonatomic, readonly, copy) NSString *hostName;

/**
 * The failback policy for this server.
 *
 * @see CSFailbackPolicy
 */
@property (nonatomic, readonly) CSFailbackPolicy failbackPolicy;

/**
 * A dictionary of transport type to port number.
 */
@property (nonatomic, readonly, copy) NSDictionary *transportTypeToPortMap;

/**
 * Array of NSStrings containing URIs specifying routing information for SIP requests sent to this
 * server.
 */
@property (nonatomic, readonly, copy) NSArray *preloadedRoutes;

/**
 * A Boolean value indicating whether this server is a permanent member of any registration group it
 * is a part of.
 *
 * The permanent flag instructs the signaling engine to attempt to maintain a registration with this
 * server regardless of conditions that would otherwise cause registration with this server to be
 * deferred until connections with higher priority servers were lost.
 */
@property (nonatomic, readonly, getter=isPermanentMemberOfRegistrationGroup) BOOL permanentMemberOfRegistrationGroup;

+ (instancetype)serverWithHostname:(NSString *)hostName
					failbackPolicy:(CSFailbackPolicy)policy;

+ (instancetype)serverWithTransportType:(CSTransportType)transportType
							   hostName:(NSString *)hostName
								   port:(NSUInteger)port
						 failbackPolicy:(CSFailbackPolicy)policy
						preloadedRoutes:(NSArray *)preloadedRoutes
   isPermanentMemberOfRegistrationGroup:(BOOL)isPermanentMemberOfRegistrationGroup;

+ (instancetype)serverWithHostName:(NSString *)hostName
			transportTypeToPortMap:(NSDictionary *)transportTypeToPortMap
					failbackPolicy:(CSFailbackPolicy)policy
				   preloadedRoutes:(NSArray *)preloadedRoutes
isPermanentMemberOfRegistrationGroup:(BOOL)isPermanentMemberOfRegistrationGroup;

+ (instancetype)serverWithTransportType:(CSTransportType)transportType
							   hostName:(NSString *)hostName
								   port:(NSUInteger)port
						 failbackPolicy:(CSFailbackPolicy)policy
   isPermanentMemberOfRegistrationGroup:(BOOL)isPermanentMemberOfRegistrationGroup;

+ (instancetype)serverWithTransportType:(CSTransportType)transportType
							   hostName:(NSString *)hostName
								   port:(NSUInteger)port
						 failbackPolicy:(CSFailbackPolicy)policy;

@end
