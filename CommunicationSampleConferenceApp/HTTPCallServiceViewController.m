/******************************************************************************/
/*                                                                            */
/* Copyright Avaya Inc.                                                       */
/*                                                                            */
/******************************************************************************/

#import "HTTPCallServiceViewController.h"
#import "SDKManager.h"
#import "CSCall+Additions.h"
#import "ActiveCallViewController.h"
#import "NotificationHelper.h"
#import "ConfigData.h"
#import "CTRegex.h"
#import "GNAudio.h"
#import "CTAppInfo.h"

#import <PgyUpdate/PgyUpdateManager.h>

NSString *const kIDErrorDesc = @"输入会议ID不正确，请检查";
NSString *const kGetMediaAuthority = @"audioAndVideoAuthor";


 extern NSString *const WZ_HSS_bundleId;



@interface HTTPCallServiceViewController ()

@property (nonatomic) CSCall *currentCall;
@property (nonatomic) UITapGestureRecognizer *tap;

@end

@implementation HTTPCallServiceViewController



- (void)viewDidLoad {
    [super viewDidLoad];
    
    //Set delegate to hide keyboard on iPhone
    self.conferenceURLTextField.delegate = self;
    self.displayNameTextField.delegate = self;
    self.conferenceUsernameTextField.delegate = self;
    self.conferencePasswordTextField.delegate = self;
    self.conferenceIDTextField.delegate = self;
    //Hide keyboard once clicked outside of Phone Pad
    self.tap = [[UITapGestureRecognizer alloc]
                initWithTarget:self
                action:@selector(dismissKeyboard)];
    
    [self.view addGestureRecognizer:self.tap];
    
    // Restore UI from saved configuration
    [self restoreConfiguration];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refresh:) name:kRefreshWindowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(userDidRegister:) name:kUserDidRegisterNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(userDidFailToRegister:) name:kUserDidFailToRegisterNotification object:nil];
    
    NSLog(@"%s start user auto-login", __PRETTY_FUNCTION__);
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
        
        // Create user in async task
        [[SDKManager getInstance] setupClient];
    });
    
    self.titleLabel.text = [ConfigData getInstance].tanShi_Name ;
    self.conferenceIDTextField.clearButtonMode = UITextFieldViewModeWhileEditing ;
    [self setPGY];
    [self setUpUI];
}


- (void)setUpUI {

    if ([[CTAppInfo appBundleId] isEqual:WZ_HSS_bundleId]) {
        self.titleLabel.hidden = YES ;
        self.idLabel.text = @"远程会诊探视ID：" ;
        [self.makeVideoCallLabel setTitle:@"开始" forState:UIControlStateNormal ] ;
    }
    
}

- (void)viewWillAppear:(BOOL)animated
{
    [[UIApplication sharedApplication] setIdleTimerDisabled:NO];
}

    

- (void)dealloc{
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kRefreshWindowNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kUserDidRegisterNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kUserDidFailToRegisterNotification object:nil];

    [self.view removeGestureRecognizer:self.tap];
}

- (void)setPGY {
        //启动更新检查SDK
    [[PgyUpdateManager sharedPgyManager] startManagerWithAppId:[ConfigData getInstance].PGY_APP_ID];
    [[PgyUpdateManager sharedPgyManager] checkUpdate];

}

- (IBAction)makeVideoCall:(UIButton *)sender {
    
        
    NSString *ID = self.conferenceIDTextField.text ;
//     温州火神山不判断一下类容
    if (![[CTAppInfo appBundleId] isEqual:WZ_HSS_bundleId]) {
        if(![CTRegex is6Number:ID] ) {

            [NotificationHelper displayToastToUser:kIDErrorDesc complete:nil];
            return;
        }

    }
    
    
    if (![[NSUserDefaults standardUserDefaults] objectForKey:kGetMediaAuthority]) {
        
        [GNAudio requestAudioAndVideoAuthor:^{
            
            [self checkAuthority];
        }];
        return ;
    }
    
    [self checkAuthority];
}


- (void)checkAuthority {
    
    [GNAudio audioAndVideoAuthor:^{
        
        [self gotoActiveCall] ;

    }] ;
    
}

- (void)dismissKeyboard {
    [self.conferenceURLTextField resignFirstResponder];
    [self.conferenceIDTextField resignFirstResponder];

}

- (void)setBorderWidth:(UIButton *)btn
{
    btn.layer.borderWidth = 0.5f;
}

- (void)gotoActiveCall {
    
    UIActivityIndicatorView *_active = [self setActivityIndicator] ;
    [self createCallWithCompletionHandler:^(NSError *error) {
    
        [_active stopAnimating];
        [_active removeFromSuperview];
        if (error == nil) {
            
            [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
            [self performSegueWithIdentifier:@"videoCallSegue" sender:nil] ;
        
        }
 
    }] ;
}

- (UIActivityIndicatorView *)setActivityIndicator {
    
    //创建
    UIActivityIndicatorView *_active = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
//    _active.color = [UIColor redColor];
    _active.frame = self.view.frame ;
    //控件中心坐标
    _active.center = self.view.center  ;
    //开启动画
    [_active startAnimating];
    _active.hidesWhenStopped = YES;
    //添加
    [self.view addSubview:_active];

    return  _active;
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    
    
    UINavigationController *navigationController = [segue destinationViewController];
    if (![navigationController isKindOfClass:[UINavigationController class]]) {
        return;
    }
    ActiveCallViewController *transferViewController = (ActiveCallViewController *)[navigationController topViewController];
    
    if ([segue.identifier isEqualToString:@"audioCallSegue"]) {
        NSLog(@"%s Perform Audio call segue", __PRETTY_FUNCTION__);
        NSLog(@"%s currentCall = [%@]", __PRETTY_FUNCTION__, self.currentCall);
        [self audioCall];
        transferViewController.currentCall = self.currentCall;
            
    } else if ([segue.identifier isEqualToString:@"videoCallSegue"]) {
        NSLog(@"%s Perform Video call segue", __PRETTY_FUNCTION__);
        NSLog(@"%s currentCall = [%@]", __PRETTY_FUNCTION__, self.currentCall);
        [self videoCall];
        transferViewController.currentCall = self.currentCall;
    }
}

- (void)audioCall {
    
    AVAudioSession *audioSession = [AVAudioSession sharedInstance];
    
    if (![audioSession setActive:YES error:nil]) {
        NSLog(@"Failed to create audio Session for audio call");
    }
    
    if (![audioSession setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:(AVAudioSessionCategoryOptionAllowBluetooth | AVAudioSessionCategoryOptionMixWithOthers) error:nil]) {
    }
    
    [self.currentCall start];
    
}

- (void)videoCall {
    
    [[SDKManager getInstance].mediaManager configureVideoForOutgoingCall:self.currentCall withVideoMode:CSVideoModeSendReceive];
    
    AVAudioSession *audioSession = [AVAudioSession sharedInstance];
    
    if (![audioSession setActive:YES error:nil]) {
        NSLog(@"Failed to create audio Session for video call");
    }
    
    if (![audioSession setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:(AVAudioSessionCategoryOptionAllowBluetooth | AVAudioSessionCategoryOptionMixWithOthers) error:nil]) {
    }
    
    [self.currentCall start];
}

- (void)createCallWithCompletionHandler:(void(^)(NSError*))completionHandler {
    // Update configuration with UI data
    ConfigData *configuration = [self saveConfiguration];
    // Retrieve the token and other meeting details
    [self.unifiedPortalService
     requestToJoinMeetingWithConfiguration: configuration.unifiedPortalConfiguration
     conferenceId: configuration.conferenceID
     userName: configuration.displayName
     presentationOnlyMode: NO
     callbackNumber: @""
     oneTimePin: @""
     completionHandler:
     ^(CSUnifiedPortalMeetingInfo *meetingInfo, NSError *error)
        {
         if(error != nil)
         {
//             self.messageLabel.text = [NSString stringWithFormat:@"Join failed with error: %@", [error localizedDescription]];
             
            NSString *desc = @"" ;
            NSInteger code = error.code ;
            switch (code) {
                case 27:
                    desc = kIDErrorDesc ;
                    break;
                case -1:
                    desc = @"网络异常，无法进入会议室" ;
                    break;
                default:
                    desc = @"还未到指定探视时间" ;
                    break;
            }
             [NotificationHelper displayToastToUser:desc complete:nil];
             
         }
         else
         {
             self.messageLabel.text = @"";
             
             CSCallCreationInfo *callCreationInfo = [[CSCallCreationInfo alloc] init];
             callCreationInfo.callType             = CSCallTypeHttpMeetme;
             callCreationInfo.conferenceId         = configuration.conferenceID;
             callCreationInfo.conferencePasscode   = @"";
             callCreationInfo.portalToken          = meetingInfo.portalToken;
             callCreationInfo.uccpURL              = meetingInfo.uccpURL;
             callCreationInfo.serviceGatewayURL    = meetingInfo.serviceGatewayURL;
             callCreationInfo.portalURL            = configuration.portalURL;
             callCreationInfo.meetmeUserName       = configuration.displayName;
             callCreationInfo.presentationOnlyMode = NO;
             
             CSCall *call;
             call = [self.callService createCallWithInfo: callCreationInfo];
             call.remoteAddress = configuration.conferenceID;
             
             self.currentCall = call;
         }
         completionHandler(error);
     }];
}

- (IBAction)guestLoginSwitchValueChanged:(id)sender {
    BOOL loginAsGuest = self.guestLoginSwitch.on;
    
    self.displayNameLabel.enabled = loginAsGuest;
    self.displayNameTextField.enabled = loginAsGuest;
    self.conferenceUsernameLabel.enabled = !loginAsGuest;
    self.conferenceUsernameTextField.enabled = !loginAsGuest;
    self.conferencePasswordLabel.enabled = !loginAsGuest;
    self.conferencePasswordTextField.enabled = !loginAsGuest;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    
    if (textField == self.conferenceIDTextField) {
        
        [textField resignFirstResponder];
        if (self.guestLoginSwitch.on) {
            [self.displayNameTextField becomeFirstResponder];
        } else {
            [self.conferenceUsernameTextField becomeFirstResponder];
        }
    } else if (textField == self.conferenceUsernameTextField) {

        [textField resignFirstResponder];
        [self.conferencePasswordTextField becomeFirstResponder];
    } else {
        
        [textField resignFirstResponder];
    }
    
    return YES;
}

- (void)refresh:(NSNotification *)notification {
    
    CSUser *user = [SDKManager getInstance].user;
    if (user) {
        self.callService = user.callService;
        self.unifiedPortalService = user.unifiedPortalService;
    }
    
    if (self.unifiedPortalService == nil) {
        self.makeVideoCallLabel.hidden = YES;
        self.makeAudioCallLabel.hidden = YES;
        self.messageLabel.text = @"Unified Portal Service is not available";
    }
}

- (void)userDidRegister:(NSNotification *)notification  {
    self.makeVideoCallLabel.hidden = NO;
    self.makeAudioCallLabel.hidden = NO;
    self.messageLabel.text = @"";
}

- (void)userDidFailToRegister:(NSNotification *)notification  {
    self.makeVideoCallLabel.hidden = YES;
    self.makeAudioCallLabel.hidden = YES;
    self.messageLabel.text = @"Unified Portal Service is not available";
}

- (void)restoreConfiguration {
    ConfigData *configuration = [ConfigData getInstance];
    self.guestLoginSwitch.on = configuration.loginAsGuest;
//    self.conferenceURLTextField.text = configuration.conferenceURL;
    
    NSString *conferenceURL = configuration.conferenceURL;
    if (conferenceURL.length > 0) {
        NSArray *temp = [conferenceURL componentsSeparatedByString:@"="];
        if (temp.count > 1) {
            
            self.conferenceIDTextField.text = [temp lastObject ];
        }
    }
    
    
    self.conferenceUsernameTextField.text = configuration.conferenceUsername;
    self.conferenceUsernameTextField.enabled = !configuration.loginAsGuest;
    self.conferencePasswordTextField.text = configuration.conferencePassword;
    self.conferencePasswordTextField.enabled = !configuration.loginAsGuest;
    self.displayNameTextField.text = configuration.displayName;
    self.displayNameTextField.enabled = configuration.loginAsGuest;
}

- (ConfigData *)saveConfiguration {
    ConfigData *configuration = [ConfigData getInstance];
    
    configuration.conferenceURL = [NSString stringWithFormat:@"%@%@",[ConfigData getInstance].conference_Default_URL,self.conferenceIDTextField.text];
    
    configuration.loginAsGuest = self.guestLoginSwitch.on;
    configuration.displayName = (self.displayNameTextField.text.length > 0)? self.displayNameTextField.text : @"Guest";
    configuration.conferenceUsername = self.conferenceUsernameTextField.text;
    configuration.conferencePassword = self.conferencePasswordTextField.text;
    [configuration saveConfiguration];
    return configuration;
}

//https://conferencing1.brightel.com.cn
//测试会议ID：299999和299998 两个。
//“您的姓名”可以默认写一个，CHIT也可以的。或者LSS（雷神山缩写）

@end

