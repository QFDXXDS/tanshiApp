//
//  CSVideoInterface.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-22.
//  Copyright (c) 2015 Avaya. All rights reserved.
//

#ifndef clientsdk_CSVideoInterface_h
#define clientsdk_CSVideoInterface_h
#import "CSCPUThresholdConfiguration.h"
#import "CSCPUThresholdType.h"
#import "CSVideoCommon.h"

@protocol CSVideoInterfaceDelegate;

@protocol CSVideoInterface <NSObject>

/**
 * The delegate used to handle video-interface-related events.
 */
@property (nonatomic, assign) id<CSVideoInterfaceDelegate> delegate;


/**
* This function sets DSCP value for video.
*
* @param dscpValue DSCP value must be in range 0-63.
* @return YES if DSCP value is set, otherwise NO.
*/
-(BOOL)setDscp:(int) dscpValue;
/**
* Enable/Disables CPU Usage for video call(s) and control Tx/Rx
*/
-(BOOL)enableCPUAdaptiveVideo:(BOOL)bEnable;
/**
* Registers the threshold for monitoring overriding any registered(or default) threshold
* values for the given threshold type.
* @param threshold new threshold configuration
*/
-(BOOL)registerCPUThresholdConfig:(CSCPUThresholdConfiguration*) threshold;
/**
* Unregisters threshold from monitoring
* @param thresholdType threshold type
*/
-(BOOL)unRegisterCPUThresholdConfig:(CSCPUThresholdType) thresholdType;
/**
* Checks if the input threshold type was already registered for monitoring.
* @return YES If the threshold is available and updates the values threshold argument
* @param thresholdType threshold type
* @param threshold threshold
* It returns NO if no threshold was registered for thresholdType.
 */
-(BOOL)isThresholdAlreadyRegistered:(CSCPUThresholdType)thresholdType forThreshold:(CSCPUThresholdConfiguration*) threshold;
/**
 * Retrieves a VideoSink for the specified channel. This is used to attach a Video Source (capturer).
 * @return CSVideoSink A CSVideoSink associated with the videochannel iD
 * @param channelId id of video channel from which to retrieve the VideoSink.
 * It returns nil if channel does not exist or does not have a VideoSink.
 */
-(id <CSVideoSink>) getLocalVideoSink:(int) channelId;
/**
 * Retrieves a VideoSource for the specified channel. This is used to attach a Video Sink (renderer).
 * @return CSVideoSource A CSVideoSource associated with the videochannel iD
 * @param channelId id of video channel to retrieve the VideoSource from.
 * It returns nil if channel does not exist or does not have a VideoSource.
 */
-(id <CSVideoSource>) getRemoteVideoSource:(int) channelId;
/**
 * Returns if video packets are being received for the channel specified by the videoChannelID (only for AAC and MSS conferences).
 * @return true If the video is receiving for the specified channel ID.
 * @param channelId Id of video channel to retrieve the state of video receiving from.
 */
-(BOOL)isVideoreceiving:(int) channelId;

@end

@protocol CSVideoInterfaceDelegate <NSObject>

@optional
/**
 * Occurs 3 seconds after conference server stops sending video
 *
 * WARNING!!!
 * Unlike other Client Services callbacks, this event is NOT queued for delivery through
 * the client.ProcessCallbacks() method.  Therefore, the application must do the work to
 * process this event on the proper application thread.
 *
 * @param videoInterface The interface sending the message.
 * @param nChannelId ID of the channel associated with the video stream (used by media and signaling engines and client app)
 */
- (void)videoInterface:(id<CSVideoInterface>)videoInterface onVideoInactiveForChannelId:(int)nChannelId;

/**
 * Occurs when conference server continues sending video
 *
 * WARNING!!!
 * Unlike other Client Services callbacks, this event is NOT queued for delivery through
 * the client.ProcessCallbacks() method.  Therefore, the application must do the work to
 * process this event on the proper application thread.
 *
 * @param videoInterface The interface sending the message.
 * @param nChannelId ID of the channel associated with the video stream (used by media and signaling engines and client app)
 */
- (void)videoInterface:(id<CSVideoInterface>)videoInterface onVideoResumedForChannelId:(int)nChannelId;

@property (nonatomic, assign) bool bVideoIsReceiving;

@end

#endif // clientsdk_CSVideoInterface_h
