//
//  CSEchoCancellationMobileModeMode.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-22.
//  Copyright (c) 2015 Avaya. All rights reserved.
//

#ifndef clientsdk_CSEchoCancellationMobileMode_h
#define clientsdk_CSEchoCancellationMobileMode_h

typedef NS_ENUM(NSInteger, CSEchoCancellationMobileMode)
{
	CSEchoCancellationMobileModeDefault = 0,

	CSEchoCancellationMobileModeQuietEarpieceOrHeadset,
	CSEchoCancellationMobileModeEarpiece,
	CSEchoCancellationMobileModeLoudEarpiece,
	CSEchoCancellationMobileModeSpeakerphone,
	CSEchoCancellationMobileModeLoudSpeakerphone
};

#endif // clientsdk_CSEchoCancellationMobileMode_h
