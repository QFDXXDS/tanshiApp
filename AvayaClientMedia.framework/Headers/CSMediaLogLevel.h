//
//  CSMediaLogLevel.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-20.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSLogLevel_h
#define clientsdk_CSLogLevel_h
#import <Foundation/Foundation.h>
                
typedef NS_ENUM(NSUInteger, CSMediaLogLevel)
{
    CSMediaLogLevelNone,
    CSMediaLogLevelError,
    CSMediaLogLevelWarn,
    CSMediaLogLevelInfo,
    CSMediaLogLevelDebug,
    CSMediaLogLevelVerbose
};
#endif
