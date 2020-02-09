/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Enumeration representing presence state of a user.
 */
typedef NS_ENUM(NSUInteger, CSPresenceState) {
	/**
	 * Presence state is not specified.
	 */
	CSPresenceStateUnspecified,
	/**
	 * Presence state is unknown.
	 */
	CSPresenceStateUnknown,
	/**
	 * Presence state is available.
	 */
	CSPresenceStateAvailable,
	/**
	 * Presence state indicating that the user is currently on a call.
	 */	
	CSPresenceStateOnACall,
	/**
	 * Presence state indicating that the user is busy, e.g. in a meeting.
	 */	
	CSPresenceStateBusy,
	/**
	 * Presence state indicating that the user is away from their client.
	 */	
	CSPresenceStateAway,
	/**
	 * Presence state indicating that currently the user does not want other people to contact them.
	 */	
	CSPresenceStateDoNotDisturb,
	/**
	 * Presence state indicating that the user is not in the office.
	 */	
	CSPresenceStateOutOfOffice,
	/**
	 * Presence state indicating that the user is offline, i.e. not using any client.
	 */	
	CSPresenceStateOffline
};

/**
 * Enumeration representing the location-based "mode" of a user.
 *
 * <p>
 * The Location-based "mode" of a user is used when the user wants to publish their location to other
 * users, i.e. make it publicly available.
 */
typedef NS_ENUM(NSUInteger, CSPresenceLocationMode) {
	/**
	 * Location mode is not specified.
	 */
	CSPresenceLocationModeUnspecified,
	/**
	 * Location mode indicating that the user is in the office.
	 */
	CSPresenceLocationModeOffice,
	/**
	 * Location mode indicating that the user is at home.
	 */
	CSPresenceLocationModeHome,
	/**
	 * Location mode indicating that the user is online via a mobile device.
	 */
	CSPresenceLocationModeMobile,
	/**
	 * Location mode indicating that the user is out of office traveling.
	 */
	CSPresenceLocationModeTraveling
};

/**
 * Optional elements of a presence object.
 */
typedef NS_OPTIONS(NSUInteger, CSPresenceOptions) {

	/**
	 * Indicates none of the options are supported.
	 */
	CSPresenceOptionNone         = 0,
	
	/**
	 * Indicates support for a manual (user-assigned) presence state.
	 */
	 
	CSPresenceOptionManualState  = 1U << 0,

	/**
	 * Indicates support for presence location modes.
	 */
	CSPresenceOptionLocationMode = 1U << 1,

	/**
	 * Indicates support for presence notes.
	 */
	CSPresenceOptionNote         = 1U << 2
};

/**
 * Presence information for a user.
 *
 * <p>This class is used to create and set up a desired presence state for a local user (outgoing presence)
 * or get presence states for other users (incoming presence).
 * Presence information is divided into 2 parts: an automatic part and an application part.</p>
 *
 * <p>The automatic part consists of so-called presence channels and their availability.
 * A channel is a way to communicate to a user including communication address and availability of the channel.
 * The channels include a phone channel, a video channel, an IM channel and a calendar channel.
 * For instance, phone channel represents a phone number of a user and current {@link CSPresenceState} of the channel. 
 * If the state of the phone channel is available, the user is able to receive calls. If the state is "on a call", the user is unlikely to accept a new call.
 * The automatic part of presence information is controlled by the library and used for incoming presence only.</p>
 * 
 * <p>The application part of presence information consists of manually published {@link CSPresenceState}, {@link CSPresenceLocationMode} and a note.
 * These are used for both incoming and outgoing presence, and controlled by the application.
 * Application {@link CSPresenceState} is a presence state that a user wants to set their client to.
 * Application {@link CSPresenceLocationMode} is also controlled by the user specifying their current location.
 * Application note is just a short string representing some user comment regarding their current status.</p>
 *
 * <p>Although there are many aspects to presence information, there is also an overall presence state populated automatically.
 * The overall state should be used to represent the state of the user.</p>
 *
 * @see {@link CSPresenceService}
 */
@interface CSPresence : NSObject

/**
 * Specifies the set of supported options for this presence object.
 *
 * <p>Some aspects of the presence object are optional and these options
 * control how the presence publication will manage the tuples associated
 * with the optional elements. For example, if the {@link CSPresenceOptions::CSPresenceOptionNote}
 * option is set and the note string is empty, any existing note on the
 * server will be removed. If the option is not set the note will not be
 * changed.</p>
 */
@property (nonatomic) CSPresenceOptions supportedOptions;

/**
 * Presentity is the address of the user that this presence information is associated with.
 */
@property (nonatomic, readonly) NSString *presentity;

/**
 * For incoming presence, the overall presence state as determined by the availability calculation.
 */
@property (nonatomic, readonly) CSPresenceState overallState;

/**
 * The manual presence state set by the user, if any.
 * <p>
 * If the value of the manual state is CSPresenceStateUnspecified, no manual state is set and the
 * overall presence state is determined automatically.
 */
@property (nonatomic) CSPresenceState manualState;

/**
 * The presence state of the phone channel, if any.
 */
@property (nonatomic) CSPresenceState phoneState;

/**
 * The contact address associated with the phone channel, if any.
 */
@property (nonatomic, readonly) NSString *phoneContact;

/**
 * The presence state of the video channel, if any.
 */
@property (nonatomic) CSPresenceState videoState;

/**
 * The contact address associated with the video channel, if any.
 */
@property (nonatomic, readonly) NSString *videoContact;

/**
 * The presence state of the enterprise instant messaging channel, if any.
 */
@property (nonatomic) CSPresenceState enterpriseIMState;

/**
 * The contact address associated with the enterprise instant messaging channel, if any.
 */
@property (nonatomic, readonly) NSString *enterpriseIMContact;

/**
 * The presence state of the calendar channel, if any.
 */
@property (nonatomic, readonly) CSPresenceState calendarState;

/**
 * The user's appointment or meeting start date associated with the calendar state, if any.
 */
@property (nonatomic, readonly) NSDate *calendarStartDate;

/**
 * The user's appointment or meeting end date associated with the calendar state, if any.
 */
@property (nonatomic, readonly) NSDate *calendarEndDate;

/**
 * The location-based "mode" of the user, if any.
 */
@property (nonatomic) CSPresenceLocationMode locationMode;

/**
 * The presence note.
 */
@property (nonatomic, copy) NSString *note;

@end
