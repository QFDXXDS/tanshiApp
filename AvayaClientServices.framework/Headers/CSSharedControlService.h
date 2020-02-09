/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSControllableEndpoint.h"

@class CSSharedControlService;
/**
 *  Describes methods that are implemented by the delegate of a @c CSSharedControlService.
 */
@protocol CSSharedControlDelegate <NSObject>

/**
 * Occurs when a controllable endpoint is available to do Shared Control with, i.e. when the desk phone is logged in and there was no desk phone
 * logged in before.
 * @param sharedControlService service which sent notification.
 * @param endpoints array containing @c CSControllableEndpoint objects.
 */
- (void)sharedControlService:(CSSharedControlService *)sharedControlService didFindControllableEndpoints:(NSArray*)endpoints;

/**
 * Occurs when there is an update in list of controllable endpoints.
 * This update can be addition or removal of an endpoint, i.e. the desk phone is logged in or out.
 *
 * @param sharedControlService service which sent notification.
 * @param endpoints array containing @c CSControllableEndpoint objects.
 */
- (void)sharedControlService:(CSSharedControlService *)sharedControlService didUpdateControllableEndpoints: (NSArray*)endpoints;

/**
 * Occurs when no controllable endpoint is available to do Shared Control with, i.e. there is no
 * desk phone logged in.
 * @param sharedControlService service which sent notification.
 */
- (void)sharedControlServiceDidDetectAllControllableEndpointsUnavailable:(CSSharedControlService *)sharedControlService;

/**
 * Occurs when the shared control link with the controllable endpoint is established and a user can control
 * the desk phone now.
 * This is typically when the RegisterApplicationResponse is received from the desk phone.
 *
 * @param sharedControlService service which sent notification.
 * @param endpoint connected endpoint.
 */
- (void)sharedControlService:(CSSharedControlService *)sharedControlService
		didConnectToEndpoint:(CSControllableEndpoint *)endpoint;

/**
 * Occurs when the shared control link with the controllable endpoint is ended gracefully or down because of network issues.
 *
 * @param sharedControlService service which sent notification.
 * @param endpoint disconnected endpoint.
 * @param error error description if disconnect is result of error.
 */
-(void)sharedControlService:(CSSharedControlService *)sharedControlService
  didDisconnectFromEndpoint:(CSControllableEndpoint *)endpoint
				  withError:(NSError *)error;

/**
 * Occurs when shared control link with the controllable endpoint could not be setup.
 * This is typically when the shared control link cannot be setup with the controlled endpoint
 * due to various reasons.
 *
 * @param sharedControlService service which sent notification.
 * @param endpoint endpoint for which setup has failed.
 * @param error error object describing a problem.
 */
-(void)sharedControlService:(CSSharedControlService *)sharedControlService
 didFailToConnectToEndpoint:(CSControllableEndpoint *)endpoint
				  withError:(NSError *)error;

@end

/**
 * This service provides the user with the ability to direct media to the Desk Phone (Hard Phone)
 * while issuing signaling commands from the Desk Phone and/or the client.
 * Access to the shared control service is provided by the SharedControlService property on the {@link CSUser} class.
 * A Spark based shared signalling channel is established between the controlling client (soft client)
 * and the controlled device (Desk Phone) through the Aura Session Manager, to keep call states in sync
 * and communicate signaling messages.
 * The Shared Control mechanism is a first party control mechanism similar to the CTI interface traditionally 
 * provided on Windows PCs except that the controlling and controlled endpoints are endpoints registered with
 * Avaya Aura.
 * This feature has two main entities:
 * @li @c @b Controlled Endpoint/Client/Device - Avaya endpoints that support the shared control mechanism advertise their support by inserting "avaya-sc-enabled"
 * tag in the contact URI they register. The clients are currently not planned to be controlled endpoints.
 * @li @c @b Controlling Endpoint/Client - when a user chooses to run the client in the shared control mode, the application does not receive incoming calls
 * from the server but from the controlled endpoint instead. This is done so that all incoming and outgoing requests
 * are sent over to the endpoint that is “actively” registered with Aura (the desk phone) and receives incoming calls.
 * The client always acts as a controlling endpoint.
 *
 * @attention Following are the current limitations in Shared Control:
 * @li @c Currently only SIP mode is supported for Shared Control.
 * @li @c Currently SM is the only Avaya registrar that supports the registration in Shared Control.
 * @li @c Currently only Avaya 96x1 desk phones and Summit (H175) series are supported for Shared Control.
 * @li @c The server addresses list on the controlling and controlled endpoints should be identical to avoid registration issues.
 * @li @c Split media i.e.audio on controlled endpoint and video on controlling endpoint is only supported with Summit (H175) phones.
 * @li @c The controlled endpoint supports only one controlling endpoint in Shared Control. The latest controlling endpoint
 *   initiating the session controls the controlled endpoint. For instance: if UC client - 1 is in Shared Control with
 *   controlled endpoint, and UC client - 2 initiates Shared Control with same controlled endpoint,
 *   the session with client - 1 is ended by controlled endpoint.
 */
@interface CSSharedControlService : NSObject

/**
 * Notifications about available endpoints and connection state changes.
 */
@property(nonatomic, weak) id<CSSharedControlDelegate> sharedControlDelegate;

/**
 * Activates the shared control service.

 * @param endpoint The controllable endpoint to be used in shared control.
 * @param completionHandler A block to be called when the operation is completed. Method will do nothing if the block is nil. 
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 * @note Local calls will be destroyed when system in the activating shared control link state.
 *             Switching from This Computer mode to Desk Phone Mode - if a user wants to
 *             continue the call, a user can bridge - on to that call from the desk phone before switching
 *             since MDA is ON and the "Max. Simultaneous Devices" setting is set to 2 (for Shared Control).

 */
- (void)activateSharedControlWithControllableEndpoint:(CSControllableEndpoint *)endpoint completionHandler:(void(^)(NSError *error))completionHandler;

/**
 * Deactivates the shared control service.

 * @param completionHandler A block to be called when the operation is completed. Method will do nothing if the block is nil.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @note Local calls will be destroyed when the system in the deactivating shared control link state.
 *             Switching from Desk Phone mode to This Computer mode i.e. deactivating 
 *             the shared control service - any soft client calls are lost, but the call stays up
 *             on the controlled device. As soon as the soft client successfully switches to 
 *             This Computer, a user can bridge on to the call by joining, essentially have
 *             audio coming into the soft client since MDA is ON and the "Max. Simultaneous Devices" setting is set to 2.
 */
- (void)deactivateSharedControlWithCompletionHandler:(void(^)(NSError *error))completionHandler;

@end
