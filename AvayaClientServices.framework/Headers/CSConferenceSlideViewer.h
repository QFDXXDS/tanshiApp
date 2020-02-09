/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSConferenceSlide.h"

@protocol CSConferenceSlideViewerDelegate;

/**
 * **Unsupported:**
 * Conference slide viewing is currently not supported.
 * Interface object representing the slide viewer feature of a conference call.
 * ---
 * **Unsupported:**
 * This class and all of its supporting classes are for internal Avaya use only and should not be
 * used by third party applications at this time. This is an incubating feature that is currently
 * under development and the classes and methods associated with this feature are subject to change
 * at any time. Use of this feature will not be supported by Avaya until such time that it is
 * officially released.
 */
@interface CSConferenceSlideViewer : NSObject

/**
 * The delegate used to handle slide viewer related events.
 */
@property (nonatomic, weak) id<CSConferenceSlideViewerDelegate> delegate;

/**
 * Initiates subscription to slide information.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c slides If the operation was not successful this parameter is nil.
 *        If there is no slides available, an empty list is returned.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)subscribeWithCompletionHandler:(void (^)(NSArray *slides, NSError *error)) handler;

/**
 * Ends subscription to slide information.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)unsubscribeWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Get information about the list of currently available slides.
 */
@property (nonatomic, readonly) NSArray *slides;

@end


/**
 * **Unsupported:**
 * Conference slide viewing is currently not supported.
 * Describes methods that are implemented by the delegate of a @c CSConferenceSlideViewer.
 */
@protocol CSConferenceSlideViewerDelegate <NSObject>

/**
 * Called to report a new slide has been added to the presentation.
 * @param slideViewer Slide viewer instance this callback is associated with.
 * @param slide Information about the new slide.
 */

- (void)conferenceSlideViewer: (CSConferenceSlideViewer *)slideViewer didHaveNewSlide: (CSConferenceSlide *) slide;

/**
 * Called when the slide viewer session is over.
 *
 * @param slideViewer Slide viewer instance this callback is associated with.
 * @param endedRemotely Flag indicating whether slide viewer connection was ended by
 * the server, or by the local user.
 */
- (void)conferenceSlideViewer: (CSConferenceSlideViewer *)slideViewer didEndSubscription: (BOOL) endedRemotely;

@end



