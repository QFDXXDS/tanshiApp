/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCallPickupFeatureRinger.h"


/**
 * The Enhance or Call Pickup alert details.
 */
@interface CSCallPickupAlertParameters : NSObject

/**
 * Constructs a CSCallPickupAlertParameters object from the specified parameters.
 *
 * @param callingName            The caller name. 
 * @param callingNumber          The caller number.
 * @param calledName             The callee name.
 * @param calledNumber           The callee number.
 * @param ringPattern            The ring pattern.
 * @param ringType               The ring type.
 * @param pickupRingerOn         YES for the pickup ringer ON otherwise NO.
 * @param enhancedPickupAlertOn  YES for the enhance pickup alert ON otherwise NO.
 */

- (instancetype)initWithCallingName:(NSString *)callingName
                         callingNumber:(NSString*)callingNumber
                         calledName:(NSString*)calledName
                         calledNumber:(NSString*)calledNumber
                         ringPattern:(CSRingPattern)ringPattern
                         ringType:(CSRingType)ringType
                         pickupRingerOn:(BOOL)pickupRingerOn
                         enhancedPickupAlertOn:(BOOL)enhancedPickupAlertOn;


/**
 * The person's name who has initiated the call.
 */

@property (nonatomic, readonly) NSString *callingName;

/**
 * The person's number who has initiated the call.
 */

@property (nonatomic, readonly) NSString *callingNumber;

/**
 * The person's name to whom the call is requested.
 */

@property (nonatomic, readonly) NSString *calledName;

/**
 * The person's number to whom the call is requested.
 */

@property (nonatomic, readonly) NSString *calledNumber;

/**
 * The ring pattern if configured
 */

@property (nonatomic, readonly) CSRingPattern ringPattern;

/**
 * The ring type based on which the application shall play different audio files.
 */

@property (nonatomic, readonly) CSRingType ringType;

/**
 * Returns true if the pickup ringer status is ON else returns false.
 */

@property (nonatomic, readonly) BOOL pickupRingerOn;

/**
 * Returns true if the enhance pickup status is ON else returns false.
 */

@property (nonatomic, readonly) BOOL enhancedPickupAlertOn;

@end
