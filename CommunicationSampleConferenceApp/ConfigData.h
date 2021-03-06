/******************************************************************************/
/*                                                                            */
/* Copyright Avaya Inc.                                                       */
/*                                                                            */
/******************************************************************************/

#import <Foundation/Foundation.h>
#import <AvayaClientServices/AvayaClientServices.h>
#import "ClientCredentialProvider.h"

@interface ConfigData : NSObject

@property (nonatomic, readwrite) NSString *conferenceUsername;
@property (nonatomic, readwrite) NSString *passCode;

@property (nonatomic, readwrite) NSString *conferencePassword;
@property (nonatomic, readwrite) NSString *displayName;
@property (nonatomic, readwrite) BOOL loginAsGuest;
@property (nonatomic, readwrite) NSString *conferenceURL;

@property (nonatomic, readwrite) NSString *conferenceID;
@property (nonatomic, readwrite) NSURL *portalURL;


@property (nonatomic, readwrite) NSString *tanShi_Name;
@property (nonatomic, readwrite) NSString *conference_Default_URL;
@property (nonatomic, readwrite) NSString *PGY_APP_ID;


+ (instancetype) getInstance;

- (CSUserConfiguration *) userConfigurationFromConfigData;
- (CSVoIPConfigurationAudio *) audioConfigurationFromConfigData;
- (CSVoIPConfigurationVideo *) videoConfigurationFromConfigData;
- (CSUnifiedPortalConfiguration *) unifiedPortalConfiguration;

- (void) saveConfiguration;

@end
