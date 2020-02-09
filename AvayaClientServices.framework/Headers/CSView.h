/* Copyright Avaya Inc. */

#ifndef AvayaClientServices_CSView_h
#define AvayaClientServices_CSView_h

#if !TARGET_OS_IPHONE
@class NSView;
typedef NSView CSView;
#else
@class UIView;
typedef UIView CSView;
#endif

#endif
