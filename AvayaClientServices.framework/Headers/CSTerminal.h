/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSContactStringField.h"

/**
 * Represents an immutable terminal contact object.
 *
 * Terminals can be retrieved by using {@link CSContactService} methods
 * ::CSContactService::searchTerminalsWithRequest:watcher:.
 * This methos takes a DataRetrievalWatcher argument which allows the application to be notified about the status of the operation and changes to the list of terminals retrieved.
 *
 * This object cannot be used to edit the terminal contact record.
 */
@interface CSTerminal : NSObject

/**
 * The name of the terminal.
 */
@property (nonatomic, readonly) NSString *name;

/**
 * The dialable terminal number. This number is used to add the terminal to a conference.
 */
@property (nonatomic, readonly) NSString *phoneNumber;

@end
