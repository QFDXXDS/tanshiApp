/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Class representing User Configuration information for a Conference.
 */
@interface CSConferenceConfiguration : NSObject

/**
 * Adhoc conference URL.
 * If both a conference URL is set and local conferencing is enabled, the conference factory will be used. 
 */
@property (nonatomic, copy) NSURL *conferenceFactoryURL;

/**
 * The URL of the Conference Portal.
 * This allows the client UI to launch the conference portal for extended of advanced conference interactions,
 * such as settings.
 */
@property (nonatomic, copy) NSURL *conferencePortalURL;

/**
 * Conference Moderator code, to allow Click to Join own bridge via Meetme Client
 */
@property (nonatomic, copy) NSString *moderatorCode;

/**
 * Conference Participant code, to allow user to share participant code to other users in Calendar invites and Share My Bridge.
 */
@property (nonatomic, copy) NSString *participantCode;

/**
 * Conference Moderator URL, to allow Click to Join own bridge via Meetme Client
 */
@property (nonatomic, copy) NSURL *moderatorURL;

/**
 * Conference Participant URL, to allow user to share participant URL to other users in Calendar invites and Share My Bridge.
 */
@property (nonatomic, copy) NSURL *participantURL;

/**
 * The Scopia Virtual Room ID for the Virtual room owner.
 */
@property (nonatomic, copy) NSString *virtualRoomID;

/**
 * A Boolean value indicating whether the UCCP conference protocol is enabled.
 *
 */
@property (nonatomic, getter=isUCCPEnabled) BOOL uccpEnabled;

/**
 * A Boolean value indicating whether the additional UCCP features is enabled.
 *
 */
@property (nonatomic, getter=isUCCPAdditionalFeaturesEnabled) BOOL uccpAdditionalFeaturesEnabled;

/**
 * A Boolean value indicating whether the enhanced conferencing is enabled.
 * Also not all call capabilities would be available if it's disabled.
 */
@property(nonatomic, getter = isEnhancedConferencingEnabled) BOOL enhancedConferencingEnabled;

/**
 * A Boolean value indicating whether the local conferencing is enabled.
 * In a local conference media mixing is performed locally on the endpoint rather than via a conferencing server. 
 * This option is typically enabled only in deployments without server based conferencing capabilities. 
 * If both a {@link #conferenceFactoryURL} is set and local conferencing is enabled, the conference factory will be used.
 * Defaults to false.
 */
@property(nonatomic, readonly, getter=isLocalConferencingEnabled) BOOL localConferencingEnabled;

@end
