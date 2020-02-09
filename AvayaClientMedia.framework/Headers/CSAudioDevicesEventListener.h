//
//  CSAudioDevicesEventListener.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-21.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSAudioDevicesEventListener_h
#define clientsdk_CSAudioDevicesEventListener_h
#import <Foundation/Foundation.h>

@protocol CSAudioDevicesEventListener <NSObject>
-(void)onWiredHeadSetPluggedIn;
-(void)onWiredHeadSetUnPlugged;
-(void)onBluetoothHeadSetConnected;
-(void)onSpeakerConnected;
-(void)onBluetoothHeadSetDisconnected;
-(void)onBluetoothAdapterStateChanged:(BOOL) state;
@end
#endif // clientsdk_CSAudioDevicesEventListener_h
