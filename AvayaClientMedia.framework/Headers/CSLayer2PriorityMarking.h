/* Copyright Avaya Inc. */

#ifndef clientsdk_CSLayer2PriorityMarking_h
#define clientsdk_CSLayer2PriorityMarking_h

#import <Foundation/Foundation.h>

/**
 * Enum indicating the priority levels for implementing quality of service (QoS) at the media access control (MAC) level.
 * The classes of service are provided through 3-bit PCP field in an IEEE 802.1Q header added to the frame.
 */
typedef NS_ENUM(NSUInteger, CSLayer2PriorityMarking) {
    /** Corresponds to priority 0 */
    CSLayer2PriorityMarkingBestEffort,
    /** Corresponds to priority 1 */
    CSLayer2PriorityMarkingBackground,
    /** Corresponds to priority 2 */
    CSLayer2PriorityMarkingExcellentEffort,
    /** Corresponds to priority 3 */
    CSLayer2PriorityMarkingCriticalApplication,
    /** Corresponds to priority 4 */
    CSLayer2PriorityMarkingVideo,
    /** Corresponds to priority 5 */
    CSLayer2PriorityMarkingVoice,
    /** Corresponds to priority 6 */
    CSLayer2PriorityMarkingInternetworkControl,
    /** Corresponds to priority 7 */
    CSLayer2PriorityMarkingNetworkControl,
    /** Makes CSDK to use values from the network or use an appropriate default */
    CSLayer2PriorityMarkingAutomatic
};

#endif /* clientsdk_CSLayer2PriorityMarking_h */
