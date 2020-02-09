/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSFeatureType.h"
#import "CSFeatureStatusParameters.h"

@class CSCallPickupAlertParameters;

/**
 * The Call Pickup Alert feature status
 */
@interface CSCallPickupAlertStatus : NSObject

/**
 * The feature type associated with this status.
 */
@property (nonatomic, readonly) CSFeatureType featureType;

/**
 * The feature's status.
 */
@property (nonatomic, readonly) CSFeatureStatus status;

/**
 * The Call Pickup group name.
 *
 * Populated with the name of the group.
 */
@property (nonatomic, readonly) NSString *pickupGroupName;

/**
 * The call pickup alert status data.
 */
@property (nonatomic, readonly) CSCallPickupAlertParameters *callPickupAlertArgs;

/**
 * Constructs CSCallPickupAlertStatus object from the specified parameters.
 * @param featureType The feature type associated with the group, directed or extended call pickup alerts.
 * @param status The status of the feature (on or off).
 * @param pickupGroupName The pickup group for which the alert is received.
 * @param callPickupAlertArgs The Enhance or Call Pickup alert details.
 */
- (instancetype)initWithFeatureType:(CSFeatureType)featureType status:(CSFeatureStatus)status pickupGroupName:(NSString *)pickupGroupName callPickupAlertArgs:(CSCallPickupAlertParameters *)callPickupAlertArgs;


@end

