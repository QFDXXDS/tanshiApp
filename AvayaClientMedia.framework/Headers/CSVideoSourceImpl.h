//
//  CSVideoSourceImpl.h
//  scpmedia
//
//  Created by Nathan Peacock.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSVideoSourceImpl_h
#define clientsdk_CSVideoSourceImpl_h
#import <Foundation/Foundation.h>
#import "CSVideoCommon.h"

@interface CSVideoSourceImpl : NSObject <CSVideoSource>
{
}

- (id)initWithIVideoSource:(IVideoSource_t*)pVideoSource;

@end
#endif //  clientsdk_CSVideoSourceImpl_h
