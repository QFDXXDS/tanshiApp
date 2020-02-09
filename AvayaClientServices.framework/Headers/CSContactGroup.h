/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCapability.h"
#import "CSContact.h"
#import "CSDefines.h"

@protocol CSContactGroupDelegate;

/**
 * Represents contact group object which exposes all possible contact group details.
 * It allows to add and remove contacts to/from group and update name of the group.
 *
 * Contact groups can be created by using ContactService method 
 * createContactGroupWithName:name members:members completionHandler:completionHandler
 * and deleted by method deleteContactGroup:(CSContactGroup *)group completionHandler:completionHandler.
 */
@interface CSContactGroup : NSObject

/**
 * This delegate responsible for handling updates for this contact group.
 */
@property (nonatomic, weak) id<CSContactGroupDelegate> delegate;

/**
 * Name of the group of contacts.
 * @return Name of the group of contacts.
 */
@property (nonatomic, readonly) NSString *name;

/**
 * Set of contacts associated with group.
 * @return Set of {@link CSContact} members of group
 */
@property (nonatomic, readonly) NSSet<CSContact *> *groupMembers;

/**
 * Capability indicating whether this contact group can be renamed.
 * @return {@link CSCapability} object describing whether the Contact Group supports renaming.
 */
@property (nonatomic, readonly) CSCapability *renameGroupCapability;

/**
 * Capability indicating whether this contact group can add new contacts.
 * @return {@link CSCapability} object describing whether the Contact Group supports adding new contacts.
 */
@property (nonatomic, readonly) CSCapability *addContactsCapability;

/**
 * Capability indicating whether this contact group can remove contacts.
 * @return {@link CSCapability} object describing whether the Contact Group supports removing contacts.
 */
@property (nonatomic, readonly) CSCapability *removeContactsCapability;

/**
 * Renames group.
 *
 * Renaming of the group results in raising 2 events on CSContactServiceDelegate - didDeleteContactGroups and didAddContactGroups.
 *
 * @param newName New name of the group of contacts. Group name length is limited by the server. There are some characters not allowed to be present in group name (\&lt; \&gt; , \").
 * @param completionHandler A block to be called when the operation is completed.
 *		  If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
-(void)renameGroup:(NSString *)newName completionHandler:(void (^)(NSError *error))completionHandler;

/**
 * Adds new contacts to a group.
 *
 * Operation fails if at least one contact can't be added to a group due to capability not allowed.
 * Entire collection remains unchanged in this case.
 * Providing contact as argument which already exists in group treated as Success operation.
 *
 * @param contacts Set of {@link CSContact} objects to be added to a group
 * @param completionHandler A block to be called when the operation is completed.
 *        If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
-(void)addContacts:(NSSet<CSContact *> *)contacts completionHandler:(void (^)(NSError *error))completionHandler;

/**
 * Removes contacts from a group
 *
 * Operation fails if at least one contact can't be removed from group due to capability not allowed.
 * Entire collection remains unchanged in this case.
 * Providing contact as argument which doesn't exist in group treated as Success operation.
 *
 * @param contacts array of {@link CSContact} objects to be removed from a group
 * @param completionHandler A block to be called when the operation is completed.
 *        If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
-(void)removeContacts:(NSSet<CSContact *> *)contacts completionHandler:(void (^)(NSError *error))completionHandler;

@end

/**
 * Describes methods that are implemented by the delegate of a @c CSContactGroup.
 */
@protocol CSContactGroupDelegate <NSObject>

/**
 * Occurs when new contacts were added to the group, either through local or remote actions.
 *
 * @param contactGroup The contact group that was updated.
 * @param contacts The contacts that were added.
 */
- (void)contactGroup:(CSContactGroup *)contactGroup didAddContacts:(NSSet<CSContact *> *)contacts;

/**
 * Occurs when contacts were removed from the group, either through local or remote actions.
 *
 * @param contactGroup The contact group that was updated.
 * @param contacts The contacts that were removed.
 */
- (void)contactGroup:(CSContactGroup *)contactGroup didRemoveContacts:(NSSet<CSContact *> *)contacts;

@end
