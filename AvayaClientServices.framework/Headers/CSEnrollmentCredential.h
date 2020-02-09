/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSDefines.h"

/**
 * Represents credential that can be used for identity certificate enroll.
 *
 * <p>
 * Credentials consist of certificate common name and enrollment password.
 * </P>
 *
 * <p>
 * This interface includes all of the convenient methods for constructing an EnrollmentCredential.
 * </p>
 */

@interface CSEnrollmentCredential : NSObject

/**
 * Certificate common name of the credential.
 */
@property (readonly) NSString *commonName;

/**
 * Password of the credential.
 */
@property (readonly) NSString *enrollmentPassword;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithCommonName:(NSString *)commonName andPassword:(NSString *)password;

/**
 * Constructor of a credential using username and password.
 * 
 * @param commonName certificate common name for this credential
 * @param password enrollment password for this credential
 */
+ (instancetype)credentialWithCommonName:(NSString *)commonName andPassword:(NSString *)password;

@end

