/* Copyright Avaya Inc. */

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import "CSParticipant.h"
#import "CSCameraControl.h"

@class CSCapability;
@class CSActiveParticipant;

/**
 * Enumeration representing active participant media status.
 */
typedef NS_ENUM(NSUInteger, CSParticipantMediaStatus) {
	/** 
	 * There is no media 
	 */
	CSParticipantMediaNone,
	/**
	 * Media is being sent, but no media is being received. 
	 */
	CSParticipantMediaSendOnly,
	/**
	 * Media is being received, but not sent. 
	 */
	CSParticipantMediaReceiveOnly,
	/** 
	 * Media is being sent and received. 
	 */
	CSParticipantMediaSendReceive,
	/**
	 * Media is being received, but other participant doesn't get media from this participant, because server has blocked it.
	 */
	CSParticipantMediaBlockedByServer,
};

/**
* Enumeration representing active participant connection status.
*/
typedef NS_ENUM(NSUInteger, CSParticipantConnectionStatus) {
	/**
	 * Connection status is not specified.
	 */
	CSParticipantConnectionStatusUnknown,
	/**
	 * Participant is connecting, i.e. either dialing in, or being dialed out towards.
	 */
	CSParticipantConnectionStatusConnecting,
	/**
	 * Participant is in the conference call.
	 */
	CSParticipantConnectionStatusConnected,
	/**
	 * Participant is leaving the conference call, either on his or her own, or forced out by the conference moderator.
	 */
	CSParticipantConnectionStatusDisconnecting,
	/**
	 * Participant left the conference call. This status is only valid for DroppedParticipant object.
	 */
	CSParticipantConnectionStatusDisconnected,
	/**
	 * Participant is being authorized to join the conference call.
	 * A participant may be in "authorizing" state while waiting to be admitted to a locked conference call
	 * or while joining a conference that is passcode protected.
	 * Upon admission to a locked conference call or entering the correct passcode, the participant transitions to connected state.
	 */
	CSParticipantConnectionStatusAuthorizing
};

/**
 * Describes methods that are implemented by the delegate of a @c CSActiveParticipant.
 */
@protocol CSActiveParticipantDelegate <CSParticipantDelegate>

/**
 * Called when the participant's connection status has changed.
 *
 * @param participant Participant whose connection status has changed.
 */
- (void)activeParticipantDidChangeConnectionStatus:(CSActiveParticipant *)participant;

/**
 * Called when the participant's application sharing status has changed.
 *
 * @param participant Participant whose application sharing status has changed.
 */
- (void)activeParticipantDidChangeApplicationSharingStatus:(CSActiveParticipant *)participant;

/**
 * Called when a participant has been designated as a moderator.
 *
 * @param participant Participant who has been designated as a moderator.
 */
- (void)activeParticipantDidAssignAsModerator:(CSActiveParticipant *)participant;

/**
 * Called when a participant is no longer designated as a moderator.
 *
 * @param participant Participant who is no longer designated as a moderator.
 */
- (void)activeParticipantDidUnassignAsModerator:(CSActiveParticipant *)participant;

/**
 * Called when a participant has been designated as a lecturer.
 *
 * @param participant Participant who has been designated as a lecturer.
 */
- (void)activeParticipantDidAssignAsLecturer:(CSActiveParticipant *)participant;

/**
 * Called when a participant is no longer designated as a lecturer.
 *
 * @param participant Participant who is no longer designated as a lecturer.
 */
- (void)activeParticipantDidUnassignAsLecturer:(CSActiveParticipant *)participant;

/**
 * Called when a participant has been designated as a presenter.
 *
 * @param participant Participant whose has been designated as a presenter.
 */
- (void)activeParticipantDidAssignAsPresenter:(CSActiveParticipant *)participant;

/**
 * Called when a participant is no longer designated as a presenter.
 *
 * @param participant Participant who is no longer designated as a presenter.
 */
- (void)activeParticipantDidUnassignAsPresenter:(CSActiveParticipant *)participant;

/**
 * Called to report that a participant's audio has been changed.
 *
 * @param participant Participant whose audio was changed.
 * @param newStatus New audio status.
 */
- (void)activeParticipant: (CSActiveParticipant *)participant didChangeAudioStatus: (CSParticipantMediaStatus)newStatus;

/**
 * Called to report that a participant's video has been changed.
 *
 * @param participant Participant whose video was changed.
 * @param newStatus New audio status.
 */
- (void)activeParticipant: (CSActiveParticipant *)participant didChangeVideoStatus: (CSParticipantMediaStatus)newStatus;

/**
 * Called to report that a participant's video has been blocked.
 * @param participant Participant whose video block status has changed.
 */
- (void)activeParticipantDidRaiseHand:(CSActiveParticipant *)participant;

/**
 * Called to report that a participant's hand is lowered, either by the participant, or
 * by a moderator who acknowledged the participant raising hand.
 * @param participant Participant whose hand is lowered.
 */
- (void)activeParticipantDidLowerHand:(CSActiveParticipant *)participant;

/**
 * Called to report that a participant's camera remote control support has been changed.
 * @param participant Participant whose camera remote control support was changed.
 */
-(void)activeParticipantDidChangeCameraRemoteControlSupport:(CSActiveParticipant *)participant;

@end

/**
 * Interface object representing an active participant in a conference call.
 */
@interface CSActiveParticipant : CSParticipant<NSCopying>

/**
 * The delegate used to handle active participant related events.
 */
@property (nonatomic, weak) id<CSActiveParticipantDelegate> delegate;

/** Whether the participant's audio is muted. */

@property (nonatomic, readonly, getter=isAudioMutedByServer) BOOL audioMutedByServer;

/** Whether the participant's audio is active. */

@property (nonatomic, readonly, getter=isActiveAudio) BOOL audioActive;

/** Participant audio state, as known by the conferencing system. */

@property (nonatomic, readonly) CSParticipantMediaStatus audioStatus;

/** Participant connection state, as known by the conferencing system. */

@property (nonatomic, readonly) CSParticipantConnectionStatus connectionStatus;

/** Whether the participant's video is active. */

@property (nonatomic, readonly, getter=isActiveVideo) BOOL videoActive;

/** Whether the participant's web collaboration is active. */

@property (nonatomic, readonly, getter=isApplicationSharingActive) BOOL applicationSharingActive;

/** Whether the participant's hand is raised. */

@property (nonatomic, readonly, getter=isHandRaised) BOOL handRaised;

/**
 * The time participant has raised hand.
 * @return  null if hand is lowered or never raised
 */

@property (nonatomic, readonly) NSDate *handRaisedDate;

/**
 * The time participant has lowered hand.
 * @return null if hand is raised or never lowered
 */

@property (nonatomic, readonly) NSDate *handLoweredDate;

/** Participant's video block (i.e., transmission) status, as known by the conferencing system. */

@property (nonatomic, readonly, getter=isVideoBlockedByServer) BOOL videoBlockedByServer;

/** Participant video state, as known by the conferencing system. */

@property (nonatomic, readonly) CSParticipantMediaStatus videoStatus;

/**
 * Video channel id associated with the video participant during
 * a multi video stream conference call.
 */
@property (nonatomic, readonly) int videoChannelId;

/** Whether the participant is a moderator. */

@property (nonatomic, readonly, getter=isModerator) BOOL moderator;

/** Whether the participant is a presenter. */

@property (nonatomic, readonly, getter=isPresenter) BOOL presenter;

/** Whether the participant is a lecturer. */

@property (nonatomic, readonly, getter=isLecturer) BOOL lecturer;

/** Whether the participant's camera is controllable. */

@property(nonatomic, readonly, getter = isCameraRemoteControllable) BOOL cameraRemoteControllable;

/** Last time the participant was an active talker on the conference call. */

@property (nonatomic, readonly, getter=lastSpokenDate) NSDate *lastSpokenDate;

/** Participant's entry time to the conference. */

@property (nonatomic, readonly) NSDate *enterDate;

/**
 * CSCapability object indicating whether lowering another participant's hand is supported.
 * Lower participant hand capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *lowerParticipantHandCapability;

/**
 * CSCapability object indicating whether local user can lower participant's hand and unmute audio.
 *
 * This capability is <b>Allowed</b> if all of the following are true:
 * <ul>
 * <li>The conference call supports raise hand feature.</li>
 * <li>The local user has permission to lower another participant's hand.</li>
 * <li>Participant's hand is raised.</li>
 * <li>Participant's audio is muted by moderator.</li>
 * </ul>
 * Conference moderation features are not supported when the client is used in shared control mode.
 * @see #lowerParticipantHandCapability:
 * @return A CSCapability object.
 */
@property (nonatomic, readonly) CSCapability *lowerParticipantHandAndUnmuteAudioCapability;

/**
 * CSCapability object indicating whether mute of a selected participant is supported.
 */
@property (nonatomic, readonly) CSCapability *muteParticipantAudioCapability;

/**
 * CSCapability object indicating whether unmute of a selected participant is supported.
 */
@property (nonatomic, readonly) CSCapability *unmuteParticipantAudioCapability;

/**
 * CSCapability object indicating whether block video of a selected participant is supported.
 * Conference video capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *blockParticipantVideoCapability;

/**
 * CSCapability object indicating whether unblock video of a selected participant is supported.
 * Conference video capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *unblockParticipantVideoCapability;

/**
 * CSCapability object indicating whether pan/tilt/zoom (PTZ) of the participant's camera can be controlled programmatically.
 * Conference video capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *cameraRemoteControlCapability;

/**
 * CSCapability object indicating whether selecting a participant as the conference lecturer is supported.
 * The CSCapability returns not supported if the conference call does not support selection of a participant
 * as the lecturer, or if the local user does not have permission to assign a participant as the lecturer on the call.
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *assignAsLecturerCapability;

/**
 * CSCapability object indicating whether selecting a participant as the conference moderator is supported.
 * The CSCapability returns not supported if the conference call does not support selection of a participant
 * as the moderator, or if the local user does not have permission to assign a participant as the moderator on the call.
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *assignAsModeratorCapability;

/**
 * CSCapability object indicating whether selecting a participant as the conference presenter is supported.
 * The CSCapability returns not supported if the conference call does not support selection of a participant
 * as the presenter, or if the local user does not have permission to assign or unassign a participant as the presenter on the call.
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *assignAsPresenterCapability;

/**
 * CSCapability object indicating whether deselecting a participant as the conference presenter is supported.
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *unassignAsPresenterCapability;

/**
 * Returns whether local user can unassign  a participant as a lecturer.
 * The capability returns not supported if the conference call does not
 * support deselection of a participant as the lecturer,
 * or if the local user does not have permission to unset a participant
 * as the lecturer on the call.
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * @return capability information.
 */
@property (nonatomic, readonly) CSCapability *unassignAsLecturerCapability;

/**
 * Returns whether the user supports private chat in conference.
 */
@property (nonatomic, readonly) CSCapability *inConferencePrivateChatCapability;

/**
 * CSCapability object indicating whether the local user can pin current participant's video in a specific position
 * of the current video layout.
 *
 * This capability returns not supported if the conference call
 * does not support video pinning/unpinning, or video pin/unpin requests.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see pinVideo:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *videoPinCapability;


/**
 * A Boolean value indicating whether the participant has limited capabilities on the call.
 * Restricted participant cannot be lecturer or presenter and cannot become a normal participant.
 * Restricted participant has no moderator controls and can only have a single receive-only video stream.
 * Restricted participant cannot unblock camera and send video, or cannot perform remote camera control operations (e.g., control camera of a remote room system).
 * Restricted participant is muted by the conference server by default, and can only be unmuted by the moderator, e.g., by getting moderator's attention to be unmuted through raise hand mechanism.
 */
@property (nonatomic, readonly, getter=isRestrictedParticipant) BOOL restrictedParticipant;

/**
 * A Boolean value indicating that the active participant was on the conference but previously not visible in the conference roster.
 * This can happen when there are more participants on the conference call than what can be provided by the conference server in the roster.
 *
 * When/if this hidden user becomes visible and gets added to the roster, the client can use this property to identify that this participant
 * was already in the conference (and not just entering the meeting). The client application can use this property to update its UI
 *  accordingly: for example adding a special badge icon for this participant or adding the participant to a different list.
 */
@property (nonatomic, readonly) BOOL wasPreviouslyNotVisibleInParticipantList;

/**
 * Lowers a participant's hand on the conference call. The local user must be a moderator
 * for this operation to complete successfully.
 *
 * @param unmuteAudio Indication as to whether the participant whose hand is lowered is to be unmuted.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)lowerHand:(BOOL) unmuteAudio completionHandler:(void (^)(NSError *error))handler;


/**
 * Mutes a participant on the call. The local user must be a moderator
 * for this operation to complete successfully.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)muteWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Unmutes a participant on the call. The local user must be a moderator
 * for this operation to complete successfully.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)unmuteWithCompletionHandler:(void (^)(NSError *error))handler;


/**
 * Blocks a participant's video on the call. The local user must be a moderator
 * for this operation to complete successfully.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)blockVideoWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Unblocks a participant's video on the call. The local user must be a moderator
 * for this operation to complete successfully.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)unblockVideoWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Initiates a remote camera control command. If the far-end camera does not support
 * remote camera commands, the command fails.
 * @param control Camera control command
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)initiateCameraControl:(CSCameraControl)control completionHandler:(void (^)(NSError *error))handler;

/**
 * Used by a conference moderator to select a participant to be a moderator during the conference call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)assignAsModeratorWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Used by a conference moderator to select a participant to no longer be a moderator during the conference call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)unassignAsModeratorWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Used by a conference moderator to select a participant to be a presenter during the conference call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)assignAsPresenterWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Used by a conference moderator to select a participant to no longer be a presenter during the conference call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)unassignAsPresenterWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Used by a conference moderator to select a participant to be a lecturer during the conference call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)assignAsLecturerWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Used by a conference moderator to select a participant to no longer be a lecturer during the conference call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)unassignAsLecturerWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Requests for current participant's video to be pinned in a certain area of the video image.
 *
 * The destination coordinates can be any point within a video region inside the video image.
 * They do not have to be a point at the boundary of the video region. In order to undo 
 * a previous video pin operation, the application needs to call CSConference::setVideoLayout:completionHandler:
 * and specify CSVideoLayoutDynamic layout option.
 *
 * @param destinationPoint Coordinates of the participant's final video position in the video image.
 * The values are in the range 0.0 to 1.0, with 0, 0 referring to the upper left of the video image.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSActiveParticipant::videoPinCapability
 */
- (void)pinVideoWithDestinationPoint:(CGPoint)destinationPoint completionHandler:(void (^)(NSError *error))handler;

@end
