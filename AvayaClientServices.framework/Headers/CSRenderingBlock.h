/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

/**
 * CSRenderingBlock object which represents one block of given size received
 * from collaboration server. One sharing frame is build from many blocks
 * depending on frame. Each block contains RGB data. Objects of this class usually
 * aren't used explicitly by client unless custom sharing canvas is developed. Particular
 * position related properties (position, size, rect) can be used to draw data in context.
 *
 * @see CSSharingBlock
 */
@interface CSRenderingBlock : NSObject

/**
 * Position of received blocked
 */
@property (nonatomic, readonly) CGPoint position;

/**
 * Data of received block
 */
@property (nonatomic, readonly) uint8_t *data;

/**
 * Length of the data contained by block
 */
@property (nonatomic, readonly) NSInteger dataLength;

/**
 * Size of received block
 */
@property (nonatomic, readonly) CGSize size;

/**
 * Rect of received block
 */
@property (nonatomic, readonly) CGRect rect;

@end
