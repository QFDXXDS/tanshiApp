/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"
#import "CSAuthenticationMethod.h"

/**
 * Configuration information for ACS.
 */
@interface CSACSConfiguration : NSObject

/**
 * A Boolean value indicating whether the ACS provider is enabled.
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

#ifdef CS_SUPPORTS_MULTIPLE_AUTHENTICATION_METHODS
/**
 * Set priorities of authentication methods to be used for provider.
 */
@property (nonatomic, copy) NSArray *authenticationMethodPreferences;

#endif // CS_SUPPORTS_MULTIPLE_AUTHENTICATION_METHODS

/**
 * The URL of the server to connect with.
 * CSServerInfo will be ignored if this URL is specified.
 */
@property (nonatomic, copy) NSURL *serverURL;

@end
