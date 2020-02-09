/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Conferencing configuration returned by Unified Portal.
 */
@interface CSUnifiedPortalConferencingConfiguration : NSObject

/**
 * Virtual rooms configured for user.
 */
@property (nonatomic, readonly) NSArray *virtualRooms;

@end
