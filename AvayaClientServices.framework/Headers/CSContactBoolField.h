/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactField.h"

/**
 * Represents a boolean field associated with a contact.
 */
@interface CSContactBoolField : CSContactField

/**
 * Boolean value stored in this field.
 * @return value of field.
 */
@property (nonatomic, readonly) BOOL fieldValue;

/**
 * Returns YES if field is empty.
 * @return YES if field is empty.
 */
@property (nonatomic, readonly) BOOL isEmpty;

@end
