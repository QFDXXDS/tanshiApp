//
//  CSCPUThesholdType.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-20.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSCPUThresholdType_h
#define clientsdk_CSCPUThresholdType_h
#import <Foundation/Foundation.h>

// Note thse values should be in sync with enums defined in cpu_threshold_config.h
typedef NS_ENUM(NSUInteger, CSCPUThresholdType)
{
    // Consider...
    // X = Client Process CPU Usage percentage, X1 = Configured Process Usage Threshold.
    // Y = Overall CPU Usage percentage, Y1 = Configured Overall CPU Usage Threshold.
    
    CSCPUThresholdTypeBelow = 0,      // This threshold is triggered, if the % of collected samples that meet criteria
    // (X < X1 AND Y < Y1) is greater than the configured thresholdTriggerPercent.
    // When this is triggered, application may choose to step up the video resolution
    // or add additional video streams.
    
    CSCPUThresholdTypeExceed1,        // This threshold is triggered if the % of collected samples that meet criteria
    // (X > X1 OR Y > Y1) is greater than the configured thresholdTriggerPercent.
    // When this is triggered, application should consider step down the video
    // resolution (or remove video streams in case of multi stream video).
    
    CSCPUThresholdTypeExceed2         // This threshold is triggered if the % of collected samples that meet criteria
    // (X > X1 OR Y > Y1) is greater than the configured thresholdTriggerPercent.
    // When this is triggered, application should consider step down the video
    // resolution (or remove video streams in case of multi stream video). If the
    // current video resolution is the lowest possible, application shall try to
    // de-escalate the video call to audio.
    // *** NOTE: This should not be configured with CPU and Process usage threshold
    // values lesser than CPUThresholdTypeExceed1 ***.
    
};
#endif // clientsdk_CSCPUThresholdType_h
