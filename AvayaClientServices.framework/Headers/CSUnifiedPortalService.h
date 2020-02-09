/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSUnifiedPortalConfiguration.h"
#import "CSUnifiedPortalResources.h"
#import "CSUnifiedPortalMeetingInfo.h"
#import "CSUnifiedPortalConferencingConfiguration.h"

@protocol CSUnifiedPortalServiceDelegate;

typedef void (^GetResourcesCompletionHandler)(CSUnifiedPortalResources *resources, NSString *portalUserToken, NSDate *portalUserTokenExpirationTime, CSUnifiedPortalConferencingConfiguration *conferencingConfiguration, NSError *error);
typedef void (^RequestToJoinMeetingCompletionHandler)(CSUnifiedPortalMeetingInfo *meetingInfo, NSError *error);
typedef void (^GetPortalUserTokenCompletionHandler)(NSString *portalUserToken, NSDate *portalUserTokenExpirationTime, NSError *error);
typedef void (^SendClientInfoCompletionHandler)(NSError *error);

/**
 * The UnifiedPortalService provides access to Unified Portal features.
 */
@interface CSUnifiedPortalService : NSObject

/**
 * The delegate responsible for handling unified portal service related events.
 */
@property (nonatomic, weak) id<CSUnifiedPortalServiceDelegate> delegate;

/**
 * Returns YES if the Unified Portal service is available.
 * @return YES if the Unified Portal service is available.
 */
@property (nonatomic, readonly) BOOL serviceAvailable;

/**
 * Get the Unified Portal resources.
 * @param unifiedPortalConfiguration Server configuration that will be used for this request.
 * @param handler The completion handler for this operation.
 */
-(void)getResourcesWithConfiguration:(CSUnifiedPortalConfiguration *) unifiedPortalConfiguration
				   completionHandler:(GetResourcesCompletionHandler) handler;

/**
 * Get the Unified Portal resources.
 * @param unifiedPortalConfiguration Server configuration that will be used for this request.
 * @param conferenceId The optional conference virtual room number used by Unified Portal for proper tenant selection. May be null.
 * @param handler The completion handler for this operation.
 */
-(void)getResourcesWithConfiguration:(CSUnifiedPortalConfiguration *) unifiedPortalConfiguration
				   conferenceId:(NSString *)conferenceId
				   completionHandler:(GetResourcesCompletionHandler) handler;

/**
 * Request to join Meet-me conference.
 * If successful, the meeting info will be provided via completion handler.
 * @param unifiedPortalConfiguration Server configuration that will be used for this request.
 * @param conferenceId The conference virtual room number to join.
 * @param meetMeUserName The user display name. Mandatory when joining the meeting as guest.
 * @param isPresentationOnlyMode When set to true, join the meeting in presentation only mode.
 * @param callBackNumber The conference server will call back to this number when joining the meeting in presentation only mode.
 * @param oneTimePin One time PIN. Mandatory when virtual room is one time PIN protected. Virtual room owner shall create and provide one time PIN to start the meeting. Non-owners shall provide one time PIN to join the meeting.
 * @param handler The completion handler for this operation.
 */
-(void)requestToJoinMeetingWithConfiguration:(CSUnifiedPortalConfiguration *)unifiedPortalConfiguration
								conferenceId:(NSString *)conferenceId
									userName:(NSString *)meetMeUserName
						presentationOnlyMode:(BOOL) isPresentationOnlyMode
							  callbackNumber:(NSString *)callBackNumber
								  oneTimePin:(NSString *)oneTimePin
						   completionHandler:(RequestToJoinMeetingCompletionHandler)handler;

/**
 * Get the Portal user token.
 * @param unifiedPortalConfiguration Server configuration that will be used for this request.
 * @param handler The completion handler for this operation.
 */
-(void)getPortalUserTokenWithConfiguration:(CSUnifiedPortalConfiguration *) unifiedPortalConfiguration
				   completionHandler:(GetPortalUserTokenCompletionHandler)handler;

/**
 * Get the Portal user token.
 * @param unifiedPortalConfiguration Server configuration that will be used for this request.
 * @param conferenceId The optional conference virtual room number used by Unified Portal for proper tenant selection. May be null.
 * @param handler The completion handler for this operation.
 */
-(void)getPortalUserTokenWithConfiguration:(CSUnifiedPortalConfiguration *) unifiedPortalConfiguration
				   conferenceId:(NSString *)conferenceId
				   completionHandler:(GetPortalUserTokenCompletionHandler)handler;

/**
 * Send client info to Unified Portal.
 * Used by desktop clients which are launched by portal and receive client detection session id for sending client information back to portal.
 * @param unifiedPortalConfiguration Server configuration that will be used for this request.
 * @param clientSessionId The session id passed by portal to client.
 * @param clientInfo String-serialized client info. Passed to the portal as is, without any preprocessing.
 * @param handler The completion handler for this operation.
 */
-(void)sendClientInfoWithConfiguration:(CSUnifiedPortalConfiguration *) unifiedPortalConfiguration
				   clientSessionId:(NSString *)clientSessionId
				   clientInfo:(NSString *)clientInfo
				   completionHandler:(SendClientInfoCompletionHandler)handler;

@end

@protocol CSUnifiedPortalServiceDelegate <NSObject>

/**
 * Called when the Unified Portal service becomes available.
 *
 * @param unifiedPortalService The Unified Portal service associated with the callback.
 */
- (void)unifiedPortalServiceDidBecomeAvailable:(CSUnifiedPortalService *)unifiedPortalService;

/**
 * Called when the Unified Portal service becomes unavailable.
 *
 * @param unifiedPortalService The Unified Portal service associated with the callback.
 */
- (void)unifiedPortalServiceDidBecomeUnavailable:(CSUnifiedPortalService *)unifiedPortalService;

@end
