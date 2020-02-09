/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCredentialProvider.h"
#import "CSMediaConfiguration.h"
#import "CSSecurityPolicyConfiguration.h"

typedef NS_ENUM(NSUInteger, CSProxyMode) {
  CSProxyModeNoProxy,
  CSProxyModeUseOperatingSystemSettings,
  CSProxyModeUseOperatingSystemSettingsWithSTUN
};

@interface CSClientConfiguration : NSObject

/**
 * Initialize with configuration detail with directory for storing persistent data.
 */
- (instancetype)initWithDataDirectory:(NSString *)dataDirectory;

/**
 * Initialize with configuration details like name and version of the product, platform,
 * operating system version, and build number, vendor name and device handle
 */
- (instancetype)initWithDataDirectory:(NSString *)dataDirectory
                          productName:(NSString *)productName
                       productVersion:(NSString *)productVersion
                             platform:(NSString *)platform
                            osVersion:(NSString *)osVersion
                          buildNumber:(NSString *)buildNumber
                           vendorName:(NSString *)vendorName;

/**
 * Product name
 */
@property (nonatomic, copy) NSString *productName;

/**
 * Product version
 */
@property (nonatomic, copy) NSString *productVersion;

/**
 * Platform
 */
@property (nonatomic, copy) NSString *platform;

/**
 * Operating system version
 */
@property (nonatomic, copy) NSString *osVersion;

/**
 * Build number
 */
@property (nonatomic, copy) NSString *buildNumber;

/**
 * Vendor name
 */
@property (nonatomic, copy) NSString *vendorName;

/**
 * The product-identifying string used in the User-Agent header.
 */
@property (nonatomic, copy) NSString *userAgentName;

/**
 * A unique instance id of the user agent. This is the instance.id defined in RFC 5626.
 * According to RFC 5626, each UA MUST have an Instance Identifier Uniform Resource Name (URN)
 * [RFC2141] that uniquely identifies the device.  Usage of a URN provides a persistent and
 * unique name for the UA instance.  It also provides an easy way to guarantee uniqueness within
 * the AOR.  This URN MUST be persistent across power cycles of the device.  The
 * instance ID MUST NOT change as the device moves from one network to another.
 * A device like a "soft phone", when first installed, can generate a UUID [RFC4122] and
 * then save this in persistent storage for all future use.
 *
 * This is typically a string representation of a UUID.
 */
@property (nonatomic, copy) NSString *userAgentInstanceId;

/**
 * Configuration data containing security policy
 */
@property (nonatomic, strong) CSSecurityPolicyConfiguration *securityPolicyConfiguration;

/**
 * Configuration data containing the media (audio, video) data
 */
@property (nonatomic, strong) CSMediaConfiguration *mediaConfiguration;

/**
 * The directory for storing persistent data.
 */
@property (nonatomic, copy) NSString *dataDirectory;

/**
 * Used to control the collection of analytics data by the SDK.
 *
 * The analytics information collected by the SDK is for internal Avaya use only and contains
 * no personally identifiable information. These analytics are used solely by Avaya for the purposes
 * of improving its products and will not be shared with anyone outside of Avaya.
 *
 * Note that changes to this setting are not effective after the CSClient object has been created.
 *
 * The default value is NO (the collection of analytics is disabled).
 */
@property (nonatomic) BOOL analyticsEnabled;

/**
 * Proxy mode to use with network connections.
 */
@property (nonatomic, assign) CSProxyMode proxyMode;

/**
 * Credential provider for proxy authentication.
 */
@property (nonatomic, weak) id<CSCredentialProvider> proxyCredentialProvider;

/**
 * Defines if proxy fallback feature is enabled or not.
 *
 * Proxy fallback is a feature that will allow Client SDK to connect directly to given endpoint despite proxy settings.
 * First, connection is made via proxy (if set in Operating System) and if there's a failure (except wrong credentials),
 * another attempt is made to establish a connection, only this time bypassing proxy settings.
 */
@property (nonatomic, assign, getter=isProxyFallbackEnabled) BOOL proxyFallbackEnabled;

#if TARGET_OS_IPHONE

/**
 * A Boolean value indicating whether the SDK detects and handles the presence
 * of cellular calls on the device.
 *
 * Applications making use of CallKit to integrate the SDK with the iOS
 * telephony system via a CXProvider should set this to NO.
 *
 * Prior to the introduction of CallKit, VoIP applications needed to handle a
 * cellular call becoming active on the device, as iOS would prioritize audio
 * for the cellular call, disabling audio for the VoIP application. The SDK
 * includes features to handle this automatically, placing active calls on hold
 * and preventing new calls from being started until the cellular call ends. For
 * applications using CallKit these features are no longer needed and should be
 * disabled. CallKit applications should instead use
 * CSClient::audioSessionDidBecomeActive: to inform the SDK of when CallKit
 * activates and deactivates the audio session.
 *
 * Defaults to YES.
 */
@property (nonatomic) BOOL cellularCallDetectionEnabled;

#endif

#if !TARGET_OS_IPHONE

/**
 * A Boolean value indicating whether the audio device call control feature is enabled.
 *
 * When true, allows the user to answer, end, mute, unmute, hold, and unhold calls
 * using buttons on certain Avaya-branded audio devices (L1xx headsets, B109 speakerphone).
 * Button control is enabled automatically when the same supported headset is selected for
 * use as the microphone and earphone device. Button control is disabled when either the
 * microphone or earphone is an unsupported device. This feature is independent of
 * headset control by the App or External API, and those services should continue to work
 * with the devices that they support.
 
 * Defaults to YES.
 */
@property (nonatomic) BOOL audioDeviceCallControlEnabled;

#endif

@end
