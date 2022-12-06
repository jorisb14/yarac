
/**
 * @file rtm.c
 *
 * @copyright This file is a part of the project yarac and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-11-14
 */

#include <rtm.h>
#include <logger.h>

/**
 * @addtogroup rtm
 * 
 * @{
 */

#if YARAC_DEBUG
static signed long long _rtm_counter = 0;
#endif

signed char RTM_malloc(
	const void** const destination,
	const unsigned long long size,
	signed char* const succeeded)
{
	if (destination == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `destination` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*destination = (void*)malloc(size);

	if (*destination == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"function malloc(...) returned with an error! Failed to allocate memory!");
		*succeeded = 0;
		return 1;
	}

#if YARAC_DEBUG
	++_rtm_counter;
#endif

	*succeeded = 1;
	return 1;
}

signed char RTM_realloc(
	const void** const destination,
	const unsigned long long size,
	signed char* const succeeded)
{
	if (destination == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `destination` is invalid (null)!");
		return 0;
	}

	if (*destination == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `destination`'s deref is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	*destination = (void*)realloc((void*)(*destination), size);

	if (*destination == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"function realloc(...) returned with an error! Failed to allocate memory!");
		*succeeded = 0;
		return 1;
	}

	*succeeded = 1;
	return 1;
}

signed char RTM_free(
	const void* const * const source,
	signed char* const succeeded)
{
	if (source == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `source` is invalid (null)!");
		return 0;
	}

	if (succeeded == NULL)
	{
		W_Logger_log(LOG_KIND_INTERNAL, NO_LOCATION, "%s",
			"provided function parameter `succeeded` is invalid (null)!");
		return 0;
	}

	free((void*)(*source));

#if YARAC_DEBUG
	--_rtm_counter;
#endif

	*succeeded = 1;
	return 1;
}

/**
 * @}
 */
