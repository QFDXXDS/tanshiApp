/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSSIPUserConfiguration.h"
#import "CSHTTPUserConfiguration.h"
#import "CSAMMConfiguration.h"
#import "CSACSConfiguration.h"
#import "CSBFCPConfiguration.h"
#import "CSCESConfiguration.h"
#import "CSLDAPConfiguration.h"
#import "CSDialingRulesConfiguration.h"
#import "CSConferenceConfiguration.h"
#import "CSPPMConfiguration.h"
#if TARGET_OS_IPHONE
 #import "CSPushNotificationConfiguration.h"
#endif
#import "CSEC500Configuration.h"
#import "CSWCSConfiguration.h"
#import "CSLocalContactConfiguration.h"
#import "CSPresenceConfiguration.h"
#import "CSVideoUserConfiguration.h"
#import "CSZangConfiguration.h"
#import "CSIPOfficeConfiguration.h"
#import "CSMessagingConfiguration.h"

/**
 * Configuration information for a @c CSUser.
 */
@interface CSUserConfiguration : NSObject


/**
 * Configuration information for the user's SIP provider.
 */
@property (nonatomic, strong) CSSIPUserConfiguration *SIPUserConfiguration;

/**
 * Configuration information for the user's HTTP provider.
 */
@property (nonatomic, strong) CSHTTPUserConfiguration *HTTPUserConfiguration;

/**
 * Configuration information for the user's AMM provider.
 */
@property (nonatomic, strong) CSAMMConfiguration *AMMConfiguration;

/**
 * Configuration information for the user's ACS provider.
 */
@property (nonatomic, strong) CSACSConfiguration *ACSConfiguration;

/**
 * Configuration information for the user's CES provider.
 */
@property (nonatomic, strong) CSCESConfiguration *CESConfiguration;

/**
 * Configuration information for the user's LDAP provider.
 */
@property (nonatomic, strong) CSLDAPConfiguration *LDAPConfiguration;

/**
 * Configuration information for the user's Dialing Rules provider.
 */
@property (nonatomic, strong) CSDialingRulesConfiguration *dialingRulesConfiguration;

/**
 * Configuration information for the user's Conference provider.
 */
@property (nonatomic, strong) CSConferenceConfiguration *conferenceConfiguration;

/**
 * Configuration information for the user's PPM server.
 * If this information is nil (the default), then the initial SIP proxy server address from
 * the SipUserConfiguration as the PPM server address.
 */
@property (nonatomic, strong) CSPPMConfiguration *PPMConfiguration;

#if TARGET_OS_IPHONE
/**
 * Configuration for the user's push notification provider.
 */
@property (nonatomic, strong) CSPushNotificationConfiguration *pushNotificationConfiguration;
#endif

/**
 * Configuration information for the user's EC500 provider.
 */
@property (nonatomic, strong) CSEC500Configuration *EC500Configuration;

/**
 * Configuration information for the user's WCS provider.
 */
@property (nonatomic, strong) CSWCSConfiguration *WCSConfiguration;

/**
 * BFCP Configuration information.
 */
@property (nonatomic, strong) CSBFCPConfiguration *BFCPConfiguration;

/**
 * Configuration information for the user's Local Contact provider.
 */
@property (nonatomic, strong) CSLocalContactConfiguration *localContactConfiguration;

/**
 * Presence configuration settings
 */
@property (nonatomic, strong) CSPresenceConfiguration *presenceConfiguration;

/**
 * Video configuration settings
 */
@property (nonatomic, strong) CSVideoUserConfiguration *videoUserConfiguration;

/**
 * Zang configuration settings
 */
@property (nonatomic, strong) CSZangConfiguration *zangConfiguration;

/**
 * IP Office configuration settings
 */
@property (nonatomic, strong) CSIPOfficeConfiguration *IPOfficeConfiguration;

/**
 * Messaging configuration settings
 */
@property (nonatomic, strong) CSMessagingConfiguration *messagingConfiguration;

/**
 * Set full file path to the file in which local user's call logs are to be persisted.  This path
 * is provided by the UI/client that is aware of the appropriate directory applicable for such
 * platform dependent storage location.  If invalid path is provided, the call log items will not be
 * persisted, but will be updated in the cache during runtime only.
 */
@property (nonatomic, strong) NSURL *localCallLogFilePath;

/**
 * Controls whether or not the external app interface is available.
 */
@property (nonatomic) BOOL externalAppInterfaceEnabled;

/**
 * Enable or disable bandwidth regulation.
 */
@property (nonatomic) BOOL bandwidthRegulationEnabled;

@end
