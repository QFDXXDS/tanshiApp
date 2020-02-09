/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Meeting media types.
 */
typedef NS_ENUM(NSUInteger, CSMeetingMediaType) {
	/**
	 * The media type is not defined.
	 */
	CSMeetingMediaTypeUndefined,
	
	/**
	 * The conference has no video (audio only).
	 */
	CSMeetingMediaTypeAudioOnly,
	
	/**
	 * The conference video is composited.
	 * The layout of the composite video image is controlled by the conference media server.
	 */
	CSMeetingMediaTypeCompositeVideo,
	
	/**
	 * Video images of different participants are routed to the client as a single video stream by the conference media server.
	 * The layout of the different video images is controlled by the local client.
	 */
	CSMeetingMediaTypeSwitchedVideo,
	
	/**
	 * Video images of different participants are separately routed by the conference media server.
	 * The layout of the different video images is controlled by the local client.
	 */
	CSMeetingMediaTypeMultiStreamSwitchedVideo
};
