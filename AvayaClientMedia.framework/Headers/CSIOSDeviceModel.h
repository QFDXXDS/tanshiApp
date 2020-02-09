//
//  CSIOSDeviceModel.h
//  scpmedia
//
//  Created by Rabail Khan on 2014-06-02.
//  Copyright (c) 2014 Avaya. All rights reserved.
//

#ifndef clientsdk_CSIOSDeviceModel_h
#define clientsdk_CSIOSDeviceModel_h
#import <Foundation/Foundation.h>
@interface CSIOSDeviceModel : NSObject

typedef NS_ENUM(NSUInteger, kDeviceModel)
{
    kDeviceModeliPADSimulator = 0,
    kDeviceModeliPAD1,
    kDeviceModeliPAD2,
    kDeviceModeliPAD3,
    kDeviceModeliPAD4,
    kDeviceModeliPADAir,
    kDeviceModeliPADMini,
    kDeviceModeliPADMiniRetina,
    kDeviceModeliPhone5,
    kDeviceModeliPhone5C,
    kDeviceModeliPhone5S,
    kDeviceModeliPhone6,
    kDeviceModeliPADNewerOrUnKnown
};

+ (NSString *)deviceModelName;
+ (kDeviceModel)deviceModel;

@end

#endif //clientsdk_CSIOSDeviceModel_h
