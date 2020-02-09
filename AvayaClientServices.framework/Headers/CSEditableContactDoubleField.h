/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactDoubleField.h"

/**
 * Represents a field in an EditableContact which stores a double, inheriting the meta data description of the field from the original contact field.
 * The editable version of a contact field is obtained from the {@link CSEditableContact} class.
 */
@interface CSEditableContactDoubleField: CSContactDoubleField

/**
 * Sets double value stored in this field.
 * @param fieldValue value to be set.
 */
- (void)setFieldValue:(NSNumber *)fieldValue;

@end
