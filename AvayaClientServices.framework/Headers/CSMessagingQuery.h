/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>

/**
 *  Messaging query data.
 *  This class provides data for the messaging service search.
 *  @see -[CSMessagingService searchConversations:watcher:]
 */
@interface CSMessagingQuery : NSObject

/**
 * Initialize query object with default values:
 *
 * - query : empty
 * - queryAfter : empty
 * - numberResultsPerConversation : 15
 * - searchParticipants : YES
 * - searchSubject : YES
 * - searchBody : YES
 */
- (instancetype)init;

/**
 * Initialize query object
 *
 * @param query Expression to be searched. If query is specified, the server will perform a search operation. If query is omitted, the server will perform a getConversations operation
 * @param queryAfter ISO-8601 date string; filters messages based on last-modified-date
 * @param numberResultsPerConversation Number of message entries per conversation to return
 * @param searchParticipants Search participants attribute
 * @param searchSubject Search subject attribute
 * @param searchBody Search body attribute
 */
- (instancetype)initWithQuery:(NSString *)query
				   queryAfter:(NSString *)queryAfter
 numberResultsPerConversation:(NSUInteger)numberResultsPerConversation
		   searchParticipants:(BOOL)searchParticipants
				searchSubject:(BOOL)searchSubject
				   searchBody:(BOOL)searchBody;

/**
 * Search participants attribute.
 */
@property (nonatomic, getter=isSearchParticipants) BOOL searchParticipants;

/**
 * Search subject attribute.
 */
@property (nonatomic, getter=isSearchSubject) BOOL searchSubject;

/**
 * Search body attribute.
 */
@property (nonatomic, getter=isSearchBody) BOOL searchBody;

/**
 * ISO-8601 date string; filters messages based on last-modified-date
 */
@property (nonatomic, copy) NSString *queryAfter;

/**
 * Get expression to be searched. If a query is specified, the server will perform a search
 * operation. If a query is omitted, the server will perform a getConversations operation.
 * @return String to match in search.
 */
@property (nonatomic, copy) NSString *query;

/**
 * Number of message entries per conversation to return (if not specified, defaults to 15)
 */
@property (nonatomic) NSUInteger numberResultsPerConversation;

@end
