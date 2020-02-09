/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@class CSOtherPhoneService;
/**
 *  Describes methods that are implemented by the delegate of a @c CSOtherPhoneService.
 */
@protocol CSOtherPhoneServiceDelegate <NSObject>

/**
 * Sent when other phone mode has been activated.
 *
 * @param otherPhoneService The other phone service instance sending the message.
 */
- (void)otherPhoneServiceDidActivate:(CSOtherPhoneService *)otherPhoneService;

/**
 * Sent when other phone mode has been deactivated.
 *
 * @param otherPhoneService The other phone service instance sending the message.
 */
- (void)otherPhoneServiceDidDeactivate:(CSOtherPhoneService *)otherPhoneService;

@end

/** Completion handler for actions performed on the CSOtherPhoneService */
typedef void (^CSOtherPhoneCompletionHandler)(NSError *error);

/**
 * This service provides the user with the ability to direct media to any other phone
 * (typically a cell phone/ home phone) while controlling signaling from the client.
 * Access to the this service is provided by the otherPhoneNumber property on the {@link CSUser} class.
 * When other phone mode is activated, at any given point of time, only one number will
 * be used as the other phone number.
 * For any outgoing or incoming call, there would be one call towards the other phone number
 * and one call towards the target number.
 * Applications would still have a single call, towards the target number to manage.
 * The second call leg towards other phone will be managed internally by Client SDK.
 *
 * @attention following are limitations in other phone mode:
 * @li @c currently video calls are not supported in other phone mode
 * @li @c HTTP calls are not supported in other phone mode
 *
 *
 * <p>The CSOtherPhoneService object provides a set of APIs that allows application developers to
 * activate and deactivate the other phone number.
 * </p>
 *
 * <p>The client application is notified about status updates reported by the other phone services
 * through a delegate that the application adds to the CSOtherPhoneService object.
 * These updates may be the result of local operations on the CSOtherPhoneService object.</p>
 */
@interface CSOtherPhoneService : NSObject

/**
 * Notifications about service state change.
 */
@property (nonatomic, weak) id<CSOtherPhoneServiceDelegate> otherPhoneServiceDelegate;

/**
 * Activates other phone mode using the specified phone number, or updates the
 * phone number if other phone mode is already active.
 *
 * If this method is called while another activation attempt is already in
 * progress, the previous invocation of this method will be cancelled with an
 * error code of CSErrorCancelled and activation will proceed using the
 * @c numberToActivate from the latest invocation.
 *
 * @param numberToActivate The number to be used as active other phone number
 * @param completionHandler The completion handler for this operation.
 *
 */
- (void)activateOtherPhoneModeWithNumber:(NSString *)numberToActivate completionHandler:(CSOtherPhoneCompletionHandler)completionHandler;

/**
 * Deactivates the other phone mode.
 *
 * @param completionHandler The completion handler for this operation.
 */
- (void)deactivateOtherPhoneModeWithCompletionHandler:(CSOtherPhoneCompletionHandler)completionHandler;

/**
 * Other phone number which is currently active .
 *
 */
@property (nonatomic, readonly) NSString *otherPhoneNumber;

@end

