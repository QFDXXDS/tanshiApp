/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactField.h"

/**
 * Defines the types of phone numbers that can be associated with a contact.
 */
typedef NS_ENUM(NSUInteger, CSContactPhoneNumberType) {
	CSContactPhoneNumberTypeWork,	/**< Work phone number type. */
	CSContactPhoneNumberTypeHandle,	/**< Home phone number type. */
	CSContactPhoneNumberTypeMobile,	/**< Mobile phone number type. */
	CSContactPhoneNumberTypeHome,	/**< Handle phone number type. */
	CSContactPhoneNumberTypeFax,	/**< Fax phone number type. */
	CSContactPhoneNumberTypePager,	/**< Pager phone number type. This type is not supported by enterprise sources. */
	CSContactPhoneNumberTypeAssistant, /**< Assistant phone number type. This type is not supported by enterprise sources. */
	CSContactPhoneNumberTypeOther	/**< Assistant phone number type. This type is not supported by enterprise sources. */
};

/**
 * Represents a phone number field associated with a contact.
 *
 * Since a given contact can have multiple phone numbers a default number must be chosen.
 * Only one phone number can be default for a given contact.
 */
@interface CSContactPhoneField : CSContactField

/**
 * Phone number.
 * @return A NSString containing the phone number.
 */
@property (nonatomic, readonly) NSString *phoneNumber;

/**
 * The phone number Label1.
 * @return A NSString containing the Label1.
 */
@property (nonatomic, readonly) NSString *label1;

/**
 * The phone number Label2.
 * @return A NSString containing the Label2.
 */
@property (nonatomic, readonly) NSString *label2;

/**
 * The phone number category.
 * @return A NSString containing the category.
 */
@property (nonatomic, readonly) NSString *category;

/**
 * The phone number type, i.e work.
 * @return The phone number type.
 */
@property (nonatomic, readonly) CSContactPhoneNumberType type;

/**
 * The phone number speed dial flag.
 * @return YES if speed dial is enabled.
 */
@property (nonatomic, readonly, getter=isSpeedDialEnabled) BOOL speedDialEnabled;

/**
 * A Boolean value indicating whether this field respresents the default phone
 * number.
 * @return YES if field represents the default phone number.
 */
@property (nonatomic, readonly, getter=isDefaultPhoneNumber) BOOL defaultPhoneNumber;

/**
 * Is this the default phone number for the contact?
 * @return YES if this is the default phone number in the list.
 */
@property (nonatomic, readonly) BOOL isEmpty;

@end
