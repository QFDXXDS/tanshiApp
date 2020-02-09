/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSVoiceMessagingStatusParameters.h"

@protocol CSVoiceMessagingServiceDelegate;

/**
 * The CSVoiceMessagingServiceDelegate object is accessible from the User object,
 * providing voicemail status updates.
 */
@interface CSVoiceMessagingService : NSObject

/**
 * The delegate responsible for voice messaging events.
 */
@property (nonatomic, weak) id<CSVoiceMessagingServiceDelegate> delegate;

/**
 * Get the voicemail number configured for the user
 */
@property (nonatomic, readonly) NSString *voicemailNumber;

/**
 * CSVoiceMessagingStatusParameters object indicating whether there is a voicemail Message waiting.
 */
@property (nonatomic, readonly) CSVoiceMessagingStatusParameters *voiceMessagingStatus;

@end

@protocol CSVoiceMessagingServiceDelegate <NSObject>
@optional

/**
 * Sent to indicate that voice messaging service is available.
 *
 * @param voiceMessagingService The voice messaging service associated with voicemail.
 */
- (void)voiceMessagingServiceDidBecomeAvailable:(CSVoiceMessagingService *)voiceMessagingService;

/**
 * Sent to indicate that voice messaging service is unavailable.
 *
 * @param voiceMessagingService The voice messaging service associated with voicemail.
 */
- (void)voiceMessagingServiceDidBecomeUnavailable:(CSVoiceMessagingService *)voiceMessagingService;

/**
 * Sent when the status of a feature has changed.
 *
 * @param voiceMessagingService The voice messaging service associated with voicemail.
 * @param voiceMessagingStatus  The updated voice messaging status information.
 */
- (void)voiceMessagingService:(CSVoiceMessagingService *)voiceMessagingService didChangeVoiceMessagingStatus:(CSVoiceMessagingStatusParameters *)voiceMessagingStatus;

/**
 * Sent when voice mail number is changed.
 *
 * @param voiceMessagingService The voice messaging service associated with voicemail.
 * @param voicemailNumber The voice mail number configured for the user.
 */
- (void)voiceMessagingService:(CSVoiceMessagingService *)voiceMessagingService didChangeVoicemailNumber:(NSString *)voicemailNumber;

@end
