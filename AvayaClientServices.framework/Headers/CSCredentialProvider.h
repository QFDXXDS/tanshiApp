/* Copyright Avaya Inc. */

#import "CSChallenge.h"
#import "CSUserCredential.h"

@protocol CSCredentialProvider <NSObject>

/**
 * Request a credential in response to a challenge.
 *
 * The challenge contains information about the credentials needed and the 
 * number of previous failures (if any).  
 * When credentials are available that can satisfy the challenge, the
 * completionHandler should be invoked.  This need not happen synchronously.
 *
 * Note that if, when originally passing the ICredentialProvider 
 * interface pointer into the SDK via a user configuration structure, a
 * username/domain was also provided in that same structure, then that
 * same username/domain must be provided in the ICredential passed to
 * the completion handler.
 *
 * Also note that if no credentials are available that can satisfy the
 * challenge, it is expected that a nil ICredential will be passed to
 * the completion handler to complete the challenge/response transaction.
 *
 * @param challenge Information about the challenge that prompted the caller to request a credential.
 * @param completionHandler The callback to invoke with the credential once it is known.
 */
- (void)credentialProviderDidReceiveChallenge:(CSChallenge *)challenge completionHandler:(void (^)(CSUserCredential *credential))completionHandler;

/**
 * Report the credential obtained from the previous credential challenge request has been accepted.
 *
 * @param challenge Information about the challenge that prompted the caller to request a credential.
 */
- (void)credentialProviderDidReceiveCredentialAccepted:(CSChallenge *)challenge;

/**
 * Report the previous credential challenge request has been cancelled. Credential Provider can ignore the
 * previous request. 
 *
 * @param challenge Information about the challenge that prompted the caller to request a credential.
 */
- (void)credentialProviderDidReceiveChallengeCancelled:(CSChallenge *)challenge;

@optional

/**
 * Checks whether preemptive challenge is supported by the associated credential provider.
 * A pre-emptive challenge will be issued prior to sending an request to the server. It can
 * be used in some scenarios (like OAuth), where the UI has credentials that the server can
 * validate. Default value is false. Some authentication schemes (like digest) require that
 * an unauthenticated request be sent to the server to generate a challenge response from the
 * server. An interface that implements CredentialProvider and responds with OAuth tokens
 * shall return true when this method is invoked. On contrary, an interface that returns
 * username/password type, shall return false.
 *
 * @return YES if preemptive challenge is supported
 */
- (BOOL)supportsPreEmptiveChallenge;

@end
