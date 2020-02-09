/* Copyright Avaya Inc. */

/**
 * Supported Data sharing modes for collaboration.
 */

typedef NS_ENUM(uint32_t, CSDataSharingMode) {
	/**
	 * Unknown sharing mode.
	 */
	CSSharingModeUnknown = 0,

	/**
	 * BFCP over UDP
	 */
	CSSharingModeBfcpUdp,

	/**
	 * BFCP over TCP
	 */
	CSSharingModeBfcpTcp,

	/**
	 * BFCP over TLC.
	 */
	CSSharingModeBfcpTls,

	/**
	 * WCS over web socket.
	 */
	CSSharingModeWcsWebSocket,
    
    /**
     * WCS over HTTP.
     */
    CSSharingModeWcsHttp,
};

