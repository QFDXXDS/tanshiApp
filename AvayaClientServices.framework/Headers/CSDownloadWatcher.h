/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@interface CSDownloadWatcher : NSObject

/**
 * This function allows clients to cancel pending download request
 */
- (void)cancel;

@end
