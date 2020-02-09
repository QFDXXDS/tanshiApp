/* Copyright Avaya Inc. */

/**
 * Protocol used as a common interface for read-only and editable contacts.
 */
@protocol CSContact <NSObject>

@required

/**
 * The matching/merging address. That parameter can be used as a record’s unique id.
 * @return Contact string field containing the matching/merging address.
 */
@property (nonatomic, readonly) NSString *uniqueAddressForMatching;

/**
 * The non-localized last name.
 * @return Contact string field containing non-localized last name.
 */
@property (nonatomic, readonly) CSContactStringField *asciiLastName;

/**
 * The non-localized first name.
 * @return Contact string field containing non-localized first name.
 */
@property (nonatomic, readonly) CSContactStringField *asciiFirstName;

/**
 * The non-localized display name.
 * @return Contact string field containing non-localized display name.
 */
@property (nonatomic, readonly) CSContactStringField *asciiDisplayName;

/**
 * The non-localized alias.
 * @return Contact string field containing a non-localized alias.
 */
@property (nonatomic, readonly) CSContactStringField *asciiAlias;

/**
 * The native first name.
 * @return Contact string field containing the native first name.
 */
@property (nonatomic, readonly) CSContactStringField *firstName;

/**
 * The native last name.
 * @return Contact string field containing the native last name.
 */
@property (nonatomic, readonly) CSContactStringField *lastName;

/**
 * The native display name.
 * @return Contact string field containing the native display name.
 */
@property (nonatomic, readonly) CSContactStringField *displayName;

/**
 * The native alias.
 * @return Contact string field containing the native alias.
 */
@property (nonatomic, readonly) CSContactStringField *alias;

/**
 * The street address.
 * @return Contact string field containing the street address.
 */
@property (nonatomic, readonly) CSContactStringField *streetAddress;

/**
 * The city.
 * @return Contact string field containing the city.
 */
@property (nonatomic, readonly) CSContactStringField *city;

/**
 * The state.
 * @return Contact string field containing the state.
 */
@property (nonatomic, readonly) CSContactStringField *state;

/**
 * The country.
 * @return Contact string field containing the country.
 */
@property (nonatomic, readonly) CSContactStringField *country;

/**
 * The postal code.
 * @return Contact string field containing the postal code.
 */
@property (nonatomic, readonly) CSContactStringField *postalCode;

/**
 * The name of a person who is a supervisor.
 * @return Contact string field containing the name of a person who is a supervisor.
 */
@property (nonatomic, readonly) CSContactStringField *manager;

/**
 * The title or company role.
 * @return Contact string field containing the title or company role.
 */
@property (nonatomic, readonly) CSContactStringField *title;

/**
 * The language is per contact record.
 * @return Contact string field containing the language is per contact record.
 */
@property (nonatomic, readonly) CSContactStringField *language;

/**
 * The company.
 * @return Contact string field containing the company.
 */
@property (nonatomic, readonly) CSContactStringField *company;

/**
 * The department.
 * @return Contact string field containing the department.
 */
@property (nonatomic, readonly) CSContactStringField *department;

/**
 * The notes field.
 * @return Contact string field containing the notes field.
 */
@property(nonatomic, readonly) CSContactStringField *notes;

/**
 * The rank field defining the contact sorting order.
 * @return Non-negative double value. 0.0 value means "No rank".
 */
@property(nonatomic, readonly) CSContactDoubleField *rank;

/**
 * The list of custom1 values.
 * @return list of custom1 values.
 */
@property(nonatomic, readonly) CSContactStringFieldList *custom1;

/**
 * The list of custom2 values.
 * @return list of custom2 values.
 */
@property(nonatomic, readonly) CSContactStringFieldList *custom2;

/**
 * The list of custom3 values.
 * @return list of custom3 values.
 */
@property(nonatomic, readonly) CSContactStringFieldList *custom3;

/**
 * The location.
 * @return Contact string field containing the location.
 */
@property (nonatomic, readonly) CSContactStringField *location;

/**
 * The list of phone numbers.
 * @return Contact multi value field containing list of phone numbers.
 */
@property (nonatomic, readonly) CSContactPhoneFieldList *phoneNumbers;

/**
 * The list of email addresses.
 * @return Contact multi value field containing list of email addresses.
 */
@property (nonatomic, readonly) CSContactEmailFieldList *emailAddresses;

/**
 * Contact's list of instant messaging addresses.
 * @return Contact multi value field containing list of instant messaging addresses..
 */
@property (nonatomic, readonly) CSContactIMAddressFieldList *IMAddresses;

/**
 * The favorite flag.
 * @return Contact bool field containing the favorite flag.
 */
@property (nonatomic, readonly) CSContactBoolField *favorite;

/**
 * The buddy flag. Used for presence feature purpose.
 * @return Contact bool field containing the buddy flag.
 */
@property (nonatomic, readonly, getter=isBuddy) CSContactBoolField *isBuddy;

/**
 * The VIP flag.
 * @return Contact bool field containing the VIP flag.
 */
@property (nonatomic, readonly, getter=isVIP) CSContactBoolField *isVIP;

/*
 * Returns YES if contact is video capable.
 * @return YES if Contact is video capable.
 */
@property (nonatomic, readonly) CSContactBoolField *videoCapable;

/*
 * Returns YES if extended contact details are available.
 * @return YES if extended contact details are available.
 */
@property (nonatomic, readonly) BOOL isExtendedContactDetailsAvailable;

/*
 * Returns YES if addition of email address will not make contact invalid.
 * @return YES if addition of email address will not make contact invalid.
 */
@property (nonatomic, readonly) BOOL canAddEmailAddress;

/*
 * Returns YES if addition of IM address will not make contact invalid.
 * @return YES if addition of IM address will not make contact invalid.
 */
@property (nonatomic, readonly) BOOL canAddIMAddress;

/*
 * Returns YES if addition of phone number of a specified type will not make contact invalid.
 * @param contactPhoneNumberType type of phone number.
 * @return YES if addition of phone number of a given {@link ContactPhoneNumberType} is allowed.
 */
- (BOOL)canAddPhoneNumberOfType:(CSContactPhoneNumberType)type;

/**
 * The list extra fields used for local contacts.
 * Returns empty NSDictionary if underlying object is {@link CSEditableContact}.
 */
@property (nonatomic, readonly) NSDictionary *extraFields;

@end
