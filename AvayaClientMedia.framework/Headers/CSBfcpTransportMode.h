//
//  CSBfcpTransportMode.h
//  scpmedia
//
//  Copyright (c) 2015 Avaya. All rights reserved.
//
#ifndef clientsdk_CSBfcpTransportMode_h
#define clientsdk_CSBfcpTransportMode_h

typedef NS_ENUM(NSInteger, CSBfcpTransportMode)
{
	CSBfcpTransportModeDisabled = -1,
	CSBfcpTransportModeUdpOnly,
	CSBfcpTransportModeTcpOnly,
	CSBfcpTransportModeUdpPreferred,
	CSBfcpTransportModeTcpPreferred
};

#endif
