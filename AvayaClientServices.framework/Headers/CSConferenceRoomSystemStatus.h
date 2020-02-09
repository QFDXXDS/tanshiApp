/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Enumeration representing conferencing room system's status.
 */
typedef NS_ENUM(NSUInteger, CSConferenceRoomSystemStatus) {
    /**
     * The room system's status is unknown.
     */
    CSConferenceRoomSystemStatusUnknown,
    
    /**
     * The room system is available.
     * The user can initiate mobile link connection to this system.
     */
    CSConferenceRoomSystemStatusAvailable,
    
    /**
     * The room system is busy.
     * Mobile link connection attempt will fail.
     */
    CSConferenceRoomSystemStatusBusy,
    
    /**
     * The user is not allowed to connect to the room system.
     * Mobile link connection attempt will fail.
     */
    CSConferenceRoomSystemStatusNotAllowed
};
