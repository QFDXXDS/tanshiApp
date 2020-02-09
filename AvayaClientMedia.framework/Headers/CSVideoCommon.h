//
//  CSVideoCommon.h
//  scpmedia
//
//  Created by Nathan Peacock.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSVideoCommon_h
#define clientsdk_CSVideoCommon_h

#ifdef __cplusplus

	namespace clientsdk {
		namespace media {
			struct IVideoFrame;
			struct IVideoSink;
			struct IVideoSource;
		}
	}

	typedef struct clientsdk::media::IVideoFrame  IVideoFrame_t;
	typedef struct clientsdk::media::IVideoSink   IVideoSink_t;
	typedef struct clientsdk::media::IVideoSource IVideoSource_t;

#else // objective-c

	struct IVideoFrame;
	struct IVideoSink;
	struct IVideoSource;

	typedef struct IVideoFrame  IVideoFrame_t;
	typedef struct IVideoSink   IVideoSink_t;
	typedef struct IVideoSource IVideoSource_t;

#endif

@protocol CSVideoSink
- (void) handleVideoFrame:(IVideoFrame_t*)pVideoFrame;
@end

@protocol CSVideoSource
- (void) setVideoSink:(id<CSVideoSink>)videoSink;
@end

#endif
