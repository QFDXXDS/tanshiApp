//
/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"
#import "CSAuthenticationMethod.h"

/**
 * Configuration information for AMM.
 */
@interface CSAMMConfiguration : NSObject

/**
 * A Boolean value indicating whether the AMM provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * The signaling server to connect with
 */
@property (nonatomic, strong) CSServerInfo *server;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

/**
 * Polling interval (0 implies long polling).
 */
@property (nonatomic) NSUInteger pollingIntervalInMinutes;

#ifdef CS_SUPPORTS_MULTIPLE_AUTHENTICATION_METHODS
/**
 * Set priorities of authentication methods to be used for provider.
 */
@property (nonatomic, copy) NSArray *authenticationMethodPreferences;

#endif // CS_SUPPORTS_MULTIPLE_AUTHENTICATION_METHODS

#if TARGET_OS_IPHONE
/**
 * A Boolean value indicating whether Push Notifications are enabled.
 */
@property (nonatomic) BOOL pushNotificationsEnabled;

/**
 * A unique app-device token assigned by Apple to an
 * application instance running in a specific iOS device.
 * This is used by the Avaya Multimedia Messaging (AMM) server when
 * sending messaging events towards the push notification client.
 */
@property (nonatomic, copy) NSData *remoteNotificationsDeviceToken;

/**
 * A Boolean value indicating whether incoming push notification events should
 * be sent through Apple's development push notification network
 * (api.development.push.apple.com) or the production push notification network
 * (api.push.apple.com). The Boolean flag is set to YES  if the application is built
 * using a development provisioning profile. By default, the property is
 * set to NO, and Apple's production network is used to route push notification
 * messages.
 */
@property (nonatomic) BOOL useDevelopmentPushNotificationNetwork;
#endif //TARGET_OS_IPHONE
@end
