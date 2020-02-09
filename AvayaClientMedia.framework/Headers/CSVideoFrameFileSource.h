//
//  CSVideoFrameFileSource.h
//  scpmedia
//
//  Created by David McGarry on 1/28/16.
//  Copyright (c) 2016 Avaya. All rights reserved.
//

#import "CSVideoSourceImpl.h"

@interface CSVideoFrameFileSource : CSVideoSourceImpl

- (instancetype) init;

+ (NSArray *) allowedFileTypes;

- (void) readFromURL:(NSURL *)url
				rate:(uint32_t)rate
			   width:(uint32_t)width
			  height:(uint32_t)height;

- (void) signal;

@end
