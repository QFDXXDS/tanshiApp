/* Copyright Avaya Inc. */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation-unknown-command"

/**
 * \if OSX
 *
 * Enum type indicating current whiteboard tool of CSWhiteboardCanvas.
 * @see CSWhiteboardCanvas::tool
 *
 * \endif
 *
 * \if iOS
 *
 * Enum type indicating current whiteboard tool of CSIOSWhiteboardCanvas.
 *
 * @see CSIOSWhiteboardCanvas::tool
 * 
 * \endif
 */

#pragma clang diagnostic pop

typedef NS_ENUM(NSUInteger, CSWhiteboardTool) {
	CSWhiteboardToolMove, /**< Tool which enables user to move shape */
	CSWhiteboardToolDelete, /**< Tool which enables user to delete shape */
	
	CSWhiteboardToolPen, /**< Pen */
	CSWhiteboardToolMarker, /**< Marker */
	
	CSWhiteboardToolLineSmall, /**< Small size line */
	CSWhiteboardToolLineMedium, /**< Medium size line */
	CSWhiteboardToolLineBig, /**< Big size line */
	
	CSWhiteboardToolRectangle, /**< Rectangle */
	CSWhiteboardToolRectangleFilled, /**< Filled rectangle */
	
	CSWhiteboardToolEllipse, /**< Ellipse */
	CSWhiteboardToolEllipseFilled, /**< Filled ellipse */
	
	CSWhiteboardToolStamp, /**< Stamp */
	
	CSWhiteboardToolTextSmall, /**< Small size text */
	CSWhiteboardToolTextMedium, /**< Medium size text */
	CSWhiteboardToolTextBig /**< Big size text */
};
