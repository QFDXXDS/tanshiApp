/******************************************************************************/
/*                                                                            */
/* Copyright Avaya Inc.                                                       */
/*                                                                            */
/******************************************************************************/

#import "ActiveCallViewController.h"
#import "ConferenceControlViewController.h"
#import "UIViewController+AutoRotation.h"
#import "GNAudio.h"
#import "WHToast/WHToast.h"


#define SCREEN_WIDTH     [UIScreen mainScreen].bounds.size.width
#define SCREEN_HEIGHT    [UIScreen mainScreen].bounds.size.height


@interface ActiveCallViewController ()

@property (nonatomic) UITapGestureRecognizer *tap;
@property (nonatomic, weak) NSTimer *callTimer;
@property (nonatomic) BOOL viewInitialized;
@property (nonatomic, strong) MediaManager *mediaManager;
@property (nonatomic, weak) CSCollaboration *collaboration;
@property (nonatomic, weak) CSContentSharing *contentSharing;

@end

@implementation ActiveCallViewController

- (UIInterfaceOrientationMask)ar_supportedOrientations {
    return UIInterfaceOrientationMaskAllButUpsideDown;
}

-(void)viewWillAppear:(BOOL)animated{
    self.navigationController.navigationBarHidden = YES;
    
}
- (void)statusBar:(NSNotification *)notification {
    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    if (orientation == UIDeviceOrientationLandscapeLeft || orientation == UIDeviceOrientationLandscapeRight) {
        NSLog(@"横屏");
        self.remoteVideoView.frame = CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_WIDTH/16*9);
        self.remoteVideoView.center = CGPointMake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    }else if (orientation == UIDeviceOrientationPortrait) {
        NSLog(@"竖屏");
        self.remoteVideoView.frame = CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_WIDTH/16*9);
        self.remoteVideoView.center = CGPointMake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-50);
    }
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Register for call state change notifications
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(refresh:) name:kRefreshActiveCallWindowNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(statusBar:) name:UIDeviceOrientationDidChangeNotification object:nil];
    
    [[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(audioRouteChangeListenerCallback:)
     name:AVAudioSessionRouteChangeNotification
     object:[AVAudioSession sharedInstance]];
    
    self.remoteVideoView.frame = CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_WIDTH/16*9);
    self.remoteVideoView.center = CGPointMake(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-50);
    
    
    // Display current call status
    self.callState.text = @"";
    
    self.mediaManager = [SDKManager getInstance].mediaManager;
    
    if(self.currentCall.isConference) {
        
        NSLog(@"%s Call is Conference call, populate participant list", __PRETTY_FUNCTION__);
        
        NSArray *participantsNames = [self.currentCall.conference.participants valueForKey:@"displayName"];
        self.participantList.text = [participantsNames componentsJoinedByString:@"\n"];
        
        self.conferenceControlBtnLabel.hidden = !self.currentCall.conference.moderationCapability.allowed;
        
    } else if(self.currentCall.callerIdentityPrivate) {
        
        NSLog(@"%s Call identitiy is private", __PRETTY_FUNCTION__);
        self.participantList.text = @"Restricted";
    } else {
        
        NSLog(@"%s Update caller display name", __PRETTY_FUNCTION__);
        self.participantList.text = self.currentCall.remoteDisplayName;
    }
    
    
    [self speakerOpen];
    
    if ([self isHeadSetPlugging] || [self isBleToothOutput]) {
        [self.speakerButton setBackgroundImage:[UIImage imageNamed:@"扬声器"] forState:UIControlStateNormal];
        self.speakerButton.selected = YES;
        self.speakerButton.userInteractionEnabled = NO;
    }
    
    //Hide keyboard once clicked outside of Phone Pad
    self.tap = [[UITapGestureRecognizer alloc]
                initWithTarget:self
                action:@selector(dismissKeyboard)];
    
    [self.view addGestureRecognizer:self.tap];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        
        if ([GNAudio audioAuthor] == 2) {
            [WHToast showMessage:@"麦克风权限关闭" originY:SCREEN_HEIGHT/2+100 duration:3 finishHandler:^{
                [self.micButton setBackgroundImage:[UIImage imageNamed:@"关闭麦克风-开启"] forState:UIControlStateNormal];
                self.micButton.selected = YES;
            }];
        }
        
        if ([GNAudio videoAuthor] == 2) {
            [WHToast showMessage:@"摄像头权限关闭" originY:SCREEN_HEIGHT/2+150 duration:3 finishHandler:^{
                
            }];
        }

    });
    
}

- (void)audioRouteChangeListenerCallback:(NSNotification *)notification {
    NSDictionary *interuptionDict = notification.userInfo;
    NSInteger routeChangeReason   = [[interuptionDict
                                      valueForKey:AVAudioSessionRouteChangeReasonKey] integerValue];
    switch (routeChangeReason) {
        case AVAudioSessionRouteChangeReasonNewDeviceAvailable:
            //插入耳机时关闭扬声器播放
            [self.speakerButton setBackgroundImage:[UIImage imageNamed:@"扬声器"] forState:UIControlStateNormal];
            self.speakerButton.selected = YES;
            self.speakerButton.userInteractionEnabled = NO;
            break;
        case AVAudioSessionRouteChangeReasonOldDeviceUnavailable:
            //拔出耳机时的处理为开启扬声器播放
            self.speakerButton.userInteractionEnabled = YES;
            [self.speakerButton setBackgroundImage:[UIImage imageNamed:@"扬声器-开启"] forState:UIControlStateNormal];
            self.speakerButton.selected = NO;
            for (CSSpeakerDevice *speaker in [[self.mediaManager audioInterface] availableAudioDevices]) {
                
                if ([speaker.name isEqualToString:@"AudioDeviceSpeaker"]) {
                    [self.mediaManager setSpeaker:speaker];
                    break;
                }
            }
            break;
        case AVAudioSessionRouteChangeReasonCategoryChange:
            // called at start - also when other audio wants to play
            NSLog(@"AVAudioSessionRouteChangeReasonCategoryChange");
            break;
    }
}

- (BOOL)isHeadSetPlugging {
    AVAudioSessionRouteDescription* route = [[AVAudioSession sharedInstance] currentRoute];
    for (AVAudioSessionPortDescription* desc in [route outputs]) {
        if ([[desc portType] isEqualToString:AVAudioSessionPortHeadphones])
            return YES;
    }
    return NO;
}
-(BOOL)isBleToothOutput{
    AVAudioSessionRouteDescription *currentRount = [AVAudioSession sharedInstance].currentRoute;
    AVAudioSessionPortDescription *outputPortDesc = currentRount.outputs[0];
    if([outputPortDesc.portType isEqualToString:@"BluetoothA2DPOutput"]){
        NSLog(@"当前输出的线路是蓝牙输出，并且已连接");
        return YES;
    }else{
        NSLog(@"当前是spearKer输出");
        return NO;
    }
}

- (void)speakerOpen {
    dispatch_time_t delayTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(6.0 * NSEC_PER_SEC));
    
    dispatch_after(delayTime, dispatch_get_main_queue(), ^{
        if ([self isHeadSetPlugging] || [self isBleToothOutput]) {
            //有耳机设备
        }else {
            for (CSSpeakerDevice *speaker in [[self.mediaManager audioInterface] availableAudioDevices]) {
                if ([speaker.name isEqualToString:@"AudioDeviceSpeaker"]) {
                    [self.mediaManager setSpeaker:speaker];
                    break;
                }
            }
        }
    });
    
}

- (void)dealloc {
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kRefreshActiveCallWindowNotification object:nil];
    
    [self.view removeGestureRecognizer:self.tap];
}

- (void)dismissKeyboard {

}

- (void)viewDidDisappear:(BOOL)animated {
    
    [super viewDidDisappear:YES];
    //Release video resources
    [self deallocViews];
}

- (void)setBorderWidth:(UIButton *)btn {
    
    btn.layer.borderWidth = 0.5f;
    btn.layer.borderColor = [[UIColor blackColor]CGColor];
}

- (IBAction)endCallBtnClicked:(id)sender {

    NSLog(@"%s", __PRETTY_FUNCTION__);
    [[SDKManager getInstance] endCall: [self currentCall]];
    [self dismissViewControllerAnimated:YES completion:^{NSLog(@"%s Controller Dismiss", __PRETTY_FUNCTION__);}];
}

- (IBAction)holdCallBtnClicked:(id)sender {
	
    NSLog(@"%s", __PRETTY_FUNCTION__);
    [[SDKManager getInstance] holdOrUnHoldCall:[self currentCall]];

}

- (IBAction)muteSwitchValueChanged:(id)sender {
    
    if (!self.currentCall.audioMuted) {
        
        if(self.currentCall.muteCapability.allowed) {
            
            NSLog(@"%s Call audio can be muted", __PRETTY_FUNCTION__);
            
            [self.currentCall muteAudio: YES completionHandler:^(NSError *error) {
                
                if(error) {
                    
                    [NotificationHelper displayMessageToUser:[NSString stringWithFormat:@"Error while muting audio of call, callId: [%lu]", (long)self.currentCall.callId] TAG:__PRETTY_FUNCTION__];
                } else {
                    
                    NSLog(@"%s Audio Mute succesfful for call, callId: [%lu]", __PRETTY_FUNCTION__, (long)self.currentCall.callId);
                }
            }];
        } else {
            
            NSLog(@"%s Call audio cannot be muted", __PRETTY_FUNCTION__);
        }
    } else {
        
        if(self.currentCall.unmuteCapability.allowed && self.currentCall.audioMuted) {
            
            NSLog(@"%s Call audio can be unmuted", __PRETTY_FUNCTION__);
            
            [self.currentCall muteAudio:NO completionHandler:^(NSError *error) {
                
                if(error) {
                    
                    [NotificationHelper displayMessageToUser:[NSString stringWithFormat:@"Error while muting Audio of the call, callId: [%ld]", (long)self.currentCall.callId] TAG: __PRETTY_FUNCTION__];
                } else {
                    
                    NSLog(@"%s Audio of call muted successfully, callId:[%lu]", __PRETTY_FUNCTION__, (long)self.currentCall.callId);
                }
            }];
        } else {
            
            NSLog(@"%s Call audio cannot be unmuted", __PRETTY_FUNCTION__);
        }
    }
}

- (IBAction)speakerPhoneSwitchValueChanged:(id)sender {

    if (self.speakerPhoneSwitch.on) {

        for (CSSpeakerDevice *speaker in [[self.mediaManager audioInterface] availableAudioDevices]) {

            if ([speaker.name isEqualToString:@"AudioDeviceSpeaker"]) {

                [self.mediaManager setSpeaker:speaker];
                break;
            }
        }
    }else {

        [self.mediaManager setSpeaker:nil];
    }
}

- (void)refresh:(NSNotification *)notification {
    
    if (self.currentCall.videoChannels.count != 0) {
        
        NSLog(@"%s call has Video", __PRETTY_FUNCTION__);
        [self initViews];
    } else {
        
        NSLog(@"%s call doesn't have Video", __PRETTY_FUNCTION__);
        [self deallocViews];
    }
    
    NSString *state = nil;
    
    // Determine current call state
    switch (self.currentCall.state) {
        case CSCallStateIdle:
            state = @"Idle";
            break;
        case CSCallStateInitiating:
            state = @"Initiating";
            break;
        case CSCallStateAlerting:
            state = @"Alerting";
            break;
        case CSCallStateRemoteAlerting:
            state = @"Remote Alerting";
            break;
        case CSCallStateEstablished:
        {
            state = @"Established";
            [self.callTimer invalidate];
            
            self.callTimer = [NSTimer scheduledTimerWithTimeInterval:1
                                                              target:self selector:@selector(callTimer:)
                                                            userInfo:nil repeats:YES];
            break;
        }
        case CSCallStateHolding:
            state = @"Holding";
            break;
        case CSCallStateHeld:
            state = @"Held";
            break;
        case CSCallStateUnholding:
            state = @"Unholding";
            break;
        case CSCallStateVideoUpdating:
            state = @"Video Updating";
            break;
        case CSCallStateTransferring:
            state = @"Transferring";
            break;
        case CSCallStateBeingTransferred:
            state = @"Being Transferred";
            break;
        case CSCallStateIgnored:
            state = @"Ignored";
            break;
        case CSCallStateFailed:
            state = @"Failed";
            //End Call Timer
            
            [self.callTimer invalidate];
            [self deallocViews];
            break;
        case CSCallStateEnding:
            state = @"Ending";
            break;
        case CSCallStateEnded:
        {
            state = @"Ended";
            [self.callTimer invalidate];
            [self deallocViews];
            [self dismissViewControllerAnimated:YES completion:^{NSLog(@"%s controller dismiss", __PRETTY_FUNCTION__);}];
            break;
        }
        case CSCallStateRenegotiating:
            state = @"Renegotiating";
            break;
        case CSCallStateFarEndRenegotiating:
            state = @"Far end Renegotiating";
            break;
        default:
            state = @"Unknown";
            break;
    }
    
    // Update current call state on UI
    self.callState.text = [NSString stringWithFormat:@"%@", state];
    
    if(self.currentCall.isConference) {
        
        //Upon refresh reset participant List to Null.
        self.participantList.text = @"";
        NSLog(@"%s Call is Conference call, populate participant list", __PRETTY_FUNCTION__);
        NSArray *participantsNames = [self.currentCall.conference.participants valueForKey:@"displayName"];
        self.participantList.text = [participantsNames componentsJoinedByString:@"\n"];
        
        self.conferenceControlBtnLabel.hidden = !self.currentCall.conference.moderationCapability.allowed;
    } else if(self.currentCall.callerIdentityPrivate) {
        
        NSLog(@"%s Call identitiy is private", __PRETTY_FUNCTION__);
        self.participantList.text = @"Restricted";
    } else {
        
        NSLog(@"%s Update caller display name", __PRETTY_FUNCTION__);
        self.participantList.text = self.currentCall.remoteDisplayName;
    }
}

- (NSString *)callTimerAsFormattedString {
    
    // Get elapsed time since call was established
    NSTimeInterval interval = - [self.currentCall.establishedDate timeIntervalSinceNow];
    NSString *intervalString = [[NSDateComponentsFormatter new] stringFromTimeInterval: interval];
    
    NSString *callTimerFormat;
    
    //Set correct format to hh:mm:ss
    switch(intervalString.length){
        case 1:
            callTimerFormat = @"00:00:0%@";
            break;
            
        case 2:
            callTimerFormat = @"00:00:%@";
            break;
            
        case 4:
            callTimerFormat = @"00:0%@";
            break;
            
        case 5:
            callTimerFormat = @"00:%@";
            break;
            
        case 7:
            callTimerFormat = @"0%@";
            break;
            
        default :
            callTimerFormat = @"%@";
    }
    
    return [NSString stringWithFormat:callTimerFormat, intervalString];
}

- (void)callTimer:(NSTimer*)theTimer {
    
    self.callDuration.text = [self callTimerAsFormattedString];
}

- (void)initViews {
    
    // Perform initialization only once
    if (!self.viewInitialized) {
        
        [self.mediaManager initVideoView:self];
        self.viewInitialized = YES;
        
        self.mediaManager.localVideoSink = (CSVideoRendererIOS *) self.localVideoView.layer;
        self.mediaManager.remoteVideoSink = (CSVideoRendererIOS *) self.remoteVideoView.layer;
        
        // Show local video preview while is active
        if((self.currentCall.state != CSCallStateEnding) || (self.currentCall.state != CSCallStateEnded)) {
            
            [self.mediaManager runLocalVideo];
        }
    }
    // Show remote video preview when call is established
    if ([self.currentCall state] == CSCallStateEstablished) {
        
        [self.mediaManager.remoteVideoSink handleVideoFrame:nil];
        [self.mediaManager runRemoteVideo:self.currentCall];
    }
    
    // show labels on window
    self.remoteVideoLabel.hidden = NO;
    self.localVideoLabel.hidden = NO;
    
    // show local video preview
    self.localVideoView.hidden = NO;
    self.remoteVideoView.hidden = NO;
}

- (void)deallocViews{
    
    NSLog(@"%s", __PRETTY_FUNCTION__);
    
    // Hide local and remote video previews
    self.localVideoView.hidden = YES;
    self.remoteVideoView.hidden = YES;
    self.remoteVideoLabel.hidden = YES;
    self.localVideoLabel.hidden = YES;
    
    // Release video
    [self.mediaManager.localVideoSink handleVideoFrame:nil];
    [self.mediaManager.videoCapturer setVideoSink:nil];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    
    ConferenceControlViewController *viewController = segue.destinationViewController;
    
    if ([segue.identifier isEqualToString:@"conferenceControlSegue"]) {
        
        viewController.conferenceCall = self.currentCall.conference;
    }
}




- (IBAction)speakerButtonAction:(id)sender {
    
    if (self.speakerButton.selected) {
        
        [self.speakerButton setBackgroundImage:[UIImage imageNamed:@"扬声器-开启"] forState:UIControlStateNormal];
        self.speakerButton.selected = NO;
        for (CSSpeakerDevice *speaker in [[self.mediaManager audioInterface] availableAudioDevices]) {
            
            if ([speaker.name isEqualToString:@"AudioDeviceSpeaker"]) {
                [self.mediaManager setSpeaker:speaker];
                break;
            }
        }
        
        
    }else {
        [self.speakerButton setBackgroundImage:[UIImage imageNamed:@"扬声器"] forState:UIControlStateNormal];
        self.speakerButton.selected = YES;
        [self.mediaManager setSpeaker:nil];

       
    }
    
}

- (IBAction)micButtonAction:(id)sender {
    
    if ([GNAudio audioAuthor] == 2) {
        [WHToast showMessage:@"麦克风权限关闭" originY:SCREEN_HEIGHT/2+100 duration:2 finishHandler:^{
            [self.micButton setBackgroundImage:[UIImage imageNamed:@"关闭麦克风-开启"] forState:UIControlStateNormal];
            
        }];
        return;
    }
    
    if (self.micButton.selected) {
        
        [self.micButton setBackgroundImage:[UIImage imageNamed:@"麦克风"] forState:UIControlStateNormal];
        self.micButton.selected = NO;
        
        if(self.currentCall.unmuteCapability.allowed && self.currentCall.audioMuted) {
            
            NSLog(@"%s Call audio can be unmuted", __PRETTY_FUNCTION__);
            
            [self.currentCall muteAudio:NO completionHandler:^(NSError *error) {
                
                if(error) {
                    
                    [NotificationHelper displayMessageToUser:[NSString stringWithFormat:@"Error while muting Audio of the call, callId: [%ld]", (long)self.currentCall.callId] TAG: __PRETTY_FUNCTION__];
                } else {
                    
                    NSLog(@"%s Audio of call muted successfully, callId:[%lu]", __PRETTY_FUNCTION__, (long)self.currentCall.callId);
                }
            }];
        } else {
            
            NSLog(@"%s Call audio cannot be unmuted", __PRETTY_FUNCTION__);
        }
        
    }else {
        
        [self.micButton setBackgroundImage:[UIImage imageNamed:@"关闭麦克风-开启"] forState:UIControlStateNormal];
        self.micButton.selected = YES;
        
        if(self.currentCall.muteCapability.allowed) {
            
            NSLog(@"%s Call audio can be muted", __PRETTY_FUNCTION__);
            
            [self.currentCall muteAudio: YES completionHandler:^(NSError *error) {
                
                if(error) {
                    
                    [NotificationHelper displayMessageToUser:[NSString stringWithFormat:@"Error while muting audio of call, callId: [%lu]", (long)self.currentCall.callId] TAG:__PRETTY_FUNCTION__];
                } else {
                    
                    NSLog(@"%s Audio Mute succesfful for call, callId: [%lu]", __PRETTY_FUNCTION__, (long)self.currentCall.callId);
                }
            }];
        } else {
            
            NSLog(@"%s Call audio cannot be muted", __PRETTY_FUNCTION__);
        }
        
        
    }
    
}

- (IBAction)cameraButtonAction:(id)sender {
    
    if ([GNAudio videoAuthor] == 2) {
        [WHToast showMessage:@"摄像头权限关闭" originY:SCREEN_HEIGHT/2+150 duration:2 finishHandler:^{
            
        }];
        
        return;
    }
    
    if (self.cameraButton.selected) {
        
        self.cameraButton.selected = NO;
        [self.mediaManager.videoCapturer useVideoCameraAtPosition:CSVideoCameraPositionFront completion:nil];
        
    }else {
        
        self.cameraButton.selected = YES;
        [self.mediaManager.videoCapturer useVideoCameraAtPosition:CSVideoCameraPositionBack completion:nil];
    }
    
}
@end

