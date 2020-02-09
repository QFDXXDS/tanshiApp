/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, CSBFCPMode)
{
	/** BFCP is disabled */
	CSBFCPModeDisabled = 0,
	/** BFCP will be offered over UDP but can be answered over UDP or TCP*/
	CSBFCPModeUdpOnly,
	/** BFCP will be offered over TCP but can be answered over UDP or TCP*/
	CSBFCPModeTcpOnly
};

/**
 * Configuration information for BFCP.
 */
@interface CSBFCPConfiguration : NSObject

/**
 * A Boolean value indicating whether BFCP is enabled.
 *
 */
@property (nonatomic, getter=isBFCPEnabled) BOOL enabled;

/**
 * Indicates BFCP transport mode.
 *
 */
@property(nonatomic)CSBFCPMode bfcpMode;

/**
 * Indicates BFCP UDP mininum port value.
 *
 */
@property(nonatomic)NSUInteger bfcpUdpMinPort;

/**
 * Indicates BFCP UDP maximum port value.
 *
 */
@property(nonatomic)NSUInteger bfcpUdpMaxPort;

@end
