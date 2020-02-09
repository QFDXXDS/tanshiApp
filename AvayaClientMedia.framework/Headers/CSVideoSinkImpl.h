//
//  CSVideoSinkImpl.h
//  scpmedia
//
//  Created by David McGarry.
//  Copyright (c) 2015 Avaya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CSVideoCommon.h"

@interface CSVideoSinkImpl : NSObject <CSVideoSink>
{
}
- (id) initWithIVideoSink:(IVideoSink_t*)pVideoSink;

@end
