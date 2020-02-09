/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCertificateBasicConstraint.h"

/**
 *
 * Represents X.509 certificate attributes information to be consumed by client applications.
 *
 */
@interface CSCertificateInfo : NSObject

/**
 * Certificate subject summary. Simple string represents a human understandable certificate subject summary.
 */
@property (nonatomic, readonly) NSString *subjectSummary;

/**
 * Certificate serial number.
 */
@property (nonatomic, readonly) NSString *serialNumber;

/**
 * Certificate Subject Name
 */
@property (nonatomic, readonly) NSString *subjectName;

/**
 * Certificate Issuer Name.
 */
@property (nonatomic, readonly) NSString *issuerName;

/**
 * Local time before which certificate is not valid.
 */
@property (nonatomic, readonly) NSDate *notValidBeforeDate;

/**
 * Local time after which certificate is no longer valid
 */
@property (nonatomic, readonly) NSDate *notValidAfterDate;

/**
 * Certificate hash computed using SHA-1
 */
@property (nonatomic, readonly) NSString *thumbprintSHA1;

/**
 * Certificate hash computed using SHA-256
 */
@property (nonatomic, readonly) NSString *thumbprintSHA256;

/**
 * Subject alternate Name attribute
 */
@property (nonatomic, readonly) NSArray *subjectAlternativeName;

/**
 * Certificate extensions represented in one-line format.
 */
@property (nonatomic, readonly) NSString *extension;

/**
 * Certificate Extended Key Usage Extension property.
 */
@property (nonatomic, readonly) NSString *extendedKeyUsage;

/**
 * Certificate is a CA certificate if set. 
 */
@property (nonatomic, readonly) BOOL isCACertificate;

/**
 * If basic constraint extension is available returns an object describing this extension
 */
@property (nonatomic, readonly) CSCertificateBasicConstraint *basicConstraints;

/**
 * DEPRECATED since 252.0.0
 */
- (instancetype)initWithCertificateSerialNumber:(NSString*)serialNumber
								 subjectSummary:(NSString*)subjectSummary
									subjectName:(NSString*)subjectName
									 issuerName:(NSString*)issuerName
							 notValidBeforeDate:(NSDate*)notValidBeforeDate
							  notValidAfterDate:(NSDate*)notValidAfterDate
								 thumbprintSHA1:(NSString*)thumbprintSHA1
							   thumbprintSHA256:(NSString*)thumbprintSHA256
						 subjectAlternativeName:(NSArray*)subjectAlternativeName
								isCACertificate:(BOOL)isCACertificate
									  extension:(NSString*)extension
							   extendedKeyUsage:(NSString*)extendedKeyUsage DEPRECATED_MSG_ATTRIBUTE("Use 'initWithCertificate:' instead.");

/**
 * Creates certificate info from provided certificate \a SecCertificateRef.
 * API has been porvided since on iOS platfrom there is no system API to
 * fetch certificate information.
 */
- (instancetype)initWithCertificate: (SecCertificateRef)cert;

/**
 * Creates certificate info from provided certificate \a SecCertificateRef.
 * API has been porvided since on iOS platfrom there is no system API to
 * fetch certificate information.
 */
+ (instancetype)certificateInfoForCertificate: (SecCertificateRef)cert;

@end
