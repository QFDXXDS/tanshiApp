/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * The associated parameters of a Enhanced Call Forwarding feature invocation.
 *
 * The parameters for Uncondiational Call forward viz. avaya-cm-cfall-internal-action, avaya-cm-cfall-internal-dest.
 * on busy call forward, on response call forward for internal and external.
 */

@interface CSCallForwardingStatus : NSObject

 /**
 * Constructs a CSCallForwardingStatus object from the specified parameters.
 *
 * @param enabledForInternalCalls YES if call forwarding is enabled for the internal calls.
 * @param enabledForExternalCalls YES if call forwarding is enabled for the external calls. Always NO for IP Office.
 * @param destinationForInternalCalls The destination address for the internal call forward.
 * @param destinationForExternalCalls The destination address for the external call forward. Always empty for IP Office.
 */

- (instancetype)initWithInternalCallForwardingStatus:(BOOL)enabledForInternalCalls
                        externalCallForwardingStatus:(BOOL)enabledForExternalCalls
                                 internalDestination:(NSString*)destinationForInternalCalls
                                 externalDestination:(NSString*)destinationForExternalCalls;

/**
 * A Boolean value indicating the status of call forwarding for internal calls.
 *
 * The value of this property is YES if the call forwarding is enabled for 
 * internal calls.
 */

@property (nonatomic, readonly) BOOL enabledForInternalCalls;

/**
 * A Boolean value indicating the status of call forwarding for external calls.
 *
 * The value of this property is YES if the call forwarding is enabled for
 * external calls.
 */

@property (nonatomic, readonly) BOOL enabledForExternalCalls;

/**
 * Returns the destination address where the call needs to be
 * forwarded for internal calls. 		
 */

@property (nonatomic, readonly) NSString *destinationForInternalCalls;

/**
* Returns the destination address where the call needs to be
* forwarded for external calls.
*/

@property (nonatomic, readonly) NSString *destinationForExternalCalls;

@end
