/* Copyright Avaya Inc. */


#import <Foundation/Foundation.h>
#import "CSCapability.h"

/**
 * The CSContentSharingCapabilities object provides access to content sharing capabilities.
 *
 * The CSContentSharingCapabilities object is accessible via CSContentSharing and
 * groups all CSContentSharing properties. Each property is also accessible
 * directly via CSContentSharing.
 *
 * @see CSContentSharing::sharingCapabilities
 */
@interface CSContentSharingCapabilities : NSObject

/**
 * @see CSCollaboration::shareFullScreenCapability
 */
@property (nonatomic, readonly) CSCapability *shareFullScreenCapability;

/**
 * @see CSCollaboration::shareApplicationWindowCapability
 */
@property (nonatomic, readonly)	CSCapability *shareApplicationWindowCapability;

/**
 * @see CSCollaboration::shareScreenRegionCapability
 */
@property (nonatomic, readonly) CSCapability *shareScreenRegionCapability;

/**
 * @see CSCollaboration::supportRemoteControlCapability
 */
@property (nonatomic, readonly) CSCapability *supportRemoteControlCapability;

/**
 * @see CSCollaboration::offerRemoteControlCapability
 */
@property (nonatomic, readonly) CSCapability *offerRemoteControlCapability;

/**
 * @see CSCollaboration::requestRemoteControlCapability
 */
@property (nonatomic, readonly) CSCapability *requestRemoteControlCapability;

@end
