//
//  CSSpeakerDevice.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-21.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSSpeakerDevice_h
#define clientsdk_CSSpeakerDevice_h
#import <Foundation/Foundation.h>
#import "CSAudioDevice.h"

@interface CSSpeakerDevice : CSAudioDevice

@property(atomic) void* nativeDevice;

- (instancetype)initWithType:(CSAudioDeviceType)type;
- (instancetype)initWithNativeDevice:(void*)device;

@end
#endif
