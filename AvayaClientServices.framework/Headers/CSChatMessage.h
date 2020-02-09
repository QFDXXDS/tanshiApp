/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSActiveParticipant.h"

/**
* Represents chat message and associated information.
*/
@interface CSChatMessage : NSObject

/**
* Message id.
*/
@property (nonatomic, readonly) NSString *messageId;

/**
* Time of message delivery to the server.
*/
@property (nonatomic, readonly) NSDate *time;

/**
* Message content.
*/
@property (nonatomic, readonly) NSString *message;

/**
* Sender of the message.
*/
@property (nonatomic, readonly) CSParticipant *sender;

/**
* Recipient of the message.
*/
@property (nonatomic, readonly) CSParticipant *recipient;

/**
* True if message is private, false if message is public.
*/
@property (nonatomic, readonly, getter=isPrivate) BOOL privateMessage;

@end
