/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSConnectionPolicy.h"
#import "CSCredentialProvider.h"
#import "CSSIPClientConfiguration.h"
#import "CSMediaTransportPreference.h"
#import "CSOutboundSubscriptionConfiguration.h"

/**
 * The mobility mode for a user.
 */
typedef NS_ENUM(uint32_t, CSSIPMobilityMode) {
	/**
	 * No mobility information is available.
	 */
	CSSIPMobilityModeUnspecified = 0,

	/**
	 * The user is at a fixed location.
	 */
	CSSIPMobilityModeFixed,

	/**
	 * The user is on a mobile device.
	 */
	CSSIPMobilityModeMobile
};

/**
 *  Indicates the SIP session manager address type preference when the client connects to dual stack server from a dual stack client network.
 */
typedef NS_ENUM(NSInteger, CSSignalingAddressMode) {
	/**
	 * Prefer IPv4 SM address
	 */
	CSSignalingAddressModeIPv4 = 0,

	/**
	 * Prefer IPv6 SM address
	 */
	CSSignalingAddressModeIPv6
};

/**
 *  Indicates the IP address type preference to use when negotiating media streams when the client connects to dual stack server from a dual
 *  stack client network.
 */
typedef NS_ENUM(NSInteger, CSMediaAddressMode) {
	/**
	 * Only use local IPv4 address during media information exchange.
	 * This option is used in an IPv4 only network environment, where the
	 * local client has an IPv4 network address.
	 * Setting this mode in an IPv6  only environment is a configuration
	 * error, however the call is allowed to proceed with an IPv6 media
	 * address.
	 */
	CSMediaAddressModeIPv4 = 0,
	/**
	 * Only use local IPv6 address during media information exchange.
	 * This option is used in an IPv6 only network environment, where the
	 * local client has an IPv6 network addresses.
	 * Setting this mode in an IPv4 only environment is a configuration
	 * error, however the call is allowed to proceed with an IPv4 media
	 * address.
	 */
	CSMediaAddressModeIPv6,
	/**
	 * Prefer local IPv4 address over local IPv6 address when both
	 * are available to the local endpoint.
	 * This option is used in a dual IPv4 and IPv6 network environment, where the
	 * local client has both IPv4 and IPv6 address.
	 * Both IPv4 and IPv6 local addresses are provided during media
	 * exchange, and the IPv4 local address is preferred over the IPv6 address.
	 */
	CSMediaAddressModeIPv4Then6,
	/**
	 * Prefer local IPv6 address over local IPv4 address when both
	 * are available to the local endpoint.
	 * This option is used in a dual IPv4 and IPv6 network environment, where the
	 * local client has both IPv4 and IPv6 addresses.
	 * Both IPv4 and IPv6 local addresses are provided during media
	 * exchange, and the IPv6 local address is preferred over the IPv4 address.
	 */
	CSMediaAddressModeIPv6Then4
};

/**
 * Configuration information for a @c CSSIPSignalingEngine.
 */
@interface CSSIPUserConfiguration : NSObject

/**
 * A Boolean value indicating whether the SIP provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * The connection policy defining the signaling servers to communicate with.
 */
@property (nonatomic, strong) CSConnectionPolicy *connectionPolicy;

/**
 * The user ID.
 */
@property (nonatomic, copy) NSString *userId;

/**
 * The SIP domain for the user.
 */
@property (nonatomic, copy) NSString *domain;

/**
 * The credential provider to be used for SIP authentication.
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

/**
 * The display name used to identify the endpoint the user is on.
 *
 * In SIP this is inserted in the display name portion of SIP Contact header. For example, the display name
 * may be set to "Alice's Flare on iPad". This label is used to identify an endpoint from a list of endpoints
 * that can be registered on behalf of the user (e.g., when SM's parallel forking group feature is enabled).
 */
@property (nonatomic, copy) NSString *displayName;

/**
 * The language string to use in Accept-Language header.
 */
@property (nonatomic, copy) NSString *language;

/**
 * The mobility mode for the user.
 */
@property (nonatomic) CSSIPMobilityMode mobilityMode;

/**
 * The alternate network type for a dual-mode client.
 *
 * Generally set to "mobile" for dual-mode clients.
 */
@property (nonatomic, copy) NSString *alternateNetwork;

/**
 * The address-of-record for the user in the alternate network.
 *
 * For a dual-mode client, this specifies the user's cell number.
 */
@property (nonatomic, copy) NSString *alternateAddressOfRecord;

/**
 * List of enabled ciphersuites for SRTP
 */

@property (nonatomic, strong)NSArray* mediaEncryptionCipherList;

/**
 * A Boolean value indicating whether encryption is enabled for SRTCP.
 */
@property (nonatomic) BOOL SRTCPEnabled;

/**
 * Controls whether the SIP endpoint uses sips (secure SIP) URI scheme for all SIP requests it initiates towards the network,
 * including secure media calls.
 *
 * If enabled, SIP endpoint registers a SIPS Contact address with the SIP registrar, and uses SRTP
 * crypto suites as controlled by {@link #mediaEncryptionCipherList}.
 *
 * If disabled, SIP endpoint registers a SIP Contact address with the SIP registrar, and uses SRTP
 * crypto suites as controlled by {@link #mediaEncryptionCipherList}.
 *
 */
@property (nonatomic) BOOL useSIPSURIOverTLS;

/**
 * Configuration information for SIP Client data.
 */
@property (nonatomic, strong) CSSIPClientConfiguration *SIPClientConfiguration;

/**
 * Configuration information for Outbound Subscription data.
 */
@property (nonatomic, strong) CSOutboundSubscriptionConfiguration *outboundSubscriptionConfiguration;

/**
 * VoIP Calling preference of user.
 */
@property (nonatomic) CSMediaTransportPreference voipCallingPreference;

/**
 * Indicates the SIP session manager address type preference when the client connects to dual stack server from a dual stack client network
 */
@property (nonatomic) CSSignalingAddressMode signalingAddressMode;

/**
 * Indicates the IP address type preference to use when negotiating media streams when the client connects to dual stack server from a dual
 * stack client network.
 */
@property (nonatomic) CSMediaAddressMode mediaAddressMode;

/**
 * A Boolean value indicating if transfer to voicemail feature is enabled.
 */
@property (nonatomic, getter=isTransferToVoicemailEnabled) BOOL transferToVoicemailEnabled;

/**
 * It accelerates dialing by eliminating the need to wait for
 * the INTER_DIGIT_TIMEOUT timer to expire.
 * The value can contain 0 to 1023 characters; the default value is null ("").
 * See the telephone Administrator's Guide for format and setting alternatives.
 * example: "[23]xxxx|91xxxxxxxxxx|9[2-9]xxxxxxxxx"
 */
@property (nonatomic, copy) NSString *dialPlan;

/**
 * The emergency phone numbers
 *
 * Used in the Non-Aura environment.
 * In a Aura environment, the identification of emergency numbers occurs automatically.
 */
@property (nonatomic, strong) NSSet *emergencyNumbers;

@end
