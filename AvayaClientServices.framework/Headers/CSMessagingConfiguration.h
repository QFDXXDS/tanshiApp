/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * User configuration information for the messaging service.
 * This class provides configuration and preference data for the messaging service features.
 */
@interface CSMessagingConfiguration : NSObject

/**
 * The initial time interval between a connection failure and a reconnect attempt.
 *
 * If connection attempts continue to fail the reconnect interval will be progressively extended
 * using a backoff algorithm based on this initial reconnect interval.
 *
 * Set to zero to disable automatic reconnection attempts.
 */
@property (nonatomic) NSTimeInterval initialReconnectInterval;

/**
 * A Boolean value indicating whether message delivery and read updates should be tracked or not.
 * By default, delivery/read states are not monitored.
 */
@property (nonatomic, getter=isMessageDeliveryReadStateMonitoringEnabled) BOOL messageDeliveryReadStateMonitoringEnabled;

/**
 * A Boolean value indicating whether the application wants to report
 * 'message read' indication to other conversation participants, i.e. let 
 * other conversation participants know when I mark a message as read.
 * By default, message read reports are enabled.
 */
@property (nonatomic, getter=isMessageReadReportingEnabled) BOOL messageReadReportingEnabled;


@end
