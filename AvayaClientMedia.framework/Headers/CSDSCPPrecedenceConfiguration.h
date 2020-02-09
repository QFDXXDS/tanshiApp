//
//  DSCPPrecedenceConfiguration.h
//  scpmedia
//
//  Copyright © 2017 Avaya. All rights reserved.
//

#ifndef CSDSCPPrecedenceConfiguration_h
#define CSDSCPPrecedenceConfiguration_h

typedef NS_ENUM(NSInteger, CSDSCPPrecedenceType)
{
    CSDSCPPrecedenceTypeAudio,
    CSDSCPPrecedenceTypeVideo,
};

@interface CSDSCPPrecedenceConfiguration : NSObject<NSCopying>

+(CSDSCPPrecedenceConfiguration *) createDefaultConfigFor:(CSDSCPPrecedenceType)type;

-(id)initWithDSCPForRoutinePrecendence:(int)routine
                           AndPriority:(int)priority
                          AndImmediate:(int)immediate
                              AndFlash:(int)flash
                      AndFlashOverride:(int)flashOverride;

@property(nonatomic, readonly)int dscpRoutine;
@property(nonatomic, readonly)int dscpPriority;
@property(nonatomic, readonly)int dscpImmediate;
@property(nonatomic, readonly)int dscpFlash;
@property(nonatomic, readonly)int dscpFlashOverride;

@end

#endif /* CSDSCPPrecedenceConfiguration_h */
