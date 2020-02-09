/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSBasicShape.h"
#import "CSShape.h"
#import "CSCircleShape.h"
#import "CSWhiteboardText.h"
#import "CSParticipant.h"
#import "CSDataSet.h"

@protocol CSWhiteboardSurfaceDelegate;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"

/**
 * \if OSX
 *
 * The CSWhiteboardSurface object represents independent whiteboard surface containing
 * all shapes drawn on given whiteboard surface. Whiteboard surface content is displayed on
 * CSWhiteboardCanvas. Client can obtain objects of this class using methods of class CSWhiteboard. 
 * Methods related to adding/modifying/removing particular shapes shouldn't be invoked by client explicitly 
 * unless custom whiteboard canvas is developed. 
 * Methods NSObject::isEqual and NSObject::hash are implemented for this class.
 *
 * \endif
 *
 * \if iOS
 *
 * The CSWhiteboardSurface object represents independent whiteboard surface containing
 * all shapes drawn on given whiteboard surface. Whiteboard surface content is displayed on
 * CSIOSWhiteboardCanvas. Client can obtain objects of this class using methods of class CSWhiteboard.
 * Methods related to adding/modifying/removing particular shapes shouldn't be invoked by client explicitly 
 * unless custom whiteboard canvas is developed. 
 * Methods NSObject::isEqual and NSObject::hash are implemented for this class.
 *
 * \endif
 *
 * @see CSWhiteboard
 */

#pragma clang diagnostic pop

@interface CSWhiteboardSurface : NSObject

/**
 * The delegate used to handle events related to whiteboard surface.
 */
@property (nonatomic, weak) id<CSWhiteboardSurfaceDelegate> delegate;

/**
 * The whiteboard surface ID associated with the particular CSWhiteboardSurface object.
 */
@property (nonatomic, readonly) NSString *surfaceId;

/**
 * Data of participant who added whiteboard surface.
 */
@property (nonatomic, readonly) CSParticipant *addedBy;

/**
 * Data of participant who removed whiteboard surface.
 */
@property (nonatomic, readonly) CSParticipant *removedBy;

/**
 * Array containing all shapes belonging to this whiteboard surface as objects of class CSBasicShape.
 *
 * @see CSBasicShape
 */
@property (nonatomic, readonly) NSArray *shapes;

/**
 * CSCapability object indicating whether the local user is allowed to set given
 * whiteboard surface active. To do so, the local user needs to be moderator, presenter
 * or panel model mode has to be enabled.
 *
 * @see CSWhiteboardSurface::setAsActiveWithCompletionHandler:
 */
@property (nonatomic, readonly, copy) CSCapability *setAsActiveCapability;

/**
 * Selects this surface as the active whiteboard surface.
 * Only one surface can be active during a collaboration session.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c surface CSWhiteboardSurface object set as active.
 *		  @li @c participant CSParticipant object providing information about collaboration
 *		  participant who set surface as active (local user in case of this method).
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)setAsActiveWithCompletionHandler:(void (^)(CSWhiteboardSurface *surface, CSParticipant *participant, NSError *error))handler;

/**
 * Adds a shape to the whiteboard surface.
 *
 * @param points Array of CSShapePoint points.
 * @param color Color of shape.
 * @param width Width of shape.
 * @param filled True if shape is filled.
 * @param finished Set to true when shape is finished / closed
 * @param handler A block to be called when the operation is completed.
 *        @li @c shape CSBasicShape object made with given points.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 * @return CSShape object made with given points
 *
 */
- (CSShape *)addShapeWithPoints:(NSArray *)points
						  color:(NSUInteger)color
						  width:(NSUInteger)width
					   isFilled:(BOOL)filled
					 isFinished:(BOOL)finished
			  completionHandler:(void (^)(CSBasicShape *shape, NSError *error))handler;

/**
 * Marks shape as finished.
 *
 * @param shape CSBasicShape to be marked as finished.
 * @param handler A block to be called when the operation is completed.
 *        @li @c shape CSBasicShape object marked as finished.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSWhiteboardSurface::finishShape:completionHandler:
 */
- (void)finishShape:(CSBasicShape *)shape completionHandler:(void (^)(CSBasicShape *shape, NSError *error))handler;

/**
 * Adds a circle to the whiteboard surface. Method is deprecated.
 * Use CSWhiteboardSurface::addCircleWithTopLeft:bottomRight:color:width:isFilled:completionHandler: instead.
 *
 * @param topLeft Top left point of circle
 * @param bottomRight Bottom right point of circle.
 * @param color Color of circle.
 * @param width Width of circle.
 * @param filled True if circle is filled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c shape Added circle as CSBasicShape object.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 * @return CSCircleShape object made with given parameters
 */
- (CSCircleShape *)addCircleWithTopLeft:(CSShapePoint *)topLeft
							bottomRight:(CSShapePoint *)bottomRight
								  color:(NSUInteger)color
								  width:(NSUInteger)width
							   isFilled:(BOOL)filled
					  completionHandler:(void (^)(CSBasicShape *shape, NSError *error))handler;

/**
 * Adds a text to the whiteboard surface. Method is deprecated.
 * Use CSWhiteboardSurface::addText:atPosition:fontSize:color:completionHandler: instead.
 *
 * @param text Content of the whiteboard text object.
 * @param position Position of the text on the whiteboard surface.
 * @param fontSize Font size of the text.
 * @param color Color of the text.
 * @param handler A block to be called when the operation is completed.
 *        @li @c shape Added text as CSBasicShape object.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 * @return CSWhiteboardText object made with given parameters.
 */
- (CSWhiteboardText *)addText:(NSString *)text
				   atPosition:(CSShapePoint *)position
					 fontSize:(NSUInteger)fontSize
						color:(NSUInteger)color
			completionHandler:(void (^)(CSBasicShape *shape, NSError *error))handler;

/**
 * Updates given shape. Can be used to continue drawing or to move given shape.
 * 
 * @param shape CSBasicShape to be updated or moved.
 * @param handler A block to be called when the operation is completed.
 *        @li @c shape Updated/moved shape.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)updateShape:(CSBasicShape *)shape completionHandler:(void (^)(CSBasicShape *shape, NSError *error))handler;

/**
 * Deletes a shape from surface.
 *
 * @param shape CSBasicShape object to be deleted from whiteboard surface.
 * @param handler A block to be called when the operation is completed.
 *        @li @c shape Deleted shape.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)deleteShape:(CSBasicShape *)shape completionHandler:(void (^)(CSBasicShape *shape, NSError *error))handler;

/**
 * Removes all content from the drawing surface. It shouldn't be used by client unless
 * custom whiteboard canvas is developed. See CSWhiteboardCanvas::clearWhiteboardWithCompletionHandler:
 * and CSIOSWhiteboardCanvas::clearWhiteboardWithCompletionHandler.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c surface Shape that was cleared if operation was successful.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSWhiteboardCanvas::clearWhiteboardWithCompletionHandler:
 * @see CSIOSWhiteboardCanvas::clearWhiteboardWithCompletionHandler:
 */
-(void)clearContentWithCompletionHandler:(void (^)(CSWhiteboardSurface *surface, NSError *error))handler;

@end

/**
 * CSWhiteboardSurfaceDelegate is registered as an observer of whiteboard surface update notifications.
 * Client doesn't need to implement this protocol unless custom whiteboard canvas is developed. This
 * delegate is used internally by Client SDK.
 *
 * @see CSWhiteboardSurface
 */
@protocol CSWhiteboardSurfaceDelegate <NSObject>

/**
 * Reports that a whiteboard surface content was cleared by one of collaboration participant
 * excluding local user. In case of local user this event reported is by completion handler in
 * CSWhiteboardSurface::clearContentWithCompletionHandler:.
 *
 * @param surface The whiteboard surface sending the message.
 *
 * @see CSWhiteboardSurface::clearContentWithCompletionHandler:
 */
- (void)whiteboardSurfaceDidClearSurface:(CSWhiteboardSurface *)surface;

@optional

/**
 * Reports that a shape was added by one of the collaboration participant
 * excluding local user. In case of local user this event reported is by 
 * completion handler in CSWhiteboardSurface::addShapeWithPoints:color:width:isFilled:isFinished:completionHandler:.
 *
 * @param surface The whiteboard surface sending the message.
 * @param shape Added shape.
 *
 * @see CSWhiteboardSurface::addShapeWithPoints:color:width:isFilled:isFinished:completionHandler:
 */
- (void)whiteboardSurface:(CSWhiteboardSurface *)surface didAddShape:(CSBasicShape *)shape;

/**
 * Reports that a shape was updated by one of the collaboration participant
 * excluding local user. In case of local user this event reported is by
 * completion handler in CSWhiteboardSurface::updateShape:completionHandler:.
 *
 * @param surface The whiteboard surface sending the message.
 * @param shape Updated shape.
 *
 * @see CSWhiteboardSurface::updateShape:completionHandler:
 */
- (void)whiteboardSurface:(CSWhiteboardSurface *)surface didUpdateShape:(CSBasicShape *)shape;

/**
 * Reports that on whiteboard page user has finished drawing shape.
 *
 * @param surface The whiteboard surface sending the message.
 * @param shape Finished shape.
 */
- (void)whiteboardSurface:(CSWhiteboardSurface *)surface didEndShape:(CSBasicShape *)shape;

/**
 * Reports that a shape was deleted by one of the collaboration participant
 * excluding local user. In case of local user this event reported is by
 * completion handler in CSWhiteboardSurface::deleteShape:completionHandler:.
 *
 * @param surface The whiteboard surface sending the message.
 * @param shape Deleted shape.
 *
 * @see CSWhiteboardSurface::deleteShape:completionHandler:
 */
- (void)whiteboardSurface:(CSWhiteboardSurface *)surface didDeleteShape:(CSBasicShape *)shape;

@end
