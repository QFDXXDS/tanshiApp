//
//  CSAudioDevice.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-21.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSAudioDevice_h
#define clientsdk_CSAudioDevice_h
#import <Foundation/Foundation.h>

/**
 * Audio device interface. A device that emits sound (speaker) or listens for sound (microphone)
 */
@interface CSAudioDevice : NSObject

/**
 * Enumeration for audio device type
 */
typedef NS_ENUM(NSUInteger, CSAudioDeviceType)
{
    /**
     * Audio device type is not defined
     */
	CSAudioDeviceNone,
    /**
     * Default audio device
     */
	CSAudioDeviceDefault,
    /**
     * Wired headset audio device
     */
	CSAudioDeviceWiredHeadset,
    /**
     * Handset audio device
     */
	CSAudioDeviceHandset,
    /**
     * Speaker audio device
     */
	CSAudioDeviceSpeaker,
    /**
     * Wireless headset audio device
     */
	CSAudioDeviceBluetoothHeadset,
    /**
     * Named audio device
     */
	CSAudioDeviceNamed
};

/**
 * Audio device name
 */
@property(atomic, copy) NSString* name;
/**
 * Audio device GUID
 */
@property(atomic, copy) NSString* guid;
/**
 * Audio device type
 */
@property(atomic, readonly) CSAudioDeviceType type;
/**
 * Pointer to native audio device
 */
@property(atomic) void* nativeAudioDevice;

/**
 * Constructs audio device of specific type
 */
- (instancetype)initWithType:(CSAudioDeviceType)type;
/**
 * Indicates if audio device is system default
 */
- (BOOL)isDefault;
/**
 * Indicates if audio device is built-in
 */
- (BOOL)isBuiltIn;

@end
#endif // clientsdk_CSAudioDevice_h
