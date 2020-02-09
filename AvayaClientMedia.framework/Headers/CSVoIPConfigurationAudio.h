//
//  CSVoIPConfigurationAudio.h
//  scpmedia
//
//  Copyright (c) 2015 Avaya. All rights reserved.
//

#ifndef clientsdk_CSVoIPConfigurationAudio_h
#define clientsdk_CSVoIPConfigurationAudio_h
#import <Foundation/Foundation.h>
#import "CSVoiceActivityDetectionMode.h"
#import "CSEchoCancellationMode.h"
#import "CSEchoCancellationMobileMode.h"
#import "CSBackgroundNoiseGenerationMode.h"
#import "CSNoiseSuppressionMode.h"
#import "CSAutomaticGainControlMode.h"
#import "CSAutomaticGainControlConfiguration.h"
#import "CSOpusCodecProfileMode.h"
#import "CSAudioCodec.h"
#import "CSDSCPPrecedenceConfiguration.h"
#import "CSLayer2PriorityMarking.h"

@interface CSVoIPConfigurationAudio : NSObject

@property(nonatomic, assign)BOOL disableSilenceSup;

@property(nonatomic, assign)int dscpAudio;
@property(nonatomic, assign, getter=isAutomaticDscpConfigurationEnabled)BOOL automaticDscpConfigurationEnabled;
@property(nonatomic, assign)int firstPingInterval;
@property(nonatomic, assign)int periodicPingInterval;
@property(nonatomic, assign)int minPortRange;
@property(nonatomic, assign)int maxPortRange;
@property(nonatomic, assign)int dtmfPayloadType;
@property(nonatomic, assign)int opusPayloadType;
@property(nonatomic, strong)NSArray* codecList;

@property(nonatomic, assign)CSVoiceActivityDetectionMode voiceActivityDetectionMode;
@property(nonatomic, assign)CSEchoCancellationMode echoCancellationMode;
@property(nonatomic, assign)CSEchoCancellationMobileMode echoCancellationMobileMode;
@property(nonatomic, assign)CSBackgroundNoiseGenerationMode backgroundNoiseGenerationMode;
@property(nonatomic, assign)CSNoiseSuppressionMode transmitNoiseSuppressionMode;
@property(nonatomic, assign)CSNoiseSuppressionMode receiveNoiseSuppressionMode;
@property(nonatomic, assign)CSAutomaticGainControlMode transmitAutomaticGainControlMode;
@property(nonatomic, assign)CSAutomaticGainControlMode receiveAutomaticGainControlMode;
@property(nonatomic, assign)CSOpusCodecProfileMode opusMode;

@property(nonatomic, copy)NSString* toneFilePath;
@property(nonatomic, copy)CSAutomaticGainControlConfiguration* transmitAutomaticGainControlConfiguration;
@property(nonatomic, copy)CSAutomaticGainControlConfiguration* receiveAutomaticGainControlConfiguration;

@property(nonatomic, copy)CSDSCPPrecedenceConfiguration* dscpPrecedenceConfig;

@property(nonatomic, assign)CSLayer2PriorityMarking layer2PriorityMarking;

@end
#endif
