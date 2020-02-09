/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSMediaTransportPreference.h"

/**
 * User configuration information for video.
 * This class provides the configuration data associated between a user and video properties.
 */
@interface CSVideoUserConfiguration : NSObject

/**
 * The feature type associated with this status.
 */
@property (nonatomic) CSMediaTransportPreference enabledPreference;

@end
