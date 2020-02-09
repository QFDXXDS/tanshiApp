#import <Foundation/Foundation.h>
#import "CSConferenceRoomSystemStatus.h"

/**
 * Class representing the conference room system information received from the conference server.
 * It is used to report the list of room system(s) that were discovered through the mobile
 * link discovery mechanism.
 */
@interface CSConferenceRoomSystemInformation : NSObject

/** Room system network address information. */
@property (nonatomic, readonly) NSString *address;

/** Flag indicating whether room system requires pass code for the mobile link connection. */
@property (nonatomic, readonly) BOOL passcodeRequired;

/** Room system’s name. */
@property (nonatomic, readonly) NSString *name;

/** Room system’s status. */
@property (nonatomic, readonly) CSConferenceRoomSystemStatus status;

@end
