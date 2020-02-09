/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import <AvayaClientMedia/CSVoIPConfigurationAudio.h>
#import <AvayaClientMedia/CSVoIPConfigurationVideo.h>

/**
 * Media Configuration.
 */
@interface CSMediaConfiguration : NSObject


/**
 * Configuration information for Audio data.
 */
@property(nonatomic, strong) CSVoIPConfigurationAudio *audioConfiguration;

/**
* Configuration information for Video data.
*/
@property(nonatomic, strong) CSVoIPConfigurationVideo *videoConfiguration;


@end
