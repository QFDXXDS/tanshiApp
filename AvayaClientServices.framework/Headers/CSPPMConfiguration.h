//
/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"

/**
 * The Personal Profile Manager configuration class that contains the configuration data specific for this User.
 * In some deployments, the PPM server address may be different from the initial SIP proxy server address.
 */
@interface CSPPMConfiguration : NSObject

/**
 * A Boolean value indicating whether the PPM provider is enabled.
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * A Boolean value indicating whether PPM contacts are enabled.
 */
@property (nonatomic) BOOL contactsEnabled;

/**
 * A Boolean value indicating whether 24x7 Call Journaling are enabled.
 */
@property (nonatomic) BOOL callJournalingEnabled;

/**
 * The PPM server to connect with
 */
@property (nonatomic, strong) CSServerInfo *server;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;


@end
