//
//  CSAudioInterfaceIOS.h
//  scpmedia
//
//  Created by John Marshall on 2015-01-22.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSAudioInterfaceIOS_h
#define clientsdk_CSAudioInterfaceIOS_h
#import "CSAudioInterface.h"
#import <AudioToolbox/AudioToolbox.h>
#import <AudioUnit/AudioUnit.h>

@interface CSAudioInterfaceIOS : NSObject <CSAudioInterface>

- (instancetype)initWithAudioEngine:(void*)audioEngine;

@end

#endif // clientsdk_CSAudioInterfaceIOS_h
