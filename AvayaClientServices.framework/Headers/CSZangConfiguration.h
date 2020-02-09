/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"
#import "CSAuthenticationMethod.h"

/**
 * Configuration information for Zang.
 */
@interface CSZangConfiguration : NSObject

/**
 * A Boolean value indicating whether the Zang provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * The server address
 */
@property (nonatomic, strong) CSServerInfo *authorizationServer;

@property (nonatomic, strong) CSServerInfo *spacesServer;

@property (nonatomic, strong) NSString *clientId;

@property (nonatomic, strong) NSString *secret;

@property (nonatomic, strong) NSString *redirectURI;

@property (nonatomic, strong) NSString *scope;

/**
 * URL generated from the configuration to authorization.
 * Example: https://accounts.zang.io/oauth2/authorize/...
 */
@property (nonatomic, readonly) NSString *authorizationURL;

/**
 * URL generated from the configuration for OAuth2 access_token POST request.
 * Example: https://accounts.zang.io/oauth2/access_token
 */
@property (nonatomic, readonly) NSString *accessTokenURL;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

@end
