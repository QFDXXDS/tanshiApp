/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * The auto dial feature is used to store frequently used or important
 * numbers. When the button programmed for a given autodial number is
 * pressed, that stored number will be dialed.
 */
@interface CSAutodial : NSObject

/**
 * Constructs an Autodial object from the specified parameters.
 *
 * @param buttonLocation Index of Autodial button.
 * @param label Label of destination extension.
 * @param extension Destination extension.
 * @param isExtensionEditable YES if destination extension is editable.
 */
- (instancetype)initWithButtonLocation:(NSInteger)buttonLocation destinationLabel:(NSString *)label destinationExtension:(NSString *)extension destinationExtensionEditable:(BOOL)isExtensionEditable;

/**
 * The button index of the autodial feature as configured on the server.
 */
@property (nonatomic, readonly) NSInteger buttonLocation;

/**
 * Returns the label text for the destination extension as assigned
 * by the user or the administrator on the server.
 */
@property (nonatomic, copy) NSString *destinationLabel;

/**
 * Returns the destination extension.
 */
@property (nonatomic, copy) NSString *destinationExtension;

/**
 * Indicates whether the destination extension field can be edited by the user or not.
 */
@property (nonatomic, readonly, getter=isDestinationExtensionEditable) BOOL destinationExtensionEditable;

@end
