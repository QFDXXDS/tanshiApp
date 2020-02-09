/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

#import "CSServerInfo.h"
#import "CSCredentialProvider.h"

typedef NS_ENUM(NSUInteger, CSLDAPDirectoryType) {
	CSLDAPDirectoryTypeUndefined,
	CSLDAPDirectoryTypeActiveDirectory,
	CSLDAPDirectoryTypeNovell,
	CSLDAPDirectoryTypeDomino
};

typedef NS_ENUM(NSUInteger, CSLDAPScopeType) {
	CSLDAPScopeTypeBase,
	CSLDAPScopeTypeOneLevel,
	CSLDAPScopeTypeSubtree
};


/**
 * Configuration information for LDAP.
 */
@interface CSLDAPConfiguration : NSObject

/**
 * A Boolean value indicating whether the LDAP provider is enabled.
 *
 */
@property (nonatomic, getter=isEnabled) BOOL enabled;

/**
 * The signaling server to connect with
 */
@property (nonatomic, strong) CSServerInfo *server;

/**
 * The credential provider
 */
@property (nonatomic, weak) id <CSCredentialProvider> credentialProvider;

/**
 * The base of the distinguished name in a LDAP DIT (Directory Information Tree)
 */
@property (nonatomic, copy) NSString *baseDistinguishedName;

/**
 * YES if IM (Instant Messaging) domain substitution is required.
 */
@property (nonatomic, getter=isIMDomainSubstitutionRequired) BOOL IMDomainSubstitutionRequired;

/**
 * The LDAP attribute that contains the IM handle for the user
 */
@property (nonatomic, copy) NSString *IMHandleAttribute;

/**
 * When GSS (Generic Security Service) bind is enabled, the Windows credentials are used for LDAP connection.
 */
@property (nonatomic, getter=isGSSBind) BOOL GSSBind;

/**
 * Define supported directory type.
 */
@property (nonatomic) CSLDAPDirectoryType directoryType;

/**
 * Define the scope of the LDAP search.
 */
@property (nonatomic) CSLDAPScopeType scopeType;

/**
 * The search time out (in seconds)
 * Range between 10 to 200 seconds
 *
 * Default is 100
 */
@property (nonatomic) NSUInteger searchTimeoutInSeconds;

/**
 * The maximum number of matching entries to display
 * Range between 10 to 100 entries
 *
 * Default is 50
 */
@property (nonatomic) NSUInteger maxEntries;

/**
 * A Boolean value indicating whether the LDAP provider is used for contact resolution.
 *
 * Default is true.
 */
@property (nonatomic) BOOL contactResolutionEnabled;

@end
