/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Transport type to use for a connection to a signaling server.
 */
typedef NS_ENUM(NSUInteger, CSTransportType) {
	/**
	 * The appropriate transport type will be discovered via DNS.
	 */
	CSTransportTypeAutomatic = 0,

	/**
	 * Encrypted TLS.
	 */
	CSTransportTypeTLS = 1,

	/**
	 * Unencrypted TCP.
	 */
	CSTransportTypeTCP = 2,

	/**
	 * Unencrypted UDP.
	 */
	CSTransportTypeUDP = 3
};
