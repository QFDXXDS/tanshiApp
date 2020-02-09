/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>


/**
 * Enumeration defining different video modes that 
 * are supported for a call.
 */
typedef NS_ENUM(NSUInteger, CSVideoMode) {
	CSVideoModeNone = 0,
	/**
	 * Bi-directional video request.
	 */
	CSVideoModeSendReceive,
	/**
	 * Receive-only (i.e., no camera capture and send) video request.
	 */
	CSVideoModeReceiveOnly,
	/**
	 * Send-only (i.e., no receipt of incoming video) video request.
	 */
	CSVideoModeSendOnly,
	/**
	 * Inactive video request, i.e., no send or receive, but video remains
	 * enabled.
	 */
	CSVideoModeInactive,
	/**
	 * Disable video request (i.e., remove video).
	 */
	CSVideoModeDisable
};

