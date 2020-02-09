/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSEnhancedCallForwardingStatus.h"

/**
 * The feature actions that can be used when invoking a feature.
 */
typedef NS_ENUM(NSInteger, CSFeatureAction) {
	/** Undefined action. */
	CSFeatureActionUndefined = 0,
	/** Action to enable the feature. */
	CSFeatureActionOn,
	/** Action to disable the feature. */
	CSFeatureActionOff
};

/**
 * The associated parameters for a feature invocation.
 *
 * This is a union of the parameters that can be passed in the invocation for any supported
 * feature. The caller is expected to know which parameters are supported for a specific
 * feature (some required, some optional).
 */
@interface CSFeatureInvocationParameters : NSObject

/**
 * The action used in the 'avaya-cm-action' parameter of the feature invocation.
 *
 * If set to CSFeatureActionUndefined, avaya-cm-action is not used during feature invocation.
 */
@property (nonatomic) CSFeatureAction action;

/**
 * The destination used in the 'avaya-cm-destination'=\<destination\>' parameter of the feature
 * invocation.
 *
 * If set to nil, avaya-cm-destination is not used during feature invocation.
 */
@property (nonatomic, copy) NSString *destination;

/**
 * The extension used in in 'avaya-cm-extension' parameter of the feature invocation.
 *
 * If set to nil, avaya-cm-extension is not used during feature invocation.
 */
@property (nonatomic, copy) NSString *extension;

/**
 * The number used in the 'avaya-cm-pickup-number' parameter of the feature invocation.
 *
 * If set to -1, avaya-cm-pickup-number is not used during feature invocation.
 */
@property (nonatomic) NSInteger pickupNumber;

/**
 * The extension used in the To and Request-URI of the feature invocation (in place of the the local
 * user's AOR).
 *
 * If set to nil, the local user's AOR is used for feature invocation.
 */
@property (nonatomic, copy) NSString *ownerExtension;

/**
 * For Enhanced Call Forwarding feature invocation, ECF parameter from Client received in "enhancedCallForwardingStatus".
 *
 * If set, the other standard parameters are of no relavance.
 */
@property (nonatomic, copy) CSEnhancedCallForwardingStatus *enhancedCallForwardingStatus;

/**
 * The Hunt Group Number to be used in avaya-cm-group parameter for the hunt-group-busy-position feature invocation
 */
@property (nonatomic) NSInteger huntGroupNumber;

@end
