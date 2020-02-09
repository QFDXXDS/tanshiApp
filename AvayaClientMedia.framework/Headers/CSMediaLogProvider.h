//
//  CSMediaLogProvider.h
//  scpmedia
//
//  Created by John Marshall on 2015-01-22.
//  Copyright (c) 2015 Avaya. All rights reserved.
//

#ifndef clientsdk_CSMediaLogProvider_h
#define clientsdk_CSMediaLogProvider_h
#import <Foundation/Foundation.h>
#import "CSMediaLogLevel.h"

@protocol CSMediaLogProvider <NSObject>

/**
 * @param level The log level of the message.
 * @param tag An optional tag string categorizing the message. May be nil.
 * @param msg The log message.
 */
- (void) onLogMessage:(NSString*)msg WithLevel:(CSMediaLogLevel)level AndTag:(NSString*)tag ;
@end

#endif // clientsdk_CSMediaLogProvider_h
