/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactField.h"

/**
 * Interface for multi-value contact field. It must be defined in order to provide
 * information about capabilities when there aren't any items.
 */
@interface CSContactMultiValueField : CSContactField

/**
 * Return NSArray of field values.
 * @return NSArray of field values.
 */
@property (nonatomic, readonly) NSArray *values;

/**
 * Returns YES if field is empty.
 * @return YES if field is empty.
 */
@property (nonatomic, readonly) BOOL isEmpty;

/**
 * Returns size of values field.
 * @return size of values field.
 */
@property (nonatomic, readonly) NSUInteger size;

@end
