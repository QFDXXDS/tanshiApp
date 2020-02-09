//
//  CTRegex.m
//  VidyoSample
//
//  Created by Xianxiangdaishu on 2017/12/7.
//  Copyright © 2017年 com.changhongit. VidyoSample. All rights reserved.
//

#import "CTRegex.h"

@implementation CTRegex

+ (BOOL)isMobile:(NSString *)mobile {
    
    NSString *regex = @"^[0-9]*$";
    
    
    return [self regex:regex string:mobile];
    
}
+ (BOOL)isValidUrlStr:(NSString *)urlStr {
    
    NSString * regex = @"^[a-zA-Z0-9:/.]*$";
    
    return [self regex:regex string:urlStr];
}

+ (BOOL)isNumber:(NSString *)string {
    
    NSString * regex = @"^[0-9]*$";
    
    return [self regex:regex string:string];
}
+ (BOOL)is4Number:(NSString *)string {
    
    NSString * regex = @"^[0-9]{4}$";
    
    return [self regex:regex string:string];
}

+ (BOOL)is6Number:(NSString *)string {
    
    NSString * regex = @"^[1-2][0-9]{5}$";
    
    return [self regex:regex string:string];
}

+ (BOOL)isNumberStart:(NSString *)string {
    
    NSString * regex = @"^[1-2]$";
    
    return [self regex:regex string:string];
}


+ (BOOL)regex:(NSString *)regex string:(NSString *)string {
    
    NSPredicate *urlTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", regex];
    return [urlTest evaluateWithObject:string];
}

@end
