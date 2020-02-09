/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@interface CSVoiceMessagingStatusParameters : NSObject

/**
 * Indicates if there is a new voice mail message pending.
 */
@property (nonatomic, readonly, getter=isMessageWaiting) BOOL messageWaiting;


- (instancetype)initWithVoiceMessagingStatus:(BOOL)messageWaiting;

@end
