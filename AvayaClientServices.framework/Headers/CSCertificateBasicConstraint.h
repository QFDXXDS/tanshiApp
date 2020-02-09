/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Basic constraint certificate extension
 */
@interface CSCertificateBasicConstraint : NSObject

/**
 * is certificate authority
 */
@property (readonly, nonatomic) BOOL certificateAuthority;

/**
 * allowed path length
 */
@property (readonly, nonatomic) NSInteger pathLength;

@end
