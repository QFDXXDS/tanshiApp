/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSUser.h"
#import "CSDownloadService.h"

@class CSClientConfiguration;
@class CSMediaServicesInstance;

@protocol CSClientDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 * Log levels used by Avaya Client Services.
 */
typedef NS_ENUM(NSUInteger, CSLogLevel) {
	CSLogLevelError,
	CSLogLevelWarning,
	CSLogLevelInfo,
	CSLogLevelDebug
};

/**
 * Signature for a block used for logging.
 *
 * @param level The log level of the message.
 * @param tag An optional tag string categorizing the message. May be nil.
 * @param message The log message.
 */
typedef void (^CSLogHandler)(CSLogLevel level,  NSString * _Nullable tag, NSString *message);

@interface CSClient : NSObject

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithConfiguration:(CSClientConfiguration *)clientConfiguration delegate:(nullable id<CSClientDelegate>)delegate delegateQueue:(nullable dispatch_queue_t)queue NS_DESIGNATED_INITIALIZER;

/**
 * The delegate used to handle client-related events.
 */
@property (nonatomic, weak) id<CSClientDelegate> delegate;

/**
 * The queue on which delegate methods are called.
 */
@property (nonatomic, readonly) dispatch_queue_t delegateQueue;

/**
 * The media services instance associated with this client.
 */
@property (nonatomic, readonly) CSMediaServicesInstance *mediaServices;

/**
 * The certificate manager instance associated with this client.
 */
@property (nonatomic, readonly) CSCertificateManager *certificateManager;

/**
 * Service providing access to file download services for this user.
 */
@property (nonatomic, readonly) CSDownloadService *downloadService;

/**
 * The current log level, which controls the verbosity of log output.
 *
 * The default log level is @c CSLogLevelError.
 */
@property (class) CSLogLevel logLevel;

/**
 * A log handler block to call when the library logs a message.
 *
 * This block may be called from multiple threads. By default the handler is
 * @c nil and logging is performed through NSLog.
 */
@property (class, nullable) CSLogHandler logHandler;

/**
 * The current version of the library.
 */
@property (class, readonly) NSString *versionString;

/**
 * Returns configured cipher suites excluding black listed cipher suites.
 * @see -[CSSecurityPolicyConfiguration] blackListedCipherSuites
 */
@property (readonly) NSArray<NSNumber *> *configuredCipherSuites;

/**
 * Creates and configures a new @c CSUser instance.
 *
 * @param userConfiguration The configuration information for the new user.
 * @param handler A completion handler receiving the new user object or an error
 *        object describing the reason user creation failed.
 */
- (void)createUserWithConfiguration:(CSUserConfiguration *)userConfiguration completionHandler:(void (^)(CSUser *user, NSError *error))handler;

/**
 * Starts an asynchronus shutdown of the client
 *
 * All users and associated sessions will be removed, all sockets closed, all services shut down and other
 * internal resources released. When shutdown is complete, the <see -[CSClientDelegate clientDidShutdown:]> 
 * event will be fired. At that point, it is safe to dispose of the client.
 *
 * Shutdown may be graceful or ungraceful from the signaling perspective. 
 *
 * In a graceful shutdown, it will attempt to disconnect all established connections with servers and to
 * unregister users with servers if applicable, before proceeding with shutdown and cleanup of internal resources. 
 * It will wait to ensure that all the required signaling is exchanged with the servers before the shutdown
 * operation is reported as complete. This graceful shutdown operation may take some time as it may require 
 * waiting on timeouts if the server or remote end of sessions are unreachable or unresponsive.
 *
 * In an ungraceful shutdown, only shutdown of local services and local resource cleanup are performed.
 *
 * @param gracefulShutdown true if an attempt should be made to disconnect users from servers, to wait for 
 *                         signaling completed, before cleanup of local resources (a graceful shutdown).
 *                         false if local-only shutdown should be performed (an ungraceful shutdown).
 *
 * @see -[CSClientDelegate clientDidShutdown:]
 */
- (void)shutdown:(BOOL)gracefulShutdown;

/**
 * Prepares the client for a period of background operation during which the process may be
 * suspended.
 *
 * This is used to support the background mode for VoIP applications on iOS. In this mode a keepalive handler
 * is used to wake up the application periodically while it is in the background, and between invocations of
 * this handler the process may be suspended. During the interval in which the process is suspended the
 * client may need to refresh its registration with the call server in order to maintain service. This method
 * checks for any such conditions and, if possible, performs them immediately so that the client will
 * maintain service while the process is in the suspended state.
 *
 * In some cases it may not be possible for the client to support the specified background interval. For
 * example, if the requested background interval is 10 minutes and the user's call server has been configured
 * with a registration refresh time of 5 minutes, this method will return NO as it is not possible to support
 * a 10 minute suspend interval when the registration must be refreshed every 5 minutes. If this method
 * returns NO the application should use the best available means of preventing the application from being
 * suspended, or inform the user that background operation is not possible. Because the conditions that
 * prevent use of the specified background interval may change during the life of the application it should
 * support the return value of this method changing each time the application enters the background or its
 * keepalive handler is invoked.
 *
 * @param interval The maximum time interval that the application may be suspended for. This should be the
 *        same value passed to -[UIApplication setKeepAliveTimeout:handler:].
 *
 * @return YES if the client was able to successfully prepare for the specified background interval, NO if
 *         not.
 */
- (BOOL)prepareForBackgroundInterval:(NSTimeInterval)interval;

/**
 * Starts an asynchronus removal of a user
 *
 * A user and associated sessions will be removed, all sockets closed, all services shut down and other
 * internal resources released. When removal is complete, the <see -[CSClientDelegate client:didRemoveUser:]> 
 * event will be fired. At that point, it is safe to dispose of the user.
 *
 * Removal may be graceful or ungraceful from the signaling perspective.
 *
 * In a graceful removal, it will attempt to disconnect all established connections used by the user and to
 * unregister the user with servers if applicable, before proceeding with shutdown and cleanup of internal 
 * resources allocated for the user. It will wait to ensure that all the required signaling is exchanged 
 * with the servers before the shutdown operation is reported as complete. This graceful shutdown operation 
 * may take some time as it may require waiting on timeouts if the server or remote end of sessions are 
 * unreachable or unresponsive.
 *
 * In an ungraceful removal, only shutdown of local services and local resource cleanup for the user are 
 * performed.
 *
 * @param user The user to remove.
 * @param gracefulRemove true if an attempt should be made to disconnect user from servers, to wait for 
 *                       signaling completed, before cleanup of local resources (a graceful removal).
 *                       false if local-only removal should be performed (an ungraceful removal).
 *
 * @see -[CSClientDelegate client:didRemoveUser:]
 */
- (void)removeUser:(CSUser *)user gracefulRemove:(BOOL)gracefulRemove;


#if TARGET_OS_IPHONE
/**
 * For CallKit applications, informs the SDK when the AVAudioSession is
 * activated or deactivated.
 *
 * This method is intended to be connected to the application's
 * CXProviderDelegate provider:didActivateAudioSession: and
 * provider:didDeactivateAudioSession: methods. Since CallKit activates the
 * audio session separately from the call initiation action the SDK needs to be
 * informed of this activation/deactivation as a separate step.
 *
 * If legacy cellular call detection is enabled via CSClientConfiguration::cellularCallDetectionEnabled
 * this method has no effect.
 */
- (void)audioSessionDidBecomeActive:(BOOL)active;

#endif

@end

/**
 * Describes methods that are implemented by the delegate of a @c CSClient.
 *
 * These methods are used to provide information about the lifecycle of the client and to delegate
 * actions such as certificate trust evaluation.
 */
@protocol CSClientDelegate <NSObject>

/**
 * Sent when the client has shut down.
 *
 * @param client The client sending the message.
 */
- (void)clientDidShutdown:(CSClient *)client;

/**
 * Sent when the client creates a new user.
 *
 * @param client The client sending the message.
 * @param user The newly-created user.
 */
- (void)client:(CSClient *)client didCreateUser:(CSUser *)user;

/**
 * Sent when the client removes an user.
 *
 * @param client The client sending the message.
 * @param user The removed user.
 */
- (void)client:(CSClient *)client didRemoveUser:(CSUser *)user;

@end

NS_ASSUME_NONNULL_END
