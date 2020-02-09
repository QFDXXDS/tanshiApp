/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactField.h"

/**
 * Describes the type associated with the email address.
 */
typedef NS_ENUM(NSUInteger, CSContactEmailAddressType) {
	/**
	 * Work email address type.
	 */
	CSContactEmailAddressTypeWork,

	/**
	 * Home email address type.
	 */
	CSContactEmailAddressTypeHome,

	/**
	 * Mobile email address type.
	 */
	CSContactEmailAddressTypeMobile,

	/**
	 * Custom email address type.
	 */
	CSContactEmailAddressTypeCustom,

	/**
	 * Other email address type.
	 */
	CSContactEmailAddressTypeOther
};

/**
 * This class describes the email addresses for the contact record.
 */
@interface CSContactEmailAddressField : CSContactField

/**
 * The type of this email address (e.g. WORK, HOME, etc).
 * @return The email address type.
 */
@property (nonatomic, readonly) CSContactEmailAddressType type;

/**
 * The email address.
 * @return A NSString containing the email address.
 */
@property (nonatomic, readonly) NSString *address;

/**
 * The email label.
 * @return A NSString containing the email label.
 */
@property (nonatomic, readonly) NSString *label;

@end
