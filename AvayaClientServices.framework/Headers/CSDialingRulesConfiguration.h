/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 * The dialing rules configuration to be applied to transform
 * a user supplied number into a dialable number.
 */
@interface CSDialingRulesConfiguration : NSObject

/**
 * Indicates whether the dialing rules are enabled.
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * The string of digits to prepend to the dialed number to make an external call from an enterprise network.
 *
 * <p>To disambiguate between internal and external numbers most PBX systems require an access code like "9"
 * to obtain an outside line.</p>
 *
 */
@property (nonatomic, copy) NSString *outsideLineAccessCode;

/**
 * The country code for the user's region.
 *
 *<p>For example, if local phone number is in the form of +1 303-538-1234, then the country code is "1".</p>
 *
 */
@property (nonatomic, copy) NSString *countryCode;

/**
 * The area code for the user's region.
 *
 * <p>For example, if local phone number is in the form of +1 303-538-1234, then the area code is "303".</p>
 *
 */
@property (nonatomic, copy) NSString *areaCode;

/**
 * Indicates whether or not the area code should be removed when dialing local numbers.
 *
 * <p>For example, if the area code is set to "303", the outside line access code is set to "9", and this option
 * is enabled, then applying dialing rules to "303-538-1234" will result in "95381234".</p>
 *
*/
@property (nonatomic, getter=isRemoveAreaCodeForLocalCalls) BOOL removeAreaCodeForLocalCalls;

/**
 * The prefix used for internal extensions.
 *
 * <p>For example, if the area code is set to "303", the prefix is set to "538", and the extension length is 5
 * then the number "+1 303-538-12345" will be dialed as "12345". The combination of area code and prefix allows
 * the dialing rules to recognize an internal number from local, national or international numbering format.</p>
 *
 */
@property (nonatomic, copy) NSString *pbxPrefix;

 /**
  * The long distance access code for the user's region.
  *
  * <p>For example, in the United States, the access code would be "1".</p>
  *
  */
@property (nonatomic, copy) NSString *longDistanceAccessCode;

/**
 * The access code for outgoing international calls.
 *
 * <p>For example, in the United States, this access code would be "011".</p>
 *
 */
@property (nonatomic, copy) NSString *internationalAccessCode;

/**
 * The lengths of national numbers valid for the user's country.
 *
 * <p>These lengths represent numbers without the country code. For example, some European countries like Italy have variable
 * national number lengths between 8 to 12.</p>
 *
 */
@property (nonatomic, copy) NSArray *nationalNumberLengths;

/**
 * The lengths of all internal extensions in the enterprise network.
 *
 */
@property (nonatomic, copy) NSArray *extensionLengths;

/**
 * Indicates whether to disable the dialing rules logic that automatically prefixes the outside line access code to numbers
 * that are shorter than the shortest extension length.
 *
 */
@property (nonatomic) BOOL applyOutsideLineAccessCodeToShortNumbers;

/**
 * Indicates whether to allow sending of E.164 numbers (i.e any numbers with a leading '+') directly to the network server without
 * application of any dialing rules transformations.
 *
 */
@property (nonatomic) BOOL allowE164Passthrough;

/**
 * Indicates whether pressing pound sign during off-hook dialing should trigger the call start.
 */
@property (nonatomic) BOOL enablePoundKeyAsCallTrigger;

@end
