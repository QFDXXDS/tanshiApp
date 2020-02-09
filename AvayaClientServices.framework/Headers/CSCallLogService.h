/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSCapability.h"

@protocol CSCallLogServiceDelegate;
 
/**
 * Describes the status of call log service operations
 */
typedef NS_ENUM(NSInteger, CSCallLogOperationStatusType) {
	/** Operation is successful. */
	CSCallLogOperationStatusTypeSucceeded = 0,
	/** Operation failed. Unrecoverable error. If the problem persists please consult support team. */
	CSCallLogOperationStatusTypeFailed
};

/** Completion handler for actions performed on the CSCallLogService */
typedef void (^CSCallLogCompletionHandler)(NSError *error);


/**
 * Call Log Service provides history entries for calls that have been made or received on the client.
 * The full path to the call log file should be provided by setting UserConfiguration.LocalCallLogFilePath
 * to a platform dependent file path. The path should be unique for each user logging in on the client.
 * @note Currently only local call logs are supported. This means that if call events happen when a user is logged off
 * there will be no call logs captured.
 */
@interface CSCallLogService : NSObject


/** The delegate responsible for handling call log events. */
@property (nonatomic, weak) id<CSCallLogServiceDelegate> delegate;


/** Array of CSCallLogItem containing all call logs */
@property (nonatomic, readonly) NSArray *callLogs;

/**
 * @return CSCapability describing whether 24x7 Call Journaling is enabled.
 */
@property (nonatomic, readonly) CSCapability *networkCallLogsCapability;

/**
 * CSCapability describing whether call logs can be added by client using @see addCallLogsWithArray:withCompletionHandler.
 * Allowed when @see networkCallLogsCapability is not allowed.
 * A client cannot add call logs when 24x7 Call Journaling is enabled on the server and allowed by @see CSPPMConfiguration.
 * @return CSCapability object describing whether manual call logs can be added.
 */
@property (nonatomic, readonly) CSCapability *addCallLogsCapability;

/**
 * CSCapability describing whether call logs can be removed using @see removeCallLogsWithArray:withCompletionHandler.
 * Disabled while network outage.
 * @return CSCapability describing whether call logs can be removed.
 */
@property (nonatomic, readonly) CSCapability *removeCallLogsCapability;


/** This operation reloads all call log items from the persistent storage.
 * The callLogs property contains all call log items loaded from the storage. Completes action with completion handler. 
 * @param handler A block to be called to report the status of the operation.
 */
- (void)resynchronizeCallLogsWithCompletionHandler: (CSCallLogCompletionHandler)handler;


/** 
 * Remove call logs provided in array. 
 * The client can select specific call log objects and request the call log service to remove them permanently.
 * Completes action with completion handler.
 *
 * @param array The array of call log objects to remove.
 * @param handler A block to be called to report the status of the operation.
 */
- (void)removeCallLogsWithArray:(NSArray *)array withCompletionHandler: (CSCallLogCompletionHandler)handler;


/** 
 * Clears all existing call logs from the cache and persistent local storage. Completes action with competion handler. 
 * @param handler A block to be called to report the status of the operation.
 */
- (void)removeAllCallLogsWithCompletionHandler:(CSCallLogCompletionHandler)handler;

/** 
 * Adds the call logs provided in array. Completes action with completion handler.
 *
 * @param array The array of call log objects to add.
 * @param handler A block to be called to report the status of the operation.
 */
- (void)addCallLogsWithArray:(NSArray *)array withCompletionHandler: (CSCallLogCompletionHandler)handler;

@end


/** Describes methods that are implemented by the delegate of a @c CSCallLogService. */
@protocol CSCallLogServiceDelegate <NSObject>

@optional

/** 
 * Callback to indicate a set of call log items have been loaded into cache.
 *
 * @param callLogService The call log service instance sending the message.
 * @param callLogItems the list of call log items loaded from the persistent storage.
 * @param status the status of the load operation.
 */
- (void)callLogServiceDidLoad:(CSCallLogService *)callLogService callLogItems:(NSArray *)callLogItems withStatus:(CSCallLogOperationStatusType)status;


/** 
 * Callback to report removal of call log items.
 *
 * @param callLogService The call log service instance sending the message.
 * @param removedCallLogItemsArray the list of call log items removed from the Call Logs Service.
 */
- (void)callLogService:(CSCallLogService *)callLogService didRemoveCallLogs:(NSArray *)removedCallLogItemsArray;


/**
 * Callback to indicate that call logs item have been added.  New addition of call log item is triggered by
 * ending of an active call.
 *
 * @param callLogService The call log service instance sending the message.
 * @param addedCallLogItemsArray the list of call log items added to the Call Logs Service.
 */
- (void)callLogService:(CSCallLogService *)callLogService didAddCallLogs:(NSArray *)addedCallLogItemsArray;


/**
 * Callback to indicate that Call Log Items have been updated.  This callback can be used to indicate
 * update of one or more Call Log Items
 *
 * @param callLogService The call log service instance sending the message.
 * @param updatedCallLogItemsArray the list of call log items updated by the Call Logs Service.
 */
- (void)callLogService:(CSCallLogService *)callLogService didUpdateCallLogs:(NSArray *)updatedCallLogItemsArray;

/**
 * Occurs when the Сall Log Service capabilities changed.
 * Check the Call Log Service capabilities when the event is triggered.
 */
- (void)callLogServiceDidChangeCapabilities: (CSCallLogService *)callLogService;

@end
