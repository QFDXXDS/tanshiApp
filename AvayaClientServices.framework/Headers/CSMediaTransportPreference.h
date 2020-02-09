/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * The list of Media Transport network preferences.
 *
 * This structure provides a list of choices based on the network type
 * preference. A feature (i.e. VoIP calls, or video) can be enabled based on
 * network connectivity. It is necessary to allow a feature to be enabled based
 * on the preference of network connectivity.
 * All Transports (enabled) and No Media (disabled are independent of network
 * type. The WiFI only state is included to indicate that the feature is
 * dependent on WiFi connectivity.
 */
typedef NS_ENUM(NSInteger, CSMediaTransportPreference) {
	CSMediaTransportNoMedia = 0,
	CSMediaTransportAllTransports,
	CSMediaTransportWifiOnly,
#if TARGET_OS_IPHONE
	/**
	 * Indicates user’s preference to use cellular network for telephony
	 * features and media. When both WiFi and cellular data network connectivity
	 * are available, SIP-based telephony signaling and media traffic are routed
	 * through the cellular data network.
	 * HTTP-based telephony and media traffic are routed through WiFi.
	 * When cellular data network connectivity is not available but WiFi
	 * connectivity is, all telephony and media traffic are routed through WiFi.
	 * If cellular data network connectivity becomes available while connected
	 * through WiFi, SIP-based signaling and any active SIP-based call(s) will
	 * be moved over to the cellular data network.
	 */
	CSMediaTransportCellular,
#endif
};
