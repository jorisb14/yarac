
/**
 * @file lexer.c
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-10-31
 */

#include <lexer.h>
#include <logger.h>
#include <rtm.h>
#include <types.h>

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <ctype.h>

/**
 * @addtogroup lexer
 * 
 * @{
 */

static char* _lexer_begin;
static char* _lexer_current;
static char* _lexer_end;
static struct Location _lexer_location;
static unsigned long long _lexer_id;

/**
 * Used to optimize parsing of keyword, intrinsic, decorator, and other tokens.
 */
struct Lexer_TokenTemplate
{
	const char* name;
	unsigned long long length;
};

/**
 * [PRIVATE]
 * 
 * Read a line from provided file and return the length of the line. Return 0 in case of an error
 * and 1 in case of a success. Should be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_getLine(1, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
static signed char Lexer_getLine(
	unsigned long long* const length,
	FILE* const file,
	signed char* const reachedEOF,
	signed char* const succeeded);

#define W_Lexer_getLine(_inmacro_length, _inmacro_file, _inmacro_reachedEOF, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_getLine((_inmacro_length), (_inmacro_file), (_inmacro_reachedEOF), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_getLine(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Move the _lexer_current pointer by a specified amount. Return 0 in case of an error and 1 in
 * case of a success. Should be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_moveBy(1, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
static signed char Lexer_moveBy(
	const signed long long amount,
	signed char* const succeeded);

#define W_Lexer_moveBy(_inmacro_amount, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_moveBy((_inmacro_amount), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_moveBy(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Check if provided char is a whitespace. Return 0 in case of an error and 1 in case of a success.
 * Should be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     signed char is;
 *     signed char succeeded;
 *     assert(Lexer_isWhitespaceChar('a', %is, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
static signed char Lexer_isWhitespaceChar(
	const char ch,
	signed char* const is,
	signed char* const succeeded);

#define W_Lexer_isWhitespaceChar(_inmacro_ch, _inmacro_is, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_isWhitespaceChar((_inmacro_ch), (_inmacro_is), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_isWhitespaceChar(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Check if provided char is an identifier char. Return 0 in case of an error and 1 in case of a
 * success. Should be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     signed char is;
 *     signed char succeeded;
 *     assert(Lexer_isIdentifierChar('a', &is, &succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
static signed char Lexer_isIdentifierChar(
	const char ch,
	signed char* const is,
	signed char* const succeeded);

#define W_Lexer_isIdentifierChar(_inmacro_ch, _inmacro_is, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_isIdentifierChar((_inmacro_ch), (_inmacro_is), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_isIdentifierChar(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Skip consecutive whitespaces in a line. Return 0 in case of an error and 1 in case of a success.
 * Should be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     assert(Lexer_skipWhitespaces(&succeeded) == 1);
 *     assert(succeeded == 1);
 *     // ... 
 * @endcode
 */
static signed char Lexer_skipWhitespaces(
	signed char* const succeeded);

#define W_Lexer_skipWhitespaces(_inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_skipWhitespaces((_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_skipWhitespaces(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Try parse a keyword token. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_tryParseKeyword(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_tryParseKeyword(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_tryParseKeyword(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_tryParseKeyword((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_tryParseKeyword(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Try parse an intrinsic token. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     struct Vector tokens;
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_tryParseIntrinsic(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_tryParseIntrinsic(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_tryParseIntrinsic(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_tryParseIntrinsic((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_tryParseIntrinsic(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Try parse a decorator token. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     struct Vector tokens;
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_tryParseDecorator(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_tryParseDecorator(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_tryParseDecorator(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_tryParseDecorator((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_tryParseDecorator(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Try parse an identifier token. Return 0 in case of an error and 1 in case of a success. Should
 * be used as this:
 * 
 * @code{.c}
 *     struct Vector tokens;
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_tryParseIdentifier(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_tryParseIdentifier(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_tryParseIdentifier(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_tryParseIdentifier((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_tryParseIdentifier(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Try parse a string literal token. Return 0 in case of an error and 1 in case of a success.
 * Should be used as this:
 * 
 * @code{.c}
 *     struct Vector tokens;
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_tryParseStringLiteral(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_tryParseStringLiteral(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_tryParseStringLiteral(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_tryParseStringLiteral((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_tryParseStringLiteral(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Try parse a signed integer (i8 - i64) literal token. Return 0 in case of an error and 1 in case
 * of a success. Should be used as this:
 * 
 * @code{.c}
 *     struct Vector tokens;
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_tryParseSignedIntegerLiteral(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_tryParseSignedIntegerLiteral(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_tryParseSignedIntegerLiteral(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_tryParseSignedIntegerLiteral((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_tryParseSignedIntegerLiteral(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Try parse a unsigned integer (u8 - u64) literal token. Return 0 in case of an error and 1 in
 * case of a success. Should be used as this:
 * 
 * @code{.c}
 *     struct Vector tokens;
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_tryParseUnsignedIntegerLiteral(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_tryParseUnsignedIntegerLiteral(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_tryParseUnsignedIntegerLiteral(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_tryParseUnsignedIntegerLiteral((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_tryParseUnsignedIntegerLiteral(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Try parse a floating point literal (f32 - f64) literal token. Return 0 in case of an error and 1
 * in case of a success. Should be used as this:
 * 
 * @code{.c}
 *     struct Vector tokens;
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_tryParseFloatingPointLiteral(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_tryParseFloatingPointLiteral(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_tryParseFloatingPointLiteral(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_tryParseFloatingPointLiteral((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_tryParseFloatingPointLiteral(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Try parse a pointer literal token. Return 0 in case of an error and 1 in case of a success.
 * Should be used as this:
 * 
 * @code{.c}
 *     struct Vector tokens;
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_tryParsePointerLiteral(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_tryParsePointerLiteral(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_tryParsePointerLiteral(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_tryParsePointerLiteral((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_tryParsePointerLiteral(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Try parse an invalid token. Return 0 in case of an error and 1 in case of a success. Should be
 * used as this:
 * 
 * @code{.c}
 *     struct Vector tokens;
 *     // ... 
 *     signed char succeeded;
 *     assert(Lexer_tryParseInvalid(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_tryParseInvalid(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_tryParseInvalid(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_tryParseInvalid((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_tryParseInvalid(...) returned with internal failure!"); \
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
 * [PRIVATE]
 * 
 * Lex a line, append tokens, and collect logs. Return 0 in case of an error and 1 in case of a
 * success. Should be used as this:
 * 
 * @code{.c}
 *     struct Vector tokens;
 *     // ... 
 *     assert(Lexer_lexLine(&tokens, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
static signed char Lexer_lexLine(
	struct Vector* const * const tokens,
	signed char* const succeeded);

#define W_Lexer_lexLine(_inmacro_tokens, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!Lexer_lexLine((_inmacro_tokens), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function Lexer_lexLine(...) returned with internal failure!"); \
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

signed char Lexer_lexFile(
	const char* filePath,
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (filePath == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `filePath` is invalid (null)!");
		return 0;
	}

	if (strlen(filePath) <= 0)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `filePath` was empty!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	// Setup
	_lexer_begin = _lexer_current = _lexer_end = NULL;
	_lexer_location = (struct Location)
	{
		.file = filePath,
		.line = 1,
		.column = 1
	};
	_lexer_id = 0;

	// Opening a provided file
	FILE* file = fopen(filePath, "r");

	if (file == NULL)
	{
		W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
			"failed to open source file with path `%s`!",
			filePath);
		*succeeded = 0;
		return 1;
	}

	signed char reachedEOF = 0;

	while (!reachedEOF)
	{
		unsigned long long length = 0;

		W_Lexer_getLine(&length, file, &reachedEOF, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			// TODO: log!
			// *succeeded = 0;
			return 1;
		},
		{});

		if (reachedEOF)
		{
			break;
		}

		#define SUGGESTED_MAX_LINE_LENGTH ((signed long long)256)
		if (length > SUGGESTED_MAX_LINE_LENGTH) // NOTE: warn when line is longer than SUGGESTED_MAX_LINE_LENGTH symbols
		{
			struct Location location = (struct Location) { .file = filePath, .line = _lexer_location.line, .column = SUGGESTED_MAX_LINE_LENGTH };
			W_Logger_log(LOG_KIND_WARNING, location,
				"a line of code should not exceed %lld symbols!",
				SUGGESTED_MAX_LINE_LENGTH);
		}
		#undef SUGGESTED_MAX_LINE_LENGTH

		_lexer_current = _lexer_begin;
		_lexer_end = _lexer_begin + length;

		W_Lexer_lexLine(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to lex line!");
			// *succeeded = 0;
			return 1;
		},
		{});

		++_lexer_location.line;
		_lexer_location.column = 1;
	}

	if (_lexer_begin != NULL)
	{
		W_RTM_free((const void* const * const)&_lexer_begin, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to deallocate lexer's read line buffer!");
			// *succeeded = 0;
			return 1;
		},
		{});
	}

	fclose(file);
	*succeeded = 1;
	return 1;
}

signed char Lexer_validateTokens(
	const char* const filePath,
	const struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (filePath == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `filePath` is invalid (null)!");
		return 0;
	}

	if (strlen(filePath) <= 0)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `filePath` was empty!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if ((*tokens)->count <= 0)
	{
		W_Logger_log(LOG_KIND_ERROR, NO_LOCATION,
			"provided function parameter `tokens` is empty in file `%s`, whch is forbidden!",
			filePath);
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 1;

	for (unsigned long long index = 0; index < (*tokens)->count; ++index)
	{
		struct Token* token = NULL;

		W_Vector_getAt((struct Vector* const * const)tokens, index, (void** const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			// TODO: log!
			// *succeeded = 0;
			return 1;
		},
		{});

		if (token->kind == TOKEN_KIND_INVALID)
		{
			W_Logger_log(LOG_KIND_ERROR, token->location,
				"encountered an invalid token `%.*s`!",
				(signed int)token->source.length, token->source.buffer);
			*succeeded = 0;
		}
	}

	return 1;
}

static signed char Lexer_getLine(
	unsigned long long* const length,
	FILE* const file,
	signed char* const reachedEOF,
	signed char* const succeeded)
{
	if (length == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `length` is invalid (null)!");
		return 0;
	}

	if (file == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `file` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;
	*reachedEOF = 0;
	*length = 0;

	char c = 0;

	do
	{
		c = fgetc(file);

		if (c == '\n')
		{
			break;
		}

		if (c == EOF)
		{
			*reachedEOF = 1;
			break;
		}

		++(*length);
	} while (c != EOF);

	if (*length <= 0 && *reachedEOF)
	{
		*succeeded = 1;
		return 1;
	}

	*length = *length != 0 ? *length + 1 : *length;
	fseek(file, -(*length), SEEK_CUR);

	if (_lexer_begin != NULL)
	{
		W_RTM_free((const void* const * const)&_lexer_begin, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			// TODO: log!
			// *succeeded = 0;
			return 1;
		},
		{
			_lexer_begin = NULL;
		});
	}

	W_RTM_malloc((const void** const)&_lexer_begin, (*length + 1) * sizeof(char), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		// TODO: log!
		// *succeeded = 0;
		return 1;
	},
	{});

	char* result = fgets(_lexer_begin, *length + 1, file);
	_lexer_begin[*length] = 0;
	(void)result; // Hack to supress errors for unused return value.

	*succeeded = 1;
	return 1;
}

static signed char Lexer_moveBy(
	const signed long long amount,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	for (signed long long i = 0; i < amount && _lexer_current < _lexer_end; ++i)
	{
		++_lexer_current;
		++_lexer_location.column;
	}

	*succeeded = 1;
	return 1;
}

static signed char Lexer_isWhitespaceChar(
	const char ch,
	signed char* const is,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*is = ch == ' ' || ch == '\t' || ch == '\n';
	*succeeded = 1;
	return 1;
}

static signed char Lexer_isIdentifierChar(
	const char ch,
	signed char* const is,
	signed char* const succeeded)
{
	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*is = ch == '.' || ch == '_' || isalpha(ch) || isdigit(ch);
	*succeeded = 1;
	return 1;
}

static signed char Lexer_skipWhitespaces(
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	while (1)
	{
		signed char isWhitespaceChar = 0;

		W_Lexer_isWhitespaceChar(*_lexer_current, &isWhitespaceChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to check if char is a whitespace!");
			// *succeeded = 0;
			return 1;
		},
		{});

		if (isWhitespaceChar)
		{
			W_Lexer_moveBy(1, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to move the lexer's pointer!");
				// *succeeded = 0;
				return 1;
			},
			{});
		}
		else
		{
			break;
		}
	}

	*succeeded = 1;
	return 1;
}

static signed char Lexer_tryParseKeyword(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	// NOTE: this `keywordTokenKindsCount` define must be changed when modifying the `keywordTokenKinds` set!
	#define keywordTokenKindsCount ((unsigned int)36)
	static const struct Lexer_TokenTemplate keywordTokenKinds[] =
	{
		[TOKEN_KIND_KEYWORD_I8] = { "i8", 2 },
		[TOKEN_KIND_KEYWORD_I16] = { "i16", 3 },
		[TOKEN_KIND_KEYWORD_I32] = { "i32", 3 },
		[TOKEN_KIND_KEYWORD_I64] = { "i64", 3 },
		[TOKEN_KIND_KEYWORD_U8] = { "u8", 2 },
		[TOKEN_KIND_KEYWORD_U16] = { "u16", 3 },
		[TOKEN_KIND_KEYWORD_U32] = { "u32", 3 },
		[TOKEN_KIND_KEYWORD_U64] = { "u64", 3 },
		[TOKEN_KIND_KEYWORD_F32] = { "f32", 3 },
		[TOKEN_KIND_KEYWORD_F64] = { "f64", 3 },
		[TOKEN_KIND_KEYWORD_P8] = { "p8", 2 },
		[TOKEN_KIND_KEYWORD_P16] = { "p16", 3 },
		[TOKEN_KIND_KEYWORD_P32] = { "p32", 3 },
		[TOKEN_KIND_KEYWORD_P64] = { "p64", 3 },
		[TOKEN_KIND_KEYWORD_NULL] = { "null", 4 },
		[TOKEN_KIND_KEYWORD_IMPORT] = { "import", 6 },
		[TOKEN_KIND_KEYWORD_FROM] = { "from", 4 },
		[TOKEN_KIND_KEYWORD_MODULE] = { "module", 6 },
		[TOKEN_KIND_KEYWORD_EXPORT] = { "export", 6 },
		[TOKEN_KIND_KEYWORD_ALIAS] = { "alias", 5 },
		[TOKEN_KIND_KEYWORD_CONST] = { "const", 5 },
		[TOKEN_KIND_KEYWORD_PACKED] = { "packed", 6 },
		[TOKEN_KIND_KEYWORD_STRUCT] = { "struct", 6 },
		[TOKEN_KIND_KEYWORD_FIELD] = { "field", 5 },
		[TOKEN_KIND_KEYWORD_BYTES] = { "bytes", 5 },
		[TOKEN_KIND_KEYWORD_INLINE] = { "inline", 6 },
		[TOKEN_KIND_KEYWORD_PROCEDURE] = { "procedure", 9 },
		[TOKEN_KIND_KEYWORD_IN] = { "in", 2 },
		[TOKEN_KIND_KEYWORD_OUT] = { "out", 3 },
		[TOKEN_KIND_KEYWORD_AS] = { "as", 2 },
		[TOKEN_KIND_KEYWORD_RETURN] = { "return", 6 },
		[TOKEN_KIND_KEYWORD_IF] = { "if", 2 },
		[TOKEN_KIND_KEYWORD_WHILE] = { "while", 5 },
		[TOKEN_KIND_KEYWORD_WITH] = { "with", 4 },
		[TOKEN_KIND_KEYWORD_DO] = { "do", 2 },
		[TOKEN_KIND_KEYWORD_END] = { "end", 3 }
	};
	static_assert((TOKEN_KIND_LAST_KEYWORD - TOKEN_KIND_FIRST_KEYWORD + 1) == keywordTokenKindsCount,
		"The local `keywordTokenKinds` set is not synced with updated types enum!");
	#undef keywordTokenKindsCount

	unsigned long long wordLength = 0;

	for (const char* temp = _lexer_current; temp < _lexer_end; ++temp)
	{
		signed char isWhitespaceChar = 0;

		W_Lexer_isWhitespaceChar(*temp, &isWhitespaceChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to check if char is a whitespace!");
			// *succeeded = 0;
			return 1;
		},
		{});

		if (isWhitespaceChar)
		{
			break;
		}

		++wordLength;
	}

	if (wordLength <= 0)
	{
		*succeeded = 0;
		return 1;
	}

	for (signed long long type = TOKEN_KIND_FIRST_KEYWORD; type <= TOKEN_KIND_LAST_KEYWORD; ++type)
	{
		const char* keywordTokenKind = keywordTokenKinds[type].name;
		const unsigned long long keywordTokenKindLength = keywordTokenKinds[type].length;

		if ((wordLength == keywordTokenKindLength) && (strncmp(_lexer_current, keywordTokenKind, keywordTokenKindLength) == 0))
		{
			struct Token* token = NULL;

			// NOTES:
			//     1. Token is allocated on the heap. It should be deallocated at any error or crash of the compiler.
			//     2. Tokens are handled in the main process of the compiler.
			//     3. I do not handle the deallocation of the token in case of an errors below with mallocs for buffers
			//        and sources, because these errors will not crash the compiler and all the memory it used will be
			//        deallocated either way. So, there is no need to deallocated the token in case of the following
			//        errors right now. (Need to keep in mind in the future!)
			W_Token_create(&token, _lexer_id++, type, &_lexer_location, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to add token to tokens list!");
				// *succeeded = 0;
				return 1;
			},
			{});

			token->source.buffer = NULL;

			W_RTM_malloc((const void** const)&token->source.buffer, wordLength * sizeof(char), succeeded,
			{
				// NOTES:
				//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
				//        is going to be shut down either way.
				W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to push new memory block to !");

				// NOTES:
				//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
				//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
				//        big of a deal to leave a single token.
				W_Token_destroy((const struct Token* const * const)&token, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					*succeeded = 0;
					return 0;
				},
				{});

				*succeeded = 0;
				return 1;
			},
			{});

			memcpy(token->source.buffer, _lexer_current, wordLength);
			token->source.length = wordLength;

			W_Lexer_moveBy(wordLength, succeeded,
			{
				// NOTES:
				//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
				//        is going to be shut down either way.
				W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to move the lexer's pointer!");

				// NOTES:
				//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
				//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
				//        big of a deal to leave a single token.
				W_Token_destroy((const struct Token* const * const)&token, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					*succeeded = 0;
					return 0;
				},
				{});

				*succeeded = 0;
				return 1;
			},
			{});

			W_Vector_pushLast(tokens, (void* const)token, succeeded,
			{
				// NOTES:
				//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
				//        is going to be shut down either way.
				W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to add token to tokens list!");

				// NOTES:
				//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
				//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
				//        big of a deal to leave a single token.
				W_Token_destroy((const struct Token* const * const)&token, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					*succeeded = 0;
					return 0;
				},
				{});

				*succeeded = 0;
				return 1;
			},
			{});

			*succeeded = 1;
			return 1;
		}
	}

	*succeeded = 0;
	return 1;
}

static signed char Lexer_tryParseIntrinsic(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	// NOTE: this `intrinsicTokenKindsCount` define must be changed when modifying the `intrinsicTokenKinds` set!
	#define intrinsicTokenKindsCount ((unsigned int)37)
	static const struct Lexer_TokenTemplate intrinsicTokenKinds[] =
	{
		[TOKEN_KIND_INTRINSIC_ADD] = { "add", 3 },
		[TOKEN_KIND_INTRINSIC_SUBTRACT] = { "subtract", 8 },
		[TOKEN_KIND_INTRINSIC_MULTIPLY] = { "multiply", 8 },
		[TOKEN_KIND_INTRINSIC_DIVIDE] = { "divide", 6 },
		[TOKEN_KIND_INTRINSIC_MODULUS] = { "modulus", 7 },
		[TOKEN_KIND_INTRINSIC_EQUAL] = { "equal", 5 },
		[TOKEN_KIND_INTRINSIC_NEQUAL] = { "nequal", 6 },
		[TOKEN_KIND_INTRINSIC_GREATER] = { "greater", 7 },
		[TOKEN_KIND_INTRINSIC_LESS] = { "less", 4 },
		[TOKEN_KIND_INTRINSIC_BAND] = { "band", 4 },
		[TOKEN_KIND_INTRINSIC_BOR] = { "bor", 3 },
		[TOKEN_KIND_INTRINSIC_BNOT] = { "bnot", 4 },
		[TOKEN_KIND_INTRINSIC_XOR] = { "xor", 3 },
		[TOKEN_KIND_INTRINSIC_SHIFTL] = { "shiftl", 6 },
		[TOKEN_KIND_INTRINSIC_SHIFTR] = { "shiftr", 6 },
		[TOKEN_KIND_INTRINSIC_AND] = { "and", 3 },
		[TOKEN_KIND_INTRINSIC_OR] = { "or", 2 },
		[TOKEN_KIND_INTRINSIC_NOT] = { "not", 3 },
		[TOKEN_KIND_INTRINSIC_SYSCALL0] = { "syscall0", 8 },
		[TOKEN_KIND_INTRINSIC_SYSCALL1] = { "syscall1", 8 },
		[TOKEN_KIND_INTRINSIC_SYSCALL2] = { "syscall2", 8 },
		[TOKEN_KIND_INTRINSIC_SYSCALL3] = { "syscall3", 8 },
		[TOKEN_KIND_INTRINSIC_SYSCALL4] = { "syscall4", 8 },
		[TOKEN_KIND_INTRINSIC_SYSCALL5] = { "syscall5", 8 },
		[TOKEN_KIND_INTRINSIC_SYSCALL6] = { "syscall6", 8 },
		[TOKEN_KIND_INTRINSIC_CLONE] = { "clone", 5 },
		[TOKEN_KIND_INTRINSIC_DROP] = { "drop", 4 },
		[TOKEN_KIND_INTRINSIC_OVER] = { "over", 4 },
		[TOKEN_KIND_INTRINSIC_SWAP] = { "swap", 4 },
		[TOKEN_KIND_INTRINSIC_READ8] = { "read8", 5 },
		[TOKEN_KIND_INTRINSIC_READ16] = { "read16", 6 },
		[TOKEN_KIND_INTRINSIC_READ32] = { "read32", 6 },
		[TOKEN_KIND_INTRINSIC_READ64] = { "read64", 6 },
		[TOKEN_KIND_INTRINSIC_WRITE8] = { "write8", 6 },
		[TOKEN_KIND_INTRINSIC_WRITE16] = { "write16", 7 },
		[TOKEN_KIND_INTRINSIC_WRITE32] = { "write32", 7 },
		[TOKEN_KIND_INTRINSIC_WRITE64] = { "write64", 7 }
	};
	static_assert((TOKEN_KIND_LAST_INTRINSIC - TOKEN_KIND_FIRST_INTRINSIC + 1) == intrinsicTokenKindsCount,
		"The local `intrinsicTokenKinds` set is not synced with updated types enum!");
	#undef intrinsicTokenKindsCount

	unsigned long long wordLength = 0;

	for (const char* temp = _lexer_current; temp < _lexer_end; ++temp)
	{
		signed char isWhitespaceChar = 0;

		W_Lexer_isWhitespaceChar(*temp, &isWhitespaceChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to check if char is a whitespace!");
			// *succeeded = 0;
			return 1;
		},
		{});

		if (isWhitespaceChar)
		{
			break;
		}

		++wordLength;
	}

	if (wordLength <= 0)
	{
		*succeeded = 0;
		return 1;
	}

	for (signed long long type = TOKEN_KIND_FIRST_INTRINSIC; type <= TOKEN_KIND_LAST_INTRINSIC; ++type)
	{
		const char* intrinsicTokenKind = intrinsicTokenKinds[type].name;
		const unsigned long long intrinsicTokenKindLength = intrinsicTokenKinds[type].length;

		if ((wordLength == intrinsicTokenKindLength) && (strncmp(_lexer_current, intrinsicTokenKind, intrinsicTokenKindLength) == 0))
		{
			// NOTES:
			//     1. Token is allocated on the heap. It should be deallocated at any error or crash of the compiler.
			//     2. Tokens are handled in the main process of the compiler.
			//     3. I do not handle the deallocation of the token in case of an errors below with mallocs for buffers
			//        and sources, because these errors will not crash the compiler and all the memory it used will be
			//        deallocated either way. So, there is no need to deallocated the token in case of the following
			//        errors right now. (Need to keep in mind in the future!)
			struct Token* token = NULL;

			W_Token_create(&token, _lexer_id++, type, &_lexer_location, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to add token to tokens list!");
				// *succeeded = 0;
				return 1;
			},
			{});

			token->source.buffer = NULL;

			W_RTM_malloc((const void** const)&token->source.buffer, wordLength * sizeof(char), succeeded,
			{
				// NOTES:
				//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
				//        is going to be shut down either way.
				W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to push new memory block to !");

				// NOTES:
				//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
				//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
				//        big of a deal to leave a single token.
				W_Token_destroy((const struct Token* const * const)&token, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					*succeeded = 0;
					return 0;
				},
				{});

				*succeeded = 0;
				return 1;
			},
			{});

			memcpy(token->source.buffer, _lexer_current, wordLength);
			token->source.length = wordLength;

			W_Lexer_moveBy(wordLength, succeeded,
			{
				// NOTES:
				//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
				//        is going to be shut down either way.
				W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to move the lexer's pointer!");

				// NOTES:
				//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
				//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
				//        big of a deal to leave a single token.
				W_Token_destroy((const struct Token* const * const)&token, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					*succeeded = 0;
					return 0;
				},
				{});

				*succeeded = 0;
				return 1;
			},
			{});

			W_Vector_pushLast(tokens, (void* const)token, succeeded,
			{
				// NOTES:
				//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
				//        is going to be shut down either way.
				W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to add token to tokens list!");

				// NOTES:
				//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
				//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
				//        big of a deal to leave a single token.
				W_Token_destroy((const struct Token* const * const)&token, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					*succeeded = 0;
					return 0;
				},
				{});

				*succeeded = 0;
				return 1;
			},
			{});

			*succeeded = 1;
			return 1;
		}
	}

	*succeeded = 0;
	return 1;
}

static signed char Lexer_tryParseDecorator(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	// NOTE: this `decoratorTokenKindsCount` define must be changed when modifying the `decoratorTokenKinds` set!
	#define decoratorTokenKindsCount ((unsigned int)3)
	static const struct Lexer_TokenTemplate decoratorTokenKinds[] =
	{
		[TOKEN_KIND_DECORATOR_COMPILE_TIME] = { "@compile_time", 13 },
		[TOKEN_KIND_DECORATOR_SUPPRESS_WARNINGS] = { "@suppress_warnings", 18 },
		[TOKEN_KIND_DECORATOR_NOT_IMPLEMENTED] = { "@not_implemented", 16 }
	};
	static_assert((TOKEN_KIND_LAST_DECORATOR - TOKEN_KIND_FIRST_DECORATOR + 1) == decoratorTokenKindsCount,
		"The local `decoratorTokenKinds` set is not synced with updated types enum!");
	#undef decoratorTokenKindsCount

	unsigned long long wordLength = 0;

	for (const char* temp = _lexer_current; temp < _lexer_end; ++temp)
	{
		signed char isWhitespaceChar = 0;

		W_Lexer_isWhitespaceChar(*temp, &isWhitespaceChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to check if char is a whitespace!");
			// *succeeded = 0;
			return 1;
		},
		{});

		if (isWhitespaceChar)
		{
			break;
		}

		++wordLength;
	}

	if (wordLength <= 0)
	{
		*succeeded = 0;
		return 1;
	}

	for (signed long long type = TOKEN_KIND_FIRST_DECORATOR; type <= TOKEN_KIND_LAST_DECORATOR; ++type)
	{
		const char* decoratorTokenKind = decoratorTokenKinds[type].name;
		const unsigned long long decoratorTokenKindLength = decoratorTokenKinds[type].length;

		if ((wordLength == decoratorTokenKindLength) && (strncmp(_lexer_current, decoratorTokenKind, decoratorTokenKindLength) == 0))
		{
			// NOTES:
			//     1. Token is allocated on the heap. It should be deallocated at any error or crash of the compiler.
			//     2. Tokens are handled in the main process of the compiler.
			//     3. I do not handle the deallocation of the token in case of an errors below with mallocs for buffers
			//        and sources, because these errors will not crash the compiler and all the memory it used will be
			//        deallocated either way. So, there is no need to deallocated the token in case of the following
			//        errors right now. (Need to keep in mind in the future!)
			struct Token* token = NULL;

			W_Token_create(&token, _lexer_id++, type, &_lexer_location, succeeded,
			{
				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to add token to tokens list!");
				// *succeeded = 0;
				return 1;
			},
			{});

			token->source.buffer = NULL;

			W_RTM_malloc((const void** const)&token->source.buffer, wordLength * sizeof(char), succeeded,
			{
				// NOTES:
				//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
				//        is going to be shut down either way.
				W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to push new memory block to !");

				// NOTES:
				//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
				//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
				//        big of a deal to leave a single token.
				W_Token_destroy((const struct Token* const * const)&token, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					*succeeded = 0;
					return 0;
				},
				{});

				*succeeded = 0;
				return 1;
			},
			{});

			memcpy(token->source.buffer, _lexer_current, wordLength);
			token->source.length = wordLength;

			W_Lexer_moveBy(wordLength, succeeded,
			{
				// NOTES:
				//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
				//        is going to be shut down either way.
				W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to move the lexer's pointer!");

				// NOTES:
				//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
				//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
				//        big of a deal to leave a single token.
				W_Token_destroy((const struct Token* const * const)&token, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					*succeeded = 0;
					return 0;
				},
				{});

				*succeeded = 0;
				return 1;
			},
			{});

			W_Vector_pushLast(tokens, (void* const)token, succeeded,
			{
				// NOTES:
				//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
				//        is going to be shut down either way.
				W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

				*succeeded = 0;
				return 0;
			},
			{
				W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
					"failed to add token to tokens list!");

				// NOTES:
				//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
				//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
				//        big of a deal to leave a single token.
				W_Token_destroy((const struct Token* const * const)&token, succeeded,
				{
					*succeeded = 0;
					return 0;
				},
				{
					*succeeded = 0;
					return 0;
				},
				{});

				*succeeded = 0;
				return 1;
			},
			{});

			*succeeded = 1;
			return 1;
		}
	}

	*succeeded = 0;
	return 1;
}

static signed char Lexer_tryParseIdentifier(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	signed char isFirstCharIdentifierChar = 0;

	// Checking for invalid first symbol
	W_Lexer_isIdentifierChar(*_lexer_current, &isFirstCharIdentifierChar, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided char was not an identifier char!");
		// *succeeded = 0;
		return 1;
	},
	{});

	if (isdigit(*_lexer_current) || *_lexer_current == '.') // First char of an identifier must not be a digit or a dot.
	{
		*succeeded = 0;
		return 1;
	}

	signed char dotsExist = 0;
	unsigned long long wordLength = 0;

	for (const char* temp = _lexer_current; temp < _lexer_end; ++temp)
	{
		signed char isIdentifierChar = 0;

		W_Lexer_isIdentifierChar(*temp, &isIdentifierChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"provided char was not an identifier char!");
			// *succeeded = 0;
			return 1;
		},
		{});

		if (!isIdentifierChar)
		{
			break;
		}

		if (*temp == '.')
		{
			++dotsExist;
		}

		signed char isWhitespaceChar = 0;

		W_Lexer_isWhitespaceChar(*temp, &isWhitespaceChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to check if char is a whitespace!");
			// *succeeded = 0;
			return 1;
		},
		{});

		if (isWhitespaceChar)
		{
			break;
		}

		++wordLength;
	}

	if (wordLength <= 0)
	{
		*succeeded = 0;
		return 1;
	}

	if (*(_lexer_current + wordLength - 1) == '.')
	{
		*succeeded = 0;
		return 1;
	}

	// NOTES:
	//     1. Token is allocated on the heap. It should be deallocated at any error or crash of the compiler.
	//     2. Tokens are handled in the main process of the compiler.
	//     3. I do not handle the deallocation of the token in case of an errors below with mallocs for buffers
	//        and sources, because these errors will not crash the compiler and all the memory it used will be
	//        deallocated either way. So, there is no need to deallocated the token in case of the following
	//        errors right now. (Need to keep in mind in the future!)
	struct Token* token = NULL;

	if (!dotsExist)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_IDENTIFIER, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});
	}
	else
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_IDENTIFIERS, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});
	}

	token->source.buffer = NULL;

	W_RTM_malloc((const void** const)&token->source.buffer, wordLength * sizeof(char), succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to push new memory block to !");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	memcpy(token->source.buffer, _lexer_current, wordLength);
	token->source.length = wordLength;

	W_Lexer_moveBy(wordLength, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to move the lexer's pointer!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	W_Vector_pushLast(tokens, (void* const)token, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to add token to tokens list!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

static signed char Lexer_tryParseStringLiteral(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	if (*_lexer_current != '\"')
	{
		*succeeded = 0;
		return 1;
	}

	const char* literal = _lexer_current + 1;
	unsigned long long literalLength = 0;

	for (const char* iterator = _lexer_current + 1; 1; ++iterator, ++literalLength)
	{
		if (*(iterator) == '\"' && (iterator - 1 >= _lexer_begin) && *(iterator - 1) != '\"') break;
		if (*(iterator) == '\"' && (iterator - 2 >= _lexer_begin) && *(iterator - 1) == '\"' && *(iterator - 2) == '\"') break;
	}

	unsigned long long bytesLength = 0;

	for (unsigned long long index = 0; index < literalLength; ++index, ++bytesLength)
	{
		if (literal[index] == '\\' && index + 1 < literalLength)
		{
			switch (literal[index + 1])
			{
				case 'a':
				{
					bytesLength -= 1;
				} break;

				case 'b':
				{
					bytesLength -= 1;
				} break;

				case 'f':
				{
					bytesLength -= 1;
				} break;

				case 'n':
				{
					bytesLength -= 1;
				} break;

				case 'r':
				{
					bytesLength -= 1;
				} break;

				case 't':
				{
					bytesLength -= 1;
				} break;

				case 'v':
				{
					bytesLength -= 1;
				} break;

				case '\\':
				{
					bytesLength -= 1;
				} break;

				case '\'':
				{
					bytesLength -= 0;
				} break;

				case '\"':
				{
					bytesLength -= 1;
				} break;

				case '\?':
				{
					bytesLength -= 1;
				} break;

				default:
				{
				} break;
			}
		}
	}

	unsigned char* bytes = NULL;

	W_RTM_malloc((const void** const)&bytes, bytesLength * sizeof(char), succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to push new memory block to !");
		// *succeeded = 0;
		return 1;
	},
	{});

	for (unsigned long long index = 0, iter = 0; index < literalLength;)
	{
		if (literal[index] == '\\' && index + 2 <= literalLength)
		{
			switch (literal[index + 1])
			{
				case 'a':
				{
					memset(bytes + iter, '\a', 1);
					++iter;
					index += 2;
				} break;

				case 'b':
				{
					memset(bytes + iter, '\b', 1);
					++iter;
					index += 2;
				} break;

				case 'f':
				{
					memset(bytes + iter, '\f', 1);
					++iter;
					index += 2;
				} break;

				case 'n':
				{
					memset(bytes + iter, '\n', 1);
					++iter;
					index += 2;
				} break;

				case 'r':
				{
					memset(bytes + iter, '\r', 1);
					++iter;
					index += 2;
				} break;

				case 't':
				{
					memset(bytes + iter, '\t', 1);
					++iter;
					index += 2;
				} break;

				case 'v':
				{
					memset(bytes + iter, '\v', 1);
					++iter;
					index += 2;
				} break;

				case '\\':
				{
					memset(bytes + iter, '\\', 1);
					++iter;
					index += 2;
				} break;

				case '\'':
				{
					memset(bytes + iter, '\'', 1);
					++iter;
					index += 2;
				} break;

				case '\"':
				{
					memset(bytes + iter, '\"', 1);
					++iter;
					index += 2;
				} break;

				case '\?':
				{
					memset(bytes + iter, '\?', 1);
					++iter;
					index += 2;
				} break;

				default:
				{
					index += 1;
				} break;
			}
		}
		else
		{
			bytes[iter++] = literal[index];
			index += 1;
		}
	}

	// NOTES:
	//     1. Token is allocated on the heap. It should be deallocated at any error or crash of the compiler.
	//     2. Tokens are handled in the main process of the compiler.
	//     3. I do not handle the deallocation of the token in case of an errors below with mallocs for buffers
	//        and sources, because these errors will not crash the compiler and all the memory it used will be
	//        deallocated either way. So, there is no need to deallocated the token in case of the following
	//        errors right now. (Need to keep in mind in the future!)
	struct Token* token = NULL;

	W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_STRING, &_lexer_location, succeeded,
	{
		// NOTES:
		//     1. Need to free bytes array because it will get lost at this stage of the compiler!
		W_RTM_free((const void* const * const)&bytes, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to add token to tokens list!");

		// NOTES:
		//     1. Need to free bytes array because it will get lost at this stage of the compiler!
		W_RTM_free((const void* const * const)&bytes, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	token->value.string.bytes = bytes;
	token->value.string.length = bytesLength;

	token->source.buffer = NULL;

	W_RTM_malloc((const void** const)&token->source.buffer, literalLength * sizeof(char), succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to push new memory block to !");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	memcpy(token->source.buffer, literal, literalLength);
	token->source.length = literalLength;

	W_Lexer_moveBy(literalLength + 2, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to move the lexer's pointer!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	W_Vector_pushLast(tokens, (void* const)token, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to add token to tokens list!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

static signed char Lexer_tryParseSignedIntegerLiteral(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	const char prefix = *_lexer_current;
	
	if (!(isdigit(prefix) || prefix == '+' || prefix == '-'))
	{
		*succeeded = 0;
		return 1;
	}

	const char* literal = _lexer_current;
	unsigned long long literalLength = 1;
	for (const char* iterator = _lexer_current + 1; isdigit(*iterator) && iterator < _lexer_end; ++iterator, ++literalLength);

	if (literalLength <= 0)
	{
		*succeeded = 0;
		return 1;
	}

	if (*(literal + literalLength) != 'i')
	{
		*succeeded = 0;
		return 1;
	}

	if (literal + literalLength + 1 < _lexer_end)
	{
		signed char isWhitespaceChar = 0;

		W_Lexer_isWhitespaceChar(*(literal + literalLength + 1), &isWhitespaceChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 1;
		},
		{});

		if (!isWhitespaceChar)
		{
			*succeeded = 0;
			return 1;
		}
	}

	++literalLength;
	signed long long literalValue = 0;

	if (sscanf(literal, "%lld", &literalValue) != 1)
	{
		// NOTE: should not log, because it is supposed to fail if the source is not numeric literal.
		*succeeded = 0;
		return 1;
	}

	// NOTES:
	//     1. Token is allocated on the heap. It should be deallocated at any error or crash of the compiler.
	//     2. Tokens are handled in the main process of the compiler.
	//     3. I do not handle the deallocation of the token in case of an errors below with mallocs for buffers
	//        and sources, because these errors will not crash the compiler and all the memory it used will be
	//        deallocated either way. So, there is no need to deallocated the token in case of the following
	//        errors right now. (Need to keep in mind in the future!)
	struct Token* token = NULL;

	if (literalValue >= INT8_MIN && literalValue <= INT8_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_I8, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.i8 = (signed char)literalValue;
	}
	else if (literalValue >= INT16_MIN && literalValue <= INT16_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_I16, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.i16 = (signed short)literalValue;
	}
	else if (literalValue >= INT32_MIN && literalValue <= INT32_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_I32, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.i32 = (signed int)literalValue;
	}
	else // if (literalValue >= INT64_MIN && literalValue <= INT64_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_I64, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.i64 = (signed long long)literalValue;
	}

	token->source.buffer = NULL;

	W_RTM_malloc((const void** const)&token->source.buffer, literalLength * sizeof(char), succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to push new memory block to !");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	memcpy(token->source.buffer, literal, literalLength);
	token->source.length = literalLength;

	W_Lexer_moveBy(literalLength, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to move the lexer's pointer!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	W_Vector_pushLast(tokens, (void* const)token, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to add token to tokens list!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

static signed char Lexer_tryParseUnsignedIntegerLiteral(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	const char prefix = *_lexer_current;
	
	if (!(isdigit(prefix) || prefix == '+'))
	{
		*succeeded = 0;
		return 1;
	}

	const char* literal = _lexer_current;
	unsigned long long literalLength = 1;
	for (const char* iterator = _lexer_current + 1; isdigit(*iterator) && iterator < _lexer_end; ++iterator, ++literalLength);

	if (literalLength <= 0)
	{
		*succeeded = 0;
		return 1;
	}

	if (*(literal + literalLength) != 'u')
	{
		*succeeded = 0;
		return 1;
	}

	if (literal + literalLength + 1 < _lexer_end)
	{
		signed char isWhitespaceChar = 0;

		W_Lexer_isWhitespaceChar(*(literal + literalLength + 1), &isWhitespaceChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 1;
		},
		{});

		if (!isWhitespaceChar)
		{
			*succeeded = 0;
			return 1;
		}
	}

	++literalLength;
	unsigned long long literalValue = 0;

	if (sscanf(literal, "%llu", &literalValue) != 1)
	{
		// NOTE: should not log, because it is supposed to fail if the source is not numeric literal.
		*succeeded = 0;
		return 1;
	}

	// NOTES:
	//     1. Token is allocated on the heap. It should be deallocated at any error or crash of the compiler.
	//     2. Tokens are handled in the main process of the compiler.
	//     3. I do not handle the deallocation of the token in case of an errors below with mallocs for buffers
	//        and sources, because these errors will not crash the compiler and all the memory it used will be
	//        deallocated either way. So, there is no need to deallocated the token in case of the following
	//        errors right now. (Need to keep in mind in the future!)
	struct Token* token = NULL;

	if (literalValue <= UINT8_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_U8, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.u8 = (unsigned char)literalValue;
	}
	else if (literalValue <= UINT16_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_U16, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.u16 = (unsigned short)literalValue;
	}
	else if (literalValue <= UINT32_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_U32, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.u32 = (unsigned int)literalValue;
	}
	else // if (literalValue >= INT64_MIN && literalValue <= INT64_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_U64, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.u64 = (unsigned long long)literalValue;
	}

	token->source.buffer = NULL;

	W_RTM_malloc((const void** const)&token->source.buffer, literalLength * sizeof(char), succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to push new memory block to !");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	memcpy(token->source.buffer, literal, literalLength);
	token->source.length = literalLength;

	W_Lexer_moveBy(literalLength, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to move the lexer's pointer!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	W_Vector_pushLast(tokens, (void* const)token, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to add token to tokens list!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

static signed char Lexer_tryParseFloatingPointLiteral(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	const char prefix = *_lexer_current;
	
	if (!(isdigit(prefix) || prefix == '-' || prefix == '+'))
	{
		*succeeded = 0;
		return 1;
	}

	const char* literal = _lexer_current;
	unsigned long long literalLength = 1;
	unsigned int dotsCount = 0;

	for (const char* iterator = _lexer_current + 1; (isdigit(*iterator) || *iterator == '.') && iterator < _lexer_end; ++iterator, ++literalLength)
	{
		if (*iterator == '.') ++dotsCount;
	}

	if (literalLength <= 0)
	{
		*succeeded = 0;
		return 1;
	}

	if (dotsCount > 1)
	{
		*succeeded = 0;
		return 1;
	}

	if (*(literal + literalLength) != 'f')
	{
		*succeeded = 0;
		return 1;
	}

	if (literal + literalLength + 1 < _lexer_end)
	{
		signed char isWhitespaceChar = 0;

		W_Lexer_isWhitespaceChar(*(literal + literalLength + 1), &isWhitespaceChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 1;
		},
		{});

		if (!isWhitespaceChar)
		{
			*succeeded = 0;
			return 1;
		}
	}

	++literalLength;
	long double literalValue = 0;

	if (sscanf(literal, "%Lf", &literalValue) != 1)
	{
		// NOTE: should not log, because it is supposed to fail if the source is not numeric literal.
		*succeeded = 0;
		return 1;
	}

	// NOTES:
	//     1. Token is allocated on the heap. It should be deallocated at any error or crash of the compiler.
	//     2. Tokens are handled in the main process of the compiler.
	//     3. I do not handle the deallocation of the token in case of an errors below with mallocs for buffers
	//        and sources, because these errors will not crash the compiler and all the memory it used will be
	//        deallocated either way. So, there is no need to deallocated the token in case of the following
	//        errors right now. (Need to keep in mind in the future!)
	struct Token* token = NULL;

	if (literalValue >= -FLT_MAX && literalValue <= FLT_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_F32, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.f32 = (float)literalValue;
	}
	else // if (literalValue >= -LDBL_MAX && literalValue <= LDBL_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_F64, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.f64 = (long double)literalValue;
	}

	token->source.buffer = NULL;

	W_RTM_malloc((const void** const)&token->source.buffer, literalLength * sizeof(char), succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to push new memory block to !");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	memcpy(token->source.buffer, literal, literalLength);
	token->source.length = literalLength;

	W_Lexer_moveBy(literalLength, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to move the lexer's pointer!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	W_Vector_pushLast(tokens, (void* const)token, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to add token to tokens list!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

static signed char Lexer_tryParsePointerLiteral(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	const char prefix = *_lexer_current;
	
	if (!isdigit(prefix))
	{
		*succeeded = 0;
		return 1;
	}

	const char* literal = _lexer_current;
	unsigned long long literalLength = 1;
	for (const char* iterator = _lexer_current + 1; isdigit(*iterator) && iterator < _lexer_end; ++iterator, ++literalLength);

	if (literalLength <= 0)
	{
		*succeeded = 0;
		return 1;
	}

	if (*(literal + literalLength) != 'p')
	{
		*succeeded = 0;
		return 1;
	}

	if (literal + literalLength + 1 < _lexer_end)
	{
		signed char isWhitespaceChar = 0;

		W_Lexer_isWhitespaceChar(*(literal + literalLength + 1), &isWhitespaceChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 1;
		},
		{});

		if (!isWhitespaceChar)
		{
			*succeeded = 0;
			return 1;
		}
	}

	++literalLength;
	unsigned long long literalValue = 0;

	if (sscanf(literal, "%llu", &literalValue) != 1)
	{
		// NOTE: should not log, because it is supposed to fail if the source is not numeric literal.
		*succeeded = 0;
		return 1;
	}

	// NOTES:
	//     1. Token is allocated on the heap. It should be deallocated at any error or crash of the compiler.
	//     2. Tokens are handled in the main process of the compiler.
	//     3. I do not handle the deallocation of the token in case of an errors below with mallocs for buffers
	//        and sources, because these errors will not crash the compiler and all the memory it used will be
	//        deallocated either way. So, there is no need to deallocated the token in case of the following
	//        errors right now. (Need to keep in mind in the future!)
	struct Token* token = NULL;

	if (literalValue <= UINT8_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_P8, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.p8 = (unsigned char)literalValue;
	}
	else if (literalValue <= UINT16_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_P16, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.p16 = (unsigned short)literalValue;
	}
	else if (literalValue <= UINT32_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_P32, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.p32 = (unsigned int)literalValue;
	}
	else // if (literalValue >= INT64_MIN && literalValue <= INT64_MAX)
	{
		W_Token_create(&token, _lexer_id++, TOKEN_KIND_LITERAL_P64, &_lexer_location, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to add token to tokens list!");
			// *succeeded = 0;
			return 1;
		},
		{});

		token->value.p64 = (unsigned long long)literalValue;
	}

	token->source.buffer = NULL;

	W_RTM_malloc((const void** const)&token->source.buffer, literalLength * sizeof(char), succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to push new memory block to !");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	memcpy(token->source.buffer, literal, literalLength);
	token->source.length = literalLength;

	W_Lexer_moveBy(literalLength, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to move the lexer's pointer!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	W_Vector_pushLast(tokens, (void* const)token, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to add token to tokens list!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

static signed char Lexer_tryParseInvalid(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	const char* word = _lexer_current;
	unsigned long long wordLength = 0;

	for (const char* temp = _lexer_current; temp < _lexer_end; ++temp)
	{
		signed char isWhitespaceChar = 0;

		W_Lexer_isWhitespaceChar(*temp, &isWhitespaceChar, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to check if char is a whitespace!");
			// *succeeded = 0;
			return 1;
		},
		{});

		if (isWhitespaceChar)
		{
			break;
		}

		++wordLength;
	}

	if (wordLength <= 0)
	{
		*succeeded = 0;
		return 1;
	}

	struct Token* token = NULL;

	// NOTES:
	//     1. Token is allocated on the heap. It should be deallocated at any error or crash of the compiler.
	//     2. Tokens are handled in the main process of the compiler.
	//     3. I do not handle the deallocation of the token in case of an errors below with mallocs for buffers
	//        and sources, because these errors will not crash the compiler and all the memory it used will be
	//        deallocated either way. So, there is no need to deallocated the token in case of the following
	//        errors right now. (Need to keep in mind in the future!)
	W_Token_create(&token, _lexer_id++, TOKEN_KIND_INVALID, &_lexer_location, succeeded,
	{
		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to add token to tokens list!");
		// *succeeded = 0;
		return 1;
	},
	{});

	token->source.buffer = NULL;

	W_RTM_malloc((const void** const)&token->source.buffer, wordLength * sizeof(char), succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to push new memory block to !");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	memcpy(token->source.buffer, word, wordLength);
	token->source.length = wordLength;

	W_Lexer_moveBy(wordLength, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to move the lexer's pointer!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	W_Vector_pushLast(tokens, (void* const)token, succeeded,
	{
		// NOTES:
		//     1. Not handling callbacks, because we are just trying to free the token. At this point the compiler
		//        is going to be shut down either way.
		W_Token_destroy((const struct Token* const * const)&token, succeeded, {}, {}, {});

		*succeeded = 0;
		return 0;
	},
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"failed to add token to tokens list!");

		// NOTES:
		//     1. Not handling callbacks, because if destroying the token failed once, it will probably fail more times.
		//     2. The compiler is going to be shut down either way and the memory is going to be deallocated, so not that
		//        big of a deal to leave a single token.
		W_Token_destroy((const struct Token* const * const)&token, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			*succeeded = 0;
			return 0;
		},
		{});

		*succeeded = 0;
		return 1;
	},
	{});

	*succeeded = 1;
	return 1;
}

static signed char Lexer_lexLine(
	struct Vector* const * const tokens,
	signed char* const succeeded)
{
	if (_lexer_begin == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_begin is invalid (null)!");
		return 0;
	}

	if (_lexer_current == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_current is invalid (null)!");
		return 0;
	}

	if (_lexer_end == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"global _lexer_end is invalid (null)!");
		return 0;
	}

	if (tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens` is invalid (null)!");
		return 0;
	}

	if (*tokens == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `tokens`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*succeeded = 0;

	// Handlng empty line
	if (_lexer_begin == _lexer_end)
	{
		*succeeded = 1;
		return 1;
	}

	while (_lexer_current < _lexer_end)
	{
		// Skip white space
		W_Lexer_skipWhitespaces(succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
				"failed to skip whitespaces!");
			// *succeeded = 0;
			return 1;
		},
		{});

		// Check if line was only white spaces and return if so
		if (_lexer_current == _lexer_end)
		{
			*succeeded = 1;
			return 1;
		}

		// Skip inline comment  
		if (*_lexer_current == '#')
		{
			*succeeded = 1;
			return 1;
		}

		// Trying to parse keyword
		W_Lexer_tryParseKeyword(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{},
		{
			continue;
		});

		// Trying to parse intrinsic
		W_Lexer_tryParseIntrinsic(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{},
		{
			continue;
		});

		// Trying to parse decorator
		W_Lexer_tryParseDecorator(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{},
		{
			continue;
		});

		// Trying to parse identifier
		W_Lexer_tryParseIdentifier(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{},
		{
			continue;
		});

		W_Lexer_tryParseStringLiteral(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			// *succeeded = 0;
		},
		{
			// *succeeded = 1;
			continue;
		});

		W_Lexer_tryParseSignedIntegerLiteral(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			// *succeeded = 0;
		},
		{
			// *succeeded = 1;
			continue;
		});

		W_Lexer_tryParseUnsignedIntegerLiteral(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			// *succeeded = 0;
		},
		{
			// *succeeded = 1;
			continue;
		});

		W_Lexer_tryParseFloatingPointLiteral(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			// *succeeded = 0;
		},
		{
			// *succeeded = 1;
			continue;
		});

		W_Lexer_tryParsePointerLiteral(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			// *succeeded = 0;
		},
		{
			// *succeeded = 1;
			continue;
		});

		// Trying to parse invalid
		W_Lexer_tryParseInvalid(tokens, succeeded,
		{
			*succeeded = 0;
			return 0;
		},
		{
			W_Logger_log(LOG_KIND_INTERNAL, _lexer_location, "%s",
				"failed to parse any kind of token!");
			// *succeeded = 0;
			return 0;
		},
		{});
	}

	*succeeded = 1;
	return 1;
}

/**
 * @}
 */
