/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSWhiteboardSurface.h"
#import "CSParticipant.h"

@class CSDataSet;

@protocol CSWhiteboardDelegate;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"

/**
 * The CSWhiteboard object provides access to whiteboard related capabilities and actions.
 * CSWhiteboard object is accessible via CSCollaboration. Status updates concerning whiteboard
 * are reported via CSWhiteboardDelegate.
 *
 * \if OSX
 * In order to display whiteboard client also
 * needs to create CSWhiteboardCanvas and initialize it properly.
 * \endif
 *
 * \if iOS
 * In order to display whiteboard client also
 * needs to create CSIOSWhiteboardCanvas and initialize it properly.
 * \endif
 *
 * CSWhiteboard is responsible for handling whole whiteboard session. Whiteboard session may have
 * many independent CSWhiteboardSurface objects where each of CSWhiteboardSurface object is responsible
 * for one whiteboard drawings.
 *
 * @see CSCollaboration
 *
 */

#pragma clang diagnostic pop

@interface CSWhiteboard : NSObject

/**
 * The delegate used to handle events related to whiteboard session.
 */
@property (nonatomic, weak) id<CSWhiteboardDelegate> delegate;

/**
 * Array containing all existing CSWhiteboardSurface objects in the current whiteboard session.
 * Array is sorted by creating time of objects.
 */
@property (nonatomic, readonly) NSArray *surfaces;

/**
 * CSCapability object indicating whether the local user is allowed to remove
 * whiteboard surface. To do so, the local user needs to be moderator, presenter
 * or panel model mode has to be enabled. It's not allowed to remove surface 
 * when it's the last whiteboard surface in current whiteboard session.
 *
 * @see CSWhiteboardSurface
 */
@property (nonatomic, readonly, copy) CSCapability *removeSurfaceCapability;

/**
 * CSCapability object indicating whether the local user is allowed to add
 * whiteboard surface. To do so, the local user needs to be moderator, presenter
 * or panel model mode has to be enabled.
 *
 * @see CSWhiteboardSurface
 * @see CSWhiteboard::requestNewSurfaceWithCompletionHandler:
 */
@property (nonatomic, readonly, copy) CSCapability *addSurfaceCapability;

/**
 * Starts the whiteboard session.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c surface CSWhiteboardSurface object of first whiteboard surface created
 *		  on whiteboard start.
 *		  @li @c participant CSParticipant object providing information about collaboration.
 *		  participant who started whiteboard (local user in case of this method).
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)startWithCompletionHandler:(void (^)(CSWhiteboardSurface *surface, CSParticipant *participant, NSError *error))handler;

/**
 * Ends the whiteboard session.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c whiteboard Ended whiteboard if operation was successful.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)endWithCompletionHandler:(void (^)(CSWhiteboard *whiteboard, NSError *error))handler;

/**
 * Requests new whiteboard surface. If whiteboard surface was added
 * CSWhiteboardDelegate::whiteboard:didAddSurface:byParticipant: is called 
 * apart from completion handler.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c surface created CSWhiteboardSurface object.
 *		  @li @c participant CSParticipant object providing information about
 *		  collaboration participant who requested surface (local user in case of this method).
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
* @see CSWhiteboardDelegate::whiteboard:didAddSurface:byParticipant:
 */
- (void)requestNewSurfaceWithCompletionHandler:(void (^)(CSWhiteboardSurface *surface, CSParticipant *participant, NSError *error))handler;

/**
 * Removes whiteboard surface. If whiteboard surface was removed
 * CSWhiteboardDelegate::whiteboard:didRemoveSurface:byParticipant: is called
 * apart from completion handler.
 *
 *
 * @param surface The surface to remove.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSWhiteboardDelegate::whiteboard:didRemoveSurface:byParticipant:
 */
- (void)removeSurface:(CSWhiteboardSurface *)surface withCompletionHandler:(void (^)(CSWhiteboardSurface *surface, CSParticipant *participant, NSError *error))handler;

/**
 * Returns active whiteboard surface. With property CSWhiteboard::surfaces 
 * can be used to display number of active sharing surface in UI.
 *
 */
- (CSWhiteboardSurface *)getActiveSurface;


@end

/**
 * Whiteboard delegate provides updates about the status of whiteboard sharing.
 * Shapes drawn during a content sharing session is reported through the vector returned from
 * getShapes method. As a result, no separate shape added/removed/updated callbacks
 * are provided through the delegate.
 */
@protocol CSWhiteboardDelegate <NSObject>

/**
 * Sent when the whiteboard session ends, either by a local or remote action.
 *
 * @param whiteboard CSWhiteboard object sending the message.
 *
 * @see CSWhiteboard::endWithCompletionHandler:
 */
- (void)whiteboardDidEnd:(CSWhiteboard *)whiteboard;

/**
 * Sent when the whiteboard session starts, either by a local or remote action.
 *
 * @param whiteboard CSWhiteboard object sending the message.
 * @param surface Active surface of started whiteboard session.
 * @param participant Data of participant who started whiteboard.
 *
 * @see CSWhiteboard::startWithCompletionHandler:
 */
-  (void)whiteboard:(CSWhiteboard *)whiteboard
didStartWithSurface:(CSWhiteboardSurface *)surface
	  byParticipant:(CSParticipant *)participant;

/**
 * Sent when the whiteboard active surface changes, either by a local or remote action.
 *
 * @param whiteboard CSWhiteboard object sending the message.
 * @param surface Whiteboard surface set as active.
 * @param participant Data of participant who set whiteboard surface active.
 *
 * @see CSWhiteboardSurface::setAsActiveWithCompletionHandler:
 */
-  (void)whiteboard:(CSWhiteboard *)whiteboard
didSetActiveSurface:(CSWhiteboardSurface *)surface
	  byParticipant:(CSParticipant *)participant;

/**
 * Sent when the whiteboard surface is added, either by a local or remote action.
 *
 * @param whiteboard CSWhiteboard object sending the message.
 * @param surface Added whiteboard surface
 * @param participant Data of participant who added surface.
 *
 * @see CSWhiteboard::requestNewSurfaceWithCompletionHandler:
 */
- (void)whiteboard:(CSWhiteboard *)whiteboard
	 didAddSurface:(CSWhiteboardSurface *)surface
	 byParticipant:(CSParticipant *)participant;

/**
 * Sent when the whiteboard surface is removed, either by a local or remote action.
 *
 * @param whiteboard CSWhiteboard object sending the message.
 * @param surface Removed whiteboard surface
 * @param participant Data of participant who removed surface.
 *
 * @see CSWhiteboard::removeSurface:withCompletionHandler:}
 */
- (void)whiteboard:(CSWhiteboard *)whiteboard
  didRemoveSurface:(CSWhiteboardSurface *)surface
	 byParticipant:(CSParticipant *)participant;

@end
