/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Set of additional values that are passed to Download Service's completion handler.
 */
@interface CSDownloadResultInfo: NSObject

- (instancetype)initWithETag:(NSString *)eTag isNotModified:(BOOL)isNotModified actualLocationURL:(NSURL *)actualLocationURL isMovedPermanently:(BOOL)isMovedPermanently;

/**
 * Value of HTTP 1.1 entity tag returned by server.
 */
@property (nonatomic, readonly, copy) NSString *eTag;

/**
 * A boolean value indicating whether the data was not modified. It is calculated by server based on the ETag passed in the optional parameters.
 */
@property (nonatomic, readonly) BOOL isNotModified;

/**
 * New target URL if redirection happens. Contains the last URL in redirection chain.
 */
@property (nonatomic, readonly, copy) NSURL *actualLocationURL;

/**
 * Were all of the redirections in the redirection chain permanent?
 */
@property (nonatomic, readonly) BOOL isMovedPermanently;

@end
