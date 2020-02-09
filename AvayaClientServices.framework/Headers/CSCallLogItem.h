/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCapability.h"
#import "CSCallCreationInfo.h"
#import "CSCall.h"

/**
 * Describes the media source type of the call log.
 */
typedef NS_ENUM(NSInteger, CSCallLogSourceType) {
	/** The media type is not defined. */
	CSCallLogSourceTypeUndefined = 0,
	/** A voice only call. */
	CSCallLogSourceTypeVoice,
	/** A voice call with video. */
	CSCallLogSourceTypeVideo,
	/** Instant message conversation. */
	CSCallLogSourceTypeIm,
	/** Call log loaded from the client (i.e. for EC500 feature). */
	CSCallLogSourceTypeEC500
};

/**
 * Describes the action type that generated the call log item or the call log event.
 */
typedef NS_ENUM(NSInteger, CSCallLogActionType) {
	/** The action type is not defined. */
	CSCallLogActionTypeUndefined = 0,
	/** A missed call. The incoming call was not answered by the client. */
	CSCallLogActionTypeMissed,
	/** A call was redirected to another destination (e.g. voicemail). */
	CSCallLogActionTypeRedirected,
	/** An incoming call was answered by the client. */
	CSCallLogActionTypeAnswered,
	/** An outbound call from the client. */
	CSCallLogActionTypeOutgoing,
	/** A call was transferred from the client to another destination. */
	CSCallLogActionTypeTransferred,
	/** An incoming call. */
	CSCallLogActionTypeIncoming

};

/** Represents information about a call log item. Each call record is represented by a CallLogItem object that 
 * provides several attributes such as call start time, remote address, call duration, etc. In addition, each 
 * CallLogItem may be associated with a Contact object which may be used to provide picture caller ID or
 * a customized name for the remote party of a call log item.
 * @see CSContact
 */
@interface CSCallLogItem : NSObject

/** CallLogItem constructor with parameters. */
- (instancetype)initWithRemoteNumber:(NSString *)remoteNumber localUserName:(NSString *)localUserName sessionSubject:(NSString*)sessionSubject startTime:(NSDate *)startTime endTime:(NSDate *)endTime durationInSeconds:(NSInteger)durationInSeconds sourceType:(CSCallLogSourceType)sourceType actionType:(CSCallLogActionType)actionType isConference:(BOOL)isConference isIgnored:(BOOL)isIgnored isCallerIdPrivate:(BOOL)isCallerIdPrivate callLogParticipants:(NSArray *)callLogParticipants callEvents:(NSArray *)callEvents properties:(NSDictionary *)properties;

/** Local user's identity. */
@property (nonatomic, readonly) NSString *localUserName;

/** Extension of the call owner for bridged line appearances cases. */
@property (nonatomic, readonly) NSString *lineAppearanceOwner;

/**
 * List of remote participants on the call. Contains objects of type CSCallLogParticipant.
 * This list represents those addresses/endpoints/users participated in this leg of the call and does not
 * represent the union of all users who participated in this call. The local user may
 * have conversed with those remoteParticipants listed in callEvents records.
 * @see CSCallLogParticipant
 */
@property (nonatomic, readonly) NSArray *remoteParticipants;

/**
 * List of remote participants on the conference call. Contains objects of type CSCallLogRemoteParticipant.
 * If this call log was, at any time during the call, a conference, this
 * property represents those participants who were in that conference leg
 * of the call. conferenceRemoteParticipants represents a subset of all remoteParticipants
 * in all CSCallLogItem objects represented in callEvents as well as those in the top level
 * CSCallLogItem.
 * @see CSCallLogRemoteParticipant
 */
@property (nonatomic, readonly) NSArray *conferenceRemoteParticipants;

/** Call subject for this call log item. Call subject can be set by the client to get the context of the call.
 * For example the client can set a call subject for the call from the IM window and the CallLogItem will reflect that.
 * Call subject can also be obtained from a conference. 
 */
@property (nonatomic, readonly) NSString *subject;

/**
 * Remote number to be used to redial this call. It represents
 * the address (phone number) to the far end in the call.
 * This value does not imply the call will be completed
 * in all cases.
*/
@property (nonatomic, readonly) NSString *remoteNumber;

/** The call start time (UTC). */
@property (nonatomic, readonly) NSDate *startTime;

/** The call end time (UTC). */
@property (nonatomic, readonly) NSDate *endTime;

/** Duration of the first leg of the call in seconds. */
@property (nonatomic, readonly) NSTimeInterval durationInSeconds;

/** Duration of established call on answer. If the call is not answered then Total duration shows full call duration from the first ring. */
@property (nonatomic, readonly) NSTimeInterval totalDurationInSeconds;

/** The media source type for this call log item (ie. Video, Voice or IM etc). */
@property (nonatomic, readonly) CSCallLogSourceType callLogSourceType;

/** Action type that generated this call log item (ie. Answered or Outgoing etc). */
@property (nonatomic, readonly) CSCallLogActionType callLogActionType;

/** Indicates if the first leg of the call was a conference type. */
@property (nonatomic, readonly, getter=isConference) BOOL conference;

/** Indicates if the call was ever a conference in its life cycle. */
@property (nonatomic, readonly) BOOL wasConference;

/** Indicates if the call was ignored by the local user. */
@property (nonatomic, readonly, getter=isIgnored) BOOL ignored;

/** Indicates if a remote party requested the call id to be private.
 * This property does not provide a mechanism to enforce redial disablement.
 * The property value only provides a guideline for the client behavior. 
 */
@property (nonatomic, readonly, getter=isCallerPrivate) BOOL callerIdPrivate;

/** Indicates if the call record is created for the remote call.*/
@property (nonatomic, readonly, getter=isRemote) BOOL remote;

/** The call type of this call log item. */
@property(nonatomic, readonly) CSCallType callType;

/** The URL of the Unified Portal Server (MeetMe call type only). */
@property(nonatomic, readonly) NSURL *portalURL;

/** The Virtual Room id of the conference call. */
@property(nonatomic, readonly) NSString *conferenceId;

/** The conference passcode used to join the conference call. */
@property(nonatomic, readonly) NSString *conferencePasscode;

/** The name of the Virtual Room. */
@property(nonatomic, readonly) NSString *virtualRoomName;

/** Indicates if the call was created in presentation only mode. */
@property(nonatomic, readonly, getter=isPresentationOnlyMode) BOOL presentationOnlyMode;

/**
 * The current precedence level of call.
 * @see CSPrecedenceLevel
 */
@property (nonatomic, readonly) CSPrecedenceLevel precedenceLevel;

/**
 * The reason why this call was preempted.
 * @see CSPreemptionReason
 */
@property (nonatomic, readonly) CSPreemptionReason preemptionReason;

/** 
 * Indicates if this call log item can be used to redial the remote number.
 * Currently, this capability has a 1:1 mapping to callerIdPrivate.
 * The capability value of Allowed == YES does not imply that the remote
 * number reported in this CSCallLogItem will always result in the call being
 * completed.
 * The return value for this method only indicates whether or not an attempt
 * can be made to redial this log entry. Ultimately, whether or not redial attempts
 * will be successful depends on the ability for the voice network to
 * route the call successfully. This can only be determined by an actual
 * attempt to place the call. 
*/
@property (nonatomic, readonly) CSCapability *redialCapability;

/** 
 * NSArray with CSCallLogItem objects.
 * Collection of call events recorded for the call log. A CSCallLogItem
 * (ie. instance of this class) provides a wholistic view of individual
 * transactions that took place during the lifecycle of a call.
 * After answering an incoming call or a dial out to a remote user, the call can
 * get transferred (ie. remote address is changed in the same call dialog) or
 * redirected/forwarded to a different number/user. These transactions will be captured
 * in the callEvents list. Each event in callEvents list contains the full detail
 * of a CSCallLogItem.
 * @note Note that the CSCallLogItem represents the details of the first leg of the call and
 * entries in callEvents list represent subsequent call transactions.  For example,
 * if a call was made from user A to B, and then user B transferred user A to user C,
 * then CSCallLogItem will represent the initial call leg between A and B, and the 1
 * callEvents item will represent the transferred call leg between A and C.  These 2
 * call legs make up the one call experienced by user A.
*/
@property (nonatomic, readonly) NSArray *callEvents;

/**
 * Map of key/value pair for any additional generic properties for this call log item.
 * @note This is a place holder for future generic name/value pair properties.
*/
@property (nonatomic, readonly) NSDictionary *properties;

/** The count indicates the total number of calls of similar action type (ie. Missed, Outgoing or Incoming etc).
 * For example, if there are 3 "Incoming" calls from the User A, then the call count will be 3
 */
@property(nonatomic, readonly) NSInteger callCount;

/** Indicates an Unique number assosiated with the call log record assigned by the server.
 * For the local call logs, default value will be 0
 */
@property(nonatomic, readonly) NSInteger instanceId;

/** The tag assosiated with the call log item */
@property(nonatomic, readonly) NSString *tag;

/** The hunt group name. */
@property(nonatomic, readonly) NSString *huntGroupName;

/** The hunt group number */
@property(nonatomic, readonly) NSString *huntGroupNumber;

@end
