/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * Defines the list of supported features. This enum is for all of the features
 * supported by the signaling engine, not tailored based on capabilities provisioned
 * for the user in the network. It is also not tailored based on which features are
 * client invokable via -[CSUser invokeFeature:].
 */
typedef NS_ENUM(NSInteger, CSFeatureType) {
	/**
	 * The uninitialized (or unknown) feature type.
	 */
	CSFeatureTypeUninitialized = 0,

	/**
	 * Send All Calls is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that is used to activate/deactivate coverage path for calls coming in
	 * at a CM station (extension). In summary, the feature activates/de-activates
	 * call coverage at CM. Depending on how CM extension is provisioned, the calls
	 * may be covered to another extension, voice mail, etc. Incoming priority calls
	 * are not affected by the feature's status, that is, incoming priority calls
	 * do not get covered as a result of activating the SAC feature.
	 *
	 * It should be noted that the SAC feature FNU may be used to apply to local user's
	 * CM extension as well as to a third party CM extension (avaya-cm-destination).
	 */
	CSFeatureTypeSendAllCalls,

	/**
	 * Call Forward All is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that is used to activate/deactivate call forwarding for calls coming in
	 * at a CM station (extension). In summary, the feature
	 * activates/de-activates call forwarding at CM.
	 *
	 * It should be noted that the call forward all feature FNU may be used to apply to
	 * local user's CM extension as well as to a third party CM extension (avaya-cm-destination).
	 */
	CSFeatureTypeForwardAllCalls,

	/**
	 * Call Forward Busy No Answer is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that is used to activate/deactivate call forwarding for incoming calls when busy
	 * or when not answered by the user at a CM station (extension). In summary, the feature
	 * activates/de-activates call forwarding at CM.
	 *
	 * It should be noted that this feature FNU may be used to apply to
	 * local user's CM extension as well as to a third party CM extension (avaya-cm-destination).
	 */
	CSFeatureTypeForwardBusyNoAnswerCalls,

	/**
	 * Exclusion is an AST-I feature that uses a 'Feature-Named-URI' (FNU) that is
	 * used to activate/deactivate exclusion by a bridged line appearance user.
	 * In summary, the feature activates/de-activates exclusion at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeExclusion,

	/**
	 * EC500 is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that is used to activate/deactivate EC 500 cellular call extension
	 * at a CM station (extension). In summary, the feature
	 * activates/de-activates EC500 feature at CM station.
	 */
	CSFeatureTypeEC500,

	/**
	 * Extend Call is an AST-I feature that uses a 'Feature-Named-URI' (FNU) that
	 * is used to extend a call to the off-PBX destinations associated with the
	 * extension.
	 * In summary, the feature invokes extend call at the CM station
	 * associated with the user.
	 */
	CSFeatureTypeExtendCall,

	/**
	 * Call Park is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows the user to place the current call in the call park state
	 * so it can be retrieved from another phone.
	 * In summary, the feature invokes call park at the CM station
	 * associated with the user.
	 */
	CSFeatureTypeCallPark,

	/**
	 * Call Unpark is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows the user to retrieve a call parked at another extension.
	 *
	 * In summary, the feature invokes call unpark at the CM station
	 * associated with the user.
	 */
	CSFeatureTypeCallUnpark,

	/**
	 * Auto Callback is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user who placed a call to a busy or unanswered telephone
	 * to be called back automatically when the called telephone becomes available
	 * to receive a call.
	 *
	 * In summary, the feature activates/de-activates auto-callback at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeAutoCallback,

	/**
	 * Whisper Page is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows the user to to make and receive whisper pages. A whisper page
	 * is an announcement sent to another extension that is active on a call where only
	 * the person on the extension hears the announcement; any other parties on the call
	 * cannot hear the announcement.
	 *
	 * In summary, the feature activates/de-activates whisper page at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeWhisperPage,

	/**
	 * Group Call Pickup is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows the user to answer a call that is ringing in the user's
	 * pickup group.
	 *
	 * In summary, the feature invokes group call pickup at the CM station
	 * associated with the user.
	 */
	CSFeatureTypeGroupCallPickup,

	/**
	 * Extended Group Call Pickup is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to answer calls directed to another call pickup group.
	 *
	 * In summary, the feature invokes extended group call pickup at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeExtendedGroupCallPickup,

	/**
	 * Calling Party Number Block is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to block the sending of the calling party number for
	 * one call.
	 *
	 * In summary, the feature invokes calling party number block at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeCallingPartyNumberBlock,

	/**
	 * Calling Party Number Unblock is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to deactivate calling party number (CSN) blocking and
	 * allows the CSN to be sent for a single call.
	 *
	 * In summary, the feature invokes calling party number unblock at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeCallingPartyNumberUnblock,

	/**
	 * One-Touch Recording is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to start and end the recording of an in-progress
	 * conversation using the AUDIX system recording facility.
	 *
	 * In summary, the feature invokes one-touch recording at the
	 * CM station associated with the user.
	 */
	CSFeatureTypeOneTouchRecording,

	/**
	 * Directed Call Pickup is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows the user to answer a call ringing at another extension without
	 * having to be a member of a pickup group.
	 *
	 * In summary, the feature invokes directed call pickup at the CM
	 * station associated with the user.
	 */
	CSFeatureTypeDirectedCallPickup,

	/**
	 * Priority Call is an AST-I feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to place priority calls or change an existing call to
	 * a priority call.
	 *
	 * In summary, the feature invokes priority call at the CM station
	 * associated with the user.
	 */
	CSFeatureTypePriorityCall,

	/**
	 * Enhanced Call Forwarding is feature that uses a 'Feature-Named-URI'
	 * (FNU) that allows a user to configure call forwarding for internal or
	 * external calls with seprate settings for busy, no reply, and
	 * unconditional forwarding. In summary, the feature invokes enhanced
	 * call forwarding at the CM station associated with the user.
	 */
	CSFeatureTypeEnhancedCallForwarding,
	
	/**
	 * Busy Indicator is a feature that allows one to observe another extension
	 * for its availability.
	 * When the far end destination goes off-hook, CM notifies
	 * the same via \<feature name ="busy-indicator" status="on"/\>
	 * When the far end destination goes on-hook, CM notifies
	 * the same via \<feature name ="busy-indicator" status="off"/\>
	 */
	CSFeatureTypeBusyIndicator,
	
	/**
	 * Autodial is a feature button which can be configured as a speed-dial
	 * either by Admin or the user. User can edit the autodial Label
	 * and/or number.
	 *
	 * User can always edit the destinationLabel
	 * User can edit the destinationExtension if the 
	 * isDestinationExtensionEditable flag is true.
	 */
	CSFeatureTypeAutodial,
	
	/**
	 * Hunt Group Busy Position is a feature button which allows user to opt-in/opt-out
	 * from Hunt Group calls.
	 * If your admin have configured your extension as a member of a hunt group,
	 * you will be eligible to receive calls made to that hunt group.
	 * When you don't want to receive calls on that hunt group, the feature needs to be enabled.
	 * When feature is enabled, user will not receive any calls on that Hunt Group.
	 * When feature is disabled, user will start recieving the calls on that hunt group again.
	 *
	 * User can also set the personalized label for the button.
	 */
	CSFeatureTypeHuntGroupBusyPosition,

    /**
     * The Team Button feature allows the user to view the state of another
     * station and allow the user to answer any calls which are actively
     * ringing on that station. The button can also be used as a speed dial
     * to call the monitored station when it is idle.
     */
    CSFeatureTypeTeamButton
};
