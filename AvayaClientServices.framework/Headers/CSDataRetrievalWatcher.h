/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSDataSet.h"
#import "CSDataRetrieval.h"
#import "CSDataCollectionChangeType.h"

// When support for DataSet in the public API is removed, delete this #define and any blocks of code that are
// being conditionally compiled by the DATASET_SUPPORTED define.
#define DATASET_SUPPORTED

@protocol CSDataRetrievalWatcherDelegate;

/**
 * This class defines an interface that client applications use to perform data retrieval operations
 * for both static and dynamic collections of objects within the SDK.
 *
 * An instance of this watcher class is created by the client application for use in methods that
 * initiate some form of data retrieval operation that runs asynchronously and updates a collection
 * of objects.  It can be used in cases where a static collection of objects is being
 * retrieved (e.g. search results, etc) or for dynamically updated collections that are retrieved
 * and then subsequently updated as events occur within the system (e.g. the active participants
 * in a conference call).
 *
 * Following creation of a CSDataRetrievalWatcher object, and before the object is used in a
 * method call, the application should install a CSDataRetrievalWatcherDelegate on the object.
 * This allows the application's delegate to be wired up prior to initiating the action that will perform the
 * data retrieval.
 *
 * For **static** collections, the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * message will be sent as objects are added to the collection during the retrieval.
 * Once the static collection has been completely retrieved, the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcherDidComplete: dataRetrievalWatcherDidComplete}
 * message will be sent indicating that the retrieval is complete.  Following this, no additional messages will be sent.
 *
 * For **dynamic** collections, the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * message will be sent as objects are added to the collection during the initial retrieval.
 * It will also be sent whenever any of the objects already in the collection are changed or removed.
 * Once the initial retrieval of the dynamic collection has been completed, the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcherDidComplete: dataRetrievalWatcherDidComplete}
 * message will be sent indicating that the initial retrieval is complete.
 * Following this, the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * message will be sent whenever any changes to the collection occur.
 */
@interface CSDataRetrievalWatcher : NSObject

/**
 * The unique request ID associated with this data retrieval.
 * If the request has not been initiated or is not outstanding, the value will be 0.
 */
@property (nonatomic, readonly) NSUInteger requestId;

/**
 * Has the data retrieval operation been cancelled?
 * @return Returns @c YES if the data retrieval was cancelled, @c NO otherwise.
 */
@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;

/**
 * Has the data retrieval completed?
 *
 * When data retrieval has been completed, the {@link #snapshot} property will contain the complete data collection.
 *
 * If this watcher object is watching a **dynamic** collection, additional
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * messages may be received via the installed delegates as the collection is changed following the retrieval.
 * @return Returns @c YES if the data retrieval has been completed, @c NO otherwise.
 */
@property (nonatomic, readonly) BOOL completed;

/**
 * Returns a snapshot of the objects currently in the collection being watched by this object.
 *
 * Note that the returned array is a snapshot in time and is not dynamically updated as the collection changes.
 * Notifications that the collection has changed are received through the installed delegates via the
 * {@link CSDataRetrievalWatcherDelegate::dataRetrievalWatcher:contentsDidChange:changedItems: dataRetrievalWatcher:contentsDidChange:changedItems}
 * message.
 */
@property (nonatomic, readonly, copy) NSArray *snapshot;

/**
 * Adds a delegate to be notified of progress in retrieving a data collection.
 * @param delegate The delegate to be added.
 * @see #removeDelegate:
 */
- (void)addDelegate:(id<CSDataRetrievalWatcherDelegate>)delegate;

/**
 * Removes a delegate from the watcher object.
 * @param delegate The delegate to be removed.
 * @see #addDelegate:
 */
- (void)removeDelegate:(id<CSDataRetrievalWatcherDelegate>)delegate;

/**
 * Cancels the current data retrieval operation if one is in progress.
 * After this, the cancellation will be reported asynchronously to listeners.
 */
- (void)cancel;

@end

/**
 * This protocol is used by {@link CSDataRetrievalWatcher} objects to report progress for the 
 * retrieval operation and updates to the associated data collection.
 */
@protocol CSDataRetrievalWatcherDelegate <NSObject>

@optional // Allow different delegates to be defined to handle parts of this protocol.

/**
 * Sent to report progress in loading elements into the data collection.
 *
 * This message is sent as new elements are added to the data collection and is useful for 
 * updating any progress indicator that may be associated with the data retrieval operation.
 *
 * @param dataRetrievalWatcher The data retrieval watcher object sending the message.
 * @param determinate If @c YES, the total number of elements to be loaded is
 *        known in advance. If @c NO, the total number of elements is not known,
 *        and the retrieval will continue until all elements have been loaded.
 * @param retrievedCount The number of elements that have been retrieved so far.
 * @param totalCount The total number of elements being retrieved. This can only be relied upon
 *        when the *determinate* parameter is @c YES.  When the *determinate* parameter
 *        is @c NO, this will be zero.
 *
 * @see #dataRetrievalWatcher:contentsDidChange:changedItems:
 */
- (void)dataRetrievalWatcher:(CSDataRetrievalWatcher *)dataRetrievalWatcher didUpdateProgress:(BOOL)determinate retrievedCount:(NSUInteger)retrievedCount totalCount:(NSUInteger)totalCount;

/**
 * Sent to report successful completion of the data retrieval operation.
 * @param dataRetrievalWatcher The data retrieval watcher whose retrieval operation has completed.
 */
- (void)dataRetrievalWatcherDidComplete:(CSDataRetrievalWatcher *)dataRetrievalWatcher;

/**
 * Sent to report that the data retrieval operation has failed.
 *
 * After this message is sent, there will be no further updates to the data retrieval
 * and data collection. Any existing data in the data collection that was already
 * received is still accessible and might still be of use.
 *
 * @param dataRetrievalWatcher The data retrieval watcher whose retrieval operation has failed.
 * @param error An error object containing information about the failure.
 */
- (void)dataRetrievalWatcher:(CSDataRetrievalWatcher *)dataRetrievalWatcher didFailWithError:(NSError *)error;

/**
 * Sent whenever the underlying data collection has changed.
 *
 * @param dataRetrievalWatcher The data retrieval watcher whose contents have changed.
 * @param changeType The type of change that has occurred on the data collection.
 * @param changedItems An array of data items that have changed. For a delete change,
 *                     the supplied data items have been removed from the data collection.
 *                     For a "collection cleared" change, this array will be empty.
 */
- (void)dataRetrievalWatcher:(CSDataRetrievalWatcher *)dataRetrievalWatcher contentsDidChange:(CSDataCollectionChangeType)changeType changedItems:(NSArray *)changedItems;

@end
