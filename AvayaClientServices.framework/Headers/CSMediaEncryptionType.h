/* Copyright Avaya Inc. */

/**
 * Supported media encryption types.
 */

typedef NS_ENUM(uint32_t, CSMediaEncryptionType) {
	/**
	 * No media encryption is being done.
	 */
	CSMediaEncryptionTypeNone = 0,

	/**
	 * AES 128 SHA 1 HMAC 80 encryption is being used.
	 */
	CSMediaEncryptionTypeAES128SHA1HMAC80,

	/**
	 * AES 128 SHA 1 HMAC 32 encryption is being used.
	 */
	CSMediaEncryptionTypeAES128SHA1HMAC32,

	/**
	 * AES 256 SHA 1 HMAC 80 encryption is being used.
	 */
	CSMediaEncryptionTypeAES256SHA1HMAC80,

	/**
	 * AES 256 SHA 1 HMAC 32 encryption is being used.
	 */
	CSMediaEncryptionTypeAES256SHA1HMAC32,
};

