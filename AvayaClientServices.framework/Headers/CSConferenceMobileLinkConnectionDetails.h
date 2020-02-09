/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Class representing the connection details when mobile link successfully connected
 * to the specific room system.
 */
@interface CSConferenceMobileLinkConnectionDetails : NSObject

/**
 * The address of the connected conference room system.
 */
@property (nonatomic, readonly) NSString *roomSystemAddress;

/**
 * The participant id of the connected conference room system.
 */
@property (nonatomic, readonly) NSString *roomSystemParticipantId;

@end
