/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactStringField.h"

/**
 * Represents a field in an EditableContact which stores a string, inheriting the metadata description of the field from the original contact field.
 * The editable version of a contact field is obtained from the {@link CSEditableContact} class.
 */
@interface CSEditableContactStringField : CSContactStringField

/**
 * Sets string value stored in this field.
 * @param fieldValue value to be set.
 */
- (void)setFieldValue:(NSString *)fieldValue;

@end
