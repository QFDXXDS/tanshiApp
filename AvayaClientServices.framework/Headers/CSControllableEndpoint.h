/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * The details of a controllable endpoint for shared control.
 *
 * The ControllableEndpoint class provides access to the details
 * of controllable endpoint which can be used for shared control.
 */
@interface CSControllableEndpoint : NSObject

/**
 * Numeric Id identifying the controlled endpoint.
 */
@property (nonatomic, readonly) int intId;

/**
 * URI of the controllable endpoint.
 */
@property (nonatomic, readonly) NSString *URI;

/**
 * Display name of the controllable endpoint.
 */
@property (nonatomic, readonly) NSString *displayName;

/**
 * Serial number of the controllable endpoint.
 */
@property (nonatomic, readonly) NSString *serialNumber;

/**
 * Firmware version of the controllable endpoint.
 */
@property (nonatomic, readonly) NSString *firmwareVersion;

/**
 * Model of the controllable endpoint.
 */
@property (nonatomic, readonly) NSString *model;

/**
 * Unique string Id of the controllable endpoint.
 */
@property (nonatomic, readonly) NSString *endpointId;

@end
