//
//  CSAutomaticGainControlConfiguration.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-22.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSAutomaticGainControlConfiguration_h
#define clientsdk_CSAutomaticGainControlConfiguration_h
#import <Foundation/Foundation.h>

@interface CSAutomaticGainControlConfiguration : NSObject

@property(nonatomic,getter = isLimiterEnabled)BOOL limiterEnabled;
@property(nonatomic)int targetLevelBOv;
@property(nonatomic)int digitalCompressionGaindB;

-(instancetype)initWithStatus:(BOOL)limiterEnabled AndTargetLevel:(int)targetLevelBOv AndDigitalCompressionGain:(int)digitalCompressionGaindB;
@end
#endif // clientsdk_CSAutomaticGainControlConfiguration_h
