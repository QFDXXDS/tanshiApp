#import <Foundation/Foundation.h>

/**
 * The various ring pattern values.
 */
typedef NS_ENUM(NSInteger, CSRingPattern) {
	/** Undefined ring pattern. */
	CSRingPatternUnspecified = 0,
	/** Half ring pattern. */
	CSRingPatternHalfRing,
	/** Intercom ring pattern. */
	CSRingPatternInterRing
};

/**
 * The various ring types.
 */
typedef NS_ENUM(NSInteger, CSRingType) {
	/** Undefined ring type. */
	CSRingTypeUnspecified = 0,
	/** Abbreviated ring type. */
	CSRingTypeAbbreviated,
	/** Delayed ring Type. */
	CSRingTypeDelayed,
	/** Intercom ring Type. */
	CSRingTypeIntercom,
	/** Ring type ON i.e alerts with ring. */
	CSRingTypeOn,
	/** Ring type OFF used for enhanced call-pickup alert. */
	CSRingTypeOff,
	/** Continuous ring type. */
	CSRingTypeContinuous,
	/** Silent ring type if user busy. */
	CSRingTypeIfBusySilent,
	/** Single ring if user busy. */
	CSRingTypeIfBusySingle,
	/** Single ring Type. */
	CSRingTypeSingle
};

