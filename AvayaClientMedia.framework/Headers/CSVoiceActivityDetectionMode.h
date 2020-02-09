//
//  CSVoiceActivityDetectionMode.h
//  scpmedia
//
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSVoiceActivityDetectionMode_h
#define clientsdk_CSVoiceActivityDetectionMode_h

typedef NS_ENUM(NSInteger, CSVoiceActivityDetectionMode)
{
	CSVoiceActivityDetectionModeOff = 0,
	CSVoiceActivityDetectionModeDefault,

	CSVoiceActivityDetectionModeNormal,
	CSVoiceActivityDetectionModeLowBitrate,
	CSVoiceActivityDetectionModeAggressive,
	CSVoiceActivityDetectionModeVeryAggressive
};

#endif
