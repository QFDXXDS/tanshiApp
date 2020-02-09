//
//  CSVideoRendererIOS.h
//  scpmedia
//
//  Created by Nathan Peacock.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSVideoRendererIOS_h
#define clientsdk_CSVideoRendererIOS_h
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES3/gl.h>
#import <QuartzCore/QuartzCore.h>
#import "CSVideoCommon.h"

typedef void (^CGSizeListener)(CGSize size);

@interface CSVideoRendererIOS : CAEAGLLayer <CSVideoSink>

@property (nonatomic, assign) CGSize videoFrameResolution __deprecated;

@property (atomic, readonly) CGSize videoFrameSize;

@property (atomic, strong) CGSizeListener videoFrameSizeListener;

@property BOOL paused;

@property BOOL mirrored;

@property (atomic) BOOL isRootWindow;

@property int countCheckRootWindow;

@end

#endif // clientsdk_CSVideoRendererIOS_h
