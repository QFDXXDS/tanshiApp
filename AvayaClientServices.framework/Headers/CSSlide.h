/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#include "CSWhiteboardSurface.h"
#import "CSRenderingBlock.h"

@protocol CSSlideDelegate;

/**
 * **Unsupported:**
 * The library sharing feature is currently not supported.
 * ---
 * **Unsupported:**
 * This class and all of its supporting classes are for internal Avaya use only and should not be
 * used by third party applications at this time. This is an incubating feature that is currently
 * under development and the classes and methods associated with this feature are subject to change
 * at any time. Use of this feature will not be supported by Avaya until such time that it is
 * officially released.
 */
@interface CSSlide : CSWhiteboardSurface

/**
 * Not supported in Client SDK 3.0
 */
@property (nonatomic, weak) id<CSSlideDelegate> slideDelegate;

/**
 * Not supported in Client SDK 3.0
 */
- (void)requestSlideDataWithCompletionHandler:(void (^)(CSRenderingBlock *data, NSError *error))handler;

/**
 * Not supported in Client SDK 3.0
 *
 * This method compares this slide to other. The subject of comparison
 * is clientsdk::SlidePtr of this and other slides.
 */
- (BOOL)isEqualToSlide:(CSSlide *)other;

@end

/**
 * **Unsupported:**
 * The library sharing feature is currently not supported.
 */
@protocol CSSlideDelegate <NSObject>


@end
