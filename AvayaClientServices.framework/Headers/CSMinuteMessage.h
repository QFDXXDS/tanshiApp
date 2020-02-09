/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSParticipant.h"

/**
 * Possible types of minute message in the conference.
 *
 * @see CSMinuteMessage::status
 */
typedef NS_ENUM(NSInteger, CSMinuteType) {
	/** Minute message is a note. */
	CSMinuteTypeNote = 1,
	/** Minute message is a keyword. */
	CSMinuteTypeKeyword,
	/** Minute message is a question. */
	CSMinuteTypeQuestion,
	/** Minute message is an action. */
	CSMinuteTypeAction,
	/** Type of minute message is unknown. */
	CSMinuteTypeUnknown
};

/**
 * Possible states for a meeting minute message in conference.
 *
 * @see CSMinuteMessage::status
 */
typedef NS_ENUM(NSInteger, CSMinuteStatus) {
	/**Response from server is not received yet. */
	CSMinuteStatusPending,
	/** Minute has been successfully sent to server and response has been received. */
	CSMinuteStatusConfirmed,
	/** Server returned an error while adding minute to conference. */
	CSMinuteStatusError,
	/** Minute has been removed from conference. */
	CSMinuteStatusDeleted,
	/** Status of minute message is unknown */
	CSMinuteStatusUnknown,
};

/**
 * **Unsupported:**
 * The meeting minutes feature is currently not supported.
 * The CSMinuteMessage object represent message that can be sent using
 * meeting minutes service.
 * ---
 * **Unsupported:**
 * This class and all of its supporting classes are for internal Avaya use only and should not be
 * used by third party applications at this time. This is an incubating feature that is currently
 * under development and the classes and methods associated with this feature are subject to change
 * at any time. Use of this feature will not be supported by Avaya until such time that it is
 * officially released.
 *
 * @see CSMeetingMinutes
 */
@interface CSMinuteMessage : NSObject

/**
 * The minute message ID associated with the particular minute object.
 */
@property (nonatomic, readonly) NSString *minuteId;

/**
 * Adding date of particular meeting minute object.
 */
@property (nonatomic, readonly) NSDate *date;

/**
 * Content of particular meeting minute object. Can be changed after minute is added
 * to conference and updated using {@link CSMeetingMinutes::updateMinute:completionHandler:}.
 */
@property (nonatomic, readwrite, strong) NSString *content;

/**
 * The type of particular meeting minute object. Can be changed after minute is added
 * to conference and updated using {@link CSMeetingMinutes::updateMinute:completionHandler:}.
 */
@property (nonatomic, readwrite) CSMinuteType type;

/**
 * The participant who added particular minute message.
 */
@property (nonatomic, readonly) CSParticipant *sender;

/**
 * Indicates whether given minute message object is personal minute. Can be changed after minute is added
 * to conference and updated using {@link CSMeetingMinutes::updateMinute:completionHandler:}.
 */
@property (nonatomic, readwrite, getter=isPersonal) BOOL personal;

/**
 * The status of particular meeting minute object.
 */
@property (nonatomic, readonly) CSMinuteStatus status;

/**
 * Indicates whether given minute message object is minute added by local user.
 */
@property (nonatomic, readonly, getter=isMine) BOOL mine;

/**
 * CSCapability object indicating whether the local user can edit particular 
 * meeting minute object in conference.
 *
 * @see CSMeetingMinutes::updateMinute:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *editCapability;

/**
 * CSCapability object indicating whether the local user can remove particular 
 * meeting minute object from conference.
 *
 * @see CSMeetingMinutes::removeMinute:completionHandler:
 */
@property (nonatomic, readonly) CSCapability *deleteCapability;

@end
