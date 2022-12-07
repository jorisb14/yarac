
/**
 * @file rtm.h
 *
 * @copyright This file is a part of the project yarac and is distributed under GNU GPLv3 license
 * that should have been included with the project.
 * If not, see https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * @author jorisb
 *
 * @date 2022-11-14
 */

#ifndef _RTM_H_
#define _RTM_H_

/**
 * @addtogroup rtm
 * 
 * @{
 */

signed char RTM_malloc(
	const void** const destination,
	const unsigned long long size,
	signed char* const succeeded);

#define W_RTM_malloc(_inmacro_destination, _inmacro_size, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!RTM_malloc((_inmacro_destination), (_inmacro_size), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function RTM_malloc(...) returned with internal failure!"); \
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

signed char RTM_realloc(
	const void** const destination,
	const unsigned long long size,
	signed char* const succeeded);

#define W_RTM_realloc(_inmacro_destination, _inmacro_size, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!RTM_realloc((_inmacro_destination), (_inmacro_size), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function RTM_realloc(...) returned with internal failure!"); \
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

signed char RTM_free(
	const void* const * const source,
	signed char* const succeeded);

#define W_RTM_free(_inmacro_source, _inmacro_succeeded, _inmacro_internalFailCallback, _inmacro_logicalFailCallback, _inmacro_successCallback) \
	{ \
		if (!RTM_free((_inmacro_source), (_inmacro_succeeded))) \
		{ \
			W_Logger_log(LOG_KIND_INTERNAL, INTERNAL_LOCATION, "%s", \
				"function RTM_free(...) returned with internal failure!"); \
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
