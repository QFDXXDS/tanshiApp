/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCredentialProvider.h"
#import "CSAuthenticationMethod.h"

@interface CSDownloadServiceConfiguration : NSObject

/**
 * The credential provider.
 */
@property (nonatomic, strong) id <CSCredentialProvider> credentialProvider;

/**
 * Set priorities of authentication methods to be used for provider.
 */
@property (nonatomic, copy) NSArray* authenticationMethodPreferences;

@end
