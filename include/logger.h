
/**
 * @file logger.h
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-10-31
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <location.h>

#include <stdlib.h>

/**
 * @addtogroup logger
 * 
 * @{
 */

enum
{
	LOG_KIND_SUCCESS = 0,
	LOG_KIND_INFO,
	LOG_KIND_WARNING,
	LOG_KIND_ERROR,
	LOG_KIND_INTERNAL,

	LOG_KINDS_COUNT
};

void Logger_log(
	const signed long long kind,
	const struct Location location,
	const struct Location sourceTrace,
	const char* functionName,
	const char* format,
	...);

#define W_Logger_log(kind, location, format, ...) \
	{ \
		Logger_log((kind), (location), (struct Location) { .file = __FILE__, .line = (unsigned long long)__LINE__, .column = 0 }, __func__, (format), __VA_ARGS__); \
	}

/**
 * @}
 */

#endif
