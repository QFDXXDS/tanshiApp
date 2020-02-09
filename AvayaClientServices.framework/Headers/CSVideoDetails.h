/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSMediaEncryptionType.h"

/**
 * Video channel common statistics for send and receive.
 */
@interface CSVideoStatistics : NSObject

/**
 * Target sent/received frame rate in frames per second.
 */
@property (nonatomic, readonly) NSUInteger targetFrameRate;

/**
 * Actual sent/received frame rate in frames per second.
 */
@property (nonatomic, readonly) NSUInteger actualFrameRate;

/**
 * Width of the sent/received video stream.
 */
@property (nonatomic, readonly) NSUInteger width;

/**
 * Height of the sent/received video stream.
 */
@property (nonatomic, readonly) NSUInteger height;

/**
 * Actual send/receive side jitter buffer size in milliseconds.
 *
 * In VoIP, a jitter buffer is a shared data area where video packets can be
 * collected, stored, and sent to the video processor in evenly spaced intervals.
 * Variations in packet arrival time, called jitter, can occur because of
 * network congestion, timing drift, or route changes. The jitter buffer,
 * which is located at the receiving end of the video connection, intentionally
 * delays the arriving packets so that the end user experiences a clear connection
 * with very little video delays.
 */
@property (nonatomic, readonly) NSUInteger jitterBufferSizeMilliseconds;

/**
 * Target sent/received bit rate per second.
 */
@property (nonatomic, readonly) NSUInteger targetBitrate;

/**
 * Actual sent/received bit rate per second.
 */
@property (nonatomic, readonly) NSUInteger actualBitrate;

/**
 * Total number of packets sent/received.
 */
@property (nonatomic, readonly) NSUInteger packetCount;

/**
 * Total number of bytes sent/received.
 */
@property (nonatomic, readonly) NSUInteger byteCount;

/**
 * Number of key frames locally requested (receive direction), or remotely requested (send direction).
 */
@property (nonatomic, readonly) NSUInteger keyFrameCount;

/**
 * Total number of packets lost in transmit/receive direction.
 */
@property (nonatomic, readonly) NSUInteger packetLossTotal;

/**
 * Fraction of packets lost in transmit/receive direction.
 */
@property (nonatomic, readonly) NSUInteger packetLossFraction;

/**
 * To print the description of the object without the newline characters.
 */
- (NSDictionary*)CSPropertyDescriptionForObject:(Class)cls;

@end

////////////////////////////////////////////////////////////////////////////////

@interface CSVideoTransmitStatistics : CSVideoStatistics

/**
 * 802.1p Layer 2 priority tag, if set.
 */
@property (nonatomic, readonly) NSUInteger RTP8021pTag;

/**
 * DSCP tag, if set.
 */
@property (nonatomic, readonly) NSUInteger RTPDSCP;

@end

////////////////////////////////////////////////////////////////////////////////

/**
 * Video related details for session.
 */
@interface CSVideoDetails : NSObject

/**
 * The name of the video codec being used.
 */
@property (nonatomic, readonly) NSString *codec;

/**
 * Payload type
 */
@property (nonatomic, readonly) NSUInteger payloadType;

/**
 * The round-trip audio delay (in milliseconds) calculated as per RFC 3550.
 * This is the time required for an RTP packet to go from sender to receiver and back.
 */
@property (nonatomic, readonly) NSUInteger roundTripTimeMilliseconds;

/**
 * Local media IP address.
 */
@property (nonatomic, readonly) NSString *localIPAddress;

/**
 * Remote media IP address.
 */
@property (nonatomic, readonly) NSString *remoteIPAddress;

/**
 * Local media termination port.
 */
@property (nonatomic, readonly) NSUInteger localPort;

/**
 * Remote media termination port.
 */
@property (nonatomic, readonly) NSUInteger remotePort;

/**
 * Type for encryption used for video session.
 */
@property (nonatomic, readonly) CSMediaEncryptionType encryptionType;

/**
 * Status indication for whether Video is tunneled or not.
 */
@property(nonatomic, readonly) BOOL mediaTunneled;

/**
 * Status indication for whether tunneled Video goes through proxy or not.
 */
@property(nonatomic, readonly, getter=isMediaProxied) BOOL mediaProxied;

/**
 * Flag indicating whether RTCP is encrypted or not.
 */
@property (nonatomic, readonly, getter=isRTCPEncrypted) BOOL RTCPEncrypted;

/**
 * Video channel id associated with media engine resources.
 */
@property (nonatomic, readonly) NSUInteger channelId;

/**
 * Receive stream statistics.
 */
@property (nonatomic, readonly) CSVideoStatistics *receiveStatistics;

/**
 * Send stream statistics.
 */
@property (nonatomic, readonly) CSVideoTransmitStatistics *transmitStatistics;

@end
