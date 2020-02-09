/******************************************************************************/
/*                                                                            */
/* Copyright Avaya Inc.                                                       */
/*                                                                            */
/******************************************************************************/

#ifndef clientsdk_CSAudioFilePlayerListener_h
#define clientsdk_CSAudioFilePlayerListener_h
#import <Foundation/Foundation.h>

@protocol CSAudioFilePlayer;

/**
 * Audio file player notification interface
 */
@protocol CSAudioFilePlayerListener

/**
 * Signal that the player has started playing.
 * @param player The audio file player control interface.
 */
- (void)audioFileDidStartPlaying:(id<CSAudioFilePlayer>)player;

/**
 * Signal that the player has stopped playing.
 * @param player The audio file player control interface.
 */
- (void)audioFileDidStopPlaying:(id<CSAudioFilePlayer>)player;

@end


#endif // clientsdk_CSAudioFilePlayerListener_h
