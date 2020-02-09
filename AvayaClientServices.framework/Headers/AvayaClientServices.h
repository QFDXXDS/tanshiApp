/* Copyright Avaya Inc. */

#import <AvayaClientServices/CSActiveParticipant.h>
#import <AvayaClientServices/CSAudioDetails.h>
#import <AvayaClientServices/CSBasicShape.h>
#import <AvayaClientServices/CSCall.h>
#import <AvayaClientServices/CSCallFeatureService.h>
#import <AvayaClientServices/CSCallForwardingStatus.h>
#import <AvayaClientServices/CSCallLogItem.h>
#import <AvayaClientServices/CSCallLogParticipant.h>
#import <AvayaClientServices/CSCallLogService.h>
#import <AvayaClientServices/CSCallPickupAlertParameters.h>
#import <AvayaClientServices/CSCallPickupAlertStatus.h>
#import <AvayaClientServices/CSCallPickupFeatureRinger.h>
#import <AvayaClientServices/CSCallService.h>
#import <AvayaClientServices/CSCameraControl.h>
#import <AvayaClientServices/CSCertificateInfo.h>
#import <AvayaClientServices/CSChat.h>
#import <AvayaClientServices/CSChatMessage.h>
#import <AvayaClientServices/CSCircleShape.h>
#import <AvayaClientServices/CSClient.h>
#import <AvayaClientServices/CSClientConfiguration.h>
#import <AvayaClientServices/CSClipboardEvent.h>
#import <AvayaClientServices/CSCollaboration.h>
#import <AvayaClientServices/CSCollaborationService.h>
#import <AvayaClientServices/CSConference.h>
#import <AvayaClientServices/CSConferenceSlideViewer.h>
#import <AvayaClientServices/CSConferenceMobileLink.h>
#import <AvayaClientServices/CSConferenceRoomSystemInformation.h>
#import <AvayaClientServices/CSConferenceSlide.h>
#import <AvayaClientServices/CSConnectionPolicy.h>
#import <AvayaClientServices/CSContact.h>
#import <AvayaClientServices/CSContactBoolField.h>
#import <AvayaClientServices/CSContactDoubleField.h>
#import <AvayaClientServices/CSContactEmailAddressField.h>
#import <AvayaClientServices/CSContactField.h>
#import <AvayaClientServices/CSContactIMAddressField.h>
#import <AvayaClientServices/CSContactPhoneField.h>
#import <AvayaClientServices/CSContactService.h>
#import <AvayaClientServices/CSContactStringField.h>
#import <AvayaClientServices/CSCollaborationDetails.h>
#import <AvayaClientServices/CSEditableContactBoolField.h>
#import <AvayaClientServices/CSEditableContactDoubleField.h>
#import <AvayaClientServices/CSEditableContactEmailAddressField.h>
#import <AvayaClientServices/CSContactField.h>
#import <AvayaClientServices/CSEditableContactIMAddressField.h>
#import <AvayaClientServices/CSEditableContactPhoneField.h>
#import <AvayaClientServices/CSContactService.h>
#import <AvayaClientServices/CSContactStringField.h>
#import <AvayaClientServices/CSContentSharing.h>
#import <AvayaClientServices/CSCredentialProvider.h>
#import <AvayaClientServices/CSDataRetrievalWatcher.h>
#import <AvayaClientServices/CSDefines.h>
#import <AvayaClientServices/CSDroppedParticipant.h>
#import <AvayaClientServices/CSEditableContact.h>
#import <AvayaClientServices/CSEnhancedCallForwardingStatus.h>
#import <AvayaClientServices/CSError.h>
#import <AvayaClientServices/CSFeatureInvocationParameters.h>
#import <AvayaClientServices/CSFeatureStatusParameters.h>
#import <AvayaClientServices/CSFeatureType.h>
#import <AvayaClientServices/CSIdentified.h>
#import <AvayaClientServices/CSKeyboardEvent.h>
#import <AvayaClientServices/CSLibraryDocument.h>
#import <AvayaClientServices/CSLibraryManager.h>
#import <AvayaClientServices/CSLibrarySharing.h>
#import <AvayaClientServices/CSLocalContactConfiguration.h>
#import <AvayaClientServices/CSMeetingMediaType.h>
#import <AvayaClientServices/CSMeetingMinutes.h>
#import <AvayaClientServices/CSMessage.h>
#import <AvayaClientServices/CSMessageBodyPart.h>
#import <AvayaClientServices/CSMessageDeliveryDetails.h>
#import <AvayaClientServices/CSMessageWaitingStatus.h>
#import <AvayaClientServices/CSMessagingAddressValidation.h>
#import <AvayaClientServices/CSMessagingAttachment.h>
#import <AvayaClientServices/CSMessagingConversation.h>
#import <AvayaClientServices/CSMessagingSearchConversation.h>
#import <AvayaClientServices/CSMessagingEnums.h>
#import <AvayaClientServices/CSMessagingLeaveConversationResponse.h>
#import <AvayaClientServices/CSMessagingLimits.h>
#import <AvayaClientServices/CSMessagingParticipant.h>
#import <AvayaClientServices/CSMessagingQuery.h>
#import <AvayaClientServices/CSMessagingService.h>
#import <AvayaClientServices/CSMinuteMessage.h>
#import <AvayaClientServices/CSMouseEvent.h>
#import <AvayaClientServices/CSMaxSupportedVideoResolutionsCapability.h>
#import <AvayaClientServices/CSParticipant.h>
#import <AvayaClientServices/CSPendingParticipant.h>
#import <AvayaClientServices/CSPhysicalAddress.h>
#import <AvayaClientServices/CSPresence.h>
#import <AvayaClientServices/CSPresenceConfiguration.h>
#import <AvayaClientServices/CSPresenceListSubscription.h>
#import <AvayaClientServices/CSIPOfficeConfiguration.h>
#ifdef INCLUDE_WATCHER_REQUEST
#import <AvayaClientServices/CSPresenceWatcherRequest.h>
#endif
#import <AvayaClientServices/CSRegistrationGroup.h>
#import <AvayaClientServices/CSRenderingBlock.h>
#import <AvayaClientServices/CSScreenSharingListener.h>
#import <AvayaClientServices/CSSettingsFileParser.h>
#import <AvayaClientServices/CSShape.h>
#import <AvayaClientServices/CSSharingBlock.h>
#import <AvayaClientServices/CSSharingDisplay.h>
#import <AvayaClientServices/CSSignalingServer.h>
#import <AvayaClientServices/CSSignalingServerGroup.h>
#import <AvayaClientServices/CSSIPUserConfiguration.h>
#import <AvayaClientServices/CSSlide.h>
#import <AvayaClientServices/CSSlider.h>
#import <AvayaClientServices/CSSliderSlide.h>
#import <AvayaClientServices/CSUnifiedPortalConferencingConfiguration.h>
#import <AvayaClientServices/CSUnifiedPortalConfiguration.h>
#import <AvayaClientServices/CSUnifiedPortalResources.h>
#import <AvayaClientServices/CSUnifiedPortalMeetingInfo.h>
#import <AvayaClientServices/CSUnifiedPortalService.h>
#import <AvayaClientServices/CSUser.h>
#import <AvayaClientServices/CSUserConfiguration.h>
#import <AvayaClientServices/CSUserCredential.h>
#import <AvayaClientServices/CSVersion.h>
#import <AvayaClientServices/CSVideoChannel.h>
#import <AvayaClientServices/CSVideoResolutionPreference.h>
#import <AvayaClientServices/CSVideoResolutionCapability.h>
#import <AvayaClientServices/CSVideoLayout.h>
#import <AvayaClientServices/CSVideoUserConfiguration.h>
#import <AvayaClientServices/CSVirtualRoom.h>
#import <AvayaClientServices/CSVoiceMessagingService.h>
#import <AvayaClientServices/CSVoiceMessagingStatusParameters.h>
#import <AvayaClientServices/CSWhiteboard.h>
#import <AvayaClientServices/CSWhiteboardSurface.h>
#import <AvayaClientServices/CSWhiteboardText.h>
#import <AvayaClientServices/CSLineAppearance.h>
#import <AvayaClientServices/CSSecurityPolicyConfiguration.h>
#import <AvayaClientServices/CSSpaceService.h>
#import <AvayaClientServices/CSSpaceParticipant.h>

#if TARGET_OS_IPHONE
// iOS specific functionality
#import <AvayaClientServices/CSIOSScreenSharingView.h>
#import <AvayaClientServices/CSIOSWhiteboardCanvas.h>
#import <AvayaClientServices/CSPushNotificationConfiguration.h>
#import <AvayaClientServices/CSPushNotificationsEncryptionScheme.h>
#import <AvayaClientServices/CSPushNotificationService.h>
#else
// OS X specific functionality
#import <AvayaClientServices/CSSharingApplicationWindow.h>
#import <AvayaClientServices/CSOSXScreenSharingView.h>
#import <AvayaClientServices/CSPresentationSlideCanvas.h>
#import <AvayaClientServices/CSPresentationSlidesListener.h>
#import <AvayaClientServices/CSWhiteboardCanvas.h>
#endif

// Media engine
#import <AvayaClientMedia/CSMediaServicesProvider.h>

#if TARGET_OS_IPHONE
#import <AvayaClientMedia/CSVideoCapturerIOS.h>
#import <AvayaClientMedia/CSVideoRendererIOS.h>
#else
#import <AvayaClientMedia/CSVideoCapturerOSX.h>
#import <AvayaClientMedia/CSVideoRendererOSX.h>
#endif
