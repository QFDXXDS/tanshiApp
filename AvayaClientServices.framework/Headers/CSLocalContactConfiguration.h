/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * For iOS there is no need to have the configuration information. So just enable this service by default.
 */
@interface CSLocalContactConfiguration : NSObject

/**
 * A Boolean value indicating whether the Local device provider is enabled.
 *
 */
@property (nonatomic) BOOL enabled;


@end
