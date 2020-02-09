//
//  CSVideoInterfaceIOS.h
//  scpmedia
//
//  Created by Rabail Khan on 2015-01-22.
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSVideoInterfaceIOS_h
#define clientsdk_CSVideoInterfaceIOS_h
#import <Foundation/Foundation.h>
#import "CSVideoInterface.h"

@interface CSVideoInterfaceIOS : NSObject <CSVideoInterface>

-(id)initWithVideoEngine:(void*)videoEngine;
@end
#endif // clientsdk_CSVideoInterfaceIOS_h
