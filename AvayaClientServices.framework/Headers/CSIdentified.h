/* Copyright Avaya Inc. */

/**
 * Interface for SDK objects that have persistent and unique IDs within their
 * scope.
 * There's support here for getting the ID as either a long integer or a string,
 * so that clients can use whichever of the two is most convenient for them.
 * The two representations of the ID must be consistent and unchanging.
 */

#import <Foundation/Foundation.h>

@interface CSIdentified : NSObject

- (instancetype)initWithIntegerID:(NSInteger)integerID;
/**
 * Get the item's ID as a long integer.
 *
 * @return The item's ID as a long integer.
 */
@property (nonatomic, readonly) NSInteger integerID;

/**
 * Get the item's ID as a string.
 *
 * @return The item's ID as a string.
 */
@property (nonatomic, readonly) NSString *stringID;
@end
