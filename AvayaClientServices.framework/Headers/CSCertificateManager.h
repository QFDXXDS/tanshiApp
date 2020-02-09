/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSEnrollmentCredentialProvider.h"
#import "CSSCEPConfiguration.h"
#import "CSCertificateInfo.h"
#import "CSSecurityPolicyConfiguration.h"

@class CSCertificateManager;

/**
 * Describes methods that are implemented by the delegate of a CSCertificateManager.
 *
 * @see ::CSCertificateManager::validateCertificateWithSecTrustRef:completionHandler:
 */
@protocol CSCertificateManagerDelegate <NSObject>

- (void)didFinishValidateCertificateWithSecTrustRef:(SecTrustRef)secTrustRef error:(NSError*)error;

@end

/**
 * Describes methods that are implemented by the delegate of a CSCertificateManager.
 *
 * @see ::CSCertificateManager::enrollWithConfiguration:enrollmentCredentialProvider:completionHandler:
 */
@protocol CSCertificateManagerEnrollmentDelegate <NSObject>

- (void)didEnrollCertificateWithSecTrustRef:(SecTrustRef)secTrustRef secIdentityRef:(SecIdentityRef)secIdentityRef result:(NSError*)result;

@end

/**
 * CSCertificateManagerClientIdentityDelegate is registered as a listener to get notified
 * about the client identity certificate's expiration status.
 *
 * The client application gets notified about the client certificate's expiration status by specifying number of
 * days before expiry calculated as per the configured security policy.
 *
 * @see ::CSSecurityPolicyConfiguration::certificateRenewalValue
 */
@protocol CSCertificateManagerClientIdentityDelegate <NSObject>

- (void)certificateManager:(CSCertificateManager *)certManager clientIdentityWillExpireInDays:(NSInteger)daysToExpire;


#if !TARGET_OS_IPHONE
/**
 * Called every time Client SDK needs to access keychain.
 * Set {@link CSSecurityPolicyConfiguration::usePrivateKeychainForIdentityCertificate} to true if app wants to use
 * the private keychain.
 * If the private keychain is not provided
 * {@link CSCertificateManager::enrollWithConfiguration:enrollmentCredentialProvider:completionHandler:} will fail.
 *
 * The client provides either the reference to the unlocked keychain or error in case if the application
 * decides to not use the private keychain or it fails to create one.
 * The keychain provided will be used to store the security items to avoid using the default keychain shared between
 * all apps.
 *
 * @param certificateManager The certificate manager instance sending the message.
 * @param completionHandler The callback to invoke with the reference to unlocked keychain
 * and error in case of failure.
 *							@c secKeychain A reference to an unlocked private keychain. nil in case of an error.
 *							@c error Is an object describing failure reason. nil if operation succeeded.
 */
@optional
- (void)certificateManager:(CSCertificateManager *)certificateManager
didRequestAccessToPrivateKeychainWithCompletionHandler:(void (^)(SecKeychainRef secKeychain, NSError *error))completionHandler;
#endif

@end

/**
 * Certificate manager class allows application developers to configure and make
 * use of the library's client/server certificate trust validation logic.
 * It allows specification of a client identity certificate, configure a
 * private trust store and certificate trust validation of all the connections,
 * application is making on its own.
 *
 *
 * The developers can use the {@link #setCertificates:error:} method
 * to create a private trust store. It (private trust store) is an application
 * managed certificate store that contains the Root and Intermediate CA certificates
 * trusted (known as "trusted anchors") by an application. The private trust store is
 * used to validate the server/client certificate chain for all the secure connections
 * made by an application.
 *
 *
 * The private trust store has following advantages over the conventional system
 * certificate stores provided by Operating System -
 *
 * <ul>
 *      <li>The private trust store offers a <i>sandbox</i> certificate store
 *      exclusively used and managed by an application.</li>
 *
 *      <li>The trusted anchors (certificates) in the private trust store are
 *      not shared with trusted anchors from system certificate store.</li>
 *
 *      <li>Application administrators choose to distribute only necessary trusted
 *      CA certificates in a controlled way, not worrying for any rouge CA
 *      certificate being added to the private trust store.
 *      </li>
 *
 *      <li>Application can <i>create</i> and <i>delete</i> the private trust store without
 *      affecting the system certificate stores and thus affecting other connection-oriented
 *      applications.
 *      </li>
 * </ul>
 *
 * The private trust store allows application to be more secure. For example, consider a scenario
 * where a CA inadvertently had issued certificates and revoked those later on. CA publishes the
 * certificate status information so that application may choose to query and proceed. However,
 * revocation status check process has its own challenges making it unsuitable, causing the
 * rouge servers to be trusted by an applications. Such cases can be easily managed by using
 * the private trust store. Application administrator may simply remove the corresponding CA
 * certificate that had issued invalid certificates such that insecure connections cannot
 * be established with the server.
 *
 * This class allows an application to store a client identity certificate which can be used to
 * pass on to the server upon server's request during TLS Mutual Authentication. A client identity
 * certificate is trust validated by the server and untrusted certificate will be rejected by the
 * server by issuing SSL Alert and severing the connection.
 *
 * The client applications can register a certificate status listener to get notified when client
 * identity certificate is about to expire. This notification serves as a reminder for an user
 * to begin requesting a renewed certificate for this application. This notification period
 * can be configured using {@link CSSecurityPolicyConfiguration}.
 *
 * Applications that have been using default certificate trust validation logic, can now delegate
 * the trust validation request to this class. The certificate validation methods offered by this class
 * allows the use of the private trust store or system trust store. Also, certain behavior
 * of these methods can be preconfigured based on the application deployment scenarios via
 * {@link CSSecurityPolicyConfiguration}.
 *
 */
@interface CSCertificateManager : NSObject

/**
 * Delegate used to handle events related to client identity certificate's status.
 */
@property (nonatomic, weak) id<CSCertificateManagerClientIdentityDelegate> clientIdentityDelegate;

/**
 * Returns information about the certificates stored in the private trust store.
 *
 * This method returns an array of {@link CSCertificateInfo} objects from the private trust store
 * only. An attempt to retrieve the certificate information while private trust store is not
 * created is returned with @c nil array.
 *
 * The {@link CSCertificateInfo} class object represents a selected set of X.509 certificate
 * attributes that can be used for informative purpose, for example, displaying the existing
 * trusted anchors (CA certificates) to client application's users.
 * 
 * @return An array of {@link CSCertificateInfo} if the private trust store exists;
 *		   @c nil in case the private trust store is absent.
 *
 * @see CSCertificateManager::isCertificateStoreInUse
 */
- (NSArray *)appCertificatesInfo;

/**
 * Returns information about the client identity certificate in use.
 *
 * This method returns a {@link CSCertificateInfo} object from the current client identity certificate.
 *
 * The {@link CSCertificateInfo} class object represents a selected set of X.509 certificate
 * attributes that can be used for informative purpose, for example, displaying the current
 * client identity certificate to client application's users.
 *
 * @return A {@link CSCertificateInfo} if a client identity certificate is set;
 *		   @c nil in case the client identity certificate is nil.
 *
 */
- (CSCertificateInfo *)clientIdentityCertificateInfo;

/**
 * Returns a list of certificates stored in the private trust store.
 *
 * This method returns a certificates stored in the private trust store as an array
 * of @c SecCertificateRef. This method can be used as an alternative to
 * {@link #appCertificatesInfo}, where client application wants to
 * use their own certificate information parsing logic.
 *
 * @return An array of @c SecCertificateRef objects if private trust store exists;
 *         @c nil when private trust store is absent.
 *
 * @see CSCertificateManager::appCertificatesInfo
 */
- (NSArray *)certificates;

/**
 * Deletes an existing private trust store.
 *
 * Client application can delete an existing private trust store if it wants to modify the
 * certificates or it wants to use system certificate stores supplied by the OS.
 *
 * This method deletes the private trust store only. An attempt to delete other trust
 * stores is ignored.
 *
 * @see CSCertificateManager::isCertificateStoreInUse
 */
- (void)deleteCertStore;

/**
 * Returns the private trust store status.
 *
 * This method can be used to determine if a client application has successfully creates its
 * own trust store. It can also be used to check if the private trust store already exists.
 *
 * @return @c YES  The private trust store exists.
 *         @c NO The private trust store is absent.
 *
 * @see CSCertificateManager::setCertificates
 */
- (BOOL)isCertificateStoreInUse;


/**
 * Creates the private trust store using supplied trusted anchors (Root and Intermediate CA certificates).
 *
 * This method creates the private trust store if one does not exists. Unlike system certificate stores,
 * the client application can configure only one trust store.The Root and Intermediate CA certificates
 * can be added while creating the trust store and cannot be modified subsequently; any such modification
 * attempts result into an error. In order to modify existing private trust store, a call to 
 * {@link CSCertificateManager::deleteCertStore} is required followed by {@link CSCertificateManager::setCertificates:error:}.
 *
 * Before calling this method, client applications must ensure the 
 * {@link CSSecurityPolicyConfiguration::privateTrustStoreEnabled} property is enabled.
 * 
 * @param certificates CA certificates trusted by the client application.
 * @param error  If operation is successful @c error is nil. If an error occurred it contains an object
 *               describing the error.
 *
 * @return @c YES If operation is successful and private trust store has been created.
 *         @c NO If operation is failed; detailed error information is available via @c error object.
 */
-(BOOL)setCertificates:(NSArray*)certificates error:(NSError**)error;


/**
 * Performs a trust validation of a certificate chain to determine if the secure connection with the peer
 * can be trusted.
 *
 * While establishing secure connection, the certificate chain is received as part of SSL Handshake that can be
 * validated using this method. The validation result determines if the connection is secure and peer can be trusted.
 * This method performs trust validation asynchronously and upon completion a block is called to post the result.
 *
 * As per RFC 5280, the trust validation involves a certificate chain building which leads upto a trusted anchors.
 * For client application, if the private trust store has been configured, it will be @e solely used to build a
 * certificate chain. In a case when the private trust store is unavailable, the system certificate stores will be
 * used. This method does not fallback between the certificate stores (private trust store vs system certificate stores)
 * or shares them while looking for the trusted anchors.
 *
 *
 * The client application that wants perform hostname validation using service type can use @c expectedServiceDomain
 * parameter leaving @c expectedHostname empty and vice versa. These two fields are mutually exclusive.
 *
 * @param secTrustRef       A reference to the trust object to evaluate.
 * @param completionHandler A block to be called when the operation is completed.
 *                          @c error If the operation is successful this parameter is @c nil.
 *                          If an error occurred it contains an object describing the error.
 *
 *
 * @see CSCertificateManager::validateCertificateWithSecTrustRef(SecTrustRef) expectedServiceDomain:(NSString*) expectedHostname:(NSString*) peerPort:(int)  completionHandler:(void (^)(NSError *error))
 */
- (void)validateCertificateWithSecTrustRef:(SecTrustRef)secTrustRef completionHandler:(void (^)(NSError *error))completionHandler;



/**
 * Performs a trust validation of a certificate chain to determine if the secure connection with the peer
 * can be trusted.
 *
 * While establishing secure connection, the certificate chain is received as part of SSL Handshake that can be
 * validated using this method. The validation result determines if the connection is secure and peer can be trusted.
 * This method performs trust validation asynchronously and upon completion a block is called to post the result.
 *
 * As per RFC 5280, the trust validation involves a certificate chain building which leads upto a trusted anchors.
 * For client application, if the private trust store has been configured, it will be @e solely used to build a
 * certificate chain. In a case when the private trust store is unavailable, the system certificate stores will be
 * used. This method does not fall back between the certificate stores (private trust store vs system certificate stores)
 * or shares them while looking for the trusted anchors.
 *
 * As part of the trust validation, this method performs an extended hostname validation (known as "server identity validation")
 * by matching different identifiers as explained below. The configured hostname is internally supplied by each "Service" or
 * "Provider" calling this method. The client application can configure a policy to ignore the hostname validation errors. Such
 * policy can be set via {@link CSSecurityPolicyConfiguration::continueOnTLSServerIdentityFailure} property. By default, this method
 * currently ignores all hostname validation errors.
 *
 * The hostname is matched as per the following order of identifiers:
 *
 * -# The match is performed against identifiers like DNS name and IP address from certificate's subject alternative name (SAN)
 * attribute.
 * -# If subject alternative name attribute is unavailable, the match is performed against certificate's common name (CN) attribute.
 *
 * For SIP service domains, a full match is performed against URI and DNS parameters value from certificate's subject alternative name
 * attribute.
 *
 * For Wildcard certificates, a partial matching for DNS hostname is supported except for SIP service domains (RFC 5922).
 *
 * Following rules apply for partial matching:
 *
 * @li The match is performed at a single level sub-domain.
 *     @c *.example.com matches with @c foo.example.com
 *     @c *.*.example.com does not match with @c foo.bar.example.com
 * @li Internet TLDs (Top Level Domains) do not match.
 *     @c *.com does not match with @c example.com
 *     @c *.co.in does not match with @c example.co.in
 * @li Partial domain name match is not supported.
 *     @c f*.example.com does not match with @c foo.example.com
 * @li Partial matching for SIP service domain is not supported.
 *
 *
 * This method verifies certificate's revocation status, however, this feature is not supported on iOS. The revocation status
 * of an entire certificate chain is verified using OCSP or CRL. The revocation check using OCSP is preferred over CRL.
 * The client application can configure the security policy to be used while processing the revocation errors. The security
 * policy can be configured by setting {@link CSSecurityPolicyConfiguration::revocationCheckPolicy}.
 *
 *
 * @param secTrustRef           A reference to the trust object to evaluate.
 * @param expectedServiceDomain The domain the server is expected to be authoritative for.
 * @param expectedHostname      The hostname that was used to connect to the server that provided the certificates.
 * @param peerPort              The port number that was used to connect to the server that provided the certificates.
 * @param completionHandler     A block to be called when operation is completed.
 *                              @c error If the operation is successful this parameter is @c nil. If an error occurred it
 *                              contains an object describing the error.
 *
 * @see ::CSSecurityPolicyConfiguration::continueOnTLSServerIdentityFailure
 * @see ::CSSecurityPolicyConfiguration::revocationCheckPolicy
 * @see ::CSCertificateManager::validateCertificateWithSecTrustRef:completionHandler:
 */
- (void)validateCertificateWithSecTrustRef:(SecTrustRef)secTrustRef expectedServiceDomain:(NSString*)expectedServiceDomain expectedHostname:(NSString*)expectedHostname peerPort:(int)peerPort  completionHandler:(void (^)(NSError *error))completionHandler;

#if TARGET_OS_IPHONE
/**
 * Deletes a provisioned client identity certificate and a private key. Items are deleted from application keychain.
 *
 * Client application can modify the client certificate by deleting an existing certificate
 * and setting newer one.
 *
 * @param errorResult @c error If the operation is successful this parameter is @c nil. If an error occurred it
 *                    contains an object describing the error.
 *
 * @return @c YES A provisioned client identity certificate and a private key is deleted.
 *         @c NO Failure to delete the client identity certificate and a private key. The detailed error information
 *         is available @c error object.
 */
#else
/**
 * Deletes persistent reference to client identity used by Client SDK. Client SDK will stop using client identity.
 * Items are not removed from a keychain since it is application responsibility.
 *
 * @param errorResult @c error If the operation is successful this parameter is @c nil. If an error occurred it
 *                    contains an object describing the error.
 *
 * @return @c YES A provisioned client identity certificate and a private key is deleted.
 *         @c NO Failure to delete the client identity certificate and a private key. The detailed error information
 *         is available @c error object.
 */
#endif
- (BOOL)deleteClientIdentityWithError: (NSError **)errorResult;


/**
 * DEPRECATED since 241.0.0
 */
- (NSError *)setClientIdentityCertificateFromPKCS12Data: (NSData *)PKCS12Data
										   withPassword: (NSString *)password DEPRECATED_MSG_ATTRIBUTE("Use 'setClientIdentity:withCertificateChain:error:' instead.");

#if TARGET_OS_IPHONE
/**
 * Securely stores a client identity certificate and a private key to use during mutual authentication.
 * Items are recored in application keychain.
 *
 * A client identity certificate identifies each client and generally issued unique to each client.
 * This certificate is sent to the server upon request during the mutual authentication process as
 * part of the SSL Handshake.
 *
 * Client application using custom client certificate enrollment process can use this method to provision
 * retrieved client identity.
 *
 * @param secIdentity       A reference to @c SecIdentityRef containing the client identity mainly private key.
 * @param identityCertChain A reference to an array of @c SecCertificateRef containing client identity certificate chain.
 * @param errorResult       @c error If the operation is successful this parameter is @c nil. If an error occurred it
 *                          contains an object describing the error.
 *
 * @return @c YES If the client identity has been provisioned successfully.
 *         @c NO If method is failed to provision client identity. The error describing the failure is available via
 *         @c error object.
 */
#else
/**
 * Saves persistent reference to keychain items @c SecIdentityRef and @c SecCertificateRef.
 * When Client SDK starts it will restore client identity from a keychain.
 *
 * It is application responsibility to maintain client identity items lifetime in the keychain.
 * Note that application can use custom keychain to protect its data.
 *
 * A client identity certificate identifies each client and generally issued unique to each client.
 * This certificate is sent to the server upon request during the mutual authentication process as
 * part of the SSL Handshake.
 *
 * Client application using custom client certificate enrollment process can use this method to provision
 * retrieved client identity.
 *
 * @param secIdentity       A reference to @c SecIdentityRef containing the client identity.
 * @param identityCertChain A reference to an array of @c SecCertificateRef containing client identity certificate chain.
 * @param errorResult       @c error If the operation is successful this parameter is @c nil. If an error occurred it
 *                          contains an object describing the error.
 *
 * @return @c YES If the client identity has been provisioned successfully.
 *         @c NO If method is failed to provision client identity. The error describing the failure is available via
 *         @c error object.
 */
#endif
- (BOOL)setClientIdentity: (SecIdentityRef)secIdentity
	 withCertificateChain: (NSArray *)identityCertChain
					error: (NSError **)errorResult;


/**
 * Requests client identity certificate enrollment.
 *
 * A client identity certificate identifies each client and generally issued unique to each client.
 * This certificate is sent to the server upon request during the mutual authentication process as
 * part of the SSL Handshake.
 *
 * @param configuration					SCEP Configuration that will be used for client identity certificate enrollment.
 * @param enrollmentCredentialProvider	A reference to an enrollment credentials provider that challenges the client for
 * enrollment credentials (certificate common name and enrollment password).
 * @param completionHandler				A block to be called when operation is completed.
 *										@c identityCertChain A reference to an array of @c SecCertificateRef containing
 *										client identity certificate chain.
 *										@c secIdentity A reference to @c SecIdentityRef containing the client identity mainly private key.
 *										@c result Is an object describing enrollment result
 */
- (void)enrollWithConfiguration: (CSSCEPConfiguration *)configuration
   enrollmentCredentialProvider: (id<CSEnrollmentCredentialProvider>)enrollmentCredentialProvider
			  completionHandler: (void (^)(CFArrayRef identityCertChain, SecIdentityRef secIdentity, NSError *result))completionHandler;

/**
 * Returns a provisioned client identity.
 *
 * @return A reference to @c SecIdentityRef object containing client identity certificates
 *         and a private key. If client identity is not provisioned, it returns @c nil.
 *
 * @see CSCertificateManager::clientIdentityCertificateChain
 */
- (SecIdentityRef)clientIdentity;


/**
 * Returns a provisioned client identity certificate (chain).
 *
 * @return A reference to an array of @c SecCertificateRef containing client identity certificate chain.
 *         If the client identity is not provisioned, it returns @c nil.
 *
 * @see CSCertificateManager::clientIdentity
 */
- (CFArrayRef)clientIdentityCertificateChain;


@end

