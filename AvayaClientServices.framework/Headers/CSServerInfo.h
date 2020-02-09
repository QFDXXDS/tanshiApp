/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSTypes.h"

/**
 * Represents a server to communicate with.
 */
@interface CSServerInfo : NSObject

/**
 * The server's host name.
 */
@property (nonatomic, readonly, copy) NSString *hostName;

/**
 * The server port to connect to.
 */
@property (nonatomic, readonly) NSUInteger port;

/**
 * Whether or not the connection to the server should be secure
 */
@property (nonatomic, readonly, getter=isSecure) BOOL secure;

+ (instancetype)serverWithHostName:(NSString *)hostName
							  port:(NSUInteger)port
							secure:(BOOL)secure;

@end
