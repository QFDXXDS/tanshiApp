//
//  CSAudioRecordPlayStatusListener.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-21.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSAudioRecordPlayStatusListener_h
#define clientsdk_CSAudioRecordPlayStatusListener_h
#import <Foundation/Foundation.h>

@interface CSAudioRecordPlayStatusListener : NSObject
-(void)onInitRecording;
-(void)onStartRecording:(int)audioSessionId;
-(void)onStopRecording:(int)audioSessionId;
-(void)onInitPlayback;
-(void)onStartPlayback;
-(void)onStopPlayback;
@end

#endif // clientsdk_CSAudioRecordPlayStatusListener_h
