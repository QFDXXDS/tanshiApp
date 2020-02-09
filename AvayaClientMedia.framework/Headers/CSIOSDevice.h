//
//  CSIOSDevice.h
//  scpmedia
//
//  Created by John Marshall on 2015-01-22.
//  Copyright (c) 2015 Avaya. All rights reserved.
//

#ifndef clientsdk_CSIOSDevice_h
#define clientsdk_CSIOSDevice_h
#import <Foundation/Foundation.h>
#import "CSDevice.h"

@interface CSIOSDevice : NSObject <CSDevice>

- (id)initWithNativeEngine:(void*)engine;

@end

#endif // clientsdk_CSIOSDevice_h
