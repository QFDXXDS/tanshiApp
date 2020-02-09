/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactField.h"

/**
 * Represents a string field associated with a contact.
 */
@interface CSContactStringField : CSContactField

/**
 * String value stored in this field.
 * @return value of field.
 */
@property (nonatomic, readonly) NSString *fieldValue;

/**
 * Returns YES if field is empty.
 * @return YES if field is empty.
 */
@property (nonatomic, readonly) BOOL isEmpty;

@end
