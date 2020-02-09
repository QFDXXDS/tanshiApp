/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@interface CSPhysicalAddress : NSObject
/**
 * street address
 */
@property (nonatomic, copy) NSString *streetAddress;
/**
 * city name
 */
@property (nonatomic, copy) NSString *city;
/**
 * state or province
 */
@property (nonatomic, copy) NSString *stateOrProvince;
/**
 * country name
 */
@property (nonatomic, copy) NSString *country;
/**
 * zip code or postal code
 */
@property (nonatomic, copy) NSString *zipOrPostalCode;
/**
 * formatted string representing complete address
 */
@property (nonatomic, copy) NSString *formattedAddress;

@end
