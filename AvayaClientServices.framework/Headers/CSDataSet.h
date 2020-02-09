/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, CSDataSetChangeType){
	/** One or more items have been added to the data set. */
	CSDataSetChangeTypeAdded,
	/** One or more items have been deleted from the data set. */
	CSDataSetChangeTypeDeleted,
	/** One or more items in the data set have changed. */
	CSDataSetChangeTypeUpdated
};

@protocol CSDataSetDelegate;

/**
 * **Deprecated:**
 * This class is for internal Avaya use only.
 * ---
 * **Deprecated:**
 * This class is not thread safe and has been deprecated for third party application use.
 * Any public methods returning CSDataSet are now marked as deprecated and have been replaced
 * by equivalent methods on the same class. Third party applications
 * should not use these deprecated methods as they are not supported by Avaya.
 */
@interface CSDataSet : NSObject <NSFastEnumeration>

/**
 *	Returns count The total number of elements in the data set.
 */
@property (nonatomic, readonly) NSUInteger count;

/**
 *	Returns an new array that is a copy of the data set.
 */
- (NSArray*)array;

/**
 * Returns a Boolean value that indicates the data set contains the object or not.
 * @param object The object to test the membership of the data set.
 * @return @c YES if the data set contains the object @ NO
 *         otherwise.
 */
- (BOOL)containsObject:(id)object;

/**
 *	Return the object at the index of the data set.
 *  If index is beyond the end of the ordered set (that is, if index is greater than or equal to thevalue returned by count), an NSRangeException is raised.
 * @param idx An index
 */
- (id)objectAtIndexedSubscript:(NSUInteger)idx;

/**
 * Executes a given block using each object in the data set, starting with the first object and continuing through the data set to the last object.
 * If the Block parameter is nil this method will raise an exception. Values allocated within the block will be deallocated after the block is executed. Use retain to explicitly maintain those values.
 * This method executes synchronously.
 *
 *@param block The block to apply to elements in the array. The block takes three arguments:
 *	@li @c obj The element in the array.
 *	@li @c idx The index of the element in the data set.
 *	@li @c *stop A reference to a Boolean value. The block can set the value to YES to stop further processing of the array. The stop argument is an out-only argument. You should only ever set this Boolean to YES within the Block.
 */
- (void)enumerateObjectsUsingBlock:(void (^)(id obj, NSUInteger idx, BOOL *stop))block;

/**
 * Returns by reference a C array of objects over which the sender should iterate, and as the return value the number of objects in the array. (required)
 * The state structure is assumed to be of stack local memory, so you can recast the passed in state structure to one more suitable for your iteration.
 *
 * @param state Context information that is used in the enumeration to, in addition to other possibilities, ensure that the collection has not been mutated.
 * @param buffer A C array of objects over which the sender is to iterate.
 * @param len The maximum number of objects to return in stackbuf.
 * @return The number of objects returned in stackbuf. Returns 0 when the iteration is finished.
 */
- (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(id __unsafe_unretained [])buffer count:(NSUInteger)len;

/**
 * Add a delegate to be notified of data set changed
 *
 * @param delegate The delegate to be added.
 */
- (void)addDelegate:(id<CSDataSetDelegate>)delegate;

/**
 * Remove a delegate to be notified of data set changed
 *
 * @param delegate The delegate to be removed.
 */
- (void)removeDelegate:(id<CSDataSetDelegate>)delegate;

@end

/**
 * **Deprecated:**
 * This class is for internal Avaya use only.
 */
@protocol CSDataSetDelegate <NSObject>
/**
 * Called whenever the underlying data set has changed.
 *
 * @param dataSet The data set whose contents have changed.
 * @param changedType Enum instance indicating what kind of change it was.
 * @param indexes List of the indices of the elements that have
 *                       changed. For a delete change, the indices are the
 *                       previous indices of the elements, which are now
 *                       occupied by other elements.
 */
- (void)dataSet:(CSDataSet *)dataSet didChange:(CSDataSetChangeType)changedType valuesAtIndexes:(NSIndexSet *)indexes;

/**
 * Called whenever the underlying data has been invalidated.
 * For example, this could be that the user is no longer permitted to access the data.
 *
 * @param dataSet The data set that has been invalidated.
 */
- (void)dataSetInvalidated:(CSDataSet *)dataSet;

@end


