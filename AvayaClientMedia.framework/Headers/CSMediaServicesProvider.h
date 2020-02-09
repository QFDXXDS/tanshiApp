//
//  CSMediaServicesProvider.h
//  scpmedia
//
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSMediaServicesProvider_h
#define clientsdk_CSMediaServicesProvider_h
#import <Foundation/Foundation.h>
#import "CSMediaServicesInstance.h"

@interface CSMediaServicesProvider : NSObject

+ (CSMediaServicesProvider*)instance;

- (CSMediaServicesInstance*)newProviderInstanceWithAudio:(CSVoIPConfigurationAudio*)audioConfig AndVideo: (CSVoIPConfigurationVideo*)videoConfig;

@end

#endif // clientsdk_CSMediaServicesProvider_h
