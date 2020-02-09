//
//  CSAudioInterface.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-21.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSAudioInterface_h
#define clientsdk_CSAudioInterface_h
#import <Foundation/Foundation.h>

#import "CSMicrophoneDevice.h"
#import "CSSpeakerDevice.h"
#import "CSAudioRecordPlayStatusListener.h"
#import "CSAudioDevicesEventListener.h"
#import "CSAudioFilePlayerListener.h"
#import "CSAudioFilePlayer.h"

@protocol CSAudioInterface <NSObject>

/**
 * Current muted state of the audio
 */
@property (nonatomic, readonly, getter=isMuted) BOOL audioMuted;

/**
 * Current muted state of the speaker
 */
@property (nonatomic, readonly, getter=isSpeakerMuted) BOOL speakerMuted;

/**
 * Array of (AudioDevice*) available Microphone devices.
 */
#if TARGET_OS_IPHONE
@property (nonatomic, readonly) NSArray* availableRecordDevices __deprecated;
#else
@property (nonatomic, readonly) NSArray* availableRecordDevices;
#endif

/**
 * Array of (AudioDevice*) available Playout devices.
 */
#if TARGET_OS_IPHONE
@property (nonatomic, readonly) NSArray* availablePlayDevices __deprecated;
@property (nonatomic, readonly) NSArray* availableAudioDevices __deprecated;
#else
@property (nonatomic, readonly) NSArray* availablePlayDevices;
#endif

#if TARGET_OS_IPHONE
@property(nonatomic,readonly)CSMicrophoneDevice* activeMicrophone __deprecated;
@property(nonatomic,readonly)CSSpeakerDevice* activeSpeaker __deprecated;
#else
@property(nonatomic,readonly)CSMicrophoneDevice* activeMicrophone;
@property(nonatomic,readonly)CSSpeakerDevice* activeSpeaker;
#endif
    
#if TARGET_OS_IPHONE
@property(nonatomic, strong)CSMicrophoneDevice* userRequestedMicrophone __deprecated;
@property(nonatomic, strong)CSSpeakerDevice* userRequestedSpeaker __deprecated;
@property(nonatomic, strong)CSAudioDevice* userRequestedDevice __deprecated;
#else
@property(nonatomic, strong)CSMicrophoneDevice* userRequestedMicrophone;
@property(nonatomic, strong)CSSpeakerDevice* userRequestedSpeaker;
#endif
    
@property(nonatomic, assign) id<CSAudioDevicesEventListener> delegate;

-(BOOL)isBluetoothActive;
-(void)startBluetooth;
-(void)stopBluetooth;
-(BOOL)isBluetoothConnected;
-(BOOL)isHeadsetConnected;
-(BOOL)isSpeakerConnected;

/**
 * Sets the dynamic payload type for telephony events.
 * @param payloadType The new payloadType for telephony events.
 *
 * @return true if the input value is accepted because it is between 96-127;
 *         false is returned when the input value is not accepted.
 */
- (BOOL)setTelephonyEventPayloadType: (int)payloadType;

/**
 * Get the telephony event payload type.
 *
 * @return payload type set for telephony events.
 */
- (int)getTelephonyEventPayloadType;


/**
 * Set the muted state of the audio
 * @param mute The new mute state of the audio.
 *
 * @return YES for success, NO for failure.
 */
- (BOOL)mute:(BOOL)mute;

/**
* Set the muted state of the speaker
* @param mute The new mute state of the speaker.
*
* @return YES for success, NO for failure.
*/
- (BOOL)muteSpeaker:(BOOL)mute;

- (void)registerRecordPlayStatusListener:(CSAudioRecordPlayStatusListener*)listener;

/**
 * Set the speaker audio gain
 * @param gain The new audio gain [0, 255].
 *
 * @return YES for success, NO for failure.
 */
- (BOOL)setSpeakerGain:(int)gain;

/**
 * Get the speaker audio gain
 *
 * @return The current audio gain [0, 255].
 */
- (int)speakerGain;

/**
 * Set the microphone audio gain
 * @param gain The new audio gain [0, 255].
 *
 * @return YES for success, NO for failure.
 */
- (BOOL)setMicrophoneGain:(int)gain;

/**
 * Get the microphone audio gain
 *
 * @return The current audio gain [0, 255].
 */
- (int)microphoneGain;

/** Create an Audio File Player.
 * @param pAudioFilePlayerListener CSAudioFilePlayerListener for start/stop events.
 * @return CSAudioFilePlayer to control audio playback.
 */
- (id<CSAudioFilePlayer>)createAudioFilePlayer:(id<CSAudioFilePlayerListener>)pAudioFilePlayerListener;

/**
 * This function sets DSCP value for audio.
 *
 * @param dscpValue DSCP value must be in range 0-63.
 * @return YES if DSCP value is set, otherwise NO.
 */
-(BOOL)setDscp:(int) dscpValue;


@end
#endif // clientsdk_CSAudioInterface_h
