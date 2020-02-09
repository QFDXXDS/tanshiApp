/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCollaboration.h"

@class CSCall;

@protocol CSCollaborationServiceDelegate;

/**
 * The CSCollaborationService object provides service for creating and removing CSCollaboration objects.
 *
 * Status updates of CSCollaborationService are reported through the CSCollaborationServiceDelegate object.
 *
 * @see CSCollaborationServiceDelegate
 */
@interface CSCollaborationService : NSObject

/**
 * The delegate used to handle updates of CSCollaborationService.
 */
@property (nonatomic, weak) id<CSCollaborationServiceDelegate> delegate;

/**
 * Indicates whether there is an active collaboration in progress
 */
@property (nonatomic, readonly) BOOL hasActiveCollaboration;

/**
 * Creates a new collaboration session from collaboration URL and collaboration code
 *
 * @param collaborationURL URL of collaboration
 * @param collaborationCode Code for collaboration
 * @param passcode Passcode for collaboration
 * @param guestName Optional guest name for collaboration
 * @param handler Block to be called when the operation is completed.
 *		  @li @c collab If the operation was successful this parameter contains created  CSCollaboration object
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (CSCollaboration *)createCollaborationWithCollaborationURL:(NSString *)collaborationURL
										   collaborationCode:(NSString *)collaborationCode
													passcode:(NSString *)passcode
												   guestName:(NSString *)guestName
										   completionHandler:(void (^)(CSCollaboration *collab, NSError *error)) handler;

/**
 * Creates a new collaboration session based on the input collaboration session URI.
 * This method is used by endpoints such as the Equinox Conferencing room system endpoints
 * that independently and programmatically obtain the complete web collaboration URI
 * from the conference server without using the call creation services provided by the SDK.
 * It is the application's responsibility to make sure that all of the parameters
 * required to connect to the web collaboration server are provided in collaborationURL.
 * Otherwise collaboration creation process will fail.
 *
 * @param webConferenceURI Complete collaboration session URI including all of the parameters
 * required to set up a web collaboration connection.
 * @param handler Block to be called when the operation is completed.
 *    @li @c collaboration If the operation was successful this parameter contains created CSCollaboration object
 *    @li @c error If the operation was successful this parameter is nil. If an error occurred it contains an object describing the error.
 */
- (void)createCollaborationWithWebConferenceURI:(NSURL *)webConferenceURI
							  completionHandler:(void (^)(CSCollaboration *collaboration, NSError *error)) handler;

/**
 * Creates a new collaboration session for the given call.
 * Returns empty pointer if the call is not a conference or it already has a collaboration.
 * Otherwise returns the pointer to the uninitialized collaboration object and starts process
 * of collaboration creation.
 *
 * @param call Call for which the collaboration session is created
 * @param handler Block to be called when the operation is completed.
 *		  @li @c collab If the operation was successful this parameter contains created  CSCollaboration object
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (CSCollaboration *)createCollaborationForCall: (CSCall *)call
						  withCompletionHandler: (void (^)(CSCollaboration *collab, NSError *error))handler;

@end

/**
 * CSCollaborationServiceDelegate is registered as an observer of CSCollaborationService status update notifications.
 *
 * The client application is notified about status updates reported by the collaboration server
 * through the CSCollaborationServiceDelegate object.
 *
 * @see CSCollaborationService
 */
@protocol CSCollaborationServiceDelegate <NSObject>

/**
 * Reports that CSCollaboration object was created automatically.
 *
 * @param collabService Collaboration service which created collaboration.
 * @param collab CSCollaboration object which has been created.
 */
- (void)collaborationService:(CSCollaborationService *)collabService didCreateCollaboration:(CSCollaboration *)collab;

/**
 * Reports that CSCollaboration object was removed after ended collaboration call.
 *
 * @param collabService Collaboration service which removed collaboration.
 * @param collab CSCollaboration object which has been removed.
 */
- (void)collaborationService:(CSCollaborationService *)collabService didRemoveCollaboration:(CSCollaboration *)collab;

@optional

/**
 * Reports that an error occurred during automatic creation of the collaboration.
 *
 * @param collabService   Collaboration service which failed to create new collaboration.
 * @param error           Object containing failure information.
 */
- (void)collaborationService:(CSCollaborationService *)collabService didFailToCreateCollaborationWithError:(NSError *)error;

@end
