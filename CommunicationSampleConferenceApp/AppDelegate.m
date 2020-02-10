/******************************************************************************/
/*                                                                            */
/* Copyright Avaya Inc.                                                       */
/*                                                                            */
/******************************************************************************/

#import "AppDelegate.h"
#import "Constants.h"

//版本：V2.8.9.1 (2018.5.24)
//改变了检查更新 SDK 的机制，现在只通过比较 App 自身的 Version 和 Build 来判断是否有新版本。
//对于 iOS 11 以上的版本，有新版本时，不带回调的检查更新方法将不再跳转到 Safari 。
#import <PgySDK/PgyManager.h>
#import <PgyUpdate/PgyUpdateManager.h>

NSString  * const PGY_APP_ID = @"ae1de8cb87bbd9396d151b91f1779151" ;

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    //Set Incoming Call Alert Object
    [self setPGY];
    // Override point for customization after application launch.
    return YES;
}

- (void)setPGY {
    
    //启动基本SDK
    [[PgyManager sharedPgyManager] startManagerWithAppId:PGY_APP_ID];
    //启动更新检查SDK
    [[PgyUpdateManager sharedPgyManager] startManagerWithAppId:PGY_APP_ID];
    //关闭用户反馈功能(默认开启)：
    [[PgyManager sharedPgyManager] setEnableFeedback:NO];
}

- (void)dealloc {

}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
