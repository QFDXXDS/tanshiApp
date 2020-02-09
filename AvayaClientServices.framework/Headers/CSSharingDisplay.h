/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

/**
 * CSSharingDisplay object provides set of information about display which can be
 * shared using CSContentSharing::startSharingFullScreenWithScreenId:completionHandler.
 *
 * @see CSContentSharing::startSharingFullScreenWithScreenId:completionHandler:
 */
@interface CSSharingDisplay : NSObject

/**
 * Vendor number of display.
 */
@property (nonatomic, copy) NSString *name;

/**
 * Size of the display.
 */
@property (nonatomic) CGRect size;

/**
 * Unique ID of the display. Used in method CSContentSharing::startSharingFullScreenWithScreenId:completionHandler
 * to start full screen sharing.
 *
 * @see CSContentSharing::startSharingFullScreenWithScreenId:completionHandler:
 */
@property (nonatomic) NSInteger displayId;

@end
