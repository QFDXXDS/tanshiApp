/* Copyright Avaya Inc. */

#if (!TARGET_OS_IPHONE || TARGET_OS_MAC)
#import <Foundation/Foundation.h>
#endif
#if (TARGET_OS_IPHONE)
#import <CoreGraphics/CoreGraphics.h>
#endif
@interface CSKeyboardEvent : NSObject

- (instancetype)initWithFirstKey:(NSUInteger)firstKey secondKey:(NSUInteger)secondKey
							ctrl:(BOOL)ctrlState alt:(BOOL)altState shift:(BOOL)shiftState
							cmd:(BOOL)cmdState windows:(BOOL)windowsState;

@property (nonatomic, readonly) NSUInteger firstKey;
@property (nonatomic, readonly) NSUInteger secondKey;

@property (nonatomic, readonly) BOOL keyCtrl;
@property (nonatomic, readonly) BOOL keyAlt;
@property (nonatomic, readonly) BOOL keyShift;
@property (nonatomic, readonly) BOOL keyCmd;
@property (nonatomic, readonly) BOOL keyWindows;

@end
