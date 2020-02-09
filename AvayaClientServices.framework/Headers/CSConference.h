/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSVideoLayout.h"
#import "CSDataCollectionChangeType.h"
#import "CSVideoChannel.h"

// When support for DataSet in the public API is removed, delete this #define and any blocks of code that are
// being conditionally compiled by the DATASET_SUPPORTED define.
#define DATASET_SUPPORTED

@class CSActiveParticipant, CSCall, CSCapability, CSDataSet, CSParticipant;
@class CSChat;
@class CSMeetingMinutes;
@class CSConferenceSlideViewer;
@class CSConferenceMobileLink;

@protocol CSConferenceDelegate;

/**
 * Recording status of the conference call.
 */
typedef NS_ENUM(NSInteger, CSConferenceRecordingStatus) {
	CSConferenceRecordingStatusOff,      /**< Conference recording is off, or is not supported. */
	CSConferenceRecordingStatusOn,       /**< Conference recording is on. */
	CSConferenceRecordingStatusPaused,   /**< Conference recording is paused. */
	CSConferenceRecordingStatusFailed    /**< Conference recording is failed. */
};

/**
 * Overall encryption status of the conference call.
 */
typedef NS_ENUM(NSInteger, CSConferenceEncryptionStatus) {
	/** Conference encryption status is unknown, for example, if the conference server
	 *  does not support the indication. */
	CSConferenceEncryptionStatusUnknown,
	/** None of the media legs (audio or video) are encrypted. */
	CSConferenceEncryptionStatusNotEncrypted,
	/** Some of the media legs are encrypted. */
	CSConferenceEncryptionStatusPartiallyEncrypted,
	/** All of the media legs are encrypted. */
	CSConferenceEncryptionStatusEncrypted
};

/**
 * Overall streaming status of the conference call.
 */
typedef NS_ENUM(NSInteger, CSConferenceStreamingStatus) {
	/** Conference streaming status is unknown, for example, if the conference server
	 *  does not support the indication. */
	CSConferenceStreamingStatusUnknown,
	/** Conference is not being streamed. */
	CSConferenceStreamingStatusDisabled,
	/** Conference is being streamed. */
	CSConferenceStreamingStatusEnabled,
};

/**
 * The CSConference object provides access to conferencing related capabilities and actions.
 *
 * The CSConference object is accessible from the CSCall object and
 * provides a set of APIs that allow application developers to access different features
 * and services provided by Avaya's different conferencing solutions.
 *
 * In general, the capabilities and the set of allowed operations
 * are not only dependent on the capabilities of the conferencing server,
 * but also on the specific privileges assigned to the local user
 * on the conference call.  For example, if the local user is a moderator
 * of the call, (s)he will be able to perform conference operations
 * such as lock/unlock the call, start/stop recording,
 * as well as operations on participants such as mute/unmute,
 * add a new participant to the call, or drop an existing participant
 * from the call. Status updates reported by the conference server are reported
 * through the CSConferenceDelegate object.
 *
 * @see CSConferenceDelegate
 */
@interface CSConference : NSObject

/**
 * A Boolean value indicating whether the conference call is waiting to be started.
 *
 * The value of this property is NO if the conference has not started because the conference requires a
 * moderator to join before start.
 *
 * Note: This feature is not fully supported across all conferencing platforms.
 */
@property (nonatomic, readonly, getter=isWaitingToStart) BOOL waitingToStart;

/**
 * An array of CSActiveParticipant objects representing the participants who are currently
 * in the conference.
 *
 * The returned array is a snapshot in time and is not dynamically updated as the list changes.
 * Updates to the participant list (add, remove or update) are reported through the CSConferenceDelegate via the
 * {@link CSConferenceDelegate::conference:participantsDidChange:changedParticipants: participantsDidChange}
 * message.
 *
 * @see CSConference::retrieveParticipantListCapability
 * @see CSConference::pendingParticipants
 * @see CSConference::droppedParticipants
 */
@property (atomic, readonly, copy) NSArray *participants;

/**
 * An array of CSDroppedParticipant objects representing participants who have left the conference.
 *
 * When an CSActiveParticipant leaves the call, or is forced out by a
 * moderator, the corresponding entry is removed from the conference roster list,
 * and a new entry is added to the dropped participant list.
 *
 * The returned array is a snapshot in time and is not dynamically updated as the list changes.
 * Updates to the dropped participant list (add, remove or update) are reported through the CSConferenceDelegate via the
 * {@link CSConferenceDelegate::conference:droppedParticipantsDidChange:changedParticipants: droppedParticipantsDidChange}
 * message.
 *
 * @see CSConference::retrieveParticipantListCapability
 * @see CSConference::participants
 * @see CSConference::pendingParticipants
 */
@property (atomic, readonly, copy) NSArray *droppedParticipants;

/**
 * An array of CSPendingParticipant objects representing the participants who are waiting to be admitted to the conference.
 *
 * A pending participant is a person who is waiting to join a conference
 * call that is locked. A moderator of the conference call may allow
 * entry of a pending participant into the conference call. 
 * During the time that a participant is pending, the same participant could also appear in the active participants list as an 
 * CSActiveParticipant whose "ConnectionStatus" property is set to "Authorizing".
 * When a pending participant is allowed to enter the locked conference call, the corresponding
 * entry is removed from the pending participant list. Subsequently, a corresponding 
 * CSActiveParticipant will change it's state to "connected" in list of conference participants.
 *
 * The returned array is a snapshot in time and is not dynamically updated as the list changes.
 * Updates to the pending participant list (add, remove or update) are reported through the CSConferenceDelegate via the
 * {@link CSConferenceDelegate::conference:pendingParticipantsDidChange:changedParticipants: pendingParticipantsDidChange}
 * message.
 *
 * @see CSConference::retrieveParticipantListCapability
 * @see CSConference::participants
 * @see CSConference::droppedParticipants
 */
@property (atomic, readonly, copy) NSArray *pendingParticipants;

/**
 * An array of CSActiveParticipant objects representing the participants who are actively talking.
 *
 * The returned array is a snapshot in time and is not dynamically updated as the list changes.
 * Updates to the active talkers list (add, remove or update) are reported through the CSConferenceDelegate via the
 * {@link CSConferenceDelegate::conference:activeTalkersDidChange:changedParticipants: activeTalkersDidChange}
 * message.
 *
 * @see CSConference::recentTalkers
 */
@property (atomic, readonly, copy) NSArray *activeTalkers;

/**
 * An array of CSActiveParticipant objects representing the participants whose video
 * is currently being received during a multi video channel conference call.
 *
 * The returned array is a snapshot of the active video participants whose video is
 * being received at the time this property is queried, and is not dynamically updated
 * as the list changes. Updates to the list are reported through the CSConferenceDelegate via the
 * {@link CSConferenceDelegate::conference:didActiveVideoParticipantChange: didActiveVideoParticipantChange}
 * message.
 * If the query is made for a conference call that is not multi video channel enabled, or if there is
 * no active video participant on a multi video channel enabled conference call, the query returns nil.
 * The application can query {@link CSCall::multiVideoChannelsCapability} to determine
 * if the call is multi video channel enabled.
 */
@property (atomic, readonly, copy) NSArray *activeVideoSourceParticipants;

/**
 * An array of CSActiveParticipant objects representing the participants who are recent talkers.
 *
 * The returned array is a snapshot in time and is not dynamically updated as the list changes.
 * Updates to the recent talkers list (add, remove or update) are reported through the CSConferenceDelegate via the
 * {@link CSConferenceDelegate::conference:recentTalkersDidChange:changedParticipants: recentTalkersDidChange}
 * message.
 *
 * @see CSConference::activeTalkers
 */
@property (atomic, readonly, copy) NSArray *recentTalkers;

#ifdef DATASET_SUPPORTED
/**
 * CSDataSet object indicating the participants who are in the conference.
 *
 * Updates to the participant list (add, remove or update)
 * are reported through the CSDataSetDelegate of the CSDataSet object.
 *
 * @see CSConference::retrieveParticipantListCapability
 * @see CSConference::pendingParticipants
 * @see CSConference::droppedParticipants
 * @deprecated Use the {@link #participants} property instead.
 */
@property (nonatomic, readonly) CSDataSet *activeParticipants DEPRECATED_ATTRIBUTE;

/**
 * CSDataSet object indicating the participants who are active talkers.
 *
 * Updates to the participant list (add, remove or update)
 * are reported through the CSDataSetDelegate of the CSDataSet object.
 *
 * @see CSConference::recentTalkerParticipants
 * @deprecated Use the {@link #activeTalkers} property instead.
 */
@property (nonatomic, readonly) CSDataSet *activeTalkerParticipants DEPRECATED_ATTRIBUTE;

/**
 * CSDataSet object indicating the participants who have left the conference.
 *
 * When an CSActiveParticipant leaves the call, or is forced out by a
 * moderator, the corresponding entry is removed from the conference roster list,
 * and a new entry is added to the dropped participant list.
 *
 * Updates to the participant list (add, remove or update)
 * are reported through the CSDataSetDelegate of the CSDataSet object.
 *
 * @see CSConference::retrieveParticipantListCapability
 * @see CSConference::pendingParticipants
 * @see CSConference::activeParticipants
 * @deprecated Use the {@link #droppedParticipants} property instead.
 */
@property (nonatomic, readonly) CSDataSet *droppedParticipantsDS DEPRECATED_ATTRIBUTE;

/**
 * CSDataSet object indicating the participants who are waiting to be admitted to the conference.
 *
 * A pending participant is a person who is waiting to join a conference
 * call that is locked. A moderator of the conference call may allow
 * entry of a pending participant into the conference call. When a pending
 * participant is allowed to enter the locked conference call, the corresponding
 * entry is removed from the pending participant list. Subsequently, a new
 * CSActiveParticipant is added to the list of conference participants.
 *
 * Updates to the participant list (add, remove or update)
 * are reported through the CSDataSetDelegate of the CSDataSet object.
 *
 * @see CSConference::retrieveParticipantListCapability
 * @see CSConference::activeParticipants
 * @see CSConference::droppedParticipants
 * @deprecated Use the {@link #pendingParticipants} property instead.
 */
@property (nonatomic, readonly) CSDataSet *pendingParticipantsDS DEPRECATED_ATTRIBUTE;

/**
 * CSDataSet object indicating the participants who are recent talkers.
 *
 * Updates to the participant list (add, remove or update)
 * are reported through the CSDataSetDelegate of the CSDataSet object.
 *
 * @see CSConference::activeTalkerParticipants
 * @deprecated Use the {@link #recentTalkers} property instead.
 */
@property (nonatomic, readonly) CSDataSet *recentTalkerParticipants DEPRECATED_ATTRIBUTE;
#endif

/**
 * The delegate used to handle conference-related events.
 */
@property (nonatomic, weak) id<CSConferenceDelegate> delegate;

/**
 * CSCapability object indicating whether the conference call can be queried to
 * get the list of conference participants.
 *
 * @see CSConference::activeParticipants
 */
@property (nonatomic, readonly) CSCapability *retrieveParticipantListCapability;

/**
 * CSCapability object indicating whether in-conference chat is supported.
 *
 * In-conference chat allows conference participants to exchange messages amongst each other
 * without interrupting the speaker.  These messages can either be private between selected
 * participants or shared with all conference participants.
 *
 * The application may use the result of this query to enable or disable chat functions.
 * See CSChat for more information about the in-conference chat feature.
 *
 * In-conference chat capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::inConferenceChat
 *
 */
@property (nonatomic, readonly) CSCapability *inConferenceChatCapability;

/**
 * CSChat object associated with the conference call.
 *
 * CSChat object can be used to query for list of messages or send a new message.
 *
 * @see CSConference::inConferenceChatCapability
 */
@property (nonatomic, readonly) CSChat *inConferenceChat;

/**
 * CSCapability object indicating whether meeting minutes feature is supported.
 *
 * The meeting minutes feature allows conference participants to enter notes, for example,
 * to mark the beginning of a new topic during a conference call.
 * See CSMeetingMinutes for more information about the meeting minutes
 * feature. The application may use the result of this query to enable or
 * disable meeting minutes related functions.
 *
 * Meeting minutes capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::meetingMinutes
 */
@property (nonatomic, readonly) CSCapability *meetingMinutesCapability;

/**
 * CSMeetingMinutes object associated with the conference call.
 *
 * CSMeetingMinutes object can be used to query for list of minutes or to
 * add a new minute, or edit or remove an existing minute.
 *
 * @see CSConference::meetingMinutesCapability
 */
@property (nonatomic, readonly) CSMeetingMinutes *meetingMinutes;

/**
 * CSCapability object indicating whether the conference supports mobile link
 * connection to conference room systems.
 *
 * The mobile link feature allows an application to control a conference call while
 * terminating audio and video on a conferencing room system. The application may use
 * the result of this query to enable or disable mobile link related functions.
 * The support for the mobile link is dependent on the conferencing system version.
 * See CSConferenceMobileLink for more information about the conference mobile link
 * feature.
 *
 * Mobile link capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::mobileLink
 */
@property (nonatomic, readonly) CSCapability *mobileLinkCapability;

/**
 * CSConferenceMobileLink object is the mobile link instance associated 
 * with the conference.
 *
 * @see CSConference::mobileLinkCapability
 */
@property (nonatomic, readonly) CSConferenceMobileLink *mobileLink;

/**
 * CSCapability object indicating whether the conference supports 
 * personal viewing of presentation slides.
 *
 * For example, a person who joins a conference call late can use the slide viewer feature
 * to view the document pages that have already been shared during the call. The application may use
 * the result of this query to enable or disable functions related to viewing of previously shared
 * slides during the conference.
 * The support for the slide viewer is dependent on the conferencing system version.
 * See CSConferenceSlideViewer for more information about the conference slide viewer
 * feature.
 *
 * Slide viewer capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::slideViewer
 *
 */
@property (nonatomic, readonly) CSCapability *conferenceSlideViewerCapability;

/**
 * CSConferenceSlideViewer object is the slide viewer instance associated
 * with the conference call.
 *
 * @see CSConference::conferenceSlideViewerCapability
 */
@property (nonatomic, readonly) CSConferenceSlideViewer *slideViewer;

/**
 * The collaboration URL associated with the conference call, if the conference call
 * is capable of supporting collaboration. 
 */
@property (nonatomic, readonly) NSURL *collaborationURL;

/**
 * CSCapability object indicating whether the local user can moderate the conference call.
 * Slide viewer capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *moderationCapability;

/**
 * CSCapability object indicating whether the conference server allows local user 
 * to request to become a moderator. 
 *
 * The capability returns not supported if the conference server
 * does not support self-promotion to become a moderator capability, or if the local user 
 * is already a moderator.
 * The application may use the result of this query to enable or disable functions related to
 * requesting to become a moderator.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::pinRequiredToBecomeModerator
 * @see CSConference::requestToBecomeModerator:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *requestToBecomeModeratorCapability;

/**
 * A Boolean value indicating whether the conference call requires entry of a moderator PIN
 * before the local user is allowed to become a moderator. 
 *
 * The value of this property is YES only if CSConference::requestToBecomeModeratorCapability: 
 * returns supported indication. The application may use this method to prompt the user for moderator 
 * PIN before calling CSConference::requestToBecomeModerator:completionHandler:.
 * 
 * @see CSConference::getRequestToBecomeModeratorCapability
 */
@property (nonatomic, readonly, getter=isPinRequiredToBecomeModerator) BOOL pinRequiredToBecomeModerator;

/**
 * Issues a request to promote the local user to become a conference moderator.
 *
 * @param moderatorPin Optional PIN required to issue the moderator request. If PIN
 * is not required, an empty string is provided as the input argument.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)requestToBecomeModerator:(NSString*)moderatorPin completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the conference call reports
 * the active talker information. 
 *
 * Reporting of active talkers is dependent on the capabilities of the conferencing system.
 * Active talker capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::activeTalkerParticipants
 */
@property (nonatomic, readonly) CSCapability *activeTalkerCapability;

/**
 * CSCapability object indicating whether the local user can mute self audio 
 * on the conference call.
 *
 * The capability returns not supported if the local user does not have permission
 * to mute self audio, or if this feature is not supported by the conferencing server.
 * This will also be not supported when the local user has already muted audio.
 *
 * The application may use the CSActiveParticipant::muteWithCompletionHandler: instance associated with the local user to
 * request mute of local user's audio from the conference server.
 */
@property (nonatomic, readonly) CSCapability *muteSelfAudioCapability;

/**
 * CSCapability object indicating whether the local user can unmute self audio 
 * on the conference call.
 *
 * The capability returns not supported if the local user does not have permission
 * to unmute self audio. This can happen under the following circumstances:
 * <ul>
 * <li>The local user does not have audio muted.</li>
 * <li>The feature is not supported by the conference server.</li>
 * <li>The conference is in lecture mode and the local user is not the moderator or lecturer.</li>
 * </ul>
 * The application may use the CSActiveParticipant::unmuteWithCompletionHandler: instance associated with the local user to
 * request unmute of local user's audio from the conference server.
 *
 */
@property (nonatomic, readonly) CSCapability *unmuteSelfAudioCapability;

/**
 * CSCapability object indicating whether the local user can block self video 
 * on the conference call.
 *
 * The capability returns not supported if the local user does not have permission
 * to block self video. This is typically when the local user has already blocked video.
 * The application may use the CSActiveParticipant::blockVideoWithCompletionHandler: instance
 * associated with the local user to request block of local user's video from the conference server.
 *
 * Conference video features are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *blockSelfVideoCapability;

/**
 * CSCapability object indicating whether the local user can unblock self video 
 * on the conference call.
 *
 * The capability returns not supported if the local user does not have permission
 * to unblock self video. This is typically when the local user does not have video blocked,
 * or when the conference is in lecture mode and the local user is not the moderator or lecturer.
 * The application may use the CSActiveParticipant::unblockVideoWithCompletionHandler: instance
 * associated with the local user to request unblock of local user's video from the conference server.
 *
 * Conference video features are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 */
@property (nonatomic, readonly) CSCapability *unblockSelfVideoCapability;

/**
 * CSCapability object indicating whether the local user can lock/unlock the conference call.     
 *
 * The capability returns not supported if the conference call does not
 * support lock/unlock, or if the local user does not have permission
 * to lock/unlock the conference call.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::locked
 * @see CSConference::setLocked:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateLockCapability;

/**
 * A Boolean value indicating the lock status of the conference call.
 *
 * The value of this property is NO if the call is not a conference call or the
 * conference call is not locked.
 *
 * @see CSConference::updateLockCapability
 * @see CSConference::setLocked:completionHandler:
 */
@property (nonatomic, readonly, getter=isLocked) BOOL locked;

/**
 * Locks or unlocks the conference call.
 *
 * If the call is not a conference call or the conference call is not locked, an error will
 * occur. When the operation is successful, a status update is reported through the 
 * CSConferenceDelegate::conference:didChangeLockStatus: for this CSConference object.
 *
 * @param locked If @c YES the conference is locked. If @c NO the conference is unlocked.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::updateLockCapability
 * @see CSConference::locked
 */
- (void)setLocked:(BOOL)locked completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can put the conference call in lecture mode.
 *
 * The capability returns not supported if the conference call does not
 * support lecture mode, or if the local user does not have permission
 * to set the call into lecture mode.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::lectureModeActive
 * @see CSConference::setLectureModeActive:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateLectureModeCapability;

/**
 * A Boolean value indicating whether lecture mode is active.
 *
 * The value of this property is NO if the call is not a conference call, or if the conference call does not have
 * lecture mode active.
 * 
 * @see CSConference::updateLectureModeCapability
 * @see CSConference::setLectureModeActive:completionHandler:
 */
@property (nonatomic, readonly, getter=isLectureModeActive) BOOL lectureModeActive;

/**
 * Enables or disables lecture mode for the conference call.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeLectureModeStatus: for this CSConference object.
 *
 * @param active If @c YES lecture mode is enabled. If @c NO lecture mode is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::lectureModeActive
 * @see CSConference::updateLectureModeCapability
 */
- (void)setLectureModeActive:(BOOL)active completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can change the conference call continuation mode.
 *
 * Continuation mode allows the conference call to continue after the
 * moderator leaves the conference call. This feature is not applicable to
 * all Avaya conferencing solutions.
 * The capability returns not supported if the conference call does not
 * support conference continuation after the moderator leaves the call, or if
 * the local user does not have permission to set the call continuation mode.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::continuationActive
 * @see CSConference::setContinuationActive:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateContinuationStatusCapability;

/**
 * A Boolean value indicating whether the conference continues after all moderators have left.
 *
 * The value of this property is NO if the call is not a conference call, or if the
 * conference call's continuation status is not set or if the feature is not supported.
 *
 * @see CSConference::updateContinuationStatusCapability
 * @see CSConference::setContinuationActive:completionHandler:

 */
@property (nonatomic, readonly, getter=isContinuationActive) BOOL continuationActive;

/**
 * Enables or disables conference continuation status after moderator exits the conference call.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeContinuationStatus: for this CSConference object.
 *
 * @param active If @c YES continuation is enabled. If @c NO continuation is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::updateContinuationStatusCapability
 * @see CSConference::continuationActive
 */
- (void)setContinuationActive:(BOOL)active completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can start conference recording.
 *
 * The capability returns not supported if the conference call does not
 * support recording, or if the local user does not have permission to
 * start recording of the call, or if the recording is already active.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::startRecordingWithCompletionHandler:
 * @see CSConference::stopRecordingWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *startRecordingCapability;

/**
 * CSCapability object indicating whether the local user can stop conference recording.
 *
 * The capability returns not supported if the conference call does not
 * support recording, or if the local user does not have permission to
 * start recording of the call, or if the recording is not active.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::startRecordingWithCompletionHandler:
 * @see CSConference::stopRecordingWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *stopRecordingCapability;

/**
 * CSCapability object indicating whether the local user can pause conference recording.
 *
 * The capability returns not supported if the conference call does not
 * support recording, or if the local user does not have permission to
 * pause recording of the call, or if the recording is already paused.
 *
 * @see CSConference::startRecordingWithCompletionHandler:
 * @see CSConference::stopRecordingWithCompletionHandler:
 */
@property(nonatomic, readonly) CSCapability *pauseRecordingCapability;

/**
 * CSCapability object indicating whether the local user can resume conference recording.
 *
 * The capability returns not supported if the conference call does not
 * support recording, or if the local user does not have permission to
 * resume recording of the call, or if the recording is paused.
 *
 * @see CSConference::startRecordingWithCompletionHandler:
 * @see CSConference::stopRecordingWithCompletionHandler:
 */
@property(nonatomic, readonly) CSCapability *resumeRecordingCapability;

/**
 * CSCapability object indicating whether the local user can assign name and description for the meeting recording.
 *
 * The capability returns not supported if the conference call does not
 * support setting name and description.
 *
 * @see CSConference::startRecordingWithCompletionHandler:
 * @see CSConference::stopRecordingWithCompletionHandler:
 */
@property(nonatomic, readonly) CSCapability *assignRecordingNameCapability;

/**
 * A Boolean value indicating whether the conference is being recorded.
 *
 * The value of this property is NO if the call is not a conference call, or if the conference is not being recorded.
 *
 * @see CSConference::startRecordingCapability
 * @see CSConference::stopRecordingCapability
 * @see CSConference::startRecordingWithCompletionHandler:
 * @see CSConference::stopRecordingWithCompletionHandler:
 */
@property (nonatomic, readonly, getter=isRecordingActive) BOOL recordingActive;

/**
 * Returns the meeting recording name.
 */
@property (nonatomic, readonly, getter=recordingName) NSString *recordingName;

/**
 * Returns the meeting recording description.
 */
@property (nonatomic, readonly, getter=recordingDescription) NSString *recordingDescription;

/**
 * Starts conference recording.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeRecordingStatus: for this CSConference object.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::startRecordingCapability
 * @see CSConference::stopRecordingCapability
 * @see CSConference::recordingActive
 * @see CSConference::stopRecordingWithCompletionHandler:
 */
- (void)startRecordingWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Starts conference recording.
 *
 * @param handler A block to be called when the operation is completed.
 * @param recordingName Name of the meeting recording.
 * @param recordingDescription Description of the meeting recording.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)startRecording:(NSString*)recordingName
  recordingDescription:(NSString*)recordingDescription
	 completionHandler:(void (^)(NSError *error))handler;

/**
 * Stops conference recording.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeRecordingStatus: for this CSConference object.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::startRecordingCapability
 * @see CSConference::stopRecordingCapability
 * @see CSConference::recordingActive
 * @see CSConference::startRecordingWithCompletionHandler:
 */
- (void)stopRecordingWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * A Boolean value indicating whether the recording of the conference call is paused. 
 *
 * The value of this property is NO if the conference recording is paused, or if recording pause/resume is not
 * supported by the conference server. The CSConference::recordingActive and
 * CSConference::recordingPaused properties together return the current status of the conference
 * recording.
 *
 * @see CSConference::pauseRecordingCapability
 * @see CSConference::resumeRecordingCapability
 * @see CSConference::pauseRecordingWithCompletionHandler:
 * @see CSConference::resumeRecordingWithCompletionHandler:
 */
@property (nonatomic, readonly, getter=isRecordingPaused) BOOL recordingPaused;

/**
 * A Boolean value indicating whether the  conference call is in waiting passcode state. 
 *
 * The value of this property is NO if the conference is not currently waiting for passcode form user.
 *
 * @see CSConference::sendPasscode
 */
@property (nonatomic, readonly, getter=isPasscodeRequiredToEnterConference) BOOL isPasscodeRequiredToEnterConference;

/**
 * A Boolean value indicating whether the  conference call is in waiting external admission state.
 *
 * The value of this property is NO if the conference is not currently waiting for external admission thorough DTMF.
 */
@property (nonatomic, readonly, getter=isExternalAdmissionRequiredToEnterConference) BOOL isExternalAdmissionRequiredToEnterConference;

/**
 * A Boolean value indicating whether the conference call is waiting access to join locked conference.
 *
 * The value of this property is NO if the conference is not required permissions to join conference.
 */
@property (nonatomic, readonly, getter=isPermissionRequiredToEnterLockedConference) BOOL permissionRequiredToEnterLockedConference;

/**
 * Pauses conference recording.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeRecordingStatus: for this CSConference object.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::pauseRecordingCapability
 * @see CSConference::resumeRecordingCapability
 * @see CSConference::recordingPaused
 * @see CSConference::resumeRecordingWithCompletionHandler:
*/
- (void)pauseRecordingWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Resumes conference recording.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeRecordingStatus: for this CSConference object.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::pauseRecordingCapability
 * @see CSConference::resumeRecordingCapability
 * @see CSConference::recordingPaused
 * @see CSConference::pauseRecordingWithCompletionHandler:
 */
- (void)resumeRecordingWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can enable/disable video for the conference call.
 *
 * The capability returns not supported if the conference call does not
 * support control of video allow/disallow, or if the local user does not
 * have permission to control video allow/disallow status of the call.
 *
 * Conference video capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::videoAllowed
 * @see CSConference::setVideoAllowed:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateVideoAllowedCapability;

/**
 * A Boolean value indicating whether the conference allows video.
 *
 * The value of this property is NO if the call is not a conference
 * call, or if video on the conference call is not allowed.
 *
 * @see CSConference::updateVideoAllowedCapability
 * @see CSConference::setVideoAllowed:completionHandler:
 */
@property (nonatomic, readonly, getter=isVideoAllowed) BOOL videoAllowed;

/**
 * Controls whether video is allowed on the conference call.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeVideoStatus: for this CSConference object.
 *
 * @param allowed If @c YES video is allowed. If @c NO video is disallowed.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::updateVideoAllowedCapability
 * @see CSConference::videoAllowed
 */
- (void)setVideoAllowed:(BOOL)allowed completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can control entry/exit tone setting 
 * of the conference call.
 *
 * The capability returns not supported if the conference call does not
 * support entry/exit tones, or if the local user does not have permission
 * to control the entry/exit tones.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::entryExitToneActive
 * @see CSConference::setEntryExitToneActive:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateEntryExitToneStatusCapability;

/**
 * A Boolean value indicating whether participant entry/exit tones are enabled for the conference.
 *
 * The value of this property is NO if the call is not a conference call, or if the conference call's entry/exit tone is not enabled.
 *
 * @see CSConference::updateEntryExitToneStatusCapability
 * @see CSConference::setEntryExitToneActive:completionHandler:
 */
@property (nonatomic, readonly, getter=isEntryExitToneActive) BOOL entryExitToneActive;

/**
 * Controls whether entry and exit tones are allowed for the conference call.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeEntryExitToneStatus: for this CSConference object.
 *
 * @param active If @c YES participant entry/exit tones are enabled. If @c NO entry/exit tones are disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::updateEntryExitToneStatusCapability
 * @see CSConference::entryExitToneActive
 */
- (void)setEntryExitToneActive:(BOOL)active completionHandler:(void (^)(NSError *error))handler;

/**
 * Current streaming status.
 */
@property (nonatomic, readonly) CSConferenceStreamingStatus streamingStatus;

/**
 * Current encryption status.
 */
@property (nonatomic, readonly) CSConferenceEncryptionStatus encryptionStatus;

/**
 * The subject of the conference if one is provided by the conference server.
 *
 * A nil string is returned if there is no subject provided.
 */
@property (nonatomic, readonly, getter=subject) NSString *subject;

/**
 * The brand name of the conference if one is provided by the conference server.
 * A nil string is returned if there is no brand name provided.
 */
@property (nonatomic, readonly, getter=brandName) NSString *brandName;

/**
 * CSCapability object indicating whether the local user can control panel mode status of the conference call.
 *
 * The capability returns not supported if the conference call does not
 * support panel mode setting, or if the local user does not have permission to control
 * the panel mode setting.
 *
 * Update multiple presenters capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::multiplePresentersAllowed
 * @see CSConference::setMultiplePresentersAllowed:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateMultiplePresentersCapability;

/**
 * A Boolean value indicating whether multi presenter mode is enabled for the conference.
 *
 * The value of this property is NO if the call is not a conference call or if the multi-presenter mode is not enabled.
 *
 * @see CSConference::updateMultiplePresentersCapability
 * @see CSConference::setMultiplePresentersAllowed:completionHandler:
 */
@property (nonatomic, readonly, getter=areMultiplePresentersAllowed) BOOL multiplePresentersAllowed;

/**
 * Controls whether there can be multiple presenters (panelists) on the call.
 *
 * @param allowed If @c YES multiple presenters are allowed. If @c NO multiple presenters are not allowed.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::updateMultiplePresentersCapability
 * @see CSConference::multiplePresentersAllowed
 */
- (void)setMultiplePresentersAllowed:(BOOL)allowed completionHandler:(void (^)(NSError *error))handler;


/**
 * CSCapability object indicating whether the local user can control display of the local user's video in
 * the personal video layout received from the conference server.
 *
 * The capability returns not supported if the conference call does not support this feature.
 *
 * Conference video capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::videoSelfSeeActive
 * @see CSConference::setVideoSelfSeeActive:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateVideoSelfSeeCapability;

/**
 * A Boolean value indicating whether the self see option is currently active.
 *
 * @see CSConference::updateVideoSelfSeeCapability
 * @see CSConference::setVideoSelfSeeActive:completionHandler:
 */
@property (nonatomic, readonly) BOOL videoSelfSeeActive;

/**
 * Controls display of the local user's video in
 * the personal video layout received from the conference server.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeVideoSelfSeeStatus: for this CSConference object.
 *
 * @param active If @c YES self see is enabled. If @c NO self see is disabled.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::updateVideoSelfSeeCapability
 * @see CSConference::videoSelfSeeActive
 */
- (void)setVideoSelfSeeActive:(BOOL)active completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can control display of participant names in the
 * personal video layout received from the conference server.
 *
 * The capability returns not supported if the conference call does not support this feature.
 *
 * Conference video capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::participantNameDisplayActive
 * @see CSConference::setDisplayVideoParticipantNameActive:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateDisplayVideoParticipantNameCapability;

/**
 * A Boolean value indicating whether participant name display option is currently active.
 *
 * @see CSConference::updateDisplayVideoParticipantNameCapability
 * @see CSConference::setDisplayVideoParticipantNameActive:completionHandler:
 */
@property (nonatomic, readonly) BOOL participantNameDisplayActive;

/**
 * Controls whether participant names are displayed on the video image received
 * from the conference server.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeDisplayParticipantNameOnVideo: for this CSConference object.
 *
 * @param active If @c YES display of participant names on the video image is active. If @c NO display
 * of participant names on the video image is not active.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::updateDisplayVideoParticipantNameCapability
 * @see CSConference::participantNameDisplayActive
 */
- (void)setDisplayVideoParticipantNameActive:(BOOL)active completionHandler:(void (^)(NSError *error))handler;

/**
 * A Boolean value indicating whether the 'always display active speaker's video' option is currently enabled.
 * 
 * This property cannot be changed programmatically.
 */
@property (nonatomic, readonly) BOOL activeSpeakerVideoAlwaysDisplayed;

/**
 * CSCapability object indicating whether the local user can control the video layout setting 
 * of the video received from the conference server.
 *
 * The capability returns not supported if the conference call does not
 * support video layout setting.
 *
 * Conference video capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::videoLayout
 * @see CSConference::supportedVideoLayouts
 * @see CSConference::setVideoLayout:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *updateVideoLayoutCapability;

/**
 * Current layout of the video image created by the conference server.
 *
 * CSVideoLayoutNone is returned to indicate that the conference server does not support video layout selection.
 *
 * @see CSConference::updateVideoLayoutCapability
 * @see CSConference::supportedVideoLayouts
 * @see CSConference::setVideoLayout:completionHandler:
 */
@property (nonatomic, readonly) CSVideoLayout videoLayout;

/**
 * Sets the local user's personal video layout preference.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeVideoLayout: for this CSConference object.
 *
 * @param layout User selected video layout if the conference server supports the layout selection.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::updateVideoLayoutCapability
 * @see CSConference::supportedVideoLayouts
 * @see CSConference::videoLayout
 */
- (void)setVideoLayout:(CSVideoLayout)layout completionHandler:(void (^)(NSError *error))handler;

/**
 * The list of video layouts that the user can choose from. If the conference server does not
 * support video layout selection, nil is returned.
 *
 * @see CSConference::updateVideoLayoutCapability
 * @see CSConference::videoLayout
 * @see CSConference::setVideoLayout:completionHandler:
*/
@property (nonatomic, readonly) NSArray *supportedVideoLayouts;

/**
 * CSCapability object indicating whether local user can extend the end 
 * time of the conference call, if the conference has an end time set.
 *
 * The capability returns not supported if the conference call does not
 * support meeting extension, or if the local user does not have permission
 * to extend the conference call.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::meetingEndTime
 * @see CSConference::extendMeeting:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *extendMeetingCapability;

/** 
 * Meeting end time if an end time is set for the conference call. A nil
 * value is returned if there is no end time specified for the call.
 *
 * @see CSConference::extendMeetingCapability
 * @see CSConference::extendMeeting:completionHandler:
 */
@property (nonatomic, readonly) NSDate *meetingEndTime;

/**
 * Extends the meeting by the specified amount of time.
 *
 * When the operation is successful, a status update is reported through
 * the CSConferenceDelegate::conference:didChangeMeetingEndTime: for this CSConference object.
 *
 * @param additionalTimeInMinutes Additional time by which the conference call is extended.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::extendMeetingCapability
 * @see CSConference::meetingEndTime
 */
- (void)extendMeeting:(uint32_t) additionalTimeInMinutes completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can end the conference call.
 *
 * The capability returns not supported if the local user does not have permission to
 * end the conference.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 * 
 * @see CSConference::endConferenceWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *endConferenceCapability;

/**
 * CSCapability object indicating whether the local user can retrieve dialing information from the conference server.
 *
 * The capability returns not supported if the local user does not have permission to
 * retrieve dialing information from the conference server.
 * @see CSConference::retrieveDialInInformation
 */
@property (nonatomic, readonly) CSCapability *retrieveDialInInformationCapability;

/**
 * Ends the conference call.
 *
 * This action can only be invoked by a conference moderator.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::endConferenceCapability
 */
- (void)endConferenceWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Retrieves dialing information for the conference call.
 * *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *        @li @c dialingInformation If the operation was successful this parameter will contain a value indicates the result of operation.
 *        If the operation is failed it will be nil
 *
 * @see CSConference::retrieveDialInInformationCapability
 */
- (void)retrieveDialInInformationWithCompletionHander:(void (^)(NSString *dialingInformation, NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can pin a specific participant's video in a specific position
 * of the current video layout. 
 *
 * This capability returns not supported if the conference call
 * does not support video pinning/unpinning, or video pin/unpin requests.
 *
 *Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::pinVideoWithSourcePoint:destinationPoint:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *videoPinCapability;

/**
 * Requests for a specific participant's video to be pinned in a certain area of the video image. 
 *
 * The source and destination coordinates can be any point within a video region inside the video image. 
 * They do not have to be a point at the
 * boundary of the video region. In order to undo a previous video pin operation, the application
 * needs to call CSConference::setVideoLayout:completionHandler: and specify CSVideoLayoutDynamic layout option.
 *
 * @param sourcePoint Coordinates of the participant's initial video position in the video image.
 * The values are in the range 0.0 to 1.0, with 0, 0 referring to the upper left of the video image.
 * @param destinationPoint Coordinates of the participant's final video position in the video image.
 * The values are in the range 0.0 to 1.0, with 0, 0 referring to the upper left of the video image.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::videoPinCapability
 */
- (void)pinVideoWithSourcePoint:(CGPoint)sourcePoint destinationPoint:(CGPoint)destinationPoint completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can raise hand
 * (e.g., to get moderator's or panelists' attention).
 *
 * The capability returns not supported if the conference call does not support raising hand.
 *
 * Raise hand capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::handRaised
 * @see CSConference::raiseHandWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *raiseHandCapability;

/**
 * CSCapability object indicating whether the local user can lower hand 
 * (e.g., lower hand after getting moderator's
 *
 * The capability returns not supported if the conference call does not support lowering hand.
 *
 * Lower hand capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::handRaised
 * @see CSConference::lowerHandWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *lowerHandCapability;

/**
 * Called to raise local user's hand on the conference call to get the moderator's attention,
 * who can unmute and hence allow the participant to speak.
 *
 * If the operation is successful, a participant status update notification is reported through the
 * CSActiveParticipantDelegate associated with the local user's CSActiveParticipant.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::raiseHandCapability
 * @see CSConference::handRaised
 * @see CSConference::lowerHandWithCompletionHandler:
 */
- (void)raiseHandWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Called to lower local user's hand on the conference call to indicate that the user no longer
 * wants to get the moderator's attention.
 * 
 * If the operation is successful, a participant status update notification is reported through the
 * CSActiveParticipantDelegate associated with the local user's CSActiveParticipant.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference:lowerHandCapability
 * @see CSConference::handRaised
 * @see CSConference::raiseHandWithCompletionHandler:
 */
- (void)lowerHandWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * A Boolean value indicating whether the local user's hand is raised.
 *
 * @see CSConference:raiseHandCapability
 * @see CSConference:lowerHandCapability
 * @see CSConference::lowerHandWithCompletionHandler:
 * @see CSConference::raiseHandWithCompletionHandler:
 */
@property (nonatomic, readonly, getter=isHandRaised) BOOL handRaised;

/**
 * CSCapability object indicating whether the local user can mute all participants at once.
 *
 * The capability returns not supported if the conference call does not
 * support this control, or if the local user does
 * not have permission to mute all on the call.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::muteAllParticipantsWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *muteAllParticipantsCapability;

/**
 * CSCapability object indicating whether the local user can unmute all participants at once.
 *
 * The capability returns not supported if the conference call does not
 * support this control, or if the local user does
 * not have permission to unmute all on the call.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::unmuteAllParticipantsWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *unmuteAllParticipantsCapability;

/**
 * Used by a conference moderator to mute all participants on the conference call. 
 *
 * Other moderators, lecturers and presenters are not affected by this call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::muteAllParticipantsCapability
 */
- (void)muteAllParticipantsWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Used by a conference moderator to unmute all participants on the conference call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::unmuteAllParticipantsCapability
 */
- (void)unmuteAllParticipantsWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating the local user can request the conference server to dial out 
 * towards a specified address, for example, to add a new user to the conference call.
 *
 * The capability returns not supported if the conference call does not
 * support the participant dial-out feature, or if the local user does not have
 * permission to initiate dial-out.
 *
 * Conference moderation capabilities are not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::addParticipant:completionHandler:
 * @see CSConference::addParticipantFromCall:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *addParticipantViaDialoutCapability;

/**
 * Add a participant to a call. 
 *
 * If the method is called on a 2-party call, the call is escalated
 * to a conference call. In this case, the CSCallDelegate::call:didChangeConferenceStatus: is called to report call status change.
 * If the method is called on a conference call, the participant is added to the conference call
 * using bridge-assisted dial-out. The method may be called multiple times to add multiple participants to
 * the conference call.
 *
 * @param participant The participant address the server dials out towards.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::addParticipantViaDialoutCapability
 * @see CSConference::addParticipantFromCall:completionHandler:
 */
- (void)addParticipant:(NSString *)participant completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can request the conference server to add a participant from a specified call to current call,
 * for example, to add a new user to the conference call.
 *
 * The capability returns not supported if the conference call does not
 * support the merge feature, or if the local user does not have
 * permission to initiate it.
 *
 * @param callToAdd Call to be merged to the conference call.
 *
 * @see CSConference::addParticipant:completionHandler:
 * @see CSConference::addParticipantFromCall:completionHandler:
 */
- (CSCapability *)getAddParticipantFromCallCapability:(CSCall *)callToAdd;

/**
 * Add participant from a call. 
 *
 * If the method is called on a 2-party call, the two calls are merged together to create a conference call.
 * In this case, the CSCallDelegate::call:didChangeConferenceStatus: is called to report call status change.
 * If the method is called on a conference call, the input argument call is transferred over to the
 * conference call represented by this object. If the user wants to create a conference call by merging multiple existing
 * calls, this method can be called for each of the calls.
 *
 * @param call The call to add to the conference.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::addParticipantViaDialoutCapability
 * @see CSConference::addParticipant:completionHandler:
 */
- (void)addParticipantFromCall:(CSCall *)call completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating the local user can request the conference server to dial out
 * towards a terminal IP address to add a terminal as a new user to the conference call.
 *
 * The capability returns not supported if the conference call does not support the terminal dial-out feature,
 * or if the local user does not have permission to initiate dial-out.
 *
 * @see CSConference::addTerminal:completionHandler:
 */
@property(nonatomic, readonly) CSCapability *addTerminalIPAddressViaDialoutCapability;

/**
 * Add a terminal to a conference call by terminal IP address.
 *
 * The terminal is added using bridge-assisted dial-out. The method may be called multiple times
 * to add multiple terminals to the conference call.
 * In order to cancel dial-out terminal please use the method CSConference::removeParticipant
 *
 * @param terminalIPAddress Terminal IP address to add the terminal to the conference call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::addTerminalIPAddressViaDialoutCapability:
 */
-(void)addTerminal:(NSString *)terminalIPAddress completionHandler:(void(^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can select and remove a participant from the call.
 * 
 * The capability returns not supported if the conference call does not
 * support specification of a participant for removal, or if the local user does not have permission
 * to select and drop a participant from the call.
 *
 * @see CSConference::removeParticipant:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *removeParticipantCapability;

/**
 * Initiates removal of the selected participant from the conference call.
 * 
 * The method call is not successful if this is a two party call or if the server returns an error.
 *
 * For each successful removal, the corresponding CSActiveParticipant object is removed from the conference roster list,
 * and the application is notified through CSConferenceDelegate of this CSConference object.
 *
 * @param participant The participant who is being removed from the call.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::removeParticipantCapability
 */
- (void)removeParticipant:(CSActiveParticipant *)participant completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the last participant can be dropped from the call. 
 *
 * @see CSConference::removeLastParticipantWithCompletionHandler:
 */
@property (nonatomic, readonly) CSCapability *removeLastParticipantCapability;

/**
 * Removes the last participant that was added to a conference call either locally or remotely.
 * 
 * This method can only be used for conference calls where CSConference::removeLastParticipantCapability
 * indicates that this operation is supported. As a result of removing the last party,
 * if the participant count goes down to 2, the CSCall object may transition to a 2-party call.
 * In this case, CSCallDelegate::call:didChangeConferenceStatus: is called to report call status change.
 * Calling this method on non-CM conference calls returns an error.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::removeLastParticipantCapability
 */
- (void)removeLastParticipantWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can accept or deny
 * a pending participant's request to enter a locked conference call.
 * 
 * Local user is not allowed to access/deny a pending participant, if the conference call
 * does not support the feature, or if the local user does not have permission to accept/deny a
 * pending participant's entry request, or if there is no one waiting to be admitted to the call.
 *
 * Accept/Deny pending participant capability is not supported when the client is used in shared control mode.
 * See CSSharedControlService.
 *
 * @see CSConference::pendingParticipants
 */
@property (nonatomic, readonly) CSCapability *acceptDenyPendingParticipantCapability;

/**
 * Request for permission to enter a locked conference call.
 * 
 * This is preceded by CSConferenceDelegate::conferenceDidRequirePermissionToEnter:
 * callback to the application. If the user decides to request permission to
 * enter the locked conference call, this method should be called.
 * If the user decides not to request permission from the moderator, CSCall::end should be called to
 * end local user's connection to the conference call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If the operation
 *        is pending approval the parameter contains an object with @c code of CSErrorPendingApproval.
 *        If an error occurred it contains an object describing the error.
 */
- (void)sendRequestToEnterLockedConferenceWithCompletionHandler:(void (^)(NSError *error))handler;

/**
 * Request for admission to enter a conference call that is passcode-protected.
 * 
 * This is preceded by CSConferenceDelegate::conference:didRequirePasscode:
 * callback to the application.
 * If the user provides passcode to enter the conference call,
 * this method should be called. If the user does not want to provide passcode, CSCall::end: should be
 * called to end the local endpoint's participation to the conference call.
 *
 * @param passcode Admission passcode.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)sendPasscode:(NSString*) passcode completionHandler:(void (^)(NSError *error))handler;

/**
 * CSCapability object indicating whether the local user can sign in
 *
 * The capability returns not supported if the conference call does not
 * support sign in, or if the local user does not have permission
 * to sign in.
 *
 * @see CSConference::signIn:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *signInCapability;

/**
 * A Boolean value indicating whether the call is an event conference or a regular conference.
 */
@property (nonatomic, readonly, getter=isEventConference) BOOL eventConference;

/**
 * Sign in local user.
 *
 * When the operation is successful
 *
 * @param portalUserToken User token received from the portal.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see CSConference::signInCapability
 */
- (void)signInWithPortalUserToken:(NSString *)portalUserToken completionHandler:(void (^)(NSError *error))handler;

@end


/**
 * CSConferenceDelegate is registered as an observer of conference status update notifications.
 *
 * The client application is notified about status updates reported by the conference server
 * through the CSConferenceDelegate object. These updates may be the result of local operations
 * on the CSConference object as well as remote changes initiated by either the server or other 
 * users on the conference call.
 * For example if the local user is a conference moderator, (s)he may call CSConference::startRecordingWithCompletionHandler:,
 * resulting in the delegate CSConferenceDelegate::conference:didChangeRecordingStatus: being invoked.
 * Similarly, a remote conference moderator may start conference recording, which will result in receipt of a network 
 * notification, invoking the same delegate.
 *
 * It should be noted that the set of notifications depends on the capabilities of the
 * conference server.  In some conference server environments, some of the delegates may
 * never be invoked because the server does not support the underlying services/features that
 * result in those notifications.
 *
 * @see CSConference
 */
@protocol CSConferenceDelegate <NSObject>

/**
 * Sent to report that the conference has not started, and the local user is waiting
 * for the conference to start. 
 * 
 * At this point, the conference server may provide
 * wait treatment to the end user, e.g., by playing music and/or displaying a still video image.
 * This information is reported based on an indication received from the conference server
 * and may not be provided depending on the server's capabilities.
 *
 * @param conference The conference sending the message.
 */
- (void)conferenceWaitingToStart:(CSConference *)conference;

/**
 * Sent when the conference has started.
 *
 * Called only when CSConferenceDelegate::conferenceWaitingToStart: is previously called.
 *
 * @param conference The conference sending the message.
 */
- (void)conferenceDidStart:(CSConference *)conference;

/**
 * Sent when the capabilities of the conference have changed.
 *
 * The listener can query the CSConference object to find out about the capability that changed. 
 * Usually, the capabilities changed notification is tied to the features supported by the conference 
 * server as well as the local user's role (e.g., moderator, presenter, lecturer, etc.) for the 
 * conference call.
 *
 * @param conference The conference sending the message.
 */
- (void)conferenceCapabilitiesDidChange:(CSConference *)conference;

/**
 * Sent when the conference recording has failed.
 *
 * @param conference The conference sending the message.
 */
- (void)conferenceRecordingDidFail:(CSConference *)conference;

/**
* Sent when the conference subject has changed.
*
* @param conference The conference sending the message.
* @param subject The new subject of the conference.
*/

- (void)conference:(CSConference *)conference didChangeSubject:(NSString *)subject;

/**
 * Sent when the conference brand name has changed.
 *
 * @param conference The conference sending the message.
 * @param brandName The new brand name of the conference.
 */
- (void)conference:(CSConference *)conference didChangeBrandName:(NSString *)brandName;

/**
 * Sent when the lock status of the conference has changed as a result of a local or remote operation.
 *
 * @param conference The conference sending the message.
 * @param locked The new lock status.
 *
 * @see CSConference::locked
 * @see CSConference::setLocked:completionHandler:
 */
- (void)conference:(CSConference *)conference didChangeLockStatus:(BOOL)locked;

/**
 * Sent when the lecture mode status of the conference has changed as a result of a local or remote operation.
 *
 * @param conference The conference sending the message.
 * @param active @c YES if lecture mode is active, @c NO if it is inactive.
 *
 * @see CSConference::lectureModeActive
 * @see CSConference::setLectureModeActive:completionHandler:
 */
- (void)conference:(CSConference *)conference didChangeLectureModeStatus:(BOOL)active;

/**
 * Sent when the entry/exit tone status of the conference has changed as a result of a local or remote operation.
 *
 * @param conference The conference sending the message.
 * @param active @c YES if lecture mode is active, @c NO if it is inactive.
 *
 * @see CSConference::entryExitToneActive
 * @see CSConference::setEntryExitToneActive:completionHandler:
 */
- (void)conference:(CSConference *)conference didChangeEntryExitToneStatus:(BOOL)active;

/**
 * Sent when the continuation status of the conference has changed as a result of a local or remote operation.
 *
 * @param conference The conference sending the message.
 * @param active @c YES if continuation is active, @c NO if it is inactive.
 *
 * @see CSConference::continuationActive
 * @see CSConference::setContinuationActive:completionHandler:
 */
- (void)conference:(CSConference *)conference didChangeContinuationStatus:(BOOL)active;

/**
 * Sent when the recording status of the conference has changed as a result of a local or remote operation.
 *
 * @param conference The conference sending the message.
 * @param status New conference recording status.
 *
 * @see CSConference::recordingActive
 * @see CSConference::recordingPaused
 * @see CSConference::startRecordingWithCompletionHandler:
 * @see CSConference::stopRecordingWithCompletionHandler:
 * @see CSConference::pauseRecordingWithCompletionHandler:
 * @see CSConference::resumeRecordingWithCompletionHandler:
 */
- (void)conference:(CSConference *)conference didChangeRecordingStatus:(CSConferenceRecordingStatus)status;

/**
 * Sent when the overall media encryption status of the conference has changed based on the encryption status
 * of current participants on the call.
 *
 * @param conference The conference sending the message.
 * @param status New media encryption status.
 *
 * @see CSConference::encryptionStatus
 */
- (void)conference:(CSConference *)conference didChangeEncryptionStatus:(CSConferenceEncryptionStatus)status;

/**
 * Sent when the overall streaming status of the conference has changed based on the streaming status
 * of current conference the call.
 *
 * @param conference The conference sending the message.
 * @param status New streaming status.
 *
 * @see CSConference::streamingStatus
 */
- (void)conference:(CSConference *)conference didChangeStreamingStatus:(CSConferenceStreamingStatus)status;

/**
 * Sent when the automatic end time of the conference call has changed.
 *
 * @param conference The conference sending the message.
 * @param meetingEndTime End time of the conference call.
 *
 * @see CSConference::extendMeeting:completionHandler:
 */
- (void)conference:(CSConference *)conference didChangeMeetingEndTime:(NSDate *)meetingEndTime;

/**
 * Sent when video is allowed or disallowed for the conference as a result of a local
 * or remote operation.
 *
 * @param conference The conference sending the message.
 * @param allowed @c YES if video is allowed, @c NO if it is disallowed.
 *
 * @see CSConference::videoAllowed
 * @see CSConference::setVideoAllowed:completionHandler:
 */
- (void)conference:(CSConference *)conference didChangeVideoStatus:(BOOL)allowed;

/**
 * Sent when the option to display self-see video in video image has changed.
 *
 * @param conference The conference sending the message.
 * @param active @c YES if the self-see video option is active, @c NO if it is not active.
 *
 * @see CSConference::videoSelfSeeActive
 * @see CSConference::setVideoSelfSeeActive:completionHandler:
 */
- (void)conference:(CSConference *)conference didChangeVideoSelfSeeStatus:(BOOL)active;

/**
 * Sent when the option to display video participant name on video image has changed.
 *
 * @param conference The conference sending the message.
 * @param active @c YES if the option to display video participant name on video image is active, @c NO if it is not active.
 *
 * @see CSConference::participantNameDisplayActive
 * @see CSConference::setDisplayVideoParticipantNameActive:completionHandler:
 */
- (void)conference:(CSConference *)conference didChangeDisplayParticipantNameOnVideo:(BOOL)active;

/**
 * Sent when the option to always display the active speaker's video has changed.
 *
 * @param conference The conference sending the message.
 * @param active @c YES if the option to always display the active speaker's video is active, @c NO if it is not active.
 *
 * @see CSConference::activeSpeakerVideoAlwaysDisplayed
 */
- (void)conference:(CSConference *)conference didChangeAlwaysDisplayActiveSpeakerVideo:(BOOL)active;

/**
 * Sent when the current video layout setting has been changed by the conference server.
 * 
 * @param conference The conference sending the message.
 * @param layout Current video layout.
 *
 * @see CSConference::videoLayout
 * @see CSConference::setVideoLayout:completionHandler:
 */
- (void)conference:(CSConference *)conference didChangeVideoLayout:(CSVideoLayout)layout;

/**
 * Sent when the list of video layouts supported by the conference server for the current call
 * has changed.
 * 
 * @param conference The conference sending the message.
 * @param layouts List of supported video layouts.
 *
 * @see CSConference::supportedVideoLayouts
 */
- (void)conference:(CSConference *)conference didChangeSupportedVideoLayouts:(NSArray *)layouts;

/**
 * Sent when local user's hand is raised (due to local hand raise operation)
 *
 * @param conference The conference sending the message.
 *
 * @see CSConference::handRaised
 * @see CSConference::raiseHandWithCompletionHandler:
 * @see CSConference::lowerHandWithCompletionHandler:
 */
- (void)conferenceHandRaised:(CSConference *)conference;

/**
 * Sent when local user's hand has been lowered.
 * This can occur when either the conference moderator or 
 * the local user lowers the hand.
 *
 * @param conference The conference sending the message.
 *
 * @see CSConference::handRaised
 * @see CSConference::raiseHandWithCompletionHandler:
 * @see CSConference::lowerHandWithCompletionHandler:
 */
- (void)conferenceHandLowered:(CSConference *)conference;

/**
 * Sent when the user needs to provide admission passcode before (s)he can be
 * admitted to the conference call. 
 *
 * Upon receiving this event, the client
 * application should prompt user for the conference admission passcode.
 * If user chooses to enter the conference room, the client application
 * needs to call CSConference::sendPasscode:completionHandler:, after collecting 
 * the passcode from the end user.
 * If user chooses not to enter the conference room, the client application
 * needs to CSCall::end: to end the connection to the conference call.
 * 
 * @param conference The conference sending the message.
 * @param permissionToEnterLockedConferenceRequired 
 *        @c YES if the conference room is locked and passcode is required to get in.
 *        @ NO if the conference room is not locked, but passcode is
 * required to get in.
 */
- (void)conference:(CSConference *)conference didRequirePasscode:(BOOL)permissionToEnterLockedConferenceRequired;

/**
 * Sent to report that the user is trying to join a locked conference call that 
 * does not require a passcode for entry. 
 *
 * If the user chooses to request permission
 * from the moderator to enter the call, the application should call
 * CSConference::sendRequestToEnterLockedConferenceWithCompletionHandler:. 
 * If the user chooses not to request permission, the application should CSCall::end:
 * to end the connection to the conference call. It should be noted that
 * a locked conference call may also require admission passcode. In this case,
 * CSConference:conference:didRequirePasscode: is called with permissionToEnterLockedConferenceRequired
 * set to YES.
 * 
 * @param conference The conference sending the message.
 */
- (void)conferenceDidRequirePermissionToEnter:(CSConference *)conference;


/**
 * Sent to report that the conference has a healthy signaling path. 
 *
 * Depending on the network topology, the call session and the conference controls may share 
 * the same signaling connection (e.g., SIP and tunnel CCMP), or may use different connections. 
 * This is why separate service available/unavailable callback is provided for the CSConference object.
 *
 * @param conference The conference sending the message.
 */
- (void)conferenceServiceDidBecomeAvailable:(CSConference *)conference;

/**
 * Sent to report that the conference does not have a healthy signaling path. 
 *
 * Depending on the network topology, the call session and the conference controls may share 
 * the same signaling connection (e.g., SIP and tunnel CCMP), or may use different connections. 
 * This is why separate service available/unavailable callback is provided for the CSConference object.
 *
 * @param conference The conference sending the message.
 * @param error code describing why the conference service became unavailable.
 */
- (void)conference:(CSConference *)conference serviceDidBecomeUnavailable:(NSError *)error;

@optional

/**
 * Sent to report that the list of conference participants has changed.
 *
 * @param conference The conference sending the message.
 * @param changeType The type of change that has occurred to the participant list.
 * @param changedParticipants An array of CSActiveParticipant objects that have changed. For a delete change,
 *                     the supplied objects have been removed from the list.
 *                     For a "collection cleared" change, this array will be empty.
 * @see CSConference::participants
 */
- (void)conference:(CSConference *)conference participantsDidChange:(CSDataCollectionChangeType)changeType changedParticipants:(NSArray *)changedParticipants;

/**
 * Sent to report that the list of participants that have dropped from the conference has changed.
 *
 * @param conference The conference sending the message.
 * @param changeType The type of change that has occurred to the participant list.
 * @param changedParticipants An array of CSDroppedParticipant objects that have changed. For a delete change,
 *                     the supplied objects have been removed from the list.
 *                     For a "collection cleared" change, this array will be empty.
 * @see CSConference::droppedParticipants
 */
- (void)conference:(CSConference *)conference droppedParticipantsDidChange:(CSDataCollectionChangeType)changeType changedParticipants:(NSArray *)changedParticipants;

/**
 * Sent to report that the list of pending conference participants has changed.
 *
 * @param conference The conference sending the message.
 * @param changeType The type of change that has occurred to the participant list.
 * @param changedParticipants An array of CSPendingParticipant objects that have changed. For a delete change,
 *                     the supplied objects have been removed from the list.
 *                     For a "collection cleared" change, this array will be empty.
 * @see CSConference::pendingParticipants
 */
- (void)conference:(CSConference *)conference pendingParticipantsDidChange:(CSDataCollectionChangeType)changeType changedParticipants:(NSArray *)changedParticipants;

/**
 * Sent to report that the list of active talkers in the conference has changed.
 *
 * @param conference The conference sending the message.
 * @param changeType The type of change that has occurred to the participant list.
 * @param changedParticipants An array of CSActiveParticipant objects that have changed. For a delete change,
 *                     the supplied objects have been removed from the list.
 *                     For a "collection cleared" change, this array will be empty.
 * @see CSConference::activeTalkers
 */
- (void)conference:(CSConference *)conference activeTalkersDidChange:(CSDataCollectionChangeType)changeType changedParticipants:(NSArray *)changedParticipants;

/**
 * Sent to report that the list of active talkers in the conference has changed.
 *
 * @param conference The conference sending the message.
 * @param changeType The type of change that has occurred to the participant list.
 * @param changedParticipants An array of CSActiveParticipant objects that have changed. For a delete change,
 *                     the supplied objects have been removed from the list.
 *                     For a "collection cleared" change, this array will be empty.
 * @see CSConference::recentTalkers
 */
- (void)conference:(CSConference *)conference recentTalkersDidChange:(CSDataCollectionChangeType)changeType changedParticipants:(NSArray *)changedParticipants;

/**
 * Sent when the external admission status for the current conference call has changed.
 *
 * @param conference The conference sending the message.
 * @param required Current conference's external admission status.
 */
- (void)conference:(CSConference *)conference didChangeExternalAdmissionStatus:(BOOL)required;

/**
 * Sent during a multi video channel conference call when a video channel's receive
 * status changes, e.g., when the server starts or stops
 * sending video packets over a video channel represented by the videoChannel argument.
 * Server may stop sending video, when, for example, the number of video participants falls 
 * below a certain number, no long requiring a negotiated video channel. It is recommended that the
 * video renderer associated with the video channel remain allocated, as the
 * number of video participants on the call may increase, resulting in video transmission
 * by the server over the video channel.
 * @param conference  The conference sending the message.
 * @param videoChannel Video channel whose video receive status has changed.
 * @param receiving @c YES if video channel has started receiving video packets, @c NO 
 *                  the channel has stopped receiving video packets.
 */
- (void)conference:(CSConference *)conference videoChannelReceiveStatusDidChange:(CSVideoChannel *)videoChannel receiveStatus:(BOOL) receiving;

/**
 * Sent to report during a multi video channel conference call that the active video participant
 * received over a video channel has changed. The video channel id information is provided
 * in participant argument. This information can be used to render the display name of the video
 * participant in the video rendering area associated with the specified video channel.
 * @param conference  The conference sending the message.
 * @param participant Participant whose video is received over specified video channel
 *                    identified by CSActiveParticipant::videoChannelId:.
 * @see CSActiveParticipant::videoChannelId
 */
- (void)conference:(CSConference *) conference didActiveVideoParticipantChange:(CSActiveParticipant *)participant;

/**
 * Sent when conference type has changed.
 * Event conference is a large meeting (up to 2000 active participants) which is mainly used for large events and training.
 *
 * @param conference The conference sending the message.
 * @param eventConferenceStatus True if conference type changed to Event type. False - changed to Regular.
 */
- (void)conference:(CSConference *)conference didChangeEventConferenceStatus:(BOOL)eventConferenceStatus;
@end
