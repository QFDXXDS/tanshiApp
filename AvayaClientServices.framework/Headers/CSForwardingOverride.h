#import <Foundation/Foundation.h>

/**
 * Specifies whether the forwarding destination
 * of monitored station will be ignored by Team Button speed dial invocation
 * if any of forwarding features are enabled on the monitored station.
 * Rerouting is considered active if Send All Calls, Call Forward or Enhanced
 * Call Forward have active forwarding.
 *
 * If set to ask, the client can override the forwarding destination.
 *
 */
typedef NS_ENUM(NSInteger, CSForwardingOverride) {
    /**
     * Call forwarding destination on the monitored station will not
     * be overridden by Team Button speed dial invocation.
     */
    CSForwardingOverrideNo = 0,
    /**
     * Call forwarding destination on the monitored station will
     * be overridden by Team Button speed dial invocation.
     */
    CSForwardingOverrideYes,
    /**
     * The client can specify whether Call forwarding destination on the monitored
     * station will be overridden by Team Button speed dial invocation or not.
     */
    CSForwardingOverrideAsk
};
