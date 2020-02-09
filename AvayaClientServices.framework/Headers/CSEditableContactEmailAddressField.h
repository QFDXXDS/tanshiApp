/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactEmailAddressField.h"

/**
 * Represents a field in an EditableContact which stores an email address, inheriting the metadata description of the field from the original contact field.
 * <p>In order to add a new email address create object of this class and add to the email addresses collection.</p>
 */
@interface CSEditableContactEmailAddressField : CSContactEmailAddressField

/**
 * Sets or updates the email Address.
 * @param address The new email Address.
 */
- (void)setAddress:(NSString *)address;

/**
 * Sets or updates the email Address label.
 * @param label The new email Address label.
 */
- (void)setLabel:(NSString *)label;

/**
 * Sets or updates the email Address type.
 * @param emailAddressType The new email Address type.
 */
- (void)setEmailAddressType:(CSContactEmailAddressType)emailAddressType;

@end
