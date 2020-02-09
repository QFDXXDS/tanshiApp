#import <Foundation/Foundation.h>

/**
 * Enumeration of video resolutions supported for multi video streaming
 * conference calls.
 */

typedef NS_ENUM(NSUInteger, CSVideoResolutionForMultiVideoStreaming) {
	CSVideoResolutionForMultiVideoStreaming180p,
	CSVideoResolutionForMultiVideoStreaming360p,
	CSVideoResolutionForMultiVideoStreaming720p
};

typedef NS_ENUM(NSUInteger, CSVideoResolutionForMainVideoStreaming) {
    CSVideoResolutionForMainVideoStreaming180p,
    CSVideoResolutionForMainVideoStreaming360p,
    CSVideoResolutionForMainVideoStreaming720p,
    CSVideoResolutionForMainVideoStreaming1080p
};

/**
 * A class the client application's preference for receive only
 * video resolution for the multiple video channels that can 
 * be supported on the call. This class is used when setting
 * video preference information on the CSCall object.
 * @see CSCall::setVideoResolutionPreferences:videoChannelPreferences:completionHandler.
 * @deprecated Use {@link CSVideoResolutionPreferenceForMultiVideoStreaming}
 */
DEPRECATED_MSG_ATTRIBUTE("Use CSVideoResolutionPreferenceForMultiVideoStreaming instead")
@interface CSVideoResolutionPreference : NSObject <NSCopying>

- (instancetype)initWithVideoResolution:(CSVideoResolutionForMultiVideoStreaming)videoResolution;

/**
 * Video resolution preference.
 */
@property (nonatomic, readonly) CSVideoResolutionForMultiVideoStreaming videoResolution;

@end


/**
 * A class the client application's preference for receive only
 * video resolution for the multiple video channels that can
 * be supported on the call. This class is used when setting
 * video preference information on the CSCall object.
 * @see CSCall::setVideoResolutionPreferences:videoChannelPreferences:completionHandler.
 */

@interface CSVideoResolutionPreferenceForMultiVideoStreaming : NSObject <NSCopying>

- (instancetype)initWithVideoResolution:(CSVideoResolutionForMultiVideoStreaming)videoResolution;

/**
 * Video resolution preference.
 */
@property (nonatomic, readonly) CSVideoResolutionForMultiVideoStreaming videoResolution;

@end


@interface CSVideoResolutionPreferenceForMainVideoStreaming : NSObject <NSCopying>

- (instancetype)initWithVideoResolution:(CSVideoResolutionForMainVideoStreaming)videoResolution;

/**
 * Video resolution preference.
 */
@property (nonatomic, readonly) CSVideoResolutionForMainVideoStreaming videoResolution;

@end

