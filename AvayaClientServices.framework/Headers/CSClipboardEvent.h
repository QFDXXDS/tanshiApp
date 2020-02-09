/* Copyright Avaya Inc. */

#if (!TARGET_OS_IPHONE || TARGET_OS_MAC)
#import <Foundation/Foundation.h>
#endif
#if (TARGET_OS_IPHONE)
#import <CoreGraphics/CoreGraphics.h>
#endif

@interface CSClipboardEvent : NSObject

- (instancetype)initWithString:(NSString*)text asCopy:(BOOL)copy;

@property (strong, nonatomic, readonly) NSString* content;
@property (nonatomic, readonly) BOOL isCopy; // It can't be called copy

@end
