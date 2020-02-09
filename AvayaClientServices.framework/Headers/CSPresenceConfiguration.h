/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * User configuration information for the presence service.
 * This class provides configuration and preference data for the presence service features.
 */
@interface CSPresenceConfiguration : NSObject

/**
 * Indicates whether the presence service is enabled.
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * Sets a link between "Do Not Disturb" presence state and "Send All Calls" call service feature.
 *
 * <p>If the link is enabled and "Send All Calls" feature is available, the following behavior applies. 
 * Once the presence state of the user changes to "Do not Disturb", "Send All Calls" is automatically switched on.
 * If the presence state of the user changes from "Do not Disturb" to any other state, "Send All Calls" is automatically switched off.</p>
 */
@property (nonatomic) BOOL sendAllCallsOnDoNotDisturb;

/**
 * An optional parameter to specify the presence server address.
 *
 * <p>If configured, this server will be used as the domain in the request URI for all presence-related messages. 
 * Otherwise the address will be discovered automatically.</p>
 */
@property (nonatomic, copy) NSString *serverAddress;

/**
 * Sets the timeout for the user inactivity timer.
 *
 * <p>Inactivity timer is used to automatically change the user's presence state to 'away'
 * if the user is inactive, i.e. not using the device with the installed application.
 * When the timer fires, the user's presence is set to the 'away' state.	
 * If zero value is specified, the inactivity timer is disabled.</p>
 */
@property (nonatomic) NSTimeInterval autoAwayTimeout;


@end
