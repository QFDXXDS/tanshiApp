/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Message waiting status information.
 */
@interface CSMessageWaitingStatus : NSObject

/**
 * A Boolean value indicating whether there are new messages waiting.
 *
 * This flag is set for all messaging systems.
 */
@property (nonatomic) BOOL hasMessagesWaiting;

/**
 * The number of new messages waiting, if provided by the messaging system.
 *
 * Set to a value of -1 if the messaging system does not provide this information.
 */
@property (nonatomic) NSInteger newMessageCount;

/**
 * The total number of messages stored, if provided by the messaging system.
 *
 * Set to a value of -1 if the messaging system does not provide this information.
 */
@property (nonatomic) NSInteger totalMessageCount;

/**
 * The number of new urgent messages waiting, if provided by the messaging system.
 *
 * Set to a value of -1 if the messaging system does not provide this information.
 */
@property (nonatomic) NSInteger newUrgentMessageCount;

/**
 * The total number of urgent messages stored, if provided by the messaging system.
 *
 * Set to a value of -1 if the messaging system does not provide this information.
 */
@property (nonatomic) NSInteger totalUrgentMessageCount;

@end
