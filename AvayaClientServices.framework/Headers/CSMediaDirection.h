/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Media direction used for video and audio.
 */

typedef NS_ENUM(NSUInteger, CSMediaDirection) {
	/** Media direction is not defined */
	CSMediaDirectionUndefined,
	/** Media direction is send only */
	CSMediaDirectionSendOnly,
	/** Media direction is receive only */
	CSMediaDirectionReceiveOnly,
	/** Media direction is send and receive */
	CSMediaDirectionSendReceive,
	/** Media direction is inactive */
	CSMediaDirectionInactive,
};
