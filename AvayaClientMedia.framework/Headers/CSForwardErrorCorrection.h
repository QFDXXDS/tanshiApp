//
//  CSForwardErrorCorrection.h
//  scpmedia
//
//  Created by David McGarry on 4/5/17.
//  Copyright © 2017 Avaya. All rights reserved.
//

#ifndef CSForwardErrorCorrection_h
#define CSForwardErrorCorrection_h

typedef NS_ENUM(NSInteger, CSForwardErrorCorrection)
{
	CSForwardErrorCorrectionNone = 0,
	CSForwardErrorCorrectionRFC5109Red, // Standard RFC5109 FEC as a redundant encoding
	CSForwardErrorCorrectionRFC5109Fec, // Standard RFC5109 FEC as a separate stream
	CSForwardErrorCorrectionProprietary // Proprietry FEC (same stream as the media stream)
};
	
#endif /* CSForwardErrorCorrection_h */
