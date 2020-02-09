/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@protocol CSSliderDelegate;

/**
 * @brief The CSSlider object provides access to slider-related actions.
 * This object is accessible via the CSCollaboration object.
 *
 * Feature overview:
 *
 * - The server periodically generates a 'screenshot' of currently presented
 *   content (screen sharing or whiteboard) and notifies clients that the data
 *   is available to download. The client is notified of these new "slides" 
 *   via the ::CSSliderDelegate::slider:didAddSlides:.
 *
 * - For each slide, the client can download the full image and/or the smaller thumbnail.
 *
 * Certain collaboration/server events (i.e. change of presenter) might make the slides 
 * unavailable which is reported via the ::CSSliderDelegate::slider:didRemoveSlides: delegate method.
 */
@interface CSSlider : NSObject

@property (nonatomic, weak) id<CSSliderDelegate> delegate;


/**
 * NSArray of currently available slides.
 *
 * This property is useful if client does not want to handle ::CSSliderDelegate
 * events when the slider feature is not displayed to the user. It can be used 
 * to obtain the up-to-date collection of slides when the slider UI is about to
 * be displayed. To receive further slide updates, the client should set
 * ::CSSlider::delegate.
 * The client should obtain current collection and set ::CSSlider::delegate in
 * a single method, invoked on the same dispatch queue as passed to the 
 * ::CSClient. This guarantees that no slides are duplicated or missed due to 
 * race conditions.
 */
@property (nonatomic, readonly, copy) NSArray *slides;

@end

@protocol CSSliderDelegate <NSObject>

/**
 * Is invoked when new slides are available.
 *
 * The preferred time to register event handlers is as soon as CSCollaboration
 * instance is started, i.e. in the delegate method
 * ::CSCollaborationDelegate::collaborationDidStart: event of the 
 * ::CSCollaborationDelegate.
 *
 * In cases where the client delays registering event handlers to some later 
 * point in time, the ::CSSlider::slides property can be used to retrieve 
 * currently available slides.
 *
 * @param slider slider which sent notification.
 * @param addedSliderSlides array encapsulates a non-nil, thread-safe, read-only
 *                          collection of new slides.
 */
- (void)slider:(CSSlider *)slider didAddSlides:(NSArray *)addedSliderSlides;

/**
 * Is invoked when some of the previously added slides are no longer available.
 *
 * When a slide is reported as removed, any subsequent attempt to fetch 
 * CSSliderSlide images shall result in an error.
 *
 * See ::CSSliderDelegate::slider:didAddSlides: for information at which point 
 * event handlers should be registered.
 *
 * @param slider slider which sent notification.
 * @param removedSliderSlides array encapsulates a non-nil, thread-safe, 
 *        read-only collection of now unavailable slides.
 */
- (void)slider:(CSSlider *)slider didRemoveSlides:(NSArray *)removedSliderSlides;

@end
