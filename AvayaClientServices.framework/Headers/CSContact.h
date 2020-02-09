/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCapability.h"
#import "CSContactBoolField.h"
#import "CSContactDoubleField.h"
#import "CSContactEmailAddressField.h"
#import "CSContactField.h"
#import "CSContactIMAddressField.h"
#import "CSContactPhoneField.h"
#import "CSContactStringField.h"
#import "CSPhysicalAddress.h"
#import "CSPresence.h"
#import "CSContactEmailFieldList.h"
#import "CSContactPhoneFieldList.h"
#import "CSContactIMAddressFieldList.h"
#import "CSContactStringFieldList.h"
#import "CSContactProtocol.h"
#import "CSDefines.h"

/**
 * Unique ID for contacts from ContactSourceType.Local source.
 */
CS_EXTERN NSString * const kCSContactExtraFieldNativeId;

/**
 * The contact source type used at the binding to filter the get contacts
 */
typedef NS_ENUM(NSUInteger, CSContactSourceType) {
	CSContactSourceTypeLocal,
	CSContactSourceTypeEnterprise,
	CSContactSourceTypeAll,
};

typedef NS_ENUM(NSUInteger, CSMatchedContactLevel){
	/**
	 * If the addresses being compared are dialstrings, feature access codes, or phone numbers
	 * then this is an exact match after any alphanumeric characters are converted to digits and any visual separators are removed
	 * If the addresses being compared are URI's then this an exact match as defined by RFC3261 section 19.1.4.
	 */
	CSMatchedContactExactType1,
	/**
	 * At least one of the addresses was a URI.
	 * The phone number(s) extracted from the URI match in a normalized format.
	 */
	CSMatchedContactExactType2,
	/** Reserved for future use */
	CSMatchedContactExactType3,
	/** Reserved for future use */
	CSMatchedContactExactType4,
	/** Reserved for future use */
	CSMatchedContactExactType5,
	/** The phone number and/or phone numbers extracted from a URI match the rightmost 10 digits */
	CSMatchedContactPartialType1,
	/** Reserved for future use */
	CSMatchedContactPartialType2,
	/** Reserved for future use */
	CSMatchedContactPartialType3,
	/** Reserved for future use */
	CSMatchedContactPartialType4,
	/** Reserved for future use */
	CSMatchedContactPartialType5,
	/** There is no matched contact */
	CSNoMatch,
};

/**
 * Enumeration that describes the types of the ACL-confirm policy handling.
 * <p>
 * When a request to start watching presence of some user is issued by the client
 * the presence server the client is connected to relies on Access Information Control policy,
 * also known as Access Control List (ACL), to decide whether the requesting user has permissions
 * to get the presence of the desired user. 
 * <p>
 * The ACL policy applies to a particular presentity and has the following three options:
 * <ul>
 *   <li>"ALLOW" means all requests are to be serviced and presence is provided to the requesting user.</li>
 *   <li>"BLOCK" means all requests are politely ignored by a presence server and presence is not provided.</li>
 *	 <li>"CONFIRM" means that a presence request is serviced only if the remote user (presentity) explicitly allows that via a pop-up dialog.</li>	
 * </ul>
 * <p>
 * The "CONFIRM" option implies that each presence watcher request results in a pop-up message displayed on a presentity side
 * which may introduce undesired distraction and bad experience for the remote user. 
 * <p>
 * The CSAccessControlBehavior setting can be used to avoid this behavior when the start presence request is issued.
 * <ul>
 *   <li>If set to CSAccessControlBehaviorNone, "CONFIRM" policy would be treated as "BLOCK" by the presence server.</li>
 *   <li>If set to CSAccessControlBehaviorPrompt, "CONFIRM" policy will result in requesting the remote user to explicitly allow watching their presence.</li>
 * </ul>
 */
typedef NS_ENUM(NSUInteger, CSAccessControlBehavior){
	/**
	 * "CONFIRM" policy would be treated as "BLOCK" by the presence server.
	 */
	CSAccessControlBehaviorNone,
	/**
	 * "CONFIRM" policy will result in requesting the remote user to explicitly allow watching their presence.
	 */
	CSAccessControlBehaviorPrompt
};


@protocol CSContactDelegate;


/**
 * Represents an immutable contact object which exposes all possible contact details.
 * The contact object can also be used to subscribe for presence updates.
 *
 * Contacts can be retrieved by using {@link CSContactService} methods
 * ::CSContactService::retrieveContactsForSource:watcher:
 * or ::CSContactService::searchContactsWithSearchString:searchScope:searchLocation:maxNumberOfResults:maxChunkSize:watcher:.
 * Both methods take a DataRetrievalWatcher argument which allows the application to be notified about the status of the operation and changes to the list of contacts retrieved.
 *
 * This object cannot be used to edit the contact record. In order to update a contact record the following steps are required:
 *
 * -# Call ::CSContactService::createEditableContactFromContact: to get an editable contact object.
 * -# Make updates to the fields of the {@link CSEditableContact} object that was returned.
 * -# Call ::CSContactService::updateContact:completionHandler: to save the changes.
 *
 * @see ::CSEditableContact
 */
@interface CSContact : NSObject<CSContact>

/**
 * This delegate responsible for handling updates for this contact.
 */
@property (nonatomic, weak) id<CSContactDelegate> delegate;

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
 * Retrieve contact's Picture.
 *
 * @param completionHandler A block to be called when the operation is completed.
 *        @li @c bytes the buffer containing picture data
 *		  @li @c length the number of bytes in hold from bytes
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)retrievePictureWithCompletionHandler:(void (^)(NSData *pictureData, NSError *error))completionHandler;

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
 * The presence state of this contact.
 *
 * Note that for the presence to start being updated, #startPresenceWithAccessControlBehavior:completionHandler: must be invoked.
 */
@property (nonatomic, readonly) CSPresence *presence;

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

/**
 * Returns list of contact sources
 * @return list of contact sources
 */
@property (nonatomic, readonly) NSArray *contactSources;

/**
 * @return Capability object describing whether the contact services can update this contact
 */
@property (nonatomic, readonly) CSCapability *updateCapability;

/**
 * @return Capability object describing whether the contact services can delete this contact
 */
@property (nonatomic, readonly) CSCapability *deleteCapability;

/**
 * @return Capability object describing whether this contact can be added to a group.
 */
@property (nonatomic, readonly) CSCapability *addToGroupCapability;

/**
 * The list extra fields used for local contacts.
 */
@property (nonatomic, readonly) NSDictionary* extraFields;

/**
 * Returns if this contact source type is set on contact
 */
- (BOOL)hasContactSourceType:(CSContactSourceType)contactSourceType;

/**
 * Returns if this contact has picture set on
 */
- (BOOL)hasPicture;

/**
 * Begin monitoring presence for this contact. Once the operation is completed, #presence will return the actual presence information for the contact.
 *
 * @param accessControlBehavior Type of the ACL-confirm policy handling.
 * @param completionHandler Completion handler that is invoked once the operation  completes.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)startPresenceWithAccessControlBehavior:(CSAccessControlBehavior)accessControlBehavior completionHandler:(void (^)(NSError *error))completionHandler;

/**
 * Stop monitoring presence for this contact.  Once the operation is completed, #presence will not be able to provide actual user's presence information.
 *
 * @param completionHandler Completion handler that is invoked once the operation  completes.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)stopPresenceWithCompletionHandler:(void (^)(NSError *error))completionHandler;

/**
 * Removes contact's picture from cache. This method helps to manage the application memory.
 * When the contact picture is not needed, it can be removed and downloaded again in the future.
 *
 * @see #retrievePictureWithCompletionHandler:
 */
- (void)removePictureFromCache;

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
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link canAddEmailAddress} method instead.
 */
@property (nonatomic, readonly) BOOL canAddEmailAddress DEPRECATED_ATTRIBUTE;

/*
 * Returns YES if addition of IM address will not make contact invalid.
 * @return YES if addition of IM address will not make contact invalid.
 */
@property (nonatomic, readonly) BOOL canAddIMAddress;

/*
 * Returns YES if addition of phone number of a specified type will not make contact invalid.
 * @param type type of phone number.
 * @return YES if addition of phone number of a given {@link ContactPhoneNumberType} is allowed.
 */
- (BOOL)canAddPhoneNumberOfType:(CSContactPhoneNumberType)type;

/*
 * Returns YES if addition of email address of a specified type will not make contact invalid.
 * @param type type of email address.
 * @return YES if addition of email address of a given {@link CSContactEmailAddressType} is allowed.
 */
- (BOOL)canAddEmailAddressOfType:(CSContactEmailAddressType)type;

@end

/**
 * Describes methods that are implemented by the delegate of a @c CSContact.
 */
@protocol CSContactDelegate <NSObject>

/**
 * Sent when the contact has been changed.
 *
 * @param contact The changed contact.
 */
- (void)contactUpdated:(CSContact *)contact;

/**
 * Sent when contact presence tracking has started.
 *
 * @param contact instance associated with presence subscription.
 */
- (void)contactDidStartPresence:(CSContact *)contact;

/**
 * Sent when contact presence tracking has stopped.
 *
 * @param contact instance associated with presence subscription.
 */
- (void)contactDidStopPresence:(CSContact *)contact;

/**
 * Sent when presence information of the contact is updated.
 *
 * @param contact Contact object associated with presence subscription.
 * @param presence Presence object carrying presence information for the contact.
 */
- (void)contact:(CSContact *)contact didUpdatePresence:(CSPresence *)presence;

@end
