/* Copyright Avaya Inc. */

/**
 * Enumeration representing remote camera control commands.
 * The commands are used to control pan, tilt and zoom (PTZ)
 * cameras that support programmatic remote control. For instance,
 * conference room systems' cameras are controllable by conference
 * moderators.
 */

typedef NS_ENUM(NSUInteger, CSCameraControl) {
	/**
	 * Move camera up.
	 */
	CSCameraControlUp = 0,
	/**
	 * Move camera down.
	 */
	CSCameraControlDown,
	/**
	 * Move camera left.
	 */
	CSCameraControlLeft,
	/**
	 * Move camera right.
	 */
	CSCameraControlRight,
	/**
	 * Zoom the camera in.
	 */
	CSCameraControlZoomIn,
	/**
	 * Zoom the camera out.
	 */
	CSCameraControlZoomOut
};

