/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSMediaEncryptionType.h"


/**
 * Audio-related details for a session.
 */
@interface CSAudioDetails : NSObject

/**
 * The local IP address used for the audio session.
 */
@property (nonatomic, readonly) NSString *localIPAddress;

/**
 * The local RTP receive port for the audio session (as per SDP offer/answer exchange).
 */
@property (nonatomic, readonly) NSUInteger localPort;

/**
 * The remote IP address used for the audio session.
 */
@property (nonatomic, readonly) NSString *remoteIPAddress;

/**
 * The remote RTP receive port for the audio session (as per SDP offer/answer exchange).
 */
@property (nonatomic, readonly) NSUInteger remotePort;

/**
 * The name of the audio codec being used.
 */
@property (nonatomic, readonly) NSString *codec;

/**
 * Media encryption mode for the audio session.
 */
@property (nonatomic, readonly) CSMediaEncryptionType encryptionType;

/**
 * Status indication for whether Audio is tunneled or not.
 */
@property(nonatomic, readonly, getter=isMediaTunneled) BOOL mediaTunneled;

/**
 * Status indication for whether tunneled Audio goes through proxy or not.
 */
@property(nonatomic, readonly, getter=isMediaProxied) BOOL mediaProxied;

/**
 * RTCP encryption status for the audio session.
 * True if feedback RTCP packets are encrypted false otherwise.
 * If it is true RTCP packets should be decripted before reading
 * audio stream details.
 */

@property (nonatomic, readonly) BOOL RTCSEncrypted;

/**
 * The dynamic payload type used for telephony events (DTMF tones).
 */
@property (nonatomic, readonly) NSUInteger DTMFPayloadType;

/**
 * The packetization interval in milliseconds.
 * This represents the time duration of the audio data contained in each packet.
 * It is retrieved from the ptime attribute from the SDP audio codec config.
 */
@property (nonatomic, readonly) NSUInteger packetizationMilliseconds;

/**
 * The round-trip audio delay (in milliseconds) calculated as per RFC 3550.
 * This is the time required for an RTP packet to go from sender to receiver and back.
 */
@property (nonatomic, readonly) NSUInteger roundTripTimeMilliseconds;

/**
 * The total number of RTP packets transmitted.
 */
@property (nonatomic, readonly) NSUInteger numberOfPacketsTransmitted;

/**
 * The total number of RTP packets received.
 */
@property (nonatomic, readonly) NSUInteger numberOfPacketsReceived;

/**
 * The total number of RTP payload bytes transmitted.
 */
@property (nonatomic, readonly) NSUInteger numberOfBytesTransmitted;

/**
 * The total number of RTP payload bytes received.
 */
@property (nonatomic, readonly) NSUInteger numberOfBytesReceived;

/**
 * The fractional loss seen locally.
 * This is 8-bits size value.
 * The fraction of RTP data packets from source lost since
 * the previous SR or RR packet was sent, expressed as a fixed
 * point number with the binary point at the left edge of the
 * field. (That is equivalent to taking the integer part after
 * multiplying the loss fraction by 256.) This fraction is defined
 * to be the number of packets lost divided by the number of
 * packets expected. If the loss is negative
 * due to duplicates, the fraction lost is set to zero.
 */
@property (nonatomic, readonly) NSUInteger localFractionLost;

/**
 * The fractional loss seen remotely.
 * This is 8-bits size value.
 * The fraction of RTP data packets from source lost since
 * the previous SR or RR packet was sent, expressed as a fixed
 * point number with the binary point at the left edge of the
 * field. (That is equivalent to taking the integer part after
 * multiplying the loss fraction by 256.) This fraction is defined
 * to be the number of packets lost divided by the number of
 * packets expected. If the loss is negative
 * due to duplicates, the fraction lost is set to zero.
 */
@property (nonatomic, readonly) NSUInteger remoteFractionLost;

/**
 * The average jitter buffer size in milliseconds the local end is experiencing on the received RTP stream.
 * In VoIP, a jitter buffer is a shared data area where voice packets can be
 * collected, stored, and sent to the voice processor in evenly spaced intervals.
 * Variations in packet arrival time, called jitter, can occur because of
 * network congestion, timing drift, or route changes. The jitter buffer,
 * which is located at the receiving end of the voice connection, intentionally
 * delays the arriving packets so that the end user experiences a clear connection
 * with very little sound distortion.
 */
@property (nonatomic, readonly) NSUInteger averageLocalJitterMilliseconds;

/**
 * The average jitter buffer size in milliseconds the remote end is experiencing on the transmitted RTP stream.
 * In VoIP, a jitter buffer is a shared data area where voice packets can be
 * collected, stored, and sent to the voice processor in evenly spaced intervals.
 * Variations in packet arrival time, called jitter, can occur because of
 * network congestion, timing drift, or route changes. The jitter buffer,
 * which is located at the receiving end of the voice connection, intentionally
 * delays the arriving packets so that the end user experiences a clear connection
 * with very little sound distortion.
 */
@property (nonatomic, readonly) NSUInteger averageRemoteJitterMilliseconds;

/**
 * The current jitter buffer size in milliseconds.
 * In VoIP, a jitter buffer is a shared data area where voice packets can be
 * collected, stored, and sent to the voice processor in evenly spaced intervals.
 * Variations in packet arrival time, called jitter, can occur because of
 * network congestion, timing drift, or route changes. The jitter buffer,
 * which is located at the receiving end of the voice connection, intentionally
 * delays the arriving packets so that the end user experiences a clear connection
 * with very little sound distortion.
 */
@property (nonatomic, readonly) NSUInteger currentBufferSizeMilliseconds;

/**
 * The preferred (optimal) jitter buffer size in milliseconds.
 * In VoIP, a jitter buffer is a shared data area where voice packets can be
 * collected, stored, and sent to the voice processor in evenly spaced intervals.
 * Variations in packet arrival time, called jitter, can occur because of
 * network congestion, timing drift, or route changes. The jitter buffer,
 * which is located at the receiving end of the voice connection, intentionally
 * delays the arriving packets so that the end user experiences a clear connection
 * with very little sound distortion.
 */
@property (nonatomic, readonly) NSUInteger preferredBufferSizeMilliseconds;

/**
 * The percentage of packets lost (network + late).
 */
@property (nonatomic, readonly) NSUInteger currentPacketLossRate;

/**
 * The percentage of packets discarded (late).
 */
@property (nonatomic, readonly) NSUInteger currentDiscardRate;

/**
 * Fraction of synthesized speech frames inserted through expansion
 * in total frame count in buffer.
 * In case of a starved jitter buffer synthesized speech frames will be added.
 * This process is called "expand".
 */
@property (nonatomic, readonly) NSUInteger currentExpandRate;

/**
 * Fraction of synthesized speech frames inserted through pre-emptive expansion
 * in total frame count in buffer.
 * In case of a shallow jitter buffer synthesized speech frames will be added.
 * This process is called "pre-emptive expand" and based on previous frames.
 */
@property (nonatomic, readonly) NSUInteger currentPreemptiveRate;

/**
 * Fraction of data removed through acceleration.
 * In case of a full jitter buffer speech frames will be deleted.
 * This process is called "acceleration".
 */
@property (nonatomic, readonly) NSUInteger currentAccelerateRate;

@end
