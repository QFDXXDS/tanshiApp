/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import "CSView.h"
#import "CSContentSharing.h"

@class CSSharingBlock;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"

/**
 * CSScreenSharingListener is a class that is responsible for two things:
 * 1. It's a listener to a CSContentSharingDelegate which delegates events
 * coming from collaboration server concerning content sharing.
 * 2. It's a drawing delegate of CALayer behind a CSScreenSharingView object
 * and it's responsible for drawing incoming frames on the layer.
 *
 * \if OSX
 *
 * Proper use of this class:
 * - Client creates a view of CSScreenSharingView class
 * - Client creates a CSScreenSharingListener object (inited with sharing view's size)
 * - set contentSharingDelegate of CSScreenSharingView to object of CSScreenSharingListener class
 *
 * \endif
 *
 * \if iOS
 *
 * Proper use of this class:
 * - Client creates a view of CSIOSScreenSharingView class
 * - Client creates a CSScreenSharingListener object (inited with sharing view's size)
 * - set contentSharingDelegate of CSIOSScreenSharingView to object of CSScreenSharingListener class
 *
 * \endif
 *
 * Client doesn't need to invoke methods of this class in order to make content sharing work
 * unless custom screen sharing view is developed.
 *
 * @see CSContentSharingDelegate
 */

#pragma clang diagnostic pop

#if MAC_OS_X_VERSION_MAX_ALLOWED >= 101200
@interface CSScreenSharingListener : NSObject <CALayerDelegate>
#else
@interface CSScreenSharingListener : NSObject
#endif

/**
 * The layer that drawing will be performed on.
 * Initialized internally by CSScreenSharingListener.
 */
@property (nonatomic, strong) CALayer *drawingLayer;

/**
 * A view, that a drawingLayer is assigned as content.
 * Here, it's used to apply any sharing screen viewport size changes.
 * Initialized internally by CSScreenSharingListener.
 */
@property (nonatomic, weak) CSView *drawingView;

/**
 * Initializer without arguments is not available for this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 * Draws CSSharingBlock object received from collaboration server on layer.
 *
 * @param bitmapBlock Block to draw on drawing layer
 *
 * @see CSSharingBlock
 */
- (void)drawSharingBlock:(CSSharingBlock *)bitmapBlock;

/**
 * Implementation of informal CALayer drawing protocol. It puts content on layer.
 * It is called, when needsDisplay is set to YES on drawingLayer
 *
 * @param layer Layer to display
 */
- (void)displayLayer:(CALayer *)layer;

/**
 * Inits CSScreenSharingListener with frame size which is used to properly set a pause screen size.
 *
 * @param frame Frame of screen sharing view
 */
- (instancetype)initWithFrame:(CGRect)frame NS_DESIGNATED_INITIALIZER;

/**
 * Sets drawing layer frame to rect which origin is {0,0} and given size.
 *
 * @param size Size of frame to be set.
 */
- (void)setViewSize:(CGSize)size;

/**
 * @return Returns size of the current screen sharing.
 */
- (CGSize)contentSize;

@end
