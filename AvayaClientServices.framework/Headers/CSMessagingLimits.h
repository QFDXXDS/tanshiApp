/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSDefines.h"

typedef unsigned long long CSLimitsSizeType;

CS_EXTERN CSLimitsSizeType CSLimitsSizeTypeUnlimited;

/**
 * This class defines current limits for various messaging service operations.
 * These limits are configured on the messaging server and can change if the server administrator changes them.
 *
 * @see -[CSMessagingServiceDelegate messagingServiceDidChangeCapabilities:]
 */
@interface CSMessagingLimits : NSObject

/**
 * Get the maximum size of an audio file attachment.
 *
 * @return the maximum size of an audio file attachment.
 */
@property (nonatomic, readonly) CSLimitsSizeType maxAudioSize;

/**
 * Get the maximum size of an image file attachment.
 *
 * @return the maximum size of an image file attachment.
 */
@property (nonatomic, readonly) CSLimitsSizeType maxImageSize;

/**
 * Get the maximum size of an attachment that is not an audio file or image file attachment.
 *
 * @return the maximum size of an attachment that is not an audio file or image file attachment.
 */
@property (nonatomic, readonly) CSLimitsSizeType maxGenericAttachmentSize;

/**
 * Get the maximum text length value accepted.
 *
 * @return the maximum text length value accepted.
 * @see -[CSMessage setBodyAndReportTyping:completionHandler:]
 */
@property (nonatomic, readonly) CSLimitsSizeType maxTextLength;

/**
 * Get the maximum video size value accepted.
 *
 * @return the maximum video size value accepted.
 */
@property (nonatomic, readonly) CSLimitsSizeType maxVideoSize;

/**
 * Get the maximum number of attachments per message accepted.
 *
 * @return the maximum number of attachments per message accepted.
 */
@property (nonatomic, readonly) CSLimitsSizeType maxNumberOfAttachmentsPerMessage;

/**
 * Get the maximum conversation subject length.
 *
 * @return the maximum conversation subject length.
 * @see CSMessagingConversation setSubject:completionHandler:]
 */
@property (nonatomic, readonly) CSLimitsSizeType maxConversationSubjectLength;

/**
 * Specifies if client has access to rich content capabilities (attachments of type other than other generic).
 *
 * @return the rich content allowed flag.
 */
@property (nonatomic, readonly, getter=isRichContentAllowed) BOOL richContentAllowed;

@end
