/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"

/**
 * Configuration information for IP Office.
 */
@interface CSIPOfficeConfiguration : NSObject

/**
 * A Boolean value indicating whether the IP Office provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * A Boolean value indicating whether to enable One-X Portal messaging service for IP Office 
 *
 */
@property (nonatomic, getter=isMessagingEnabled) BOOL messagingEnabled;

/**
 * A Boolean value indicating whether the IP Office contacts provider is enabled.
 *
 */
@property (nonatomic) BOOL contactsEnabled;

/**
 * A Boolean value indicating whether the IP Office presence provider is enabled.
 *
 */
@property (nonatomic) BOOL presenceEnabled;

/**
 * A Boolean value indicating whether the IP Office Centralized Call Log is enabled.
 */
@property (nonatomic) BOOL callLogEnabled;

/**
 * The signaling server to connect with
 */
@property (nonatomic, strong) CSServerInfo *server;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

/**
 * Messaging credential provider. The messaging service and server are not coupled to SIP service.
 */
@property (nonatomic, weak) id <CSCredentialProvider> messagingCredentialProvider;

/**
 * The URL of the primary messaging server
 */
@property (nonatomic, copy) NSURL *primaryMessagingServerUrl;

/**
 * The URL of the secondary messaging server
 */
@property (nonatomic, copy) NSURL *secondaryMessagingServerUrl;

@end
