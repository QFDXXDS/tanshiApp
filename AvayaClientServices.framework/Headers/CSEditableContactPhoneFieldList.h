/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactPhoneFieldList.h"
#import "CSEditableContactPhoneField.h"

/**
 * List of editable contact phone numbers.
 */
@interface CSEditableContactPhoneFieldList : CSContactPhoneFieldList

/**
 * Replaces all phone number fields with given values if write capability is allowed. Otherwise no action.
 * @param phoneNumbers array of CSEditableContactPhoneField values to set.
 */
- (void)setValues:(NSArray *)phoneNumbers;

/**
 * Add an phone number to the list if write capability is allowed. Otherwise no action.
 * @param phoneNumber an object of type CSEditableContactPhoneField values to add.
 */
- (void)addItem:(CSEditableContactPhoneField *)phoneNumber;

/**
 * Remove an phone number from the list if write capability is allowed. Otherwise no action.
 * @param phoneNumber an object of type CSEditableContactPhoneField values to add.
 */
- (void)removeItem:(CSEditableContactPhoneField *)phoneNumber;

@end
