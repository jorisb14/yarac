
/**
 * @file lexer.h
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-10-31
 */

#ifndef _LEXER_H_
#define _LEXER_H_

#include <containers.h>

/**
 * @addtogroup lexer
 * 
 * @{
 */

/**
 * Open and lex a provided file. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     // ... 
 *     assert(Lexer_lexFile(filePath, &tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
signed char Lexer_lexFile(
	const char* filePath,
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_lexFile(_inmacro_filePath, _inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_lexFile((_inmacro_filePath), (_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_lexFile(...) returned with internal failure!"); \
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

/**
 * Validate lexed tokens. Return 0 in case of an error and 1 in case of a success. Should be used
 * as this:
 * 
 * @code{.c}
 *     // ... 
 *     assert(Lexer_validateTokens(filePath, &tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
signed char Lexer_validateTokens(
	const char* const filePath,
	const struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_validateTokens(_inmacro_filePath, _inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_validateTokens((_inmacro_filePath), (_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_validateTokens(...) returned with internal failure!"); \
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

/**
 * @}
 */

#endif
