/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSBasicShape.h"

/**
 * CSWhiteboardText objects represent text that can be added to whiteboard surface.
 * Client doesn't need to use this class explicitly unless custom whiteboard is developed.
 *
 * @see CSWhiteboardSurface
 */
@interface CSWhiteboardText : CSBasicShape

/**
 * Content of CSWhiteboardText.
 */
@property (nonatomic, readonly) NSString *content;

/**
 * Position of text on whiteboard surface.
 */
@property (nonatomic, readonly) CGPoint position;

@end
