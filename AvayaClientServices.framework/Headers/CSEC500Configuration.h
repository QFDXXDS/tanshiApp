//
/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * The EC500 Feature Name Extensions (FNE's) class that contains the configuration data specific for this User.
 */
@interface CSEC500Configuration : NSObject

/**
 * A Boolean value indicating whether the PPM server is configured.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * Number to dial EC500 voicemail system.
 */
@property (nonatomic, copy) NSString *voicemailNumber;

/**
 * Number to dial for Off-Pbx call enable. Enables the Off-Pbx-Call feature.
 */
@property (nonatomic, copy) NSString *fneSimRingEnableNumber;

/**
 * Number to dial for Off-Pbx call disable. Disables the Off-Pbx call feature.
 */
@property (nonatomic, copy) NSString *fneSimRingDisableNumber;

/**
 * Number to dial for enabling call forwarding. Enables the Call Forward feature.
 */
@property (nonatomic, copy) NSString *fneCallForwardEnableNumber;

/**
 * Number to dial for call forward cancel. Disables the Call Forward feature.
 */
@property (nonatomic, copy) NSString *fneCallForwardCancelNumber;

/**
 * Number to dial for active appearance select.
 */
@property (nonatomic, copy) NSString *fneActiveAppearanceSelectNumber;

/**
 * Number to dial for idle appearance select.
 */
@property (nonatomic, copy) NSString *fneIdleAppearanceSelectNumber;

/**
 * Number to dial for send all calls enable. Enables the Send All Calls feature.
 */
@property (nonatomic, copy) NSString *fneSendAllCallsEnableNumber;

/**
 * Number to dial for send all calls cancel. Cancels the Send All Calls feature.
 */
@property (nonatomic, copy) NSString *fneSendAllCallsCancelNumber;

/**
 * Delay (in seconds) inserted between the EC500 call being placed and the transmission of the digits for EC500.
 *
 * Values are 3,6,9,12 or 15 seconds
 */
@property (nonatomic) NSUInteger fneSetupDelayInSeconds;

/**
 * Specifies if the Station Security is enabled or not.
 */
@property (nonatomic, getter=isStationSecurityEnabled) BOOL stationSecurityEnabled;

@end
