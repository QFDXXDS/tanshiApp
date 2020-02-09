/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSMinuteMessage.h"
#import "CSDataCollectionChangeType.h"

// When support for DataSet in the public API is removed, delete this #define and any blocks of code that are
// being conditionally compiled by the DATASET_SUPPORTED define.
#define DATASET_SUPPORTED

@class CSDataSet;

@protocol CSMeetingMinutesDelegate;

/**
 * **Unsupported:**
 * The meeting minutes feature is currently not supported.
 * The CSMeetingMinutes object provides access to meeting minutes related capabilities and actions.
 *
 * The CSMeetingMinutes object is accessible via CSConference and CSCollaboration. Client is notified
 * about status updates concerning conference chat via CSMeetingMinutesDelegate object.
 * ---
 * **Unsupported:**
 * This class and all of its supporting classes are for internal Avaya use only and should not be
 * used by third party applications at this time. This is an incubating feature that is currently
 * under development and the classes and methods associated with this feature are subject to change
 * at any time. Use of this feature will not be supported by Avaya until such time that it is
 * officially released.
 *
 * @see CSMeetingMinutesDelegate
 * @see CSCollaboration
 * @see CSConference
 * @see CSMinuteMessage
 */
@interface CSMeetingMinutes : NSObject

/**
 * **Unsupported:**
 * The delegate used to handle meeting minutes related events.
 */
@property (nonatomic, weak) id<CSMeetingMinutesDelegate> delegate;

/**
 * An array of CSMinuteMessage objects representing the minutes of the meeting.
 *
 * The returned array is a snapshot in time and is not dynamically updated as the list changes.
 * Updates to the minutes list (add, remove or update) are reported through the CSMeetingMinutesDelegate via the
 * {@link CSMeetingMinutesDelegate::meetingMinutes:minutesDidChange:changedMinutes: minutesDidChange}
 * message.
 */
@property (atomic, readonly, copy) NSArray *minutes;

#ifdef DATASET_SUPPORTED
/**
 * CSDataSet object containing the minute messages. Property is deprecated.
 * Use the {@link #minutes} property instead.
 */
@property (nonatomic, readonly) CSDataSet *minuteMessages DEPRECATED_ATTRIBUTE;
#endif

/**
 * Adds meeting minute to conference.
 *
 * @param messageContent Content of minute.
 * @param type Type of the conference minute.
 * @param isPersonal Indicates if given minute is personal.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *        @li @c message If the operation was successful this parameter contains sent minute.
 */
- (void)addMinuteMessage:(NSString *)messageContent
                  ofType:(CSMinuteType)type
                personal:(BOOL)isPersonal
       completionHandler:(void (^)(CSMinuteMessage *message, NSError *error))handler;

/**
 * Updates meeting minute.
 *
 * @param minuteMessage Meeting minute to be updated.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *        @li @c message If the operation was successful this parameter contains updated minute.
 */
- (void)updateMinute:(CSMinuteMessage *)minuteMessage
   completionHandler:(void (^)(CSMinuteMessage *message, NSError *error))handler;

/**
 * Removes meeting minute from conference.
 *
 * @param minuteMessage Meeting minute to be removed.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *        @li @c message If the operation was successful this parameter contains removed minute.
 */
- (void)removeMinute:(CSMinuteMessage *)minuteMessage
   completionHandler:(void (^)(CSMinuteMessage *message, NSError *error))handler;

@end

/**
 * **Unsupported:**
 * The meeting minutes feature is currently not supported.
 * Meeting minutes delegate provides updates about the status of minutes service.
 *
 * The client application is notified about status updates reported by the server
 * through the CSMeetingMinutesDelegate object. These updates may be the result of local operations
 * on the CSMeetingMinutesDelegate object as well as remote changes initiated by either the server or other
 * users on the conference call.
 *
 * @see CSChat::delegate
 */
@protocol CSMeetingMinutesDelegate <NSObject>

/**
 * Called when the minutes session started and became available. Minutes can become
 * available/unavailable in case of network disruptions within one call.
 *
 * @param minutes The minutes service sending the message.
 *
 * @see CSMeetingMinutes::meetingMinutesDidReportServiceUnavailable:
 */
- (void)meetingMinutesDidReportServiceAvailable:(CSMeetingMinutes *)minutes;

/**
 * Called when the minutes became unavailable what can be caused by network disruption.
 * It doesn't mean that minutes session has ended.
 *
 * @param minutes The minutes service sending the message.
 *
 * @see CSMeetingMinutes::meetingMinutesDidReportServiceAvailable:
 */
- (void)meetingMinutesDidReportServiceUnavailable:(CSMeetingMinutes *)minutes;

@optional

/**
 * Reports that the list of minutes in the meeting has changed.
 *
 * @param minutes The chat sending the message.
 * @param changeType The type of change that has occurred to the message list.
 * @param changedMinutes An array of CSMinuteMessage objects that have changed. For a delete change,
 *                     the supplied objects have been removed from the list.
 *                     For a "collection cleared" change, this array will be empty.
 *
 * @see CSMeetingMinutes::minutes
 */
- (void)meetingMinutes:(CSMeetingMinutes *)minutes minutesDidChange:(CSDataCollectionChangeType)changeType changedMinutes:(NSArray *)changedMinutes;

/**
 * Reports that new minute message has been received. Methods is deprecated.
 * Use {@link CSMeetingMinutesDelegate::meetingMinutes:minutesDidChange:changedMinutes:} instead.
 */
- (void)meetingMinutes:(CSMeetingMinutes *)minutes didReceiveMinute:(CSMinuteMessage *)minute DEPRECATED_MSG_ATTRIBUTE("Use CSMeetingMinutesDelegate::meetingMinutes:minutesDidChange:changedMinutes: instead");

/**
 * Reports that minute was updated. Methods is deprecated.
 * Use {@link CSMeetingMinutesDelegate::meetingMinutes:minutesDidChange:changedMinutes:} instead.
 */
- (void)meetingMinutes:(CSMeetingMinutes *)minutes didEditMinute:(CSMinuteMessage *)minute DEPRECATED_MSG_ATTRIBUTE("Use CSMeetingMinutesDelegate::meetingMinutes:minutesDidChange:changedMinutes: instead");

/**
 * Reports that minute was deleted. Methods is deprecated.
 * Use {@link CSMeetingMinutesDelegate::meetingMinutes:minutesDidChange:changedMinutes:} instead.
 */
- (void)meetingMinutes:(CSMeetingMinutes *)minutes didDeleteMinute:(CSMinuteMessage *)minute DEPRECATED_MSG_ATTRIBUTE("Use CSMeetingMinutesDelegate::meetingMinutes:minutesDidChange:changedMinutes: instead");

@end
