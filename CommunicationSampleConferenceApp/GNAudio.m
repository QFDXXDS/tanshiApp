//
//  GNAudio.m
//  CHitVideo
//
//  Created by Xianxiangdaishu on 2018/1/24.
//  Copyright © 2018年 changhongit. All rights reserved.
//

#import "GNAudio.h"
#import <AVFoundation/AVFoundation.h>
#import "NotificationHelper.h"

@implementation GNAudio


+ (BOOL)otherAudioPlaying {
    
    return [AVAudioSession sharedInstance].otherAudioPlaying;
}
+ (void)audioAndVideoAuthor:(void (^)(void))complete {
    
    AVAuthorizationStatus audioStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio] ;
    AVAuthorizationStatus videoStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo] ;

    if (audioStatus == AVAuthorizationStatusNotDetermined || videoStatus == AVAuthorizationStatusNotDetermined) {

        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL granted) {

            complete();
        }];
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {

            complete();
        }];
    } else {
        complete();
    }
}

+ (BOOL)audioAndVideoAuthor {
    
    AVAuthorizationStatus audioStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio] ;
    AVAuthorizationStatus videoStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo] ;

    if (audioStatus == AVAuthorizationStatusDenied ) {

        [NotificationHelper displayToastToUser:@"请打开麦克风权限" complete:^{
            

            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString] options:@{UIApplicationOpenURLOptionsSourceApplicationKey:@YES} completionHandler:nil];
        }] ;
        return NO ;
    }
    if (videoStatus == AVAuthorizationStatusDenied ) {

        [NotificationHelper displayToastToUser:@"请打开相机权限" complete:^{
            
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString] options:@{UIApplicationOpenURLOptionsSourceApplicationKey:@YES} completionHandler:nil];

        }] ;
        return NO ;
    }
    
    return YES ;
}

@end
