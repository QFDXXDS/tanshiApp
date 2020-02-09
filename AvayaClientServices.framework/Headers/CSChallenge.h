/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, CSAuthorizationMethod) {
	CSAuthorizationMethodBasic,
	CSAuthorizationMethodDigest,
	CSAuthorizationMethodNegotiate,
	CSAuthorizationMethodPortalUserToken,
	CSAuthorizationMethodBearer
};

/**
 * The CSChallenge class for use with a CSCredentialProvider.
 * Based on the CSChallenge, the CSCredentialProvider can request that credentials be supplied.
 *
 */

@interface CSChallenge : NSObject

/**
 * The Realm value associated with the challenge.
 * If the challenge supports multiple auth methods, username/password authorization Realm is returned.
 */
@property (readonly) NSString *realm;

/**
 * Get Realm values for the specified auth method associated with the challenge.
 * If the challenge does not support specified method or the method does not have associated Realm value, empty array is returned.
 */
- (NSArray<NSString *> *)realmsForAuthMethod:(CSAuthorizationMethod)authMethod;

/**
 * The Host associated with the challenge.
 */
@property (readonly) NSString *host;

/**
 * YES if hash credentials are supported.
 */
@property (readonly) BOOL hashCredentialSupported;

/**
 * The failure count based on the number of requests.
 */
@property (readonly) NSUInteger failureCount;

/**
 * YES if Portal User Token authentication is supported.
 */
@property (readonly) BOOL portalUserTokenSupported;

/**
 * A boolean value indicating whether the sender of the challenge can accept OAuth2 Token.
 * @return The return value is true if the sender can accept auth tokens, otherwise false.
 */
@property (readonly, getter=isAuthTokenSupported) BOOL authTokenSupported;

/**
 * A boolean value indicating whether the sender of the challenge can accept username/password
 * as a response to this challenge.
 * @return The return value is true if the username/password are an acceptable response, otherwise false.
 */
@property (readonly, getter=isUsernamePasswordSupported) BOOL usernamePasswordSupported;

/**
 * Location of authorization resource associated with auth token challenge.
 * Credential provider can navigate to this URI using browser window in order to authorize
 * and retrieve auth token for the challenge.
 */
@property (readonly) NSURL *location;

@end

