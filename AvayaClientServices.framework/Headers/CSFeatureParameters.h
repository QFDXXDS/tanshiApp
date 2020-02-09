/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSFeatureType.h"

/**
 * This is a union of the parameters of the FNU features.
 * The caller should know which parameters to populate for a specific feature.
 */
@interface CSFeatureParameters : NSObject

/**
 * The feature type associated with the feature.
 */
@property (nonatomic) CSFeatureType featureType;

/**
 * The owner extension associated with this feature.
 *
 * Populate if targeted feature's owner is different from the local user's extension.
 */
@property (nonatomic, copy) NSString *ownerExtension;

/**
 * The Hunt Group Number associated with the hunt-group-busy-position feature
 *
 * Populate if the feature is Hunt Group Busy Position feature.
 */
@property (nonatomic) NSInteger huntGroupNumber;

/**
 * Constructs an CSFeatureStatusParameters object from the specified parameters.
 *
 * @param featureType					The feature type associated with the feature.
 * @param ownerExtension				The owner extension associated with this feature.
 * @param huntGroupNumber				The Hunt Group Number associated with the hunt-group-busy-position feature
 */
- (instancetype)initWithFeatureType:(CSFeatureType)featureType
					 ownerExtension:(NSString*)ownerExtension
					huntGroupNumber:(NSInteger)huntGroupNumber;
@end
