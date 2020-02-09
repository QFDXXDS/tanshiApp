//
//  CTRegex.h
//  VidyoSample
//
//  Created by Xianxiangdaishu on 2017/12/7.
//  Copyright © 2017年 com.changhongit. VidyoSample. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CTRegex : NSObject

+ (BOOL)isMobile:(NSString *)mobile ;

+ (BOOL)isValidUrlStr:(NSString *)urlStr ;

+ (BOOL)isNumber:(NSString *)string ;


+ (BOOL)is4Number:(NSString *)string  ;

+ (BOOL)is6Number:(NSString *)string ;

+ (BOOL)isNumberStart:(NSString *)string ;


@end
