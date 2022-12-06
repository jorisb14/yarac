
/**
 * @file parser.h
 *
 * @copyright This file is a part of the project yarac and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-11-01
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <containers.h>
#include <types.h>

/**
 * @addtogroup parser
 * 
 * @{
 */

// TODO: finish the parser API!

/**
 * Parse frame from the provided tokens. Return 0 in case of an error and 1 in case of a success.
 * Should be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     assert(Parser_parseFrame(&frame, &tokens, &succeeded) == 1);
 * @endcode
 */
signed char Parser_parseFrame(
	struct Frame** const frame,
	const struct List* const * const tokens,
	signed char* const succeeded);

#define W_Parser_parseFrame(_inmacro_frame, _inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_parseFrame((_inmacro_frame), (_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_parseFrame(...) returned with internal failure!"); \
			_inmacro_internalFailCallback \
		} \
		else \
		{ \
			if (!(*(_inmacro_succeeded))) \
			{ \
				_inmacro_logicalFailCallback \
			} \
			else \
			{ \
				_inmacro_successCallback \
			} \
		} \
	}

#if 0

/**
 * Parse frame from the provided tokens. Return 0 in case of an error and 1 in case of a success.
 * Should be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     assert(Parser_parseFrame(&tokens, &frame, &succeeded) == 1);
 * @endcode
 */
signed char Parser_parseFrame(
	const struct List* const tokens,
	struct Frame** const frame,
	signed char* const succeeded);

#define W_Parser_parseFrame(_inmacro_tokens, _inmacro_frame, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Parser_parseFrame((_inmacro_tokens), (_inmacro_frame), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Parser_parseFrame(...) returned with internal failure!"); \
			_inmacro_internalFailCallback \
		} \
		else \
		{ \
			if (!(*(_inmacro_succeeded))) \
			{ \
				_inmacro_logicalFailCallback \
			} \
			else \
			{ \
				_inmacro_successCallback \
			} \
		} \
	}

#endif

/**
 * @}
 */

#endif
