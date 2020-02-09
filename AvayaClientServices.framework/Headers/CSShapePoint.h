/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

/**
 * CSShapePoint objects represent points used by CSShape class. 
 * This class doesn't need to be used by client unless custom whiteboard canvas
 * is developed.
 *
 * @see CSShape
 */
@interface CSShapePoint : NSObject

/**
 * Indicates whether instance is move point.
 */
@property (nonatomic, getter=isMovePoint) BOOL movePoint;

/**
 * CGPoint backing CSShapePoint
 */
@property (nonatomic) CGPoint point;

/**
 * Initializer with CGPoint as move point.
 *
 * @param point CGPoint object that CSShapePoint should be initialized with.
 */
- (instancetype)initWithMovePoint:(CGPoint)point;

/**
 * Initializer with CGPoint.
 *
 * @param point CGPoint object that CSShapePoint should be initialized with.
 */
- (instancetype)initWithLinePoint:(CGPoint)point;

/**
 * Initializer with CGPoint.
 *
 * @param point CGPoint object that CSShapePoint should be initialized with.
 * @param isMove Indicates whether initialized point is move point.
 */
- (instancetype)initWithPoint:(CGPoint)point isMovePoint:(BOOL)isMove;

@end
