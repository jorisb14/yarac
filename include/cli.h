
/**
 * @file cli.h
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-11-02
 */

#ifndef _CLI_H_
#define _CLI_H_

#include <containers.h>

/**
 * @addtogroup cli
 * 
 * @{
 */

struct CLI_Args
{
	struct List* includeDirectories;
	struct List* sources;
	const char* outputFormat;
	const char* artefactsDirectory;
	const char* optimizationMode;
};

/**
 * Create CLI arguments container. Return 0 in case of an error and 1 in case of a success. Should
 * be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     struct CLI_Args* args = NULL;
 *     assert(CLI_Args_create(&args, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
signed char CLI_Args_create(
	struct CLI_Args** const args,
	signed char* const succeeded);

#define W_CLI_Args_create(_inmacro_args, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!CLI_Args_create((_inmacro_args), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function CLI_Args_create(...) returned with internal failure!"); \
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
 * Destroy CLI arguments container. Return 0 in case of an error and 1 in case of a success. Should
 * be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     assert(W_CLI_Args_destroy(&args, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
signed char CLI_Args_destroy(
	const struct CLI_Args* const * const args,
	signed char* const succeeded);

#define W_CLI_Args_destroy(_inmacro_args, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!CLI_Args_destroy((_inmacro_args), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function CLI_Args_destroy(...) returned with internal failure!"); \
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
 * Parse the command-line and setup flags. Return 0 in case of an error and 1 in case of a success.
 * Should be used as this:
 * 
 * @code{.c}
 *     // ... 
 *     struct CLI_Args clArgs = {0};
 *     assert(CLI_tryParseArgs(&argc, &argv, &clArgs, &succeeded) == 1);
 *     assert(succeeded == 1);
 * @endcode
 */
signed char CLI_tryParseArgs(
	signed int* const argc,
	const char*** const argv,
	struct CLI_Args* const * const args,
	signed char* const succeeded);

#define W_CLI_tryParseArgs(_inmacro_argc, _inmacro_argv, _inmacro_args, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!CLI_tryParseArgs((_inmacro_argc), (_inmacro_argv), (_inmacro_args), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s", \
				"function CLI_tryParseArgs(...) returned with internal failure!"); \
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
