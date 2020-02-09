/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSDefines.h"

/**
 * Represents a user credential that can be used to respond to an authentication credential challenge.
 *
 * <p>
 * Credentials may consist of username, password, HA1 String and domain information. Depending on the 
 * system configuration, some of the parameters may not be available or applicable for a particular 
 * credential. For example, some credential may be made up of username and password only. In such case,
 * the domain and HA1 String will be just empty strings. In some other configurations (e.g., for SIP 
 * authentication), the HA1 String and the username are the only user credential information available 
 * from the configuration server for a user. In such case, the user credential will have empty strings
 * for password and domain.
 * </P>
 *
 * <p>
 * This interface includes all of the convenient methods for constructing a UserCredential. 
 * </p>
 */

@interface CSUserCredential : NSObject

/**
 * Username of the credential.
 */
@property (readonly) NSString *username;

/**
 * Password of the credential (empty string if N/A for this credential).
 */
@property (readonly) NSString *password;

/**
 * Domain of the credential (empty string if N/A for this credential).
 */
@property (readonly) NSString *domain;

/**
 * HA1 of the credential (empty string if N/A for this credential).
 */
@property (readonly) NSString *ha1String;

/**
 * The Portal User Token of the credential.
 */
@property (readonly) NSString *portalUserToken;

/**
 * Access token for OAuth2 bearer.
 */
@property (readonly) NSString *accessToken;

/**
 * The time until which the credential is valid.
 * When credentialExpiry is set to nil, then credential is only used once.
 */
@property (readonly) NSDate *credentialExpiry;


- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithUsername:(NSString *)username password:(NSString *)password domain:(NSString *)domain ha1String:(NSString *)ha1String NS_DESIGNATED_INITIALIZER;

/**
 * Constructor of a credential using username and password.
 * 
 * @param username username for this credential
 * @param password password for this credential
 */
+ (instancetype)credentialWithUsername:(NSString *)username andPassword:(NSString *)password;

/**
 * Constructor of a credential using username, password and domain.
 * 
 * @param username username for this credential
 * @param password password for this credential
 * @param domain domain for this credential (empty string if n/a)
 */
+ (instancetype)credentialWithUsername:(NSString *)username password:(NSString *)password andDomain:(NSString *)domain;

/**
 * Constructor of a credential using username, password, domain and HA1 string.
 * 
 * @param username username for this credential
 * @param password password for this credential (empty string if n/a)
 * @param domain domain for this credential (empty string if n/a)
 * @param ha1String HA1 string for this credential (empty string if n/a)
 */
+ (instancetype)credentialWithUsername:(NSString *)username password:(NSString *)password domain:(NSString *)domain andHa1String:(NSString *)ha1String;

/**
 * Constructor of a credential using username, password, domain and HA1 string.
 *
 * @param username username for this credential
 * @param password password for this credential (empty string if n/a)
 * @param domain domain for this credential (empty string if n/a)
 * @param ha1String HA1 string for this credential (empty string if n/a)
 * @param expiry Date when credential expires
 */
+ (instancetype)credentialWithUsername:(NSString *)username password:(NSString *)password domain:(NSString *)domain ha1String:(NSString *)ha1String expiry:(NSDate *)expiry;

/**
 * Constructor of a credential using OAuth2 access_token.
 *
 * @param accessToken OAuth2 access_token
 */
+ (instancetype)credentialWithAccessToken:(NSString *)accessToken;

/**
 * Constructor of a credential using OAuth2 access token and expiration time.
 *  When credentialExpiry is set to nil, then credential is only used once.
 *
 * @param accessToken OAuth2 access token
 * @param expiry Date when token expires.
 */
+ (instancetype)credentialWithAccessToken:(NSString *)accessToken expiry:(NSDate *)expiry;

/**
 * Constructor of a credential using Portal User Token.
 * 
 * @param portalUserToken token for this credential
 */
+ (instancetype)credentialWithPortalUserToken:(NSString *)portalUserToken;

/**
 * Constructor of a credential using Portal User Token.
 *
 * @param portalUserToken token for this credential
 * @param expiry Date when credential expires
 */
+ (instancetype)credentialWithPortalUserToken:(NSString *)portalUserToken expiry:(NSDate *)expiry;

@end

