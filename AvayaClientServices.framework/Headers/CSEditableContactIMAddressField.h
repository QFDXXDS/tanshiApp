/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactIMAddressField.h"

/**
 * Represents a field in an EditableContact which stores an IM address, inheriting the meta data description of the field from the original contact field.
 * The editable version of a contact field is obtained from the {@link CSEditableContact} class.
 */
@interface CSEditableContactIMAddressField : CSContactIMAddressField

/**
 * Sets email address value stored in this field.
 * @param value value to be set.
 */
- (void)setValue:(NSString *)value;

/**
 * Sets email address type stored in this field.
 * @param type type to be set.
 */
- (void)setType:(NSString *)type;

/**
 * Sets email address subtype stored in this field.
 * @param subType type to be set.
 */
- (void)setSubType:(NSString *)subType;

@end
