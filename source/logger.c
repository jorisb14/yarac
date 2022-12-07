
/**
 * @file logger.c
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-10-31
 */

#include <logger.h>

#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

/**
 * @addtogroup logger
 * 
 * @{
 */

static const char* Logger_stringifyKind(
	const signed long long kind);

void Logger_log(
	const signed long long kind,
	const struct Location location,
	const struct Location sourceTrace,
	const char* functionName,
	const char* format,
	...)
{
	if (functionName == NULL)
	{
		return;
	}

	if (format == NULL)
	{
		return;
	}

	if (location.file == NULL && location.line == 0 && location.column == 0)
	{
		fprintf(stdout, "[no location]: %s: ",
			Logger_stringifyKind(kind));
	}
	else
	{
		fprintf(stdout, "%s:%llu:%llu: %s: ",
			location.file, location.line, location.column,
			Logger_stringifyKind(kind));
	}

	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
	fprintf(stdout, "\n");

#if YARAC_DEBUG
	if (location.file == NULL && location.line == 0 && location.column == 0)
	{
		fprintf(stdout, "[no location]: source trace: %s(...)\n",
			functionName);
	}
	else
	{
		fprintf(stdout, "%s:%llu:%llu: source trace: %s(...)\n",
			sourceTrace.file, sourceTrace.line, sourceTrace.column,
			functionName);
	}
#else
	(void)sourceTrace;
#endif
}

static const char* Logger_stringifyKind(
	const signed long long kind)
{
	#define GREEN(str)  "\033[32m"str"\033[0m"
	#define YELLOW(str) "\033[33m"str"\033[0m"
	#define RED(str)    "\033[31m"str"\033[0m"

	const char* stringifiedKind = NULL;

	switch (kind)
	{
		case LOG_KIND_SUCCESS:
		{
			stringifiedKind = GREEN("success");
		} break;

		case LOG_KIND_INFO:
		{
			stringifiedKind = "info";
		} break;

		case LOG_KIND_WARNING:
		{
			stringifiedKind = YELLOW("warning");
		} break;

		case LOG_KIND_ERROR:
		{
			stringifiedKind = RED("error");
		} break;

		case LOG_KIND_INTERNAL:
		{
			stringifiedKind = RED("internal");
		} break;

		default:
		{
			assert(!"Should never reach this block!");
			return NULL;
		} break;
	}

	return stringifiedKind;
}

/**
 * @}
 */
