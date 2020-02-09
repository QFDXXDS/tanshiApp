/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Data that is common for a HTTP Client
 *
 */
@interface CSHTTPClientConfiguration : NSObject

/**
 * Local video response timeout (in seconds)
 *
 */
@property (nonatomic, assign) NSUInteger localVideoResponseTimeout;

/**
 * How long to wait for a final server response on every outgoing call transaction (in seconds)
 *
 */
@property (nonatomic, assign) NSUInteger responseTimeout;

/**
 * How long to wait for a server response on every single network transaction (in seconds)
 *
 */
@property (nonatomic, assign) NSUInteger fastResponseTimeout;

/**
 * Controls whether the codec selection on the answerer side is done based on the codec preferences of
 * the calling UA or the answering UA. By default, a common codec is selected based on the preferences of the
 * calling UA.
 *
 */
@property (nonatomic, assign) BOOL selectCodecBasedOnCallerPreferences;

@end
