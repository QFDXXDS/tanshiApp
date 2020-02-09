/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactField.h"

/**
 * Represents a double field associated with a contact.
 */
@interface CSContactDoubleField : CSContactField

/**
 * Double value stored in this field.
 * @return value of field.
 */
@property (nonatomic, readonly) NSNumber *fieldValue;

/**
 * Returns YES if field is empty.
 * @return YES if field is empty.
 */
@property (nonatomic, readonly) BOOL isEmpty;

@end
