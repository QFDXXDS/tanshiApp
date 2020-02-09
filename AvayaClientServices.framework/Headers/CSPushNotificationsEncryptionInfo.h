/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#include "CSPushNotificationsEncryptionScheme.h"

/**
 * Encryption information for Push Notifications.
 * This is only reported out by the Client SDK for
 * services such as Avaya Aura Messaging where incoming push notifications
 * are decrypted by an iOS Notification Service Extension, and not
 * by the Client SDK. Telephony related push notifications are
 * decrypted by the Client SDK and telephony encryption information
 * is not reported up to the application.
 */
@interface CSPushNotificationsEncryptionInfo : NSObject

/**
 * Encryption scheme reported by the server.
 */
@property (nonatomic, readonly) CSPushNotificationsEncryptionScheme encryptionScheme;

/**
 * Encryption key reported by the server.
 */
@property (nonatomic, readonly) NSString *encryptionKey;

@end

