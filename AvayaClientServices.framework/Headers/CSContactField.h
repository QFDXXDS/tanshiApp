/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCapability.h"

/**
 * Each field in a contact has a structure associated with it which describes where it came from
 * and if it can be modified. This is the base class for all the fields stored in the CSContact object.
 */
typedef NS_ENUM(NSUInteger, CSProviderSourceType){
	CSProviderSourceTypeLDAP,
	CSProviderSourceTypeACS,
	CSProviderSourceTypePPM,
	CSProviderSourceTypeLocal,
	CSProviderSourceTypeZang,
	CSProviderSourceTypeIPO,
	CSProviderSourceTypeOther
};

/**
 * A base class for all contact-related field classes which defines the common attributes for all field types.
 */
@interface CSContactField : NSObject

/**
 * Write capability for particular field.
 * @return capability information.
 */
@property (nonatomic, readonly) CSCapability *writeCapability;

/**
 * Provider source type for particular field.
 * @return Contact provider source type.
 */
@property (nonatomic, assign) CSProviderSourceType source;

@end

