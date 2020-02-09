/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSDefines.h"

/**
 * The Avaya Client Services error domain.
 *
 * Error codes in this domain are defined in the CSErrorCode enumeration.
 */
CS_EXTERN NSString * const CSErrorDomain;

/**
 * The error code from the underlying signaling protocol as an NSNumber.
 *
 * For SIP, this is the response code.
 */
CS_EXTERN NSString * const CSProtocolErrorCodeKey;

/**
 * The error string from the underlying signaling protocol.
 *
 * For SIP, this is the reason phrase.
 */
CS_EXTERN NSString * const CSProtocolErrorStringKey;

/**
 * The warning code from the underlying signaling protocol as an NSNumber.
 *
 * For SIP, this is the code provided in the Warning header.
 */
CS_EXTERN NSString * const CSProtocolWarningCodeKey;

/**
 * The warning string from the underlying signaling protocol.
 *
 * For SIP, this is the text provided in the Warning header.
 */
CS_EXTERN NSString * const CSProtocolWarningStringKey;

/**
 * The number of seconds until a retry is attempted automatically as an NSNumber.
 */
CS_EXTERN NSString * const CSSecondsUntilRetryKey;

/**
 * Error codes used by Avaya Client Services.
 */
typedef NS_ENUM(NSInteger, CSErrorCode) {

	/**
	 * An unknown error occurred.
	 *
	 * If this error code is received it is a bug and should be reported.
	 */
	CSErrorUnknown = -1,

	// General errors
	CSErrorNone = 0,                         /**< Operation completed successfully. */
	CSErrorFailed = 1,                       /**< Operation has failed. */
	CSErrorInternal = 2,                     /**< Operation has failed due to an internal error. */
	CSErrorInProgress = 3,                   /**< Operation has failed because another operation is in progress. */
	CSErrorTimeout = 4,                      /**< Reported when the send of a network message timed out locally, or a response to
											  the message was not received from the server in time. */
	CSErrorInvalidState = 5,                 /**< Reported when the request cannot be supported at this time due to the current state of the call. */
	CSErrorNotSupported = 6,                 /**< Reported when a requested operation cannot be supported locally, because the state of the
											  underlying resource does not allow the operation at this time. */
	CSErrorAuthenticationFailure = 7,        /**< Reported when local user's authentication with the network has failed. */
	CSErrorClientShutDown = 8,
	CSErrorCancelled = 9,                    /**< The operation was cancelled. */
	CSErrorInvalidDomain = 10,
	CSErrorCellularCallInProgress = 11,      /**< Reported when a local VoIP/video call creation has failed because of an
											  on-going cellular call. */
	CSErrorNotLicensed = 12,                 /**< Reported when an operation is denied because user does not have the license
											  to perform the operation. */
	CSErrorNotAuthorized = 13,               /**< Reported when an operation is denied because user does not have the privileges
											  to perform the operation. */
	CSErrorNoCredentialProvider = 14,        /**< Reported when there is no credential provider provided in the service configuration data. */
	CSErrorConfigurationError = 15,          /**< Reported when there is an error discovered in the service configuration data. */
	CSErrorNoAnswer = 16,                    /**< Reported there is no answer from far end. */
	CSErrorNotAllowed = 17,                  /**< Reported when the request operation is not allowed at all. */
	CSErrorIncorrectPasscodeTryAgain = 18,   /**< Reported when provided passcode for conference is not valid, indicates that there could be
											  one more attempt to provide passcode. */
	CSErrorIncorrectPasscodeDisconnecting = 19, /**< Reported when provided passcode for conference is not valid, indicates that there will be
											  no more attempts to provide passcode. */
	CSErrorPendingApproval = 20,             /**< Reported when conference is in pending approval state. */
	CSErrorLayoutNotAvailable = 21,          /**< Reported when the conference server is unable to support the selected video layout. */
	CSErrorCapabilityDenied = 22,			 /**< User is not allowed to perform operation. */

	CSErrorConferenceSocketFailed = 23,		 /**< Reported when UCCP web socket connection fails. */
	CSErrorConferenceCertificateFailed = 24,			 /**< Reported when UCCP web socket certificate fails. */
	CSErrorConferenceFeatureNegotiationFailed = 25,			 /**< Reported when UCCP handshake fails. */
	CSErrorHTTPUACertificateFailed = 26,			 /**< Reported when Service Gateway certificate fails. */

	CSErrorWrongCurrentConference = 27,			/**< Reported if conference id is incorrect.*/
	CSErrorIncorrectInput = 28,					/**< Reported if user input is incorrect.*/
	CSErrorGuestAccessDenied = 29,				/**< Reported if user is guest and guest access disabled.*/
	CSErrorValidationFailed = 30,				/**< Reported if the name of the user did not pass validation.*/
	CSErrorOneTimePinRequired = 31,				/**< Reported if user is owner and one time pin is required.*/
	CSErrorForbiddenOneTimePinRequired = 32,	/**< Reported if oneTimePin required, but given user isn't owner of room.*/
	CSErrorLockedConference = 33,				/**< Reported if conference is locked and the user is not allowed to knock to it.*/
	CSErrorInitiateNonVirtualRoomMeetingDisallowed = 34,	/**< Reported if a user tries to create a meeting outside a virtual room.*/
	CSErrorWebCollaborationDisabled = 35,		/**< Reported if web collaboration is disabled. */
	CSErrorIViewNotConnected = 36,				/**< Reported if iView is not available. */
	CSErrorVirtualRoomNotFound = 37,			/**< Reported if provided conference id is not found. */
	CSErrorTenantDoesNotExist = 38,				/**< Reported if provided tenant alias does not exist. */
	CSErrorProxyAuthenticationError = 39,		/**< The authentication credentials provided for logging into the proxy were rejected. */
	CSErrorVirtualRoomDoesNotAllowInstantMeeting  = 40,	/**< Reported if virtual room does not allow creation of instant meeting.
														 An instant meeting is a meeting that was not scheduled beforehand.*/
	CSErrorVirtualRoomDisabled = 41,			/**< Reported if virtual room is disabled.*/
	CSErrorCallInProgress = 42,					/**< Reported if any operation can not be completed because a call is already in progress */
		
	// Connection errors
	CSErrorConnectionFailure = 100,
	CSErrorServerUntrusted = 101,
	CSErrorSendFailure = 102,                 	/**< Reported when a network message could not be sent due to a network connection error. */
	CSErrorUnrecognizedServer = 103,
	CSErrorSSLFatalAlert = 104,
	CSErrorWifiUnavailable = 105,             	/**< Reported when a VoIP/video call cannot be set up because there is no Wifi
												 network available to initiate a call and the local policy restricts VoIP/video
												 calls to Wifi networks only. */
	CSErrorUnsupportedLocalNetwork = 106,     	/**< Registration has failed because the device is currently connected to an unsupported network type. */
	CSErrorProxyConnectionError = 107,			/**< A connection could not be established to the proxy server. */

	// Invalid parameter errors
	CSErrorInvalidParameter = 200,            	/**< Reported when an invalid parameter is used for the request. */
	CSErrorSIPInvalidDomain = 201,
	CSErrorSIPInvalidUserId = 202,
	CSErrorSIPInvalidAddressOfRecord = 203,
	CSErrorSIPEmptyServerList = 204,
	CSErrorSIPInvalidServer = 205,
	CSErrorSIPUserExists = 206,
	CSErrorSIPInvalidCredentialProvider = 207,
	CSErrorInvalidDataDirectory = 208,
	CSErrorHTTPInvalidUserId = 209,
	CSErrorHTTPInvalidCredentialProvider = 210,
	CSErrorHTTPUserExists = 211,
	CSErrorUnsupportedConnectionPolicy = 212,
	CSErrorInvalidSessionRefreshInterval = 213,

	// Signaling errors
	CSErrorNotRegistered = 300,                /**< Reported when an operation fails because the server believes the user is not
												registered. */
	CSErrorServerFailure = 301,                /**< Reported when the request has failed due to an internal server error. */
	CSErrorServerEnded = 302,
	CSErrorMaximumRegistrationsExceeded = 304,
	CSErrorRejected = 305,                     /**< Reported when the request is rejected by the server due to a permission error. */
	CSErrorBusy = 306,                         /**< Reported when the request is rejected by the server due to resource being busy. */
	CSErrorRedirected = 307,                   /**< Network re-directed the request. */
	CSErrorCodecMismatch = 308,                /**< Reported when a VoIP session cannot be established due to incompatible codecs
												between the local and remote parties. */
	CSErrorUserNotFound = 309,                 /**< Reported when the called party address is not known to the server. */
	CSErrorUserTemporarilyUnavailable = 310,   /**< Reported when the called party has no device registered on his/her behalf, making
												call setup not possible at this point in time. */
	CSErrorNoAvailableCallAppearance = 312,    /**< Reported when the local user's call initiation attempt fails because
												the Avaya Communication Manager has no idle line appearance available for the call. */
	CSErrorLineReservationFailure = 313,       /**< Reported when a line reservation attempt is failed by the server. */
	CSErrorRemoteCallNoLongerAlerting = 314,   /**< Reported when an attempt to locally answer an incoming
												call at a remote extension (e.g., at a bridged line appearance extension)
												has failed because the call was already answered remotely. */
	CSErrorRetryLimitExceeded = 315,
	CSErrorInvalidResponse = 316,
	CSErrorConferenceAddressNotValid = 317,    /**< Reported when an ad-hoc conference creation attempt fails because the provisioned
												network address used for ad-hoc conference creation is not valid. */
	CSErrorCallTerminated = 318,               /**< Reported when outgoing call request is terminated or canceled by user action. */

	CSErrorConfigurationDataNotAvailable = 319, /**< Reported when the configuration data for the user is not available at the server. */
	
	CSErrorOneTimePINRequiredForVirtualRoomAccess = 320,      /**< Reported when one time pin is required and user is not owner of the room. */
	CSErrorOneTimePINRequiredForOwnerVirtualRoomAccess = 321, /**< Reported when one time pin is required and user is owner of the room. */

	// Media errors
	CSErrorMediaCreationFailure = 400,         /**< Reported when local audio and/or video resources cannot be initialized successfully. */
	CSErrorMediaStartFailure = 401,            /**< Reported when local audio and/or video resources cannot be started successfully. */
	CSErrorRemoteMediaProcessingFailure = 402, /**< Reported when the application tries to accept an incoming call, but this attempt
												fails because the remote audio and/or video information could not be applied to local
												audio/video resources.*/
	CSErrorVideoDenied = 403,                  /**< Reported when a mid-call video add request was denied by the remote party. */

	// Feature errors
	CSErrorFeatureCancelled = 500,

	// Contact Providers errors
	CSErrorContactProviderPictureNotAvailable = 600,		/**< Contact doesn't have a picture or specific contact provider uses LDAP as a source
															   * for pictures and it is not configured / available at the time.*/
	CSErrorContactProviderContactIdInvalid = 601,		/**< Missing or invalid provider contact ID. */
	CSErrorContactProviderDatabaseNoAccess = 602,		/**< Provider cannot access the database for reading or writing. */
	CSErrorContactProviderDuplicateContact = 603,		/**< This error can occur when trying to add a new contact with the same */
	CSErrorContactProviderContactNotIMUser = 604,		/**< * This error can occur when trying to add a new contact with the same
														 * email address or phone number as any of the existing contacts. */
	CSErrorContactProviderContactAddressNULL = 605,		/**< Address field is empty. */
	CSErrorContactProviderInvalidContact = 606,		/**< Provided data failed a validation step. */
	CSErrorContactProviderRequiredDataMissing = 607,		/**< Required fields are missing. */
	CSErrorContactProviderInvalidValue = 608,		/**< Invalid contact field value. */
	CSErrorContactProviderDatabaseNotAccessible = 609,		/**< Problem with the database accessibility. */
	CSErrorContactProviderContactDoesNotExists = 610,		/**< Name field is empty or not present. */
	CSErrorContactProviderNoProfile = 611,		/**< An internal contact does not have a communication profile. */
	CSErrorContactProviderConfigurationMismatch = 612,		/**< Value exceeded server limit, typically maximum of 70 data items.
															 * As of SM 6.2 Feature Pack 1 this limit is increased to 100 data items.
 */
	CSErrorContactProviderRetry = 613,		/**< Server is busy. Provider is retrying the operation. */
	CSErrorContactProviderDeleteContactNotSupported = 614,		/**< Provider does not support deletion of contacts operation. */
	CSErrorContactProviderAddContactNotSupported = 615,		/**< Provider does not support creation of new contacts operation. */
	CSErrorContactProviderUpdateContactNotSupported = 616,		/**< Provider does not support updating contacts operation. */
	CSErrorContactProviderRetrievePictureNotSupported = 617,		/**< Provider does not support retrieving contact picture operation. */
	CSErrorContactProviderNotMatch = 618,		/**< No provider matches the contact source. */
	CSErrorContactNotFound = 619,		/**< Contact not found. */
	CSErrorContactProviderDigestMismatch = 620,		/**< Digest Authentication failed. */
	
	// Messaging Provider errors
	CSErrorNoParticipants = 650,
	CSErrorParticipantAddressInvalid = 651,
	CSErrorMessageNotFound = 652,
	CSErrorSubjectLengthExceeded = 653,
	CSErrorAttachmentSizeExceeded = 654,
	CSErrorThumbnailSizeExceeded = 655,
	CSErrorFailedToOpenDestinationFile = 656,
	CSErrorFailedToOpenFileToAttach = 657,
	CSErrorWrongAttachmentPath = 658,
	CSErrorUnsupportedMediaTypeForAttachmentThumbnail = 659,
	CSErrorMaxNumberOfAttachmentsLimitExceeded = 660,
	CSErrorBodyLengthExceeded = 661,
	CSErrorAttachmentNotFound = 662,
	CSErrorMessageEmpty = 663,
	CSErrorAttachmentEmpty = 664,
	CSErrorConversationAlreadyExists = 665,
	CSErrorConversationNotFound = 666,				 /**< Requested conversation could not be found. */
	CSErrorParticipantsMismatch = 667,				 /**< The message recipients do not match the conversation participants. */

	// Certificate Provider error
	CSErrorCertificateUntrusted = 700,               /**< Reported when certificate chain cannot be trusted. This is often a generic error. */
	CSErrorCertificateTrusted = 701,                 /**< Reported when certificate chain is trusted. */
	CSErrorCertificateHasExpired = 702,              /**< Reported when one or more certificates in the chain are expired. */
	CSErrorCertificateNotYetValid = 703,             /**< Reported when one or more certificates in the chain are yet to commence. */
	CSErrorCertificateRevoked = 704,                 /**< Reported when one or more certificates in the chain are revoked. */
	CSErrorCertificateInvalidServerIdentity = 705,   /**< Reported when identity presented by the server does not match the hostname to which
													  client is connecting to. */
	CSErrorCertificateInvalidEncoding = 706,         /**< Reported when one or more certificates in the chain has unsupported encoding. */
	CSErrorCertificateParsingFailed = 707,           /**< Reported when one or more certificates in the chain is corrupted. */
	CSErrorCertificateRevocationStatusUnknown = 708, /**< Reported when one or more certificate's revocation information cannot be retrieved. */
	CSErrorInvalidCertificateUsage = 709,            /**< Reported when certificate or certificate chain is not valid for its intended usage. */
	CSErrorCertificateInvalidExtension = 710,        /**< Reported when one of the certificate in the chain has extension which is not valid. */
	CSErrorCertificateUntrustedRoot = 711,           /**< Reported when CA certificates that form a complete chain cannot be trusted. */
	CSErrorCertificateInvalidSignature = 712,        /**< Reported when one or more certificate has invalid signature. */
	CSErrorCertificateInvalidServiceDomain = 713,    /**< Reported when service identity presented by the server does not match the service identity
													  to which client is connecting to. */
	CSErrorCertificateInvalidSIPDomain = 714,        /**< Reported when SIP service identity presented by the server does not match the SIP domain to
													  which client is connecting to. */

	CSErrorCertificateStoreExists = 715,              /**< Reported when an attempt to create private trust store when it already exists. */
	CSErrorCertificateStoreError = 716,               /**< Reported when an error is encountered while creating the private trust store. */
	CSErrorCertificateStoreCreateFailed = 717,        /**< Reported when private trust store cannot be created due to security policy. */
	CSErrorServerCertificateChainRevoked = 718,       /**< Reported when one or more certificates in the chain are revoked. */
	CSErrorCertificateRequestCanceled = 719,          /**< Reported when ongoing certificate validation request was canceled. */
	CSErrorBadPrivateKey = 720,                       /**< Reported when supplied private key is corrupt. */
	CSErrorPrivateKeyContainerFailure = 721,          /**< Reported when Keychain cannot be accessed to retrieve private key. */
	CSErrorPrivateKeyStoreFailure = 722,              /**< Reported when a private key storage failed. */
	CSErrorPrivateKeyExportFailure = 724,             /**< Reported when a private key is failed to retrieve from client identity stored in keychain. */
	CSErrorMissingCertificateStore = 725,             /**< Reported when a client identity is missing from the Keychain. */
	CSErrorClientIdentityStoreFailure = 726,          /**< Reported when a client identity cannot be stored in the Keychain */
	CSErrorEncryptionFailure = 727,                   /**< Unsupported for iOS and macOS. */
	CSErrorDecryptionFailure = 728,                   /**< Unsupported for iOS and macOS. */
	CSErrorUnsupportedCertificateStore = 729,         /**< Unsupported for iOS and macOS. */
	CSErrorClientIdentityCertificateUnknownCA = 730,  /**< Reported when registration has failed because the client identity presented by
													   the client applicatio is issued by unknown CA. */
	CSErrorClientIdentityCertificateAccessDenied = 731, /**< Reported when registration has failed because server has disallowed the connection for
														 this client application in spite of trusted client certificates */
	CSErrorClientIdentityCertificateBad = 732,         /**< Reported when registration has failed due to bad (sometimes acts as generic error)
														client certificate. */
	CSErrorClientIdentityCertificateUnsupported = 733, /**< Reported when registration has failed because the client identity certificate presented
														by the client application is not supported by the server. */
	CSErrorClientIdentityCertificateNoCertificate = 734, /**< Reported when registration has failed because the client identity certificate
														  presented by the client application is missing. This error is code is used for SSLv3
														  connections only.*/
	CSErrorClientIdentityCertificateRevoked = 735,      /**< Reported when registration has failed because the client identity certificate presented
														 by the client application is revoked. */
	CSErrorClientIdentityCertificateExpired = 736,      /**< Reported when registration has failed because the client identity certificate presented
														 by the client application is expired. */
	CSErrorClientIdentityCertificateUnknown = 737,      /**< Reported when registration has failed because an unknown error has occurred on the
														 server while validating the presented client identity certificate. */
	CSErrorSSLHandshakeFailure = 738,                   /**< Reported when registration has failed because client application is unable to negotiate
														 an acceptable set of security parameters. */
	CSErrorPrivateTrustStoreError = 739,                /**< Reported when registration has failed because client application has configured
														 to use the private trust store via {@link CSSecurityPolicyConfiguration} but
														 it is unavailable. */
	CSErrorCertificateEnrollmentFailed = 740,                     /**< Reported when certificate enrollment has failed. */
	CSErrorCertificateEnrollmentNotConnected = 741,               /**< Reported when connection to SCEP server failed. */
	CSErrorCertificateEnrollmentCaCertificateIsInvalid = 742,     /**< Reported when connection to SCEP server failed because of invalid CA issue or CA doesn't exist. */
	CSErrorCertificateEnrollmentWrongConfiguration = 743,         /**< Reported when enrollment failed because of wrong configuration. */
	CSErrorCertificateEnrollmentCertificateAlreadyEnrolled = 744, /**< Reported when SCEP enrollment failed because the certificate was already enrolled. */
	CSErrorCertificateEnrollmentWrongPassword = 745,              /**< Reported when SCEP password is incorrect. */
	CSErrorKeyLengthTooSmall = 746,                               /**< Reported when key length is too small to be acceptable for current security policy. */
	CSErrorInvalidIdentityCertificate = 747,                      /**< Reported when client identity certificate is rejected by the server. */
	CSErrorCertificateEnrollmentRequestPending = 748,             /**< Reported when the enrollment request is failed due to pending response (manual approvement is enabled on SCEP server). */
	CSErrorCertificateEnrollmentFailedToSetIdentity = 749,        /**< Reported when the identity certificate cannot be applied. */
	CSErrorCertificateEnrollmentInProgress = 750,                 /**< Reported when the enrollment request is already in progress. */
	CSErrorInvalidDigestAlgorithm = 751,                          /**< Reported when digest algorithm is unsupported or it is disabled in security policy. */
	CSErrorInvalidAsymmetricEncryptionAlgorithm = 752,            /**< Reported when asymmetric encryption algorithm is unsupported or it is disabled in security policy. */
	CSErrorIncompatiblePrivateKeyFormat DEPRECATED_MSG_ATTRIBUTE("Use CSErrorInvalidAsymmetricEncryptionAlgorithm instead.") = CSErrorInvalidAsymmetricEncryptionAlgorithm,

	// Shared Control errors
	CSErrorSharedControlInvalidError = 800,
	CSErrorSharedControlLocallyDisconnected = 801,
	CSErrorSharedControlControlledEndpointEnded = 802,
	CSErrorSharedControlLinkDownError = 803,
	CSErrorSharedControlAuthenticationError = 804,
	CSErrorSharedControlConnectionError = 805,
	CSErrorSharedControlInvalidStateError = 806,
	CSErrorSharedControlServerError = 807,
	CSErrorSharedControlServerEndedError = 808,
	CSErrorSharedControlGeneralError = 809,
	CSErrorSharedControlControlLinkLocalError = 810,
	CSErrorSharedControlControlLinkRemoteError = 811,

	// Directory Search Provider errors
	CSErrorDirectorySearchProviderUnknownReason = 900,
	CSErrorDirectorySearchProviderInternalError = 901,
	CSErrorDirectorySearchProviderBackendSourceNotConnectable = 902,
	CSErrorDirectorySearchProviderAuthenticationFailed = 903,
	CSErrorDirectorySearchProviderCertificateError = 904,
	CSErrorDirectorySearchProviderSecureConnection_failed = 905,
	CSErrorDirectorySearchProviderRequestTimeout = 906,
	CSErrorDirectorySearchProviderUserCancel = 907,
	CSErrorDirectorySearchProviderConfigChange = 908,
	CSErrorDirectorySearchProviderNoPicture = 909,
	CSErrorDirectorySearchProviderInvalidSearchRequestId = 910,
	CSErrorDirectorySearchProviderInvalidSearchCriteria = 911,
	CSErrorDirectorySearchProviderInvalidSearchType = 912,
	CSErrorDirectorySearchProviderMaxSearchLimitCrossed = 913,
	CSErrorDirectorySearchProviderInvalidChunksize = 914,
	CSErrorDirectorySearchProviderDatabaseError = 915,
	CSErrorDirectorySearchProviderRetry = 916,
	CSErrorDirectorySearchProviderRegularExpression = 917,
	CSErrorDirectorySearchProviderLdapConnectFailed = 918,
	CSErrorDirectorySearchProviderLdapSearchFailed = 919,
	CSErrorDirectorySearchProviderLdapRetrieveResultsFailed = 920,
	CSErrorDirectorySearchProviderProvisioningError = 921,
	CSErrorDirectorySearchProviderDigestMismatch = 922,
	CSErrorDirectorySearchProviderRetrievePictureNotSupported = 923,
	CSErrorDirectorySearchProviderSearchTerminalNotSupported = 924,
	CSErrorDirectorySearchProviderInvalidSearchRequest = 925,

	// Autodial update errors
	CSErrorAutodialDatabaseNotAccessible = 1000,
	CSErrorAutodialDatabaseReadWriteFailure = 1001,
	CSErrorAutodialConfigurationMismatch = 1002,
	CSErrorAutodialNotIMUser = 1003,
	CSErrorAutodialInvalidValue = 1004,
	CSErrorAutodialNoListAvailable = 1005,
	CSErrorAutodialNoButtonFound = 1006,
	CSErrorAutodialHandleInvalid = 1007,
	CSErrorAutodialDigestMismatch = 1008,
    CSErrorAutodialUpdateInProgress = 1009,

	// Collaboration errors
	CSErrorCollaborationCannotEdit = 1100,
	CSErrorCollaborationOperationInProgress = 1101,
	CSErrorCollaborationInternalError = 1102,
	CSErrorCollaborationHTTPStatusCodeError = 1103,
	CSErrorCollaborationPermissionDenied = 1104,
	CSErrorCollaborationCanceled = 1105,
	CSErrorCollaborationNotSupported = 1106,
	CSErrorCollaborationTimeout = 1107,
	CSErrorCollaborationNotConnectable = 1108,
	CSErrorCollaborationProtocolError = 1109,
	CSErrorCollaborationAuthenticationFailed = 1110,
	CSErrorCollaborationInvalidCertificate = 1111,
	CSErrorCollaborationServerError = 1112,
	CSErrorCollaborationMeetingNotFound = 1113,
	CSErrorCollaborationTargetNotFound = 1114,
	CSErrorCollaborationUnavailable = 1115,
	CSErrorCollaborationCollaborationAlreadyCreated = 1116,
	CSErrorCollaborationConfigurationError = 1117,
	CSErrorCollaborationCapabilityRejectedByServer = 1118,
	CSErrorCollaborationInsufficientBandwidth = 1119,

	//Conference connection errors
	CSErrorNetworkNotAvailable = 1200,
	CSErrorInvalidCertificate = 1201,
	CSErrorConferenceConnectionFailedToRecover = 1202,     /**< Attempts to recover connection to conference server have failed.
															The SDK will not be able to support conference call features for the conference call. */

	//Download operation errors
	CSErrorDownloadConnectionFailure = 1300,
	CSErrorDownloadInvalidDestinationDirectory = 1301,
	CSErrorDownloadUnsupportedProtocol = 1302,
	CSErrorDownloadErrorWritingFile = 1303,
	CSErrorDownloadInvalidContentType = 1304,
	CSErrorDownloadBinaryDataExceedsMaxSize = 1305,   /**< Max size of the downloaded binary data is exceeded. */

	//Mobile link errors
	CSErrorMobileLinkSpeakerMuted = 1400,                /**< Reported when Sonic detected that the speaker is muted. */
	CSErrorMobileLinkHeadsetConnected = 1401,            /**< Reported when Sonic detected that headset is connected. */
	CSErrorMobileLinkSonicSignalGenerationFailed = 1402,  /**< Reported when Sonic fails to generate the signal. */
	
	// Feature Label update errors
	CSErrorFeatureLabelDatabaseNotAccessible = 1403,        /**< Reported for database access problem. */
	CSErrorFeatureLabelDatabaseReadWriteFailure = 1404,     /**< Reported for database access failure for reading or writing. */
	CSErrorFeatureLabelConfigurationMismatch = 1405,        /**< Reported when the handle indicated in request not found in database. */
	CSErrorFeatureLabelNotIMUser = 1406,                    /**< Reported when requesting user does not exist in the database. */
	CSErrorFeatureLabelInvalidValue = 1407,                 /**< Reported when invalid field value OR string length exceeds maximum. */
	CSErrorFeatureLabelNoListAvailable = 1408,              /**< Reported when the request from the endpoint did not contain any data. */
	CSErrorFeatureLabelNoButtonFound = 1409,                /**< Reported when the request is for a button that has been deleted on CM. */
	CSErrorFeatureLabelHandleInvalid = 1410,                /**< Reported for missing or invalid provider handle. */
	CSErrorFeatureLabelDigestMismatch = 1411,               /**< Reported for digest authentication failure. */
	CSErrorFeatureLabelUpdateInProgress = 1412,             /**< Reported when device data update already in progress. */
	
	// Push notification errors
	CSErrorPushNotificationServiceShutdown = 1500,         /**<The operation failed because the client has been or is in the process of being shut down. */
	CSErrorPushNotificationServiceRequestCancelled = 1501,
	CSErrorPushNotificationServiceInvalidState = 1502,
	CSErrorPushNotificationServiceInternalError = 1503, 
	CSErrorPushNotificationServiceConnectionError = 1504,  /**<The notification cannot be processed due to no server connectivity. */
	CSErrorPushNotificationServiceDialogNotFound = 1505,   /**< No matching remote dialog found for the notification after dialog subscription refresh. */
	CSErrorPushNotificationServiceConfigurationError = 1506,  /**<The notification cannot be processed due to configuration. */
	CSErrorPushNotificationServiceConnectionSecurityFault = 1507, /**< The connection could not be established securely. */
	CSErrorPushNotificationServiceAuthenticationError = 1508, /**< The credentials provided were not accepted by the server. */

	CSErrorGroupLimitExceeded = 1600,                      /** Group count has reached maximum */
	CSErrorGroupAlreadyExists = 1601,                      /** Group with specified name already exists */
	CSErrorGroupContactsLimitExceeded = 1602,              /** Group contacts count has reached maximum */
	CSErrorGroupCreateNotSupported = 1603,                 /** Contact group provider does not support operation */
	CSErrorGroupDeleteNotSupported = 1604,                 /** Contact group provider does not support operation */
	CSErrorGroupRenameNotSupported = 1605,                 /** Contact group provider does not support operation */
	CSErrorGroupNameInvalid = 1606,                        /** Missing or Invalid Provider contact group name */
	CSErrorGroupNotFound = 1607,                           /** Contact group not found */
	CSErrorGroupAddContactsNotSupported = 1608,            /** Add contacts to a group isn't supported */
	CSErrorGroupRemoveContactsNotSupported = 1609,         /** Remove contacts from a group isn't supported */
	CSErrorGroupNameExceedsMaxLength = 1610,               /** Contact group name is too long */
	CSErrorInvalidCharactersInGroupName = 1611,            /** Contact group name contains invalid characters */
};
