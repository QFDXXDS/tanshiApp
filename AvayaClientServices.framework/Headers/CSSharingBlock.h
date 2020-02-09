/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSRenderingBlock.h"

/**
 * CSRenderingBlock object which represents one block of given size received
 * from collaboration server. Comparing to CSRenderingBlock it's higher level
 * since raw image data are transformed into CGImage here. Objects of this class usually
 * aren't used explicitly by client unless custom sharing canvas is developed.
 *
 * @see CSRenderingBlock
 */
@interface CSSharingBlock : NSObject

/**
 * Creates a CSSharingBlock object from data in CSRenderingBlock.
 * CSSharingBlock is backed by CGImage object which can be drawn on CGContext
 * using method CSSharingBlock::drawInContext:.
 *
 * @see CSSharingBlock::drawInContext:
 */
-(instancetype)initWithRenderingBlock:(CSRenderingBlock *)renderingBlock;

/**
 * Creates a block from existing CGImage. Can be used for testing.
 *
 * @param image CGImage object which should back created CSSharingBlock
 * @param rect Rect which define position of image in coordinates of frame containing given block
 */
-(instancetype)initWithCGImage:(CGImageRef)image rect:(CGRect)rect;

/**
 * Puts CGImage which backs CSSharingBlock object on given drawing context.
 *
 * @param context Context on which CGImage is supposed to be drawn.
 */
-(void)drawInContext:(CGContextRef)context;

/**
 * Flips Y coord to put image on context properly since the coordinate system
 * on OSX is originated from BottomLeft point of the screen (when operating on CGContext).
 *
 * @param viewHeight Height of the whole frame which given block belongs to.
 */
-(void)invertYWithViewHeight:(CGFloat)viewHeight;

@end
