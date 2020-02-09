/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSFeatureType.h"

@class CSEnhancedCallForwardingStatus;

/**
 * The feature status values.
 */
typedef NS_ENUM(NSInteger, CSFeatureStatus) {
	/** The feature status is Undefined. */
	CSFeatureStatusUndefined = 0,
	/** The feature status is ON. */
	CSFeatureStatusOn,
	/** The feature status is OFF. */
	CSFeatureStatusOff,
	/** The feature status is Alerting. */
	CSFeatureStatusAlerting
};

/**
 * The associated parameters for a specific feature status.
 *
 * This is a union of the parameters that can be present in the status for any supported
 * feature. The caller should know which parameters to expect for a specific feature (some
 * required, some optional).
 */
@interface CSFeatureStatusParameters : NSObject

/**
 * This is the location of the feature button as configured on the server.
 */
@property (nonatomic, readonly) NSInteger buttonLocation;

/**
 * The feature type associated with this status.
 */
@property (nonatomic, readonly) CSFeatureType featureType;

/**
 * The feature's status.
 */
@property (nonatomic, readonly) CSFeatureStatus status;

/**
 * The owner extension this feature status is targeted for.
 *
 * Populated only if different from the local user's extension.
 */
@property (nonatomic, readonly) NSString *ownerExtension;

/**
 * The destination extension associated with this feature.
 *
 * Populated with the value of the 'avaya-cm-destination' parameter if present in the status update.
 */
@property (nonatomic, readonly) NSString *destination;

/**
 * This field will be populated only when received from the server.
 * This is the short form of the URI. It can be received in feature status update.
 *
 * Eg:
 * \<feature-status entity="sip:14088640028\@svuca.com" version="1" state="full" avext="40028"\>
 * \<feature name ="busy-indicator" status="off"/\>
 * \</feature-status\>
 *
 */
@property (nonatomic, readonly) NSString *destinationShortForm;

/**
 * This is the location of the feature button as configured on SMGR. This is normally associated with Autodial feature buttons.
 * 
 * @deprecated It is recommended to use featureLabel instead.
 */
@property (nonatomic, readonly) NSString *destinationLabel DEPRECATED_ATTRIBUTE;

/**
 * This is the label associated with the feature.
 *
 */
@property (nonatomic, readonly) NSString *featureLabel;

/**
 * This is the flag which indicates whether the destinationExtension can be edited or not by the user.
 */
@property (nonatomic, readonly) BOOL isDestinationExtensionEditable;

/**
 * This field gives the Hunt Group Number populated with value of "avaya-cm-group" parameter if present in feature status notify
 * for hunt-group-busy-position feature.
 * For other features, this property will return 0.
 */
@property (nonatomic, readonly) NSInteger huntGroupNumber;

/**
 * The Enhanced Call Forward status for the user's local extension, if any.
 */
@property (nonatomic, readonly) CSEnhancedCallForwardingStatus *enhancedCallForwardingStatus;

/**
 * This is the flag which indicates whether the feature label can be edited or not by the user.
 */
@property (nonatomic, readonly, getter=isFeatureLabelEditable) BOOL featureLabelEditable;

/**
 * Constructs an CSFeatureStatusParameters object from the specified parameters.
 *
 * @param buttonLocation                The index of the feature button.
 * @param featureType                   The feature type associated with this status.
 * @param status                        The feature status.
 * @param ownerExtension                The owner extension this feature status is targeted for.
 * @param destination                   The destination extension associated with this feature.
 * @param destinationShortForm          The short form of the destination extension.
 * @param featureLabel                  The label text of the feature.
 * @param isExtensionEditable           YES if the destination extension is editable otherwise NO.
 * @param enhancedCallForwardingStatus  The enhanced call forward status.
 * @param huntGroupNumber               The hunt group number associated with this feature.
 * @param featureLabelEditable          YES if the feature label is editable otherwise NO
 */
- (instancetype)initWithFeatureButtonLocation:(NSInteger)buttonLocation
								  featureType:(CSFeatureType)featureType
									   status:(CSFeatureStatus)status
							   ownerExtension:(NSString*)ownerExtension
								  destination:(NSString*)destination
						 destinationShortForm:(NSString*)destinationShortForm
								 featureLabel:(NSString*)featureLabel
				 destinationExtensionEditable:(BOOL)isExtensionEditable
				 enhancedCallForwardingStatus:(CSEnhancedCallForwardingStatus*)enhancedCallForwardingStatus
							  huntGroupNumber:(NSInteger)huntGroupNumber
							featureLabelEditable:(BOOL)featureLabelEditable;

@end
