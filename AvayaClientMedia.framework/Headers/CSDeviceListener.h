//
//  CSDeviceListener.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-21.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSDeviceListener_h
#define clientsdk_CSDeviceListener_h
#import <Foundation/Foundation.h>
#import "CSAudioDevicesEventListener.h"

@protocol CSDeviceListener <NSObject>
/**
* Add a new listener to be informed when there are audio device events.
*
* @param listener The new listener.
*/
-(void) addAudioDevicesEventListener:(id<CSAudioDevicesEventListener>) listener;
/**
* Remove a new listener to stop being informed when there are audio device events session.
*
* @param listener The listener to be removed.
*/
-(void) removeAudioDevicesEventListener:(id<CSAudioDevicesEventListener>) listener;
@end
#endif // clientsdk_CSDeviceListener_h
