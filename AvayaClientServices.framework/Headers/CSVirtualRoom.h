/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Virtual room configured for user
 */
@interface CSVirtualRoom : NSObject

/**
 * Id of the virtual room.
 */
@property (nonatomic, readonly) NSString *roomId;

/**
 * Name of the virtual room.
 */
@property (nonatomic, readonly) NSString *roomName;

/**
 * Description of the virtual room.
 */
@property (nonatomic, readonly) NSString *roomDescription;

/**
 * A boolean value indicating whether this VR is public.
 */
@property (nonatomic, readonly, getter=isPublic) BOOL publicRoom;

/**
 * A boolean value indicating whether this is default VR for the user.
 */
@property (nonatomic, readonly, getter=isDefault) BOOL defaultRoom;

/**
 * Virtual room number.
 */
@property (nonatomic, readonly) NSString *roomNumber;

/**
 * Virtual room PIN.
 */
@property (nonatomic, readonly) NSString *roomAccessPIN;

/**
 * Virtual room moderator PIN.
 */
@property (nonatomic, readonly) NSString *roomModeratorPIN;

/**
 * A boolean value indicating whether the one time PIN is required.
 */
@property(nonatomic, readonly, getter = isOneTimePinRequired) BOOL oneTimePinRequired;

/**
 * A dictionary of extra properties the application may be interested in.
 * Complex property values are JSON encoded strings.
 */
@property(nonatomic, readonly) NSDictionary *extraProperties;

- (instancetype)initWithRoomId:(NSString *)roomId
				 roomName:(NSString *)roomName
				 roomDescription:(NSString *)roomDescription
				 publicRoom:(BOOL)publicRoom
				 defaultRoom:(BOOL)defaultRoom
				 roomNumber:(NSString *)roomNumber
				 roomAccessPIN:(NSString *)roomAccessPIN
				 roomModeratorPIN:(NSString *)roomModeratorPIN
				 oneTimePinRequired : (BOOL)oneTimePinRequired
				 extraProperties: (NSDictionary *)extraProperties;

@end
