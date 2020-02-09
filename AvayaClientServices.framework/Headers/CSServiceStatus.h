/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * The service disabled reason.
 */
typedef NS_ENUM(NSUInteger, CSServiceDisabledReason) {
                CSServiceDisabledReasonNone,
                CSServiceDisabledReasonInvalidState,
                CSServiceDisabledReasonNotConfigured,
                CSServiceDisabledReasonNotSupported,
                CSServiceDisabledReasonNotLicensed,
                CSServiceDisabledReasonInternalError
};


/*
* A class representing whether a certain service is enabled based
* on the current user configuration.
*/

@interface CSServiceStatus : NSObject

/**
 * Whether the service is enabled
 */
@property (nonatomic, readonly) BOOL enabled;

/**
 * Service disabled reason
 */
@property (nonatomic, readonly) CSServiceDisabledReason disabledReason;

@end
