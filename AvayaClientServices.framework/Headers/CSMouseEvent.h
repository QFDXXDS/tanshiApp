/* Copyright Avaya Inc. */

#if (!TARGET_OS_IPHONE || TARGET_OS_MAC)
#import <Foundation/Foundation.h>
#endif
#if (TARGET_OS_IPHONE)
#import <CoreGraphics/CoreGraphics.h>
#endif

// Mouse button state
typedef NS_ENUM(NSInteger, CSMouseButtonState) {
	CSMouseButtonNone,
	CSMouseButtonPressed,
	CSMouseButtonReleased,
	CSMouseButtonDoubleClicked
};

@interface CSMouseEvent : NSObject

- (instancetype)initWithPosition:(CGPoint)poistion
					  wheelState:(NSUInteger)mouseWheel
				FirstButtonState:(CSMouseButtonState)firstState
			   SecondButtonState:(CSMouseButtonState)secondState
				ThirdButtonState:(CSMouseButtonState)thirdState;

@property (nonatomic, readonly) CGPoint postion;
@property (nonatomic, readonly) NSUInteger mouseWheel;
@property (nonatomic, readonly) CSMouseButtonState firstMouseButtonStatus;
@property (nonatomic, readonly) CSMouseButtonState secondMouseButtonStatus;
@property (nonatomic, readonly) CSMouseButtonState thirdMouseButtonStatus;

@end
