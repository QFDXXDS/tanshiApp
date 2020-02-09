#import <AvayaClientMedia/CSAudioCodec.h>
#import <AvayaClientMedia/CSAudioDevice.h>
#import <AvayaClientMedia/CSAudioFilePlayerListener.h>
#import <AvayaClientMedia/CSAudioFilePlayer.h>
#import <AvayaClientMedia/CSAudioInterface.h>
#import <AvayaClientMedia/CSAudioRecordPlayStatusListener.h>
#import <AvayaClientMedia/CSAutomaticGainControlConfiguration.h>
#import <AvayaClientMedia/CSAutomaticGainControlMode.h>
#import <AvayaClientMedia/CSBackgroundNoiseGenerationMode.h>
#import <AvayaClientMedia/CSBfcpTransportMode.h>
#import <AvayaClientMedia/CSCongestionControlAlgorithm.h>
#import <AvayaClientMedia/CSCPUThresholdConfiguration.h>
#import <AvayaClientMedia/CSCPUThresholdType.h>
#import <AvayaClientMedia/CSDevice.h>
#import <AvayaClientMedia/CSDeviceListener.h>
#import <AvayaClientMedia/CSDSCPPrecedenceConfiguration.h>
#import <AvayaClientMedia/CSEchoCancellationMobileMode.h>
#import <AvayaClientMedia/CSEchoCancellationMode.h>
#import <AvayaClientMedia/CSForwardErrorCorrection.h>
#import <AvayaClientMedia/CSMaxVideoResolution.h>
#import <AvayaClientMedia/CSMediaLogLevel.h>
#import <AvayaClientMedia/CSMediaLogProvider.h>
#import <AvayaClientMedia/CSMediaServicesInstance.h>
#import <AvayaClientMedia/CSMediaServicesProvider.h>
#import <AvayaClientMedia/CSMicrophoneDevice.h>
#import <AvayaClientMedia/CSNoiseSuppressionMode.h>
#import <AvayaClientMedia/CSOpusCodecProfileMode.h>
#import <AvayaClientMedia/CSSpeakerDevice.h>
#import <AvayaClientMedia/CSVideoCodecVendor.h>
#import <AvayaClientMedia/CSVideoCommon.h>
#import <AvayaClientMedia/CSVideoFrameFileSource.h>
#import <AvayaClientMedia/CSVideoInterface.h>
#import <AvayaClientMedia/CSVideoSplitter.h>
#import <AvayaClientMedia/CSVoiceActivityDetectionMode.h>
#import <AvayaClientMedia/CSVoIPConfigurationAudio.h>
#import <AvayaClientMedia/CSVoIPConfigurationVideo.h>
#import <AvayaClientMedia/CSVideoSinkImpl.h>
#import <AvayaClientMedia/CSVideoSourceImpl.h>

#if TARGET_OS_IPHONE
// iOS specific functionality
#import <AvayaClientMedia/CSAudioInterfaceIOS.h>
#import <AvayaClientMedia/CSIOSDevice.h>
#import <AvayaClientMedia/CSIOSDeviceModel.h>
#import <AvayaClientMedia/CSVideoCapturerIOS.h>
#import <AvayaClientMedia/CSVideoInterfaceIOS.h>
#import <AvayaClientMedia/CSVideoRendererIOS.h>
#else
// OS X specific functionality		
#import <AvayaClientMedia/CSScreenCapturerOSX.h>
#import <AvayaClientMedia/CSVideoCaptureDevice.h>
#import <AvayaClientMedia/CSVideoCaptureFormat.h>
#import <AvayaClientMedia/CSVideoCapturerOSX.h>
#import <AvayaClientMedia/CSVideoRendererOSX.h>
#endif
