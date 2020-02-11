//
//  GNAudio.m
//  CHitVideo
//
//  Created by Xianxiangdaishu on 2018/1/24.
//  Copyright © 2018年 changhongit. All rights reserved.
//

#import "GNAudio.h"
#import "NotificationHelper.h"

extern NSString *const kGetMediaAuthority ;


@implementation GNAudio


+ (BOOL)otherAudioPlaying {
    
    return [AVAudioSession sharedInstance].otherAudioPlaying;
}
+ (void)requestAudioAndVideoAuthor:(void (^)(void))complete {
    
    AVAuthorizationStatus audioStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio] ;
    AVAuthorizationStatus videoStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo] ;

    if (audioStatus == AVAuthorizationStatusNotDetermined || videoStatus == AVAuthorizationStatusNotDetermined) {

        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL granted) {

            dispatch_async(dispatch_get_main_queue(), ^{

                [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {

                    [[NSUserDefaults standardUserDefaults] setObject:@(1) forKey:kGetMediaAuthority] ;
                    dispatch_async(dispatch_get_main_queue(), ^{
                        complete();
                    });
                }];
            });

        }];
    }
}

+ (void)audioAndVideoAuthor:(void (^)(void))complete {
    
    if ([self audioAuthor] == AVAuthorizationStatusDenied || [self videoAuthor] == AVAuthorizationStatusDenied ) {

        [NotificationHelper displayToastToUser:@"请打开麦克风和相机权限" done:^{
            
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString] options:@{UIApplicationOpenURLOptionsSourceApplicationKey:@YES} completionHandler:nil];

        } cancel:^{
            complete ? complete() : nil ;
        } ] ;
    } else {
        
        complete ? complete() : nil ;
    }
    
//    if ([self videoAuthor] == AVAuthorizationStatusDenied ) {
//
//        [NotificationHelper displayToastToUser1:@"请打开相机权限" complete:^{
//
//            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString] options:@{UIApplicationOpenURLOptionsSourceApplicationKey:@YES} completionHandler:nil];
//
//        }] ;
//    }
//
}



+ (AVAuthorizationStatus)audioAuthor {
    
    AVAuthorizationStatus audioStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio] ;

    return audioStatus ;
}


+ (AVAuthorizationStatus)videoAuthor {
    
    AVAuthorizationStatus videoStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo] ;

    return videoStatus ;
}



@end
