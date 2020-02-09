/* Copyright Avaya Inc. */

#import "CSEnrollmentCredential.h"

/**
  * Interface used to represent a CSEnrollmentCredentialProvider.
  * An enrollment credential provider needs Certificate Common Name and enrollment password for the enrollment.
  */
@protocol CSEnrollmentCredentialProvider <NSObject>

/**
 * Request an enrollment credential.
 *
 * @return credential provided.
 */
- (CSEnrollmentCredential *)credentialProviderDidReceiveChallenge;

/**
 * Report the credential obtained from the previous credential challenge request has been accepted.
 */
- (void)credentialProviderDidReceiveCredentialAccepted;


@end
