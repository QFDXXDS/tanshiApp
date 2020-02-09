/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSDataSharingMode.h"
#import "CSMediaEncryptionType.h"

/**
 * Collaboration common statistics for send and receive
 */
@interface CSCollaborationStatistics : NSObject

/**
 * Width of the sent/received presentation video stream
 */
@property (nonatomic, readonly) NSUInteger width;

/**
 * Height of the sent/received presentation video stream
 */
@property (nonatomic, readonly) NSUInteger height;

/**
 * Actual sent/received frame rate in frames per second
 */
@property (nonatomic, readonly) NSUInteger actualFrameRate;

/**
 *  Presentation Video codec
 */
@property (nonatomic, readonly) NSString *codec;

/**
 * Round Trip Time
 */
@property (nonatomic, readonly) NSUInteger roundTripTimeMilliseconds;

/**
 * Actual sent/received bit rate per second
 */
@property (nonatomic, readonly) NSUInteger actualBitrate;

/**
 * Target sent/received bit rate per second
 */
@property (nonatomic, readonly) NSUInteger targetBitrate;

/**
 * Jitter in milliseconds
 */
@property (nonatomic, readonly) NSUInteger jitterMillis;

/**
 * Total number of packets lost in transmit/receive direction
 */
@property (nonatomic, readonly) NSUInteger packetLossCount;

/**
 * Percentage of packets lost in transmit/receive direction
 */
@property (nonatomic, readonly) NSUInteger packetLossPercentage;

/**
 * To print the description of the object without the newline characters
 */
- (NSDictionary*)CSPropertyDescriptionForObject:(Class)cls;

@end

////////////////////////////////////////////////////////////////////////////////

@interface CSCollaborationReceiveStatistics : CSCollaborationStatistics

/**
 * WCS frame count
 *
 * If value is undefined NSUIntegerMax is returned
 */
@property (nonatomic, readonly) NSUInteger frameCount;

/**
 * WCS frames lost percentage
 *
 * If value is undefined NSUIntegerMax is returned
 */
@property (nonatomic, readonly) NSUInteger frameLossPercentage;

/**
 * WCS queue size
 *
 * If value is undefined NSUIntegerMax is returned
 */
@property (nonatomic, readonly) NSUInteger queueSize;

@end

////////////////////////////////////////////////////////////////////////////////

typedef NS_ENUM(uint32_t, CSCollaborationContentSharingMode)
{
	CSCollaborationContentSharingModeNone,     /**< Content sharing is inactive. */
	CSCollaborationContentSharingModeTransmit, /**< Collaboration client transmits content sharing. */
	CSCollaborationContentSharingModeReceive   /**< Collaboration client receives content sharing. */
};

/**
 * Collaboration related details for session
 */
@interface CSCollaborationDetails : NSObject

/**
 * Data sharing mode for collaboration session
 */
@property (nonatomic, readonly) CSDataSharingMode sharingMode;

/**
 * Type for encryption used for collaboration session
 */
@property (nonatomic, readonly) CSMediaEncryptionType encryptionType;

/**
 * Send stream statistics
 */
@property (nonatomic, readonly) CSCollaborationStatistics *transmitStatistics;

/**
 * Receive stream statistics
 */
@property (nonatomic, readonly) CSCollaborationReceiveStatistics *receiveStatistics;

/**
 * Current content sharing mode
 */
@property (nonatomic, readonly) CSCollaborationContentSharingMode contentSharingMode;

@end
