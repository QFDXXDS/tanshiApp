/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * User configuration information for SCEP (Simple Certificate Enrollment Protocol).
 * This protocol is used to retrieve Client Identity certificates from the enrollment server.
 */
@interface CSSCEPConfiguration : NSObject

/**
 * A string value representing an URL of SCEP (Simple Certificate Enrollment Protocol) server.
 * This URL is used to download PKCS #12 file containing an identity certificate and its private key.
 */
@property (nonatomic, copy) NSURL* serverUrl;

/**
 * A string value representing HTTP proxy server that can be between the client and the SCEP server.
 */
@property (nonatomic, copy) NSURL* HTTPProxy;

/**
 * A string value representing Common name (CN) used in the subject of a SCEP certificate request.
 */
@property (nonatomic, copy) NSString* certificateCommonName;

/**
 * A string value representing the part of the certificate subject Distinguished Name
 * (DN) that will be common to all clients.
 * It must begin with a "/" and may include OU, O, L, ST, and C values.
 * The default value is the empty string. It is recommended that a forward-slash character "/"
 * is used as a separator between components, as commas have been found not to work with some servers.
 */
@property (nonatomic, copy) NSString* certificateDistinguishedName;

/**
 * A string value representing an identifier for the CA certificate with which the certificate
 * request is to be signed, if the server hosts multiple certificate authorities.
 */
@property (nonatomic, copy) NSString* certificateCAIdentifier;

/**
 * A string value representing the password to be included (if not empty)
 * in the challengePassword attribute of an SCEP certificate request.
 */
@property (nonatomic, copy) NSString* challengePassword;

/**
 * A numeric value representing the bit length of the public and private keys
 * generated for the SCEP certificate request.
 */
@property (nonatomic) NSInteger certificateKeyLength;

/**
 * A boolean value representing the client behavior if the SCEP server indicates
 * that the certificate request is pending manual approval.
 * If false then the SCEP server will be periodically polled in the background.
 * Provide an indication that the certificate request is pending
 * but do not prevent the application from being used.
 * If false then the application is prevented from being used until a certificate is received
 * or the request is rejected.
 */
@property (nonatomic) BOOL requestWaitingApproval;
@end
