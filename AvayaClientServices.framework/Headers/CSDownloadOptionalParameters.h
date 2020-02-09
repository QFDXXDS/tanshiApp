/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Set of optional parameters for Download service.
 */
@interface CSDownloadOptionalParameters: NSObject

- (instancetype)initWithETag:(NSString *)eTag;

/**
 * HTTP 1.1 entity tag that can be set for download request. Use value returned by Download Service's completion handler or empty string.
 */
@property (nonatomic, copy) NSString *eTag;

@end
