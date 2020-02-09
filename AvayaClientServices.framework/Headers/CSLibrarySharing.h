/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSLibraryDocument.h"
#import "CSParticipant.h"
#import "CSSlide.h"

@protocol CSLibrarySharingDelegate;

/**
 * The library sharing feature is currently not supported apart from two methods of CSLibrarySharingDelegate
 * notifying the client about library sharing started and ended.
 */
@interface CSLibrarySharing : NSObject

/*
 * CSCollaborationDelegate is registered as an observer of library sharing status update notifications.
 * For now only method notifying about sharing started and ended are supported.
 *
 * @see CSLibrarySharingDelegate::CSLibrarySharingDelegate:didStartWithSlide:withParticipant
 * @see CSLibrarySharingDelegate::librarySharingDidEnd:
 */
@property (nonatomic, weak) id<CSLibrarySharingDelegate> delegate;

/**
 * Not supported in Client SDK 3.0
 *
 * Tell if the local user is sharing a document from network-based document library.
 */
@property (nonatomic, readonly, getter=isPresenting) BOOL presenting;

/**
 * Not supported in Client SDK 3.0
 *
 * List of slides in current document.
 */
@property (nonatomic, readonly) NSArray *slides;

/**
 * Not supported in Client SDK 3.0
 *
 * Get active slide of current document
 */
@property (nonatomic, readonly) CSSlide *activeSlide;

/**
 * Not supported in Client SDK 3.0
 */
- (void)shareDocument:(CSLibraryDocument *)document
			   onPage:(NSUInteger)pageNumber
	completionHanlder:(void (^)(CSSlide *slide, NSError *error))handler;

/**
 * Not supported in Client SDK 3.0
 */
- (void)stopSharingWithCompletionHandler:(void (^)(CSSlide *slide, NSError *error))handler;

@end


/**
 * Library sharing delegate provides updates about the status of library document sharing
 * and whether a new shared page is received from the server (for a non presenting participant).
 */
@protocol CSLibrarySharingDelegate <NSObject>

/**
 * Reports that library sharing has started.
 *
 * @param librarySharing Object of CSLibrarySharing sending the message.
 */
- (void)librarySharingDidStart:(CSLibrarySharing *)librarySharing;

/**
 * Reports that library sharing has started. Method is called on each slide changed.
 * 
 * @param librarySharing Object of CSLibrarySharing sending the message.
 * @param slide Always nil since library sharing is not supproted in Client SDK 3.0
 * @param participant Indicates participant who started library sharing
 */
- (void)librarySharing:(CSLibrarySharing *)librarySharing didShareSlide:(CSSlide *)slide byParticipant:(CSParticipant *)participant;

/**
 * Reports that library sharing has ended.
 *
 * @param librarySharing Object of CSLibrarySharing sending the message.
 */
- (void)librarySharingDidEnd:(CSLibrarySharing *)librarySharing;

@end
