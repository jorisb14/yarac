
/**
 * @file location.h
 *
 * @copyright This file is a part of the project yarac and is distributed under MIT license that
 * should have been included with the project. If not, see https://choosealicense.com/licenses/mit/
 *
 * @author jorisb
 *
 * @date 2022-10-31
 */

#ifndef _LOCATION_H_
#define _LOCATION_H_

/**
 * @addtogroup types
 * 
 * @{
 */

struct Location
{
	const char* file;
	unsigned long long line;
	unsigned long long column;
};

#if YARAC_DEBUG
#	define NO_LOCATION ((struct Location) { .file = (const char*)__FILE__, .line = (unsigned long long)__LINE__, .column = 0 })
#else
#	define NO_LOCATION ((struct Location) { .file = NULL, .line = 0, .column = 0 })
#endif

#define INVALID_LOCATION NO_LOCATION

/**
 * @}
 */

#endif
