/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSEditableContact.h"
#import "CSCapability.h"
#import "CSDataRetrievalWatcher.h"
#import "CSContactField.h"
#import "CSContactGroup.h"
#import "CSContactLimits.h"
#import "CSTerminal.h"

/**
 *	Options for directory search scope
 */
typedef NS_ENUM(NSUInteger, CSContactSearchScope) {
	CSContactSearchScopeName,
	CSContactSearchScopeHandle,
	CSContactSearchScopeAll
};

/**
 *	Options for contact search location
 */
typedef NS_ENUM(NSUInteger, CSContactSearchLocation) {
	CSContactSearchLocalCache,
	CSContactSearchNetwork,
	CSContactSearchAll
};

/**
 *  Type of scope used for resolveContacts: method.
 */
typedef NS_ENUM(NSUInteger, CSContactResolveContactsScope) {
	CSContactResolveContactsScopeNumber,
	CSContactResolveContactsScopeHandle
};

/**
 * Contains all results of cached contacts matching.
 */
@interface CSMatchedContactsWithMatchLevel : NSObject
/**
 * Contains the list of matched contacts.
 * If the addresses being compared are dial-strings, feature access codes, or phone numbers
 * then this is an exact match after any alphanumeric characters are converted to digits and any visual separators are removed
 * If the addresses being compared are URI's then this an exact match as defined by RFC3261 section 19.1.4.
 */
@property (nonatomic, strong) NSArray *exactType1Contacts;

/**
 * Contains the list of matched contacts.
 * At least one of the addresses was a URI.
 * The phone number(s) extracted from the URI match in a normalized format.
 */
@property (nonatomic, strong) NSArray *exactType2Contacts;

/**
 * Contains the list of matched contacts.
 * The phone number and/or phone numbers extracted from a URI match the rightmost 10 digits
 */
@property (nonatomic, strong) NSArray *partialType1Contacts;

/**
 * All matched contacts.
 */
@property (nonatomic, strong) NSArray *allContacts;

@property (nonatomic, assign) bool isEmpty;
@end

/**
 * Contains search query string with corresponding data retrieval watcher object.
 */
@interface CSContactSearchQueryWatcherPair : NSObject

/**
 * Search query string.
 */
@property (nonatomic, strong) NSString *queryString;

/**
 * Data retrieval watcher object created for the query above.
 */
@property (nonatomic, strong) CSDataRetrievalWatcher *dataRetrievalWatcher;
@end

/**
 * Request object for search terminals.
 */
@interface CSSearchTerminalsRequest : NSObject

/**
 * The search string, terminal name.
 */
@property (nonatomic, readonly) NSString *searchString;

/**
 * The maximum number of results to return.
 */
@property (nonatomic, readonly) unsigned int maxNumberOfResults;

/**
 * The number of results to return in each update from the server.
 */
@property (nonatomic, readonly) unsigned int maxChunkSize;

/**
 * Initialize search terminals request.
 *
 * @param searchString The search string, terminal name.
 * @param maxNumberOfResults The maximum number of results to return.
 * @param maxChunkSize The number of results to return in each update from the server.
 */
- (instancetype)initWithSearchString:(NSString *)searchString
				  maxNumberOfResults:(unsigned int)maxNumberOfResults
						maxChunkSize:(unsigned int)maxChunkSize;

@end

/**
 * Request object for extended contact search.
 */
@interface CSContactSearchRequest : NSObject

/**
 * The search string, name.
 */
@property (nonatomic, readonly) NSString *nameSearchString;

/**
 * The search string, location.
 */
@property (nonatomic, readonly) NSString *locationSearchString;

/**
 * The search string, department.
 */
@property (nonatomic, readonly) NSString *departmentSearchString;

/**
 * The maximum number of results to return.
 */
@property (nonatomic, readonly) unsigned int maxNumberOfResults;

/**
 * The number of results to return in each update from the server.
 */
@property (nonatomic, readonly) unsigned int maxChunkSize;

/**
 * Initialize extended contact search request.
 * At least one search string should be filled in.
 * It is permissible to pass null or empty string into search strings.
 * Validation on parameters will be performed.
 * @param nameSearchString The search string, name.
 *                         It could contain words split by space
 *                         i.e. first name, last name, display name,
 *                         up to 4 words will be searched.
 * @param locationSearchString The search string, location.
 * @param departmentSearchString The search string, department.
 * @param maxNumberOfResults The maximum number of results to return.
 * @param maxChunkSize The number of results to return in each update from the server.
 */
- (instancetype)initWithNameSearchString:(NSString *)nameSearchString
                    locationSearchString:(NSString *)locationSearchString
                  departmentSearchString:(NSString *)departmentSearchString
                  maxNumberOfResults:(NSUInteger)maxNumberOfResults
                        maxChunkSize:(NSUInteger)maxChunkSize;

/**
 * Initialize extended contact search request with default number of results.
 * The maximum number of results to return is 50.
 * The number of results to return in each update from the server is 10.
 * At least one search string should be filled in.
 * It is permissible to pass null or empty string into search strings.
 * Validation on parameters will be performed.
 * @param nameSearchString The search string, name.
 *                         It could contain words split by space
 *                         i.e. first name, last name, display name,
 *                         up to 4 words will be searched.
 * @param locationSearchString The search string, location.
 * @param departmentSearchString The search string, department.
 */
- (instancetype)initWithNameSearchString:(NSString *)nameSearchString
                    locationSearchString:(NSString *)locationSearchString
                  departmentSearchString:(NSString *)departmentSearchString;

@end

/**
 * Request object for resolve contact searches.
 */
@interface CSContactResolveContactsRequest : NSObject

/**
 * An array of CSContactSearchQueryWatcherPair objects
 */
@property (nonatomic, strong) NSArray *searches;

/**
 * Scope for resolving contacts - search by number or handle.
 */
@property (nonatomic, assign) CSContactResolveContactsScope scopeType;

/**
 * Contact search type (local contacts and/or enterprise contacts).
 */
@property (nonatomic, assign) CSContactSearchLocation searchLocation;


/**
 * Designated initializer of CSContactResolveContactsRequest class.
 *
 * Object can also be initialized with default init method, but in this case all properties must have been set manually 
 * before passing this object to resolveContact: method.
 *
 * @param searches An array of CSContactSearchQueryWatcherPair objects
 * @param scopeType Scope for resolving contacts
 * @param searchLocation Contact search location
 */
- (instancetype)initWithSearches:(NSArray *)searches scopeType:(CSContactResolveContactsScope)scopeType searchLocation:(CSContactSearchLocation)searchLocation;

@end

/**
 * Call back for contact creation
 *
 * @param contactCreated New contact object created from the create contact request, nil if the operation is not successful
 * @param error nil if the operation was successful. If an error occurred it
 *        contains an object describing the error.
 */
typedef void(^contactCreationCallback)(CSContact *contactCreated, NSError *error) DEPRECATED_ATTRIBUTE;
@protocol CSContactServiceDelegate;

/**
 * The CSContactService object is accessible from the CSUser object, and
 * providing access to functionality associated with contacts.
 *
 * <p>The ContactService object provides a set of APIs that allow application developers to manage
 * a user's contacts and perform searches for other users.
 * In general, the capabilities and the set of allowed operations are dependent on the state of
 * the contact related servers and services.</p>
 *
 * <p>The client application is notified about status updates reported by the contact services
 * through a delegate that the application adds to the CSContactService object.
 * These updates may be the result of local operations on the ContactService object as well as
 * remote changes initiated by either the service/server or other users.</p>
 *
 * In order to retrieve a list of contacts, call -[retrieveContactsForSource:watcher:] selector.
 * This should be done after -[contactServiceAvailable:] was called.
 */
@interface CSContactService : NSObject

/**
 * The delegate responsible for handling contact service related events such as updated, deleted, added, capabilties changed, return results.
 */
@property (nonatomic, weak) id<CSContactServiceDelegate> delegate;

/**
 * Returns YES if the Contact service is available.
 * @return YES if the Contact service is available.
 */
@property (nonatomic, readonly) BOOL serviceAvailable;

/**
 * @return The list of available and online {@link CSContactSourceType}
 * If there is more than one source, the {@link CSContactSourceTypeAll} source will be added into the online list.
 */
@property (nonatomic, readonly) NSArray *availableContactSourceTypes;

/**
 * Returns CSCapability object describing whether the Contact service supports deleting contacts.
 * @return {@link CSCapability} object describing whether the Contact service supports deleting contacts.
 */
@property (nonatomic, readonly) CSCapability *deleteContactCapability;

/**
 * Returns CSCapability object describing whether the Contact service supports adding contacts.
 * @return {@link CSCapability} object describing whether the Contact service supports adding contacts.
 */
@property (nonatomic, readonly) CSCapability *addContactCapability;

/**
 * Returns Capability object describing whether the Contact service supports searching contacts.
 * @return {@link CSCapability} object describing whether the Contact service supports searching contacts.
 */
@property (nonatomic, readonly) CSCapability *networkSearchContactCapability;

/**
 * Returns Capability object describing whether the Contact service supports searching terminals.
 * @return {@link CSCapability} object describing whether the Contact service supports searching terminals.
 */
@property (nonatomic, readonly) CSCapability *networkSearchTerminalCapability;

/**
 * Returns Capability object describing whether the Contact service supports contact search by name.
 * @return {@link CSCapability} object describing whether the Contact service supports contact search by name.
 */
@property (nonatomic, readonly) CSCapability *networkContactSearchByNameCapability;

/**
 * Returns Capability object describing whether the Contact service supports contact search by location.
 * @return {@link CSCapability} object describing whether the Contact service supports contact search by location.
 */
@property (nonatomic, readonly) CSCapability *networkContactSearchByLocationCapability;

/**
 * Returns Capability object describing whether the Contact service supports contact search by department.
 * @return {@link CSCapability} object describing whether the Contact service supports contact search by department.
 */
@property (nonatomic, readonly) CSCapability *networkContactSearchByDepartmentCapability;

/**
 * Returns CSCapability object describing whether the Contact service supports updating contacts.
 * @return {@link CSCapability} object describing whether the Contact service supports updating contacts.
 */
@property (nonatomic, readonly) CSCapability *updateContactCapability;

/**
 * Returns CSCapability object describing whether the Contact service supports favorite contacts.
 * @return {@link CSCapability} object describing whether the Contact service supports favorite contacts.
 */
@property (nonatomic, readonly) CSCapability *favoriteContactsCapability;

/**
 * Returns CSCapability object describing whether the Contact service supports {@link resolveContacts:}.
 * @return {@link CSCapability} object describing whether the Contact service supports {@link resolveContacts:}.
 * 
 * This capability only covers searches where the {@link CSContactResolveContactsRequest.searchLocation} property is set to ::CSContactSearchNetwork.
 *
 * For searches where the @c searchLocation property is set to ::CSContactSearchLocalCache, the {@link CSContactServiceDelegate::contactService:loadContactsCompleteForSource:doneLoadingAllSources:} callback where the doneLoadingAllSources flag is @c YES, indicates that the user's local contacts have been loaded and local searches should complete successfully.
 *
 * For searches where the @c searchLocation property is set to ::CSContactSearchAll, the ::CSContactSearchLocalCache search is executed first. In case no results are found ::CSContactSearchNetwork search is triggered.
 */
@property (nonatomic, readonly) CSCapability *resolveEnterpriseContactsCapability;

/**
 * Returns NSSet of supported by current provider phone number types packed as NSNumber.
 * @return The Set of supported {@link CSContactPhoneNumberType}.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * It is recommended to use the {@link contactLimits} property instead.
 */
@property (nonatomic, readonly) NSSet *supportedPhoneNumberTypes DEPRECATED_ATTRIBUTE;

/**
 * Provides supported limits for the current enterprise contact provider.
 */
@property (nonatomic, readonly) CSContactLimits *contactLimits;

/** Capability describing whether the Contact Service supports Contact Group creation or not.
 * @return {@link CSCapability} object describing whether the Contact service supports contact groups creation.
 */
@property (nonatomic, readonly) CSCapability *createContactGroupCapability;

/** Capability describing whether the Contact Service supports Contact Group removal or not.
 * @return {@link CSCapability} object describing whether the Contact service supports contact groups removal.
 */
@property (nonatomic, readonly) CSCapability *deleteContactGroupCapability;

/** Maximum length of contact group name.
* @return Maximum length of contact group name.
*/
@property (nonatomic, readonly) NSUInteger maxContactGroupNameLength;

/** Maximum number of Contact Groups allowed for usage.
* @return Maximum number of allowed Contact Groups.
*/
@property (nonatomic, readonly) NSUInteger maxNumberOfContactGroups;

/** Maximum number of Contacts allowed per Group.
* @return Maximum number of Contacts allowed per Group.
*/
@property (nonatomic, readonly) NSUInteger maxNumberOfContactsPerGroup;

/**
 * Returns YES if Contact service supports Contacts Groups functionality.
 * @return YES if Contact service supports Contacts Groups functionality.
 */
@property (nonatomic, readonly) BOOL contactGroupsSupported;

/**
 * Retrieves the contact list from the given source.
 *
 * @param contactSourceType The type of contacts to retrieve.
 * Specify CSContactSourceTypeAll to get contacts from all available sources.
 * @param watcher A {@link CSDataRetrievalWatcher} object, created by the application, to track the progress of the requested
 * contact retrieval. Prior to calling this method, the application should
 * have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher object to
 * receive notifications on the progress of the retrieval.
 *
 * The data items returned to the application via the watcher object will be of type {@link CSContact}.
 */
- (void)retrieveContactsForSource:(CSContactSourceType)contactSourceType watcher:(CSDataRetrievalWatcher *)watcher;

/**
 * Gets the contact information for the currently logged-in user.
 * <p>It is possible for no contact record to be found for the current user. In this case the application
 * should fall back to other methods for retrieving or displaying contact information for the current user.</p>
 *
 * @param completionHandler The completion handler for this operation. Operation
 *                          success or failure is reported through this handler.
 */
- (void)retrieveSelfContactWithCompletionHandler:(void (^)(CSContact *contact, NSError *error))completionHandler;

/**
 * Search for the contacts with given request parameters. There can be only one search in progress with a particular
 * string. If such a search already exists, a new one won't be started.
 *
 * @param watcher        A DataRetrievalWatcher object, created by the application, to track the progress of the requested
 *                       operation.  Prior to calling this method, the application should have
 *                       installed a {@link CSDataRetrievalWatcherDelegate} on the watcher object to
 *                       receive notifications on the progress of the retrieval.
 * @param searchString   The search string, can be first name, last name, phone number.
 * @param searchScope    Identifies which field or fields to search in. Specify appropriate {@link CSContactSearchScope}
 * @param searchLocation Determines which contacts will be searched.
 * @param maxResults     The maximum number of results to return.
 * @param maxChunkSize   The number of results to return in each update from the server.
 * The data items returned to the application via the watcher object will be of type {@link CSContact}.
 */
- (void)searchContactsWithSearchString:(NSString *)searchString
						   searchScope:(CSContactSearchScope)searchScope
						searchLocation:(CSContactSearchLocation)searchLocation
					maxNumberOfResults:(unsigned int)maxResults
						  maxChunkSize:(unsigned int)maxChunkSize
							   watcher:(CSDataRetrievalWatcher *)watcher;

/**
 * Search for the terminals with given request parameters. There can be only one search in progress with a particular
 * request. If such a search already exists, a new one won't be started.
 *
 * @param request        A {@link CSSearchTerminalsRequest} object containing search parameters.
 * @param watcher        A DataRetrievalWatcher object, created by the application, to track the progress of the requested
 *                       operation. Prior to calling this method, the application should have
 *                       installed a {@link CSDataRetrievalWatcherDelegate} on the watcher object to
 *                       receive notifications on the progress of the retrieval.
 * The data items returned to the application via the watcher object will be of type {@link CSTerminal}.
 */
- (void)searchTerminalsWithRequest:(CSSearchTerminalsRequest *)request
						   watcher:(CSDataRetrievalWatcher *)watcher;

/**
 * Extended search for the contacts with given request parameters.
 *
 * @param request        A {@link CSContactSearchRequest} object containing search parameters.
 * @param watcher        A DataRetrievalWatcher object, created by the application, to track the progress of the requested
 *                       operation. Prior to calling this method, the application should have
 *                       installed a {@link CSDataRetrievalWatcherDelegate} on the watcher object to
 *                       receive notifications on the progress of the retrieval.
 * The data items returned to the application via the watcher object will be of type {@link CSContact}.
 */
- (void)searchContactsWithRequest:(CSContactSearchRequest *)request
                           watcher:(CSDataRetrievalWatcher *)watcher;


#ifdef DATASET_SUPPORTED
/**
 * Get the contact list from the given source.
 *
 * @param contactSourceType The source type of contacts to retrieve.
 * @return the CSDataRetrieval object, the UI needs to add its self as the DataRetrievalDelegate for the get contacts update
 * @return Contact data retrieval object, nil if source type is invalid.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link retrieveContactsForSource:watcher:} method instead.
 */
- (CSDataRetrieval *)contactsForSource:(CSContactSourceType)contactSourceType DEPRECATED_ATTRIBUTE;

/**
 * Search for the contacts with given request parameters. There can be only one search in progress with a particular
 * string. If such a search already exists, a new one won't be started.
 *
 * @param searchString Search string can be first name, last name, phone number.
 * @param searchScope    Identifies which field or fields to search in. Specify appropriate {@link CSContactSearchScope}
 * @param searchLocation Determines which contacts will be searched.
 * @param maxResults     The maximum number of results to return.
 * @param maxChunkSize   The number of results to return in each update from the server.
 *
 * Search contact using a SearchCriterion (scope, address types, contact attributes, etc).
 * SearchCriteria is composed of AND'd or OR'd SearchCriteria objects.
 * A SearchCriteria is of the form: AttributeName, Predicate, Value, where
 * AttributeName could be: "phone", "im", "lastname", etc.
 * Predicate would be: contains, equal, less or equal, etc. Equals includes fuzzy matching per i18n requirements
 * value user entered text. For phone numbers special characters like space, -, (, ), etc are ignored on search.
 * This would allow for searches like: lastname: Doe, email
 * @return CSDataRetrieval object, the UI needs to add its self as the CSDataRetrievalListener for the search contacts update.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * Use the {@link searchContactsWithSearchString:searchScope:searchLocation:maxNumberOfResults:maxChunkSize:watcher:} method instead.
 */
- (CSDataRetrieval *)searchContactsWithSearchString:(NSString *)searchString
										searchScope:(CSContactSearchScope)searchScope
									 searchLocation:(CSContactSearchLocation)searchLocation
								 maxNumberOfResults:(unsigned int)maxResults
									   maxChunkSize:(unsigned int)maxChunkSize DEPRECATED_ATTRIBUTE;
#endif

/**
 * Search for the contacts in application cache with given search string.
 * Contact cache is built from all retrieved items regardless of whether the
 * #retrieveContactsForSource:watcher: selector was called.
 *
 * @param searchString Search string can be first first name, last name, display name, alias, phone numbers, email address,
 *                     IM handle, city, department depending on selected scope.
 * @param searchScope Identifies which field or fields to search in. Specify appropriate {@link CSContactSearchScope}
 * @return CSMatchedContactsWithMatchLevel structure which contains matches with match levels.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 * It is recommended to use the ::CSContactService::resolveContacts: method instead.
 */
- (CSMatchedContactsWithMatchLevel *)searchCachedContactsWithSearchString:(NSString *)searchString
															searchScope:(CSContactSearchScope)searchScope DEPRECATED_ATTRIBUTE;
/**
 * Get matching contact (from cache) to the one from search results. Returns nil if contact is not found.
 * @param searchContact the contact received from search.
 * @return matching contact (from cache) to the one from search results or nil if contact is not found
 */
- (CSContact *)getMatchingContactForDirectoryContact:(CSContact *)searchContact;

/**
 * Change the search contacts request with a given new query string. All other parameters are immutable.
 *
 * @param searchString Search string can be first first name, last name, display name, alias, phone numbers, email address,
 *                     IM handle, city, department depending on selected scope.
 * @param watcher The existing data retrieval watcher that was created by the previous
 *                #searchContactsWithSearchString:searchScope:searchLocation:maxNumberOfResults:maxChunkSize:watcher: selector call.
 * @deprecated THIS SELECTOR WILL BE REMOVED IN RELEASE VERSION 3.3.
 */
- (void)changeSearchRequestWithSearchString:(NSString *)searchString forWatcher:(CSDataRetrievalWatcher *)watcher DEPRECATED_ATTRIBUTE;

#ifdef DATASET_SUPPORTED
/**
 * Change the search contacts request with a given new query string. All other parameters are immutable.
 *
 * @param searchString Search string can be first first name, last name, display name, alias, phone numbers, email address,
 *                     IM handle, city, department depending on selected scope.
 * @param dataRetrieval The object that used to retrive the contacts from the search request
 * @deprecated Use the {@link changeSearchRequestWithSearchString:forWatcher:} method instead.
 * @see -[networkSearchContactCapability:]
 */
- (void)changeSearchRequestWithSearchString:(NSString *)searchString forDataRetrieval:(CSDataRetrieval *)dataRetrieval DEPRECATED_ATTRIBUTE;
#endif

/**
 * Adds a new contact.
 *
 * @param contact The editable contact used to create the new contact.  This editable contact
 *                can be created using one of the following methods:
 * <ul>
 *  <li> by calling createEditableContact and then filling in the fields appropriately.</li>
 *  <li> by calling createEditableContactFromContact: to populate the editable contact from a directory search result.</li>
 * </ul>
 * @param completionHandler The completion handler for this operation.
 * @see -[addContactCapability]
 * @see -[updateContact:completionHandler:]
 * @see -[deleteContact:completionHandler:]
 */
- (void)addContact:(CSEditableContact *)contact completionHandler:(void (^)(CSContact *contact, BOOL contactWasMerged, NSError *error))completionHandler;

/**
 * Update an existing contact.
 *
 * <p>Note that there can be only one operation in progress for each CSEditableContact at the same time. Before the operation will return a result,
 * all subsequent attempts to update or add same contact will result in instant failure and according error code.</p>
 *
 * @param contact The editable contact object used to update this record on the
 *                enterprise source. This object must be created from a regular immutable contact by calling
 *                #createEditableContactFromContact:
 * @param completionHandler The completion handler for this operation.
 * @see -[updateContactCapability]
 * @see -[deleteContact:completionHandler]
 */
- (void)updateContact:(CSEditableContact *)contact completionHandler:(void (^)(CSContact *contact, NSError *error))completionHandler;

/**
 * Delete an existing contact.
 *
 * <p>Note that there can be only one operation in progress for each CSEditableContact at the same time. Before the operation will return a result,
 * all subsequent attempts to update or add same contact will result in instant failure and according error code.</p>
 *
 * @param contact The contact to be deleted.
 * @param completionHandler The completion handler for this operation.
 * @see -[deleteContactCapability]
 */
- (void)deleteContact:(CSContact*)contact completionHandler:(void (^)(NSError *error))completionHandler;

/**
 * Creates a new editable contact object from a given existing contact.
 *
 * This function can be used to create a new local contact from the results of a directory search performed by the
 * #searchContactsWithSearchString:searchScope:searchLocation:maxNumberOfResults:maxChunkSize:watcher: selector.
 * After creating an CSEditableContact from one of the search results, call the #addContact:completionHandler: selector to create and save the new contact.
 * Creating an enterprise contact from a local contact can be done using the same approach.
 *
 * This method must be used to update an existing contact as well. After the new {@link CSEditableContact} is
 * created, and the desired contact fields have been updated, use the
 * #updateContact:completionHandler: method to send a request.
 *
 * @param contact The contact whose current values will be used to populate the new {@link CSEditableContact}.
 * @return An {@link CSEditableContact} that has all the editable properties set based on the specified input contact.
 * Note that fields not supported by the enterprise source will not be used.
 *
 * @see -[createEditableContact]
 * @see -[addContact:completionHandler:]
 * @see -[updateContact:completionHandler:]
 */
- (CSEditableContact *)createEditableContactFromContact:(CSContact *)contact;

/**
 * Creates a new {@link CSEditableContact} object with default values.
 *
 * This method must be used to create a new {@link CSEditableContact} object before calling the #addContact:completionHandler: selector.
 *
 * @return {@link CSEditableContact} that has all the editable properties set to default values (source and capability).
 *
 * @see #createEditableContactFromContact:
 * @see #addContact:completionHandler:
 */
- (CSEditableContact *)createEditableContact;

/**
 * Search for the contacts with given request parameters. There can be only one search in progress with a particular string.
 * If such a search already exists, a new one won't be started.
 *
 * During the search contentsDidChange and didFailWithError callbacks may be triggered multiple times if there are multiple search locations.
 * The search is complete when the dataRetrievalWatcherDidComplete callback is triggered on the watcher.
 *
 * @param request A ::CSContactResolveContactsRequest object, which encapsulates the resolve contact search request. Contains search strings,
 *        searching scope, and source.
 *
 * @see #resolveEnterpriseContactsCapability
 */
- (void)resolveContacts:(CSContactResolveContactsRequest *)request;

/**
 * Creates a Contact Group with specified group name and group members.
 * Group members can be ommited. In this case Contact Service creates Contact Group with empty list of contacts.
 *
 * @param name Unique name of the group. Group name length is limited by the server. There are some characters not allowed to be present in group name (\&lt; \&gt; , \").
 * @param members Set of contacts to add into a group during creation.
 * @param completionHandler The completion handler for this operation.
 */
- (void)createContactGroupWithName:(NSString *)name members:(NSSet<CSContact *> *)members completionHandler:(void (^)(CSContactGroup *contactGroup, NSError *error))completionHandler;

/**
 * Deletes Contact Group.
 *
 * @param group Group of contacts for removal
 * @param completionHandler The completion handler for this operation.
 */
- (void)deleteContactGroup:(CSContactGroup *)group completionHandler:(void (^)(NSError *error))completionHandler;

/**
* Retrieves the contact groups
*
* @param watcher A {@link CSDataRetrievalWatcher} object, created by the application, to track the progress of the requested
* contact groups retrieval. Prior to calling this method, the application should
* have installed a {@link CSDataRetrievalWatcherDelegate} on the watcher object to
* receive notifications on the progress of the retrieval.
*
* The data items returned to the application via the watcher object will be of type {@link CSContactGroup}.
*/
-(void)retrieveContactGroupsWithWatcher:(CSDataRetrievalWatcher *)watcher;
@end


/**
 * Describes methods that are implemented by the delegate of a @c CSContactService.
 */
@protocol CSContactServiceDelegate <NSObject>

/**
 * Called when the contact service becomes available for use.
 *
 * @param contactService The contact service associated with the callback.
 */
- (void)contactServiceAvailable:(CSContactService *)contactService;

/**
 * Called when the contact service becomes unavailable for use.
 *
 * @param contactService The contact service associated with the callback.
 */
- (void)contactServiceUnavailable:(CSContactService *)contactService;

/**
 * Called when an underlying contact provider fails.
 *
 * @param contactService The contact service associated with the callback.
 * @param sourceType The contact source type that the failed provider is responsible for.
 * @param error The error code for the failure.
 */
- (void)contactService:(CSContactService *)contactService providerForSourceType:(CSContactSourceType)sourceType didFailWithError:(NSError *)error;

/**
 * Called when contact loading from an underlying provider completed.
 *
 * @param contactService The contact service associated with the callback.
 * @param source The source that is done loading contacts
 * @param done YES when all sources have completed their attempt to load contacts.
 */
- (void)contactService:(CSContactService *)contactService loadContactsCompleteForSource:(CSContactSourceType)source doneLoadingAllSources:(BOOL)done;

/**
 * Called when contact loading from an underlying provider fails.
 *
 * @param contactService The contact service associated with the callback.
 * @param error the reason for contacts not being loaded
 * @param source The source that is done loading contacts
 * @param done YES when all sources have completed their attempt to load contacts, UI can ignore the source type when this set to YES,
 * NO if some sources are still loading.
 */
- (void)contactService:(CSContactService *)contactService loadContactsFailedWithError:(NSError *)error forSource:(CSContactSourceType)source doneLoadingAllSources:(BOOL)done;

/**
 * Called when contact groups loading from an underlying provider fails.
 *
 * @param contactService The contact service associated with the callback.
 * @param error The reason for contact groups not being loaded
 * @param source The source that could not loading contact groups
 */
- (void)contactService:(CSContactService *)contactService loadContactGroupsFailedWithError:(NSError *)error forSource:(CSContactSourceType)source;


/**
 * Called when the list of available contact providers changes.
 * For example, if ACS provider has stopped working, an event will be triggered.
 *
 * @param contactService The contact service associated with the callback.
 */
- (void)contactServiceDidReloadData:(CSContactService *)contactService;

/**
 * Called when any of the contact service's capabilities changes.
 *
 * @param contactService The contact service associated with the callback.
 */
- (void)contactServiceDidChangeCapabilities:(CSContactService *)contactService;

/**
 * Called when contact were added.
 *
 * @param contactService The contact service associated with the callback.
 * @param contacts vector of added contacts.
 */
- (void)contactService:(CSContactService *)contactService didAddContacts:(NSArray *)contacts;

/**
 * Called when contacts were deleted.
 *
 * @param contactService The contact service associated with the callback.
 * @param contacts vector of deleted contacts.
 */
- (void)contactService:(CSContactService *)contactService didDeleteContacts:(NSArray *)contacts;

/**
 * Called when contact groups were added.
 *
 * @param contactService The contact service associated with the callback.
 * @param contactGroups set of added contact groups.
 */
- (void)contactService:(CSContactService *)contactService didAddContactGroups:(NSSet<CSContactGroup *> *)contactGroups;

/**
 * Called when contact groups were deleted.
 *
 * @param contactService The contact service associated with the callback.
 * @param contactGroups set of deleted contact groups.
 */
- (void)contactService:(CSContactService *)contactService didDeleteContactGroups:(NSSet<CSContactGroup *> *)contactGroups;

@end
