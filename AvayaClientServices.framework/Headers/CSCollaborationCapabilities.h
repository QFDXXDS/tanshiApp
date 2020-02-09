/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSCapability.h"

/**
 * The CSCollaborationCapabilities object provides access to collaboration capabilities.
 *
 * The CSCollaborationCapabilities object is accessible via CSCollaboration and
 * groups all CSCollaboration properties. Each property is also accessible
 * directly via CSCollaboration.
 *
 * @see CSCollaboration::capabilities
 */
@interface CSCollaborationCapabilities : NSObject

/**
 * @see CSCollaboration::contentSharingCapability
 */
@property (nonatomic, readonly) CSCapability *contentSharingCapability;

/**
 * @see CSCollaboration::networkLibraryCapability
 */
@property (nonatomic, readonly) CSCapability *networkLibraryCapability;

/**
 * @see CSCollaboration::librarySharingCapability
 */
@property (nonatomic, readonly) CSCapability *librarySharingCapability;

/**
 * @see CSCollaboration::whiteboardCapability
 */
@property (nonatomic, readonly) CSCapability *whiteboardCapability;

/**
 * @see CSCollaboration::retrieveParticipantListCapability
 */
@property (nonatomic, readonly) CSCapability *retrieveParticipantListCapability;

@end
