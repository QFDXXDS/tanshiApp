/* Copyright Avaya Inc. */

#ifndef CSDataCollectionChangeType_h
#define CSDataCollectionChangeType_h

/**
 * An enumeration used to describe the type of change that has occurred to a data collection.
 */
typedef NS_ENUM(NSUInteger, CSDataCollectionChangeType) {
	/**
	 * One or more items have been added to the data collection.
	 */
	CSDataCollectionChangeTypeAdded,
	
	/**
	 * One or more items in the data collection have changed.
	 */
	CSDataCollectionChangeTypeUpdated,
	
	/**
	 * One or more items have been deleted from the data collection.
	 */
	CSDataCollectionChangeTypeDeleted,
	
	/**
	 * The entire data collection has been cleared (i.e. all items removed).
	 */
	CSDataCollectionChangeTypeCleared
};

#endif /* CSDataCollectionChangeType_h */
