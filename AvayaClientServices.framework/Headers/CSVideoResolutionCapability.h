#import <Foundation/Foundation.h>
#import "CSVideoResolutionPreference.h"

/**
 * Class representing the maximum resolution that can supported for
 * a video stream during a multi video stream conference call.
 * Different video streams will have a different maximum resolution
 * based on the capabilities of the conference server and the limitations
 * of local CPU/platform, and provisioned bandwidth and resolution settings.
 **/

@interface CSVideoResolutionCapability : NSObject <NSCopying>

/**
 * Maximum video resolution that can be supported.
 **/

@property (nonatomic, readonly) CSVideoResolutionForMultiVideoStreaming maxSupportedVideoResolution;

@end
