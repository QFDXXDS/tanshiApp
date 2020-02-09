/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactField.h"

/**
 * List of contact handles.
 *
 * If the list is not empty, one of its elements can be set as the default. It is not mandatory.
 */
@interface CSContactIMAddressField : CSContactField

/**
 * The handle.
 */
@property (nonatomic, readonly) NSString *value;

/**
 * The type of this handle.
 */
@property (nonatomic, readonly) NSString *type;

/**
 * The sub-type of this handle.
 */
@property (nonatomic, readonly) NSString *subType;

/**
 * @return A Boolean value indicating whether the field is empty.
 */
@property (nonatomic, readonly) BOOL isEmpty;

@end
