//
//  CSVideoSplitter.h
//  scpmedia
//
//  Created by David McGarry on 8/4/16.
//  Copyright (c) 2016 Avaya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CSVideoCommon.h"

@interface CSVideoSplitter : NSObject <CSVideoSink>

- (instancetype) initWithVideoSinks:(NSArray*)sinks;

@end
