/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

/**
 * Enum indicating selection status of CSBasicShape on the server side. In other words,
 * if our action is confirmed by server.
 *
 * @see selectionStatus
 */
typedef NS_ENUM(NSUInteger, CSShapeSelectionStatus)
{
	CSShapeSelectionPending, /**< Response from server not received yet*/
	CSShapeSelectionConfirmed, /**< Shape has been successfully sent to server and response has been received */
	CSShapeSelectionError /**< Server returned an error */
};

/**
 * Base class for shapes that can be drawn on whiteboard surface. Client doesn't
 * need to use this class explicitly unless custom whiteboard is developed.
 *
 * @see CSShape
 * @see CSWhiteboardText
 * @see CSCircleShape
 */
@interface CSBasicShape : NSObject

/**
 * The shape ID associated with the particular shape object.
 */
@property (nonatomic, strong, readonly, getter=getShapeId) NSString *shapeId;

/**
 * Color of shape in ARGB format. Alpha is stored in most significant byte.
 */
@property (nonatomic, readonly) NSUInteger color;

/**
 * Width of shape
 */
@property (nonatomic, readonly) CGFloat width;

/**
 * Geometric translation of shape.
 */
@property (nonatomic) CGPoint translation;

/**
 * Status of CSBasicShape sent to server.
 */
@property (nonatomic, readonly) CSShapeSelectionStatus selectionStatus;

/**
 * Indicates whether shape is created by local user.
 */
@property (nonatomic, readonly, getter=isMine) BOOL mine;

/**
 * Display name of user who created shape.
 */
@property (nonatomic, strong, readonly) NSString *ownerDisplayName;

@end
