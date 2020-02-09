/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@interface CSSpaceParticipant: NSObject

@property (nonatomic, strong) NSString *profileId;
@property (nonatomic, strong) NSString *lastUpdateTime;
@property (nonatomic, strong) NSString *timezone;
@property (nonatomic, strong) NSString *username;
@property (nonatomic, strong) NSString *email;
@property (nonatomic, strong) NSString *givenName;
@property (nonatomic, strong) NSString *familyName;
@property (nonatomic, strong) NSString *pictureUrl;
@property (nonatomic, strong) NSString *displayName;
@property (nonatomic, strong) NSString *type;

@property (nonatomic, strong) NSArray *emails;
@property (nonatomic, strong) NSArray *permissions;

@end
