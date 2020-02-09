//
//  CSVideoCapturerIOS.h
//  rvMedia
//
//  Created by David McGarry on 3/11/11.
//  Copyright 2011 RADVISION Inc. All rights reserved.
//

#import "CSVideoCommon.h"

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

extern NSString *const CSVideoCapturerErrorDomain;

typedef NS_ENUM(NSInteger, CSVideoCapturerErrorCode)
{
	CSVideoCapturerErrorCode_RuntimeError = 1,
	CSVideoCapturerErrorCode_DeviceNotFound,
	CSVideoCapturerErrorCode_DeviceInUse,
	CSVideoCapturerErrorCode_UnknownError,
	CSVideoCapturerErrorCode_UnsupportedInput,
	CSVideoCapturerErrorCode_UnsupportedOutput,
	CSVideoCapturerErrorCode_UnsupportedSessionPreset,
	CSVideoCapturerErrorCode_ApplicationIsNotAuthorizedToUseDevice,
};

typedef NS_ENUM(NSUInteger, CSVideoCapturerParams)
{
	CSVideoCapturerParams_640x480_480x640 = 0,
	CSVideoCapturerParams_640x480_640x360,
	CSVideoCapturerParams_640x480_624x352,
	CSVideoCapturerParams_640x480_480x272,
	CSVideoCapturerParams_480x360_480x272,
	CSVideoCapturerParams_352x288_320x192,
	CSVideoCapturerParams_352x288_320x180,
	CSVideoCapturerParams_LandscapeOnly_480x272,
	CSVideoCapturerParams_LandscapePortrait_480x272,
	CSVideoCapturerParams_MaxIndex,
};

typedef NS_ENUM(NSInteger, CSVideoCameraPosition)
{
	CSVideoCameraPositionUnspecified = AVCaptureDevicePositionUnspecified,
	CSVideoCameraPositionBack		 = AVCaptureDevicePositionBack,
	CSVideoCameraPositionFront		 = AVCaptureDevicePositionFront,
};

typedef NS_ENUM(NSInteger, CSVideoCapturerInterruptionReason)
{
	CSVideoCapturerInterruptionReason_Unspecified				= 0,
	CSVideoCapturerInterruptionReason_InUseByAnotherClient		= AVCaptureSessionInterruptionReasonVideoDeviceInUseByAnotherClient,
	CSVideoCapturerInterruptionReason_NotAvailableInBackground	= AVCaptureSessionInterruptionReasonVideoDeviceNotAvailableInBackground,
	CSVideoCapturerInterruptionReason_NotAvailableWithMultipleForegroundApps = AVCaptureSessionInterruptionReasonVideoDeviceNotAvailableWithMultipleForegroundApps,
};


@protocol CSVideoCapturerDelegate <NSObject>

- (void) videoCapturerRuntimeError:(NSError *)error;

@optional

- (void) videoCapturerWasInterruptedWithReason:(CSVideoCapturerInterruptionReason)reason;
- (void) videoCapturerWasInterrupted;
- (void) videoCapturerInterruptionEnded;

@end


@interface CSVideoCapturerIOS : NSObject <CSVideoSource>

@property (atomic, strong) id<CSVideoSink> videoSink;
@property (atomic, strong) id<CSVideoSink> localVideoSink;
@property (nonatomic, weak) id<CSVideoCapturerDelegate> delegate;

- (void) setParams:(CSVideoCapturerParams)params;

- (void) setFrameRate:(int32_t)framesPerSecond;

- (BOOL) hasVideoCameraAtPosition:(CSVideoCameraPosition)position;

- (void) useVideoCameraAtPosition:(CSVideoCameraPosition)position
					   completion:(void (^)(NSError *error))completion;

@end
