/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Represent busy indicator feature. An attendent can track busy or the idle status
 * of a destination extension. This object is provided with notification
 * whenever the status changes.
 */
@interface CSBusyIndicator : NSObject

/**
 * Returns the destination extension.
 */
@property (nonatomic, readonly) NSString *destinationExtension;

/**
 * Returns the short form of destination extension.
 */
@property (nonatomic, readonly) NSString *destinationShortForm;

/**
 * Returns the label text for the destination extension as assigned
 * by the user or the administrator on the server. 
 * Returns the empty string if not assigned.
 */
@property (nonatomic, readonly) NSString *destinationLabel;

/**
 * Indicates whether the extension is busy or idle.
 */
@property (nonatomic, readonly, getter=isBusy) BOOL busy;

/**
 * Indicates location of BusyIndicator button.
 */
@property (nonatomic, readonly) NSInteger buttonLocation;

@end
