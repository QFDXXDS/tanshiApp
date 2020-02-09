/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"
/**
 * Configuration information for CES.
 */
@interface CSCESConfiguration : NSObject

/**
 * A Boolean value indicating whether the CES provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * The signaling server to connect with
 */
@property (nonatomic, strong) CSServerInfo *server;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

/**
 * The voicemail PIN
 */
@property (nonatomic, copy) NSString *voicemailPIN;

@end
