/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactIMAddressFieldList.h"
#import "CSEditableContactIMAddressField.h"

/**
 * List of editable contact IM addresses.
 */
@interface CSEditableContactIMAddressFieldList : CSContactIMAddressFieldList

/**
 * Replaces all IM address fields with given values if write capability is allowed. Otherwise no action.
 * @param addresses array of CSEditableContactIMAddressField values to set.
 */
- (void)setValues:(NSArray *)addresses;

/**
 * Add an IM address to the list if write capability is allowed. Otherwise no action.
 * @param address an object of type CSEditableContactIMAddressField values to add.
 */
- (void)addItem:(CSEditableContactIMAddressField *)address;

/**
 * Remove an IM address from the list if write capability is allowed. Otherwise no action.
 * @param address an object of type CSEditableContactIMAddressField values to add.
 */
- (void)removeItem:(CSEditableContactIMAddressField *)address;

@end
