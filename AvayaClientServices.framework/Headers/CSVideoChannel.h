#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "CSMediaDirection.h"

typedef NS_ENUM(NSUInteger, CSOverloadVideoStatus) {
	/** Video overload status is normal */
	CSOverloadVideoStatusNormal,
	/** Video overload status video frame resolution reduced*/
	CSOverloadVideoStatusResolutionReduced,
	/** Video overload status for deactivation of video */
	CSOverloadVideoStatusDeactivationRequested,
};

typedef NS_ENUM(NSUInteger, CSDisabledReason) {
	/** Video disable reason is not known */
	CSDisabledReasonNone,
	/** Local user has disabled the video */
	CSDisabledReasonLocalUser,
	/** Remote user has disabled the video */
	CSDisabledReasonRemoteUser,
	/** Video is disabled because of insufficinet bandwidth */
	CSDisabledReasonInsufficientBandwidth,
	/**Video is disabled because of platform limitations */
	CSDisabledReasonPlatformLimitations,
	/**Video is disabled because of wrong video layout selection*/
	CSDisabledReasonLayoutSelection
};

/**
* Interface to get video channel related information.
*/
@interface CSVideoChannel : NSObject <NSCopying>

- (instancetype)initWithChannelId:(int)channelId;

@property (nonatomic, readonly) int channelId;
@property (nonatomic, readonly) CSMediaDirection requestedDirection;
@property (nonatomic, readonly) CSMediaDirection negotiatedDirection;
@property (nonatomic, readonly) bool enabled;
@property (nonatomic, readonly) CSDisabledReason disabledReason;
@property (nonatomic, readonly) CSOverloadVideoStatus overloadVideoStatus;
@property (nonatomic, readonly) bool isPresentationChannel;

@end
