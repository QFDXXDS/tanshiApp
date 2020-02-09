/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

/**
 * **Unsupported:**
 * The library sharing feature is currently not supported.
 *
 * Class that represents information about a document stored at a conferencing server library.
 * ---
 * **Unsupported:**
 * This class and all of its supporting classes are for internal Avaya use only and should not be
 * used by third party applications at this time. This is an incubating feature that is currently
 * under development and the classes and methods associated with this feature are subject to change
 * at any time. Use of this feature will not be supported by Avaya until such time that it is
 * officially released.
 */
@interface CSLibraryDocument : NSObject

/**
 * Not supported in Client SDK 3.0
 */
@property (nonatomic, readonly) NSString *documentId;

/**
 * Not supported in Client SDK 3.0
 *
 * Document title.
 */
@property (nonatomic, readonly) NSString *title;

/**
 * Not supported in Client SDK 3.0
 *
 * Document path on the library server.
 */
@property (nonatomic, readonly) NSString *url;

/**
 * Not supported in Client SDK 3.0
 *
 * Document creation date. Provided in string form by the network library server.
 */
@property (nonatomic, readonly) NSString *creationDate;

/**
 * Not supported in Client SDK 3.0
 *
 * Number of pages in the document.
 */
@property (nonatomic, readonly) NSUInteger pagesCount;

/**
 * Not supported in Client SDK 3.0
 *
 * Size of the document page in pixels.
 */
@property (nonatomic, readonly) CGSize contentSize;

/**
 * Not supported in Client SDK 3.0
 *
 * Location of the icon file on the network library.
 */
@property (nonatomic, readonly) NSString *iconFile;

@end
