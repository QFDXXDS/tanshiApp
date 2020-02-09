/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, CSCallType)
{
	CSCallTypeDefaultRegisteredService = 0,
	CSCallTypeHttpMeetme,
	CSCallTypeHttpGuestWithAuthorizationToken
};

@interface CSCallCreationInfo : NSObject

/**
 * Initialize a call creation info with remote call arguments. Can be used if application needs to create a call using remote call information.
 *
 * @param lineAppearanceId The Avaya lineid for the remote call.
 * @param lineAppearanceOwner The remote call owner name.
 */
- (instancetype)initWithLineAppearanceId:(NSInteger)lineAppearanceId lineAppearanceOwner:(NSString *)lineAppearanceOwner;

/**
 * Initialize a call creation info with remote call arguments. Can be used if application needs to create a conference call using remote call
 * information.
 *
 * @param conferenceId The Virtual Room id to identify the conference room that will be used if we make the call to Conference system.
 * @param conferencePasscode The Virtual Room PIN to identify the conference room.
 * @param portalToken Correlation-token provided by Scopia/Portal to correlate Portal session with SIP Signalling.
 */
- (instancetype)initWithConferenceId:(NSString *)conferenceId conferencePasscode:(NSString *)conferencePasscode portalToken:(NSString *)portalToken;


/**
 * Initialize a MeetMe conference call creation info with with conference related arguments. Can be used if application needs to create a MeetMe call using remote Conferencing platform.
 *
 * @param conferenceId The Virtual Room id to identify the conference room that will be used if we make the call to Conference system.
 * @param conferencePasscode The Virtual Room PIN to identify the conference room.
 * @param portalToken Conference correlation token provided by Scopia/Portal.
 * @param uccpURL The URL to establish UCCP connection to the conference server.
 * @param serviceGatewayURL The Service Gateway URL to establish HTTP connection to the server.
 * @param portalURL The Unified Portal Server URL. Required for redial capability.
 * @param meetMeUserName The user display name to represent user in MeetMe calls.
 * @param remoteAddress The remote address.
 * @param presentationOnlyMode Presentation only mode
 */
-(instancetype)initMeetMeCallWithConferenceId:(NSString *)conferenceId
						   conferencePasscode:(NSString *)conferencePasscode
								  portalToken:(NSString *)portalToken
									  uccpURL:(NSURL *)uccpURL
							serviceGatewayURL:(NSURL *)serviceGatewayURL
									portalURL:(NSURL *)portalURL
							   meetMeUserName:(NSString *)meetMeUserName
								remoteAddress:(NSString *)remoteAddress
						 presentationOnlyMode:(BOOL)presentationOnlyMode;

/**
 * Initialize guest user creation call information where user is allowed to
 * make a single call using the provided authorization token. The one time 
 * call creation with the authorization token is used in Avaya contact center environment
 * where a user with mobile client can initiate a web based call towards contact center.
 * Currently, this method of placing calls is not used in non-contact center environments.
 * @param authorizationToken Authorization token needed to initiate the one-time call. The token is used
 *        by the service gateway to determine whether the call should be allowed to proceed or not.
 * @param serviceGatewayURL The Service Gateway URL to establish HTTP connection to the server.
 * @param contextId Opaque data representing the id of contextual data stored in the 
 *        contact center solution that is associated with this call.
 * @param remoteAddress Called party information. In the contact center solution, this can be
 *        a "vector directory number" (VDN) towards the contact center application, or the contact
 *        center agent's direct phone number. The use of this parameter is optional. Depending on the
 *        contact center solution, the remote number may not be needed if the remote number is implicitly 
 *        associated with the authorization token on the service gateway side. When the remote number 
 *        is associated with the token, this parameter should be nil.
 */

-(instancetype)initWithAuthorizationToken:(NSString *)authorizationToken
						serviceGatewayURL:(NSURL *)serviceGatewayURL
								contextId:(NSString *)contextId
							remoteAddress:(NSString *)remoteAddress;

/**
 * The Avaya lineid for the remote call.
 */
@property (nonatomic) NSInteger lineAppearanceId;

/**
 * The remote call owner name.
 */
@property (nonatomic, copy) NSString *lineAppearanceOwner;

/**
 * The remote address for this call.
 *
 * when making call with line appearance id, this value must be set.
 */
@property (nonatomic, copy) NSString *remoteAddress;

/**
 * A Boolean value indicating whether any configured dialing rules should be
 * applied to the remote address before dialing.
 *
 * The default value of this property is @c YES.
 *
 * @see CSUserConfiguration::dialingRulesConfiguration
 */
@property (nonatomic) BOOL applyDialingRules;

/**
 * The Virtual Room id to identify the conference room that will be used if we make the call to Conference system.
 */
@property (nonatomic, copy) NSString *conferenceId;

/**
 * The Virtual Room PIN to identify the conference room.
 */
@property (nonatomic, copy) NSString *conferencePasscode;

/**
 * Correlation-token provided by Scopia/Portal to correlate Portal session with SIP Signalling.
 */
@property (nonatomic, copy) NSString *portalToken;

/**
 * The URL to establish UCCP connection to the conference server.
 * This allows client UI to establish conference in presentation only mode through UCCP web socket connection.
 */
@property (nonatomic, copy) NSURL *uccpURL;

/**
 * A Boolean value indicating whether the call should be created in presentation only mode.
 */
@property (nonatomic, getter=isPresentationOnlyMode) BOOL presentationOnlyMode;

/**
 * Indicates whether or not off-hook dialing will be used to specify the remote
 * address.
 *
 * Off-hook dialing is used to support the user experience of a traditional desk
 * telephone where the handset is lifted (goes off-hook) and the user enters the
 * digits to dial via a dialpad. In this mode the remote address is not
 * specified before -[CSCall start] is called and digits are entered via
 * -[CSCall addRemoteAddressDigit:] as the user enters them in the UI. When a
 * match against the call server's dial plan is found the call will be
 * automatically initiated.
 */
@property (nonatomic, getter=isOffHookDialingEnabled) BOOL offHookDialingEnabled;

/**
 * Enum value indicating whether default registered service (SIP call through Aura) or a Meetme call through Service gateway is to be created
 **/
@property (nonatomic) CSCallType callType;

/**
 * Service Gateway (ESG) URL
 */
@property (nonatomic, copy) NSURL *serviceGatewayURL;

/**
 * User name used for meetme conference creation
 */
@property (nonatomic, copy) NSString *meetmeUserName;

/**
 * The Unified portal Service URL
 */
@property (nonatomic, copy) NSURL *portalURL;

/**
 * Authorization token needed to initiate the call. Used by the service gateway to 
 * determine whether the call should be allowed to proceed or not.
 */
@property (nonatomic, copy) NSString *authorizationToken;

/**
 * Opaque data representing the id of contextual data stored in the contact center solution 
 * that is associated with this call.
 */
@property (nonatomic, copy) NSString *contextId;

@end
