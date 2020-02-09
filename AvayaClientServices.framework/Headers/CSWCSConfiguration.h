/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * The CSWCSConfiguration class provides information about WCS configuration.
 * Object of this class is accessible via CSUserConfiguration.
 */
@interface CSWCSConfiguration : NSObject

/**
 * A Boolean value indicating whether the WCS is enabled. Value is read from config
 * but client can change it via this property so as to disable WCS.
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

@end
