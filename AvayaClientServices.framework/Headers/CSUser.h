/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCallFeatureService.h"
#import "CSCallService.h"
#import "CSVoiceMessagingService.h"
#import "CSMessagingService.h"
#import "CSPresenceService.h"
#import "CSUserConfiguration.h"
#import "CSSharedControlService.h"
#import "CSCertificateManager.h"
#import "CSContactService.h"
#import "CSCollaborationService.h"
#import "CSCallLogService.h"
#if TARGET_OS_IPHONE
 #import "CSPushNotificationService.h"
#endif
#import "CSUnifiedPortalService.h"
#import "CSServiceStatus.h"
#import "CSSpaceService.h"
#import "CSOtherPhoneService.h" 
#if !TARGET_OS_IPHONE
 #import "CSHIDService.h" 
#endif


@protocol CSUserRegistrationDelegate;
@protocol CSUserAdminEventDelegate;
@protocol CSUserExternalAppInterfaceDelegate;
@protocol CSUserResourceDiscoveryDelegate;

/**
 * Represents an user (an extension or user account) that can be registered with a call server.
 *
 * Identities are created through a protocol-specific signaling engine instance.
 */
@interface CSUser : NSObject

/**
 * The delegate responsible for handling user registration related events.
 */
@property (nonatomic, weak) id<CSUserRegistrationDelegate> registrationDelegate;


@property(nonatomic, weak) id<CSUserAdminEventDelegate> userAdminDelegate;

/**
 * The delegate responsible for handling external app interface related events.
 */
@property(nonatomic, weak) id<CSUserExternalAppInterfaceDelegate> externalAppInterfaceDelegate;

/**
 * The delegate responsible for handling resource discovery related events.
 */
@property(nonatomic, weak) id<CSUserResourceDiscoveryDelegate> resourceDiscoveryDelegate;

/**
 * The user ID of the user.
 */
@property (nonatomic, readonly) NSString *userId;

/**
 * Service providing call features for this user.
 *
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSCallService* callService;

/**
 * Service providing call features for this user.
 *
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSCallFeatureService* callFeatureService;

/**
 * Service providing voice messaging feature for this user.
 *
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSVoiceMessagingService* voiceMessagingService;

/**
 * Service providing access to presence features for this user.
 *
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSPresenceService* presenceService;

/**
 * Service providing access to messaging features for this user.
 *
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSMessagingService* messagingService;

/**
 * Service providing other phone mode for this user.
 *
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSOtherPhoneService* otherPhoneService;

#if !TARGET_OS_IPHONE
/**
 * Service providing access to Human Interface Device (HID) updates.
 */
@property (nonatomic, readonly) CSHIDService *hidService;
#endif

#if TARGET_OS_IPHONE
/**
 * Service providing access to push notification message processing for this user.
 *
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSPushNotificationService *pushNotificationService;
#endif

/**
 * Service providing access to shared control features for this user.
 *
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSSharedControlService *sharedControlService;

/**
 * Service providing access to contact features for this user.
 *
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSContactService *contactService;

/**
 * Service providing collaboration services for this user.
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSCollaborationService *collaborationService;

/**
 * Service providing call log services for this user.
 * If the user has not yet been configured this property will return @c nil.
 */
@property (nonatomic, readonly) CSCallLogService *callLogService;

@property (nonatomic, readonly) CSSpaceService *spaceService;

/**
 * Service providing access to Unified Portal features for this user.
 */
@property (nonatomic, readonly) CSUnifiedPortalService *unifiedPortalService;

/**
 * The application Ids of any external applications that have registered
 * to monitor and / or control calls on behalf of this user.
 */
@property (nonatomic, readonly) NSArray *externalAppIds;

/**
 * Returns ServiceStatus object describing whether the Contact service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *contactServiceStatus;
 
/**
 * Returns ServiceStatus object describing whether the Messaging service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *messagingServiceStatus;

/**
 * Returns ServiceStatus object describing whether the Call service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *callServiceStatus;
 
/**
 * Returns ServiceStatus object describing whether the Collaboration service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *collaborationServiceStatus;
 
/**
 * Returns ServiceStatus object describing whether the CallFeature service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *callFeatureServiceStatus;
 
/**
 * Returns ServiceStatus object describing whether the Presence service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *presenceServiceStatus;

/**
 * Returns ServiceStatus object describing whether the PushNotification service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *pushNotificationServiceStatus;
 
/**
 * Returns ServiceStatus object describing whether the CallLog service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *callLogServiceStatus;
 
/**
 * Returns ServiceStatus object describing whether the VoiceMessaging service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *voiceMessagingServiceStatus;

/**
 * Returns ServiceStatus object describing whether the UnifiedPortal service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *unifiedPortalServiceStatus;
 
/**
 * Returns ServiceStatus object describing whether the SharedControl service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *sharedControlServiceStatus;

/**
 * Returns ServiceStatus object describing whether the other phone service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *otherPhoneServiceStatus;

#if !TARGET_OS_IPHONE
/**
 * Returns ServiceStatus object describing whether the HID service is enabled.
 * @return {@link CSServiceStatus} object describing whether a certain service is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *hidServiceStatus;
#endif

/**
 * Returns the SignalingServerGroup containing the complete call server list used by system,
 * it contains additional servers discovered by system from different source including the servers
 * provided by the user. Client application can persist it and then use it for subsequent registrations
 * for creation of {@link CSConnectionPolicy}.
 * @return {@link CSSignalingServerGroup} object containing the complete call server list used by system.
 * @li user:didReceiveSignalingServerGroup:
 */
@property (nonatomic, readonly) CSSignalingServerGroup *signalingServerGroup;

/**
 * Starts all services.
 *
 * Progress is provided via the CSUserRegistrationDelegate methods and other service delegates.
 * A successful callback sequence for a two-server configuration will be similar to the
 * following:
 *
 * @li user:registrationInProgressWithServer:<server 1>
 * @li user:registrationInProgressWithServer:<server 2>
 * @li user:registrationSuccessfulWithServer:<server 1>
 * @li user:registrationSuccessfulWithServer:<server 2>
 * @li userRegistrationSuccessfulWithAllServers
 */
- (void)start;

/**
 * Stops all the services.
 *
 * Progress is provided via the CSUserRegistrationDelegate methods and other service delegates.
 * A successful callback sequence for a two-server configuration will be similar to the
 * following:
 *
 * @li user:unregistrationInProgressWithServer:<server 1>
 * @li user:unregistrationInProgressWithServer:<server 2>
 * @li user:unregistrationSuccessfulWithServer:<server 1>
 * @li user:unregistrationSuccessfulWithServer:<server 2>
 * @li userUnregistrationCompleteWithAllServers
 */
- (void)stop;

@end

typedef NS_ENUM(NSUInteger, CSConfigurationReloadRequestType) {
	CSConfigurationReloadRequestTypeAll,
	CSConfigurationReloadRequestTypeEndpointConfiguration,
	CSConfigurationReloadRequestTypeContacts,
	CSConfigurationReloadRequestTypeMaintenanceData,
	CSConfigurationReloadRequestTypeCallHistory
};

/**
 * Identifies the type of a discovered resource item that is of interest to the
 * client application.  These items are received from a connected server as part
 * of a registrqation response or through a resource discovery process.
 */
typedef NS_ENUM(NSUInteger, CSResourceDiscoveryItemType) {
	/**
	 * Indicates that the discovered resource is the primary address of the
	 * One-X Portal server. This resource type applies only to IP Office
	 * deployments where the One-X Portal is used as the messaging server.
	 */
	CSResourceDiscoveryItemTypeOneXPortalPrimaryServer,
	/**
	 * Indicates that the discovered resource is the secondary address of the
	 * One-X Portal server. This resource type applies only to IP Office
	 * deployments where the One-X Portal is used as the messaging server.
	 */
	CSResourceDiscoveryItemTypeOneXPortalSecondaryServer,
	/**
	 * Indicates that the discovered resource is the username that should be
	 * used to login to the One-X Portal server. This resource type applies only
	 * to IP Office deployments where the One-X Portal is used as the messaging
	 * server.
	 */
	CSResourceDiscoveryItemTypeOneXPortalUsername,
};

@protocol CSUserExternalAppInterfaceDelegate <NSObject>

/**
 * An external application has registered to the external app interface
 * in order to monitor, place and/or control calls on this user's
 * behalf.
 *
 * @param user The user the external app is interacting with.
 * @param appId The identifier of the external application.
 */
-(void)user:(CSUser *)user didRegisterExternalAppWithId:(NSString *)appId;

/**
 * A previously connected external application has unregistered from
 * the external app interface.
 *
 * @param user The user the external app is interacting with.
 * @param appId The identifier of the external application.
 */
-(void)user:(CSUser *)user didUnregisterExternalAppWithId:(NSString *)appId;

@end

@protocol CSUserAdminEventDelegate <NSObject>

- (void)userDidReceiveRebootRequest:(CSUser *)user;

- (void)user:(CSUser *)user didReceiveConfigurationReloadRequest:(CSConfigurationReloadRequestType)reloadRequestType;

/**
* Sent when a registration response has alternate call server list. Client application should persist the
* signaling server group and include them in subsequent registrations
*
* @param user The user sending the message.
* @param serverGroup  Complete list of signaling servers. 
*/
- (void)user:(CSUser *)user didReceiveSignalingServerGroup:(CSSignalingServerGroup *)serverGroup;

@end

@protocol CSUserResourceDiscoveryDelegate <NSObject>

/**
 * Sent when a resource of interest to the client application is discovered
 * during registration or resource discovery.
 *
 * @param user The user sending the message.
 * @param resourceType  Identifies the type of the resource that was discovered.
 * @param resourceData  The resource data that was discovered for the indicated resource type.
 */
- (void)user:(CSUser *)user didDiscoverResourceOfType:(CSResourceDiscoveryItemType)resourceType
	resourceData:(NSString *)resourceData;

@end

@protocol CSUserRegistrationDelegate <NSObject>

/**
 * Sent when a registration attempt is started.
 *
 * @param user The user sending the message.
 * @param server The server being contacted.
 */
- (void)user:(CSUser *)user didStartRegistrationWithServer:(CSSignalingServer *)server;

/**
 * Sent when the user has been successfully registered.
 *
 * @param user The user sending the message.
 * @param server The server being contacted.
 */
- (void)user:(CSUser *)user didRegisterWithServer:(CSSignalingServer *)server;

/**
 * Sent when a registration attempt has failed. If error.code is CSErrorRedirected,
 * the next registration/unregistration methods (for example didRegisterWithServer or didFailToRegisterWithServer) will be called
 * with a new CSSignalingServer that will be different from the initially configured one.
 *
 * @param user The user sending the message.
 * @param server The server being contacted.
 * @param error An error object describing the failure.
 */
- (void)user:(CSUser *)user didFailToRegisterWithServer:(CSSignalingServer *)server error:(NSError *)error;

/**
 * Sent when all registrations have been successful.
 *
 * @param user The user sending the message.
 */
- (void)userDidRegisterWithAllServers:(CSUser *)user;

/**
 * Sent when all registrations have failed.
 *
 * @param user The user sending the message.
 * @param flag Indicates that if Client SDK will retry the failed registration request;
 *        False means registration failure is fatal and application
 *        must start a new registration after resolving the issue that 
 *        blocked the registrations from succeeding.
 
 */
- (void)userDidFailToRegisterWithAllServers:(CSUser *)user willRetry:(BOOL)flag;

/**
 * Sent when an unregistration attempt is started.
 *
 * @param user The user sending the message.
 * @param server The server being contacted.
 */
- (void)user:(CSUser *)user didStartUnregistrationWithServer:(CSSignalingServer *)server;

/**
 * Sent when the user has been successfully unregistered.
 *
 * @param user The user sending the message.
 * @param server The server being contacted.
 */
- (void)user:(CSUser *)user didUnregisterWithServer:(CSSignalingServer *)server;

/**
 * Sent when an unregistration attempt has failed.
 *
 * @param user The user sending the message.
 * @param server The server being contacted.
 * @param error An error object describing the failure.
 */
- (void)user:(CSUser *)user didFailToUnregisterWithServer:(CSSignalingServer *)server error:(NSError *)error;

/**
 * Sent when unregistration is complete.
 *
 * @param user The user sending the message.
 */
- (void)userDidCompleteUnregistrationWithAllServers:(CSUser *)user;

/**
 * Occurs when the registration response payload is received from network.
 *
 * @param user user that the callback is associated with.
 * @param payloadParts an array which contains message parts of type CSMessageBodyPart.
 * @param server is a server which has sent registration response payload after registration request.
 */
-(void) user:(CSUser *)user didReceiveRegistrationResponsePayload:(NSArray *)payloadParts fromServer:(CSSignalingServer *)server;

@end
