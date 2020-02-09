//
//  CSVoIPConfigurationVideo.h
//  scpmedia
//
//  Copyright (c) 2015 Avaya. All rights reserved.
//

#ifndef clientsdk_CSVoIPConfigurationVideo_h
#define clientsdk_CSVoIPConfigurationVideo_h

#import <Foundation/Foundation.h>
#import "CSBfcpTransportMode.h"
#import "CSCongestionControlAlgorithm.h"
#import "CSMaxVideoResolution.h"
#import "CSForwardErrorCorrection.h"
#import "CSVideoCodecVendor.h"
#import "CSDSCPPrecedenceConfiguration.h"
#import "CSLayer2PriorityMarking.h"

@interface CSVoIPConfigurationVideo : NSObject

@property(nonatomic,getter = isEnabled)BOOL enabled;
@property(nonatomic,getter = isCpuAdaptiveVideoEnabled)BOOL cpuAdaptiveVideoEnabled;

@property(nonatomic)int dscpVideo;
@property(nonatomic, assign, getter=isAutomaticDscpConfigurationEnabled)BOOL automaticDscpConfigurationEnabled;

@property(nonatomic, assign)int firstVideoPingInterval;
@property(nonatomic, assign)int periodicVideoPingInterval;
@property(nonatomic, assign)int minPortRange;
@property(nonatomic, assign)int maxPortRange;

@property(nonatomic)CSBfcpTransportMode bfcpMode;
@property(nonatomic)CSCongestionControlAlgorithm congestionControlAlgorithm;
@property(nonatomic)int anyNetworkBandwidthLimitKbps;
@property(nonatomic)int cellularNetworkBandwidthLimitKbps;
@property(nonatomic)CSMaxVideoResolution maxVideoResolution;
@property(nonatomic)CSForwardErrorCorrection forwardErrorCorrection;
@property(nonatomic)CSVideoCodecVendor videoCodecVendor;
@property(nonatomic)BOOL enableMultipleVideoStreamSupport;

@property(nonatomic, copy)CSDSCPPrecedenceConfiguration* dscpPrecedenceConfig;

@property(nonatomic)BOOL retransmissionEnabled;
@property(nonatomic)BOOL h264HighProfileEnabled;

@property(nonatomic, assign)CSLayer2PriorityMarking layer2PriorityMarking;

@end
#endif
