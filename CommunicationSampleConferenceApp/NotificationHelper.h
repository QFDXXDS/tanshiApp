/******************************************************************************/
/*                                                                            */
/* Copyright Avaya Inc.                                                       */
/*                                                                            */
/******************************************************************************/

#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

@interface NotificationHelper : NSObject

+ (void)displayMessageToUser:(NSString *)msg TAG:(const char[])tag;
+ (void) displayToastToUser: (NSString *) msg complete:(void (^)(void))complete  ;

/// 带cancel的提示
/// @param msg <#msg description#>
/// @param complete <#complete description#>
+ (void)displayToastToUser: (NSString *) msg
                   done:(void (^)(void))done
                    cancel:(void (^)(void))cancel ;


@end
