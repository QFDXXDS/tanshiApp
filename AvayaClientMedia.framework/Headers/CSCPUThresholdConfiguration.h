//
//  CSCPUThesholdConfiguration.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-20.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSCPUThresholdConfiguration_h
#define clientsdk_CSCPUThresholdConfiguration_h
#import <Foundation/Foundation.h>
#import "CSCPUThresholdType.h"

@interface CSCPUThresholdConfiguration : NSObject

@property(nonatomic)CSCPUThresholdType thresholdType;

@property(nonatomic)int processCPUUsePercentage;

@property(nonatomic)int totalCPUUsePercentage;

@property(nonatomic)int numOfSamples;

@property(nonatomic)int thresholdTriggerPercentage;



@end

#endif // clientsdk_CSCPUThresholdConfiguration_h
