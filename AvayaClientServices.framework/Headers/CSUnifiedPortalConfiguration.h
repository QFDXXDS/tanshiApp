/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCredentialProvider.h"
#import "CSAuthenticationMethod.h"


@interface CSUnifiedPortalConfiguration : NSObject

/**
 * The URL of the server to connect with.
 */
@property (nonatomic, copy) NSURL *serverURL;

/**
 * The credential provider.
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

/**
 * Set priorities of authentication methods to be used for provider.
 */
@property (nonatomic, copy) NSArray* authenticationMethodPreferences;

/**
 * The minimum portal version to support Meet-Me conference calls.
 */
@property (nonatomic, copy) NSString* meetMeMinPortalVersion;

@end
