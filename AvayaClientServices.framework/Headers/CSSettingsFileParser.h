/* Copyright Avaya Inc. */

#import <Foundation/Foundation.h>
@protocol CSSettingsFileParserDelegate;

/**
 * Represents a parser that reads Avaya endpoint settings file format. 
 */
@interface CSSettingsFileParser : NSObject

@property (nonatomic, retain) NSData *data;

/**
 * The delegate used to handle setting file related events.
 */
@property (nonatomic, weak) id<CSSettingsFileParserDelegate> delegate;

/**
 * Parses the supplied settings file.
 *
 * The delegate passed is used to handle all operations that are specified in
 * the settings file, see CSSettingsFileParserDelegate for details.
 *
 * @return YES if the input buffer was fully parsed, NO if parsing was
 * interrupted by a request for an additional settings file.
 */
- (BOOL)parse;

/**
 * Continues parsing of a previous parse that was interrupted.
 *
 * A parse may be interrupted if a call is made to the delegate method
 * parser:requestAdditionalSettingsFile:. If the requested file cannot be
 * obtained the application should call continueParse to continue parsing the
 * current file.
 *
 * @return YES if the input buffer was fully parsed, NO if parsing was
 * interrupted by a request for an additional settings file.
 */
- (BOOL)continueParse;

@end

/**
 * CSSettingsFileParserDelegate is registered as an observer of setting file parser.
 * @see CSSettingsFileParser
 */
@protocol CSSettingsFileParserDelegate <NSObject>

/**
 * Called when the settings file requires the value of a variable.
 *
 * When the parser encounters an statement like:
 *
 * IF $VARIABLE SEQ 1 GOTO JUMP
 *
 * This method will be called to retrieve the value of VARIABLE. If the
 * variable exists the value should be returned. If the value does not exist,
 * this method should return nil and the test will be skipped.
 *
 * @param parser The parser object.
 * @param name The variable name.
 * @return The value of the variable if it exists exists, nil if not.
 */
- (NSString *)parser:(CSSettingsFileParser *)parser getVariable:(NSString *)name;

/**
 * Called when the settings file specifies a new value for a variable.
 *
 * @param parser The parser object.
 * @param name The name of the variable in upper case.
 * @param value The value of the variable.
 */
- (void)parser:(CSSettingsFileParser *)parser setVariable:(NSString *)name value:(NSString *)value;

/**
 * Called when an additional settings file is requested
 *
 * This method is called for statements like:
 *
 * GET 46xxsettings.txt
 *
 * This specifies that parsing of the current settings file should stop and the
 * specified file be parsed instead. However, if the requested file cannot be
 * obtained (for example, does not exist on the server) then parsing of the
 * current file should resume.
 *
 * To accomplish this an application should attempt to retrieve the requested
 * file and if successful update the data property with the contents of the
 * new file and call parse. If unsuccessful, call continueParse to continue
 * parsing the current buffer.
 *
 * @param parser The parser object.
 * @param path Relative path to the requested file on the server.
 */
- (void)parser:(CSSettingsFileParser *)parser requestAdditionalSettingsFile:(NSString *)path;

@end
