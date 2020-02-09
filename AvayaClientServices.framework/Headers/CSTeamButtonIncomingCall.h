/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@interface CSTeamButtonIncomingCall : NSObject

/**
 * Unique identifier of the Team Button call.
 * Please note that the value will not match the id of the call created as the result of team button pick up.
 */
@property (nonatomic) NSInteger uniqueId;

/**
 * The person's name who has initiated the call.
 */
@property (nonatomic, readonly) NSString *callingName;

/**
 * The person's number  who has initiated the call.
 */
@property (nonatomic, readonly) NSString *callingNumber;

/**
 * The person's name to whom the call is requested.
 */
@property (nonatomic, readonly) NSString *calledName;

/**
 * The person's name to whom the call is requested.
 */
@property (nonatomic, readonly) NSString *calledNumber;

/**
 * Specifies the delay interval in seconds the team button alert should be delayed by.
 */
@property (nonatomic, readonly) NSTimeInterval delayInterval;

/**
 * Picks up a team button call.
 *
 * @param handler A block to be called when the operation is completed.
 *        @li @c error If the operation was successful this parameter is nil. If
 *        an error occurred it contains an object describing the error.
 *
 * @see CSTeamButton::pickupCapability
 */
- (void)pickupWithCompletionHandler:(void (^)(NSError *error))handler;


@end
