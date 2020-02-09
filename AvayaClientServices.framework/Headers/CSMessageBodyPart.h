/* Copyright Avaya Inc. */
#import <Foundation/Foundation.h>

/**
 * Represents a message body of sip response.
 */
@interface CSMessageBodyPart : NSObject

/**
 * data represents raw body.
 */
@property (nonatomic, readonly) NSData *data;

/**
 * mimeType represents Multipurpose Internet Mail Extensions type of the payload.
 */
@property (nonatomic, readonly) NSString *mimeType;

/**
 * disposition represents disposition of the part.
 */
@property (nonatomic, readonly) NSString *disposition;

/**
 * encoding of the part to help decode the data.
 */
@property (nonatomic, readonly) NSString *encoding;

/**
 * nestedParts of the payload of type CSMessageBodyPart.
 */
@property (nonatomic, readonly) NSArray *nestedParts;

@end
