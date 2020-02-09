/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContact.h"
#import "CSEditableContactDoubleField.h"
#import "CSEditableContactStringField.h"
#import "CSEditableContactBoolField.h"
#import "CSEditableContactPhoneFieldList.h"
#import "CSEditableContactEmailFieldList.h"
#import "CSEditableContactIMAddressFieldList.h"
#import "CSEditableContactStringFieldList.h"

/**
 * Mutable contact object which exposes all provided contact details.
 *
 * CSEditableContact can be created by using either ::CSContactService::createEditableContact
 * or ::CSContactService::createEditableContactFromContact:. Second method needs a regular
 * contact as a source for data.
 *
 * EditableContact can be used in two contact service methods - ::CSContactService::addContact:completionHandler:
 * and ::CSContactService::updateContact:completionHandler:.
 */
@interface CSEditableContact : NSObject<CSContact>

/**
 * The matching/merging address. That parameter can be used as a record’s unique id.
 * @return Contact string field containing the matching/merging address.
 */
@property (nonatomic, readonly) NSString *uniqueAddressForMatching;

/**
 * The non-localized last name.
 * @return Contact string field containing non-localized last name.
 */
@property (nonatomic, readonly) CSEditableContactStringField *asciiLastName;

/**
 * The non-localized first name.
 * @return Contact string field containing non-localized first name.
 */
@property (nonatomic, readonly) CSEditableContactStringField *asciiFirstName;

/**
 * The non-localized display name.
 * @return Contact string field containing non-localized display name.
 */
@property (nonatomic, readonly) CSEditableContactStringField *asciiDisplayName;

/**
 * The non-localized alias.
 * @return Contact string field containing a non-localized alias.
 */
@property (nonatomic, readonly) CSEditableContactStringField *asciiAlias;

/**
 * The native first name.
 * @return Contact string field containing the native first name.
 */
@property (nonatomic, readonly) CSEditableContactStringField *firstName;

/**
 * The native last name.
 * @return Contact string field containing the native last name.
 */
@property (nonatomic, readonly) CSEditableContactStringField *lastName;

/**
 * The native display name.
 * @return Contact string field containing the native display name.
 */
@property (nonatomic, readonly) CSEditableContactStringField *displayName;

/**
 * The native alias.
 * @return Contact string field containing the native alias.
 */
@property (nonatomic, readonly) CSEditableContactStringField *alias;

/**
 * The street address.
 * @return Contact string field containing the street address.
 */
@property (nonatomic, readonly) CSEditableContactStringField *streetAddress;

/**
 * The city.
 * @return Contact string field containing the city.
 */
@property (nonatomic, readonly) CSEditableContactStringField *city;

/**
 * The state.
 * @return Contact string field containing the state.
 */
@property (nonatomic, readonly) CSEditableContactStringField *state;

/**
 * The country.
 * @return Contact string field containing the country.
 */
@property (nonatomic, readonly) CSEditableContactStringField *country;

/**
 * The postal code.
 * @return Contact string field containing the postal code.
 */
@property (nonatomic, readonly) CSEditableContactStringField *postalCode;

/**
 * The name of a person who is a supervisor.
 * @return Contact string field containing the name of a person who is a supervisor.
 */
@property (nonatomic, readonly) CSEditableContactStringField *manager;

/**
 * The title or company role.
 * @return Contact string field containing the title or company role.
 */
@property (nonatomic, readonly) CSEditableContactStringField *title;

/**
 * The language is per contact record.
 * @return Contact string field containing the language is per contact record.
 */
@property (nonatomic, readonly) CSEditableContactStringField *language;

/**
 * The company.
 * @return Contact string field containing the company.
 */
@property (nonatomic, readonly) CSEditableContactStringField *company;

/**
 * The department.
 * @return Contact string field containing the department.
 */
@property (nonatomic, readonly) CSEditableContactStringField *department;

/**
 * The notes field.
 * @return Contact string field containing the notes field.
 */
@property (nonatomic, readonly) CSEditableContactStringField *notes;

/**
 * The rank field defining the contact sorting order.
 * @return Non-negative double value. 0.0 value means "No rank".
 */
@property (nonatomic, readonly) CSEditableContactDoubleField *rank;

/**
 * The list of custom1 values.
 * @return list of custom1 values.
 */
@property (nonatomic, readonly) CSEditableContactStringFieldList *custom1;

/**
 * The list of custom2 values.
 * @return list of custom2 values.
 */
@property (nonatomic, readonly) CSEditableContactStringFieldList *custom2;

/**
 * The list of custom3 values.
 * @return list of custom3 values.
 */
@property (nonatomic, readonly) CSEditableContactStringFieldList *custom3;

/**
 * The location.
 * @return Contact string field containing the location.
 */
@property (nonatomic, readonly) CSEditableContactStringField *location;

/**
 * The list of phone numbers.
 * @return Contact multi value field containing list of phone numbers.
 */
@property (nonatomic, readonly) CSEditableContactPhoneFieldList *phoneNumbers;

/**
 * The list of email addresses.
 * @return Contact multi value field containing list of email addresses.
 */
@property (nonatomic, readonly) CSEditableContactEmailFieldList *emailAddresses;

/**
 * Contact's list of instant messaging addresses.
 * @return Contact multi value field containing list of instant messaging addresses..
 */
@property (nonatomic, readonly) CSEditableContactIMAddressFieldList *IMAddresses;

/**
 * The favorite flag.
 * @return Contact bool field containing the favorite flag.
 */
@property (nonatomic, readonly) CSEditableContactBoolField *favorite;

/**
 * The buddy flag. Used for presence feature purpose.
 * @return Contact bool field containing the buddy flag.
 */
@property (nonatomic, readonly, getter=isBuddy) CSEditableContactBoolField *isBuddy;

/**
 * The VIP flag.
 * @return Contact bool field containing the VIP flag.
 */
@property (nonatomic, readonly, getter=isVIP) CSEditableContactBoolField *isVIP;

/*
 * Contact is video capable.
 */
@property (nonatomic, readonly) CSContactBoolField *videoCapable;

/**
 * Returns Contact capabilities to save the current state of the contact
 *  1. A savable contact has 1 name (first, last), and at least 1 address (phone number, email).
 *  2. Also cannot break any rules for the maximum number of phone numbers, email addresses etc. for a provider.
 * @return YES if it's possible to save Contact with current state of values, NO if not.
 */
@property (nonatomic, readonly) BOOL isContactSavable;

/*
 * Returns YES if provider with ExtendedDetailsCapability is configured. Provider with this capability supports more fields for contacts.
 * @return YES if provider with ExtendedDetailsCapability is configured. Provider with this capability supports more fields for contacts.
 */
@property (nonatomic, readonly) BOOL isExtendedContactDetailsAvailable;

/*
 * Returns YES if addition of email address will not make contact invalid.
 * @return YES if addition of email address will not make contact invalid.
 * @deprecated Use the {@link canAddEmailAddress} method instead.
 */
@property (nonatomic, readonly) BOOL canAddEmailAddress DEPRECATED_ATTRIBUTE;;

/*
 * Returns YES if addition of IM address will not make contact invalid.
 * @return YES if addition of IM address will not make contact invalid.
 */
@property (nonatomic, readonly) BOOL canAddIMAddress;

/*
 * Returns YES if addition of phone number of a specified type will not make contact invalid.
 * @param contactPhoneNumberType type of phone number.
 * @return YES if addition of phone number of a given {@link CSContactPhoneNumberType} is allowed.
 */
- (BOOL)canAddPhoneNumberOfType:(CSContactPhoneNumberType)type;

/*
 * Returns YES if addition of email address of a specified type will not make contact invalid.
 * @param type type of email address.
 * @return YES if addition of email address of a given {@link CSContactEmailAddressType} is allowed.
 */
- (BOOL)canAddEmailAddressOfType:(CSContactEmailAddressType)type;

/**
 * The list extra fields used for local contacts. 
 * Returns empty NSDictionary.
 */
@property (nonatomic, readonly) NSDictionary *extraFields;

@end
