/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCapability.h"
#import "CSContentSharing.h"
#import "CSChat.h"
#import "CSMeetingMinutes.h"
#import "CSLibraryManager.h"
#import "CSLibrarySharing.h"
#import "CSWhiteboard.h"
#import "CSCollaborationCapabilities.h"
#import "CSCollaborationDetails.h"
#import "CSSlider.h"

/**
 * Defines the different types of collaboration renderer that the client application
 * needs to create to display collaboration content.
 */
typedef NS_ENUM(NSUInteger, CSCollaborationRenderType)
{
	/**
	 * The presented content is provided via Avaya web conferencing protocol.
	 */
	CSCollaborationRenderTypeWebBased,
	/**
	 * The presented content is provided through a real-time video stream, controlled
	 * by binary floor control protocol (BFCP).
	 */
	CSCollaborationRenderTypeVideoStreamBased,
	/**
	 * The collaboration is not available at this moment.
	 */
	CSCollaborationRenderTypeRendererNotAllowed
};

/**
 * @brief Delegate used to report that receiving sharing control operation finished.
 *
 * Nil if operation succeeded, not nil otherwise.
 *
 * @param error Error information.
 */
typedef void (^CSReceivingSharingControlCompletionHandler)(NSError *error);

@protocol CSCollaborationDelegate;

/**
 * The CSCollaboration object provides access to collaboration related capabilities and actions.
 *
 * The CSCollaboration object is accessible via CSCollaborationService and
 * provides a set of APIs that allow application developers to access different features
 * and services provided by Avaya's various collaboration solutions.
 *
 * In general, the capabilities and the set of allowed operations
 * are not only dependent on the capabilities of the conferencing server,
 * but also on the specific privileges assigned to the local user
 * on the collaboration call. The local user may have moderator and/or presenter capabilities.
 * Status updates concerning collaboration are reported
 * through the CSCollaborationDelegate object.
 *
 * @see CSCollaborationDelegate
 */

@interface CSCollaboration : NSObject

/**
 * The delegate used to handle collaboration-related events.
 */
@property (nonatomic, weak) id<CSCollaborationDelegate> delegate;

/**
 * The collaboration ID associated with the particular collaboration object.
 */
@property (nonatomic, readonly) NSUInteger collaborationId;

/**
 * The call ID associated with the particular collaboration object.
 *
 * @see CSCall
 */
@property (nonatomic, readonly) NSInteger callId;

/**
 * CSCapability object indicating whether collaboration supports content sharing.
 *
 * @see CSContentSharing
 */
@property (nonatomic, readonly) CSCapability *contentSharingCapability;

/**
 * CSContentSharing object associated with the collaboration.
 *
 * CSContentSharing object provides set of APIs which allow to access different
 * features concerning receiving and sharing content.
 */
@property (nonatomic, readonly) CSContentSharing *contentSharing;

/**
 * CSCapability object indicating whether in-conference chat is supported.
 * Object accessible also via CSConference. For more information see CSConference::inConferenceChat
 *
 * @see CSConference::inConferenceChat
 */
@property (nonatomic, readonly) CSCapability *chatCapability;

/**
 * CSChat object associated with the collaboration.
 *
 * CSChat object can be used to query for list of messages or send a new message.
 * Object accessible also via CSConference
 *
 * @see CSConference::inConferenceChat
 */
@property (nonatomic, readonly) CSChat *chat;

/**
 * CSCapability object indicating whether collaboration call supports meeting minutes.
 * Object accessible also via CSConference. For more information see CSConference::inConferenceChat
 
 * @see CSConference::meetingMinutesCapability
 * @see CSMeetingMinutes
 */
@property (nonatomic, readonly) CSCapability *meetingMinutesCapability;

/**
 * CSMeetingMinutes object associated with the conference call.
 *
 * CSMeetingMinutes object can be used to query for list of minutes or to
 * add a new minute, or edit or remove an existing minute.
 * Object accessible also via CSConference.
 *
 * @see CSConference::meetingMinutes
 */
@property (nonatomic, readonly) CSMeetingMinutes *meetingMinutes;

/**
 * CSCapability object indicating whether collaboration call supports network library.
 *
 * @see CSLibraryManager
 */
@property (nonatomic, readonly) CSCapability *networkLibraryCapability;

/**
 * CSLibraryManager object associated with the collaboration.
 *
 * CSLibraryManager object provides set of APIs which allow to access different
 * features concerning network library management.
 *
 * @see networkLibraryCapability.
 */
@property (nonatomic, readonly) CSLibraryManager *libraryManager;

/**
 * CSCapability object indicating whether collaboration call supports library sharing.
 *
 * @see CSLibraryManager
 */
@property (nonatomic, readonly) CSCapability *librarySharingCapability;

/**
 * CSLibraryManager object provides set of APIs which allow to access different
 * features concerning library sharing.
 */
@property (nonatomic, readonly) CSLibrarySharing *librarySharing;

/**
 * {@link CSCapability} object indicating whether whiteboard sharing can be started by local participant.
 *
 * Note that {@link CSWhiteboardDelegate} delegate added to {@link CSWhiteboard} object may still receive messages
 * even if this capability is not allowed. E.g. if local user does not have the required permissions
 * to start whiteboard sharing, but it was started by another collaboration participant.
 *
 * @see CSWhiteboard
 */
@property (nonatomic, readonly) CSCapability *whiteboardCapability;

/**
 * CSWhiteboard object associated with the collaboration.
 *
 * CSWhiteboard object provides set of APIs which allow to access different
 * features concerning receiving and sharing whiteboard.
 */
@property (nonatomic, readonly) CSWhiteboard *whiteboard;

/**
 * @brief Returns CSCapability object indicating whether the slider feature is available.
 *
 * The capability is:
 *
 * - CSCapabilityNotSupported if slider is not supported by this collaboration instance.
 * - CSCapabilityInvalidState before the collaboration is started or after it has ended.
 * - CSCapabilityNetworkUnavailable if slider is temporarily unavailable due to connection loss.
 * - CSCapabilityNotDenied otherwise.
 *
 * @see CSSlider
 */
@property (nonatomic, readonly) CSCapability *sliderCapability;

/**
 * @brief Returns CSSlider object associated with the collaboration.
 *
 * Shall not be nil.
 */
@property (nonatomic, readonly) CSSlider *slider;

/**
 * CSCapability object indicating whether the conference call can be queried to
 * get the list of conference participants. Object accessible also via CSConference.
 * For more information see ::CSConference::retrieveParticipantListCapability.
 *
 * @see CSConference::retrieveParticipantListCapability
 */
@property (nonatomic, readonly) CSCapability *retrieveParticipantListCapability;

/**
 * A Boolean value indicating whether all starting events coming from server 
 * have been processed or, another words, when local collaboration state is
 * synchronized with server.
 */
@property (nonatomic, readonly) BOOL initialized;

/**
 * Indicates whether the current collaboration user has presenter privileges.
 * Collaboration participant can be promoted to presenter. In panel mode conference
 * all users are presenters.
 */
@property (nonatomic, readonly) BOOL hasPresenterPrivilege;

/**
 * Indicates whether the current collaboration user has moderator privileges.
 * Collaboration participant can be promoted to moderator but the original moderator
 * loses moderator control.
 */
@property (nonatomic, readonly) BOOL hasModeratorPrivilege;

/**
 * Indicates that the current user was ejected from the collaboration by the moderator.
 */
@property (nonatomic, readonly, getter=isEjected) BOOL ejected;

/**
 * CSCollaborationCapabilities object containing set of collaboration capabilities
 */
@property (nonatomic, readonly) CSCollaborationCapabilities *capabilities;

/**
 * Returns the type of renderer. Client may use this information to create proper renderer
 * to display collaboration content.
 */
@property (nonatomic, readonly) CSCollaborationRenderType collaborationRenderType;

/**
 * Returns true if receiving sharing is paused.
 *
 * Initially set to false.
 *
 * Changes to true after a call to the ::CSCollaboration::pauseReceivingSharingWithCompletionHandler:
 * method succeeds. Changes to false again after a subsequent call to the
 * ::CSCollaboration::resumeReceivingSharingWithCompletionHandler: method succeeds.
 *
 * @see receivingSharingControlCapability
 * @see CSCollaboration::pauseReceivingSharingWithCompletionHandler:
 * @see CSCollaboration::resumeReceivingSharingWithCompletionHandler:
 */
@property (nonatomic, readonly) BOOL receivingSharingPaused;

/**
 * @brief Returns CSCapability object indicating whether it is possible to control receiving sharing
 *
 * The capability is:
 *
 * - CSCapabilityNotSupported if control is not supported.
 * - CSCapabilityNetworkUnavailable if control is temporarily unavailable due to connection loss.
 * - CSCapabilityNotDenied otherwise.
 * 
 * @see CSCollaboration::pauseReceivingSharingWithCompletionHandler:
 * @see CSCollaboration::resumeReceivingSharingWithCompletionHandler:
 * @see CSCollaboration::receivingSharingPaused
 */
@property (nonatomic, readonly) CSCapability *receivingSharingControlCapability;

/**
 * Starts the collaboration session with completion handler. Collaboration can not
 * be started twice or during collaboration starting or ending process.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)startWithCompletionHandler:(void (^)(NSError* error))handler;

/**
 * Ends the collaboration session with completion handler. Collaboration can not
 * be ended twice or during collaboration starting or ending process.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)endWithCompletionHandler:(void (^)(NSError* error))handler;

/**
 * Return the participant list associated with the collaboration session. Depending on the capabilities of
 * the collaboration session, the list of participants may not be provided (e.g., when presentation is
 * supported through RTP video stream and not through the web collaboration interface).
 * This method is added to support collaboration only sessions where there is no corresponding audio/video
 * conference call. This method may be called when the collaboration session is
 * associated with a conference call. The call/conference object may be queried to retrieve the
 * full list of participants whereas this method may be used to retrieve the collaboration-only participants.
 * Updates to the participant list (add, remove or update) are reported through the DataSetChangeListener
 * instance registered with the DataSet object.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c participantList If the operation was successful this parameter contains list of collaboration participants.
 */
- (void)getParticipantListWithCompletionHandler:(void (^)(NSDictionary *participantList))handler;

/**
 * Deprecated please use \a acquireCollaborationDetailsWithCompletionHandler: .
 */
- (void)readCollaborationDetailsWithCompletionHandler:(void (^)(CSCollaborationDetails *))handler DEPRECATED_MSG_ATTRIBUTE("Use acquireCollaborationDetailsWithCompletionHandler: instead");

/**
 * Returns the details associated with the collaboration.
 */
- (void)acquireCollaborationDetailsWithCompletionHandler:(void (^)(CSCollaborationDetails *, NSError *))handler;

/**
 * @brief Pauses receiving certain collaboration sharing updates.
 *
 * Currently stops content sharing image updates and whiteboard drawing updates.
 *
 * Can be used to reduce application event-handling workload in situations when sharing
 * does not need to be processed (e.g. sharing-related UI components are hidden).
 *
 * Receiving sharing can be started again with ::CSCollaboration::resumeReceivingSharingWithCompletionHandler: without losing any intermediate data
 * (i.e. the up-to-date content sharing key frame and all whiteboard drawing events will be eventually received).
 *
 * Succeeds if receiving sharing is already paused.
 *
 * @see ::CSCollaboration::resumeReceivingSharingWithCompletionHandler:
 *
 * @param completionHandler Completion handler instance used to report that the operation finished.
 */
- (void)pauseReceivingSharingWithCompletionHandler:(CSReceivingSharingControlCompletionHandler)completionHandler;

/**
 * @brief Resumes receiving certain collaboration sharing updates.
 *
 * Starts receiving sharing updates previously paused by ::CSCollaboration::pauseReceivingSharingWithCompletionHandler:.
 * 
 * Succeeds if receiving sharing is already resumed.
 *
 * @see ::CSCollaboration::pauseReceivingSharingWithCompletionHandler:
 *
 * @param completionHandler Completion handler instance used to report that the operation finished.
 */
- (void)resumeReceivingSharingWithCompletionHandler:(CSReceivingSharingControlCompletionHandler)completionHandler;

@end


/**
 * CSCollaborationDelegate is registered as an observer of collaboration status update notifications.
 *
 * The client application is notified about status updates reported by the collaboration server
 * through the CSCollaborationDelegate object. These updates may be the result of local operations
 * on the CSCollaboration object as well as remote changes initiated by either the server or other
 * users on the collaboration call.
 *
 * @see CSCollaboration
 */
@protocol CSCollaborationDelegate <NSObject>

/**
 * Reports that a collaboration instance has started automatically. Notification
 * is not send after starting collaboration by user. In situation of starting 
 * collaboration explicitly by user he is notified by completion handler.
 *
 * @param collaboration The collaboration sending the message.
 *
 * @see CSCollaboration::startWithCompletionHandler:
 */
- (void)collaborationDidStart:(CSCollaboration *)collaboration;

/**
 * Reports that a collaboration instance and all of its channels
 * (whiteboard, content sharing, library sharing, etc.) has been ended.
 * This notification is not sent when the collaboration is ended by local user.
 * In this case, the local application is notified by the completion handler.
 *
 * @param collaboration The collaboration sending the message.
 *
 * @see CSCollaboration::endWithCompletionHandler:
 */
- (void)collaborationDidEnd:(CSCollaboration *)collaboration;

/**
 * Called when the collaboration session started and became available. Collaboration
 * can become available/unavailable in case of network disruptions within one
 * collaboration call.
 *
 * @param collaboration The collaboration sending the message.
 *
 * @see CSCollaboration::collaborationServiceDidBecomeUnavailable:
 */
- (void)collaborationServiceDidBecomeAvailable:(CSCollaboration *)collaboration;

/**
 * Called when the collaboration session became unavailable due to network disruption.
 * This notification does not indicate that the collaboration session was ended.
 *
 * @param collaboration The collaboration sending the message.
 *
 * @see CSCollaboration::collaborationServiceDidBecomeAvailable:
 */
- (void)collaborationServiceDidBecomeUnavailable:(CSCollaboration *)collaboration;

/**
 * Reports that the collaboration's capabilities have changed.
 *
 * @param collaboration The collaboration sending the message.
 */
- (void)collaborationDidChangeCapabilities:(CSCollaboration *)collaboration;

/**
 * Reports that the local user has been ejected from collaboration.
 *
 * @param collaboration The collaboration sending the message.
 */
- (void)collaborationDidEjectParticipant:(CSCollaboration *)collaboration;

/**
 * Reports that the local user's presenter privilege was changed.
 *
 * @param collaboration The collaboration sending the message.
 */
- (void)collaborationDidChangePresenterPrivilege:(CSCollaboration *)collaboration;

/**
 * Reports that the local user's moderator privilege was changed.
 *
 * @param collaboration The collaboration sending the message.
 */
-(void)collaborationDidChangeModeratorPrivilege:(CSCollaboration *)collaboration;

/**
 * Reports that the collaboration has been initialized - all starting events were processed.
 *
 * @param collaboration The collaboration sending the message.
 *
 * @see CSCollaboration::initialized
 */
-(void)collaborationDidInitialize:(CSCollaboration *)collaboration;

@end
