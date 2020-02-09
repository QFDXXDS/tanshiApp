/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#if defined(TARGET_OS_IPHONE)
 #import <PushKit/PushKit.h>
#endif
#import "CSPushNotificationConfiguration.h"
#import "CSServiceStatus.h"

@protocol CSPushNotificationServiceDelegate;

typedef NS_ENUM(NSInteger, CSPushNotificationServiceType) {
	/**
	 * Telephony service type that delivers incoming call and message 
	 * waiting status notifications.
	 */
	CSPushNotificationTelephonyService,
};

/**
 * Represents the push notification service handling associated with a user.
 * A single instance of this object is created when a new CSUser instance is
 * created.  Any ClientSDK-related push notification information received by the
 * iOS application is passed into this object.  It should be noted that the iOS
 * application may choose to receive push notification information that is not
 * related to the ClientSDK's operations, any may selectively pass push
 * notification data received based on the context of the notification message.
 */
@interface CSPushNotificationService : NSObject

/**
 * The delegate responsible for handling push notification service events.
 */
@property (nonatomic, weak) id<CSPushNotificationServiceDelegate> delegate;

/**
 * Called by the client application for the ClientSDK to process the push 
 * notification message received from the Apple Push Notification service 
 * (APNs).  The signature of the API is consistent with the callback provided by
 * the PushKit framework when there is an incoming push notification.
 *
 * @param userInfo Push notification message received from APNs.
 * @param handler A block to be called when the operation is completed.
 *	@li @c error If the operation was successful this parameter is nil.  If
 *		an error occurred it contains an object describing the error.
 */
- (void)processRemoteNotification:(PKPushPayload *)userInfo completionHandler:(void(^)(NSError *error))handler;

/**
 * Reurns the ServiceStatus object describing whether the telephony event push 
 * service is enabled.
 * This property reflects the status of the network-based telephony push
 * notification service on behalf of this user.
 *
 * @return {@link CSServiceStatus} object describing whether a certain service 
 *	is enabled.
 */
@property (nonatomic, readonly) CSServiceStatus *telephonyEventServiceStatus;

@end

/**
 * Definition of the delegate interface that will receive push notification
 * service status.
 */
@protocol CSPushNotificationServiceDelegate <NSObject>

/**
 * Sent when the push notification service for a service type (e.g. telephony)
 * is enabled.
 *
 * @param service Push notification service instance.
 * @param type Service type.  Currently, only
 *	CSPushNotificationTelephonyService is supported.
 */
- (void)pushNotificationService:(CSPushNotificationService *)service didEnableServiceType:(CSPushNotificationServiceType)type;

/**
 * Sent when the push notification service for a service type (e.g. telephony)
 * is disabled.  For example, telephony notifications are disabled when a user
 * logs out of the SIP server, or when a push notification about a server 
 * failure is received.
 *
 * @param service Push notification service instance.
 * @param type Service type.  Currently, only
 *	CSPushNotificationTelephonyService is supported.
 */
-(void)pushNotificationService:(CSPushNotificationService*)service didDisableServiceType:(CSPushNotificationServiceType)type;

/**
 * Sent when the ClientSDK is unable to setup the push notification service type
 * successfully.  The failure may be due to an issue on the network server side
 * or local.  For example, an error is reported when connectivity to the 
 * telephony push notification network server is lost, or when the service could
 * not be started due to missing or invalid configuration information.
 *
 * @param service Push notification service instance.
 * @param type Service type.  Currently, only 
 *	CSPushNotificationTelephonyService is supported.
 * @param error Error object describing the reason for the failure.
 * @param willRetry Boolean indicating whether service reactivation is 
 *	automatically reattempted by the ClientSDK.
 */
-(void)pushNotificationService:(CSPushNotificationService *)service didFailToEnableNotificationsForServiceType:(CSPushNotificationServiceType)type error:(NSError *)error willRetry:(BOOL)willRetry;

@end

