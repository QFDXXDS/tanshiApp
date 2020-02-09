/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSPresence.h"
@protocol CSPresenceListSubscriptionDelegate;

/**
 * An ad hoc presence list subscription.
 *
 * <p>
 * This class provides an interface for watching the presence of a group of users specified by their addresses.
 * The addresses must be recognizable by the presence server the user is connected to.
 */
@interface CSPresenceListSubscription : NSObject

 /**
  * The delegate responsible for handling subscription-related events.
  */
@property (nonatomic, weak) id<CSPresenceListSubscriptionDelegate> delegate;

/**
 * Adds an address to the subscription to start watching the presence of the user associated with the specified address.
 * <p>
 * It is allowed to add new addresses to the subscription after the subscription has been started.
 */
- (void)addAddress:(NSString *)address;

/**
 * Removes an address from the subscription.
 * <p>
 * It is allowed to remove addresses from the subscription after the subscription has been started.
 */
- (void)removeAddress:(NSString *)address;

/**
 * Starts the subscription and watching presence for the subscribed addresses.
 */
- (void)start;

/**
 * Stops the subscription.
 */
- (void)stop;

@end

/**
 * Describes methods that are implemented by the delegate of a @c CSPresenceListSubscription.
 */
@protocol CSPresenceListSubscriptionDelegate <NSObject>

/**
 * Sent when presence list subscription has started successfully.
 *
 * @param subscription The subscription sending the message.
 */
- (void)presenceListSubscriptionDidStart:(CSPresenceListSubscription *)subscription;

/**
 * Sent when an unrecoverable failure occurs preventing the subscription from starting.
 *
 * @param subscription The subscription sending the message.
 * @param error An error object describing the failure.
 */
- (void)presenceListSubscription:(CSPresenceListSubscription *)subscription didFailToStartWithError:(NSError *)error;

/**
 * Sent when presence information is received for a remote user.
 *
 * @param subscription The subscription sending the message.
 * @param presence The presence information that was received.
 */
- (void)presenceListSubscription:(CSPresenceListSubscription *)subscription didReceivePresence:(CSPresence *)presence;

/**
 * Sent when the subscription has been stopped either intentionally or as a result of the error.
 *
 * @param subscription The subscription sending the message.
 * @param error An error object describing the failure if any.
 */
- (void)presenceListSubscription:(CSPresenceListSubscription *)subscription didStopWithError:(NSError *)error;

@end
