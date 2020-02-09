/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
#import "CSDownloadOptionalParameters.h"
#import "CSDownloadResultInfo.h"
#import "CSDownloadServiceConfiguration.h"
#import "CSDownloadWatcher.h"

/** Completion handler for #CSDownloadService::retrieveDataFromUrlWithConfiguration:sourceURL:optionalParameters:completionHandler: */
typedef void (^CSRetrieveDataFromUrlWithOptionalParametersCompletionHandler)(NSData *binaryData, CSDownloadResultInfo *resultInfo, NSError *error);

/** Completion handler for #CSDownloadService::retrieveTextFromUrlWithConfiguration:sourceURL:optionalParameters:completionHandler: */
typedef void(^CSRetrieveTextFromUrlWithOptionalParametersCompletionHandler)(NSString *textData, CSDownloadResultInfo *resultInfo, NSError *error);

/** Completion handler for #CSDownloadService::downloadFileFromUrlWithConfiguration:sourceURL:destinationDirectory:optionalParameters:completionHandler: */
typedef void(^CSDownloadFileFromUrlWithOptionalParametersCompletionHandler)(NSFileHandle *fileHandle, CSDownloadResultInfo *resultInfo, NSError *error);

/**
 * The DownloadService object provides a set of APIs that allow app to download any files through a URL securely including auto configure setting file, trust cert file, custom logo file, etc.
 */
@interface CSDownloadService : NSObject

/**
 * Retrieve arbitrary binary data from URL. 
 * The download limit is set to 5 MB. 
 * If a client needs to download files larger than 5 MB it should use #downloadFileFromUrlWithConfiguration:sourceURL:destinationDirectory:completionHandler:
 * Otherwise, a successful result is not guaranteed. The operation can fail with DownloadServiceError.Failed error.
 *
 * @param downloadServiceConfiguration Server configuration that will be used for this request.
 * @param sourceURL URL of the source file.
 * @param handler The completion handler for this operation.
 *
 * @return DownloadWatcher object for monitoring download requests.
 */
-(CSDownloadWatcher *)retrieveDataFromUrlWithConfiguration:(CSDownloadServiceConfiguration *)downloadServiceConfiguration
								  sourceURL:(NSURL *)sourceURL
						  completionHandler:(void(^)(NSData *binaryData, NSError *error)) handler;

/**
 * Retrieve arbitrary binary data from URL.
 * The download limit is set to 5 MB.
 * If a client needs to download files larger than 5 MB it should use #downloadFileFromUrlWithConfiguration:sourceURL:destinationDirectory:optionalParameters:completionHandler:
 * Otherwise, a successful result is not guaranteed. The operation can fail with DownloadServiceError.Failed error.
 *
 * @param downloadServiceConfiguration Server configuration that will be used for this request.
 * @param sourceURL URL of the source file.
 * @param optionalParameters Optional parameters to control download process.
 * @param handler The completion handler for this operation. The binaryData may be null if either an error occurs or the file has not been modified as compared to its version identified by the E-Tag passed as part of the optional download parameters.
 *
 * @return DownloadWatcher object for monitoring download requests.
 */
-(CSDownloadWatcher *)retrieveDataFromUrlWithConfiguration:(CSDownloadServiceConfiguration *)downloadServiceConfiguration
                                                 sourceURL:(NSURL *)sourceURL
                                        optionalParameters:(CSDownloadOptionalParameters *)optionalParameters
                                         completionHandler:(CSRetrieveDataFromUrlWithOptionalParametersCompletionHandler) handler;


/**
 * Retrieve text data from URL.
 * The download limit is set to 5 MB. 
 * If a client needs to download files larger than 5 MB it should use #downloadFileFromUrlWithConfiguration:sourceURL:destinationDirectory:completionHandler:
 * Otherwise, a successful result is not guaranteed. The operation can fail with DownloadServiceError.Failed error.
 * Use this method only for downloading text files(Content-Type prefix "text" or "message").
 * Otherwise the operation will fail with DownloadServiceError.InvalidContentType error.
 * @param downloadServiceConfiguration Server configuration that will be used for this request.
 * @param sourceURL URL of the source file.
 * @param handler The completion handler for this operation.
 *
 * @return DownloadWatcher object for monitoring download requests.
 */
-(CSDownloadWatcher *)retrieveTextFromUrlWithConfiguration:(CSDownloadServiceConfiguration *)downloadServiceConfiguration
								  sourceURL:(NSURL *)sourceURL
						  completionHandler:(void(^)(NSString *textData, NSError *error)) handler;

/**
 * Retrieve text data from URL.
 * The download limit is set to 5 MB.
 * If a client needs to download files larger than 5 MB it should use #downloadFileFromUrlWithConfiguration:sourceURL:destinationDirectory:optionalParameters:completionHandler:
 * Otherwise, a successful result is not guaranteed. The operation can fail with DownloadServiceError.Failed error.
 * Use this method only for downloading text files(Content-Type prefix "text" or "message").
 * Otherwise the operation will fail with DownloadServiceError.InvalidContentType error.
 * @param downloadServiceConfiguration Server configuration that will be used for this request.
 * @param sourceURL URL of the source file.
 * @param optionalParameters Optional parameters to control download process.
 * @param handler The completion handler for this operation. The textData may be null if either an error occurs or the file has not been modified as compared to its version identified by the E-Tag passed as part of the optional download parameters.
 *
 * @return DownloadWatcher object for monitoring download requests.
 */
-(CSDownloadWatcher *)retrieveTextFromUrlWithConfiguration:(CSDownloadServiceConfiguration *)downloadServiceConfiguration
                                                 sourceURL:(NSURL *)sourceURL
                                        optionalParameters:(CSDownloadOptionalParameters *)optionalParameters
                                         completionHandler:(CSRetrieveTextFromUrlWithOptionalParametersCompletionHandler) handler;


/**
 * Retrieve FileHandle for downloaded data from URL.
 * This function allows clients to download large files.
 *
 * @param downloadServiceConfiguration Server configuration that will be used for this request.
 * @param destinationDirectory The directory for storing downloaded data.
 * @param sourceURL URL of the source file.
 * @param handler The completion handler for this operation.
 *
 * @return DownloadWatcher object for monitoring download requests.
 */
-(CSDownloadWatcher *)downloadFileFromUrlWithConfiguration:(CSDownloadServiceConfiguration *)downloadServiceConfiguration
								  sourceURL:(NSURL *)sourceURL
					   destinationDirectory:(NSString *)destinationDirectory
						  completionHandler:(void(^)(NSFileHandle *fileHandle, NSError *error)) handler;


/**
 * Retrieve FileHandle for downloaded data from URL.
 * This function allows clients to download large files.
 *
 * @param downloadServiceConfiguration Server configuration that will be used for this request.
 * @param destinationDirectory The directory for storing downloaded data.
 * @param sourceURL URL of the source file.
 * @param optionalParameters Optional parameters to control download process.
 * @param handler The completion handler for this operation. The fileHandle may be null if either an error occurs or the file has not been modified as compared to its version identified by the E-Tag passed as part of the optional download parameters.
 *
 * @return DownloadWatcher object for monitoring download requests.
 */
-(CSDownloadWatcher *)downloadFileFromUrlWithConfiguration:(CSDownloadServiceConfiguration *)downloadServiceConfiguration
                                                 sourceURL:(NSURL *)sourceURL
                                      destinationDirectory:(NSString *)destinationDirectory
                                        optionalParameters:(CSDownloadOptionalParameters *)optionalParameters
                                         completionHandler:(CSDownloadFileFromUrlWithOptionalParametersCompletionHandler) handler;

@end

