//
//  CSDevice.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-21.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSDevice_h
#define clientsdk_CSDevice_h
#import <Foundation/Foundation.h>
#import "CSCPUThresholdConfiguration.h"
#import "CSCPUThresholdType.h"
#import "CSMediaLogProvider.h"
#import "CSAudioInterface.h"

@protocol CSDevice <NSObject>

-(void)shutDown;

-(void)setApplicationBackgroundStatus:(BOOL)backgroundStatus;
/**
 * This function sets state for the VMon service. YES will enable VMon on
 * subsequent audio sessions. This will not affect any active audio
 * sessions. The default setting is NO
 *
 * @param address address for the VMon service.
 * @param port for the VMon service
 */
- (void)enableVmon:(NSString*)address ForPort:(int)port;

/**
 * This function sets state for the VMon service. YES will enable VMon on
 * subsequent audio sessions. This will not affect any active audio
 * sessions. The default setting is NO
 */
- (void)disableVmon;


@end //CSDevice : NSObject
#endif // clientsdk_CSDevice_h
