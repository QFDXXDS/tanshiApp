/******************************************************************************/
/*                                                                            */
/* Copyright Avaya Inc.                                                       */
/*                                                                            */
/******************************************************************************/

#import <UIKit/UIKit.h>
#import "NotificationHelper.h"
#import "SDKManager.h"
#import "MediaManager.h"


@interface ActiveCallViewController : UIViewController

@property (nonatomic, weak) IBOutlet UILabel *callDuration;
@property (nonatomic, weak) IBOutlet UILabel *callState;
@property (nonatomic, weak) IBOutlet UITextView *participantList;
@property (nonatomic, weak) IBOutlet UIButton *endCallBtn;
@property (nonatomic, weak) IBOutlet UISwitch *speakerPhoneSwitch;
@property (nonatomic, weak) IBOutlet UIView *remoteVideoView;
@property (nonatomic, weak) IBOutlet UIView *localVideoView;
@property (nonatomic, weak) IBOutlet UILabel *remoteVideoLabel;
@property (weak, nonatomic) IBOutlet UISwitch *muteSwitch;
@property (nonatomic, weak) IBOutlet UILabel *localVideoLabel;
@property (nonatomic, weak) IBOutlet UIButton *conferenceControlBtnLabel;
@property (nonatomic, weak) IBOutlet UIButton *holdCallBtn;

@property (nonatomic, weak) CSCall *currentCall;
@property (nonatomic,copy)NSString *passCode;

@property (weak, nonatomic) IBOutlet UIButton *speakerButton;
@property (weak, nonatomic) IBOutlet UIButton *micButton;
@property (weak, nonatomic) IBOutlet UIButton *cameraButton;

//扬声器点击方法
- (IBAction)speakerButtonAction:(id)sender;
//麦克风点击方法
- (IBAction)micButtonAction:(id)sender;
//相机点击方法
- (IBAction)cameraButtonAction:(id)sender;


//挂断
- (IBAction)endCallBtnClicked:(id)sender;
//静音
- (IBAction)muteSwitchValueChanged:(id)sender;
//扬声器
- (IBAction)speakerPhoneSwitchValueChanged:(id)sender;
- (IBAction)holdCallBtnClicked:(id)sender;
@end
