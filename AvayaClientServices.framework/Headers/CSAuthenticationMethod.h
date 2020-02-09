/* Copyright Avaya Inc. */

typedef NS_ENUM(NSInteger, CSAuthenticationMethod)
{
	/**
	 * Basic or Digest authentication, if server proposes both versions Digest is preferred.
	 * If this authentication method is used credential provider is requested to deliver user name and
	 * password (optionally in ha1 form).
	 */
	CSAuthenticationMethodDigestOrBasic,
	
	/**
	 * Client SDK will use system calls to authenticate user using Integrated Windows Authentication
	 * With this authentication methods process will be performed without interaction
	 * with credential provider.
	 */
	CSAuthenticationMethodNegotiate,
	
	/**
	 * Bearer token authentication.
	 * If this authentication method is used, credential provider is requested to deliver auth token
	 * with the time of token expiry.
	 */
	CSAuthenticationMethodBearer
};
