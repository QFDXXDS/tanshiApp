/* Copyright Avaya Inc. */


#import <Foundation/Foundation.h>
#import "CSBasicShape.h"
#import "CSShapePoint.h"

/**
 * CSCircleShape objects represent circular shape that can be added to whiteboard surface.
 * Client doesn't need to use this explicitly unless custom whiteboard is created.
 *
 * @see CSWhiteboardSurface
 */
@interface CSCircleShape : CSBasicShape

/**
 * Top left point of circle.
 */
@property (nonatomic, readonly) CGPoint topLeft;

/**
 * Bottom right point of circle.
 */
@property (nonatomic, readonly) CGPoint bottomRight;

/**
 * Indicates whether shape is filled.
 */
@property (nonatomic, readonly, getter=isFilled) BOOL filled;

@end
