/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCapability.h"
#import "CSParticipant.h"
#import "CSContentSharingCapabilities.h"
#import "CSRenderingBlock.h"

#import "CSMouseEvent.h"
#import "CSClipboardEvent.h"
#import "CSKeyboardEvent.h"

#if !TARGET_OS_IPHONE
#import "CSSharingApplicationWindow.h"
#import <Cocoa/Cocoa.h>
#endif

@class CSScreenSharingListener;
@protocol CSContentSharingDelegate;
@protocol CSContentSharingRemoteControlDelegate;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"

/**
 * Completion handler used to obtain participants that support remote control.
 *
 * @param participants In case of success NSArray of CSParticipant that support
 *                     remote control, \a nil in case of error.
 * @param error        In case of error contains error information. In case of
 *                     success \a nil value.
 */
typedef void (^CSRemoteControlParticipantsCompletionHandler)(
	NSArray<CSParticipant *> *participants,
	NSError *error);

/**
 * The CSContentSharing object provides access to content sharing related capabilities and actions.
 * This class is used for receiving and sending content sharing. CSContentSharing object is accessible
 * via CSCollaboration. Status updates concerning content sharing are reported via CSContentSharingDelegate.
 * CSContentSharing caches last frame of received content sharing. It's needed in situation
 * when sharing is started before creating UI elements needed to present it.
 *
 *
 * @see CSCollaboration
 * @see CSContentSharingDelegate
 * @see CSScreenSharingListener
 *
 * \if OSX
 * @see CSOSXScreenSharingView
 * \endif
 *
 * \if iOS
 * @see CSIOSScreenSharingView
 * \endif
 */
@interface CSContentSharing :NSObject

/**
 * The delegate used to handle content sharing related events.
 */
@property (nonatomic, weak) id<CSContentSharingDelegate> delegate;

/**
 * Should be created and set by client here and also in the screen sharing view.
 *
 * @see CSContentSharingDelegate
 * \if iOS
 * @see CSIOSScreenSharingView
 * \elseif OSX
 * @see CSOSXScreenSharingView
 * \endif
 */
@property (nonatomic, strong) CSScreenSharingListener *screenSharingListener;

/**
 * The delegate used to handle remote control related events.
 */
@property (nonatomic, weak) id<CSContentSharingRemoteControlDelegate> remoteControlDelegate;

/**
 * Indicates participant who is currently sharing. Returns nil in case sharing is not active.
 */
@property (nonatomic, readonly) CSParticipant *currentPresenter;

#if !TARGET_OS_IPHONE

/**
 * CSCapability object indicating whether sharing full screen is supported.
 *
 * @see CSCollaboration::contentSharingCapability
 */
@property (nonatomic, readonly) CSCapability *shareFullScreenCapability;

/**
 * Indicates whether local user is sharing full screen.
 */
@property (nonatomic, readonly) BOOL isSharingFullScreen;

/**
 * CSCapability object indicating whether sharing application window is supported.
 *
 * @see CSCollaboration::contentSharingCapability
 */
@property (nonatomic, readonly) CSCapability *shareApplicationWindowCapability;

/**
 * Indicates whether local user is sharing application window.
 */
@property (nonatomic, readonly) BOOL isSharingApplicationWindow;

/**
 * CSCapability object indicating whether sharing region of screen is supported.
 *
 * @see CSCollaboration::contentSharingCapability
 */
@property (nonatomic, readonly) CSCapability *sharedScreenRegionCapability;

/**
 * Indicates whether local user is sharing region of screen.
 */
@property (nonatomic, readonly) BOOL isSharingScreenRegion;

/**
 * Deprecated since 3.0.50. Please use CSCollaboration property.
 * @see CSCollaboration::hasPresenterPrivilege
 */
@property (nonatomic, readonly) BOOL hasPresenterPrivilege DEPRECATED_ATTRIBUTE;

/**
 * Indicates whether local user is sharing. 
 */
@property (nonatomic, readonly) BOOL isPresenting;

/**
 * CSCapability object indicating whether the content sharing supports remote control.
 */
@property (nonatomic, readonly) CSCapability *supportRemoteControlCapability;

/**
 * CSCapability object indicating whether the content sharing supports offering a remote control.
 */
@property (nonatomic, readonly) CSCapability *offerRemoteControlCapability;

/**
 * CSCapability object indicating whether the content sharing supports requesting for remote control.
 */
@property (nonatomic, readonly) CSCapability *requestRemoteControlCapability;

/**
 * Returns true if remote control session is currently started and current user is either presenting or
 * remote-controlling the presenter.
 */
@property (nonatomic, readonly) BOOL isRemoteControlOn;

/**
 * Participant who has remote control over any other collaboration participant.
 * Nil in case remote control is not active.
 */
@property (nonatomic, readonly) CSParticipant *remoteController;

/**
 * CSContentSharingCapabilities object containing set of content sharing capabilities
 */
@property (nonatomic,readonly) CSContentSharingCapabilities *sharingCapabilities;

/**
 * CSharingApplicationWindow object. During application sharing it's object of currently shared
 * application window. Otherwise, it's not guaranteed that this object is valid.
 *
 * @see #availableAppWindows
 * @see #startSharingApplicationWindowWithWindow:completionHandler:
 */
@property (nonatomic, readonly) CSSharingApplicationWindow *sharedApplicationWindow;

/**
 * NSDictionary containing objects of CSSharingDisplay. Each CSSharingDisplay can be shared
 * using content sharing method startSharingFullScreenWithScreenId:completionHandler:.
 * Display IDs are keys of this dictionary.
 *
 * @see #startSharingFullScreenWithScreenId:completionHandler:
 * @see ::CSSharingDisplay
 */
@property (nonatomic, readonly) NSDictionary *availableDisplays;

/**
 * NSArray containing CSharingApplicationWindow objects which can be shared using
 * content sharing method {@link startSharingApplicationWindowWithWindow:completionHandler:}.
 * Array contains also windows of client application which can be filtered out using
 * NSWindow::windowNumber and {@link CSSharingApplicationWindow::winId}.
 *
 * @see #startSharingApplicationWindowWithWindow:completionHandler:
 * @see ::CSSharingApplicationWindow
 */
@property (nonatomic, readonly) NSArray *availableAppWindows;

/**
 * CGRect object which indicates frame of the display which is currently shared. 
 * For example, in case of sharing application window, CGRect is frame of shared window.
 * Change of this property is notified by CSContentSharingDelegate::contentSharing:didChangeSharingFrame:.
 * When sharing is not active, it's not guaranteed that this object is valid.
 *
 * @see ::CSContentSharingDelegate::contentSharing:didChangeSharingFrame:
 */
@property (nonatomic, readonly) CGRect sharingFrame;

/**
 * This method is used during application sharing to start scraping additional window besides
 * main application window. To start sharing application window use {@link startSharingApplicationWindowWithWindow:completionHandler:}.
 * Should be used solely during sharing application window, doesn't work without application sharing started and
 * doesn't start application sharing. Method should be used to add custom client windows which are supposed to overlay shared application window.
 * Windows which are added via this method, but doesn't overlay main shared application window, aren't
 * shared. Windows added with this function should be removed with #stopScrapingWindow:
 * or #stopScrapingAllWindows.
 *
 * @param window NSWindow object which should be scrapped besides main application window
 * @param zOrder Ordering of overlapping scraped window images. 
 * A window with a higher z-order value than another window appears on the foreground
 * and may hide a portion of, or entire window with the lower z-order.
 *
 * @see #startSharingApplicationWindowWithWindow:completionHandler:
 * @see #stopScrapingWindow:
 * @see #stopScrapingAllWindows
 */
- (void)startScrapingWindow:(NSWindow *)window withZOrder:(NSUInteger)zOrder;

/**
 * Removes window from which scraping is being performed.
 * It doesn't stop application window sharing.
 * You can't remove the main application window form scraping via this method.
 * It should be used solely during sharing application window.
 *
 * @param window Window object
 *
 * @see #startSharingApplicationWindowWithWindow:completionHandler:
 * @see #startScrapingWindow:withZOrder:
 * @see #stopScrapingAllWindows
 */
- (void)stopScrapingWindow:(NSWindow *)window;

/**
 * Empties the collection of additional windows which are scrapped besides main application window.
 * It doesn't stop application sharing, it doesn't remove main application window from scraping
 * and it doesn't stop sharing application window. It should be used solely during sharing application window.
 *
 * @see #startScrapingWindow:withZOrder:
 * @see #startSharingApplicationWindowWithWindow:completionHandler:
 * @see #stopScrapingWindow:
 */
- (void)stopScrapingAllWindows;

/**
 * Starts sharing full screen. You don't need to stop another sharing before using it.
 * When this method is used while sharing is received, sharing of another participant
 * will be stopped if local user have sufficient permissions (local user is moderator or presenter).
 * Screens possible to share can be obtained using CSContentSharing::availableDisplays.
 *
 * @param screenId ID of screen which should be shared.
 * @param handler Block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see #availableDisplays
 * @see ::CSSharingDisplay
 */
- (void)startSharingFullScreenWithScreenId:(NSInteger)screenId completionHandler:(void (^)(NSError* error))handler;

/**
 * Starts sharing of an application window. You don't need to stop another sharing before using it.
 * When this method is used while sharing is received, sharing of another participant
 * will be stopped if local user have sufficient permissions (local user is moderator or presenter).
 * Application windows possible to share can be obtained by CSContentSharing::availableAppWindows.
 *
 * \note So as to make it possibile to share minimised application and bring application to front
 *		 when sharing is started accessibility API needs to be used. Because of it, when starting sharing
 *		 application, alert is shown. User can allow application to control computer in system preferences or deny it.
 *		 Alert is shown asynchronously.
 *
 *
 * @param window CSSharingApplicationWindow which should be shared
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see #availableAppWindows
 * @see ::CSSharingApplicationWindow
 */
- (void)startSharingApplicationWindowWithWindow:(CSSharingApplicationWindow *)window completionHandler:(void (^)(NSError *error))handler;

/**
 * Starts sharing of a specified screen region. You don't need to stop another sharing before using it.
 * When this method is used while sharing is received, sharing of another participant
 * will be stopped if local user have sufficient permissions (local user is moderator or presenter).
 * Screens possible to share can be obtained using CSContentSharing::availableDisplays. Sharing coordinates 
 * are relative to given screenId.
 *
 * @param screenId ID of screen which should be shared.
 * @param x X coordinate of the bottom left corner in pixels.
 * @param y Y coordinate of the bottom left corner in pixels.
 * @param width Width of the shared region in pixels.
 * @param height Height of the shared region in pixels.
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 *
 * @see #availableDisplays
 */
- (void)startSharingScreenRegionWithScreenId:(NSInteger)screenId posX:(NSInteger)x posY:(NSInteger)y width:(NSInteger)width height:(NSInteger)height completionHandler:(void (^)(NSError* error))handler;

/**
 * Ends content sharing of local user or content sharing of another collaboration 
 * participant if local user has sufficient permissions i.e. is presenter or moderator.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)endWithCompletionHandler:(void (^)(NSError* error))handler;

/**
 * Pauses content sharing of local user. It doesn't pause content sharing of another collaboration participant.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)pauseWithCompletionHandler:(void (^)(NSError* error))handler;

/**
 * Resumes content sharing. It doesn't resume content sharing of another collaboration participant.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)resumeWithCompletionHandler:(void (^)(NSError* error))handler;

/**
 * Grants remote control to given participant. Can be also be invoked as response after
 * ::CSContentSharingRemoteControlDelegate::contentSharing:didReceiveRemoteControlRequest:.
 *
 * @param participant Participant who is offered remote control.
 * @param handler A block to be called when the operation is completed.
 *        @li @c participant Particpant granting remote control.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)grantRemoteControlWithParticipant:(CSParticipant *)participant
						completionHandler:(void (^)(CSParticipant *participant, NSError *error))handler;

/**
 * Denies incoming remote control request of collaboration participant.
 * Shoule be invoked after receiving notification ::CSContentSharingRemoteControlDelegate::contentSharing:didReceiveRemoteControlRequest:.
 *
 * @param participant Participant whose request is to be denied.
 * @param handler A block to be called when the operation is completed.
 *        @li @c participant Participant whose request was denied if operation was succesful.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)denyRemoteControlWithParticipant:(CSParticipant *)participant
					   completionHandler:(void (^)(CSParticipant *participant, NSError* error))handler;

/**
 * Request remote control from current presenter if sharing is active. After presenter response, client is notified
 * with ::CSContentSharingRemoteControlDelegate::contentSharing:didReceiveRemoteControlDeny: or
 * ::CSContentSharingRemoteControlDelegate::contentSharing:didReceiveRemoteControlGrant:.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c participant participant The participant, who request was sent to, if operation was succesful.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)requestRemoteControlWithCompletionHandler:(void (^)(CSParticipant *participant, NSError *error))handler;

/**
 * Decline remote control offer from current presenter for local user. Should be invoked 
 * after receiving ::CSContentSharingRemoteControlDelegate::contentSharing:didReceiveRemoteControlOffer:.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c participant participant The participant whose offer was declined if operation was succesful.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)declineRemoteControlWithCompletionHandler:(void (^)(CSParticipant *participant, NSError *error))handler;

/**
 * Ends remote control session.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c participant The local user data.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)endRemoteControlWithCompletionHandler: (void (^)(CSParticipant *participant, NSError* error))handler;

/**
 * Starts remote control. Should be called after receiving ::CSContentSharingRemoteControlDelegate::contentSharing:didReceiveRemoteControlOffer:.
 * It doesn't need to be called in situation when local user requests remote control and gets grant for remote control because it's invoked
 * internally by Client SDK.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c participant The local user data.
 *		  @li @c error If the operation was successful this parameter is nil. If an error occurred it
 *        contains an object describing the error.
 */
- (void)startRemoteControlWithCompletionHandler:(void (^)(CSParticipant *participant, NSError* error))handler;

/**
 * Sends keyboard event. Client doesn't need to use this method unless custom 
 * sharing view is developed.
 */
- (void)sendKeyboardEvent:(CSKeyboardEvent*)keyboardEvent;

/**
 * Sends mouse event. Client doesn't need to use this method unless custom
 * sharing view is developed.
 */
- (void)sendMouseEvent:(CSMouseEvent*)mouseEvent;

/**
 * Sends clipboard event. Client doesn't need to use this method unless custom
 * sharing view is developed.
 */
- (void)sendClipboardEvent:(CSClipboardEvent*)clipboardEvent;


/**
 * Obtain the participants that support remote control.
 *
 * Before calling the method you need to check that
 * ::CSContentSharing::supportRemoteControlCapability is in allowed state.
 * Otherwise the method call will fail with appropriate error.
 *
 * Since there is no collaboration/content sharing event notification about 
 * a change of participants, client has to rely on corresponding ::CSConference
 * events to be notified about participant list changes. Whenever such 
 * notification occurs, client must expect that remote control participant list
 * might have changed and this method must be called again, if up to date 
 * participant list is to be presented to the user.
 *
 * \see ::CSConference::participants
 *
 * @param completionHandler Completion handler for this operation.
 */
-(void)retrieveRemoteControlParticipantsWithCompletionHandler:(CSRemoteControlParticipantsCompletionHandler)completionHandler;

#endif

@end

/**
 * CSContentSharingDelegate is registered as an observer of content sharing status update notifications.
 *
 * The client application is notified about content sharing status updates reported by the collaboration server
 * through the CSContentSharingDelegate object. These updates may be the result of local operations
 * on the CSContentSharing object as well as remote changes initiated by either the server or other
 * users on the collaboration call.
 *
 * \if OSX
 * @see CSOSXScreenSharingView
 * \endif
 *
 * \if iOS
 * @see CSIOSScreenSharingView
 * \endif
 */
@protocol CSContentSharingDelegate <NSObject>

@optional

/**
 * Reports that content sharing session has been started by other collaboration participant.
 *
 * \if OSX
 * When this delegate method is triggered in the client application, {@link CSContentSharing::isRemoteControlOn} flag
 * is set to true.
 * \endif
 *
 * @param content CSContentSharing sending the message.
 * @param participant CSParticipant object indicating participant who started content sharing.
 */
- (void)contentSharing:(CSContentSharing *)content didStartByParticipant:(CSParticipant *)participant;

/**
 * Reports that content sharing session has been ended by other collaboration participant. Cab be also called so as
 * to indicate that remote control ended between other collaboration participant wihout local user being involved.
 *
 * @param content CSContentSharing sending the message.
 */
- (void)contentSharingDidEnd:(CSContentSharing *)content;

/**
 * Reports that content sharing session has been paused by other collaboration participant.
 *
 * @param content CSContentSharing sending the message.
 */
- (void)contentSharingDidPause:(CSContentSharing *)content;

/**
 * Reports that content sharing session has been resumed by other collaboration participant.
 *
 * @param content CSContentSharing sending the message.
 */
- (void)contentSharingDidResume:(CSContentSharing *)content;

/**
 * Sends information about cursor position with received content sharing.
 * 
 * @param content CSContentSharing sending the message.
 * @param position Cursor coordinates of the received content sharing.
 */
- (void)contentSharing:(CSContentSharing *)content didReceiveCursorPosition:(CGPoint)position;

/**
 * Reports that entire content sharing frame was received from server. It indicates that
 * client screen sharing is ready to be shown to user. Size parameter lets client
 * properly update UI with sharing size if needed.
 *
 * @param content CSContentSharing sending the message.
 * @param frameSize Size of received sharing frame.
 */
- (void)contentSharing:(CSContentSharing *)content didReceiveSharingFrame:(CGSize)frameSize;

/**
 * Reports that sent sharing frame has changed. Invoked when local user changes
 * shared area (e.g. sharing type is changed, shared application window is resized)
 *
 * @param content CSContentSharing sending the message.
 * @param frame Updated frame of shared area.
 */
-(void)contentSharing:(CSContentSharing *)content didChangeSharingFrame:(CGRect)frame;

#if !TARGET_OS_IPHONE

/**
 * Reports change of state of sharing application window. Invoked solely during application 
 * window sharing session (also when application sharing is paused). See CSSharingWindow::CSSharingApplicationWindowState
 * because it can change state of sharing.
 *
 * @param content CSContentSharing sending the message.
 * @param applicationWindowState Updated state of shared application window.
 *
 * @see CSSharingWindow::CSSharingApplicationWindowState
 */
- (void)contentSharing:(CSContentSharing *)content didChangeApplicationWindowState:(CSSharingApplicationWindowState)applicationWindowState;

/**
 * Called when content sharing capabilities have changed.
 */
- (void)contentSharingDidChangeCapabilities:(CSContentSharing *)content;

#endif

@end

/**
 * CSContentSharingRemoteControlDelegate is registered as an observer of content sharing status update notifications
 * concerning remote control.
 *
 * The client application is notified about content sharing status updates reported by the collaboration server
 * through the CSContentSharingRemoteControlDelegate object. These updates may be the result of local operations
 * on the CSContentSharing object as well as remote changes initiated by either the server or other
 * users on the collaboration call.
 *
 *
 * @see ::CSContentSharing
 */
@protocol CSContentSharingRemoteControlDelegate <NSObject>

/**
 * Reports that remote control was ended. Sent also when local user is not in remote control session.
 * Method is not invoked in case remote control was ended by local user.
 *
 * @param content CSContentSharing sending the message.
 * @param participant User who ended remote control.
 *
 * \if OSX
 * @see ::CSContentSharing::endRemoteControlWithCompletionHandler:
 * \endif
 */
-(void)contentSharing:(CSContentSharing *)content didReceiveRemoteControlEnd:(CSParticipant *)participant;

/**
 * Reports that remote control was started.
 *
 * Response for remote control grant \if OSX ::CSContentSharing::grantRemoteControlWithParticipant:completionHandler: \endif,
 * but sent also in case other participants of collaboration started remote control session between them.
 * Method is not invoked in case remote control was started by local user.
 *
 * @param content CSContentSharing sending the message.
 * @param participant User who started remote control.
 *
 * \if OSX
 * @see ::CSContentSharing::startRemoteControlWithCompletionHandler:
 * \endif
 */
-(void)contentSharing:(CSContentSharing *)content didReceiveRemoteControlStart:(CSParticipant *)participant;

/**
 * Reports that outgoing request for remote control was denied by collaboration participant.
 * Invoked when collaboration participant is sharing.
 *
 * @param content CSContentSharing sending the message.
 * @param participant User who declined remote control grant.
 *
 * \if OSX
 * @see ::CSContentSharing::requestRemoteControlWithCompletionHandler:
 * \endif
 */
-(void)contentSharing:(CSContentSharing *)content didReceiveRemoteControlDeny:(CSParticipant *)participant;

/**
 * Reports that collaboration participant decline remote control grant from local user.
 * Invoked when local user is sharing.
 *
 * @param content CSContentSharing sending the message.
 * @param participant User who declined remote control.
 *
 * \if OSX
 * @see ::CSContentSharing::grantRemoteControlWithParticipant:completionHandler:
 * \endif
 */
-(void)contentSharing:(CSContentSharing *)content didReceiveRemoteControlDecline:(CSParticipant *)participant;

/**
 * Reports that local user request for remote control was granted by presenter.
 *
 * \if OSX
 * Receiving this event will not open the remote session. IncomingRemoteControlGrant event only
 * confirms that the current user has rights to start such session.
 *
 * To start remote control session user shall call {@link CSContentSharing::startRemoteControlWithCompletionHandler:}
 * method. It could be done in delegate method or in another moment in the future.
 * \endif
 *
 * @param content CSContentSharing sending the message.
 * @param participant User who granted remote control.
 *
 * \if OSX
 * @see ::CSContentSharing::requestRemoteControlWithCompletionHandler:
 * \endif
 */
-(void)contentSharing:(CSContentSharing *)content didReceiveRemoteControlGrant:(CSParticipant *)participant;

/**
 * Reports that remote control was requested by collaboration participant.
 *
 * \if OSX
 * Invoked when local user is sharing. Can be denied with {@link CSContentSharing::denyRemoteControlWithParticipant:completionHandler:}
 * or accepted with {@link CSContentSharing::grantRemoteControlWithParticipant:completionHandler:}.
 * \endif
 *
 * @param content ::CSContentSharing sending the message.
 * @param participant User who requested remote control.
 */
-(void)contentSharing:(CSContentSharing *)content didReceiveRemoteControlRequest:(CSParticipant *)participant;

/**
 * Reports that remote control was offered by collaboration participant.
 *
 * \if OSX
 * Invoked when collaboration participant is sharing. Can be declined with {@link CSContentSharing::declineRemoteControlWithCompletionHandler:}
 * and accepted with {@link CSContentSharing::startRemoteControlWithCompletionHandler:}.
 * \endif
 *
 * @param content ::CSContentSharing sending the message.
 * @param participant User who offered remote control.
 */
-(void)contentSharing:(CSContentSharing *)content didReceiveRemoteControlOffer:(CSParticipant *)participant;

@end

#pragma clang diagnostic pop
