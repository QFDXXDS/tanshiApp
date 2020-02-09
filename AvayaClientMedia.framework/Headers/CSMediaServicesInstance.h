//
//  CSMediaServicesInstance.h
//  scpmedia
//
//  Copyright (c) 2015 Avaya. All rights reserved.
//

#ifndef clientsdk_CSMediaServicesInstance_h
#define clientsdk_CSMediaServicesInstance_h
#import <Foundation/Foundation.h>
#import "CSDevice.h"
#import "CSAudioInterface.h"
#import "CSVideoInterface.h"
#import "CSVoIPConfigurationAudio.h"
#import "CSVoIPConfigurationVideo.h"
#import "CSMediaLogProvider.h"

@interface CSMediaServicesInstance : NSObject

/**
 * Init with set audio and video configurations
 * @param voIPaudioConfig The configured audio settings.
 * @param voIPvideoConfig The configured video settings.
 *
 * @return self.
 */
- (id)initWithAudio:(CSVoIPConfigurationAudio*)voIPaudioConfig AndVideo:(CSVoIPConfigurationVideo*)voIPvideoConfig;

+ (CSMediaLogLevel)logLevel;
+ (void)setLogLevel:(CSMediaLogLevel)level;

+ (void) setLogProvider:(id<CSMediaLogProvider>) provider;
+ (id<CSMediaLogProvider>) logProvider;

+ (NSString*)versionString;

@property (nonatomic, readonly) void* nativeEngine;
@property (nonatomic, readonly) id<CSDevice> deviceInterface;
@property (nonatomic, readonly) id<CSAudioInterface> audioInterface;
@property (nonatomic, readonly) id<CSVideoInterface> videoInterface;

@end

#endif // clientsdk_CSMediaServicesInstance_h
