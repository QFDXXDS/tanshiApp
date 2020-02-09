/* Copyright Avaya Inc. */

#import <UIKit/UIKit.h>
#import "CSScreenSharingListener.h"
#import "CSContentSharing.h"

/**
 * CSIOSScreenSharingView object provides screen sharing canvas on which
 * received frames are drawn on. Client should hold strong reference to object 
 * of this class.
 */
@interface CSIOSScreenSharingView : UIView

/**
 * CSScreenSharingListener object which implements CSContentSharingDelegate
 * and is responsible for drawing incoming frames on CALayer object
 * backing CSScreenSharingView. CSScreenSharingListener has to be created and set
 * by client.
 */
@property (nonatomic, strong) CSScreenSharingListener *contentSharingDelegate;

/**
 * Image of cursor which is rendered on sharing canvas. By default image with name
 * cursor.png from CSScreenSharingListener class bundle is taken. In case image
 * is not provided neither in CSScreenSharingListener bundle nor by
 * this property, cursor isn't rendered on sharing canvas.
 */
@property (strong, nonatomic) UIImage *cursorImage;

/**
 * Image of pause which is rendered in the center of sharing canvas when sharing
 * is paused. There's no default image for pause icon. In case image
 * is not provided by client using this property, pause image isn't rendered on 
 * sharing canvas.
 */
@property (strong, nonatomic) UIImage *pauseImage;

@end
