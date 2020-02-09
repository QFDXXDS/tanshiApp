//
//  CSAudioCodec.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-20.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSAudioCodec_h
#define clientsdk_CSAudioCodec_h
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, CSAudioCodec)
{
	CSAudioCodecG711A,
	CSAudioCodecG711U,
	CSAudioCodecG722,
	CSAudioCodecG729,
	CSAudioCodecG726_32,
	CSAudioCodecIsac,
	CSAudioCodecOpus    
};
#endif // clientsdk_CSAudioCodec_h
