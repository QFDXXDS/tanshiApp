//
//  CSEchoCancellationMode.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-22.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSEchoCancellationMode_h
#define clientsdk_CSEchoCancellationMode_h

typedef NS_ENUM(NSInteger, CSEchoCancellationMode)
{
	CSEchoCancelationModeOff = 0,
	CSEchoCancelationModeDefault,
	CSEchoCancelationModeNative,

	CSEchoCancelationModeConference,
	CSEchoCancelationModeAcoustic,
	CSEchoCancelationModeMobile
};

#endif // clientsdk_CSEchoCancellationMode_h
