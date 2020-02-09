/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCapability.h"

/**
 * Resources returned by Unified Portal.
 */
@interface CSUnifiedPortalResources : NSObject

/**
 * The URL of Avaya Aura Device Services. 
 * Shall be used to configure contact services when in Meet-me mode.
 * @see CSACSConfiguration
 */
@property (nonatomic, readonly, copy) NSURL * aadsURL;

/**
 * Specifies the lower limit of the UDP port range to be used by BFCP signaling channel.
 * Shall be used to populate BFCP configuration data when in Meet-me mode.
 * @see CSBFCPConfiguration
 */
@property (nonatomic) NSUInteger bfcpUdpMinPort;

/**
 * Specifies the upper limit of the UDP port range to be used by BFCP signaling channel.
 * Shall be used to populate BFCP configuration data when in Meet-me mode.
 * @see CSBFCPConfiguration
 */
@property (nonatomic) NSUInteger bfcpUdpMaxPort;

/**
 * The URL of App Cast Service.
 * Meet-me client shall periodically check for software updates using this URL.
 */
@property (nonatomic, readonly, copy) NSURL * appCastURL;

/**
 * The client update checking interval.
 */
@property (nonatomic) NSTimeInterval appCastCheckInterval;

/**
 * A dictionary of extra properties the application may be interested in.
 * Complex property values are JSON encoded strings.
 */
@property (nonatomic, readonly) NSDictionary *extraProperties;

/**
 * Capability info indicating whether local user can request to join Meet-Me conference.
 * The capability returns not supported if the portal version provided in
 * portal resource discovery older then configured minimum portal version.
 */
@property (nonatomic, readonly) CSCapability* requestToJoinMeetingCapability;

- (instancetype)initWithAadsURL:(NSURL *)aadsURL
				 bfcpUdpMinPort:(NSUInteger) bfcpUdpMinPort
				 bfcpUdpMaxPort:(NSUInteger) bfcpUdpMaxPort
				 appCastURL:(NSURL *) appCastURL
				 appCastCheckInterval:(NSTimeInterval) appCastCheckInterval
				 extraProperties:(NSDictionary *) extraProperties
				 requestToJoinMeetingCapability:(CSCapability *)requestToJoinMeetingCapability;

@end
