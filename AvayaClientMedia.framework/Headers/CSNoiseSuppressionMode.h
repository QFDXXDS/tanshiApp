//
//  CSNoiseSuppressionMode.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-22.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSNoiseSuppressionMode_h
#define clientsdk_CSNoiseSuppressionMode_h

typedef NS_ENUM(NSInteger, CSNoiseSuppressionMode)
{
	CSNoiseSuppressionModeOff = 0,
	CSNoiseSuppressionModeDefault,
	CSNoiseSuppressionModeNative,

	CSNoiseSuppressionModeConference,
	CSNoiseSuppressionModeLowSuppression,
	CSNoiseSuppressionModeModerateSuppression,
	CSNoiseSuppressionModeHighSuppression,
	CSNoiseSuppressionModeVeryHighSuppression
};
#endif
