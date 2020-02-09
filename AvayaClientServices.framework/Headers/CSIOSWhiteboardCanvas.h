/* Copyright Avaya Inc. */

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "CSWhiteboardSurface.h"
#import "CSWhiteboardTool.h"

/**
 * CSIOSWhiteboardCanvas object provides whiteboard canvas on which user can
 * draw and received whiteboard drawings are displayed.
 */
@interface CSIOSWhiteboardCanvas : UIView

/**
 * Current whiteboard surface of whiteboard.
 */
@property (strong, nonatomic) CSWhiteboardSurface *whiteboardSurface;

/**
 * Current color of drawing on whiteboard. Default color is set to black.
 */
@property (strong, nonatomic) UIColor *color;

/**
 * Current tool for drawing on whiteboard. Default tool is set to eMove.
 */
@property (assign, nonatomic) CSWhiteboardTool tool;

/**
 * Initializes with frame.
 *
 * @param frameRect Rect that CSWhiteboardCanvas is initialized with.
 */
- (instancetype)initWithFrame:(CGRect)frameRect;

/**
 * Initializes with coder.
 *
 * @param coder Coder that CSWhiteboardCanvas is initialized with.
 */
- (instancetype)initWithCoder:(NSCoder *)coder;

/**
 * Clears whiteboard. Operation is completed on whiteboard canvas (drawings are removed) after
 * response from server. There's also corresponding method {@link CSWhiteboardSurface::clearContentWithCompletionHandler:}
 * but, unless you want to create custom whiteboard canvas, use this one.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c surface CSWhiteboardSurface object which was cleared.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)clearWhiteboardWithCompletionHandler:(void (^)(CSWhiteboardSurface *surface, NSError *error))handler;


@end
