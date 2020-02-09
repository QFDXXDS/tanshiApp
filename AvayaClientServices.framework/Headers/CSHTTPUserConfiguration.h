/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSHTTPClientConfiguration.h"
#import "CSMediaTransportPreference.h"


/**
 * Configuration information for a HttpSignalingEngine
 */
@interface CSHTTPUserConfiguration : NSObject

/**
 * A Boolean value indicating whether the HTTP provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * List of enabled ciphersuites for SRTP
 */

@property (nonatomic, strong)NSArray* mediaEncryptionCipherList;

/**
 * A Boolean value indicating whether encryption is enabled for SRTCP.
 */
@property (nonatomic) BOOL SRTCPEnabled;

/**
 * Configuration information for HTTP Client data.
 */
@property (nonatomic, strong) CSHTTPClientConfiguration *HTTPClientConfiguration;

/**
 * A Boolean value indicating whether the Media Tunneling is allowed by the configuration.
 * If media tunneling is allowed, Client SDK will try to tunnel audio/video data on ports 443/8443
 * upon failure of audio/video data connections on standard ports.
 */
@property(nonatomic, getter = isMediaTunnelingEnabled) BOOL mediaTunnelingEnabled;

/**
 * A Boolean value indicating whether the Media Tunneling is enforced by the configuration.
 * Should be used only for testing purposes.
 */
@property(nonatomic, getter = isMediaTunnelingEnforced) BOOL mediaTunnelingEnforced;

/**
 * VoIP Calling preference of user.
 */
@property (nonatomic) CSMediaTransportPreference voipCallingPreference;

@end
