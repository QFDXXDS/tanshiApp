/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSDataRetrievalWatcher.h"
#import "CSConferenceMobileLinkConnectionDetails.h"
#import <AvayaClientMedia/CSSpeakerDevice.h>

@protocol CSConferenceMobileLinkDelegate;

/**
 * Enumeration represemting the mobile link connection status to a conference room system.
 */
typedef NS_ENUM(NSInteger, CSConferenceMobileLinkConnectionStatus) {
	/**
	 * Mobile link not connected.
	 */
	CSConferenceMobileLinkNotConnected,
	/**
	 * Mobile link is connecting.
	 */
	CSConferenceMobileLinkConnecting,
	/**
	 * Mobile link connection established.
	 */
	CSConferenceMobileLinkConnected,
	/**
	 * Mobile link disconnecting.
	 */
	CSConferenceMobileLinkDisconnecting
};

/**
 * Interface object representing mobile link feature of a conference call.
 */
@interface CSConferenceMobileLink : NSObject

/**
 * The delegate used to handle mobile link related events.
 */
@property (nonatomic, weak) id<CSConferenceMobileLinkDelegate> delegate;

/**
 * Set Audio device that will be used for playing Sonic signal during room system(s) discovery.
 * @param speaker Speaker device.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)setAudioDevice:(CSSpeakerDevice *)speaker completionHandler:(void (^)(NSError *error))handler;

/**
 * Initiates discovery of room system(s) that are in the vicinity of this application.
 *
 * @param watcher A DataRetrievalWatcher object, created by the application, to track the progress of the requested
 * operation. Prior to calling this method, the application should have
 * installed a {@link CSDataRetrievalWatcherDelegate} on the watcher object to
 * receive notifications on the progress of the retrieval.
 * The data items returned to the application via the watcher object will be of type {@link CSConferenceRoomSystemInformation}.
 */
- (void)discoverWithWatcher: (CSDataRetrievalWatcher *)watcher;

/**
 * Initiates mobile link connection to the specified room system. The room system address may be
 * obtained through mobile link discovery, or through manual provisioning of the room system's
 * IP address by the the end user.
 * @param address Network address of the room system to which the mobile link connection is initiated.
 * @param passcode Optional Passcode required for mobile link connection setup.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */

- (void)connectToAddress:(NSString *)address passcode:(NSString *)passcode statusHandler:(void (^)(NSError *error))handler;

/**
 * Ends an existing mobile link connection to a room system.
 *
 * @param disconnectRoomSystem Whether the room system should be disconnected from the meeting.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)disconnectIncludingRoomSystem:(BOOL)disconnectRoomSystem completionHandler:(void (^)(NSError *error))handler;


/**
 * Address of the currently connected conference room system.
 */
@property (nonatomic, readonly) NSString *currentRoomSystemAddress;

/**
 * The participant id of the connected conference room system.
 */
@property (nonatomic, readonly) NSString *roomSystemParticipantId;

/**
 * Current connection status.
 */
@property (nonatomic, readonly) CSConferenceMobileLinkConnectionStatus connectionStatus;


@end


/**
 * Describes methods that are implemented by the delegate of a @c CSConferenceMobileLink.
 */
@protocol CSConferenceMobileLinkDelegate <NSObject>

/**
 * Called when the mobile link connection is established.
 *
 * @param conferenceMobileLink The mobileLink object that has connected to a room system.
 * @param conferenceMobileLinkConnectionDetails The connection details.
 */
- (void)conferenceMobileLink: (CSConferenceMobileLink *)conferenceMobileLink didConnect: (CSConferenceMobileLinkConnectionDetails *)conferenceMobileLinkConnectionDetails;

/**
 * Called when the mobile link connection is over.
 *
 * @param conferenceMobileLink The mobileLink object that has connected to a room system.
 * @param endedRemotely Flag indicating whether mobile link connection was ended by 
 * the server, or by the local user.
 */
- (void)conferenceMobileLink: (CSConferenceMobileLink *)conferenceMobileLink didDisconnect: (BOOL) endedRemotely;

@end
