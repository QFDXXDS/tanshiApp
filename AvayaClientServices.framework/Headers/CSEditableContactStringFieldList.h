/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactStringFieldList.h"
#import "CSEditableContactStringField.h"

/**
 * List of editable contact strings fields.
 */
@interface CSEditableContactStringFieldList : CSContactStringFieldList

/**
 * Replaces all string fields with given values if write capability is allowed. Otherwise no action.
 * @param strings array of CSEditableContactStringField values to set.
 */
- (void)setValues:(NSArray *)strings;

/**
 * Add an string to the list if write capability is allowed. Otherwise no action.
 * @param string an object of type CSEditableContactStringField values to add.
 */
- (void)addItem:(CSEditableContactStringField *)string;

/**
 * Remove an string from the list if write capability is allowed. Otherwise no action.
 * @param string an object of type CSEditableContactStringFieldList values to add.
 */
- (void)removeItem:(CSEditableContactStringField *)string;

@end
