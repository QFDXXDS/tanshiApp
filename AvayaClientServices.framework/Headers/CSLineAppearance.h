/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

@interface CSLineAppearance : NSObject

@property (nonatomic, readonly) NSInteger lineId;
@property (nonatomic, readonly, getter=isBridged) BOOL bridged;
@property (nonatomic, readonly) NSString *lineOwnerAddress;

- (instancetype)initWithLineId:(NSInteger)lineId bridged:(BOOL)bridged lineOwnerAddress:(NSString *)lineOwnerAddress;
@end

