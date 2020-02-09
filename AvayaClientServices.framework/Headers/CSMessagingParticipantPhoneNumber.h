/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSMessagingEnums.h"

/**
 * Represents a participant's phone number.
 */
@interface CSMessagingParticipantPhoneNumber : NSObject

/**
 * Indicates whether the number is verified.
 * @return true if the number is verified.
 */
@property (nonatomic, readonly, getter=isVerified) BOOL verified;

/**
 * Indicated whether the number is primary.
 * @return true if the number is primary.
 */
@property (nonatomic, readonly, getter=isPrimary) BOOL primary;

/**
 * Returns E.164 formatted phone number.
 * @return E.164 formatted phone number.
 */
@property (nonatomic, readonly) NSString* canonicalForm;

/**
 * Returns phone number type.
 * @return phone number type.
 */
@property (nonatomic, readonly) CSMessagingParticipantPhoneNumberType type;

/**
 * When {@link #type} has value {@link CSMessagingParticipantPhoneNumberTypeCustom}
 * this value represents the name of the custom number type provided by a user.
 *
 * @see {@link #type}
 * @return phone number custom type.
 */
@property (nonatomic, readonly) NSString* customType;

/**
 * Returns the phone number.
 * @return the phone number.
 */
@property (nonatomic, readonly) NSString* value;

@end
