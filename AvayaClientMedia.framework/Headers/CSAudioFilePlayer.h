/******************************************************************************/
/*                                                                            */
/* Copyright Avaya Inc.                                                       */
/*                                                                            */
/******************************************************************************/

#ifndef clientsdk_CSAudioFilePlayer_h
#define clientsdk_CSAudioFilePlayer_h
#import <Foundation/Foundation.h>

/**
 * Audio file player control interface
 */
@protocol CSAudioFilePlayer <NSObject>

/**
 * Audio Tones playable by the CSAudioFilePlayer.
 * Resources for these tones must be available at CSVoIPConfigurationAudio toneFilePath.
 */
typedef NS_ENUM(NSInteger, CSAudioTone)
{
    CSAudioToneUndefined = -1,
    CSAudioToneIncomingCallInternal,
    CSAudioToneIncomingCallExternal,
    CSAudioToneIncomingCallIntercom,
    CSAudioToneIncomingCallPriority,
    CSAudioToneIncomingCallAutoAnswer,
    CSAudioToneIncomingAutoCallback,
    CSAudioToneReorder,
    CSAudioToneIntercept,
    CSAudioToneBusy,
    CSAudioToneDial,
    CSAudioTonePublicDial,
    CSAudioToneRingback,
    CSAudioToneCoverage,
    CSAudioToneCallPickupAlert,
    CSAudioToneCallPickupEndAlert,
    CSAudioToneDtmfZero,
    CSAudioToneDtmfOne,
    CSAudioToneDtmfTwo,
    CSAudioToneDtmfThree,
    CSAudioToneDtmfFour,
    CSAudioToneDtmfFive,
    CSAudioToneDtmfSix,
    CSAudioToneDtmfSeven,
    CSAudioToneDtmfEight,
    CSAudioToneDtmfNine,
    CSAudioToneDtmfStar,
    CSAudioToneDtmfPound,
    CSAudioToneDtmfA,
    CSAudioToneDtmfB,
    CSAudioToneDtmfC,
    CSAudioToneDtmfD,
    CSAudioToneDtmfPause,
    CSAudioToneButtonClickEffect,
    CSAudioToneErrorBeep,
    CSAudioToneMaxValue
};

/**
 * Audio tone to play.  Resources for these tones must be available at CSVoIPConfigurationAudio toneFilePath.
 */
@property(nonatomic) CSAudioTone tone;

/**
 * Audio file to play.
 */
@property(nonatomic, copy) NSString *file;

/**
 * Audio tone/file looping flag.  TRUE to loop forever, FALSE to play once.
 */
@property(nonatomic) BOOL isLoop;

/**
 * Audio tone/file duration.  Number of milliseconds to play tone/file; zero to play the entire tone/file.
 */
@property(nonatomic) int durationMs;

/**
 * Audio tone/file gain, in range [0, 255]
 */
@property(nonatomic) int gain;

/**
 * Destintion to play tone/file.  TRUE to play on speakers, FALSE to mix with microphone.  Can be overridden by useMicrophone
 */
@property(nonatomic) BOOL useSpeaker;

/**
 * Play tone/file to stream.  TRUE to mix to stream, FALSE to not mix to stream.
 */
@property(nonatomic) BOOL useStream;


/**
 * Listener for audio tone/file start and stop events.
 */
@property(nonatomic, weak) id<CSAudioFilePlayerListener> audioFilePlayerListener;

/**
 * Signal the player to start the tone/file.
 * @return TRUE if player starts successfully; otherwise FALSE.
 */
- (BOOL)startPlaying;

/**
 * Signal the player to stop the tone/file.
 * @return TRUE if player stops successfully; otherwise FALSE.
 */
- (BOOL)stopPlaying;

/**
 * Query the player status.
 * @return TRUE if playing; otherwise FALSE.
 */
- (BOOL)isPlaying;

@end
#endif // clientsdk_CSAudioFilePlayer_h
