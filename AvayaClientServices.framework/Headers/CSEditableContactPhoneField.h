/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactPhoneField.h"

/**
 * Represents a field in an CSEditableContact which stores a phone number, inheriting the metadata description of the field from the original contact field.
 * The editable version of a contact field is obtained from the {@link CSEditableContact} class.
 */
@interface CSEditableContactPhoneField : CSContactPhoneField

/**
 * Sets or updates the phone number string.
 * @param phoneNumber A NSString containing the new phone number.
 */
- (void)setPhoneNumber:(NSString *)phoneNumber;

/**
 * Sets or updates the phone number Label1.
 * @param label1 A NSString containing the new phone number Label1.
 */
- (void)setLabel1:(NSString *)label1;

/**
 * Sets or updates the phone number Label2.
 * @param label2 A NSString containing the new phone number Label2.
 */
- (void)setLabel2:(NSString *)label2;

/**
 * Sets or updates the phone number category.
 * @param category A NSString containing the new phone number category.
 */
- (void)setCategory:(NSString *)category;

/**
 * Sets or updates the phone number type (e.g. WORK, HOME, etc).
 * @param phoneNumberType The new phone number type.
 */
- (void)setPhoneNumberType:(CSContactPhoneNumberType)phoneNumberType;

/**
 * Sets or updates the speed dial flag.
 * @param speedDialEnabled flag value to be set.
 */
- (void)setSpeedDialEnabled:(BOOL)speedDialEnabled;

/**
 * Changes the default status of this phone number.
 * This field is not affected by {@link #writeCapability} capability.
 * @param defaultPhoneNumber Set to true to make this phone number the default.
 */
- (void)setDefaultPhoneNumber:(BOOL)defaultPhoneNumber;

@end
