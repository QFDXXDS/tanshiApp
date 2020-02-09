//
//  CSAutomaticGainControlMode.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-22.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSAutomaticGainControlMode_h
#define clientsdk_CSAutomaticGainControlMode_h
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, CSAutomaticGainControlMode)
{
	CSAutomaticGainControlModeOff = 0,
	CSAutomaticGainControlModeDefault,
	CSAutomaticGainControlModeNative,

	CSAutomaticGainControlModeAdaptiveAnalog,
	CSAutomaticGainControlModeAdaptiveDigital,
	CSAutomaticGainControlModeFixedDigital
};


#endif // clientsdk_CSAutomaticGainControlMode_h
