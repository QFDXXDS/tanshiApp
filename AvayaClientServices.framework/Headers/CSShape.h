/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSBasicShape.h"
#import "CSShapePoint.h"

/**
 * CSShape objects represent free shape that can be added to whiteboard surface. 
 * CSShape is build from points which can be connected or not. Client doesn't
 * need to use this class explicitly unless custom whiteboard is developed.
 *
 * @see CSWhiteboardSurface
 */
@interface CSShape : CSBasicShape

/**
 * Array of points that shape is made with. Array contains objects of CSShapePoint class.
 *
 * @see CSShapePoint
 */
@property (nonatomic, strong, readonly) NSMutableArray *points;

/**
 * Indicates whether shape is filled.
 */
@property (nonatomic, readonly, getter=isFilled) BOOL filled;

/**
 * Indicates whether is finished.
 */
@property (nonatomic, readonly, getter=isFinished) BOOL finished;

/**
 * Updates shape with array of new points. 
 *
 * @param points Array containing CSShapePoint object that shape should be updated with.
 */
- (void)updateShapeWithPoints:(NSArray *)points;

@end
