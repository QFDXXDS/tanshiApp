/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@interface CSContactLimits : NSObject

/**
 *
 */
@property (nonatomic, readonly) NSSet * supportedPhoneNumberTypes;

/**
 * Returns supported phone number types.
 */
@property (nonatomic, readonly) NSSet * supportedEmailAddressTypes;

/**
 * Returns supported email address types.
 */
@property (nonatomic, readonly) NSSet * supportedIMAddressTypes;

/**
 * Returns supported search scope types.
 */
@property (nonatomic, readonly) NSSet * supportedSearchScopeTypes;

/**
 * Returns supported IM address types.
 */
@property (nonatomic, readonly) NSUInteger maxPhoneNumbersPerContact;

/**
 * Returns maximum email addresses per contact.
 */
@property (nonatomic, readonly) NSUInteger maxEmailAddressesPerContact;

/**
 * Returns maximum IM addresses per contact.
 */
@property (nonatomic, readonly) NSUInteger maxIMAddressesPerContact;

/**
 * Returns maximum search records per request.
 */
@property (nonatomic, readonly) NSUInteger maxSearchRecordsPerRequest;

@end
