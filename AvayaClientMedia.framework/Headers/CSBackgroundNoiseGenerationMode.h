//
//  CSBackgroundNoiseGenerationMode.h
//  scpmedia
//
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSBackgroundNoiseGenerationMode_h
#define clientsdk_CSBackgroundNoiseGenerationMode_h

typedef NS_ENUM(NSInteger, CSBackgroundNoiseGenerationMode)
{
	CSBackgroundNoiseGenerationModeOff = 0,
	CSBackgroundNoiseGenerationModeDefault,
	
	CSBackgroundNoiseGenerationModeOn,
	CSBackgroundNoiseGenerationModeFade
};

#endif
