/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Block completion handler used to return image data related to slide.
 *
 * @param slideData Raw binary data of an encoded image (either PNG or JPEG).
 *                  Not nil if the request succeeded.
 * @param error Error information. Not nil if the request failed.
 */
typedef void (^CSSliderSlideFetchCompletionHandler)(NSData  *slideData,
												    NSError *error);

/**
 * The ::CSSliderSlide object provides slide metadata and allows the
 * download of related images.
 *
 * These objects are obtained by the client application either through the
 * ::CSSliderDelegate::slider:didAddSlides: delegate method or the property 
 * ::CSSlider::slides of ::CSSlider class.
 *
 * There is a 1-1 correspondence between ::CSSliderSlide instances and actual
 * slides, so they can be compared by reference.
 *
 * @see CSSlider
 */
@interface CSSliderSlide : NSObject

/**
 * Number of the slide in the slides collection (starting from 1).
 *
 * This value shall never change through object lifetime.
 *
 * At any given point there shall never be two or more available slides with the same number.
 * However, after all slides are removed the numbering might be reset.
 * Currently all slides are removed e.g. when presenter changes.
 */
@property (nonatomic, readonly) NSUInteger number;

/**
 * Time at which the slide was created.
 */
@property (nonatomic, copy, readonly) NSDate *creationDate;

/**
 * @brief Retrieves thumbnail image from the server.
 * 
 * Client is expected to cache image data to avoid multiple calls to this method. 
 * Image data is not stored anywhere inside the SDK.
 *
 * @param completionHandler Completion handler instance that is used to return
 *                          thumbnail image data.
 */
- (void)fetchThumbnailWithCompletionHandler:(CSSliderSlideFetchCompletionHandler)completionHandler;

/**
 * @brief Retrieves full image from the server.
 * 
 * Client is expected to cache image data to avoid multiple calls to this method. 
 * Image data is not stored anywhere inside the SDK.
 *
 * @param completionHandler Completion handler instance that is used to return
 *                          full image data.
 */
- (void)fetchContentWithCompletionHandler:(CSSliderSlideFetchCompletionHandler)completionHandler;

/**
 * @brief Cancels pending ::CSSliderSlide::fetchThumbnailWithCompletionHandler: requests.
 *
 * Fetch requests may be serialized internally so that only a couple (possibly 
 * one) simultaneous server request is sent at any given moment. This can result
 * in high latencies for any new requests if client previously issued fetch
 * requests for many slides during a small period of time. This method allows 
 * the application to cancel some earlier requests before they finish if the
 * client is not interested in the result anymore and therefore reduce time
 * required to finish newer requests.
 */
- (void)cancelThumbnailFetching;

/**
 * @brief Cancels pending ::CSSliderSlide::fetchContentWithCompletionHandler: requests.
 *
 * See ::CSSliderSlide::cancelThumbnailFetching for details.
 */
- (void)cancelContentFetching;

@end
