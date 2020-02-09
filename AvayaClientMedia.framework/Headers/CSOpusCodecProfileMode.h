//
//  CSOpusCodecProfileMode.h
//  scpmedia
//
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSOpusCodecProfileMode_h
#define clientsdk_CSOpusCodecProfileMode_h

typedef NS_ENUM(NSInteger, CSOpusCodecProfileMode)
{
	CSOpusCodecProfileModeOff = -1,
	CSOpusCodecProfileModeDefault,

	CSOpusCodecProfileModeConstrainedNarrowBand,
	CSOpusCodecProfileModeNarrowBand,
	CSOpusCodecProfileModeWideBand,
	CSOpusCodecProfileModeSuperWideBand
};

#endif

