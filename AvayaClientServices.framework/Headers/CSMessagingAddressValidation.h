/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Interface for address validation response.
 *
 * This class is used to return the results of address validation.
 */
@interface CSMessagingAddressValidation : NSObject

/**
 * Address that was sent to {@link CSMessagingService::validateAddresses:watcher: -[CSMessagingService validateAddresses:watcher:]} method.
 *
 * @return The address that was sent to validate.
 */
@property (nonatomic, readonly) NSString *query;

/**
 * @return An array of NSString of valid addresses returned by the server for address query.
 */
@property (nonatomic, readonly) NSArray *validAddresses;

@end
