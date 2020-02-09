/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSMeetingMediaType.h"

/**
 * Meeting info returned by Unified Portal.
 * Shall be used to populate @see CSCallCreationInfo when creating HTTP Meet-me conference call.
 */

@interface CSUnifiedPortalMeetingInfo : NSObject

/**
 * Correlation token provided by Unified Portal.
 */
@property (nonatomic, readonly, copy) NSString *portalToken;

/**
 * The Service Gateway (ESG) URL
 */
@property (nonatomic, readonly, copy) NSURL *serviceGatewayURL;

/**
 * The URL of the UCCS server.
 * This allows application to establish conference in presentation only mode.
 */
@property (nonatomic, readonly, copy) NSURL *uccpURL;

/**
 * The media type of the meeting.
 */
@property (nonatomic, readonly) CSMeetingMediaType mediaType;

/**
 * A Boolean value indicating whether Web Collaboration Service is enabled for this meeting.
 */
@property (nonatomic, readonly) BOOL webCollaborationServiceEnabled;

/**
 * A dictionary of extra properties the application may be interested in.
 * Complex property values are JSON-encoded strings.
 */
@property (nonatomic, readonly) NSDictionary* extraProperties;

- (instancetype)initWithPortalToken:(NSString *)portalToken
				  serviceGatewayURL:(NSURL *)serviceGatewayURL
							uccpURL:(NSURL *)uccpURL
						  mediaType:(CSMeetingMediaType)mediaType
	 webCollaborationServiceEnabled:(BOOL)webCollaborationServiceEnabled
					extraProperties:(NSDictionary *)extraProperties;

@end
