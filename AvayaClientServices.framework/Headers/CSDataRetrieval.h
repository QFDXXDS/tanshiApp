/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSDataSet.h"

@protocol CSDataRetrievalDelegate;

/**
 * **Deprecated:**
 * Replaced by CSDataRetrievalWatcher.
 * ---
 * **Deprecated:**
 * This class is not thread safe and has been replaced by the CSDataRetrievalWatcher class.
 * Any public methods using CSDataRetrieval are now marked as deprecated and have been replaced
 * by equivalent methods using the CSDataRetrievalWatcher class. Third party applications
 * should not use these deprecated methods as they are not supported by Avaya.
 */
@interface CSDataRetrieval : NSObject

/**
 * This delegates responsible for handling the CSDataRetrieval events
 */
@property (atomic, readonly) NSArray *delegates;

/**
 * The dataset
 */
@property (nonatomic, readonly) CSDataSet *dataSet;

/**
 * Has this data retrieval operation been cancelled?
 * @return @c YES if the operation was cancelled, @c NO otherwise.
 */
@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;

/**
 * Has this data retrieval completed retrieve data?
 * When it is completed, the dataset is filled with data and ready to listen for changes.
 * @return @c YES if it is completed, @c NO otherwise.
 */
@property (nonatomic, readonly, getter=isCompleted) BOOL completed;

/**
 * The requestId that is set by the service when it return DataRetrieval instance.
 */
@property (nonatomic) NSUInteger serviceRequestId;

/**
 * Add a delegate to be notified of progress in retrieving a data set.
 * @param delegate The delegate to be added.
 */
- (void)addDelegate:(id<CSDataRetrievalDelegate>)delegate;

/**
 * Remove a delegate to be notified of progress in retrieving a data set.
 * @param delegate The delegate to be removed.
 */
- (void)removeDelegate:(id<CSDataRetrievalDelegate>)delegate;

/**
 * Cancel the current data retrieval operation.
 * After this, the cancellation will be reported asynchronously to listeners
 */
- (void)cancel;

@end

/**
 * **Deprecated:**
 * Replaced by CSDataRetrievalWatcherDelegate.
 */
@protocol CSDataRetrievalDelegate <NSObject>

/**
 * Called to report progress in loading elements into the data set.
 *
 * This is called after new elements have been added to the data set.
 *
 * @param dataRetrieval The data retrieval operation in progress.
 * @param determinate If @c YES, the total number of elements to be loaded is
 *        known in advance. If @c NO, the total number of elements is not known,
 *        and the retrieval will continue until it runs out of data.
 * @param retrievedCount The number of elements that has been retrieved so far.
 * @param totalCount The total number of elements. This can only be relied upon
 *        when determinate is @c YES.
 */
- (void)dataRetrieval:(CSDataRetrieval *)dataRetrieval didUpdateProgress:(BOOL)determinate retrievedCount:(NSUInteger)retrievedCount totalCount:(NSUInteger)totalCount;

/**
 * Called when the data retrieval operation has completed.
 * @param dataRetrieval The data retrieval operation that completed.
 */
- (void)dataRetrievalDidComplete:(CSDataRetrieval *)dataRetrieval;

/**
 * Called when the data retrieval operation has failed.
 * If this is called, there will be no further updates to the data retrieval
 * and data set. Any existing data in the data set that was already
 * received is still accessible and might still be of use.
 *
 * @param dataRetrieval The data retrieval operation that failed.
 * @param error Object containing information about the failure.
 */
- (void)dataRetrieval:(CSDataRetrieval *)dataRetrieval didFailWithError:(NSError *)error;

@end
