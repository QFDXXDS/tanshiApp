/* Copyright Avaya Inc. */

#import "CSCapability.h"

/** A class representing multi video resolution capabilities of the Client SDK .
 * In addition to the properties exposed by <see cref="Capability"/>, this class
 * exposes a property that provides the maximum number of simultaneous receive-only
 * video channels that can be supported by the SDK and their maximum resolution,
 * based on the limitations of the local CPU/platform, bandwidth and resolution
 * configuration information.
 * Capability::allowed returns false for a point to point video call,
 * or if the conference call does not support multiple video streams. In this case
 * maxSupportedVideoResolutions returns nil.
 */

@interface CSMaxSupportedVideoResolutionsCapability : CSCapability

/** 
 * Returns a list of <see cref="CSVideoResolutionCapability"/> representing
 * the maximum video resolution of the receive-only video streams that can
 * be simultaneously supported by the Client SDK.
 * It returns nil if this object is associated with a call that
 * does not support multiple video streams.
 */

@property (nonatomic, readonly) NSArray *maxSupportedVideoResolutions;

@end
