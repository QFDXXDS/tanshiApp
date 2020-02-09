/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCallCreationInfo.h"
#import "CSVideoMode.h"

@class CSCall;
@class CSCapability;
@protocol CSCallServiceDelegate;

/**
 * Service for creating and receiving audio/video calls.
 */
@interface CSCallService : NSObject

/**
 * The delegate responsible for handling call events.
 */
@property (nonatomic, weak) id<CSCallServiceDelegate> delegate;

/**
 * A Boolean value indicating whether there is a call in initiating state.
 * @return @c YES if there is at least one call initiated but not
 * yet established, @c NO otherwise.
 */
@property (nonatomic, readonly) BOOL hasInitiatingCall;

/**
 * A Boolean value indicating whether there is a call in held state.
 */
@property (nonatomic, readonly) BOOL hasHeldCall;

/**
 * Gets CSCapability object indicating whether the video is allowed.
 * video capability is calculated based on license, user configuration and available network.
 */
@property (nonatomic, readonly) CSCapability *videoCapability;

/**
 * Gets CSCapability object indicating whether the VoIP calling is allowed.
 * VoIP calling capability is calculated based on user configuration and available network.
 */
@property(nonatomic, readonly) CSCapability *voipCallingCapability;

/**
 * A Boolean value indicating whether auto-answer is administered.
 *
 * This information is used to indicate how the client will behave when an incoming call is received.
 *
 * Do not use this information to determine if an incoming call should be answered automatically by your
 * client. Instead use the call.canAutoAnswer property for that purpose.
 *
 * NOTE: The SDK never auto-answers a call, we simply provide info indicating whether the call can be 
 * auto-answered. It's up to the client to act on this info and automatically answer the call.
 * @return true if auto-answer is administered.
 */
@property (nonatomic, readonly, getter=isAutoAnswerAdministered) BOOL autoAnswerAdministered;

/**
 * Gets information about the line appearances.
 * @return An NSArray of CSLineAppearance objects.
 */
@property (nonatomic, readonly) NSArray *lineAppearances;

/**
 * Gets information about the emergency numbers.
 * @return An NSArray of strings.
 */
@property (nonatomic, readonly) NSArray *emergencyNumbers;

/**
 * Creates a new outgoing call.
 * @return Creates a new outgoing call.
 */
- (CSCall *)createCall;

/**
 * Creates a new outgoing call with information provided in the input argument.
 *
 * @param callCreationInfo Call creation information
 * @return Creates a new outgoing call on bridge line.
 */
-(CSCall *)createCallWithInfo:(CSCallCreationInfo *)callCreationInfo;

/**
 * Get current locally established active call.
 * An active call is local and in established state.
 * The active call is null if there is no call or all local calls are in held state.
 * @return The new active call if exist otherwise nil.
 */

@property (nonatomic,readonly) CSCall *activeCall;

/**
 * Returns the list of calls that are currently in the ignored stated.
 */
- (NSArray *)ignoredCalls;

/**
 * @return the calls that are in progress.
 */
- (NSArray *)calls;

/**
* Apply dialing rules . It is used for applying dialing rules outside of the call service (e.g ec500 calls)
* @param inputNumber to which dialing rules logic needs to be applied.
* @return A number that can be dialed or the number as is if the number is not valid or cannot be transformed.
*/
- (NSString *)applyDialingRulesForEC500:(NSString *)inputNumber;

/**
 * Gets CSCapability object indicating whether the video is allowed for specific call type. 
 * For each call type video capability is calculated based on license, user configuration and available network.
 * @param callType the call type.
 * @return CSCapability object indicating whether the video is allowed.
 */
- (CSCapability*)videoCapabilityForCallType:(CSCallType)callType;

/**
 * Gets CSCapability object indicating whether the VoIP calling is allowed for specific call type.
 * For each call type VoIP calling capability is calculated based on user configuration and available network.
 * @param callType the call type.
 * @return CSCapability object indicating whether the VoIP calling is allowed.
 */
- (CSCapability*)voipCallingCapabilityForCallType:(CSCallType)callType;
@end

/**
 * Describes methods that are implemented by the delegate of a @c CSCallService.
 */
@protocol CSCallServiceDelegate <NSObject>

/**
 * Sent when an incoming call is received.
 *
 * @param callService The call service sending the message.
 * @param call The incoming call.
 */
- (void)callService:(CSCallService *)callService didReceiveIncomingCall:(CSCall *)call;

/**
 * Sent when a call is created.
 *
 * @param callService The call service sending the message.
 * @param call The created call.
 */
- (void)callService:(CSCallService *)callService didCreateCall:(CSCall *)call;

/**
 * Sent when the user is informed of an incoming call that was not delivered to
 * the local application due to an active server feature, such as call
 * forwarding or send all calls. If desired the application can use the
 * information in this session object to update its call history records. Since
 * the session is already ended no further events will be sent for it.
 *
 * @param callService The call service sending the message.
 * @param call The undelivered call.
 */
- (void)callService:(CSCallService *)callService didReceiveNotificationOfUndeliveredIncomingCall:(CSCall *)call;

/**
 * Sent when a call previously associated with the call service has been
 * removed.
 *
 * @param callService The call service sending the message.
 * @param call The removed call.
 */
- (void)callService:(CSCallService *)callService didRemoveCall:(CSCall *)call;

/**
 * Sent when the service's capabilties have changed. e.g VideoCapability, VoIPCallingCapability.
 *
 * @param callService The call service sending the message.
 */
- (void)callServiceDidChangeCapabilities:(CSCallService *)callService;

/**
 * Sent when a there is change in active call.
 * An active call is local and in established state.
 * The active call is null if there is no call, or all local calls are in held state.
 * @param callService The call service sending the message.
 * @param call new call, or null if there is no active call
 */
- (void)callService:(CSCallService *)callService didChangeActiveCall:(CSCall *)call;

/**
 * Called to report the receipt of a CTI call request informing the local client that a
 * new video call should be started with the specified video direction.
 * It should be noted that video call start requires the client application
 * initialize video resources such a video rendering view and a camera, which is why
 * this callback is required to be handled by the application in order to complete
 * the call setup.
 * This callback is not reported for an incoming audio call creation request, as
 * the audio call creation request is automatically handled by the Client SDK, 
 * using the user-selected (or default) microphone and playback devices. 
 * If the incoming video call request is for a bidirectional video call, but the 
 * local camera device cannot be initialized, the client application should proceed
 * with establishing a receive-only video call by first calling
 * call.setVideoMode(CSVideoModeReceiveOnly), and then call.start(). 
 * If, for some reason, the client application is unable to create a receive-only 
 * video call, it should proceed with creating an audio-only call, by first calling
 * call.setVideoMode(CSVideoModeDisable), and then call.start().
 * Failure to create a call will result in timeout of the network request and 
 * will cause call setup failure at the network based CTI application.
 * @param callService The call service sending the message.
 * @param call Outgoing call on which start() should be called after UI video resources are initialized.
 * @param videoMode Required video mode/direction. Used to initialize the UI video resources.
 */

- (void)callService:(CSCallService *)callService didReceiveRequestToStartCall:(CSCall *)call withVideoMode:(CSVideoMode)videoMode;

/**
 * Called to report the receipt of a CTI call request informing the local client that an
 * incoming video call should be accepted with the specified video direction.
 * It should be noted that video call answering requires the client application
 * initialize video resources such a video rendering view and a camera, which is why
 * this callback is required to be handled by the application in order to complete
 * the call setup.
 * This callback is not reported for handling answering of an incoming audio call 
 * request, as the audio call request is automatically handled by the Client SDK 
 * using the user-selected (or default) microphone and playback devices. 
 * For video calls, because the video rendering surface is directly under the client 
 * application's control, answering of an incoming video call request cannot 
 * be automatically handled by the Client SDK.
 * If the answer call request is for a bidirectional video, but the 
 * local camera device cannot be initialized, the client application should proceed
 * with establishing a receive-only video call by first calling
 * call.setVideoMode(CSVideoModeReceiveOnly), and then calling call.accept(). 
 * If, for some reason, the client application is unable to answer the call with 
 * receive-only video, it should proceed with answering the call with audio-only, 
 * by first calling call.setVideoMode(CSVideoModeDisable), and then call.accept().
 * Failure to answer the incoming call in a timely fashion will result in timeout 
 * of the network request and call setup failure.
 * @param callService The call service sending the message.
 * @param call Incoming call on which accept() should be called after UI video resources are initialized.
 * @param videoMode Required video mode/direction. Used to initialize the UI video resources.
 */

- (void)callService:(CSCallService *)callService didReceiveRequestToAcceptCall:(CSCall *)call withVideoMode:(CSVideoMode)videoMode;

@end
