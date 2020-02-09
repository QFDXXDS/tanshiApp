/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactEmailFieldList.h"
#import "CSEditableContactEmailAddressField.h"

/**
 * List of editable contact email addresses.
 */
@interface CSEditableContactEmailFieldList : CSContactEmailFieldList

/**
 * Replaces all email address fields with given values if write capability is allowed. Otherwise no action.
 * @param emailAddresses array of CSEditableContactEmailAddressField values to set.
 */
- (void)setValues:(NSArray *)emailAddresses;

/**
 * Add an email address to the list if write capability is allowed. Otherwise no action.
 * @param emailAddress an object of type CSEditableContactEmailAddressField values to add.
 */
- (void)addItem:(CSEditableContactEmailAddressField *)emailAddress;

/**
 * Remove an email address from the list if write capability is allowed. Otherwise no action.
 * @param emailAddress an object of type CSEditableContactEmailAddressField values to add.
 */
- (void)removeItem:(CSEditableContactEmailAddressField *)emailAddress;

@end
