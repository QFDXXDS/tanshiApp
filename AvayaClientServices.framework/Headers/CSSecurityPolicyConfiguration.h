/* Copyright Avaya Inc. */
#import <Foundation/Foundation.h>
#import "CSSCEPConfiguration.h"

/**
 * Security policy configuration for certificate revocation.
 */
typedef NS_ENUM(NSUInteger, CSSecurityPolicy) {
	
	/**
	 * Enable revocation check and treat all certificate revocation errors as fatal.
	 */
	CSSecurityPolicyRequired = 0,
	
	/**
	 * Enable revocation check and treat indeterminate certificate revocation errors as non-fatal.
	 * 
	 * Indeterminate errors are the errors reported when client application cannot fetch
	 * certificate revocation information from the revocation servers due to issues like
	 * server unreachable, network issues, server busy etc.
	 */
	CSSecurityPolicyBestEffort,
	
	/**
	 * Disable certificate revocation check.
	 * The revocation checks are restricted to cached results.
	 */
	CSSecurityPolicyDisabled
};

typedef NS_ENUM(NSUInteger, CSTLSProtocolVersion) {
	/**
	 *  TLS v1.0
	 */
	CSTLSProtocolVersionTLS_1_0 = 0,
	
	/**
	 *  TLS v1.1
	 */
	CSTLSProtocolVersionTLS_1_1 = 1,
	
	/**
	 *  TLS v1.2
	 */
	CSTLSProtocolVersionTLS_1_2 = 2,
};

typedef NS_ENUM(NSUInteger, CSTrustStoreMode) {
	
	/**
	 * Use only private trust for trust evaluation.
	 */
	CSTrustStoreModePrivateOnly = 0,
	
	/**
	 * Use private and system trust stores for trust evaluation.
	 */
	CSTrustStoreModePrivateAndSystem = 1
};


@interface CSSecurityPolicyConfiguration : NSObject

/**
 * A boolean value to specify the action to take when server identity validation fails.
 *
 * Applications that would like to ignore the server identity validation failures
 * and continue setting up the secure connection can configure this value
 * as @c YES. However, it is highly not recommended as to avoid any
 * man-in-the-middle attacks.
 * In some cases, where certain certificates do not have the necessary
 * attributes to comply with the server identity validation rules and
 * network administrator thinks the client applications are connecting
 * to trusted servers, can configure this settings to @c NO such
 * that such errors are ignored.
 *
 * Default value is @c YES
 */
@property (nonatomic) BOOL continueOnTLSServerIdentityFailure;

/**
 * An enumeration specifying applicable revocation policy.
 * 
 * The default value of the revocation policy is @c CSSecurityPolicyBestEffort.
 *
 * Client application's trust validation behavior for various
 * revocation policies.
 *
 * <ul>
 *  <li>
 *      @c CSSecurityPolicyDisabled: The revocation check will not
 *      be performed during certificate trust validation.
 *  </li>
 *  <li>
 *      @c CSSecurityPolicyBestEffort: The revocation check will be
 *      performed but any non-conclusive errors are not treated as "fatal".
 *  </li>
 *  <li>
 *      @c CSSecurityPolicyRequired: The revocation check will be
 *      performed and all errors are treated as "fatal".
 *  </li>
 * </ul>
 *
 * Certificate revocation is supported for macOS (OS X) only. 
 */
@property (nonatomic) CSSecurityPolicy revocationCheckPolicy;

/**
 * A boolean value to specify if the private trust store MUST be used for certificate
 * validations, if set to true.
 */
@property (nonatomic) BOOL  privateTrustStoreEnabled;

/**
 * A boolean value to specify if application private keychain should be used to store the security items.
 * If value is set to NO default keychain will be used.
 */
@property (nonatomic) BOOL  usePrivateKeychainForIdentityCertificate;

/**
 * An integer value specifying the percentage (0-100) of certificate's max age after which client
 * should issue a certificate renewal notification.
 * 
 * Default value of this parameter is 90%.
 */
@property (nonatomic, copy) NSNumber* certificateRenewalValue;

/**
 * Specifies minimum allowed TLS protocol version
 *
 * Default value of this parameter is @c CSTLSProtocolVersionTLS_1_0.
 *
 * Allowed TLS protocols
 *
 * <ul>
 *  <li>
 *      @c CSTLSProtocolVersionTLS_1_0 : All TLS protocol versions are allowed.
 *  </li>
 *  <li>
 *      @c CSTLSProtocolVersionTLS_1_1 : TLS 1.1 and above are allowed.
 *  </li>
 *  <li>
 *      @c CSTLSProtocolVersionTLS_1_2 : TLS 1.2 and above are allowed.
 *  </li>
 * </ul>
 */
@property (nonatomic, assign) CSTLSProtocolVersion minimumPermittedTLSProtocolVersion;

/**
 * Specifies the type of trust store to be used for trust evaluation.
 */
@property (nonatomic, assign) CSTrustStoreMode trustStoreMode;

/**
 * Specifies the black listed cipher suites which will not be included during
 * TLS connection negotiation.
 *
 * List of available Cipher Suites
 *
 * TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
 * TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384
 * TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384
 * TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384
 * TLS_DH_DSS_WITH_AES_256_GCM_SHA384
 * TLS_DHE_DSS_WITH_AES_256_GCM_SHA384
 * TLS_DH_RSA_WITH_AES_256_GCM_SHA384
 * TLS_DHE_RSA_WITH_AES_256_GCM_SHA384
 * TLS_DHE_RSA_WITH_AES_256_CBC_SHA256
 * TLS_DHE_DSS_WITH_AES_256_CBC_SHA256
 * TLS_DH_RSA_WITH_AES_256_CBC_SHA256
 * TLS_DH_DSS_WITH_AES_256_CBC_SHA256
 * TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384
 * TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384
 * TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384
 * TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384
 * TLS_RSA_WITH_AES_256_GCM_SHA384
 * TLS_RSA_WITH_AES_256_CBC_SHA256
 * TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256
 * TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256
 * TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256
 * TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256
 * TLS_DH_DSS_WITH_AES_128_GCM_SHA256
 * TLS_DHE_DSS_WITH_AES_128_GCM_SHA256
 * TLS_DH_RSA_WITH_AES_128_GCM_SHA256
 * TLS_DHE_RSA_WITH_AES_128_GCM_SHA256
 * TLS_DHE_RSA_WITH_AES_128_CBC_SHA256
 * TLS_DHE_DSS_WITH_AES_128_CBC_SHA256
 * TLS_DH_RSA_WITH_AES_128_CBC_SHA256
 * TLS_DH_DSS_WITH_AES_128_CBC_SHA256
 * TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256
 * TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256
 * TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256
 * TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256
 * TLS_RSA_WITH_AES_128_GCM_SHA256
 * TLS_RSA_WITH_AES_128_CBC_SHA256
 * TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA
 * TLS_RSA_WITH_AES_128_CBC_SHA
 * TLS_DHE_RSA_WITH_AES_128_CBC_SHA
 * TLS_RSA_WITH_AES_256_CBC_SHA
 *
 * Application can choose to blacklist cipher suites from the above list using
 * this API and the blacklisted ciphers will not be included in TLS connection
 * negotiation.
 *
 * Note: If user chooses to black list all available cipher suites, the library will
 * pick its default cipher suites for session negotiations.
 */
@property (nonatomic, copy) NSArray *blackListedCipherSuites;

@end
