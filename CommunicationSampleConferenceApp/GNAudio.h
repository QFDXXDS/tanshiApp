//
//  GNAudio.h
//  CHitVideo
//
//  Created by Xianxiangdaishu on 2018/1/24.
//  Copyright © 2018年 changhongit. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GNAudio : NSObject

+ (BOOL)otherAudioPlaying ;

+ (void)audioAndVideoAuthor:(void (^)(void))complete ;

+ (BOOL)audioAndVideoAuthor ;

@end
