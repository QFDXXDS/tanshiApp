#import <Foundation/Foundation.h>

/**
 * Class representing a slide that has been presented on a conference call.
 *
 * **Unsupported:**
 * Conference slide viewing is currently not supported.
 *
 * The conference slide viewer allows a client application to subscribe and view the list of slides 
 * shared during a conference call. By subscribing to the slide viewer, active and new users can 
 * review the slides that were already shared in a meeting, without affecting the current presentation.
 *
 * ---
 * **Unsupported:**
 * This class and all of its supporting classes are for internal Avaya use only and should not be
 * used by third party applications at this time. This is an incubating feature that is currently
 * under development and the classes and methods associated with this feature are subject to change
 * at any time. Use of this feature will not be supported by Avaya until such time that it is
 * officially released.
 */
@interface CSConferenceSlide : NSObject

/** Network address of the actual size image. */
@property (nonatomic, readonly) NSString *actualSizeImageAddress;

/** Network address of the thumbnail size image. */
@property (nonatomic, readonly) NSString *thumbnailImageAddress;

@end
